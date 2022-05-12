# -*- coding:utf-8 -*-
"""
@author: fsksf

@since: 2022/4/28 8:35
"""
from typing import List, Dict
from datetime import datetime, time
import pandas as pd
from dataclasses import dataclass
from sqlalchemy import desc
from jqdatasdk import opt, query
from datetime import datetime, timedelta
from fnlib.options import opt_compose_price, get_rest_pct, distance
from fnlib.balck76 import calculate_impv
from fnlib.obj import Period, Contract, OptContract
from fnlib.contract_manager import ContractManager
from vnpy.trader.object import TickData, SubscribeRequest, ContractData, BarData
from vnpy.trader.constant import Direction, Offset, OptionType, Exchange
from vnpy.app.portfolio_strategy import StrategyTemplate, StrategyEngine
from vnpy.app.portfolio_strategy.jq import login_jq


@dataclass
class PosTarget:
    leg_2: int = None
    leg_1: int = None

    def __bool__(self):
        return self.leg_2 is None and self.leg_1 is None


class WCIVStrategy(StrategyTemplate):
    """"""

    author = "kangyuqiang"
    r: float = 0.02
    volume: int = 1
    threshold_up: float = 0.02                          # 阈值1
    threshold_down: float = -0.02                       # 阈值2
    avg1: float = 0.0                                   # 均值
    days_adv_change: int = 3
    days_adv_close: int = 4
    adv_close_time = time(hour=13, minute=20, second=0)
    parameters = [
        "volume",
        "r",
        "threshold_up",
        "threshold_down",
        "avg1",
        "days_adv_change",
        "days_adv_close",
    ]
    variables = [
        "pos",
        "leg_2_iv",
        "leg_1_iv",
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
        #                          # 当月为第二条腿    # 次月为第一条腿
        self.underlying_symbol, self.leg_2_opt, self.leg_1_opt = vt_symbols[:3]
        self.leg_2_iv = None
        self.leg_1_iv = None
        self.delta_iv = None
        self.pos: Dict[str, int] = dict()
        self.target_pos: PosTarget = None
        self._last_tick: Dict[str, TickData] = {}
        self._last_Bar: Dict[str, BarData] = {}
        self._synthetic_futures_price: Dict[str, float] = {}
        self._sbd = set()
        self.order_start_dt = None
        self.order_cancel_count = 10
        self.trading = True

    def on_init(self):
        """
        Callback when strategy is inited.
        """

        self.write_log("策略初始化")
        now = datetime.now()
        start = now - timedelta(days=30 * 6)
        end = now + timedelta(days=30 * 6)
        with login_jq():
            df: pd.DataFrame = opt.run_query(query(opt.OPT_CONTRACT_INFO).filter(
                opt.OPT_CONTRACT_INFO.expire_date >= start,
                opt.OPT_CONTRACT_INFO.expire_date <= end,
                opt.OPT_CONTRACT_INFO.underlying_symbol == self.underlying_symbol.replace('.SSE', '.XSHG')
            ).order_by(desc(opt.OPT_CONTRACT_INFO.id)))

            df['code'] = df['code'].str.replace('.XSHG', '.SSE')
            df['underlying_symbol'] = df['underlying_symbol'].str.replace('.XSHG', '.SSE')
            self.contract_manager.opt_contract_from_df(df)
        self.write_log('初始化完成')

    def on_start(self):
        """
        Callback when strategy is started.
        """
        self.trading = True
        self.write_log("策略启动")

    def on_stop(self):
        """
        Callback when strategy is stopped.
        """
        self.write_log("策略停止")

    def on_bars(self, bars: Dict[str, BarData]) -> None:
        self.cancel_all()
        for bar in bars.values():
            self._last_Bar[bar.vt_symbol] = bar
        underlying_bar = bars.pop(self.underlying_symbol)
        self.update_underlying_bar(underlying_bar)
        self.update_options_bar()

    def get_tick(self, symbol):
        return self._last_tick.get(symbol)

    def get_bar(self, symbol):
        return self._last_Bar.get(symbol)

    def get_pos(self, vt_symbol):
        return self.pos.get(vt_symbol, 0)

    def update_options_bar(self):
        """
        计算隐含波动率
        """
        leg_2_bar: BarData = self.get_bar(self.leg_2_opt)
        leg_1_bar: BarData = self.get_bar(self.leg_1_opt)
        if not leg_2_bar or not leg_1_bar:
            self.write_log(f'计算波动率，行情有空, {leg_2_bar}, {leg_1_bar}')
            return
        leg_2_opt = self.contract_manager.get_option_contract(leg_2_bar.vt_symbol)
        leg_1_opt = self.contract_manager.get_option_contract(leg_1_bar.vt_symbol)
        self.write_log(f"第一第二期权标的 {leg_2_opt}, {leg_1_opt}")
        leg_2_price = (leg_2_bar.close_price + leg_2_bar.close_price) / 2
        leg_1_price = (leg_1_bar.close_price + leg_1_bar.close_price) / 2
        leg_2_period = self.contract_manager.get_contract_period(leg_2_opt, dt=leg_2_bar.datetime)
        leg_1_period = self.contract_manager.get_contract_period(leg_1_opt, dt=leg_2_bar.datetime)
        leg_2_atm = self._synthetic_futures_price.get(leg_2_period)
        leg_1_atm = self._synthetic_futures_price.get(leg_1_period)
        if leg_2_atm is None or leg_1_atm is None:
            self.write_log(f'合成期货的价格为None: {leg_2_atm}, {leg_1_atm}')
            return
        leg_2_iv = calculate_impv(
            price=leg_2_price,
            s=leg_2_atm,
            k=leg_2_opt.exercise_price,
            r=self.r,
            t=get_rest_pct(end_dt=leg_2_opt.expire_date, now=leg_2_bar.datetime),
            cp=1 if leg_2_opt.contract_type == 'CO' else -1
        )
        leg_1_iv = calculate_impv(
            price=leg_1_price,
            s=leg_1_atm,
            k=leg_1_opt.exercise_price,
            r=self.r,
            t=get_rest_pct(end_dt=leg_1_opt.expire_date, now=leg_2_bar.datetime),
            cp=1 if leg_1_opt.contract_type == 'CO' else -1
        )
        self.leg_2_iv = round(leg_2_iv, 4)
        self.leg_1_iv = round(leg_1_iv, 4)
        self.put_event()
        self.check_iv()
        print(f'{leg_2_bar.datetime} 波动率 {self.leg_2_iv}, {self.leg_1_iv}, {self.delta_iv}')

    def update_underlying_bar(self, bar: BarData):
        """
        计算合成期货价格
        """
        underlying_bar: BarData = self.get_bar(self.underlying_symbol)
        if underlying_bar is None:
            return
        price = underlying_bar.close_price
        for p in [Period.curr_month, Period.next_month]:
            call, put = self.contract_manager.get_equal_opts(
                underlying=self.underlying_symbol,
                price=price,
                dt=underlying_bar.datetime,
                period=p,
                days_adv_change=self.days_adv_change
            )
            if call.code not in self._sbd:
                call_symbol, call_ex = call.code.rsplit('.')
                self._sbd.add(call.code)

            if put.code not in self._sbd:
                put_symbol, put_ex = put.code.rsplit('.')
                self._sbd.add(put.code)

            if call is None or put is None:
                self.write_log('平值合约计算出来为None')
                continue
            call_bar: BarData = self.get_bar(call.code)
            put_bar: BarData = self.get_bar(put.code)
            if call_bar is None or put_bar is None:
                print(f'平值合约的行情为: {call_bar}, {put_bar}')
                continue
            futures_price = opt_compose_price(
                c_price=call_bar.close_price,
                p_price=put_bar.close_price,
                r=self.r,
                rest_pct=get_rest_pct(end_dt=call.expire_date, now=underlying_bar.datetime),
                exercise_price=call.exercise_price
            )
            # 合成期货价格
            self._synthetic_futures_price[p] = futures_price

    def delta(self):
        if self.leg_2_iv is None or self.leg_1_iv is None:
            return None
        # 当月 - 次月
        self.delta_iv = round(self.leg_2_iv - self.leg_1_iv, 4)
        return self.delta_iv

    def if_hege(self):
        leg_2_pos = self.get_pos(self.leg_2_opt)
        leg_1_pos = self.get_pos(self.leg_1_opt)
        if leg_2_pos == -leg_1_pos:
            return True
        else:
            return False

    def spread_pos(self):
        leg_2_pos = self.get_pos(self.leg_2_opt)
        leg_1_pos = self.get_pos(self.leg_1_opt)
        mi = min(abs(leg_2_pos), abs(leg_1_pos))
        if leg_2_pos == 0 or leg_1_pos == 0:
            return 0
        elif leg_2_pos > 0 and leg_1_pos < 0:
            return mi
        elif leg_2_pos < 0 and leg_1_pos > 0:
            return -mi
        else:
            return 0

    def take_target_pos(self):
        leg_2_pos = self.get_pos(self.leg_2_opt)
        leg_1_pos = self.get_pos(self.leg_1_opt)

        leg_2_bar: BarData = self.get_bar(self.leg_2_opt)
        leg_1_bar: BarData = self.get_bar(self.leg_1_opt)
        if not self.if_hege():
            # 先处理不平衡的问题
            leg_2_diff_pos = -leg_1_pos - leg_2_pos

            # 当前有持仓
            # 开仓
            if leg_2_diff_pos > 0:
                if leg_2_pos >= 0:
                    print('不平衡，先买入当月合约')
                    self.buy(
                        vt_symbol=self.leg_2_opt,
                        volume=leg_2_diff_pos,
                        price=leg_2_bar.close_price
                    )
                else:
                    if abs(leg_2_pos) > leg_2_diff_pos:
                        volume = leg_2_diff_pos
                    else:
                        volume = leg_2_pos
                    self.cover(
                        vt_symbol=self.leg_2_opt,
                        volume=abs(volume),
                        price=leg_2_bar.close_price
                    )
            elif leg_2_diff_pos < 0:
                if leg_2_pos <= 0:
                    self.short(
                        vt_symbol=self.leg_2_opt,
                        volume=abs(leg_2_diff_pos),
                        price=leg_2_bar.close_price
                    )
                else:
                    if leg_2_pos > abs(leg_2_diff_pos):
                        volume = leg_2_diff_pos
                    else:
                        volume = leg_2_pos
                    self.sell(
                        vt_symbol=self.leg_2_opt,
                        volume=abs(volume),
                        price=leg_2_bar.close_price
                    )

        # 主动
        leg_1_diff_pos = self.target_pos.leg_1 - leg_1_pos
        if self.target_pos.leg_1 != 0:
            if leg_1_diff_pos > 0:
                print('空仓情况，先买多次月合约')
                self.buy(
                    vt_symbol=self.leg_1_opt,
                    volume=leg_1_diff_pos,
                    price=leg_1_bar.close_price
                )
            elif leg_1_diff_pos < 0:
                print('空仓情况，先卖空次月合约')
                self.short(
                    vt_symbol=self.leg_1_opt,
                    volume=abs(leg_1_diff_pos),
                    price=leg_1_bar.close_price
                )
        else:
            if leg_1_diff_pos > 0:
                print('平仓次月合约')
                self.cover(
                    vt_symbol=self.leg_1_opt,
                    volume=leg_1_diff_pos,
                    price=leg_1_bar.close_price
                )
            elif leg_1_diff_pos < 0:
                print('空仓情况，先买入次月合约')
                self.sell(
                    vt_symbol=self.leg_1_opt,
                    volume=abs(leg_1_diff_pos),
                    price=leg_1_bar.close_price
                )

    def check_iv(self):
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
        leg_2_pos = self.get_pos(self.leg_2_opt)
        leg_1_pos = self.get_pos(self.leg_1_opt)
        leg_2_opt: OptContract = self.contract_manager.get_option_contract(self.leg_2_opt)
        leg_1_opt: OptContract = self.contract_manager.get_option_contract(self.leg_1_opt)
        last_underlying_bar: BarData = self.get_bar(self.underlying_symbol)

        down_limit, up_limit = self.price_limit(last_underlying_bar.close_price)
        if self.target_pos and \
                self.target_pos.leg_1 == leg_1_pos and \
                self.target_pos.leg_2 == leg_2_pos:
            self.target_pos = None

        if delta is None:
            return

        if not (down_limit <= leg_1_opt.exercise_price <= up_limit and
                down_limit <= leg_2_opt.exercise_price <= up_limit):
            self.write_log('行权价超出两个跳范围，忽略开仓卖出条件')
            return
        if delta < self.avg1 and self.spread_pos() < 0:
            # 有多仓，平仓
            print('平')
            self.target_pos = PosTarget(leg_2=0, leg_1=0)
            self.take_target_pos()
            return

        elif delta > self.avg1 and self.spread_pos() > 0:
            # 平
            self.target_pos = PosTarget(leg_2=0, leg_1=0)
            self.take_target_pos()
            return
        elif delta > self.threshold_up and self.spread_pos() == 0:
            print('大')
            self.target_pos = PosTarget(leg_2=-self.volume, leg_1=self.volume)
            self.take_target_pos()
            return
        elif delta < self.threshold_down and self.spread_pos() == 0:
            print('小')
            # 空仓情况，买入当月合约，卖出次月合约
            self.target_pos = PosTarget(leg_2=self.volume, leg_1=-self.volume)
            self.take_target_pos()
            return

    @staticmethod
    def price_limit(etf_price):
        if etf_price <= 2.925:
            return etf_price - 0.05 * 2, etf_price + 0.05 * 2
        elif 2.925 < etf_price <= 2.975:
            return etf_price - 0.05 * 2, etf_price + 0.05 + 0.1
        elif 2.975 < etf_price <= 3.05:
            return etf_price - 0.05 * 2, etf_price + 0.1 * 2
        elif 3.05 < etf_price <= 3.15:
            return etf_price - 0.05 - 0.1, etf_price + 0.1 * 2
        elif etf_price > 3.1:
            return etf_price - 0.1 * 2, etf_price + 0.1 * 2

    def check_expire(self):
        # 检查过期时间
        now = datetime.now()
        leg_2_opt: OptContract = self.contract_manager.get_option_contract(self.leg_2_opt)
        leg_1_opt: OptContract = self.contract_manager.get_option_contract(self.leg_1_opt)
        days1 = distance(dt_a=now, dt_b=leg_2_opt.expire_date)
        days2 = distance(dt_a=now, dt_b=leg_1_opt.expire_date)
        pos_2 = self.get_pos(self.leg_2_opt)
        pos_1 = self.get_pos(self.leg_1_opt)
        bar1: BarData = self.get_bar(self.leg_2_opt)
        bar2: BarData = self.get_bar(self.leg_1_opt)
        tm = now.time()
        if days1 <= self.days_adv_close and days2 <= self.days_adv_close and tm > self.adv_close_time:
            self.write_log('临近交易日，触发平仓并关闭策略')
            self.cancel_all()
            if pos_2 > 0:
                self.sell(vt_symbol=self.leg_2_opt,
                          price=bar1.close_price,
                          volume=pos_2)
            elif pos_2 < 0:
                self.cover(vt_symbol=self.leg_2_opt,
                           price=bar1.close_price,
                           volume=abs(pos_2))

            if pos_1 > 0:
                self.sell(vt_symbol=self.leg_1_opt,
                          price=bar2.close_price,
                          volume=pos_1)
            elif pos_1 < 0:
                self.cover(vt_symbol=self.leg_1_opt,
                           price=bar2.close_price,
                           volume=abs(pos_1))
            if pos_2 == pos_1 == 0:
                self.inited = False
                self.on_stop()
