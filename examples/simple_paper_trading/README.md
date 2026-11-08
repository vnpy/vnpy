# 模拟交易全流程示例

用 vnpy 核心的事件引擎、主引擎、网关抽象和 OMS，完整跑通：

```
模拟行情 CSV
   -> SimGateway 回放 tick / 本地撮合
   -> EventEngine 分发事件
   -> MaCrossStrategy 计算信号并 send_order
   -> SimGateway 成交并推送 order/trade/position/account
   -> OmsEngine 缓存 -> 账户、持仓、成交、权益报表
```

## 运行

```bash
python examples/simple_paper_trading/run.py
```

生成的数据在 `examples/simple_paper_trading/data/bars.csv`（已被 .gitignore 忽略）。

## 文件说明

| 文件 | 作用 | 替换场景 |
|---|---|---|
| `run.py` | 生成行情、创建引擎、组装网关与策略、打印报表 | 接入真实券商时修改这里 |
| `sim_gateway.py` | 本地模拟券商网关，实现 `BaseGateway` 全部接口 | 替换为真实网关 |
| `ma_strategy.py` | 双均线策略，只依赖 `MainEngine` 和事件 | 替换为你自己的策略 |

## 替换策略

策略只做三件事：

1. 在构造函数里 `main_engine.subscribe(...)` 订阅行情；
2. 在 `on_tick`（或 `on_bar`）中计算信号；
3. 通过 `main_engine.send_order(OrderRequest, gateway_name)` 下单，并在
   `on_order` / `on_trade` 中更新状态。

因此替换策略只需改 `ma_strategy.py`，网关和报表都不需要动。

如果要用 `vnpy.alpha` 训练出的模型信号，可参考
[`examples/simple_alpha/run.py`](../simple_alpha/run.py)：把模型预测保存为
`datetime / vt_symbol / signal` 的 DataFrame，然后在策略的 `on_tick`
中按当前时间查信号、设置目标仓位即可。

## 接入真实券商

以 A 股 XTP 为例：

```python
# pip install vnpy_xtp
from vnpy_xtp import XtpGateway

main_engine.add_gateway(XtpGateway)
strategy = MaCrossStrategy(
    main_engine, event_engine,
    gateway_name="XTP",          # 改成真实网关名
    vt_symbols=SYMBOLS,
)
main_engine.connect(xtp_setting, "XTP")
```

期货 CTP 同理，把 `SimGateway` 换成 `vnpy_ctp.CtpGateway`，并传入 SimNow /
期货公司的账号配置即可。策略代码不用改，因为：

* 所有网关都实现同一套 `BaseGateway` 接口；
* 所有网关都输出同一套 `TickData / OrderData / TradeData / PositionData / AccountData`；
* 下单统一走 `MainEngine.send_order`，成交统一通过事件回调。

需要注意的差异：

* **方向与开平**：股票卖出通常用 `Direction.SHORT`；期货平仓需要
  `Offset.CLOSE / CLOSETODAY / CLOSEYESTERDAY`，可使用
  `vnpy.trader.converter.OffsetConverter` 处理上期所平今平昨。
* **实时 K 线**：本示例的模拟行情每个交易日只推送一个 tick，因此策略直接把
  tick 当作日 K 线。接入实时行情后，请用
  `vnpy.trader.utility.BarGenerator` 聚合成 1 分钟 / 日 K 线，再在
  `on_bar` 中计算信号，避免盘中反复触发。
* **交易时段与重连**：真实网关负责断线重连；策略可在 `EVENT_TIMER` 上做
  交易时段检查。
* **风控**：真实交易应增加资金、持仓、单笔上限、撤单频率等风控检查。

## 模拟网关的简化点

* 只支持股票多头，卖出即平仓，不支持融券做空；
* 限价单在下一 tick 一次性全部成交，不模拟部分成交、滑点和涨跌停；
* 手续费按成交金额比例收取，买 0.05%、卖 0.15%（含印花税），最低 5 元；
* 行情来自历史 CSV，按 `speed` 参数逐日回放。
