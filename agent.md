# Agent 修改记录

- 日期：2026-11-08
- 仓库：https://github.com/wsx604022350/qaz_vnpy
- 基线：VeighNa vnpy 4.5.0（上游提交 `c6e231c`）
- 说明：本次只新增示例与文档，未修改 `vnpy/` 框架核心代码。

## 一、本次目标

在 vnpy 框架内完成从“模拟交易”到“真实数据多因子回测”的完整链路，并实现聚宽社区文章
《红利低波与红利价值 双子组合月度轮动策略样本外回测》的公开规则版本。

## 二、新增示例

### 1. `examples/simple_paper_trading/`

模拟交易全流程：

- `sim_gateway.py`：本地模拟券商网关，实现 `BaseGateway` 的
  connect / subscribe / send_order / cancel_order / query 接口，并按下一个 tick
  撮合限价单，推送 order / trade / position / account 事件。
- `ma_strategy.py`：MA5/MA20 双均线策略，演示“订阅 → 信号 → 下单 → 成交”链路。
- `run.py`：生成模拟日线、回放行情、打印账户/持仓/成交/收益报表。
- `README.md`：替换策略、接入真实券商的说明。

实测：3 个标的、2 年模拟数据、48 笔成交，期末权益 +3.61%，最大回撤 -3.08%。
模拟数据，仅验证流程，不代表真实收益。

### 2. `examples/simple_alpha/`

模型驱动投研流程：

- 生成模拟日线 → `AlphaLab` 存 parquet；
- `AlphaDataset` 计算均线、动量、波动率、RSI、VWAP 偏离等因子；
- `LassoModel` 训练并预测；
- `SimpleTopKStrategy` 按模型信号选 Top-K，使用 `BacktestingEngine` 回测。

实测（模拟数据）：2024 年 +155.81%，仅验证“数据 → 因子 → 模型 → 信号 → 回测”链路。

### 3. `examples/real_data_weekly/`

真实数据周度多因子回测：

- `fetch_data.py`：从东方财富公开接口拉取沪深300成分股真实日线；
- `run_backtest.py`：6 个因子（20/5 日动量、20 日波动率、量比、MA20 偏离、RSI14），
  截面 Z-Score 加权打分，选 Top-10，回测最近 5 个交易日。

实测：100 只股票，2026-11-02 ~ 2026-11-06，策略 +3.97%，沪深300 +1.21%；
但平均 Rank IC = -0.182，说明这一周因子与次日收益负相关，正收益不能归因于因子。
一周样本太短，不能用于判断因子有效性。

### 4. `examples/dividend_rotation/`

按聚宽文章公开规则重建的“红利低波 + 红利价值”月度轮动策略：

- `fetch_data.py`：东方财富 10 年不复权日线 + AkShare 财务/分红数据；
- `refetch_dividends.py`：统一重抓现金分红、送股、转增；
- `run_backtest.py`：因子计算、月度选股、交易模拟、绩效报告；
- `plot_equity.py`：累计增长率折线图与回撤图（PNG + HTML）；
- `README.md`：策略规则、数据口径、局限性说明。

策略规则：

- 红利低波（HLDB）：股息率最高 10% 中按加权 Beta 从低到高选 5 只；
- 红利价值（HLJZ）：PE 5~50、ROE 5~100、营收增速 5~100、净利增速 10~100，
  再按股息率选 5 只；
- 两个组合取并集、等权，每月末信号、下一交易日开盘调仓；
- 昨日涨停、今日开板的持仓清仓；
- 佣金 0.03%，卖出印花税 0.10%，滑点 0.20%。

实测：248 只当前沪深300成分股，2016-11-07 ~ 2026-11-06：

| 指标 | 策略 | 沪深300 | 上证红利 | 中证红利 |
|---|---:|---:|---:|---:|
| 累计增长率 | +264.32% | +20.79% | +26.72% | +36.86% |
| 年化增长率 | +14.35% | +1.98% | +2.49% | +3.31% |
| 最大回撤 | -20.35% | -45.60% | -29.50% | -29.66% |

夏普 0.83，平均持仓 9.6 只，年化换手率 8.60 倍。

## 三、本次修复的问题

1. **东方财富长历史前复权数据异常**：部分股票出现负价、十年 +9000% 等错误。
   改为“不复权价格 + 现金分红 + 送股/转增”自行重建总收益。
2. **`AlphaLab.save_bar_data()` 按单合约写入**：多合约一次性传入会全部写入
   第一个合约的 parquet，改为逐合约保存。
3. **CSV 股票代码前导零丢失**：`000001` 被 pandas 读成 `1`，读取时强制
   `dtype={"symbol": str}`。
4. **模拟网关平仓后 OMS 保留旧持仓**：改为推送零持仓快照。
5. **收盘未撤挂单导致资金冻结**：回放结束时撤销未成交委托并释放冻结资金。
6. **委托时间被成交时间覆盖**：保留委托提交时间，便于还原“信号日 → 成交日”。
7. **IDE 占用输出文件导致回测中断**：CSV/HTML 写入增加 `PermissionError`
   回退文件名。
8. **绩效图口径**：从“净值”改为“累计增长率”，图例同时展示累计与年化增长率。

## 四、数据与局限

- 所有 `data/`、`lab/` 目录均为生成数据，已在 `.gitignore` 中忽略；
  重新运行对应 `fetch_data.py` 可重建。
- 模拟交易与 `simple_alpha` 使用人工模拟行情，收益不代表真实市场。
- `real_data_weekly` 只回测一周，统计意义很弱，且平均 IC 为负。
- `dividend_rotation` 使用当前沪深300成分股回测十年，存在存活偏差；
  财务/分红口径为近似值；基准为价格指数（不含分红），超额收益被高估；
  未模拟 ST、涨停买入限制、股息税、冲击成本等。
- 聚宽文章完整源码需要登录，`dividend_rotation` 是公开规则的规则重建版，
  不是原代码逐行复刻，结果与文章 2026 年样本外结果存在差异。

## 五、运行方式

```bash
# 模拟交易
python examples/simple_paper_trading/run.py

# 模型投研（模拟数据）
python examples/simple_alpha/run.py

# 真实数据周度多因子
python examples/real_data_weekly/fetch_data.py
python examples/real_data_weekly/run_backtest.py

# 红利双子组合十年回测
python examples/dividend_rotation/fetch_data.py
python examples/dividend_rotation/refetch_dividends.py
python examples/dividend_rotation/run_backtest.py
python examples/dividend_rotation/plot_equity.py
```

## 六、远程仓库

- `origin`：https://github.com/wsx604022350/qaz_vnpy
- `upstream`：https://gitee.com/vnpy/vnpy.git（原 vnpy 上游，保留用于同步）
