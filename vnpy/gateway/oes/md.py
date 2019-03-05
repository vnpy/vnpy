from datetime import datetime
from threading import Thread
# noinspection PyUnresolvedReferences
from typing import Any, Callable, Dict

from vnpy.api.oes.vnoes import MdsApiClientEnvT, MdsApi_DestoryAll, MdsApi_InitAllByConvention, \
    MdsApi_IsValidQryChannel, MdsApi_IsValidTcpChannel, MdsApi_LogoutAll, \
    MdsApi_SubscribeMarketData, MdsApi_WaitOnMsg, MdsL2StockSnapshotBodyT, MdsMktDataRequestEntryT, \
    MdsMktDataRequestReqT, MdsMktRspMsgBodyT, MdsStockSnapshotBodyT, SGeneralClientChannelT, \
    SMsgHeadT, SPlatform_IsNegEpipe, SPlatform_IsNegEtimeout, cast, eMdsExchangeIdT, \
    eMdsMktSubscribeFlagT, eMdsMsgTypeT, eMdsSecurityTypeT, eMdsSubscribeDataTypeT, \
    eMdsSubscribeModeT, eMdsSubscribedTickExpireTypeT, eSMsgProtocolTypeT

from vnpy.trader.constant import Exchange
from vnpy.trader.gateway import BaseGateway
from vnpy.trader.object import SubscribeRequest, TickData
from .error_code import error_to_str

EXCHANGE_MDS2VT = {
    eMdsExchangeIdT.MDS_EXCH_SSE: Exchange.SSE,
    eMdsExchangeIdT.MDS_EXCH_SZSE: Exchange.SZSE,
}
EXCHANGE_VT2MDS = {v: k for k, v in EXCHANGE_MDS2VT.items()}


class OesMdMessageLoop:

    def __init__(self, gateway: BaseGateway, env: MdsApiClientEnvT):
        self.gateway = gateway
        self.env = env
        self.alive = False
        self.th = Thread(target=self.message_loop)

        self.message_handlers: Dict[int, Callable[[dict], None]] = {
            eMdsMsgTypeT.MDS_MSGTYPE_MARKET_DATA_SNAPSHOT_FULL_REFRESH: self.on_market_full_refresh,
            eMdsMsgTypeT.MDS_MSGTYPE_L2_MARKET_DATA_SNAPSHOT: self.on_l2_market_data_snapshot,
            eMdsMsgTypeT.MDS_MSGTYPE_L2_ORDER: self.on_l2_order,
            eMdsMsgTypeT.MDS_MSGTYPE_L2_TRADE: self.on_l2_trade,

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
        self.symbol_to_exchange[symbol] = exchange

    def get_last_tick(self, symbol):
        try:
            return self.last_tick[symbol]
        except KeyError:
            tick = TickData(
                gateway_name=self.gateway.gateway_name,
                symbol=symbol,
                exchange=self.symbol_to_exchange[symbol],
                # todo: use cache of something else to resolve exchange
                datetime=datetime.utcnow()
            )
            self.last_tick[symbol] = tick
            return tick

    def start(self):
        self.alive = True
        self.th.start()

    def join(self):
        self.th.join()

    def on_message(self, session_info: SGeneralClientChannelT,
                   head: SMsgHeadT,
                   body: Any):
        if session_info.protocolType == eSMsgProtocolTypeT.SMSG_PROTO_BINARY:
            b = cast.toMdsMktRspMsgBodyT(body)
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

    def message_loop(self):
        tcp_channel = self.env.tcpChannel
        timeout_ms = 1000
        is_timeout = SPlatform_IsNegEtimeout
        is_disconnected = SPlatform_IsNegEpipe
        while self.alive:
            ret = MdsApi_WaitOnMsg(tcp_channel,
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

    def on_l2_market_data_snapshot(self, d: MdsMktRspMsgBodyT):
        data: MdsL2StockSnapshotBodyT = d.mktDataSnapshot.l2Stock
        symbol = str(data.SecurityID)
        tick = self.get_last_tick(symbol)
        tick.limit_up = data.HighPx / 10000
        tick.limit_down = data.LowPx / 10000
        tick.open_price = data.OpenPx / 10000
        tick.pre_close = data.ClosePx / 10000
        tick.high_price = data.HighPx / 10000
        tick.low_price = data.LowPx / 10000

        for i in range(min(data.BidPriceLevel, 5)):
            tick.__dict__['bid_price_' + str(i + 1)] = data.BidLevels[i].Price / 10000
        for i in range(min(data.OfferPriceLevel, 5)):
            tick.__dict__['ask_price_' + str(i + 1)] = data.OfferLevels[i].Price / 10000
        self.gateway.on_tick(tick)

    def on_market_full_refresh(self, d: MdsMktRspMsgBodyT):
        data: MdsStockSnapshotBodyT = d.mktDataSnapshot.stock
        symbol = data.SecurityID
        tick = self.get_last_tick(symbol)
        tick.limit_up = data.HighPx / 10000
        tick.limit_down = data.LowPx / 10000
        tick.open_price = data.OpenPx / 10000
        tick.pre_close = data.ClosePx / 10000
        tick.high_price = data.HighPx / 10000
        tick.low_price = data.LowPx / 10000

        for i in range(5):
            tick.__dict__['bid_price_' + str(i + 1)] = data.BidLevels[i].Price / 10000
        for i in range(5):
            tick.__dict__['ask_price_' + str(i + 1)] = data.OfferLevels[i].Price / 10000
        self.gateway.on_tick(tick)
        pass

    def on_l2_trade(self, d: MdsMktRspMsgBodyT):
        data = d.trade
        symbol = data.SecurityID
        tick = self.get_last_tick(symbol)
        tick.datetime = datetime.utcnow()
        tick.volume = data.TradeQty
        tick.last_price = data.TradePrice / 10000
        self.gateway.on_tick(tick)

    def on_market_data_request(self, d: MdsMktRspMsgBodyT):
        pass

    def on_trading_session_status(self, d: MdsMktRspMsgBodyT):
        pass

    def on_l2_market_overview(self, d: MdsMktRspMsgBodyT):
        pass

    def on_index_snapshot_full_refresh(self, d: MdsMktRspMsgBodyT):
        pass

    def on_option_snapshot_ful_refresh(self, d: MdsMktRspMsgBodyT):
        pass

    def on_best_orders_snapshot(self, d: MdsMktRspMsgBodyT):
        pass

    def on_l2_order(self, d: MdsMktRspMsgBodyT):
        pass

    def on_security_status(self, d: MdsMktRspMsgBodyT):
        pass

    def stop(self):
        self.alive = False


class OesMdApi:

    def __init__(self, gateway: BaseGateway):
        self.gateway = gateway
        self.env = MdsApiClientEnvT()
        self.message_loop = OesMdMessageLoop(gateway, self.env)

    def connect(self, config_path: str):
        if not MdsApi_InitAllByConvention(self.env, config_path):
            pass

        if not MdsApi_IsValidTcpChannel(self.env.tcpChannel):
            pass
        if not MdsApi_IsValidQryChannel(self.env.qryChannel):
            pass

    def start(self):
        self.message_loop.start()

    def stop(self):
        self.message_loop.stop()
        if not MdsApi_LogoutAll(self.env, True):
            pass  # doc for this function is error
        if not MdsApi_DestoryAll(self.env):
            pass  # doc for this function is error

    def join(self):
        self.message_loop.join()

    # why isn't arg a ContractData?
    def subscribe(self, req: SubscribeRequest):
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
        entry.securityType = eMdsSecurityTypeT.MDS_SECURITY_TYPE_STOCK  # todo: option and others
        entry.instrId = int(req.symbol)

        self.message_loop.register_symbol(req.symbol, req.exchange)
        ret = MdsApi_SubscribeMarketData(
            self.env.tcpChannel,
            mds_req,
            entry)
        if not ret:
            self.gateway.write_log(
                f"MdsApi_SubscribeByString failed with {ret}:{error_to_str(ret)}")
        pass
