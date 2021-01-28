from typing import List, Dict
from datetime import datetime

from vnpy.app.portfolio_strategy import StrategyTemplate, StrategyEngine
from vnpy.trader.utility import BarGenerator, extract_vt_symbol
from vnpy.trader.object import TickData, BarData


class PcpArbitrageStrategy(StrategyTemplate):
    """"""

    author = "用Python的交易员"

    entry_level = 20
    price_add = 5
    fixed_size = 1

    strike_price = 0
    futures_price = 0
    synthetic_price = 0
    current_spread = 0
    futures_pos = 0
    call_pos = 0
    put_pos = 0
    futures_target = 0
    call_target = 0
    put_target = 0

    parameters = [
        "entry_level",
        "price_add",
        "fixed_size"
    ]
    variables = [
        "strike_price",
        "futures_price",
        "synthetic_price",
        "current_spread",
        "futures_pos",
        "call_pos",
        "put_pos",
        "futures_target",
        "call_target",
        "put_target",
    ]

    def __init__(
        self,
        strategy_engine: StrategyEngine,
        strategy_name: str,
        vt_symbols: List[str],
        setting: dict
    ):
        """"""
        super().__init__(strategy_engine, strategy_name, vt_symbols, setting)

        self.bgs: Dict[str, BarGenerator] = {}
        self.last_tick_time: datetime = None

        # Obtain contract info
        for vt_symbol in self.vt_symbols:
            symbol, exchange = extract_vt_symbol(vt_symbol)

            if "C" in symbol:
                self.call_symbol = vt_symbol
                _, strike_str = symbol.split("-C-")     # For CFFEX/DCE options
                self.strike_price = int(strike_str)
            elif "P" in symbol:
                self.put_symbol = vt_symbol
            else:
                self.futures_symbol = vt_symbol

            def on_bar(bar: BarData):
                """"""
                pass

            self.bgs[vt_symbol] = BarGenerator(on_bar)

    def on_init(self):
        """
        Callback when strategy is inited.
        """
        self.write_log("策略初始化")

        self.load_bars(1)

    def on_start(self):
        """
        Callback when strategy is started.
        """
        self.write_log("策略启动")

    def on_stop(self):
        """
        Callback when strategy is stopped.
        """
        self.write_log("策略停止")

    def on_tick(self, tick: TickData):
        """
        Callback of new tick data update.
        """
        if (
            self.last_tick_time
            and self.last_tick_time.minute != tick.datetime.minute
        ):
            bars = {}
            for vt_symbol, bg in self.bgs.items():
                bars[vt_symbol] = bg.generate()
            self.on_bars(bars)

        bg: BarGenerator = self.bgs[tick.vt_symbol]
        bg.update_tick(tick)

        self.last_tick_time = tick.datetime

    def on_bars(self, bars: Dict[str, BarData]):
        """"""
        self.cancel_all()

        # Calcualate spread data
        call_bar = bars[self.call_symbol]
        put_bar = bars[self.put_symbol]
        futures_bar = bars[self.futures_symbol]

        self.futures_price = futures_bar.close_price
        self.synthetic_price = (
            call_bar.close_price - put_bar.close_price + self.strike_price
        )
        self.current_spread = self.synthetic_price - self.futures_price

        # Get current position
        self.call_pos = self.get_pos(self.call_symbol)
        self.put_pos = self.get_pos(self.put_symbol)
        self.futures_pos = self.get_pos(self.futures_symbol)

        # Calculate target position
        if not self.futures_pos:
            if self.current_spread > self.entry_level:
                self.call_target = -self.fixed_size
                self.put_target = self.fixed_size
                self.futures_target = self.fixed_size
            elif self.current_spread < -self.entry_level:
                self.call_target = self.fixed_size
                self.put_target = -self.fixed_size
                self.futures_target = -self.fixed_size
        elif self.futures_pos > 0:
            if self.current_spread <= 0:
                self.call_target = 0
                self.put_target = 0
                self.futures_target = 0
        else:
            if self.current_spread >= 0:
                self.call_target = 0
                self.put_target = 0
                self.futures_target = 0

        # Execute orders
        target = {
            self.call_symbol: self.call_target,
            self.put_symbol: self.put_target,
            self.futures_symbol: self.futures_target
        }

        for vt_symbol in self.vt_symbols:
            target_pos = target[vt_symbol]
            current_pos = self.get_pos(vt_symbol)

            pos_diff = target_pos - current_pos
            volume = abs(pos_diff)
            bar = bars[vt_symbol]

            if pos_diff > 0:
                price = bar.close_price + self.price_add

                if current_pos < 0:
                    self.cover(vt_symbol, price, volume)
                else:
                    self.buy(vt_symbol, price, volume)
            elif pos_diff < 0:
                price = bar.close_price - self.price_add

                if current_pos > 0:
                    self.sell(vt_symbol, price, volume)
                else:
                    self.short(vt_symbol, price, volume)

        self.put_event()
