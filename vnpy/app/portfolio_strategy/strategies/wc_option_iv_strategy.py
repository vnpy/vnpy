# -*- coding:utf-8 -*-
"""
@author: fsksf

@since: 2022/4/28 8:35
"""
from typing import List, Dict
from datetime import datetime
import pandas as pd
from dataclasses import dataclass
from sqlalchemy import desc
from jqdatasdk import opt, query
from datetime import datetime, timedelta
from fnlib.options import opt_compose_price, get_rest_pct, distance
from fnlib.balck76 import calculate_impv
from fnlib.obj import Period, Contract, OptContract
from fnlib.contract_manager import ContractManager
from vnpy.trader.object import TickData, OrderData, TradeData, SubscribeRequest, ContractData
from vnpy.trader.constant import Direction, Offset, OptionType, Exchange
from vnpy.app.portfolio_strategy import StrategyTemplate, StrategyEngine
from vnpy.trader.utility import BarGenerator, extract_vt_symbol
from vnpy.trader.object import TickData, BarData
from vnpy.app.portfolio_strategy.jq import login_jq


@dataclass
class PosTarget:
    first: int = None
    second: int = None

    def __bool__(self):
        return self.first is None and self.second is None


class WCIVStrategy(StrategyTemplate):
    """"""

    author = "kangyuqiang"
    r: float = 0.02
    volume: int = 100
    threshold1: float = 0.02                    # 阈值1
    threshold2: float = 0.01                    # 阈值2
    avg1: float = 0.001                         # 均值
    days_adv_change: int = 3
    days_adv_close: int = 4

    parameters = [
        "volume",
        "r",
        "threshold1",
        "threshold2",
        "avg1",
        "days_adv_change",
        "days_adv_close",
    ]
    variables = [
        "pos",
        "first_iv",
        "second_iv",
        "delta_iv"
    ]

    def __init__(
            self,
            strategy_engine: StrategyEngine,
            strategy_name: str,
            vt_symbols: List[str],
            setting: dict
    ):
        """"""
        super().__init__(strategy_engine, strategy_name, vt_symbols, setting)

        self.iv_engine = strategy_engine
        self.contract_manager = ContractManager()
        self.underlying_symbol, self.first_opt, self.second_opt = vt_symbols
        self.first_iv = None
        self.second_iv = None
        self.delta_iv = None
        self.pos: Dict[str, int] = dict()
        self.target_pos: PosTarget = None
        self._last_tick: Dict[TickData] = {}
        self._synthetic_futures_price: Dict[str, float]  = {}
        self._sbd = set()
        self.order_start_dt = None
        self.order_cancel_count = 10

    def on_init(self):
        """
        Callback when strategy is inited.
        """

        self.write_log("策略初始化")
        now = datetime.now()
        end = now + timedelta(days=30 * 6)
        with login_jq():
            df: pd.DataFrame = opt.run_query(query(opt.OPT_CONTRACT_INFO).filter(
                opt.OPT_CONTRACT_INFO.expire_date >= now,
                opt.OPT_CONTRACT_INFO.expire_date <= end,
                opt.OPT_CONTRACT_INFO.underlying_symbol == self.underlying_symbol.replace('.SSE', '.XSHG')
            ).order_by(desc(opt.OPT_CONTRACT_INFO.id)))

            print(df)
            df['code'] = df['code'].str.replace('.XSHG', '.SSE')
            df['underlying_symbol'] = df['underlying_symbol'].str.replace('.XSHG', '.SSE')
            self.contract_manager.opt_contract_from_df(df)
        self.write_log('初始化完成')

    def on_start(self):
        """
        Callback when strategy is started.
        """
        self.write_log("策略启动")

    def on_stop(self):
        """
        Callback when strategy is stopped.
        """
        self.write_log("策略停止")

    def on_tick(self, tick: TickData):
        if tick.vt_symbol == self.underlying_symbol:
            self.update_underlying_tick(tick)
        else:
            self.update_options_tick(tick)

    def get_tick(self, symbol):
        return self._last_tick.get(symbol)

    def get_pos(self, vt_symbol):
        return self.pos.get(vt_symbol, 0)

    def update_options_tick(self, tick: TickData):
        """
        计算隐含波动率
        """
        self._last_tick[tick.vt_symbol] = tick
        first_tick: TickData = self.get_tick(self.first_opt)
        second_tick: TickData = self.get_tick(self.second_opt)
        if not first_tick or not second_tick:
            self.write_log(f'计算波动率，行情有空, {first_tick}, {second_tick}')
            return
        first_opt = self.contract_manager.get_option_contract(first_tick.vt_symbol)
        second_opt = self.contract_manager.get_option_contract(second_tick.vt_symbol)
        first_price = (first_tick.ask_price_1 + first_tick.bid_price_1) / 2
        second_price = (second_tick.ask_price_1 + second_tick.bid_price_1) / 2
        first_period = self.contract_manager.get_contract_period(first_opt, dt=tick.datetime)
        second_period = self.contract_manager.get_contract_period(second_opt, dt=tick.datetime)
        first_atm = self._synthetic_futures_price.get(first_period)
        second_atm = self._synthetic_futures_price.get(second_period)
        if first_atm is None or second_atm is None:
            self.write_log(f'合成期货的价格为None: {first_atm}, {second_atm}')
            return
        first_iv = calculate_impv(
            price=first_price,
            s=first_atm,
            k=first_opt.exercise_price,
            r=self.r,
            t=get_rest_pct(end_dt=first_opt.expire_date, now=tick.datetime),
            cp=1 if first_opt.contract_type == 'CO' else -1
        )
        second_iv = calculate_impv(
            price=second_price,
            s=second_atm,
            k=second_opt.exercise_price,
            r=self.r,
            t=get_rest_pct(end_dt=second_opt.expire_date, now=tick.datetime),
            cp=1 if second_opt.contract_type == 'CO' else -1
        )
        self.first_iv = round(first_iv, 4)
        self.second_iv = round(second_iv, 4)
        self.put_event()
        self.check_iv(tick)

    def update_underlying_tick(self, tick: TickData):
        """
        计算合成期货价格
        """
        self._last_tick[tick.vt_symbol] = tick
        underlying_tick: TickData = self.get_tick(self.underlying_symbol)
        if underlying_tick is None:
            return
        price = underlying_tick.last_price
        for p in [Period.curr_month, Period.next_month]:
            call, put = self.contract_manager.get_equal_opts(
                underlying=self.underlying_symbol,
                price=price,
                dt=underlying_tick.datetime,
                period=p,
                days_adv_change=self.days_adv_change
            )
            if call.code not in self._sbd:
                call_symbol, call_ex = call.code.rsplit('.')
                contract: ContractData = self.iv_engine.main_engine.get_contract(call.code)
                self.iv_engine.main_engine.subscribe(
                    req=SubscribeRequest(symbol=call_symbol, exchange=Exchange(call_ex)),
                    gateway_name=contract.gateway_name
                )
                self.iv_engine.symbol_strategy_map[call.code].append(self)
                self._sbd.add(call.code)

            if put.code not in self._sbd:
                put_symbol, put_ex = put.code.rsplit('.')
                contract: ContractData = self.iv_engine.main_engine.get_contract(put.code)
                self.iv_engine.main_engine.subscribe(
                    req=SubscribeRequest(symbol=put_symbol, exchange=Exchange(put_ex)),
                    gateway_name=contract.gateway_name
                )
                self.iv_engine.symbol_strategy_map[put.code].append(self)
                self._sbd.add(call.code)

            if call is None or put is None:
                self.write_log('平值合约计算出来为None')
                continue
            call_tick: TickData = self.get_tick(call.code)
            put_tick: TickData = self.get_tick(put.code)
            if call_tick is None or put_tick is None:
                print(f'平值合约的行情为: {call_tick}, {put_tick}')
                continue
            futures_price = opt_compose_price(
                c_price=call_tick.last_price,
                p_price=put_tick.last_price,
                r=self.r,
                rest_pct=get_rest_pct(end_dt=call.expire_date, now=underlying_tick.datetime),
                exercise_price=call.exercise_price
            )
            # 合成期货价格
            self._synthetic_futures_price[p] = futures_price

    def delta(self):
        if self.first_iv is None or self.second_iv is None:
            return None
        self.delta_iv = round(self.first_iv - self.second_iv, 4)
        return self.delta_iv

    def if_hege(self):
        first_pos = self.get_pos(self.first_opt)
        second_pos = self.get_pos(self.second_opt)
        if abs(first_pos) == abs(second_pos):
            return True
        else:
            return False

    def take_target_pos(self):
        first_pos = self.get_pos(self.first_opt)
        second_pos = self.get_pos(self.second_opt)

        first_tick: TickData = self.get_tick(self.first_opt)
        second_tick: TickData = self.get_tick(self.second_opt)
        if not self.if_hege():
            # 先处理不平衡的问题
            first_diff_pos = self.target_pos.first - first_pos
            if self.target_pos.first != 0:
                # 开仓
                if first_diff_pos > 0:

                    print('不平衡，先买入当月合约')
                    self.send_order(
                        vt_symbol=self.first_opt,
                        volume=first_diff_pos,
                        direction=Direction.LONG,
                        offset=Offset.OPEN,
                        price=first_tick.ask_price_2
                    )
                else:
                    print('不平衡情况，先买空当月合约')
                    self.send_order(
                        vt_symbol=self.first_opt,
                        volume=abs(first_diff_pos),
                        direction=Direction.SHORT,
                        offset=Offset.OPEN,
                        price=first_tick.bid_price_2
                    )
            else:
                # 平仓
                if first_diff_pos > 0:

                    print('买平')
                    self.send_order(
                        vt_symbol=self.first_opt,
                        volume=first_diff_pos,
                        direction=Direction.LONG,
                        offset=Offset.CLOSE,
                        price=first_tick.ask_price_2
                    )
                else:
                    print('卖平')
                    self.send_order(
                        vt_symbol=self.first_opt,
                        volume=first_diff_pos,
                        direction=Direction.SHORT,
                        offset=Offset.CLOSE,
                        price=first_tick.bid_price_2
                    )
            return
        second_diff_pos = self.target_pos.second - second_pos
        if self.target_pos.second != 0:
            if second_diff_pos > 0:
                print('空仓情况，先买多次月合约')
                self.send_order(
                    vt_symbol=self.second_opt,
                    volume=second_diff_pos,
                    direction=Direction.LONG,
                    offset=Offset.OPEN,
                    price=second_tick.ask_price_2
                )
            elif second_diff_pos < 0:
                print('空仓情况，先卖空次月合约')
                self.send_order(
                    vt_symbol=self.second_opt,
                    volume=abs(second_diff_pos),
                    direction=Direction.SHORT,
                    offset=Offset.OPEN,
                    price=second_tick.bid_price_2
                )
        else:
            if second_diff_pos > 0:
                print('空仓情况，先买入次月合约')
                self.send_order(
                    vt_symbol=self.second_opt,
                    volume=second_diff_pos,
                    direction=Direction.LONG,
                    offset=Offset.CLOSE,
                    price=second_tick.ask_price_2
                )
            elif second_diff_pos < 0:
                print('空仓情况，先买入次月合约')
                self.send_order(
                    vt_symbol=self.second_opt,
                    volume=abs(second_diff_pos),
                    direction=Direction.SHORT,
                    offset=Offset.CLOSE,
                    price=second_tick.bid_price_2
                )

    def check_iv(self, tick: TickData):
        # 检查买卖条件
        if self.active_orderids:
            if self.order_start_dt and \
                    (datetime.now() - self.order_start_dt).seconds > self.order_cancel_count:
                self.cancel_all()
            return
        if not self.if_hege():
            self.take_target_pos()
            return
        delta = self.delta()
        first_pos = self.get_pos(self.first_opt)
        second_pos = self.get_pos(self.second_opt)
        first_opt: OptContract = self.contract_manager.get_option_contract(self.first_opt)
        second_opt: OptContract = self.contract_manager.get_option_contract(self.second_opt)
        last_underlying_tick = self.get_tick(self.underlying_symbol)
        price_tick = self.price_tick(tick.last_price)
        up_limit = 2 * price_tick + last_underlying_tick.last_price
        down_limit = last_underlying_tick.last_price - 2 * price_tick
        if self.target_pos and \
                self.target_pos.second == second_pos and \
                self.target_pos.first == first_pos:
            self.target_pos = None

        if delta is None:
            return

        if not (down_limit <= second_opt.exercise_price <= up_limit and
                down_limit <= first_opt.exercise_price <= up_limit):
            self.write_log('行权价超出两个跳范围，忽略开仓卖出条件')
            return

        if delta > self.threshold1:
            print('大')

            self.target_pos = PosTarget(first=-self.volume, second=self.volume)
            self.take_target_pos()
            return
        elif delta < self.threshold2:
            print('小')
            # 空仓情况，买入当月合约，卖出次月合约
            self.target_pos = PosTarget(first=self.volume, second=-self.volume)
            self.take_target_pos()
            return
        elif delta < self.avg1 and second_pos > 0 and first_pos < 0:
            # 有多仓，平仓

            self.target_pos = PosTarget(first=0, second=0)
            self.take_target_pos()
            return

        elif delta > self.avg1 and second_pos < 0 and first_pos > 0:
            # 平

            self.target_pos = PosTarget(first=0, second=0)
            self.take_target_pos()
            return


    @staticmethod
    def price_tick(etf_price):
        if etf_price < 3:
            return 0.05
        else:
            return 0.1

    def check_expire(self):
        # 检查过期时间
        now = datetime.now()
        first_opt: OptContract = self.contract_manager.get_option_contract(self.first_opt)
        second_opt: OptContract = self.contract_manager.get_option_contract(self.second_opt)
        days1 = distance(dt_a=now, dt_b=first_opt.expire_date)
        days2 = distance(dt_a=now, dt_b=second_opt.expire_date)
        pos1 = self.get_pos(self.first_opt)
        pos2 = self.get_pos(self.second_opt)
        tick1: TickData = self.get_tick(self.first_opt)
        tick2: TickData = self.get_tick(self.second_opt)
        if days1 <= self.days_adv_close and days2 <= self.days_adv_close:
            self.cancel_all()
            if pos1 > 0:
                self.send_order(vt_symbol=self.first_opt,
                                direction=Direction.SHORT,
                                offset=Offset.CLOSE,
                                price=tick1.ask_price_3,
                                volume=pos1)
            elif pos1 < 0:
                self.send_order(vt_symbol=self.first_opt,
                                direction=Direction.LONG,
                                offset=Offset.CLOSE,
                                price=tick1.bid_price_3,
                                volume=abs(pos1))

            if pos2 > 0:
                self.send_order(vt_symbol=self.second_opt,
                                direction=Direction.SHORT,
                                offset=Offset.CLOSE,
                                price=tick2.ask_price_3,
                                volume=pos2)
            elif pos2 < 0:
                self.send_order(vt_symbol=self.second_opt,
                                direction=Direction.LONG,
                                offset=Offset.CLOSE,
                                price=tick2.bid_price_3,
                                volume=abs(pos2))
            if pos1 == pos2 == 0:
                self.inited = False
                self.on_stop()
