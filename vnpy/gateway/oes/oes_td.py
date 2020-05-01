import time
from copy import copy
from dataclasses import dataclass
from datetime import datetime, timedelta, timezone
from gettext import gettext as _
from threading import Lock, Thread
# noinspection PyUnresolvedReferences
from typing import Any, Callable, Dict
import pytz

from vnpy.api.oes.vnoes import OesApiClientEnvT, OesApiSubscribeInfoT, OesApi_DestoryAll, \
    OesApi_InitLogger, OesApi_InitOrdChannel2, OesApi_InitQryChannel2, OesApi_InitRptChannel2, \
    OesApi_LogoutAll, OesApi_QueryCashAsset, OesApi_QueryOptHolding, OesApi_QueryOption, \
    OesApi_QueryOrder, OesApi_QueryStkHolding, OesApi_QueryStock, OesApi_SendOrderCancelReq, \
    OesApi_SendOrderReq, OesApi_SetCustomizedDriverId, OesApi_SetCustomizedIpAndMac, \
    OesApi_SetThreadPassword, OesApi_SetThreadUsername, OesApi_WaitReportMsg, OesOrdCancelReqT, \
    OesOrdCnfmT, OesOrdRejectT, OesOrdReqT, OesQryCashAssetFilterT, OesQryCursorT, \
    OesQryOptionFilterT, OesQryOrdFilterT, OesQryStkHoldingFilterT, OesQryStockFilterT, \
    OesRspMsgBodyT, OesStockBaseInfoT, OesTrdCnfmT, SGeneralClientChannelT, SMSG_PROTO_BINARY, \
    SMsgHeadT, caster, eOesBuySellTypeT, eOesMarketIdT, eOesMsgTypeT, eOesOrdStatusT, \
    eOesOrdTypeShT, eOesOrdTypeSzT, eOesSubscribeReportTypeT

from vnpy.gateway.oes.error_code import error_to_str
from vnpy.gateway.oes.utils import create_remote_config, is_disconnected
from vnpy.trader.constant import Direction, Exchange, Offset, OrderType, Product, Status
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
    (Exchange.SSE, OrderType.LIMIT): eOesOrdTypeShT.OES_ORD_TYPE_SH_LMT,
    (Exchange.SZSE, OrderType.LIMIT): eOesOrdTypeSzT.OES_ORD_TYPE_SZ_LMT,
}
ORDER_TYPE_OES2VT = {
    (eOesMarketIdT.OES_MKT_SH_ASHARE, eOesOrdTypeShT.OES_ORD_TYPE_SH_LMT): OrderType.LIMIT,
    (eOesMarketIdT.OES_MKT_SZ_ASHARE, eOesOrdTypeSzT.OES_ORD_TYPE_SZ_LMT): OrderType.LIMIT,
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

CHINA_TZ = pytz.timezone("Asia/Shanghai")


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
    return datetime(year, month, day, hour, minute, sec, mill * 1000, tzinfo=CHINA_TZ)


class OesTdMessageLoop:

    def __init__(self,
                 gateway: BaseGateway,
                 env: OesApiClientEnvT,
                 td: "OesTdApi",
                 order_manager: "OrderManager",
                 ):
        """"""
        self.gateway = gateway

        self._env = env
        self._td = td
        self._order_manager = order_manager

        self._alive = False
        self._th = Thread(target=self._message_loop)

        self.message_handlers: Dict[eOesMsgTypeT, Callable[[OesRspMsgBodyT], int]] = {
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
        if not self._alive:  # not thread-safe
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
        self._td.connect_rpt_channel()

    def _on_message(self, session_info: SGeneralClientChannelT,
                    head: SMsgHeadT,
                    body: Any):
        """"""
        if session_info.protocolType == SMSG_PROTO_BINARY:
            b = caster.toOesRspMsgBodyT(body)
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
            try:
                i = self._order_manager.get_order(data.clSeqNo)
            except KeyError:
                return  # rejected order created by others, don't need to care.

            vt_order = i.vt_order
            if vt_order == Status.ALLTRADED:
                return

            vt_order.status = Status.REJECTED

            self.gateway.on_order(copy(vt_order))
            self.gateway.write_log(
                f"Order: {vt_order.vt_symbol}-{vt_order.vt_orderid} Code: {error_code} Rejected: {error_string}")
        else:
            self.gateway.write_log(f"撤单失败，订单号： {data.origClSeqNo}。原因：{error_string}")

    def on_order_inserted(self, d: OesRspMsgBodyT):
        """"""
        data = d.rptMsg.rptBody.ordInsertRsp

        vt_order = self._order_manager.oes_order_to_vt(data)
        self.gateway.on_order(copy(vt_order))

    def on_order_report(self, d: OesRspMsgBodyT):
        """"""
        data: OesOrdCnfmT = d.rptMsg.rptBody.ordCnfm

        vt_order = self._order_manager.oes_order_to_vt(data)
        self.gateway.on_order(copy(vt_order))

    def on_trade_report(self, d: OesRspMsgBodyT):
        """"""
        data: OesTrdCnfmT = d.rptMsg.rptBody.trdCnfm

        i = self._order_manager.get_order(data.clSeqNo)
        vt_order = i.vt_order

        trade = TradeData(
            gateway_name=self.gateway.gateway_name,
            symbol=data.securityId,
            exchange=EXCHANGE_OES2VT[data.mktId],
            orderid=str(data.clSeqNo),
            tradeid=str(data.exchTrdNum),
            direction=vt_order.direction,
            offset=vt_order.offset,
            price=data.trdPrice / 10000,
            volume=data.trdQty,
            datetime=parse_oes_datetime(data.trdDate, data.trdTime)
        )
        vt_order.status = STATUS_OES2VT[data.ordStatus]
        vt_order.traded = data.cumQty
        vt_order.time = parse_oes_datetime(data.trdDate, data.trdTime)
        self.gateway.on_trade(trade)
        self.gateway.on_order(copy(vt_order))

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
            frozen=data.lockHld,
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
        self.config_path: str = ''
        self.ord_server: str = ''
        self.qry_server: str = ''
        self.rpt_server: str = ''
        self.username: str = ''
        self.password: str = ''
        self.hdd_serial: str = ''
        self.customize_ip: str = ''
        self.customize_mac: str = ''

        self.gateway = gateway

        self._env = OesApiClientEnvT()

        self._order_manager: "OrderManager" = OrderManager(self.gateway.gateway_name)
        self._message_loop = OesTdMessageLoop(gateway,
                                              self._env,
                                              self,
                                              self._order_manager
                                              )

        self._last_seq_lock = Lock()
        self._last_seq_index = 1000000  # 0 has special manning for oes
        self._ord_reconnect_lock = Lock()

    def connect(self):
        """Connect to trading server.
        :note set config_path before calling this function
        """
        OesApi_InitLogger(self.config_path, 'log')

        OesApi_SetCustomizedIpAndMac(self.customize_ip, self.customize_mac)

        OesApi_SetCustomizedDriverId(self.hdd_serial)

        if not self._connect_ord_channel():
            self.gateway.write_log(_("无法初始化交易下单通道(td_ord_server)"))

        if not self._connect_qry_channel():
            self.gateway.write_log(_("无法初始化交易查询通道(td_qry_server)"))

        if not self.connect_rpt_channel():
            self.gateway.write_log(_("无法初始化交易查询通道(td_qry_server)"))
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

    def _connect_qry_channel(self):
        OesApi_SetThreadUsername(self.username)
        OesApi_SetThreadPassword(self.password)

        return OesApi_InitQryChannel2(self._env.qryChannel,
                                      create_remote_config(self.qry_server,
                                                           self.username,
                                                           self.password))

    def _connect_ord_channel(self):
        OesApi_SetThreadUsername(self.username)
        OesApi_SetThreadPassword(self.password)

        if not OesApi_InitOrdChannel2(self._env.ordChannel,
                                      create_remote_config(self.ord_server,
                                                           self.username,
                                                           self.password),
                                      0):
            return False
        self._last_seq_index = max(self._last_seq_index, self._env.ordChannel.lastOutMsgSeq + 1)
        return True

    def connect_rpt_channel(self):
        OesApi_SetThreadUsername(self.username)
        OesApi_SetThreadPassword(self.password)

        subscribe_info = OesApiSubscribeInfoT()
        subscribe_info.clEnvId = 0
        subscribe_info.rptTypes = (eOesSubscribeReportTypeT.OES_SUB_RPT_TYPE_BUSINESS_REJECT
                                   | eOesSubscribeReportTypeT.OES_SUB_RPT_TYPE_ORDER_INSERT
                                   | eOesSubscribeReportTypeT.OES_SUB_RPT_TYPE_ORDER_REPORT
                                   | eOesSubscribeReportTypeT.OES_SUB_RPT_TYPE_TRADE_REPORT
                                   | eOesSubscribeReportTypeT.OES_SUB_RPT_TYPE_FUND_TRSF_REPORT
                                   | eOesSubscribeReportTypeT.OES_SUB_RPT_TYPE_CASH_ASSET_VARIATION
                                   | eOesSubscribeReportTypeT.OES_SUB_RPT_TYPE_HOLDING_VARIATION
                                   )
        return OesApi_InitRptChannel2(self._env.rptChannel,
                                      create_remote_config(self.rpt_server,
                                                           self.username,
                                                           self.password),
                                      subscribe_info,
                                      0)

    def _reconnect_ord_channel(self):
        with self._ord_reconnect_lock:  # prevent spawning multiple reconnect thread
            self.gateway.write_log(_("正在重新连接到交易下单通道"))
            while not self._connect_ord_channel():
                time.sleep(1)

            self.gateway.write_log(_("成功重新连接到交易下单通道"))

    def _schedule_reconnect_ord_channel(self):
        Thread(target=self._reconnect_ord_channel, ).start()

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
        data = caster.toOesCashAssetItemT(body)
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
        data: OesStockBaseInfoT = caster.toOesStockItemT(body)
        contract = ContractData(
            gateway_name=self.gateway.gateway_name,
            symbol=data.securityId,
            exchange=EXCHANGE_OES2VT[data.mktId],
            name=data.securityName,
            product=PRODUCT_OES2VT[data.mktId],
            size=data.buyQtyUnit,
            min_volume=100,
            net_position=True,
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
        data = caster.toOesOptionItemT(body)
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
        data = caster.toOesStkHoldingItemT(body)

        position = PositionData(
            gateway_name=self.gateway.gateway_name,
            symbol=data.securityId,
            exchange=EXCHANGE_OES2VT[data.mktId],
            direction=Direction.NET,
            volume=data.sumHld,
            frozen=data.lockHld,
            price=data.costPrice / 10000,
            # pnl=data.costPrice - data.originalCostAmt,
            pnl=0,
            yd_volume=data.originalHld,
        )
        self.gateway.on_position(position)
        return 1

    def query_option_holding(self) -> bool:
        """"""
        f = OesQryStkHoldingFilterT()
        f.mktId = eOesMarketIdT.OES_MKT_ID_UNDEFINE
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
        data = caster.toOesOptHoldingItemT(body)

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
        oes_req.ordType = ORDER_TYPE_VT2OES[(vt_req.exchange, vt_req.type)]
        oes_req.bsType = BUY_SELL_TYPE_VT2OES[(vt_req.exchange, vt_req.offset, vt_req.direction)]
        oes_req.invAcctId = ""
        oes_req.securityId = vt_req.symbol
        oes_req.ordQty = int(vt_req.volume)
        oes_req.ordPrice = int(vt_req.price * 10000)
        oes_req.origClOrdId = order_id

        order = vt_req.create_order_data(str(order_id), self.gateway.gateway_name)
        order.direction = Direction.NET  # fix direction into NET: stock only
        self._order_manager.save_order(order_id, order)

        ret = OesApi_SendOrderReq(self._env.ordChannel,
                                  oes_req
                                  )

        if ret >= 0:
            order.status = Status.SUBMITTING
        else:
            order.status = Status.REJECTED
            self.gateway.write_log(_("下单失败"))  # todo: can I stringify error?
            if is_disconnected(ret):
                self.gateway.write_log(_("下单时连接发现连接已断开，正在尝试重连"))
                self._schedule_reconnect_ord_channel()
        self.gateway.on_order(order)

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

        ret = OesApi_SendOrderCancelReq(self._env.ordChannel,
                                        oes_req)
        if ret < 0:
            self.gateway.write_log(_("撤单失败"))  # todo: can I stringify error?
            if is_disconnected(ret):  # is here any other ret code indicating connection lost?
                self.gateway.write_log(_("撤单时连接发现连接已断开，正在尝试重连"))
                self._schedule_reconnect_ord_channel()

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
        data: OesOrdCnfmT = caster.toOesOrdItemT(body)

        i = self._order_manager.get_order(data.clSeqNo)
        vt_order = i.vt_order
        vt_order.status = STATUS_OES2VT[data.ordStatus]
        vt_order.volume = data.ordQty
        vt_order.traded = data.cumQty
        self.gateway.on_order(copy(vt_order))
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
        data: OesOrdCnfmT = caster.toOesOrdItemT(body)
        vt_order = self._order_manager.oes_order_to_vt(data)
        self.gateway.on_order(vt_order)
        return 1


class OrderManager:

    def __init__(self, gateway_name: str):
        self._orders: Dict[int, InternalOrder] = {}
        self.gateway_name = gateway_name

    def oes_order_to_vt(self, data):
        order_id = data.clSeqNo
        if hasattr(data, "origClSeqNo") and data.origClSeqNo:
            order_id = data.origClSeqNo
        try:
            i = self.get_order(order_id)
            vt_order = i.vt_order
            vt_order.status = STATUS_OES2VT[data.ordStatus]
            vt_order.volume = data.ordQty
            vt_order.traded = data.cumQty
            vt_order.time = parse_oes_datetime(data.ordDate, data.ordTime).isoformat()
        except KeyError:
            if data.bsType == eOesBuySellTypeT.OES_BS_TYPE_BUY:
                offset = Offset.OPEN
            else:
                offset = Offset.CLOSE

            vt_order = OrderData(
                gateway_name=self.gateway_name,
                symbol=data.securityId,
                exchange=EXCHANGE_OES2VT[data.mktId],
                orderid=str(order_id if order_id else data.origClSeqNo),  # generated id
                type=ORDER_TYPE_OES2VT[(data.mktId, data.ordType)],
                direction=Direction.NET,
                offset=offset,
                price=data.ordPrice / 10000,
                volume=data.ordQty,
                traded=data.cumQty,
                status=STATUS_OES2VT[
                    data.ordStatus],

                # this time should be generated automatically or by a static function
                datetime=parse_oes_datetime(data.ordDate, data.ordCnfmTime),
            )
            self.save_order(order_id, vt_order)
        return vt_order

    def save_order(self, order_id: int, order: OrderData):
        """"""
        self._orders[order_id] = InternalOrder(
            order_id=order_id,
            vt_order=order,
        )

    def get_order(self, order_id: int):
        """"""
        return self._orders[order_id]
