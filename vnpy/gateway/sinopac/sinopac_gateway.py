"""
Gateway for Sinopac Seruritites.
Author: ypochien@gmail.com
"""
import json
import os
import sys
from collections import OrderedDict
from copy import copy
from datetime import datetime
from threading import Thread
from time import sleep

import requests
import shioaji as sj
from shioaji import constant
from shioaji.account import StockAccount, FutureAccount
from shioaji.order import Status as SinopacStatus


from vnpy.trader.constant import (
    Direction,
    Exchange,
    Product,
    OptionType,
    Status,
    Offset,
)
from vnpy.trader.event import EVENT_TIMER
from vnpy.trader.gateway import BaseGateway
from vnpy.trader.object import (
    TickData,
    OrderData,
    TradeData,
    ContractData,
    PositionData,
    SubscribeRequest,
    OrderRequest,
    CancelRequest,
)

EXCHANGE_VT2SINOPAC = {Exchange.TSE: "TSE",
                       Exchange.TFE: "TFE"}
EXCHANGE_SINOPAC2VT = {v: k for k, v in EXCHANGE_VT2SINOPAC.items()}

STATUS_SINOPAC2VT = {
    SinopacStatus.Cancelled: Status.CANCELLED,
    SinopacStatus.Failed: Status.REJECTED,
    SinopacStatus.Filled: Status.ALLTRADED,
    SinopacStatus.PartFilled: Status.PARTTRADED,
    SinopacStatus.PreSubmitted: Status.SUBMITTING,
    SinopacStatus.Submitted: Status.NOTTRADED,
    SinopacStatus.PendingSubmit: Status.SUBMITTING,
    SinopacStatus.Inactive: Status.SUBMITTING,
}


class SinopacGateway(BaseGateway):
    """
    VN Trader Gateway for Sinopac connection
    """

    default_setting = {
        "身份證字號": "",
        "密碼": "",
        "憑證檔案路徑": "",
        "憑證密碼": "",
        "環境": ["正式", "模擬"],
        "預設現貨帳號": "0",
        "預設期貨帳號": "0",
    }

    exchanges = list(EXCHANGE_SINOPAC2VT.values())

    def __init__(self, event_engine):
        """Constructor"""
        super(SinopacGateway, self).__init__(event_engine, "Sinopac")

        self.subscribed = set()
        self.userid = ""
        self.password = ""
        self.ticks = {}
        self.code2contract = {}

        self.trades = set()
        self.orders = OrderedDict()

        self.count = 0
        self.interval = 20

        self.thread = Thread(target=self.query_data)
        self.query_funcs = [self.query_position, self.query_trade]
        self.api = sj.Shioaji()

    def proc_trade(self, trades):
        self.write_log("cb_update_status")
        # trades = self.api.list_trades()
        for item in trades:
            self.orders[item.order.seqno] = item
            if item.status.status in [SinopacStatus.Filled]:  # 成交
                tradeid = item.status.id
                if tradeid in self.trades:
                    continue
                self.trades.add(tradeid)
                trade = TradeData(
                    symbol=f"{item.contract.code} {item.contract.name}",
                    exchange=EXCHANGE_SINOPAC2VT.get(
                        item.contract.exchange, Exchange.TSE
                    ),
                    direction=Direction.LONG
                    if item.order.action == "Buy"
                    else Direction.SHORT,
                    tradeid=tradeid,
                    orderid=item.order.seqno.rjust(6, "0"),
                    price=float(item.order.price),
                    volume=float(item.order.quantity),
                    datetime=item.status.order_datetime,
                    gateway_name=self.gateway_name,
                )
                self.on_trade(trade)
            else:
                self.write_log(str(item))
                unVol = float(
                    item.order.quantity - (item.status.deal_quantity + item.status.cancel_quantity))
                order = OrderData(
                    symbol=f"{item.contract.code} {item.contract.name}",
                    exchange=EXCHANGE_SINOPAC2VT.get(
                        item.contract.exchange, Exchange.TSE
                    ),
                    orderid=item.order.seqno.rjust(6, "0"),
                    direction=Direction.LONG
                    if item.order.action == "Buy"
                    else Direction.SHORT,
                    price=float(item.order.price),
                    volume=unVol,
                    traded=float(item.status.deal_quantity),
                    status=STATUS_SINOPAC2VT[item.status.status],
                    datetime=item.status.order_datetime,
                    gateway_name=self.gateway_name,
                )
                self.on_order(order)

    def query_trade(self):
        self.api.update_status(timeout=0, cb=self.proc_trade)

    def query_data(self):
        """
        Query all data necessary.
        """
        sleep(2.0)  # Wait 2 seconds till connection completed.

        self.query_position()
        self.query_trade()

        # Start fixed interval query.
        self.event_engine.register(EVENT_TIMER, self.process_timer_event)

    def connect(self, setting: dict):

        userid = setting["身份證字號"]
        password = setting["密碼"]
        try:
            self.api.login(userid, password, contracts_cb=self.query_contract)
        except Exception as exc:
            self.write_log(f"登入失败. [{exc}]")
            return
        self.write_log(f"登入成功. [{userid}]")
        self.select_default_account(setting.get(
            "預設現貨帳號", 0), setting.get("預設期貨帳號", 0))
        self.query_position()
        self.write_log("庫存部位查詢")
        if setting["憑證檔案路徑"] != "":
            self.api.activate_ca(
                setting["憑證檔案路徑"], setting["憑證密碼"], setting["身份證字號"])
            self.write_log(f"{setting['身份證字號']} 憑證 已啟用.")
        self.api.quote.set_callback(self.quote_callback)
        self.write_log("交易行情 - 連線成功")
        self.thread.start()

    def select_default_account(self, select_stock_number, select_futures_number):
        stock_account_count = 0
        futures_account_count = 0
        for acc in self.api.list_accounts():
            if isinstance(acc, StockAccount):
                self.write_log(
                    f"股票帳號: [{stock_account_count}] - {acc.broker_id}-{acc.account_id} {acc.username}"
                )
                stock_account_count += 1
            if isinstance(acc, FutureAccount):
                self.write_log(
                    f"期貨帳號: [{futures_account_count}] - {acc.broker_id}-{acc.account_id} {acc.username}"
                )
                futures_account_count += 1

        if stock_account_count >= 2:
            acc = self.api.list_accounts()[int(select_stock_number)]
            self.api.set_default_account(acc)
            self.write_log(
                f"***預設 現貨下單帳號 - [{select_stock_number}] {acc.broker_id}-{acc.account_id} {acc.username}"
            )

        if futures_account_count >= 2:
            acc = self.api.list_accounts()[int(select_futures_number)]
            self.api.set_default_account(acc)
            self.write_log(
                f"***預設 期貨下單帳號 - [{select_futures_number}] {acc.broker_id}-{acc.account_id} {acc.username}"
            )

    def proc_account(self, data):
        pass

    def process_timer_event(self, event):
        """"""
        self.count += 1
        if self.count < self.interval:
            return
        self.count = 0
        func = self.query_funcs.pop(0)
        func()
        self.query_funcs.append(func)

    def query_contract(self, securities_type=None):
        self.write_log("商品檔" + securities_type)
        if securities_type == constant.SecurityType.Future:
            for category in self.api.Contracts.Futures:
                for contract in category:
                    data = ContractData(
                        symbol=f"{contract.code}",
                        exchange=Exchange.TFE,
                        name=contract.name + contract.delivery_month,
                        product=Product.FUTURES,
                        size=200,
                        pricetick=contract.unit,
                        net_position=True,
                        min_volume=1,
                        gateway_name=self.gateway_name,
                    )
                    self.on_contract(data)
                    self.code2contract[contract.code] = contract
        if securities_type == constant.SecurityType.Option:
            for category in self.api.Contracts.Options:
                for contract in category:
                    data = ContractData(
                        symbol=f"{contract.code} {contract.name}",
                        exchange=Exchange.TFE,
                        name=contract.name + contract.delivery_month,
                        product=Product.OPTION,
                        size=50,
                        net_position=True,
                        pricetick=contract.unit,
                        min_volume=1,
                        gateway_name=self.gateway_name,
                        option_strike=contract.strike_price,
                        option_underlying=contract.underlying_code,
                        option_type=OptionType.CALL
                        if contract.option_right == "C"
                        else OptionType.PUT,
                        option_expiry=None,
                    )
                    self.on_contract(data)
                    self.code2contract[contract.code] = contract
        if securities_type == constant.SecurityType.Stock:
            for category in self.api.Contracts.Stocks:
                for contract in category:
                    data = ContractData(
                        symbol=f"{contract.code}",
                        exchange=Exchange.TSE,
                        name=contract.name,
                        product=Product.EQUITY,
                        size=1,
                        net_position=False,
                        pricetick=contract.unit,
                        min_volume=1,
                        gateway_name=self.gateway_name,
                    )
                    self.on_contract(data)
                    self.code2contract[contract.code] = contract

    def tick_snapshot(self, contract):
        snapshot = self.api.quote.snapshots([contract])[0]
        code = snapshot.code
        tick = self.ticks.get(code, None)
        if tick is None:
            info = self.code2contract[code]
            tick = TickData(
                symbol=code,
                exchange=Exchange.TSE,
                name=f"{info['name']}",
                datetime=snapshot.ts,
                gateway_name=self.gateway_name,
            )
        tick.volume = snapshot.total_volume
        tick.last_price = snapshot.close
        tick.limit_up = contract.limit_up
        tick.open_interest = 0
        tick.limit_down = contract.limit_down
        tick.open_price = snapshot.open
        tick.high_price = snapshot.high
        tick.low_price = snapshot.low
        tick.pre_close = contract.reference
        tick.bid_price_1 = snapshot.buy_price
        tick.bid_volume_1 = snapshot.buy_volume
        tick.ask_price_1 = snapshot.sell_price
        tick.ask_volume_1 = snapshot.sell_volume
        self.ticks[code] = tick
        self.on_tick(copy(tick))

    def getContractSnapshot(self, contract):
        self.tick_snapshot(contract)

    def subscribe(self, req: SubscribeRequest):
        """"""
        if req.symbol in self.subscribed:
            return

        contract = self.code2contract.get(req.symbol, None)
        if contract:
            self.getContractSnapshot(contract)
            self.api.quote.subscribe(contract, quote_type="tick")
            self.api.quote.subscribe(contract, quote_type="bidask")
            self.write_log(
                "訂閱 {} {} {}".format(req.exchange.value,
                                     contract.code, contract.name)
            )
            self.subscribed.add(req.symbol)
        else:
            self.write_log("無此訂閱商品[{}].".format(str(req)))

    def send_order(self, req: OrderRequest):
        """"""
        self.write_log("***send_order")
        self.write_log(str(req))
        if req.exchange == Exchange.TFE:
            action = (
                constant.ACTION_BUY
                if req.direction == Direction.LONG
                else constant.ACTION_SELL
            )
            price_type = constant.FUTURES_PRICE_TYPE_LMT
            order_type = constant.FUTURES_ORDER_TYPE_ROD
            order = self.api.Order(
                req.price,
                req.volume,
                action=action,
                price_type=price_type,
                order_type=order_type,
            )

        elif req.exchange == Exchange.TSE:
            action = (
                constant.ACTION_BUY
                if req.direction == Direction.LONG
                else constant.ACTION_SELL
            )
            price_type = constant.STOCK_PRICE_TYPE_LIMITPRICE
            order_type = constant.STOCK_ORDER_TYPE_COMMON
            first_sell = (
                constant.STOCK_FIRST_SELL_YES
                if req.offset == Offset.CLOSETODAY
                else constant.STOCK_FIRST_SELL_NO
            )
            order = self.api.Order(
                price=req.price,
                quantity=int(req.volume),
                action=action,
                price_type=price_type,
                order_type=order_type,
                first_sell=first_sell,
            )
        trade = self.api.place_order(
            self.code2contract[req.symbol], order, 0, self.cb_placeorder
        )
        orderdata = req.create_order_data(order.seqno, self.gateway_name)
        self.orders[orderdata.orderid] = trade
        self.on_order(orderdata)
        return orderdata.vt_orderid

    def cb_placeorder(self, trade: sj.order.Trade):
        self.write_log("order_callback.")
        self.orders[trade.order.seqno] = trade
        if trade.status.status in [SinopacStatus.Filled]:  # 成交
            tradeid = trade.status.id
            trade = TradeData(
                symbol=f"{trade.contract.code} {trade.contract.name}",
                exchange=EXCHANGE_SINOPAC2VT.get(
                    trade.contract.exchange, Exchange.TSE),
                direction=Direction.LONG
                if trade.order.action == "Buy"
                else Direction.SHORT,
                tradeid=tradeid,
                orderid=trade.order.seqno.ljust(6, "0"),
                price=float(trade.order.price),
                volume=float(trade.order.quantity),
                time=trade.status.order_datetime,
                gateway_name=self.gateway_name,
            )
            self.on_trade(trade)
        else:
            order = OrderData(
                symbol=f"{trade.contract.code} {trade.contract.name}",
                exchange=EXCHANGE_SINOPAC2VT.get(
                    trade.contract.exchange, Exchange.TSE),
                orderid=trade.order.seqno,
                direction=Direction.LONG
                if trade.order.action == "Buy"
                else Direction.SHORT,
                price=float(trade.order.price),
                volume=float(
                    trade.order.quantity
                    - (trade.status.deal_quantity + trade.status.cancel_quantity)
                ),
                traded=float(trade.status.deal_quantity),
                status=STATUS_SINOPAC2VT[trade.status.status],
                time=trade.status.order_datetime,
                gateway_name=self.gateway_name,
            )
            self.on_order(order)

    def cancel_order(self, req: CancelRequest):
        """"""
        self.write_log("***cancel_order")
        self.write_log(str(req))
        self.write_log(str(self.orders[req.orderid]))
        self.api.cancel_order(self.orders[req.orderid])

    def query_account(self):
        """"""
        self.write_log("***query_account")

    def query_position(self):
        """"""
        self.api.get_stock_account_unreal_profitloss().update()
        data = self.api.get_stock_account_unreal_profitloss().data()["summary"]
        for item in data:
            volume = float(item["real_qty"]) / 1000
            total_qty = float(item["real_qty"]) / 1000
            yd_qty = float(item["qty"]) / 1000
            pos = PositionData(
                symbol=f"{item['stock']} {item['stocknm']}",
                exchange=EXCHANGE_SINOPAC2VT.get("TSE", Exchange.TSE),
                direction=Direction.LONG if volume >= 0 else Direction.SHORT,
                volume=volume,
                frozen=total_qty - yd_qty,
                price=float(item["avgprice"]),
                pnl=float(item["unreal"]),
                yd_volume=yd_qty,
                gateway_name=self.gateway_name,
            )
            self.on_position(pos)

    def close(self):
        """"""

    def quote_callback(self, topic, data):
        """
        # L/TFE/TXFF9
        {'Amount': [21088.0], 'AmountSum': [1028165646.0], 'AvgPrice': [10562.513699263414],
         'Close': [10544.0], 'Code': 'TXFF9', 'Date': '2019/05/16', 'DiffPrice': [-37.0],
         'DiffRate': [-0.34968339476419996], 'DiffType': [4], 'High': [10574.0],
         'Low': [10488.0], 'Open': 10537.0, 'TargetKindPrice': 10548.47, 'TickType': [2],
         'Time': '11:15:11.911000', 'TradeAskVolSum': 52599, 'TradeBidVolSum': 53721,
         'VolSum': [97341], 'Volume': [2]}
        # Q/TFE/TXFF9
        {'AskPrice': [10545.0, 10546.0, 10547.0, 10548.0, 10549.0], 'AskVolSum': 262,
         'AskVolume': [17, 99, 59, 45, 42], 'BidPrice': [10544.0, 10543.0, 10542.0, 10541.0, 10540.0],
         'BidVolSum': 289, 'BidVolume': [16, 41, 32, 123, 77], 'Code': 'TXFF9', 'Date': '2019/05/16',
         'DiffAskVol': [0, 0, 0, -1, 0], 'DiffAskVolSum': -1, 'DiffBidVol': [0, 0, 0, 0, 0], 'DiffBidVolSum': 0,
         'FirstDerivedAskPrice': 10547.0, 'FirstDerivedAskVolume': 1, 'FirstDerivedBidPrice': 10542.0,
         'FirstDerivedBidVolume': 1, 'TargetKindPrice': 10548.47, 'Time': '11:15:11.911000'}

        # QUT/idcdmzpcr01/TSE/2330
        {'AskPrice': [248.0, 248.5, 249.0, 249.5, 250.0], 'AskVolume': [355, 632, 630, 301, 429],
         'BidPrice': [247.5, 247.0, 246.5, 246.0, 245.5], 'BidVolume': [397, 389, 509, 703, 434],
         'Date': '2019/05/17', 'Time': '09:53:00.706928'}
        """
        try:
            topics = topic.split("/")
            realtime_type = topics[0]
            tick = None
            if realtime_type == "L":
                tick = self.qutote_futures_L(data)
            elif realtime_type == "Q":
                tick = self.quote_futures_Q(data)
            elif realtime_type == "MKT":
                tick = self.quote_stock_MKT(topics[3], data)
            elif realtime_type == "QUT":
                tick = self.qute_stock_QUT(topics[3], data)
            if tick:
                tick.open_interest = 0
                self.on_tick(copy(tick))
        except Exception as e:
            exc_type, _, exc_tb = sys.exc_info()
            filename = os.path.split(exc_tb.tb_frame.f_code.co_filename)[1]
            self.write_log(
                "[{}][{}][{}][{}]".format(
                    exc_type, filename, exc_tb.tb_lineno, str(e))
            )
            self.write_log(data)

    def quote_futures_Q(self, data):
        code = data.get("Code", None)
        if code is None:
            return
        tick = self.ticks.get(code, None)
        if tick is None:
            contract = self.code2contract[code]
            tick = TickData(
                symbol=data["Code"],
                exchange=Exchange.TFE,
                name=f"{contract['name']}{contract['delivery_month']}",
                datetime=datetime.now(),
                gateway_name=self.gateway_name,
            )
            self.ticks[code] = tick
        tick.bid_price_1 = data["BidPrice"][0]
        tick.bid_price_2 = data["BidPrice"][1]
        tick.bid_price_3 = data["BidPrice"][2]
        tick.bid_price_4 = data["BidPrice"][3]
        tick.bid_price_5 = data["BidPrice"][4]
        tick.ask_price_1 = data["AskPrice"][0]
        tick.ask_price_2 = data["AskPrice"][1]
        tick.ask_price_3 = data["AskPrice"][2]
        tick.ask_price_4 = data["AskPrice"][3]
        tick.ask_price_5 = data["AskPrice"][4]
        tick.bid_volume_1 = data["BidVolume"][0]
        tick.bid_volume_2 = data["BidVolume"][1]
        tick.bid_volume_3 = data["BidVolume"][2]
        tick.bid_volume_4 = data["BidVolume"][3]
        tick.bid_volume_5 = data["BidVolume"][4]
        tick.ask_volume_1 = data["AskVolume"][0]
        tick.ask_volume_2 = data["AskVolume"][1]
        tick.ask_volume_3 = data["AskVolume"][2]
        tick.ask_volume_4 = data["AskVolume"][3]
        tick.ask_volume_5 = data["AskVolume"][4]
        return tick

    def qutote_futures_L(self, data):
        code = data.get("Code", None)
        if code is None:
            return
        tick = self.ticks.get(code, None)
        if tick is None:
            contract = self.code2contract.get(code, None)
            tick = TickData(
                symbol=code,
                exchange=Exchange.TFE,
                name=f"{contract['name']}{contract['delivery_month']}",
                datetime=datetime.now(),
                gateway_name=self.gateway_name,
            )
            self.ticks[code] = tick
        tick.datetime = datetime.strptime(
            "{} {}".format(data["Date"], data["Time"]), "%Y/%m/%d %H:%M:%S.%f"
        )
        tick.volume = int(data["VolSum"][0])
        tick.last_price = data["Close"][0]
        tick.limit_up = 0
        tick.open_interest = 0
        tick.limit_down = 0
        tick.open_price = data["Open"]
        tick.high_price = data["High"][0]
        tick.low_price = data["Low"][0]
        tick.pre_close = data["Close"][0] - data["DiffPrice"][0]
        return tick

    def quote_stock_MKT(self, code, data):
        """
        QUT/idcdmzpcr01/TSE/2330
        {'AskPrice': [248.0, 248.5, 249.0, 249.5, 250.0], 'AskVolume': [355, 632, 630, 301, 429],
        'BidPrice': [247.5, 247.0, 246.5, 246.0, 245.5], 'BidVolume': [397, 389, 509, 703, 434],
         'Date': '2019/05/17', 'Time': '09:53:00.706928'}

        MKT/idcdmzpcr01/TSE/2330
        {'Close': [248.0], 'Time': '09:53:00.706928',
            'VolSum': [7023], 'Volume': [1]}
        """

        tick = self.ticks.get(code, None)
        if tick is None:
            contract = self.code2contract[code]
            tick = TickData(
                symbol=code,
                exchange=Exchange.TSE,
                name=f"{contract['name']}{contract['delivery_month']}",
                datetime=datetime.now(),
                gateway_name=self.gateway_name,
                low_price=99999,
            )
            self.ticks[code] = tick
        tick.datetime = datetime.combine(
            datetime.today(),
            datetime.strptime("{}".format(data["Time"]), "%H:%M:%S.%f").time(),
        )
        tick.volume = int(data["VolSum"][0])
        tick.last_price = data["Close"][0]
        tick.limit_up = 0
        tick.open_interest = 0
        tick.limit_down = 0
        tick.open_price = data["Close"][0] if tick.open_price == 0 else tick.open_price
        tick.high_price = (
            data["Close"][0] if data["Close"][0] > tick.high_price else tick.high_price
        )
        tick.low_price = (
            data["Close"][0] if data["Close"][0] < tick.low_price else tick.low_price
        )
        tick.pre_close = tick.open_price
        return tick

    def qute_stock_QUT(self, code, data):
        tick = self.ticks.get(code, None)
        if tick is None:
            contract = self.code2contract[code]
            tick = TickData(
                symbol=code,
                exchange=Exchange.TSE,
                name=f"{contract['name']}{contract['delivery_month']}",
                datetime=datetime.now(),
                gateway_name=self.gateway_name,
            )
            self.ticks[code] = tick
        tick.bid_price_1 = data["BidPrice"][0]
        tick.bid_price_2 = data["BidPrice"][1]
        tick.bid_price_3 = data["BidPrice"][2]
        tick.bid_price_4 = data["BidPrice"][3]
        tick.bid_price_5 = data["BidPrice"][4]

        tick.ask_price_1 = data["AskPrice"][0]
        tick.ask_price_2 = data["AskPrice"][1]
        tick.ask_price_3 = data["AskPrice"][2]
        tick.ask_price_4 = data["AskPrice"][3]
        tick.ask_price_5 = data["AskPrice"][4]

        tick.bid_volume_1 = data["BidVolume"][0]
        tick.bid_volume_2 = data["BidVolume"][1]
        tick.bid_volume_3 = data["BidVolume"][2]
        tick.bid_volume_4 = data["BidVolume"][3]
        tick.bid_volume_5 = data["BidVolume"][4]

        tick.ask_volume_1 = data["AskVolume"][0]
        tick.ask_volume_2 = data["AskVolume"][1]
        tick.ask_volume_3 = data["AskVolume"][2]
        tick.ask_volume_4 = data["AskVolume"][3]
        tick.ask_volume_5 = data["AskVolume"][4]
        return tick
