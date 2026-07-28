# AQR Trading

AQR 是建立在 vn.py 之上的 A 股自动化交易执行框架。本目录按
《AQR v1.1：面向自动化实盘的 A 股量化交易系统开发框架》实施。

当前迭代只实现 Phase 0（AQR-001～016）：先保证订单意图、Transactional
Outbox、vn.py、交易事件、投影、对账和熔断形成正确闭环。研究模型、选股和
组合优化不能调用 `MainEngine.send_order`，将在后续阶段通过
`execution.command_outbox` 接入。

## 当前运行结构

```text
OrderIntent + CommandOutbox (同一 PostgreSQL 事务)
        ↓ FOR UPDATE SKIP LOCKED
OutboxCommandConsumer
        ↓
AqrExecutionApp → RiskManagerApp → PaperAccountApp
        ↓
Order/Trade/Position/Account events
        ↓
ExecutionEventBridge
        ↓
Event Store + Projection + Reconciliation
```

PostgreSQL 是唯一持久化事实源。`.venv`、vn.py OMS 和 PaperAccount 的内存
状态都只是运行缓存。

## 本机快速开始

项目当前复用 Docker 容器 `qts-postgres` 的 PostgreSQL 16，并使用隔离数据库
`aqr_core`。连接配置保存在未纳入 Git 的 `.env`。

```powershell
cd C:\Users\14463\Documents\VNPY
.\setup_windows.bat
.\aqr\migrate_windows.bat
.\aqr\test_windows.bat
.\aqr\start_execution_windows.bat
```

Execution Service 启动时默认处于 HALT，只有 PostgreSQL 可用且启动对账通过
后才开始消费 Outbox。数据库、Gateway 或对账失败时均 Fail Closed。

## 数据库迁移

```powershell
cd aqr
$env:AQR_DATABASE_URL="postgresql+psycopg://user:password@localhost:5432/aqr_core"
..\.venv\Scripts\python.exe -m alembic upgrade head
```

主要 Schema：

- `execution`: order_intent、command_outbox、order_event、order_projection、
  trade_fill、position_projection、account_snapshot
- `reconciliation`: run、diff
- `audit`: system_alert

## 安全边界

- 只有 `aqr-execution-vnpy` 进程能调用 vn.py 下单/撤单接口。
- `UNKNOWN` 委托不得自动重发。
- Outbox 命令按 `(account_id, client_order_id)` 幂等。
- vn.py 事件按 `(gateway_name, deduplication_key)` 去重。
- Live 配置默认启用 `shadow_mode`，尚未开放真实资金。

项目架构基线见 [docs/AQR_V1.1_FRAMEWORK.md](docs/AQR_V1.1_FRAMEWORK.md)，
详细实施状态见 [docs/DEVELOPMENT_PLAN.md](docs/DEVELOPMENT_PLAN.md)。
