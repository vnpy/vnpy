""""""
import os
import uuid
import bz2
import pickle
import traceback
import zlib

from abc import ABC
from copy import copy
from typing import Any, Callable
from logging import INFO, ERROR
from datetime import datetime
from vnpy.trader.constant import Interval, Direction, Offset, Status, OrderType
from vnpy.trader.object import BarData, TickData, OrderData, TradeData
from vnpy.trader.utility import virtual, append_data, extract_vt_symbol, get_underlying_symbol

from .base import StopOrder, EngineType
from .cta_grid_trade import CtaGrid, CtaGridTrade, LOCK_GRID
from .cta_position import CtaPosition


class CtaTemplate(ABC):
    """CTA策略模板"""

    author = ""
    parameters = []
    variables = []

    # 保存委托单编号和相关委托单的字典
    # key为委托单编号
    # value为该合约相关的委托单
    active_orders = {}

    def __init__(
            self,
            cta_engine: Any,
            strategy_name: str,
            vt_symbol: str,
            setting: dict,
    ):
        """"""
        self.cta_engine = cta_engine
        self.strategy_name = strategy_name
        self.vt_symbol = vt_symbol

        self.inited = False  # 是否初始化完毕
        self.trading = False  # 是否开始交易
        self.pos = 0  # 持仓/仓差
        self.entrust = 0  # 是否正在委托, 0, 无委托 , 1, 委托方向是LONG， -1, 委托方向是SHORT

        self.tick_dict = {}  # 记录所有on_tick传入最新tick

        # Copy a new variables list here to avoid duplicate insert when multiple
        # strategy instances are created with the same strategy class.
        self.variables = copy(self.variables)
        self.variables.insert(0, "inited")
        self.variables.insert(1, "trading")
        self.variables.insert(2, "pos")
        self.variables.insert(3, "entrust")

    def update_setting(self, setting: dict):
        """
        Update strategy parameter wtih value in setting dict.
        """
        for name in self.parameters:
            if name in setting:
                setattr(self, name, setting[name])

    @classmethod
    def get_class_parameters(cls):
        """
        Get default parameters dict of strategy class.
        """
        class_parameters = {}
        for name in cls.parameters:
            class_parameters[name] = getattr(cls, name)
        return class_parameters

    def get_parameters(self):
        """
        Get strategy parameters dict.
        """
        strategy_parameters = {}
        for name in self.parameters:
            strategy_parameters[name] = getattr(self, name)
        return strategy_parameters

    def get_variables(self):
        """
        Get strategy variables dict.
        """
        strategy_variables = {}
        for name in self.variables:
            strategy_variables[name] = getattr(self, name)
        return strategy_variables

    def get_data(self):
        """
        Get strategy data.
        """
        strategy_data = {
            "strategy_name": self.strategy_name,
            "vt_symbol": self.vt_symbol,
            "class_name": self.__class__.__name__,
            "author": self.author,
            "parameters": self.get_parameters(),
            "variables": self.get_variables(),
        }
        return strategy_data

    def get_positions(self):
        """ 返回持仓数量"""
        pos_list = []
        if self.pos > 0:
            pos_list.append({
                "vt_symbol": self.vt_symbol,
                "direction": "long",
                "volume": self.pos
            })
        elif self.pos < 0:
            pos_list.append({
                "vt_symbol": self.vt_symbol,
                "direction": "short",
                "volume": abs(self.pos)
            })
        return pos_list

    @virtual
    def on_timer(self):
        pass

    @virtual
    def on_init(self):
        """
        Callback when strategy is inited.
        """
        pass

    @virtual
    def on_start(self):
        """
        Callback when strategy is started.
        """
        pass

    @virtual
    def on_stop(self):
        """
        Callback when strategy is stopped.
        """
        pass

    @virtual
    def on_tick(self, tick: TickData):
        """
        Callback of new tick data update.
        """
        pass

    @virtual
    def on_bar(self, bar: BarData):
        """
        Callback of new bar data update.
        """
        pass

    @virtual
    def on_trade(self, trade: TradeData):
        """
        Callback of new trade data update.
        """
        pass

    @virtual
    def on_order(self, order: OrderData):
        """
        Callback of new order data update.
        """
        pass

    @virtual
    def on_stop_order(self, stop_order: StopOrder):
        """
        Callback of stop order update.
        """
        pass

    def buy(self, price: float, volume: float, stop: bool = False, lock: bool = False,
            vt_symbol: str = '', order_type: OrderType = OrderType.LIMIT,
            order_time: datetime = None, grid: CtaGrid = None):
        """
        Send buy order to open a long position.
        """
        if OrderType in [OrderType.FAK, OrderType.FOK]:
            if self.is_upper_limit(vt_symbol):
                self.write_error(u'涨停价不做FAK/FOK委托')
                return []
        return self.send_order(vt_symbol=vt_symbol,
                               direction=Direction.LONG,
                               offset=Offset.OPEN,
                               price=price,
                               volume=volume,
                               stop=stop,
                               lock=lock,
                               order_type=order_type,
                               order_time=order_time,
                               grid=grid)

    def sell(self, price: float, volume: float, stop: bool = False, lock: bool = False,
             vt_symbol: str = '', order_type: OrderType = OrderType.LIMIT,
             order_time: datetime = None, grid: CtaGrid = None):
        """
        Send sell order to close a long position.
        """
        if OrderType in [OrderType.FAK, OrderType.FOK]:
            if self.is_lower_limit(vt_symbol):
                self.write_error(u'跌停价不做FAK/FOK sell委托')
                return []
        return self.send_order(vt_symbol=vt_symbol,
                               direction=Direction.SHORT,
                               offset=Offset.CLOSE,
                               price=price,
                               volume=volume,
                               stop=stop,
                               lock=lock,
                               order_type=order_type,
                               order_time=order_time,
                               grid=grid)

    def short(self, price: float, volume: float, stop: bool = False, lock: bool = False,
              vt_symbol: str = '', order_type: OrderType = OrderType.LIMIT,
              order_time: datetime = None, grid: CtaGrid = None):
        """
        Send short order to open as short position.
        """
        if OrderType in [OrderType.FAK, OrderType.FOK]:
            if self.is_lower_limit(vt_symbol):
                self.write_error(u'跌停价不做FAK/FOK short委托')
                return []
        return self.send_order(vt_symbol=vt_symbol,
                               direction=Direction.SHORT,
                               offset=Offset.OPEN,
                               price=price,
                               volume=volume,
                               stop=stop,
                               lock=lock,
                               order_type=order_type,
                               order_time=order_time,
                               grid=grid)

    def cover(self, price: float, volume: float, stop: bool = False, lock: bool = False,
              vt_symbol: str = '', order_type: OrderType = OrderType.LIMIT,
              order_time: datetime = None, grid: CtaGrid = None):
        """
        Send cover order to close a short position.
        """
        if OrderType in [OrderType.FAK, OrderType.FOK]:
            if self.is_upper_limit(vt_symbol):
                self.write_error(u'涨停价不做FAK/FOK cover委托')
                return []
        return self.send_order(vt_symbol=vt_symbol,
                               direction=Direction.LONG,
                               offset=Offset.CLOSE,
                               price=price,
                               volume=volume,
                               stop=stop,
                               lock=lock,
                               order_type=order_type,
                               order_time=order_time,
                               grid=grid)

    def send_order(
            self,
            vt_symbol: str,
            direction: Direction,
            offset: Offset,
            price: float,
            volume: float,
            stop: bool = False,
            lock: bool = False,
            order_type: OrderType = OrderType.LIMIT,
            order_time: datetime = None,
            grid: CtaGrid = None
    ):
        """
        Send a new order.
        """
        # 兼容cta_strategy的模板，缺省不指定vt_symbol时，使用策略配置的vt_symbol
        if vt_symbol == '':
            vt_symbol = self.vt_symbol

        if not self.trading:
            return []

        vt_orderids = self.cta_engine.send_order(
            strategy=self,
            vt_symbol=vt_symbol,
            direction=direction,
            offset=offset,
            price=price,
            volume=volume,
            stop=stop,
            lock=lock,
            order_type=order_type
        )

        if order_time is None:
            order_time = datetime.now()

        for vt_orderid in vt_orderids:
            d = {
                'direction': direction,
                'offset': offset,
                'vt_symbol': vt_symbol,
                'price': price,
                'volume': volume,
                'order_type': order_type,
                'traded': 0,
                'order_time': order_time,
                'status': Status.SUBMITTING
            }
            if grid:
                d.update({'grid': grid})
                grid.order_ids.append(vt_orderid)
            self.active_orders.update({vt_orderid: d})
        if direction == Direction.LONG:
            self.entrust = 1
        elif direction == Direction.SHORT:
            self.entrust = -1
        return vt_orderids

    def cancel_order(self, vt_orderid: str):
        """
        Cancel an existing order.
        """
        if self.trading:
            return self.cta_engine.cancel_order(self, vt_orderid)

        return False

    def cancel_all(self):
        """
        Cancel all orders sent by strategy.
        """
        if self.trading:
            self.cta_engine.cancel_all(self)

    def is_upper_limit(self, symbol):
        """是否涨停"""
        tick = self.tick_dict.get(symbol, None)
        if tick is None or tick.limit_up is None or tick.limit_up == 0:
            return False
        if tick.bid_price_1 == tick.limit_up:
            return True

    def is_lower_limit(self, symbol):
        """是否跌停"""
        tick = self.tick_dict.get(symbol, None)
        if tick is None or tick.limit_down is None or tick.limit_down == 0:
            return False
        if tick.ask_price_1 == tick.limit_down:
            return True

    def write_log(self, msg: str, level: int = INFO):
        """
        Write a log message.
        """
        self.cta_engine.write_log(msg=msg, strategy_name=self.strategy_name, level=level)

    def write_error(self, msg: str):
        """write error log message"""
        self.write_log(msg=msg, level=ERROR)

    def get_engine_type(self):
        """
        Return whether the cta_engine is backtesting or live trading.
        """
        return self.cta_engine.get_engine_type()

    def load_bar(
            self,
            days: int,
            interval: Interval = Interval.MINUTE,
            callback: Callable = None,
    ):
        """
        Load historical bar data for initializing strategy.
        """
        if not callback:
            callback = self.on_bar

        self.cta_engine.load_bar(self.vt_symbol, days, interval, callback)

    def load_tick(self, days: int):
        """
        Load historical tick data for initializing strategy.
        """
        self.cta_engine.load_tick(self.vt_symbol, days, self.on_tick)

    def put_event(self):
        """
        Put an strategy data event for ui update.
        """
        if self.inited:
            self.cta_engine.put_strategy_event(self)

    def send_email(self, msg):
        """
        Send email to default receiver.
        """
        if self.inited:
            self.cta_engine.send_email(msg, self)

    def sync_data(self):
        """
        Sync strategy variables value into disk storage.
        """
        if self.trading:
            self.cta_engine.sync_strategy_data(self)


class CtaSignal(ABC):
    """"""

    def __init__(self):
        """"""
        self.signal_pos = 0

    @virtual
    def on_tick(self, tick: TickData):
        """
        Callback of new tick data update.
        """
        pass

    @virtual
    def on_bar(self, bar: BarData):
        """
        Callback of new bar data update.
        """
        pass

    def set_signal_pos(self, pos):
        """"""
        self.signal_pos = pos

    def get_signal_pos(self):
        """"""
        return self.signal_pos


class TargetPosTemplate(CtaTemplate):
    """"""
    tick_add = 1

    last_tick = None
    last_bar = None
    target_pos = 0
    vt_orderids = []

    def __init__(self, cta_engine, strategy_name, vt_symbol, setting):
        """"""
        super(TargetPosTemplate, self).__init__(
            cta_engine, strategy_name, vt_symbol, setting
        )
        self.variables.append("target_pos")

    @virtual
    def on_tick(self, tick: TickData):
        """
        Callback of new tick data update.
        """
        self.last_tick = tick

        if self.trading:
            self.trade()

    @virtual
    def on_bar(self, bar: BarData):
        """
        Callback of new bar data update.
        """
        self.last_bar = bar

    @virtual
    def on_order(self, order: OrderData):
        """
        Callback of new order data update.
        """
        vt_orderid = order.vt_orderid

        if not order.is_active() and vt_orderid in self.vt_orderids:
            self.vt_orderids.remove(vt_orderid)

    def set_target_pos(self, target_pos):
        """"""
        self.target_pos = target_pos
        self.trade()

    def trade(self):
        """"""
        self.cancel_all()

        pos_change = self.target_pos - self.pos
        if not pos_change:
            return

        long_price = 0
        short_price = 0

        if self.last_tick:
            if pos_change > 0:
                long_price = self.last_tick.ask_price_1 + self.tick_add
                if self.last_tick.limit_up:
                    long_price = min(long_price, self.last_tick.limit_up)
            else:
                short_price = self.last_tick.bid_price_1 - self.tick_add
                if self.last_tick.limit_down:
                    short_price = max(short_price, self.last_tick.limit_down)

        else:
            if pos_change > 0:
                long_price = self.last_bar.close_price + self.tick_add
            else:
                short_price = self.last_bar.close_price - self.tick_add

        if self.get_engine_type() == EngineType.BACKTESTING:
            if pos_change > 0:
                vt_orderids = self.buy(long_price, abs(pos_change))
            else:
                vt_orderids = self.short(short_price, abs(pos_change))
            self.vt_orderids.extend(vt_orderids)

        else:
            if self.vt_orderids:
                return

            if pos_change > 0:
                if self.pos < 0:
                    if pos_change < abs(self.pos):
                        vt_orderids = self.cover(long_price, pos_change)
                    else:
                        vt_orderids = self.cover(long_price, abs(self.pos))
                else:
                    vt_orderids = self.buy(long_price, abs(pos_change))
            else:
                if self.pos > 0:
                    if abs(pos_change) < self.pos:
                        vt_orderids = self.sell(short_price, abs(pos_change))
                    else:
                        vt_orderids = self.sell(short_price, abs(self.pos))
                else:
                    vt_orderids = self.short(short_price, abs(pos_change))
            self.vt_orderids.extend(vt_orderids)


class CtaProTemplate(CtaTemplate):
    """
    增强模板
    """

    idx_symbol = None  # 指数合约

    price_tick = 1  # 商品的最小价格跳动
    symbol_size = 10  # 商品得合约乘数
    margin_rate = 0.1  # 商品的保证金

    # 委托类型
    order_type = OrderType.LIMIT
    cancel_seconds = 120  # 撤单时间(秒)

    # 资金相关
    max_invest_rate = 0.1  # 最大仓位(0~1)
    max_invest_margin = 0  # 资金上限 0，不限制
    max_invest_pos = 0  # 单向头寸数量上限 0，不限制

    # 是否回测状态
    backtesting = False

    # 逻辑过程日志
    dist_fieldnames = ['datetime', 'symbol', 'volume', 'price',
                       'operation', 'signal', 'stop_price', 'target_price',
                       'long_pos', 'short_pos']

    def __init__(self, cta_engine, strategy_name, vt_symbol, setting):
        """"""
        self.position = None  # 仓位组件
        self.policy = None  # 事务执行组件
        self.gt = None  # 网格交易组件
        self.klines = {}  # K线组件字典: kline_name: kline

        self.cur_datetime = None  # 当前Tick时间
        self.cur_mi_tick = None  # 最新的主力合约tick( vt_symbol)
        self.cur_99_tick = None  # 最新得指数合约tick( idx_symbol)

        self.cur_mi_price = None  # 当前价（主力合约 vt_symbol)
        self.cur_99_price = None  # 当前价（tick时，根据tick更新，onBar回测时，根据bar.close更新)

        self.last_minute = None  # 最后的分钟,用于on_tick内每分钟处理的逻辑

        super(CtaProTemplate, self).__init__(
            cta_engine, strategy_name, vt_symbol, setting
        )

        # 增加仓位管理模块
        self.position = CtaPosition(strategy=self)

        # 增加网格持久化模块
        self.gt = CtaGridTrade(strategy=self)

        # 增加指数合约
        if 'idx_symbol' not in self.parameters:
            self.parameters.append('idx_symbol')

        if 'backtesting' not in self.parameters:
            self.parameters.append('backtesting')

    def update_setting(self, setting: dict):
        """
        Update strategy parameter wtih value in setting dict.
        """
        for name in self.parameters:
            if name in setting:
                setattr(self, name, setting[name])

        if self.idx_symbol is None:
            symbol, exchange = extract_vt_symbol(self.vt_symbol)
            self.idx_symbol = get_underlying_symbol(symbol).upper() + '99.' + exchange.value
        if self.vt_symbol != self.idx_symbol:
            self.write_log(f'指数合约:{self.idx_symbol}, 主力合约:{self.vt_symbol}')
        self.price_tick = self.cta_engine.get_price_tick(self.vt_symbol)
        self.symbol_size = self.cta_engine.get_size(self.vt_symbol)
        self.margin_rate = self.cta_engine.get_margin_rate(self.vt_symbol)

    def save_klines_to_cache(self, kline_names: list = []):
        """
        保存K线数据到缓存
        :param kline_names: 一般为self.klines的keys
        :return:
        """
        if len(kline_names) == 0:
            kline_names = list(self.klines.keys())

        # 获取保存路径
        save_path = self.cta_engine.get_data_path()
        # 保存缓存的文件名
        file_name = os.path.abspath(os.path.join(save_path, f'{self.strategy_name}_klines.pkb2'))
        with bz2.BZ2File(file_name, 'wb') as f:
            klines = {}
            for kline_name in kline_names:
                kline = self.klines.get(kline_name, None)
                # if kline:
                #    kline.strategy = None
                #    kline.cb_on_bar = None
                klines.update({kline_name: kline})
            pickle.dump(klines, f)

    def load_klines_from_cache(self, kline_names: list = []):
        """
        从缓存加载K线数据
        :param kline_names:
        :return:
        """
        if len(kline_names) == 0:
            kline_names = list(self.klines.keys())

        save_path = self.cta_engine.get_data_path()
        file_name = os.path.abspath(os.path.join(save_path, f'{self.strategy_name}_klines.pkb2'))
        try:
            last_bar_dt = None
            with bz2.BZ2File(file_name, 'rb') as f:
                klines = pickle.load(f)
                # 逐一恢复K线
                for kline_name in kline_names:
                    # 缓存的k线实例
                    cache_kline = klines.get(kline_name, None)
                    # 当前策略实例的K线实例
                    strategy_kline = self.klines.get(kline_name, None)

                    if cache_kline and strategy_kline:
                        # 临时保存当前的回调函数
                        cb_on_bar = strategy_kline.cb_on_bar
                        # 缓存实例数据 =》 当前实例数据
                        strategy_kline.__dict__.update(cache_kline.__dict__)

                        # 所有K线的最后时间
                        if last_bar_dt and strategy_kline.cur_datetime:
                            last_bar_dt = max(last_bar_dt, strategy_kline.cur_datetime)
                        else:
                            last_bar_dt = strategy_kline.cur_datetime

                        # 重新绑定k线策略与on_bar回调函数
                        strategy_kline.strategy = self
                        strategy_kline.cb_on_bar = cb_on_bar

                        self.write_log(f'恢复{kline_name}缓存数据,最新bar结束时间:{last_bar_dt}')

                self.write_log(u'加载缓存k线数据完毕')
                return last_bar_dt
        except Exception as ex:
            self.write_error(f'加载缓存K线数据失败:{str(ex)}')
        return None

    def get_klines_snapshot(self):
        """返回当前klines的切片数据"""
        try:
            d = {
                'strategy': self.strategy_name,
                'datetime': datetime.now()}
            klines = {}
            for kline_name in sorted(self.klines.keys()):
                klines.update({kline_name: self.klines.get(kline_name).get_data()})
            kline_names = list(klines.keys())
            binary_data = zlib.compress(pickle.dumps(klines))
            d.update({'kline_names': kline_names, 'klines': binary_data, 'zlib': True})
            return d
        except Exception as ex:
            self.write_error(f'获取klines切片数据失败:{str(ex)}')
            return {}

    def init_position(self):
        """
        初始化Positin
        使用网格的持久化，获取开仓状态的多空单，更新
        :return:
        """
        self.write_log(u'init_position(),初始化持仓')
        pos_symbols = set()
        if len(self.gt.up_grids) <= 0:
            self.position.short_pos = 0
            # 加载已开仓的空单数据，网格JSON
            short_grids = self.gt.load(direction=Direction.SHORT, open_status_filter=[True])
            if len(short_grids) == 0:
                self.write_log(u'没有持久化的空单数据')
                self.gt.up_grids = []

            else:
                self.gt.up_grids = short_grids
                for sg in short_grids:
                    if len(sg.order_ids) > 0 or sg.order_status:
                        self.write_log(f'重置委托状态:{sg.order_status},清除委托单：{sg.order_ids}')
                        sg.order_status = False
                        sg.order_ids = []

                    short_symbol = sg.snapshot.get('mi_symbol', self.vt_symbol)
                    pos_symbols.add(short_symbol)
                    self.write_log(u'加载持仓空单[{},价格:{}],[指数:{},价格：{}],数量:{}手'
                                   .format(short_symbol, sg.snapshot.get('open_price'),
                                           self.idx_symbol, sg.open_price, sg.volume))
                    self.position.short_pos -= sg.volume

                self.write_log(u'持久化空单，共持仓:{}手'.format(abs(self.position.short_pos)))

        if len(self.gt.dn_grids) <= 0:
            # 加载已开仓的多数据，网格JSON
            self.position.long_pos = 0
            long_grids = self.gt.load(direction=Direction.LONG, open_status_filter=[True])
            if len(long_grids) == 0:
                self.write_log(u'没有持久化的多单数据')
                self.gt.dn_grids = []
            else:
                self.gt.dn_grids = long_grids
                for lg in long_grids:

                    if len(lg.order_ids) > 0 or lg.order_status:
                        self.write_log(f'重置委托状态:{lg.order_status},清除委托单：{lg.order_ids}')
                        lg.order_status = False
                        lg.order_ids = []
                    # lg.type = self.line.name
                    long_symbol = lg.snapshot.get('mi_symbol', self.vt_symbol)
                    pos_symbols.add(long_symbol)

                    self.write_log(u'加载持仓多单[{},价格:{}],[指数{},价格:{}],数量:{}手'
                                   .format(lg.snapshot.get('miSymbol'), lg.snapshot.get('open_price'),
                                           self.idx_symbol, lg.open_price, lg.volume))
                    self.position.long_pos += lg.volume

                self.write_log(f'持久化多单，共持仓:{self.position.long_pos}手')

        self.position.pos = self.position.long_pos + self.position.short_pos

        self.write_log(u'{}加载持久化数据完成，多单:{}，空单:{},共:{}手'
                       .format(self.strategy_name,
                               self.position.long_pos,
                               abs(self.position.short_pos),
                               self.position.pos))
        self.pos = self.position.pos
        self.gt.save()
        self.display_grids()

        if not self.backtesting:
            pos_symbols.add(self.vt_symbol)
            pos_symbols.add(self.idx_symbol)
            # 如果持仓的合约，不在self.vt_symbol中，需要订阅
            for symbol in list(pos_symbols):
                self.write_log(f'新增订阅合约:{symbol}')
                self.cta_engine.subscribe_symbol(strategy_name=self.strategy_name, vt_symbol=symbol)

    def get_positions(self):
        """
        获取策略当前持仓(重构，使用主力合约）
        :return: [{'vt_symbol':symbol,'direction':direction,'volume':volume]
        """
        if not self.position:
            return []
        pos_list = []

        if self.position.long_pos > 0:
            for g in self.gt.get_opened_grids(direction=Direction.LONG):
                vt_symbol = g.snapshot.get('mi_symbol', self.vt_symbol)
                open_price = g.snapshot.get('open_price', g.open_price)
                pos_list.append({'vt_symbol': vt_symbol,
                                 'direction': 'long',
                                 'volume': g.volume - g.traded_volume,
                                 'price': open_price})

        if abs(self.position.short_pos) > 0:
            for g in self.gt.get_opened_grids(direction=Direction.SHORT):
                vt_symbol = g.snapshot.get('mi_symbol', self.vt_symbol)
                open_price = g.snapshot.get('open_price', g.open_price)
                pos_list.append({'vt_symbol': vt_symbol,
                                 'direction': 'short',
                                 'volume': abs(g.volume - g.traded_volume),
                                 'price': open_price})

        if self.cur_datetime and (datetime.now() - self.cur_datetime).total_seconds() < 10:
            self.write_log(u'当前持仓:{}'.format(pos_list))
        return pos_list

    def tns_cancel_logic(self, dt, force=False):
        "撤单逻辑"""
        if len(self.active_orders) < 1:
            self.entrust = 0
            return

        for vt_orderid in list(self.active_orders.keys()):
            order_info = self.active_orders.get(vt_orderid)
            if order_info.get('status', None) in [Status.CANCELLED, Status.REJECTED]:
                self.active_orders.pop(vt_orderid, None)
                continue

            order_time = order_info.get('order_time')
            over_ms = (dt - order_time).total_seconds()
            if (over_ms > self.cancel_seconds) \
                    or force:  # 超过设置的时间还未成交
                self.write_log(f'{dt}, 超时{over_ms}秒未成交，取消委托单：{order_info}')

                if self.cancel_order(vt_orderid):
                    order_info.update({'status': Status.CANCELLING})
                else:
                    order_info.update({'status': Status.CANCELLED})

        if len(self.active_orders) < 1:
            self.entrust = 0

    def tns_switch_long_pos(self):
        """切换合约，从持仓的非主力合约，切换至主力合约"""

        if self.entrust != 0 and self.position.long_pos == 0:
            return

        if self.cur_mi_price == 0:
            return

        none_mi_grid = None
        none_mi_symbol = None

        # 找出非主力合约的持仓网格
        for g in self.gt.get_opened_grids(direction=Direction.LONG):
            none_mi_symbol = g.snapshot.get('mi_symbol')
            if none_mi_symbol is None or none_mi_symbol == self.vt_symbol:
                # 如果持仓的合约，跟策略配置的vt_symbol一致，则不处理
                continue
            if not g.open_status or g.order_status or g.volume - g.traded_volume <= 0:
                continue
            none_mi_grid = g
            if g.traded_volume > 0 and g.volume - g.traded_volume > 0:
                g.volume -= g.traded_volume
                g.traded_volume = 0
            break
        if none_mi_grid is None:
            return

        # 找到行情中非主力合约/主力合约的最新价
        none_mi_tick = self.tick_dict.get(none_mi_symbol)
        mi_tick = self.tick_dict.get(self.vt_symbol, None)
        if none_mi_tick is None or mi_tick is None:
            return

        # 如果涨停价，不做卖出
        if self.is_upper_limit(none_mi_symbol) or self.is_upper_limit(self.vt_symbol):
            return
        none_mi_price = max(none_mi_tick.last_price, none_mi_tick.bid_price_1)

        grid = copy(none_mi_grid)

        # 委托卖出非主力合约
        vt_orderids = self.sell(price=none_mi_price,
                                volume=none_mi_grid.volume,
                                vt_symbol=none_mi_symbol,
                                order_type=self.order_type,
                                grid=none_mi_grid)
        if len(vt_orderids) > 0:
            self.write_log(f'切换合约,委托卖出非主力合约{none_mi_symbol}持仓:{none_mi_grid.volume}')

            # 添加买入主力合约
            grid.id = str(uuid.uuid1())
            grid.snapshot.update({'mi_symbol': self.vt_symbol, 'open_price': self.cur_mi_price})
            self.gt.dn_grids.append(grid)

            vt_orderids = self.buy(price=self.cur_mi_price + 5 * self.price_tick,
                                   volume=grid.volume,
                                   vt_symbol=self.vt_symbol,
                                   order_type=self.order_type,
                                   grid=grid)
            if len(vt_orderids) > 0:
                self.write_log(u'切换合约,委托买入主力合约:{},价格:{},数量:{}'
                               .format(self.vt_symbol, self.cur_mi_price, grid.volume))
                self.gt.save()
            else:
                self.write_error(f'委托买入主力合约:{self.vt_symbol}失败')
        else:
            self.write_error(f'委托卖出非主力合约:{none_mi_symbol}失败')

    def tns_switch_short_pos(self):
        """切换合约，从持仓的非主力合约，切换至主力合约"""
        if self.entrust != 0 and self.position.short_pos == 0:
            return

        if self.cur_mi_price == 0:
            return

        none_mi_grid = None
        none_mi_symbol = None

        # 找出非主力合约的持仓网格
        for g in self.gt.get_opened_grids(direction=Direction.SHORT):
            none_mi_symbol = g.snapshot.get('mi_symbol')
            if none_mi_symbol is None or none_mi_symbol == self.vt_symbol:
                continue
            if not g.open_status or g.order_status or g.volume - g.traded_volume <= 0:
                continue
            none_mi_grid = g
            if g.traded_volume > 0 and g.volume - g.traded_volume > 0:
                g.volume -= g.traded_volume
                g.traded_volume = 0
            break

        # 找不到与主力合约不一致的持仓网格
        if none_mi_grid is None:
            return

        # 找到行情中非主力合约的最新价
        none_mi_tick = self.tick_dict.get(none_mi_symbol)
        mi_tick = self.tick_dict.get(self.vt_symbol, None)
        if none_mi_tick is None or mi_tick is None:
            return

        # 如果跌停价，不做cover
        if self.is_lower_limit(none_mi_symbol) or self.is_lower_limit(self.vt_symbol):
            return
        none_mi_price = max(none_mi_tick.last_price, none_mi_tick.bid_price_1)

        grid = copy(none_mi_grid)
        # 委托平空非主力合约
        vt_orderids = self.cover(price=none_mi_price,
                                 volume=none_mi_grid.volume,
                                 vt_symbol=self.vt_symbol,
                                 order_type=self.order_type,
                                 grid=none_mi_grid)
        if len(vt_orderids) > 0:
            self.write_log(f'委托平空非主力合约{none_mi_symbol}持仓:{none_mi_grid.volume}')

            # 添加卖出主力合约
            grid.id = str(uuid.uuid1())
            grid.snapshot.update({'mi_symbol': self.vt_symbol, 'open_price': self.cur_mi_price})
            self.gt.up_grids.append(grid)
            vt_orderids = self.short(price=self.cur_mi_price,
                                     volume=grid.volume,
                                     vt_symbol=self.vt_symbol,
                                     order_type=self.order_type,
                                     grid=grid)
            if len(vt_orderids) > 0:
                self.write_log(f'委托做空主力合约:{self.vt_symbol},价格:{self.cur_mi_price},数量:{grid.volume}')
                self.gt.save()
            else:
                self.write_error(f'委托做空主力合约:{self.vt_symbol}失败')
        else:
            self.write_error(f'委托平空非主力合约:{none_mi_symbol}失败')

    def display_grids(self):
        """更新网格显示信息"""
        if not self.inited:
            return

        up_grids_info = self.gt.to_str(direction=Direction.SHORT)
        if len(self.gt.up_grids) > 0:
            self.write_log(up_grids_info)

        dn_grids_info = self.gt.to_str(direction=Direction.LONG)
        if len(self.gt.dn_grids) > 0:
            self.write_log(dn_grids_info)

    def display_tns(self):
        """显示事务的过程记录=》 log"""
        if not self.inited:
            return
        self.write_log(u'{} 当前指数{}价格:{},当前主力{}价格：{}'
                       .format(self.cur_datetime,
                               self.idx_symbol, self.cur_99_price,
                               self.vt_symbol, self.cur_mi_price))
        if hasattr(self, 'policy'):
            policy = getattr(self, 'policy')
            op = getattr(policy, 'to_json', None)
            if callable(op):
                self.write_log(u'当前Policy:{}'.format(policy.to_json()))

    def save_dist(self, dist_data):
        """
        保存策略逻辑过程记录=》 csv文件按
        :param dist_data:
        :return:
        """
        if self.backtesting:
            save_path = self.cta_engine.get_logs_path()
        else:
            save_path = self.cta_engine.get_data_path()
        try:
            if self.position and 'long_pos' not in dist_data:
                dist_data.update({'long_pos': self.position.long_pos})
            if self.position and 'short_pos' not in dist_data:
                dist_data.update({'short_pos': self.position.short_pos})

            file_name = os.path.abspath(os.path.join(save_path, f'{self.strategy_name}_dist.csv'))
            append_data(file_name=file_name, dict_data=dist_data, field_names=self.dist_fieldnames)
        except Exception as ex:
            self.write_error(u'save_dist 异常:{} {}'.format(str(ex), traceback.format_exc()))

    def save_tns(self, tns_data):
        """
        保存多空事务记录=》csv文件,便于后续分析
        :param tns_data:
        :return:
        """
        if self.backtesting:
            save_path = self.cta_engine.get_logs_path()
        else:
            save_path = self.cta_engine.get_data_path()

        try:
            file_name = os.path.abspath(os.path.join(save_path, f'{self.strategy_name}_tns.csv'))
            append_data(file_name=file_name, dict_data=tns_data)
        except Exception as ex:
            self.write_error(u'save_tns 异常:{} {}'.format(str(ex), traceback.format_exc()))

    def send_wechat(self, msg: str):
        """实盘时才发送微信"""
        if self.backtesting:
            return
        self.cta_engine.send_wechat(msg=msg, strategy=self)


class CtaProFutureTemplate(CtaProTemplate):
    """期货交易增强版模板"""

    activate_fak = False
    activate_today_lock = False

    def __init__(self, cta_engine, strategy_name, vt_symbol, setting):
        """"""
        super().__init__(cta_engine, strategy_name, vt_symbol, setting)

        self.parameters.append('activate_fak')
        self.parameters.append('activate_today_lock')

    def update_setting(self, setting: dict):
        """更新配置参数"""
        super().update_setting(setting)

        # 实盘时，判断是否激活使用FAK模式
        if not self.backtesting:
            if self.activate_fak:
                self.order_type = OrderType.FAK

    def load_policy(self):
        """加载policy"""
        if self.policy:
            self.write_log(u'load_policy(),初始化Policy')

            self.policy.load()
            self.write_log(u'Policy:{}'.format(self.policy.to_json()))

    def on_start(self):
        """启动策略（必须由用户继承实现）"""
        self.write_log(u'启动')
        self.trading = True
        self.put_event()

    # ----------------------------------------------------------------------
    def on_stop(self):
        """停止策略（必须由用户继承实现）"""
        self.active_orders.clear()
        self.pos = 0
        self.entrust = 0

        self.write_log(u'停止')
        self.put_event()

    def on_trade(self, trade: TradeData):
        """交易更新"""
        self.write_log(u'{},交易更新:{},当前持仓：{} '
                       .format(self.cur_datetime,
                               trade.__dict__,
                               self.position.pos))

        dist_record = dict()
        if self.backtesting:
            dist_record['datetime'] = trade.time
        else:
            dist_record['datetime'] = ' '.join([self.cur_datetime.strftime('%Y-%m-%d'), trade.time])
        dist_record['volume'] = trade.volume
        dist_record['price'] = trade.price
        dist_record['symbol'] = trade.vt_symbol

        if trade.direction == Direction.LONG and trade.offset == Offset.OPEN:
            dist_record['operation'] = 'buy'
            self.position.open_pos(trade.direction, volume=trade.volume)
            dist_record['long_pos'] = self.position.long_pos
            dist_record['short_pos'] = self.position.short_pos

        if trade.direction == Direction.SHORT and trade.offset == Offset.OPEN:
            dist_record['operation'] = 'short'
            self.position.open_pos(trade.direction, volume=trade.volume)
            dist_record['long_pos'] = self.position.long_pos
            dist_record['short_pos'] = self.position.short_pos

        if trade.direction == Direction.LONG and trade.offset != Offset.OPEN:
            dist_record['operation'] = 'cover'
            self.position.close_pos(trade.direction, volume=trade.volume)
            dist_record['long_pos'] = self.position.long_pos
            dist_record['short_pos'] = self.position.short_pos

        if trade.direction == Direction.SHORT and trade.offset != Offset.OPEN:
            dist_record['operation'] = 'sell'
            self.position.close_pos(trade.direction, volume=trade.volume)
            dist_record['long_pos'] = self.position.long_pos
            dist_record['short_pos'] = self.position.short_pos

        self.save_dist(dist_record)
        self.pos = self.position.pos

    def fix_order(self, order: OrderData):
        """修正order被拆单得情况"""
        order_info = self.active_orders.get(order.vt_orderid, None)
        if order_info:
            volume = order_info.get('volume')
            if volume != order.volume:
                self.write_log(f'调整{order.vt_orderid} volume:{volume}=>{order.volume}')
                order_info.update({'volume': order.volume})

    def on_order(self, order: OrderData):
        """报单更新"""
        # 未执行的订单中，存在是异常，删除
        self.write_log(u'{}报单更新，{}'.format(self.cur_datetime, order.__dict__))

        # 修正order被拆单得情况"
        self.fix_order(order)

        if order.vt_orderid in self.active_orders:

            if order.volume == order.traded and order.status in [Status.ALLTRADED]:
                self.on_order_all_traded(order)

            elif order.offset == Offset.OPEN and order.status in [Status.CANCELLED]:
                # 开仓委托单被撤销
                self.on_order_open_canceled(order)

            elif order.offset != Offset.OPEN and order.status in [Status.CANCELLED]:
                # 平仓委托单被撤销
                self.on_order_close_canceled(order)

            elif order.status == Status.REJECTED:
                if order.offset == Offset.OPEN:
                    self.write_error(u'{}委托单开{}被拒，price:{},total:{},traded:{}，status:{}'
                                     .format(order.vt_symbol, order.direction, order.price, order.volume,
                                             order.traded, order.status))
                    self.on_order_open_canceled(order)
                else:
                    self.write_error(u'OnOrder({})委托单平{}被拒，price:{},total:{},traded:{}，status:{}'
                                     .format(order.vt_symbol, order.direction, order.price, order.volume,
                                             order.traded, order.status))
                    self.on_order_close_canceled(order)
            else:
                self.write_log(u'委托单未完成,total:{},traded:{},tradeStatus:{}'
                               .format(order.volume, order.traded, order.status))
        else:
            self.write_error(u'委托单{}不在策略的未完成订单列表中:{}'.format(order.vt_orderid, self.active_orders))

    def on_order_all_traded(self, order: OrderData):
        """
        订单全部成交
        :param order:
        :return:
        """
        self.write_log(u'{},委托单:{}全部完成'.format(order.time, order.vt_orderid))
        order_info = self.active_orders[order.vt_orderid]

        # 通过vt_orderid，找到对应的网格
        grid = order_info.get('grid', None)
        if grid is not None:
            # 移除当前委托单
            if order.vt_orderid in grid.order_ids:
                grid.order_ids.remove(order.vt_orderid)

            # 网格的所有委托单已经执行完毕
            if len(grid.order_ids) == 0:
                grid.order_status = False
                grid.traded_volume = 0

                # 平仓完毕（cover， sell）
                if order.offset != Offset.OPEN:
                    grid.open_status = False
                    grid.close_status = True

                    self.write_log(f'{grid.direction.value}单已平仓完毕,order_price:{order.price}'
                                   + f',volume:{order.volume}')

                    self.write_log(f'移除网格:{grid.to_json()}')
                    self.gt.remove_grids_by_ids(direction=grid.direction, ids=[grid.id])

                # 开仓完毕( buy, short)
                else:
                    grid.open_status = True
                    self.write_log(f'{grid.direction.value}单已开仓完毕,order_price:{order.price}'
                                   + f',volume:{order.volume}')

                # 网格的所有委托单部分执行完毕
            else:
                old_traded_volume = grid.traded_volume
                grid.traded_volume += order.volume

                self.write_log(f'{grid.direction.value}单部分{order.offset}仓，'
                               + f'网格volume:{grid.volume}, traded_volume:{old_traded_volume}=>{grid.traded_volume}')

                self.write_log(f'剩余委托单号:{grid.order_ids}')

        # 在策略得活动订单中，移除
        self.active_orders.pop(order.vt_orderid, None)

    def on_order_open_canceled(self, order: OrderData):
        """
        委托开仓单撤销
        如果是FAK模式，重新修改价格，再提交
        FAK用于实盘，需要增加涨跌停判断
        :param order:
        :return:
        """
        self.write_log(u'委托开仓单撤销:{}'.format(order.__dict__))

        if not self.trading:
            if not self.backtesting:
                self.write_error(u'当前不允许交易')
            return

        if order.vt_orderid not in self.active_orders:
            self.write_error(u'{}不在未完成的委托单中{}。'.format(order.vt_orderid, self.active_orders))
            return

        # 直接更新“未完成委托单”，更新volume,retry次数
        old_order = self.active_orders[order.vt_orderid]
        self.write_log(u'{} 委托信息:{}'.format(order.vt_orderid, old_order))
        old_order['traded'] = order.traded
        order_vt_symbol = copy(old_order['vt_symbol'])
        order_volume = old_order['volume'] - old_order['traded']
        if order_volume <= 0:
            msg = u'{} {}{}需重新开仓数量为{}，不再开仓' \
                .format(self.strategy_name,
                        order.vt_orderid,
                        order_vt_symbol,
                        order_volume)
            self.write_error(msg)

            self.write_log(u'移除:{}'.format(order.vt_orderid))
            self.active_orders.pop(order.vt_orderid, None)
            return

        order_price = old_order['price']
        order_type = old_order.get('order_type', OrderType.LIMIT)
        order_retry = old_order.get('retry', 0)
        grid = old_order.get('grid', None)
        if order_retry > 20:
            # 这里超过20次尝试失败后，不再尝试,发出告警信息
            msg = u'{}  {}/{}手， 重试开仓次数{}>20' \
                .format(self.strategy_name,
                        order_vt_symbol,
                        order_volume,
                        order_retry)
            self.write_error(msg)
            self.send_wechat(msg)

            if grid:
                if order.vt_orderid in grid.order_ids:
                    grid.order_ids.remove(order.vt_orderid)

                # 网格的所有委托单已经执行完毕
                if len(grid.order_ids) == 0:
                    grid.order_status = False

                self.gt.save()
                self.write_log(u'网格信息更新:{}'.format(grid.__dict__))

            self.write_log(u'移除:{}'.format(order.vt_orderid))
            self.active_orders.pop(order.vt_orderid, None)
            return

        order_retry += 1

        # FAK 重新开单
        if old_order['direction'] == Direction.LONG and order_type == OrderType.FAK:
            # 更新网格交易器

            self.write_log(u'FAK模式，需要重新发送buy委托.grid:{}'.format(grid.__dict__))
            # 更新委托平仓价
            buy_price = max(self.cur_mi_tick.ask_price_1, self.cur_mi_tick.last_price, order_price) + self.price_tick
            # 不能超过涨停价
            if self.cur_mi_tick.limit_up > 0 and buy_price > self.cur_mi_tick.limit_up:
                buy_price = self.cur_mi_tick.limit_up

            if self.is_upper_limit(self.vt_symbol):
                self.write_log(u'{}涨停，不做buy'.format(self.vt_symbol))
                return

            # 发送委托
            vt_orderids = self.buy(price=buy_price,
                                   volume=order_volume,
                                   vt_symbol=self.vt_symbol,
                                   order_type=OrderType.FAK,
                                   order_time=self.cur_datetime,
                                   grid=grid)
            if not vt_orderids:
                self.write_error(u'重新提交{} {}手开多单,价格：{}，失败'.
                                 format(self.vt_symbol, order_volume, buy_price))
                return

            # 更新retry的次数
            for vt_orderid in vt_orderids:
                info = self.active_orders.get(vt_orderid, None)
                info.update({'retry': order_retry})

            self.gt.save()
            # 删除旧的委托记录
            self.write_log(u'移除旧的委托记录:{}'.format(order.vt_orderid))
            self.active_orders.pop(order.vt_orderid, None)

        elif old_order['direction'] == Direction.SHORT and order_type == OrderType.FAK:

            self.write_log(u'FAK模式，需要重新发送short委托.grid:{}'.format(grid.__dict__))
            short_price = min(self.cur_mi_tick.bid_price_1, self.cur_mi_tick.last_price, order_price) - self.price_tick
            # 不能超过跌停价
            if self.cur_mi_tick.limit_down > 0 and short_price < self.cur_mi_tick.limit_down:
                short_price = self.cur_mi_tick.limit_down

            if self.is_lower_limit(self.vt_symbol):
                self.write_log(u'{}跌停，不做short'.format(self.vt_symbol))
                return

            # 发送委托
            vt_orderids = self.short(price=short_price,
                                     volume=order_volume,
                                     vt_symbol=self.vt_symbol,
                                     order_type=OrderType.FAK,
                                     order_time=self.cur_datetime,
                                     grid=grid)

            if not vt_orderids:
                self.write_error(
                    u'重新提交{} {}手开空单,价格:{}, 失败'.format(self.vt_symbol, order_volume, short_price))
                return

            # 更新retry的次数
            for vt_orderid in vt_orderids:
                info = self.active_orders.get(vt_orderid, None)
                info.update({'retry': order_retry})

            self.gt.save()
            # 删除旧的委托记录
            self.write_log(u'移除旧的委托记录:{}'.format(order.vt_orderid))
            self.active_orders.pop(order.vt_orderid, None)
        else:
            pre_status = old_order.get('status', Status.NOTTRADED)
            old_order.update({'status': Status.CANCELLED})
            self.write_log(u'委托单状态:{}=>{}'.format(pre_status, old_order.get('status')))
            if grid:
                if order.vt_orderid in grid.order_ids:
                    grid.order_ids.remove(order.vt_orderid)

                if not grid.order_ids:
                    grid.order_status = False

                self.gt.save()
            self.active_orders.update({order.vt_orderid: old_order})

        self.display_grids()

    def on_order_close_canceled(self, order: OrderData):
        """委托平仓单撤销"""
        self.write_log(u'委托平仓单撤销:{}'.format(order.__dict__))

        if order.vt_orderid not in self.active_orders:
            self.write_error(u'{}不在未完成的委托单中:{}。'.format(order.vt_orderid, self.active_orders))
            return

        if not self.trading:
            self.write_error(u'当前不允许交易')
            return

        # 直接更新“未完成委托单”，更新volume,Retry次数
        old_order = self.active_orders[order.vt_orderid]
        self.write_log(u'{} 订单信息:{}'.format(order.vt_orderid, old_order))
        old_order['traded'] = order.traded
        # order_time = old_order['order_time']
        order_symbol = copy(old_order['symbol'])
        order_volume = old_order['volume'] - old_order['traded']
        if order_volume <= 0:
            msg = u'{} {}{}重新平仓数量为{}，不再平仓' \
                .format(self.strategy_name, order.vt_orderid, order_symbol, order_volume)
            self.write_error(msg)
            self.send_wechat(msg)
            self.write_log(u'活动订单移除:{}'.format(order.vt_orderid))
            self.active_orders.pop(order.vt_orderid, None)
            return

        order_price = old_order['price']
        order_type = old_order.get('order_type', OrderType.LIMIT)
        order_retry = old_order['retry']
        grid = old_order.get('grid', None)
        if order_retry > 20:
            msg = u'{} 平仓撤单 {}/{}手， 重试平仓次数{}>20' \
                .format(self.strategy_name, order_symbol, order_volume, order_retry)
            self.write_error(msg)
            self.send_wechat(msg)
            if grid:
                if order.vt_orderid in grid.order_ids:
                    grid.order_ids.remove(order.vt_orderid)
                if not grid.order_ids:
                    grid.order_status = False
                self.gt.save()
                self.write_log(u'更新网格=>{}'.format(grid.__dict__))

            self.write_log(u'移除活动订单:{}'.format(order.vt_orderid))
            self.active_orders.pop(order.vt_orderid, None)
            return

        order_retry += 1

        if old_order['direction'] == Direction.LONG and order_type == OrderType.FAK:
            self.write_log(u'FAK模式，需要重新发送cover委托.grid:{}'.format(grid.__dict__))
            # 更新委托平仓价
            cover_tick = self.tick_dict.get(order_symbol, self.cur_mi_tick)
            cover_price = max(cover_tick.ask_price_1, cover_tick.last_price, order_price) + self.price_tick
            # 不能超过涨停价
            if cover_tick.limit_up > 0 and cover_price > cover_tick.limit_up:
                cover_price = cover_tick.limit_up

            if self.is_upper_limit(order_symbol):
                self.write_log(u'{}涨停，不做cover'.format(order_symbol))
                return

            # 发送委托
            vt_orderids = self.cover(price=cover_price,
                                     volume=order_volume,
                                     vt_symbol=order_symbol,
                                     order_type=OrderType.FAK,
                                     order_time=self.cur_datetime,
                                     grid=grid)
            if not vt_orderids:
                self.write_error(u'重新提交{} {}手平空单{}失败'.format(order_symbol, order_volume, cover_price))
                return

            for vt_orderid in vt_orderids:
                info = self.active_orders.get(vt_orderid)
                info.update({'retry': order_retry})

            self.gt.save()
            self.write_log(u'移除活动订单:{}'.format(order.vt_orderid))
            self.active_orders.pop(order.vt_orderi, None)

        elif old_order['direction'] == Direction.SHORT and order_type == OrderType.FAK:
            self.write_log(u'FAK模式，需要重新发送sell委托.grid:{}'.format(grid.__dict__))
            sell_tick = self.tick_dict.get(order_symbol, self.cur_mi_tick)
            sell_price = min(sell_tick.bid_price_1, sell_tick.last_price, order_price) - self.price_tick

            # 不能超过跌停价
            if sell_tick.limit_down > 0 and sell_price < sell_tick.limit_down:
                sell_price = sell_tick.limit_down

            if self.is_lower_limit(order_symbol):
                self.write_log(u'{}涨停，不做sell'.format(order_symbol))
                return

            # 发送委托
            vt_orderids = self.sell(price=sell_price,
                                    volume=order_volume,
                                    vt_symbol=order_symbol,
                                    order_type=OrderType.FAK,
                                    order_time=self.cur_datetime,
                                    grid=grid)

            if not vt_orderids:
                self.write_error(u'重新提交{} {}手平多单{}失败'.format(order_symbol, order_volume, sell_price))
                return

            for vt_orderid in vt_orderids:
                info = self.active_orders.get(vt_orderid)
                info.update({'retry': order_retry})

            self.gt.save()

            self.write_log(u'移除活动订单:{}'.format(order.vt_orderid))
            self.active_orders.pop(order.vt_orderid, None)

        else:
            pre_status = old_order.get('status', Status.NOTTRADED)
            old_order.update({'status': Status.CANCELLED})
            self.write_log(u'委托单状态:{}=>{}'.format(pre_status, old_order.get('status')))
            if grid:
                if order.vt_orderid in grid.order_ids:
                    grid.order_ids.remove(order.vt_orderid)
                if len(grid.order_ids) == 0:
                    grid.order_status = False
                self.gt.save()
            self.active_orders.update({order.vt_orderid: old_order})

        self.display_grids()

    def on_stop_order(self, stop_order: StopOrder):
        self.write_log(f'停止单触发:{stop_order.__dict__}')

    def cancel_all_orders(self):
        """
        重载撤销所有正在进行得委托
        :return:
        """
        self.write_log(u'撤销所有正在进行得委托')
        self.tns_cancel_logic(dt=datetime.now(), force=True, reopen=False)

    def tns_cancel_logic(self, dt, force=False, reopen=False):
        "撤单逻辑"""
        if len(self.active_orders) < 1:
            self.entrust = 0
            return

        canceled_ids = []

        for vt_orderid in list(self.active_orders.keys()):
            order_info = self.active_orders[vt_orderid]
            order_vt_symbol = order_info.get('vt_symbol', self.vt_symbol)
            order_time = order_info['order_time']
            order_volume = order_info['volume'] - order_info['traded']
            # order_price = order_info['price']
            # order_direction = order_info['direction']
            # order_offset = order_info['offset']
            order_grid = order_info['grid']
            order_status = order_info.get('status', Status.NOTTRADED)
            order_type = order_info.get('order_type', OrderType.LIMIT)
            over_seconds = (dt - order_time).total_seconds()

            # 只处理未成交的限价委托单
            if order_status in [Status.NOTTRADED] and (order_type == OrderType.LIMIT or '.SPD' in order_vt_symbol):
                if over_seconds > self.cancel_seconds or force:  # 超过设置的时间还未成交
                    self.write_log(u'超时{}秒未成交，取消委托单：vt_orderid:{},order:{}'
                                   .format(over_seconds, vt_orderid, order_info))
                    order_info.update({'status': Status.CANCELING})
                    self.active_orders.update({vt_orderid: order_info})
                    ret = self.cancel_order(str(vt_orderid))
                    if not ret:
                        self.write_log(u'撤单失败,更新状态为撤单成功')
                        order_info.update({'status': Status.CANCELLED})
                        self.active_orders.update({vt_orderid: order_info})

                continue

            # 处理状态为‘撤销’的委托单
            elif order_status == Status.CANCELLED:
                self.write_log(u'委托单{}已成功撤单，删除{}'.format(vt_orderid, order_info))
                canceled_ids.append(vt_orderid)

                if reopen:
                    # 撤销的委托单，属于开仓类，需要重新委托
                    if order_info['offset'] == Offset.OPEN:
                        self.write_log(u'超时撤单后，重新开仓')
                        # 开空委托单
                        if order_info['direction'] == Direction.SHORT:
                            short_price = self.cur_mi_price - self.price_tick
                            if order_grid.volume != order_volume and order_volume > 0:
                                self.write_log(
                                    u'网格volume:{},order_volume:{}不一致，修正'.format(order_grid.volume, order_volume))
                                order_grid.volume = order_volume

                            self.write_log(u'重新提交{}开空委托,开空价{}，v:{}'.format(order_vt_symbol, short_price, order_volume))
                            vt_orderids = self.short(price=short_price,
                                                     volume=order_volume,
                                                     vt_symbol=order_vt_symbol,
                                                     order_type=order_type,
                                                     order_time=self.cur_datetime,
                                                     grid=order_grid)

                            if len(vt_orderids) > 0:
                                self.write_log(u'委托成功，orderid:{}'.format(vt_orderids))
                                order_grid.snapshot.update({'open_price': short_price})
                            else:
                                self.write_error(u'撤单后，重新委托开空仓失败')
                        else:
                            buy_price = self.cur_mi_price + self.price_tick
                            if order_grid.volume != order_volume and order_volume > 0:
                                self.write_log(
                                    u'网格volume:{},order_volume:{}不一致，修正'.format(order_grid.volume, order_volume))
                                order_grid.volume = order_volume

                            self.write_log(u'重新提交{}开多委托,开多价{}，v:{}'.format(order_vt_symbol, buy_price, order_volume))
                            vt_orderids = self.buy(price=buy_price,
                                                   volume=order_volume,
                                                   vt_symbol=order_vt_symbol,
                                                   order_type=order_type,
                                                   order_time=self.cur_datetime,
                                                   grid=order_grid)

                            if len(vt_orderids) > 0:
                                self.write_log(u'委托成功，orderids:{}'.format(vt_orderids))
                                order_grid.snapshot.update({'open_price': buy_price})
                            else:
                                self.write_error(u'撤单后，重新委托开多仓失败')
                    else:
                        # 属于平多委托单
                        if order_info['direction'] == Direction.SHORT:
                            sell_price = self.cur_mi_price - self.price_tick
                            self.write_log(u'重新提交{}平多委托,{}，v:{}'.format(order_vt_symbol, sell_price, order_volume))
                            vt_orderids = self.sell(price=sell_price,
                                                    volume=order_volume,
                                                    vt_symbol=order_vt_symbol,
                                                    order_type=order_type,
                                                    order_time=self.cur_datetime,
                                                    grid=order_grid)
                            if len(vt_orderids) > 0:
                                self.write_log(u'委托成功，orderids:{}'.format(vt_orderids))
                            else:
                                self.write_error(u'撤单后，重新委托平多仓失败')
                        # 属于平空委托单
                        else:
                            cover_price = self.cur_mi_price + self.price_tick
                            self.write_log(u'重新提交{}平空委托,委托价{}，v:{}'.format(order_vt_symbol, cover_price, order_volume))
                            vt_orderids = self.cover(price=cover_price,
                                                     volume=order_volume,
                                                     vt_symbol=order_vt_symbol,
                                                     order_type=order_type,
                                                     order_time=self.cur_datetime,
                                                     grid=order_grid)
                            if len(vt_orderids) > 0:
                                self.write_log(u'委托成功，orderids:{}'.format(vt_orderids))
                            else:
                                self.write_error(u'撤单后，重新委托平空仓失败')
                else:
                    if order_info['offset'] == Offset.OPEN \
                            and order_grid \
                            and len(order_grid.order_ids) == 0 \
                            and order_grid.traded_volume == 0:
                        self.write_log(u'移除委托网格{}'.format(order_grid.__dict__))
                        order_info['grid'] = None
                        self.gt.remove_grids_by_ids(direction=order_grid.direction, ids=[order_grid.id])

        # 删除撤单的订单
        for vt_orderid in canceled_ids:
            self.write_log(u'删除orderID:{0}'.format(vt_orderid))
            self.active_orders.pop(vt_orderid, None)

        if len(self.active_orders) == 0:
            self.entrust = 0

    def tns_close_long_pos(self, grid):
        """
        事务平多单仓位
        1.来源自止损止盈平仓
        逻辑: 如果当前账号昨仓满足平仓数量,直接平仓,如果不满足,则创建锁仓网格.
        :param 平仓网格
        :return:
        """
        self.write_log(u'执行事务平多仓位:{}'.format(grid.to_json()))

        # 平仓网格得合约
        sell_symbol = grid.snapshot.get('mi_symbol', self.vt_symbol)
        # 从cta engine获取当前账号中，sell_symbol的持仓情况
        grid_pos = self.cta_engine.get_position_holding(vt_symbol=sell_symbol)
        if grid_pos is None:
            self.write_error(u'无法获取{}得持仓信息'.format(sell_symbol))
            return False

        # 不需要日内锁仓，或者昨仓可以满足,发出委托卖出单
        if (grid_pos.long_yd >= grid.volume > 0 and grid_pos.long_td == 0 and grid_pos.short_td == 0) \
                or not self.activate_today_lock:
            if self.activate_today_lock:
                self.write_log(u'昨仓多单:{},没有今仓,满足条件,直接平昨仓'.format(grid_pos.long_yd))

            sell_price = self.cta_engine.get_price(sell_symbol)
            if sell_price is None:
                self.write_error(f'暂时不能获取{sell_symbol}价格，不能平仓')
                return False

            # 发出平多委托
            if grid.traded_volume > 0:
                grid.volume -= grid.traded_volume
                grid.traded_volume = 0

            vt_orderids = self.sell(price=sell_price,
                                    volume=grid.volume,
                                    vt_symbol=sell_symbol,
                                    order_type=self.order_type,
                                    order_time=self.cur_datetime,
                                    grid=grid)
            if len(vt_orderids) == 0:
                self.write_error(u'多单平仓委托失败')
                return False
            else:
                self.write_log(u'多单平仓委托成功，编号:{}'.format(vt_orderids))
                return True

        # 当前没有昨仓,采用锁仓处理
        else:
            self.write_log(u'昨仓多单:{}不满足条件,创建对锁仓'.format(grid_pos.longYd))
            dist_record = dict()
            dist_record['datetime'] = self.cur_datetime
            dist_record['symbol'] = sell_symbol
            dist_record['price'] = self.cur_mi_price
            dist_record['volume'] = grid.volume
            dist_record['operation'] = 'add short lock[long]'
            self.save_dist(dist_record)

            # 创建一个对锁网格
            lock_grid = copy(grid)
            # 网格类型, => 锁仓格
            lock_grid.type = LOCK_GRID
            lock_grid.id = str(uuid.uuid1())
            lock_grid.direction = Direction.SHORT
            lock_grid.open_status = False
            lock_grid.order_status = False
            lock_grid.order_ids = []

            vt_orderids = self.short(self.cur_mi_price,
                                     volume=lock_grid.volume,
                                     vt_symbol=self.vt_symbol,
                                     order_type=self.order_type,
                                     order_time=self.cur_datetime,
                                     grid=lock_grid)

            if len(vt_orderids) > 0:
                # 原做多网格得类型,设置为锁仓格
                grid.type = LOCK_GRID
                self.write_log(u'委托创建对锁单(空单)成功,委托编号:{},{},p:{},v:{}'
                               .format(vt_orderids,
                                       sell_symbol,
                                       self.cur_mi_price,
                                       lock_grid.volume))
                lock_grid.snapshot.update({'mi_symbol': self.vt_symbol, 'open_price': self.cur_mi_price})
                self.gt.up_grids.append(lock_grid)
                return True
            else:
                self.write_error(u'未能委托对锁单(空单)')
                return False

    def tns_close_short_pos(self, grid):
        """
        事务平空单仓位
        1.来源自止损止盈平仓
        2.来源自换仓
        逻辑: 如果当前账号昨仓满足平仓数量,直接平仓,如果不满足,则创建锁仓网格.
        :param 平仓网格
        :return:
        """
        self.write_log(u'执行事务平空仓位:{}'.format(grid.to_json()))
        # 平仓网格得合约
        cover_symbol = grid.snapshot.get('mi_symbol', self.vt_symbol)
        # vt_symbol => holding position
        grid_pos = self.cta_engine.get_position_holding(cover_symbol)
        if grid_pos is None:
            self.write_error(u'无法获取{}得持仓信息'.format(cover_symbol))
            return False

        # 昨仓可以满足,发出委托卖出单
        if (grid_pos.short_yd >= grid.volume > 0 and grid_pos.long_td == 0 and grid_pos.short_td == 0) \
                or not self.activate_today_lock:
            if self.activate_today_lock:
                self.write_log(u'昨仓空单:{},没有今仓, 满足条件,直接平昨仓'.format(grid_pos.short_yd))

            cover_price = self.cta_engine.get_price(cover_symbol)
            if cover_price is None:
                self.write_error(f'暂时没有{cover_symbol}行情，不能执行平仓')
                return False

            # 发出cover委托
            if grid.traded_volume > 0:
                grid.volume -= grid.traded_volume
                grid.traded_volume = 0

            vt_orderids = self.cover(price=cover_price,
                                     volume=grid.volume,
                                     vt_symbol=cover_symbol,
                                     order_type=self.order_type,
                                     order_time=self.cur_datetime,
                                     grid=grid)
            if len(vt_orderids) == 0:
                self.write_error(u'空单平仓委托失败')
                return False
            else:
                self.write_log(u'空单平仓委托成功，编号:{}'.format(vt_orderids))
                return True

        # 当前没有昨仓,采用锁仓处理
        else:
            self.write_log(u'昨仓空单:{}不满足条件,建立对锁仓'.format(grid_pos.shortYd))
            dist_record = dict()
            dist_record['datetime'] = self.cur_datetime
            dist_record['symbol'] = cover_symbol
            dist_record['price'] = self.cur_mi_price
            dist_record['volume'] = grid.volume
            dist_record['operation'] = 'add long lock[short]'
            self.save_dist(dist_record)
            # 创建一个对锁网格
            lock_grid = copy(grid)
            # 网格类型, => 锁仓格
            lock_grid.type = LOCK_GRID
            lock_grid.id = str(uuid.uuid1())
            lock_grid.direction = Direction.LONG
            lock_grid.open_status = False
            lock_grid.order_status = False
            lock_grid.order_ids = []

            vt_orderids = self.buy(price=self.cur_mi_price,
                                   volume=lock_grid.volume,
                                   vt_symbol=cover_symbol,
                                   order_type=self.order_type,
                                   grid=lock_grid)

            if len(vt_orderids) > 0:
                # 原做空网格得类型,设置为锁仓格
                grid.type = LOCK_GRID
                self.write_log(u'委托创建对锁单(多单)成功,委托编号:{},{},p:{},v:{}'
                               .format(vt_orderids,
                                       self.vt_symbol,
                                       self.cur_mi_price,
                                       lock_grid.volume))
                lock_grid.snapshot.update({'mi_symbol': self.vt_symbol, 'open_price': self.cur_mi_price})
                self.gt.dn_grids.append(lock_grid)
                return True
            else:
                self.write_error(u'未能委托对锁单(多单)')
                return False

    def tns_open_from_lock(self, open_symbol, open_volume, grid_type, open_direction):
        """
        从锁仓单中,获取已开的网格(对手仓设置为止损)
        1, 检查多空锁仓单中,是否有满足数量得昨仓,
        2, 定位到需求网格,
        :param open_symbol: 开仓合约(主力合约)
        :param open_volume:
        :param grid_type 更新网格的类型
        :param open_direction: 开仓方向
        :return: None, 保留的格
        """

        # 检查多单得对锁格
        locked_long_grids = self.gt.get_opened_grids_within_types(direction=Direction.LONG, types=[LOCK_GRID])
        if len(locked_long_grids) == 0:
            return None
        locked_long_dict = {}

        for g in locked_long_grids:
            symbol = g.snapshot.get('mi_symbol', self.vt_symbol)

            if g.order_status or g.order_ids:
                self.write_log(u'当前对锁格:{}存在委托,不纳入计算'.format(g.to_json()))
                continue

            if symbol != open_symbol:
                self.write_log(u'不处理symbol不一致: 委托请求:{}, Grid mi Symbol:{}'.format(open_symbol, symbol))
                continue

            volume = g.volume - g.traded_volume
            locked_long_dict.update({symbol: locked_long_dict.get(symbol, 0) + volume})

        locked_long_volume = locked_long_dict.get(open_symbol, 0)
        if locked_long_volume < open_volume:
            self.write_log(u'锁单中,没有足够得多单:{},需求:{}'.format(locked_long_volume, open_volume))
            return None

        # 空单对锁格
        locked_short_grids = self.gt.get_opened_grids_within_types(direction=Direction.SHORT, types=[LOCK_GRID])
        if len(locked_short_grids) == 0:
            return None

        locked_short_dict = {}

        for g in locked_short_grids:
            symbol = g.snapshot.get('mi_symbol', self.vt_symbol)
            if g.order_status or g.order_ids:
                self.write_log(u'当前对锁格:{}存在委托,不进行解锁'.format(g.to_json()))
                continue
            if symbol != open_symbol:
                self.write_log(u'不处理symbol不一致: 委托请求:{}, Grid mi Symbol:{}'.format(open_symbol, symbol))
                continue
            volume = g.volume - g.traded_volume
            locked_short_dict.update({symbol: locked_short_dict.get(symbol, 0) + volume})

        locked_short_volume = locked_short_dict.get(open_symbol, 0)

        if locked_short_volume < open_volume:
            self.write_log(u'锁单中,没有足够得空单:{},需求:{}'.format(locked_short_volume, open_volume))
            return None

        # 检查空单昨仓是否满足
        symbol_pos = self.cta_engine.get_position_holding(open_symbol)
        if (open_direction == Direction.LONG and symbol_pos.short_yd < open_volume) \
                or (open_direction == Direction.SHORT and symbol_pos.long_yd < open_volume):
            self.write_log(u'昨仓数量,多单:{},空单:{},不满足:{}'
                           .format(symbol_pos.long_yd, symbol_pos.short_yd, open_volume))
            return None

        # 合并/抽离出 满足open_volume得多格,
        target_long_grid = None
        remove_long_grid_ids = []
        for g in sorted(locked_long_grids, key=lambda grid: grid.volume):
            if g.orderStatus or len(g.orderRef) > 0:
                continue
            if target_long_grid is None:
                target_long_grid = g
                if g.volume == open_volume:
                    self.write_log(u'第一个网格持仓数量一致:g.volume:{},open_volume:{}'
                                   .format(g.volume, open_volume))
                    break
                elif g.volume > open_volume:
                    self.write_log(u'第一个网格持仓数量大于需求:g.volume:{},open_volume:{}'
                                   .format(g.volume, open_volume))
                    remain_grid = copy(g)
                    g.volume = open_volume
                    remain_grid.volume -= open_volume
                    remain_grid.id = uuid.uuid1()
                    self.gt.dn_grids.append(remain_grid)
                    self.write_log(u'添加剩余仓位到新多单网格:g.volume:{}'
                                   .format(remain_grid.volume))
                    break
            else:
                if g.volume <= open_volume - target_long_grid.volume:
                    self.write_log(u'网格持仓数量:g.volume:{},open_volume:{},保留格:{}'
                                   .format(g.volume,
                                           open_volume,
                                           target_long_grid.volume))
                    target_long_grid.volume += g.volume
                    g.volume = 0
                    self.write_log(u'计划移除:{}'.format(g.id))
                    remove_long_grid_ids.append(g.id)
                else:
                    self.write_log(u'转移前网格持仓数量:g.volume:{},open_volume:{},保留格:{}'
                                   .format(g.volume,
                                           open_volume,
                                           target_long_grid.volume))
                    g.volume -= (open_volume - target_long_grid.volume)
                    target_long_grid.volume = open_volume
                    self.write_log(u'转移后网格持仓数量:g.volume:{},open_volume:{},保留格:{}'
                                   .format(g.volume,
                                           open_volume,
                                           target_long_grid.volume))

                    break

        target_short_grid = None
        remove_short_grid_ids = []
        for g in sorted(locked_short_grids, key=lambda grid: grid.volume):
            if g.order_status or g.order_ids:
                continue
            if target_short_grid is None:
                target_short_grid = g
                if g.volume == open_volume:
                    self.write_log(u'第一个空单网格持仓数量满足需求:g.volume:{},open_volume:{}'
                                   .format(g.volume, open_volume))
                    break
                elif g.volume > open_volume:
                    self.write_log(u'第一个空单网格持仓数量大于需求:g.volume:{},open_volume:{}'
                                   .format(g.volume, open_volume))
                    remain_grid = copy(g)
                    g.volume = open_volume
                    remain_grid.volume -= open_volume
                    remain_grid.id = uuid.uuid1()
                    self.gt.up_grids.append(remain_grid)
                    self.write_log(u'添加剩余仓位到新空单网格:g.volume:{}'
                                   .format(remain_grid.volume))
                    break
            else:
                if g.volume <= open_volume - target_short_grid.volume:
                    target_short_grid.volume += g.volume
                    g.volume = 0
                    remove_short_grid_ids.append(g.id)
                else:
                    self.write_log(u'转移前空单网格持仓数量:g.volume:{},open_volume:{},保留格:{}'
                                   .format(g.volume,
                                           open_volume,
                                           target_short_grid.volume))
                    g.volume -= (open_volume - target_short_grid.volume)
                    target_short_grid.volume = open_volume
                    self.write_log(u'转移后空单网格持仓数量:g.volume:{},open_volume:{},保留格:{}'
                                   .format(g.volume,
                                           open_volume,
                                           target_short_grid.volume))

                    break

        if target_long_grid.volume is None or target_short_grid is None:
            self.write_log(u'未能定位多单网格和空单网格,不能解锁')
            return None

        # 移除volume为0的网格
        self.gt.remove_grids_by_ids(direction=Direction.LONG, ids=remove_long_grid_ids)
        self.gt.remove_grids_by_ids(direction=Direction.SHORT, ids=remove_short_grid_ids)

        if open_direction == Direction.LONG:
            self.write_log(u'保留多单,对空单:{}平仓'.format(target_short_grid.id))
            # 对空单目标网格进行平仓
            cover_price = self.cta_engine.get_price(open_symbol)
            # 使用止损价作为平仓
            self.write_log(u'空单止损价 :{} =>{}'.format(target_short_grid.stop_price, cover_price - 10 * self.price_tick))
            target_short_grid.stop_price = cover_price - 10 * self.price_tick
            # 更新对锁格类型=>指定类型
            self.write_log(u'空单类型 :{} =>{}'.format(target_short_grid.type, grid_type))
            target_short_grid.type = grid_type
            # 返回保留的多单网格
            return target_long_grid

        else:
            self.write_log(u'保留空单,对多单平仓')
            sell_price = self.cta_engine.get_price(open_symbol)
            # # 使用止损价作为平仓
            self.write_log(u'多单止损价 :{} =>{}'.format(target_short_grid.stop_price, sell_price + 10 * self.price_tick))
            target_long_grid.stop_price = sell_price + 10 * self.price_tick
            # 更新对锁格类型=>指定类型
            self.write_log(u'多单类型 :{} =>{}'.format(target_short_grid.type, grid_type))
            target_long_grid.type = grid_type
            # 返回保留的空单网格
            return target_short_grid

    def tns_close_locked_grids(self, grid_type):
        """
        事务对所有对锁网格进行平仓
        :return:
        """
        # 正在委托时,不处理
        if self.entrust != 0:
            return

        # 多单得对锁格
        locked_long_grids = self.gt.get_opened_grids_within_types(direction=Direction.LONG, types=[LOCK_GRID])
        if len(locked_long_grids) == 0:
            return
        locked_long_dict = {}

        for g in locked_long_grids:
            vt_symbol = g.snapshot.get('mi_symbol', self.vt_symbol)
            volume = g.volume - g.traded_volume
            locked_long_dict.update({vt_symbol: locked_long_dict.get(vt_symbol, 0) + volume})
            if g.orderStatus or g.order_ids:
                self.write_log(u'当前对锁格:{}存在委托,不进行解锁'.format(g.to_json()))
                return

        locked_long_volume = sum(locked_long_dict.values(), 0)

        # 空单对锁格
        locked_short_grids = self.gt.get_opened_grids_within_types(direction=Direction.SHORT, types=[LOCK_GRID])
        if len(locked_short_grids) == 0:
            return

        locked_short_dict = {}

        for g in locked_short_grids:
            vt_symbol = g.snapshot.get('mi_symbol', self.vt_symbol)
            volume = g.volume - g.traded_volume
            locked_short_dict.update({vt_symbol: locked_short_dict.get(vt_symbol, 0) + volume})
            if g.orderStatus or g.order_ids:
                self.write_log(u'当前对锁格:{}存在委托,不进行解锁'.format(g.to_json()))
                return

        locked_short_volume = sum(locked_short_dict.values(), 0)

        # debug info
        self.write_log(u'多单对锁格:{}'.format([g.to_json() for g in locked_long_grids]))
        self.write_log(u'空单对锁格:{}'.format([g.to_json() for g in locked_short_grids]))

        if locked_long_volume != locked_short_volume:
            self.write_error(u'对锁格多空数量不一致,不能解锁.\n多:{},\n空:{}'
                             .format(locked_long_volume, locked_short_volume))
            return

        # 检查所有品种得昨仓是否满足数量
        for vt_symbol, volume in locked_long_dict.items():
            pos = self.cta_engine.get_position_holding(vt_symbol, None)
            if pos is None:
                self.write_error(u'{} 没有获取{}得持仓信息,不能解锁')
                return

            # 检查多空单得昨单能否满足
            if pos.long_yd < volume or pos.short_yd < volume:
                self.write_error(u'{}持仓昨仓多单:{},空单:{},不满足解锁数量:{}'
                                 .format(vt_symbol, pos.long_yd, pos.short_td, volume))
                return

            if pos.long_td > 0 or pos.short_td > 0:
                self.write_log(u'{}存在今多仓:{},空仓{},不满足解锁条件'.format(vt_symbol, pos.long_td, pos.short_td))
                return

            price = self.cta_engine.get_price(vt_symbol)
            if price is None:
                self.write_error(u'{}价格不在tick_dict缓存中,不能解锁'.format(vt_symbol))

        # 所有合约价格和仓位都满足同时解开
        for g in locked_long_grids:
            dist_record = dict()
            dist_record['datetime'] = self.cur_datetime
            dist_record['symbol'] = self.vt_symbol
            dist_record['price'] = self.cur_mi_price
            dist_record['volume'] = g.volume
            dist_record['operation'] = 'close lock[long]'
            self.save_dist(dist_record)

            # 通过切换回普通网格，提升止损价的方式实现平仓
            self.write_log(
                u'网格 从锁仓 {}=>{}，提升止损价{}=>{}进行离场'.format(LOCK_GRID, grid_type, g.stop_price,
                                                        self.cur_99_price / 2))
            g.type = grid_type
            g.stop_price = self.cur_99_price / 2

        for g in locked_short_grids:
            dist_record = dict()
            dist_record['datetime'] = self.cur_datetime
            dist_record['symbol'] = self.vt_symbol
            dist_record['price'] = self.cur_mi_price

            dist_record['volume'] = g.volume
            dist_record['operation'] = 'close lock[short]'
            self.save_dist(dist_record)

            # 通过切换回普通网格，提升止损价的方式实现平仓
            self.write_log(u'网格 从锁仓 {}=>{}，提升止损价{}=>{}进行离场'.format(LOCK_GRID, grid_type, g.stop_price,
                                                                   self.cur_99_price * 2))
            g.type = grid_type
            g.stop_price = self.cur_99_price * 2

    def grid_check_stop(self):
        """
        网格逐一止损/止盈检查 (根据指数价格进行止损止盈）
        :return:
        """
        if self.entrust != 0:
            return

        if not self.trading:
            if not self.backtesting:
                self.write_error(u'当前不允许交易')
            return

        # 多单网格逐一止损/止盈检查：
        long_grids = self.gt.get_opened_grids_without_types(direction=Direction.LONG, types=[LOCK_GRID])

        for g in long_grids:
            # 满足离场条件，或者碰到止损价格
            if g.stop_price > 0 and g.stop_price > self.cur_99_price \
                    and g.openStatus and not g.orderStatus:
                dist_record = dict()
                dist_record['datetime'] = self.cur_datetime
                dist_record['symbol'] = self.idx_symbol
                dist_record['volume'] = g.volume
                dist_record['price'] = self.cur_99_price
                dist_record['operation'] = 'stop leave'
                dist_record['signals'] = '{}<{}'.format(self.cur_99_price, g.stop_price)
                # 止损离场
                self.write_log(u'{} 指数价:{} 触发多单止损线{},{}当前价:{}。指数开仓价:{},主力开仓价:{},v：{}'.
                               format(self.cur_datetime, self.cur_99_price, g.stop_price, self.vt_symbol,
                                      self.cur_mi_price,
                                      g.open_price, g.snapshot.get('open_price'), g.volume))
                self.save_dist(dist_record)

                if self.tns_close_long_pos(g):
                    self.write_log(u'多单止盈/止损委托成功')
                else:
                    self.write_error(u'多单止损委托失败')

        # 空单网格止损检查
        short_grids = self.gt.get_opened_grids_without_types(direction=Direction.SHORT, types=[LOCK_GRID])
        for g in short_grids:
            if g.stop_price > 0 and g.stop_price < self.cur_99_price \
                    and g.openStatus and not g.orderStatus:
                dist_record = dict()
                dist_record['datetime'] = self.cur_datetime
                dist_record['symbol'] = self.idx_symbol
                dist_record['volume'] = g.volume
                dist_record['price'] = self.cur_99_price
                dist_record['operation'] = 'stop leave'
                dist_record['signals'] = '{}<{}'.format(self.cur_99_price, g.stop_price)
                # 网格止损
                self.write_log(u'{} 指数价:{} 触发空单止损线:{},{}最新价:{}。指数开仓价:{},主力开仓价:{},v：{}'.
                               format(self.cur_datetime, self.cur_99_price, g.stop_price, self.vt_symbol,
                                      self.cur_mi_price,
                                      g.open_price, g.snapshot.get('open_price'), g.volume))
                self.save_dist(dist_record)

                if self.tns_close_short_pos(g):
                    self.write_log(u'空单止盈/止损委托成功')
                else:
                    self.write_error(u'委托空单平仓失败')
