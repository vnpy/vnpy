from datetime import datetime, timedelta
from typing import Any

import quickfix as fix

from vnpy.trader.constant import Exchange, OrderType, Direction, Status
from vnpy.trader.utility import extract_vt_symbol


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



class FixInitiator(fix.Application):

    def __init__(self):
        """"""
        super().__init__()

        now_timestamp = datetime.now().strftime("%H%M%S0000")
        self.algoid = int(now_timestamp)

        self.session_id = 0

        self.callbacks = {
            fix.MsgType_ExecutionReport: self.on_order
        }

        self.algo_settings = {}

    def onCreate(self, session_id: int):
        """"""
        self.session_id = session_id

    def onLogon(self, session_id: int):
        """"""
        print("on logon", session_id)

    def onLogout(self, session_id: int):
        """"""
        print("on logout", session_id)

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
        print("from app")
        header = message.getHeader()

        msg_type = fix.MsgType()
        header.getField(msg_type)

        callback = self.callbacks.get(msg_type.getValue(), None)
        if callback:
            callback(message)

    def on_order(self, message: fix.Message):
        """"""
        algoid = get_field_value(message, fix.ClOrdID())
        tradeid = get_field_value(message, fix.ExecID())
        orderid = get_field_value(message, fix.OrderID())

        status = get_field_value(message, fix.OrdStatus())
        side = get_field_value(message, fix.Side())
        genus_symbol = get_field_value(message, fix.Symbol())

        trade_volume = get_field_value(message, fix.LastShares())
        trade_price = get_field_value(message, fix.LastPx())

        order_traded = get_field_value(message, fix.CumQty())
        order_left = get_field_value(message, fix.LeavesQty())
        order_volume = order_traded + order_left

        text = get_field_value(message, fix.Text())
        algo_type = get_field_value(message, fix.StringField(847))

        d = {
            "algoid": algoid,
            "tradeid": tradeid,
            "orderid": orderid,
            "side": side,
            "algo_type": algo_type,
            "status": STATUS_GNS2VT[status],
            "genus_symbol": genus_symbol,
            "trade_volume": trade_volume,
            "trade_price": trade_price,
            "order_traded": order_traded,
            "order_left": order_left,
            "order_volume": order_volume,
            "text": text
        }

        self.algo_settings[algoid] = {
            "symbol": genus_symbol,
            "side": side,
            "algo_type": algo_type
        }
        print(d)

    def start_algo(
        self,
        vt_symbol: str,
        volume: int,
        price: float,
        order_type: OrderType,
        direction: Direction,
        algo_type: str
    ):
        message = new_message(fix.MsgType_NewOrderSingle)

        symbol, exchange = extract_vt_symbol(vt_symbol)
        genus_exchange = EXCHANGE_VT2GNS[exchange]
        genus_symbol = f"{symbol}.{genus_exchange}"

        side = DIRECTION_VT2GNS[direction]
        genus_type = ORDERTYPE_VT2GNS[order_type]

        utc_now = datetime.utcnow()
        hours = timedelta(hours=1)
        mins = timedelta(minutes=1)

        utc_start = (utc_now - mins).strftime("%Y%m%d-%H:%M:%S")
        utc_end = (utc_now + hours).strftime("%Y%m%d-%H:%M:%S")

        self.algoid += 1
        algoid = str(self.algoid)
        message.setField(fix.ClOrdID(algoid))

        message.setField(fix.HandlInst("2"))
        message.setField(fix.Currency("CNY"))

        message.setField(fix.ExDestination(genus_exchange))
        message.setField(fix.Symbol(genus_symbol))
        message.setField(fix.Side(side))
        message.setField(fix.OrdType(genus_type))
        message.setField(fix.OrderQty(volume))

        if order_type == OrderType.LIMIT:
            message.setField(fix.Price(price))

        parameters = f"StartTime;{utc_start}^EndTime;{utc_end}"
        message.setField(847, algo_type)
        message.setField(848, parameters)

        fix.Session.sendToTarget(message, self.session_id)

        self.algo_settings[algoid] = {
            "symbol": genus_symbol,
            "side": side,
            "algo_type": algo_type
        }

        return algoid

    def stop_algo(self, algoid: str):
        """"""
        algo_setting = self.algo_settings.get(algoid, None)
        if not algo_setting:
            print(f"{algoid} algo setting not found.")
            return

        message = new_message(fix.MsgType_OrderCancelRequest)

        self.algoid += 1
        message.setField(fix.ClOrdID(str(self.algoid)))
        message.setField(fix.OrigClOrdID(orderid))
        message.setField(fix.Symbol(algo_setting["symbol"]))
        message.setField(fix.Side(algo_setting["side"]))
        message.setField(847, algo_setting["algo_type"])

        fix.Session.sendToTarget(message, self.session_id)


def new_message(msg_type: int) -> fix.Message:
    """"""
    message = fix.Message()

    header = message.getHeader()
    header.setField(fix.BeginString("FIX.4.2"))
    header.setField(fix.MsgType(fix.MsgType_OrderCancelRequest))

    utc_now = datetime.utcnow()
    utc_timestamp = utc_now.strftime("%Y%m%d-%H:%M:%S")
    message.setField(60, utc_timestamp)

    return message


def get_field_value(field_map: fix.FieldMap, field: Any) -> Any:
    """"""
    field_map.getField(field)
    return field.getValue()


if __name__ == "__main__":
    from time import sleep

    app = FixInitiator()
    settings = fix.SessionSettings("genus_mother.cfg")
    store_factory = fix.FileStoreFactory(settings)
    log_factory = fix.ScreenLogFactory(settings)

    initiator = fix.SocketInitiator(app, store_factory, settings, log_factory)
    initiator.start()

    sleep(3)

    orderid = app.start_algo(
        "510050.SSE",
        10000,
        0,
        OrderType.MARKET,
        Direction.LONG,
        "TWAP"
    )

    sleep(3)

    app.stop_algo(orderid)

    while True:
        sleep(1)