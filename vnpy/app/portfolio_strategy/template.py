from abc import ABC, abstractmethod
from copy import copy
from datetime import datetime
from typing import TYPE_CHECKING, Optional
from collections import defaultdict

import pandas as pd
import polars as pl

from vnpy.trader.constant import Interval, Direction, Offset, Exchange
from vnpy.trader.object import BarData, TickData, OrderData, TradeData, FactorData
from vnpy.trader.utility import virtual, BarGenerator, extract_vt_symbol, convert_dict_to_dataframe

from vnpy.app.portfolio_strategy.base import EngineType

if TYPE_CHECKING:
    from vnpy.app.portfolio_strategy.engine import StrategyEngine


class StrategyTemplate(ABC):
    """组合策略模板"""

    author: str = ""
    parameters: list = []
    variables: list = []
    factors: list = []  # {factor_name}_{interval}
    exchange: Exchange = Exchange.BINANCE
    interval: Interval = Interval.MINUTE

    def __init__(
            self,
            strategy_engine: "StrategyEngine",
            strategy_name: str,
            vt_symbols: list[str],
            setting: dict
    ) -> None:
        """构造函数"""
        self.strategy_engine: "StrategyEngine" = strategy_engine
        self.strategy_name: str = strategy_name
        self.vt_symbols: list[str] = vt_symbols
        self.factor_dict = None

        self.checklist: dict[str, bool] = {}
        self.portfolio_value: float = 0

        # 状态控制变量
        self.inited: bool = False
        self.trading: bool = False

        # 持仓数据字典
        self.pos_data: dict[str, float] = defaultdict(float)  # 实际持仓
        self.target_data: dict[str, float] = defaultdict(float)  # 目标持仓

        #Tick数据字典
        self.ticks: dict[str, TickData] = defaultdict(TickData)
        #Bar数据字典
        self.bars: dict[str, BarData] = defaultdict(BarData)

        # 委托缓存容器
        self.orders: dict[str, OrderData] = {}
        self.active_orderids: set[str] = set()

        # 复制变量名列表，插入默认变量内容
        self.variables: list = copy(self.variables)
        self.variables.insert(0, "inited")
        self.variables.insert(1, "trading")
        self.variables.insert(2, "pos_data")
        self.variables.insert(3, "target_data")

        # 设置策略参数
        self.update_setting(setting)
        self.init_factors()

    def init_factors(self) -> None:
        """初始化策略因子"""
        self.factor_dict: dict[tuple[str, str], FactorData] = {}
        self.status_dict: dict[tuple[str, str], bool] = {}
        for vt_symbol in self.vt_symbols:
            symbol, _ = extract_vt_symbol(vt_symbol, is_factor=False)
            for factor_name in self.factors:
                factor: FactorData = FactorData(
                    symbol=symbol,
                    exchange=self.exchange,
                    datetime=datetime.now(),
                    interval=self.interval,
                    value=0,
                    factor_name=factor_name,
                    gateway_name="strategy_template"
                )
                self.factor_dict[(symbol, factor_name)] = factor
                self.status_dict[(symbol, factor_name)] = False

    def update_setting(self, setting: dict) -> None:
        """设置策略参数"""
        for name in self.parameters:
            if name in setting:
                setattr(self, name, setting[name])

    def init_status_dict(self) -> None:
        """初始化因子检查列表"""
        self.status_dict.update((key, False) for key in self.status_dict)

    @classmethod
    def get_class_parameters(cls) -> dict:
        """查取策略默认参数"""
        class_parameters: dict = {}
        for name in cls.parameters:
            class_parameters[name] = getattr(cls, name)
        return class_parameters

    def get_parameters(self) -> dict:
        """查询策略参数"""
        strategy_parameters: dict = {}
        for name in self.parameters:
            strategy_parameters[name] = getattr(self, name)
        return strategy_parameters

    def get_variables(self) -> dict:
        """查询策略变量"""
        strategy_variables: dict = {}
        for name in self.variables:
            strategy_variables[name] = getattr(self, name)
        return strategy_variables

    def get_data(self) -> dict:
        """查询策略状态数据"""
        strategy_data: dict = {
            "strategy_name": self.strategy_name,
            "vt_symbols": self.vt_symbols,
            "class_name": self.__class__.__name__,
            "author": self.author,
            "parameters": self.get_parameters(),
            "variables": self.get_variables(),
            "factors": self.factor_dict
        }
        return strategy_data

    @virtual
    def on_init(self) -> None:
        """策略初始化回调"""
        self.inited = True
        pass

    @virtual
    def on_start(self) -> None:
        """策略启动回调"""
        self.trading = True
        pass

    @virtual
    def on_stop(self) -> None:
        """策略停止回调"""
        self.trading = False
        pass

    @virtual
    def on_tick(self, tick: TickData) -> None:
        """行情推送回调"""
        if tick.vt_symbol in self.vt_symbols:
            self.ticks[tick.vt_symbol] = tick

        pass

    @virtual
    def on_bars(self, bars: dict[str, BarData]) -> None:
        """K线切片回调"""
        pass

    def on_bar(self, bar: BarData) -> None:
        """K线推送回调"""
        if bar.vt_symbol in self.vt_symbols:
            self.bars[bar.vt_symbol] = bar
        return

    def on_factor(self, factor: FactorData) -> None:
        # todo 优化因子推送逻辑
        if self.trading:
            """因子推送回调"""
            updated_all: bool = self.update_factor(factor)
            if updated_all:
                factor_df: Optional[pd.DataFrame, pl.DataFrame] = convert_dict_to_dataframe(data=self.factor_dict, is_polars=False)
                self.calculate(factor_df)
                self.init_status_dict()
        return

    def update_factor(self, factor: FactorData) -> bool:
        """因子数据更新"""
        symbol = factor.symbol
        factor_name = factor.factor_name
        key = (symbol, factor_name)
        if key in self.factor_dict:
            self.factor_dict[key] = factor
            self.status_dict[key] = True
        else:
            self.write_log(f"因子{factor.factor_name}不在策略因子列表中")

        return all(self.status_dict.values())

    @abstractmethod
    def calculate(self, df) -> None:
        """因子推送完成回调"""
        # todo 优化因子推送完成逻辑, update target positions
        pass

    def update_trade(self, trade: TradeData) -> None:
        """成交数据更新"""
        if trade.direction == Direction.LONG:
            self.pos_data[trade.vt_symbol] += trade.volume
        else:
            self.pos_data[trade.vt_symbol] -= trade.volume

    def update_order(self, order: OrderData) -> None:
        """委托数据更新"""
        self.orders[order.vt_orderid] = order

        if not order.is_active() and order.vt_orderid in self.active_orderids:
            self.active_orderids.remove(order.vt_orderid)

    def buy(self, vt_symbol: str, price: float, volume: float, lock: bool = False, net: bool = False) -> list[str]:
        """买入开仓"""
        return self.send_order(vt_symbol, Direction.LONG, Offset.OPEN, price, volume, lock, net)

    def sell(self, vt_symbol: str, price: float, volume: float, lock: bool = False, net: bool = False) -> list[str]:
        """卖出平仓"""
        return self.send_order(vt_symbol, Direction.SHORT, Offset.CLOSE, price, volume, lock, net)

    def short(self, vt_symbol: str, price: float, volume: float, lock: bool = False, net: bool = False) -> list[str]:
        """卖出开仓"""
        return self.send_order(vt_symbol, Direction.SHORT, Offset.OPEN, price, volume, lock, net)

    def cover(self, vt_symbol: str, price: float, volume: float, lock: bool = False, net: bool = False) -> list[str]:
        """买入平仓"""
        return self.send_order(vt_symbol, Direction.LONG, Offset.CLOSE, price, volume, lock, net)

    def send_order(
            self,
            vt_symbol: str,
            direction: Direction,
            offset: Offset,
            price: float,
            volume: float,
            lock: bool = False,
            net: bool = False,
    ) -> list[str]:
        """发送委托"""
        if self.trading:
            vt_orderids: list = self.strategy_engine.send_order(
                self, vt_symbol, direction, offset, price, volume, lock, net
            )

            for vt_orderid in vt_orderids:
                self.active_orderids.add(vt_orderid)

            return vt_orderids
        else:
            return []

    def cancel_order(self, vt_orderid: str) -> None:
        """撤销委托"""
        if self.trading:
            self.strategy_engine.cancel_order(self, vt_orderid)

    def cancel_all(self) -> None:
        """全撤活动委托"""
        for vt_orderid in list(self.active_orderids):
            self.cancel_order(vt_orderid)

    def get_pos(self, vt_symbol: str) -> float:
        """查询当前持仓"""
        return self.pos_data.get(vt_symbol, 0)

    def get_target(self, vt_symbol: str) -> float:
        """查询目标仓位"""
        return self.target_data[vt_symbol]

    def set_target(self, vt_symbol: str, target: float) -> None:
        """设置目标仓位"""
        self.target_data[vt_symbol] = target

    def rebalance_portfolio(self, bars: dict[str, BarData]) -> None:
        """基于目标执行调仓交易"""
        self.cancel_all()

        # 只发出当前K线切片有行情的合约的委托
        for vt_symbol, bar in bars.items():
            # 计算仓差
            target: float = self.get_target(vt_symbol)
            pos: float = self.get_pos(vt_symbol)
            diff: float = target - pos

            # 多头
            if diff > 0:
                # 计算多头委托价
                order_price: float = self.calculate_price(
                    vt_symbol,
                    Direction.LONG,
                    bar.close_price
                )

                # 计算买平和买开数量
                cover_volume: float = 0
                buy_volume: float = 0

                if pos < 0:
                    cover_volume = min(diff, abs(pos))
                    buy_volume = diff - cover_volume
                else:
                    buy_volume = diff

                # 发出对应委托
                if cover_volume:
                    self.cover(vt_symbol, order_price, cover_volume)

                if buy_volume:
                    self.buy(vt_symbol, order_price, buy_volume)
            # 空头
            elif diff < 0:
                # 计算空头委托价
                order_price: float = self.calculate_price(
                    vt_symbol,
                    Direction.SHORT,
                    bar.close_price
                )

                # 计算卖平和卖开数量
                sell_volume: float = 0
                short_volume: float = 0

                if pos > 0:
                    sell_volume = min(abs(diff), pos)
                    short_volume = abs(diff) - sell_volume
                else:
                    short_volume = abs(diff)

                # 发出对应委托
                if sell_volume:
                    self.sell(vt_symbol, order_price, sell_volume)

                if short_volume:
                    self.short(vt_symbol, order_price, short_volume)

    @virtual
    def calculate_price(
            self,
            vt_symbol: str,
            direction: Direction,
            reference: float
    ) -> float:
        """计算调仓委托价格（支持按需重载实现）"""
        return reference

    def get_order(self, vt_orderid: str) -> Optional[OrderData]:
        """查询委托数据"""
        return self.orders.get(vt_orderid, None)

    def get_all_active_orderids(self) -> list[str]:
        """获取全部活动状态的委托号"""
        return list(self.active_orderids)

    def write_log(self, msg: str) -> None:
        """记录日志"""
        self.strategy_engine.write_log(msg, self)

    def get_engine_type(self) -> EngineType:
        """查询引擎类型"""
        return self.strategy_engine.get_engine_type()

    def get_pricetick(self, vt_symbol: str) -> float:
        """查询合约最小价格跳动"""
        return self.strategy_engine.get_pricetick(self, vt_symbol)

    def get_size(self, vt_symbol: str) -> float | None:
        """查询合约乘数"""
        return self.strategy_engine.get_size(self, vt_symbol)

    def load_bars(self, days: int, interval: Interval = Interval.MINUTE) -> None:
        """加载历史K线数据来执行初始化"""
        self.strategy_engine.load_bars(self, days, interval)

    def put_event(self) -> None:
        """推送策略数据更新事件"""
        if self.inited:
            self.strategy_engine.put_strategy_event(self)

    def send_email(self, msg: str) -> None:
        """发送邮件信息"""
        if self.inited:
            self.strategy_engine.send_email(msg, self)

    def sync_data(self) -> None:
        """同步策略状态数据到文件"""
        if self.trading:
            self.strategy_engine.sync_strategy_data(self)
