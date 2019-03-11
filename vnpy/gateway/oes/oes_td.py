from dataclasses import dataclass
from datetime import datetime, timedelta, timezone
from gettext import gettext as _
from threading import Lock, Thread
# noinspection PyUnresolvedReferences
from typing import Any, Callable, Dict

from vnpy.api.oes.vnoes import OesApiClientEnvT, OesApi_DestoryAll, OesApi_InitAllByConvention, \
    OesApi_IsValidOrdChannel, OesApi_IsValidQryChannel, OesApi_IsValidRptChannel, OesApi_LogoutAll, \
    OesApi_QueryCashAsset, OesApi_QueryOptHolding, OesApi_QueryOption, OesApi_QueryOrder, \
    OesApi_QueryStkHolding, OesApi_QueryStock, OesApi_SendOrderCancelReq, OesApi_SendOrderReq, \
    OesApi_SetThreadPassword, OesApi_SetThreadUsername, OesApi_WaitReportMsg, OesOrdCancelReqT, \
    OesOrdCnfmT, OesOrdRejectT, OesOrdReqT, OesQryCashAssetFilterT, OesQryCursorT, \
    OesQryOptionFilterT, OesQryOrdFilterT, OesQryStkHoldingFilterT, OesQryStockFilterT, \
    OesRspMsgBodyT, OesStockBaseInfoT, OesTrdCnfmT, SGeneralClientChannelT, SMSG_PROTO_BINARY, \
    SMsgHeadT, SPlatform_IsNegEpipe, cast, eOesBuySellTypeT, eOesMarketIdT, \
    eOesMsgTypeT, eOesOrdStatusT, eOesOrdTypeShT, eOesOrdTypeSzT

from vnpy.gateway.oes.error_code import error_to_str
from vnpy.trader.constant import Direction, Exchange, Offset, PriceType, Product, Status
from vnpy.trader.gateway import BaseGateway
from vnpy.trader.object import AccountData, CancelRequest, ContractData, OrderData, OrderRequest, \
    PositionData, TradeData

EXCHANGE_OES2VT = {
    eOesMarketIdT.OES_MKT_SH_ASHARE: Exchange.SSE,
    eOesMarketIdT.OES_MKT_SZ_ASHARE: Exchange.SZSE,
    eOesMarketIdT.OES_MKT_SH_OPTION: Exchange.SHFE,
}
EXCHANGE_VT2OES = {v: k for k, v in EXCHANGE_OES2VT.items()}

PRODUCT_OES2VT = {
    eOesMarketIdT.OES_MKT_SH_ASHARE: Product.EQUITY,
    eOesMarketIdT.OES_MKT_SZ_ASHARE: Product.EQUITY,
    eOesMarketIdT.OES_MKT_SH_OPTION: Product.FUTURES,
}

# only limit price can match, all other price types are not perfectly match.
ORDER_TYPE_VT2OES = {
    (Exchange.SSE, PriceType.LIMIT): eOesOrdTypeShT.OES_ORD_TYPE_SH_LMT,
    (Exchange.SZSE, PriceType.LIMIT): eOesOrdTypeSzT.OES_ORD_TYPE_SZ_LMT,
}

BUY_SELL_TYPE_VT2OES = {
    (Exchange.SSE, Offset.OPEN, Direction.LONG): eOesBuySellTypeT.OES_BS_TYPE_BUY,
    (Exchange.SSE, Offset.OPEN, Direction.SHORT): eOesBuySellTypeT.OES_BS_TYPE_SELL,
    (Exchange.SSE, Offset.OPEN, Direction.NET): eOesBuySellTypeT.OES_BS_TYPE_BUY,
    (Exchange.SSE, Offset.CLOSE, Direction.LONG): eOesBuySellTypeT.OES_BS_TYPE_SELL,
    (Exchange.SSE, Offset.CLOSE, Direction.SHORT): eOesBuySellTypeT.OES_BS_TYPE_BUY,
    (Exchange.SSE, Offset.CLOSE, Direction.NET): eOesBuySellTypeT.OES_BS_TYPE_SELL,

    (Exchange.SZSE, Offset.OPEN, Direction.LONG): eOesBuySellTypeT.OES_BS_TYPE_BUY,
    (Exchange.SZSE, Offset.OPEN, Direction.SHORT): eOesBuySellTypeT.OES_BS_TYPE_SELL,
    (Exchange.SZSE, Offset.OPEN, Direction.NET): eOesBuySellTypeT.OES_BS_TYPE_BUY,
    (Exchange.SZSE, Offset.CLOSE, Direction.LONG): eOesBuySellTypeT.OES_BS_TYPE_SELL,
    (Exchange.SZSE, Offset.CLOSE, Direction.SHORT): eOesBuySellTypeT.OES_BS_TYPE_BUY,
    (Exchange.SZSE, Offset.CLOSE, Direction.NET): eOesBuySellTypeT.OES_BS_TYPE_SELL,

    (Exchange.SHFE, Offset.OPEN, Direction.LONG): eOesBuySellTypeT.OES_BS_TYPE_BUY_OPEN,
    (Exchange.SHFE, Offset.OPEN, Direction.SHORT): eOesBuySellTypeT.OES_BS_TYPE_SELL_OPEN,
    (Exchange.SHFE, Offset.OPEN, Direction.NET): eOesBuySellTypeT.OES_BS_TYPE_BUY_OPEN,
    (Exchange.SHFE, Offset.CLOSE, Direction.LONG): eOesBuySellTypeT.OES_BS_TYPE_BUY_CLOSE,
    (Exchange.SHFE, Offset.CLOSE, Direction.SHORT): eOesBuySellTypeT.OES_BS_TYPE_SELL_CLOSE,
    (Exchange.SHFE, Offset.CLOSE, Direction.NET): eOesBuySellTypeT.OES_BS_TYPE_BUY_CLOSE,
    # todo: eOesBuySellTypeT.OES_BS_TYPE_OPTION_EXERCISE == 行权
}

STATUS_OES2VT = {
    eOesOrdStatusT.OES_ORD_STATUS_NEW: Status.NOTTRADED,
    eOesOrdStatusT.OES_ORD_STATUS_DECLARED: Status.NOTTRADED,
    eOesOrdStatusT.OES_ORD_STATUS_PARTIALLY_FILLED: Status.PARTTRADED,
    eOesOrdStatusT.OES_ORD_STATUS_FILLED: Status.ALLTRADED,

    eOesOrdStatusT.OES_ORD_STATUS_CANCEL_DONE: Status.CANCELLED,
    eOesOrdStatusT.OES_ORD_STATUS_PARTIALLY_CANCELED: Status.CANCELLED,
    eOesOrdStatusT.OES_ORD_STATUS_CANCELED: Status.CANCELLED,

    eOesOrdStatusT.OES_ORD_STATUS_INVALID_OES: Status.REJECTED,
    eOesOrdStatusT.OES_ORD_STATUS_INVALID_SH_F: Status.REJECTED,
    eOesOrdStatusT.OES_ORD_STATUS_INVALID_SH_E: Status.REJECTED,
    eOesOrdStatusT.OES_ORD_STATUS_INVALID_SH_COMM: Status.REJECTED,
    eOesOrdStatusT.OES_ORD_STATUS_INVALID_SZ_F: Status.REJECTED,
    eOesOrdStatusT.OES_ORD_STATUS_INVALID_SZ_E: Status.REJECTED,
    eOesOrdStatusT.OES_ORD_STATUS_INVALID_SZ_REJECT: Status.REJECTED,
    eOesOrdStatusT.OES_ORD_STATUS_INVALID_SZ_TRY_AGAIN: Status.REJECTED,
}

bjtz = timezone(timedelta(hours=8))


@dataclass
class InternalOrder:
    order_id: int = None
    vt_order: OrderData = None


def parse_oes_datetime(date: int, time: int):
    """convert oes datetime to python datetime"""
    # YYYYMMDD
    year = int(date / 10000)
    month = int((date % 10000) / 100)
    day = int(date % 100)

    # HHMMSSsss
    hour = int(time / 10000000)
    minute = int((time % 10000000) / 100000)
    sec = int((time % 100000) / 1000)
    mill = int(time % 1000)
    return datetime(year, month, day, hour, minute, sec, mill * 1000, tzinfo=bjtz)


class OesTdMessageLoop:

    def __init__(self,
                 gateway: BaseGateway,
                 env: OesApiClientEnvT,
                 td: "OesTdApi"
                 ):
        """"""
        self.gateway = gateway

        self._env = env
        self._td = td

        self._alive = False
        self._th = Thread(target=self._message_loop)

        self.message_handlers: Dict[int, Callable[[dict], None]] = {
            eOesMsgTypeT.OESMSG_RPT_BUSINESS_REJECT: self.on_order_rejected,
            eOesMsgTypeT.OESMSG_RPT_ORDER_INSERT: self.on_order_inserted,
            eOesMsgTypeT.OESMSG_RPT_ORDER_REPORT: self.on_order_report,
            eOesMsgTypeT.OESMSG_RPT_TRADE_REPORT: self.on_trade_report,
            eOesMsgTypeT.OESMSG_RPT_STOCK_HOLDING_VARIATION: self.on_stock_holding,
            eOesMsgTypeT.OESMSG_RPT_OPTION_HOLDING_VARIATION: self.on_option_holding,
            eOesMsgTypeT.OESMSG_RPT_CASH_ASSET_VARIATION: self.on_cash,

            eOesMsgTypeT.OESMSG_RPT_REPORT_SYNCHRONIZATION: lambda x: 1,
            eOesMsgTypeT.OESMSG_SESS_HEARTBEAT: lambda x: 1,
        }

    def start(self):
        """"""
        self._alive = True
        self._th.start()

    def stop(self):
        """"""
        self._alive = False

    def join(self):
        """"""
        self._th.join()

    def reconnect(self):
        """"""
        self.gateway.write_log(_("正在尝试重新连接到交易服务器。"))
        self._td.connect()

    def _on_message(self, session_info: SGeneralClientChannelT,
                    head: SMsgHeadT,
                    body: Any):
        """"""
        if session_info.protocolType == SMSG_PROTO_BINARY:
            b = cast.toOesRspMsgBodyT(body)
            if head.msgId in self.message_handlers:
                self.message_handlers[head.msgId](b)
            else:
                self.gateway.write_log(
                    f"unknown msg id : {head.msgId}   {eOesMsgTypeT(head.msgId)}")
        else:
            self.gateway.write_log(f"unknown prototype : {session_info.protocolType}")
        return 1

    def _message_loop(self):
        """"""
        rpt_channel = self._env.rptChannel
        timeout_ms = 1000
        is_disconnected = SPlatform_IsNegEpipe

        while self._alive:
            ret = OesApi_WaitReportMsg(rpt_channel,
                                       timeout_ms,
                                       self._on_message)
            if ret < 0:
                # if is_timeout(ret):
                #     pass  # just no message
                if is_disconnected(ret):
                    self.gateway.write_log(_("与交易服务器的连接已断开。"))
                    while self._alive and not self.reconnect():
                        pass
        return

    def on_order_rejected(self, d: OesRspMsgBodyT):
        """"""
        error_code = d.rptMsg.rptHead.ordRejReason
        error_string = error_to_str(error_code)
        data: OesOrdRejectT = d.rptMsg.rptBody.ordRejectRsp
        if not data.origClSeqNo:
            i = self._td.get_order(data.clSeqNo)
            vt_order = i.vt_order

            if vt_order == Status.ALLTRADED:
                return

            vt_order.status = Status.REJECTED

            self.gateway.on_order(vt_order)
            self.gateway.write_log(
                f"Order: {vt_order.vt_symbol}-{vt_order.vt_orderid} Code: {error_code} Rejected: {error_string}")
        else:
            self.gateway.write_log(f"撤单失败，订单号： {data.origClSeqNo}。原因：{error_string}")

    def on_order_inserted(self, d: OesRspMsgBodyT):
        """"""
        data = d.rptMsg.rptBody.ordInsertRsp

        if not data.origClSeqNo:
            i = self._td.get_order(data.clSeqNo)
        else:
            i = self._td.get_order(data.origClSeqNo)
        vt_order = i.vt_order
        vt_order.status = STATUS_OES2VT[data.ordStatus]
        vt_order.volume = data.ordQty
        vt_order.traded = data.cumQty
        vt_order.time = parse_oes_datetime(data.ordDate, data.ordTime)

        self.gateway.on_order(vt_order)

    def on_order_report(self, d: OesRspMsgBodyT):
        """"""
        data: OesOrdCnfmT = d.rptMsg.rptBody.ordCnfm

        if not data.origClSeqNo:
            i = self._td.get_order(data.clSeqNo)
        else:
            i = self._td.get_order(data.origClSeqNo)
        vt_order = i.vt_order

        vt_order.status = STATUS_OES2VT[data.ordStatus]
        vt_order.volume = data.ordQty
        vt_order.traded = data.cumQty
        vt_order.time = parse_oes_datetime(data.ordDate, data.ordCnfmTime)

        self.gateway.on_order(vt_order)

    def on_trade_report(self, d: OesRspMsgBodyT):
        """"""
        data: OesTrdCnfmT = d.rptMsg.rptBody.trdCnfm

        i = self._td.get_order(data.clSeqNo)
        vt_order = i.vt_order
        # vt_order.status = STATUS_OES2VT[data.ordStatus]

        trade = TradeData(
            gateway_name=self.gateway.gateway_name,
            symbol=data.securityId,
            exchange=EXCHANGE_OES2VT[data.mktId],
            orderid=data.userInfo,
            tradeid=data.exchTrdNum,
            direction=vt_order.direction,
            offset=vt_order.offset,
            price=data.trdPrice / 10000,
            volume=data.trdQty,
            time=parse_oes_datetime(data.trdDate, data.trdTime)
        )
        vt_order.status = STATUS_OES2VT[data.ordStatus]
        vt_order.traded = data.cumQty
        vt_order.time = parse_oes_datetime(data.trdDate, data.trdTime)
        self.gateway.on_trade(trade)
        self.gateway.on_order(vt_order)

    def on_option_holding(self, d: OesRspMsgBodyT):
        """"""
        pass

    def on_stock_holding(self, d: OesRspMsgBodyT):
        """"""
        data = d.rptMsg.rptBody.stkHoldingRpt
        position = PositionData(
            gateway_name=self.gateway.gateway_name,
            symbol=data.securityId,
            exchange=EXCHANGE_OES2VT[data.mktId],
            direction=Direction.NET,
            volume=data.sumHld,
            frozen=data.lockHld,  # todo: to verify
            price=data.costPrice / 10000,
            # pnl=data.costPrice - data.originalCostAmt,
            pnl=0,
            yd_volume=data.originalHld,
        )
        self.gateway.on_position(position)

    def on_cash(self, d: OesRspMsgBodyT):
        """"""
        data = d.rptMsg.rptBody.cashAssetRpt

        balance = data.currentTotalBal
        availiable = data.currentAvailableBal
        # drawable = data.currentDrawableBal
        account_id = data.cashAcctId
        account = AccountData(
            gateway_name=self.gateway.gateway_name,
            accountid=account_id,
            balance=balance,
            frozen=balance - availiable,
        )
        self.gateway.on_account(account)
        return 1


class OesTdApi:

    def __init__(self, gateway: BaseGateway):
        """"""
        self.config_path: str = None
        self.username: str = ''
        self.password: str = ''
        self.gateway = gateway

        self._env = OesApiClientEnvT()

        self._message_loop = OesTdMessageLoop(gateway,
                                              self._env,
                                              self)

        self._last_seq_lock = Lock()
        self._last_seq_index = 1000000  # 0 has special manning for oes

        self._orders: Dict[int, InternalOrder] = {}

    def connect(self):
        """Connect to trading server.
        :note set config_path before calling this function
        """
        OesApi_SetThreadUsername(self.username)
        OesApi_SetThreadPassword(self.password)

        config_path = self.config_path
        if not OesApi_InitAllByConvention(self._env, config_path, -1, self._last_seq_index):
            return False
        self._last_seq_index = max(self._last_seq_index, self._env.ordChannel.lastOutMsgSeq + 1)

        if not OesApi_IsValidOrdChannel(self._env.ordChannel):
            return False
        if not OesApi_IsValidQryChannel(self._env.qryChannel):
            return False
        if not OesApi_IsValidRptChannel(self._env.rptChannel):
            return False
        return True

    def start(self):
        """"""
        self._message_loop.start()

    def stop(self):
        """"""
        self._message_loop.stop()
        OesApi_LogoutAll(self._env, True)
        OesApi_DestoryAll(self._env)

    def join(self):
        """"""
        self._message_loop.join()

    def _get_new_seq_index(self):
        """"""
        with self._last_seq_lock:
            index = self._last_seq_index
            self._last_seq_index += 1
            return index

    def query_account(self):
        """"""
        OesApi_QueryCashAsset(self._env.qryChannel,
                              OesQryCashAssetFilterT(),
                              self.on_query_asset
                              )

    def on_query_asset(self,
                       session_info: SGeneralClientChannelT,
                       head: SMsgHeadT,
                       body: Any,
                       cursor: OesQryCursorT,
                       ):
        """"""
        data = cast.toOesCashAssetItemT(body)
        balance = data.currentTotalBal / 10000
        availiable = data.currentAvailableBal / 10000
        # drawable = data.currentDrawableBal
        account_id = data.cashAcctId
        account = AccountData(
            gateway_name=self.gateway.gateway_name,
            accountid=account_id,
            balance=balance,
            frozen=balance - availiable,
        )
        self.gateway.on_account(account)
        return 1

    def query_stock(self, ) -> bool:
        """"""
        f = OesQryStockFilterT()
        ret = OesApi_QueryStock(self._env.qryChannel, f, self.on_query_stock)
        return ret >= 0

    def on_query_stock(self,
                       session_info: SGeneralClientChannelT,
                       head: SMsgHeadT,
                       body: Any,
                       cursor: OesQryCursorT,
                       ):
        """"""
        data: OesStockBaseInfoT = cast.toOesStockItemT(body)
        contract = ContractData(
            gateway_name=self.gateway.gateway_name,
            symbol=data.securityId,
            exchange=EXCHANGE_OES2VT[data.mktId],
            name=data.securityName,
            product=PRODUCT_OES2VT[data.mktId],
            size=data.buyQtyUnit,
            pricetick=data.priceUnit,
        )
        self.gateway.on_contract(contract)
        return 1

    def query_option(self) -> bool:
        """"""
        f = OesQryOptionFilterT()
        ret = OesApi_QueryOption(self._env.qryChannel,
                                 f,
                                 self.on_query_option
                                 )
        return ret >= 0

    def on_query_option(self,
                        session_info: SGeneralClientChannelT,
                        head: SMsgHeadT,
                        body: Any,
                        cursor: OesQryCursorT,
                        ):
        """"""
        data = cast.toOesOptionItemT(body)
        contract = ContractData(
            gateway_name=self.gateway.gateway_name,
            symbol=data.securityId,
            exchange=EXCHANGE_OES2VT[data.mktId],
            name=data.securityName,
            product=PRODUCT_OES2VT[data.mktId],
            size=data.roundLot,
            pricetick=data.tickSize,
        )
        self.gateway.on_contract(contract)
        return 1

    def query_stock_holding(self) -> bool:
        """"""
        f = OesQryStkHoldingFilterT()
        ret = OesApi_QueryStkHolding(self._env.qryChannel,
                                     f,
                                     self.on_query_stock_holding
                                     )
        return ret >= 0

    def on_query_stock_holding(self,
                               session_info: SGeneralClientChannelT,
                               head: SMsgHeadT,
                               body: Any,
                               cursor: OesQryCursorT,
                               ):
        """"""
        data = cast.toOesStkHoldingItemT(body)

        position = PositionData(
            gateway_name=self.gateway.gateway_name,
            symbol=data.securityId,
            exchange=EXCHANGE_OES2VT[data.mktId],
            direction=Direction.NET,
            volume=data.sumHld,
            frozen=data.lockHld,
            price=data.costPrice / 10000,
            # pnl=data.costPrice - data.originalCostAmt,
            pnl=0,  # todo: oes只提供日初持仓价格信息，不提供最初持仓价格信息，所以pnl只有当日的
            yd_volume=data.originalHld,
        )
        self.gateway.on_position(position)
        return 1

    def query_option_holding(self) -> bool:
        """"""
        f = OesQryStkHoldingFilterT()
        f.mktId = eOesMarketIdT.OES_MKT_ID_UNDEFINE
        f.userInfo = 0
        ret = OesApi_QueryOptHolding(self._env.qryChannel,
                                     f,
                                     self.on_query_holding
                                     )
        return ret >= 0

    def on_query_holding(self,
                         session_info: SGeneralClientChannelT,
                         head: SMsgHeadT,
                         body: Any,
                         cursor: OesQryCursorT,
                         ):
        """"""
        data = cast.toOesOptHoldingItemT(body)

        # 权利
        pos_long = PositionData(
            gateway_name=self.gateway.gateway_name,
            symbol=data.securityId,
            exchange=EXCHANGE_OES2VT[data.mktId],
            direction=Direction.LONG,
            volume=data.hldA,
            frozen=data.hldRA,
            price=0,
            # pnl=data.costPrice - data.originalCostAmt,
            pnl=0,
            yd_volume=0,
        )
        self.gateway.on_position(pos_long)

        # 义务
        pos_short = PositionData(
            gateway_name=self.gateway.gateway_name,
            symbol=data.securityId,
            exchange=EXCHANGE_OES2VT[data.mktId],
            direction=Direction.SHORT,
            volume=data.hldB,
            frozen=data.hldRB,
            price=0,
            # pnl=data.costPrice - data.originalCostAmt,
            pnl=0,
            yd_volume=0,
        )
        self.gateway.on_position(pos_short)

        return 1

    def query_contracts(self):
        """"""
        self.query_stock()
        # self.query_option()
        # self.query_issue()

    def query_position(self):
        """"""
        self.query_stock_holding()
        self.query_option_holding()

    def send_order(self, vt_req: OrderRequest):
        """"""
        seq_id = self._get_new_seq_index()
        order_id = seq_id

        oes_req = OesOrdReqT()
        oes_req.clSeqNo = seq_id
        oes_req.mktId = EXCHANGE_VT2OES[vt_req.exchange]
        oes_req.ordType = ORDER_TYPE_VT2OES[(vt_req.exchange, vt_req.price_type)]
        oes_req.bsType = BUY_SELL_TYPE_VT2OES[(vt_req.exchange, vt_req.offset, vt_req.direction)]
        oes_req.invAcctId = ""
        oes_req.securityId = vt_req.symbol
        oes_req.ordQty = int(vt_req.volume)
        oes_req.ordPrice = int(vt_req.price * 10000)
        oes_req.origClOrdId = order_id

        order = vt_req.create_order_data(str(order_id), self.gateway.gateway_name)
        order.direction = Direction.NET  # fix direction into NET: stock only
        self.save_order(order_id, order)

        ret = OesApi_SendOrderReq(self._env.ordChannel,
                                  oes_req
                                  )

        if ret >= 0:
            self.gateway.on_order(order)
        else:
            self.gateway.write_log("Failed to send_order!")

        return order.vt_orderid

    def cancel_order(self, vt_req: CancelRequest):
        """"""
        seq_id = self._get_new_seq_index()

        oes_req = OesOrdCancelReqT()
        order_id = int(vt_req.orderid)
        oes_req.mktId = EXCHANGE_VT2OES[vt_req.exchange]

        oes_req.clSeqNo = seq_id
        oes_req.origClSeqNo = order_id
        oes_req.invAcctId = ""
        oes_req.securityId = vt_req.symbol
        OesApi_SendOrderCancelReq(self._env.ordChannel,
                                  oes_req)

    def query_order(self, internal_order: InternalOrder) -> bool:
        """"""
        f = OesQryOrdFilterT()
        f.mktId = EXCHANGE_VT2OES[internal_order.vt_order.exchange]
        f.clSeqNo = internal_order.order_id
        ret = OesApi_QueryOrder(self._env.qryChannel,
                                f,
                                self.on_query_order
                                )
        return ret >= 0

    def on_query_order(self,
                       session_info: SGeneralClientChannelT,
                       head: SMsgHeadT,
                       body: Any,
                       cursor: OesQryCursorT):
        """"""
        data: OesOrdCnfmT = cast.toOesOrdItemT(body)

        i = self.get_order(data.clSeqNo)
        vt_order = i.vt_order
        vt_order.status = STATUS_OES2VT[data.ordStatus]
        vt_order.volume = data.ordQty - data.canceledQty
        vt_order.traded = data.cumQty
        self.gateway.on_order(vt_order)
        return 1

    def query_orders(self) -> bool:
        """"""
        f = OesQryOrdFilterT()
        ret = OesApi_QueryOrder(self._env.qryChannel,
                                f,
                                self.on_query_orders
                                )
        return ret >= 0

    def on_query_orders(self,
                        session_info: SGeneralClientChannelT,
                        head: SMsgHeadT,
                        body: Any,
                        cursor: OesQryCursorT,
                        ):
        """"""
        data: OesOrdCnfmT = cast.toOesOrdItemT(body)
        try:
            i = self.get_order(data.clSeqNo)
            vt_order = i.vt_order
            vt_order.status = STATUS_OES2VT[data.ordStatus]
            vt_order.volume = data.ordQty - data.canceledQty
            vt_order.traded = data.cumQty
            self.gateway.on_order(vt_order)
        except KeyError:
            # order_id = self.order_manager.new_remote_id()
            order_id = data.clSeqNo

            if data.bsType == eOesBuySellTypeT.OES_BS_TYPE_BUY:
                offset = Offset.OPEN
            else:
                offset = Offset.CLOSE

            vt_order = OrderData(
                gateway_name=self.gateway.gateway_name,
                symbol=data.securityId,
                exchange=EXCHANGE_OES2VT[data.mktId],
                orderid=order_id if order_id else data.origClSeqNo,  # generated id
                direction=Direction.NET,
                offset=offset,
                price=data.ordPrice / 10000,
                volume=data.ordQty - data.canceledQty,
                traded=data.cumQty,
                status=STATUS_OES2VT[data.ordStatus],

                # this time should be generated automatically or by a static function
                time=datetime.utcnow().isoformat(),
            )
            self.save_order(order_id, vt_order)
            self.gateway.on_order(vt_order)
        return 1

    def save_order(self, order_id: int, order: OrderData):
        """"""
        self._orders[order_id] = InternalOrder(
            order_id=order_id,
            vt_order=order,
        )

    def get_order(self, order_id: int):
        """"""
        return self._orders[order_id]
