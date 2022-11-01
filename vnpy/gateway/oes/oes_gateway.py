"""
Author: Ke.Ke.
"""
import hashlib
import os
from datetime import datetime
from typing import Dict, List

from vnpy.trader.gateway import BaseGateway
from vnpy.trader.utility import get_file_path, round_to
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
from vnpy.api.oes import TdApi, MdApi
from vnpy.trader.constant import (
    Direction,
    Offset,
    Exchange,
    OrderType,
    Product,
    Status,
    OptionType
)

CHANNELTYPE_OES2VT = {
    1: "委托通道",
    2: "回报通道",
    3: "交易查询通道",
    11: "TCP通道",
}

ORDERTYPE_VT2OES: Dict[int, OrderType] = {
    OrderType.LIMIT: 0,
    OrderType.MARKET: 20
}

ORDERTYPE_OES2VT = {
    0: OrderType.LIMIT,
    20: OrderType.MARKET,
}

OPTIONTYPE_OES2VT = {
    1: OptionType.CALL,
    2: OptionType.PUT
}

PRODUCT_OES2VT = {
    1: Product.EQUITY,
    2: Product.BOND,
    3: Product.ETF,
    4: Product.FUND,
    5: Product.OPTION
}

PRODUCT_VT2OES = {
    Product.EQUITY: 1,
    Product.BOND: 1,
    Product.ETF: 2,
    Product.FUND: 2,
    Product.OPTION: 3
}

DIRECTION_OES2VT = {
    1: Direction.LONG,
    2: Direction.SHORT,
    3: Direction.LONG,
}


DIRECTION_VT2OES = {
    Direction.LONG: 1,
    Direction.SHORT: 2,
}

STATUS_OES2VT = {
    0: Status.SUBMITTING,
    1: Status.NOTTRADED,
    2: Status.NOTTRADED,
    3: Status.PARTTRADED,
    4: Status.CANCELLED,
    5: Status.CANCELLED,
    6: Status.CANCELLED,
    7: Status.CANCELLED,
    8: Status.ALLTRADED,
    10: Status.REJECTED
}

OPTION_DIRECTION_VT2OES = {
    (Direction.LONG, Offset.OPEN): 11,
    (Direction.SHORT, Offset.CLOSE): 12,
    (Direction.SHORT, Offset.OPEN): 13,
    (Direction.LONG, Offset.CLOSE): 14,
}

OPTION_DIRECTION_OES2VT = {v: k for k, v in OPTION_DIRECTION_VT2OES.items()}
OPTION_DIRECTION_OES2VT[1] = (Direction.LONG, Offset.NONE)
OPTION_DIRECTION_OES2VT[2] = (Direction.SHORT, Offset.NONE)

EXCHANGE_OES2VT = {
    1: Exchange.SSE,
    2: Exchange.SZSE,
    3: Exchange.SSE,
    4: Exchange.SZSE,
}

STOCK_EXCHANGE_VT2OES = {
    Exchange.SSE: 1,
    Exchange.SZSE: 2
}

OPTION_EXCHANGE_VT2OES = {
    Exchange.SSE: 3,
    Exchange.SZSE: 4
}

SYMBOL_PRODCUT_MAP = {}
SYMBOL_NAME_MAP = {}
SYMBOL_PRICETICK_MAP = {}


class OesGateway(BaseGateway):
    """"""

    default_setting = {
        "td_ord_server": "",
        "td_rpt_server": "",
        "td_qry_server": "",
        "md_tcp_server": "",
        "md_qry_server": "",
        "username": "",
        "password": "",
        "hdd_serial": "",
        "customize_ip": "",
        "customize_mac": "",
    }

    exchanges: List[Exchange] = [Exchange.SSE, Exchange.SZSE]

    def __init__(self, event_engine):
        """Constructor"""
        super().__init__(event_engine, "OES")

        self.md_api = OesMdApi(self)
        self.td_api = OesTdApi(self)

    def connect(self, setting: dict) -> None:
        """"""
        if not setting['password'].startswith("md5:"):
            setting['password'] = "md5:" + \
                hashlib.md5(setting['password'].encode()).hexdigest()

        username = setting['username']
        password = setting['password']

        config_path = str(get_file_path("vnoes.ini"))
        with open(config_path, "wt") as f:
            if 'test' in setting:
                log_level = 'DEBUG'
                log_mode = 'console'
            else:
                log_level = 'WARNING'
                log_mode = 'file'
            log_dir = get_file_path('oes')
            log_path = os.path.join(log_dir, 'log.log')
            if not os.path.exists(log_dir):
                os.mkdir(log_dir)
            content = config_template.format(
                **setting,
                log_level=log_level,
                log_mode=log_mode,
                log_path=log_path
            )
            f.write(content)

        self.md_api.connect(
            config_path=config_path,
            username=username,
            password=password
        )

        self.td_api.connect(
            config_path=config_path,
            username=username,
            password=password,
            ord_server=setting['td_ord_server'],
            rpt_server=setting['td_rpt_server'],
            hdd_serial=setting['hdd_serial'],
            qry_server=setting['td_qry_server'],
            customize_ip=setting['customize_ip'],
            customize_mac=setting['customize_mac'],
        )

    def subscribe(self, req: SubscribeRequest) -> None:
        """"""
        self.md_api.subscribe(req)

    def send_order(self, req: OrderRequest) -> str:
        """"""
        self.td_api.send_order(req)

    def cancel_order(self, req: CancelRequest) -> None:
        """"""
        self.td_api.cancel_order(req)

    def query_account(self) -> None:
        """"""
        pass

    def query_position(self) -> None:
        """"""
        pass

    def close(self) -> None:
        """"""
        self.md_api.exit()
        self.td_api.exit()


class OesMdApi(MdApi):

    def __init__(self, gateway):
        """Constructor"""
        super(OesMdApi, self).__init__()
        self.gateway: OesGateway = gateway
        self.gateway_name: str = gateway.gateway_name

    def onConnected(self, channel: int, data: dict) -> None:
        """"""
        channel_msg = CHANNELTYPE_OES2VT[channel]
        self.gateway.write_log(f"{channel_msg}连接成功")

    def onRtnStockData(self, head: dict, data: dict) -> None:
        """"""
        timestamp = f"{head['tradeDate']} {head['updateTime']}"

        tick = TickData(
            symbol=data["SecurityID"],
            exchange=EXCHANGE_OES2VT[head["exchId"]],
            datetime=datetime.strptime(timestamp, "%Y%m%d %H%M%S%f"),
            volume=data["TotalVolumeTraded"],
            pre_close=data["PrevClosePx"],
            last_price=data["TradePx"] / 10000,
            open_price=data["OpenPx"] / 10000,
            high_price=data["HighPx"] / 10000,
            low_price=data["LowPx"] / 10000,
            gateway_name=self.gateway_name
        )
        tick.bid_price_1, tick.bid_price_2, tick.bid_price_3, tick.bid_price_4, tick.bid_price_5 = data["bid"][0:5]
        tick.ask_price_1, tick.ask_price_2, tick.ask_price_3, tick.ask_price_4, tick.ask_price_5 = data["ask"][0:5]
        tick.bid_volume_1, tick.bid_volume_2, tick.bid_volume_3, tick.bid_volume_4, tick.bid_volume_5 = data["bid_qty"][0:5]
        tick.ask_volume_1, tick.ask_volume_2, tick.ask_volume_3, tick.ask_volume_4, tick.ask_volume_5 = data["ask_qty"][0:5]

        pricetick = SYMBOL_PRICETICK_MAP.get(tick.vt_symbol, 0)
        if pricetick:
            tick.bid_price_1 = round_to(tick.bid_price_1 / 10000, pricetick)
            tick.bid_price_2 = round_to(tick.bid_price_2 / 10000, pricetick)
            tick.bid_price_3 = round_to(tick.bid_price_3 / 10000, pricetick)
            tick.bid_price_4 = round_to(tick.bid_price_4 / 10000, pricetick)
            tick.bid_price_5 = round_to(tick.bid_price_5 / 10000, pricetick)
            tick.ask_price_1 = round_to(tick.ask_price_1 / 10000, pricetick)
            tick.ask_price_2 = round_to(tick.ask_price_2 / 10000, pricetick)
            tick.ask_price_3 = round_to(tick.ask_price_3 / 10000, pricetick)
            tick.ask_price_4 = round_to(tick.ask_price_4 / 10000, pricetick)
            tick.ask_price_5 = round_to(tick.ask_price_5 / 10000, pricetick)

        tick.name = SYMBOL_NAME_MAP.get(tick.vt_symbol, "")
        self.gateway.on_tick(tick)

    def onRtnIndexData(self, head: dict, data: dict) -> None:
        """"""
        timestamp = f"{head['tradeDate']} {head['updateTime']}"

        tick = TickData(
            symbol=data["SecurityID"],
            exchange=EXCHANGE_OES2VT[head["exchId"]],
            datetime=datetime.strptime(timestamp, "%Y%m%d %H%M%S%f"),
            volume=data["TotalVolumeTraded"],
            pre_close=data["PrevCloseIdx"],
            last_price=data["LastIdx"] / 10000,
            open_price=data["OpenIdx"] / 10000,
            high_price=data["HighIdx"] / 10000,
            low_price=data["LowIdx"] / 10000,
            gateway_name=self.gateway_name
        )
        tick.name = SYMBOL_NAME_MAP.get(tick.vt_symbol, "")
        self.gateway.on_tick(tick)

    def onRtnOptionData(self, head: dict, data: dict) -> None:
        """"""
        timestamp = f"{head['tradeDate']} {head['updateTime']}"

        tick = TickData(
            symbol=data["SecurityID"],
            exchange=EXCHANGE_OES2VT[head["exchId"]],
            datetime=datetime.strptime(timestamp, "%Y%m%d %H%M%S%f"),
            volume=data["TotalVolumeTraded"],
            pre_close=data["PrevClosePx"],
            last_price=data["TradePx"] / 10000,
            open_price=data["OpenPx"] / 10000,
            high_price=data["HighPx"] / 10000,
            low_price=data["LowPx"] / 10000,
            gateway_name=self.gateway_name
        )
        tick.bid_price_1, tick.bid_price_2, tick.bid_price_3, tick.bid_price_4, tick.bid_price_5 = data["bid"][0:5]
        tick.ask_price_1, tick.ask_price_2, tick.ask_price_3, tick.ask_price_4, tick.ask_price_5 = data["ask"][0:5]
        tick.bid_volume_1, tick.bid_volume_2, tick.bid_volume_3, tick.bid_volume_4, tick.bid_volume_5 = data["bid_qty"][0:5]
        tick.ask_volume_1, tick.ask_volume_2, tick.ask_volume_3, tick.ask_volume_4, tick.ask_volume_5 = data["ask_qty"][0:5]

        pricetick = SYMBOL_PRICETICK_MAP.get(tick.vt_symbol, 0)
        if pricetick:
            tick.bid_price_1 = round_to(tick.bid_price_1 / 10000, pricetick)
            tick.bid_price_2 = round_to(tick.bid_price_2 / 10000, pricetick)
            tick.bid_price_3 = round_to(tick.bid_price_3 / 10000, pricetick)
            tick.bid_price_4 = round_to(tick.bid_price_4 / 10000, pricetick)
            tick.bid_price_5 = round_to(tick.bid_price_5 / 10000, pricetick)
            tick.ask_price_1 = round_to(tick.ask_price_1 / 10000, pricetick)
            tick.ask_price_2 = round_to(tick.ask_price_2 / 10000, pricetick)
            tick.ask_price_3 = round_to(tick.ask_price_3 / 10000, pricetick)
            tick.ask_price_4 = round_to(tick.ask_price_4 / 10000, pricetick)
            tick.ask_price_5 = round_to(tick.ask_price_5 / 10000, pricetick)

        tick.name = SYMBOL_NAME_MAP.get(tick.vt_symbol, "")
        self.gateway.on_tick(tick)

    def onDisConnected(self, channel: int, data: dict) -> None:
        """"""
        self.gateway.write_log("交易服务器连接断开")

    def subscribe(self, req: SubscribeRequest) -> None:
        """"""
        oes_exchange = STOCK_EXCHANGE_VT2OES[req.exchange]
        vt_product = SYMBOL_PRODCUT_MAP.get(req.vt_symbol, None)
        if not vt_product:
            self.gateway.write_log(f"找不到交易所合约代码{req.symbol}.{req.exchange}")
            return
        oes_product = PRODUCT_VT2OES[vt_product]
        oes_symbol = req.symbol + ".SH"
        if oes_exchange == 2:
            oes_symbol = f"{req.symbol}.SZ"

        self.subscribeMarketData(
            oes_symbol,
            oes_exchange,
            oes_product
        )

    def connect(
        self,
        config_path,
        username,
        password,
    ) -> None:
        self.createMdApi(config_path, username, password)
        self.init()


class OesTdApi(TdApi):

    userid: str = ""
    investorid: str = ""
    connect_date: int = 0
    trade_count: int = 10000
    order_count: int = 10000
    reqid: int = 10000

    orders: Dict[int, OrderData] = {}
    local_sys_ids: Dict[int, int] = {}
    sys_local_ids: Dict[int, int] = {}

    def __init__(self, gateway):
        """Constructor"""
        super(OesTdApi, self).__init__()
        self.gateway: OesGateway = gateway
        self.gateway_name: str = gateway.gateway_name

    def onBusinessReject(self, head: dict, data: dict) -> None:
        """"""
        error_no = data["ordRejReason"]
        timestamp = f"{data['ordDate']} {data['ordTime']}"
        dt = datetime.strptime(timestamp, "%Y%m%d %H%M%S%f")
        orderid = data["origClOrdId"]
        oes_type = data["ordType"]

        if data["bsType"] == 30:
            self.gateway.write_log(f"委托号{orderid} 重复撤单")
            return

        order = self.orders.get(orderid, None)
        if not order:
            symbol = data["securityId"]

            direction = DIRECTION_OES2VT.get(data["bsType"], None)
            offset = Offset.NONE
            if len(symbol) > 6:
                (direction, offset) = OPTION_DIRECTION_OES2VT[data["bsType"]]
            order = OrderData(
                orderid=orderid,
                symbol=data["securityId"],
                exchange=EXCHANGE_OES2VT[data["mktId"]],
                type=ORDERTYPE_OES2VT[oes_type],
                direction=direction,
                offset=offset,
                price=data["ordPrice"] / 10000,
                volume=data["ordQty"],
                status=Status.REJECTED,
                datetime=dt,
                gateway_name=self.gateway_name
            )
            self.gateway.on_order(order)
        else:
            order.status = Status.REJECTED
            self.gateway.on_order(order)
            msg = f"委托{orderid}拒单，原因{error_no}"
            self.gateway.write_log(msg)

    def onCashAssetVariation(self, data: dict) -> None:
        account = AccountData(
            accountid=data["cashAcctId"],
            balance=data["currentTotalBal"],
            frozen=data["marginAmt"],
            gateway_name=self.gateway_name
        )
        self.gateway.on_account(account)

    def onStockHoldingVariation(self, data: dict) -> None:
        pass

    def onOptionHoldingVariation(self, data: dict) -> None:
        self.investorid = data["invAcctId"][1:]

        pos = PositionData(
            symbol=data["securityId"],
            exchange=EXCHANGE_OES2VT[data["mktId"]],
            direction=DIRECTION_OES2VT[data["positionType"]],
            volume=data["sumQty"],
            frozen=data["closeFrzQty"],
            price=data["costPrice"] / 10000,
            gateway_name=self.gateway_name
        )
        self.gateway.on_position(pos)

    def onOptionUnderlyingHoldingVariation(self, data: dict) -> None:
        """"""
        pass

    def onOrderInsert(self, head: dict, data: dict) -> None:
        """"""
        orderid = data["origClOrdId"]

        timestamp = f"{data['ordDate']} {data['ordTime']}"
        dt = datetime.strptime(timestamp, "%Y%m%d %H%M%S%f")
        status = STATUS_OES2VT[data["ordCnfmSts"]]
        order = self.orders.get(orderid, None)
        if not order:
            symbol = data["securityId"]

            direction = DIRECTION_OES2VT.get(data["bsType"], None)
            offset = Offset.NONE
            if len(symbol) > 6:
                (direction, offset) = OPTION_DIRECTION_OES2VT.get(
                    data["bsType"],
                    (Direction.NET, Offset.NONE)
                )
            order = OrderData(
                orderid=orderid,
                symbol=symbol,
                exchange=EXCHANGE_OES2VT[data["mktId"]],
                type=ORDERTYPE_OES2VT[data["ordType"]],
                direction=direction,
                offset=offset,
                price=data["ordPrice"] / 10000,
                volume=data["ordQty"],
                status=status,
                datetime=dt,
                gateway_name=self.gateway_name
            )
            self.gateway.on_order(order)
            self.orders[orderid] = order
        else:
            order.status = status
            order.datetime = dt
            self.gateway.on_order(order)

    def onConnected(self, channel, data: dict) -> None:
        """"""
        self.reqid = max(data["lastOutMsgSeq"], self.reqid)
        channel_msg = CHANNELTYPE_OES2VT[channel]
        self.gateway.write_log(f"{channel_msg}连接成功")

        if channel == 3:
            self.query_account()

    def onDisConnected(self, channel, data: dict) -> None:
        """"""
        self.gateway.write_log("交易服务器连接断开")

    def onTradeReport(self, head: dict, data: dict) -> None:
        """"""
        sysid = data["clOrdId"]
        orderid = self.sys_local_ids.get(sysid, None)
        if not sysid:
            self.gateway.write_log("成交回报找不到对应的委托号")
        else:
            order = self.orders[orderid]
            timestamp = f"{data['trdDate']} {data['trdTime']}"
            dt = datetime.strptime(timestamp, "%Y%m%d %H%M%S%f")
            traded = data["trdQty"]
            order.status = STATUS_OES2VT[data["ordStatus"]]
            order.datetime = dt
            order.traded = traded
            self.gateway.on_order(order)

            trade = TradeData(
                orderid=order.orderid,
                symbol=order.symbol,
                datetime=order.datetime,
                exchange=order.exchange,
                direction=order.direction,
                offset=order.offset,
                price=data["trdPrice"] / 10000,
                tradeid=self._new_order_id(),
                volume=order.traded,
                gateway_name=self.gateway_name,
            )
            self.gateway.on_trade(trade)

    def onOrderReport(self, head: dict, data: dict) -> None:
        """"""
        sysid = data["clOrdId"]
        orderid = data["origClOrdId"]

        self.sys_local_ids[sysid] = orderid
        self.local_sys_ids[orderid] = sysid
        timestamp = f"{data['ordDate']} {data['ordCnfmTime']}"
        dt = datetime.strptime(timestamp, "%Y%m%d %H%M%S%f")
        status = STATUS_OES2VT[data["ordStatus"]]
        order = self.orders.get(orderid, None)
        if not order:
            symbol = data["securityId"]

            direction = DIRECTION_OES2VT.get(data["bsType"], None)
            offset = Offset.NONE
            if len(symbol) > 6:
                (direction, offset) = OPTION_DIRECTION_OES2VT[data["bsType"]]
            order = OrderData(
                orderid=orderid,
                symbol=symbol,
                exchange=EXCHANGE_OES2VT[data["mktId"]],
                type=ORDERTYPE_OES2VT[data["ordType"]],
                direction=direction,
                offset=offset,
                price=data["ordPrice"] / 10000,
                volume=data["ordQty"],
                status=status,
                datetime=dt,
                gateway_name=self.gateway_name
            )
            self.gateway.on_order(order)
        else:
            order.status = status
            order.datetime = dt
            self.gateway.on_order(order)

    def onQueryCashAsset(self, data: dict, head: dict, reqid: int) -> None:
        """"""
        account = AccountData(
            accountid=data["cashAcctId"],
            balance=data["currentTotalBal"],
            frozen=data["marginAmt"],
            gateway_name=self.gateway_name
        )
        self.gateway.on_account(account)

        self.userid = data["custId"]
        self.sendOptSettlementConfirm({"custId": self.userid})

        self.query_position()
        self.query_contract()

    def onQueryStock(self, data: dict, head: dict, reqid: int) -> None:
        """"""
        last = head["isEnd"]

        contract = ContractData(
            symbol=data["securityId"],
            exchange=EXCHANGE_OES2VT[data["mktId"]],
            product=PRODUCT_OES2VT[data["securityType"]],
            size=1,
            min_volume=data["buyQtyUnit"],
            name=data["securityName"],
            pricetick=data["priceTick"],
            gateway_name=self.gateway_name
        )
        self.gateway.on_contract(contract)
        SYMBOL_PRODCUT_MAP[contract.vt_symbol] = contract.product
        SYMBOL_NAME_MAP[contract.vt_symbol] = contract.name
        SYMBOL_PRICETICK_MAP[contract.vt_symbol] = contract.pricetick
        if last:
            self.gateway.write_log("证券合约查询完成")

    def onQueryOption(self, data: dict, head: dict, reqid: int) -> None:
        """"""
        last = head["isEnd"]
        contract = ContractData(
            symbol=data["securityId"],
            exchange=EXCHANGE_OES2VT[data["mktId"]],
            product=PRODUCT_OES2VT[data["securityType"]],
            size=1,
            min_volume=data["buyQtyUnit"],
            name=data["securityName"],
            pricetick=data["priceTick"] / 10000,
            option_strike=data["exercisePrice"] / 10000,
            option_underlying=data["underlyingSecurityId"],
            option_type=OPTIONTYPE_OES2VT[data["contractType"]],
            option_expiry=datetime.strptime(
                str(data["lastTradeDay"]), "%Y%m%d"
            ),
            gateway_name=self.gateway_name
        )
        contract.option_index = get_option_index(
            contract.option_strike, data["contractId"]
        )
        SYMBOL_PRODCUT_MAP[contract.vt_symbol] = contract.product
        SYMBOL_NAME_MAP[contract.vt_symbol] = contract.name
        SYMBOL_PRICETICK_MAP[contract.vt_symbol] = contract.pricetick
        self.gateway.on_contract(contract)
        if last:
            self.gateway.write_log("期权合约查询完成")

    def onQueryEtf(self, data: dict, head: dict, reqid: int) -> None:
        """"""
        pass

    def onSettlementConfirmedRpt(self, head: dict, data: dict) -> None:
        """"""
        error_no = data["rejReason"]
        if not error_no:
            self.gateway.write_log("期权账户结算单确认成功")

    def onQueryStkHolding(self, data: dict, head: dict, reqid: int) -> None:
        """"""
        pass

    def onQueryOptHolding(self, data: dict, head: dict, reqid: int) -> None:
        """"""
        last = head["isEnd"]

        self.investorid = data["invAcctId"][1:]

        pos = PositionData(
            symbol=data["securityId"],
            exchange=EXCHANGE_OES2VT[data["mktId"]],
            direction=DIRECTION_OES2VT[data["positionType"]],
            volume=data["sumQty"],
            frozen=data["closeFrzQty"],
            price=data["costPrice"] / 10000,
            gateway_name=self.gateway_name
        )
        self.gateway.on_position(pos)

        if last:
            self.gateway.write_log("期权持仓查询成功")

    def query_account(self) -> None:
        """"""
        self.reqid += 1
        self.queryCashAsset({}, self.reqid)

    def query_position(self) -> None:
        """"""
        self.reqid += 1
        req = {
            "custId": self.userid,
            "mktId": 0,
            "securityType": 0,
            "productType": 0
        }
        self.queryStkHolding(req, self.reqid)

        self.reqid += 1
        self.queryOptHolding(req, self.reqid)

    def query_contract(self) -> None:
        """"""
        self.reqid += 1
        stock_req = {
            "mktId": 0,
            "securityType": 0,
            "subSecurityType": 0
        }
        self.queryStock(stock_req, self.reqid)

        self.reqid += 1
        option_req = {
            "mktId": 0,
        }
        self.queryOption(option_req, self.reqid)

        self.reqid += 1
        self.queryEtf(option_req, self.reqid)

    def _new_trade_id(self) -> int:
        """"""
        self.trade_count += 1
        return self.trade_count

    def _new_order_id(self) -> int:
        """"""
        self.order_count += 1
        return self.order_count

    def connect(
        self,
        config_path,
        username,
        password,
        ord_server,
        rpt_server,
        hdd_serial,
        qry_server,
        customize_ip,
        customize_mac,
    ) -> None:
        """"""
        self.createTdApi(config_path, username, password)
        self.setCustomizedIpAndMac(customize_ip, customize_mac)
        self.setCustomizedDriverId(hdd_serial)
        self.setThreadEnvId(0)
        self.setThreadSubscribeEnvId(0)
        self.init()
        self.connect_date = int(datetime.now().strftime("%y%m%d%H%M"))

    def send_order(self, req: OrderRequest) -> str:
        """"""
        self.reqid += 1
        orderid = self.reqid

        oes_exchange = STOCK_EXCHANGE_VT2OES[req.exchange]
        oes_direction = DIRECTION_VT2OES[req.direction]
        oes_investorid = self.investorid

        # Check product
        if len(req.symbol) > 6:
            oes_exchange = OPTION_EXCHANGE_VT2OES[req.exchange]
            oes_direction = OPTION_DIRECTION_VT2OES[
                (req.direction, req.offset)
            ]

        # Check market
        if req.exchange == Exchange.SSE:
            oes_investorid = "A" + oes_investorid
        else:
            oes_investorid = "0" + oes_investorid

        oes_req = {
            "clSeqNo": self.reqid,
            "mktId": oes_exchange,
            "ordType": ORDERTYPE_VT2OES[req.type],
            "bsType": oes_direction,
            "invAcctId": oes_investorid,
            "securityId": req.symbol,
            "ordQty": int(req.volume),
            "ordPrice": int(req.price * 10000),
            "origClOrdId": orderid,
        }
        self.sendOrder(oes_req)
        order = req.create_order_data(orderid, self.gateway_name)
        self.gateway.on_order(order)

        self.orders[orderid] = order
        return order.vt_orderid

    def cancel_order(self, req: CancelRequest) -> None:
        """"""
        order = self.orders.get(req.orderid)
        if not order:
            self.gateway.write_log(f"撤单失败，委托号{req.orderid} 找不到对应的委托")
        else:
            self.reqid += 1

            oes_investorid = self.investorid
            oes_exchange = STOCK_EXCHANGE_VT2OES[req.exchange]

            # Check market
            if req.exchange == Exchange.SSE:
                oes_investorid = "A" + oes_investorid
            else:
                oes_investorid = "0" + oes_investorid

            # Check product
            if len(req.symbol) > 6:
                oes_exchange = OPTION_EXCHANGE_VT2OES[req.exchange]

            oes_req = {
                "clSeqNo": self.reqid,
                "mktId": oes_exchange,
                "invAcctId": oes_investorid,
                "securityId": order.symbol,
                "origClEnvId": 0,
                "origClSeqNo": int(req.orderid),
            }
            self.sendCancelOrder(oes_req)


def get_option_index(strike_price: float, exchange_instrument_id: str) -> str:
    """"""
    exchange_instrument_id = exchange_instrument_id.replace(" ", "")

    if "M" in exchange_instrument_id:
        n = exchange_instrument_id.index("M")
    elif "A" in exchange_instrument_id:
        n = exchange_instrument_id.index("A")
    elif "B" in exchange_instrument_id:
        n = exchange_instrument_id.index("B")
    else:
        return str(strike_price)

    index = exchange_instrument_id[n:]
    option_index = f"{strike_price:.3f}-{index}"

    return option_index


mydir = os.path.dirname(__file__)
config_template_path = os.path.join(mydir, "config_template.ini")
with open(config_template_path, "rt", encoding='utf-8') as f:
    config_template = f.read()
