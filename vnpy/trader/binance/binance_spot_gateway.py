import json
import time
from copy import copy
from datetime import datetime, timedelta
from threading import Lock
from typing import Any, Dict, List, Optional

from binance.spot import Spot
from binance.websocket.websocket_client import BinanceWebsocketClient


from vnpy.event import Event, EventEngine
from vnpy.trader.constant import (
    Direction,
    Exchange,
    Product,
    Status,
    OrderType,
    Interval
)
from vnpy.trader.event import EVENT_TIMER
from vnpy.trader.gateway import BaseGateway
from vnpy.trader.object import (
    TickData,
    OrderData,
    TradeData,
    AccountData,
    ContractData,
    BarData,
    OrderRequest,
    CancelRequest,
    SubscribeRequest,
    HistoryRequest
)
from vnpy.trader.utility import round_to

# 实盘REST API地址
REST_HOST: str = "https://api.binance.com"

# 实盘Websocket API地址
WEBSOCKET_TRADE_HOST: str = "wss://stream.binance.com:9443"
WEBSOCKET_DATA_HOST: str = "wss://stream.binance.com:9443"

# 模拟盘REST API地址
TESTNET_REST_HOST: str = "https://testnet.binance.vision"

# 模拟盘Websocket API地址
TESTNET_WEBSOCKET_TRADE_HOST: str = "wss://testnet.binance.vision"
TESTNET_WEBSOCKET_DATA_HOST: str = "wss://testnet.binance.vision"

# 委托状态映射
STATUS_BINANCE2VT: Dict[str, Status] = {
    "NEW": Status.NOTTRADED,
    "PARTIALLY_FILLED": Status.PARTTRADED,
    "FILLED": Status.ALLTRADED,
    "CANCELED": Status.CANCELLED,
    "REJECTED": Status.REJECTED,
    "EXPIRED": Status.CANCELLED
}

# 委托类型映射
ORDERTYPE_VT2BINANCE: Dict[OrderType, str] = {
    OrderType.LIMIT: "LIMIT",
    OrderType.MARKET: "MARKET"
}
ORDERTYPE_BINANCE2VT: Dict[str, OrderType] = {v: k for k, v in ORDERTYPE_VT2BINANCE.items()}

# 买卖方向映射
DIRECTION_VT2BINANCE: Dict[Direction, str] = {
    Direction.LONG: "BUY",
    Direction.SHORT: "SELL"
}
DIRECTION_BINANCE2VT: Dict[str, Direction] = {v: k for k, v in DIRECTION_VT2BINANCE.items()}

# 数据频率映射
INTERVAL_VT2BINANCE: Dict[Interval, str] = {
    Interval.MINUTE: "1m",
    Interval.HOUR: "1h",
    Interval.DAILY: "1d",
}

# 时间间隔映射
TIMEDELTA_MAP: Dict[Interval, timedelta] = {
    Interval.MINUTE: timedelta(minutes=1),
    Interval.HOUR: timedelta(hours=1),
    Interval.DAILY: timedelta(days=1),
}

# 合约数据全局缓存字典
symbol_contract_map: Dict[str, ContractData] = {}


class BinanceSpotGateway(BaseGateway):
    """
    vn.py用于对接币安现货账户的交易接口。
    """

    default_name: str = "BINANCE_SPOT"

    default_setting: Dict[str, Any] = {
        "key": "",
        "secret": "",
        "server": ["REAL", "TESTNET"]
    }

    exchanges: Exchange = [Exchange.BINANCE]

    def __init__(self, event_engine: EventEngine, gateway_name: str) -> None:
        """构造函数"""
        super().__init__(event_engine, gateway_name)

        self.trade_ws_api: "BinanceSpotTradeWebsocketApi" = BinanceSpotTradeWebsocketApi(self)
        self.market_ws_api: "BinanceSpotDataWebsocketApi" = BinanceSpotDataWebsocketApi(self)
        self.rest_api: "BinanceSpotRestAPi" = BinanceSpotRestAPi(self)

        self.orders: Dict[str, OrderData] = {}

    def connect(self, setting: dict):
        """连接交易接口"""
        key: str = setting["key"]
        secret: str = setting["secret"]
        server: str = setting["server"]

        self.rest_api.connect(key, secret, server)
        self.market_ws_api.connect(server)

        self.event_engine.register(EVENT_TIMER, self.process_timer_event)

    def subscribe(self, req: SubscribeRequest) -> None:
        """订阅行情"""
        self.market_ws_api.subscribe(req)

    def send_order(self, req: OrderRequest) -> str:
        """委托下单"""
        return self.rest_api.send_order(req)

    def cancel_order(self, req: CancelRequest) -> None:
        """委托撤单"""
        self.rest_api.cancel_order(req)

    def query_account(self) -> None:
        """查询资金"""
        pass

    def query_position(self) -> None:
        """查询持仓"""
        pass

    def query_history(self, req: HistoryRequest) -> List[BarData]:
        """查询历史数据"""
        return self.rest_api.query_history(req)

    def close(self) -> None:
        """关闭连接"""
        self.rest_api.stop()
        self.trade_ws_api.stop()
        self.market_ws_api.stop()

    def process_timer_event(self, event: Event) -> None:
        """定时事件处理"""
        self.rest_api.keep_user_stream()

    def on_order(self, order: OrderData) -> None:
        """推送委托数据"""
        self.orders[order.orderid] = copy(order)
        super().on_order(order)

    def get_order(self, orderid: str) -> OrderData:
        """查询委托数据"""
        return self.orders.get(orderid, None)


class BinanceSpotRestAPi:
    """币安现货REST API"""

    def __init__(self, gateway: BinanceSpotGateway) -> None:
        """构造函数"""
        super().__init__()

        self.gateway: BinanceSpotGateway = gateway
        self.gateway_name: str = gateway.gateway_name

        self.trade_ws_api: BinanceSpotTradeWebsocketApi = self.gateway.trade_ws_api

        self.key: str = ""
        self.secret: str = ""

        self.user_stream_key: str = ""
        self.keep_alive_count: int = 0
        self.recv_window: int = 5000
        self.time_offset: int = 0

        self.order_count: int = 1_000_000
        self.order_count_lock: Lock = Lock()
        self.connect_time: int = 0

        self._active: bool = False

    def connect(
            self,
            key: str,
            secret: str,
            server: str
    ) -> None:
        """连接REST服务器"""
        self.key = key
        self.secret = secret
        self.server = server

        self._client = Spot(api_key=self.key, api_secret=self.secret)

        self.connect_time = self._client.time()["serverTime"]

        self.gateway.write_log("REST API启动成功")
        self._active = True

        self.query_time()
        self.query_account()
        self.query_order()
        self.query_contract()
        self.start_user_stream()

    def query_time(self) -> None:
        """查询时间"""
        data = self._client.time()
        self.on_query_time(data)

    def query_account(self) -> None:
        """查询资金"""
        self.on_query_account(self._client.account())

    def query_order(self) -> None:
        """查询未成交委托"""
        self.on_query_order(self._client.get_open_orders())

    def query_contract(self) -> None:
        """查询合约信息"""
        self.on_query_contract(self._client.exchange_info())

    def _new_order_id(self) -> int:
        """生成本地委托号"""
        with self.order_count_lock:
            self.order_count += 1
            return self.order_count

    def send_order(self, req: OrderRequest) -> str:
        """委托下单"""
        # 生成本地委托号
        orderid: str = str(self.connect_time + self._new_order_id())

        # 推送提交中事件
        order: OrderData = req.create_order_data(
            orderid,
            self.gateway_name
        )
        self.gateway.on_order(order)

        # 生成委托请求
        params: dict = {
            "symbol": req.symbol.upper(),
            "side": DIRECTION_VT2BINANCE[req.direction],
            "type": ORDERTYPE_VT2BINANCE[req.type],
            "quantity": format(req.volume, "f"),
            "newClientOrderId": orderid,
            "newOrderRespType": "ACK"
        }

        if req.type == OrderType.LIMIT:
            params["timeInForce"] = "GTC"
            params["price"] = str(req.price)
        elif req.type == OrderType.STOP:
            params["type"] = "STOP_MARKET"
            params["stopPrice"] = float(req.price)

        try:
            data = self._client.new_order(**params)
            self.on_send_order(data, order)
        except Exception as e:
            self.on_send_order_error(e, order)
            return ""

        return order.vt_orderid

    def cancel_order(self, req: CancelRequest) -> None:
        """委托撤单"""

        params: dict = {
            "symbol": req.symbol.upper(),
            "origClientOrderId": req.orderid
        }

        order: OrderData = self.gateway.get_order(req.orderid)

        data = self._client.cancel_order(**params)
        self.on_cancel_order(data, order)

    def start_user_stream(self) -> None:
        """生成listenKey"""
        data = self._client.new_listen_key()
        self.on_start_user_stream(data)

    def keep_user_stream(self) -> None:
        """延长listenKey有效期"""
        self.keep_alive_count += 1
        if self.keep_alive_count < 600:
            return
        self.keep_alive_count = 0

        try:
            data = self._client.renew_listen_key(listenKey=self.user_stream_key)
            self.on_keep_user_stream(data)
        except Exception as e:
            self.on_keep_user_stream_error(e)

    def on_query_time(self, data: dict) -> None:
        """时间查询回报"""
        local_time = int(time.time() * 1000)
        server_time = int(data["serverTime"])
        self.time_offset = local_time - server_time

    def on_query_account(self, data: dict) -> None:
        """资金查询回报"""
        for account_data in data["balances"]:
            account: AccountData = AccountData(
                accountid=account_data["asset"],
                balance=float(account_data["free"]) + float(account_data["locked"]),
                frozen=float(account_data["locked"]),
                gateway_name=self.gateway_name
            )

            if account.balance:
                self.gateway.on_account(account)

        self.gateway.write_log("账户资金查询成功")

    def on_query_order(self, data: dict) -> None:
        """未成交委托查询回报"""
        for d in data:
            # 过滤不支持类型的委托
            if d["type"] not in ORDERTYPE_BINANCE2VT:
                continue

            order: OrderData = OrderData(
                orderid=d["clientOrderId"],
                symbol=d["symbol"].lower(),
                exchange=Exchange.BINANCE,
                price=float(d["price"]),
                volume=float(d["origQty"]),
                type=ORDERTYPE_BINANCE2VT[d["type"]],
                direction=DIRECTION_BINANCE2VT[d["side"]],
                traded=float(d["executedQty"]),
                status=STATUS_BINANCE2VT.get(d["status"], None),
                datetime=datetime.fromtimestamp(int(d["time"])/1000),
                gateway_name=self.gateway_name,
            )
            self.gateway.on_order(order)

        self.gateway.write_log("委托信息查询成功")

    def on_query_contract(self, data: dict) -> None:
        """合约信息查询回报"""
        for d in data["symbols"]:
            base_currency: str = d["baseAsset"]
            quote_currency: str = d["quoteAsset"]
            name: str = f"{base_currency.upper()}/{quote_currency.upper()}"

            pricetick: float = 1
            min_volume: float = 1

            for f in d["filters"]:
                if f["filterType"] == "PRICE_FILTER":
                    pricetick = float(f["tickSize"])
                elif f["filterType"] == "LOT_SIZE":
                    min_volume = float(f["stepSize"])

            contract: ContractData = ContractData(
                symbol=d["symbol"].lower(),
                exchange=Exchange.BINANCE,
                name=name,
                pricetick=pricetick,
                size=1,
                min_volume=min_volume,
                product=Product.SPOT,
                history_data=True,
                gateway_name=self.gateway_name,
                stop_supported=True
            )
            self.gateway.on_contract(contract)

            symbol_contract_map[contract.symbol] = contract

        self.gateway.write_log("合约信息查询成功")

    def on_send_order(self, data: dict, order: OrderData) -> None:
        """委托下单回报"""
        if data['status'] not in STATUS_BINANCE2VT:
            self.on_send_order_failed(data, order)
        pass

    def on_send_order_failed(self, data: dict, order: OrderData) -> None:
        """委托下单失败服务器报错回报"""
        order.status = Status.REJECTED
        self.gateway.on_order(order)

        self.gateway.write_log(f"{order.vt_orderid}委托失败，状态码：{data['code']}, 信息：{data['msg']}")

    def on_send_order_error(
            self, exception, order: OrderData
    ) -> None:
        """委托下单回报函数报错回报"""
        order.status = Status.REJECTED
        self.gateway.on_order(order)

        self.gateway.write_log(f"{order.vt_orderid}委托失败：{exception}")

    def on_cancel_order(self, data: dict, order: OrderData) -> None:
        """委托撤单回报"""
        if data['code']:
            self.on_cancel_failed(data, order)
        pass

    def on_cancel_failed(self, data: dict, order: OrderData) -> None:
        """撤单回报函数报错回报"""
        if order:
            order.status = Status.REJECTED
            self.gateway.on_order(order)

        msg = f"撤单失败，状态码：{data['code']}，信息：{data['msg']}"
        self.gateway.write_log(msg)

    def on_start_user_stream(self, data: dict) -> None:
        """生成listenKey回报"""
        self.user_stream_key = data["listenKey"]
        self.keep_alive_count = 0

        if self.server == "REAL":
            url = WEBSOCKET_TRADE_HOST
        else:
            url = TESTNET_WEBSOCKET_TRADE_HOST

        self.trade_ws_api.connect(url, self.user_stream_key)

    def on_keep_user_stream(self, data) -> None:
        """延长listenKey有效期回报"""
        pass

    def on_keep_user_stream_error(
            self, exception) -> None:
        """延长listenKey有效期函数报错回报"""
        # 当延长listenKey有效期时，忽略超时报错
        self.gateway.write_log(f"延长listenKey有效期失败：{exception}; reconnecting...")
        try:
            self.start_user_stream()
        except Exception as e:
            self.gateway.write_log(f"重连失败：{e}")

    def query_history(self, req: HistoryRequest) -> List[BarData]:
        """查询历史数据"""
        history: List[BarData] = []
        limit: int = 1000
        start_time: int = int(datetime.timestamp(req.start))

        sleep_seconds = 0.5
        while True:
            # 创建查询参数
            params: dict = {
                "symbol": req.symbol.upper(),
                "interval": INTERVAL_VT2BINANCE[req.interval],
                "limit": limit,
                "startTime": start_time * 1000,  # 转换成毫秒
            }

            if req.end:
                end_time: int = int(datetime.timestamp(req.end))
                interval_seconds = int(TIMEDELTA_MAP[req.interval].total_seconds())  # 周期的秒数
                if end_time // interval_seconds == datetime.now().timestamp() // interval_seconds:  # 结束于现在，则不要当下未完成的柱子
                    end_time -= interval_seconds

                params["endTime"] = end_time * 1000

            try:
                data = self._client.klines(**params)
                data = json.loads(data)
                if data['code']:
                    if data['code'] == 429:
                        self.gateway.write_log(f"获取历史数据失败：{data['code']}, {data['msg']}")
                        self.gateway.write_log(f"{sleep_seconds=} for retring connection")
                        time.sleep(sleep_seconds)
                        sleep_seconds *= 2
                        continue
                    else:
                        sleep_seconds = 0.5

                    if data["code"] // 100 != 2:
                        self.gateway.write_log(f"获取历史数据失败：{data['code']}, {data['msg']}")
                        break
                else:
                    for row in data:
                        bar: BarData = BarData(
                            symbol=req.symbol,
                            exchange=req.exchange,
                            datetime=datetime.fromtimestamp(row[0]),
                            interval=req.interval,
                            volume=float(row[5]),
                            turnover=float(row[7]),
                            open_price=float(row[1]),
                            high_price=float(row[2]),
                            low_price=float(row[3]),
                            close_price=float(row[4]),
                            gateway_name=self.gateway_name
                        )
                        history.append(bar)

                    begin: datetime = history[0].datetime
                    end: datetime = history[-1].datetime
                    self.gateway.write_log(f"获取历史数据成功，{req.symbol} - {req.interval.value}, {begin} - {end}")

                    if len(data) < limit:
                        break

                    start_dt = bar.datetime + TIMEDELTA_MAP[req.interval]
                    start_time = int(datetime.timestamp(start_dt))
            except Exception as e:
                self.gateway.write_log(f"获取历史数据失败：{e}")
                break

        return history

    def stop(self) -> None:
        """停止"""
        self._active = False
        self._client.close_listen_key(listenKey=self.user_stream_key)


class BinanceSpotTradeWebsocketApi:
    """币安现货交易Websocket API"""

    def __init__(self, gateway: BinanceSpotGateway) -> None:
        """构造函数"""
        super().__init__()

        self.gateway: BinanceSpotGateway = gateway
        self.gateway_name = gateway.gateway_name
        self._active: bool = False

    def connect(self, stream_url: str, listen_key: str) -> None:
        """连接Websocket交易频道"""
        self._client = SpotWebsocketStreamClient(stream_url=stream_url,
                                                 on_message=self.on_packet)
        self._client.user_data(listen_key)

        self._active = True

        self.on_connected()

    def on_connected(self) -> None:
        """连接成功回报"""
        self.gateway.write_log("交易Websocket API连接成功")

    def on_packet(self, _, packet) -> None:
        """推送数据回报"""
        if isinstance(packet, str):
            packet = json.loads(packet)
        event_type = packet.get("e", None)
        if event_type == "outboundAccountPosition":
            self.on_account(packet)
        elif event_type == "executionReport":
            self.on_order(packet)
        elif event_type == "listenKeyExpired":
            self.on_listen_key_expired()

    def on_listen_key_expired(self) -> None:
        """ListenKey过期"""
        self.gateway.write_log("listenKey过期")
        self.disconnect()

    def disconnect(self) -> None:
        """"主动断开webscoket链接"""
        self._active = False
        if self._client:
            self._client.stop()
            self.gateway.write_log("交易Websocket API断开")

    def on_account(self, packet: dict) -> None:
        """资金更新推送"""
        for d in packet["B"]:
            account: AccountData = AccountData(
                accountid=d["a"],
                balance=float(d["f"]) + float(d["l"]),
                frozen=float(d["l"]),
                gateway_name=self.gateway_name
            )

            if account.balance:
                self.gateway.on_account(account)

    def on_order(self, packet: dict) -> None:
        """委托更新推送"""
        # 过滤不支持类型的委托
        if packet["o"] not in ORDERTYPE_BINANCE2VT:
            return

        if packet["C"] == "":
            orderid: str = packet["c"]
        else:
            orderid: str = packet["C"]

        offset = self.gateway.get_order(orderid).offset if self.gateway.get_order(orderid) else None

        order: OrderData = OrderData(
            symbol=packet["s"].lower(),
            exchange=Exchange.BINANCE,
            orderid=orderid,
            type=ORDERTYPE_BINANCE2VT[packet["o"]],
            direction=DIRECTION_BINANCE2VT[packet["S"]],
            price=float(packet["p"]),
            volume=float(packet["q"]),
            traded=float(packet["z"]),
            status=STATUS_BINANCE2VT[packet["X"]],
            datetime=datetime.fromtimestamp(packet["O"]/1000),
            gateway_name=self.gateway_name,
            offset=offset
        )

        self.gateway.on_order(order)

        # 将成交数量四舍五入到正确精度
        trade_volume = float(packet["l"])
        contract: ContractData = symbol_contract_map.get(order.symbol, None)
        if contract:
            trade_volume = round_to(trade_volume, contract.min_volume)

        if not trade_volume:
            return

        trade: TradeData = TradeData(
            symbol=order.symbol,
            exchange=order.exchange,
            orderid=order.orderid,
            tradeid=packet["t"],
            direction=order.direction,
            price=float(packet["L"]),
            volume=trade_volume,
            datetime=datetime.fromtimestamp(packet["T"]/1000),
            gateway_name=self.gateway_name,
            offset=offset
        )
        self.gateway.on_trade(trade)

    def on_disconnected(self) -> None:
        """连接断开回报"""
        self.gateway.write_log("交易Websocket API断开")
        self.gateway.rest_api.start_user_stream()

    def stop(self):
        self.disconnect()
        self._active = False


class BinanceSpotDataWebsocketApi:
    """币安现货行情Websocket API"""

    def __init__(self, gateway: BinanceSpotGateway) -> None:
        """构造函数"""
        super().__init__()

        self.gateway: BinanceSpotGateway = gateway
        self.gateway_name: str = gateway.gateway_name

        self.ticks: Dict[str, TickData] = {}
        self.reqid: int = 0
        self._active: bool = False

    def connect(self, server: str):
        """连接Websocket行情频道"""
        if server == "REAL":
            self._client = SpotWebsocketStreamClient(stream_url=WEBSOCKET_DATA_HOST, on_message=self.on_packet)
        else:
            self._client = SpotWebsocketStreamClient(stream_url=TESTNET_WEBSOCKET_DATA_HOST, on_message=self.on_packet)

        self._active = True
        self.on_connected()

    def on_connected(self) -> None:
        """连接成功回报"""
        self.gateway.write_log("行情Websocket API连接成功")

        # 重新订阅行情
        if self.ticks:
            for symbol in self.ticks.keys():
                self._client.ticker(symbol)
                self._client.partial_book_depth(symbol)

    def subscribe(self, req: SubscribeRequest) -> None:
        """订阅行情"""
        if req.symbol in self.ticks:
            return

        if req.symbol not in symbol_contract_map:
            self.gateway.write_log(f"找不到该合约代码{req.symbol}")
            return

        self.reqid += 1

        # 创建TICK对象
        tick: TickData = TickData(
            symbol=req.symbol,
            name=symbol_contract_map[req.symbol].name,
            exchange=Exchange.BINANCE,
            datetime=datetime.now(),
            gateway_name=self.gateway_name,
        )
        self.ticks[req.symbol] = tick

        self._client.ticker(req.symbol)
        self._client.partial_book_depth(req.symbol)

    def on_packet(self, _, packet: dict) -> None:
        """推送数据回报"""
        stream: Optional[str] = packet.get("stream", None)

        if not stream:
            return

        data: dict = packet["data"]

        symbol, channel = stream.split("@")
        tick: TickData = self.ticks[symbol]

        if channel == "ticker":
            tick.volume = float(data['v'])
            tick.turnover = float(data['q'])
            tick.open_price = float(data['o'])
            tick.high_price = float(data['h'])
            tick.low_price = float(data['l'])
            tick.last_price = float(data['c'])
            tick.datetime = datetime.fromtimestamp(float(data['E'])/1000)
        else:
            bids: list = data["bids"]
            for n in range(min(5, len(bids))):
                price, volume = bids[n]
                tick.__setattr__("bid_price_" + str(n + 1), float(price))
                tick.__setattr__("bid_volume_" + str(n + 1), float(volume))

            asks: list = data["asks"]
            for n in range(min(5, len(asks))):
                price, volume = asks[n]
                tick.__setattr__("ask_price_" + str(n + 1), float(price))
                tick.__setattr__("ask_volume_" + str(n + 1), float(volume))

        if tick.last_price:
            tick.localtime = datetime.now()
            self.gateway.on_tick(copy(tick))

    def on_disconnected(self) -> None:
        """连接断开回报"""
        self._client.stop()
        self.gateway.write_log("行情Websocket API断开")

    def stop(self):
        self._active = False
        if self._client:
            self._client.stop()


class SpotWebsocketStreamClient(BinanceWebsocketClient):
    def __init__(
            self,
            stream_url="wss://stream.binance.com:9443",
            on_message=None,
            on_open=None,
            on_close=None,
            on_error=None,
            on_ping=None,
            on_pong=None,
            is_combined=False,
            timeout=None,
            logger=None,
            proxies: Optional[dict] = None,
    ):
        if is_combined:
            stream_url = stream_url + "/stream"
        else:
            stream_url = stream_url + "/ws"
        super().__init__(
            stream_url,
            on_message=on_message,
            on_open=on_open,
            on_close=on_close,
            on_error=on_error,
            on_ping=on_ping,
            on_pong=on_pong,
            timeout=timeout,
            logger=logger,
            proxies=proxies,
        )

    def agg_trade(self, symbol: str | list[str], id=None, action=None, **kwargs):
        """Aggregate Trade Streams

        The Aggregate Trade Streams push trade information that is aggregated for a single taker order.

        Stream Name: <symbol>@aggTrade

        Update Speed: Real-time
        """
        if isinstance(symbol, str):
            symbol = [symbol]
        stream_name = ["{}@aggTrade".format(s.lower()) for s in symbol]

        self.send_message_to_server(stream_name, action=action, id=id)

    def trade(self, symbol: str | list[str], id=None, action=None, **kwargs):
        """Trade Streams

        The Trade Streams push raw trade information; each trade has a unique buyer and seller.

        Stream Name: <symbol>@trade

        Update Speed: Real-time
        """

        if isinstance(symbol, str):
            symbol = [symbol]
        stream_name = ["{}@trade".format(s.lower()) for s in symbol]

        self.send_message_to_server(stream_name, action=action, id=id)

    def kline(self, symbol: str | list[str], interval: str, id=None, action=None):
        """Kline/Candlestick Streams

        The Kline/Candlestick Stream push updates to the current klines/candlestick every second.

        Stream Name: <symbol>@kline_<interval>

        interval:
        m -> minutes; h -> hours; d -> days; w -> weeks; M -> months

        - 1m
        - 3m
        - 5m
        - 15m
        - 30m
        - 1h
        - 2h
        - 4h
        - 6h
        - 8h
        - 12h
        - 1d
        - 3d
        - 1w
        - 1M

        Update Speed: 2000ms
        """
        if isinstance(symbol, str):
            symbol = [symbol]
        stream_name = ["{}@kline_{}".format(s.lower(), interval) for s in symbol]

        self.send_message_to_server(stream_name, action=action, id=id)

    def mini_ticker(self, symbol=None, id=None, action=None, **kwargs):
        """Individual symbol or all symbols mini ticker

        24hr rolling window mini-ticker statistics.
        These are NOT the statistics of the UTC day, but a 24hr rolling window for the previous 24hrs

        Stream Name: <symbol>@miniTicker or
        Stream Name: !miniTicker@arr

        Update Speed: 1000ms
        """

        if symbol is None:
            stream_name = "!miniTicker@arr"
        else:
            stream_name = "{}@miniTicker".format(symbol.lower())

        self.send_message_to_server(stream_name, action=action, id=id)

    def ticker(self, symbol=None, id=None, action=None, **kwargs):
        """Individual symbol or all symbols ticker

        24hr rolling window ticker statistics for a single symbol.
        These are NOT the statistics of the UTC day, but a 24hr rolling window for the previous 24hrs.

        Stream Name: <symbol>@ticker or
        Stream Name: !ticker@arr

        Update Speed: 1000ms
        """

        if symbol is None:
            stream_name = "!ticker@arr"
        else:
            stream_name = "{}@ticker".format(symbol.lower())
        self.send_message_to_server(stream_name, action=action, id=id)

    def book_ticker(self, symbol, id=None, action=None, **kwargs):
        """Individual symbol book ticker

        Pushes any update to the best bid or ask's price or quantity in real-time for a specified symbol.

        Stream Name: <symbol>@bookTicker

        Update Speed: realtime
        """

        self.send_message_to_server(
            "{}@bookTicker".format(symbol.lower()), action=action, id=id
        )

    def partial_book_depth(
            self, symbol: str, level=5, speed=1000, id=None, action=None, **kwargs
    ):
        """Partial Book Depth Streams

        Top bids and asks, Valid are 5, 10, or 20.

        Stream Names: <symbol>@depth<levels> OR <symbol>@depth<levels>@100ms.

        Update Speed: 1000ms or 100ms
        """
        self.send_message_to_server(
            "{}@depth{}@{}ms".format(symbol.lower(), level, speed), id=id, action=action
        )

    def rolling_window_ticker(self, symbol: str, windowSize: str, id=None, action=None):
        """Rolling window ticker statistics for a single symbol, computed over multiple windows.

        Stream Name: <symbol>@ticker_<window_size>

        Window Sizes: 1h, 4h, 1d

        Update Speed: 1000ms

        Note: This stream is different from the <symbol>@ticker stream. The open time "O" always starts on a minute, while the closing time "C" is the current time of the update. As such, the effective window might be up to 59999ms wider that <window_size>.
        """
        self.send_message_to_server(
            "{}@ticker_{}".format(symbol.lower(), windowSize), id=id, action=action
        )

    def rolling_window_ticker_all_symbols(self, windowSize: str, id=None, action=None):
        """All Market Rolling Window Statistics Streams

        Rolling window ticker statistics for all market symbols, computed over multiple windows. Note that only tickers that have changed will be present in the array.

        Stream Name: !ticker_<window-size>@arr

        Window Size: 1h, 4h, 1d

        Update Speed: 1000ms
        """
        self.send_message_to_server(
            "!ticker_{}@arr".format(windowSize), id=id, action=action
        )

    def diff_book_depth(self, symbol: str, speed=1000, id=None, action=None, **kwargs):
        """Diff. Depth Stream

        Stream Name: <symbol>@depth OR <symbol>@depth@100ms

        Update Speed: 1000ms or 100ms

        Order book price and quantity depth updates used to locally manage an order book.
        """

        self.send_message_to_server(
            "{}@depth@{}ms".format(symbol.lower(), speed), action=action, id=id
        )

    def user_data(self, listen_key: str, id=None, action=None, **kwargs):
        """Listen to user data by using the provided listen_key"""
        self.send_message_to_server(listen_key, action=action, id=id)
