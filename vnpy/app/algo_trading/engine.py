
import os
import sys
from datetime import datetime
from functools import lru_cache
from vnpy.event import EventEngine, Event
from vnpy.trader.engine import BaseEngine, MainEngine
from vnpy.trader.event import (
    EVENT_TICK, EVENT_TIMER, EVENT_ORDER, EVENT_TRADE)
from vnpy.trader.constant import (Direction, Offset, OrderType, Status)
from vnpy.trader.object import (SubscribeRequest, OrderRequest, LogData, CancelRequest)
from vnpy.trader.utility import load_json, save_json, round_to, get_folder_path
from vnpy.trader.util_logger import setup_logger, logging

from .template import AlgoTemplate


APP_NAME = "AlgoTrading"

EVENT_ALGO_LOG = "eAlgoLog"
EVENT_ALGO_SETTING = "eAlgoSetting"
EVENT_ALGO_VARIABLES = "eAlgoVariables"
EVENT_ALGO_PARAMETERS = "eAlgoParameters"


class AlgoEngine(BaseEngine):
    """"""
    setting_filename = "algo_trading_setting.json"

    def __init__(self, main_engine: MainEngine, event_engine: EventEngine):
        """Constructor"""
        super().__init__(main_engine, event_engine, APP_NAME)

        self.algos = {}
        self.symbol_algo_map = {}
        self.orderid_algo_map = {}

        self.algo_vtorderid_order_map = {}  # 记录外部发起的算法交易委托编号，便于通过算法引擎撤单

        self.algo_templates = {}
        self.algo_settings = {}

        self.algo_loggers = {}  # algo_name: logger

        self.load_algo_template()
        self.register_event()

    def init_engine(self):
        """"""
        self.write_log("算法交易引擎启动")
        self.load_algo_setting()

    def load_algo_template(self):
        """"""
        from .algos.twap_algo import TwapAlgo
        from .algos.iceberg_algo import IcebergAlgo
        from .algos.sniper_algo import SniperAlgo
        from .algos.stop_algo import StopAlgo
        from .algos.best_limit_algo import BestLimitAlgo
        from .algos.grid_algo import GridAlgo
        from .algos.dma_algo import DmaAlgo
        from .algos.arbitrage_algo import ArbitrageAlgo

        self.add_algo_template(TwapAlgo)
        self.add_algo_template(IcebergAlgo)
        self.add_algo_template(SniperAlgo)
        self.add_algo_template(StopAlgo)
        self.add_algo_template(BestLimitAlgo)
        self.add_algo_template(GridAlgo)
        self.add_algo_template(DmaAlgo)
        self.add_algo_template(ArbitrageAlgo)

    def add_algo_template(self, template: AlgoTemplate):
        """"""
        self.algo_templates[template.__name__] = template

    def load_algo_setting(self):
        """"""
        self.algo_settings = load_json(self.setting_filename)

        for setting_name, setting in self.algo_settings.items():
            self.put_setting_event(setting_name, setting)

        self.write_log("算法配置载入成功")

    def save_algo_setting(self):
        """"""
        save_json(self.setting_filename, self.algo_settings)

    def register_event(self):
        """"""
        self.event_engine.register(EVENT_TICK, self.process_tick_event)
        self.event_engine.register(EVENT_TIMER, self.process_timer_event)
        self.event_engine.register(EVENT_ORDER, self.process_order_event)
        self.event_engine.register(EVENT_TRADE, self.process_trade_event)

    def process_tick_event(self, event: Event):
        """"""
        tick = event.data

        algos = self.symbol_algo_map.get(tick.vt_symbol, None)
        if algos:
            for algo in algos:
                algo.update_tick(tick)

    def process_timer_event(self, event: Event):
        """"""
        # Generate a list of algos first to avoid dict size change
        algos = list(self.algos.values())

        for algo in algos:
            algo.update_timer()

    def process_trade_event(self, event: Event):
        """"""
        trade = event.data

        algo = self.orderid_algo_map.get(trade.vt_orderid, None)
        if algo:
            algo.update_trade(trade)

    def process_order_event(self, event: Event):
        """"""
        order = event.data

        algo = self.orderid_algo_map.get(order.vt_orderid, None)
        if algo:
            algo.update_order(order)

    def start_algo(self, setting: dict):
        """"""
        template_name = setting["template_name"]
        algo_template = self.algo_templates[template_name]

        algo = algo_template.new(self, setting)
        algo.start()

        self.algos[algo.algo_name] = algo
        return algo.algo_name

    def stop_algo(self, algo_name: str):
        """"""
        algo = self.algos.get(algo_name, None)
        if algo:
            algo.stop()
            self.algos.pop(algo_name)

    def stop_all(self):
        """"""
        for algo_name in list(self.algos.keys()):
            self.stop_algo(algo_name)

    def subscribe(self, algo: AlgoTemplate, vt_symbol: str):
        """"""
        contract = self.main_engine.get_contract(vt_symbol)
        if not contract:
            self.write_log(f'订阅行情失败，找不到合约：{vt_symbol}', algo)
            return

        algos = self.symbol_algo_map.setdefault(vt_symbol, set())

        if not algos:
            req = SubscribeRequest(
                symbol=contract.symbol,
                exchange=contract.exchange
            )
            self.main_engine.subscribe(req, contract.gateway_name)

        algos.add(algo)

    def send_order(
        self,
        algo: AlgoTemplate,
        vt_symbol: str,
        direction: Direction,
        price: float,
        volume: float,
        order_type: OrderType,
        offset: Offset
    ):
        """"""
        contract = self.main_engine.get_contract(vt_symbol)
        if not contract:
            self.write_log(f'委托下单失败，找不到合约：{vt_symbol}', algo_name=algo.algo_name)
            return

        volume = round_to(volume, contract.min_volume)
        if not volume:
            return ""

        req = OrderRequest(
            symbol=contract.symbol,
            exchange=contract.exchange,
            direction=direction,
            type=order_type,
            volume=volume,
            price=price,
            offset=offset
        )
        vt_orderid = self.main_engine.send_order(req, contract.gateway_name)

        self.orderid_algo_map[vt_orderid] = algo
        return vt_orderid

    def cancel_order(self, algo: AlgoTemplate, vt_orderid: str):
        """"""
        order = self.main_engine.get_order(vt_orderid)

        if not order:
            self.write_log(f"委托撤单失败，找不到委托：{vt_orderid}", algo)
            return

        req = order.create_cancel_request()
        self.main_engine.cancel_order(req, order.gateway_name)

    def send_algo_order(self, req: OrderRequest, gateway_name: str):
        """发送算法交易指令"""
        self.write_log(u'创建算法交易,gateway_name:{},strategy_name:{},vt_symbol:{},price:{},volume:{}'
                       .format(gateway_name, req.strategy_name, req.vt_symbol, req.price, req.volume))

        # 创建算法实例，由算法引擎启动
        trade_command = ''
        if req.direction == Direction.LONG and req.offset == Offset.OPEN:
            trade_command = 'Buy'
        elif req.direction == Direction.SHORT and req.offset == Offset.OPEN:
            trade_command = 'Short'
        elif req.direction == Direction.SHORT and req.offset != Offset.OPEN:
            trade_command = 'Sell'
        elif req.direction == Direction.LONG and req.offset != Offset.OPEN:
            trade_command = 'Cover'

        all_custom_contracts = self.main_engine.get_all_custom_contracts()
        contract_setting = all_custom_contracts.get(req.vt_symbol, {})
        algo_setting = {
            'templateName': u'SpreadTrading套利',
            'order_vt_symbol': req.vt_symbol,
            'order_command': trade_command,
            'order_price': req.price,
            'order_volume': req.volume,
            'timer_interval': 60 * 60 * 24,
            'strategy_name': req.strategy_name,
            'gateway_name': gateway_name
        }
        algo_setting.update(contract_setting)

        # 算法引擎
        algo_name = self.start_algo(algo_setting)
        self.write_log(u'send_algo_order(): start_algo {}={}'.format(algo_name, str(algo_setting)))

        # 创建一个Order事件
        order = req.create_order_data(orderid=algo_name, gateway_name=gateway_name)
        order.orderTime = datetime.now().strftime('%H:%M:%S.%f')
        order.status = Status.SUBMITTING

        event1 = Event(type=EVENT_ORDER, data=order)
        self.event_engine.put(event1)

        # 登记在本地的算法委托字典中
        self.algo_vtorderid_order_map.update({order.vt_orderid: order})

        return order.vt_orderid

    def is_algo_order(self, req: CancelRequest, gateway_name: str):
        """是否为外部算法委托单"""
        vt_orderid = '.'.join([req.orderid, gateway_name])
        if vt_orderid in self.algo_vtorderid_order_map:
            return True
        else:
            return False

    def cancel_algo_order(self, req: CancelRequest, gateway_name: str):
        """外部算法单撤单"""
        vt_orderid = '.'.join([req.orderid, gateway_name])
        order = self.algo_vtorderid_order_map.get(vt_orderid, None)
        if not order:
            self.write_error(f'{vt_orderid}不在算法引擎中,撤单失败')
            return False

        algo = self.algos.get(req.orderid, None)
        if not algo:
            self.write_error(f'{req.orderid}算法实例不在算法引擎中,撤单失败')
            return False

        ret = self.stop_algo(req.orderid)
        if ret:
            order.cancelTime = datetime.now().strftime('%H:%M:%S.%f')
            order.status = Status.CANCELLED
            event1 = Event(type=EVENT_ORDER, data=order)
            self.event_engine.put(event1)
            self.write_log(f'算法实例撤单成功:{req.orderid}')
            return True
        else:
            self.write_error(f'算法实例撤单失败:{req.orderid}')
            return False

    def get_tick(self, algo: AlgoTemplate, vt_symbol: str):
        """"""
        tick = self.main_engine.get_tick(vt_symbol)

        if not tick:
            self.write_log(f"查询行情失败，找不到行情：{vt_symbol}", algo_name=algo.algo_name)

        return tick

    def get_price(self, algo: AlgoTemplate, vt_symbol: str):
        tick = self.main_engine.get_tick(vt_symbol)

        if not tick:
            self.write_log(f"查询行情失败，找不到行情：{vt_symbol}", algo_name=algo.algo_name)
            return None

        return tick.last_price

    @lru_cache()
    def get_size(self, vt_symbol: str):
        """查询合约的size"""
        contract = self.main_engine.get_contract(vt_symbol)
        if contract is None:
            self.write_error(f'查询不到{vt_symbol}合约信息')
            return 10
        return contract.size

    @lru_cache()
    def get_margin_rate(self, vt_symbol: str):
        """查询保证金比率"""
        contract = self.main_engine.get_contract(vt_symbol)
        if contract is None:
            self.write_error(f'查询不到{vt_symbol}合约信息')
            return 0.1
        if contract.margin_rate == 0:
            return 0.1
        return contract.margin_rate

    @lru_cache()
    def get_price_tick(self, vt_symbol: str):
        """查询价格最小跳动"""
        contract = self.main_engine.get_contract(vt_symbol)
        if contract is None:
            self.write_error(f'查询不到{vt_symbol}合约信息')
            return 0.1

        return contract.pricetick

    def get_account(self, vt_accountid: str = ""):
        """ 查询账号的资金"""
        # 如果启动风控，则使用风控中的最大仓位
        if self.main_engine.rm_engine:
            return self.main_engine.rm_engine.get_account(vt_accountid)

        if len(vt_accountid) > 0:
            account = self.main_engine.get_account(vt_accountid)
            return account.balance, account.avaliable, round(account.frozen * 100 / (account.balance + 0.01), 2), 100
        else:
            accounts = self.main_engine.get_all_accounts()
            if len(accounts) > 0:
                account = accounts[0]
                return account.balance, account.avaliable, round(account.frozen * 100 / (account.balance + 0.01),
                                                                 2), 100
            else:
                return 0, 0, 0, 0

    def get_contract(self, algo: AlgoTemplate, vt_symbol: str):
        """"""
        contract = self.main_engine.get_contract(vt_symbol)

        if not contract:
            self.write_log(msg=f"查询合约失败，找不到合约：{vt_symbol}", algo_name=algo.algo_name)

        return contract

    def write_log(self, msg: str, algo_name: str = None, level: int = logging.INFO):
        """增强版写日志"""
        if algo_name:
            msg = f"{algo_name}：{msg}"

        log = LogData(msg=msg, gateway_name=APP_NAME, level=level)
        event = Event(EVENT_ALGO_LOG, data=log)
        self.event_engine.put(event)

        # 保存单独的策略日志
        if algo_name:
            algo_logger = self.algo_loggers.get(algo_name, None)
            if not algo_logger:
                log_path = get_folder_path('log')
                log_filename = os.path.abspath(os.path.join(log_path, str(algo_name)))
                print(u'create logger:{}'.format(log_filename))
                self.algo_loggers[algo_name] = setup_logger(
                    file_name=log_filename,
                    name=str(algo_name))
                algo_logger = self.algo_loggers.get(algo_name)
            if algo_logger:
                algo_logger.log(level, msg)

        # 如果日志数据异常，错误和告警，输出至sys.stderr
        if level in [logging.CRITICAL, logging.ERROR, logging.WARNING]:
            print(msg, file=sys.stderr)

    def write_error(self, msg: str, algo_name: str = ''):
        """写入错误日志"""
        self.write_log(msg=msg, algo_name=algo_name, level=logging.ERROR)

    def put_setting_event(self, setting_name: str, setting: dict):
        """"""
        event = Event(EVENT_ALGO_SETTING)
        event.data = {
            "setting_name": setting_name,
            "setting": setting
        }
        self.event_engine.put(event)

    def update_algo_setting(self, setting_name: str, setting: dict):
        """"""
        self.algo_settings[setting_name] = setting

        self.save_algo_setting()

        self.put_setting_event(setting_name, setting)

    def remove_algo_setting(self, setting_name: str):
        """"""
        if setting_name not in self.algo_settings:
            return
        self.algo_settings.pop(setting_name)

        event = Event(EVENT_ALGO_SETTING)
        event.data = {
            "setting_name": setting_name,
            "setting": None
        }
        self.event_engine.put(event)

        self.save_algo_setting()

    def put_parameters_event(self, algo: AlgoTemplate, parameters: dict):
        """"""
        event = Event(EVENT_ALGO_PARAMETERS)
        event.data = {
            "algo_name": algo.algo_name,
            "parameters": parameters
        }
        self.event_engine.put(event)

    def put_variables_event(self, algo: AlgoTemplate, variables: dict):
        """"""
        event = Event(EVENT_ALGO_VARIABLES)
        event.data = {
            "algo_name": algo.algo_name,
            "variables": variables
        }
        self.event_engine.put(event)
