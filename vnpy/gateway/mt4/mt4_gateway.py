import threading
from datetime import datetime
from typing import Any, Callable, Dict, Tuple, Set, List
import pytz
from time import time
from collections import defaultdict

import zmq
import zmq.auth
from zmq.backend.cython.constants import NOBLOCK


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
)


FUNCTION_QUERYCONTRACT = 0
FUNCTION_SUBSCRIBE = 1
FUNCTION_SENDORDER = 2
FUNCTION_CANCELORDER = 3
FUNCTION_MODIFYORDER = 4

TYPE_BUY = 0
TYPE_SELL = 1
TYPE_BUY_LIMIT = 2
TYPE_SELL_LIMIT = 3
TYPE_BUY_STOP = 4
TYPE_SELL_STOP = 5

DIRECTION_MT2VT = {
    TYPE_BUY: Direction.LONG,
    TYPE_SELL: Direction.SHORT
}

ORDERTYPE_MT2VT = {
    TYPE_BUY_LIMIT: (Direction.LONG, OrderType.LIMIT),
    TYPE_SELL_LIMIT: (Direction.SHORT, OrderType.LIMIT),
    TYPE_BUY_STOP: (Direction.LONG, OrderType.STOP),
    TYPE_SELL_STOP: (Direction.SHORT, OrderType.STOP),
}
ORDERTYPE_VT2MT = {v: k for k, v in ORDERTYPE_MT2VT.items()}

CHINA_TZ = pytz.timezone("Asia/Shanghai")


class Mt4Gateway(BaseGateway):
    """
    VN Trader Gateway for MT4.
    """

    default_setting = {
        "通讯地址": "localhost",
        "请求端口": "8888",
        "订阅端口": "6666",
    }

    exchanges = [Exchange.OTC]

    def __init__(self, event_engine):
        """Constructor"""
        super().__init__(event_engine, "MT4")

        self.callbacks: Dict[str, Callable] = {
            "order": self.on_order_info,
            "account": self.on_account_info,
            "price": self.on_price_info,
        }

        self.client = Mt4Client(self)

        self.active_orders: Dict[str, OrderData] = {}
        self.opened_order_info: List[Dict] = []

        self.orderid_closeid_map: Dict[str, str] = {}
        self.orderid_close_counts: Dict[str, int] = defaultdict(int)

    def connect(self, setting: dict):
        """"""
        address = setting["通讯地址"]
        req_port = setting["请求端口"]
        sub_port = setting["订阅端口"]

        req_address = f"tcp://{address}:{req_port}"
        sub_address = f"tcp://{address}:{sub_port}"

        self.client.start(req_address, sub_address)

        self.query_contract()

    def subscribe(self, req: SubscribeRequest) -> None:
        """"""
        mt4_req = {
            "type": FUNCTION_SUBSCRIBE,
            "symbol": req.symbol
        }
        self.client.send_request(mt4_req)

    def send_order(self, req: OrderRequest) -> str:
        """"""
        if req.offset == Offset.CLOSE:
            return self.modify_order(req)

        cmd = ORDERTYPE_VT2MT.get((req.direction, req.type), None)
        if not cmd:
            self.write_log(f"不支持的委托类型：{req.type.value}")
            return ""

        mt4_req = {
            "type": FUNCTION_SENDORDER,
            "symbol": req.symbol,
            "cmd": cmd,
            "price": req.price,
            "volume": req.volume,
            "magic": 0,
            "comment": req.reference,

        }

        packet = self.client.send_request(mt4_req)
        self.write_log(str(packet))

        orderid = str(packet["data"]["ticket"])
        order = req.create_order_data(orderid, self.gateway_name)
        order.status = Status.NOTTRADED
        self.active_orders[orderid] = order
        self.on_order(order)

        return orderid

    def cancel_order(self, req: CancelRequest) -> None:
        """"""
        if "close" in req.orderid:
            ticket = int(req.orderid.split("_")[1])
            mt4_req = {
                "type": FUNCTION_MODIFYORDER,
                "ticket": ticket,
                "price": 0,
                "take_profit": 0,
                "expiration": "1970.01.01 00:00",
            }
            mt4_rep = self.client.send_request(mt4_req)
            self.write_log(str(mt4_rep))

            closeid = self.orderid_closeid_map.pop(str(ticket))
            order = self.active_orders.pop(closeid)
            order.status = Status.CANCELLED
            self.on_order(order)
        else:
            mt4_req = {
                "type": FUNCTION_CANCELORDER,
                "ticket": int(req.orderid)
            }

            mt4_rep = self.client.send_request(mt4_req)
            self.write_log(str(mt4_rep))

    def modify_order(self, req: OrderRequest) -> str:
        """"""
        target = None
        for d in self.opened_order_info:
            if d["take_profit"]:
                continue

            if req.symbol != d["symbol"]:
                continue

            if req.volume != d["lots"]:
                continue

            if req.direction == Direction.LONG and d["type"] == TYPE_BUY:
                continue

            if req.direction == Direction.SHORT and d["type"] == TYPE_SELL:
                continue

            target = d
            break

        if target is None:
            self.write_log("平仓委托失败，找不到匹配的可平仓位")
            return ""

        mt4_req = {
            "type": FUNCTION_MODIFYORDER,
            "ticket": target["ticket"],
            "price": 0,
            "take_profit": req.price,
            "expiration": "1970.01.01 00:00",
        }

        packet = self.client.send_request(mt4_req)
        self.write_log(str(packet))

        orderid = str(d['ticket'])
        closeid = self.new_closeid(orderid)
        self.orderid_closeid_map[orderid] = closeid

        order = req.create_order_data(closeid, self.gateway_name)
        order.status = Status.NOTTRADED

        self.active_orders[closeid] = order
        self.on_order(order)

        return closeid

    def query_contract(self) -> None:
        """"""
        mt4_req = {"type": FUNCTION_QUERYCONTRACT}
        mt4_rep: dict = self.client.send_request(mt4_req)

        if mt4_rep:
            self.write_log("MT4连接成功")

        for d in mt4_rep["data"]:
            contract = ContractData(
                symbol=d["symbol"],
                exchange=Exchange.OTC,
                name=d["symbol"],
                product=Product.FOREX,
                size=d["lot_size"],
                pricetick=pow(10, -d["digits"]),
                min_volume=d["min_lot"],
                gateway_name=self.gateway_name,
            )
            self.on_contract(contract)

        self.write_log("合约信息查询成功")

    def query_account(self) -> None:
        """"""
        pass

    def query_position(self) -> None:
        """"""
        pass

    def close(self) -> None:
        """"""
        self.client.stop()
        self.client.join()

    def callback(self, packet: dict) -> None:
        """"""
        type_ = packet["type"]
        callback_func = self.callbacks.get(type_, None)

        if callback_func:
            callback_func(packet)

    def on_account_info(self, packet: dict) -> None:
        """"""
        data = packet["data"]

        account = AccountData(
            accountid=data["name"],
            balance=data["balance"],
            frozen=data["margin"],
            gateway_name=self.gateway_name
        )
        self.on_account(account)

    def on_order_info(self, packet: dict) -> None:
        """"""
        if "data" not in packet:
            return

        positions: Dict[Tuple[str, Direction], PositionData] = {}
        active_orderids: Set[str] = set()
        self.opened_order_info.clear()

        for d in packet["data"]:
            symbol = d["symbol"]
            type_ = d["type"]
            orderid = str(d["ticket"])

            # Opened order
            if type_ in DIRECTION_MT2VT:
                self.opened_order_info.append(d)

                direction = DIRECTION_MT2VT[type_]
                key = (symbol, type_)

                position = positions.get(key, None)
                if not position:
                    position = PositionData(
                        symbol=symbol,
                        exchange=Exchange.OTC,
                        direction=direction,
                        gateway_name=self.gateway_name
                    )
                    positions[key] = position

                cost = position.price * position.volume
                cost += d["lots"] * d["open_price"]
                position.volume += d["lots"]
                position.price = cost / position.volume

                # check for order traded
                if orderid in self.active_orders:
                    order = self.active_orders.pop(orderid)
                    order.traded = order.volume
                    order.status = Status.ALLTRADED
                    self.on_order(order)

                    trade = TradeData(
                        symbol=order.symbol,
                        exchange=order.exchange,
                        orderid=order.orderid,
                        tradeid=order.orderid,
                        direction=order.direction,
                        offset=order.offset,
                        price=order.price,
                        volume=order.volume,
                        datetime=datetime.now(CHINA_TZ),
                        gateway_name=self.gateway_name
                    )

                    self.on_trade(trade)

                # check for close order
                if d["take_profit"]:
                    if orderid not in self.orderid_closeid_map:
                        closeid = self.new_closeid(orderid)
                        active_orderids.add(closeid)
                        self.orderid_closeid_map[orderid] = closeid

                        if type_ == TYPE_BUY:
                            close_direction = Direction.SHORT
                        else:
                            close_direction = Direction.LONG

                        order = OrderData(
                            symbol=symbol,
                            exchange=Exchange.OTC,
                            orderid=closeid,
                            direction=close_direction,
                            type=OrderType.LIMIT,
                            offset=Offset.CLOSE,
                            price=d["take_profit"],
                            volume=d["lots"],
                            status=Status.NOTTRADED,
                            datetime=generate_datetime(d["open_time"]),
                            gateway_name=self.gateway_name,
                        )
                        self.active_orders[closeid] = order
                        self.on_order(order)
                    else:
                        closeid = self.orderid_closeid_map[orderid]
                        active_orderids.add(closeid)
                else:
                    if orderid in self.orderid_closeid_map:
                        closeid = self.orderid_closeid_map.pop(orderid)
                        order = self.active_orders.pop(closeid)
                        order.status = Status.CANCELLED
                        self.on_order(order)

            # Pending order
            if type_ in ORDERTYPE_MT2VT:
                active_orderids.add(orderid)

                if orderid not in self.active_orders:
                    direction, order_type = ORDERTYPE_MT2VT[type_]

                    order = OrderData(
                        symbol=symbol,
                        exchange=Exchange.OTC,
                        orderid=str(d["ticket"]),
                        direction=direction,
                        type=order_type,
                        offset=Offset.OPEN,
                        price=d["open_price"],
                        volume=d["lots"],
                        status=Status.NOTTRADED,
                        datetime=generate_datetime(d["open_time"]),
                        gateway_name=self.gateway_name,
                    )
                    self.active_orders[order.orderid] = order

                    self.on_order(order)

        # Push position update
        for position in positions.values():
            self.on_position(position)

        # Check for order cancelled
        for order in list(self.active_orders.values()):
            if order.orderid not in active_orderids:
                if "close" in order.orderid:
                    order.status = Status.ALLTRADED
                    order.traded = order.volume

                    trade = TradeData(
                        symbol=order.symbol,
                        exchange=order.exchange,
                        orderid=order.orderid,
                        tradeid=order.orderid,
                        direction=order.direction,
                        offset=order.offset,
                        price=order.price,
                        volume=order.volume,
                        datetime=datetime.now(CHINA_TZ),
                        gateway_name=self.gateway_name
                    )
                    self.on_trade(trade)

                    self.on_order(order)
                    self.active_orders.pop(order.orderid)
                else:
                    order.status = Status.CANCELLED

                    self.on_order(order)
                    self.active_orders.pop(order.orderid)

    def new_closeid(self, orderid: str) -> str:
        """"""
        self.orderid_close_counts[orderid] += 1
        count = self.orderid_close_counts[orderid]
        closeid = f"close_{orderid}_{count}"
        return closeid

    def on_price_info(self, packet: dict) -> None:
        """"""
        if "data" not in packet:
            return

        for d in packet["data"]:
            dt = datetime.fromtimestamp(d["time"])

            tick = TickData(
                symbol=d["symbol"],
                exchange=Exchange.OTC,
                name=d["symbol"],
                high_price=d["high"],
                low_price=d["high"],
                bid_price_1=d["bid"],
                ask_price_1=d["ask"],
                datetime=dt,
                gateway_name=self.gateway_name
            )
            self.on_tick(tick)


class Mt4Client:
    """"""

    def __init__(self, gateway: Mt4Gateway):
        """Constructor"""
        self.gateway: Mt4Gateway = gateway

        self.context: zmq.Context = zmq.Context()
        self.socket_req: zmq.Socket = self.context.socket(zmq.REQ)
        self.socket_sub: zmq.Socket = self.context.socket(zmq.SUB)
        self.socket_sub.setsockopt_string(zmq.SUBSCRIBE, "")

        self.active: bool = False
        self.thread: threading.Thread = None
        self.lock: threading.Lock = threading.Lock()

    def start(self, req_address: str, sub_address: str) -> None:
        """
        Start RpcClient
        """
        if self.active:
            return

        # Connect zmq port
        self.socket_req.connect(req_address)
        self.socket_sub.connect(sub_address)

        # Start RpcClient status
        self.active = True

        # Start RpcClient thread
        self.thread = threading.Thread(target=self.run)
        self.thread.start()

    def stop(self) -> None:
        """
        Stop RpcClient
        """
        if not self.active:
            return
        self.active = False

    def join(self) -> None:
        """"""
        if self.thread and self.thread.is_alive():
            self.thread.join()
        self.thread = None

    def run(self) -> None:
        """
        Run RpcClient function
        """
        while self.active:
            if not self.socket_sub.poll(1000):
                continue

            data = self.socket_sub.recv_json(flags=NOBLOCK)
            self.callback(data)

        # Close socket
        self.socket_req.close()
        self.socket_sub.close()

    def callback(self, data: Dict) -> None:
        """
        Callable function
        """
        self.gateway.callback(data)

    def send_request(self, req: Dict) -> Dict:
        """"""
        if not self.active:
            return {}

        self.socket_req.send_json(req)
        data = self.socket_req.recv_json()
        return data


def generate_datetime(timestamp: str) -> datetime:
    """"""
    dt = datetime.strptime(timestamp, "%Y.%m.%d %H:%M")
    dt = dt.replace(tzinfo=CHINA_TZ)
    return dt
