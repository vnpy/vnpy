"""
Multi-factor stock-selection backtest on real A-share data.

Data:
    CSI 300 constituents, qfq daily bars fetched from Eastmoney
    (see fetch_data.py). The script uses the latest 5 trading days
    as the backtest week and the prior day's close as the first signal.

Factors:
    mom20      20-day momentum          (+)
    mom5       5-day momentum           (+)
    vol20      20-day volatility        (-)
    vol_ratio  5-day / 20-day volume    (+)
    ma_ratio   close / MA20 - 1         (+)
    rsi14      14-day RSI               (-)

Strategy:
    Cross-sectional z-score, weighted composite score, long top K,
    equal weight, rebalance daily, fill at next bar open.

Run:
    python examples/real_data_weekly/fetch_data.py
    python examples/real_data_weekly/run_backtest.py

Caveat:
    One week is far too short to evaluate a factor. This is a pipeline
    demonstration, not evidence that the factors work.
"""

import shutil
import sys
from datetime import date
from pathlib import Path

# Windows console may default to GBK
if sys.stdout.encoding and sys.stdout.encoding.lower() not in {"utf-8", "utf8"}:
    sys.stdout.reconfigure(encoding="utf-8", errors="replace")  # type: ignore[attr-defined]

import numpy as np
import pandas as pd
import polars as pl
import requests

from vnpy.alpha import AlphaLab, AlphaStrategy, BacktestingEngine
from vnpy.trader.constant import Exchange, Interval
from vnpy.trader.object import BarData, TradeData
from vnpy.trader.utility import floor_to


BASE_DIR: Path = Path(__file__).resolve().parent
DATA_PATH: Path = BASE_DIR.joinpath("data", "csi300_bars.csv")
LAB_PATH: Path = BASE_DIR.joinpath("lab")

CAPITAL: float = 5_000_000
TOP_K: int = 10

# Factor name -> weight in the composite score
FACTOR_WEIGHTS: dict[str, float] = {
    "mom20": 0.30,
    "mom5": 0.15,
    "vol20": -0.20,
    "vol_ratio": 0.15,
    "ma_ratio": 0.15,
    "rsi14": -0.10,
}

INDEX_SECID: str = "1.000300"       # CSI 300
KLINE_URL: str = "https://push2his.eastmoney.com/api/qt/stock/kline/get"
HEADERS: dict[str, str] = {"User-Agent": "Mozilla/5.0"}


class TopKStrategy(AlphaStrategy):
    """Long the top-K composite-score stocks, equal weight, daily rebalance."""

    top_k: int = TOP_K
    cash_ratio: float = 0.90
    price_add: float = 0.05
    min_volume: int = 100

    def on_init(self) -> None:
        """Initialization callback."""
        self.write_log(f"多因子 Top{self.top_k} 策略初始化完成")

    def on_trade(self, trade: TradeData) -> None:
        """Trade callback."""
        pass

    def on_bars(self, bars: dict[str, BarData]) -> None:
        """Rebalance toward the top-K names on each bar."""
        signal: pl.DataFrame = self.get_signal()
        if signal.is_empty():
            return

        signal = signal.sort("signal", descending=True)
        top_symbols: set[str] = set(
            signal["vt_symbol"].head(self.top_k).to_list()
        )

        portfolio_value: float = self.get_portfolio_value()
        target_value: float = portfolio_value * self.cash_ratio / self.top_k

        vt_symbol: str
        bar: BarData
        for vt_symbol, bar in bars.items():
            if vt_symbol in top_symbols and bar.close_price > 0:
                target_volume: float = floor_to(
                    target_value / bar.close_price,
                    self.min_volume,
                )
                self.set_target(vt_symbol, target_volume)
            else:
                self.set_target(vt_symbol, 0)

        self.execute_trading(bars, price_add=self.price_add)


def compute_rsi(series: pd.Series, window: int = 14) -> pd.Series:
    """Compute Wilder's RSI for one price series."""
    delta: pd.Series = series.diff()
    gain: pd.Series = delta.clip(lower=0.0)
    loss: pd.Series = (-delta).clip(lower=0.0)

    avg_gain: pd.Series = gain.ewm(
        alpha=1.0 / window, min_periods=window, adjust=False
    ).mean()
    avg_loss: pd.Series = loss.ewm(
        alpha=1.0 / window, min_periods=window, adjust=False
    ).mean()

    rs: pd.Series = avg_gain / avg_loss
    return 100.0 - 100.0 / (1.0 + rs)


def load_and_compute_factors() -> tuple[
    pd.DataFrame,
    pd.DataFrame,
    list[pd.Timestamp],
    list[pd.Timestamp],
]:
    """Load bars, compute factors, and return (raw_df, work_df, signal_dates)."""
    if not DATA_PATH.exists():
        raise FileNotFoundError(
            f"找不到 {DATA_PATH}，请先运行 fetch_data.py"
        )

    raw_df: pd.DataFrame = pd.read_csv(
        DATA_PATH,
        parse_dates=["datetime"],
        dtype={"symbol": str, "exchange": str},
    )
    raw_df["vt_symbol"] = raw_df["symbol"] + "." + raw_df["exchange"]
    raw_df = raw_df.sort_values(["vt_symbol", "datetime"]).reset_index(drop=True)

    work_df: pd.DataFrame = raw_df.copy()
    grouped = work_df.groupby("vt_symbol", group_keys=False)

    # Momentum and volatility
    work_df["ret1"] = grouped["close"].pct_change()
    work_df["mom20"] = grouped["close"].pct_change(20)
    work_df["mom5"] = grouped["close"].pct_change(5)
    work_df["vol20"] = grouped["ret1"].transform(
        lambda s: s.rolling(20).std()
    )

    # Trend
    work_df["ma20"] = grouped["close"].transform(
        lambda s: s.rolling(20).mean()
    )
    work_df["ma_ratio"] = work_df["close"] / work_df["ma20"] - 1.0

    # Volume expansion
    work_df["vol_ratio"] = grouped["volume"].transform(
        lambda s: s.rolling(5).mean() / s.rolling(20).mean()
    )
    work_df["amount_ma20"] = grouped["turnover"].transform(
        lambda s: s.rolling(20).mean()
    )

    # RSI
    work_df["rsi14"] = grouped["close"].transform(compute_rsi)

    # Next-day close-to-close return, used only for IC evaluation
    work_df["fwd_ret1"] = grouped["close"].shift(-1) / work_df["close"] - 1.0

    work_df.replace([np.inf, -np.inf], np.nan, inplace=True)

    # Liquidity filter: 20-day average turnover >= 50 million CNY
    work_df = work_df[work_df["amount_ma20"] >= 50_000_000].copy()

    factor_cols: list[str] = list(FACTOR_WEIGHTS)
    work_df.dropna(subset=factor_cols, inplace=True)

    # Cross-sectional z-score with +/-3 clipping
    for col in factor_cols:
        mean = work_df.groupby("datetime")[col].transform("mean")
        std = work_df.groupby("datetime")[col].transform("std")
        z = (work_df[col] - mean) / std.replace(0.0, np.nan)
        work_df[col + "_z"] = z.clip(-3.0, 3.0)

    z_cols: list[str] = [col + "_z" for col in factor_cols]
    work_df.dropna(subset=z_cols, inplace=True)

    # Composite score
    work_df["signal"] = 0.0
    for col, weight in FACTOR_WEIGHTS.items():
        work_df["signal"] += weight * work_df[col + "_z"]

    # Latest 5 trading days = backtest week; previous day = first signal
    all_dates: list[pd.Timestamp] = sorted(
        pd.to_datetime(work_df["datetime"]).dt.normalize().unique()
    )
    if len(all_dates) < 7:
        raise RuntimeError("历史数据不足，至少需要 7 个交易日")

    week_dates: list[pd.Timestamp] = list(all_dates[-5:])
    signal_dates: list[pd.Timestamp] = list(all_dates[-6:])

    return raw_df, work_df, signal_dates, week_dates


def fetch_index_bars(start: pd.Timestamp, end: pd.Timestamp) -> pd.DataFrame:
    """Fetch CSI 300 daily open/close for the benchmark."""
    params: dict = {
        "secid": INDEX_SECID,
        "fields1": "f1,f2,f3,f4,f5,f6",
        "fields2": "f51,f52,f53,f54,f55,f56,f57,f58,f59,f60,f61",
        "klt": "101",
        "fqt": "0",
        "beg": start.strftime("%Y%m%d"),
        "end": end.strftime("%Y%m%d"),
        "lmt": "100",
    }

    response: requests.Response = requests.get(
        KLINE_URL, params=params, headers=HEADERS, timeout=20
    )
    response.raise_for_status()

    data: dict | None = response.json().get("data")
    if not data:
        raise RuntimeError("无法获取沪深300指数数据")

    rows: list[dict] = []
    line: str
    for line in data["klines"]:
        parts: list[str] = line.split(",")
        rows.append({
            "datetime": pd.Timestamp(parts[0]),
            "open": float(parts[1]),
            "close": float(parts[2]),
        })

    return pd.DataFrame(rows).sort_values("datetime").reset_index(drop=True)


def save_to_lab(raw_df: pd.DataFrame, vt_symbols: list[str]) -> AlphaLab:
    """Save bars and contract settings into AlphaLab."""
    if LAB_PATH.exists():
        shutil.rmtree(LAB_PATH)

    lab: AlphaLab = AlphaLab(str(LAB_PATH))

    vt_symbol: str
    for vt_symbol in vt_symbols:
        sub: pd.DataFrame = raw_df[raw_df["vt_symbol"] == vt_symbol]

        bars: list[BarData] = []
        row: object
        for row in sub.itertuples(index=False):
            bars.append(BarData(
                symbol=row.symbol,
                exchange=Exchange(row.exchange),
                datetime=row.datetime.to_pydatetime(),
                interval=Interval.DAILY,
                open_price=float(row.open),
                high_price=float(row.high),
                low_price=float(row.low),
                close_price=float(row.close),
                volume=float(row.volume),
                turnover=float(row.turnover),
                open_interest=0,
                gateway_name="EM",
            ))

        lab.save_bar_data(bars)
        lab.add_contract_setting(
            vt_symbol=vt_symbol,
            long_rate=0.0003,
            short_rate=0.0013,      # sell side includes stamp duty
            size=1,
            pricetick=0.01,
        )

    return lab


def main() -> None:
    """Run the weekly multi-factor backtest."""
    raw_df, work_df, signal_dates, week_dates = load_and_compute_factors()

    week_start: pd.Timestamp = week_dates[0]
    week_end: pd.Timestamp = week_dates[-1]
    signal_start: pd.Timestamp = signal_dates[0]

    print("=" * 78)
    print("真实数据多因子选股回测")
    print("=" * 78)
    print(f"数据文件    : {DATA_PATH}")
    print(f"股票数量    : {work_df['vt_symbol'].nunique()}")
    print(f"数据范围    : {raw_df['datetime'].min().date()} ~ {raw_df['datetime'].max().date()}")
    print(f"信号日期    : {signal_start.date()} ~ {week_end.date()}")
    print(f"回测周      : {week_start.date()} ~ {week_end.date()}")
    print()

    print("因子与权重：")
    for col, weight in FACTOR_WEIGHTS.items():
        print(f"  {col:10s} {weight:+.2f}")
    print()

    # Build the signal DataFrame
    signal_df: pd.DataFrame = work_df[
        (work_df["datetime"] >= signal_start)
        & (work_df["datetime"] <= week_end)
    ][["datetime", "vt_symbol", "signal"]].copy()

    # Top-K names for each signal date
    print("每日选股 Top {}：".format(TOP_K))
    dt: pd.Timestamp
    for dt in sorted(signal_df["datetime"].unique()):
        group: pd.DataFrame = signal_df[signal_df["datetime"] == dt]
        top: pd.DataFrame = group.sort_values("signal", ascending=False).head(TOP_K)
        names: str = ", ".join(
            f"{row.vt_symbol}({row.signal:+.2f})"
            for row in top.itertuples(index=False)
        )
        print(f"  {pd.Timestamp(dt).date()}  {names}")
    print()

    # Rank IC for signal dates with a next-day return
    ic_rows: list[tuple[pd.Timestamp, float, int]] = []
    for dt in sorted(signal_df["datetime"].unique()):
        cross: pd.DataFrame = work_df[work_df["datetime"] == dt][
            ["signal", "fwd_ret1"]
        ].dropna()

        if len(cross) >= 10:
            ic: float = cross["signal"].corr(cross["fwd_ret1"], method="spearman")
            if not np.isnan(ic):
                ic_rows.append((pd.Timestamp(dt), ic, len(cross)))

    print("单日 Rank IC（因子分数与次日收益的秩相关）：")
    if ic_rows:
        for dt, ic, count in ic_rows:
            print(f"  {dt.date()}  IC={ic:+.3f}  股票数={count}")
        avg_ic: float = float(np.mean([row[1] for row in ic_rows]))
        print(f"  平均 IC = {avg_ic:+.3f}（样本仅一周，仅供参考）")
        if avg_ic < 0:
            print("  警告：本周因子分数与次日收益负相关，正收益不能归因于因子。")
    else:
        print("  无有效 IC 样本")
    print()

    vt_symbols: list[str] = sorted(signal_df["vt_symbol"].unique().tolist())
    lab: AlphaLab = save_to_lab(raw_df, vt_symbols)

    # Run the backtest
    engine: BacktestingEngine = BacktestingEngine(lab)
    engine.set_parameters(
        vt_symbols=vt_symbols,
        interval=Interval.DAILY,
        start=signal_start.to_pydatetime(),
        end=week_end.to_pydatetime(),
        capital=CAPITAL,
        risk_free=0.0,
        annual_days=252,
        fill_price="open",
    )
    engine.add_strategy(
        TopKStrategy,
        {
            "top_k": TOP_K,
            "cash_ratio": 0.90,
            "price_add": 0.05,
        },
        pl.from_pandas(signal_df),
    )

    engine.load_data()
    engine.run_backtesting()

    daily_df: pl.DataFrame | None = engine.calculate_result()
    if daily_df is None:
        print("回测没有产生成交")
        return

    # Add the equity curve; avoid annualizing a 5-day sample
    daily_df = daily_df.with_columns(
        balance=pl.col("net_pnl").cum_sum() + CAPITAL
    )

    # Week-only statistics
    week_start_date: date = week_start.date()
    week_end_date: date = week_end.date()

    week_df: pl.DataFrame = daily_df.filter(
        (pl.col("date") >= week_start_date)
        & (pl.col("date") <= week_end_date)
    )

    before_df: pl.DataFrame = daily_df.filter(
        pl.col("date") < week_start_date
    )
    start_equity: float = (
        float(before_df["balance"][-1]) if before_df.height else CAPITAL
    )
    end_equity: float = float(week_df["balance"][-1])
    week_return: float = end_equity / start_equity - 1.0

    week_pnl: float = float(week_df["net_pnl"].sum())
    week_commission: float = float(week_df["commission"].sum())
    week_turnover: float = float(week_df["turnover"].sum())
    week_trade_count: int = int(week_df["trade_count"].sum())
    week_win_days: int = week_df.filter(pl.col("net_pnl") > 0).height
    week_loss_days: int = week_df.filter(pl.col("net_pnl") < 0).height

    balances: list[float] = [start_equity] + week_df["balance"].to_list()
    peak: float = balances[0]
    max_dd: float = 0.0
    value: float
    for value in balances:
        peak = max(peak, value)
        max_dd = min(max_dd, value / peak - 1.0)

    # Benchmark: Monday open -> Friday close, aligned with the first fill
    try:
        index_df: pd.DataFrame = fetch_index_bars(week_start, week_end)
        benchmark_return: float = float(
            index_df["close"].iloc[-1] / index_df["open"].iloc[0] - 1.0
        )
        benchmark_text: str = f"{benchmark_return:+.2%}"
        excess_text: str = f"{week_return - benchmark_return:+.2%}"
    except Exception as exc:
        benchmark_text = f"获取失败（{exc}）"
        excess_text = "N/A"

    print()
    print("=" * 78)
    print("回测周结果")
    print("=" * 78)
    print(f"起始权益      : {start_equity:>14,.2f}")
    print(f"期末权益      : {end_equity:>14,.2f}")
    print(f"周收益        : {week_return:>14.2%}")
    print(f"沪深300周收益 : {benchmark_text:>14}  （周一开盘~周五收盘）")
    print(f"超额收益      : {excess_text:>14}")
    print(f"周净盈亏      : {week_pnl:>14,.2f}")
    print(f"手续费        : {week_commission:>14,.2f}")
    print(f"成交额        : {week_turnover:>14,.2f}")
    print(f"成交笔数      : {week_trade_count:>14d}")
    print(f"盈利/亏损天数 : {week_win_days:>6d} / {week_loss_days}")
    print(f"周内最大回撤  : {max_dd:>14.2%}")

    # Trade details within the week
    trades: list[TradeData] = [
        trade
        for trade in engine.get_all_trades()
        if week_start_date <= trade.datetime.date() <= week_end_date
    ]

    print()
    print(f"周内成交明细（{len(trades)} 笔）：")
    if not trades:
        print("  无成交")
    else:
        trade: TradeData
        for trade in trades:
            print(
                f"  {trade.datetime:%Y-%m-%d}  {trade.vt_symbol:12s} "
                f"{trade.direction.value} {trade.volume:>7.0f} "
                f"@ {trade.price:>8.2f}"
            )

    print()
    print("说明：")
    print("  1. 真实数据来自东方财富公开接口，前复权日线，股票池为当前沪深300前100只。")
    print("  2. 只回测最近 5 个交易日，样本极短，不能用来判断因子或策略是否有效。")
    print("  3. 未模拟滑点、冲击成本、涨跌停无法成交、停牌等真实约束。")
    print("  4. 因子权重是人为设定的，未做任何参数优化，以避免在这 5 天上过拟合。")


if __name__ == "__main__":
    main()
