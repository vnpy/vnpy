import time
from copy import copy
from datetime import datetime
from gettext import gettext as _
from threading import Thread
# noinspection PyUnresolvedReferences
from typing import Any, Callable, Dict
import pytz

from vnpy.api.oes.vnoes import MdsApiClientEnvT, MdsApi_DestoryAll, MdsApi_InitLogger, \
    MdsApi_InitTcpChannel2, MdsApi_LogoutAll, MdsApi_SetThreadPassword, MdsApi_SetThreadUsername, \
    MdsApi_SubscribeMarketData, MdsApi_WaitOnMsg, MdsL2StockSnapshotBodyT, MdsMktDataRequestEntryT, \
    MdsMktDataRequestReqBufT, MdsMktDataRequestReqT, MdsMktRspMsgBodyT, MdsStockSnapshotBodyT, \
    SGeneralClientChannelT, SMsgHeadT, caster, eMdsExchangeIdT, eMdsMktSubscribeFlagT, eMdsMsgTypeT, \
    eMdsMdProductTypeT, eMdsSubscribeDataTypeT, eMdsSubscribeModeT, eMdsSubscribedTickExpireTypeT, \
    eMdsSubscribedTickTypeT, eSMsgProtocolTypeT

from vnpy.gateway.oes.utils import create_remote_config, is_disconnected
from vnpy.trader.constant import Exchange
from vnpy.trader.gateway import BaseGateway
from vnpy.trader.object import SubscribeRequest, TickData
from .error_code import error_to_str

EXCHANGE_MDS2VT = {
    eMdsExchangeIdT.MDS_EXCH_SSE: Exchange.SSE,
    eMdsExchangeIdT.MDS_EXCH_SZSE: Exchange.SZSE,
}
EXCHANGE_VT2MDS = {v: k for k, v in EXCHANGE_MDS2VT.items()}

CHINA_TZ = pytz.timezone("Asia/Shanghai")


class OesMdMessageLoop:

    def __init__(self, gateway: BaseGateway, md: "OesMdApi", env: MdsApiClientEnvT):
        """"""
        self.gateway = gateway
        self.env = env

        self._alive = False
        self._md = md
        self._th = Thread(target=self._message_loop)

        self.message_handlers: Dict[eMdsMsgTypeT, Callable[[MdsMktRspMsgBodyT], int]] = {
            # tick & orderbook
            eMdsMsgTypeT.MDS_MSGTYPE_MARKET_DATA_SNAPSHOT_FULL_REFRESH: self.on_init_tick,
            eMdsMsgTypeT.MDS_MSGTYPE_L2_MARKET_DATA_SNAPSHOT: self.on_l2_tick,
            eMdsMsgTypeT.MDS_MSGTYPE_L2_ORDER: self.on_l2_order,
            eMdsMsgTypeT.MDS_MSGTYPE_L2_TRADE: self.on_l2_trade,

            # others
            eMdsMsgTypeT.MDS_MSGTYPE_QRY_SECURITY_STATUS: self.on_security_status,
            eMdsMsgTypeT.MDS_MSGTYPE_L2_MARKET_DATA_INCREMENTAL: lambda x: 1,
            eMdsMsgTypeT.MDS_MSGTYPE_L2_BEST_ORDERS_SNAPSHOT: self.on_best_orders_snapshot,
            eMdsMsgTypeT.MDS_MSGTYPE_INDEX_SNAPSHOT_FULL_REFRESH: self.on_index_snapshot_full_refresh,
            eMdsMsgTypeT.MDS_MSGTYPE_L2_MARKET_OVERVIEW: self.on_l2_market_overview,
            eMdsMsgTypeT.MDS_MSGTYPE_OPTION_SNAPSHOT_FULL_REFRESH: self.on_option_snapshot_ful_refresh,
            eMdsMsgTypeT.MDS_MSGTYPE_TRADING_SESSION_STATUS: self.on_trading_session_status,
            eMdsMsgTypeT.MDS_MSGTYPE_SECURITY_STATUS: self.on_security_status,
            eMdsMsgTypeT.MDS_MSGTYPE_MARKET_DATA_REQUEST: self.on_market_data_request,

            eMdsMsgTypeT.MDS_MSGTYPE_HEARTBEAT: lambda x: 1,
        }
        self.last_tick: Dict[str, TickData] = {}
        self.symbol_to_exchange: Dict[str, Exchange] = {}

    def register_symbol(self, symbol: str, exchange: Exchange):
        """"""
        self.symbol_to_exchange[symbol] = exchange

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
        self.gateway.write_log(_("正在尝试重新连接到行情服务器。"))
        return self._md.connect_tcp_channel()

    def _get_last_tick(self, symbol):
        """"""
        try:
            return self.last_tick[symbol]
        except KeyError:
            tick = TickData(
                gateway_name=self.gateway.gateway_name,
                symbol=symbol,
                exchange=self.symbol_to_exchange[symbol],
                datetime=datetime.now(CHINA_TZ)
            )
            self.last_tick[symbol] = tick
            return tick

    def _on_message(self, session_info: SGeneralClientChannelT,
                    head: SMsgHeadT,
                    body: Any):
        """"""
        if session_info.protocolType == eSMsgProtocolTypeT.SMSG_PROTO_BINARY:
            b = caster.toMdsMktRspMsgBodyT(body)
            if head.msgId in self.message_handlers:
                # self.gateway.write_log(
                #     f"msg id : {head.msgId}   {eMdsMsgTypeT(head.msgId)}")
                self.message_handlers[head.msgId](b)
            else:
                self.gateway.write_log(
                    f"unknown msg id : {head.msgId}   {eMdsMsgTypeT(head.msgId)}")
        else:
            self.gateway.write_log(f"unknown prototype : {session_info.protocolType}")
        return 1

    def _message_loop(self):
        """"""
        tcp_channel = self.env.tcpChannel
        timeout_ms = 1000
        while self._alive:
            ret = MdsApi_WaitOnMsg(tcp_channel,
                                   timeout_ms,
                                   self._on_message)
            if ret < 0:
                # if is_timeout(ret):
                #     pass  # just no message
                if is_disconnected(ret):
                    self.gateway.write_log(_("与行情服务器的连接已断开。"))
                    while self._alive and not self.reconnect():
                        time.sleep(1)
        return

    def on_l2_tick(self, d: MdsMktRspMsgBodyT):
        """"""
        data: MdsL2StockSnapshotBodyT = d.mktDataSnapshot.l2Stock
        symbol = str(data.SecurityID)
        tick = self._get_last_tick(symbol)
        tick.open_price = data.OpenPx / 10000
        tick.pre_close = data.ClosePx / 10000
        tick.high_price = data.HighPx / 10000
        tick.low_price = data.LowPx / 10000

        for i in range(min(data.BidPriceLevel, 5)):
            tick.__dict__['bid_price_' + str(i + 1)] = data.BidLevels[i].Price / 10000
            tick.__dict__['bid_volume_' + str(i + 1)] = data.BidLevels[i].QrderQty / 100
        for i in range(min(data.OfferPriceLevel, 5)):
            tick.__dict__['ask_price_' + str(i + 1)] = data.OfferLevels[i].Price / 10000
            tick.__dict__['ask_volume_' + str(i + 1)] = data.OfferLevels[i].QrderQty / 100
        self.gateway.on_tick(copy(tick))

    def on_init_tick(self, d: MdsMktRspMsgBodyT):
        """"""
        data: MdsStockSnapshotBodyT = d.mktDataSnapshot.stock
        symbol = data.SecurityID
        tick = self._get_last_tick(symbol)
        tick.open_price = data.OpenPx / 10000
        tick.pre_close = data.ClosePx / 10000
        tick.high_price = data.HighPx / 10000
        tick.low_price = data.LowPx / 10000

        for i in range(5):
            tick.__dict__['bid_price_' + str(i + 1)] = data.BidLevels[i].Price / 10000
            tick.__dict__['bid_volume_' + str(i + 1)] = data.BidLevels[i].QrderQty / 100
        for i in range(5):
            tick.__dict__['ask_price_' + str(i + 1)] = data.OfferLevels[i].Price / 10000
            tick.__dict__['ask_volume_' + str(i + 1)] = data.OfferLevels[i].QrderQty / 100
        self.gateway.on_tick(copy(tick))

    def on_l2_trade(self, d: MdsMktRspMsgBodyT):
        """"""
        data = d.trade
        symbol = data.SecurityID
        tick = self._get_last_tick(symbol)
        tick.datetime = datetime.now(CHINA_TZ)
        tick.volume = data.TradeQty
        tick.last_price = data.TradePrice / 10000
        self.gateway.on_tick(copy(tick))

    def on_market_data_request(self, d: MdsMktRspMsgBodyT):
        """"""
        pass

    def on_trading_session_status(self, d: MdsMktRspMsgBodyT):
        """"""
        pass

    def on_l2_market_overview(self, d: MdsMktRspMsgBodyT):
        """"""
        pass

    def on_index_snapshot_full_refresh(self, d: MdsMktRspMsgBodyT):
        """"""
        pass

    def on_option_snapshot_ful_refresh(self, d: MdsMktRspMsgBodyT):
        """"""
        pass

    def on_best_orders_snapshot(self, d: MdsMktRspMsgBodyT):
        """"""
        pass

    def on_l2_order(self, d: MdsMktRspMsgBodyT):
        """"""
        pass

    def on_security_status(self, d: MdsMktRspMsgBodyT):
        """"""
        pass


class OesMdApi:

    def __init__(self, gateway: BaseGateway):
        """"""
        self.gateway = gateway
        self.config_path: str = ''
        self.tcp_server: str = ''
        self.qry_server: str = ''

        self.username: str = ''
        self.password: str = ''

        self._env = MdsApiClientEnvT()
        self._message_loop = OesMdMessageLoop(gateway, self, self._env)

    def connect(self) -> bool:
        """"""
        """Connect to trading server.
        :note set config_path before calling this function
        """
        MdsApi_InitLogger(self.config_path, "log")
        return self.connect_tcp_channel()

    def start(self):
        """"""
        self._message_loop.start()

    def stop(self):
        """"""
        self._message_loop.stop()
        MdsApi_LogoutAll(self._env, True)
        MdsApi_DestoryAll(self._env)

    def join(self):
        """"""
        self._message_loop.join()

    def connect_tcp_channel(self):
        """"""
        MdsApi_SetThreadUsername(self.username)
        MdsApi_SetThreadPassword(self.password)

        info = MdsMktDataRequestReqBufT()
        info.mktDataRequestReq.subMode = eMdsSubscribeModeT.MDS_SUB_MODE_SET
        info.mktDataRequestReq.tickType = eMdsSubscribedTickTypeT.MDS_TICK_TYPE_LATEST_SIMPLIFIED
        info.mktDataRequestReq.isRequireInitialMktData = True
        info.mktDataRequestReq.tickExpireType = eMdsSubscribedTickExpireTypeT.MDS_TICK_EXPIRE_TYPE_TIMELY
        info.mktDataRequestReq.dataTypes = (eMdsSubscribeDataTypeT.MDS_SUB_DATA_TYPE_L1_SNAPSHOT
                                            | eMdsSubscribeDataTypeT.MDS_SUB_DATA_TYPE_L2_SNAPSHOT
                                            | eMdsSubscribeDataTypeT.MDS_SUB_DATA_TYPE_L2_BEST_ORDERS
                                            | eMdsSubscribeDataTypeT.MDS_SUB_DATA_TYPE_L2_TRADE
                                            | eMdsSubscribeDataTypeT.MDS_SUB_DATA_TYPE_L2_ORDER
                                            )
        info.mktDataRequestReq.beginTime = 0
        info.mktDataRequestReq.subSecurityCnt = 0
        if not MdsApi_InitTcpChannel2(self._env.tcpChannel,
                                      create_remote_config(server=self.tcp_server,
                                                           username=self.username,
                                                           password=self.password),
                                      info):
            return False
        return True

    def subscribe(self, req: SubscribeRequest):
        """"""
        mds_req = MdsMktDataRequestReqT()
        entry = MdsMktDataRequestEntryT()
        mds_req.subMode = eMdsSubscribeModeT.MDS_SUB_MODE_APPEND
        mds_req.tickType = eMdsSubscribedTickExpireTypeT.MDS_TICK_EXPIRE_TYPE_TIMELY  # 1s, 3s?
        mds_req.sseStockFlag = eMdsMktSubscribeFlagT.MDS_MKT_SUB_FLAG_DEFAULT
        mds_req.sseIndexFlag = eMdsMktSubscribeFlagT.MDS_MKT_SUB_FLAG_DEFAULT
        mds_req.sseOptionFlag = eMdsMktSubscribeFlagT.MDS_MKT_SUB_FLAG_DEFAULT
        mds_req.szseStockFlag = eMdsMktSubscribeFlagT.MDS_MKT_SUB_FLAG_DEFAULT
        mds_req.szseIndexFlag = eMdsMktSubscribeFlagT.MDS_MKT_SUB_FLAG_DEFAULT
        mds_req.szseOptionFlag = eMdsMktSubscribeFlagT.MDS_MKT_SUB_FLAG_DEFAULT
        mds_req.isRequireInitialMktData = 1
        mds_req.tickExpireType = eMdsSubscribedTickExpireTypeT.MDS_TICK_EXPIRE_TYPE_TIMELY
        mds_req.dataTypes = (
            eMdsSubscribeDataTypeT.MDS_SUB_DATA_TYPE_L1_SNAPSHOT
            | eMdsSubscribeDataTypeT.MDS_SUB_DATA_TYPE_L2_SNAPSHOT
            | eMdsSubscribeDataTypeT.MDS_SUB_DATA_TYPE_L2_TRADE
            | eMdsSubscribeDataTypeT.MDS_SUB_DATA_TYPE_L2_ORDER
            | eMdsSubscribeDataTypeT.MDS_SUB_DATA_TYPE_INDEX_SNAPSHOT
            | eMdsSubscribeDataTypeT.MDS_SUB_DATA_TYPE_OPTION_SNAPSHOT
        )
        mds_req.beginTime = 0
        mds_req.subSecurityCnt = 1

        entry.exchId = EXCHANGE_VT2MDS[req.exchange]
        entry.mdProductType = eMdsMdProductTypeT.MDS_SECURITY_TYPE_STOCK  # todo: option and others
        entry.instrId = int(req.symbol)

        self._message_loop.register_symbol(req.symbol, req.exchange)
        ret = MdsApi_SubscribeMarketData(
            self._env.tcpChannel,
            mds_req,
            entry)
        if not ret:
            self.gateway.write_log(
                f"MdsApi_SubscribeByString failed with {ret}:{error_to_str(ret)}")
