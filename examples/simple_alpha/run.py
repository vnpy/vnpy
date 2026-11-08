"""
最简单的“模型驱动”量化交易全流程示例。

完整流程：
    1. 生成可复现的模拟日线行情（不依赖外部数据源/交易接口）
    2. 通过 AlphaLab 落盘为 parquet
    3. 构建 AlphaDataset：因子表达式 + 预测标签
    4. 训练 Lasso 模型
    5. 用模型预测值生成交易信号 signal
    6. 简单 Top-K 策略按 signal 调仓，回测引擎负责撮合
    7. 输出回测统计指标

运行：
    python examples/simple_alpha/run.py

依赖：
    pip install "vnpy[alpha]"
"""

import shutil
import sys
from datetime import datetime
from pathlib import Path

# Windows 控制台默认可能是 GBK，统一用 UTF-8 输出中文日志
if sys.stdout.encoding and sys.stdout.encoding.lower() not in {"utf-8", "utf8"}:
    sys.stdout.reconfigure(encoding="utf-8", errors="replace")  # type: ignore[attr-defined]

import numpy as np
import pandas as pd
import polars as pl

from vnpy.alpha import AlphaDataset, AlphaLab, AlphaStrategy, BacktestingEngine, Segment
from vnpy.alpha.dataset import process_cs_norm
from vnpy.alpha.model.models.lasso_model import LassoModel
from vnpy.trader.constant import Exchange, Interval
from vnpy.trader.object import BarData, TradeData
from vnpy.trader.utility import floor_to


# ---------------------------------------------------------------------------
# 1. 基本参数
# ---------------------------------------------------------------------------
SIM_SYMBOLS: list[str] = [
    "600000.SSE",
    "000001.SZSE",
    "600519.SSE",
]

DATA_START: datetime = datetime(2020, 1, 1)
DATA_END: datetime = datetime(2024, 12, 31)

TRAIN_PERIOD: tuple[str, str] = ("2022-01-01", "2022-12-31")
VALID_PERIOD: tuple[str, str] = ("2023-01-01", "2023-12-31")
TEST_PERIOD: tuple[str, str] = ("2024-01-01", "2024-12-31")

LAB_PATH: Path = Path(__file__).parent.joinpath("lab")

CAPITAL: float = 1_000_000
TOP_K: int = 2
MIN_VOLUME: int = 100


# ---------------------------------------------------------------------------
# 2. 模拟行情：几何随机游走 + 可复现随机种子
# ---------------------------------------------------------------------------
def generate_bar_data(
    symbols: list[str],
    start: datetime,
    end: datetime,
    seed: int = 42
) -> list[BarData]:
    """生成一批模拟日线 BarData。"""
    rng: np.random.Generator = np.random.default_rng(seed)
    dates: pd.DatetimeIndex = pd.bdate_range(start, end)

    bars: list[BarData] = []

    vt_symbol: str
    for i, vt_symbol in enumerate(symbols):
        symbol, exchange_str = vt_symbol.split(".")
        exchange: Exchange = Exchange(exchange_str)

        count: int = len(dates)

        # 每只股票给不同的波动率，并生成“持续性漂移”：
        # 让收益率存在正自相关，模型的动量类因子才能学到有效规律。
        volatility: float = 0.012 + 0.004 * i

        drift: np.ndarray = np.zeros(count)
        drift_vol: float = 0.0015 + 0.0005 * i
        t: int
        for t in range(1, count):
            drift[t] = 0.95 * drift[t - 1] + rng.normal(0, drift_vol)

        returns: np.ndarray = drift + rng.normal(0, volatility, count)
        closes: np.ndarray = 20.0 * np.exp(np.cumsum(returns))

        opens: np.ndarray = closes * (1 + rng.normal(0, 0.002, count))
        highs: np.ndarray = np.maximum(opens, closes) * (1 + np.abs(rng.normal(0, 0.004, count)))
        lows: np.ndarray = np.minimum(opens, closes) * (1 - np.abs(rng.normal(0, 0.004, count)))
        volumes: np.ndarray = np.maximum(rng.lognormal(12, 0.4, count).round(), 100)

        vwaps: np.ndarray = (highs + lows + closes) / 3
        turnovers: np.ndarray = volumes * vwaps

        j: int
        for j in range(count):
            bar: BarData = BarData(
                symbol=symbol,
                exchange=exchange,
                datetime=dates[j].to_pydatetime(),
                interval=Interval.DAILY,
                open_price=round(float(opens[j]), 2),
                high_price=round(float(highs[j]), 2),
                low_price=round(float(lows[j]), 2),
                close_price=round(float(closes[j]), 2),
                volume=float(volumes[j]),
                turnover=float(turnovers[j]),
                open_interest=0,
                gateway_name="SIM",
            )
            bars.append(bar)

    return bars


# ---------------------------------------------------------------------------
# 3. 数据预处理函数
# ---------------------------------------------------------------------------
def process_fill_feature(df: pl.DataFrame) -> pl.DataFrame:
    """只填充因子列，保留 label 的 NaN（训练时按 label 是否有效裁剪样本）。"""
    feature_cols: list[str] = df.columns[2:-1]

    return df.with_columns([
        pl.col(col).fill_null(0.0).fill_nan(0.0)
        for col in feature_cols
    ])


def process_normalize(df: pl.DataFrame) -> pl.DataFrame:
    """横截面 Z-Score 标准化。"""
    return process_cs_norm(df, "zscore")


def process_drop_invalid(df: pl.DataFrame) -> pl.DataFrame:
    """训练集剔除 label/因子缺失的样本。"""
    return df.fill_nan(None).drop_nulls()


# ---------------------------------------------------------------------------
# 4. 最简单的模型驱动策略：按预测信号持有 Top-K
# ---------------------------------------------------------------------------
class SimpleTopKStrategy(AlphaStrategy):
    """每天按模型信号等权持有得分最高的 K 只股票（仅做多）。"""

    top_k: int = TOP_K
    cash_ratio: float = 0.95
    price_add: float = 0.02
    min_volume: int = MIN_VOLUME

    def on_init(self) -> None:
        """策略初始化。"""
        self.write_log(f"策略初始化完成，持仓上限 {self.top_k} 只")

    def on_trade(self, trade: TradeData) -> None:
        """成交回调：本例无需额外处理。"""
        pass

    def on_bars(self, bars: dict[str, BarData]) -> None:
        """每根 K 线回调：根据最新模型信号设置目标仓位并调仓。"""
        signal: pl.DataFrame = self.get_signal()
        if signal.is_empty():
            return

        # 按预测得分从高到低排序，选出目标持仓
        signal = signal.sort("signal", descending=True)
        top_symbols: set[str] = set(
            signal["vt_symbol"].head(self.top_k).to_list()
        )

        # 按当前总资产计算每只股票的目标市值
        portfolio_value: float = self.get_portfolio_value()
        target_value: float = portfolio_value * self.cash_ratio / self.top_k

        vt_symbol: str
        bar: BarData
        for vt_symbol, bar in bars.items():
            if vt_symbol in top_symbols and bar.close_price > 0:
                target_volume: float = floor_to(
                    target_value / bar.close_price,
                    self.min_volume
                )
                self.set_target(vt_symbol, target_volume)
            else:
                # 不在目标池中的持仓全部清掉
                self.set_target(vt_symbol, 0)

        # 撤掉未成交旧单，并按目标仓位发送新单
        self.execute_trading(bars, price_add=self.price_add)


# ---------------------------------------------------------------------------
# 5. 主流程
# ---------------------------------------------------------------------------
def main() -> None:
    """跑通 数据 -> 因子 -> 模型 -> 信号 -> 交易 -> 回测 全流程。"""
    # -------------------------
    # 5.1 准备数据并落盘
    # -------------------------
    print("=" * 70)
    print("步骤 1/6：生成模拟行情并写入 AlphaLab")
    print("=" * 70)

    # 每次运行重新生成数据，避免历史 parquet 与新数据混在一起
    if LAB_PATH.exists():
        shutil.rmtree(LAB_PATH)

    lab: AlphaLab = AlphaLab(str(LAB_PATH))

    bars: list[BarData] = generate_bar_data(SIM_SYMBOLS, DATA_START, DATA_END)

    # save_bar_data 按 bars[0].vt_symbol 命名文件，必须逐合约写入
    bars_by_symbol: dict[str, list[BarData]] = {vt_symbol: [] for vt_symbol in SIM_SYMBOLS}
    bar: BarData
    for bar in bars:
        bars_by_symbol[bar.vt_symbol].append(bar)

    vt_symbol: str
    for vt_symbol in SIM_SYMBOLS:
        lab.save_bar_data(bars_by_symbol[vt_symbol])

    print(f"已写入 {len(bars)} 条日线，合约：{', '.join(SIM_SYMBOLS)}")

    # 回测引擎需要合约乘数、手续费率和最小变动价位
    for vt_symbol in SIM_SYMBOLS:
        lab.add_contract_setting(
            vt_symbol=vt_symbol,
            long_rate=0.0005,
            short_rate=0.0015,      # 卖出包含印花税
            size=1,
            pricetick=0.01,
        )

    # -------------------------
    # 5.2 构建因子数据集
    # -------------------------
    print()
    print("=" * 70)
    print("步骤 2/6：构建 AlphaDataset（因子表达式 + 标签）")
    print("=" * 70)

    df: pl.DataFrame | None = lab.load_bar_df(
        SIM_SYMBOLS,
        Interval.DAILY,
        TRAIN_PERIOD[0],
        TEST_PERIOD[1],
        extended_days=30,
    )
    if df is None:
        raise RuntimeError("行情数据加载失败")

    dataset: AlphaDataset = AlphaDataset(
        df=df,
        train_period=TRAIN_PERIOD,
        valid_period=VALID_PERIOD,
        test_period=TEST_PERIOD,
    )

    # 简单因子：均线偏离、动量、波动率、RSI、VWAP 偏离
    dataset.add_feature("ma5", "ts_mean(close, 5) / close")
    dataset.add_feature("ma20", "ts_mean(close, 20) / close")
    dataset.add_feature("mom5", "close / ts_delay(close, 5) - 1")
    dataset.add_feature("mom20", "close / ts_delay(close, 20) - 1")
    dataset.add_feature("vol20", "ts_std(close / ts_delay(close, 1) - 1, 20)")
    dataset.add_feature("rsi6", "ta_rsi(close, 6) / 100")
    dataset.add_feature("vwap_ratio", "vwap / close - 1")

    # 标签：下一根 K 线的收益率 close[t+2] / close[t+1] - 1
    dataset.set_label("ts_delay(close, -2) / ts_delay(close, -1) - 1")

    # 推理数据：填缺失 + 横截面标准化
    dataset.add_processor("infer", process_fill_feature)
    dataset.add_processor("infer", process_normalize)

    # 训练数据：在推理数据基础上剔除 label 缺失样本
    dataset.add_processor("learn", process_drop_invalid)

    print("开始计算因子表达式……")
    dataset.prepare_data(max_workers=4)
    dataset.process_data()
    print("因子数据集准备完成")

    # -------------------------
    # 5.3 训练模型
    # -------------------------
    print()
    print("=" * 70)
    print("步骤 3/6：训练 Lasso 模型")
    print("=" * 70)

    model: LassoModel = LassoModel(
        alpha=0.0005,
        max_iter=10_000,
        random_state=42,
    )
    model.fit(dataset)
    model.detail()

    # -------------------------
    # 5.4 生成信号
    # -------------------------
    print()
    print("=" * 70)
    print("步骤 4/6：模型预测并生成 signal")
    print("=" * 70)

    test_df: pl.DataFrame = dataset.fetch_infer(Segment.TEST).sort(
        ["datetime", "vt_symbol"]
    )
    predictions: np.ndarray = model.predict(dataset, Segment.TEST)

    signal_df: pl.DataFrame = test_df.select(
        ["datetime", "vt_symbol"]
    ).with_columns(
        pl.Series("signal", predictions)
    )

    print(f"信号数量：{signal_df.height}")
    print(signal_df.head(5))

    # -------------------------
    # 5.5 回测交易
    # -------------------------
    print()
    print("=" * 70)
    print("步骤 5/6：策略回测（模型信号驱动交易）")
    print("=" * 70)

    engine: BacktestingEngine = BacktestingEngine(lab)
    engine.set_parameters(
        vt_symbols=SIM_SYMBOLS,
        interval=Interval.DAILY,
        start=datetime(2024, 1, 1),
        end=datetime(2024, 12, 31),
        capital=CAPITAL,
        risk_free=0.02,
        annual_days=252,
        fill_price="open",
    )
    engine.add_strategy(
        SimpleTopKStrategy,
        {
            "top_k": TOP_K,
            "cash_ratio": 0.95,
            "price_add": 0.02,
        },
        signal_df,
    )

    engine.load_data()
    engine.run_backtesting()

    daily_df: pl.DataFrame | None = engine.calculate_result()
    if daily_df is None:
        print("回测没有产生任何成交，请检查信号与撮合逻辑")
        return

    # -------------------------
    # 5.6 输出结果
    # -------------------------
    print()
    print("=" * 70)
    print("步骤 6/6：回测统计结果")
    print("=" * 70)

    statistics: dict = engine.calculate_statistics()

    key: str
    value: object
    for key, value in statistics.items():
        if isinstance(value, float):
            print(f"{key:24s}: {value:,.4f}")
        else:
            print(f"{key:24s}: {value}")

    print()
    print(f"成交笔数：{len(engine.get_all_trades())}")
    print(f"委托笔数：{len(engine.get_all_orders())}")
    print()
    print("最近 5 个交易日的逐日盈亏：")
    print(engine.daily_df.tail(5).select(
        ["date", "trade_count", "turnover", "commission", "net_pnl", "balance"]
    ))
    print()
    print("说明：行情为人工模拟数据，回测结果仅用于验证完整流程，不代表策略实盘表现。")


if __name__ == "__main__":
    main()
