import time
from dataclasses import dataclass
from datetime import datetime
from typing import Dict, Tuple
import pytz

from vnpy.api.es import MdApi, TdApi
from vnpy.event import EventEngine
from vnpy.trader.utility import get_folder_path
from vnpy.trader.constant import (
    Exchange,
    Product,
    Direction,
    Status,
    OrderType
)
from vnpy.trader.gateway import BaseGateway
from vnpy.gateway.es import es_gateway
from vnpy.trader.object import (
    CancelRequest,
    OrderRequest,
    SubscribeRequest,
    TickData,
    ContractData,
    OrderData,
    TradeData,
    PositionData,
    AccountData
)


PRODUCT_TYPE_ES2VT: Dict[str, Product] = {
    "P": Product.SPOT,
    "F": Product.FUTURES,
    "O": Product.OPTION,
    "Z": Product.INDEX,
    "T": Product.EQUITY,
}

EXCHANGE_ES2VT: Dict[str, Exchange] = {
    "CFFEX": Exchange.CFFEX,
    "SHFE": Exchange.SHFE,
    "CZCE": Exchange.CZCE,
    "DCE": Exchange.DCE,
    "INE": Exchange.INE
}

EXCHANGE_VT2ES: Dict[Exchange, str] = {v: k for k, v in EXCHANGE_ES2VT.items()}

DIRECTION_ES2VT: Dict[str, Direction] = {
    "N": Direction.NET,
    "B": Direction.LONG,
    "S": Direction.SHORT,
}
DIRECTION_VT2ES: Dict[Direction, str] = {
    v: k for k, v in DIRECTION_ES2VT.items()}

STATUS_ES2VT: Dict[str, Status] = {
    "0": Status.SUBMITTING,
    "1": Status.SUBMITTING,
    "4": Status.NOTTRADED,
    "5": Status.PARTTRADED,
    "6": Status.ALLTRADED,
    "7": Status.CANCELLED,
    "9": Status.CANCELLED,
}

ORDERTYPE_ES2VT: Dict[str, OrderType] = {
    "1": OrderType.MARKET,
    "2": OrderType.LIMIT
}
ORDERTYPE_VT2ES = {v: k for k, v in ORDERTYPE_ES2VT.items()}

ERROR_VT2ES: Dict[str, int] = {
    "TAPIERROR_SUCCEED": 0
}

LOGLEVEL_VT2TAP: Dict[str, str] = {
    "APILOGLEVEL_NONE": "N",
    "APILOGLEVEL_ERROR": "E",
    "APILOGLEVEL_WARNING": "W",
    "APILOGLEVEL_DEBUG": "D"
}
LOGLEVEL_VT2ES: Dict[str, str] = {
    "APILOGLEVEL_ERROR": "1",
    "APILOGLEVEL_WARNING": "2",
    "APILOGLEVEL_DEBUG": "3"
}

commodity_infos: Dict[str, "CommodityInfo"] = {}
contract_infos: Dict[Tuple[str, "Exchange"], "ContractInfo"] = {}

FLAG_VT2ES: Dict[str, str] = {
    "APIYNFLAG_YES": "Y",
    "APIYNFLAG_NO": "N",
    "TAPI_CALLPUT_FLAG_CALL": "C",
    "TAPI_CALLPUT_FLAG_PUT": "P",
    "TAPI_CALLPUT_FLAG_NONE": "N"
}

CHINA_TZ = pytz.timezone("Asia/Shanghai")
default_setting = {
    "行情账号": "Q497525430",
    "行情密码": "797878",
    "行情服务器": "61.163.243.173",
    "行情端口": 6161,
    "交易账号": "Q497525430",
    "交易密码": "797878",
    "交易服务器": "61.163.243.173",
    "交易端口": 6160,
    "授权码": "Demo_TestCollect"
}

setting = default_setting
quote_username = setting["行情账号"]
quote_password = setting["行情密码"]
quote_host = setting["行情服务器"]
quote_port = setting["行情端口"]
trade_username = setting["交易账号"]
trade_password = setting["交易密码"]
trade_host = setting["交易服务器"]
trade_port = setting["交易端口"]
auth_code = setting["授权码"]



data = {
    "UserNo": quote_username,
    "Password": quote_password,
    "ISModifyPassword": "N",
    "ISDDA": "N"
}

es_contract = {
    "ExchangeNo": "SHFE",
    "CommodityType": "F",
    "CommodityNo":  "AG",
    "ContractNo1": "2012",
    "CallOrPutFlag1": "N",
    "CallOrPutFlag2": "N"
}

es_order_SFHE= {
    "AccountNo": "Q497525430",
    "ExchangeNo": "SHFE",
    "CommodityType": "F",
    "CommodityNo": "AG",
    "ContractNo": "2012",
    "OrderSource": 'A',
    "IsRiskOrder": "N",
    "HedgeFlag": "T",
    "PositionEffect": "O",
    #"StrikePrice":
    "OrderType":"2",
    "OrderSide":"B",
    "OrderPrice":6400,
    "OrderQty":1
}

es_order_ZCE = {
    "AccountNo": "Q497525430",
    "ExchangeNo": "ZCE",
    "CommodityType": "F",
    "CommodityNo": "SR",
    "ContractNo": "101",
    "OrderSource": 'A',
    "IsRiskOrder": "N",
    "HedgeFlag": "T",
    "PositionEffect": "O",
    #"StrikePrice":
    "OrderType": "2",
    "OrderSide": "B",
    "OrderPrice": 4920,
    "OrderQty": 1
}
class EsGateway(BaseGateway):
    """
    VN Trader gateway for Esunny(new version) 9.0.
    """

    default_setting = {
        "行情账号": "Q497525430",
        "行情密码": "797878",
        "行情服务器": "61.163.243.17",
        "行情端口": 6161,
        "交易账号": "Q497525430",
        "交易密码": "797878",
        "交易服务器": "61.163.243.173",
        "交易端口": 6160,
        "授权码": "Demo_TestCollect"
    }

    exchanges = list(EXCHANGE_VT2ES.keys())

    def __init__(self, event_engine: EventEngine):
        """"""
        super().__init__(event_engine, "ES")

        self.md_api = QuoteApi(self)
        self.td_api = EsTradeApi(self)

    def connect(self, setting: dict) -> None:
        """"""
        quote_username = setting["行情账号"]
        quote_password = setting["行情密码"]
        quote_host = setting["行情服务器"]
        quote_port = setting["行情端口"]
        trade_username = setting["交易账号"]
        trade_password = setting["交易密码"]
        trade_host = setting["交易服务器"]
        trade_port = setting["交易端口"]
        auth_code = setting["授权码"]

        self.md_api.connect(
            quote_username,
            quote_password,
            quote_host,
            quote_port,
            auth_code
        )
        self.td_api.connect(
            trade_username,
            trade_password,
            trade_host,
            trade_port,
            auth_code
        )

    def close(self) -> None:
        """"""
        pass

    def subscribe(self, req: SubscribeRequest) -> None:
        """"""
        self.md_api.subscribe(req)

    def send_order(self, req: OrderRequest) -> str:
        """"""
        return self.td_api.send_order(req)

    def cancel_order(self, req: CancelRequest) -> None:
        """"""
        self.td_api.cancel_order(req)

    def query_account(self) -> None:
        """"""
        pass

    def query_position(self) -> None:
        """"""
        pass

class QuoteApi(MdApi):
    """
    Implementation of ES quote api.
    """

    def __init__(self, gateway: EsGateway):
        """"""
        super().__init__()

        self.gateway: EsGateway = gateway
        self.gateway_name: str = "ES"
   

    def onRspLogin(self, error: int, data: dict) -> None:
        """
        Callback of login request.
        """

        print(onRspLogin)
        if error != ERROR_VT2ES["TAPIERROR_SUCCEED"]:
            self.gateway.write_log(f"行情服务器登录失败：{error}")
        else:
            self.gateway.write_log("行情服务器登录成功")

    def onAPIReady(self) -> None:
        """
        Callback when API is ready for sending requests or queries.
        """
        print("onAPIReady_md ok")
        self.subscribeQuote(es_contract)
        print("subscribeQuote", i)

    def onDisconnect(self, reason: int) -> None:
        """
        Callback when connection to TAP server is lost.
        """
        self.gateway.write_log(f"行情服务器连接断开，原因：{reason}")
        print("onDisconnect", {reason})
    def onRspSubscribeQuote(
        self,
        session: int,
        error: int,
        last: str,
        data: dict
    ) -> None:
        """
        Callback of subscribe market data request.
        """
        
        if error != ERROR_VT2ES["TAPIERROR_SUCCEED"]:
            print("onDisconnect", {error})
            self.gateway.write_log(f"订阅行情失败：{error}")
        else:
            self.update_tick(data)

    def onRtnQuote(self, data: dict) -> None:
        """
        Callback of new data update.
        """
        self.update_tick(data)

    def update_tick(self, data: dict) -> None:
        """
        Convert TAP quote data structure into TickData event and push it.
        """
        symbol = data["CommodityNo"] + data["ContractNo1"]
        exchange = EXCHANGE_ES2VT[data["ExchangeNo"]]

        contract_info = contract_infos.get((symbol, exchange), None)
        if not contract_info:
            print(f"行情合约信息无法匹配：{symbol}和{exchange}")
            self.gateway.write_log(f"行情合约信息无法匹配：{symbol}和{exchange}")
            return

        tick = TickData(
            symbol=symbol,
            exchange=exchange,
            datetime=parse_datetime(data["DateTimeStamp"]),
            name=contract_info.name,
            volume=data["QTotalQty"],
            last_price=data["QLastPrice"],
            last_volume=data["QLastQty"],
            limit_up=data["QLimitUpPrice"],
            limit_down=data["QLimitDownPrice"],
            open_price=data["QOpeningPrice"],
            high_price=data["QHighPrice"],
            low_price=data["QLowPrice"],
            pre_close=data["QPreClosingPrice"],
            bid_price_1=data["QBidPrice"][0],
            bid_price_2=data["QBidPrice"][1],
            bid_price_3=data["QBidPrice"][2],
            bid_price_4=data["QBidPrice"][3],
            bid_price_5=data["QBidPrice"][4],
            ask_price_1=data["QAskPrice"][0],
            ask_price_2=data["QAskPrice"][1],
            ask_price_3=data["QAskPrice"][2],
            ask_price_4=data["QAskPrice"][3],
            ask_price_5=data["QAskPrice"][4],
            bid_volume_1=data["QBidQty"][0],
            bid_volume_2=data["QBidQty"][1],
            bid_volume_3=data["QBidQty"][2],
            bid_volume_4=data["QBidQty"][3],
            bid_volume_5=data["QBidQty"][4],
            ask_volume_1=data["QAskQty"][0],
            ask_volume_2=data["QAskQty"][1],
            ask_volume_3=data["QAskQty"][2],
            ask_volume_4=data["QAskQty"][3],
            ask_volume_5=data["QAskQty"][4],
            gateway_name=self.gateway_name,
        )
        self.gateway.on_tick(tick)


class EsTradeApi(TdApi):
    """
    Implementation of TAP trade api.
    """

    def __init__(self, gateway: EsGateway):
        """"""
        super().__init__()

        self.gateway: EsGateway = gateway
        #self.gateway_name: str = gateway.gateway_name
        self.gateway_name: str = "ES"

        self.account_no = ""        # required when sending order request
        self.cancel_reqs = {}       # waiting cancel order requests before OrderNo received

        # for mapping relationship between TAP OrderNo and ClientOrderNo
        self.sys_local_map = {}
        self.local_sys_map = {}
        self.sys_server_map = {}
    

    def onConnect(self, userNo:str ) -> None:
        """
        Callback when connection is established with TAP server.
        """
        #self.gateway.write_log("交易服务器连接成功")
        print("onConnect ok")

    def onRspLogin(self, userNo: str, error: int, data: dict) -> None:
        """
        Callback of login request.
        """
        if error != ERROR_VT2ES["TAPIERROR_SUCCEED"]:
            print(f"交易服务器登录失败，错误码：{error}")
            #self.gateway.write_log(f"交易服务器登录失败，错误码：{error}")
            
        else:
            #self.gateway.write_log("交易服务器登录成功")
            print(f"onRspLogin ok  ")

    def onAPIReady(self, userNo: str) -> None:
        """
        Callback when API is ready for sending requests or queries.

        """
        print("onAPIReady_td2 ok")
        print("getPosition: ", td.getPosition(trade_username))  # ok 待还原参数
        print("getAccount: ", td.getAccount(trade_username))  # ok 待还原参数

        print("getExchange: ", td.getExchange(trade_username))
        print("getCommodity: ", td.getCommodity(trade_username))
        print("getContract: ", td.getContract(trade_username))

        print("getFund: ", td.getFund(trade_username))
        print("getOrder: ", td.getOrder(trade_username))
        print("getFill: ", td.getFill(trade_username))
        print("getClose: ", td.getClose(trade_username))
        print("getExchangeStateInfo: ", td.getExchangeStateInfo(trade_username,1,1,"N"))
        print("getUpperChannel: ", td.getUpperChannel(trade_username,1,4,"N"))
        #print("getCurrency: ", td.getCurrency(trade_username,1,4,"N"))  #bad -28当前用户对应的系统暂不支持的功能
        
        req = {
            "CommodityType": "F",
            
        }
        #print("qryAccountRent: ", td.qryAccountRent(trade_username, 1, req)) #ok



        #i = td.insertOrder(trade_username, 1979, es_order_ZCE)  #ok
        
        req = {
            "ServerFlag" : "c",
            "OrderNo" : "OC200813SQ00018153"
        }
        i = td.cancelOrder(trade_username, 1979, req)  #ok
        print("cancelOrder:",i)
        OrderProcess = {
            "ServerFlag": "C",
            "OrderNo": "1"
        }
        i = td.qryOrderProcess(trade_username,0,OrderProcess)   #没死也没回报
        print("qryOrderProcess", i) 
        

        #i = td.qryDeepQuote(trade_username, 0, es_contract)   #已无此权限
        


    def onDisconnect(self, user:str, nReasonCode: int)-> None:
        
        print(f"onDisconnect,nReasonCode:   {nReasonCode}")
    
    def onRspSubmitUserLoginInfo(self, uerNo: str, nSessionID: int, data: dict) -> None:

        print(f"onRspSubmitUserLoginInfo ok, nSessionID:  {nSessionID} data: {data}")
    
    def onRtnErrorMsg(self, userNo:str, ErrorMsg:str):

        print(f"onRtnErrorMsg ok, ErrorMsg: {ErrorMsg}")

    def onRtnExchangeStateInfo(self, userNo: str, data: dict) -> None: #bad

        print("onRtnExchangeStateInfo ok")
        
    def onRtnPosition(self, userNo: str, data: dict) -> None:

        print("onRtnPosition ok") 
    
    def onRspQryOrderProcess(self,  userNo, nRequestID, nErrorCode, last, data) -> None:

        print("onRspQryOrderProcess ok")

    # 60105  操作账号没有上期挂单查询权限 交易所已经取消 函数能正常运行不退出
    #def onRspQryDeepQuote(self,  userNo, nRequestID, nErrorCode, last, data) -> None:
    #    print(f"onRspQryDeepQuote ok,{nRequestID}, {nErrorCode} ,{last},  {data}")
    
    def onRspAccountRentInfo(self, userNo, nRequestID, nErrorCode, last, data) -> None: 

        print(f"onRspAccountRentInfo ok")


#--test md----------------------------------
md = QuoteApi("ES")
td = EsTradeApi("ES")  # es_gateway
print(time.strftime('%Y-%m-%d %H:%M:%S'))
path = ('C:\\Users\\mel_6\\.vntrader\\es')
path = get_folder_path(td.gateway_name.lower())
req = {
    "AuthCode": auth_code,
    "KeyOperationLogPath": str(path)
}

""" print("-------------------------test md ----------------------")
i = md.getTapQuoteAPIVersion()
print("getTapQuoteAPIVersion", i)

print("init", md.init())

i = md.setTapQuoteAPIDataPath(str(path))    # ok
print("setTapQuoteAPIDataPath", i)
i = md.setTapQuoteAPILogLevel(LOGLEVEL_VT2TAP["APILOGLEVEL_DEBUG"])  //-10002
print("setTapQuoteAPILogLevel", i, LOGLEVEL_VT2TAP["APILOGLEVEL_DEBUG"])

md.createTapQuoteAPI(req, 0)
print("createTapQuoteAPI", i)

i=md.setHostAddress(quote_host, quote_port)
print("setHostAddress",i)

i = md.login(data)
print("mdlogin", i)

print("finish...")
while True:
    time.sleep(3) """

#--test td------------------------------
print("---test td --")

print(path)
#i = td.setEsTradeAPIDataPath(str(path))  # ?执行就退出 md ok
#print("setEsTradeAPIDataPath", i)
#i = td.setEsTradeAPILogLevel(LOGLEVEL_VT2ES["APILOGLEVEL_DEBUG"])   # md 报错 td退出
#print("setEsTradeAPILogLevel", i)

td.createEsTradeAPI()

td.init()
SystemType_VT2ES: Dict[str, int] = {
    "TAPI_SYSTEM_TYPE_ESUNNY": 1
}
LoginType_VT2ES: Dict[str, int] = {
    "TAPI_LOGINTYPE_NORMAL": 1 
}
UserInfo = {
    "SystemType": SystemType_VT2ES["TAPI_SYSTEM_TYPE_ESUNNY"],
    "UserNo": trade_username,
    "LoginIP": trade_host,
    "LoginProt": trade_port,
    "LoginType": LoginType_VT2ES["TAPI_LOGINTYPE_NORMAL"]
}
print(UserInfo)
i = td.setUserInfo(UserInfo)
print("setUserInfo", i)


UserType_VT2ES: Dict[str, int] = {
    "TAPI_USERTYPE_TRADER": 30000
}
NoticeIgnoreFlag_VT2ES: Dict[str, int] = {
    "TAPINoticeIgnoreFlagType": 0x00000000,
    "TAPI_NOTICE_IGNORE_FUND": 0x00000001,
    "TAPI_NOTICE_IGNORE_POSITIONPROFIT": 0x00000020,
    "TAPINoticeIgnoreFlagType": 0xFFFFFFFF
}
LoginAuth = {
    "UserNo": trade_username,
    "UserType": UserType_VT2ES["TAPI_USERTYPE_TRADER"],
    "AuthCode": auth_code,
    "AppID": auth_code,
    "ISModifyPassword": "N",
    "Password": "797878",
    #"NewPassword": ，
    "ISDDA": "N",
    "NoticeIgnoreFlag": NoticeIgnoreFlag_VT2ES["TAPI_NOTICE_IGNORE_FUND"]
    #"LoginInfo":，

}
i = td.startUser(trade_username, LoginAuth)
print("startUser",i)

print("finish...")
while True:
    time.sleep(3)







