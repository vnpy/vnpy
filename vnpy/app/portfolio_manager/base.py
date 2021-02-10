from typing import Dict, List, TYPE_CHECKING

from vnpy.trader.object import TradeData
from vnpy.trader.constant import Direction

if TYPE_CHECKING:
    from .engine import PortfolioEngine


class ContractResult:
    """"""

    def __init__(
        self,
        engine: "PortfolioEngine",
        reference: str,
        vt_symbol: str,
        open_pos: int = 0
    ) -> None:
        """"""
        super().__init__()

        self.engine: "PortfolioEngine" = engine

        self.reference: str = reference
        self.vt_symbol: str = vt_symbol

        self.open_pos: int = open_pos
        self.last_pos: int = open_pos

        self.trading_pnl: float = 0
        self.holding_pnl: float = 0
        self.total_pnl: float = 0

        self.trades: Dict[str, TradeData] = {}
        self.new_trades: List[TradeData] = []

        self.long_volume: float = 0
        self.short_volume: float = 0
        self.long_cost: float = 0
        self.short_cost: float = 0

    def update_trade(self, trade: TradeData) -> None:
        """"""
        # Filter duplicate trade push
        if trade.vt_tradeid in self.trades:
            return
        self.trades[trade.vt_tradeid] = trade
        self.new_trades.append(trade)

        if trade.direction == Direction.LONG:
            self.last_pos += trade.volume
        else:
            self.last_pos -= trade.volume

    def calculate_pnl(self) -> None:
        """"""
        vt_symbol = self.vt_symbol

        contract = self.engine.get_contract(vt_symbol)
        tick = self.engine.get_tick(vt_symbol)
        if not contract or not tick:
            return

        last_price = tick.last_price
        size = contract.size

        # Sum new trade cost
        for trade in self.new_trades:
            trade_volume = trade.volume
            trade_cost = trade.price * trade_volume * size

            if trade.direction == Direction.LONG:
                self.long_cost += trade_cost
                self.long_volume += trade_volume
            else:
                self.short_cost += trade_cost
                self.short_volume += trade_volume

        self.new_trades.clear()

        # Calculate trading pnl
        long_value = self.long_volume * last_price * size
        long_pnl = long_value - self.long_cost

        shrot_value = self.short_volume * last_price * size
        short_pnl = self.short_cost - shrot_value

        self.trading_pnl = long_pnl + short_pnl

        # Calculate holding and total pnl
        self.holding_pnl = (last_price - tick.pre_close) * self.open_pos * size
        self.total_pnl = self.holding_pnl + self.trading_pnl


class PortfolioResult:
    """"""

    def __init__(self, reference: str) -> None:
        """"""
        super().__init__()

        self.reference: str = reference
        self.trading_pnl: float = 0
        self.holding_pnl: float = 0
        self.total_pnl: float = 0

    def clear_pnl(self) -> None:
        """"""
        self.trading_pnl = 0
        self.holding_pnl = 0
        self.total_pnl = 0
