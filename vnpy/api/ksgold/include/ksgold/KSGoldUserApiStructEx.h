#ifndef __KSGOLDUSERAPISTRUCTEX__H__
#define __KSGOLDUSERAPISTRUCTEX__H__

#include "KSGoldUserApiDataTypeEx.h"

namespace KSGoldTradeAPI
{

enum KS_TE_RESUME_TYPE
{
	KS_TERT_RESTART = 0,
	KS_TERT_RESUME,
	KS_TERT_QUICK
};

///用户登录请求
struct CThostFtdcReqUserLoginField
{
	TThostFtdcTraderIDType     AccountID;			//登录帐号
	TThostFtdcLoginType        LoginType;           //登录账号类型
	TThostFtdcPasswordType     Password;			//密码
	TThostFtdcIPAddressType	   LoginIp;				//终端IP地址
	TThostFtdcMacAddressType   MacAddress;			//Mac地址
	TThostFtdcProductInfoType  UserProductionInfo;	//用户端产品信息
	TThostFtdcProtocolInfoType ProtocolInfo;		//协议信息
	//TThostFtdcDiskSerialNoType DiskSerialNo;		//硬盘序列号
};

///用户登录应答
struct CThostFtdcRspUserLoginField
{
	TThostFtdcDateType				 TradeDate;				//交易日期
	TThostFtdcLoginBatchType		 SessionID;				//会话编号
	TThostFtdcClientIDType			 ClientID;         		//客户号
	TThostFtdcCSRCInvestorNameType	 clientName;			//客户名称
	TThostFtdcClientIDType			 TradeCode;			   	//交易编码	
	TThostFtdcSeatIDType			 SeatNo;				//席位号
	TThostFtdcIPAddressType			 lastLoginIp;			//上次登录IP地址
	TThostFtdcDateType				 lastLoginDate;			//上次登录日期
	TThostFtdcTimeType				 lastLoginTime;			//上次登录时间
	TThostFtdcTraderIDType			 AccountID;				//登录账号
	TThostFtdcLoginType				 LoginType;				//登录账号类型
	TThostFtdcPasswordType			 Password;				//密码
	TThostFtdcMacAddressType		 MacAddress;			//MAC地址
	TThostFtdcIPAddressType			 LoginIp;				//终端IP地址
	TThostFtdcProductInfoType		 UserProductionInfo;	//用户端产品信息
	TThostFtdcProtocolInfoType		 ProtocolInfo;			//协议信息
	TThostFtdcSystemNameType		 SystemName;			//交易系统名称
	TThostFtdcFrontIDType			 FrontID;			    //前置编号
	TThostFtdcOrderRefType			 MaxOrderRef;			//最大报单引用
	TThostFtdcTimeType			 	 SgeTime;			    //金交所时间
};

///用户登出请求
struct CThostFtdcUserLogoutField
{
	TThostFtdcIPAddressType	        LoginIp;				//终端IP地址
	TThostFtdcMacAddressType        MacAddress;			    //Mac地址
	TThostFtdcClientIDType			ClientID;         		//客户号
};

///客户会话信息通用查新请求
struct CThostFtdcQryClientSessionField
{
	TThostFtdcClientIDType			 ClientID;         		//客户号
};

///客户会话信息通用查新应答
struct CThostFtdcRspClientSessionField
{
	TThostFtdcClientIDType			 ClientID;         		//客户号
	TThostFtdcLoginBatchType		 SessionID;				//会话ID
	TThostFtdcIdDiffCode             IdDiffCode;			//身份区分特征码
	TThostFtdcIPAddressType			 CurLoginIp;			//登录IP地址
	TThostFtdcMacAddressType		 CurMacAddress;			//MAC地址
	TThostFtdcStatus				 Status;				//登录状态
	TThostFtdcTimeType				 LoginTime;				//登录时间
	TThostFtdcDateType				 LoginDate;				//登录日期
	TThostFtdcTimeType				 LogoutTime;			//录出时间
	TThostFtdcDateType				 LogoutDate;			//录出日期
	TThostFtdcFailNumber			 FailNumber;			//登录失败次数
};

///查询交割品种应答
struct CThostFtdcRspVarietyCodeField
{
	TThostFtdcExchangeIDType	    ExchangeID;			//交易所代码	
	TThostFtdcAbbrType				VarietyShortName;	//品种简称	
	TThostFtdcAbbrType				VarietyFullName;	//品种全称		
	TThostFtdcInstrumentIDType		VarietyCode;	    //交割品种代码
	TThostFtdcDeliveryVarietyType	VarietyType;        //品种类别
	TThostFtdcWeightUnit			WeightUnit;			//重量单位
	TThostFtdcOrderStatusType		Status;				//状态
	TThostFtdcMinTakeVolumn			MinTakeVolumn;		//最小提货量
	TThostFtdcTakeUnit				TakeUnit;			//提货单位		
	TThostFtdcWeightType			Weight;				//默认重量		
	TThostFtdcProductIDType			ProductID;			//产品代码	
};

///查询合约应答
struct CThostFtdcInstrumentField
{
	TThostFtdcExchangeIDType	    ExchangeID;   //交易所代码	
	TThostFtdcInstrumentIDType		InstID;       //合约代码	
	TThostFtdcRateType				LowerLimit;   //跌停板率		
	TThostFtdcMarketIDType			MarketID;     //市场代码
	TThostFtdcVolumeType			MaxHand;      //最大申报限量
	TThostFtdcVolumeType			MinHand;      //最小申报限量
	TThostFtdcInstrumentNameType    Name;         //合约名称
	TThostFtdcOpenFlagType			OpenFlag;     //活跃标志
	TThostFtdcPriceType				Tick;         //最小变动价位		
	TThostFtdcInstStateFlagType		TradeState;	  //合约交易状态		
	TThostFtdInstUnitType			Unit;         //交易单位数量
	TThostFtdcRateType				UpperLimit;   //涨停板率		
	TThostFtdcVarietyIDType			VarietyID;    //交割品种代码
	TThostFtdcVarietyType			VarietyType;  //品种类别	
	TThostFtdcMarketType			MarketType;   //市场标志
	TThostFtdcProductIDType			ProductID;    //产品代码	
};

///查询资金账户
struct CThostFtdcQryTradingAccountField
{
	TThostFtdcClientIDType			 ClientID;      //客户号	
};

//查询历史资金
struct CThostFtdcQryHisCapitalField
{
	TThostFtdcClientIDType			 ClientID;      //客户号	
	TThostFtdcDateType               StartDate;     //开始日期
	TThostFtdcDateType               EndDate;       //结束日期
};

///查询费率保证金率
struct CThostFtdcQryCostMarginFeeField
{
	TThostFtdcClientIDType			 ClientID;      //客户号	
	TThostFtdcInstrumentIDType       InstID;		//合约代码
};


//查询历史资金应答
struct CThostFtdcRspHisCapitalField
{
    TThostFtdcDateType              TradeDate;			//交易日期
	TThostFtdcMoneyType		        AvailCap;			//可用资金
	TThostFtdcMoneyType		        Todayprofit;		//当日盈亏
	TThostFtdcMoneyType		        PosiMargin;			//持仓保证金
	TThostFtdcMoneyType		        PickUpMargin;		//提货保证金
	TThostFtdcMoneyType		        StorageMargin;		//仓储保证金
	TThostFtdcMoneyType		        TradeFee;;			//交易手续费
	TThostFtdcMoneyType		        TodayInOut;			//出入金
	TThostFtdcMoneyType		        EtfTransferFee;		//ETF 认申赎费 
	TThostFtdcMoneyType		        EtfTransferFeeFrzn; //ETF 认申赎费冻结
	TThostFtdcMoneyType		        EtfCashBalance;     //T-1 日实际现金差额 
	TThostFtdcMoneyType		        EtfCashBalanceFrzn; //T 日预估现金差额
};

///查询费率保证金率应答
struct CThostFtdcRspCostMarginFeeField
{
	TThostFtdcClientIDType			 ClientID;				//客户号
	TThostFtdcInstrumentIDType       InstID;				//合约代码
	TThostFtdcBuyOpenHandFee		 BuyOpenHandFee;        //买开手续费率
	TThostFtdcBuyOffsetHandFee       BuyOffsetHandFee;      //买平手续费率
	TThostFtdcSellOpenHandFee		 SellOpenHandFee;       //卖开手续费率
	TThostFtdcSellOffsetHandFee      SellOffsetHandFee;     //卖平手续费率
	TThostFtdcBuyMarginFee			 BuyMarginFee;          //买保证金率
	TThostFtdcSellMarginFee          SellMarginFee;         //卖保证金率
	TThostFtdcSeatBuyMarginFee       SeatBuyMarginFee;      //席位买保证金率
	TThostFtdcSeatSellMarginFee      SeatSellMarginFee;     //席位卖保证金率
};

///查询资金账户应答
struct CThostFtdcTradingAccountField
{
	TThostFtdcClientIDType	ClientID;	     //客户号
	TThostFtdcMoneyType		AvailCap;        //可用资金
	TThostFtdcMoneyType		Available;       //可提资金
	TThostFtdcMoneyType		PosiMargin;      //持仓保证金
	TThostFtdcMoneyType		BuyPosiMargin;   //买持仓保证金
	TThostFtdcMoneyType		SellPosiMargin;  //卖持仓保证金
	TThostFtdcMoneyType		StorageMargin;   //仓储保证金
	TThostFtdcMoneyType		TotalFee;;       //总手续费
	TThostFtdcMoneyType		TotalFrozen;     //总冻结资金
	TThostFtdcMoneyType		OrderFrozen;     //委托冻结	
	TThostFtdcMoneyType		SpotSellFrozen;  //现货卖出冻结
	TThostFtdcMoneyType		TodayIn;         //当日入金
	TThostFtdcMoneyType		TodayOut;        //当日出金
	TThostFtdcMoneyType		LastFrozen;      //上日冻结资金
	TThostFtdcMoneyType		TotalFrozenFee;  //总冻结手续费	
	TThostFtdcMoneyType		PickUpMargin;    //提货保证金
	TThostFtdcMoneyType		MiddleMargin;    //中立仓保证金
};

///响应信息
struct CThostFtdcRspInfoField
{
	TThostFtdcErrorIDType	ErrorID;	//错误代码
	TThostFtdcErrorMsgType	ErrorMsg;	//错误信息
};

///深度行情
struct CThostFtdcDepthMarketDataField
{
	TThostFtdcInstrumentIDType		InstID;       		//合约代码 
	TThostFtdcInstrumentNameType	Name;				//合约名称 
	TThostFtdcMarketNameType		MarketName;			//市场名称“00”现货市场，“01”tn远期市场，“10”递延，“11”交割中立仓 
	TThostFtdcPriceType				PreSettle;			//昨结算 
	TThostFtdcPriceType				PreClose;			//昨收盘 
	TThostFtdcPriceType				Open;				//开盘价 
	TThostFtdcPriceType				High;				//最高价 
	TThostFtdcPriceType				Low;				//最低价 
	TThostFtdcPriceType				Last;				//最新价 
	TThostFtdcPriceType				Close;				//收盘价 
	TThostFtdcPriceType				Bid1;				//最高买价一 
	TThostFtdcVolumeType			BidLot1;			//最高买量一,交割买量 
	TThostFtdcPriceType				Ask1;				//最低卖价一 
	TThostFtdcVolumeType			AskLot1;			//最低卖量一 
	TThostFtdcPriceType				Bid2;				//最高买价二 
	TThostFtdcVolumeType			BidLot2;			//最高买量二,交割卖量 
	TThostFtdcPriceType				Ask2;				//最低卖价二 
	TThostFtdcVolumeType			AskLot2;			//最低卖量二 
	TThostFtdcPriceType				Bid3;				//最高买价三 
	TThostFtdcVolumeType			BidLot3;			//最高买量三,中立仓买量
	TThostFtdcPriceType				Ask3;				//最低卖价三 
	TThostFtdcVolumeType			AskLot3;			//最低卖量三 
	TThostFtdcPriceType				Bid4;				//最高买价四 
	TThostFtdcVolumeType			BidLot4;			//最高买量四,中立仓卖量
	TThostFtdcPriceType				Ask4;				//最低卖价四 
	TThostFtdcVolumeType			AskLot4;			//最低卖量四 
	TThostFtdcPriceType				Bid5;				//最高买价五 
	TThostFtdcVolumeType			BidLot5;			//最高买量五 
	TThostFtdcPriceType				Ask5;				//最低卖价五 
	TThostFtdcVolumeType			AskLot5;			//最低卖量五 
	TThostFtdcPriceType				Bid6;				//最高买价六 
	TThostFtdcVolumeType			BidLot6;			//最高买量六 
	TThostFtdcPriceType				Ask6;				//最低卖价六 
	TThostFtdcVolumeType			AskLot6;			//最低卖量六 
	TThostFtdcPriceType				Bid7;				//最高买价七 
	TThostFtdcVolumeType			BidLot7;			//最高买量七 
	TThostFtdcPriceType				Ask7;				//最低卖价七 
	TThostFtdcVolumeType			AskLot7;			//最低卖量七 
	TThostFtdcPriceType				Bid8;				//最高买价八 
	TThostFtdcVolumeType			BidLot8;			//最高买量八 
	TThostFtdcPriceType				Ask8;				//最低卖价八 
	TThostFtdcVolumeType			AskLot8;			//最低卖量八
	TThostFtdcPriceType				Bid9;				//最高买价九 
	TThostFtdcVolumeType			BidLot9;			//最高买量九 
	TThostFtdcPriceType				Ask9;				//最低卖价九 
	TThostFtdcVolumeType			AskLot9;			//最低卖量九 
	TThostFtdcPriceType				Bid10;				//最高买价十 
	TThostFtdcVolumeType			BidLot10;			//最高买量十 
	TThostFtdcPriceType				Ask10;				//最低卖价十 
	TThostFtdcVolumeType			AskLot10;			//最低卖量十 
	TThostFtdcVolumeType			Volume;				//成交量（双边） 
	TThostFtdcVolumeType			OpenInt;			//持仓量（双边） 
	TThostFtdcPriceType				UpDown;				//涨跌 
	TThostFtdcMoneyType				Turnover;			//成交额 
	TThostFtdcPriceType				Settle;				//结算价 
	TThostFtdcPriceType				Average;			//均价 
	TThostFtdcDateType				QuoteDate;			//行情日期 
	TThostFtdcTimeType				QuoteTime;			//行情时间 
	TThostFtdcWeightType			weight;				//成交（双边）重量
	TThostFtdcPriceType				highLimit;			//涨停板
	TThostFtdcPriceType				lowLimit;			//跌停板
	TThostFtdcRateType				UpDownRate;			//涨跌幅度
};

///输入报单
struct CThostFtdcInputOrderField
{
	TThostFtdcSeatIDType			SeatID;          //席位号
	TThostFtdcClientIDType			ClientID;        //客户号
	TThostFtdcClientIDType			TradeCode;       //交易编码		
	TThostFtdcInstrumentIDType      InstID;          //合约代码	
	TThostFtdcBsFlagType			BuyOrSell;       //买卖方向
	TThostFtdcOffsetFlagType		OffsetFlag;      //开平标志	
	TThostFtdcVolumeType			Amount;          //委托手数		
	TThostFtdcPriceType				Price;           //委托价格		
	TThostFtdcMarketIDType			MarketID;        //市场代码	
	TThostFtdcOrderRefType			OrderRef;		 //报单引用
	TThostFtdcLoginBatchType		SessionID;		 //会话ID
	TThostFtdcHedgeFlagType			HedgeFlag;		 //投保标志
	TThostFtdcCmdType				CmdType;		 //指令类型
	TThostFtdcIPAddressType	        LoginIp;		 //终端IP地址
	TThostFtdcMacAddressType        MacAddress;	     //Mac地址
};

///条件单委托
struct CThostFtdcConditionOrderField
{
	TThostFtdcExchangeIDType	    ExchangeID;		 //交易所代码
	TThostFtdcSeatIDType			SeatID;          //席位号
	TThostFtdcClientIDType			ClientID;        //客户号
	TThostFtdcClientIDType			TradeCode;       //交易编码
	TThostFtdcMarketIDType			MarketID;        //市场代码
	TThostFtdcInstrumentIDType      InstID;          //合约代码
	TThostFtdcBsFlagType			BuyOrSell;       //买卖方向
	TThostFtdcOffsetFlagType		OffsetFlag;      //开平标志
	TThostFtdcVolumeType			Amount;          //委托手数
	TThostFtdcByteType				OrderType;       //委托类型
	TThostFtdcByteType				MiddleFlag;      //中立仓标志
	TThostFtdcByteType				PriceFlag;       //条件委托价格类型
	TThostFtdcPriceType				Price;           //预委托价格	
	TThostFtdcPriceType				TrigPrice;	     //预委托触发价格
	TThostFtdcValidDay				ValidDay;		 //有效期天数
	TThostFtdcVolumnCheck			VolumnCheck;	 //数量检查标志
	TThostFtdcOrderRefType			OrderRef;		 //报单引用
	TThostFtdcLoginBatchType		SessionID;		 //会话ID
	TThostFtdcCmdType				CmdType;		 //指令类型
	TThostFtdcIPAddressType	        LoginIp;		 //终端IP地址
	TThostFtdcMacAddressType        MacAddress;	     //Mac地址
   
};

///条件单委托应答
struct CThostFtdcRspConditionOrderField
{
	TThostFtdcSeatIDType			SeatID;				//席位号
	TThostFtdcClientIDType			ClientID;		    //客户号
	TThostFtdcClientIDType			TradeCode;			//交易编码
	TThostFtdcExchangeIDType	    ExchangeID;			//交易所代码
	TThostFtdcOrderRefType			ConditionOrderNo;	//条件单编号
	TThostFtdcDateType				EntrustDate;	    //委托日期
	TThostFtdcDateType				TradeDate;		    //自然日期
	TThostFtdcTimeType				EntrustTime;        //委托时间
	TThostFtdcOrderStatusType		Status;				//条件单委托状态
	TThostFtdcMarketIDType			MarketID;			//市场代码
	TThostFtdcInstrumentIDType      InstID;				//合约代码
	TThostFtdcBsFlagType			BuyOrSell;			//买卖方向
	TThostFtdcOffsetFlagType		OffsetFlag;			//开平标志
	TThostFtdcVolumeType			Amount;				//委托手数
	TThostFtdcByteType				OrderType;			//条件单类型
	TThostFtdcByteType				MiddleFlag;			//中立仓标志
	TThostFtdcByteType				PriceFlag;			//条件委托价格类型
	TThostFtdcPriceType				Price;				//预委托价格	
	TThostFtdcPriceType				TrigPrice;			//预委托触发价格
	TThostFtdcValidDay				ValidDay;			//有效期天数
	TThostFtdcVolumnCheck			VolumnCheck;		//数量检查标志
	TThostFtdcOrderRefType			OrderRef;			//报单引用
	TThostFtdcLoginBatchType		SessionID;			//会话ID
	TThostFtdcCmdType				CmdType;			//指令类型
};

///输入报单应答
struct CThostFtdcRspInputOrderField
{
	TThostFtdcOrderRefType			LocalOrderNo;	 //本地报单号
	TThostFtdcOrderStatusType		Status;			 //委托状态
	TThostFtdcSeatIDType			SeatID;          //席位号
	TThostFtdcClientIDType			ClientID;        //客户号
	TThostFtdcClientIDType			TradeCode;       //交易编码		
	TThostFtdcInstrumentIDType      InstID;          //合约代码	
	TThostFtdcBsFlagType			BuyOrSell;       //买卖方向
	TThostFtdcOffsetFlagType		OffsetFlag;      //开平标志	
	TThostFtdcVolumeType			Amount;          //委托手数		
	TThostFtdcPriceType				Price;           //委托价格		
	TThostFtdcMarketIDType			MarketID;        //市场代码	
	TThostFtdcOrderRefType			OrderRef;		 //报单引用
	TThostFtdcLoginBatchType		SessionID;		 //会话ID
	TThostFtdcRequestIDType			RequestID;		 //请求编号
	TThostFtdcHedgeFlagType			HedgeFlag;		 //投保标志
	TThostFtdcCmdType				CmdType;		 //指令类型
};


///条件单撤单
struct CThostFtdcConditionActionOrderField
{
	TThostFtdcClientIDType			ClientID;		    //客户号
	TThostFtdcOrderRefType			ConditionOrderNo;	//条件单编号
	TThostFtdcIPAddressType	        LoginIp;			//终端IP地址
	TThostFtdcMacAddressType        MacAddress;			//Mac地址
};

///条件单撤单应答
struct CThostFtdcRspConditionActionOrderField
{
	TThostFtdcClientIDType			ClientID;		    //客户号
	TThostFtdcOrderRefType			ConditionOrderNo;	//条件单编号
};

///条件单查询
struct CThostFtdcConditionOrderQryField
{
	TThostFtdcClientIDType			ClientID;			//客户号
	TThostFtdcOrderRefType			ConditionOrderNo;	//条件单编号
	TThostFtdcOrderStatusType		Status;				//条件单状态
	TThostFtdcInstrumentIDType		InstID;				//合约代码
	TThostFtdcDateType				StartDate;		    //起始日期
	TThostFtdcDateType				EndDate;		    //结束日期
	TThostFtdcOrderRefType			OrderRef;			//报单引用
	TThostFtdcLoginBatchType		SessionID;			//会话ID
	TThostFtdcCmdType				CmdType;			//指令类型
};

///条件单查询应答
struct CThostFtdcRspConditionOrderQryField
{
	TThostFtdcClientIDType			ClientID;			//客户号
	TThostFtdcDateType				StartDate;		    //起始日期
	TThostFtdcDateType				EndDate;		    //结束日期
	TThostFtdcOrderRefType			ConditionOrderNo;	//条件单编号
	TThostFtdcOrderRefType			LocalOrderNo;		//本地报单号
	TThostFtdcByteType				OrderType;			//委托单类型
	TThostFtdcCSRCInvestorNameType	EntrustTypeName;	//委托类型名称
	TThostFtdcInstrumentIDType		InstID;				//合约代码
	TThostFtdcBsFlagType			BuyOrSell;	        //买卖方向
	TThostFtdcOffsetFlagType		OffSetFlag;		    //开平标志
	TThostFtdcOrderStatusType		Status;				//条件单状态
	TThostFtdcVolumeType			Amount;				//委托手数
	TThostFtdcPriceType				Price;				//委托价格
	TThostFtdcPriceType				TriggerPrice;		//触发价格
	TThostFtdcTimeType				EntrustTime;        //委托时间
	TThostFtdcTimeType				TriggerTime;        //触发时间
	TThostFtdcRemark				ReasonDesc;			//原因
	TThostFtdcDateType				EntrustDate;	    //委托日期
	TThostFtdcDateType				ExpireDate;			//到期日
	TThostFtdcDateType				TriggerDate;		//触发交易日期
	TThostFtdcOrderRefType			OrderRef;			//报单引用
	TThostFtdcLoginBatchType		SessionID;			//会话ID
	TThostFtdcCmdType				CmdType;			//指令类型
};

///条件单成交查询
struct CThostFtdcConditionOrderMatchField
{
	TThostFtdcClientIDType			ClientID;			//客户号
	TThostFtdcInstrumentIDType		InstID;				//合约代码
	TThostFtdcOrderRefType			ConditionOrderNo;	//条件单编号
	TThostFtdcOrderRefType			LocalOrderNo;		//委托编号
};

///条件单成交查询应答
struct CThostFtdcRspConditionOrderMatchField
{
	TThostFtdcClientIDType			ClientID;			//客户号
	TThostFtdcMatchNoType			MatchNo;            //成交单编号
	TThostFtdcOrderRefType			ConditionOrderNo;	//条件单编号
	TThostFtdcOrderRefType			LocalOrderNo;		//委托编号
	TThostFtdcByteType				EntrustType;		//委托类型
	TThostFtdcInstrumentIDType		InstID;				//合约代码
	TThostFtdcBsFlagType			BuyOrSell;	        //买卖方向
	TThostFtdcOffsetFlagType		OffSetFlag;		    //开平标志
	TThostFtdcVolumeType			Amount;				//委托手数
	TThostFtdcPriceType				Price;				//委托价格
	TThostFtdcVolumeType			MatchVolumn;		//成交数量
	TThostFtdcPriceType				MatchPrice;			//成交价格
	TThostFtdcTimeType				MatchTime;			//成交时间
};

///报单撤单回报
struct CThostFtdcOrderRtnField
{
	TThostFtdcOrderNoType			orderNo;		//系统报单号	
	TThostFtdcOrderRefType			localOrderNo;;	//本地报单号	
	TThostFtdcOrderStatusType		status;			//委托状态	
	TThostFtdcVolumeType			cancelQty;		//撤单手数
};


///输入报单操作
struct CThostFtdcInputOrderActionField
{
	TThostFtdcClientIDType		ClientID;         //客户号
	TThostFtdcOrderRefType		LocalOrderNo;     //本地报单号
	TThostFtdcMarketIDType		MarketID;		  //市场代码
	TThostFtdcOrderRefType		OrderRef; 		  //报单引用
	TThostFtdcLoginBatchType	SessionID;		  //会话编号
	TThostFtdcRequestIDType		RequestID;		  //请求编号
	TThostFtdcIPAddressType	   LoginIp;			  //终端IP地址
	TThostFtdcMacAddressType   MacAddress;		  //Mac地址
};


///输入报单操作应答
struct CThostFtdcRspInputOrderActionField
{
	TThostFtdcClientIDType		ClientID;         //客户号
	TThostFtdcOrderRefType		localOrderNo;     //本地报单号
	TThostFtdcOrderStatusType	Status;			  //委托状态
	TThostFtdcMarketIDType		marketID;		  //市场代码
	TThostFtdcOrderRefType		OrderRef; 		  //报单引用
	TThostFtdcLoginBatchType	SessionID;		  //会话编号
	TThostFtdcRequestIDType		RequestID;		  //请求编号
};

///报单操作
struct CThostFtdcOrderActionField
{
	TThostFtdcOrderRefType		localOrderNo;     //本地报单号	
	TThostFtdcByteType			orderFlag;        //委托标志	
	TThostFtdcMarketIDType		marketID;		  //市场代码	
	TThostFtdcTraderIDType		traderID;         //撤单操作员
	TThostFtdcOrderRefType		OrderRef; 		  //报单引用
	TThostFtdcLoginBatchType	SessionID;		  //会话编号
	TThostFtdcTradeWayType      tradeWay;         //委托渠道	
};

///查询成交应答
struct CThostFtdcTradeField
{
	TThostFtdcClientIDType			ClientID;          //客户号
	TThostFtdcOrderNoType			OrderNo;           //系统报单号
	TThostFtdcMatchNoType			MatchNo;           //成交单编号
	TThostFtdcInstrumentIDType		InstID;            //合约代码
	TThostFtdcBsFlagType			BuyOrSell;	       //买卖方向
	TThostFtdcOffsetFlagType		OffSetFlag;		   //开平标志
	TThostFtdcPriceType				Price;             //成交价格
	TThostFtdcVolumeType			Volume;            //成交手数
	TThostFtdcMoneyType				Amount;            //成交金额	
	TThostFtdcByteType				Order_flag;        //委托类型
	TThostFtdcDateType				MatchDate;		   //成交日期
	TThostFtdcTimeType				MatchTime;         //成交时间	
	TThostFtdcOrderRefType			LocalOrderNo;	   //本地报单号
	TThostFtdcMarketIDType			MarketID;	       //市场代码	
	TThostFtdcMoneyType				Trade_fee;         //手续费
	TThostFtdcByteType				Forceoffset_flag;  //强平标志	
	TThostFtdcVolumeType			Forcebatchnum;     //强平批次号
	TThostFtdcTradeWayType			TradeWay;          //渠道标志
	TThostFtdcHedgeFlagType			HedgeFlag;		   //投保标志
	TThostFtdcLoginBatchType		SessionID;		   //会话编号
	TThostFtdcOrderRefType			OrderRef; 		   //报单引用
};

///查询合约
struct CThostFtdcQryInstrumentField
{
	TThostFtdcClientIDType	  ClientID;            //客户号
	TThostFtdcContractIDType  ContractID;          //合约代码
	TThostFtdcProductIDType   ProductID;           //产品代码
};

///查询交割品种
struct CThostFtdcQryVarietyCodeField
{
	TThostFtdcClientIDType	  ClientID;            //客户号
	TThostFtdcContractIDType  VarietyID;		   //交割品种代码
	TThostFtdcProductIDType   ProductID;           //产品代码
};

///查询成交
struct CThostFtdcQryTradeField
{
	TThostFtdcClientIDType		ClientID;           //客户号
	TThostFtdcMarketIDType		MarketID;			//市场代码
	TThostFtdcInstrumentIDType  InstID;				//合约代码
	TThostFtdcOrderRefType		LocalOrderNo;		//本地报单编号
};

///查询报单
struct CThostFtdcQryOrderField
{
	TThostFtdcClientIDType		ClientID;           //客户号
	TThostFtdcMarketIDType		MarketID;			//市场代码
	TThostFtdcOrderRefType		LocalOrderNo;		//本地报单编号
	TThostFtdcInstrumentIDType  InstID;				//合约代码
	TThostFtdcHedgeFlagType		HedgeFlag;		    //投保标志
	TThostFtdcCmdType			CmdType;		    //指令类型
	TThostFtdcLoginBatchType	SessionID;			//会话编号
	TThostFtdcOrderRefType		OrderRef; 			//报单引用
};

///查询报单应答
struct CThostFtdcOrderField
{
	TThostFtdcClientIDType			ClientID;				//客户号
	TThostFtdcOrderNoType			OrderNo;				//系统报单号	
	TThostFtdcOrderRefType			LocalOrderNo;			//本地报单号
	TThostFtdcMarketIDType			MarketID;				//市场代码
	TThostFtdcInstrumentIDType      InstID;					//合约代码
	TThostFtdcBsFlagType			BuyOrSell;				//买卖方向
	TThostFtdcOffsetFlagType		OffsetFlag;				//开平标志
	TThostFtdcVolumeType			Amount;					//委托手数	
	TThostFtdcPriceType				Price;					//委托价格
	TThostFtdcVolumeType			MatchQty;				//成交手数
	TThostFtdcOrderStatusType		Status;					//委托状态	
	TThostFtdcTimeType				EntrustTime;			//委托时间
	TThostFtdcByteType				Forceoffset_flag;		//强平标志
	TThostFtdcVolumeType			CancelQty;				//撤单手数
	TThostFtdcTimeType				CancelTime;				//撤单时间
	TThostFtdcTradeWayType			TradeWay;				//交易渠道
	TThostFtdcHedgeFlagType			HedgeFlag;				//投保标志
	TThostFtdcLoginBatchType		SessionID;				//会话编号
	TThostFtdcOrderRefType			OrderRef; 				//报单引用
	TThostFtdcCmdType				CmdType;				//指令类型
	TThostFtdcRequestIDType			RequestID;				//请求编号
};

///查询投资者持仓
struct CThostFtdcQryInvestorPositionField
{
	TThostFtdcClientIDType		ClientID;           //客户号
	TThostFtdcMarketIDType		MarketID;			//市场代码
	TThostFtdcInstrumentIDType	InstID;				//合约代码
};

///查询投资者持仓明细
struct CThostFtdcQryInvestorPositionDetailField
{
	TThostFtdcClientIDType		ClientID;           //客户号
	TThostFtdcDateType			QueryData;			//查询日期
};


///查询投资者持仓应答
struct CThostFtdcInvestorPositionField
{
	TThostFtdcClientIDType			ClientID;					//客户号
	TThostFtdcInstrumentIDType		InstID;						//合约代码
	TThostFtdcMarketIDType			MarketID;					//市场代码
	TThostFtdcVolumeType			LongPosi;					//可用买持仓量	
	TThostFtdcPriceType				LongPosiAvgPrice;			//买持均价
	TThostFtdcVolumeType			ShortPosi;					//可用卖持仓量	
	TThostFtdcPriceType				ShortPosiAvgPrice;			//卖持均价	
	TThostFtdcPriceType				LongOpenAvgPrice;			//买开均价
	TThostFtdcPriceType				ShortOpenAvgPrice;			//卖开均价	
	TThostFtdcVolumeType			LongPosiFrozen;				//买持仓冻结	
	TThostFtdcVolumeType			ShortPosiFrozen;			//卖持仓冻结	
	TThostFtdcVolumeType			LongPosiVol;				//买持仓总量	
	TThostFtdcVolumeType			ShortPosiVol;				//卖持仓总量	
	TThostFtdcVolumeType			TodayLong;					//当日买开	
	TThostFtdcVolumeType			TodayShort;					//当日卖开	
	TThostFtdcVolumeType			TodayOffsetShort;			//当日卖平	
	TThostFtdcVolumeType			TodayOffsetLong;			//当日买平	
	TThostFtdcVolumeType			LastLong;					//上日买持仓	
	TThostFtdcVolumeType			LastShort;					//上日卖持仓		
};

///查询投资者持仓明细应答
struct CThostFtdcInvestorPositionDetailField
{
	TThostFtdcClientIDType			ClientID;					//客户号
	TThostFtdcCSRCInvestorNameType	ClientShortName;			//客户简称
	TThostFtdcDateType				Data;						//日期
	TThostFtdcInstrumentIDType		InstID;						//合约代码
	TThostFtdcBsFlagType			BuyOrSell;					//买卖方向
	TThostFtdcVolumeType			Volumn;						//数量
	TThostFtdcPriceType				Settle;						//结算价
	TThostFtdcDateType				OpenFlagData;				//开仓日期
	TThostFtdcMatchNoType			MatchNo;				    //成交单编号	
};

///查询库存
struct CThostFtdcQryStorageField
{
	TThostFtdcVarietyIDType  VarietyID;            //交割品种代码
	TThostFtdcClientIDType	 ClientID;			   //客户号
};

//ETF认购
struct CThostFtdcSubScriptionField
{
   TThostFtdcClientIDType	    ClientID;	     //客户号
   TThostFtdcSeatIDType			SeatNo;		     //席位号
   TThostFtdcEtfCodeType		EtfCode;         //黄金ETF基金代码
   TThostFtdcInstrumentIDType	InstrumentID1;	 //合约代码1
   TThostFtdcWeightType			weight1;		 //重量1
   TThostFtdcInstrumentIDType	InstrumentID2;	 //合约代码2
   TThostFtdcWeightType			weight2;		 //重量2
   TThostFtdcInstrumentIDType	InstrumentID3;	 //合约代码3
   TThostFtdcWeightType			weight3;		 //重量3
   TThostFtdcInstrumentIDType	InstrumentID4;	 //合约代码4
   TThostFtdcWeightType			weight4;		 //重量4
   TThostFtdcInstrumentIDType	InstrumentID5;	 //合约代码5
   TThostFtdcWeightType			weight5;		 //重量5
   TThostFtdcWeightType			Totalweight;     //总重量
   TThostFtdcLoginBatchType		SessionID;		 //会话ID
   TThostFtdcIPAddressType	    LoginIp;		 //终端IP地址
   TThostFtdcMacAddressType     MacAddress;	     //Mac地址
};

//ETF申购
struct CThostFtdcApplyForPurchaseField
{
   TThostFtdcClientIDType	    ClientID;	     //客户号
   TThostFtdcSeatIDType			SeatNo;		     //席位号
   TThostFtdcEtfCodeType		EtfCode;         //黄金ETF基金代码
   TThostFtdcInstrumentIDType	InstrumentID1;	 //合约代码1
   TThostFtdcWeightType			weight1;		 //重量1
   TThostFtdcInstrumentIDType	InstrumentID2;	 //合约代码2
   TThostFtdcWeightType			weight2;		 //重量2
   TThostFtdcInstrumentIDType	InstrumentID3;	 //合约代码3
   TThostFtdcWeightType			weight3;		 //重量3
   TThostFtdcInstrumentIDType	InstrumentID4;	 //合约代码4
   TThostFtdcWeightType			weight4;		 //重量4
   TThostFtdcInstrumentIDType	InstrumentID5;	 //合约代码5
   TThostFtdcWeightType			weight5;		 //重量5
   TThostFtdcWeightType			Totalweight;     //总重量
   TThostFtdcFundUnitType       fundunit;        //份额
   TThostFtdcLoginBatchType		SessionID;		 //会话ID
   TThostFtdcIPAddressType	    LoginIp;		 //终端IP地址
   TThostFtdcMacAddressType     MacAddress;	     //Mac地址
};

//ETF赎回
struct CThostFtdcRedeemField
{
   TThostFtdcClientIDType	    ClientID;		 //客户号
   TThostFtdcSeatIDType			SeatNo;		     //席位号
   TThostFtdcEtfCodeType		EtfCode;         //黄金ETF基金代码
   TThostFtdcFundUnitType       fundunit;        //份额
   TThostFtdcLoginBatchType		SessionID;		 //会话ID
   TThostFtdcIPAddressType	    LoginIp;		 //终端IP地址
   TThostFtdcMacAddressType     MacAddress;	     //Mac地址
};

//ETF账户绑定
struct CThostFtdcETFBingingField
{
	TThostFtdcClientIDType	       ClientID;		 //客户号
	TThostFtdcEtfStockTxCodeType   StockTradeCode;	 //投资人证券账号
	TThostFtdcEtfCodeType		   EtfCode;          //黄金ETF基金代码
	TThostFtdcManagedUnitType      EtfManagedUnit;   //托管单元
	TThostFtdcIPAddressType	       LoginIp;		     //终端IP地址
	TThostFtdcMacAddressType       MacAddress;	     //Mac地址
};

//ETF账户解绑定
struct CThostFtdcETFUnBingingField
{
	TThostFtdcClientIDType	        ClientID;		 //客户号
	TThostFtdcEtfStockTxCodeType    StockTradeCode;	 //投资人证券账号
	TThostFtdcEtfCodeType		    EtfCode;         //黄金ETF基金代码
	TThostFtdcIPAddressType	       LoginIp;		     //终端IP地址
	TThostFtdcMacAddressType       MacAddress;	     //Mac地址
};

//ETF账户绑定解绑定状态推送
struct CThostFtdcETFBindingStatusField
{
	TThostFtdcClientIDType	        ClientID;		         //客户号
	TThostFtdcEtfStockTxCodeType    StockTradeCode;	         //投资人证券账号
	TThostFtdcEtfCodeType		    EtfCode;                 //黄金ETF基金代码
	TThostFtdcBindingStatusType   	BindingStatus;	         //绑定和解绑定状态
	TThostFtdcDateType				BindingDate;	         //绑定日期
	TThostFtdcOrderRefType		    BindingLocalOrderNo;	 //绑定本地编号
	TThostFtdcOrderRefType		    BindingEtfrevsn;	     //绑定备案流水
    TThostFtdcDateType				UnBindingDate;	         //解绑定日期
	TThostFtdcOrderRefType		    UnBindingLocalOrderNo;	 //解绑定本地编号
	TThostFtdcOrderRefType		    UnBindingEtfrevsn;	     //解绑定备案流水
};

//ETF认申赎交易查询 
struct CThostFtdcQryETFTradeDetailField
{
   TThostFtdcClientIDType	        ClientID;		 //客户号
};

//ETF认申赎清单查询 
struct CThostFtdcQryETFPcfDetailField
{
   TThostFtdcDateType		StartDate;              //开始日期            
   TThostFtdcDateType       EndDate;				//结束日期
   TThostFtdcEtfCodeType    EtfCode;				//黄金ETF基金代码
};

//ETF认申赎清单查询应答 
struct CThostFtdcETFPcfDetailField
{
	TThostFtdcDateType		    TradeDate;             //交易日            
	TThostFtdcEtfCodeType       EtfCode;			   //黄金ETF基金代码
	TThostFtdcInstrumentIDType	InstrumentID1;	       //合约代码1
	TThostFtdcMoneyType			TMoneydiff1;		   //T日预估现金差额1
	TThostFtdcMoneyType			TPreMoneydiff1;		   //T-1日实际现金差额1
	TThostFtdcInstrumentIDType	InstrumentID2;	       //合约代码2
	TThostFtdcMoneyType			TMoneydiff2;		   //T日预估现金差额2
	TThostFtdcMoneyType			TPreMoneydiff2;		   //T-1日实际现金差额2
	TThostFtdcInstrumentIDType	InstrumentID3;	       //合约代码3
	TThostFtdcMoneyType			TMoneydiff3;		   //T日预估现金差额3
	TThostFtdcMoneyType			TPreMoneydiff3;		   //T-1日实际现金差额3
	TThostFtdcInstrumentIDType	InstrumentID4;	       //合约代码4
	TThostFtdcMoneyType			TMoneydiff4;		   //T日预估现金差额4
	TThostFtdcMoneyType			TPreMoneydiff4;		   //T-1日实际现金差额4
	TThostFtdcInstrumentIDType	InstrumentID5;	       //合约代码5
	TThostFtdcMoneyType			TMoneydiff5;		   //T日预估现金差额5
	TThostFtdcMoneyType			TPreMoneydiff5;		   //T-1日实际现金差额5
	TThostFtdcWeightType        minTradeWeight;	       //最小申购赎回重量
	TThostFtdcWeightType        TodayPurchaseMaxLimit; //当日申购上限
	TThostFtdcWeightType        TodayRedeemMaxLimit;   //当日赎回上限
	TFtdcETFALLOWStatusType     TodayAllow;            //当日是否允许申购/赎回标志
	TThostFtdcWeightType        PreETFWeight;          //每份黄金ETF基金对应的黄金重量
};


//ETF认申赎交易查询应答
struct CThostFtdcETFTradeDetailField
{
	TThostFtdcClientIDType	      ClientID;			    //客户号
    TThostFtdcEtfTradeType        tradeType;            //交易类型
	TThostFtdcOrderNoType		  OrderNo;				//金交所ETF交易编号	
	TThostFtdcOrderRefType		  LocalOrderNo;			//本地申赎编号
	TThostFtdcDateType			  RequestDate;			//请求日期
	TThostFtdcTimeType            RequestTime;          //请求时间
	TThostFtdcEtfCodeType	      EtfCode;              //黄金ETF基金代码
	TThostFtdcInstrumentIDType	  InstrumentID1;	    //合约代码1
	TThostFtdcWeightType		  weight1;				//重量1
	TThostFtdcInstrumentIDType	  InstrumentID2;		//合约代码2
	TThostFtdcWeightType		  weight2;				//重量2
	TThostFtdcInstrumentIDType	  InstrumentID3;		//合约代码3
	TThostFtdcWeightType		  weight3;				//重量3
	TThostFtdcInstrumentIDType	  InstrumentID4;		//合约代码4
	TThostFtdcWeightType		  weight4;				//重量4
	TThostFtdcInstrumentIDType	  InstrumentID5;		//合约代码5
	TThostFtdcWeightType		  weight5;				//重量5
    TThostFtdcWeightType		  Totalweight;			//总重量
    TThostFtdcFundUnitType        fundunit;				//份额
	TThostFtdcDateType			  confirmDate;			//确认日期
	TThostFtdcEtfTradeStatusType  tradestatus;          //交易状态
	TThostFtdcErrorMsgType	      ErrorMsg;	            //失败原因 
	TThostFtdcRequestIDType		  RequestID;			//请求编号
};

///库存应答
struct CThostFtdcStorageField
{
	TThostFtdcClientIDType	 ClientID;			   //客户号
	TThostFtdcVarietyIDType  VarietyID;            //交割品种代码	
	TThostFtdcWeightType     totalStorage;		   //库存总量
	TThostFtdcWeightType     availableStorage;     //可用库存
	TThostFtdcWeightType     frozenStorage;	       //现货冻结库存	
	TThostFtdcWeightType     pendStorage;          //待提库存
	TThostFtdcWeightType     todayBuy;             //当日买入
	TThostFtdcWeightType     todaySell;	           //当日卖出
	TThostFtdcWeightType     todayDeposit;         //当日存入
	TThostFtdcWeightType     todayDraw;			   //当日提出
	TThostFtdcWeightType     todayBorrow;          //当日借入
	TThostFtdcWeightType     todayLend;	           //当日借出
	TThostFtdcWeightType     impawnStorage;        //质押库存
	TThostFtdcWeightType     lawFrozen;            //法律冻结库存
	TThostFtdcWeightType     bankFrozen;           //银行冻结库存	
	TThostFtdcByteType       customType;           //客户类别
	TThostFtdcWeightType     storageCost;          //库存成本
	TThostFtdcWeightType     impawnFrozen;         //质押冻结库存
	TThostFtdcWeightType     transFrozen;          //过户业务冻结库存
};

///市场状态
struct CThostFtdcMarketStatusField
{
	TThostFtdcMktStatusType   	MktStatus;	//市场状态
	TThostFtdcMarketIDType    	marketID ;	//市场代码
	TThostFtdcExchCodeType   	ExchCode;	//交易所代码
};

///合约状态
struct CThostFtdcInstrumentStatusField
{
	TThostFtdcExchangeIDType		ExchangeID;			//交易所代码
	TThostFtdcInstrumentIDType		InstrumentID;		//合约代码
	TThostFtdcInstrumentStatusType	InstrumentStatus;	//合约交易状态
}; 

///指定的合约
struct CThostFtdcSpecificInstrumentField
{
	TThostFtdcInstrumentIDType	InstrumentID; 		//合约代码
};

///查询行情
struct CThostFtdcQryQuotationField
{
	TThostFtdcMarketIDType    	marketID ;			//市场代码
	TThostFtdcInstrumentIDType	InstrumentID;       //合约代码
};

///修改密码
struct CThostFtdcModifyPasswordField
{
	TThostFtdcOldPassword		OldPassword;		//原密码
	TThostFtdcNewPassword		NewPassword;		//新密码
};

///修改密码应答
struct CThostFtdcModifyPasswordRsqField
{
	TThostFtdcClientIDType		 ClientID;			//客户号
};

///中行出入金
struct CThostFtdcBOCMoneyIOField
{
	TThostFtdcTransFerType		TransFerType;		//出入金类型；0出金，1入金；
	TThostFtdcTransFerAmount	TransFerAmount;		//转账金额
	TThostFtdcTradePassword		TradePassword;		//交易密码
	TThostFtdcClientIDType		ClientID;			//客户号
};
///中行出入金应答
struct CThostFtdcBOCMoneyIORspField
{
	TThostFtdcClientIDType		 ClientID;			//客户号
};

}	/// end of namespace KSGoldTradeAPI




#endif  ///__KSGOLDUSERAPISTRUCTEX__H__
