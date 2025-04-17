from functools import lru_cache
import urllib
import hashlib
import hmac
import time
from copy import copy
from typing import Callable, Optional
from enum import Enum
from time import sleep
from datetime import datetime, timedelta

from numpy import format_float_positional

from vnpy.event import Event, EventEngine
from vnpy.trader.constant import (
    Direction,
    Exchange,
    Product,
    Status,
    OrderType,
    Interval
)
from vnpy.trader.gateway import BaseGateway
from vnpy.trader.object import (
    TickData,
    OrderData,
    TradeData,
    AccountData,
    ContractData,
    PositionData,
    BarData,
    OrderRequest,
    CancelRequest,
    SubscribeRequest,
    HistoryRequest
)
from vnpy.trader.event import EVENT_TIMER
from vnpy.trader.utility import round_to, ZoneInfo, round_volume
from vnpy.rest import Request, RestClient, Response
from vnpy.websocket import WebsocketClient


# Timezone constant
UTC_TZ = ZoneInfo("UTC")

# Real server hosts
F_REST_HOST: str = "https://fapi.binance.com"
F_WEBSOCKET_TRADE_HOST: str = "wss://ws-fapi.binance.com/ws-fapi/v1"
F_WEBSOCKET_USER_HOST: str = "wss://fstream.binance.com/ws/"
F_WEBSOCKET_DATA_HOST: str = "wss://fstream.binance.com/stream"

# Testnet server hosts
F_TESTNET_REST_HOST: str = "https://testnet.binancefuture.com"
F_TESTNET_WEBSOCKET_TRADE_HOST: str = "wss://testnet.binancefuture.com/ws-fapi/v1"
F_TESTNET_WEBSOCKET_USER_HOST: str = "wss://stream.binancefuture.com/ws/"
F_TESTNET_WEBSOCKET_DATA_HOST: str = "wss://stream.binancefuture.com/stream"

# Order status map
STATUS_BINANCES2VT: dict[str, Status] = {
    "NEW": Status.NOTTRADED,
    "PARTIALLY_FILLED": Status.PARTTRADED,
    "FILLED": Status.ALLTRADED,
    "CANCELED": Status.CANCELLED,
    "REJECTED": Status.REJECTED,
    "EXPIRED": Status.CANCELLED
}

# Order type map
ORDERTYPE_VT2BINANCES: dict[OrderType, tuple[str, str]] = {
    OrderType.LIMIT: ("LIMIT", "GTC"),
    OrderType.MARKET: ("MARKET", "GTC"),
    OrderType.FAK: ("LIMIT", "IOC"),
    OrderType.FOK: ("LIMIT", "FOK"),
}
ORDERTYPE_BINANCES2VT: dict[tuple[str, str], OrderType] = {v: k for k, v in ORDERTYPE_VT2BINANCES.items()}

# Direction map
DIRECTION_VT2BINANCES: dict[Direction, str] = {
    Direction.LONG: "BUY",
    Direction.SHORT: "SELL"
}
DIRECTION_BINANCES2VT: dict[str, Direction] = {v: k for k, v in DIRECTION_VT2BINANCES.items()}

# Kline interval map
INTERVAL_VT2BINANCES: dict[Interval, str] = {
    Interval.MINUTE: "1m",
    Interval.HOUR: "1h",
    Interval.DAILY: "1d",
}

# Timedelta map
TIMEDELTA_MAP: dict[Interval, timedelta] = {
    Interval.MINUTE: timedelta(minutes=1),
    Interval.HOUR: timedelta(hours=1),
    Interval.DAILY: timedelta(days=1),
}

# Set weboscket timeout to 24 hour
WEBSOCKET_TIMEOUT = 24 * 60 * 60


# Global dict for contract data
symbol_contract_map: dict[str, ContractData] = {}


# Authentication level
class Security(Enum):
    NONE: int = 0
    SIGNED: int = 1
    API_KEY: int = 2


class BinanceLinearGateway(BaseGateway):
    """
    The Binance linear trading gateway for VeighNa.

    1. Only support crossed position
    2. Only support one-way mode
    """

    default_name: str = "BINANCE_LINEAR"

    default_setting: dict = {
        "API Key": "",
        "API Secret": "",
        "Server": ["REAL", "TESTNET"],
        "Kline Stream": ["False", "True"],
        "Proxy Host": "",
        "Proxy Port": 0
    }

    exchanges: Exchange = [Exchange.BINANCE]

    def __init__(self, event_engine: EventEngine, gateway_name: str) -> None:
        """
        The init method of the gateway.

        event_engine: the global event engine object of VeighNa
        gateway_name: the unique name for identifying the gateway
        """
        super().__init__(event_engine, gateway_name)

        self.trade_ws_api: BinanceLinearTradeWebsocketApi = BinanceLinearTradeWebsocketApi(self)
        self.user_ws_api: BinanceLinearUserWebsocketApi = BinanceLinearUserWebsocketApi(self)
        self.market_ws_api: BinanceLinearDataWebsocketApi = BinanceLinearDataWebsocketApi(self)
        self.rest_api: BinanceLinearRestApi = BinanceLinearRestApi(self)

        self.orders: dict[str, OrderData] = {}

    def connect(self, setting: dict) -> None:
        """Start server connections"""
        key: str = setting["API Key"]
        secret: str = setting["API Secret"]
        server: str = setting["Server"]
        kline_stream: bool = setting["Kline Stream"] == "True"
        proxy_host: str = setting["Proxy Host"]
        proxy_port: int = setting["Proxy Port"]

        self.rest_api.connect(key, secret, server, proxy_host, proxy_port)
        self.trade_ws_api.connect(key, secret, server, proxy_host, proxy_port)
        self.market_ws_api.connect(server, kline_stream, proxy_host, proxy_port)

        self.event_engine.register(EVENT_TIMER, self.process_timer_event)

    def subscribe(self, req: SubscribeRequest) -> None:
        """Subscribe market data"""
        self.market_ws_api.subscribe(req)

    def send_order(self, req: OrderRequest) -> str:
        """Send new order"""
        return self.trade_ws_api.send_order(req)

    def cancel_order(self, req: CancelRequest) -> None:
        """Cancel existing order"""
        self.trade_ws_api.cancel_order(req)

    def query_account(self) -> None:
        """Not required since Binance provides websocket update"""
        pass

    def query_position(self) -> None:
        """Not required since Binance provides websocket update"""
        pass

    def query_history(self, req: HistoryRequest) -> list[BarData]:
        """Query kline history data"""
        return self.rest_api.query_history(req)

    def close(self) -> None:
        """Close server connections"""
        self.rest_api.stop()
        self.user_ws_api.stop()
        self.market_ws_api.stop()

    def process_timer_event(self, event: Event) -> None:
        """Process timer task"""
        self.rest_api.keep_user_stream()

    def on_order(self, order: OrderData) -> None:
        """Save a copy of order and then push"""
        self.orders[order.orderid] = copy(order)
        super().on_order(order)

    def get_order(self, orderid: str) -> OrderData:
        """Get previously saved order"""
        return self.orders.get(orderid, None)


class BinanceLinearRestApi(RestClient):
    """The REST API of BinanceLinearGateway"""

    def __init__(self, gateway: BinanceLinearGateway) -> None:
        """
        The init method of the api.

        gateway: the parent gateway object for pushing callback data.
        """
        super().__init__()

        self.gateway: BinanceLinearGateway = gateway
        self.gateway_name: str = gateway.gateway_name

        self.user_ws_api: BinanceLinearUserWebsocketApi = self.gateway.user_ws_api

        self.key: str = ""
        self.secret: bytes = b""

        self.user_stream_key: str = ""
        self.keep_alive_count: int = 0
        self.time_offset: int = 0

        self.order_count: int = 1_000_000
        self.order_prefix: str = ""

        self.commission_rate: float = 0.0006

    def sign(self, request: Request) -> Request:
        """Standard callback for signing a request"""
        security: Security = request.data["security"]
        if security == Security.NONE:
            request.data = None
            return request

        if request.params:
            path: str = request.path + "?" + urllib.parse.urlencode(request.params)
        else:
            request.params = dict()
            path: str = request.path

        if security == Security.SIGNED:
            timestamp: int = int(time.time() * 1000)

            if self.time_offset > 0:
                timestamp -= abs(self.time_offset)
            elif self.time_offset < 0:
                timestamp += abs(self.time_offset)

            request.params["timestamp"] = timestamp

            query: str = urllib.parse.urlencode(sorted(request.params.items()))
            signature: bytes = hmac.new(
                self.secret,
                query.encode("utf-8"),
                hashlib.sha256
            ).hexdigest()

            query += "&signature={}".format(signature)
            path: str = request.path + "?" + query

        request.path = path
        request.params = {}
        request.data = {}

        # Add header to the request
        headers = {
            "Content-Type": "application/x-www-form-urlencoded",
            "Accept": "application/json",
            "X-MBX-APIKEY": self.key,
            "Connection": "close"
        }

        if security in [Security.SIGNED, Security.API_KEY]:
            request.headers = headers

        return request

    def connect(
        self,
        key: str,
        secret: str,
        server: str,
        proxy_host: str,
        proxy_port: int
    ) -> None:
        """Start server connection"""
        self.key = key
        self.secret = secret.encode()
        self.proxy_port = proxy_port
        self.proxy_host = proxy_host
        self.server = server

        self.order_prefix = datetime.now().strftime("%y%m%d%H%M%S")

        if self.server == "REAL":
            self.init(F_REST_HOST, proxy_host, proxy_port)
        else:
            self.init(F_TESTNET_REST_HOST, proxy_host, proxy_port)

        self.start()

        self.gateway.write_log("REST API started")

        self.query_time()
        self.query_contract()

    def query_time(self) -> None:
        """Query server time"""
        data: dict = {"security": Security.NONE}

        path: str = "/fapi/v1/time"

        self.add_request(
            "GET",
            path,
            callback=self.on_query_time,
            data=data
        )

    def query_account(self) -> None:
        """
        Query account balance
        Get current account information. 
        User in single-asset/ multi-assets mode will see different value, 
        see comments in response section for detail.
        """
        data: dict = {"security": Security.SIGNED}

        path: str = "/fapi/v3/account"

        self.add_request(
            method="GET",
            path=path,
            callback=self.on_query_account,
            data=data
        )

    def query_position(self) -> None:
        """
        Query holding positions
        Get current position information
        (only symbol that has position or open orders will be returned).
        """
        data: dict = {"security": Security.SIGNED}

        path: str = "/fapi/v3/positionRisk"

        self.add_request(
            method="GET",
            path=path,
            callback=self.on_query_position,
            data=data
        )

    def query_order(self) -> None:
        """Query open orders"""
        data: dict = {"security": Security.SIGNED}

        path: str = "/fapi/v1/openOrders"

        self.add_request(
            method="GET",
            path=path,
            callback=self.on_query_order,
            data=data
        )

    def query_contract(self) -> None:
        """Query available contracts"""
        data: dict = {"security": Security.NONE}

        path: str = "/fapi/v1/exchangeInfo"

        self.add_request(
            method="GET",
            path=path,
            callback=self.on_query_contract,
            data=data
        )
    
    @lru_cache(maxsize=128)
    def get_cached_contract(self, symbol: str) -> Optional[ContractData]:
        """从缓存中获取合约信息"""
        return symbol_contract_map.get(symbol)

    def send_order(self, req: OrderRequest) -> str:
        """Send new order"""
        # Generate new order id
        self.order_count += 1
        orderid: str = self.order_prefix + str(self.order_count)

        # Push a submitting order event
        order: OrderData = req.create_order_data(
            orderid,
            self.gateway_name
        )
        self.gateway.on_order(order)

        # Create order parameters
        data: dict = {"security": Security.SIGNED}

        contract: Optional[ContractData] = self.get_cached_contract(req.symbol)
        if contract:
            req.volume = round_volume(float(req.volume), contract.min_volume, self.commission_rate)

        params: dict = {
            "symbol": req.symbol,
            "side": DIRECTION_VT2BINANCES[req.direction],
            "quantity": format_float(req.volume),
            "newClientOrderId": order.orderid, #todo check orderid or vt_order_id
            "newOrderRespType": "FULL"
        }

        if req.type == OrderType.MARKET:
            params["type"] = "MARKET"
        elif req.type == OrderType.STOP:
            params["type"] = "STOP_MARKET"
            params["stopPrice"] = format_float(req.price)
        else:
            order_type, time_condition = ORDERTYPE_VT2BINANCES[req.type]
            params["type"] = order_type
            params["timeInForce"] = time_condition
            params["price"] = format_float(req.price)

        path: str = "/fapi/v1/order"

        self.add_request(
            method="POST",
            path=path,
            callback=self.on_send_order,
            data=data,
            params=params,
            extra=order,
            on_error=self.on_send_order_error,
            on_failed=self.on_send_order_failed
        )

        return order.vt_orderid

    def cancel_order(self, req: CancelRequest) -> None:
        """Cancel existing order"""
        data: dict = {"security": Security.SIGNED}

        params: dict = {
            "symbol": req.symbol,
            "origClientOrderId": req.orderid
        }

        path: str = "/fapi/v1/order"

        order: OrderData = self.gateway.get_order(req.orderid)

        self.add_request(
            method="DELETE",
            path=path,
            callback=self.on_cancel_order,
            params=params,
            data=data,
            on_failed=self.on_cancel_failed,
            extra=order
        )

    def start_user_stream(self) -> None:
        """Create listen key for user stream"""
        data: dict = {"security": Security.API_KEY}

        path: str = "/fapi/v1/listenKey"

        self.add_request(
            method="POST",
            path=path,
            callback=self.on_start_user_stream,
            data=data
        )

    def keep_user_stream(self) -> None:
        """Extend listen key validity"""
        if not self.user_stream_key:
            return

        self.keep_alive_count += 1
        if self.keep_alive_count < 600:
            return
        self.keep_alive_count = 0

        data: dict = {"security": Security.API_KEY}

        params: dict = {"listenKey": self.user_stream_key}

        path: str = "/fapi/v1/listenKey"

        self.add_request(
            method="PUT",
            path=path,
            callback=self.on_keep_user_stream,
            params=params,
            data=data,
            on_error=self.on_keep_user_stream_error
        )

    def on_query_time(self, data: dict, request: Request) -> None:
        """Callback of server time query"""
        local_time: int = int(time.time() * 1000)
        server_time: int = int(data["serverTime"])
        self.time_offset: int = local_time - server_time

        self.gateway.write_log(f"Server time updated, local offset: {self.time_offset}ms")

        # Query private data after time offset is calculated
        if self.key and self.secret:
            self.query_account()
            self.query_position()
            self.query_order()
            self.start_user_stream()

    def on_query_account(self, data: dict, request: Request) -> None:
        """Callback of account balance query"""
        for asset in data["assets"]:
            account: AccountData = AccountData(
                accountid=asset["asset"],
                balance=float(asset["walletBalance"]),
                frozen=float(asset["maintMargin"]),
                gateway_name=self.gateway_name
            )

            self.gateway.on_account(account)

        self.gateway.write_log("Account balance data is received")

    def on_query_position(self, data: list, request: Request) -> None:
        """Callback of holding positions query"""
        for d in data:
            position: PositionData = PositionData(
                symbol=d["symbol"],
                exchange=Exchange.BINANCE,
                direction=Direction.NET,
                volume=float(d["positionAmt"]),
                price=float(d["entryPrice"]),
                pnl=float(d["unRealizedProfit"]),
                gateway_name=self.gateway_name,
            )

            self.gateway.on_position(position)

        self.gateway.write_log("Holding positions data is received")

    def on_query_order(self, data: list, request: Request) -> None:
        """Callback of open orders query"""
        for d in data:
            key: tuple[str, str] = (d["type"], d["timeInForce"])
            order_type: OrderType = ORDERTYPE_BINANCES2VT.get(key, None)
            if not order_type:
                continue

            order: OrderData = OrderData(
                orderid=d["clientOrderId"],
                symbol=d["symbol"],
                exchange=Exchange.BINANCE,
                price=float(d["price"]),
                volume=float(d["origQty"]),
                type=order_type,
                direction=DIRECTION_BINANCES2VT[d["side"]],
                traded=float(d["executedQty"]),
                status=STATUS_BINANCES2VT.get(d["status"], None),
                datetime=generate_datetime(d["time"]),
                gateway_name=self.gateway_name,
            )
            self.gateway.on_order(order)

        self.gateway.write_log("Open orders data is received")

    def on_query_contract(self, data: dict, request: Request) -> None:
        """Callback of available contracts query"""
        for d in data["symbols"]:
            base_currency: str = d["baseAsset"]
            quote_currency: str = d["quoteAsset"]
            name: str = f"{base_currency.upper()}/{quote_currency.upper()}"

            pricetick: int = 1
            min_volume: int = 1

            for f in d["filters"]:
                if f["filterType"] == "PRICE_FILTER":
                    pricetick = float(f["tickSize"])
                elif f["filterType"] == "LOT_SIZE":
                    min_volume = float(f["stepSize"])

            contract: ContractData = ContractData(
                symbol=d["symbol"],
                exchange=Exchange.BINANCE,
                name=name,
                pricetick=pricetick,
                size=1,
                min_volume=min_volume,
                product=Product.FUTURES,
                net_position=True,
                history_data=True,
                gateway_name=self.gateway_name,
                stop_supported=True
            )
            self.gateway.on_contract(contract)

            symbol_contract_map[contract.symbol] = contract

        self.gateway.write_log("Available contracts data is received")

    def on_send_order(self, data: dict, request: Request) -> None:
        """Successful callback of send_order"""
        pass

    def on_send_order_failed(self, status_code: str, request: Request) -> None:
        """Failed callback of send_order"""
        order: OrderData = request.extra
        order.status = Status.REJECTED
        self.gateway.on_order(order)

        msg: str = f"Send order failed, status code: {status_code}, message: {request.response.text}"
        self.gateway.write_log(msg)

    def on_send_order_error(self, exception_type: type, exception_value: Exception, tb, request: Request) -> None:
        """Error callback of send_order"""
        order: OrderData = request.extra
        order.status = Status.REJECTED
        self.gateway.on_order(order)

        if not issubclass(exception_type, ConnectionError):
            self.on_error(exception_type, exception_value, tb, request)

    def on_cancel_order(self, data: dict, request: Request) -> None:
        """Successful callback of cancel_order"""
        pass

    def on_cancel_failed(self, status_code: str, request: Request) -> None:
        """Failed callback of cancel_order"""
        if request.extra:
            order = request.extra
            order.status = Status.REJECTED
            self.gateway.on_order(order)

        msg: str = f"Cancel orde failed, status code: {status_code}, message: {request.response.text}, order: {request.extra} "
        self.gateway.write_log(msg)

    def on_start_user_stream(self, data: dict, request: Request) -> None:
        """Successful callback of start_user_stream"""
        self.user_stream_key = data["listenKey"]
        self.keep_alive_count = 0

        if self.server == "REAL":
            url = F_WEBSOCKET_USER_HOST + self.user_stream_key
        else:
            url = F_TESTNET_WEBSOCKET_USER_HOST + self.user_stream_key

        self.user_ws_api.connect(url, self.proxy_host, self.proxy_port)

    def on_keep_user_stream(self, data: dict, request: Request) -> None:
        """Successful callback of keep_user_stream"""
        pass

    def on_keep_user_stream_error(self, exception_type: type, exception_value: Exception, tb, request: Request) -> None:
        """Error callback of keep_user_stream"""
        if not issubclass(exception_type, TimeoutError):        # Ignore timeout exception
            self.on_error(exception_type, exception_value, tb, request)

    def query_history(self, req: HistoryRequest) -> list[BarData]:
        """Query kline history data"""
        history: list[BarData] = []
        limit: int = 1500

        start_time: int = int(datetime.timestamp(req.start))

        while True:
            # Create query parameters
            params: dict = {
                "symbol": req.symbol,
                "interval": INTERVAL_VT2BINANCES[req.interval],
                "limit": limit
            }

            params["startTime"] = start_time * 1000
            path: str = "/fapi/v1/klines"
            if req.end:
                end_time = int(datetime.timestamp(req.end))
                params["endTime"] = end_time * 1000     # Convert to milliseconds

            resp: Response = self.request(
                "GET",
                path=path,
                data={"security": Security.NONE},
                params=params
            )

            # Break the loop if request failed
            if resp.status_code // 100 != 2:
                msg: str = f"Query kline history failed, status code: {resp.status_code}, message: {resp.text}"
                self.gateway.write_log(msg)
                break
            else:
                data: dict = resp.json()
                if not data:
                    msg: str = f"No kline history data is received, start time: {start_time}"
                    self.gateway.write_log(msg)
                    break

                buf: list[BarData] = []

                for row in data:
                    bar: BarData = BarData(
                        symbol=req.symbol,
                        exchange=req.exchange,
                        datetime=generate_datetime(row[0]),
                        interval=req.interval,
                        volume=float(row[5]),
                        turnover=float(row[7]),
                        open_price=float(row[1]),
                        high_price=float(row[2]),
                        low_price=float(row[3]),
                        close_price=float(row[4]),
                        gateway_name=self.gateway_name
                    )
                    bar.extra = {
                        "trade_count": int(row[8]),
                        "active_volume": float(row[9]),
                        "active_turnover": float(row[10]),
                    }
                    buf.append(bar)

                begin: datetime = buf[0].datetime
                end: datetime = buf[-1].datetime

                history.extend(buf)
                msg: str = f"Query kline history finished, {req.symbol} - {req.interval.value}, {begin} - {end}"
                self.gateway.write_log(msg)

                # Break the loop if the latest data received
                if (
                    len(data) < limit
                    or (req.end and end >= req.end)
                ):
                    break

                # Update query start time
                start_dt = bar.datetime + TIMEDELTA_MAP[req.interval]
                start_time = int(datetime.timestamp(start_dt))

            # Wait to meet request flow limit
            sleep(0.5)

        # Remove the unclosed kline
        if history:
            history.pop(-1)

        return history


class BinanceLinearUserWebsocketApi(WebsocketClient):
    """The user data websocket API of BinanceLinearGateway"""

    def __init__(self, gateway: BinanceLinearGateway) -> None:
        """
        The init method of the api.

        gateway: the parent gateway object for pushing callback data.
        """
        super().__init__()

        self.gateway: BinanceLinearGateway = gateway
        self.gateway_name: str = gateway.gateway_name

    def connect(self, url: str, proxy_host: str, proxy_port: int) -> None:
        """Start server connection"""
        self.init(url, proxy_host, proxy_port, receive_timeout=WEBSOCKET_TIMEOUT)
        self.start()

    def on_connected(self) -> None:
        """Callback when server is connected"""
        self.gateway.write_log("User data Websocket API is connected")

    def on_packet(self, packet: dict) -> None:
        """Callback of data update"""
        if packet["e"] == "ACCOUNT_UPDATE":
            self.on_account(packet)
        elif packet["e"] == "ORDER_TRADE_UPDATE":
            self.on_order(packet)
        elif packet["e"] == "listenKeyExpired":
            self.on_listen_key_expired()

    def on_listen_key_expired(self) -> None:
        """Callback of listen key expired"""
        self.gateway.write_log("Listen key is expired")
        self.disconnect()

    def disconnect(self) -> None:
        """Disconnect the websocket"""
        self.gateway.write_log("User data Websocket API is disconnected")
        self.stop()

    def on_account(self, packet: dict) -> None:
        """Callback of account balance and holding position update"""
        for acc_data in packet["a"]["B"]:
            account: AccountData = AccountData(
                accountid=acc_data["a"],
                balance=float(acc_data["wb"]),
                frozen=float(acc_data["wb"]) - float(acc_data["cw"]),
                gateway_name=self.gateway_name
            )

            if account.balance:
                self.gateway.on_account(account)

        for pos_data in packet["a"]["P"]:
            if pos_data["ps"] == "BOTH":
                volume = pos_data["pa"]
                if "." in volume:
                    volume = float(volume)
                else:
                    volume = int(volume)

                position: PositionData = PositionData(
                    symbol=pos_data["s"],
                    exchange=Exchange.BINANCE,
                    direction=Direction.NET,
                    volume=volume,
                    price=float(pos_data["ep"]),
                    pnl=float(pos_data["up"]),
                    gateway_name=self.gateway_name,
                )
                self.gateway.on_position(position)

    def on_order(self, packet: dict) -> None:
        """
        Callback of order and trade update
        When new order created, order status changed will push such event. 
        event type is ORDER_TRADE_UPDATE.
        {
            "e":"ORDER_TRADE_UPDATE",		   // Event Type
            "E":1568879465651,			       // Event Time
            "T":1568879465650,			       // Transaction Time
            "o":{								
                "s":"BTCUSDT",			         // Symbol
                "c":"TEST",				           // Client Order Id
                // special client order id:
                // starts with "autoclose-": liquidation order
                // "adl_autoclose": ADL auto close order
                // "settlement_autoclose-": settlement order for delisting or delivery
                "S":"SELL",					         // Side
                "o":"TRAILING_STOP_MARKET",	 // Order Type
                "f":"GTC",					         // Time in Force
                "q":"0.001",				         // Original Quantity
                "p":"0",					           // Original Price
                "ap":"0",					           // Average Price
                "sp":"7103.04",				       // Stop Price. Please ignore with TRAILING_STOP_MARKET order
                "x":"NEW",					         // Execution Type
                "X":"NEW",					         // Order Status
                "i":8886774,				         // Order Id
                "l":"0",					           // Order Last Filled Quantity
                "z":"0",					           // Order Filled Accumulated Quantity
                "L":"0",					           // Last Filled Price
                "N":"USDT",            	     // Commission Asset, will not push if no commission
                "n":"0",               	     // Commission, will not push if no commission
                "T":1568879465650,			     // Order Trade Time
                "t":0,			        	       // Trade Id
                "b":"0",			    	         // Bids Notional
                "a":"9.91",					         // Ask Notional
                "m":false,					         // Is this trade the maker side?
                "R":false,					         // Is this reduce only
                "wt":"CONTRACT_PRICE", 		   // Stop Price Working Type
                "ot":"TRAILING_STOP_MARKET", // Original Order Type
                "ps":"LONG",					       // Position Side
                "cp":false,						       // If Close-All, pushed with conditional order
                "AP":"7476.89",				       // Activation Price, only puhed with TRAILING_STOP_MARKET order
                "cr":"5.0",					         // Callback Rate, only puhed with TRAILING_STOP_MARKET order
                "pP": false,                 // If price protection is turned on
                "si": 0,                     // ignore
                "ss": 0,                     // ignore
                "rp":"0",	   					       // Realized Profit of the trade
                "V":"EXPIRE_TAKER",          // STP mode
                "pm":"OPPONENT",             // Price match mode
                "gtd":0                      // TIF GTD order auto cancel time
            }
        }
        """
        ord_data: dict = packet["o"]
        key: tuple[str, str] = (ord_data["o"], ord_data["f"])
        order_type: OrderType = ORDERTYPE_BINANCES2VT.get(key, None)
        if not order_type:
            return
        offset = self.gateway.get_order(ord_data["c"]).offset if self.gateway.get_order(ord_data["c"]) else None

        order: OrderData = OrderData(
            symbol=ord_data["s"],
            exchange=Exchange.BINANCE,
            orderid=str(ord_data["c"]),
            type=order_type,
            direction=DIRECTION_BINANCES2VT[ord_data["S"]],
            price=float(ord_data["p"]),
            volume=float(ord_data["q"]),
            traded=float(ord_data["z"]),
            status=STATUS_BINANCES2VT[ord_data["X"]],
            datetime=generate_datetime(packet["E"]),
            gateway_name=self.gateway_name,
            offset=offset
        )

        self.gateway.on_order(order)

        # Round trade volume to meet step size
        trade_volume: float = float(ord_data["l"])
        contract: ContractData = symbol_contract_map.get(order.symbol, None)
        if contract:
            trade_volume = round_to(trade_volume, contract.min_volume)

        if not trade_volume:
            return

        trade: TradeData = TradeData(
            symbol=order.symbol,
            exchange=order.exchange,
            orderid=order.orderid,
            tradeid=ord_data["t"],
            direction=order.direction,
            price=float(ord_data["L"]),
            volume=trade_volume,
            datetime=generate_datetime(ord_data["T"]),
            gateway_name=self.gateway_name,
            offset=offset
        )
        self.gateway.on_trade(trade)

    def on_disconnected(self, status_code: int, msg: str) -> None:
        """Callback when server is disconnected"""
        self.gateway.write_log(f"Trade Websocket API is disconnected, code: {status_code}, msg: {msg}")
        self.gateway.rest_api.start_user_stream()

    def on_error(self, e: Exception) -> None:
        """
        Callback when exception raised.
        """
        self.gateway.write_log(f"Trade Websocket API exception: {e}")


class BinanceLinearDataWebsocketApi(WebsocketClient):
    """The data websocket API of BinanceLinearGateway"""

    def __init__(self, gateway: BinanceLinearGateway) -> None:
        """
        The init method of the api.

        gateway: the parent gateway object for pushing callback data.
        """
        super().__init__()

        self.gateway: BinanceLinearGateway = gateway
        self.gateway_name: str = gateway.gateway_name

        self.ticks: dict[str, TickData] = {}
        self.reqid: int = 0
        self.kline_stream: bool = False

    def connect(
        self,
        server: str,
        kline_stream: bool,
        proxy_host: str,
        proxy_port: int,
    ) -> None:
        """Start server connection"""
        self.kline_stream = kline_stream

        if server == "REAL":
            self.init(F_WEBSOCKET_DATA_HOST, proxy_host, proxy_port, receive_timeout=WEBSOCKET_TIMEOUT)
        else:
            self.init(F_TESTNET_WEBSOCKET_DATA_HOST, proxy_host, proxy_port, receive_timeout=WEBSOCKET_TIMEOUT)

        self.start()

    def on_connected(self) -> None:
        """Callback when server is connected"""
        self.gateway.write_log("Data Websocket API is connected")

        # Resubscribe market data
        if self.ticks:
            channels = []
            for symbol in self.ticks.keys():
                channels.append(f"{symbol}@ticker")
                channels.append(f"{symbol}@depth10")

                if self.kline_stream:
                    channels.append(f"{symbol}@kline_1m")

            req: dict = {
                "method": "SUBSCRIBE",
                "params": channels,
                "id": self.reqid
            }
            self.send_packet(req)

    def subscribe(self, req: SubscribeRequest) -> None:
        """Subscribe market data"""
        if req.symbol in self.ticks:
            return

        if req.symbol not in symbol_contract_map:
            self.gateway.write_log(f"Symbol not found {req.symbol}")
            return

        self.reqid += 1

        # Initialize tick object
        tick: TickData = TickData(
            symbol=req.symbol,
            name=symbol_contract_map[req.symbol].name,
            exchange=Exchange.BINANCE,
            datetime=datetime.now(UTC_TZ),
            gateway_name=self.gateway_name,
        )
        tick.extra = {}
        self.ticks[req.symbol.lower()] = tick

        channels = [
            f"{req.symbol.lower()}@ticker",
            f"{req.symbol.lower()}@depth10"
        ]

        if self.kline_stream:
            channels.append(f"{req.symbol.lower()}@kline_1m")

        req: dict = {
            "method": "SUBSCRIBE",
            "params": channels,
            "id": self.reqid
        }
        self.send_packet(req)

    def on_packet(self, packet: dict) -> None:
        """Callback of data update"""
        stream: str = packet.get("stream", None)

        if not stream:
            return

        data: dict = packet["data"]

        symbol, channel = stream.split("@")
        tick: TickData = self.ticks[symbol]

        if channel == "ticker":
            tick.volume = float(data["v"])
            tick.turnover = float(data["q"])
            tick.open_price = float(data["o"])
            tick.high_price = float(data["h"])
            tick.low_price = float(data["l"])
            tick.last_price = float(data["c"])
            tick.datetime = generate_datetime(float(data["E"]))
        elif channel == "depth10":
            bids: list = data["b"]
            for n in range(min(10, len(bids))):
                price, volume = bids[n]
                tick.__setattr__("bid_price_" + str(n + 1), float(price))
                tick.__setattr__("bid_volume_" + str(n + 1), float(volume))

            asks: list = data["a"]
            for n in range(min(10, len(asks))):
                price, volume = asks[n]
                tick.__setattr__("ask_price_" + str(n + 1), float(price))
                tick.__setattr__("ask_volume_" + str(n + 1), float(volume))
        else:
            kline_data: dict = data["k"]

            # Check if bar is closed
            bar_ready: bool = kline_data.get("x", False)
            if not bar_ready:
                return

            dt: datetime = generate_datetime(float(kline_data["t"]))

            tick.extra["bar"] = BarData(
                symbol=symbol.upper(),
                exchange=Exchange.BINANCE,
                datetime=dt.replace(second=0, microsecond=0),
                interval=Interval.MINUTE,
                volume=float(kline_data["v"]),
                turnover=float(kline_data["q"]),
                open_price=float(kline_data["o"]),
                high_price=float(kline_data["h"]),
                low_price=float(kline_data["l"]),
                close_price=float(kline_data["c"]),
                gateway_name=self.gateway_name
            )

        if tick.last_price:
            tick.localtime = datetime.now()
            self.gateway.on_tick(copy(tick))

    def on_disconnected(self, status_code: int, msg: str) -> None:
        """Callback when server is disconnected"""
        self.gateway.write_log(f"Data Websocket API is disconnected, code: {status_code}, msg: {msg}")

    def on_error(self, e: Exception) -> None:
        """
        Callback when exception raised.
        """
        self.gateway.write_log(f"Data Websocket API exception: {e}")


class BinanceLinearTradeWebsocketApi(WebsocketClient):
    """The trade websocket API of BinanceLinearGateway"""

    def __init__(self, gateway: BinanceLinearGateway) -> None:
        """
        The init method of the api.

        gateway: the parent gateway object for pushing callback data.
        """
        super().__init__()

        self.gateway: BinanceLinearGateway = gateway
        self.gateway_name: str = gateway.gateway_name

        self.key: str = ""
        self.secret: bytes = b""
        self.proxy_port: int = 0
        self.proxy_host: str = ""
        self.server: str = ""

        self.reqid: int = 0
        self.order_count: int = 0
        self.order_prefix: str = ""

        self.reqid_callback_map: dict[int, Callable] = {}
        self.reqid_order_map: dict[int, OrderData] = {}

        self.commission_rate: float = 0.0006

    def connect(
        self,
        key: str,
        secret: str,
        server: str,
        proxy_host: str,
        proxy_port: int
    ) -> None:
        """Start server connection"""
        self.key = key
        self.secret = secret.encode()
        self.proxy_port = proxy_port
        self.proxy_host = proxy_host
        self.server = server

        self.order_prefix = datetime.now().strftime("%y%m%d%H%M%S")

        if self.server == "REAL":
            self.init(F_WEBSOCKET_TRADE_HOST, proxy_host, proxy_port)
        else:
            self.init(F_TESTNET_WEBSOCKET_TRADE_HOST, proxy_host, proxy_port)

        self.start()

    def sign(self, params: dict) -> None:
        """Generate the signature for the request"""
        timestamp: int = int(time.time() * 1000)
        params["timestamp"] = timestamp

        payload: str = "&".join([f"{k}={v}" for k, v in sorted(params.items())])
        signature: str = hmac.new(
            self.secret,
            payload.encode("utf-8"),
            hashlib.sha256
        ).hexdigest()
        params["signature"] = signature

    @lru_cache(maxsize=128)
    def get_cached_contract(self, symbol: str) -> Optional[ContractData]:
        """从缓存中获取合约信息"""
        return symbol_contract_map.get(symbol)

    def send_order(self, req: OrderRequest) -> str:
        """Send new order"""
        # Generate new order id
        self.order_count += 1
        orderid: str = self.order_prefix + str(self.order_count)

        # Push a submitting order event
        order: OrderData = req.create_order_data(
            orderid,
            self.gateway_name
        )
        self.gateway.on_order(order)

        contract: Optional[ContractData] = self.get_cached_contract(req.symbol)
        if contract:
            req.volume = round_volume(float(req.volume), contract.min_volume, self.commission_rate)

        # Create order parameters
        params: dict = {
            "apiKey": self.key,
            "symbol": req.symbol,
            "side": DIRECTION_VT2BINANCES[req.direction],
            "quantity": format_float(req.volume),
            "newClientOrderId": order.orderid, #todo check orderid or vt_orderid
            "newOrderRespType": "FULL"
        }

        if req.type == OrderType.MARKET:
            params["type"] = "MARKET"
        elif req.type == OrderType.STOP:
            params["type"] = "STOP_MARKET"
            params["stopPrice"] = format_float(req.price)
        else:
            order_type, time_condition = ORDERTYPE_VT2BINANCES[req.type]
            params["type"] = order_type
            params["timeInForce"] = time_condition
            params["price"] = format_float(req.price)

        self.sign(params)

        self.reqid += 1
        self.reqid_callback_map[self.reqid] = self.on_send_order
        self.reqid_order_map[self.reqid] = order

        packet: dict = {
            "id": self.reqid,
            "method": "order.place",
            "params": params,
        }
        self.send_packet(packet)

        return order.vt_orderid

    def cancel_order(self, req: CancelRequest) -> None:
        """Cancel existing order"""
        params: dict = {
            "apiKey": self.key,
            "symbol": req.symbol,
            "origClientOrderId": req.orderid
        }
        self.sign(params)

        self.reqid += 1
        self.reqid_callback_map[self.reqid] = self.on_cancel_order

        packet: dict = {
            "id": self.reqid,
            "method": "order.cancel",
            "params": params,
        }
        self.send_packet(packet)

    def on_connected(self) -> None:
        """Callback when server is connected"""
        self.gateway.write_log("Trade Websocket API is connected")

    def on_packet(self, packet: dict) -> None:
        """Callback of data update"""
        reqid: int = packet.get("id", 0)
        callback: Callable = self.reqid_callback_map.get(reqid, None)
        if callback:
            callback(packet)

    def on_send_order(self, packet: dict) -> None:
        """Callback of send order"""
        error: dict = packet.get("error", None)
        if not error:
            return

        error_code: str = error["code"]
        error_msg: str = error["msg"]
        msg: str = f"Send order failed, error code: {error_code}, message: {error_msg}"
        self.gateway.write_log(msg)

        reqid: int = packet.get("id", 0)
        order: OrderData = self.reqid_order_map.get(reqid, None)
        if order:
            order.status = Status.REJECTED
            self.gateway.on_order(order)

    def on_cancel_order(self, packet: dict) -> None:
        """Callback of cancel order"""
        error: dict = packet.get("error", None)
        if not error:
            return

        error_code: str = error["code"]
        error_msg: str = error["msg"]
        msg: str = f"Cancel order failed, error code: {error_code}, message: {error_msg}"
        self.gateway.write_log(msg)


def generate_datetime(timestamp: float) -> datetime:
    """Generate datetime object from Binance timestamp"""
    dt: datetime = datetime.fromtimestamp(timestamp / 1000, tz=UTC_TZ)
    return dt


def format_float(f: float) -> str:
    """
    Convert float number to string with correct precision.

    Fix potential error -1111: Parameter "quantity" has too much precision
    """
    return format_float_positional(f, trim="-")


class BinanceUsdtGateway(BinanceLinearGateway):
    """Compatibility interface for the old BinanceUsdtGateway"""

    default_name: str = "BINANCE_USDT"
