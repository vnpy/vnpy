from typing import Dict, TYPE_CHECKING

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

        self.trades: Dict[str, TradeData] = {}

    def update_trade(self, trade: TradeData) -> None:
        """"""
        self.trades[trade.vt_tradeid] = trade

        if trade.direction == Direction.LONG:
            self.last_pos += trade.volume
        else:
            self.last_pos -= trade.volume

    def calculate_pnl(self) -> None:
        """"""
        vt_symbol = self.vt_symbol

        contract = self.engine.get_conrtact(vt_symbol)
        tick = self.engine.get_tick(vt_symbol)
        if not contract or not tick:
            return

        last_price = tick.last_price
        size = contract.size

        # Calculate trading pnl
        trading_pnl = 0

        for trade in self.trades.values():
            if trade.direction == Direction.LONG:
                pos_change = trade.volume
            else:
                pos_change = -trade.volume

            pnl = (last_price - trade.price) * pos_change * size
            trading_pnl += pnl

        self.trading_pnl = trading_pnl

        # Calculate holding pnl
        self.holding_pnl = (last_price - tick.pre_close) * self.open_pos * size


class PortfolioResult:
    """"""

    def __init__(self, reference: str) -> None:
        """"""
        super().__init__()

        self.reference: str = reference
        self.trading_pnl: float = 0
        self.holding_pnl: float = 0

    def clear_pnl(self) -> None:
        """"""
        self.trading_pnl = 0
        self.holding_pnl = 0
