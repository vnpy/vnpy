from typing import Optional
from vnpy.trader.gateway import BaseGateway
from vnpy.trader.utility import get_folder_path

from vnpy.api.tora.vntora import (
    CTORATstpTraderApi,
    CTORATstpTraderSpi,
    TORA_TSTP_EXD_SSE,
    CTORATstpRspInfoField,
    CTORATstpRspUserLoginField,
    CTORATstpQrySecurityField, CTORATstpSecurityField, CTORATstpReqUserLoginField,
    TORA_TSTP_LACT_AccountID, CTORATstpQryExchangeField, CTORATstpQryMarketDataField)

from .error_codes import get_error_msg


class ToraTdSpi(CTORATstpTraderSpi):
    def __init__(self, api: "ToraTdApi", gateway: "BaseGateway"):
        super().__init__()
        self.gateway = gateway
        self._api = api

    def OnRspQrySecurity(self, pSecurity: CTORATstpSecurityField, pRspInfo: CTORATstpRspInfoField,
                         nRequestID: int, bIsLast: bool) -> None:
        print("onrspqrysec")

    def OnFrontConnected(self) -> None:
        self.gateway.write_log("交易服务器连接成功")
        self._api.login()

    def OnRspUserLogin(self, pRspUserLoginField: CTORATstpRspUserLoginField,
                       pRspInfo: CTORATstpRspInfoField, nRequestID: int, bIsLast: bool) -> None:
        self.gateway.write_log("交易服务器登录成功")
        self._api.query_contracts()
        self._api.query_exchange()
        self._api.query_market_data()

    def OnFrontDisconnected(self, nReason: int) -> None:
        self.gateway.write_log("交易服务器连接断开")


class ToraTdApi:
    def __init__(self, gateway: BaseGateway):
        self.gateway = gateway

        self.username = ""
        self.password = ""
        self.td_address = ""

        self._native_api: Optional["CTORATstpTraderApi"] = None
        self._spi: Optional["ToraTdSpi"] = None

        self._last_req_id = 0

    def _if_error_write_log(self, error_code: int, function_name: str):
        if error_code != 0:
            err_msg = get_error_msg(error_code)
            msg = f'在执行 {function_name} 时发生错误({error_code}): {err_msg}'
            self.gateway.write_log(msg)
            return True

    def _get_new_req_id(self):
        req_id = self._last_req_id
        self._last_req_id += 1
        return req_id

    def query_contracts(self):
        info = CTORATstpQrySecurityField()
        # info.ExchangeID = TORA_TSTP_EXD_SSE
        err = self._native_api.ReqQrySecurity(info, self._get_new_req_id())
        self._if_error_write_log(err, "ReqQrySecurity")

    def query_exchange(self):
        info = CTORATstpQryExchangeField()
        info.ExchangeID = TORA_TSTP_EXD_SSE
        err = self._native_api.ReqQryExchange(info, self._get_new_req_id())

        self._if_error_write_log(err, "ReqQryExchange")

    def query_market_data(self):
        info = CTORATstpQryMarketDataField()
        info.ExchangeID = TORA_TSTP_EXD_SSE
        info.SecurityID = "010303"
        err = self._native_api.ReqQryMarketData(info, self._get_new_req_id())
        self._if_error_write_log(err, "ReqQryMarketData")

    def stop(self):
        if self._native_api:
            self._native_api.RegisterSpi(None)
            self._spi = None
            self._native_api.Release()
            self._native_api = None

    def join(self):
        if self._native_api:
            self._native_api.Join()

    def login(self):
        """
        send login request using self.username, self.password
        :return:
        """
        info = CTORATstpReqUserLoginField()
        info.LogInAccount = self.username
        info.LogInAccountType = TORA_TSTP_LACT_AccountID
        info.Password = self.password
        self._native_api.ReqUserLogin(info, self._get_new_req_id())

    def connect(self):
        """
        connect to self.td_address using self.username, self.password
        :return:
        """
        flow_path = str(get_folder_path(self.gateway.gateway_name.lower()))
        self._native_api = CTORATstpTraderApi.CreateTstpTraderApi(flow_path, True)
        self._spi = ToraTdSpi(self, self.gateway)
        self._native_api.RegisterSpi(self._spi)
        self._native_api.RegisterFront(self.td_address)
        self._native_api.Init()
        return True
