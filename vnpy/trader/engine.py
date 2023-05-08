"""
"""
import os
import time
from abc import ABC
import json
from collections import defaultdict
import cachetools.func
import cachetools.keys
from cachetools import cached, TTLCache
import logging
from logging import Logger
import smtplib
from datetime import datetime
from email.message import EmailMessage
from queue import Empty, Queue
from threading import Thread
from typing import Any, Type, Dict, List, Optional, Set, Iterable
import requests
from vnpy import WORK_DIR
from vnpy.event import Event, EventEngine
from .app import BaseApp
from .event import (
    EVENT_TICK,
    EVENT_ORDER,
    EVENT_TRADE,
    EVENT_POSITION,
    EVENT_ACCOUNT,
    EVENT_CONTRACT,
    EVENT_LOG,
    EVENT_QUOTE,
    EVENT_BASKET_COMPONENT,
    EVENT_UNIMPORTANT_TICK,
    EVENT_LOAN_MAX
)
from .gateway import BaseGateway
from .constant import Product, Direction, Status, OrderType
from .object import (
    CancelRequest,
    LogData,
    OrderRequest,
    QuoteData,
    QuoteRequest,
    SubscribeRequest,
    HistoryRequest,
    OrderData,
    BarData,
    TickData,
    TradeData,
    PositionData,
    AccountData,
    ContractData,
    Exchange,
    BasketComponent,
    LoanMaxData
)
from .setting import SETTINGS
from .utility import get_folder_path, TRADER_DIR, round_to

from vnpy.trader.jgetf_moment_profit.jgetf_api_func_def import *

class MainEngine:
    """
    Acts as the core of VN Trader.
    """

    def __init__(self, event_engine: EventEngine = None):
        """"""
        if event_engine:
            self.event_engine: EventEngine = event_engine
        else:
            self.event_engine = EventEngine()
        self.event_engine.start()

        self.gateways: Dict[str, BaseGateway] = {}
        self.engines: Dict[str, BaseEngine] = {}
        self.apps: Dict[str, BaseApp] = {}
        self.exchanges: List[Exchange] = []

        os.chdir(TRADER_DIR)    # Change working directory
        self.init_engines()     # Initialize function engines

    def add_engine(self, engine_class: Any) -> "BaseEngine":
        """
        Add function engine.
        """
        engine = engine_class(self, self.event_engine)
        self.engines[engine.engine_name] = engine
        return engine

    def add_gateway(self, gateway_class: Type[BaseGateway]) -> BaseGateway:
        """
        Add gateway.
        """
        try:
            gateway = gateway_class(self.event_engine)
        except TypeError:
            name = gateway_class.__name__.replace('Gateway', '').upper()
            gateway = gateway_class(self.event_engine, gateway_name=name)
        self.gateways[gateway.gateway_name] = gateway

        # Add gateway supported exchanges into engine
        for exchange in gateway.exchanges:
            if exchange not in self.exchanges:
                self.exchanges.append(exchange)

        return gateway

    def add_app(self, app_class: Type[BaseApp]) -> "BaseEngine":
        """
        Add app.
        """
        app = app_class()
        self.apps[app.app_name] = app

        engine = self.add_engine(app.engine_class)
        return engine

    def init_engines(self) -> None:
        """
        Init all engines.
        """
        self.add_engine(LogEngine)
        self.add_engine(OmsEngine)
        self.add_engine(EmailEngine)

    def write_log(self, msg: str, source: str = "") -> None:
        """
        Put log event with specific message.
        """
        log = LogData(msg=msg, gateway_name=source)
        event = Event(EVENT_LOG, log)
        self.event_engine.put(event)

    def get_gateway(self, gateway_name: str) -> BaseGateway:
        """
        Return gateway object by name.
        """
        gateway = self.gateways.get(gateway_name, None)
        if not gateway:
            self.write_log(f"找不到底层接口：{gateway_name}")
        return gateway

    def get_engine(self, engine_name: str) -> "BaseEngine":
        """
        Return engine object by name.
        """
        engine = self.engines.get(engine_name, None)
        if not engine:
            self.write_log(f"找不到引擎：{engine_name}")
        return engine

    def get_default_setting(self, gateway_name: str) -> Optional[Dict[str, Any]]:
        """
        Get default setting dict of a specific gateway.
        """
        gateway = self.get_gateway(gateway_name)
        if gateway:
            return gateway.get_default_setting()
        return None

    def get_all_gateway_names(self) -> List[str]:
        """
        Get all names of gatewasy added in main engine.
        """
        return list(self.gateways.keys())

    def get_all_apps(self) -> List[BaseApp]:
        """
        Get all app objects.
        """
        return list(self.apps.values())

    def get_all_exchanges(self) -> List[Exchange]:
        """
        Get all exchanges.
        """
        return self.exchanges

    def connect(self, setting: dict, gateway_name: str) -> None:
        """
        Start connection of a specific gateway.
        """
        gateway = self.get_gateway(gateway_name)
        if gateway:
            gateway.connect(setting)

    def subscribe(self, req: SubscribeRequest, gateway_name: str) -> None:
        """
        Subscribe tick data update of a specific gateway.
        """
        gateway = self.get_gateway(gateway_name)
        # 如果是ETF,则监控计算可卖、可申购、可赎回等信息
        contract: ContractData = self.get_contract(req.vt_symbol)
        if not contract:
            print('订阅不存在的标的', req.vt_symbol)
            return
        if contract.product == Product.ETF:
            self.set_basket_forcus(contract)
        if gateway:
            gateway.subscribe(req)
        if req.important:
            self.event_engine.add_important_symbol(req.vt_symbol)

    def subscribe_many(self, req_list: List[SubscribeRequest], gateway_name: str) -> None:
        """
        Subscribe tick data update of a specific gateway.
        """
        gateway = self.get_gateway(gateway_name)
        # 如果是ETF,则监控计算可卖、可申购、可赎回等信息
        for req in req_list:
            contract: ContractData = self.get_contract(req.vt_symbol)
            if not contract:
                print('订阅不存在的标的', req.vt_symbol)
                continue
            if contract.product == Product.ETF:
                self.set_basket_forcus(contract)
            if req.important:
                self.event_engine.add_important_symbol(req.vt_symbol)
        if gateway:
            gateway.subscribe_many(req_list)

    def get_basket_components(self, symbol):
        """
        不带后缀！
        """
        raise NotImplementedError

    def get_position(self, vt_positionid: str) -> Optional[PositionData]:
        """
        Get latest position data by vt_positionid.
        """
        raise NotImplementedError

    def get_basket_position(self, vt_symbol, direction=Direction.LONG):
        """
        持仓转换成篮子后的 量
        """
        raise NotImplementedError

    def check_order_request(self, req: OrderRequest) -> OrderRequest:
        """
        Send new order request to a specific gateway.
        """
        if req.direction in (Direction.BUY_BASKET, Direction.SELL_BASKET):
            return self.send_basket_order(req, gateway_name)
        contract = self.get_contract(req.vt_symbol)
        if contract is None:
            self.write_log(f'合约 {req.vt_symbol} 不存在，无法下单')
            return ""
        if not req.gateway_name:
            req.gateway_name = contract.gateway_name
        req.product = contract.product
        req.price = round_to(req.price, contract.pricetick)
        tick: TickData = self.get_tick(req.vt_symbol)

        if req.direction in [Direction.LoanSell, Direction.PreBookLoanSell]:
            if tick and req.price < tick.bid_price_1:
                req.price = tick.bid_price_1
                self.write_log(f'融卖价低于bid1, 已修正为 {req.price}@{req.vt_symbol}')

        # 最优五档转限价注册制新规
        # 最优五一般是批量下单，尽量不打印日志到队列，影响队列性能
        if req.type == OrderType.BestOrLimit:
            if req.direction in (Direction.LONG, Direction.LoanBuy):
                if tick and req.price == 0:
                    req.price = tick.ask_price_5
                    print(f'最优五限价低于bid1, 已修正为 {req.price}@{req.vt_symbol}')
                elif not tick:
                    # 没有行情，只能用市价
                    req.type = OrderType.MARKET
            elif req.direction in (Direction.SHORT, Direction.LoanSell, Direction.PreBookLoanSell):
                if tick and req.price == 0:
                    req.price = tick.bid_price_5
                    print(f'最优五限价高于ask1, 已修正为 {req.price}@{req.vt_symbol}')
                elif not tick:
                    # 没有行情，只能用市价
                    req.type = OrderType.MARKET
        return req

    def send_order(self, req: OrderRequest, gateway_name: str) -> str:
        """
        Send new order request to a specific gateway.
        """
        req.gateway_name = gateway_name
        req = self.check_order_request(req)
        if not req:
            return ""
        gateway = self.get_gateway(gateway_name)
        if gateway:
            return gateway.send_order(req)
        else:
            return ""
        
    def send_order_many(self, req_list: List[OrderRequest]):
        _checked_disp = defaultdict(list)
        _order_ids = []
        for req in req_list:
            _req = self.check_order_request(req)
            if not _req:
                continue
            _checked_disp[_req.gateway_name].append(_req)

        for gateway_name, _req_list in _checked_disp.items():
            gateway = self.get_gateway(gateway_name)
            if gateway:
                _order_ids.extend(gateway.send_order_many(_req_list))
        return _order_ids


    def send_basket_order(self, req: OrderRequest, gateway_name: str):
        contract = self.get_contract(req.vt_symbol)
        if contract.product != Product.ETF:
            raise ValueError('send_basket_order 只能买卖 ETF 篮子')
        req.product = contract.product
        gateway = self.get_gateway(gateway_name)
        if gateway:
            return gateway.send_basket_order(req)
        else:
            return None, None

    def cancel_order(self, req: CancelRequest, gateway_name: str) -> None:
        """
        Send cancel order request to a specific gateway.
        """
        gateway = self.get_gateway(gateway_name)
        if gateway:
            gateway.cancel_order(req)

    def send_quote(self, req: QuoteRequest, gateway_name: str) -> str:
        """
        Send new quote request to a specific gateway.
        """
        gateway = self.get_gateway(gateway_name)
        if gateway:
            return gateway.send_quote(req)
        else:
            return ""

    def cancel_quote(self, req: CancelRequest, gateway_name: str) -> None:
        """
        Send cancel quote request to a specific gateway.
        """
        gateway = self.get_gateway(gateway_name)
        if gateway:
            gateway.cancel_quote(req)

    def query_history(self, req: HistoryRequest, gateway_name: str) -> Optional[List[BarData]]:
        """
        Query bar history data from a specific gateway.
        """
        gateway = self.get_gateway(gateway_name)
        if gateway:
            return gateway.query_history(req)
        else:
            return None

    def get_account(self, vt_accountid: str) -> Optional[AccountData]:
        """
        根据账户id获取账户信息对象
        """
        raise NotImplementedError

    def get_all_accounts(self) -> List[AccountData]:
        """
        获取所有账户信息对象
        """
        raise NotImplementedError

    def set_basket_forcus(self, vt_symbol):
        raise NotImplementedError

    def get_contract(self, vt_symbol):
        raise NotImplementedError

    def get_tick(self, vt_symbol):
        raise NotImplementedError

    def get_spread(self, spread_name: str):
        raise NotImplementedError

    def get_moment_profit(self, etf_symbol: str):
        """
        获取ETF折、溢价瞬时利润
        折价： 买ETF，赎回成篮子，卖篮子
        溢价： 买篮子，申购成ETF，卖ETF
        :param etf_symbol:
        :return:
        """
        raise NotImplementedError

    def get_loan_max_volume(self, account_uid, vt_symbol):
        """
        获取某个账户某标的的融券额度（预约券）
        :param account_uid: JG.123456.CNY
        :param vt_symbol: 510050.SSE
        :return: int
        """
        raise NotImplementedError

    @staticmethod
    def send_hedging_report(data):
        pass

    def close(self) -> None:
        """
        Make sure every gateway and app is closed properly before
        programme exit.
        """
        # Stop event engine first to prevent new timer event.
        self.event_engine.stop()

        for engine in self.engines.values():
            engine.close()

        for gateway in self.gateways.values():
            gateway.close()


class BaseEngine(ABC):
    """
    Abstract class for implementing an function engine.
    """

    def __init__(
        self,
        main_engine: MainEngine,
        event_engine: EventEngine,
        engine_name: str,
    ):
        """"""
        self.main_engine = main_engine
        self.event_engine = event_engine
        self.engine_name = engine_name

    def close(self):
        """"""
        pass


class LogEngine(BaseEngine):
    """
    Processes log event and output with logging module.
    """

    def __init__(self, main_engine: MainEngine, event_engine: EventEngine):
        """"""
        super(LogEngine, self).__init__(main_engine, event_engine, "log")

        if not SETTINGS["log.active"]:
            return

        self.level: int = SETTINGS["log.level"]

        self.logger: Logger = logging.getLogger("VN Trader")
        self.logger.setLevel(self.level)

        self.formatter = logging.Formatter(
            "%(asctime)s  %(levelname)s: %(message)s"
        )

        self.add_null_handler()

        if SETTINGS["log.console"]:
            self.add_console_handler()

        if SETTINGS["log.file"]:
            self.add_file_handler()

        self.register_event()

    def add_null_handler(self) -> None:
        """
        Add null handler for logger.
        """
        null_handler = logging.NullHandler()
        self.logger.addHandler(null_handler)

    def add_console_handler(self) -> None:
        """
        Add console output of log.
        """
        console_handler = logging.StreamHandler()
        console_handler.setLevel(self.level)
        console_handler.setFormatter(self.formatter)
        self.logger.addHandler(console_handler)

    def add_file_handler(self) -> None:
        """
        Add file output of log.
        """
        today_date = datetime.now().strftime("%Y%m%d")
        filename = f"vt_{today_date}.log"
        log_path = get_folder_path("log")
        file_path = log_path.joinpath(filename)

        file_handler = logging.FileHandler(
            file_path, mode="a", encoding="utf8"
        )
        file_handler.setLevel(self.level)
        file_handler.setFormatter(self.formatter)
        self.logger.addHandler(file_handler)

    def register_event(self) -> None:
        """"""
        self.event_engine.register(EVENT_LOG, self.process_log_event)

    def process_log_event(self, event: Event) -> None:
        """
        Process log event.
        """
        log = event.data
        self.logger.log(log.level, log.msg)


class OmsEngine(BaseEngine):
    """
    Provides order management system function for VN Trader.
    """

    def __init__(self, main_engine: MainEngine, event_engine: EventEngine):
        """"""
        super(OmsEngine, self).__init__(main_engine, event_engine, "oms")

        self.ticks: Dict[str, TickData] = {}
        self.spread: Dict[str, "SpreadData"] = {}

        self.orders: Dict[str, OrderData] = {}
        self.trades: Dict[str, TradeData] = {}
        self.positions: Dict[str, PositionData] = {}
        self.accounts: Dict[str, AccountData] = {}
        self.contracts: Dict[str, ContractData] = {}
        self.baskets: Dict[str, Dict[BasketComponent]] = defaultdict(dict)
        self.basket_forcus: Set[ContractData] = set()                # 订阅的ETF会计算篮子可卖、可申购
        self.quotes: Dict[str, QuoteData] = {}
        self.loan_max: Dict[str, Dict[str, int]] = defaultdict(dict)        # 存储融券剩余额度

        self.active_orders: Dict[str, OrderData] = {}
        self.active_quotes: Dict[str, QuoteData] = {}

        self.add_function()
        self.register_event()
        self.last_report_tm = time.time()

    def add_function(self) -> None:
        """Add query function to main engine."""
        self.main_engine.get_tick = self.get_tick
        self.main_engine.get_order = self.get_order
        self.main_engine.get_trade = self.get_trade
        self.main_engine.get_position = self.get_position
        self.main_engine.get_account = self.get_account
        self.main_engine.get_contract = self.get_contract
        self.main_engine.get_quote = self.get_quote

        self.main_engine.get_all_ticks = self.get_all_ticks
        self.main_engine.get_all_orders = self.get_all_orders
        self.main_engine.get_all_trades = self.get_all_trades
        self.main_engine.get_all_positions = self.get_all_positions
        self.main_engine.get_all_accounts = self.get_all_accounts
        self.main_engine.get_all_contracts = self.get_all_contracts
        self.main_engine.get_all_quotes = self.get_all_quotes
        self.main_engine.get_all_active_orders = self.get_all_active_orders
        self.main_engine.get_all_active_qutoes = self.get_all_active_quotes
        self.main_engine.get_basket_components = self.get_basket_components
        self.main_engine.set_basket_forcus = self.set_basket_forcus
        self.main_engine.get_basket_position = self.get_basket_position
        self.main_engine.get_spread = self.get_spread
        self.main_engine.get_moment_profit = self.get_moment_profit
        self.main_engine.get_loan_max_volume = self.get_loan_max_volume
        self.main_engine.send_hedging_report = self.send_hedging_report

    def register_event(self) -> None:
        """"""
        self.event_engine.register(EVENT_TICK, self.process_tick_event)
        self.event_engine.register(EVENT_UNIMPORTANT_TICK, self.process_tick_event)

        self.event_engine.register(EVENT_ORDER, self.process_order_event)
        self.event_engine.register(EVENT_TRADE, self.process_trade_event)
        self.event_engine.register(EVENT_POSITION, self.process_position_event)
        self.event_engine.register(EVENT_ACCOUNT, self.process_account_event)
        self.event_engine.register(EVENT_CONTRACT, self.process_contract_event)
        self.event_engine.register(EVENT_QUOTE, self.process_quote_event)
        self.event_engine.register(EVENT_BASKET_COMPONENT, self.process_basket_component)
        self.event_engine.register(EVENT_LOAN_MAX, self.process_loan_max_event)

        from vnpy_spreadtrading.base import (
            EVENT_SPREAD_DATA
        )
        self.event_engine.register(EVENT_SPREAD_DATA, self.process_spread_event)

    def process_tick_event(self, event: Event) -> None:
        """"""
        tick: TickData = event.data
        self.ticks[tick.vt_symbol] = tick

    @cachetools.func.ttl_cache(ttl=3)
    def get_moment_profit(self, etf_symbol: str):
        """
        获取ETF折、溢价瞬时利润
        折价： 买ETF，赎回成篮子，卖篮子
        溢价： 买篮子，申购成ETF，卖ETF
        :param etf_symbol:
        :return:
        """

        contract: ContractData = self.get_contract(etf_symbol)

        if not contract:
            return None, None
        if contract.product != Product.ETF:
            return None, None
        components: List[BasketComponent] = self.get_basket_components(etf_symbol)

        headinfo = ETFRedemptionHead()
        headinfo.szETFCode = bytes(contract.symbol, encoding="gb2312")
        if contract.exchange == Exchange.SSE:
            headinfo.nETFExchangeType = MARKET_TYPE.MARKET_TYPE_STOCKSH.value
        else:
            headinfo.nETFExchangeType = MARKET_TYPE.MARKET_TYPE_STOCKSZ.value
        headinfo.dEstimateCashComponent = contract.dEstimateCashComponent
        headinfo.lCreationRedemptionUnit = contract.etf_purchase_redem_min
        headinfo.nRecordnum = len(components)
        codelist = (ETFRedemptionCodeList * len(components))()

        count = 0
        for component in components:

            codelist[count].szSecurityCode = bytes(component.symbol, encoding="gb2312")
            if contract.exchange == Exchange.SSE:
                codelist[count].nMarketType = MARKET_TYPE.MARKET_TYPE_STOCKSH.value
            else:
                codelist[count].nMarketType = MARKET_TYPE.MARKET_TYPE_STOCKSZ.value
            codelist[count].dCreationCashSubstitute = component.cash_substitute
            codelist[count].dRedemptionCashSubstitute = component.redemption_cash_substitute
            codelist[count].nSampleVolume = component.share
            codelist[count].cReplaceFlag = bytes(str(component.substitute_flag), encoding="gb2312")
            tick: TickData = self.get_tick(component.vt_symbol)
            if tick:
                codelist[count].nNowPrice = int(tick.last_price * 10000)
            else:
                codelist[count].nNowPrice = 0
            count += 1

        tick: TickData = self.get_tick(contract.vt_symbol)
        etfbuyprice = tick.bid_price_1
        etfsellprice = tick.ask_price_1

        shbenefit = BenefitInfo()
        shbenefit.dStockBuyBenefit = 0.15
        shbenefit.dStockSellBenefit = 0.15
        shbenefit.dBuyStamps = 0
        shbenefit.dSellStamps = 1
        shbenefit.dETFBuyBenefit = 0.05
        shbenefit.dETFSellBenefit = 0.05

        szbenefit = BenefitInfo()
        szbenefit.dStockBuyBenefit = 0.15
        szbenefit.dStockSellBenefit = 0.15
        szbenefit.dBuyStamps = 0
        szbenefit.dSellStamps = 1
        szbenefit.dETFBuyBenefit = 0.06
        szbenefit.dETFSellBenefit = 0.06

        etfprofit = API_CalETFProfit(headinfo, codelist, headinfo.nRecordnum, etfbuyprice, etfsellprice, szbenefit,
                                     shbenefit)

        return etfprofit.dDiscount, etfprofit.dPremium

    def process_spread_event(self, event: Event) -> None:
        spread: SpreadData = event.data
        self.spread[spread.name] = spread

    def process_order_event(self, event: Event):
        """"""
        order = event.data
        if isinstance(order, Iterable):
            for _order in order:
                self._on_order(_order)
        else:
            self._on_order(order)

    def _on_order(self, order):
        self.orders[order.vt_orderid] = order

        # If order is active, then update data in dict.
        if order.is_active():
            self.active_orders[order.vt_orderid] = order
        # Otherwise, pop inactive order from in dict
        elif order.vt_orderid in self.active_orders:
            self.active_orders.pop(order.vt_orderid)

    def process_trade_event(self, event: Event):
        """"""
        trade = event.data
        if isinstance(trade, Iterable):
            order_list = self._on_trade(trade)
        else:
            order_list = self._on_trade([trade])
        if order_list:
            self.event_engine.put(Event(type=EVENT_ORDER, data=order_list))


    def _on_trade(self, trades) -> List[OrderData]:
        """"""
        order_list = []
        for trade in trades:
            self.trades[trade.vt_tradeid] = trade
            if trade.vt_tradeid in self.trades:
                continue
            old_order = self.orders.get(trade.vt_orderid, None)
            if not old_order:
                continue
            if old_order.vt_symbol != trade.vt_symbol:
                continue
            old_order.traded += trade.volume
            if old_order.traded == old_order.volume:
                old_order.status = Status.ALLTRADED
                order_list.append(old_order)

        return  order_list

    def process_position_event(self, event: Event):
        """"""
        position = event.data
        report_data = []
        if isinstance(position, Iterable):
            for _pos in position:
                pos_report = self._on_position(_pos)
                if pos_report:
                    report_data.append(pos_report)
        else:
            pos_report = self._on_position(position)
            if pos_report:
                report_data.append(pos_report)

        self.send_hedging_report(report_data)


    def _on_position(self, position) -> None:
        """"""
        old_pos = self.get_position(position.vt_positionid)
        if position == old_pos:
            return
        self.positions[position.vt_positionid] = position
        if position.product not in  (Product.BASKET, ):
            self.calculate_basket_sp_able()

        if not SETTINGS["signal.report"]:
            return
        if position.yd_volume == 0 and position.volume == 0:
            return
        tick = self.get_tick(position.vt_symbol)
        data = {
            'position_id': position.vt_positionid,
            'account':
                f'{position.gateway_name}.{position.account_id}.{position.account_type.name}'
                if position.account_id != '' else f'{WORK_DIR}-{position.gateway_name}',
            'symbol': position.vt_symbol,
            'volume': position.volume,
            'ydVolume': position.yd_volume,
            'direction': position.direction.name,
            'avgPrice': position.price,
            'currPrice': tick.last_price if tick else 0,
            'pnl': position.pnl,
            'dt': datetime.now().strftime('%y%m%d %H:%M:%S'),
            'client': WORK_DIR
        }
        return data

    def process_account_event(self, event: Event) -> None:
        """"""
        account: AccountData = event.data
        old_account = self.accounts.get(account.vt_accountid)
        if account == old_account:
            return
        self.accounts[account.vt_accountid] = account

        if not SETTINGS["signal.report"]:
            return
        data = {
            'account_id': account.vt_accountid,
            'account': account.accountid,
            'type': account.acc_type.name,
            'currency': account.currency.name,
            'asset': account.balance,
            'avaliable': account.available,
            'income': account.income,
            'creditQuota': account.credit_quota,
            'creditBuyAvaliable': account.credit_buy_available,
            'creditSellAvaliable': account.credit_sell_available,
            'gateway': account.gateway_name,
            'dt': datetime.now().strftime('%y%m%d %H:%M:%S'),
            'client': WORK_DIR
        }
        self.send_hedging_report({'accountData': [data]})

    def process_contract_event(self, event: Event) -> None:
        """"""
        contract: Union[ContractData, List[ContractData]] = event.data
        if isinstance(contract, ContractData):
            self.contracts[contract.vt_symbol] = contract
        else:
            for _c in contract:
                self.contracts[_c.vt_symbol] = _c

    def process_basket_component(self, event: Event):
        component: Union[BasketComponent, List[BasketComponent]] = event.data
        if isinstance(component, BasketComponent):
            self.baskets[component.basket_name][component.vt_symbol] = component
        else:
            for _c in component:
                self.baskets[_c.basket_name][_c.vt_symbol] = _c

    def process_quote_event(self, event: Event) -> None:
        """"""
        quote: QuoteData = event.data
        self.quotes[quote.vt_quoteid] = quote

        # If quote is active, then update data in dict.
        if quote.is_active():
            self.active_quotes[quote.vt_quoteid] = quote
        # Otherwise, pop inactive quote from in dict
        elif quote.vt_quoteid in self.active_quotes:
            self.active_quotes.pop(quote.vt_quoteid)

    def process_loan_max_event(self, event: Event) -> None:
        loan_data: LoanMaxData = event.data
        self.loan_max[loan_data.account_uid][loan_data.vt_symbol] = loan_data.volume

    def get_tick(self, vt_symbol: str) -> Optional[TickData]:
        """
        Get latest market tick data by vt_symbol.
        """
        return self.ticks.get(vt_symbol, None)

    def get_order(self, vt_orderid: str) -> Optional[OrderData]:
        """
        Get latest order data by vt_orderid.
        """
        return self.orders.get(vt_orderid, None)

    def get_trade(self, vt_tradeid: str) -> Optional[TradeData]:
        """
        Get trade data by vt_tradeid.
        """
        return self.trades.get(vt_tradeid, None)

    def get_position(self, vt_positionid: str) -> Optional[PositionData]:
        """
        Get latest position data by vt_positionid.
        """
        return self.positions.get(vt_positionid, None)

    def get_account(self, vt_accountid: str) -> Optional[AccountData]:
        """
        Get latest account data by vt_accountid.
        """
        return self.accounts.get(vt_accountid, None)

    def get_contract(self, vt_symbol: str) -> Optional[ContractData]:
        """
        Get contract data by vt_symbol.
        """
        return self.contracts.get(vt_symbol, None)

    def get_spread(self, spread_name: str):
        """
        获取价差数据
        """
        return self.spread.get(spread_name, None)

    def get_basket_components(self, basket_name):
        basket = self.baskets.get(basket_name)
        if basket:
            return list(basket.values())
        else:
            return []

    @staticmethod
    def get_positionid(vt_symbol, product: Product, direction: Direction):
        return f"{vt_symbol}.{product.name}.{direction.name}"

    def calculate_basket_sp_able(self):
        """计算篮子可申购、可卖数量"""
        #TODO 针对A股 只计算了LONG

        for contract in self.basket_forcus:
            basket_position = PositionData(
                gateway_name=contract.gateway_name,
                symbol=contract.symbol,
                exchange=contract.exchange,
                product=Product.BASKET,
                direction=Direction.LONG
            )
            first = True
            basket_components = self.get_basket_components(contract.vt_symbol)
            etf_contract = contract
            for comp in basket_components:
                if comp.cash_flag() == 2:
                    continue
                if comp.exchange != etf_contract.exchange:
                    continue
                tick: TickData = self.get_tick(comp.vt_symbol)
                if tick is None or (tick.limit_down == tick.last_price or tick.limit_up == tick.last_price):
                    continue
                pos_id = self.get_positionid(comp.vt_symbol, product=Product.EQUITY, direction=Direction.LONG)
                pos: PositionData = self.get_position(pos_id)
                if pos is None:
                    basket_position.volume = 0
                    basket_position.sell_able = 0
                    basket_position.purchase_able = 0
                    basket_position.yd_volume = 0
                    break
                _volume = pos.volume / comp.share
                _sell_able = pos.sell_able / comp.share
                _purchase_able = pos.purchase_able / comp.share
                _yd_volume = pos.yd_volume / comp.share

                if first:
                    basket_position.valume = _volume
                    basket_position.sell_able = _sell_able
                    basket_position.purchase_able = _purchase_able
                    basket_position.yd_volume = _yd_volume
                else:
                    basket_position.valume = min(_volume, basket_position.valume)
                    basket_position.sell_able = min(_sell_able, basket_position.sell_able)
                    basket_position.purchase_able = min(_purchase_able, basket_position.purchase_able)
                    basket_position.yd_volume = min(_yd_volume, basket_position.yd_volume)

            self.event_engine.put(Event(type=EVENT_POSITION, data=basket_position))

    def set_basket_forcus(self, contract):
        self.basket_forcus.add(contract)

    def get_basket_position(self, vt_symbol, direction=Direction.LONG):
        """
        持仓转换成篮子后的 量
        """
        vt_pos_id = self.get_positionid(vt_symbol=vt_symbol, product=Product.BASKET, direction=direction)
        position = self.get_position(vt_pos_id)
        return position

    def get_quote(self, vt_quoteid: str) -> Optional[QuoteData]:
        """
        Get latest quote data by vt_orderid.
        """
        return self.quotes.get(vt_quoteid, None)

    def get_all_ticks(self) -> List[TickData]:
        """
        Get all tick data.
        """
        return list(self.ticks.values())

    def get_all_orders(self) -> List[OrderData]:
        """
        Get all order data.
        """
        return list(self.orders.values())

    def get_all_trades(self) -> List[TradeData]:
        """
        Get all trade data.
        """
        return list(self.trades.values())

    def get_all_positions(self) -> List[PositionData]:
        """
        Get all position data.
        """
        return list(self.positions.values())

    def get_all_accounts(self) -> List[AccountData]:
        """
        Get all account data.
        """
        return list(self.accounts.values())

    def get_all_contracts(self) -> List[ContractData]:
        """
        Get all contract data.
        """
        return list(self.contracts.values())

    def get_all_quotes(self) -> List[QuoteData]:
        """
        Get all quote data.
        """
        return list(self.quotes.values())

    def get_all_active_orders(self, vt_symbol: str = "") -> List[OrderData]:
        """
        Get all active orders by vt_symbol.

        If vt_symbol is empty, return all active orders.
        """
        if not vt_symbol:
            return list(self.active_orders.values())
        else:
            active_orders = [
                order
                for order in self.active_orders.values()
                if order.vt_symbol == vt_symbol
            ]
            return active_orders

    def get_all_active_quotes(self, vt_symbol: str = "") -> List[QuoteData]:
        """
        Get all active quotes by vt_symbol.

        If vt_symbol is empty, return all active qutoes.
        """
        if not vt_symbol:
            return list(self.active_quotes.values())
        else:
            active_quotes = [
                quote
                for quote in self.active_quotes.values()
                if quote.vt_symbol == vt_symbol
            ]
            return active_quotes

    def get_loan_max_volume(self, account_uid, vt_symbol):
        """
        获取某个账户某标的的融券额度（预约券）
        :param account_uid: JG.CNY.123456
        :param vt_symbol: 510050.SSE
        :return: int
        """
        return self.loan_max.get(account_uid, {}).get(vt_symbol, 0)

    def send_hedging_report(self, data):
        now = time.time()
        if now - self.last_report_tm < 3:
            return
        self.last_report_tm = now
        if not SETTINGS["signal.report"]:
            return

        try:
            requests.post(f'http://{SETTINGS["signal.host"]}/api/signal/hedging_board',
                          data=json.dumps(data), timeout=3,
                          headers={'Api-Token': SETTINGS['signal.token']})
        except Exception as e:
            print(str(e))


class EmailEngine(BaseEngine):
    """
    Provides email sending function for VN Trader.
    """

    def __init__(self, main_engine: MainEngine, event_engine: EventEngine):
        """"""
        super(EmailEngine, self).__init__(main_engine, event_engine, "email")

        self.thread: Thread = Thread(target=self.run)
        self.queue: Queue = Queue()
        self.active: bool = False

        self.main_engine.send_email = self.send_email

    def send_email(self, subject: str, content: str, receiver: str = "") -> None:
        """"""
        # Start email engine when sending first email.
        if not self.active:
            self.start()

        # Use default receiver if not specified.
        if not receiver:
            receiver = SETTINGS["email.receiver"]

        msg = EmailMessage()
        msg["From"] = SETTINGS["email.sender"]
        msg["To"] = receiver
        msg["Subject"] = subject
        msg.set_content(content)

        self.queue.put(msg)

    def run(self) -> None:
        """"""
        while self.active:
            try:
                msg = self.queue.get(block=True, timeout=1)

                with smtplib.SMTP_SSL(
                    SETTINGS["email.server"], SETTINGS["email.port"]
                ) as smtp:
                    smtp.login(
                        SETTINGS["email.username"], SETTINGS["email.password"]
                    )
                    smtp.send_message(msg)
            except Empty:
                pass

    def start(self) -> None:
        """"""
        self.active = True
        self.thread.start()

    def close(self) -> None:
        """"""
        if not self.active:
            return

        self.active = False
        self.thread.join()


if __name__ == '__main__':
    from vnpy_spreadtrading.base import SpreadData