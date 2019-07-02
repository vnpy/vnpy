""""""

import sys
import importlib
import traceback
from typing import Sequence
from pathlib import Path
from datetime import datetime
from threading import Thread

from vnpy.event import Event, EventEngine
from vnpy.trader.engine import BaseEngine, MainEngine
from vnpy.trader.constant import Direction, Offset, OrderType, Interval
from vnpy.trader.object import (
    OrderRequest,
    HistoryRequest,
    SubscribeRequest,
    TickData,
    OrderData,
    TradeData,
    PositionData,
    AccountData,
    ContractData,
    LogData,
    BarData
)
from vnpy.trader.rqdata import rqdata_client


APP_NAME = "ScriptTrader"

EVENT_SCRIPT_LOG = "eScriptLog"


class ScriptEngine(BaseEngine):
    """"""
    setting_filename = "script_trader_setting.json"

    def __init__(self, main_engine: MainEngine, event_engine: EventEngine):
        """"""
        super().__init__(main_engine, event_engine, APP_NAME)

        self.get_tick = main_engine.get_tick
        self.get_order = main_engine.get_order
        self.get_trade = main_engine.get_trade
        self.get_position = main_engine.get_position
        self.get_account = main_engine.get_account
        self.get_contract = main_engine.get_contract
        self.get_all_ticks = main_engine.get_all_ticks
        self.get_all_orders = main_engine.get_all_orders
        self.get_all_trades = main_engine.get_all_trades
        self.get_all_positions = main_engine.get_all_positions
        self.get_all_accounts = main_engine.get_all_accounts
        self.get_all_contracts = main_engine.get_all_contracts
        self.get_all_active_orders = main_engine.get_all_active_orders

        self.strategy_active = False
        self.strategy_thread = None

    def init(self):
        """
        Start script engine.
        """
        result = rqdata_client.init()
        if result:
            self.write_log("RQData数据接口初始化成功")

    def start_strategy(self, script_path: str):
        """"""
        if self.strategy_active:
            return
        self.strategy_active = True

        self.strategy_thread = Thread(
            target=self.run_strategy, args=(script_path,))
        self.strategy_thread.start()

        self.write_log("策略交易脚本启动")

    def run_strategy(self, script_path: str):
        """"""
        path = Path(script_path)
        sys.path.append(str(path.parent))

        script_name = path.parts[-1]
        module_name = script_name.replace(".py", "")

        try:
            module = importlib.import_module(module_name)
            importlib.reload(module)
            module.run(self)
        except:     # noqa
            msg = f"触发异常已停止\n{traceback.format_exc()}"
            self.write_log(msg)

    def stop_strategy(self):
        """"""
        if not self.strategy_active:
            return
        self.strategy_active = False

        if self.strategy_thread:
            self.strategy_thread.join()
        self.strategy_thread = None

        self.write_log("策略交易脚本停止")

    def send_order(
        self,
        vt_symbol: str,
        price: float,
        volume: float,
        direction: Direction,
        offset: Offset,
        order_type: OrderType
    ) -> str:
        """"""
        contract = self.get_contract(vt_symbol)
        if not contract:
            return ""

        req = OrderRequest(
            symbol=contract.symbol,
            exchange=contract.exchange,
            type=order_type,
            volume=volume,
            price=price,
            offset=offset
        )

        vt_orderid = self.main_engine.send_order(req, contract.gateway_name)
        return vt_orderid

    def subscribe(self, vt_symbols):
        """"""
        for vt_symbol in vt_symbols:
            contract = self.main_engine.get_contract(vt_symbol)
            if contract:
                req = SubscribeRequest(
                    symbol=contract.symbol,
                    exchange=contract.exchange
                )
                self.main_engine.subscribe(req, contract.gateway_name)

    def buy(self, vt_symbol: str, price: str, volume: str, order_type: OrderType = OrderType.LIMIT) -> str:
        """"""
        return self.send_order(vt_symbol, price, volume, Direction.LONG, Offset.OPEN, order_type)

    def sell(self, vt_symbol: str, price: str, volume: str, order_type: OrderType = OrderType.LIMIT) -> str:
        """"""
        return self.send_order(vt_symbol, price, volume, Direction.SHORT, Offset.CLOSE, order_type)

    def short(self, vt_symbol: str, price: str, volume: str, order_type: OrderType = OrderType.LIMIT) -> str:
        """"""
        return self.send_order(vt_symbol, price, volume, Direction.SHORT, Offset.OPEN, order_type)

    def cover(self, vt_symbol: str, price: str, volume: str, order_type: OrderType = OrderType.LIMIT) -> str:
        """"""
        return self.send_order(vt_symbol, price, volume, Direction.LONG, Offset.CLOSE, order_type)

    def cancel_order(self, vt_orderid: str) -> None:
        """"""
        order = self.get_order(vt_orderid)
        if not order:
            return

        req = order.create_cancel_request()
        self.main_engine.cancel_order(req, order.gateway_name)

    def get_tick(self, vt_symbol: str) -> TickData:
        """"""
        return self.main_engine.get_tick(vt_symbol)

    def get_ticks(self, vt_symbols: Sequence[str]) -> Sequence[TickData]:
        """"""
        ticks = []
        for vt_symbol in vt_symbols:
            tick = self.main_engine.get_tick(vt_symbol)
            ticks.append(tick)
        return ticks

    def get_order(self, vt_orderid: str) -> OrderData:
        """"""
        return self.main_engine.get_order(vt_orderid)

    def get_orders(self, vt_orderids: Sequence[str]) -> Sequence[OrderData]:
        """"""
        orders = []
        for vt_orderid in vt_orderids:
            order = self.main_engine.get_order(vt_orderid)
            orders.append(order)
        return orders

    def get_trades(self, vt_orderid: str) -> Sequence[TradeData]:
        """"""
        trades = []
        all_trades = self.main_engine.get_all_trades()

        for trade in all_trades:
            if trade.vt_orderid == vt_orderid:
                trades.append(trade)

        return trades

    def get_all_active_orders(self) -> Sequence[OrderData]:
        """"""
        return self.main_engine.get_all_active_orders()

    def get_contract(self, vt_symbol) -> ContractData:
        """"""
        return self.main_engine.get_contract(vt_symbol)

    def get_all_contracts(self) -> Sequence[ContractData]:
        """"""
        return self.main_engine.get_all_contracts()

    def get_account(self, vt_accountid: str) -> AccountData:
        """"""
        return self.main_engine.get_account(vt_accountid)

    def get_all_accounts(self) -> Sequence[AccountData]:
        """"""
        return self.main_engine.get_all_accounts()

    def get_position(self, vt_positionid: str) -> PositionData:
        """"""
        return self.main_engine.get_position(vt_positionid)

    def get_all_positions(self) -> Sequence[AccountData]:
        """"""
        return self.main_engine.get_all_positions()

    def get_bars(self, vt_symbol: str, start_date: str, interval: Interval) -> Sequence[BarData]:
        """"""
        contract = self.main_engine.get_contract(vt_symbol)
        if not contract:
            return []

        start = datetime.strptime(start_date, "%Y%m%d")

        req = HistoryRequest(
            symbol=contract.symbol,
            exchange=contract.exchange,
            start=start,
            interval=interval
        )

        bars = rqdata_client.query_history(req)
        if not bars:
            return []
        return bars

    def write_log(self, msg: str) -> None:
        """"""
        log = LogData(msg=msg, gateway_name=APP_NAME)
        print(f"{log.time}\t{log.msg}")

        event = Event(EVENT_SCRIPT_LOG, log)
        self.event_engine.put(event)
