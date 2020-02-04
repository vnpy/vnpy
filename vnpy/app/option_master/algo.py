from typing import TYPE_CHECKING, Set

from vnpy.trader.object import TickData, OrderData, TradeData
from vnpy.trader.constant import Direction, Offset
from vnpy.trader.utility import round_to

from .base import OptionData

if TYPE_CHECKING:
    from .engine import OptionAlgoEngine


class ElectronicEyeAlgo:

    def __init__(
        self,
        algo_engine: "OptionAlgoEngine",
        option: OptionData
    ):
        """"""
        self.algo_engine = algo_engine
        self.option = option
        self.underlying = option.underlying
        self.pricetick = option.pricetick
        self.vt_symbol = option.vt_symbol

        # Parameters
        self.pricing_active: bool = False
        self.trading_active: bool = False

        self.price_spread: float = 0.0
        self.volatility_spread: float = 0.0

        self.long_allowed = False
        self.short_allowed = False

        self.max_pos: int = 0
        self.target_pos: int = 0
        self.max_order_size: int = 0

        # Variables
        self.long_active_orderids: Set[str] = set()
        self.short_active_orderids: Set[str] = set()

        self.algo_spread: float = 0.0
        self.ref_price: float = 0.0
        self.algo_bid_price: float = 0.0
        self.algo_ask_price: float = 0.0
        self.pricing_impv: float = 0.0

    def start_pricing(self, params: dict):
        """"""
        if self.pricing_active:
            return

        self.price_spread = params["price_spread"]
        self.volatility_spread = params["volatility_spread"]

        self.pricing_active = True
        self.put_status_event()
        self.calculate_price()

    def stop_pricing(self):
        """"""
        if not self.pricing_active:
            return

        if self.trading_active:
            return

        self.pricing_active = False

        # Clear parameters
        self.algo_spread = 0.0
        self.ref_price = 0.0
        self.algo_bid_price = 0.0
        self.algo_ask_price = 0.0
        self.pricing_impv = 0.0

        self.put_status_event()
        self.put_pricing_event()

    def start_trading(self, params: dict):
        """"""
        if not self.pricing_active:
            return

        if not self.max_order_size:
            return

        self.long_allowed = params["long_allowed"]
        self.short_allowed = params["short_allowed"]
        self.max_pos = params["max_pos"]
        self.target_pos = params["target_pos"]
        self.max_order_size = params["max_order_size"]

        self.trading_active = True

        self.put_trading_event()
        self.put_status_event()

    def stop_trading(self):
        """"""
        if not self.trading_active:
            return

        self.trading_active = False

        self.cancel_long()
        self.cancel_short()

        self.put_status_event()
        self.put_trading_event()

    def on_underlying_tick(self, tick: TickData):
        """"""
        if self.pricing_active:
            self.calculate_price()

        if self.trading_active:
            self.do_trading()

    def on_option_tick(self, tick: TickData):
        """"""
        if self.trading_active:
            self.do_trading()

    def on_order(self, order: OrderData):
        """"""
        if not order.is_active():
            if order.vt_orderid in self.long_active_orderids:
                self.long_active_orderids.remove(order.vt_orderid)
            elif order.vt_orderid in self.short_active_orderids:
                self.short_active_orderids.remove(order.vt_orderid)

    def on_trade(self, trade: TradeData):
        """"""
        pass

    def on_timer(self):
        """"""
        if self.long_active_orderids:
            self.cancel_long()

        if self.short_active_orderids:
            self.cancel_short()

    def send_order(
        self,
        direction: Direction,
        offset: Offset,
        price: float,
        volume: int
    ) -> str:
        """"""
        vt_orderid = self.algo_engine.send_order(
            self,
            self.vt_symbol,
            direction,
            offset,
            price,
            volume
        )

        return vt_orderid

    def buy(self, price: float, volume: int):
        """"""
        vt_orderid = self.send_order(Direction.LONG, Offset.OPEN, price, volume)
        self.long_active_orderids.add(vt_orderid)

    def sell(self, price: float, volume: int):
        """"""
        self.send_order(Direction.SHORT, Offset.CLOSE, price, volume)

    def short(self, price: float, volume: int):
        """"""
        vt_orderid = self.send_order(Direction.SHORT, Offset.OPEN, price, volume)
        self.short_active_orderids.add(vt_orderid)

    def cover(self, price: float, volume: int):
        """"""
        self.send_order(Direction.LONG, Offset.CLOSE, price, volume)

    def send_long(self, price: float, volume: int):
        """"""
        option = self.option

        if not option.short_pos:
            self.buy(price, volume)
        elif option.short_pos >= volume:
            self.cover(price, volume)
        else:
            self.cover(price, option.short_pos)
            self.buy(price, volume - option.short_pos)

    def send_short(self, price: float, volume: int):
        """"""
        option = self.option

        if not option.long_pos:
            self.short(price, volume)
        elif option.long_pos >= volume:
            self.sell(price, volume)
        else:
            self.sell(price, option.long_pos)
            self.short(price, volume - option.long_pos)

        self.order_ask_price = price
        self.order_ask_volume = volume

    def cancel_order(self, vt_orderid):
        """"""
        self.algo_engine.cancel_order(vt_orderid)

    def cancel_long(self):
        """"""
        for vt_orderid in self.long_active_orderids:
            self.cancel_order(vt_orderid)

    def cancel_short(self):
        """"""
        for vt_orderid in self.short_active_orderids:
            self.cancel_order(vt_orderid)

    def check_long_finished(self):
        """"""
        if not self.long_active_orderids:
            return True

        return False

    def check_short_finished(self):
        """"""
        if not self.short_active_orderids:
            return True

        return False

    def calculate_price(self):
        """"""
        option = self.option

        # Get ref price
        self.pricing_impv = option.pricing_impv
        ref_price = option.calculate_ref_price()
        self.ref_price = round_to(ref_price, self.pricetick)

        # Calculate spread
        algo_spread = max(
            self.price_spread,
            self.volatility_spread * option.theo_vega
        )
        half_spread = algo_spread / 2

        # Calculate bid/ask
        self.algo_bid_price = round_to(ref_price - half_spread, self.pricetick)
        self.algo_ask_price = round_to(ref_price + half_spread, self.pricetick)
        self.algo_spread = round_to(algo_spread, self.pricetick)

        self.put_pricing_event()

    def do_trading(self):
        """"""
        if self.long_allowed and self.check_long_finished():
            self.snipe_long()

        if self.short_allowed and self.check_short_finished():
            self.snipe_short()

    def snipe_long(self):
        """"""
        option = self.option
        tick = option.tick

        # Calculate volume left to trade
        pos_up_limit = self.target_pos + self.max_pos
        volume_left = pos_up_limit - option.net_pos

        # Check price
        if volume_left > 0 and tick.ask_price_1 <= self.algo_bid_price:
            volume = min(
                volume_left,
                tick.ask_volume_1,
                self.max_order_size
            )

            self.send_long(self.algo_bid_price, volume)

    def snipe_short(self):
        """"""
        option = self.option
        tick = option.tick

        # Calculate volume left to trade
        pos_down_limit = self.target_pos - self.max_pos
        volume_left = option.net_pos - pos_down_limit

        # Check price
        if volume_left > 0 and tick.bid_price_1 >= self.algo_ask_price:
            volume = min(
                volume_left,
                tick.bid_volume_1,
                self.max_order_size
            )

            self.send_short(self.algo_ask_price, volume)

    def put_pricing_event(self):
        """"""
        self.algo_engine.put_algo_pricing_event(self)

    def put_trading_event(self):
        """"""
        self.algo_engine.put_algo_trading_event(self)

    def put_status_event(self):
        """"""
        self.algo_engine.put_algo_status_event(self)
