from typing import Any, Sequence, List, Optional
from datetime import datetime
from threading import Thread
from vnpy.event import EventEngine
from vnpy.trader.event import EVENT_TIMER
from vnpy.trader.constant import Exchange, Product, Direction, OrderType, Status, Offset
from vnpy.trader.gateway import BaseGateway
from vnpy.trader.object import (
    CancelRequest,
    OrderRequest,
    SubscribeRequest,
    TickData,
    ContractData,
    OrderData,
    TradeData,
    PositionData,
    AccountData,
)
from vnpy.trader.utility import get_folder_path

from vnpy.api.tora.vntora import (
    set_async_callback_exception_handler,
    AsyncDispatchException,
    CTORATstpTraderApi,
    CTORATstpMdApi,
    CTORATstpMdSpi,
    CTORATstpTraderSpi,
    TORA_TSTP_EXD_SSE,
    TORA_TSTP_EXD_SZSE,
    TORA_TSTP_EXD_HK,
    CTORATstpFundsFlowMarketDataField,
    CTORATstpEffectVolumeMarketDataField,
    CTORATstpEffectPriceMarketDataField,
    CTORATstpSpecialMarketDataField,
    CTORATstpMarketDataField,
    CTORATstpSpecificSecurityField,
    CTORATstpRspInfoField,
    CTORATstpUserLogoutField,
    CTORATstpRspUserLoginField,
)


EXCHANGE_TORA2VT = {
    TORA_TSTP_EXD_SSE: Exchange.SSE,
    TORA_TSTP_EXD_SZSE: Exchange.SZSE,
    TORA_TSTP_EXD_HK: Exchange.SEHK,
}
EXCHANGE_VT2TORA = {v: k for k, v in EXCHANGE_TORA2VT.items()}


def parse_datetime(date: str, time: str):
    return datetime.now()  # fixme: return the real time


class ToraMdSpi(CTORATstpMdSpi):

    def __init__(self, api: "ToraMdApi", gateway: "BaseGateway"):
        super().__init__()
        self.gateway = gateway

        self._api = api

    def OnFrontConnected(self) -> Any:
        self.gateway.write_log("行情服务器连接成功")

    def OnFrontDisconnected(self, nReason: int) -> Any:
        self.gateway.write_log("行情服务器连接断开")

    def OnRspError(
        self, pRspInfo: CTORATstpRspInfoField, nRequestID: int, bIsLast: bool
    ) -> Any:
        self.gateway.write_log("OnRspError")

    def OnRspUserLogin(
        self,
        pRspUserLogin: CTORATstpRspUserLoginField,
        pRspInfo: CTORATstpRspInfoField,
        nRequestID: int,
        bIsLast: bool,
    ) -> Any:
        self.gateway.write_log("行情服务器登录成功")

    def OnRspUserLogout(
        self,
        pUserLogout: CTORATstpUserLogoutField,
        pRspInfo: CTORATstpRspInfoField,
        nRequestID: int,
        bIsLast: bool,
    ) -> Any:
        self.gateway.write_log("行情服务器登出成功")

    def OnRspSubMarketData(
        self,
        pSpecificSecurity: CTORATstpSpecificSecurityField,
        pRspInfo: CTORATstpRspInfoField,
        nRequestID: int,
        bIsLast: bool,
    ) -> Any:
        self.gateway.write_log("OnRspSubMarketData")

    def OnRspUnSubMarketData(
        self,
        pSpecificSecurity: CTORATstpSpecificSecurityField,
        pRspInfo: CTORATstpRspInfoField,
        nRequestID: int,
        bIsLast: bool,
    ) -> Any:
        pass

    def OnRspSubSpecialMarketData(
        self,
        pSpecificSecurity: CTORATstpSpecificSecurityField,
        pRspInfo: CTORATstpRspInfoField,
        nRequestID: int,
        bIsLast: bool,
    ) -> Any:
        pass

    def OnRspUnSubSpecialMarketData(
        self,
        pSpecificSecurity: CTORATstpSpecificSecurityField,
        pRspInfo: CTORATstpRspInfoField,
        nRequestID: int,
        bIsLast: bool,
    ) -> Any:
        pass

    def OnRspSubFundsFlowMarketData(
        self,
        pSpecificSecurity: CTORATstpSpecificSecurityField,
        pRspInfo: CTORATstpRspInfoField,
        nRequestID: int,
        bIsLast: bool,
    ) -> Any:
        pass

    def OnRspUnSubFundsFlowMarketData(
        self,
        pSpecificSecurity: CTORATstpSpecificSecurityField,
        pRspInfo: CTORATstpRspInfoField,
        nRequestID: int,
        bIsLast: bool,
    ) -> Any:
        pass

    def OnRtnDepthMarketData(self, data: CTORATstpMarketDataField) -> Any:
        tick_data = TickData(
            gateway_name = self.gateway.gateway_name,
            symbol=data.SecurityID,
            exchange=EXCHANGE_TORA2VT[data.ExchangeID],
            datetime=parse_datetime(data.TradingDay, data.UpdateTime),
            name=data.SecurityName,
            volume=0,
            last_price=data.LastPrice,
            last_volume=data.Volume,  # to verify: is this correct?
            limit_up=data.UpperLimitPrice,
            limit_down=data.LowerLimitPrice,
            open_price=data.OpenPrice,
            high_price=data.HighestPrice,
            low_price=data.LowestPrice,
            pre_close=data.PreClosePrice,
            bid_price_1=data.BidPrice1,
            bid_price_2=data.BidPrice2,
            bid_price_3=data.BidPrice3,
            bid_price_4=data.BidPrice4,
            bid_price_5=data.BidPrice5,
            ask_price_1=data.AskPrice1,
            ask_price_2=data.AskPrice2,
            ask_price_3=data.AskPrice3,
            ask_price_4=data.AskPrice4,
            ask_price_5=data.AskPrice5,
            bid_volume_1=data.BidVolume1,
            bid_volume_2=data.BidVolume2,
            bid_volume_3=data.BidVolume3,
            bid_volume_4=data.BidVolume4,
            bid_volume_5=data.BidVolume5,
            ask_volume_1=data.AskVolume1,
            ask_volume_2=data.AskVolume2,
            ask_volume_3=data.AskVolume3,
            ask_volume_4=data.AskVolume4,
            ask_volume_5=data.AskVolume5,
        )
        self.gateway.write_log("OnRtnDepthMarketData")

    def OnRtnSpecialMarketData(
        self, pSpecialMarketData: CTORATstpSpecialMarketDataField
    ) -> Any:
        self.gateway.write_log("OnRtnSpecialMarketData")

    def OnRtnEffectPriceMarketData(
        self, pEffectPriceMarketData: CTORATstpEffectPriceMarketDataField
    ) -> Any:
        self.gateway.write_log("OnRtnEffectPriceMarketData")

    def OnRtnEffectVolumeMarketData(
        self, pEffectVolumeMarketData: CTORATstpEffectVolumeMarketDataField
    ) -> Any:
        self.gateway.write_log("OnRtnEffectVolumeMarketData")

    def OnRtnFundsFlowMarketData(
        self, pFundsFlowMarketData: CTORATstpFundsFlowMarketDataField
    ) -> Any:
        self.gateway.write_log("OnRtnFundsFlowMarketData")


class ToraMdApi:
    def __init__(self, gateway: BaseGateway):
        self.gateway = gateway
        self.md_address = ""

        self._native_api: Optional[CTORATstpMdApi] = None
        self._spi: Optional["ToraMdApi"] = None

    def stop(self):
        """
        :note not thread-safe
        """
        if self._native_api:
            self._native_api.RegisterSpi(None)
            self._spi = None
            self._native_api.Release()
            self._native_api = None

    def join(self):
        """
        :note not thread-safe
        """
        if self._native_api:
            self._native_api.Join()

    def connect(self):
        """
        :note not thread-safe
        """
        self._native_api = CTORATstpMdApi.CreateTstpMdApi()
        self._spi = ToraMdSpi(self, self.gateway)
        self._native_api.RegisterSpi(self._spi)
        self._native_api.RegisterFront(self.md_address)
        self._native_api.Init()
        return True

    def subscribe(self, symbols: List[str], exchange: Exchange):
        self._native_api.SubscribeMarketData(symbols, EXCHANGE_VT2TORA[exchange])
