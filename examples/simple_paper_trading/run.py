"""
Paper-trading end-to-end demo.

Flow:
    1. Generate a reproducible daily bar CSV (replace with real market data)
    2. EventEngine + MainEngine + SimGateway
    3. MaCrossStrategy subscribes and trades through the standard vnpy API
    4. SimGateway fills orders and pushes order/trade/position/account events
    5. Print the final account, positions, trades, and equity statistics

Run:
    python examples/simple_paper_trading/run.py

Switch to a real broker:
    * Replace SimGateway with vnpy_ctp / vnpy_xtp / vnpy_tora ... in run.py
    * Keep ma_strategy.py (or replace it with your own strategy)
"""

import sys
from datetime import datetime
from pathlib import Path
from time import sleep
from typing import cast

# Windows 控制台默认可能是 GBK，统一用 UTF-8 输出中文日志
if sys.stdout.encoding and sys.stdout.encoding.lower() not in {"utf-8", "utf8"}:
    sys.stdout.reconfigure(encoding="utf-8", errors="replace")  # type: ignore[attr-defined]

import numpy as np
import pandas as pd

from vnpy.event import EventEngine
from vnpy.trader.engine import MainEngine
from vnpy.trader.object import AccountData, PositionData, TradeData

from ma_strategy import MaCrossStrategy
from sim_gateway import SimGateway


SYMBOLS: list[str] = [
    "600000.SSE",
    "000001.SZSE",
    "600519.SSE",
]

START: datetime = datetime(2023, 1, 1)
END: datetime = datetime(2024, 12, 31)
INITIAL_CAPITAL: float = 1_000_000

DATA_PATH: Path = Path(__file__).resolve().parent.joinpath("data", "bars.csv")


def generate_bar_csv(path: Path, seed: int = 42) -> int:
    """Generate simulated daily bars and save them as CSV."""
    rng: np.random.Generator = np.random.default_rng(seed)
    dates: pd.DatetimeIndex = pd.bdate_range(START, END)

    rows: list[dict] = []

    i: int
    vt_symbol: str
    for i, vt_symbol in enumerate(SYMBOLS):
        symbol, exchange = vt_symbol.split(".")
        count: int = len(dates)

        # Persistent drift makes MA crossover meaningful on synthetic data
        drift: np.ndarray = np.zeros(count)
        t: int
        for t in range(1, count):
            drift[t] = 0.95 * drift[t - 1] + rng.normal(0, 0.0015)

        volatility: float = 0.012 + 0.004 * i
        returns: np.ndarray = drift + rng.normal(0, volatility, count)
        closes: np.ndarray = 20.0 * np.exp(np.cumsum(returns))

        opens: np.ndarray = closes * (1 + rng.normal(0, 0.002, count))
        highs: np.ndarray = np.maximum(opens, closes) * (
            1 + np.abs(rng.normal(0, 0.004, count))
        )
        lows: np.ndarray = np.minimum(opens, closes) * (
            1 - np.abs(rng.normal(0, 0.004, count))
        )
        volumes: np.ndarray = np.maximum(
            rng.lognormal(12, 0.4, count).round(), 100
        )
        vwaps: np.ndarray = (highs + lows + closes) / 3
        turnovers: np.ndarray = volumes * vwaps

        j: int
        for j in range(count):
            rows.append({
                "datetime": dates[j].strftime("%Y-%m-%d %H:%M:%S"),
                "symbol": symbol,
                "exchange": exchange,
                "interval": "d",
                "open": round(float(opens[j]), 2),
                "high": round(float(highs[j]), 2),
                "low": round(float(lows[j]), 2),
                "close": round(float(closes[j]), 2),
                "volume": float(volumes[j]),
                "turnover": float(turnovers[j]),
            })

    path.parent.mkdir(parents=True, exist_ok=True)
    pd.DataFrame(rows).to_csv(path, index=False)

    return len(rows)


def max_drawdown(curve: list[tuple[datetime, float]]) -> float:
    """Calculate the maximum drawdown from an equity curve."""
    peak: float = 0.0
    drawdown: float = 0.0

    dt: datetime
    value: float
    for dt, value in curve:
        peak = max(peak, value)
        if peak:
            drawdown = min(drawdown, value / peak - 1)

    return drawdown


def print_report(
    main_engine: MainEngine,
    gateway: SimGateway,
    strategy: MaCrossStrategy
) -> None:
    """Print account, positions, trades, and equity statistics."""
    account: AccountData | None = main_engine.get_account("SIM.PAPER")
    positions: list[PositionData] = [
        position
        for position in main_engine.get_all_positions()
        if position.volume
    ]
    trades: list[TradeData] = main_engine.get_all_trades()
    orders: list = main_engine.get_all_orders()
    last_prices: dict[str, float] = gateway.get_last_prices()
    curve: list[tuple[datetime, float]] = gateway.get_equity_curve()

    print()
    print("=" * 72)
    print("模拟交易结果")
    print("=" * 72)

    if account:
        total_return: float = account.balance / INITIAL_CAPITAL - 1
        print(f"初始资金     : {INITIAL_CAPITAL:>15,.2f}")
        print(f"期末权益     : {account.balance:>15,.2f}")
        print(f"可用资金     : {account.available:>15,.2f}")
        print(f"冻结资金     : {account.frozen:>15,.2f}")
        print(f"累计手续费   : {gateway.get_total_commission():>15,.2f}")
        print(f"总收益率     : {total_return:>15.2%}")
    else:
        print("没有收到账户数据")

    if curve:
        print(f"最大回撤     : {max_drawdown(curve):>15.2%}")

    print(f"委托笔数     : {len(orders):>15d}")
    print(f"成交笔数     : {len(trades):>15d}")
    print(f"策略内部持仓 : {dict(strategy.pos)}")

    print()
    print("当前持仓：")
    if positions:
        position: PositionData
        for position in positions:
            last_price: float = last_prices.get(position.vt_symbol, position.price)
            print(
                f"  {position.vt_symbol:12s} "
                f"数量={position.volume:>8.0f} "
                f"成本={position.price:>8.2f} "
                f"现价={last_price:>8.2f} "
                f"浮盈={position.pnl:>12.2f}"
            )
    else:
        print("  空仓")

    print()
    print("成交记录：")
    if not trades:
        print("  无")
    else:
        display: list[TradeData]
        if len(trades) <= 10:
            display = trades
        else:
            display = trades[:5] + trades[-5:]

        trade: TradeData
        for trade in display:
            print(
                f"  {trade.datetime}  {trade.vt_symbol:12s} "
                f"{trade.direction.value} {trade.volume:>8.0f} "
                f"@ {trade.price:>8.2f}"
            )

        if len(trades) > len(display):
            print(f"  ... 省略 {len(trades) - len(display)} 笔 ...")

    print()
    print("说明：模拟网关按下一根 K 线的限价撮合，未模拟滑点、部分成交和涨跌停。")


def main() -> None:
    """Run the paper-trading demo."""
    print("=" * 72)
    print("步骤 1/4：生成模拟行情")
    print("=" * 72)

    count: int = generate_bar_csv(DATA_PATH)
    print(f"已生成 {count} 条日线：{DATA_PATH}")

    print()
    print("=" * 72)
    print("步骤 2/4：创建事件引擎、主引擎和模拟网关")
    print("=" * 72)

    event_engine: EventEngine = EventEngine()
    main_engine: MainEngine = MainEngine(event_engine)

    main_engine.add_gateway(SimGateway)
    print("主引擎与模拟网关创建完成")

    print()
    print("=" * 72)
    print("步骤 3/4：创建策略并连接模拟网关")
    print("=" * 72)

    strategy: MaCrossStrategy = MaCrossStrategy(
        main_engine=main_engine,
        event_engine=event_engine,
        gateway_name="SIM",
        vt_symbols=SYMBOLS,
        fast_window=5,
        slow_window=20,
        trade_volume=5_000,
        price_add=0.002,
    )

    main_engine.connect(
        {
            "data_file": str(DATA_PATH),
            "speed": 0.002,
            "capital": INITIAL_CAPITAL,
            "buy_rate": 0.0005,
            "sell_rate": 0.0015,
        },
        "SIM",
    )

    gateway: SimGateway = cast(SimGateway, main_engine.get_gateway("SIM"))

    print()
    print("=" * 72)
    print("步骤 4/4：回放行情并模拟撮合")
    print("=" * 72)

    while not gateway.is_finished():
        sleep(0.05)

    # Give the event engine a moment to process the last queued events
    sleep(1.0)

    main_engine.close()

    print_report(main_engine, gateway, strategy)


if __name__ == "__main__":
    main()
