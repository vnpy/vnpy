"""
Position holdings and offset conversion for close, lock, and net modes.
"""

from collections.abc import Callable
from copy import copy
from typing import TYPE_CHECKING

from .object import (
    ContractData,
    OrderData,
    TradeData,
    PositionData,
    OrderRequest
)
from .constant import Direction, Offset, Exchange

if TYPE_CHECKING:
    from .engine import OmsEngine


class PositionHolding:
    """
    Track long and short position and frozen volume for one contract.
    """

    def __init__(self, contract: ContractData) -> None:
        """
        Initialize position counters and the active-order map from the contract.
        """
        self.vt_symbol: str = contract.vt_symbol
        self.exchange: Exchange = contract.exchange

        self.active_orders: dict[str, OrderData] = {}

        self.long_pos: float = 0
        self.long_yd: float = 0
        self.long_td: float = 0

        self.short_pos: float = 0
        self.short_yd: float = 0
        self.short_td: float = 0

        self.long_pos_frozen: float = 0
        self.long_yd_frozen: float = 0
        self.long_td_frozen: float = 0

        self.short_pos_frozen: float = 0
        self.short_yd_frozen: float = 0
        self.short_td_frozen: float = 0

    def update_position(self, position: PositionData) -> None:
        """
        Update long or short position volume from a position snapshot.
        """
        if position.direction == Direction.LONG:
            self.long_pos = position.volume
            self.long_yd = position.yd_volume
            self.long_td = self.long_pos - self.long_yd
        else:
            self.short_pos = position.volume
            self.short_yd = position.yd_volume
            self.short_td = self.short_pos - self.short_yd

    def update_order(self, order: OrderData) -> None:
        """
        Store an active order or drop an inactive one, then recalculate frozen volume.
        """
        if order.is_active():
            self.active_orders[order.vt_orderid] = order
        else:
            if order.vt_orderid in self.active_orders:
                self.active_orders.pop(order.vt_orderid)

        self.calculate_frozen()

    def update_order_request(self, req: OrderRequest, vt_orderid: str) -> None:
        """
        Build an order from the request and update frozen volume.
        """
        gateway_name: str
        orderid: str
        gateway_name, orderid = vt_orderid.split(".")

        order: OrderData = req.create_order_data(orderid, gateway_name)
        self.update_order(order)

    def update_trade(self, trade: TradeData) -> None:
        """
        Apply a fill to today and yesterday positions, then cap frozen volume.
        """
        if trade.direction == Direction.LONG:
            if trade.offset == Offset.OPEN:
                self.long_td += trade.volume
            elif trade.offset == Offset.CLOSETODAY:
                self.short_td -= trade.volume
            elif trade.offset == Offset.CLOSEYESTERDAY:
                self.short_yd -= trade.volume
            elif trade.offset == Offset.CLOSE:
                if trade.exchange in {Exchange.SHFE, Exchange.INE}:
                    self.short_yd -= trade.volume
                else:
                    self.short_td -= trade.volume

                    if self.short_td < 0:
                        self.short_yd += self.short_td
                        self.short_td = 0
        else:
            if trade.offset == Offset.OPEN:
                self.short_td += trade.volume
            elif trade.offset == Offset.CLOSETODAY:
                self.long_td -= trade.volume
            elif trade.offset == Offset.CLOSEYESTERDAY:
                self.long_yd -= trade.volume
            elif trade.offset == Offset.CLOSE:
                if trade.exchange in {Exchange.SHFE, Exchange.INE}:
                    self.long_yd -= trade.volume
                else:
                    self.long_td -= trade.volume

                    if self.long_td < 0:
                        self.long_yd += self.long_td
                        self.long_td = 0

        self.long_pos = self.long_td + self.long_yd
        self.short_pos = self.short_td + self.short_yd

        # Update frozen volume to ensure no more than total volume
        self.sum_pos_frozen()

    def calculate_frozen(self) -> None:
        """
        Recalculate frozen close volume from active orders and cap it by position.
        """
        self.long_pos_frozen = 0
        self.long_yd_frozen = 0
        self.long_td_frozen = 0

        self.short_pos_frozen = 0
        self.short_yd_frozen = 0
        self.short_td_frozen = 0

        order: OrderData
        for order in self.active_orders.values():
            # Ignore position open orders
            if order.offset == Offset.OPEN:
                continue

            frozen: float = order.volume - order.traded

            if order.direction == Direction.LONG:
                if order.offset == Offset.CLOSETODAY:
                    self.short_td_frozen += frozen
                elif order.offset == Offset.CLOSEYESTERDAY:
                    self.short_yd_frozen += frozen
                elif order.offset == Offset.CLOSE:
                    self.short_td_frozen += frozen

                    if self.short_td_frozen > self.short_td:
                        self.short_yd_frozen += (self.short_td_frozen
                                                 - self.short_td)
                        self.short_td_frozen = self.short_td
            elif order.direction == Direction.SHORT:
                if order.offset == Offset.CLOSETODAY:
                    self.long_td_frozen += frozen
                elif order.offset == Offset.CLOSEYESTERDAY:
                    self.long_yd_frozen += frozen
                elif order.offset == Offset.CLOSE:
                    self.long_td_frozen += frozen

                    if self.long_td_frozen > self.long_td:
                        self.long_yd_frozen += (self.long_td_frozen
                                                - self.long_td)
                        self.long_td_frozen = self.long_td

        self.sum_pos_frozen()

    def sum_pos_frozen(self) -> None:
        """
        Cap frozen volume by the position and sum today with yesterday.
        """
        # Frozen volume should be no more than total volume
        self.long_td_frozen = min(self.long_td_frozen, self.long_td)
        self.long_yd_frozen = min(self.long_yd_frozen, self.long_yd)

        self.short_td_frozen = min(self.short_td_frozen, self.short_td)
        self.short_yd_frozen = min(self.short_yd_frozen, self.short_yd)

        self.long_pos_frozen = self.long_td_frozen + self.long_yd_frozen
        self.short_pos_frozen = self.short_td_frozen + self.short_yd_frozen

    def convert_order_request_shfe(self, req: OrderRequest) -> list[OrderRequest]:
        """
        Split an SHFE or INE close into close-today and close-yesterday orders.
        """
        if req.offset == Offset.OPEN:
            return [req]

        if req.direction == Direction.LONG:
            pos_available: float = self.short_pos - self.short_pos_frozen
            td_available: float = self.short_td - self.short_td_frozen
        else:
            pos_available = self.long_pos - self.long_pos_frozen
            td_available = self.long_td - self.long_td_frozen

        if req.volume > pos_available:
            return []
        elif req.volume <= td_available:
            req_td: OrderRequest = copy(req)
            req_td.offset = Offset.CLOSETODAY
            return [req_td]
        else:
            req_list: list[OrderRequest] = []

            if td_available > 0:
                req_td = copy(req)
                req_td.offset = Offset.CLOSETODAY
                req_td.volume = td_available
                req_list.append(req_td)

            req_yd: OrderRequest = copy(req)
            req_yd.offset = Offset.CLOSEYESTERDAY
            req_yd.volume = req.volume - td_available
            req_list.append(req_yd)

            return req_list

    def convert_order_request_lock(self, req: OrderRequest) -> list[OrderRequest]:
        """
        Open to lock today volume outside SHFE and INE; otherwise close yesterday volume before opening.
        """
        if req.direction == Direction.LONG:
            td_volume: float = self.short_td
            yd_available: float = self.short_yd - self.short_yd_frozen
        else:
            td_volume = self.long_td
            yd_available = self.long_yd - self.long_yd_frozen

        close_yd_exchanges: set[Exchange] = {Exchange.SHFE, Exchange.INE}

        # If there is td_volume, we can only lock position
        if td_volume and self.exchange not in close_yd_exchanges:
            req_open: OrderRequest = copy(req)
            req_open.offset = Offset.OPEN
            return [req_open]
        # If no td_volume, we close opposite yd position first
        # then open new position
        else:
            close_volume: float = min(req.volume, yd_available)
            open_volume: float = max(0, req.volume - yd_available)
            req_list: list[OrderRequest] = []

            if yd_available:
                req_yd: OrderRequest = copy(req)
                if self.exchange in close_yd_exchanges:
                    req_yd.offset = Offset.CLOSEYESTERDAY
                else:
                    req_yd.offset = Offset.CLOSE
                req_yd.volume = close_volume
                req_list.append(req_yd)

            if open_volume:
                req_open = copy(req)
                req_open.offset = Offset.OPEN
                req_open.volume = open_volume
                req_list.append(req_open)

            return req_list

    def convert_order_request_net(self, req: OrderRequest) -> list[OrderRequest]:
        """
        Close the available position first and open any remainder, splitting SHFE and INE by today and yesterday.
        """
        if req.direction == Direction.LONG:
            pos_available: float = self.short_pos - self.short_pos_frozen
            td_available: float = self.short_td - self.short_td_frozen
            yd_available: float = self.short_yd - self.short_yd_frozen
        else:
            pos_available = self.long_pos - self.long_pos_frozen
            td_available = self.long_td - self.long_td_frozen
            yd_available = self.long_yd - self.long_yd_frozen

        # Split close order to close today/yesterday for SHFE/INE exchange
        if req.exchange in {Exchange.SHFE, Exchange.INE}:
            reqs: list[OrderRequest] = []
            volume_left: float = req.volume

            if td_available:
                td_volume: float = min(td_available, volume_left)
                volume_left -= td_volume

                td_req: OrderRequest = copy(req)
                td_req.offset = Offset.CLOSETODAY
                td_req.volume = td_volume
                reqs.append(td_req)

            if volume_left and yd_available:
                yd_volume: float = min(yd_available, volume_left)
                volume_left -= yd_volume

                yd_req: OrderRequest = copy(req)
                yd_req.offset = Offset.CLOSEYESTERDAY
                yd_req.volume = yd_volume
                reqs.append(yd_req)

            if volume_left > 0:
                open_volume: float = volume_left

                open_req: OrderRequest = copy(req)
                open_req.offset = Offset.OPEN
                open_req.volume = open_volume
                reqs.append(open_req)

            return reqs
        # Just use close for other exchanges
        else:
            reqs = []
            volume_left = req.volume

            if pos_available:
                close_volume: float = min(pos_available, volume_left)
                volume_left -= pos_available

                close_req: OrderRequest = copy(req)
                close_req.offset = Offset.CLOSE
                close_req.volume = close_volume
                reqs.append(close_req)

            if volume_left > 0:
                open_volume = volume_left

                open_req = copy(req)
                open_req.offset = Offset.OPEN
                open_req.volume = open_volume
                reqs.append(open_req)

            return reqs


class OffsetConverter:
    """
    Convert order offsets from cached long-short position holdings.
    """

    def __init__(self, oms_engine: "OmsEngine") -> None:
        """
        Store the contract lookup and an empty map of position holdings.
        """
        self.holdings: dict[str, PositionHolding] = {}

        self.get_contract: Callable[[str], ContractData | None] = oms_engine.get_contract

    def update_position(self, position: PositionData) -> None:
        """
        Update the holding from a position when offset conversion is required.
        """
        if not self.is_convert_required(position.vt_symbol):
            return

        holding: PositionHolding | None = self.get_position_holding(position.vt_symbol)
        if holding:
            holding.update_position(position)

    def update_trade(self, trade: TradeData) -> None:
        """
        Update the holding from a trade when offset conversion is required.
        """
        if not self.is_convert_required(trade.vt_symbol):
            return

        holding: PositionHolding | None = self.get_position_holding(trade.vt_symbol)
        if holding:
            holding.update_trade(trade)

    def update_order(self, order: OrderData) -> None:
        """
        Update the holding from an order when offset conversion is required.
        """
        if not self.is_convert_required(order.vt_symbol):
            return

        holding: PositionHolding | None = self.get_position_holding(order.vt_symbol)
        if holding:
            holding.update_order(order)

    def update_order_request(self, req: OrderRequest, vt_orderid: str) -> None:
        """
        Update the holding from an order request when offset conversion is required.
        """
        if not self.is_convert_required(req.vt_symbol):
            return

        holding: PositionHolding | None = self.get_position_holding(req.vt_symbol)
        if holding:
            holding.update_order_request(req, vt_orderid)

    def get_position_holding(self, vt_symbol: str) -> PositionHolding | None:
        """
        Return the holding for vt_symbol, creating it when the contract exists.
        """
        holding: PositionHolding | None = self.holdings.get(vt_symbol, None)

        if not holding:
            contract: ContractData | None = self.get_contract(vt_symbol)
            if contract:
                holding = PositionHolding(contract)
                self.holdings[vt_symbol] = holding

        return holding

    def convert_order_request(
        self,
        req: OrderRequest,
        lock: bool,
        net: bool = False
    ) -> list[OrderRequest]:
        """
        Convert the order for lock, net, or SHFE close-today mode.
        """
        if not self.is_convert_required(req.vt_symbol):
            return [req]

        holding: PositionHolding | None = self.get_position_holding(req.vt_symbol)

        if not holding:
            return [req]
        elif lock:
            return holding.convert_order_request_lock(req)
        elif net:
            return holding.convert_order_request_net(req)
        elif req.exchange in {Exchange.SHFE, Exchange.INE}:
            return holding.convert_order_request_shfe(req)
        else:
            return [req]

    def is_convert_required(self, vt_symbol: str) -> bool:
        """
        Check if the contract needs offset convert.
        """
        contract: ContractData | None = self.get_contract(vt_symbol)

        # Only contracts with long-short position mode requires convert
        if not contract:
            return False
        elif contract.net_position:
            return False
        else:
            return True
