# encoding: UTF-8
"""
Please install tiger-api before use.
pip install tigeropen
"""

from copy import copy
from datetime import datetime
from multiprocessing.dummy import Pool
from queue import Empty, Queue
import functools

import pandas as pd
from pandas import DataFrame

from tigeropen.tiger_open_config import TigerOpenClientConfig 
from tigeropen.common.consts import Language, Currency, Market
from tigeropen.quote.quote_client import QuoteClient
from tigeropen.trade.trade_client import TradeClient
from tigeropen.trade.domain.order import ORDER_STATUS
from tigeropen.push.push_client import PushClient
from tigeropen.common.exceptions import ApiException

from vnpy.trader.constant import Direction, Product, Status, PriceType, Exchange
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

PRICETYPE_VT2TIGER = {
    PriceType.LIMIT: "LMT",
    PriceType.MARKET: "MKT",
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
    ORDER_STATUS.EXPIRED: Status.NOTTRADED,
}

PUSH_STATUS_TIGER2VT = {
    "Invalid": Status.REJECTED,
    "Initial": Status.SUBMITTING,
    "PendingCancel": Status.CANCELLED,
    "Cancelled": Status.CANCELLED,
    "Submitted": Status.SUBMITTING,
    "PendingSubmit": Status.SUBMITTING,
    "Filled": Status.ALLTRADED,
    "Inactive": Status.REJECTED,
}


class TigerGateway(BaseGateway):
    """"""
    default_setting = {               
        "tiger_id": "",
        "account": "",
        "standard_account": "",
    }

    def __init__(self, event_engine):
        """Constructor"""
        super(TigerGateway, self).__init__(event_engine, "TIGER")

        self.private_key = ""
        self.tiger_id = ""
        self.account = ""
        self.standard_account = ""
        self.paper_account = ""
        self.language = ""

        self.client_config = None
        self.quote_client = None
        self.push_client = None

        self.tradeid = 0

        self.active = False
        self.queue = Queue()
        self.pool = None

        self.ticks = {}
        self.trades = set()
        self.contracts = {}
        self.symbol_names = {}

    def run(self):
        """"""
        while self.active:
            try:
                func, arg = self.queue.get(timeout=0.1)
                if arg:
                    func(arg)
                else:
                    func()
            except Empty:
                pass
    
    def add_task(self, func, arg=None):
        """"""
        self.queue.put((func, arg))

    def connect(self, setting: dict):
        """"""
        self.private_key = self.private_key
        self.tiger_id = setting["tiger_id"]
        self.account = setting["account"]
        self.standard_account = setting["standard_account"]
        self.paper_account = setting["account"]
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

        # self.thread.start()

    def init_client_config(self, sandbox=True):
        """"""
        self.client_config = TigerOpenClientConfig(sandbox_debug=sandbox)
        self.client_config.private_key = self.private_key
        self.client_config.tiger_id = self.tiger_id
        self.client_config.account = self.account
        self.client_config.standard_account = self.standard_account
        self.client_config.paper_account = self.paper_account
        self.client_config.language = self.language

    def connect_quote(self):
        """
        Connect to market data server.
        """
        self.quote_client = QuoteClient(self.client_config)
        try:
            self.symbol_names = dict(self.quote_client.get_symbol_names(lang=Language.zh_CN))
        except ApiException:
            self.write_log("行情接口连接失败")
            return
        
        if self.symbol_names:
            self.add_task(self.query_contract)

            self.write_log("行情接口连接成功")          
        
    def connect_trade(self):
        """
        Connect to trade server.
        """
        self.trade_client = TradeClient(self.client_config)
        try:
            data = self.trade_client.get_managed_accounts()
        except ApiException:
            self.write_log("交易接口连接失败")
            return
        
        if data:
            self.add_task(self.query_order)
            self.add_task(self.query_position)
            self.add_task(self.query_account)

            self.write_log("交易接口连接成功")
               
    def connect_push(self):
        """
        Connect to push server.
        """
        protocol, host, port = self.client_config.socket_host_port
        self.push_client = PushClient(host, port, (protocol == 'ssl'))
        self.push_client.connect(self.client_config.tiger_id, self.client_config.private_key)

        self.push_client.quote_changed = self.on_quote_change
        self.push_client.asset_changed = self.on_asset_change
        self.push_client.position_changed = self.on_position_change
        self.push_client.order_changed = self.on_order_change

        self.write_log("推送接口连接成功")

    def subscribe(self, req: SubscribeRequest):
        """"""
        self.push_client.subscribe_quote([req.symbol])
        self.push_client.subscribe_asset()
        self.push_client.subscribe_position()
        self.push_client.subscribe_order()

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
            
        tick.datetime = datetime.fromtimestamp(data["latest_time"] / 1000)
        tick.pre_close = data.get("prev_close", 0)
        tick.last_price = data.get("latest_price", 0)
        tick.volume = data.get("volume", 0)
        tick.open_price = data.get("open", 0)
        tick.open_price = data.get("open", 0)  
        tick.high_price = data.get("high", 0)  
        tick.low_price = data.get("low", 0) 
        tick.ask_price_1 = data.get("ask_price", 0)
        tick.bid_price_1 = data.get("bid_price", 0)  
        tick.ask_volume_1 = data.get("ask_size", 0) 
        tick.bid_volume_1 = data.get("bid_size", 0)  

        self.on_tick(copy(tick))
    
    def on_asset_change(self, tiger_account: str, data: list):
        """"""
        data = dict(data)

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
            volume=data["quantity"],
            frozen=0.0,
            price=data["average_cost"],
            pnl=data["unrealized_pnl"],
            gateway_name=self.gateway_name,
        )
        self.on_position(pos)

    def on_order_change(self, tiger_account: str, data: list):
        """"""
        print("委托", data)
        data = dict(data)
        symbol, exchange = convert_symbol_tiger2vt(data["origin_symbol"])
        status = PUSH_STATUS_TIGER2VT[data["status"]]
        
        order = OrderData(
            symbol=symbol,
            exchange=exchange,
            orderid=data["order_id"],
            direction=Direction.NET,
            price=data.get("limit_price", 0),
            volume=data["quantity"],
            traded=data["filled"],
            status=status,
            time=datetime.fromtimestamp(data["order_time"] / 1000).strftime("%H:%M:%S"),
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
                orderid=data["order_id"],
                price=data["avg_fill_price"],
                volume=data["filled"],
                time=datetime.fromtimestamp(data["trade_time"] / 1000).strftime("%H:%M:%S"),
                gateway_name=self.gateway_name,
            )
            self.on_trade(trade)
    
    def send_order(self, req: OrderRequest):
        """"""
        self.add_task(self._send_order, req)

    def _send_order(self, req: OrderRequest):
        """"""
        currency = config_symbol_currency(req.symbol)     
   
        # first, get contract
        try:        
            contract = self.trade_client.get_contracts(symbol=req.symbol, currency=currency)[0]
        except ApiException:
            self.write_log("获取合约对象失败")
            return

        # second, create order
        try:
            order = self.trade_client.create_order(
                account=self.account, 
                contract=contract, 
                action=DIRECTION_VT2TIGER[req.direction], 
                order_type=PRICETYPE_VT2TIGER[req.price_type], 
                quantity=int(req.volume), 
                limit_price=req.price,
            )
        except ApiException:
            self.write_log("创建订单失败")
            return

        # third, place order
        try:
            data = self.trade_client.place_order(order)
        except ApiException:
            self.write_log("发送订单失败")
            return

        if data:
            orderid = order.order_id
        
        order = req.create_order_data(orderid, self.gateway_name)
        self.on_order(order)
        return order.vt_orderid

    def cancel_order(self, req: CancelRequest):
        """"""
        self.add_task(self._cancel_order, req)

    def _cancel_order(self, req: CancelRequest):
        """"""
        try:
            data = self.trade_client.cancel_order(order_id=req.orderid)
        except ApiException:
            self.write_log(f"撤单失败：{req.orderid}")
            return

        if not data:
            self.write_log('撤单成功')

    def query_contract(self):
        """"""
        # HK Stock
        
        try:
            symbols_names_HK = self.quote_client.get_symbol_names(lang=Language.zh_CN, market=Market.HK)
            contract_names_HK = DataFrame(symbols_names_HK, columns=['symbol', 'name'])
        except ApiException:
            self.write_log("查询合约失败")
            return

        contractList = list(contract_names_HK["symbol"])
        i, n = 0, len(contractList)
        result = pd.DataFrame()
        while i < n:
            i += 500
            c = contractList[i - 500:i]
            r = self.quote_client.get_trade_metas(c)
            result = result.append(r)
            pass

        contract_detail_HK = result.sort_values(by="symbol", ascending=True)
        contract_HK = pd.merge(contract_names_HK, contract_detail_HK, how='left', on='symbol')
        
        for ix, row in contract_HK.iterrows():
            contract = ContractData(
                symbol=row["symbol"],
                exchange=Exchange.SEHK,
                name=row["name"],
                product=Product.EQUITY,
                size=1,
                pricetick=row["min_tick"],
                gateway_name=self.gateway_name,
            )
            self.on_contract(contract)
            self.contracts[contract.vt_symbol] = contract

        # US Stock
        symbols_names_US = self.quote_client.get_symbol_names(lang=Language.zh_CN, market=Market.US)
        contract_US = DataFrame(symbols_names_US, columns=['symbol', 'name'])

        for ix, row in contract_US.iterrows():
            contract = ContractData(
                symbol=row["symbol"],
                exchange=Exchange.SMART,
                name=row["name"],
                product=Product.EQUITY,
                size=1,
                pricetick=0.001,
                gateway_name=self.gateway_name,
            )
            self.on_contract(contract)
            self.contracts[contract.vt_symbol] = contract

        # CN Stock
        symbols_names_CN = self.quote_client.get_symbol_names(lang=Language.zh_CN, market=Market.CN)
        contract_CN = DataFrame(symbols_names_CN, columns=['symbol', 'name'])

        for ix, row in contract_CN.iterrows():
            symbol = row["symbol"]
            symbol, exchange = convert_symbol_tiger2vt(symbol)

            contract = ContractData(
                symbol=symbol,
                exchange=exchange,
                name=row["name"],
                product=Product.EQUITY,
                size=1,
                pricetick=0.001,
                gateway_name=self.gateway_name,
            )
            self.on_contract(contract)
            self.contracts[contract.vt_symbol] = contract
            
        self.write_log("合约查询成功")
            
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
                volume=i.quantity,
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
        except ApiException:
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

            order = OrderData(
                symbol=symbol,
                exchange=exchange,
                orderid=str(i.order_id),
                direction=Direction.NET,
                price=i.limit_price if i.limit_price else 0.0,
                volume=i.quantity,
                traded=i.filled,
                status=STATUS_TIGER2VT[i.status],
                time=datetime.fromtimestamp(i.order_time / 1000).strftime("%H:%M:%S"),
                gateway_name=self.gateway_name,
            )

            self.on_order(order)
    
    def process_deal(self, data):
        """
        Process trade data for both query and update.
        """
        for i in reversed(data):
            if i.status == ORDER_STATUS.PARTIALLY_FILLED or i.status == ORDER_STATUS.FILLED:
                symbol, exchange = convert_symbol_tiger2vt(str(i.contract))
                self.tradeid += 1

                trade = TradeData(
                    symbol=symbol,
                    exchange=exchange,
                    direction=Direction.NET,
                    tradeid=self.tradeid,
                    orderid=i.order_id,
                    price=i.avg_fill_price,
                    volume=i.filled,
                    time=datetime.fromtimestamp(i.trade_time / 1000).strftime("%H:%M:%S"),
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
