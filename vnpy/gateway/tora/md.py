from datetime import datetime
from typing import Any, List, Optional

from vnpy.api.tora.vntora import (CTORATstpMarketDataField, CTORATstpMdApi, CTORATstpMdSpi,
                                  CTORATstpRspInfoField, CTORATstpRspUserLoginField,
                                  CTORATstpUserLogoutField)

from vnpy.gateway.tora.error_codes import get_error_msg
from vnpy.trader.constant import Exchange
from vnpy.trader.gateway import BaseGateway
from vnpy.trader.object import (
    TickData,
)
from .constant import EXCHANGE_TORA2VT, EXCHANGE_VT2TORA


def parse_datetime(date: str, time: str):
    # sampled :
    # date: '20190611'
    # time: '16:28:24'

    return datetime.strptime(f'{date}-{time}', "%Y%m%d-%H:%M:%S")


class ToraMdSpi(CTORATstpMdSpi):
    """"""

    def __init__(self, api: "ToraMdApi", gateway: "BaseGateway"):
        """"""
        super().__init__()
        self.gateway = gateway

        self._api = api

    def OnFrontConnected(self) -> Any:
        """"""
        self.gateway.write_log("行情服务器连接成功")

    def OnFrontDisconnected(self, error_code: int) -> Any:
        """"""
        self.gateway.write_log(
            f"行情服务器连接断开({error_code}):{get_error_msg(error_code)}")

    def OnRspError(
        self, error_info: CTORATstpRspInfoField, request_id: int, is_last: bool
    ) -> Any:
        """"""
        error_id = error_info.ErrorID
        error_msg = error_info.ErrorMsg
        self.gateway.write_log(f"行情服务收到错误消息({error_id})：{error_msg}")

    def OnRspUserLogin(
        self,
        info: CTORATstpRspUserLoginField,
        error_info: CTORATstpRspInfoField,
        request_id: int,
        is_last: bool,
    ) -> Any:
        """"""
        error_id = error_info.ErrorID
        if error_id != 0:
            error_msg = error_info.ErrorMsg
            self.gateway.write_log(f"行情服务登录失败({error_id})：{error_msg}")
            return
        self.gateway.write_log("行情服务器登录成功")

    def OnRspUserLogout(
        self,
        info: CTORATstpUserLogoutField,
        error_info: CTORATstpRspInfoField,
        request_id: int,
        is_last: bool,
    ) -> Any:
        """"""
        error_id = error_info.ErrorID
        if error_id != 0:
            error_msg = error_info.ErrorMsg
            self.gateway.write_log(f"行情服务登出失败({error_id})：{error_msg}")
            return
        self.gateway.write_log("行情服务器登出成功")

    def OnRtnDepthMarketData(self, data: CTORATstpMarketDataField) -> Any:
        """"""
        if data.ExchangeID not in EXCHANGE_TORA2VT:
            return
        tick_data = TickData(
            gateway_name=self.gateway.gateway_name,
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
        self.gateway.on_tick(tick_data)


class ToraMdApi:
    """"""

    def __init__(self, gateway: BaseGateway):
        """"""
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
        """"""
        err = self._native_api.SubscribeMarketData(
            symbols, EXCHANGE_VT2TORA[exchange])
        self._if_error_write_log(err, "subscribe")

    def _if_error_write_log(self, error_code: int, function_name: str):
        """"""
        if error_code != 0:
            error_msg = get_error_msg(error_code)
            msg = f'在执行 {function_name} 时发生错误({error_code}): {error_msg}'
            self.gateway.write_log(msg)
            return True
