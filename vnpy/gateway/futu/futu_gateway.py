"""
Please install futu-api before use.
"""

from copy import copy
from datetime import datetime
from threading import Thread
from time import sleep

from futu import (
    ModifyOrderOp,
    TrdSide,
    TrdEnv,
    OpenHKTradeContext,
    OpenQuoteContext,
    OpenUSTradeContext,
    OrderBookHandlerBase,
    OrderStatus,
    OrderType,
    RET_ERROR,
    RET_OK,
    StockQuoteHandlerBase,
    TradeDealHandlerBase,
    TradeOrderHandlerBase
)

from vnpy.trader.constant import Direction, Exchange, Product, Status
from vnpy.trader.event import EVENT_TIMER
from vnpy.trader.gateway import BaseGateway
from vnpy.trader.object import (
    TickData,
    OrderData,
    TradeData,
    AccountData,
    ContractData,
    PositionData,
    SubscribeRequest,
    OrderRequest,
    CancelRequest
)

EXCHANGE_VT2FUTU = {
    Exchange.SMART: "US",
    Exchange.SEHK: "HK",
    Exchange.HKFE: "HK_FUTURE",
}
EXCHANGE_FUTU2VT = {v: k for k, v in EXCHANGE_VT2FUTU.items()}

PRODUCT_VT2FUTU = {
    Product.EQUITY: "STOCK",
    Product.INDEX: "IDX",
    Product.ETF: "ETF",
    Product.WARRANT: "WARRANT",
    Product.BOND: "BOND",
}

DIRECTION_VT2FUTU = {
    Direction.LONG: TrdSide.BUY,
    Direction.SHORT: TrdSide.SELL,
}
DIRECTION_FUTU2VT = {v: k for k, v in DIRECTION_VT2FUTU.items()}

STATUS_FUTU2VT = {
    OrderStatus.NONE: Status.SUBMITTING,
    OrderStatus.SUBMITTING: Status.SUBMITTING,
    OrderStatus.SUBMITTED: Status.NOTTRADED,
    OrderStatus.FILLED_PART: Status.PARTTRADED,
    OrderStatus.FILLED_ALL: Status.ALLTRADED,
    OrderStatus.CANCELLED_ALL: Status.CANCELLED,
    OrderStatus.CANCELLED_PART: Status.CANCELLED,
    OrderStatus.SUBMIT_FAILED: Status.REJECTED,
    OrderStatus.FAILED: Status.REJECTED,
    OrderStatus.DISABLED: Status.CANCELLED,
}


class FutuGateway(BaseGateway):
    """"""

    default_setting = {
        "密码": "",
        "地址": "127.0.0.1",
        "端口": 11111,
        "市场": ["HK", "US"],
        "环境": [TrdEnv.REAL, TrdEnv.SIMULATE],
    }

    exchanges = list(EXCHANGE_FUTU2VT.values())

    def __init__(self, event_engine):
        """Constructor"""
        super(FutuGateway, self).__init__(event_engine, "FUTU")

        self.quote_ctx = None
        self.trade_ctx = None

        self.host = ""
        self.port = 0
        self.market = ""
        self.password = ""
        self.env = TrdEnv.SIMULATE

        self.ticks = {}
        self.trades = set()
        self.contracts = {}

        self.thread = Thread(target=self.query_data)

        # For query function.
        self.count = 0
        self.interval = 1
        self.query_funcs = [self.query_account, self.query_position]

    def connect(self, setting: dict):
        """"""
        self.host = setting["地址"]
        self.port = setting["端口"]
        self.market = setting["市场"]
        self.password = setting["密码"]
        self.env = setting["环境"]

        self.connect_quote()
        self.connect_trade()

        self.thread.start()

    def query_data(self):
        """
        Query all data necessary.
        """
        sleep(2.0)  # Wait 2 seconds till connection completed.

        self.query_contract()
        self.query_trade()
        self.query_order()
        self.query_position()
        self.query_account()

        # Start fixed interval query.
        self.event_engine.register(EVENT_TIMER, self.process_timer_event)

    def process_timer_event(self, event):
        """"""
        self.count += 1
        if self.count < self.interval:
            return
        self.count = 0
        func = self.query_funcs.pop(0)
        func()
        self.query_funcs.append(func)

    def connect_quote(self):
        """
        Connect to market data server.
        """
        self.quote_ctx = OpenQuoteContext(self.host, self.port)

        class QuoteHandler(StockQuoteHandlerBase):
            gateway = self

            def on_recv_rsp(self, rsp_str):
                ret_code, content = super(QuoteHandler, self).on_recv_rsp(
                    rsp_str
                )
                if ret_code != RET_OK:
                    return RET_ERROR, content
                self.gateway.process_quote(content)
                return RET_OK, content

        class OrderBookHandler(OrderBookHandlerBase):
            gateway = self

            def on_recv_rsp(self, rsp_str):
                ret_code, content = super(OrderBookHandler, self).on_recv_rsp(
                    rsp_str
                )
                if ret_code != RET_OK:
                    return RET_ERROR, content
                self.gateway.process_orderbook(content)
                return RET_OK, content

        self.quote_ctx.set_handler(QuoteHandler())
        self.quote_ctx.set_handler(OrderBookHandler())
        self.quote_ctx.start()

        self.write_log("行情接口连接成功")

    def connect_trade(self):
        """
        Connect to trade server.
        """
        # Initialize context according to market.
        if self.market == "US":
            self.trade_ctx = OpenUSTradeContext(self.host, self.port)
        else:
            self.trade_ctx = OpenHKTradeContext(self.host, self.port)

        # Implement handlers.
        class OrderHandler(TradeOrderHandlerBase):
            gateway = self

            def on_recv_rsp(self, rsp_str):
                ret_code, content = super(OrderHandler, self).on_recv_rsp(
                    rsp_str
                )
                if ret_code != RET_OK:
                    return RET_ERROR, content
                self.gateway.process_order(content)
                return RET_OK, content

        class DealHandler(TradeDealHandlerBase):
            gateway = self

            def on_recv_rsp(self, rsp_str):
                ret_code, content = super(DealHandler, self).on_recv_rsp(
                    rsp_str
                )
                if ret_code != RET_OK:
                    return RET_ERROR, content
                self.gateway.process_deal(content)
                return RET_OK, content

        # Unlock to allow trading.
        code, data = self.trade_ctx.unlock_trade(self.password)
        if code == RET_OK:
            self.write_log("交易接口解锁成功")
        else:
            self.write_log(f"交易接口解锁失败，原因：{data}")

        # Start context.
        self.trade_ctx.set_handler(OrderHandler())
        self.trade_ctx.set_handler(DealHandler())
        self.trade_ctx.start()
        self.write_log("交易接口连接成功")

    def subscribe(self, req: SubscribeRequest):
        """"""
        for data_type in ["QUOTE", "ORDER_BOOK"]:
            futu_symbol = convert_symbol_vt2futu(req.symbol, req.exchange)
            code, data = self.quote_ctx.subscribe(futu_symbol, data_type, True)

            if code:
                self.write_log(f"订阅行情失败：{data}")

    def send_order(self, req: OrderRequest):
        """"""
        side = DIRECTION_VT2FUTU[req.direction]
        futu_order_type = OrderType.NORMAL  # Only limit order is supported.

        # Set price adjustment mode to inside adjustment.
        if req.direction is Direction.LONG:
            adjust_limit = 0.05
        else:
            adjust_limit = -0.05

        futu_symbol = convert_symbol_vt2futu(req.symbol, req.exchange)
        code, data = self.trade_ctx.place_order(
            req.price,
            req.volume,
            futu_symbol,
            side,
            futu_order_type,
            trd_env=self.env,
            adjust_limit=adjust_limit,
        )

        if code:
            self.write_log(f"委托失败：{data}")
            return ""

        for ix, row in data.iterrows():
            orderid = str(row["order_id"])

        order = req.create_order_data(orderid, self.gateway_name)
        self.on_order(order)
        return order.vt_orderid

    def cancel_order(self, req: CancelRequest):
        """"""
        code, data = self.trade_ctx.modify_order(
            ModifyOrderOp.CANCEL, req.orderid, 0, 0, trd_env=self.env
        )

        if code:
            self.write_log(f"撤单失败：{data}")

    def query_contract(self):
        """"""
        for product, futu_product in PRODUCT_VT2FUTU.items():
            code, data = self.quote_ctx.get_stock_basicinfo(
                self.market, futu_product
            )

            if code:
                self.write_log(f"查询合约信息失败：{data}")
                return

            for ix, row in data.iterrows():
                symbol, exchange = convert_symbol_futu2vt(row["code"])
                contract = ContractData(
                    symbol=symbol,
                    exchange=exchange,
                    name=row["name"],
                    product=product,
                    size=1,
                    pricetick=0.001,
                    net_position=True,
                    gateway_name=self.gateway_name,
                )
                self.on_contract(contract)
                self.contracts[contract.vt_symbol] = contract

        self.write_log("合约信息查询成功")

    def query_account(self):
        """"""
        code, data = self.trade_ctx.accinfo_query(trd_env=self.env, acc_id=0)

        if code:
            self.write_log(f"查询账户资金失败：{data}")
            return

        for ix, row in data.iterrows():
            account = AccountData(
                accountid=f"{self.gateway_name}_{self.market}",
                balance=float(row["total_assets"]),
                frozen=(float(row["total_assets"]) - float(row["avl_withdrawal_cash"])),
                gateway_name=self.gateway_name,
            )
            self.on_account(account)

    def query_position(self):
        """"""
        code, data = self.trade_ctx.position_list_query(
            trd_env=self.env, acc_id=0
        )

        if code:
            self.write_log(f"查询持仓失败：{data}")
            return

        for ix, row in data.iterrows():
            symbol, exchange = convert_symbol_futu2vt(row["code"])
            pos = PositionData(
                symbol=symbol,
                exchange=exchange,
                direction=Direction.LONG,
                volume=row["qty"],
                frozen=(float(row["qty"]) - float(row["can_sell_qty"])),
                price=float(row["cost_price"]),
                pnl=float(row["pl_val"]),
                gateway_name=self.gateway_name,
            )

            self.on_position(pos)

    def query_order(self):
        """"""
        code, data = self.trade_ctx.order_list_query("", trd_env=self.env)

        if code:
            self.write_log(f"查询委托失败：{data}")
            return

        self.process_order(data)
        self.write_log("委托查询成功")

    def query_trade(self):
        """"""
        code, data = self.trade_ctx.deal_list_query("", trd_env=self.env)

        if code:
            self.write_log(f"查询成交失败：{data}")
            return

        self.process_deal(data)
        self.write_log("成交查询成功")

    def close(self):
        """"""
        if self.quote_ctx:
            self.quote_ctx.close()

        if self.trade_ctx:
            self.trade_ctx.close()

    def get_tick(self, code):
        """
        Get tick buffer.
        """
        tick = self.ticks.get(code, None)
        symbol, exchange = convert_symbol_futu2vt(code)
        if not tick:
            tick = TickData(
                symbol=symbol,
                exchange=exchange,
                datetime=datetime.now(),
                gateway_name=self.gateway_name,
            )
            self.ticks[code] = tick

        contract = self.contracts.get(tick.vt_symbol, None)
        if contract:
            tick.name = contract.name

        return tick

    def process_quote(self, data):
        """报价推送"""
        for ix, row in data.iterrows():
            symbol = row["code"]

            tick = self.get_tick(symbol)

            date = row["data_date"].replace("-", "")
            time = row["data_time"]
            tick.datetime = datetime.strptime(
                f"{date} {time}", "%Y%m%d %H:%M:%S")
            tick.open_price = row["open_price"]
            tick.high_price = row["high_price"]
            tick.low_price = row["low_price"]
            tick.pre_close = row["prev_close_price"]
            tick.last_price = row["last_price"]
            tick.volume = row["volume"]

            if "price_spread" in row:
                spread = row["price_spread"]
                tick.limit_up = tick.last_price + spread * 10
                tick.limit_down = tick.last_price - spread * 10

            self.on_tick(copy(tick))

    def process_orderbook(self, data):
        """"""
        symbol = data["code"]
        tick = self.get_tick(symbol)

        d = tick.__dict__
        for i in range(5):
            bid_data = data["Bid"][i]
            ask_data = data["Ask"][i]
            n = i + 1

            d["bid_price_%s" % n] = bid_data[0]
            d["bid_volume_%s" % n] = bid_data[1]
            d["ask_price_%s" % n] = ask_data[0]
            d["ask_volume_%s" % n] = ask_data[1]

        if tick.datetime:
            self.on_tick(copy(tick))

    def process_order(self, data):
        """
        Process order data for both query and update.
        """
        for ix, row in data.iterrows():
            # Ignore order with status DELETED
            if row["order_status"] == OrderStatus.DELETED:
                continue

            symbol, exchange = convert_symbol_futu2vt(row["code"])
            order = OrderData(
                symbol=symbol,
                exchange=exchange,
                orderid=str(row["order_id"]),
                direction=DIRECTION_FUTU2VT[row["trd_side"]],
                price=float(row["price"]),
                volume=row["qty"],
                traded=row["dealt_qty"],
                status=STATUS_FUTU2VT[row["order_status"]],
                time=row["create_time"].split(" ")[-1],
                gateway_name=self.gateway_name,
            )

            self.on_order(order)

    def process_deal(self, data):
        """
        Process trade data for both query and update.
        """
        for ix, row in data.iterrows():
            tradeid = str(row["deal_id"])
            if tradeid in self.trades:
                continue
            self.trades.add(tradeid)

            symbol, exchange = convert_symbol_futu2vt(row["code"])
            trade = TradeData(
                symbol=symbol,
                exchange=exchange,
                direction=DIRECTION_FUTU2VT[row["trd_side"]],
                tradeid=tradeid,
                orderid=row["order_id"],
                price=float(row["price"]),
                volume=row["qty"],
                time=row["create_time"].split(" ")[-1],
                gateway_name=self.gateway_name,
            )

            self.on_trade(trade)


def convert_symbol_futu2vt(code):
    """
    Convert symbol from futu to vt.
    """
    code_list = code.split(".")
    futu_exchange = code_list[0]
    futu_symbol = ".".join(code_list[1:])
    exchange = EXCHANGE_FUTU2VT[futu_exchange]
    return futu_symbol, exchange


def convert_symbol_vt2futu(symbol, exchange):
    """
    Convert symbol from vt to futu.
    """
    futu_exchange = EXCHANGE_VT2FUTU[exchange]
    return f"{futu_exchange}.{symbol}"
