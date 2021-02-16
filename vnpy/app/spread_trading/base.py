from typing import Dict, List
from datetime import datetime
from enum import Enum
from functools import lru_cache
from parser import expr

from vnpy.trader.object import (
    TickData, PositionData, TradeData, ContractData, BarData
)
from vnpy.trader.constant import Direction, Offset, Exchange, Interval
from vnpy.trader.utility import floor_to, ceil_to, round_to, extract_vt_symbol
from vnpy.trader.database import database_manager


EVENT_SPREAD_DATA = "eSpreadData"
EVENT_SPREAD_POS = "eSpreadPos"
EVENT_SPREAD_LOG = "eSpreadLog"
EVENT_SPREAD_ALGO = "eSpreadAlgo"
EVENT_SPREAD_STRATEGY = "eSpreadStrategy"


class LegData:
    """"""

    def __init__(self, vt_symbol: str):
        """"""
        self.vt_symbol: str = vt_symbol

        # Price and position data
        self.bid_price: float = 0
        self.ask_price: float = 0
        self.bid_volume: float = 0
        self.ask_volume: float = 0

        self.long_pos: float = 0
        self.short_pos: float = 0
        self.net_pos: float = 0

        self.last_price: float = 0
        self.net_pos_price: float = 0       # Average entry price of net position

        # Tick data buf
        self.tick: TickData = None

        # Contract data
        self.size: float = 0
        self.net_position: bool = False
        self.min_volume: float = 0
        self.pricetick: float = 0

    def update_contract(self, contract: ContractData):
        """"""
        self.size = contract.size
        self.net_position = contract.net_position
        self.min_volume = contract.min_volume
        self.pricetick = contract.pricetick

    def update_tick(self, tick: TickData):
        """"""
        self.bid_price = tick.bid_price_1
        self.ask_price = tick.ask_price_1
        self.bid_volume = tick.bid_volume_1
        self.ask_volume = tick.ask_volume_1
        self.last_price = tick.last_price

        self.tick = tick

    def update_position(self, position: PositionData):
        """"""
        if position.direction == Direction.NET:
            self.net_pos = position.volume
            self.net_pos_price = position.price
        else:
            if position.direction == Direction.LONG:
                self.long_pos = position.volume
            else:
                self.short_pos = position.volume
            self.net_pos = self.long_pos - self.short_pos

    def update_trade(self, trade: TradeData):
        """"""
        # Only update net pos for contract with net position mode
        if self.net_position:
            trade_cost = trade.volume * trade.price
            old_cost = self.net_pos * self.net_pos_price

            if trade.direction == Direction.LONG:
                new_pos = self.net_pos + trade.volume

                if self.net_pos >= 0:
                    new_cost = old_cost + trade_cost
                    self.net_pos_price = new_cost / new_pos
                else:
                    # If all previous short position closed
                    if not new_pos:
                        self.net_pos_price = 0
                    # If only part short position closed
                    elif new_pos > 0:
                        self.net_pos_price = trade.price
            else:
                new_pos = self.net_pos - trade.volume

                if self.net_pos <= 0:
                    new_cost = old_cost - trade_cost
                    self.net_pos_price = new_cost / new_pos
                else:
                    # If all previous long position closed
                    if not new_pos:
                        self.net_pos_price = 0
                    # If only part long position closed
                    elif new_pos < 0:
                        self.net_pos_price = trade.price

            self.net_pos = new_pos
        else:
            if trade.direction == Direction.LONG:
                if trade.offset == Offset.OPEN:
                    self.long_pos += trade.volume
                else:
                    self.short_pos -= trade.volume
            else:
                if trade.offset == Offset.OPEN:
                    self.short_pos += trade.volume
                else:
                    self.long_pos -= trade.volume

            self.net_pos = self.long_pos - self.short_pos


class SpreadData:
    """"""

    def __init__(
        self,
        name: str,
        legs: List[LegData],
        price_multipliers: Dict[str, int],
        trading_multipliers: Dict[str, int],
        active_symbol: str,
        inverse_contracts: Dict[str, bool],
        min_volume: float
    ):
        """"""
        self.name: str = name

        self.legs: Dict[str, LegData] = {}
        self.active_leg: LegData = None
        self.passive_legs: List[LegData] = []

        self.min_volume: float = min_volume
        self.pricetick: float = 0

        # For calculating spread price
        self.price_multipliers: Dict[str, int] = price_multipliers

        # For calculating spread pos and sending orders
        self.trading_multipliers: Dict[str, int] = trading_multipliers

        # For inverse derivative contracts of crypto market
        self.inverse_contracts: Dict[str, bool] = inverse_contracts

        self.price_formula: str = ""
        self.trading_formula: str = ""

        for leg in legs:
            self.legs[leg.vt_symbol] = leg
            if leg.vt_symbol == active_symbol:
                self.active_leg = leg
            else:
                self.passive_legs.append(leg)

            price_multiplier = self.price_multipliers[leg.vt_symbol]
            if price_multiplier > 0:
                self.price_formula += f"+{price_multiplier}*{leg.vt_symbol}"
            else:
                self.price_formula += f"{price_multiplier}*{leg.vt_symbol}"

            trading_multiplier = self.trading_multipliers[leg.vt_symbol]
            if trading_multiplier > 0:
                self.trading_formula += f"+{trading_multiplier}*{leg.vt_symbol}"
            else:
                self.trading_formula += f"{trading_multiplier}*{leg.vt_symbol}"

            if not self.pricetick:
                self.pricetick = leg.pricetick
            else:
                self.pricetick = min(self.pricetick, leg.pricetick)

        # Spread data
        self.bid_price: float = 0
        self.ask_price: float = 0
        self.bid_volume: float = 0
        self.ask_volume: float = 0

        self.net_pos: float = 0
        self.datetime: datetime = None

    def calculate_price(self):
        """"""
        self.clear_price()

        # Go through all legs to calculate price
        for n, leg in enumerate(self.legs.values()):
            # Filter not all leg price data has been received
            if not leg.bid_volume or not leg.ask_volume:
                self.clear_price()
                return

            # Calculate price
            price_multiplier = self.price_multipliers[leg.vt_symbol]
            if price_multiplier > 0:
                self.bid_price += leg.bid_price * price_multiplier
                self.ask_price += leg.ask_price * price_multiplier
            else:
                self.bid_price += leg.ask_price * price_multiplier
                self.ask_price += leg.bid_price * price_multiplier

            # Round price to pricetick
            if self.pricetick:
                self.bid_price = round_to(self.bid_price, self.pricetick)
                self.ask_price = round_to(self.ask_price, self.pricetick)

            # Calculate volume
            trading_multiplier = self.trading_multipliers[leg.vt_symbol]
            inverse_contract = self.inverse_contracts[leg.vt_symbol]

            if not inverse_contract:
                leg_bid_volume = leg.bid_volume
                leg_ask_volume = leg.ask_volume
            else:
                leg_bid_volume = calculate_inverse_volume(
                    leg.bid_volume, leg.bid_price, leg.size)
                leg_ask_volume = calculate_inverse_volume(
                    leg.ask_volume, leg.ask_price, leg.size)

            if trading_multiplier > 0:
                adjusted_bid_volume = floor_to(
                    leg_bid_volume / trading_multiplier,
                    self.min_volume
                )
                adjusted_ask_volume = floor_to(
                    leg_ask_volume / trading_multiplier,
                    self.min_volume
                )
            else:
                adjusted_bid_volume = floor_to(
                    leg_ask_volume / abs(trading_multiplier),
                    self.min_volume
                )
                adjusted_ask_volume = floor_to(
                    leg_bid_volume / abs(trading_multiplier),
                    self.min_volume
                )

            # For the first leg, just initialize
            if not n:
                self.bid_volume = adjusted_bid_volume
                self.ask_volume = adjusted_ask_volume
            # For following legs, use min value of each leg quoting volume
            else:
                self.bid_volume = min(self.bid_volume, adjusted_bid_volume)
                self.ask_volume = min(self.ask_volume, adjusted_ask_volume)

            # Update calculate time
            self.datetime = datetime.now()

    def calculate_pos(self):
        """"""
        long_pos = 0
        short_pos = 0

        for n, leg in enumerate(self.legs.values()):
            leg_long_pos = 0
            leg_short_pos = 0

            trading_multiplier = self.trading_multipliers[leg.vt_symbol]
            if not trading_multiplier:
                continue

            inverse_contract = self.inverse_contracts[leg.vt_symbol]
            if not inverse_contract:
                net_pos = leg.net_pos
            else:
                net_pos = calculate_inverse_volume(
                    leg.net_pos, leg.net_pos_price, leg.size)

            adjusted_net_pos = net_pos / trading_multiplier

            if adjusted_net_pos > 0:
                adjusted_net_pos = floor_to(adjusted_net_pos, self.min_volume)
                leg_long_pos = adjusted_net_pos
            else:
                adjusted_net_pos = ceil_to(adjusted_net_pos, self.min_volume)
                leg_short_pos = abs(adjusted_net_pos)

            if not n:
                long_pos = leg_long_pos
                short_pos = leg_short_pos
            else:
                long_pos = min(long_pos, leg_long_pos)
                short_pos = min(short_pos, leg_short_pos)

        if long_pos > 0:
            self.net_pos = long_pos
        else:
            self.net_pos = -short_pos

    def clear_price(self):
        """"""
        self.bid_price = 0
        self.ask_price = 0
        self.bid_volume = 0
        self.ask_volume = 0

    def calculate_leg_volume(self, vt_symbol: str, spread_volume: float) -> float:
        """"""
        leg = self.legs[vt_symbol]
        trading_multiplier = self.trading_multipliers[leg.vt_symbol]
        leg_volume = spread_volume * trading_multiplier
        return leg_volume

    def calculate_spread_volume(self, vt_symbol: str, leg_volume: float) -> float:
        """"""
        leg = self.legs[vt_symbol]
        trading_multiplier = self.trading_multipliers[leg.vt_symbol]
        spread_volume = leg_volume / trading_multiplier

        if spread_volume > 0:
            spread_volume = floor_to(spread_volume, self.min_volume)
        else:
            spread_volume = ceil_to(spread_volume, self.min_volume)

        return spread_volume

    def to_tick(self):
        """"""
        tick = TickData(
            symbol=self.name,
            exchange=Exchange.LOCAL,
            datetime=self.datetime,
            name=self.name,
            last_price=(self.bid_price + self.ask_price) / 2,
            bid_price_1=self.bid_price,
            ask_price_1=self.ask_price,
            bid_volume_1=self.bid_volume,
            ask_volume_1=self.ask_volume,
            gateway_name="SPREAD"
        )
        return tick

    def is_inverse(self, vt_symbol: str) -> bool:
        """"""
        inverse_contract = self.inverse_contracts[vt_symbol]
        return inverse_contract

    def get_leg_size(self, vt_symbol: str) -> float:
        """"""
        leg = self.legs[vt_symbol]
        return leg.size


class AdvancedSpreadData(SpreadData):
    """"""

    def __init__(
        self,
        name: str,
        legs: List[LegData],
        variable_symbols: Dict[str, str],
        variable_directions: Dict[str, int],
        price_formula: str,
        trading_multipliers: Dict[str, int],
        active_symbol: str,
        inverse_contracts: Dict[str, bool],
        min_volume: float
    ):
        """"""
        super().__init__(
            name,
            legs,
            trading_multipliers,
            trading_multipliers,
            active_symbol,
            inverse_contracts,
            min_volume
        )

        self.variable_symbols = variable_symbols
        self.variable_directions = variable_directions
        self.price_formula = price_formula
        self.price_code = expr(price_formula).compile()

        self.variable_legs = {}
        for variable, vt_symbol in variable_symbols.items():
            leg = self.legs[vt_symbol]
            self.variable_legs[variable] = leg

    def calculate_price(self):
        """"""
        self.clear_price()

        # Go through all legs to calculate price
        bid_data = {}
        ask_data = {}
        volume_inited = False

        for variable, leg in self.variable_legs.items():
            # Filter not all leg price data has been received
            if not leg.bid_volume or not leg.ask_volume:
                self.clear_price()
                return

            # Generate price dict for calculating spread bid/ask
            variable_direction = self.variable_directions[variable]
            if variable_direction > 0:
                bid_data[variable] = leg.bid_price
                ask_data[variable] = leg.ask_price
            else:
                bid_data[variable] = leg.ask_price
                ask_data[variable] = leg.bid_price

            # Calculate volume
            trading_multiplier = self.trading_multipliers[leg.vt_symbol]
            if not trading_multiplier:
                continue

            inverse_contract = self.inverse_contracts[leg.vt_symbol]
            if not inverse_contract:
                leg_bid_volume = leg.bid_volume
                leg_ask_volume = leg.ask_volume
            else:
                leg_bid_volume = calculate_inverse_volume(
                    leg.bid_volume, leg.bid_price, leg.size)
                leg_ask_volume = calculate_inverse_volume(
                    leg.ask_volume, leg.ask_price, leg.size)

            if trading_multiplier > 0:
                adjusted_bid_volume = floor_to(
                    leg_bid_volume / trading_multiplier,
                    self.min_volume
                )
                adjusted_ask_volume = floor_to(
                    leg_ask_volume / trading_multiplier,
                    self.min_volume
                )
            else:
                adjusted_bid_volume = floor_to(
                    leg_ask_volume / abs(trading_multiplier),
                    self.min_volume
                )
                adjusted_ask_volume = floor_to(
                    leg_bid_volume / abs(trading_multiplier),
                    self.min_volume
                )

            # For the first leg, just initialize
            if not volume_inited:
                self.bid_volume = adjusted_bid_volume
                self.ask_volume = adjusted_ask_volume
                volume_inited = True
            # For following legs, use min value of each leg quoting volume
            else:
                self.bid_volume = min(self.bid_volume, adjusted_bid_volume)
                self.ask_volume = min(self.ask_volume, adjusted_ask_volume)

        # Calculate spread price
        self.bid_price = self.parse_formula(self.price_code, bid_data)
        self.ask_price = self.parse_formula(self.price_code, ask_data)

        # Round price to pricetick
        if self.pricetick:
            self.bid_price = round_to(self.bid_price, self.pricetick)
            self.ask_price = round_to(self.ask_price, self.pricetick)

        # Update calculate time
        self.datetime = datetime.now()

    def parse_formula(self, formula: str, data: Dict[str, float]):
        """"""
        locals().update(data)
        value = eval(formula)
        return value


def calculate_inverse_volume(
    original_volume: float,
    price: float,
    size: float,
) -> float:
    """"""
    if not price:
        return 0
    return original_volume * size / price


class BacktestingMode(Enum):
    BAR = 1
    TICK = 2


@lru_cache(maxsize=999)
def load_bar_data(
    spread: SpreadData,
    interval: Interval,
    start: datetime,
    end: datetime,
    pricetick: float = 0
):
    """"""
    # Load bar data of each spread leg
    leg_bars: Dict[str, Dict] = {}

    for vt_symbol in spread.legs.keys():
        symbol, exchange = extract_vt_symbol(vt_symbol)

        bar_data: List[BarData] = database_manager.load_bar_data(
            symbol, exchange, interval, start, end
        )

        bars: Dict[datetime, BarData] = {bar.datetime: bar for bar in bar_data}
        leg_bars[vt_symbol] = bars

    # Calculate spread bar data
    spread_bars: List[BarData] = []

    for dt in bars.keys():
        spread_price = 0
        spread_value = 0
        spread_available = True

        for leg in spread.legs.values():
            leg_bar = leg_bars[leg.vt_symbol].get(dt, None)

            if leg_bar:
                price_multiplier = spread.price_multipliers[leg.vt_symbol]
                spread_price += price_multiplier * leg_bar.close_price
                spread_value += abs(price_multiplier) * leg_bar.close_price
            else:
                spread_available = False

        if spread_available:
            if pricetick:
                spread_price = round_to(spread_price, pricetick)

            spread_bar = BarData(
                symbol=spread.name,
                exchange=exchange.LOCAL,
                datetime=dt,
                interval=interval,
                open_price=spread_price,
                high_price=spread_price,
                low_price=spread_price,
                close_price=spread_price,
                gateway_name="SPREAD",
            )
            spread_bar.value = spread_value
            spread_bars.append(spread_bar)

    return spread_bars


@lru_cache(maxsize=999)
def load_tick_data(
    spread: SpreadData,
    start: datetime,
    end: datetime
):
    """"""
    return database_manager.load_tick_data(
        spread.name, Exchange.LOCAL, start, end
    )
