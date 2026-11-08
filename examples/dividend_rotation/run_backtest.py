"""
Dividend low-vol + dividend value monthly rotation backtest.

Strategy reconstructed from:
    https://www.joinquant.com/view/community/detail/109dae3f0631009913504ffd035635e9?type=1
    "红利低波与红利价值 双子组合月度轮动策略样本外回测"

Rules:
    * Universe: current CSI 300 constituents (survivorship-biased approximation)
    * HLDB (红利低波):
        - dividend yield in the top 10% of the eligible universe
        - sort by 250-day beta ascending, take 5
    * HLJZ (红利价值):
        - PE(TTM) 5~50
        - ROE 5~100
        - revenue YoY growth 5~100
        - net profit YoY growth 10~100
        - sort by dividend yield descending, take 5
    * Target = union of HLDB and HLJZ, equal weight
    * Signal at month-end close, execute at next trading day open
    * Daily: sell a held stock if it was limit-up yesterday and opened today
    * Costs: commission 0.03%, stamp duty 0.10% on sells, slippage 0.20%

Data:
    * Eastmoney: unadjusted daily bars, 2015-01-01 ~ latest
    * AkShare: historical financial indicators and dividend / bonus records

Corporate actions (cash dividend, bonus shares, transfer shares) are applied
directly to cash and share counts, avoiding unreliable long-history qfq data.

Run:
    python examples/dividend_rotation/fetch_data.py
    python examples/dividend_rotation/run_backtest.py
"""

import math
import sys
from datetime import date, datetime
from pathlib import Path

if sys.stdout.encoding and sys.stdout.encoding.lower() not in {"utf-8", "utf8"}:
    sys.stdout.reconfigure(encoding="utf-8", errors="replace")  # type: ignore[attr-defined]

import numpy as np
import pandas as pd


BASE_DIR: Path = Path(__file__).resolve().parent
DATA_DIR: Path = BASE_DIR.joinpath("data")
PRICE_DIR: Path = DATA_DIR.joinpath("prices")
FIN_DIR: Path = DATA_DIR.joinpath("financial")
DIV_DIR: Path = DATA_DIR.joinpath("dividend")

BACKTEST_START: pd.Timestamp = pd.Timestamp("2016-11-07")
INITIAL_CAPITAL: float = 1_000_000.0

HLDB_COUNT: int = 5
HLJZ_COUNT: int = 5
INVEST_RATIO: float = 0.98

COMMISSION: float = 0.0003
STAMP_TAX: float = 0.0010
SLIPPAGE: float = 0.0020
RISK_FREE: float = 0.02

# Approximate disclosure deadlines: Q1 +31d, H1 +62d, Q3 +31d, annual +120d
FIN_LAG_BY_MONTH: dict[int, int] = {3: 31, 6: 62, 9: 31, 12: 120}
BETA_WINDOW: int = 250
BETA_MIN_PERIODS: int = 120


def read_price_dir(folder: Path) -> dict[str, pd.DataFrame]:
    """Read cached per-stock price CSVs."""
    result: dict[str, pd.DataFrame] = {}
    path: Path
    for path in sorted(folder.glob("*.csv")):
        df = pd.read_csv(path, parse_dates=["date"])
        df = df.drop_duplicates("date").sort_values("date")
        result[path.stem] = df
    return result


def build_matrices(
    prices: dict[str, pd.DataFrame],
    calendar: pd.DatetimeIndex,
    field: str,
    ffill: bool = False,
) -> pd.DataFrame:
    """Build a date x code matrix for one price field."""
    series: dict[str, pd.Series] = {}
    code: str
    df: pd.DataFrame
    for code, df in prices.items():
        s = df.set_index("date")[field].reindex(calendar)
        if ffill:
            s = s.ffill()
        series[code] = s
    return pd.DataFrame(series, index=calendar)


def load_index(filename: str) -> pd.DataFrame:
    """Load an index CSV."""
    df = pd.read_csv(DATA_DIR.joinpath(filename), parse_dates=["date"])
    df = df.drop_duplicates("date").sort_values("date").set_index("date")
    return df


def load_names() -> dict[str, str]:
    """Load the code -> name mapping if available."""
    path = DATA_DIR.joinpath("names.csv")
    if not path.exists():
        return {}
    df = pd.read_csv(path, dtype={"code": str})
    return dict(zip(df["code"], df["name"]))


def compute_ttm_eps(df: pd.DataFrame) -> pd.DataFrame:
    """Compute TTM EPS from cumulative EPS reports."""
    df = df.copy()
    df["report_date"] = pd.to_datetime(df["日期"])
    df = df.sort_values("report_date").drop_duplicates("report_date", keep="last")
    df["year"] = df["report_date"].dt.year
    df["quarter"] = df["report_date"].dt.quarter

    eps_col = "摊薄每股收益(元)"
    if eps_col not in df.columns:
        df["eps_ttm"] = np.nan
        return df

    eps_map: dict[tuple[int, int], float] = {}
    year: int
    quarter: int
    value: float
    for year, quarter, value in zip(df["year"], df["quarter"], df[eps_col]):
        if pd.notna(value):
            eps_map[(int(year), int(quarter))] = float(value)

    ttm_values: list[float] = []
    for year, quarter in zip(df["year"], df["quarter"]):
        year = int(year)
        quarter = int(quarter)
        current = eps_map.get((year, quarter), np.nan)
        if quarter == 4:
            ttm = current
        else:
            prev_annual = eps_map.get((year - 1, 4), np.nan)
            prev_same = eps_map.get((year - 1, quarter), np.nan)
            ttm = current + prev_annual - prev_same
        ttm_values.append(ttm)

    df["eps_ttm"] = ttm_values
    return df


def build_fin_matrix(
    calendars: pd.DatetimeIndex,
    field: str,
    ttm_eps: bool = False,
) -> pd.DataFrame:
    """Build a daily date x code matrix from financial reports."""
    series: dict[str, pd.Series] = {}
    path: Path
    for path in sorted(FIN_DIR.glob("*.csv")):
        code = path.stem
        df = pd.read_csv(path)
        if df.empty:
            continue

        if ttm_eps:
            df = compute_ttm_eps(df)
            values = df["eps_ttm"]
        else:
            if field not in df.columns:
                continue
            values = df[field]

        report_dates = pd.to_datetime(df["日期"])
        lags = (
            report_dates.dt.month
            .map(FIN_LAG_BY_MONTH)
            .fillna(120)
            .astype(int)
        )
        available_dates = report_dates + pd.to_timedelta(lags, unit="D")

        numeric = pd.to_numeric(values, errors="coerce")
        s = pd.Series(
            numeric.to_numpy(dtype=float),
            index=available_dates,
        )
        s = s.dropna().sort_index()
        s = s[~s.index.duplicated(keep="last")]
        if s.empty:
            continue

        s = s.reindex(calendars, method="ffill")
        series[code] = s

    return pd.DataFrame(series, index=calendars)


def build_dividend_matrices(
    calendars: pd.DatetimeIndex,
) -> tuple[pd.DataFrame, pd.DataFrame, pd.DataFrame]:
    """Build daily cash-dividend, bonus-share, and trailing DPS matrices."""
    dps_data: dict[str, pd.Series] = {}
    bonus_data: dict[str, pd.Series] = {}

    path: Path
    for path in sorted(DIV_DIR.glob("*.csv")):
        code = path.stem
        df = pd.read_csv(path)
        if df.empty or "除权除息日" not in df.columns:
            continue

        ex_dates = pd.to_datetime(df["除权除息日"], errors="coerce")
        cash = pd.to_numeric(df.get("派息", 0), errors="coerce").fillna(0.0) / 10.0
        bonus = (
            pd.to_numeric(df.get("送股", 0), errors="coerce").fillna(0.0)
            + pd.to_numeric(df.get("转增", 0), errors="coerce").fillna(0.0)
        ) / 10.0

        events = pd.DataFrame({
            "ex_date": ex_dates,
            "dps": cash.to_numpy(),
            "bonus": bonus.to_numpy(),
        }).dropna(subset=["ex_date"])

        # Ignore events outside the price calendar; otherwise old dividends
        # would all be mapped to the first calendar date.
        events = events[
            (events["ex_date"] >= calendars[0])
            & (events["ex_date"] <= calendars[-1])
        ]

        if events.empty:
            continue

        # Map ex-date to the first trading day on or after it
        mapped_dps: dict[pd.Timestamp, float] = {}
        mapped_bonus: dict[pd.Timestamp, float] = {}

        row: object
        for row in events.itertuples(index=False):
            pos = int(calendars.searchsorted(row.ex_date))
            if pos >= len(calendars):
                continue
            trade_date = calendars[pos]
            mapped_dps[trade_date] = mapped_dps.get(trade_date, 0.0) + float(row.dps)
            mapped_bonus[trade_date] = mapped_bonus.get(trade_date, 0.0) + float(row.bonus)

        dps_data[code] = pd.Series(mapped_dps).reindex(calendars).fillna(0.0)
        bonus_data[code] = pd.Series(mapped_bonus).reindex(calendars).fillna(0.0)

    dps_df = pd.DataFrame(dps_data, index=calendars).fillna(0.0)
    bonus_df = pd.DataFrame(bonus_data, index=calendars).fillna(0.0)
    dps_ttm_df = dps_df.rolling(BETA_WINDOW, min_periods=1).sum()
    return dps_df, bonus_df, dps_ttm_df


def board_limit(code: str) -> float:
    """Price limit ratio by board."""
    if code.startswith(("300", "301", "688")):
        return 0.20
    return 0.10


def select_targets(
    signal_date: pd.Timestamp,
    close_adj: pd.DataFrame,
    div_yield: pd.DataFrame,
    beta: pd.DataFrame,
    pe: pd.DataFrame,
    roe: pd.DataFrame,
    revenue_growth: pd.DataFrame,
    profit_growth: pd.DataFrame,
) -> tuple[list[str], pd.DataFrame, pd.DataFrame]:
    """Select HLDB and HLJZ at one signal date."""
    universe = pd.DataFrame({
        "close": close_adj.loc[signal_date],
        "div_yield": div_yield.loc[signal_date],
        "beta": beta.loc[signal_date],
        "pe": pe.loc[signal_date],
        "roe": roe.loc[signal_date],
        "revenue_growth": revenue_growth.loc[signal_date],
        "profit_growth": profit_growth.loc[signal_date],
    })

    universe = universe.dropna(subset=["close", "beta"])
    universe = universe[universe["div_yield"] > 0]

    if universe.empty:
        return [], pd.DataFrame(), pd.DataFrame()

    # HLDB: high dividend yield, then low beta
    threshold: float = universe["div_yield"].quantile(0.9)
    hldb_pool = universe[universe["div_yield"] >= threshold]
    hldb = hldb_pool.sort_values("beta", ascending=True).head(HLDB_COUNT)

    # HLJZ: fundamental filters, then high dividend yield
    hljz_pool = universe[
        universe["pe"].between(5, 50)
        & universe["roe"].between(5, 100)
        & universe["revenue_growth"].between(5, 100)
        & universe["profit_growth"].between(10, 100)
    ]
    hljz = hljz_pool.sort_values("div_yield", ascending=False).head(HLJZ_COUNT)

    targets: list[str] = list(dict.fromkeys(
        hldb.index.tolist() + hljz.index.tolist()
    ))
    return targets, hldb, hljz


def max_drawdown(equity: pd.Series) -> float:
    """Maximum drawdown."""
    peak = equity.cummax()
    return float((equity / peak - 1.0).min())


def annualized_return(equity: pd.Series) -> float:
    """Annualized return from an equity curve."""
    if len(equity) < 2:
        return 0.0
    days = len(equity)
    return float((equity.iloc[-1] / equity.iloc[0]) ** (252.0 / days) - 1.0)


def annualized_vol(returns: pd.Series) -> float:
    """Annualized volatility."""
    return float(returns.std() * math.sqrt(252.0))


def safe_to_csv(df: pd.DataFrame, path: Path) -> Path:
    """Write a CSV, falling back to a sibling file if the target is locked."""
    try:
        df.to_csv(path, index=False, encoding="utf-8")
        return path
    except PermissionError:
        fallback = path.with_name(f"{path.stem}_new{path.suffix}")
        df.to_csv(fallback, index=False, encoding="utf-8")
        print(f"{path.name} 被占用，已写入 {fallback.name}")
        return fallback


def main() -> None:
    """Load data, run the monthly rotation backtest, and print results."""
    if not PRICE_DIR.exists() or not FIN_DIR.exists():
        raise FileNotFoundError("请先运行 fetch_data.py 抓取数据")

    print("加载指数数据……")
    names = load_names()
    index_300 = load_index("index_000300.csv")
    index_015 = load_index("index_000015.csv")
    index_922 = load_index("index_000922.csv")

    calendar: pd.DatetimeIndex = index_300.index
    calendar = calendar[calendar >= pd.Timestamp("2015-01-01")]

    print("加载日线数据……")
    prices_unadj = read_price_dir(PRICE_DIR)
    print(f"股票数量：{len(prices_unadj)}")

    close_unadj = build_matrices(prices_unadj, calendar, "close")
    open_unadj = build_matrices(prices_unadj, calendar, "open")
    close_mark = close_unadj.ffill()

    print("加载财务与分红数据……")
    eps_ttm = build_fin_matrix(calendar, "eps_ttm", ttm_eps=True)
    roe = build_fin_matrix(calendar, "净资产收益率(%)")
    revenue_growth = build_fin_matrix(calendar, "主营业务收入增长率(%)")
    profit_growth = build_fin_matrix(calendar, "净利润增长率(%)")

    pe = close_unadj.div(eps_ttm)
    pe = pe.where(eps_ttm > 0)

    dps_df, bonus_df, dps_ttm = build_dividend_matrices(calendar)
    div_yield = dps_ttm.div(close_unadj)

    # Total return including cash dividends and bonus / transfer shares
    bonus_factor = 1.0 + bonus_df
    total_ret = (
        close_unadj * bonus_factor + dps_df
    ) / close_unadj.shift(1) - 1.0

    print("计算加权 Beta……")
    index_ret = index_300["close"].pct_change()
    stock_ret = total_ret

    # JoinQuant's beta gives more weight to recent observations;
    # use an exponentially weighted 250-day covariance / variance.
    ew_cov = stock_ret.ewm(
        span=BETA_WINDOW, min_periods=BETA_MIN_PERIODS
    ).cov(index_ret)
    ew_var = index_ret.ewm(
        span=BETA_WINDOW, min_periods=BETA_MIN_PERIODS
    ).var()
    beta = ew_cov.div(ew_var, axis=0)

    # Monthly rebalance schedule
    months = pd.Series(calendar, index=calendar).groupby(
        calendar.to_period("M")
    ).last()

    schedule: list[tuple[pd.Timestamp, pd.Timestamp, list[str], pd.DataFrame, pd.DataFrame]] = []
    month_end: pd.Timestamp
    for month_end in months:
        if month_end < BACKTEST_START:
            continue

        positions = calendar.get_indexer([month_end])[0]
        if positions + 1 >= len(calendar):
            continue

        exec_date = calendar[positions + 1]
        targets, hldb, hljz = select_targets(
            month_end,
            close_unadj,
            div_yield,
            beta,
            pe,
            roe,
            revenue_growth,
            profit_growth,
        )
        schedule.append((exec_date, month_end, targets, hldb, hljz))

    print(f"调仓次数：{len(schedule)}")

    # Portfolio state
    cash: float = INITIAL_CAPITAL
    shares: dict[str, float] = {}
    buy_date: dict[str, pd.Timestamp] = {}
    trades: list[dict] = []

    equity_dates: list[pd.Timestamp] = []
    equity_values: list[float] = []
    total_turnover: float = 0.0
    total_fees: float = 0.0
    holding_counts: list[int] = []

    schedule_map: dict[pd.Timestamp, tuple[list[str], pd.DataFrame, pd.DataFrame]] = {
        exec_date: (targets, hldb, hljz)
        for exec_date, signal_date, targets, hldb, hljz in schedule
    }

    backtest_dates = calendar[calendar >= BACKTEST_START]
    last_close: dict[str, float] = {}

    current: pd.Timestamp
    for current in backtest_dates:
        blocked_buy: set[str] = set()

        # -------------------------
        # Corporate actions: cash dividend + bonus / transfer shares
        # -------------------------
        code: str
        for code in list(shares.keys()):
            dps = dps_df.at[current, code] if code in dps_df.columns else 0.0
            bonus = bonus_df.at[current, code] if code in bonus_df.columns else 0.0

            if dps:
                cash += shares[code] * float(dps)
            if bonus:
                shares[code] *= 1.0 + float(bonus)

        # -------------------------
        # Daily limit-up exit rule
        # -------------------------
        pos: int = calendar.get_indexer([current])[0]
        if pos >= 2:
            prev_date: pd.Timestamp = calendar[pos - 1]
            prev2_date: pd.Timestamp = calendar[pos - 2]

            code: str
            for code in list(shares.keys()):
                if buy_date.get(code) == current:
                    continue

                c1 = close_unadj.at[prev_date, code] if code in close_unadj.columns else np.nan
                c0 = close_unadj.at[prev2_date, code] if code in close_unadj.columns else np.nan
                o = open_unadj.at[current, code] if code in open_unadj.columns else np.nan

                if pd.isna(c1) or pd.isna(c0) or pd.isna(o) or c0 <= 0:
                    continue

                limit = board_limit(code)
                yesterday_limit_up = c1 / c0 - 1.0 >= limit - 0.003
                opened = o < c1 * (1.0 + limit) * 0.999

                if yesterday_limit_up and opened:
                    sell_price = o * (1.0 - SLIPPAGE)
                    volume = shares[code]
                    proceeds = volume * sell_price
                    fee = proceeds * (COMMISSION + STAMP_TAX)
                    cash += proceeds - fee
                    total_turnover += proceeds
                    total_fees += fee
                    trades.append({
                        "date": current, "code": code, "side": "sell",
                        "shares": volume, "price": sell_price,
                        "reason": "limit_up_open",
                    })
                    del shares[code]
                    blocked_buy.add(code)

        # -------------------------
        # Monthly rebalance
        # -------------------------
        if current in schedule_map:
            targets, hldb, hljz = schedule_map[current]
            targets = [c for c in targets if c not in blocked_buy]

            if targets:
                n = len(targets)

                # Equity at today's open
                equity_open = cash
                code: str
                for code, volume in shares.items():
                    px = open_unadj.at[current, code] if code in open_unadj.columns else np.nan
                    if pd.isna(px):
                        px = last_close.get(code, 0.0)
                    equity_open += volume * px

                target_value = equity_open * INVEST_RATIO / n

                # Sell names outside the target list
                for code in list(shares.keys()):
                    if code in targets:
                        continue

                    px = open_unadj.at[current, code] if code in open_unadj.columns else np.nan
                    if pd.isna(px):
                        continue

                    sell_price = px * (1.0 - SLIPPAGE)
                    volume = shares[code]
                    proceeds = volume * sell_price
                    fee = proceeds * (COMMISSION + STAMP_TAX)
                    cash += proceeds - fee
                    total_turnover += proceeds
                    total_fees += fee
                    trades.append({
                        "date": current, "code": code, "side": "sell",
                        "shares": volume, "price": sell_price,
                        "reason": "rebalance",
                    })
                    del shares[code]

                # Adjust target weights
                for code in targets:
                    px = open_unadj.at[current, code] if code in open_unadj.columns else np.nan
                    if pd.isna(px) or px <= 0:
                        continue

                    target_shares = math.floor(
                        target_value / (px * (1.0 + SLIPPAGE)) / 100
                    ) * 100
                    current_shares = shares.get(code, 0.0)
                    diff = target_shares - current_shares

                    if diff > 0:
                        buy_price = px * (1.0 + SLIPPAGE)
                        affordable = math.floor(
                            cash / (buy_price * (1.0 + COMMISSION)) / 100
                        ) * 100
                        diff = min(diff, affordable)
                        if diff <= 0:
                            continue

                        cost = diff * buy_price
                        fee = cost * COMMISSION
                        cash -= cost + fee
                        shares[code] = current_shares + diff
                        buy_date[code] = current
                        total_turnover += cost
                        total_fees += fee
                        trades.append({
                            "date": current, "code": code, "side": "buy",
                            "shares": diff, "price": buy_price,
                            "reason": "rebalance",
                        })

                    elif diff < 0:
                        if buy_date.get(code) == current:
                            continue
                        volume = -diff
                        sell_price = px * (1.0 - SLIPPAGE)
                        proceeds = volume * sell_price
                        fee = proceeds * (COMMISSION + STAMP_TAX)
                        cash += proceeds - fee
                        shares[code] = current_shares - volume
                        if shares[code] <= 0:
                            del shares[code]
                        total_turnover += proceeds
                        total_fees += fee
                        trades.append({
                            "date": current, "code": code, "side": "sell",
                            "shares": volume, "price": sell_price,
                            "reason": "rebalance",
                        })

        # -------------------------
        # Mark to market
        # -------------------------
        equity = cash
        code: str
        for code, volume in shares.items():
            px = close_mark.at[current, code] if code in close_mark.columns else np.nan
            if pd.isna(px):
                px = last_close.get(code, 0.0)
            else:
                last_close[code] = float(px)
            equity += volume * px

        equity_dates.append(current)
        equity_values.append(equity)
        holding_counts.append(len(shares))

    equity = pd.Series(equity_values, index=equity_dates)
    daily_ret = equity.pct_change().dropna()

    # Benchmarks
    bench_300 = index_300["close"].reindex(equity.index).ffill()
    bench_015 = index_015["close"].reindex(equity.index).ffill()
    bench_922 = index_922["close"].reindex(equity.index).ffill()

    # Metrics
    total_return = float(equity.iloc[-1] / equity.iloc[0] - 1.0)
    annual_return = annualized_return(equity)
    annual_vol = annualized_vol(daily_ret)
    sharpe = (annual_return - RISK_FREE) / annual_vol if annual_vol else 0.0
    max_dd = max_drawdown(equity)

    bench_300_total = float(bench_300.iloc[-1] / bench_300.iloc[0] - 1.0)
    bench_015_total = float(bench_015.iloc[-1] / bench_015.iloc[0] - 1.0)
    bench_922_total = float(bench_922.iloc[-1] / bench_922.iloc[0] - 1.0)
    bench_300_ann = annualized_return(bench_300)
    bench_015_ann = annualized_return(bench_015)
    bench_922_ann = annualized_return(bench_922)
    bench_300_dd = max_drawdown(bench_300)
    bench_015_dd = max_drawdown(bench_015)
    bench_922_dd = max_drawdown(bench_922)

    # Yearly returns
    yearly_equity = equity.resample("YE").last()
    yearly_returns = yearly_equity.pct_change().dropna()
    yearly_300 = bench_300.resample("YE").last().pct_change().dropna()
    yearly_015 = bench_015.resample("YE").last().pct_change().dropna()
    yearly_922 = bench_922.resample("YE").last().pct_change().dropna()

    # Latest selection
    latest = schedule[-1] if schedule else None

    print()
    print("=" * 78)
    print("红利低波 + 红利价值 双子组合月度轮动回测")
    print("=" * 78)
    print(f"回测区间      : {equity.index[0].date()} ~ {equity.index[-1].date()}")
    print(f"股票池数量    : {len(prices_unadj)}")
    print(f"初始资金      : {INITIAL_CAPITAL:,.2f}")
    print(f"期末权益      : {equity.iloc[-1]:,.2f}")
    print(f"总收益率      : {total_return:+.2%}")
    print(f"年化收益率    : {annual_return:+.2%}")
    print(f"年化波动率    : {annual_vol:.2%}")
    print(f"夏普比率      : {sharpe:.2f}")
    print(f"最大回撤      : {max_dd:.2%}")
    print(f"平均持仓数    : {np.mean(holding_counts):.1f}")
    print(f"累计成交额    : {total_turnover:,.2f}")
    print(f"累计费用      : {total_fees:,.2f}")
    years = len(equity) / 252.0
    annual_turnover = total_turnover / float(equity.mean()) / years if years else 0.0
    print(f"年化换手率    : {annual_turnover:.2f}x")
    print()
    print("基准对比：")
    print(f"  沪深300       总收益 {bench_300_total:+.2%} | 年化 {bench_300_ann:+.2%} | 最大回撤 {bench_300_dd:.2%}")
    print(f"  上证红利      总收益 {bench_015_total:+.2%} | 年化 {bench_015_ann:+.2%} | 最大回撤 {bench_015_dd:.2%}")
    print(f"  中证红利      总收益 {bench_922_total:+.2%} | 年化 {bench_922_ann:+.2%} | 最大回撤 {bench_922_dd:.2%}")
    print(f"  策略超额      相对沪深300 {total_return - bench_300_total:+.2%} | 相对上证红利 {total_return - bench_015_total:+.2%} | 相对中证红利 {total_return - bench_922_total:+.2%}")

    print()
    print("年度收益：")
    year: pd.Timestamp
    for year in yearly_returns.index:
        y = year.year
        r_strategy = yearly_returns.get(year, np.nan)
        r_300 = yearly_300.get(year, np.nan)
        r_015 = yearly_015.get(year, np.nan)
        r_922 = yearly_922.get(year, np.nan)
        print(f"  {y}  策略 {r_strategy:+.2%} | 沪深300 {r_300:+.2%} | 上证红利 {r_015:+.2%} | 中证红利 {r_922:+.2%}")

    hold_counter: dict[str, int] = {}
    for _, _, target_list, _, _ in schedule:
        for code in target_list:
            hold_counter[code] = hold_counter.get(code, 0) + 1

    print()
    print("历史入选次数最多的 10 只股票：")
    ranked = sorted(hold_counter.items(), key=lambda item: item[1], reverse=True)[:10]
    for code, count in ranked:
        print(f"  {code} {names.get(code, ''):8s} 入选 {count} 次")

    if latest:
        exec_date, signal_date, targets, hldb, hljz = latest
        print()
        print(f"最新一期选股（信号日 {signal_date.date()}，执行日 {exec_date.date()}）：")
        print("  红利低波 HLDB：")
        for code, row in hldb.iterrows():
            print(f"    {code} {names.get(code, ''):8s} 股息率 {row['div_yield']:.2%}  Beta {row['beta']:.2f}  PE {row['pe']:.1f}")
        print("  红利价值 HLJZ：")
        for code, row in hljz.iterrows():
            print(f"    {code} {names.get(code, ''):8s} 股息率 {row['div_yield']:.2%}  PE {row['pe']:.1f}  ROE {row['roe']:.1f}  营收增速 {row['revenue_growth']:.1f}  净利增速 {row['profit_growth']:.1f}")
        print(f"  目标持仓：{targets}")

    print()
    print("期末持仓：")
    if shares:
        code: str
        volume: float
        for code, volume in shares.items():
            price = close_mark.at[equity.index[-1], code] if code in close_mark.columns else np.nan
            market_value = volume * float(price) if pd.notna(price) else 0.0
            print(f"  {code} {names.get(code, ''):8s} {volume:>10,.0f} 股  市值 {market_value:>14,.0f}")
    else:
        print("  空仓")

    # Save results
    safe_to_csv(
        pd.DataFrame({
            "date": equity.index,
            "equity": equity.values,
        }),
        DATA_DIR.joinpath("equity_curve.csv"),
    )

    safe_to_csv(
        pd.DataFrame(trades),
        DATA_DIR.joinpath("trades.csv"),
    )

    try:
        import plotly.graph_objects as go

        chart_series: dict[str, pd.Series] = {
            "策略": equity,
            "上证红利": bench_015,
            "中证红利": bench_922,
            "沪深300": bench_300,
        }

        fig = go.Figure()

        name: str
        series: pd.Series
        for name, series in chart_series.items():
            growth: pd.Series = series / series.iloc[0] - 1.0
            cagr: float = annualized_return(series)
            fig.add_trace(go.Scatter(
                x=series.index,
                y=growth,
                mode="lines",
                name=(
                    f"{name}  累计 {growth.iloc[-1]:+.1%} "
                    f"/ 年化 {cagr:+.1%}"
                ),
            ))

        fig.add_hline(y=0, line_width=1, line_color="gray")
        fig.update_layout(
            title="红利低波 + 红利价值 月度轮动：累计增长率",
            xaxis_title="日期",
            yaxis_title="累计增长率",
            yaxis_tickformat=".0%",
        )
        chart_path = DATA_DIR.joinpath("equity_curve.html")
        try:
            fig.write_html(chart_path)
        except PermissionError:
            chart_path = DATA_DIR.joinpath("equity_curve_new.html")
            fig.write_html(chart_path)
            print(f"equity_curve.html 被占用，已写入 {chart_path.name}")
        print()
        print(f"净值曲线已保存：{chart_path}")
    except Exception as exc:
        print(f"图表保存失败：{exc}")

    print()
    print("说明：")
    print("  1. 股票池为当前沪深300成分股，10年回测存在存活偏差。")
    print("  2. 使用不复权价格，并在除权日计入现金分红与送股/转增，重建总收益。")
    print("  3. 财务数据按披露截止日估算可用时间（一季报+31天、半年报+62天、三季报+31天、年报+120天）。")
    print("  4. 未模拟 ST、停牌延迟成交、涨跌停无法买入、冲击成本等全部真实约束。")
    print("  5. 完整源码需聚宽登录，本实现依据文章公开规则重建，细节可能与原作者不同。")


if __name__ == "__main__":
    main()
