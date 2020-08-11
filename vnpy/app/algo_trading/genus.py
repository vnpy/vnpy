from datetime import datetime, timedelta
from typing import Any, Dict
from dataclasses import dataclass
import pytz

import quickfix as fix

from vnpy.event import EventEngine, Event
from vnpy.trader.event import EVENT_TRADE, EVENT_ORDER
from vnpy.trader.engine import MainEngine
from vnpy.trader.constant import Exchange, OrderType, Direction, Status, Offset
from vnpy.trader.utility import extract_vt_symbol, generate_vt_symbol
from vnpy.trader.object import OrderRequest, OrderData, TradeData, LogData
from vnpy.trader.setting import SETTINGS

from .base import (
    EVENT_ALGO_PARAMETERS, EVENT_ALGO_VARIABLES, EVENT_ALGO_LOG, APP_NAME
)


CHINA_TZ = pytz.timezone("Asia/Shanghai")

EXCHANGE_VT2GNS = {
    Exchange.SSE: "SS",
    Exchange.SZSE: "SZ",
    Exchange.CFFEX: "CF",
    Exchange.SHFE: "SSC",
    Exchange.DCE: "DLC",
    Exchange.CZCE: "ZZC"
}
EXCHANGE_GNS2VT = {v: k for k, v in EXCHANGE_VT2GNS.items()}

ORDERTYPE_VT2GNS = {
    OrderType.MARKET: "1",
    OrderType.LIMIT: "2"
}
ORDERTYPE_GNS2VT = {v: k for k, v in ORDERTYPE_VT2GNS.items()}

DIRECTION_VT2GNS = {
    Direction.LONG: "1",
    Direction.SHORT: "2"
}
DIRECTION_GNS2VT = {v: k for k, v in DIRECTION_VT2GNS.items()}

STATUS_GNS2VT = {
    "0": Status.NOTTRADED,
    "1": Status.PARTTRADED,
    "2": Status.ALLTRADED,
    "4": Status.CANCELLED,
    "5": Status.CANCELLED,
    "6": Status.SUBMITTING,
    "8": Status.REJECTED,
    "A": Status.SUBMITTING,
    "C": Status.CANCELLED,
    "D": Status.NOTTRADED,
    "E": Status.SUBMITTING,
}
STATUS_VT2GNS = {
    Status.SUBMITTING: "A",
    Status.NOTTRADED: "0",
    Status.PARTTRADED: "1",
    Status.ALLTRADED: "2",
    Status.REJECTED: "8",
    Status.CANCELLED: "4",
}


@dataclass
class GenusChildOrder:

    cl_ord_id: str = ""
    order_id: str = ""
    symbol: str = ""
    side: str = ""
    price: float = 0.0
    order_type: str = ""
    ord_status: str = ""
    order_qty: int = 0
    cum_qty: int = 0
    avg_px: float = 0

    parent_orderid: str = ""


class GenusParentApp(fix.Application):

    def __init__(self, client: "GenusClient"):
        """"""
        super().__init__()

        self.client: "GenusClient" = client

        self.callbacks: Dict[int, callable] = {
            fix.MsgType_ExecutionReport: self.on_parent_order
        }

        self.session_id: int = 0
        self.parent_orderid: int = int(datetime.now().strftime("%H%M%S0000"))

        self.algo_settings = {}

    def onCreate(self, session_id: int):
        """"""
        self.session_id = session_id

        self.client.write_log("金纳算法交易服务：母单FIX APP创建成功")

    def onLogon(self, session_id: int):
        """"""
        self.client.write_log("金纳算法交易服务：母单FIX APP连接成功")

    def onLogout(self, session_id: int):
        """"""
        self.client.write_log("金纳算法交易服务：母单FIX APP连接断开")

    def toAdmin(self, message: fix.Message, session_id: int):
        """"""
        pass

    def toApp(self, message: fix.Message, session_id: int):
        """"""
        pass

    def fromAdmin(self, message: fix.Message, session_id: int):
        """"""
        pass

    def fromApp(self, message: fix.Message, session_id: int):
        """"""
        header = message.getHeader()

        msg_type = get_field_value(header, fix.MsgType())
        callback = self.callbacks.get(msg_type, None)
        if callback:
            callback(message)

    def on_parent_order(self, message: fix.Message):
        """"""
        parent_orderid = get_field_value(message, fix.ClOrdID())

        # Get parent orderid of cancel request
        if parent_orderid.startswith("Cancel"):
            parent_orderid = get_field_value(message, fix.OrigClOrdID())

        # If this parent order is from previous session
        if parent_orderid not in self.algo_settings:
            # Cancel it to avoid future update
            self.cancel_parent_order(parent_orderid)
            return

        tradeid = get_field_value(message, fix.ExecID())
        status = get_field_value(message, fix.OrdStatus())
        side = get_field_value(message, fix.Side())
        genus_symbol = get_field_value(message, fix.Symbol())
        order_traded = get_field_value(message, fix.CumQty())

        text = get_field_value(message, fix.Text())
        algo_type = get_field_value(message, fix.StringField(847))

        variables = {
            "推送编号": tradeid,
            "已成交": order_traded,
            "算法信息": text
        }

        self.algo_settings[parent_orderid] = {
            "symbol": genus_symbol,
            "side": side,
            "algo_type": algo_type
        }

        # Add algo active status
        if status in {"0", "1", "5", "6", "A", "D", "E"}:
            variables["active"] = True
        else:
            variables["active"] = False

        if status == "C":
            self.client.write_log("执行时间已结束，停止算法", parent_orderid)

        self.client.put_variables_event(parent_orderid, variables)

    def send_parent_order(self, setting: dict):
        """"""
        vt_symbol = setting["vt_symbol"]
        volume = setting["volume"]
        price = setting["price"]
        order_type = OrderType(setting["order_type"])
        direction = Direction(setting["direction"])
        offset = Offset(setting["offset"])
        template_name = setting["template_name"]
        algo_type = template_name.replace("Genus", "")

        message = new_message(fix.MsgType_NewOrderSingle)

        symbol, exchange = extract_vt_symbol(vt_symbol)
        genus_exchange = EXCHANGE_VT2GNS[exchange]
        genus_symbol = f"{symbol}.{genus_exchange}"

        side = DIRECTION_VT2GNS[direction]
        genus_type = ORDERTYPE_VT2GNS[order_type]

        self.parent_orderid += 1
        parent_orderid = f"{template_name}_{self.parent_orderid}"
        message.setField(fix.ClOrdID(parent_orderid))

        message.setField(fix.HandlInst("2"))
        message.setField(fix.Currency("CNY"))

        message.setField(fix.ExDestination(genus_exchange))
        message.setField(fix.Symbol(genus_symbol))
        message.setField(fix.Side(side))
        message.setField(fix.OrdType(genus_type))
        message.setField(fix.OrderQty(volume))
        message.setField(526, parent_orderid)
        message.setField(fix.Text("vnpy"))

        if order_type == OrderType.LIMIT:
            message.setField(fix.Price(price))

        seconds = setting["time"]
        dt = datetime.now() + timedelta(seconds=seconds)
        local_dt = CHINA_TZ.localize(dt)
        utc_dt = local_dt.astimezone(pytz.utc)
        utc_end = utc_dt.strftime("%Y%m%d-%H:%M:%S")

        parameters = f"EndTime;{utc_end}"

        message.setField(847, algo_type)
        message.setField(848, parameters)

        fix.Session.sendToTarget(message, self.session_id)

        self.algo_settings[parent_orderid] = {
            "symbol": genus_symbol,
            "side": side,
            "algo_type": algo_type
        }

        self.client.set_parent_offset(parent_orderid, offset)
        self.client.put_parameters_event(parent_orderid, setting)

        return parent_orderid

    def cancel_parent_order(self, parent_orderid: str):
        """"""
        algo_setting = self.algo_settings.get(parent_orderid, None)
        if not algo_setting:
            print(f"{parent_orderid} algo setting not found.")
            return

        message = new_message(fix.MsgType_OrderCancelRequest)

        self.parent_orderid += 1
        cancel_orderid = f"Cancel_{self.parent_orderid}"
        message.setField(fix.ClOrdID(cancel_orderid))
        message.setField(fix.OrigClOrdID(parent_orderid))
        message.setField(fix.Symbol(algo_setting["symbol"]))
        message.setField(fix.Side(algo_setting["side"]))
        message.setField(847, algo_setting["algo_type"])
        message.setField(fix.Text("vnpy"))

        fix.Session.sendToTarget(message, self.session_id)


class GenusChildApp(fix.Application):

    def __init__(self, client: "GenusClient"):
        """"""
        super().__init__()

        self.client: "GenusClient" = client

        self.callbacks: Dict[int, callable] = {
            fix.MsgType_NewOrderSingle: self.new_child_order,
            fix.MsgType_OrderCancelRequest: self.cancel_child_order,
        }

        self.session_id: int = 0
        self.exec_id: int = int(datetime.now().strftime("%H%M%S0000"))

        self.child_orders: Dict[str, GenusChildOrder] = {}
        self.genus_vt_map: Dict[str, str] = {}

    def onCreate(self, session_id: int):
        """"""
        self.session_id = session_id

        self.client.write_log("金纳算法交易服务：子单FIX APP创建成功")

    def onLogon(self, session_id: int):
        """"""
        self.client.write_log("金纳算法交易服务：子单FIX APP连接成功")

    def onLogout(self, session_id: int):
        """"""
        self.client.write_log("金纳算法交易服务：子单FIX APP连接断开")

    def toAdmin(self, message: fix.Message, session_id: int):
        """"""
        pass

    def toApp(self, message: fix.Message, session_id: int):
        """"""
        pass

    def fromAdmin(self, message: fix.Message, session_id: int):
        """"""
        header = message.getHeader()
        msg_type = get_field_value(header, fix.MsgType())

        if msg_type == fix.MsgType_Logon:
            self.update_seq_num(message)

    def fromApp(self, message: fix.Message, session_id: int):
        """"""
        header = message.getHeader()
        msg_type = get_field_value(header, fix.MsgType())

        callback = self.callbacks.get(msg_type, None)
        if callback:
            callback(message)

    def update_seq_num(self, message: fix.Message):
        """"""
        seq_num: int = get_field_value(message.getHeader(), fix.MsgSeqNum())
        session: fix.Session = fix.Session.lookupSession(self.session_id)
        session.setNextSenderMsgSeqNum(seq_num + 1)

    def new_child_order(self, message: fix.Message):
        """"""
        child_order = GenusChildOrder(
            cl_ord_id=get_field_value(message, fix.ClOrdID()),
            symbol=get_field_value(message, fix.Symbol()),
            side=get_field_value(message, fix.Side()),
            order_qty=get_field_value(message, fix.OrderQty()),
            price=get_field_value(message, fix.Price()),
            order_type=get_field_value(message, fix.OrdType()),
            ord_status="A",
            parent_orderid=get_field_value(message, fix.StringField(526))
        )

        # If parent offset not exist, then this child order should be ignored
        offset = self.client.get_parent_offset(child_order.parent_orderid)
        if not offset:
            return

        symbol, genus_exchange = child_order.symbol.split(".")
        exchange = EXCHANGE_GNS2VT[genus_exchange]
        direction = DIRECTION_GNS2VT[child_order.side]
        order_type = ORDERTYPE_GNS2VT[child_order.order_type]

        vt_symbol = generate_vt_symbol(symbol, exchange)

        child_order.order_id = self.client.send_order(
            vt_symbol,
            direction,
            offset,
            order_type,
            child_order.price,
            child_order.order_qty,
        )
        self.child_orders[child_order.order_id] = child_order
        self.genus_vt_map[child_order.cl_ord_id] = child_order.order_id

        msg = f"委托{direction.value}{vt_symbol}：{child_order.order_qty}@{child_order.price}"
        self.client.write_log(msg, algo_name=child_order.parent_orderid)

    def cancel_child_order(self, message: fix.Message):
        """"""
        cl_ord_id = get_field_value(message, fix.OrigClOrdID())

        vt_orderid = self.genus_vt_map.get(cl_ord_id, "")
        if vt_orderid:
            child_order = self.child_orders[vt_orderid]

            if child_order.ord_status not in {"2", "8", "4"}:
                self.client.cancel_order(vt_orderid)
                return

        # Reject cancel request
        self.exec_id += 1

        message = new_message(fix.MsgType_OrderCancelReject)
        message.setField(fix.ClOrdID(cl_ord_id))
        message.setField(fix.OrigClOrdID(cl_ord_id))
        message.setField(fix.OrdStatus("8"))
        message.setField(fix.ExecID(str(self.exec_id)))
        message.setField(434, "1")

        fix.Session.sendToTarget(message, self.session_id)

    def report_child_order(self, child_order: GenusChildOrder, trade: TradeData = None):
        """"""
        self.exec_id += 1

        message = new_message(fix.MsgType_ExecutionReport)

        message.setField(fix.ClOrdID(child_order.cl_ord_id))
        message.setField(fix.OrderID(child_order.order_id))
        message.setField(fix.ExecID(str(self.exec_id)))
        message.setField(fix.OrdStatus(child_order.ord_status))
        message.setField(fix.ExecType(child_order.ord_status))
        message.setField(fix.Symbol(child_order.symbol))
        message.setField(fix.Side(child_order.side))
        message.setField(fix.OrderQty(child_order.order_qty))

        message.setField(fix.CumQty(child_order.cum_qty))
        message.setField(fix.LeavesQty(child_order.order_qty - child_order.cum_qty))
        message.setField(fix.AvgPx(child_order.avg_px))

        if trade:
            message.setField(fix.LastShares(trade.volume))
            message.setField(fix.LastPx(trade.price))

        fix.Session.sendToTarget(message, self.session_id)

    def update_order(self, order: OrderData):
        """"""
        child_order = self.child_orders.get(order.vt_orderid, None)
        if not child_order:
            return

        child_order.ord_status = STATUS_VT2GNS[order.status]

        if order.status in {
            Status.SUBMITTING, Status.NOTTRADED, Status.CANCELLED, Status.REJECTED
        }:
            self.report_child_order(child_order)

    def update_trade(self, trade: OrderData):
        """"""
        child_order = self.child_orders.get(trade.vt_orderid, None)
        if not child_order:
            return

        old_cost = child_order.cum_qty * child_order.avg_px
        new_cost = old_cost + trade.volume * trade.price

        child_order.cum_qty += trade.volume
        child_order.avg_px = new_cost / child_order.cum_qty

        self.report_child_order(child_order, trade)


class GenusClient:

    def __init__(self, main_engine: MainEngine, event_engine: EventEngine):
        """"""
        self.main_engine: MainEngine = main_engine
        self.event_engine: EventEngine = event_engine

        self.parent_offset_map: Dict[str, Offset] = {}

        self.parent_socket: fix.SocketInitiator = None
        self.child_socket: fix.SocketAcceptor = None

    def start(self):
        """"""
        self.register_event()

        # For child app
        child_settings = fix.SessionSettings()
        child_dict = fix.Dictionary()

        child_dict.setString("ConnectionType", "acceptor")
        child_dict.setString("ResetOnLogon", "Y")
        child_dict.setString("FileLogPath", "./genus_log/child")
        child_dict.setString("LogonTimeout", "30")
        child_dict.setString("StartTime", "00:00:00")
        child_dict.setString("EndTime", "00:00:00")
        child_dict.setString("HeartBtInt", "30")
        child_dict.setString("CheckLatency", "N")
        child_dict.setString("UseDataDictionary", "N")
        child_dict.setString("FileStorePath", "./genus_store/child")
        child_dict.setString("ScreenLogShowIncoming", "N")
        child_dict.setString("ScreenLogShowOutgoing", "N")
        child_dict.setString("ScreenLogShowEvents", "N")

        child_dict.setString("SocketAcceptHost", SETTINGS["genus.child_host"])
        child_dict.setString("SocketAcceptPort", SETTINGS["genus.child_port"])

        child_session = fix.SessionID(
            "FIX.4.2",
            SETTINGS["genus.child_sender"],
            SETTINGS["genus.child_target"]
        )
        child_settings.set(child_session, child_dict)

        child_store_factory = fix.FileStoreFactory(child_settings)
        child_log_factory = fix.ScreenLogFactory(child_settings)

        self.child_app: GenusChildApp = GenusChildApp(self)
        self.child_socket = fix.SocketAcceptor(
            self.child_app,
            child_store_factory,
            child_settings,
            child_log_factory
        )
        self.child_socket.start()

        # For parent app
        parent_settings = fix.SessionSettings()
        parent_dict = fix.Dictionary()

        parent_dict.setString("ConnectionType", "initiator")
        parent_dict.setString("ResetOnLogon", "Y")
        parent_dict.setString("FileLogPath", "./genus_log/parent")
        parent_dict.setString("LogonTimeout", "30")
        parent_dict.setString("StartTime", "00:00:00")
        parent_dict.setString("EndTime", "00:00:00")
        parent_dict.setString("HeartBtInt", "30")
        parent_dict.setString("CheckLatency", "N")
        parent_dict.setString("UseDataDictionary", "N")
        parent_dict.setString("FileStorePath", "./genus_store/parent")
        parent_dict.setString("ScreenLogShowIncoming", "N")
        parent_dict.setString("ScreenLogShowOutgoing", "N")
        parent_dict.setString("ScreenLogShowEvents", "N")

        parent_dict.setString("SocketConnectHost", SETTINGS["genus.parent_host"])
        parent_dict.setString("SocketConnectPort", SETTINGS["genus.parent_port"])

        parent_session = fix.SessionID(
            "FIX.4.2",
            SETTINGS["genus.parent_sender"],
            SETTINGS["genus.parent_target"]
        )
        parent_settings.set(parent_session, parent_dict)

        parent_store_factory = fix.FileStoreFactory(parent_settings)
        parent_log_factory = fix.ScreenLogFactory(parent_settings)

        self.parent_app: GenusParentApp = GenusParentApp(self)
        self.parent_socket = fix.SocketInitiator(
            self.parent_app,
            parent_store_factory,
            parent_settings,
            parent_log_factory
        )
        self.parent_socket.start()

    def register_event(self):
        """"""
        self.event_engine.register(EVENT_ORDER, self.process_order_event)
        self.event_engine.register(EVENT_TRADE, self.process_trade_event)

    def close(self):
        """"""
        if self.parent_socket:
            self.parent_socket.stop()

        if self.child_socket:
            self.child_socket.stop()

    def send_order(
        self,
        vt_symbol: str,
        direction: Direction,
        offset: Offset,
        order_type: OrderType,
        price: float,
        volume: float,
    ):
        """"""
        contract = self.main_engine.get_contract(vt_symbol)
        if not contract:
            return ""

        req = OrderRequest(
            symbol=contract.symbol,
            exchange=contract.exchange,
            direction=direction,
            offset=offset,
            type=order_type,
            volume=volume,
            price=price
        )
        vt_orderid = self.main_engine.send_order(req, contract.gateway_name)
        return vt_orderid

    def cancel_order(self, vt_orderid: str):
        """"""
        order = self.main_engine.get_order(vt_orderid)
        req = order.create_cancel_request()
        self.main_engine.cancel_order(req, order.gateway_name)

    def process_trade_event(self, event: Event):
        """"""
        trade = event.data
        self.child_app.update_trade(trade)

    def process_order_event(self, event: Event):
        """"""
        order = event.data
        self.child_app.update_order(order)

    def start_algo(self, setting: dict):
        """"""
        self.parent_app.send_parent_order(setting)

    def stop_algo(self, algo_name: str):
        """"""
        self.parent_app.cancel_parent_order(algo_name)

    def put_parameters_event(self, algo_name: str, parameters: dict):
        """"""
        event = Event(EVENT_ALGO_PARAMETERS)
        event.data = {
            "algo_name": algo_name,
            "parameters": parameters
        }
        self.event_engine.put(event)

    def put_variables_event(self, algo_name: str, variables: dict):
        """"""
        event = Event(EVENT_ALGO_VARIABLES)
        event.data = {
            "algo_name": algo_name,
            "variables": variables
        }
        self.event_engine.put(event)

    def write_log(self, msg: str, algo_name: str = ""):
        """"""
        if algo_name:
            msg = f"{algo_name}：{msg}"

        log = LogData(msg=msg, gateway_name=APP_NAME)
        event = Event(EVENT_ALGO_LOG, data=log)
        self.event_engine.put(event)

    def set_parent_offset(self, parent_orderid: str, offset: Offset):
        """"""
        self.parent_offset_map[parent_orderid] = offset

    def get_parent_offset(self, parent_orderid: str) -> Offset:
        """"""
        return self.parent_offset_map.get(parent_orderid, None)


def new_message(msg_type: int) -> fix.Message:
    """"""
    message = fix.Message()

    header = message.getHeader()
    header.setField(fix.BeginString("FIX.4.2"))
    header.setField(fix.MsgType(msg_type))

    utc_now = datetime.utcnow()
    utc_timestamp = utc_now.strftime("%Y%m%d-%H:%M:%S")
    message.setField(60, utc_timestamp)

    return message


def get_field_value(field_map: fix.FieldMap, field: Any) -> Any:
    """"""
    field_map.getField(field)
    return field.getValue()


class GenusAlgo:
    """"""

    display_name = "金纳算法"

    default_setting = {
        "vt_symbol": "",
        "order_type": [OrderType.LIMIT.value, OrderType.MARKET.value],
        "direction": [Direction.LONG.value, Direction.SHORT.value],
        "price": 0.0,
        "volume": 0,
        "time": 60,
        "offset": [
            Offset.NONE.value,
            Offset.OPEN.value,
            Offset.CLOSE.value,
            Offset.CLOSETODAY.value,
            Offset.CLOSEYESTERDAY.value
        ]
    }


class GenusVWAP(GenusAlgo):
    display_name = "金纳 VWAP"


class GenusTWAP(GenusAlgo):
    display_name = "金纳 TWAP"


class GenusPercent(GenusAlgo):
    display_name = "金纳 Percent"


class GenusPxInline(GenusAlgo):
    display_name = "金纳 PxInline"


class GenusSniper(GenusAlgo):
    display_name = "金纳 Sniper"


class GenusDMA(GenusAlgo):
    display_name = "金纳 DMA"
