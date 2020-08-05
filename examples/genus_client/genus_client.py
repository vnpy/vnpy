import time
import importlib

import quickfix as fix
from datetime import datetime, timedelta

from vnpy.trader.constant import (
    Exchange,
    Direction,
    OrderType,
)

hours = timedelta(hours=1)
mins = timedelta(minutes=1)

EXCHANGE_VT2GNS = {
    Exchange.SSE: "SS",
    Exchange.SZSE: "SZ",
    Exchange.CFFEX: "CF",
    Exchange.SHFE: "SSC",
    Exchange.DCE: "DLC",
    Exchange.CZCE: "ZZC"
}

ORDERTYPE_VT2GNS = {
    OrderType.MARKET: "1",
    OrderType.LIMIT: "2"
}

DIRECTIONCHILD_VT2GNS = {
    "BUY": "1",
    "SELL": "2"
}

ORDERTYPECHILD_VT2GNS = {
    "MARKET": "1",
    "LIMIT": "2"
}

DIRECTION_VT2GNS = {
    Direction.LONG: "1",
    Direction.SHORT: "2"
}

SECURITYTYPECHILD_VT2GNS = {
    "COMMON_STOCK": "CS"

}

EXETYPE_GNS2VT = {
    "0": "NEW",
    "1": "PARTIAL_FILL",
    "2": "FILL",
    "3": "DONE_FOR_DAY",
    "4": "CANCELED",
    "5": "REPLACE",
    "6": "PENDING_CANCEL",
    "7": "STOPPED",
    "8": "REJECTED",
    "X": "X"
}
EXETYPE_VT2GNS = {v: k for k, v in EXETYPE_GNS2VT.items()}


class FixAcceptor(fix.Application):

    orderid: int = 100000
    execid: int = 0
    session_id = ""
    tradeid = 0
    mather_child_id = {}
    Loaded = False

    structs = {}
    orders_ma = {}

    def set_orderid(self, orderid):
        self.orderid = orderid

    def load_struct(self):
        """加载Struct"""
        module_name = f"fix_dict"
        module = importlib.import_module(module_name)

        for name in dir(module):
            if "__" not in name:
                self.structs[name] = getattr(module, name)

        for k, v in self.structs.items():
            words = k.split("_")
            name = words[0]

    def onCreate(self, session_id):
        self.session_id = session_id
        if not self.Loaded:
            self.load_struct()
            self.Loaded = True

    def onLogon(self, session_id):
        pass

    def onLogout(self, session_id):
        pass

    def toAdmin(self, msg, session_id):
        username = fix.Username("username")
        mypass = fix.Password("password")
        mycompid = fix.TargetSubID("targetsubid")
        msg.setField(username)
        msg.setField(mypass)
        msg.setField(mycompid)

    def fromAdmin(self, msg, session_id):
        d = self.msg2dict(msg)
        if d["<35>MsgType"] != "HEARTBEAT":
            msg_type = d["<35>MsgType"]
            if msg_type != "LOGON":
                print("@@Callback", d)

    def fromApp(self, msg, session_id):
        d = self.msg2dict(msg)
        print("@@Received msg: ", d)

        msg_type = d["<35>MsgType"]
        if msg_type == "ORDER_SINGLE":
            self.send_report(d)

    def toApp(self, session_id, msg):
        d = self.msg2dict(msg)
        print("@@Sent the following msg: ", d)

    def new_orderid(self) -> str:
        self.orderid = self.orderid + 1
        return str(self.orderid)

    def generate_execid(self):
        self.execid = self.execid + 1
        return self.execid

    def on_report_ma(self, data):
        print("put data from mather chanel to child channel")
        orderid = data["<37>OrderID"]
        if not orderid.startswith("mo."):
            orderid = f"mo.{orderid}"
            self.orders_ma[orderid] = data

    def put_order(self, session_id, order):
        fix.Session.sendToTarget(order, session_id)

    def send_report_replenish(self, data_ma):
        line = data_ma["<58>Text"]
        orderid = line[line.index("mo.co"):line.index(")")]

        symbol = data_ma["<55>Symbol"]
        exchange = symbol.split(".")[-1]
        now_utc = datetime.utcnow()
        now_time = now_utc.strftime("%Y%m%d-%H:%M:%S")

        order = fix.Message()
        order.getHeader().setField(fix.StringField(8, "FIX.4.2"))
        order.setField(35, "8")
        order.setField(11, orderid)
        order.setField(100, exchange)
        order.setField(17, data_ma["<17>ExecID"])
        order.setField(55, symbol)
        order.setField(150, EXETYPE_VT2GNS[data_ma["<150>ExecType"]])
        order.setField(39, EXETYPE_VT2GNS[data_ma["<39>OrdStatus"]])
        order.setField(54, DIRECTIONCHILD_VT2GNS[data_ma["<54>Side"]])
        order.setField(38, data_ma["<38>OrderQty"])
        order.setField(44, data_ma["<44>Price"])
        order.setField(32, data_ma["<32>LastShares"])
        order.setField(31, data_ma["<31>LastPx"])
        order.setField(151, data_ma["<151>LeavesQty"])
        order.setField(14, data_ma["<14>CumQty"])
        order.setField(6, data_ma["<6>AvgPx"])
        order.setField(60, now_time)

        self.put_order(self.session_id, order)
        print("-------------send child report replenish----------------------")

    def send_report(self, data):
        orderid = data["<11>ClOrdID"]
        punto = "."
        orderid_ma = punto.join(orderid.split(".")[:-2])
        data_ma = self.orders_ma.get(orderid_ma)
        if not data_ma:
            print("Not Received report from mather channel, please try again")
            return

        symbol = data["<55>Symbol"]
        exchange = symbol.split(".")[-1]
        now_utc = datetime.utcnow()
        now_time = now_utc.strftime("%Y%m%d-%H:%M:%S")
        order = fix.Message()
        order.getHeader().setField(fix.StringField(8, "FIX.4.2"))
        order.setField(35, "8")
        order.setField(11, orderid)
        order.setField(100, exchange)
        order.setField(17, data_ma["<17>ExecID"])
        order.setField(55, symbol)
        order.setField(150, EXETYPE_VT2GNS[data_ma["<150>ExecType"]])
        order.setField(39, EXETYPE_VT2GNS[data_ma["<39>OrdStatus"]])
        order.setField(54, DIRECTIONCHILD_VT2GNS[data["<54>Side"]])
        order.setField(38, data["<38>OrderQty"])
        order.setField(44, data["<44>Price"])
        order.setField(32, data_ma["<32>LastShares"])
        order.setField(31, data_ma["<31>LastPx"])
        order.setField(151, data_ma["<151>LeavesQty"])
        order.setField(14, data_ma["<14>CumQty"])
        order.setField(6, data_ma["<6>AvgPx"])
        order.setField(60, now_time)

        self.put_order(self.session_id, order)
        print("-------------send child report----------------------")

    def msg2dict(self, msg) -> dict:
        d = {}
        msg_str = msg.toString()

        words = msg_str.split("\x01")
        words = [word for word in words if word != ""]
        if (
            len(words) == 1
            and words[0] == "FIX.4.2:VnpyUAT6->GenusVnpyMarket"
        ):
            return ""

        for word in words:
            k, v = word.split("=")
            number = f"no_{k}"
            field = self.structs.get(number, None)
            if not field:
                field = k
                new_name = f"<{k}>"
                value = v
                d[new_name] = value
            else:
                name = field["name"]
                new_name = f"<{k}>{name}"
                value = field.get(v, None)
                if not value:
                    value = v
                d[new_name] = value

        return d


class FixInitiator(fix.Application):

    orderid: int = 100000
    execid: int = 0
    session_id = ""
    tradeid = 0
    mather_child_id = {}
    Loaded = False
    acceptor = None

    structs = {}

    def set_orderid(self, orderid):
        self.orderid = orderid

    def load_struct(self):
        """加载Struct"""
        module_name = f"fix_dict"
        module = importlib.import_module(module_name)

        for name in dir(module):
            if "__" not in name:
                self.structs[name] = getattr(module, name)

        for k, v in self.structs.items():
            words = k.split("_")
            name = words[0]

    def onCreate(self, session_id):
        self.session_id = session_id
        if not self.Loaded:
            self.load_struct()
            self.Loaded = True

    def onLogon(self, session_id):
        pass

    def onLogout(self, session_id):
        pass

    def toAdmin(self, msg, session_id):
        username = fix.Username("username")
        mypass = fix.Password("password")
        mycompid = fix.TargetSubID("targetsubid")
        msg.setField(username)
        msg.setField(mypass)
        msg.setField(mycompid)

    def fromAdmin(self, msg, session_id):
        d = self.msg2dict(msg)
        if d["<35>MsgType"] != "HEARTBEAT":
            msg_type = d["<35>MsgType"]
            if msg_type != "LOGON":
                print("@@Callback", d)

    def toApp(self, session_id, msg):
        d = self.msg2dict(msg)
        print("@@Sent the following msg: ", d)

    def fromApp(self, msg, session_id):
        d = self.msg2dict(msg)
        print("@@Received msg: ", d)

        msg_type = d["<35>MsgType"]
        target = d["<56>TargetCompID"]
        if msg_type == "EXECUTION_REPORT" and d["<39>OrdStatus"] == "NEW":
            self.acceptor.on_report_ma(d)

            if target == "client06" and d.get("<58>Text"):
                if "No Ack for market new or cancel order" in d["<58>Text"]:
                    print("开始补单------------------------------------------")
                    self.acceptor.send_report_replenish(d)

            elif d.get("<58>Text"):
                text = d["<58>Text"]
                print(f"母单发送失败，原因：{text}")

    def new_orderid(self) -> str:
        self.orderid = self.orderid + 1
        return str(self.orderid)

    def generate_execid(self):
        self.execid = self.execid + 1
        return self.execid

    def put_order(self, session_id, order):
        print("@@Creating Order----------------")
        fix.Session.sendToTarget(order, session_id)

    def generate_order(
        self,
        symbol,
        exchange,
        order_type,
        direction,
        volume=None,
        price=None,
    ):
        now_utc = datetime.utcnow()
        end_utc = now_utc + hours
        start_utc = now_utc - mins
        start_time = start_utc.strftime("%Y%m%d-%H:%M:%S")
        end_time = end_utc.strftime("%Y%m%d-%H:%M:%S")
        now_time = now_utc.strftime("%Y%m%d-%H:%M:%S")
        order = fix.Message()

        # Header
        order.getHeader().setField(fix.StringField(8, "FIX.4.2"))
        order.getHeader().setField(fix.MsgType(fix.MsgType_NewOrderSingle))

        order.getHeader().setField(fix.Account("account"))
        order.getHeader().setField(fix.TargetSubID("targetsubid"))

        # Body
        gns_exchange = EXCHANGE_VT2GNS[exchange]
        gns_symbol = f"{symbol}.{gns_exchange}"
        orderid = self.new_orderid()
        order.setField(11, orderid)
        order.setField(21, "2")
        order.setField(100, gns_exchange)
        order.setField(55, gns_symbol)

        if volume:
            order.setField(38, str(volume))
        else:
            order.setField(152, str(price))

        order.setField(40, ORDERTYPE_VT2GNS[order_type])
        if order_type == OrderType.LIMIT:
            order.setField(44, str(price))

        order.setField(15, "CNY")
        order.setField(60, now_time)
        order.setField(847, "TWAP")
        msg = f"StartTime;{start_time}^EndTime;{end_time}"
        order.setField(848, msg)
        order.setField(fix.CharField(54, fix.Side_BUY))

        return order

    def cancel_order(self):
        now_utc = datetime.utcnow()
        now_time = now_utc.strftime("%Y%m%d-%H:%M:%S")
        localid = str(self.orderid)
        new_localid = self.new_orderid()
        child_id = self.mather_child_id[localid]
        symbol = "600570"
        volume = 1000
        price = 0

        order = fix.Message()
        order.setField(35, "F")
        order.setField(11, localid)
        order.setField(41, new_localid)
        order.setField(37, child_id)
        order.setField(55, symbol)
        order.setField(fix.CharField(54, fix.Side_BUY))

        if volume:
            order.setField(38, str(volume))
        else:
            order.setField(152, str(price))
        order.setField(60, now_time)
        order.setField(847, "TWAP")
        self.put_order(self.session_id, order)

    def send_order(self):
        order = self.generate_order(
            symbol="600519",
            exchange=Exchange.SSE,
            volume=1000,
            order_type=OrderType.MARKET,
            direction=Direction.LONG
        )
        self.put_order(self.session_id, order)

    def msg2dict(self, msg) -> dict:
        d = {}
        msg_str = msg.toString()

        words = msg_str.split("\x01")
        words = [word for word in words if word != ""]
        if (
            len(words) == 1
            and words[0] == "FIX.4.2:client06->GenusStgyUAT1"
        ):
            return ""

        for word in words:
            k, v = word.split("=")
            number = f"no_{k}"
            field = self.structs.get(number, None)
            if not field:
                field = k
                new_name = f"<{k}>"
                value = v
                d[new_name] = value
            else:
                name = field["name"]
                new_name = f"<{k}>{name}"
                value = field.get(v, None)
                if not value:
                    value = v
                d[new_name] = value

        return d


class GenusClient:
    fix_client = None
    initiator = None
    acceptor = None

    def __init__(self):
        self.fix_acc = FixAcceptor()
        self.fix_acc.set_orderid(1003)

        self.fix_init = FixInitiator()
        self.fix_init.set_orderid(1003)
        self.fix_init.acceptor = self.fix_acc

        self.initiator = self.create_initiator(self.fix_init)
        self.acceptor = self.create_acceptor(self.fix_acc)

    def create_initiator(self, fix_client):
        settings = fix.SessionSettings("genus_mather.cfg")
        store_factory = fix.FileStoreFactory(settings)
        log_factory = fix.ScreenLogFactory(settings)
        initiator = fix.SocketInitiator(
            fix_client, store_factory, settings, log_factory
        )
        initiator.start()
        print("Initiator 创建成功！")
        return initiator

    def create_acceptor(self, fix_client):
        settings = fix.SessionSettings("genus_child.cfg")
        store_factory = fix.FileStoreFactory(settings)
        log_factory = fix.ScreenLogFactory(settings)
        acceptor = fix.SocketAcceptor(
            fix_client, store_factory, settings, log_factory
        )
        acceptor.start()
        print("acceptor 创建成功！")
        return acceptor

    def send_order(self):
        self.fix_init.send_order()

    def cancel_order_ma(self):
        self.fix_init.cancel_order()


if __name__== "__main__":
    a = GenusClient()

    time.sleep(5)

    a.send_order()

    while True:
        time.sleep(3)
