from datetime import datetime
from typing import cast

import polars as pl

from vnpy.alpha.lab import AlphaLab
from vnpy.alpha.strategy.backtesting import BacktestingEngine
from vnpy.alpha.strategy.template import AlphaStrategy
from vnpy.trader.constant import Direction, Exchange, Offset
from vnpy.trader.object import BarData, OrderData, TradeData
from vnpy.trader.utility import extract_vt_symbol, round_to


class RecordingStrategy(AlphaStrategy):
    target_volume: float = 1
    price_add: float = 0

    def on_init(self) -> None:
        self.sent: bool = False
        self.trade_counts: list[int] = []
        self.seen_symbols: list[set[str]] = []
        self.cached_ohlc: list[tuple[float, float, float, float]] = []

    def on_bars(self, bars: dict[str, BarData]) -> None:
        self.trade_counts.append(len(self.strategy_engine.trades))
        self.seen_symbols.append(set(bars))
        vt_symbol: str = self.vt_symbols[0]
        cached: BarData = self.strategy_engine.bars[vt_symbol]
        self.cached_ohlc.append(
            (cached.open_price, cached.high_price, cached.low_price, cached.close_price)
        )
        if self.sent or vt_symbol not in bars:
            return
        self.set_target(vt_symbol, self.target_volume)
        self.execute_trading(bars, self.price_add)
        self.sent = True

    def on_trade(self, trade: TradeData) -> None:
        return


def new_engine(vt_symbols: list[str], capital: float) -> BacktestingEngine:
    engine: BacktestingEngine = BacktestingEngine(cast(AlphaLab, object()))
    engine.vt_symbols = list(vt_symbols)
    engine.capital = capital
    engine.cash = capital
    vt_symbol: str
    for vt_symbol in vt_symbols:
        engine.long_rates[vt_symbol] = 0
        engine.short_rates[vt_symbol] = 0
        engine.sizes[vt_symbol] = 1
        engine.priceticks[vt_symbol] = 1
    return engine


def make_bar(
    vt_symbol: str,
    dt: datetime,
    open_price: float,
    high_price: float,
    low_price: float,
    close_price: float,
) -> BarData:
    symbol: str
    exchange: Exchange
    symbol, exchange = extract_vt_symbol(vt_symbol)
    return BarData(
        gateway_name="BACKTESTING",
        symbol=symbol,
        exchange=exchange,
        datetime=dt,
        open_price=open_price,
        high_price=high_price,
        low_price=low_price,
        close_price=close_price,
    )


def add_history(engine: BacktestingEngine, bars: list[BarData]) -> None:
    bar: BarData
    for bar in bars:
        engine.dts.add(bar.datetime)
        engine.history_data[(bar.datetime, bar.vt_symbol)] = bar


def run_recording(
    engine: BacktestingEngine,
    target_volume: float,
    price_add: float,
) -> RecordingStrategy:
    engine.add_strategy(
        RecordingStrategy,
        {"target_volume": target_volume, "price_add": price_add},
        pl.DataFrame(),
    )
    engine.run_backtesting()
    assert isinstance(engine.strategy, RecordingStrategy)
    return engine.strategy


def test_order_from_first_bar_fills_on_second_bar() -> None:
    vt_symbol: str = "rb2410.SHFE"
    first_dt: datetime = datetime(2024, 1, 2, 9, 0)
    second_dt: datetime = datetime(2024, 1, 2, 9, 1)
    engine: BacktestingEngine = new_engine([vt_symbol], 1_000_000)
    add_history(
        engine,
        [
            make_bar(vt_symbol, first_dt, 100, 101, 99, 100),
            make_bar(vt_symbol, second_dt, 100, 101, 99, 100),
        ],
    )

    strategy: RecordingStrategy = run_recording(engine, target_volume=1, price_add=0)
    trades: list[TradeData] = engine.get_all_trades()

    # 第 2 根 on_bars 开始时成交已经在，cross_order 发生在 on_bars 之前。
    assert strategy.trade_counts == [0, 1]
    assert len(trades) == 1
    assert trades[0].datetime == second_dt


def test_long_and_short_cross_prices_use_open() -> None:
    long_symbol: str = "rb2410.SHFE"
    long_first: datetime = datetime(2024, 1, 2, 9, 0)
    long_second: datetime = datetime(2024, 1, 2, 9, 1)
    long_engine: BacktestingEngine = new_engine([long_symbol], 1_000_000)
    add_history(
        long_engine,
        [
            make_bar(long_symbol, long_first, 100, 101, 99, 100),
            make_bar(long_symbol, long_second, 102, 106, 101, 104),
        ],
    )
    run_recording(long_engine, target_volume=1, price_add=0.05)
    long_trades: list[TradeData] = long_engine.get_all_trades()
    # 委托价 105 >= low 101 且 low > 0，多头成交价取 min(委托价, open)。
    assert len(long_trades) == 1
    assert long_trades[0].direction == Direction.LONG
    assert long_trades[0].price == 102

    short_symbol: str = "hc2410.SHFE"
    short_first: datetime = datetime(2024, 1, 2, 9, 0)
    short_second: datetime = datetime(2024, 1, 2, 9, 1)
    short_engine: BacktestingEngine = new_engine([short_symbol], 1_000_000)
    add_history(
        short_engine,
        [
            make_bar(short_symbol, short_first, 100, 101, 99, 100),
            make_bar(short_symbol, short_second, 104, 106, 98, 103),
        ],
    )
    run_recording(short_engine, target_volume=-1, price_add=0)
    short_trades: list[TradeData] = short_engine.get_all_trades()
    # 委托价 100 <= high 106 且 high > 0，空头成交价取 max(委托价, open)。
    assert len(short_trades) == 1
    assert short_trades[0].direction == Direction.SHORT
    assert short_trades[0].price == 104


def test_long_fill_cash_deducts_turnover_and_rate() -> None:
    vt_symbol: str = "rb2410.SHFE"
    capital: float = 1_000_000
    first_dt: datetime = datetime(2024, 1, 2, 9, 0)
    second_dt: datetime = datetime(2024, 1, 2, 9, 1)
    engine: BacktestingEngine = new_engine([vt_symbol], capital)
    engine.long_rates[vt_symbol] = 0.125
    engine.short_rates[vt_symbol] = 0.5
    engine.sizes[vt_symbol] = 10
    add_history(
        engine,
        [
            make_bar(vt_symbol, first_dt, 100, 101, 99, 100),
            make_bar(vt_symbol, second_dt, 100, 101, 99, 100),
        ],
    )

    run_recording(engine, target_volume=2, price_add=0)
    trades: list[TradeData] = engine.get_all_trades()

    assert len(trades) == 1
    assert trades[0].price == 100
    assert trades[0].volume == 2
    # turnover = 100 * 2 * 10；cash = capital - turnover - turnover * long_rate。
    assert engine.cash == 997_750
    assert engine.capital == capital


def test_execute_trading_price_add_rounds_to_tick() -> None:
    vt_symbol: str = "rb2410.SHFE"
    close_price: float = 100.3
    pricetick: float = 0.2
    engine: BacktestingEngine = new_engine([vt_symbol], 1_000_000)
    engine.priceticks[vt_symbol] = pricetick
    add_history(
        engine,
        [make_bar(vt_symbol, datetime(2024, 1, 2, 9, 0), 100, 101, 99, close_price)],
    )

    run_recording(engine, target_volume=1, price_add=0.05)
    orders: list[OrderData] = engine.get_all_orders()

    assert len(orders) == 1
    assert orders[0].offset == Offset.OPEN
    assert orders[0].price == round_to(close_price * 1.05, pricetick)
    assert orders[0].price == 105.4


def test_missing_bar_is_filled_for_cross_but_hidden_from_on_bars() -> None:
    target_symbol: str = "rb2410.SHFE"
    other_symbol: str = "hc2410.SHFE"
    first_dt: datetime = datetime(2024, 1, 2)
    second_dt: datetime = datetime(2024, 1, 3)
    engine: BacktestingEngine = new_engine([target_symbol, other_symbol], 1_000_000)
    add_history(
        engine,
        [
            make_bar(target_symbol, first_dt, 110, 112, 108, 100),
            make_bar(other_symbol, first_dt, 50, 51, 49, 50),
            make_bar(other_symbol, second_dt, 50, 52, 48, 51),
        ],
    )

    strategy: RecordingStrategy = run_recording(engine, target_volume=1, price_add=0.05)
    trades: list[TradeData] = engine.get_all_trades()

    assert strategy.seen_symbols[0] == {target_symbol, other_symbol}
    assert strategy.seen_symbols[1] == {other_symbol}
    assert strategy.cached_ohlc[1] == (100, 100, 100, 100)
    assert len(trades) == 1
    assert trades[0].datetime == second_dt
    assert trades[0].price == 100
