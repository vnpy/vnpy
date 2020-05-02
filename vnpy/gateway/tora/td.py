import functools
from dataclasses import dataclass, field
from datetime import datetime
from typing import Dict, Optional
import pytz

from vnpy.api.tora.vntora import (CTORATstpConditionOrderField, CTORATstpInputOrderActionField,
                                  CTORATstpInputOrderField, CTORATstpInvestorField,
                                  CTORATstpOrderActionField, CTORATstpOrderField,
                                  CTORATstpPositionField, CTORATstpQryExchangeField,
                                  CTORATstpQryInvestorField, CTORATstpQryMarketDataField,
                                  CTORATstpQryOrderField, CTORATstpQryPositionField,
                                  CTORATstpQrySecurityField, CTORATstpQryShareholderAccountField,
                                  CTORATstpQryTradeField, CTORATstpQryTradingAccountField,
                                  CTORATstpReqUserLoginField, CTORATstpRspInfoField,
                                  CTORATstpRspUserLoginField, CTORATstpSecurityField,
                                  CTORATstpShareholderAccountField, CTORATstpTradeField,
                                  CTORATstpTraderApi, CTORATstpTraderSpi,
                                  CTORATstpTradingAccountField, TORA_TE_RESUME_TYPE,
                                  TORA_TSTP_AF_Delete, TORA_TSTP_FCC_NotForceClose,
                                  TORA_TSTP_HF_Speculation, TORA_TSTP_LACT_AccountID,
                                  TORA_TSTP_OF_Open, TORA_TSTP_OPERW_PCClient)

from vnpy.event import EVENT_TIMER
from vnpy.trader.constant import Direction, Exchange, Offset, OrderType, Status
from vnpy.trader.gateway import BaseGateway
from vnpy.trader.object import AccountData, CancelRequest, ContractData, OrderData, OrderRequest, \
    PositionData, TradeData
from vnpy.trader.utility import get_folder_path
from .constant import DIRECTION_TORA2VT, DIRECTION_VT2TORA, EXCHANGE_TORA2VT, EXCHANGE_VT2TORA, \
    ORDER_STATUS_TORA2VT, ORDER_TYPE_TORA2VT, ORDER_TYPE_VT2TORA, PRODUCT_TORA2VT
from .error_codes import get_error_msg

CHINA_TZ = pytz.timezone("Asia/Shanghai")


def _check_error(none_return: bool = True,
                 error_return: bool = True,
                 write_log: bool = True,
                 print_function_name: bool = False):
    """
    :param none_return: return if info is None
    :param error_return: return if errors
    :param write_log: write_log if errors
    :param print_function_name print function name for every entry of this wrapper
    """

    def wrapper(func):
        @functools.wraps(func)
        def wrapped(self, info, error_info, *args):
            function_name = func.__name__
            if print_function_name:
                print(function_name, "info" if info else "None",
                      error_info.ErrorID)

            # print if errors
            error_code = error_info.ErrorID
            if error_code != 0:
                error_msg = error_info.ErrorMsg
                msg = f'在 {function_name} 中收到错误({error_code})：{error_msg}'
                if write_log:
                    self.gateway.write_log(msg)
                if error_return:
                    return

            # return if flag is set
            if none_return and info is None:
                return

            # call original function
            func(self, info, error_info, *args)

        return wrapped

    return wrapper


class QueryLoop:
    """"""

    def __init__(self, gateway: "BaseGateway"):
        """"""
        self.event_engine = gateway.event_engine

        self._seconds_left = 0
        self._query_functions = [gateway.query_account, gateway.query_position]

    def start(self):
        """"""
        self.event_engine.register(EVENT_TIMER, self._process_timer_event)

    def stop(self):
        """"""
        self.event_engine.unregister(EVENT_TIMER, self._process_timer_event)

    def _process_timer_event(self, event):
        """"""
        if self._seconds_left != 0:
            self._seconds_left -= 1
            return

        # do a query every 2 seconds.
        self._seconds_left = 2

        # get the last one and re-queue it
        # works fine if there is no so much items
        func = self._query_functions.pop(0)
        self._query_functions.append(func)

        # call it
        func()


OrdersType = Dict[str, "OrderInfo"]


class ToraTdSpi(CTORATstpTraderSpi):
    """"""

    def __init__(self, session_info: "SessionInfo",
                 api: "ToraTdApi",
                 gateway: "BaseGateway",
                 orders: OrdersType):
        """"""
        super().__init__()
        self.session_info = session_info
        self.gateway = gateway
        self.orders = orders

        self._api: "ToraTdApi" = api

    def OnRtnTrade(self, info: CTORATstpTradeField) -> None:
        """"""
        try:
            trade_data = TradeData(
                gateway_name=self.gateway.gateway_name,
                symbol=info.SecurityID,
                exchange=EXCHANGE_TORA2VT[info.ExchangeID],
                orderid=info.OrderRef,
                tradeid=info.TradeID,
                direction=DIRECTION_TORA2VT[info.Direction],
                offset=Offset.OPEN,
                price=info.Price,
                volume=info.Volume,
                datetime=datetime.now(CHINA_TZ)
            )
            self.gateway.on_trade(trade_data)
        except KeyError:
            return

    def OnRtnOrder(self, info: CTORATstpOrderField) -> None:
        """"""
        self._api.update_last_local_order_id(int(info.OrderRef))

        try:
            order_data = self.parse_order_field(info)
        except KeyError:
            return
        order_data.status = ORDER_STATUS_TORA2VT[info.OrderStatus]
        self.orders[info.OrderRef] = OrderInfo(local_order_id=info.OrderRef,
                                               exchange_id=info.ExchangeID,
                                               session_id=info.SessionID,
                                               front_id=info.FrontID,
                                               )
        self.gateway.on_order(order_data)

    @_check_error(error_return=False, write_log=False, print_function_name=False)
    def OnErrRtnOrderInsert(self, info: CTORATstpInputOrderField,
                            error_info: CTORATstpRspInfoField) -> None:
        """"""
        try:
            self._api.update_last_local_order_id(int(info.OrderRef))
        except ValueError:
            pass

        try:
            order_data = self.parse_order_field(info)
        except KeyError:
            # no prints here because we don't care about insertion failure.
            return
        order_data.status = Status.REJECTED
        self.gateway.on_order(order_data)
        self.gateway.write_log(f"拒单({order_data.orderid}):"
                               f"错误码:{error_info.ErrorID}, 错误消息:{error_info.ErrorMsg}")

    @_check_error(error_return=False, write_log=False, print_function_name=False)
    def OnErrRtnOrderAction(self, info: CTORATstpOrderActionField,
                            error_info: CTORATstpRspInfoField) -> None:
        """"""
        pass

    @_check_error()
    def OnRtnCondOrder(self, info: CTORATstpConditionOrderField) -> None:
        """"""
        pass

    @_check_error()
    def OnRspOrderAction(self, info: CTORATstpInputOrderActionField,
                         error_info: CTORATstpRspInfoField, request_id: int, is_last: bool) -> None:
        pass

    @_check_error()
    def OnRspOrderInsert(self, info: CTORATstpInputOrderField,
                         error_info: CTORATstpRspInfoField, request_id: int, is_last: bool) -> None:
        """"""
        try:
            order_data = self.parse_order_field(info)
        except KeyError:
            self.gateway.write_log(f"收到无法识别的下单回执({info.OrderRef})")
            return
        self.gateway.on_order(order_data)

    # @_check_error(print_function_name=False)
    # def OnRspQryTrade(self, info: CTORATstpTradeField, error_info: CTORATstpRspInfoField,
    #                   request_id: int, is_last: bool) -> None:
    #     return
    #
    # @_check_error(print_function_name=False)
    # def OnRspQryOrder(self, info: CTORATstpOrderField, error_info: CTORATstpRspInfoField,
    #                   request_id: int, is_last: bool) -> None:
    #     order_data = self.parse_order_field(info)
    #     self.gateway.on_order(order_data)

    @_check_error(print_function_name=False)
    def OnRspQryPosition(self, info: CTORATstpPositionField, error_info: CTORATstpRspInfoField,
                         request_id: int, is_last: bool) -> None:
        """"""
        if info.InvestorID != self.session_info.investor_id:
            self.gateway.write_log("OnRspQryPosition:收到其他账户的仓位信息")
            return
        if info.ExchangeID not in EXCHANGE_TORA2VT:
            self.gateway.write_log(
                f"OnRspQryPosition:忽略不支持的交易所：{info.ExchangeID}")
            return
        volume = info.CurrentPosition
        frozen = info.HistoryPosFrozen + info.TodayBSFrozen + \
            info.TodayPRFrozen + info.TodaySMPosFrozen
        position_data = PositionData(
            gateway_name=self.gateway.gateway_name,
            symbol=info.SecurityID,
            exchange=EXCHANGE_TORA2VT[info.ExchangeID],
            direction=Direction.NET,
            volume=volume,  # verify this: which one should vnpy use?
            frozen=frozen,  # verify this: which one should i use?
            price=info.TotalPosCost / volume,
            # verify this: is this formula correct
            pnl=info.LastPrice * volume - info.TotalPosCost,
            yd_volume=info.HistoryPos,
        )
        self.gateway.on_position(position_data)

    @_check_error(print_function_name=False)
    def OnRspQryTradingAccount(self, info: CTORATstpTradingAccountField,
                               error_info: CTORATstpRspInfoField, request_id: int,
                               is_last: bool) -> None:
        """"""
        self.session_info.account_id = info.AccountID
        account_data = AccountData(
            gateway_name=self.gateway.gateway_name,
            accountid=info.AccountID,
            balance=info.Available,
            frozen=info.FrozenCash + info.FrozenMargin + info.FrozenCommission
        )
        self.gateway.on_account(account_data)

    @_check_error()
    def OnRspQryShareholderAccount(self, info: CTORATstpShareholderAccountField,
                                   error_info: CTORATstpRspInfoField, request_id: int,
                                   is_last: bool) -> None:
        """"""
        exchange = EXCHANGE_TORA2VT[info.ExchangeID]
        self.session_info.shareholder_ids[exchange] = info.ShareholderID

    @_check_error(print_function_name=False)
    def OnRspQryInvestor(self, info: CTORATstpInvestorField, error_info: CTORATstpRspInfoField,
                         request_id: int, is_last: bool) -> None:
        """"""
        self.session_info.investor_id = info.InvestorID

    @_check_error(none_return=False, print_function_name=False)
    def OnRspQrySecurity(self, info: CTORATstpSecurityField, error_info: CTORATstpRspInfoField,
                         request_id: int, is_last: bool) -> None:
        """"""
        if is_last:
            self.gateway.write_log("合约信息查询成功")
        if not info:
            return

        if info.ProductID not in PRODUCT_TORA2VT:
            return
        if info.ExchangeID not in EXCHANGE_TORA2VT:
            return
        contract_data = ContractData(
            gateway_name=self.gateway.gateway_name,
            symbol=info.SecurityID,
            exchange=EXCHANGE_TORA2VT[info.ExchangeID],
            name=info.SecurityName,
            product=PRODUCT_TORA2VT[info.ProductID],
            size=info.VolumeMultiple,  # to verify
            pricetick=info.PriceTick,
            min_volume=info.MinLimitOrderBuyVolume,  # verify: buy?sell
            stop_supported=False,
            net_position=True,
            history_data=False,
        )
        self.gateway.on_contract(contract_data)

    def OnFrontConnected(self) -> None:
        """"""
        self.gateway.write_log("交易服务器连接成功")
        self._api.login()

    @_check_error(print_function_name=False)
    def OnRspUserLogin(self, info: CTORATstpRspUserLoginField,
                       error_info: CTORATstpRspInfoField, request_id: int, is_last: bool) -> None:
        """"""
        self._api.update_last_local_order_id(int(info.MaxOrderRef))
        self.session_info.front_id = info.FrontID
        self.session_info.session_id = info.SessionID
        self.gateway.write_log("交易服务器登录成功")
        self._api.query_initialize_status()

        self._api.start_query_loop()  # stop at ToraTdApi.stop()

    def OnFrontDisconnected(self, error_code: int) -> None:
        """"""
        self.gateway.write_log(
            f"交易服务器连接断开({error_code}):{get_error_msg(error_code)}")

    def parse_order_field(self, info):
        """
        :raise KeyError
        :param info:
        :return:
        """
        opt = info.OrderPriceType
        tc = info.TimeCondition
        vc = info.VolumeCondition
        order_type = ORDER_TYPE_TORA2VT[(opt, tc, vc)]
        order_data = OrderData(
            gateway_name=self.gateway.gateway_name,
            symbol=info.SecurityID,
            exchange=EXCHANGE_TORA2VT[info.ExchangeID],
            orderid=info.OrderRef,
            type=order_type,
            direction=DIRECTION_TORA2VT[info.Direction],
            offset=Offset.OPEN,
            price=info.LimitPrice,
            volume=info.VolumeTotalOriginal,
            traded=0,
            status=Status.NOTTRADED,
            datetime=datetime.now(CHINA_TZ)  # note: server doesn't provide a timestamp
        )
        return order_data


class ToraTdApi:

    def __init__(self, gateway: BaseGateway):
        """"""
        self.gateway = gateway

        self.username = ""
        self.password = ""
        self.td_address = ""

        self.session_info: "SessionInfo" = SessionInfo()
        self.orders: OrdersType = {}

        self._native_api: Optional["CTORATstpTraderApi"] = None
        self._spi: Optional["ToraTdSpi"] = None
        self._query_loop: Optional["QueryLoop"] = None

        self._last_req_id = 0
        self._next_local_order_id = int(1e5)

    def get_shareholder_id(self, exchange: Exchange):
        """"""
        return self.session_info.shareholder_ids[exchange]

    def update_last_local_order_id(self, new_val: int):
        """"""
        cur = self._next_local_order_id
        self._next_local_order_id = max(cur, new_val + 1)

    def _if_error_write_log(self, error_code: int, function_name: str):
        """"""
        if error_code != 0:
            error_msg = get_error_msg(error_code)
            msg = f'在执行 {function_name} 时发生错误({error_code}): {error_msg}'
            self.gateway.write_log(msg)
            return True

    def _get_new_req_id(self):
        """"""
        req_id = self._last_req_id
        self._last_req_id += 1
        return req_id

    def _get_new_order_id(self) -> str:
        """"""
        order_id = self._next_local_order_id
        self._next_local_order_id += 1
        return str(order_id)

    def query_contracts(self):
        """"""
        info = CTORATstpQrySecurityField()
        err = self._native_api.ReqQrySecurity(info, self._get_new_req_id())
        self._if_error_write_log(err, "query_contracts")

    def query_exchange(self, exchange: Exchange):
        """"""
        info = CTORATstpQryExchangeField()
        info.ExchangeID = EXCHANGE_VT2TORA[exchange]
        err = self._native_api.ReqQryExchange(info, self._get_new_req_id())

        self._if_error_write_log(err, "query_exchange")

    def query_market_data(self, symbol: str, exchange: Exchange):
        """"""
        info = CTORATstpQryMarketDataField()
        info.ExchangeID = EXCHANGE_VT2TORA[exchange]
        info.SecurityID = symbol
        err = self._native_api.ReqQryMarketData(info, self._get_new_req_id())
        self._if_error_write_log(err, "query_market_data")

    def stop(self):
        """"""
        self.stop_query_loop()

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
        self._native_api = CTORATstpTraderApi.CreateTstpTraderApi(
            flow_path, True)
        self._spi = ToraTdSpi(self.session_info, self,
                              self.gateway, self.orders)
        self._native_api.RegisterSpi(self._spi)
        self._native_api.RegisterFront(self.td_address)
        self._native_api.SubscribePublicTopic(
            TORA_TE_RESUME_TYPE.TORA_TERT_RESTART)
        self._native_api.SubscribePrivateTopic(
            TORA_TE_RESUME_TYPE.TORA_TERT_RESTART)
        self._native_api.Init()
        return True

    def send_order(self, req: OrderRequest):
        """"""
        if req.type is OrderType.STOP:
            raise NotImplementedError()
        if req.type is OrderType.FAK or req.type is OrderType.FOK:
            assert req.exchange is Exchange.SZSE
        order_id = self._get_new_order_id()
        info = CTORATstpInputOrderField()
        info.InvestorID = self.session_info.investor_id
        info.SecurityID = req.symbol
        info.OrderRef = order_id
        info.ShareholderID = self.get_shareholder_id(req.exchange)

        info.ExchangeID = EXCHANGE_VT2TORA[req.exchange]
        info.Direction = DIRECTION_VT2TORA[req.direction]
        info.CombOffsetFlag = TORA_TSTP_OF_Open
        info.CombHedgeFlag = TORA_TSTP_HF_Speculation
        if req.type is not OrderType.MARKET:
            info.LimitPrice = req.price
        info.VolumeTotalOriginal = int(req.volume)

        opt, tc, vc = ORDER_TYPE_VT2TORA[req.type]
        info.OrderPriceType = opt
        info.TimeCondition = tc
        info.VolumeCondition = vc

        # info.MinVolume = 0  # 当成交量类型为MV时有效
        info.ForceCloseReason = TORA_TSTP_FCC_NotForceClose

        # info.IsSwapOrder = 0  # 不支持互换单
        # info.UserForceClose = 0  # 用户强评标志
        info.Operway = TORA_TSTP_OPERW_PCClient  # 委托方式：PC端委托

        self.orders[order_id] = OrderInfo(info.OrderRef,
                                          info.ExchangeID,
                                          self.session_info.session_id,
                                          self.session_info.front_id,
                                          )
        self.gateway.on_order(req.create_order_data(
            order_id, self.gateway.gateway_name))

        # err = self._native_api.ReqCondOrderInsert(info, self._get_new_req_id())
        err = self._native_api.ReqOrderInsert(info, self._get_new_req_id())
        self._if_error_write_log(err, "send_order:ReqOrderInsert")

    def cancel_order(self, req: CancelRequest):
        """"""
        info = CTORATstpInputOrderActionField()
        info.InvestorID = self.session_info.investor_id
        # 没有的话：(16608)：VIP:未知的交易所代码
        info.ExchangeID = EXCHANGE_VT2TORA[req.exchange]
        info.SecurityID = req.symbol
        # info.OrderActionRef = str(self._get_new_req_id())

        order_info = self.orders[req.orderid]

        info.OrderRef = req.orderid
        info.FrontID = order_info.front_id
        info.SessionID = order_info.session_id

        info.ActionFlag = TORA_TSTP_AF_Delete  # (12673)：VIP:撤单与原报单信息不符
        # info.ActionFlag = TORA_TSTP_AF_ForceDelete  # (12368)：VIP:报单状态异常

        err = self._native_api.ReqOrderAction(info, self._get_new_req_id())
        self._if_error_write_log(err, "cancel_order:ReqOrderAction")

    def query_initialize_status(self):
        """"""
        self.query_contracts()
        self.query_investors()
        self.query_shareholder_ids()
        self.query_accounts()
        self.query_positions()
        self.query_orders()
        self.query_trades()

    def query_accounts(self):
        """"""
        info = CTORATstpQryTradingAccountField()
        err = self._native_api.ReqQryTradingAccount(
            info, self._get_new_req_id())
        self._if_error_write_log(err, "query_accounts")

    def query_shareholder_ids(self):
        """"""
        info = CTORATstpQryShareholderAccountField()
        err = self._native_api.ReqQryShareholderAccount(
            info, self._get_new_req_id())
        self._if_error_write_log(err, "query_shareholder_ids")

    def query_investors(self):
        """"""
        info = CTORATstpQryInvestorField()
        err = self._native_api.ReqQryInvestor(info, self._get_new_req_id())
        self._if_error_write_log(err, "query_investors")

    def query_positions(self):
        """"""
        info = CTORATstpQryPositionField()
        err = self._native_api.ReqQryPosition(info, self._get_new_req_id())
        self._if_error_write_log(err, "query_positions")

    def query_orders(self):
        """"""
        info = CTORATstpQryOrderField()
        err = self._native_api.ReqQryOrder(info, self._get_new_req_id())
        self._if_error_write_log(err, "query_orders")

    def query_trades(self):
        """"""
        info = CTORATstpQryTradeField()
        err = self._native_api.ReqQryTrade(info, self._get_new_req_id())
        self._if_error_write_log(err, "query_trades")

    def start_query_loop(self):
        """"""
        if not self._query_loop:
            self._query_loop = QueryLoop(self.gateway)
            self._query_loop.start()

    def stop_query_loop(self):
        """"""
        if self._query_loop:
            self._query_loop.stop()
            self._query_loop = None


@dataclass()
class OrderInfo:
    local_order_id: str
    exchange_id: str
    session_id: int
    front_id: int


@dataclass()
class SessionInfo:
    investor_id: str = None  # one investor per session
    shareholder_ids: Dict[Exchange, str] = field(
        default_factory=dict)  # one share holder id per exchange
    account_id: str = None  # one account per session
    front_id: int = None
    session_id: int = None
