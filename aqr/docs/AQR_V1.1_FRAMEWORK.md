# AQR v1.1：面向自动化实盘的 A 股量化交易系统开发框架

> 项目基线文档。由用户提供的 AQR v1.1 原始设计纳入仓库，自 2026-07-27
> 起作为架构边界、开发顺序和验收标准。若实现与本文冲突，以 Fail Closed、
> PostgreSQL 事实源、单写者和不可绕过执行链路的原则为准。

## 1. 终局目标

```text
自动更新数据
→ 自动研究和模型推理
→ 自动构建目标组合
→ 自动执行组合风控
→ 自动生成订单
→ vn.py 自动下单
→ 自动处理委托与成交回报
→ 自动更新账户和持仓
→ 自动对账
→ 异常自动熔断并通知
```

第一版起必须具备：

- vn.py 常驻交易运行时；
- 完整订单状态机；
- PostgreSQL 唯一持久化账本；
- 模拟盘和实盘共用同一执行接口；
- 所有指令幂等；
- 启动、盘中和盘后自动对账；
- 研究状态与实际账户状态严格分离；
- 任意交易可追溯至数据、模型、风控和订单事件。

第一阶段不使用真实资金，但禁止采用将来必须推翻的临时模拟架构。

## 2. 不可违反的架构原则

### 2.1 PostgreSQL 是唯一持久化事实源

PostgreSQL 永久保存数据集版本、模型实验、信号、目标持仓、风控结果、订单
意图、vn.py 委托/成交事件、实际持仓、账户快照、对账结果、告警和人工干预。
vn.py 内存 OMS 只是实时缓存。服务重启必须用数据库历史、券商查询和 Gateway
回报重建交易状态。

### 2.2 研究层不能直接下单

Qlib、vectorbt、Notebook、Dashboard 和 AI Agent 无权调用 `send_order`。
唯一合法路径：

```text
模型信号
→ 目标组合
→ 组合风控
→ 订单计划
→ 执行前审批
→ PostgreSQL Command Outbox
→ vn.py Execution Runtime
→ Gateway
```

### 2.3 批处理与实时交易分离

Prefect 负责数据、特征、训练、推理、回测、组合、日报和归因。vn.py 负责实时
行情、交易时段、委托、撤单、回报、查询、实时风控和 Gateway。vn.py 必须是
独立、常驻、可自动恢复的服务，禁止作为 Prefect 临时任务启动。

## 3. 总体架构

```text
离线研究域
数据源 → PostgreSQL/Parquet → Qlib/vectorbt
      → Portfolio Constructor → AQR Portfolio RiskEngine
                                      │
                              ApprovedOrderPlan
                                      ▼
                  PostgreSQL Transaction + Command Outbox
                                      ▼
实时执行域
EventEngine → MainEngine/OMS → AqrExecutionApp
            → RiskManagerApp → PaperAccount/Broker Gateway
                                      ▼
                         Execution Event Bridge
                                      ▼
                     PostgreSQL Event Store/Projection
                                      ▼
                      Reconciliation/Alert/Audit
```

## 4. 运行进程

- `aqr-research-worker`：数据、因子、研究、模型、目标组合和组合风控。
- `aqr-execution-vnpy`：唯一允许调用 `send_order/cancel_order` 的常驻进程。
- `aqr-reconciliation`：启动、盘中、盘后对账和未知外部订单处理。
- `aqr-api`：查询、审批、暂停、恢复、撤单、审计；只能发送数据库命令。
- `aqr-dashboard`：只读系统状态、信号、风险、订单、成交、持仓和对账。

## 5. 一致性设计

### 5.1 Transactional Outbox

`execution.order_intent` 和 `execution.command_outbox` 必须在同一事务创建。
消费者使用：

```sql
SELECT *
FROM execution.command_outbox
WHERE status = 'PENDING'
ORDER BY created_at
FOR UPDATE SKIP LOCKED;
```

命令状态：`PENDING → CLAIMED → SENT → ACKNOWLEDGED`。数据库不可用时禁止新增
下单。

### 5.2 幂等

每个订单意图必须有全局唯一 `client_order_id`，数据库唯一约束为
`(account_id, client_order_id)`。建议格式：

```text
环境-账户-策略-交易日-证券-交易所-方向-序号
```

Gateway 事件通过 `(gateway_name, deduplication_key)` 去重，成交通过
`(gateway_name, external_trade_id)` 去重。

### 5.3 事件追加和单写者

每次订单变化追加独立事件，禁止覆盖历史。当前状态由投影生成。信号、组合、
风控、订单意图、委托成交、实际持仓、对账、审批各有唯一写入者；其他组件只读。

## 6. 订单状态机

订单意图：

```text
DRAFT → RISK_APPROVED → READY → DISPATCHED → CLOSED
```

异常：`RISK_REJECTED / EXPIRED / MANUAL_REJECTED / HALTED`。

实际订单：

```text
CREATED → SUBMITTING → SUBMITTED → ACCEPTED
        → PARTIALLY_FILLED → FILLED
```

其他终态：`REJECTED / CANCELLED / EXPIRED`。不确定态：`UNKNOWN`。

`UNKNOWN` 禁止自动重发，必须查询 Gateway/券商；无法确认时账户级熔断。
`FILLED → CANCELLED`、`REJECTED → PARTIALLY_FILLED`、
`CANCELLED → ACCEPTED` 等非法迁移必须拒绝。

## 7. AqrExecutionApp 边界

```text
AqrExecutionApp
├── OutboxCommandConsumer
├── OrderMapper
├── AccountRouter
├── ExecutionPolicy
├── EventBridge
├── KillSwitch
└── HeartbeatMonitor
```

它只负责批准命令的读取、vn.py 请求转换、Gateway 路由、委托/撤单、事件回写
和异常熔断，不负责因子、训练、选股、组合优化或长期投资判断。

## 8. 双层风控

AQR 组合风控回答“组合层面是否应该交易”，检查仓位、行业/风格暴露、回撤、
模型、流动性、ST/退市、涨跌停、换手和 CVaR。

vn.py 执行风控回答“现在是否允许发出”，检查单笔数量、频率、每日成交、活动
委托、撤单、Gateway、账户新鲜度、重复订单和价格偏离。

两层风控必须从同一配置源生成，任何风控故障都 Fail Closed。

## 9. PostgreSQL 边界

Schema：

```text
meta market research signal portfolio risk
execution reconciliation audit
```

Phase 0 核心表：

- `execution.order_intent`
- `execution.command_outbox`
- `execution.order_event`
- `execution.order_projection`
- `execution.trade_fill`
- `execution.position_projection`
- `execution.account_snapshot`
- `reconciliation.run`
- `reconciliation.diff`
- `audit.system_alert`

vn.py 自身行情数据库与 AQR 订单/风控/审计账本分离；AQR 表由
SQLAlchemy/Alembic 管理。

## 10. 对账

启动顺序：

```text
暂停新订单 → 连接 Gateway → 查询账户/持仓/委托/成交
→ 与 PostgreSQL 比较 → 处理差异 → 对账通过 → 恢复交易
```

盘中事件驱动并定期校验，盘后检查委托、成交、持仓、现金、资产、费用、未关闭
订单和未知外部订单。券商存在而系统不存在的订单标记
`EXTERNAL_UNKNOWN_ORDER` 并触发高等级告警。

## 11. 故障策略

| 故障 | 动作 |
|---|---|
| PostgreSQL 不可用 | 禁止新增下单 |
| Gateway 断开 | 暂停该账户 |
| 行情过期 | 禁止依赖实时价格的新订单 |
| 委托状态未知 | 暂停该证券或账户 |
| 持仓对账失败 | 账户级 HALT |
| 重复 Outbox/回报 | 幂等忽略 |
| 风控失败 | Fail Closed |
| 研究失败 | 不沿用旧日新信号 |
| Dashboard 失败 | 不影响交易运行 |
| 通知失败 | 持久化记录并重试 |

## 12. 环境晋级

1. 历史回放；
2. vn.py PaperAccount；
3. Shadow Mode；
4. 人工审批自动执行；
5. 白名单、极低资金、小范围自动执行；
6. 按稳定时间、对账率、状态完整率、滑点、风控、回撤和恢复能力扩容。

不能仅依据策略收益升级自动化范围。

## 13. 开发阶段

### Phase 0：状态和执行骨架

交付 PostgreSQL execution Schema、领域对象、Outbox、状态机、Event Store、
Projection、vn.py Execution Service、PaperAccount、RiskManager、启动对账和
Kill Switch。

验收闭环：

```text
创建订单意图 → Outbox → vn.py → 模拟委托 → 委托事件
→ 成交事件 → PostgreSQL → 持仓更新
```

### Phase 1：数据与研究

TuShare/AKShare、PostgreSQL+Parquet、时点化股票池、特征/标签、Qlib baseline
和 vectorbt 快筛。

### Phase 2：组合和双层风控

目标组合、skfolio、AQR RiskEngine、vn.py 风控配置映射和风控审计。

### Phase 3：实时模拟和故障注入

测试重启、数据库中断、Gateway 重连、重复/乱序回报、部分成交、未知订单、
持仓差异和交易日中途恢复。

### Phase 4：券商 Gateway

将 PaperAccount 替换为正式 A 股 Gateway，其他层不修改。

## 14. 第一批任务

Phase 0：AQR-001～AQR-016，依次完成项目/CI、数据库、领域对象、状态机、
order_intent、Outbox、headless vn.py、PaperAccount、RiskManager、
AqrExecutionApp、Mapper、Event Bridge、Projection、对账、Kill Switch/
Heartbeat 和 PaperAccount E2E。

Phase 1 及以后：AQR-017～AQR-028，依次完成 TuShare、AKShare、Parquet、
数据质量、因子标签、Qlib、vectorbt、目标组合、组合风控、研究到执行链路、
API/Dashboard 和故障注入。

## 15. 最终边界

```text
Qlib 决定希望持有什么
AQR RiskEngine 决定允许持有什么
vn.py 决定如何安全执行
券商决定实际成交了什么
PostgreSQL 记录系统最终知道什么
Reconciliation 确认这些状态是否一致
```
