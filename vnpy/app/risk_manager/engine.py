# encoding: UTF-8

"""
本文件中实现了风控引擎，用于提供一系列常用的风控功能：
1. 委托流控（单位时间内最大允许发出的委托数量）
2. 总成交限制（每日总成交数量限制）
3. 单笔委托的委托数量控制
"""
import platform
from vnpy.trader.object import LogData, OrderRequest
from vnpy.event import Event, EventEngine, EVENT_TIMER
from vnpy.trader.engine import BaseEngine, MainEngine
from vnpy.trader.event import EVENT_TRADE, EVENT_ORDER, EVENT_LOG
from vnpy.trader.constant import Status
from vnpy.trader.utility import load_json, save_json


class RmEngine(BaseEngine):
    """风控引擎"""
    setting_filename = "risk_manager_setting.json"
    
    def __init__(self, main_engine: MainEngine, event_engine: EventEngine):
        """"""
        self.main_engine = main_engine
        self.event_engine = event_engine
        main_engine.rmEngine = self

        self.active = False
        self.order_flow_count = 0    # 单位时间内委托计数
        self.order_flow_limit = 50     # 委托限制
        self.order_flow_clear = 1     # 计数清空时间（秒）
        self.order_flow_timer = 0    # 计数清空时间计时
        self.order_size_limit = 100    # 单笔委托最大限制
        self.trade_count = 0        # 当日成交合约数量统计
        self.trade_limit = 1000         # 当日成交合约数量限制
        self.order_cancel_limit = 10   # 撤单总次数限制
        self.order_cancel_count = {}           # 单一合约对应撤单次数的字典
        self.active_order_limit = 20  # 活动合约最大限制
        
        self.load_setting()
        self.registerEvent()
  
    def load_setting(self):
        """"""
        setting = load_json(self.setting_filename)

        self.active = setting["active"]
        self.order_flow_limit = setting["order_flow_limit"]
        self.order_flow_clear = setting["order_flow_clear"]
        self.order_size_limit = setting["order_size_limit"]
        self.trade_limit = setting["trade_limit"]
        self.active_order_limit = setting["active_order_limit"]
        self.order_cancel_limit = setting["order_cancel_limit"]            
   
    def save_setting(self):
        """"""
        setting = {
            "active": self.active,
            "order_flow_limit": self.order_flow_limit,
            "order_flow_clear": self.order_flow_clear,
            "order_size_limit": self.order_size_limit,
            "trade_limit": self.trade_limit,
            "active_order_limit": self.active_order_limit,
            "order_cancel_limit": self.order_cancel_limit,
        }

        save_json(self.setting_filename, setting)
   
    def register_event(self):
        """"""
        self.event_engine.register(EVENT_TRADE, self.update_trade)
        self.event_engine.register(EVENT_TIMER, self.update_timer)
        self.event_engine.register(EVENT_ORDER, self.update_order)
            
    def update_order(self, event):
        """"""
        order = event.dict_["data"]
        if order.status != Status.CANCELLED:
            return
        
        if order.symbol not in self.order_cancel_count:
            self.order_cancel_count[order.symbol] = 1
        else:
            self.order_cancel_count[order.symbol] += 1
   
    def update_trade(self, event):
        """"""
        trade = event.dict_["data"]
        self.trade_count += trade.volume
    
    def update_timer(self, event):
        """"""
        self.order_flow_timer += 1

        if self.order_flow_timer >= self.order_flow_clear:
            self.order_flow_count = 0
            self.order_flow_timer = 0
   
    def write_risk_log(self, content):
        """"""
        if platform.uname() == "Windows":
            import winsound
            winsound.PlaySound("SystemHand", winsound.SND_ASYNC)

        log = LogData()
        log.log_content = content
        log.gateway_name = self.name
        event = Event(type_=EVENT_LOG)
        event.dict_["data"] = log
        self.event_engine.put(event)
   
    def checkRisk(self, req: OrderRequest, gateway_name):
        """"""
        if not self.active:
            return True

        # 检查委托数量
        if req.volume <= 0:
            self.write_risk_log(f"委托数量必须大于0")
            return False
        
        if req.volume > self.order_size_limit:
            self.write_risk_log(f"单笔委托数量{req.volume}，超过限制{self.order_size_limit}")
            return False

        # 检查成交合约量
        if self.trade_count >= self.trade_limit:
            self.write_risk_log(f"今日总成交合约数量{self.trade_count}，超过限制{self.trade_limit}")
            return False

        # 检查流控
        if self.order_flow_count >= self.order_flow_limit:
            self.write_risk_log(f"委托流数量{self.order_flow_count}，超过限制每{self.order_flow_clear}秒{self.order_flow_limit}")
            return False

        # 检查总活动合约
        active_order_count = len(self.main_engine.get_all_active_orders())
        if active_order_count >= self.active_order_limit:
            self.write_risk_log(f"当前活动委托数量{active_order_count}，超过限制{self.active_order_limit}")
            return False

        # 检查撤单次数
        if req.symbol in self.order_cancel_count and self.order_cancel_count[req.symbol] >= self.order_cancel_limit:
            self.write_risk_log(f"当日{req.symbol}撤单次数{self.order_cancel_count[req.symbol]}，超过限制{self.order_cancel_limit}")
            return False

        # 对于通过风控的委托，增加流控计数
        self.order_flow_count += 1

        return True
    
    def clear_order_flow_count(self):
        """"""
        self.order_flow_count = 0
        self.write_risk_log(f"清空流控计数")
    
    def clear_trade_count(self):
        """"""
        self.trade_count = 0
        self.write_risk_log(f"清空总成交计数")
   
    def set_order_flow_limit(self, n):
        """"""
        self.order_flow_limit = n
   
    def set_order_flow_clear(self, n):
        """"""
        self.order_flow_clear = n
    
    def set_order_size_limit(self, n):
        """"""
        self.order_size_limit = n
   
    def set_trade_limit(self, n):
        """"""
        self.trade_limit = n
   
    def set_active_order_limit(self, n):
        """"""
        self.active_order_limit = n
   
    def set_order_cancel_limit(self, n):
        """"""
        self.order_cancel_limit = n
    
    def switch_engine_status(self):
        """"""
        self.active = not self.active

        if self.active:
            self.write_risk_log(f"风险管理功能启动")
        else:
            self.write_risk_log(f"风险管理功能停止")
                
    def stop(self):
        """"""
        self.save_setting()
        
