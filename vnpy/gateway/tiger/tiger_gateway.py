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

DIRECTION_TIGER2VT = {
    "BUY":Direction.LONG,
    "SELL": Direction.SHORT,
    "sell":Direction.SHORT,
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
    ORDER_STATUS.EXPIRED: Status.NOTTRADED
}

PUSH_STATUS_TIGER2VT = {
    "Invalid":Status.REJECTED,
    "Initial":Status.SUBMITTING,
    "PendingCancel":Status.CANCELLED,
    "Cancelled":Status.CANCELLED,
    "Submitted":Status.SUBMITTING,
    "PendingSubmit":Status.SUBMITTING,
    "Filled":Status.ALLTRADED,
    "Inactive":Status.REJECTED,



}

# "private_key": "MIICXQIBAAKBgQC1amZa5YsGTklry7DAsUBOwXJCgrsZZtB21PImw/yLmrbqRfsS3vawvMigLWcCwIDnHa+hpdpeze0eHIwbZzJzUDGvRALYK9t3D8pwPVxpwX1OF8RfHCM7YQvSOvPPnHHuVQvKaR7NNm1/WmvGXC9kVJdkYQ7kCmh52siFoy1MLQIDAQABAoGAVabcmIHTt7ByncBXvUJymDxhE+HhMEcImXJEueTCca8kOUu9FNXMJvmax3VoMzZsJbIwX+OMTEJxd0wHIlEA0gECjDwFK4Q42q+ptO4QABJQVSC6I+dOt2OIY28uvT3rkenOO8KRIDt4F52PFd71ZdB1aaXixORORq1MdSLi8EkCQQDiviAB+L5R/HVxwxvqZfJ530OtFd5IipZC9YZlY1CtXWCmu89LK7UUlEuNXyGsOxyz5jLqFuNRsie5AC23tfEPAkEAzNMCa8axJWfPZIH4tGrbZ1F3I41BQdgp2zBmR7AyUMBDkli86OzmJ7QUCJA/PJxK43/IYUWm4OU5Q+SvXCr3AwJBAJTBj1Y7zwES1CpSitn5EF+MbmX71t1YrsQ3OHkD80YJ4QMCbDkw75gUwox5QSoxjd8ow3Z4laJfc1gYGeZQ41kCQQCCiQwm8cceBq3W6To+iUdw7itWngRz2Ta7uXnFwFYgvpeR4jnq3GfF7+9AkeWrVBQqLtrem0xCUfQP/+N+gudPAkBFLbt78/MpQGEDc7jyu/KE5Mp4wMMDQQwch9VLvsAZwWLysB6rZWpo3jIfp9zZ7c3zOYGNMWAZjtMmNkRJ8COH",

class TigerGateway(BaseGateway):
    """"""

    default_setting = {       
        
        "tiger_id": "20150008",
        "account": "DU575568",
        "standard_account": "DU575568",

    }

    def __init__(self, event_engine):
        """Constructor"""
        super(TigerGateway, self).__init__(event_engine, "TIGER")

        self.private_key = "MIICXQIBAAKBgQC1amZa5YsGTklry7DAsUBOwXJCgrsZZtB21PImw/yLmrbqRfsS3vawvMigLWcCwIDnHa+hpdpeze0eHIwbZzJzUDGvRALYK9t3D8pwPVxpwX1OF8RfHCM7YQvSOvPPnHHuVQvKaR7NNm1/WmvGXC9kVJdkYQ7kCmh52siFoy1MLQIDAQABAoGAVabcmIHTt7ByncBXvUJymDxhE+HhMEcImXJEueTCca8kOUu9FNXMJvmax3VoMzZsJbIwX+OMTEJxd0wHIlEA0gECjDwFK4Q42q+ptO4QABJQVSC6I+dOt2OIY28uvT3rkenOO8KRIDt4F52PFd71ZdB1aaXixORORq1MdSLi8EkCQQDiviAB+L5R/HVxwxvqZfJ530OtFd5IipZC9YZlY1CtXWCmu89LK7UUlEuNXyGsOxyz5jLqFuNRsie5AC23tfEPAkEAzNMCa8axJWfPZIH4tGrbZ1F3I41BQdgp2zBmR7AyUMBDkli86OzmJ7QUCJA/PJxK43/IYUWm4OU5Q+SvXCr3AwJBAJTBj1Y7zwES1CpSitn5EF+MbmX71t1YrsQ3OHkD80YJ4QMCbDkw75gUwox5QSoxjd8ow3Z4laJfc1gYGeZQ41kCQQCCiQwm8cceBq3W6To+iUdw7itWngRz2Ta7uXnFwFYgvpeR4jnq3GfF7+9AkeWrVBQqLtrem0xCUfQP/+N+gudPAkBFLbt78/MpQGEDc7jyu/KE5Mp4wMMDQQwch9VLvsAZwWLysB6rZWpo3jIfp9zZ7c3zOYGNMWAZjtMmNkRJ8COH"
        self.tiger_key_2005 = "MIICXAIBAAKBgQC2s9fGSfp86pYpK/9FFtdzZXcpncxDMaWww9WPPn2EnZC9zqIamz4nUewDGgya33VgoHNL7a3iGNCe4zqivhr8k1ACG68psElaRjALl1UzdAMv4xwnrxpceTCgA9AZM8x+BmVXvO5cfgIfGdoahtdxjMNjIYDkx+HORGJ1cFcmrQIDAQABAoGBAIwf8uYJ5yvXX8PEEsyScDv5HiO0+uyuLz4bdLegXfRQRKrOyFVPq6PMmQ7n87L0n7m0VbluWWaHUboK3PXkiBzTsmx0aFS3aNyr203QGXXwp9hxF2WS968/6K2zSikaDrmSkWps5dVVqhnkJ6STj7cvM6ZGYIHWPC7W79qTYHihAkEA3FvFSznaTTajvZpHq83rrCh3wmI2ggeh1M1i89HAv0EfTLkWweyNM8qO39qeaGzB/TZiOal0LR8Mk7HbGPOTVwJBANRA4LyhwczHEdwH16n5QPcrogoSsPM6uq9ZL8zYwaMTcHvEJUhW6hUMQPyWcNtenH9mwcgRF78TFGLqIH9s95sCP1bv3ebP7FCKPg+Pzrb5hwFk9dq65MZoPHC4l1Gab3EFQFQEsfXQXeURBU1L8zM/tUkxK4+US0GB/nRGtyog7wJBALU4a2lCpqgDc4EshPsP4GLosyHskX4qL4hVGpXIn5NvnoNdlgNsidHMs5O1ksgJwI6aGmuKBH9Ud/x4L6T8UW8CQEbrCa3/vIv5mHzGe9G7ZsK5VaPx3VETSeRbDUai8KGpcMXX7nFUnhsBd7YvehOSwRSd5SCWrZuejhIdn5V7hYM="
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


    def connect(self, setting: dict):
        """"""
        self.private_key = self.private_key
        self.tiger_id = setting["tiger_id"]
        self.account = setting["account"]
        self.standard_account = setting["standard_account"]
        self.paper_account = setting["account"]
        self.languege = Language.zh_CN

        self.get_client_config()
        self.connect_quote()
        self.connect_trade()
        self.connect_push()

        self.thread.start()

    def query_data(self):
        """
        Query all data necessary.
        """

        self.query_contract() 
        self.query_order() 
        self.query_position() 
        self.query_account()  


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
            self.symbol_names = dict(self.quote_client.get_symbol_names(lang=Language.zh_CN))
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
        self.push_client.connect(self.client_config.tiger_id, self.client_config.private_key)

        self.push_client.quote_changed = self.on_quote_change
        
        self.push_client.subscribe_asset()
        self.push_client.asset_changed = self.on_asset_changed
        
        self.push_client.subscribe_position()
        self.push_client.position_changed = self.on_position_changed
        
        self.push_client.subscribe_order()
        self.push_client.order_changed = self.on_order_changed

        self.write_log("推送接口连接成功")

    def subscribe(self, req: SubscribeRequest):
        """"""
        symbol = convert_symbol_vt2tiger(req.symbol, req.exchange)
        self.push_client.subscribe_quote([req.symbol])
        #self.push_client.subscribe_asset()
        # self.push_client.subscribe_position()
        #self.push_client.subscribe_order()

    def on_quote_change(self, symbol: str, data: list, trading: bool):
        symbol, exchange = convert_symbol_tiger2vt(symbol)
        name = self.symbol_names[symbol]
        data = dict(data)

        tick = self.ticks.get(symbol, None)
        if not tick:
            tick = TickData(
                symbol=symbol,
                exchange=exchange,
                datetime=None,
                gateway_name=self.gateway_name,
                name=name,
            )
            self.ticks[symbol] = tick
            
        tick.datetime = datetime.now()

        tick.pre_close = data.get("prev_close",0)
        tick.last_price = data.get("latest_price",0)
        tick.volume = data.get("volume", 0)
        tick.open_price = data.get("open", 0)

        tick.open_price = data.get("open", 0)  #美股无
        tick.high_price = data.get("high", 0)  # 美股无
        tick.low_price = data.get("low", 0) # 美股无


        tick.ask_price_1=data.get("ask_price", 0) # A股/港股无
        tick.bid_price_1=data.get("bid_price", 0)  # A股/港股无
        tick.ask_volume_1=data.get("ask_size", 0) # A股/港股无
        tick.bid_volume_1=data.get("bid_size", 0)  # A股/港股无

        self.on_tick(copy(tick))

    

    def on_asset_changed(self, account:str, data:list):
        """"""

        #print("账号", data)
        data = dict(data)
                        

        account = AccountData(
            accountid=account,
            balance=data["net_liquidation"],
            frozen=0.0,
            gateway_name=self.gateway_name,
        )
        self.on_account(account) 

        

    def on_position_changed(self, account:str, data:list):
        """"""
        #print ("持仓", data)
        data = dict(data)

        symbol = data["origin_symbol"]
        volume = data["quantity"]
        # 判断方向
        if volume > 0:
            direction = Direction.LONG
        else:
            direction = Direction.SHORT

        symbol, exchange = convert_symbol_tiger2vt(symbol)

        pos = PositionData(
            symbol=symbol,
            exchange=exchange,
            direction=direction,
            volume=volume,
            frozen=0.0,
            price=data["average_cost"],
            pnl=data["unrealized_pnl"],
            gateway_name=self.gateway_name,

        )
        self.on_position(pos)



    
    def on_order_changed(self, account: str, data: list):
        """"""
        #print("委托", data)
        data = dict(data)
        symbol = data["origin_symbol"]
        volume = data["quantity"]

        symbol, exchange = convert_symbol_tiger2vt(symbol)

        if data["order_type"] == "LMT":
            price = data["limit_price"]
        else:
            price = 0

        
        order = OrderData(
            symbol=symbol,
            exchange=exchange,
            orderid=data["order_id"],
            direction=DIRECTION_TIGER2VT[data["action"]],
            price=price,
            volume=volume,
            traded=data["filled"],
            status=PUSH_STATUS_TIGER2VT[data["status"]],
            time=time.strftime("%Y-%m-%d %H:%M:%S", time.localtime(data["order_time"] / 1000)).split(" ")[-1],
            gateway_name=self.gateway_name,
        )
        self.on_order(order)

        trade = TradeData(
            symbol=symbol,
            exchange=exchange,
            direction=DIRECTION_TIGER2VT[data["action"]],
            tradeid=data["order_id"],
            orderid=data["order_id"],
            price=data["avg_fill_price"],
            volume=data["filled"],
            time=time.strftime("%Y-%m-%d %H:%M:%S", time.localtime(data["trade_time"] / 1000)).split(" ")[-1],
            gateway_name=self.gateway_name,
        )
        self.on_trade(trade)





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
                accountid=self.account,
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
                price=float(i.average_cost),  
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
                price = 0


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

    




















    
