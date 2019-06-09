# encoding: UTF-8
"""
Author: KeKe
Please install tiger-api before use.
pip install tigeropen
"""

from copy import copy
from datetime import datetime
from multiprocessing.dummy import Pool
from queue import Empty, Queue
import functools
import traceback

import pandas as pd
from pandas import DataFrame

from tigeropen.tiger_open_config import TigerOpenClientConfig
from tigeropen.common.consts import Language, Currency, Market
from tigeropen.quote.quote_client import QuoteClient
from tigeropen.trade.trade_client import TradeClient
from tigeropen.trade.domain.order import ORDER_STATUS
from tigeropen.push.push_client import PushClient
from tigeropen.common.exceptions import ApiException

from vnpy.trader.constant import Direction, Product, Status, OrderType, Exchange
from vnpy.trader.gateway import BaseGateway
from vnpy.trader.object import (
    TickData,
    OrderData,
    TradeData,
    AccountData,
    ContractData,
    PositionData,
    SubscribeRequest,
    OrderRequest,
    CancelRequest,
)

PRODUCT_VT2TIGER = {
    Product.EQUITY: "STK",
    Product.OPTION: "OPT",
    Product.WARRANT: "WAR",
    Product.WARRANT: "IOPT",
    Product.FUTURES: "FUT",
    Product.OPTION: "FOP",
    Product.FOREX: "CASH",
}

DIRECTION_VT2TIGER = {
    Direction.LONG: "BUY",
    Direction.SHORT: "SELL",
}

DIRECTION_TIGER2VT = {
    "BUY": Direction.LONG,
    "SELL": Direction.SHORT,
    "sell": Direction.SHORT,
}

ORDERTYPE_VT2TIGER = {
    OrderType.LIMIT: "LMT",
    OrderType.MARKET: "MKT",
}

STATUS_TIGER2VT = {
    ORDER_STATUS.PENDING_NEW: Status.SUBMITTING,
    ORDER_STATUS.NEW: Status.SUBMITTING,
    ORDER_STATUS.HELD: Status.SUBMITTING,
    ORDER_STATUS.PARTIALLY_FILLED: Status.PARTTRADED,
    ORDER_STATUS.FILLED: Status.ALLTRADED,
    ORDER_STATUS.CANCELLED: Status.CANCELLED,
    ORDER_STATUS.PENDING_CANCEL: Status.CANCELLED,
    ORDER_STATUS.REJECTED: Status.REJECTED,
    ORDER_STATUS.EXPIRED: Status.NOTTRADED
}

PUSH_STATUS_TIGER2VT = {
    "Invalid": Status.REJECTED,
    "Initial": Status.SUBMITTING,
    "PendingCancel": Status.CANCELLED,
    "Cancelled": Status.CANCELLED,
    "Submitted": Status.SUBMITTING,
    "PendingSubmit": Status.SUBMITTING,
    "Filled": Status.ALLTRADED,
    "Inactive": Status.REJECTED
}


class TigerGateway(BaseGateway):
    """"""
    default_setting = {
        "tiger_id": "",
        "account": "",
        "服务器": ["标准", "环球", "仿真"],
        "private_key": "",
    }

    exchanges = [
        Exchange.SEHK,
        Exchange.SMART,
        Exchange.SSE,
        Exchange.SZSE
    ]

    def __init__(self, event_engine):
        """Constructor"""
        super(TigerGateway, self).__init__(event_engine, "TIGER")

        self.tiger_id = ""
        self.account = ""
        self.server = ""
        self.language = ""

        self.client_config = None
        self.quote_client = None
        self.push_client = None

        self.local_id = 1000000
        self.tradeid = 0

        self.active = False
        self.queue = Queue()
        self.pool = None

        self.ID_TIGER2VT = {}
        self.ID_VT2TIGER = {}
        self.ticks = {}
        self.trades = set()
        self.contracts = {}
        self.symbol_names = {}

        self.push_connected = False
        self.subscribed_symbols = set()

    def run(self):
        """"""
        while self.active:
            try:
                func, args = self.queue.get(timeout=0.1)
                func(*args)
            except Empty:
                pass

    def add_task(self, func, *args):
        """"""
        self.queue.put((func, [*args]))

    def connect(self, setting: dict):
        """"""
        self.private_key = setting["private_key"]
        self.tiger_id = setting["tiger_id"]
        self.server = setting["服务器"]
        self.account = setting["account"]
        self.languege = Language.zh_CN

        # Start thread pool for REST call
        self.active = True
        self.pool = Pool(5)
        self.pool.apply_async(self.run)

        # Put connect task into quque.
        self.init_client_config()
        self.add_task(self.connect_quote)
        self.add_task(self.connect_trade)
        self.add_task(self.connect_push)

    def init_client_config(self, sandbox=False):
        """"""
        self.client_config = TigerOpenClientConfig(sandbox_debug=sandbox)
        self.client_config.private_key = self.private_key
        self.client_config.tiger_id = self.tiger_id
        self.client_config.account = self.account
        self.client_config.language = self.language

    def connect_quote(self):
        """
        Connect to market data server.
        """
        try:
            self.quote_client = QuoteClient(self.client_config)
            self.symbol_names = dict(
                self.quote_client.get_symbol_names(lang=Language.zh_CN))
            self.query_contract()
        except ApiException:
            self.write_log("查询合约失败")
            return

        self.write_log("行情接口连接成功")
        self.write_log("合约查询成功")

    def connect_trade(self):
        """
        Connect to trade server.
        """
        self.trade_client = TradeClient(self.client_config)
        try:
            self.add_task(self.query_order)
            self.add_task(self.query_position)
            self.add_task(self.query_account)
        except ApiException:
            self.write_log("交易接口连接失败")
            return

        self.write_log("交易接口连接成功")

    def connect_push(self):
        """
        Connect to push server.
        """
        protocol, host, port = self.client_config.socket_host_port
        self.push_client = PushClient(host, port, (protocol == "ssl"))

        self.push_client.quote_changed = self.on_quote_change
        self.push_client.asset_changed = self.on_asset_change
        self.push_client.position_changed = self.on_position_change
        self.push_client.order_changed = self.on_order_change
        self.push_client.connect_callback = self.on_push_connected

        self.push_client.connect(
            self.client_config.tiger_id, self.client_config.private_key)

    def subscribe(self, req: SubscribeRequest):
        """"""
        self.subscribed_symbols.add(req.symbol)

        if self.push_connected:
            self.push_client.subscribe_quote([req.symbol])

    def on_push_connected(self):
        """"""
        self.push_connected = True
        self.write_log("推送接口连接成功")

        self.push_client.subscribe_asset()
        self.push_client.subscribe_position()
        self.push_client.subscribe_order()

        self.push_client.subscribe_quote(list(self.subscribed_symbols))

    def on_quote_change(self, tiger_symbol: str, data: list, trading: bool):
        """"""
        data = dict(data)
        symbol, exchange = convert_symbol_tiger2vt(tiger_symbol)

        tick = self.ticks.get(symbol, None)
        if not tick:
            tick = TickData(
                symbol=symbol,
                exchange=exchange,
                gateway_name=self.gateway_name,
                datetime=datetime.now(),
                name=self.symbol_names[symbol],
            )
            self.ticks[symbol] = tick

        tick.datetime = datetime.fromtimestamp(int(data["latest_time"]) / 1000)
        tick.pre_close = data.get("prev_close", tick.pre_close)
        tick.last_price = data.get("latest_price", tick.last_price)
        tick.volume = data.get("volume", tick.volume)
        tick.open_price = data.get("open", tick.open_price)
        tick.high_price = data.get("high", tick.high_price)
        tick.low_price = data.get("low", tick.low_price)
        tick.ask_price_1 = data.get("ask_price", tick.ask_price_1)
        tick.bid_price_1 = data.get("bid_price", tick.bid_price_1)
        tick.ask_volume_1 = data.get("ask_size", tick.ask_volume_1)
        tick.bid_volume_1 = data.get("bid_size", tick.bid_volume_1)

        self.on_tick(copy(tick))

    def on_asset_change(self, tiger_account: str, data: list):
        """"""
        data = dict(data)
        if "net_liquidation" not in data:
            return

        account = AccountData(
            accountid=tiger_account,
            balance=data["net_liquidation"],
            frozen=0.0,
            gateway_name=self.gateway_name,
        )
        self.on_account(account)

    def on_position_change(self, tiger_account: str, data: list):
        """"""
        data = dict(data)
        symbol, exchange = convert_symbol_tiger2vt(data["origin_symbol"])

        pos = PositionData(
            symbol=symbol,
            exchange=exchange,
            direction=Direction.NET,
            volume=int(data["quantity"]),
            frozen=0.0,
            price=data["average_cost"],
            pnl=data["unrealized_pnl"],
            gateway_name=self.gateway_name,
        )
        self.on_position(pos)

    def on_order_change(self, tiger_account: str, data: list):
        """"""
        data = dict(data)
        symbol, exchange = convert_symbol_tiger2vt(data["origin_symbol"])
        status = PUSH_STATUS_TIGER2VT[data["status"]]

        order = OrderData(
            symbol=symbol,
            exchange=exchange,
            orderid=self.ID_TIGER2VT.get(
                str(data["order_id"]), self.get_new_local_id()),
            direction=Direction.NET,
            price=data.get("limit_price", 0),
            volume=data["quantity"],
            traded=data["filled"],
            status=status,
            time=datetime.fromtimestamp(
                data["order_time"] / 1000).strftime("%H:%M:%S"),
            gateway_name=self.gateway_name,
        )
        self.on_order(order)

        if status == Status.ALLTRADED:
            self.tradeid += 1

            trade = TradeData(
                symbol=symbol,
                exchange=exchange,
                direction=Direction.NET,
                tradeid=self.tradeid,
                orderid=self.ID_TIGER2VT[str(data["order_id"])],
                price=data["avg_fill_price"],
                volume=data["filled"],
                time=datetime.fromtimestamp(
                    data["trade_time"] / 1000).strftime("%H:%M:%S"),
                gateway_name=self.gateway_name,
            )
            self.on_trade(trade)

    def get_new_local_id(self):
        self.local_id += 1
        return self.local_id

    def send_order(self, req: OrderRequest):
        """"""
        local_id = self.get_new_local_id()
        order = req.create_order_data(local_id, self.gateway_name)

        self.on_order(order)
        self.add_task(self._send_order, req, local_id)
        return order.vt_orderid

    def _send_order(self, req: OrderRequest, local_id):
        """"""
        currency = config_symbol_currency(req.symbol)
        try:
            contract = self.trade_client.get_contracts(
                symbol=req.symbol, currency=currency)[0]
            order = self.trade_client.create_order(
                account=self.account,
                contract=contract,
                action=DIRECTION_VT2TIGER[req.direction],
                order_type=ORDERTYPE_VT2TIGER[req.type],
                quantity=int(req.volume),
                limit_price=req.price,
            )
            self.ID_TIGER2VT[str(order.order_id)] = local_id
            self.ID_VT2TIGER[local_id] = str(order.order_id)

            self.trade_client.place_order(order)

        except:  # noqa
            traceback.print_exc()
            self.write_log("发单失败")
            return

    def cancel_order(self, req: CancelRequest):
        """"""
        self.add_task(self._cancel_order, req)

    def _cancel_order(self, req: CancelRequest):
        """"""
        try:
            order_id = self.ID_VT2TIGER[req.orderid]
            data = self.trade_client.cancel_order(order_id=order_id)
        except ApiException:
            self.write_log(f"撤单失败：{req.orderid}")

        if not data:
            self.write_log("撤单成功")

    def query_contract(self):
        """"""
        # HK Stock

        symbols_names_HK = self.quote_client.get_symbol_names(
            lang=Language.zh_CN, market=Market.HK)
        contract_names_HK = DataFrame(
            symbols_names_HK, columns=["symbol", "name"])

        contractList = list(contract_names_HK["symbol"])
        i, n = 0, len(contractList)
        result = pd.DataFrame()
        while i < n:
            i += 50
            c = contractList[i - 50:i]
            r = self.quote_client.get_trade_metas(c)
            result = result.append(r)

        contract_detail_HK = result.sort_values(by="symbol", ascending=True)
        contract_HK = pd.merge(
            contract_names_HK, contract_detail_HK, how="left", on="symbol")

        for ix, row in contract_HK.iterrows():
            contract = ContractData(
                symbol=row["symbol"],
                exchange=Exchange.SEHK,
                name=row["name"],
                product=Product.EQUITY,
                size=1,
                min_volume=row["lot_size"],
                pricetick=row["min_tick"],
                net_position=True,
                gateway_name=self.gateway_name,
            )
            self.on_contract(contract)
            self.contracts[contract.vt_symbol] = contract

        # US Stock
        symbols_names_US = self.quote_client.get_symbol_names(
            lang=Language.zh_CN, market=Market.US)
        contract_US = DataFrame(symbols_names_US, columns=["symbol", "name"])

        for ix, row in contract_US.iterrows():
            contract = ContractData(
                symbol=row["symbol"],
                exchange=Exchange.SMART,
                name=row["name"],
                product=Product.EQUITY,
                size=1,
                min_volume=100,
                pricetick=0.001,
                gateway_name=self.gateway_name,
            )
            self.on_contract(contract)
            self.contracts[contract.vt_symbol] = contract

        # CN Stock
        symbols_names_CN = self.quote_client.get_symbol_names(
            lang=Language.zh_CN, market=Market.CN)
        contract_CN = DataFrame(symbols_names_CN, columns=["symbol", "name"])

        for ix, row in contract_CN.iterrows():
            symbol = row["symbol"]
            symbol, exchange = convert_symbol_tiger2vt(symbol)

            contract = ContractData(
                symbol=symbol,
                exchange=exchange,
                name=row["name"],
                product=Product.EQUITY,
                size=1,
                min_volume=100,
                pricetick=0.001,
                gateway_name=self.gateway_name,
            )
            self.on_contract(contract)
            self.contracts[contract.vt_symbol] = contract

    def query_account(self):
        """"""
        try:
            assets = self.trade_client.get_assets()
        except ApiException:
            self.write_log("查询资金失败")
            return

        for i in assets:
            account = AccountData(
                accountid=self.account,
                balance=i.summary.net_liquidation,
                frozen=0.0,
                gateway_name=self.gateway_name,
            )

            self.on_account(account)

    def query_position(self):
        """"""
        try:
            position = self.trade_client.get_positions()
        except ApiException:
            self.write_log("查询持仓失败")
            return

        for i in position:
            symbol, exchange = convert_symbol_tiger2vt(i.contract.symbol)

            pos = PositionData(
                symbol=symbol,
                exchange=exchange,
                direction=Direction.NET,
                volume=int(i.quantity),
                frozen=0.0,
                price=i.average_cost,
                pnl=float(i.unrealized_pnl),
                gateway_name=self.gateway_name,
            )

            self.on_position(pos)

    def query_order(self):
        """"""
        try:
            data = self.trade_client.get_orders()
            data = sorted(data, key=lambda x: x.order_time, reverse=False)
        except:  # noqa
            traceback.print_exc()
            self.write_log("查询委托失败")
            return

        self.process_order(data)
        self.process_deal(data)

    def close(self):
        """"""
        self.active = False

        if self.push_client:
            self.push_client.disconnect()

    def process_order(self, data):
        """"""
        for i in data:
            symbol, exchange = convert_symbol_tiger2vt(str(i.contract))
            local_id = self.get_new_local_id()

            order = OrderData(
                symbol=symbol,
                exchange=exchange,
                orderid=local_id,
                direction=Direction.NET,
                price=i.limit_price if i.limit_price else 0.0,
                volume=i.quantity,
                traded=i.filled,
                status=STATUS_TIGER2VT[i.status],
                time=datetime.fromtimestamp(
                    i.order_time / 1000).strftime("%H:%M:%S"),
                gateway_name=self.gateway_name,
            )
            self.ID_TIGER2VT[str(i.order_id)] = local_id
            self.on_order(order)

        self.ID_VT2TIGER = {v: k for k, v in self.ID_TIGER2VT.items()}

    def process_deal(self, data):
        """
        Process trade data for both query and update.
        """
        for i in data:
            if i.status == ORDER_STATUS.PARTIALLY_FILLED or i.status == ORDER_STATUS.FILLED:
                symbol, exchange = convert_symbol_tiger2vt(str(i.contract))
                self.tradeid += 1

                trade = TradeData(
                    symbol=symbol,
                    exchange=exchange,
                    direction=Direction.NET,
                    tradeid=self.tradeid,
                    orderid=self.ID_TIGER2VT[str(i.order_id)],
                    price=i.avg_fill_price,
                    volume=i.filled,
                    time=datetime.fromtimestamp(
                        i.trade_time / 1000).strftime("%H:%M:%S"),
                    gateway_name=self.gateway_name,
                )

                self.on_trade(trade)


@functools.lru_cache()
def convert_symbol_tiger2vt(symbol):
    """
    Convert symbol from vt to tiger.
    """
    if symbol.encode("UTF-8").isalpha():
        exchange = Exchange.SMART
    else:
        if len(symbol) < 6:
            exchange = Exchange.SEHK
        elif symbol.startswith("6"):
            exchange = Exchange.SSE
        elif symbol.endswith(".SH"):
            exchange = Exchange.SSE
            symbol = symbol.strip(".SH")
        else:
            exchange = Exchange.SZSE
    return symbol, exchange


@functools.lru_cache()
def convert_symbol_vt2tiger(symbol, exchange):
    """
    Convert symbol from vt to tiger.
    """
    if exchange == Exchange.SSE and symbol.startswith("0"):
        symbol = symbol + ".SH"
    else:
        symbol = symbol
    return symbol


@functools.lru_cache()
def config_symbol_currency(symbol):
    """
    Config symbol to corresponding currency
    """
    if symbol.encode("UTF-8").isalpha():
        currency = Currency.USD
    else:
        if len(symbol) < 6:
            currency = Currency.HKD
        else:
            currency = Currency.CNH
    return currency
