# encoding: UTF-8
"""
Please install tiger-api before use.
pip install tigeropen
"""

from copy import copy
from threading import Thread
from time import sleep
import time
import pandas as pd
from pandas import DataFrame
from datetime import datetime

from tigeropen.tiger_open_config import TigerOpenClientConfig 
from tigeropen.common.consts import Language, Currency, Market
from tigeropen.quote.quote_client import QuoteClient
from tigeropen.trade.trade_client import TradeClient
from tigeropen.trade.domain.order import ORDER_STATUS
from tigeropen.push.push_client import PushClient
from tigeropen.common.exceptions import ApiException

from vnpy.trader.constant import Direction, Product, Status, PriceType, Exchange


from vnpy.trader.event import EVENT_TIMER
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
    Product.FOREX: "CASH"
}

DIRECTION_VT2TIGER = {
    Direction.LONG: "BUY",
    Direction.SHORT: "SELL",
}
DIRECTION_TIGER2VT = {v: k for k, v in DIRECTION_VT2TIGER.items()}

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
    ORDER_STATUS.EXPIRED: Status.NOTTRADED
}


class TigerGateway(BaseGateway):
    """"""

    default_setting = {
        "private_key": "MIICXQIBAAKBgQC1amZa5YsGTklry7DAsUBOwXJCgrsZZtB21PImw/yLmrbqRfsS3vawvMigLWcCwIDnHa+hpdpeze0eHIwbZzJzUDGvRALYK9t3D8pwPVxpwX1OF8RfHCM7YQvSOvPPnHHuVQvKaR7NNm1/WmvGXC9kVJdkYQ7kCmh52siFoy1MLQIDAQABAoGAVabcmIHTt7ByncBXvUJymDxhE+HhMEcImXJEueTCca8kOUu9FNXMJvmax3VoMzZsJbIwX+OMTEJxd0wHIlEA0gECjDwFK4Q42q+ptO4QABJQVSC6I+dOt2OIY28uvT3rkenOO8KRIDt4F52PFd71ZdB1aaXixORORq1MdSLi8EkCQQDiviAB+L5R/HVxwxvqZfJ530OtFd5IipZC9YZlY1CtXWCmu89LK7UUlEuNXyGsOxyz5jLqFuNRsie5AC23tfEPAkEAzNMCa8axJWfPZIH4tGrbZ1F3I41BQdgp2zBmR7AyUMBDkli86OzmJ7QUCJA/PJxK43/IYUWm4OU5Q+SvXCr3AwJBAJTBj1Y7zwES1CpSitn5EF+MbmX71t1YrsQ3OHkD80YJ4QMCbDkw75gUwox5QSoxjd8ow3Z4laJfc1gYGeZQ41kCQQCCiQwm8cceBq3W6To+iUdw7itWngRz2Ta7uXnFwFYgvpeR4jnq3GfF7+9AkeWrVBQqLtrem0xCUfQP/+N+gudPAkBFLbt78/MpQGEDc7jyu/KE5Mp4wMMDQQwch9VLvsAZwWLysB6rZWpo3jIfp9zZ7c3zOYGNMWAZjtMmNkRJ8COH",
        "tiger_id": "1",
        "account": "DU575569",
        "standard_account": "",
        "paper_account": "DU575569",
        "language": "Language.zh_CN",
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

        self.ticks = {}
        self.trades = set()
        self.contracts = {}
        self.symbol_names = {}

        self.thread = Thread(target=self.query_data)

        # For query function.
        self.count = 0
        self.interval = 1
        self.query_funcs = [self.query_account, self.query_position, self.query_order]

    def connect(self, setting: dict):
        """"""
        self.private_key = setting["private_key"]
        self.tiger_id = setting["tiger_id"]
        self.account = setting["account"]
        self.standard_account = setting["standard_account"]
        self.paper_account = setting["paper_account"]
        self.languege = setting["language"]

        self.get_client_config()
        self.connect_quote()
        self.connect_trade()
        self.connect_push()

        self.thread.start()

    def query_data(self):
        """
        Query all data necessary.
        """
        sleep(2.0)  # Wait 2 seconds till connection completed.

        self.query_contract()
        # self.query_trade() 
        self.query_order() 
        self.query_position() 
        self.query_account()  

        # Start fixed interval query.
        self.event_engine.register(EVENT_TIMER, self.process_timer_event)
        
    def process_timer_event(self, event):
        """"""
        self.count += 1
        if self.count < self.interval:
            return
        self.count = 0
        func = self.query_funcs.pop(0)
        func()
        self.query_funcs.append(func)

    def get_client_config(self, sandbox=True):
        """"""
        self.client_config = TigerOpenClientConfig(sandbox_debug=sandbox)
        self.client_config.private_key = self.private_key
        self.client_config.tiger_id = self.tiger_id
        self.client_config.account = self.account
        self.client_config.standard_account = self.standard_account
        self.client_config.paper_account = self.paper_account
        self.client_config.language = self.language
        return self.client_config

    def connect_quote(self):
        """
        Connect to market data server.
        """
        self.quote_client = QuoteClient(self.client_config)
        try:
            symbol_names = self.quote_client.get_symbol_names(lang=Language.zh_CN)
            self.symbol_names =dict(symbol_names)
        except ApiException:
            self.write_log("行情接口连接失败")
            return
        
        if self.symbol_names:
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
            self.write_log("交易接口连接成功")
    
    def connect_push(self):
        """
        Connect to push server.
        """
        protocol, host, port = self.client_config.socket_host_port
        self.push_client = PushClient(host, port, (protocol == 'ssl'))
        
        self.push_client.quote_changed = self.on_quote_change

        self.push_client.connect(self.client_config.tiger_id, self.client_config.private_key)

        self.write_log("推送接口连接成功")

    def subscribe(self, req: SubscribeRequest):
        """"""
        # symbol = convert_symbol_vt2tiger(req.symbol, req.exchange)
        self.push_client.subscribe_quote([req.symbol])

    def on_quote_change(self, symbol: str, data: list, trading: bool):
        #print(symbol, data, trading)

        tick = self.ticks.get(symbol, None)
        if not tick:
            tick = TickData(
                symbol=symbol,
                exchange=Exchange.SSE,
                datetime=None,
                gateway_name=self.gateway_name,
            )
            self.ticks[symbol] = tick
            # self.process_quote(data)
        contract = self.contracts.get(tick.vt_symbol, None)
        if contract:
            tick.name = contract.name

        # volume, latest_price, high_price, prev_close, low_price, open_price, latest_time = [i[1] for i in info]

        #tick.datetime = datetime.utcfromtimestamp(data[6][1] / 1000)
        tick.datetime = datetime.now()
        tick.open_price = data[5][1]
        tick.high_price = data[2][1]
        tick.low_price = data[4][1]
        tick.pre_close = data[3][1]
        tick.last_price = data[0][1]
        tick.volume = data[1][1]

        self.on_tick(copy(tick))

    def send_order(self, req: OrderRequest):
        """"""
        symbol = convert_symbol_vt2tiger(req.symbol, req.exchange)
        currency = config_symbol_currency(req.symbol)     
        order_type = PRICETYPE_VT2TIGER[req.price_type]
   
        # first, get contract
        try:        
            contract = self.trade_client.get_contracts(symbol=symbol, currency=currency)[0]
        except ApiException:
            self.write_log("获取合约对象失败")
            return

        # second, create order
        try:
            order = self.trade_client.create_order(
                account=self.account, 
                contract=contract, 
                action=DIRECTION_VT2TIGER[req.direction], 
                order_type=order_type, 
                quantity=req.volume, 
                limit_price=req.price
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
        try:
            data = self.trade_client.cancel_order(order_id=req.orderid)
        except ApiException:
            self.write_log("撤单失败")
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
                accountid=self.tiger_id,
                balance=float(i.summary.net_liquidation),
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
            symbol = i.contract.symbol
            symbol, exchange = convert_symbol_tiger2vt(symbol)            
            volume = float(i.quantity)
            # 判断方向
            if volume > 0:
                direction = Direction.LONG
            else:
                direction = Direction.SHORT

            pos = PositionData(
                symbol=symbol,
                exchange=exchange,
                direction=direction,
                volume=volume,
                frozen=0.0,
                price=float(i.market_price),  # market_price = 0.0
                pnl=float(i.average_cost),  # 未知？？
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

    def query_trade(self):
        """"""
        pass

    def close(self):
        """"""
        if self.push_client:
            self.push_client.disconnect()

    def process_order(self, data):
        """"""
        for i in data:
            symbol = str(i.contract)
            symbol, exchange = convert_symbol_tiger2vt(symbol)
            time_local = time.localtime(i.order_time / 1000)

            if i.order_type == "LMT":
                price = i.limit_price
            else:
                price = i.avg_fill_price

            order = OrderData(
                symbol=symbol,
                exchange=exchange,
                orderid=str(i.order_id),
                direction=DIRECTION_TIGER2VT[i.action],
                price=float(price),
                volume=float(i.quantity),
                traded=float(i.filled),
                status=STATUS_TIGER2VT[i.status],
                time=time.strftime("%Y-%m-%d %H:%M:%S", time_local).split(" ")[-1],
                gateway_name=self.gateway_name,
            )

            self.on_order(order)
    
    def process_deal(self, data):
        """
        Process trade data for both query and update.
        """
        for i in data:
            if i.status == ORDER_STATUS.PARTIALLY_FILLED or i.status == ORDER_STATUS.FILLED:
                symbol = str(i.contract)
                symbol, exchange = convert_symbol_tiger2vt(symbol)
                time_local = time.localtime(i.trade_time / 1000)

                trade = TradeData(
                    symbol=symbol,
                    exchange=exchange,
                    direction=DIRECTION_TIGER2VT[i.action],
                    tradeid=i.order_id,
                    orderid=i.order_id,
                    price=float(i.avg_fill_price),
                    volume=float(i.filled),
                    time=time.strftime("%Y-%m-%d %H:%M:%S", time_local).split(" ")[-1],
                    gateway_name=self.gateway_name,
                )

                self.on_trade(trade)


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


def convert_symbol_vt2tiger(symbol, exchange):
    """
    Convert symbol from vt to tiger.
    """
    if exchange == Exchange.SSE and symbol.startswith("0"):        
        symbol = symbol + ".SH"
    else:
        symbol = symbol
    return symbol


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

    




















    
