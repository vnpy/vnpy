# AQR v1.1 实施计划

## Phase 0 当前迭代

| ID | 交付 | 状态 | 当前实现 |
|---|---|---|---|
| AQR-001 | 项目、CI、配置 | 已实现 | 独立包、YAML/.env 配置、Windows 脚本 |
| AQR-002 | PostgreSQL/Alembic | 已实现 | 9 个 Schema、首版迁移 |
| AQR-003 | 领域对象 | 已实现 | Signal/Portfolio/Order/Trade/Position/Risk |
| AQR-004 | 订单状态机 | 已实现 | 合法迁移、终态保护、UNKNOWN 恢复路径 |
| AQR-005 | order_intent | 已实现 | 唯一 client_order_id 约束 |
| AQR-006 | Transactional Outbox | 已实现 | 同事务创建、SKIP LOCKED 消费 |
| AQR-007 | headless vn.py 服务 | 已实现 | 常驻服务入口和优雅停止 |
| AQR-008 | PaperAccountApp | 已接入 | 作为执行适配器加载 |
| AQR-009 | RiskManagerApp | 已接入 | 统一风险配置映射 |
| AQR-010 | AqrExecutionApp | 已实现 | vn.py BaseApp/BaseEngine |
| AQR-011 | OrderRequest Mapper | 已实现 | SSE/SZSE/BSE、买卖、限价/市价 |
| AQR-012 | Event Bridge | 已实现 | 委托/成交/持仓/账户事件 |
| AQR-013 | Projection | 已实现 | 当前委托、成交、持仓、账户快照 |
| AQR-014 | 启动/盘中对账 | 已实现 | 启动和定时持仓/活动委托对账，结果持久化 |
| AQR-015 | Kill Switch/Heartbeat | 已实现 | 分级 HALT、心跳新鲜度、委托 ACK 超时进入 UNKNOWN |
| AQR-016 | PaperAccount E2E | 已实现 | 真实 EventEngine + RiskManager + PaperAccount Tick 撮合测试 |

## 下一迭代进入条件

Phase 1 数据研究开发前必须先完成：

1. 增加 PostgreSQL 中断、乱序事件和服务重启测试。
2. 接入真实行情源，持续驱动 PaperAccount。
3. 为通知失败增加持久化重试队列。

在这些条件满足前，不接入 Qlib 或生成自动实盘订单。
