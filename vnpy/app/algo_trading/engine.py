
from vnpy.event import EventEngine, Event
from vnpy.trader.engine import BaseEngine, MainEngine
from vnpy.trader.event import (
    EVENT_TICK, EVENT_TIMER, EVENT_ORDER, EVENT_TRADE)
from vnpy.trader.constant import (Direction, Offset, OrderType)
from vnpy.trader.object import (SubscribeRequest, OrderRequest, LogData)
from vnpy.trader.utility import load_json, save_json, round_to

from .template import AlgoTemplate
from .base import (
    EVENT_ALGO_LOG, EVENT_ALGO_PARAMETERS,
    EVENT_ALGO_SETTING, EVENT_ALGO_VARIABLES,
    APP_NAME
)
from .genus import GenusClient


class AlgoEngine(BaseEngine):
    """"""
    setting_filename = "algo_trading_setting.json"

    def __init__(self, main_engine: MainEngine, event_engine: EventEngine):
        """Constructor"""
        super().__init__(main_engine, event_engine, APP_NAME)

        self.algos = {}
        self.symbol_algo_map = {}
        self.orderid_algo_map = {}

        self.algo_templates = {}
        self.algo_settings = {}

        self.load_algo_template()
        self.register_event()

    def init_engine(self):
        """"""
        self.write_log("算法交易引擎启动")
        self.load_algo_setting()

        self.genus_client = GenusClient(self.main_engine, self.event_engine)
        self.genus_client.init()

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

        from .genus import (
            GenusVWAP,
            GenusTWAP,
            GenusPercent,
            GenusPxInline,
            GenusSniper,
            GenusDMA
        )

        self.add_algo_template(GenusVWAP)
        self.add_algo_template(GenusTWAP)
        self.add_algo_template(GenusPercent)
        self.add_algo_template(GenusPxInline)
        self.add_algo_template(GenusSniper)
        self.add_algo_template(GenusDMA)

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
        template_name: str = setting["template_name"]
        if template_name.startswith("Genus"):
            return self.genus_client.start_algo(setting)

        algo_template = self.algo_templates[template_name]

        algo = algo_template.new(self, setting)
        algo.start()

        self.algos[algo.algo_name] = algo
        return algo.algo_name

    def stop_algo(self, algo_name: str):
        """"""
        if algo_name.startswith("Genus"):
            self.genus_client.stop_algo(algo_name)
            return

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
            self.write_log(f'委托下单失败，找不到合约：{vt_symbol}', algo)
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

    def get_tick(self, algo: AlgoTemplate, vt_symbol: str):
        """"""
        tick = self.main_engine.get_tick(vt_symbol)

        if not tick:
            self.write_log(f"查询行情失败，找不到行情：{vt_symbol}", algo)

        return tick

    def get_contract(self, algo: AlgoTemplate, vt_symbol: str):
        """"""
        contract = self.main_engine.get_contract(vt_symbol)

        if not contract:
            self.write_log(f"查询合约失败，找不到合约：{vt_symbol}", algo)

        return contract

    def write_log(self, msg: str, algo: AlgoTemplate = None):
        """"""
        if algo:
            msg = f"{algo.algo_name}：{msg}"

        log = LogData(msg=msg, gateway_name=APP_NAME)
        event = Event(EVENT_ALGO_LOG, data=log)
        self.event_engine.put(event)

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
