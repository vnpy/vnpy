""""""

from copy import copy
from collections import defaultdict
from datetime import datetime
from vnpy.trader.constant import Offset
from vnpy.trader.object import OrderRequest, LogData
from vnpy.event import Event, EventEngine, EVENT_TIMER
from vnpy.trader.engine import BaseEngine, MainEngine
from vnpy.trader.event import EVENT_TRADE, EVENT_ORDER, EVENT_LOG, EVENT_ACCOUNT
from vnpy.trader.constant import Status
from vnpy.trader.utility import load_json, save_json

APP_NAME = "RiskManager"


class RiskManagerEngine(BaseEngine):
    """"""
    setting_filename = "risk_manager_setting.json"

    def __init__(self, main_engine: MainEngine, event_engine: EventEngine):
        """"""
        super().__init__(main_engine, event_engine, APP_NAME)

        self.active = False

        self.order_flow_count = 0
        self.order_flow_limit = 500

        self.order_flow_clear = 1
        self.order_flow_timer = 0

        self.order_size_limit = 1000

        self.trade_count = 0
        self.trade_limit = 10000

        self.order_cancel_limit = 5000
        self.order_cancel_counts = defaultdict(int)

        self.active_order_limit = 500

        # 总仓位相关(0~100+)
        self.percent_limit = 100  # 仓位比例限制
        self.last_over_time = None  # 启动风控后，最后一次超过仓位限制的时间

        self.account_dict = {}  # 资金账号信息
        self.gateway_dict = {}  # 记录gateway对应的仓位比例
        self.currency_list = []  # 资金账号风控管理得币种

        self.load_setting()
        self.register_event()
        self.patch_send_order()

    def patch_send_order(self):
        """
        Patch send order function of MainEngine.
        """
        self._send_order = self.main_engine.send_order
        self.main_engine.send_order = self.send_order

    def send_order(self, req: OrderRequest, gateway_name: str):
        """"""
        result = self.check_risk(req, gateway_name)
        if not result:
            return ""

        return self._send_order(req, gateway_name)

    def update_setting(self, setting: dict):
        """"""
        self.active = setting["active"]
        self.order_flow_limit = setting["order_flow_limit"]
        self.order_flow_clear = setting["order_flow_clear"]
        self.order_size_limit = setting["order_size_limit"]
        self.trade_limit = setting["trade_limit"]
        self.active_order_limit = setting["active_order_limit"]
        self.order_cancel_limit = setting["order_cancel_limit"]
        self.percent_limit = setting.get('percent_limit', 100)
        if self.active:
            self.write_log("交易风控功能启动")
        else:
            self.write_log("交易风控功能停止")

    def get_setting(self):
        """"""
        setting = {
            "active": self.active,
            "order_flow_limit": self.order_flow_limit,
            "order_flow_clear": self.order_flow_clear,
            "order_size_limit": self.order_size_limit,
            "trade_limit": self.trade_limit,
            "active_order_limit": self.active_order_limit,
            "order_cancel_limit": self.order_cancel_limit,
            "percent_limit": self.percent_limit
        }
        return setting

    def load_setting(self):
        """"""
        setting = load_json(self.setting_filename)
        if not setting:
            return

        self.update_setting(setting)

    def save_setting(self):
        """"""
        setting = self.get_setting()
        save_json(self.setting_filename, setting)

    def register_event(self):
        """"""
        self.event_engine.register(EVENT_TRADE, self.process_trade_event)
        self.event_engine.register(EVENT_TIMER, self.process_timer_event)
        self.event_engine.register(EVENT_ORDER, self.process_order_event)
        self.event_engine.register(EVENT_ACCOUNT, self.process_account_event)

    def process_order_event(self, event: Event):
        """"""
        order = event.data
        if order.status != Status.CANCELLED:
            return
        self.order_cancel_counts[order.symbol] += 1

    def process_trade_event(self, event: Event):
        """"""
        trade = event.data
        self.trade_count += trade.volume

    def process_timer_event(self, event: Event):
        """"""
        self.order_flow_timer += 1

        if self.order_flow_timer >= self.order_flow_clear:
            self.order_flow_count = 0
            self.order_flow_timer = 0

    def process_account_event(self, event):
        """更新账号资金
        add by Incense
        """
        account = event.data

        # 如果有币种过滤，就进行过滤动作
        if len(self.currency_list) > 0:
            if account.currency not in self.currency_list:
                return

        # 净值为0得不做处理
        if account.balance == 0:
            return

        # 保存在dict中
        k = u'{}_{}'.format(account.vt_accountid, account.currency)
        self.account_dict.update({k: copy(account)})

        # 计算当前资金仓位
        if account.balance == 0:
            account_percent = 0
        else:
            account_percent = round((account.balance - account.available) * 100 / account.balance, 2)

        if not self.active:
            return

        # 更新gateway对应的当前资金仓位
        self.gateway_dict.update({account.gateway_name: account_percent})

        # 判断资金仓位超出
        if account_percent > self.percent_limit:
            if self.last_over_time is None or (
                    datetime.now() - self.last_over_time).total_seconds() > 60 * 10:
                self.last_over_time = datetime.now()
                msg = u'账号:{} 今净值:{},保证金占用{} 超过设定:{}' \
                    .format(account.vt_accountid,
                            account.balance, account_percent, self.percent_limit)
                self.write_log(msg)

    def get_account(self, vt_accountid: str = ""):
        """获取账号的当前净值，可用资金，账号当前仓位百分比，允许的最大仓位百分比"""
        if vt_accountid:
            account = self.account_dict.get(vt_accountid, None)
            if account:
                return account.balance, \
                       account.available, \
                       round(account.frozen * 100 / (account.balance + 0.01), 2), \
                       self.percent_limit
        if len(self.account_dict.values()) > 0:
            account = self.account_dict.values()[0]
            return account.balance, \
                   account.available, \
                   round(account.frozen * 100 / (account.balance + 0.01), 2), \
                   self.percent_limit
        else:
            return 0, 0, 0, 0

    def write_log(self, msg: str):
        """"""
        log = LogData(msg=msg, gateway_name="RiskManager")
        event = Event(type=EVENT_LOG, data=log)
        self.event_engine.put(event)

    def check_risk(self, req: OrderRequest, gateway_name: str):
        """"""
        if not self.active:
            return True

        # Check order volume
        if req.volume <= 0:
            self.write_log("委托数量必须大于0")
            return False

        if req.volume > self.order_size_limit:
            self.write_log(
                f"单笔委托数量{req.volume}，超过限制{self.order_size_limit}")
            return False

        # Check trade volume
        if self.trade_count >= self.trade_limit:
            self.write_log(
                f"今日总成交合约数量{self.trade_count}，超过限制{self.trade_limit}")
            return False

        # Check flow count
        if self.order_flow_count >= self.order_flow_limit:
            self.write_log(
                f"委托流数量{self.order_flow_count}，超过限制每{self.order_flow_clear}秒{self.order_flow_limit}次")
            return False

        # Check all active orders
        active_order_count = len(self.main_engine.get_all_active_orders())
        if active_order_count >= self.active_order_limit:
            self.write_log(
                f"当前活动委托次数{active_order_count}，超过限制{self.active_order_limit}")
            return False

        # Check order cancel counts
        if req.symbol in self.order_cancel_counts and self.order_cancel_counts[req.symbol] >= self.order_cancel_limit:
            self.write_log(
                f"当日{req.symbol}撤单次数{self.order_cancel_counts[req.symbol]}，超过限制{self.order_cancel_limit}")
            return False

        # 开仓时，检查是否超过保证金比率
        if req.offset == Offset.OPEN and self.gateway_dict.get(gateway_name, 0) > self.percent_limit:
            self.write_log(f'当前资金仓位{self.gateway_dict[gateway_name]}超过仓位限制:{self.percent_limit}')
            return False

        # Add flow count if pass all checks
        self.order_flow_count += 1
        return True
