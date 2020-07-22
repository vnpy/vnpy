import sys
import time
import quickfix as fix
from datetime import datetime, timedelta
from vnpy.trader.utility import get_file_path, get_folder_path
from vnpy.trader.object import (
    OrderRequest,
)
from vnpy.trader.constant import (
    Exchange,
    Product,
    Direction,
    OrderType,
    Status,
    Offset,
    OptionType
)

hours = timedelta(hours=1)
mins = timedelta(minutes=1)

p_setting = {
    "host": "123.56.88.75",
    "port": "11131",
    "sender": "client06",
    "target": "GenusStgyUAT1"
}

c_setting = {
    "host": "10.11.27.81",
    "port": "6668",
    "sender": "VnpyUAT6",
    "target": "GenusVnpyMarket"
}

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

DIRECTION_VT2GNS = {
    Direction.LONG: "1",
    Direction.SHORT: "2"
}


class FixClient(fix.Application):

    orderid: int = 1006
    execid: int = 0
    session_id = ""
    tradeid = 0

    def onCreate(self, session_id):
        pass

    def onLogon(self, session_id):
        print("Login success---------------------")
        self.session_id = session_id
        if self.session_id:
            print("Session ID 获取成功， id=", self.session_id)

    def onLogout(self, session_id):
        print("4-onLogout")

    def toAdmin(self, msg, session_id):
        username = fix.Username("username")
        mypass = fix.Password("password")
        mycompid = fix.TargetSubID("targetsubid")
        msg.setField(username)
        msg.setField(mypass)
        msg.setField(mycompid)

    def fromAdmin(self, msg, session_id):
        # print("1-On Front Connected")
        pass


    def toApp(self, session_id, msg):
        print("@@Sent the following msg: %s-------------" % msg.toString())
        return

    def fromApp(self, msg, session_id):
        print("@@Received msg: %s----------" % msg.toString())

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
        order.getHeader().setField(fix.MsgType(fix.MsgType_NewOrderSingle))  # MsgType

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

    def send_order(self):
        order = self.generate_order(
            symbol="600609",
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

        for word in words:
            k, v = word.split("=")
            d[k] = v

        return d


if __name__== '__main__':
    try:
        settings = fix.SessionSettings("genus.cfg")
        fix_client = FixClient()
        store_factory = fix.FileStoreFactory(settings)
        log_factory = fix.ScreenLogFactory(settings)
        initiator = fix.SocketInitiator(
            fix_client, store_factory, settings, log_factory
        )
        initiator.start()

        print("系统启动成功！--------------")

        # fix_client.send_order()

        while True:
            time.sleep(3)

    except (fix.ConfigError, fix.RuntimeError) as e:
        print(e)