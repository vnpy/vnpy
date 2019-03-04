from dataclasses import dataclass
from datetime import datetime
from threading import Thread
# noinspection PyUnresolvedReferences
from typing import Any, Callable, Dict, Tuple

from vnoes import OesApiClientEnvT, OesApi_DestoryAll, OesApi_InitAllByConvention, \
    OesApi_IsValidOrdChannel, OesApi_IsValidQryChannel, OesApi_IsValidRptChannel, OesApi_LogoutAll, \
    OesApi_QueryCashAsset, OesApi_QueryEtf, OesApi_QueryIssue, OesApi_QueryOptHolding, \
    OesApi_QueryOption, OesApi_QueryOrder, OesApi_QueryStkHolding, OesApi_QueryStock, \
    OesApi_SendOrderCancelReq, OesApi_SendOrderReq, OesApi_WaitReportMsg, OesOrdCancelReqT, \
    OesOrdCnfmT, OesOrdRejectT, OesOrdReqT, OesQryCashAssetFilterT, OesQryCursorT, OesQryEtfFilterT, \
    OesQryIssueFilterT, OesQryOptionFilterT, OesQryOrdFilterT, OesQryStkHoldingFilterT, \
    OesQryStockFilterT, OesRspMsgBodyT, OesStockBaseInfoT, OesTrdCnfmT, SGeneralClientChannelT, \
    SMSG_PROTO_BINARY, SMsgHeadT, SPlatform_IsNegEpipe, SPlatform_IsNegEtimeout, cast, \
    eOesBuySellTypeT, eOesMarketIdT, eOesMsgTypeT, eOesOrdStatusT, eOesOrdTypeShT, eOesOrdTypeSzT

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


@dataclass
class InternalOrder:
    order_id: int = None
    vt_order: OrderData = None
    req_data: OesOrdReqT = None
    rpt_data: OesOrdCnfmT = None


class OrderManager:

    def __init__(self):
        self.last_order_id = 100000000
        self._orders: Dict[int, InternalOrder] = {}

        # key tuple: seqNo, ordId, envId, userInfo
        self._remote_created_orders: Dict[Tuple[int, int, int, int], InternalOrder] = {}

    @staticmethod
    def hash_remote_order(data):
        key = (data.origClSeqNo, data.origClOrdId, data.origClEnvId, data.userInfo)
        return key

    @staticmethod
    def hash_remote_trade(data: OesTrdCnfmT):
        key = (data.clSeqNo, data.clOrdId, data.clEnvId, data.userInfo)
        return key

    def new_local_id(self):
        id = self.last_order_id
        self.last_order_id += 1
        return id

    def new_remote_id(self):
        id = self.last_order_id
        self.last_order_id += 1
        return id

    def save_local_created(self, order_id: int, order: OrderData, oes_req: OesOrdReqT):
        self._orders[order_id] = InternalOrder(
            order_id=order_id,
            vt_order=order,
            req_data=oes_req
        )

    def save_remote_created(self, order_id: int, vt_order: OrderData, data: OesOrdCnfmT):
        internal_order = InternalOrder(
            order_id=order_id,
            vt_order=vt_order,
            rpt_data=data
        )
        self._orders[order_id] = internal_order
        key = self.hash_remote_order(data)
        self._remote_created_orders[key] = internal_order

    def get_from_order_id(self, id: int):
        return self._orders[id]

    def get_remote_created_order_from_oes_data(self, data):
        """
        :return: internal_order if succeed else None, will check only remote created order
        """
        try:
            key = self.hash_remote_order(data)
        except AttributeError:
            key = self.hash_remote_trade(data)
        try:
            return self._remote_created_orders[key]
        except KeyError:
            return None

    def get_from_oes_data(self, data):
        try:
            key = self.hash_remote_order(data)
        except AttributeError:
            key = self.hash_remote_trade(data)
        try:
            return self._remote_created_orders[key]
        except KeyError:
            order_id = key[3]
            return self._orders[order_id]


class OesTdMessageLoop:

    def __init__(self,
                 gateway: BaseGateway,
                 env: OesApiClientEnvT,
                 order_manager: OrderManager,
                 td: "OesTdApi"
                 ):
        self.gateway = gateway
        self.env = env
        self.order_manager = order_manager
        self.td = td

        self.alive = False
        self.th = Thread(target=self.message_loop)

        self.message_handlers: Dict[int, Callable[[dict], None]] = {
            eOesMsgTypeT.OESMSG_RPT_BUSINESS_REJECT: self.on_reject,
            eOesMsgTypeT.OESMSG_RPT_ORDER_INSERT: self.on_order_inserted,
            eOesMsgTypeT.OESMSG_RPT_ORDER_REPORT: self.on_order_report,
            eOesMsgTypeT.OESMSG_RPT_TRADE_REPORT: self.on_trade_report,
            eOesMsgTypeT.OESMSG_RPT_STOCK_HOLDING_VARIATION: self.on_stock_holding,
            eOesMsgTypeT.OESMSG_RPT_OPTION_HOLDING_VARIATION: self.on_option_holding,
            eOesMsgTypeT.OESMSG_RPT_CASH_ASSET_VARIATION: self.on_cash,
            eOesMsgTypeT.OESMSG_SESS_HEARTBEAT: lambda x: x,
        }

    def start(self):
        self.alive = True
        self.th.start()

    def join(self):
        self.th.join()

    def on_message(self, session_info: SGeneralClientChannelT,
                   head: SMsgHeadT,
                   body: Any):
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

    def message_loop(self):
        rtp_channel = self.env.rptChannel
        timeout_ms = 1000
        is_timeout = SPlatform_IsNegEtimeout
        is_disconnected = SPlatform_IsNegEpipe

        while self.alive:
            ret = OesApi_WaitReportMsg(rtp_channel,
                                       timeout_ms,
                                       self.on_message)
            if ret < 0:
                if is_timeout(ret):
                    pass
                if is_disconnected(ret):
                    # todo: handle disconnected
                    self.alive = False
                    break
            pass
        return

    def on_reject(self, d: OesRspMsgBodyT):
        error_code = d.rptMsg.rptHead.ordRejReason
        error_string = error_to_str(error_code)
        data: OesOrdRejectT = d.rptMsg.rptBody.ordRejectRsp
        i = self.order_manager.get_from_oes_data(data)
        vt_order = i.vt_order

        if vt_order == Status.ALLTRADED:
            return

        vt_order.status = Status.REJECTED

        self.gateway.on_order(vt_order)
        self.gateway.write_log(
            f"Order: {vt_order.vt_symbol}-{vt_order.vt_orderid} Code: {error_code} Rejected: {error_string}")

    def on_order_inserted(self, d: OesRspMsgBodyT):
        data = d.rptMsg.rptBody.ordInsertRsp

        i = self.order_manager.get_from_oes_data(data)
        vt_order = i.vt_order
        vt_order.status = STATUS_OES2VT[data.ordStatus]
        vt_order.volume = data.ordQty - data.canceledQty
        vt_order.traded = data.cumQty

        self.gateway.on_order(vt_order)

    def on_order_report(self, d: OesRspMsgBodyT):
        data: OesOrdCnfmT = d.rptMsg.rptBody.ordCnfm

        i = self.order_manager.get_from_oes_data(data)
        vt_order = i.vt_order
        vt_order.status = STATUS_OES2VT[data.ordStatus]
        vt_order.volume = data.ordQty - data.canceledQty
        vt_order.traded = data.cumQty
        self.gateway.on_order(vt_order)

    def on_trade_report(self, d: OesRspMsgBodyT):
        data: OesTrdCnfmT = d.rptMsg.rptBody.trdCnfm

        i = self.order_manager.get_from_oes_data(data)
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
            time=datetime.utcnow().isoformat()  # strict
        )
        self.gateway.on_trade(trade)

        # hack :
        # Sometimes order_report is not received after a trade is received.
        # (only trade msg but no order msg)
        # This cause a problem  that vt_order.traded stay 0 after a trade, which is a error state.
        # So we have to query new status of order for every receiving of trade.
        # BUT
        # Oes have no async call to query order only.
        # And calling sync function here will slow down vnpy.
        # So we queue it into another thread.
        self.td.schedule_query_order(i)

    def on_option_holding(self, d: OesRspMsgBodyT):
        pass

    def on_stock_holding(self, d: OesRspMsgBodyT):
        data = d.rptMsg.rptBody.stkHoldingRpt
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

    def on_cash(self, d: OesRspMsgBodyT):
        data = d.rptMsg.rptBody.cashAssetRpt

        balance = data.currentTotalBal
        availiable = data.currentAvailableBal
        # drawable = data.currentDrawableBal
        account_id = data.custId
        account = AccountData(
            gateway_name=self.gateway.gateway_name,
            accountid=account_id,
            balance=balance,
            frozen=balance - availiable,
        )
        self.gateway.on_account(account)
        return 1

    def stop(self):
        self.alive = False


class OesTdApi:

    def __init__(self, gateway: BaseGateway):
        self.gateway = gateway
        self.env = OesApiClientEnvT()

        self.order_manager = OrderManager()
        self.message_loop = OesTdMessageLoop(gateway,
                                             self.env,
                                             self.order_manager,
                                             self)

        self.account_id = None
        self.last_seq_index = 1  # 0 has special manning for oes

    def connect(self, config_path: str):
        if not OesApi_InitAllByConvention(self.env, config_path, -1, self.last_seq_index):
            pass
        self.last_seq_index = self.env.ordChannel.lastOutMsgSeq + 1

        if not OesApi_IsValidOrdChannel(self.env.ordChannel):
            pass
        if not OesApi_IsValidQryChannel(self.env.qryChannel):
            pass
        if not OesApi_IsValidRptChannel(self.env.rptChannel):
            pass

    def start(self):
        self.message_loop.start()

    def stop(self):
        self.message_loop.stop()
        if not OesApi_LogoutAll(self.env, True):
            pass  # doc for this function is error
        if not OesApi_DestoryAll(self.env):
            pass  # doc for this function is error

    def join(self):
        self.message_loop.join()

    def query_account(self) -> bool:
        return self.query_cash_asset()

    def query_cash_asset(self) -> bool:
        ret = OesApi_QueryCashAsset(self.env.qryChannel,
                                    OesQryCashAssetFilterT(),
                                    self.on_query_asset
                                    )
        return ret >= 0

    def on_query_asset(self,
                       session_info: SGeneralClientChannelT,
                       head: SMsgHeadT,
                       body: Any,
                       cursor: OesQryCursorT,
                       ):
        data = cast.toOesCashAssetItemT(body)
        balance = data.currentTotalBal / 10000
        availiable = data.currentAvailableBal / 10000
        # drawable = data.currentDrawableBal
        account_id = data.custId
        account = AccountData(
            gateway_name=self.gateway.gateway_name,
            accountid=account_id,
            balance=balance,
            frozen=balance - availiable,
        )
        self.account_id = account_id
        self.gateway.on_account(account)
        return 1

    def query_stock(self, ) -> bool:
        # Thread(target=self._query_stock, ).start()
        return self._query_stock()

    def _query_stock(self, ) -> bool:
        f = OesQryStockFilterT()
        ret = OesApi_QueryStock(self.env.qryChannel, f, self.on_query_stock)
        return ret >= 0

    def on_query_stock(self,
                       session_info: SGeneralClientChannelT,
                       head: SMsgHeadT,
                       body: Any,
                       cursor: OesQryCursorT,
                       ):
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
        f = OesQryOptionFilterT()
        ret = OesApi_QueryOption(self.env.qryChannel,
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

    def query_issue(self) -> bool:
        f = OesQryIssueFilterT()
        ret = OesApi_QueryIssue(self.env.qryChannel,
                                f,
                                self.on_query_issue
                                )
        return ret >= 0

    def on_query_issue(self,
                       session_info: SGeneralClientChannelT,
                       head: SMsgHeadT,
                       body: Any,
                       cursor: OesQryCursorT,
                       ):
        data = cast.toOesIssueItemT(body)
        contract = ContractData(
            gateway_name=self.gateway.gateway_name,
            symbol=data.securityId,
            exchange=EXCHANGE_OES2VT[data.mktId],
            name=data.securityName,
            product=PRODUCT_OES2VT[data.mktId],
            size=data.qtyUnit,
            pricetick=1,
        )
        self.gateway.on_contract(contract)
        return 1

    def query_etf(self) -> bool:
        f = OesQryEtfFilterT()
        ret = OesApi_QueryEtf(self.env.qryChannel,
                              f,
                              self.on_query_etf
                              )
        return ret >= 0

    def on_query_etf(self,
                     session_info: SGeneralClientChannelT,
                     head: SMsgHeadT,
                     body: Any,
                     cursor: OesQryCursorT,
                     ):
        data = cast.toOesEtfItemT(body)
        contract = ContractData(
            gateway_name=self.gateway.gateway_name,
            symbol=data.securityId,
            exchange=EXCHANGE_OES2VT[data.mktId],
            name=data.securityId,
            product=PRODUCT_OES2VT[data.mktId],
            size=data.creRdmUnit,  # todo: to verify! creRdmUnit : 每个篮子 (最小申购、赎回单位) 对应的ETF份数
            pricetick=1,
        )
        self.gateway.on_contract(contract)
        return 1

    def query_stock_holding(self) -> bool:
        f = OesQryStkHoldingFilterT()
        ret = OesApi_QueryStkHolding(self.env.qryChannel,
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
        f = OesQryStkHoldingFilterT()
        f.mktId = eOesMarketIdT.OES_MKT_ID_UNDEFINE
        f.userInfo = 0
        ret = OesApi_QueryOptHolding(self.env.qryChannel,
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
        self.query_stock()
        # self.query_option()
        # self.query_issue()
        pass

    def query_position(self):
        self.query_stock_holding()
        self.query_option_holding()

    def send_order(self, vt_req: OrderRequest):
        seq_id = self.last_seq_index
        self.last_seq_index += 1  # note: thread un-safe here, conflict with on_query_order
        order_id = self.order_manager.new_local_id()

        oes_req = OesOrdReqT()
        oes_req.clSeqNo = seq_id
        oes_req.mktId = EXCHANGE_VT2OES[vt_req.exchange]
        oes_req.ordType = ORDER_TYPE_VT2OES[(vt_req.exchange, vt_req.price_type)]
        oes_req.bsType = BUY_SELL_TYPE_VT2OES[(vt_req.exchange, vt_req.offset, vt_req.direction)]
        oes_req.invAcctId = ""
        oes_req.securityId = vt_req.symbol
        oes_req.ordQty = int(vt_req.volume)
        oes_req.ordPrice = int(vt_req.price * 10000)
        oes_req.userInfo = order_id

        ret = OesApi_SendOrderReq(self.env.ordChannel,
                                  oes_req
                                  )

        order = vt_req.create_order_data(str(order_id), self.gateway.gateway_name)
        order.direction = Direction.NET  # fix direction into NET: stock only
        if ret >= 0:
            self.order_manager.save_local_created(order_id, order, oes_req)
            self.gateway.on_order(order)
        else:
            self.gateway.write_log("Failed to send_order!")

        return order.vt_orderid

    def cancel_order(self, vt_req: CancelRequest):
        seq_id = self.last_seq_index
        self.last_seq_index += 1  # note: thread un-safe here

        oes_req = OesOrdCancelReqT()
        order_id = int(vt_req.orderid)
        internal_order = self.order_manager.get_from_order_id(order_id)
        if internal_order.rpt_data:
            data = internal_order.rpt_data
            # oes_req.origClSeqNo = self.local_id_to_sys_id[int(order_id)]
            oes_req.origClOrdId = data.clOrdId
            oes_req.origClSeqNo = data.clSeqNo
            oes_req.origClEnvId = data.origClEnvId
            oes_req.mktId = data.mktId
            # oes_req.invAcctId = data.invAcctId
            # oes_req.mktId = data.mktId
            # oes_req.securityId = data.securityId
        else:
            data = internal_order.req_data
            oes_req.origClSeqNo = data.clSeqNo
            oes_req.mktId = internal_order.req_data.mktId

        oes_req.clSeqNo = seq_id
        oes_req.invAcctId = ""
        oes_req.securityId = vt_req.symbol
        oes_req.userInfo = order_id
        ret = OesApi_SendOrderCancelReq(self.env.ordChannel,
                                        oes_req)

        if ret >= 0:
            pass
        else:
            pass
        return

    def schedule_query_order(self, internal_order: InternalOrder) -> Thread:
        th = Thread(target=self.query_order, args=(internal_order,))
        th.start()
        return th

    def query_order(self, internal_order: InternalOrder) -> bool:
        f = OesQryOrdFilterT()
        if internal_order.req_data:
            f.clSeqNo = internal_order.req_data.clSeqNo
            f.mktId = internal_order.req_data.mktId
            f.invAcctId = internal_order.req_data.invAcctId
        else:
            f.clSeqNo = internal_order.rpt_data.origClSeqNo
            f.clOrdId = internal_order.rpt_data.origClOrdId
            f.clEnvId = internal_order.rpt_data.origClEnvId
            f.mktId = internal_order.rpt_data.mktId
            f.invAcctId = internal_order.rpt_data.invAcctId
        ret = OesApi_QueryOrder(self.env.qryChannel,
                                f,
                                self.on_query_order
                                )
        return ret >= 0

    def on_query_order(self,
                       session_info: SGeneralClientChannelT,
                       head: SMsgHeadT,
                       body: Any,
                       cursor: OesQryCursorT):
        data: OesOrdCnfmT = cast.toOesOrdItemT(body)
        i = self.order_manager.get_from_oes_data(data)
        vt_order = i.vt_order
        vt_order.status = STATUS_OES2VT[data.ordStatus]
        vt_order.volume = data.ordQty - data.canceledQty
        vt_order.traded = data.cumQty
        self.gateway.on_order(vt_order)
        return 1

    def init_query_orders(self) -> bool:
        """
        :note: this function can be called only before calling send_order
        :return:
        """
        f = OesQryOrdFilterT()
        ret = OesApi_QueryOrder(self.env.qryChannel,
                                f,
                                self.on_init_query_orders
                                )
        return ret >= 0

    def on_init_query_orders(self,
                             session_info: SGeneralClientChannelT,
                             head: SMsgHeadT,
                             body: Any,
                             cursor: OesQryCursorT,
                             ):
        data: OesOrdCnfmT = cast.toOesOrdItemT(body)
        i = self.order_manager.get_remote_created_order_from_oes_data(data)
        if not i:
            order_id = self.order_manager.new_remote_id()

            if data.bsType == eOesBuySellTypeT.OES_BS_TYPE_BUY:
                offset = Offset.OPEN
            else:
                offset = Offset.CLOSE

            vt_order = OrderData(
                gateway_name=self.gateway.gateway_name,
                symbol=data.securityId,
                exchange=EXCHANGE_OES2VT[data.mktId],
                orderid=order_id if order_id else data.userInfo,  # generated id
                direction=Direction.NET,
                offset=offset,
                price=data.ordPrice / 10000,
                volume=data.ordQty - data.canceledQty,
                traded=data.cumQty,
                status=STATUS_OES2VT[data.ordStatus],

                # this time should be generated automatically or by a static function
                time=datetime.utcnow().isoformat(),
            )
            self.order_manager.save_remote_created(order_id, vt_order, data)
            self.gateway.on_order(vt_order)
            return 1
        else:
            vt_order = i.vt_order
            vt_order.status = STATUS_OES2VT[data.ordStatus]
            vt_order.volume = data.ordQty - data.canceledQty
            vt_order.traded = data.cumQty
            self.gateway.on_order(vt_order)
            return 1
