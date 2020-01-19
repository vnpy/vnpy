""""""
from copy import copy

from vnpy.trader.engine import MainEngine
from vnpy.trader.object import (
    ContractData,
    OrderData,
    TradeData,
    PositionData,
    OrderRequest
)
from vnpy.trader.constant import (Direction, Offset, Exchange)


class OffsetConverter:
    """
    仓位转换
    """

    def __init__(self, main_engine: MainEngine):
        """"""
        self.main_engine = main_engine
        self.holdings = {}

    def update_position(self, position: PositionData):
        """"""
        if not self.is_convert_required(position.vt_symbol):
            return

        holding = self.get_position_holding(position.vt_symbol, position.gateway_name)
        holding.update_position(position)

    def update_trade(self, trade: TradeData):
        """"""
        if not self.is_convert_required(trade.vt_symbol):
            return

        holding = self.get_position_holding(trade.vt_symbol, trade.gateway_name)
        holding.update_trade(trade)

    def update_order(self, order: OrderData):
        """"""
        if not self.is_convert_required(order.vt_symbol):
            return

        holding = self.get_position_holding(order.vt_symbol, order.gateway_name)
        holding.update_order(order)

    def update_order_request(self, req: OrderRequest, vt_orderid: str, gateway_name: str = ''):
        """"""
        if not self.is_convert_required(req.vt_symbol):
            return

        holding = self.get_position_holding(req.vt_symbol, gateway_name)
        holding.update_order_request(req, vt_orderid)

    def get_position_holding(self, vt_symbol: str, gateway_name: str = ''):
        """获取持仓信息"""
        k = f'{gateway_name}.{vt_symbol}'
        holding = self.holdings.get(k, None)
        if not holding:
            contract = self.main_engine.get_contract(vt_symbol)
            holding = PositionHolding(contract)
            self.holdings[k] = holding
        return holding

    def convert_order_request(self, req: OrderRequest, lock: bool, gateway_name: str = ''):
        """"""
        if not self.is_convert_required(req.vt_symbol):
            return [req]

        holding = self.get_position_holding(req.vt_symbol, gateway_name)

        if lock:
            return holding.convert_order_request_lock(req)
        elif req.exchange in [Exchange.SHFE, Exchange.INE]:
            return holding.convert_order_request_shfe(req)
        else:
            return [req]

    def is_convert_required(self, vt_symbol: str):
        """
        Check if the contract needs offset convert.
        """
        contract = self.main_engine.get_contract(vt_symbol)

        # Only contracts with long-short position mode requires convert
        if not contract:
            return False
        elif contract.net_position:
            return False
        else:
            return True


class PositionHolding:
    """"""

    def __init__(self, contract: ContractData):
        """"""
        self.vt_symbol = contract.vt_symbol
        self.exchange = contract.exchange

        self.active_orders = {}

        self.long_pos = 0
        self.long_yd = 0
        self.long_td = 0

        self.short_pos = 0
        self.short_yd = 0
        self.short_td = 0

        self.long_pos_frozen = 0
        self.long_yd_frozen = 0
        self.long_td_frozen = 0

        self.short_pos_frozen = 0
        self.short_yd_frozen = 0
        self.short_td_frozen = 0

    def update_position(self, position: PositionData):
        """"""
        if position.direction == Direction.LONG:
            self.long_pos = position.volume
            self.long_yd = position.yd_volume
            self.long_td = self.long_pos - self.long_yd
        else:
            self.short_pos = position.volume
            self.short_yd = position.yd_volume
            self.short_td = self.short_pos - self.short_yd

    def update_order(self, order: OrderData):
        """"""
        if order.is_active():
            self.active_orders[order.vt_orderid] = order
        else:
            if order.vt_orderid in self.active_orders:
                self.active_orders.pop(order.vt_orderid)

        self.calculate_frozen()

    def update_order_request(self, req: OrderRequest, vt_orderid: str):
        """"""
        gateway_name, orderid = vt_orderid.split(".")

        order = req.create_order_data(orderid, gateway_name)
        self.update_order(order)

    def update_trade(self, trade: TradeData):
        """"""
        if trade.direction == Direction.LONG:
            if trade.offset == Offset.OPEN:
                self.long_td += trade.volume
            elif trade.offset == Offset.CLOSETODAY:
                self.short_td -= trade.volume
            elif trade.offset == Offset.CLOSEYESTERDAY:
                self.short_yd -= trade.volume
            elif trade.offset == Offset.CLOSE:
                if trade.exchange in [Exchange.SHFE, Exchange.INE]:
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
                if trade.exchange in [Exchange.SHFE, Exchange.INE]:
                    self.long_yd -= trade.volume
                else:
                    self.long_td -= trade.volume

                    if self.long_td < 0:
                        self.long_yd += self.long_td
                        self.long_td = 0

        self.long_pos = self.long_td + self.long_yd
        self.short_pos = self.short_td + self.short_yd

    def calculate_frozen(self):
        """"""
        self.long_pos_frozen = 0
        self.long_yd_frozen = 0
        self.long_td_frozen = 0

        self.short_pos_frozen = 0
        self.short_yd_frozen = 0
        self.short_td_frozen = 0

        for order in self.active_orders.values():
            # Ignore position open orders
            if order.offset == Offset.OPEN:
                continue

            frozen = order.volume - order.traded

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

            self.long_pos_frozen = self.long_td_frozen + self.long_yd_frozen
            self.short_pos_frozen = self.short_td_frozen + self.short_yd_frozen

    def convert_order_request_shfe(self, req: OrderRequest):
        """"""
        if req.offset == Offset.OPEN:
            return [req]

        if req.direction == Direction.LONG:
            pos_available = self.short_pos - self.short_pos_frozen
            td_available = self.short_td - self.short_td_frozen
        else:
            pos_available = self.long_pos - self.long_pos_frozen
            td_available = self.long_td - self.long_td_frozen

        if req.volume > pos_available:
            return []
        elif req.volume <= td_available:
            req_td = copy(req)
            req_td.offset = Offset.CLOSETODAY
            return [req_td]
        else:
            req_list = []

            if td_available > 0:
                req_td = copy(req)
                req_td.offset = Offset.CLOSETODAY
                req_td.volume = td_available
                req_list.append(req_td)

            req_yd = copy(req)
            req_yd.offset = Offset.CLOSEYESTERDAY
            req_yd.volume = req.volume - td_available
            req_list.append(req_yd)

            return req_list

    def convert_order_request_lock(self, req: OrderRequest):
        """"""
        if req.direction == Direction.LONG:
            td_volume = self.short_td
            yd_available = self.short_yd - self.short_yd_frozen
        else:
            td_volume = self.long_td
            yd_available = self.long_yd - self.long_yd_frozen

        # If there is td_volume, we can only lock position
        if td_volume:
            req_open = copy(req)
            req_open.offset = Offset.OPEN
            return [req_open]
        # If no td_volume, we close opposite yd position first
        # then open new position
        else:
            close_volume = min(req.volume, yd_available)
            open_volume = max(0, req.volume - yd_available)
            req_list = []

            if yd_available:
                req_yd = copy(req)
                if self.exchange in [Exchange.SHFE, Exchange.INE]:
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

    def to_str(self):
        return f'Long:{self.long_pos},yd:{self.long_yd},td:{self.long_td}; Short:{self.short_pos},yd:{self.short_yd},td:{self.short_yd}'
