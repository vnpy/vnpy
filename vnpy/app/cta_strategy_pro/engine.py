""""""

import importlib
import csv
import os
import sys
import traceback
from collections import defaultdict
from pathlib import Path
from typing import Any, Callable
from datetime import datetime, timedelta
from collections import OrderedDict
from concurrent.futures import ThreadPoolExecutor
from copy import copy
from functools import lru_cache

from vnpy.event import Event, EventEngine
from vnpy.trader.engine import BaseEngine, MainEngine
from vnpy.trader.object import (
    OrderRequest,
    SubscribeRequest,
    HistoryRequest,
    LogData,
    TickData,
    BarData,
    ContractData
)
from vnpy.trader.event import (
    EVENT_TIMER,
    EVENT_TICK,
    EVENT_BAR,
    EVENT_ORDER,
    EVENT_TRADE,
    EVENT_POSITION,
    EVENT_STRATEGY_POS,
)
from vnpy.trader.constant import (
    Direction,
    OrderType,
    Interval,
    Exchange,
    Offset,
    Status
)
from vnpy.trader.utility import (
    load_json, save_json,
    extract_vt_symbol,
    round_to, get_folder_path,
    get_underlying_symbol,
    append_data)

from vnpy.trader.util_logger import setup_logger, logging
from vnpy.trader.converter import OffsetConverter

from .base import (
    APP_NAME,
    EVENT_CTA_LOG,
    EVENT_CTA_STRATEGY,
    EVENT_CTA_STOPORDER,
    EngineType,
    StopOrder,
    StopOrderStatus,
    STOPORDER_PREFIX,
    MARKET_DAY_ONLY

)
from .template import CtaTemplate
from .cta_position import CtaPosition

STOP_STATUS_MAP = {
    Status.SUBMITTING: StopOrderStatus.WAITING,
    Status.NOTTRADED: StopOrderStatus.WAITING,
    Status.PARTTRADED: StopOrderStatus.TRIGGERED,
    Status.ALLTRADED: StopOrderStatus.TRIGGERED,
    Status.CANCELLED: StopOrderStatus.CANCELLED,
    Status.REJECTED: StopOrderStatus.CANCELLED
}


class CtaEngine(BaseEngine):
    """
    策略引擎【增强版】
    1、策略日志单独输出=》log/strategy_name_yyyy-mm-dd.log
    2、使用免费的tdx源，替代rqdata源
    3、取消初始化数据时，从全局的cta_strategy_data中恢复数据，改为策略自己初始化恢复数据
    4、支持多合约订阅和多合约交易. 扩展的合约在setting中配置，由策略进行订阅
    5、支持先启动策略，后连接gateway
    6、支持指定gateway的交易。主引擎可接入多个gateway
    """

    engine_type = EngineType.LIVE  # live trading engine
    engine_type = EngineType.LIVE  # live trading engine

    # 策略配置文件
    setting_filename = "cta_strategy_pro_setting.json"
    # 引擎配置文件
    engine_filename = "cta_strategy_pro_config.json"

    def __init__(self, main_engine: MainEngine, event_engine: EventEngine):
        """"""
        super(CtaEngine, self).__init__(
            main_engine, event_engine, APP_NAME)

        self.engine_config = {}

        self.strategy_setting = {}  # strategy_name: dict
        self.strategy_data = {}  # strategy_name: dict

        self.classes = {}  # class_name: stategy_class
        self.class_module_map = {}  # class_name: mudule_name
        self.strategies = {}  # strategy_name: strategy

        # Strategy pos dict,key:strategy instance name, value: pos dict
        self.strategy_pos_dict = {}

        self.strategy_loggers = {}  # strategy_name: logger

        # 未能订阅的symbols,支持策略启动时，并未接入gateway
        # gateway_name.vt_symbol: set() of (strategy_name, is_bar)
        self.pending_subcribe_symbol_map = defaultdict(set)

        self.symbol_strategy_map = defaultdict(list)  # vt_symbol: strategy list
        self.bar_strategy_map = defaultdict(list)  # vt_symbol: strategy list
        self.strategy_symbol_map = defaultdict(set)  # strategy_name: vt_symbol set

        self.orderid_strategy_map = {}  # vt_orderid: strategy
        self.strategy_orderid_map = defaultdict(
            set)  # strategy_name: orderid list

        self.stop_order_count = 0  # for generating stop_orderid
        self.stop_orders = {}  # stop_orderid: stop_order

        self.init_executor = ThreadPoolExecutor(max_workers=1)

        self.vt_tradeids = set()  # for filtering duplicate trade

        self.offset_converter = OffsetConverter(self.main_engine)

        self.last_minute = None

    def init_engine(self):
        """
        """
        self.load_strategy_class()
        self.load_strategy_setting()
        self.register_event()
        self.write_log("CTA策略引擎初始化成功")

    def close(self):
        """停止所属有的策略"""
        self.stop_all_strategies()

    def register_event(self):
        """注册事件"""
        self.event_engine.register(EVENT_TIMER, self.process_timer_event)
        self.event_engine.register(EVENT_TICK, self.process_tick_event)
        self.event_engine.register(EVENT_BAR, self.process_bar_event)
        self.event_engine.register(EVENT_ORDER, self.process_order_event)
        self.event_engine.register(EVENT_TRADE, self.process_trade_event)
        self.event_engine.register(EVENT_POSITION, self.process_position_event)

    def register_funcs(self):
        """
        register the funcs to main_engine
        :return:
        """
        self.main_engine.get_strategy_status = self.get_strategy_status

    def process_timer_event(self, event: Event):
        """ 处理定时器事件"""

        # 触发每个策略的定时接口
        for strategy in list(self.strategies.values()):
            strategy.on_timer()

        dt = datetime.now()

        if self.last_minute != dt.minute:
            self.last_minute = dt.minute

            # 主动获取所有策略得持仓信息
            all_strategy_pos = self.get_all_strategy_pos()

            # 推送到事件
            self.put_all_strategy_pos_event(all_strategy_pos)

    def process_tick_event(self, event: Event):
        """处理tick到达事件"""
        tick = event.data

        key = f'{tick.gateway_name}.{tick.vt_symbol}'
        v = self.pending_subcribe_symbol_map.pop(key, None)
        if v:
            # 这里不做tick/bar的判断了，因为基本有tick就有bar
            self.write_log(f'{key} tick已经到达,移除未订阅记录:{v}')

        strategies = self.symbol_strategy_map[tick.vt_symbol]
        if not strategies:
            return

        self.check_stop_order(tick)

        for strategy in strategies:
            if strategy.inited:
                self.call_strategy_func(strategy, strategy.on_tick, tick)

    def process_bar_event(self, event: Event):
        """处理bar到达事件"""
        pass

    def process_order_event(self, event: Event):
        """"""
        order = event.data

        self.offset_converter.update_order(order)

        strategy = self.orderid_strategy_map.get(order.vt_orderid, None)
        if not strategy:
            return

        # Remove vt_orderid if order is no longer active.
        vt_orderids = self.strategy_orderid_map[strategy.strategy_name]
        if order.vt_orderid in vt_orderids and not order.is_active():
            vt_orderids.remove(order.vt_orderid)

        # For server stop order, call strategy on_stop_order function
        if order.type == OrderType.STOP:
            so = StopOrder(
                vt_symbol=order.vt_symbol,
                direction=order.direction,
                offset=order.offset,
                price=order.price,
                volume=order.volume,
                stop_orderid=order.vt_orderid,
                strategy_name=strategy.strategy_name,
                status=STOP_STATUS_MAP[order.status],
                vt_orderids=[order.vt_orderid],
            )
            self.call_strategy_func(strategy, strategy.on_stop_order, so)

        # Call strategy on_order function
        self.call_strategy_func(strategy, strategy.on_order, order)

    def process_trade_event(self, event: Event):
        """"""
        trade = event.data

        # Filter duplicate trade push
        if trade.vt_tradeid in self.vt_tradeids:
            return
        self.vt_tradeids.add(trade.vt_tradeid)

        self.offset_converter.update_trade(trade)

        strategy = self.orderid_strategy_map.get(trade.vt_orderid, None)
        if not strategy:
            return

        # Update strategy pos before calling on_trade method
        # 取消外部干预策略pos，由策略自行完成更新
        # if trade.direction == Direction.LONG:
        #     strategy.pos += trade.volume
        # else:
        #     strategy.pos -= trade.volume
        # 根据策略名称，写入 data\straetgy_name_trade.csv文件
        strategy_name = getattr(strategy, 'name')
        trade_fields = ['time', 'symbol', 'exchange', 'vt_symbol', 'tradeid', 'vt_tradeid', 'orderid', 'vt_orderid',
                        'direction', 'offset', 'price', 'volume', 'idx_price']
        trade_dict = OrderedDict()
        try:
            for k in trade_fields:
                if k == 'time':
                    trade_dict[k] = datetime.now().strftime('%Y-%m-%d') + ' ' + getattr(trade, k, '')
                if k in ['exchange', 'direction', 'offset']:
                    trade_dict[k] = getattr(trade, k).value
                else:
                    trade_dict[k] = getattr(trade, k, '')

            # 添加指数价格
            symbol = trade_dict.get('symbol')
            idx_symbol = get_underlying_symbol(symbol).upper() + '99.' + trade_dict.get('exchange')
            idx_price = self.get_price(idx_symbol)
            if idx_price:
                trade_dict.update({'idx_price': idx_price})
            else:
                trade_dict.update({'idx_price': trade_dict.get('price')})

            if strategy_name is not None:
                trade_file = os.path.abspath(
                    os.path.join(get_folder_path('data'), '{}_trade.csv'.format(strategy_name)))
                append_data(file_name=trade_file, dict_data=trade_dict)
        except Exception as ex:
            self.write_error(u'写入交易记录csv出错：{},{}'.format(str(ex), traceback.format_exc()))

        self.call_strategy_func(strategy, strategy.on_trade, trade)

        # Sync strategy variables to data file
        # 取消此功能，由策略自身完成数据持久化
        # self.sync_strategy_data(strategy)

        # Update GUI
        self.put_strategy_event(strategy)

    def process_position_event(self, event: Event):
        """"""
        position = event.data

        self.offset_converter.update_position(position)

    def check_unsubscribed_symbols(self):
        """检查未订阅合约"""

        for key in self.pending_subcribe_symbol_map.keys():
            # gateway_name.symbol.exchange = > gateway_name, vt_symbol
            keys = key.split('.')
            gateway_name = keys[0]
            vt_symbol = '.'.join(keys[1:])

            contract = self.main_engine.get_contract(vt_symbol)
            is_bar = True if vt_symbol in self.bar_strategy_map else False
            if contract:
                # 获取合约的缩写号
                underlying_symbol = get_underlying_symbol(vt_symbol)
                dt = datetime.now()
                # 若为中金所的合约，白天才提交订阅请求
                if underlying_symbol in MARKET_DAY_ONLY and not (9 < dt.hour < 16):
                    continue

                self.write_log(f'重新提交合约{vt_symbol}订阅请求')
                for strategy_name, is_bar in list(self.pending_subcribe_symbol_map[vt_symbol]):
                    self.subscribe_symbol(strategy_name=strategy_name,
                                          vt_symbol=vt_symbol,
                                          gateway_name=gateway_name,
                                          is_bar=is_bar)
            else:
                try:
                    self.write_log(f'找不到合约{vt_symbol}信息，尝试请求所有接口')
                    symbol, exchange = extract_vt_symbol(vt_symbol)
                    req = SubscribeRequest(symbol=symbol, exchange=exchange)
                    req.is_bar = is_bar
                    self.main_engine.subscribe(req, gateway_name)

                except Exception as ex:
                    self.write_error(
                        u'重新订阅{}.{}异常:{},{}'.format(gateway_name, vt_symbol, str(ex), traceback.format_exc()))
                    return

    def check_stop_order(self, tick: TickData):
        """"""
        for stop_order in list(self.stop_orders.values()):
            if stop_order.vt_symbol != tick.vt_symbol:
                continue

            long_triggered = (
                    stop_order.direction == Direction.LONG and tick.last_price >= stop_order.price
            )
            short_triggered = (
                    stop_order.direction == Direction.SHORT and tick.last_price <= stop_order.price
            )

            if long_triggered or short_triggered:
                strategy = self.strategies[stop_order.strategy_name]

                # To get excuted immediately after stop order is
                # triggered, use limit price if available, otherwise
                # use ask_price_5 or bid_price_5
                if stop_order.direction == Direction.LONG:
                    if tick.limit_up:
                        price = tick.limit_up
                    else:
                        price = tick.ask_price_5
                else:
                    if tick.limit_down:
                        price = tick.limit_down
                    else:
                        price = tick.bid_price_5

                contract = self.main_engine.get_contract(stop_order.vt_symbol)

                vt_orderids = self.send_limit_order(
                    strategy,
                    contract,
                    stop_order.direction,
                    stop_order.offset,
                    price,
                    stop_order.volume,
                    stop_order.lock
                )

                # Update stop order status if placed successfully
                if vt_orderids:
                    # Remove from relation map.
                    self.stop_orders.pop(stop_order.stop_orderid)

                    strategy_vt_orderids = self.strategy_orderid_map[strategy.strategy_name]
                    if stop_order.stop_orderid in strategy_vt_orderids:
                        strategy_vt_orderids.remove(stop_order.stop_orderid)

                    # Change stop order status to cancelled and update to strategy.
                    stop_order.status = StopOrderStatus.TRIGGERED
                    stop_order.vt_orderids = vt_orderids

                    self.call_strategy_func(
                        strategy, strategy.on_stop_order, stop_order
                    )
                    self.put_stop_order_event(stop_order)

    def send_server_order(
            self,
            strategy: CtaTemplate,
            contract: ContractData,
            direction: Direction,
            offset: Offset,
            price: float,
            volume: float,
            type: OrderType,
            lock: bool,
            gateway_name: str = None
    ):
        """
        Send a new order to server.
        """
        # Create request and send order.
        original_req = OrderRequest(
            symbol=contract.symbol,
            exchange=contract.exchange,
            direction=direction,
            offset=offset,
            type=type,
            price=price,
            volume=volume,
        )

        # 如果没有指定网关，则使用合约信息内的网关
        if contract.gateway_name and not gateway_name:
            gateway_name = contract.gateway_name

        # Convert with offset converter
        req_list = self.offset_converter.convert_order_request(original_req, lock, gateway_name)

        # Send Orders
        vt_orderids = []

        for req in req_list:
            vt_orderid = self.main_engine.send_order(
                req, gateway_name)

            # Check if sending order successful
            if not vt_orderid:
                continue

            vt_orderids.append(vt_orderid)

            self.offset_converter.update_order_request(req, vt_orderid, gateway_name)

            # Save relationship between orderid and strategy.
            self.orderid_strategy_map[vt_orderid] = strategy
            self.strategy_orderid_map[strategy.strategy_name].add(vt_orderid)

        return vt_orderids

    def send_limit_order(
            self,
            strategy: CtaTemplate,
            contract: ContractData,
            direction: Direction,
            offset: Offset,
            price: float,
            volume: float,
            lock: bool,
            gateway_name: str = None
    ):
        """
        Send a limit order to server.
        """
        return self.send_server_order(
            strategy,
            contract,
            direction,
            offset,
            price,
            volume,
            OrderType.LIMIT,
            lock,
            gateway_name
        )

    def send_fak_order(
            self,
            strategy: CtaTemplate,
            contract: ContractData,
            direction: Direction,
            offset: Offset,
            price: float,
            volume: float,
            lock: bool,
            gateway_name: str = None
    ):
        """
        Send a limit order to server.
        """
        return self.send_server_order(
            strategy,
            contract,
            direction,
            offset,
            price,
            volume,
            OrderType.FAK,
            lock,
            gateway_name
        )

    def send_server_stop_order(
            self,
            strategy: CtaTemplate,
            contract: ContractData,
            direction: Direction,
            offset: Offset,
            price: float,
            volume: float,
            lock: bool,
            gateway_name: str = None
    ):
        """
        Send a stop order to server.

        Should only be used if stop order supported
        on the trading server.
        """
        return self.send_server_order(
            strategy,
            contract,
            direction,
            offset,
            price,
            volume,
            OrderType.STOP,
            lock,
            gateway_name
        )

    def send_local_stop_order(
            self,
            strategy: CtaTemplate,
            vt_symbol: str,
            direction: Direction,
            offset: Offset,
            price: float,
            volume: float,
            lock: bool,
            gateway_name: str = None
    ):
        """
        Create a new local stop order.
        """
        self.stop_order_count += 1
        stop_orderid = f"{STOPORDER_PREFIX}.{self.stop_order_count}"

        stop_order = StopOrder(
            vt_symbol=vt_symbol,
            direction=direction,
            offset=offset,
            price=price,
            volume=volume,
            stop_orderid=stop_orderid,
            strategy_name=strategy.strategy_name,
            lock=lock,
            gateway_name=gateway_name
        )

        self.stop_orders[stop_orderid] = stop_order

        vt_orderids = self.strategy_orderid_map[strategy.strategy_name]
        vt_orderids.add(stop_orderid)

        self.call_strategy_func(strategy, strategy.on_stop_order, stop_order)
        self.put_stop_order_event(stop_order)

        return [stop_orderid]

    def cancel_server_order(self, strategy: CtaTemplate, vt_orderid: str):
        """
        Cancel existing order by vt_orderid.
        """
        order = self.main_engine.get_order(vt_orderid)
        if not order:
            self.write_log(msg=f"撤单失败，找不到委托{vt_orderid}",
                           strategy_Name=strategy.name,
                           level=logging.ERROR)
            return

        req = order.create_cancel_request()
        self.main_engine.cancel_order(req, order.gateway_name)

    def cancel_local_stop_order(self, strategy: CtaTemplate, stop_orderid: str):
        """
        Cancel a local stop order.
        """
        stop_order = self.stop_orders.get(stop_orderid, None)
        if not stop_order:
            return
        strategy = self.strategies[stop_order.strategy_name]

        # Remove from relation map.
        self.stop_orders.pop(stop_orderid)

        vt_orderids = self.strategy_orderid_map[strategy.strategy_name]
        if stop_orderid in vt_orderids:
            vt_orderids.remove(stop_orderid)

        # Change stop order status to cancelled and update to strategy.
        stop_order.status = StopOrderStatus.CANCELLED

        self.call_strategy_func(strategy, strategy.on_stop_order, stop_order)
        self.put_stop_order_event(stop_order)

    def send_order(
            self,
            strategy: CtaTemplate,
            vt_symbol: str,
            direction: Direction,
            offset: Offset,
            price: float,
            volume: float,
            stop: bool,
            lock: bool,
            order_type: OrderType = OrderType.LIMIT,
            gateway_name: str = None
    ):
        """
        该方法供策略使用，发送委托。
        """
        contract = self.main_engine.get_contract(vt_symbol)
        if not contract:
            self.write_log(msg=f"委托失败，找不到合约：{vt_symbol}",
                           strategy_name=strategy.name,
                           level=logging.ERROR)
            return ""
        if contract.gateway_name and not gateway_name:
            gateway_name = contract.gateway_name
        # Round order price and volume to nearest incremental value
        price = round_to(price, contract.pricetick)
        volume = round_to(volume, contract.min_volume)

        if stop:
            if contract.stop_supported:
                return self.send_server_stop_order(strategy, contract, direction, offset, price, volume, lock,
                                                   gateway_name)
            else:
                return self.send_local_stop_order(strategy, vt_symbol, direction, offset, price, volume, lock,
                                                  gateway_name)
        if order_type == OrderType.FAK:
            return self.send_fak_order(strategy, contract, direction, offset, price, volume, lock, gateway_name)
        else:
            return self.send_limit_order(strategy, contract, direction, offset, price, volume, lock, gateway_name)

    def cancel_order(self, strategy: CtaTemplate, vt_orderid: str):
        """
        """
        if vt_orderid.startswith(STOPORDER_PREFIX):
            self.cancel_local_stop_order(strategy, vt_orderid)
        else:
            self.cancel_server_order(strategy, vt_orderid)

    def cancel_all(self, strategy: CtaTemplate):
        """
        Cancel all active orders of a strategy.
        """
        vt_orderids = self.strategy_orderid_map[strategy.strategy_name]
        if not vt_orderids:
            return

        for vt_orderid in copy(vt_orderids):
            self.cancel_order(strategy, vt_orderid)

    def subscribe_symbol(self, strategy_name: str, vt_symbol: str, gateway_name: str = '', is_bar: bool = False):
        """订阅合约"""
        strategy = self.strategies.get(strategy_name, None)
        if not strategy:
            return False

        contract = self.main_engine.get_contract(vt_symbol)
        if contract:
            if contract.gateway_name and not gateway_name:
                gateway_name = contract.gateway_name
            req = SubscribeRequest(
                symbol=contract.symbol, exchange=contract.exchange)
            self.main_engine.subscribe(req, gateway_name)
        else:
            self.write_log(msg=f"找不到合约{vt_symbol},添加到待订阅列表",
                           strategy_name=strategy.name)
            self.pending_subcribe_symbol_map[f'{gateway_name}.{vt_symbol}'].add((strategy_name, is_bar))
            try:
                self.write_log(f'找不到合约{vt_symbol}信息，尝试请求所有接口')
                symbol, exchange = extract_vt_symbol(vt_symbol)
                req = SubscribeRequest(symbol=symbol, exchange=exchange)
                req.is_bar = is_bar
                self.main_engine.subscribe(req, gateway_name)

            except Exception as ex:
                self.write_error(u'重新订阅{}异常:{},{}'.format(vt_symbol, str(ex), traceback.format_exc()))

        # 如果是订阅bar
        if is_bar:
            strategies = self.bar_strategy_map[vt_symbol]
            if strategy not in strategies:
                strategies.append(strategy)
                self.bar_strategy_map.update({vt_symbol: strategies})
        else:
            # 添加 合约订阅 vt_symbol <=> 策略实例 strategy 映射.
            strategies = self.symbol_strategy_map[vt_symbol]
            strategies.append(strategy)

        # 添加 策略名 strategy_name  <=> 合约订阅 vt_symbol 的映射
        subscribe_symbol_set = self.strategy_symbol_map[strategy.name]
        subscribe_symbol_set.add(contract.vt_symbol)

        return True

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

    def get_price(self, vt_symbol: str):
        """查询合约的最新价格"""
        tick = self.main_engine.get_tick(vt_symbol)
        if tick:
            return tick.last_price

        return None

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
                return account.balance, account.avaliable, round(account.frozen * 100 / (account.balance + 0.01), 2), 100
            else:
                return 0, 0, 0, 0

    def get_position(self, vt_symbol: str, direction: Direction, gateway_name: str = ''):
        """ 查询合约在账号的持仓,需要指定方向"""
        vt_position_id = f"{gateway_name}.{vt_symbol}.{direction.value}"
        return self.main_engine.get_position(vt_position_id)

    def get_position_holding(self, vt_symbol: str, gateway_name: str = ''):
        """ 查询合约在账号的持仓（包含多空）"""
        return self.offset_converter.get_position_holding(vt_symbol, gateway_name)

    def get_engine_type(self):
        """"""
        return self.engine_type

    def call_strategy_func(
            self, strategy: CtaTemplate, func: Callable, params: Any = None
    ):
        """
        Call function of a strategy and catch any exception raised.
        """
        try:
            if params:
                func(params)
            else:
                func()
        except Exception:
            strategy.trading = False
            strategy.inited = False

            msg = f"触发异常已停止\n{traceback.format_exc()}"
            self.write_log(msg=msg,
                           strategy_name=strategy.strategy_name,
                           level=logging.CRITICAL)

    def add_strategy(
            self, class_name: str, strategy_name: str, vt_symbol: str, setting: dict
    ):
        """
        Add a new strategy.
        """
        if strategy_name in self.strategies:
            self.write_log(msg=f"创建策略失败，存在重名{strategy_name}",
                           level=logging.CRITICAL)
            return

        strategy_class = self.classes.get(class_name, None)
        if not strategy_class:
            self.write_log(msg=f"创建策略失败，找不到策略类{class_name}",
                           level=logging.CRITICAL)
            return

        self.write_log(f'开始添加策略类{class_name}，实例名:{strategy_name}')
        strategy = strategy_class(self, strategy_name, vt_symbol, setting)
        self.strategies[strategy_name] = strategy

        # Add vt_symbol to strategy map.
        strategies = self.symbol_strategy_map[vt_symbol]
        strategies.append(strategy)

        subscribe_symbol_set = self.strategy_symbol_map[strategy_name]
        subscribe_symbol_set.add(vt_symbol)

        # Update to setting file.
        self.update_strategy_setting(strategy_name, setting)

        self.put_strategy_event(strategy)

        # 判断设置中是否由自动初始化和自动启动项目
        if setting.get('auto_init', False):
            self.init_strategy(strategy_name, auto_start=setting.get('auto_start', False))

    def init_strategy(self, strategy_name: str, auto_start: bool = False):
        """
        Init a strategy.
        """
        self.init_executor.submit(self._init_strategy, strategy_name, auto_start)

    def _init_strategy(self, strategy_name: str, auto_start: bool = False):
        """
        Init strategies in queue.
        """
        strategy = self.strategies[strategy_name]

        if strategy.inited:
            self.write_error(f"{strategy_name}已经完成初始化，禁止重复操作")
            return

        self.write_log(f"{strategy_name}开始执行初始化")

        # Call on_init function of strategy
        self.call_strategy_func(strategy, strategy.on_init)

        # Restore strategy data(variables)
        # Pro 版本不使用自动恢复除了内部数据功能，由策略自身初始化时完成
        # data = self.strategy_data.get(strategy_name, None)
        # if data:
        #     for name in strategy.variables:
        #         value = data.get(name, None)
        #         if value:
        #             setattr(strategy, name, value)

        # Subscribe market data 订阅缺省的vt_symbol, 如果有其他合约需要订阅，由策略内部初始化时提交订阅即可。
        self.subscribe_symbol(strategy_name, vt_symbol=strategy.vt_symbol)

        # Put event to update init completed status.
        strategy.inited = True
        self.put_strategy_event(strategy)
        self.write_log(f"{strategy_name}初始化完成")

        # 初始化后，自动启动策略交易
        if auto_start:
            self.start_strategy(strategy_name)

    def start_strategy(self, strategy_name: str):
        """
        Start a strategy.
        """
        strategy = self.strategies[strategy_name]
        if not strategy.inited:
            self.write_error(f"策略{strategy.strategy_name}启动失败，请先初始化")
            return

        if strategy.trading:
            self.write_error(f"{strategy_name}已经启动，请勿重复操作")
            return

        self.call_strategy_func(strategy, strategy.on_start)
        strategy.trading = True

        self.put_strategy_event(strategy)

    def stop_strategy(self, strategy_name: str):
        """
        Stop a strategy.
        """
        strategy = self.strategies[strategy_name]
        if not strategy.trading:
            self.write_log(f'{strategy_name}策略实例已处于停止交易状态')
            return

        # Call on_stop function of the strategy
        self.write_log(f'调用{strategy_name}的on_stop,停止交易')
        self.call_strategy_func(strategy, strategy.on_stop)

        # Change trading status of strategy to False
        strategy.trading = False

        # Cancel all orders of the strategy
        self.write_log(f'撤销{strategy_name}所有委托')
        self.cancel_all(strategy)

        # Sync strategy variables to data file
        #  取消此功能，由策略自身完成数据的持久化
        # self.sync_strategy_data(strategy)

        # Update GUI
        self.put_strategy_event(strategy)

    def edit_strategy(self, strategy_name: str, setting: dict):
        """
        Edit parameters of a strategy.
        风险警示： 该方法强行干预策略的配置
        """
        strategy = self.strategies[strategy_name]
        strategy.update_setting(setting)

        self.update_strategy_setting(strategy_name, setting)
        self.put_strategy_event(strategy)

    def remove_strategy(self, strategy_name: str):
        """
        Remove a strategy.
        """
        strategy = self.strategies[strategy_name]
        if strategy.trading:
            self.write_error(f"策略{strategy.strategy_name}移除失败，请先停止")
            return

        # Remove setting
        self.remove_strategy_setting(strategy_name)

        # 移除订阅合约与策略的关联关系
        for vt_symbol in self.strategy_symbol_map[strategy_name]:
            # Remove from symbol strategy map
            self.write_log(f'移除{vt_symbol}《=》{strategy_name}的订阅关系')
            strategies = self.symbol_strategy_map[vt_symbol]
            strategies.remove(strategy)

        # Remove from active orderid map
        if strategy_name in self.strategy_orderid_map:
            vt_orderids = self.strategy_orderid_map.pop(strategy_name)
            self.write_log(f'移除{strategy_name}的所有委托订单映射关系')
            # Remove vt_orderid strategy map
            for vt_orderid in vt_orderids:
                if vt_orderid in self.orderid_strategy_map:
                    self.orderid_strategy_map.pop(vt_orderid)

        # Remove from strategies
        self.write_log(f'移除{strategy_name}策略实例')
        self.strategies.pop(strategy_name)

        return True

    def reload_strategy(self, strategy_name: str, vt_symbol: str = '', setting: dict = {}):
        """
        重新加载策略
        一般使用于在线更新策略代码，或者更新策略参数，需要重新启动策略
        :param strategy_name:
        :param setting:
        :return:
        """
        self.write_log(f'开始重新加载策略{strategy_name}')

        # 优先判断重启的策略，是否已经加载
        if strategy_name not in self.strategies or strategy_name not in self.strategy_setting:
            self.write_error(f"{strategy_name}不在运行策略中，不能重启")
            return False
        old_strategy_config = copy(self.strategy_setting[strategy_name])

        class_name = old_strategy_config.get('class_name')
        if len(vt_symbol) == 0:
            vt_symbol = old_strategy_config.get('vt_symbol')
        if len(setting) == 0:
            setting = old_strategy_config.get('setting')

        module_name = self.class_module_map[class_name]
        # 重新load class module
        if not self.load_strategy_class_from_module(module_name):
            return False

        # 停止当前策略实例的运行，撤单
        self.stop_strategy(strategy_name)

        # 移除运行中的策略实例
        self.remove_strategy(strategy_name)

        # 重新添加策略
        self.add_strategy(class_name=class_name,
                          strategy_name=strategy_name,
                          vt_symbol=vt_symbol,
                          setting=setting)

        self.write_log(f'重新运行策略{strategy_name}执行完毕')
        return True

    def load_strategy_class(self):
        """
        Load strategy class from source code.
        """
        # 加载 vnpy/app/cta_strategy_pro/strategies的所有策略
        path1 = Path(__file__).parent.joinpath("strategies")
        self.load_strategy_class_from_folder(
            path1, "vnpy.app.cta_strategy_pro.strategies")

        # 加载 当前运行目录下strategies子目录的所有策略
        path2 = Path.cwd().joinpath("strategies")
        self.load_strategy_class_from_folder(path2, "strategies")

    def load_strategy_class_from_folder(self, path: Path, module_name: str = ""):
        """
        Load strategy class from certain folder.
        """
        for dirpath, dirnames, filenames in os.walk(str(path)):
            for filename in filenames:
                if filename.endswith(".py"):
                    strategy_module_name = ".".join(
                        [module_name, filename.replace(".py", "")])
                elif filename.endswith(".pyd"):
                    strategy_module_name = ".".join(
                        [module_name, filename.split(".")[0]])
                else:
                    continue
                self.load_strategy_class_from_module(strategy_module_name)

    def load_strategy_class_from_module(self, module_name: str):
        """
        Load/Reload strategy class from module file.
        """
        try:
            module = importlib.import_module(module_name)

            for name in dir(module):
                value = getattr(module, name)
                if (isinstance(value, type) and issubclass(value, CtaTemplate) and value is not CtaTemplate):
                    class_name = value.__name__
                    if class_name not in self.classes:
                        self.write_log(f"加载策略类{module_name}.{class_name}")
                    else:
                        self.write_log(f"更新策略类{module_name}.{class_name}")
                    self.classes[class_name] = value
                    self.class_module_map[class_name] = module_name
            return True
        except:  # noqa
            msg = f"策略文件{module_name}加载失败，触发异常：\n{traceback.format_exc()}"
            self.write_log(msg=msg, level=logging.CRITICAL)
            return False

    def load_strategy_data(self):
        """
        Load strategy data from json file.
        """
        print(f'load_strategy_data 此功能已取消，由策略自身完成数据的持久化加载', file=sys.stderr)
        return
        # self.strategy_data = load_json(self.data_filename)

    def sync_strategy_data(self, strategy: CtaTemplate):
        """
        Sync strategy data into json file.
        """
        # data = strategy.get_variables()
        # data.pop("inited")      # Strategy status (inited, trading) should not be synced.
        # data.pop("trading")
        # self.strategy_data[strategy.strategy_name] = data
        # save_json(self.data_filename, self.strategy_data)
        print(f'sync_strategy_data此功能已取消，由策略自身完成数据的持久化保存', file=sys.stderr)

    def get_all_strategy_class_names(self):
        """
        Return names of strategy classes loaded.
        """
        return list(self.classes.keys())

    def get_strategy_status(self, strategy_name):
        """
        return strategy inited/trading status
        :param strategy_name:
        :return:
        """
        inited = False
        trading = False

        strategy = self.strategies.get(strategy_name, None)
        if strategy:
            inited = strategy.inited
            trading = strategy.trading

        return inited, trading

    def get_strategy_pos(self, name, strategy=None):
        """
        获取策略的持仓字典
        :param name:策略名
        :return: [ {},{}]
        """
        # 兼容处理，如果strategy是None，通过name获取
        if strategy is None:
            if name not in self.strategies:
                self.write_log(u'getStategyPos 策略实例不存在：' + name)
                return []
            # 获取策略实例
            strategy = self.strategies[name]

        pos_list = []

        if strategy.inited:
            # 如果策略具有getPositions得方法，则调用该方法
            if hasattr(strategy, 'get_positions'):
                pos_list = strategy.get_positions()
                for pos in pos_list:
                    vt_symbol = pos.get('vt_symbol', None)
                    if vt_symbol:
                        symbol, exchange = extract_vt_symbol(vt_symbol)
                        pos.update({'symbol': symbol})

            # 如果策略有 ctaPosition属性
            elif hasattr(strategy, 'position') and issubclass(strategy.position, CtaPosition):
                symbol, exchange = extract_vt_symbol(strategy.vt_symbol)
                # 多仓
                long_pos = {}
                long_pos['vt_symbol'] = strategy.vt_symbol
                long_pos['symbol'] = symbol
                long_pos['direction'] = 'long'
                long_pos['volume'] = strategy.position.long_pos
                if long_pos['volume'] > 0:
                    pos_list.append(long_pos)

                # 空仓
                short_pos = {}
                short_pos['vt_symbol'] = strategy.vt_symbol
                short_pos['symbol'] = symbol
                short_pos['direction'] = 'short'
                short_pos['volume'] = abs(strategy.position.short_pos)
                if short_pos['volume'] > 0:
                    pos_list.append(short_pos)

            # 获取模板缺省pos属性
            elif hasattr(strategy, 'pos') and isinstance(strategy.pos, int):
                symbol, exchange = extract_vt_symbol(strategy.vt_symbol)
                if strategy.pos > 0:
                    long_pos = {}
                    long_pos['vt_symbol'] = strategy.vt_symbol
                    long_pos['symbol'] = symbol
                    long_pos['direction'] = 'long'
                    long_pos['volume'] = strategy.pos
                    if long_pos['volume'] > 0:
                        pos_list.append(long_pos)
                elif strategy.pos < 0:
                    short_pos = {}
                    short_pos['symbol'] = symbol
                    short_pos['vt_symbol'] = strategy.vt_symbol
                    short_pos['direction'] = 'short'
                    short_pos['volume'] = abs(strategy.pos)
                    if short_pos['volume'] > 0:
                        pos_list.append(short_pos)

            # 新增处理SPD结尾得特殊自定义套利合约
            try:
                if strategy.vt_symbol.endswith('SPD') and len(pos_list) > 0:
                    old_pos_list = copy(pos_list)
                    pos_list = []
                    for pos in old_pos_list:
                        # SPD合约
                        spd_vt_symbol = pos.get('vt_symbol', None)
                        if spd_vt_symbol is not None and spd_vt_symbol.endswith('SPD'):
                            spd_symbol,spd_exchange = extract_vt_symbol(spd_vt_symbol)
                            spd_setting = self.main_engine.get_all_custom_contracts().get(spd_symbol, None)

                            if spd_setting is None:
                                self.write_error(u'获取不到:{}得设置信息，检查自定义合约配置文件'.format(spd_symbol))
                                pos_list.append(pos)
                                continue

                            leg1_direction = 'long' if pos.get('direction') in [Direction.LONG, 'long'] else 'short'
                            leg2_direction = 'short' if leg1_direction == 'long' else 'long'
                            spd_volume = pos.get('volume')

                            leg1_pos = {}
                            leg1_pos.update({'symbol': spd_setting.get('leg1_symbol')})
                            leg1_pos.update({'vt_symbol': spd_setting.get('leg1_symbol')})
                            leg1_pos.update({'direction': leg1_direction})
                            leg1_pos.update({'volume': spd_setting.get('leg1_ratio', 1)*spd_volume})

                            leg2_pos = {}
                            leg2_pos.update({'symbol': spd_setting.get('leg2_symbol')})
                            leg2_pos.update({'vt_symbol': spd_setting.get('leg2_symbol')})
                            leg2_pos.update({'direction': leg2_direction})
                            leg2_pos.update({'volume': spd_setting.get('leg2_ratio', 1) * spd_volume})

                            pos_list.append(leg1_pos)
                            pos_list.append(leg2_pos)

                        else:
                            pos_list.append(pos)

            except Exception as ex:
                self.write_error(u'分解SPD失败')

        # update local pos dict
        self.strategy_pos_dict.update({name: pos_list})

        return pos_list

    def get_all_strategy_pos(self):
        """
        获取所有得策略仓位明细
        """
        strategy_pos_list = []
        for strategy_name in list(self.strategies.keys()):
            d = OrderedDict()
            d['accountid'] = self.engine_config.get('accountid', '-')
            d['strategy_group'] = self.engine_config.get('strategy_group', '-')
            d['strategy_name'] = strategy_name
            dt = datetime.now()
            d['date'] = dt.strftime('%Y%m%d')
            d['hour'] = dt.hour
            d['datetime'] = datetime.now()
            try:
                d['pos'] = self.get_strategy_pos(name=strategy_name)
            except Exception as ex:
                self.write_error(
                    u'get_strategy_pos exception:{},{}'.format(str(ex), traceback.format_exc()))
                d['pos'] = []
            strategy_pos_list.append(d)

        return strategy_pos_list

    def get_strategy_class_parameters(self, class_name: str):
        """
        Get default parameters of a strategy class.
        """
        strategy_class = self.classes[class_name]

        parameters = {}
        for name in strategy_class.parameters:
            parameters[name] = getattr(strategy_class, name)

        return parameters

    def get_strategy_parameters(self, strategy_name):
        """
        Get parameters of a strategy.
        """
        strategy = self.strategies[strategy_name]
        return strategy.get_parameters()

    def init_all_strategies(self):
        """
        """
        for strategy_name in self.strategies.keys():
            self.init_strategy(strategy_name)

    def start_all_strategies(self):
        """
        """
        for strategy_name in self.strategies.keys():
            self.start_strategy(strategy_name)

    def stop_all_strategies(self):
        """
        """
        for strategy_name in self.strategies.keys():
            self.stop_strategy(strategy_name)

    def load_strategy_setting(self):
        """
        Load setting file.
        """
        # 读取引擎得配置
        self.engine_config = load_json(self.engine_filename)

        # 读取策略得配置
        self.strategy_setting = load_json(self.setting_filename)

        for strategy_name, strategy_config in self.strategy_setting.items():
            self.add_strategy(
                strategy_config["class_name"],
                strategy_name,
                strategy_config["vt_symbol"],
                strategy_config["setting"]
            )

    def update_strategy_setting(self, strategy_name: str, setting: dict):
        """
        Update setting file.
        """
        strategy = self.strategies[strategy_name]

        self.strategy_setting[strategy_name] = {
            "class_name": strategy.__class__.__name__,
            "vt_symbol": strategy.vt_symbol,
            "setting": setting,
        }
        save_json(self.setting_filename, self.strategy_setting)

    def remove_strategy_setting(self, strategy_name: str):
        """
        Update setting file.
        """
        if strategy_name not in self.strategy_setting:
            return
        self.write_log(f'移除CTA引擎{strategy_name}的配置')
        self.strategy_setting.pop(strategy_name)
        save_json(self.setting_filename, self.strategy_setting)

    def put_stop_order_event(self, stop_order: StopOrder):
        """
        Put an event to update stop order status.
        """
        event = Event(EVENT_CTA_STOPORDER, stop_order)
        self.event_engine.put(event)

    def put_strategy_event(self, strategy: CtaTemplate):
        """
        Put an event to update strategy status.
        """
        data = strategy.get_data()
        event = Event(EVENT_CTA_STRATEGY, data)
        self.event_engine.put(event)

    def put_all_strategy_pos_event(self, strategy_pos_list: list = []):
        """推送所有策略得持仓事件"""
        for strategy_pos in strategy_pos_list:
            event = Event(EVENT_STRATEGY_POS, copy(strategy_pos))
            self.event_engine.put(event)

    def write_log(self, msg: str, strategy_name: str = '', level: int = logging.INFO):
        """
        Create cta engine log event.
        """
        # 推送至全局CTA_LOG Event
        log = LogData(msg=f"{strategy_name}: {msg}" if strategy_name else msg,
                      gateway_name="CtaStrategy",
                      level=level)
        event = Event(type=EVENT_CTA_LOG, data=log)
        self.event_engine.put(event)

        # 保存单独的策略日志
        if strategy_name:
            strategy_logger = self.strategy_loggers.get(strategy_name, None)
            if not strategy_logger:
                log_path = get_folder_path('log')
                log_filename = os.path.abspath(os.path.join(log_path, str(strategy_name)))
                print(u'create logger:{}'.format(log_filename))
                self.strategy_loggers[strategy_name] = setup_logger(file_name=log_filename,
                                                                    name=str(strategy_name))
                strategy_logger = self.strategy_loggers.get(strategy_name)
            if strategy_logger:
                strategy_logger.log(level, msg)

        # 如果日志数据异常，错误和告警，输出至sys.stderr
        if level in [logging.CRITICAL, logging.ERROR, logging.WARNING]:
            print(f"{strategy_name}: {msg}" if strategy_name else msg, file=sys.stderr)

    def write_error(self, msg: str, strategy_name: str = ''):
        """写入错误日志"""
        self.write_log(msg=msg, strategy_name=strategy_name, level=logging.ERROR)

    def send_email(self, msg: str, strategy: CtaTemplate = None):
        """
        Send email to default receiver.
        """
        if strategy:
            subject = f"{strategy.strategy_name}"
        else:
            subject = "CTA策略引擎"

        self.main_engine.send_email(subject, msg)
