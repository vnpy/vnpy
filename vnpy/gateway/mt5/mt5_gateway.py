import threading
from datetime import datetime
from typing import Callable, Dict, Set, List
from dataclasses import dataclass

import zmq
import zmq.auth
from zmq.backend.cython.constants import NOBLOCK
from tzlocal import get_localzone

from vnpy.trader.constant import (
    Direction,
    Exchange,
    OrderType,
    Product,
    Status,
    Interval
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
    HistoryRequest,
    BarData
)

PERIOD_M1 = 1
PERIOD_H1 = 12
PERIOD_D1 = 19

FUNCTION_QUERYCONTRACT = 0
FUNCTION_QUERYORDER = 1
FUNCTION_QUERYHISTORY = 2
FUNCTION_SUBSCRIBE = 3
FUNCTION_SENDORDER = 4
FUNCTION_CANCELORDER = 5

ORDER_STATE_PLACED = 1
ORDER_STATE_CANCELED = 2
ORDER_STATE_PARTIAL = 3
ORDER_STATE_FILLED = 4
ORDER_STATE_REJECTED = 5

EVENT_REQUEST = 10
EVENT_HISTORY_ADD = 6

POSITION_TYPE_BUY = 0
POSITION_TYPE_SELL = 1

TYPE_BUY = 0
TYPE_SELL = 1
TYPE_BUY_LIMIT = 2
TYPE_SELL_LIMIT = 3
TYPE_BUY_STOP = 4
TYPE_SELL_STOP = 5

INTERVAL_VT2MT = {
    Interval.MINUTE: PERIOD_M1,
    Interval.HOUR: PERIOD_H1,
    Interval.DAILY: PERIOD_D1,
}

STATUS_MT2VT = {
    0: Status.SUBMITTING,
    1: Status.NOTTRADED,
    2: Status.CANCELLED,
    3: Status.PARTTRADED,
    4: Status.ALLTRADED,
    5: Status.REJECTED
}

ORDERTYPE_MT2VT = {
    TYPE_BUY: (Direction.LONG, OrderType.MARKET),
    TYPE_SELL: (Direction.SHORT, OrderType.MARKET),
    TYPE_BUY_LIMIT: (Direction.LONG, OrderType.LIMIT),
    TYPE_SELL_LIMIT: (Direction.SHORT, OrderType.LIMIT),
    TYPE_BUY_STOP: (Direction.LONG, OrderType.STOP),
    TYPE_SELL_STOP: (Direction.SHORT, OrderType.STOP),
}
ORDERTYPE_VT2MT = {v: k for k, v in ORDERTYPE_MT2VT.items()}

LOCAL_TZ = get_localzone()


class Mt5Gateway(BaseGateway):
    """
    VN Trader Gateway for MT5.
    """

    default_setting: Dict[str, str] = {
        "通讯地址": "localhost",
        "请求端口": "6888",
        "订阅端口": "8666",
    }

    exchanges: List[Exchange] = [Exchange.OTC]

    def __init__(self, event_engine):
        """Constructor"""
        super().__init__(event_engine, "MT5")

        self.callbacks: Dict[str, Callable] = {
            "account": self.on_account_info,
            "price": self.on_price_info,
            "order": self.on_order_info,
            "position": self.on_position_info
        }

        self.client = Mt5Client(self)
        self.order_count = 0

        self.local_sys_map: Dict[str, str] = {}
        self.sys_local_map: Dict[str, str] = {}
        self.position_symbols: Set[str] = set()

        self.orders: Dict[str, OrderData] = {}
        self.market_trades: Dict[str, TradeData] = {}
        self.temp_orders: Dict[str, str] = {}

        self.sysid_order_map: Dict[str, OrderData] = {}

    def connect(self, setting: dict) -> None:
        """"""
        address = setting["通讯地址"]
        req_port = setting["请求端口"]
        sub_port = setting["订阅端口"]

        req_address = f"tcp://{address}:{req_port}"
        sub_address = f"tcp://{address}:{sub_port}"

        self.client.start(req_address, sub_address)

        self.query_contract()
        self.query_order()

    def subscribe(self, req: SubscribeRequest) -> None:
        """"""
        mt5_req = {
            "type": FUNCTION_SUBSCRIBE,
            "symbol": req.symbol
        }
        self.client.send_request(mt5_req)

    def send_order(self, req: OrderRequest) -> str:
        """"""
        cmd = ORDERTYPE_VT2MT.get((req.direction, req.type), None)

        if req.type == OrderType.FOK or req.type == OrderType.FAK or req.type == OrderType.RFQ:
            self.write_log(f"不支持的委托类型：{req.type.value}")
            return ""

        local_id = self.new_orderid()

        mt5_req = {
            "type": FUNCTION_SENDORDER,
            "symbol": req.symbol,
            "cmd": cmd,
            "price": req.price,
            "volume": req.volume,
            "comment": local_id,
        }

        packet = self.client.send_request(mt5_req)

        order = req.create_order_data(local_id, self.gateway_name)

        result = packet["data"]["result"]
        if result:
            order.status = Status.SUBMITTING
        else:
            order.status = Status.REJECTED
            self.write_log(f"委托{local_id}拒单，请检查委托价格或者委托数量！")

        self.on_order(order)
        self.orders[local_id] = order

        return order.vt_orderid

    def new_orderid(self) -> int:
        """"""
        prefix = datetime.now().strftime("%Y%m%d_%H%M%S_")

        self.order_count += 1
        suffix = str(self.order_count).rjust(4, "0")

        orderid = prefix + suffix
        return orderid

    def cancel_order(self, req: CancelRequest) -> None:
        """"""
        sys_id = self.local_sys_map[req.orderid]

        mt5_req = {
            "type": FUNCTION_CANCELORDER,
            "ticket": int(sys_id)
        }

        packet = self.client.send_request(mt5_req)
        result = packet["data"]["result"]

        if result is True:
            self.write_log(f"委托撤单成功{req.orderid}")
        elif result is False:
            self.write_log(f"委托撤单失败{req.orderid}")

    def query_contract(self) -> None:
        """"""
        mt5_req = {"type": FUNCTION_QUERYCONTRACT}
        packet = self.client.send_request(mt5_req)

        if packet:
            self.write_log("MT5连接成功")

        for d in packet["data"]:
            contract = ContractData(
                symbol=d["symbol"],
                exchange=Exchange.OTC,
                name=d["symbol"],
                product=Product.FOREX,
                size=d["lot_size"],
                pricetick=pow(10, -d["digits"]),
                min_volume=d["min_lot"],
                net_position=True,
                stop_supported=True,
                history_data=True,
                gateway_name=self.gateway_name,
            )
            self.on_contract(contract)

        self.write_log("合约信息查询成功")

    def query_order(self) -> None:
        """"""
        mt5_req = {"type": FUNCTION_QUERYORDER}
        packet = self.client.send_request(mt5_req)

        for d in packet.get("data", []):
            direction, order_type = ORDERTYPE_MT2VT[d["order_type"]]

            sys_id = str(d["order"])

            if d["order_comment"]:
                local_id = d["order_comment"]
            else:
                local_id = sys_id

            self.local_sys_map[local_id] = sys_id
            self.sys_local_map[sys_id] = local_id

            order = OrderData(
                symbol=d["symbol"],
                exchange=Exchange.OTC,
                orderid=local_id,
                direction=direction,
                type=order_type,
                price=d["order_price"],
                volume=d["order_volume_initial"],
                traded=d["order_volume_initial"] - d["order_volume_current"],
                status=STATUS_MT2VT.get(d["order_state"], Status.SUBMITTING),
                gateway_name=self.gateway_name
            )

            self.on_order(order)

        self.write_log("委托信息查询成功")

    def query_account(self) -> None:
        """"""
        pass

    def query_position(self) -> None:
        """"""
        pass

    def query_history(self, req: HistoryRequest) -> List[BarData]:
        """
        Query bar history data.
        """
        history = []

        start_time = req.start.isoformat()
        end_time = req.end.isoformat()

        mt5_req = {
            "type": FUNCTION_QUERYHISTORY,
            "symbol": req.symbol,
            "interval": INTERVAL_VT2MT[req.interval],
            "start_time": start_time,
            "end_time": end_time,
        }
        packet = self.client.send_request(mt5_req)

        if packet["result"] == -1:
            self.write_log("获取历史数据失败")
        else:
            for d in packet["data"]:
                bar = BarData(
                    symbol=req.symbol,
                    exchange=Exchange.OTC,
                    datetime=generate_datetime(d["time"]),
                    interval=req.interval,
                    volume=d["real_volume"],
                    open_price=d["open"],
                    high_price=d["high"],
                    low_price=d["low"],
                    close_price=d["close"],
                    gateway_name=self.gateway_name
                )
                history.append(bar)

            data = packet["data"]
            begin = data[0]["time"]
            end = data[-1]["time"]

            msg = f"获取历史数据成功，{req.symbol} - {req.interval.value}，{begin} - {end}"
            self.write_log(msg)

        return history

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

    def on_order_info(self, packet: dict) -> None:
        """"""
        print("on_order", packet)
        data = packet["data"]

        # Map sys and local orderid
        sys_id = str(data["order"])

        if data["comment"]:
            local_id = data["comment"]
        else:
            local_id = sys_id

        self.local_sys_map[local_id] = sys_id
        self.sys_local_map[sys_id] = local_id

        # Update order data
        order = self.orders.get(local_id, None)
        if not order:
            direction, order_type = ORDERTYPE_MT2VT[data["order_type"]]

            order = OrderData(
                symbol=data["symbol"],
                exchange=Exchange.OTC,
                orderid=local_id,
                type=order_type,
                direction=direction,
                price=data["order_price"],
                volume=data["order_volume"],
                gateway_name=self.gateway_name
            )
            self.orders[local_id] = order

        order.status = STATUS_MT2VT.get(data["order_state"], Status.SUBMITTING)
        order.traded = data["order_volume_initial"] - data["order_volume_current"]
        order.datetime = generate_datetime(data["order_time_setup"])
        self.on_order(order)

        # Update trade data
        if data["deal"]:
            trade = TradeData(
                symbol=order.symbol,
                exchange=order.exchange,
                direction=order.direction,
                price=data["deal_price"],
                volume=data["deal_volume"],
                datetime=generate_datetime(data["deal_time"]),
                gateway_name=self.gateway_name
            )
            self.on_trade(trade)

    # def on_order_info123(self, packet: dict) -> None:
    #     """"""
    #     print("on_order", packet)
    #     data = packet["data"]

    #     # Check Request Event
    #     if data["event_type"] == EVENT_REQUEST:
    #         if not data["magic"]:
    #             return
    #         local_id = str(data["magic"])
    #         sys_id = data["order_"]
    #         self.sys_local_map[sys_id] = local_id
    #         self.local_sys_map[local_id] = sys_id

    #         if sys_id in self.market_trades.keys():
    #             order = self.orders[local_id]
    #             trade = self.market_trades[sys_id]
    #             trade.direction = order.direction
    #             trade.orderid = order.orderid
    #             order.status = self.temp_orders[sys_id]
    #             order.traded = trade.volume
    #             self.on_order(order)
    #             self.on_trade(trade)
    #             del self.market_trades[sys_id]
    #             del self.temp_orders[sys_id]

    #         elif sys_id in self.temp_orders.keys():
    #             order = self.orders[local_id]
    #             order.status = self.temp_orders[sys_id]
    #             self.on_order(order)
    #             del self.temp_orders[sys_id]

    #     # Check TradeTransaction Event
    #     else:
    #         order_status = STATUS_MT2VT.get(data["order_state"], None)

    #         sys_id = data["order"]
    #         local_id = self.sys_local_map.get(sys_id, None)

    #         if local_id:
    #             # cheque order status
    #             order = self.orders[local_id]
    #             order.status = order_status
    #             self.on_order(order)

    #             # cheque trade_status
    #             if data["event_type"] == EVENT_HISTORY_ADD:
    #                 trade = TradeData(
    #                     symbol=data["symbol"],
    #                     exchange=Exchange.OTC,
    #                     tradeid=data["deal"],
    #                     orderid=order.orderid,
    #                     price=data["price"],
    #                     volume=data["volume"],
    #                     gateway_name=self.gateway_name,
    #                     direction=order.direction,
    #                     datetime=datetime.now()
    #                 )
    #                 if order.volume == trade.volume:
    #                     order.traded = trade.volume
    #                     order.status = Status.ALLTRADED
    #                 else:
    #                     order.traded = trade.volume
    #                     order.status = Status.PARTTRADED
    #                 self.on_order(order)
    #                 self.on_trade(trade)

    #         else:
    #             self.temp_orders[sys_id] = order_status

    #             if data["event_type"] == EVENT_HISTORY_ADD:
    #                 trade = TradeData(
    #                     symbol=data["symbol"],
    #                     exchange=Exchange.OTC,
    #                     tradeid=data["deal"],
    #                     orderid=data["order"],
    #                     price=data["price"],
    #                     volume=data["volume"],
    #                     gateway_name=self.gateway_name,
    #                     datetime=datetime.now()
    #                 )
    #                 self.market_trades[sys_id] = trade

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

    def on_position_info(self, packet: dict) -> None:
        """"""
        positions = {}

        data = packet.get("data", [])
        for d in data:
            position = PositionData(
                symbol=d["symbol"],
                exchange=Exchange.OTC,
                direction=Direction.NET,
                gateway_name=self.gateway_name
            )

            if d["type"] == POSITION_TYPE_BUY:
                position.volume = d["volume"]
            else:
                position.volume = -d["volume"]

            position.price = d["price"]
            position.pnl = d["current_profit"]

            positions[position.symbol] = position

        for symbol in self.position_symbols:
            if symbol not in positions:
                position = PositionData(
                    symbol=symbol,
                    exchange=Exchange.OTC,
                    direction=Direction.NET,
                    gateway_name=self.gateway_name
                )
                positions[symbol] = position

        for position in positions.values():
            self.position_symbols.add(position.symbol)
            self.on_position(position)

    def on_price_info(self, packet: dict) -> None:
        """"""
        if "data" not in packet:
            return

        for d in packet["data"]:

            tick = TickData(
                symbol=d["symbol"],
                exchange=Exchange.OTC,
                name=d["symbol"],
                bid_price_1=d["bid"],
                ask_price_1=d["ask"],
                volume=d["last_volume"],
                datetime=datetime.now(),
                gateway_name=self.gateway_name
            )
            if tick.last_price:
                tick.last_price = d["last"]
                tick.high_price = d["last_high"]
                tick.low_price = d["last_low"]
            else:
                tick.last_price = (d["bid"] + d["ask"]) / 2
                tick.high_price = (d["bid_high"] + d["ask_high"]) / 2
                tick.low_price = (d["bid_low"] + d["ask_low"]) / 2

            self.on_tick(tick)


class Mt5Client:
    """"""

    def __init__(self, gateway: Mt5Gateway):
        """Constructor"""
        self.gateway: Mt5Gateway = gateway

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
    dt = dt.replace(tzinfo=LOCAL_TZ)
    return dt


@dataclass
class OrderBuf:
    symbol: str
    type: OrderType = OrderType.LIMIT
    direction: Direction = None
    price: float = 0
    volume: float = 0
    traded: float = 0
    status: Status = Status.SUBMITTING
    datetime: datetime = None

    