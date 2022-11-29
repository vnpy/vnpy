"""
Modified program trading engine with risk manager moudle based on Vnpy original main engine.
Adapt for China Mainland option program trading supervising requirement.
Warning: Only for test, do not use in production environment!!!
"""
from vnpy.event import Event, EventEngine, EVENT_TIMER

from vnpy.trader.object import OrderRequest, CancelRequest
from vnpy.trader.constant import Direction, Status
from vnpy.trader.engine import MainEngine, BaseEngine

SETTINGS = {
    'option_rm.order_threshold': 200,
    'option_rm.cancel_rate_limit': 0.8,
    'option_rm.vol_threshold': 100,
    'option_rm.vol_interest_rate_limit': 3
}

class OptionRiskManagerEngine(BaseEngine):
    def __init__(self, main_engine: MainEngine, event_engine: EventEngine):
        """"""
        super().__init__(main_engine, event_engine, "option_rm")

        self.option_engine = None

        self.log_count = 0
        self.log_interval = 15

        self.order_threshold = SETTINGS.get('option_rm.order_threshold', 2000000)
        self.cancel_rate_limit = SETTINGS.get('option_rm.cancel_rate_limit', 0.8)
        self.vol_threshold = SETTINGS.get('option_rm.vol_threshold', 1000)
        self.vol_interest_rate_limit = SETTINGS.get('option_rm.vol_interest_rate_limit', 3)

        self.cancel_rate = 0.0
        self.vol_interest_rate = 0.0

        print(self.__dict__)

        self.register_event()

    def register_event(self) -> None:
        """"""
        self.event_engine.register(EVENT_TIMER, self.process_timer_event)

    def process_timer_event(self, event):
        """"""
        if self.log_count > self.log_interval:
            traded_vol = self.get_traded_vol()
            order_vol = self.get_all_order_vol()
            canceled_vol = self.get_canceled_order_vol()
            net_pos = self.get_net_pos()
            self.main_engine.write_log(f"当日成交量：{traded_vol}, 当日委托量:{order_vol}, 当日撤单量：{canceled_vol}，净持仓：{net_pos}")
            
            if traded_vol > self.vol_threshold:
                if net_pos:
                    self.vol_interest_rate = traded_vol / abs(self.get_net_pos())
                else:
                    self.vol_interest_rate = 9999
                self.main_engine.write_log(f"当日成交持仓比：{self.vol_interest_rate}")

            if order_vol > self.order_threshold:
                self.cancel_rate = self.get_canceled_order_vol() / order_vol
                self.main_engine.write_log(f"当日撤单比：{self.cancel_rate}")

            self.log_count = 0

        self.log_count += 1

    def get_option_engine(self):
        """"""
        if not self.option_engine:
            self.option_engine = self.main_engine.get_engine('OptionMaster')
        return self.option_engine

    def get_net_pos(self) -> int:
        """"""
        net_pos = 0
        engine = self.get_option_engine()
        for name in engine.get_portfolio_names():
            portfolio = engine.get_portfolio(name)
            net_pos += portfolio.net_pos
        return net_pos

    def get_traded_vol(self) -> int:
        """"""
        return sum(trade.volume for trade in self.main_engine.get_all_trades())

    def get_all_order_vol(self) -> int:
        """"""
        return len(self.main_engine.get_all_orders())

    def get_canceled_order_vol(self) -> int:
        """"""
        cancled_orders = [order for order in self.main_engine.get_all_orders() if order.status == Status.CANCELLED]
        return len(cancled_orders)

    def calculate_vol_interest_rate(self, req: OrderRequest) -> float:
        """
        """
        traded_vol = self.get_traded_vol()
        all_vol = traded_vol + req.volume

        if all_vol <= self.vol_threshold:
            return 0.0

        if req.direction == Direction.LONG:
            end_net_pos = self.get_net_pos() + req.volume
        else:
            end_net_pos = self.get_net_pos() - req.volume

        if end_net_pos:
            return all_vol / abs(end_net_pos)
        else:
            return self.vol_interest_rate_limit + 1

    def is_self_dealing_possible(self, req: OrderRequest) -> bool:
        """"""
        active_orders = self.main_engine.get_all_active_orders(req.vt_symbol)
        for order in active_orders:
            if req.direction == Direction.LONG:
                if order.direction == Direction.SHORT and req.price >= order.price:
                    return True
            else:
                if order.direction == Direction.LONG and req.price <= order.price:
                    return True
        return False

    def is_exceed_vol_interest_rate_limit(self, req: OrderRequest) -> bool:
        """"""
        return self.calculate_vol_interest_rate(req) > self.vol_interest_rate_limit
                
    def is_exceed_cancel_limit(self, req: CancelRequest) -> bool:
        """"""
        all_order_vol = self.get_all_order_vol()
        if all_order_vol > self.order_threshold:
            all_canceled_vol = self.get_canceled_order_vol() + 1    # add current cancel request
            return all_canceled_vol / all_order_vol > self.cancel_rate_limit
        return False 
            

class MainEngineRm(MainEngine):

    def __init__(self, event_engine: EventEngine = None):
        super().__init__(event_engine)
        self.add_engine(OptionRiskManagerEngine)

    def orm_send_check(self, req: OrderRequest) -> bool:
        """"""
        rm_engine = self.get_engine('option_rm')
        if rm_engine.is_self_dealing_possible(req):
            self.write_log(f"ORM拒绝发单：{req.vt_symbol}存在反向活动委托单，可能引发自成交")
            return False
        if rm_engine.is_exceed_vol_interest_rate_limit(req):
            self.write_log(f"ORM拒绝发单：{req.vt_symbol}委托单会导致成交持仓比超限制")
            return False
        return True

    def orm_cancel_check(self, req: CancelRequest) -> bool:
        """"""
        rm_engine = self.get_engine('option_rm')
        if rm_engine.is_exceed_cancel_limit(req):
            self.write_log(f"ORM拒绝撤单：超过最大撤单限制")
            return False
        return True

    def send_order(self, req: OrderRequest, gateway_name: str) -> str:
        """"""
        if self.orm_send_check(req):
            super().send_order(req, gateway_name)

    def cancel_order(self, req: CancelRequest, gateway_name: str) -> None:
        """"""
        if self.orm_cancel_check(req):
            super().cancel_order(req, gateway_name)