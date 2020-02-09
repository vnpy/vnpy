""""""
import os
import uuid
import bz2
import pickle
import copy
import traceback

from abc import ABC
from copy import copy
from typing import Any, Callable
from logging import INFO, ERROR
from datetime import datetime
from vnpy.trader.constant import Interval, Direction, Offset, Status
from vnpy.trader.object import BarData, TickData, OrderData, TradeData
from vnpy.trader.utility import virtual, append_data, extract_vt_symbol,get_underlying_symbol

from .base import StopOrder, EngineType
from .cta_grid_trade import CtaGrid, CtaGridTrade
from .cta_position import CtaPosition


class CtaTemplate(ABC):
    """CTA策略模板"""

    author = ""
    parameters = []
    variables = []

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

        # 保存委托单编号和相关委托单的字典
        # key为委托单编号
        # value为该合约相关的委托单
        self.active_orders = {}

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
            vt_symbol: str = '', order_time: datetime = None, grid: CtaGrid = None):
        """
        Send buy order to open a long position.
        """

        return self.send_order(vt_symbol=vt_symbol,
                               direction=Direction.LONG,
                               offset=Offset.OPEN,
                               price=price,
                               volume=volume,
                               stop=stop,
                               lock=lock,
                               order_time=order_time,
                               grid=grid)

    def sell(self, price: float, volume: float, stop: bool = False, lock: bool = False,
             vt_symbol: str = '', order_time: datetime = None, grid: CtaGrid = None):
        """
        Send sell order to close a long position.
        """
        return self.send_order(vt_symbol=vt_symbol,
                               direction=Direction.SHORT,
                               offset=Offset.CLOSE,
                               price=price,
                               volume=volume,
                               stop=stop,
                               lock=lock,
                               order_time=order_time,
                               grid=grid)

    def short(self, price: float, volume: float, stop: bool = False, lock: bool = False,
              vt_symbol: str = '', order_time: datetime = None, grid: CtaGrid = None):
        """
        Send short order to open as short position.
        """
        return self.send_order(vt_symbol=vt_symbol,
                               direction=Direction.SHORT,
                               offset=Offset.OPEN,
                               price=price,
                               volume=volume,
                               stop=stop,
                               lock=lock,
                               order_time=order_time,
                               grid=grid)

    def cover(self, price: float, volume: float, stop: bool = False, lock: bool = False,
              vt_symbol: str = '', order_time: datetime = None, grid: CtaGrid = None):
        """
        Send cover order to close a short position.
        """
        return self.send_order(vt_symbol=vt_symbol,
                               direction=Direction.LONG,
                               offset=Offset.CLOSE,
                               price=price,
                               volume=volume,
                               stop=stop,
                               lock=lock,
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
            self, vt_symbol, direction, offset, price, volume, stop, lock
        )

        if order_time is None:
            order_time = datetime.now()

        for vt_orderid in vt_orderids:
            d = {
                'direction': direction.value,
                'offset': offset.value,
                'vt_symbol': vt_symbol,
                'price': price,
                'volume': volume,
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

    backtesting = False

    # 逻辑过程日志
    dist_fieldnames = ['datetime', 'symbol', 'volume', 'price',
                       'operation', 'signal', 'stop_price', 'target_price',
                       'long_pos', 'short_pos']

    def __init__(self, cta_engine, strategy_name, vt_symbol, setting):
        """"""
        super(CtaProTemplate, self).__init__(
            cta_engine, strategy_name, vt_symbol, setting
        )

        self.idx_symbol = None  # 指数合约

        self.price_tick = 1  # 商品的最小价格跳动
        self.symbol_size = 10  # 商品得合约乘数

        self.cur_datetime = None  # 当前Tick时间

        self.cur_mi_tick = None  # 最新的主力合约tick( vt_symbol)
        self.cur_99_tick = None  # 最新得指数合约tick( idx_symbol)

        self.cur_mi_price = None  # 当前价（主力合约 vt_symbol)
        self.cur_99_price = None  # 当前价（tick时，根据tick更新，onBar回测时，根据bar.close更新)

        self.cancel_seconds = 120  # 撤单时间(秒)

        self.klines = {}  # K线字典: kline_name: kline

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
                #if kline:
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

            for kline_name in sorted(self.klines.keys()):
                d.update({kline_name: self.klines.get(kline_name).get_data()})
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

        self.write_log(
            u'{}加载持久化数据完成，多单:{}，空单:{},共:{}手'
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
                open_price = g.snapshot.get('open_price', g.openPrice)
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

        grid = copy.copy(none_mi_grid)

        # 委托卖出非主力合约
        order_ids = self.sell(price=none_mi_price, volume=none_mi_grid.volume, vt_symbol=none_mi_symbol,
                              grid=none_mi_grid)
        if len(order_ids) > 0:
            self.write_log(f'切换合约,委托卖出非主力合约{none_mi_symbol}持仓:{none_mi_grid.volume}')

            # 添加买入主力合约
            grid.id = str(uuid.uuid1())
            grid.snapshot.update({'mi_symbol': self.vt_symbol, 'open_price': self.cur_mi_price})
            self.gt.dn_grids.append(grid)

            order_ids = self.buy(price=self.cur_mi_price, volume=grid.volume, vt_symbol=self.vt_symbol, grid=grid)
            if len(order_ids) > 0:
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

        grid = copy.copy(none_mi_grid)
        # 委托平空非主力合约
        order_ids = self.cover(price=none_mi_price, volume=none_mi_grid.volume, vt_symbol=self.vt_symbol,
                               grid=none_mi_grid)
        if len(order_ids) > 0:
            self.write_log(f'委托平空非主力合约{none_mi_symbol}持仓:{none_mi_grid.volume}')

            # 添加卖出主力合约
            grid.id = str(uuid.uuid1())
            grid.snapshot.update({'mi_symbol': self.vt_symbol, 'open_price': self.cur_mi_price})
            self.gt.up_grids.append(grid)
            order_ids = self.short(price=self.cur_mi_price, volume=grid.volume, vt_symbol=self.vt_symbol, grid=grid)
            if len(order_ids) > 0:
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
