from typing import Callable

from vnpy.trader.object import (
    TickData,
    OrderData,
    TradeData,
    PositionData,
    AccountData,
    ContractData,
    OrderRequest,
    CancelRequest,
    SubscribeRequest,
    HistoryRequest,
)
from vnpy.trader.constant import (
    Direction,
    Offset,
    Exchange,
    OrderType,
    Product,
    Status,
    OptionType
)
from vnpy.trader.gateway import BaseGateway
from vnpy.api.websocket import WebsocketClient

from datetime import datetime
from copy import copy


WEBSOCKET_HOST = "wss://www.deribit.com/ws/api/v2"

PRODUCT_DERIBIT2VT = {
    "future": Product.FUTURES,
    "option": Product.OPTION
}
OPTIONTYPE_DERIBIT2VT = {
    "call": OptionType.CALL,
    "put": OptionType.PUT
}
DIRECTION_VT2DERIBIT = {Direction.LONG: "buy", Direction.SHORT: "sell"}
ORDERTYPE_VT2DERIBIT = {
    OrderType.LIMIT: "limit",
    OrderType.MARKET: "market",
}
ORDERTYPE_DERIBIT2VT = {v: k for k, v in ORDERTYPE_VT2DERIBIT.items()}
DIRECTION_DERIBIT2VT = {v: k for k, v in DIRECTION_VT2DERIBIT.items()}
STATUS_DERIBIT2VT = {
    "open": Status.NOTTRADED,
    "filled": Status.ALLTRADED,
    "rejected": Status.REJECTED,
    "cancelled": Status.CANCELLED,
}


class DeribitGateway(BaseGateway):
    """"""

    default_setting = {
        "key": "",
        "secret": "",
        "proxy_host": "",
        "proxy_port": ""
    }

    exchanges = [Exchange.DERIBIT]

    def __init__(self, event_engine):
        """"""
        super().__init__(event_engine, "DERIBIT")

        self.ws_api = DeribitWebsocketApi(self)

    def connect(self, setting: dict):
        """"""
        key = setting["key"]
        secret = setting["secret"]
        proxy_host = setting["proxy_host"]
        proxy_port = setting["proxy_port"]

        if proxy_port.isdigit():
            proxy_port = int(proxy_port)
        else:
            proxy_port = 0

        self.ws_api.connect(
            key,
            secret,
            proxy_host,
            proxy_port,
        )

    def subscribe(self, req: SubscribeRequest):
        """"""
        self.ws_api.subscribe(req)

    def send_order(self, req: OrderRequest):
        """"""
        return self.ws_api.send_order(req)

    def cancel_order(self, req: CancelRequest):
        """"""
        return self.ws_api.cancel_order(req)

    def query_account(self):
        """"""
        self.ws_api.query_account()

    def query_position(self):
        """
        Query holding positions.
        """
        pass

    def query_history(self, req: HistoryRequest):
        """
        Query bar history data.
        """
        pass

    def close(self):
        """"""
        self.ws_api.stop()


class DeribitWebsocketApi(WebsocketClient):
    """"""

    def __init__(self, gateway: BaseGateway):
        """"""
        super().__init__()

        self.gateway = gateway
        self.gateway_name = gateway.gateway_name

        self.key = ""
        self.secret = ""
        self.access_token = ""

        self.reqid = 1
        self.reqid_callback_map = {}
        self.reqid_currency_map = {}
        self.reqid_order_map = {}

        self.connect_time = 0
        self.order_count = 1000000
        self.local_sys_map = {}
        self.sys_local_map = {}
        self.cancel_requests = {}

        self.callbacks = {
            "ticker": self.on_ticker,
            "book": self.on_orderbook,
            "user": self.on_user_update,
        }

        self.ticks = {}

    def connect(
        self,
        key: str,
        secret: str,
        proxy_host: str,
        proxy_port: int
    ):
        """"""
        self.key = key
        self.secret = secret

        self.connect_time = (
            int(datetime.now().strftime("%y%m%d%H%M%S")) * self.order_count
        )

        self.init(WEBSOCKET_HOST, proxy_host, proxy_port)
        self.start()

    def subscribe(self, req: SubscribeRequest):
        """"""
        symbol = req.symbol

        self.ticks[symbol] = TickData(
            gateway_name=self.gateway_name,
            symbol=symbol,
            exchange=Exchange.DERIBIT,
            datetime=datetime.now(),
        )

        params = {
            "channels": [
                f"ticker.{symbol}.100ms",
                f"book.{symbol}.none.10.100ms",
                f"user.changes.{symbol}.raw"
            ],
            "access_token": self.access_token
        }

        self.send_request("private/subscribe", params)

    def send_order(self, req: OrderRequest):
        """"""
        self.order_count += 1
        orderid = str(self.connect_time + self.order_count)

        order = req.create_order_data(orderid, self.gateway_name)
        self.gateway.on_order(order)

        side = DIRECTION_VT2DERIBIT[req.direction]
        method = "private/" + side

        params = {
            "instrument_name": req.symbol,
            "amount": int(req.volume),
            "type": ORDERTYPE_VT2DERIBIT[req.type],
            "label": orderid,
            "price": req.price
        }

        if req.offset == Offset.CLOSE:
            params["reduce_only"] = True

        reqid = self.send_request(
            method,
            params,
            self.on_send_order
        )
        self.reqid_order_map[reqid] = order

        return order.vt_orderid

    def cancel_order(self, req: CancelRequest):
        """"""
        if req.orderid not in self.local_sys_map:
            self.cancel_requests[req.orderid] = req
            return

        sys_id = self.local_sys_map[req.orderid]

        params = {
            "order_id": sys_id,
            "access_token": self.access_token,
        }

        self.send_request(
            "private/cancel",
            params,
            self.on_cancel_order
        )

    def get_access_token(self):
        """
        use the access key and secret to get access token
        """
        params = {
            "grant_type": "client_credentials",
            "client_id": self.key,
            "client_secret": self.secret
        }

        self.send_request(
            "public/auth",
            params,
            self.on_access_token
        )

    def query_instrument(self):
        """"""
        for currency in ["BTC", "ETH"]:
            params = {
                "currency": currency,
                "expired": False,
            }

            self.send_request(
                "public/get_instruments",
                params,
                self.on_query_instrument
            )

    def query_account(self):
        """"""
        for currency in ["BTC", "ETH"]:
            params = {
                "currency": currency,
                "access_token": self.access_token
            }

            self.send_request(
                "private/get_account_summary",
                params,
                self.on_query_account
            )

    def query_position(self):
        """"""
        for currency in ["BTC", "ETH"]:
            params = {
                "currency": currency,
                "access_token": self.access_token
            }

            self.send_request(
                "private/get_positions",
                params,
                self.on_query_position
            )

    def query_order(self):
        """"""
        for currency in ["BTC", "ETH"]:
            params = {
                "currency": currency,
                "access_token": self.access_token
            }

            self.send_request(
                "private/get_open_orders_by_currency",
                params,
                self.on_query_order
            )

    def on_connected(self):
        """
        Callback when websocket is connected successfully.
        """
        self.gateway.write_log("服务器连接成功")

        self.get_access_token()
        self.query_instrument()

    def on_disconnected(self):
        """
        Callback when websocket connection is lost.
        """
        self.gateway.write_log("服务器连接断开")

    def on_packet(self, packet: dict):
        """
        callback when data is received and unpacked
        """
        if "id" in packet:
            packet_id = packet["id"]

            if packet_id in self.reqid_callback_map.keys():
                callback = self.reqid_callback_map[packet_id]
                callback(packet)

        elif "params" in packet:
            channel = packet["params"]["channel"]
            kind = channel.split(".")[0]

            callback = self.callbacks[kind]
            callback(packet)

    def on_access_token(self, packet: dict):
        """"""
        data = packet["result"]
        self.access_token = data["access_token"]

        self.gateway.write_log("服务器登录成功")

        self.query_position()
        self.query_account()
        self.query_order()

        # Subscribe to account update
        params = {
            "channels": [
                "user.portfolio.btc",
                "user.portfolio.eth"
            ],
            "access_token": self.access_token
        }

        self.send_request("private/subscribe", params)

    def on_query_instrument(self, packet: dict):
        """"""
        currency = self.reqid_currency_map[packet["id"]]

        for d in packet["result"]:
            contract = ContractData(
                symbol=d["instrument_name"],
                exchange=Exchange.DERIBIT,
                name=d["instrument_name"],
                product=PRODUCT_DERIBIT2VT[d["kind"]],
                pricetick=d["tick_size"],
                size=d["contract_size"],
                min_volume=d["min_trade_amount"],
                net_position=True,
                history_data=False,
                gateway_name=self.gateway_name,
            )

            if contract.product == Product.OPTION:
                contract.option_portfolio = d["base_currency"]
                contract.option_strike = d["strike"]
                contract.option_index = str(d["strike"])
                contract.option_underlying = d["base_currency"]
                contract.option_type = OPTIONTYPE_DERIBIT2VT[d["option_type"]]
                contract.option_expiry = datetime.fromtimestamp(
                    d["expiration_timestamp"] / 1000
                )

            self.gateway.on_contract(contract)

        self.gateway.write_log(f"{currency}合约信息查询成功")

    def on_query_position(self, packet: dict):
        """"""
        data = packet["result"]
        currency = self.reqid_currency_map[packet["id"]]

        for pos in data:
            position = PositionData(
                symbol=pos["instrument_name"],
                exchange=Exchange.DERIBIT,
                direction=Direction.NET,
                volume=pos["size"],
                pnl=float(pos["floating_profit_loss"]),
                gateway_name=self.gateway_name,
            )
            self.gateway.on_position(position)

        self.gateway.write_log(f"{currency}持仓查询成功")

    def on_query_account(self, packet: dict):
        """"""
        data = packet["result"]
        currency = data["currency"]

        account = AccountData(
            accountid=currency,
            balance=data["balance"],
            frozen=data["balance"] - data["available_funds"],
            gateway_name=self.gateway_name,
        )
        self.gateway.on_account(account)

        self.gateway.write_log(f"{currency}资金查询成功")

    def on_query_order(self, packet: dict):
        """"""
        data = packet["result"]
        currency = self.reqid_currency_map[packet["id"]]

        for d in data:
            self.on_order(d)

        self.gateway.write_log(f"{currency}委托查询成功")

    def on_send_order(self, packet: dict):
        """"""
        error = packet.get("error", None)
        if not error:
            return

        msg = error["message"]
        reason = error["data"]["reason"]
        code = error["code"]

        self.gateway.write_log(
            f"委托失败，代码：{code}，类型：{msg}，原因：{reason}"
        )

        order = self.reqid_order_map[packet["id"]]
        order.status = Status.REJECTED
        self.gateway.on_order(order)

    def on_cancel_order(self, packet: dict):
        """"""
        data = packet["result"]
        orderid = data["label"]

        order = OrderData(
            symbol=data["instrument_name"],
            exchange=Exchange.DERIBIT,
            type=ORDERTYPE_DERIBIT2VT[data["order_type"]],
            orderid=orderid,
            direction=DIRECTION_DERIBIT2VT[data["direction"]],
            price=float(data["price"]),
            volume=float(data["amount"]),
            traded=float(data["filled_amount"]),
            time=str(datetime.fromtimestamp(data["last_update_timestamp"] / 1000)),
            status=STATUS_DERIBIT2VT[data["order_state"]],
            gateway_name=self.gateway_name,
        )

        self.gateway.on_order(copy(order))

    def on_user_update(self, packet: dict):
        """"""
        if "portfolio" in packet["params"]["channel"]:
            self.on_account(packet)
            return

        data = packet["params"]["data"]

        trades = data["trades"]
        positions = data["positions"]
        orders = data["orders"]

        if orders:
            for order in orders:
                self.on_order(order)

        if trades:
            for trade in trades:
                self.on_trade(trade, orders[0]["order_id"])

        if positions:
            for position in positions:
                self.on_position(position)

    def on_order(self, data: dict):
        """"""
        if data["label"]:
            local_id = data["label"]
        else:
            local_id = data["order_id"]

        sys_id = data["order_id"]
        self.local_sys_map[local_id] = sys_id
        self.sys_local_map[sys_id] = local_id

        order = OrderData(
            symbol=data["instrument_name"],
            exchange=Exchange.DERIBIT,
            type=ORDERTYPE_DERIBIT2VT[data["order_type"]],
            orderid=local_id,
            direction=DIRECTION_DERIBIT2VT[data["direction"]],
            price=float(data["price"]),
            volume=float(data["amount"]),
            traded=float(data["filled_amount"]),
            time=str(datetime.fromtimestamp(data["last_update_timestamp"] / 1000)),
            status=STATUS_DERIBIT2VT[data["order_state"]],
            gateway_name=self.gateway_name,
        )

        if data["reduce_only"]:
            order.offset = Offset.CLOSE

        self.gateway.on_order(order)

        # Send cancel requests if necessary
        if order.orderid in self.cancel_requests:
            req = self.cancel_requests.pop(order.orderid)

            if order.is_active():
                self.cancel_order(req)

    def on_trade(self, data: list, orderid):
        """"""
        sys_id = data["order_id"]
        local_id = self.sys_local_map[sys_id]

        trade = TradeData(
            symbol=data["instrument_name"],
            exchange=Exchange.DERIBIT,
            orderid=local_id,
            tradeid=data["trade_id"],
            direction=DIRECTION_DERIBIT2VT[data["direction"]],
            price=float(data["price"]),
            volume=float(data["amount"]),
            time=str(datetime.fromtimestamp(data["timestamp"] / 1000)),
            gateway_name=self.gateway_name,
        )

        self.gateway.on_trade(trade)

    def on_position(self, data: dict):
        """"""
        pos = PositionData(
            symbol=data["instrument_name"],
            exchange=Exchange.DERIBIT,
            direction=Direction.NET,
            volume=data["size"],
            price=data["average_price"],
            pnl=float(data["floating_profit_loss"]),
            gateway_name=self.gateway_name,
        )

        self.gateway.on_position(pos)

    def on_account(self, packet: dict):
        """"""
        data = packet["params"]["data"]

        account = AccountData(
            accountid=data["currency"],
            balance=data["balance"],
            frozen=data["balance"] - data["available_funds"],
            gateway_name=self.gateway_name,
        )
        self.gateway.on_account(account)

    def on_ticker(self, packet: dict):
        """"""
        data = packet["params"]["data"]

        symbol = data["instrument_name"]
        tick = self.ticks.get(symbol, None)
        if not tick:
            return

        tick.last_price = data["last_price"]
        tick.high_price = data["stats"]["high"]
        tick.low_price = data["stats"]["low"]
        tick.volume = data["stats"]["volume"]
        tick.datetime = datetime.fromtimestamp(data["timestamp"] / 1000)

        self.gateway.on_tick(copy(tick))

    def on_orderbook(self, packet: dict):
        """"""
        data = packet["params"]["data"]

        symbol = data["instrument_name"]
        bids = data["bids"]
        asks = data["asks"]

        tick = self.ticks[symbol]
        for i in range(5):
            ix = i + 1
            if len(bids) < ix or len(asks) < ix:
                continue
            bp, bv = bids[i]
            ap, av = asks[i]

            setattr(tick, f"bid_price_{ix}", bp)
            setattr(tick, f"bid_volume_{ix}", bv)
            setattr(tick, f"ask_price_{ix}", ap)
            setattr(tick, f"ask_volume_{ix}", av)

        self.gateway.on_tick(copy(tick))

    def send_request(
        self,
        method: str,
        params: dict,
        callback: Callable = None
    ):
        """"""
        self.reqid += 1

        msg = {
            "jsonrpc": "2.0",
            "id": self.reqid,
            "method": method,
            "params": params
        }

        self.send_packet(msg)

        if callback:
            self.reqid_callback_map[self.reqid] = callback

        if "currency" in params:
            self.reqid_currency_map[self.reqid] = params["currency"]

        return self.reqid
