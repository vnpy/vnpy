from datetime import datetime
from typing import Callable, Dict

from vnpy.trader.object import BarData, TickData


class PortfolioBarGenerator:
    """"""

    def __init__(self, on_bars: Callable):
        """Constructor"""
        self.on_bars: Callable = on_bars

        self.bars: Dict[str, BarData] = {}
        self.last_ticks: Dict[str, TickData] = {}

        self.last_dt: datetime = None

    def update_tick(self, tick: TickData) -> None:
        """"""
        if not tick.last_price:
            return

        if self.last_dt and self.last_dt.minute != tick.datetime.minute:
            for bar in self.bars.items():
                bar.datetime = bar.datetime.replace(second=0, microsecond=0)

            self.on_bars(self.bars)
            self.bars = {}

        bar = self.bars.get(tick.vt_symbol, None)
        if not bar:
            bar = BarData(
                symbol=tick.symbol,
                exchange=tick.exchange,
                interval=self.interval,
                datetime=tick.datetime,
                gateway_name=tick.gateway_name,
                open_price=tick.last_price,
                high_price=tick.last_price,
                low_price=tick.last_price,
                close_price=tick.last_price,
                open_interest=tick.open_interest
            )
            self.bars[bar.vt_symbol] = bar
        else:
            bar.high_price = max(bar.high_price, tick.last_price)
            bar.low_price = min(bar.low_price, tick.last_price)
            bar.close_price = tick.last_price
            bar.open_interest = tick.open_interest
            bar.datetime = tick.datetime

        last_tick = self.last_ticks.get(tick.vt_symbol, None)
        if last_tick:
            bar.volume += max(tick.volume - last_tick.volume, 0)
            bar.turnover += max(tick.turnover - last_tick.turnover, 0)

        self.last_ticks[tick.vt_symbol] = tick
        self.last_dt = tick.datetime
