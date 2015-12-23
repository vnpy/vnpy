
#if !defined(KINSTARAPI_THOST_FTDCSTRUCT_H)
#define KINSTARAPI_THOST_FTDCSTRUCT_H

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "KSUserApiDataTypeEx.h"

//namespace KingstarAPI
//{


///用户登录请求
struct CThostFtdcReqUserLoginField
{
	TThostFtdcTraderIDType   accountID;				//登录帐号
	TThostFtdcLoginType      loginType ;             //登录类型
	TThostFtdcMemberIDType   memberID;				//会员代码
	TThostFtdcPasswordType   password;				//密码
	TThostFtdcDateType       tradeDate;				//交易日期
};

///用户登录应答
struct CThostFtdcRspUserLoginField
{
	TThostFtdcDateType       tradeDate;				//交易日期
	TThostFtdcOrderRefType  localOrderNo;			//最大本地报单号
	TThostFtdcLoginBatchType  loginbatch;			//登录批次
	TThostFtdcClientIDType  tradeCode;			   	//交易编码		
	TThostFtdcClientIDType  clientID;         		//客户号
	TThostFtdcSeatIDType    SeatNo ;				//席位号
	TThostFtdcCSRCInvestorNameType clientName;		//客户名称
	TThostFtdcIPAddressType	lastLoginIp;			//上次登录IP地址
	TThostFtdcDateType		lastLoginDate;			//上次登录日期
	TThostFtdcTimeType		lastLoginTime;			//上次登录时间
};
///用户登出请求
struct CThostFtdcUserLogoutField
{
	TThostFtdcTraderIDType  traderID;				//客户号
};




///合约
struct CThostFtdcInstrumentField
{
	TThostFtdcExchangeIDType     exchangeID;   //1		交易所代码	是	
	TThostFtdcInstrumentIDType   instID;       //2		合约代码	是	
	TThostFtdcRateType           lowerLimit;   //3		跌停板率		
	TThostFtdcMarketIDType       marketID;     //4		市场代码	是	
	TThostFtdcVolumeType         maxHand;      //5		最大申报限量	是	
	TThostFtdcVolumeType         minHand;      //6		最小申报限量	是	
	TThostFtdcInstrumentNameType       name;         //7		合约名称	是	
	TThostFtdcOpenFlagType       openFlag;     //8		活跃标志		1活跃2不活跃3只平 4只开
	TThostFtdcPriceType          tick;         //9		最小变动价位		
	TThostFtdcInstStateFlagType  tradeState;	  //10		合约交易状态		
	TThostFtdInstUnitType        unit;         //11		交易单位数量	是	
	TThostFtdcRateType           upperLimit;   //12		涨停板率		
	TThostFtdcVarietyIDType      varietyID;    //13		交割品种代码	是	
	TThostFtdcVarietyType    varietyType;  //14		品种类别	
	TThostFtdcMarketType     marketType;   //市场标志，现货、递延。。
};

//查询资金账户
struct CThostFtdcQryTradingAccountField
{
	TThostFtdcMSGType remian; //保留字段	
};

///资金账户
struct CThostFtdcTradingAccountField
{
	TThostFtdcMoneyType   availCap;        //2		可用资金	是	
	TThostFtdcMoneyType   available;       //3		可提资金	是	
	TThostFtdcMoneyType   posiMargin;      //4		持仓保证金	是	
	TThostFtdcMoneyType	  buyPosiMargin;   //5		买持仓保证金	是	
	TThostFtdcMoneyType	  sellPosiMargin;  //6		卖持仓保证金	是	
	TThostFtdcMoneyType	  storageMargin;   //8		仓储保证金	是	
	TThostFtdcMoneyType	  totalFee;;       //9		总手续费	是	
	TThostFtdcMoneyType   totalFrozen;     //10		总冻结资金	是	
	TThostFtdcMoneyType   orderFrozen;     //11		委托冻结	是	
	TThostFtdcMoneyType   spotSellFrozen;  //12		现货卖出冻结	是	
	TThostFtdcMoneyType   todayIn;         //13		当日入金	是	
	TThostFtdcMoneyType   todayOut;        //14		当日出金	是	
	TThostFtdcMoneyType   lastFrozen;      //17		上日冻结资金	是	
	TThostFtdcMoneyType   totalFrozenFee;  //18		总冻结手续费	是	
	TThostFtdcMoneyType   pickUpMargin;    // 19		提货保证金	是	
	TThostFtdcMoneyType   middleMargin;    //20		中立仓保证金	是	
};

///投资者持仓
struct CThostFtdcInvestorPositionField
{
	TThostFtdcInstrumentIDType    instID;			 //4		合约代码	是	
	TThostFtdcVolumeType    longPosi;		 //5		可用买持仓量	是	
	TThostFtdcPriceType     longPosiAvgPrice; //6		买持均价	是	
	TThostFtdcVolumeType    shortPosi;		 //7		可用卖持仓量	是	
	TThostFtdcPriceType     shortPosiAvgPrice;//8		卖持均价	是	
	TThostFtdcPriceType     longOpenAvgPrice; //9		买开均价	是	
	TThostFtdcPriceType     shortOpenAvgPrice;//10		卖开均价	是	
	TThostFtdcVolumeType    longPosiFrozen;   //11		买持仓冻结	是	
	TThostFtdcVolumeType    shortPosiFrozen;  //12		卖持仓冻结	是	
	TThostFtdcVolumeType    longPosiVol;      //13		买持仓总量	是	
	TThostFtdcVolumeType    shortPosiVol;     //14		卖持仓总量	是	
	TThostFtdcVolumeType    todayLong;        //15		当日买开	是	
	TThostFtdcVolumeType    todayShort;       //16		当日卖开	是	
	TThostFtdcVolumeType    todayOffsetShort; //17		当日卖平	是	
	TThostFtdcVolumeType    todayOffsetLong;  //18		当日买平	是	
	TThostFtdcVolumeType    lastLong;         //19		上日买持仓	是	
	TThostFtdcVolumeType    lastShort;        //20		上日卖持仓	是	
};



///响应信息
struct CThostFtdcRspInfoField
{
	///错误代码
	TThostFtdcErrorIDType	ErrorID;
	///错误信息
	TThostFtdcErrorMsgType	ErrorMsg;
};
///深度行情
struct CThostFtdcDepthMarketDataField
{
	TThostFtdcInstrumentIDType		InstID ;       	/**<合约代码 */
	TThostFtdcInstrumentNameType	Name ;	    	/**<合约名称 */
	TThostFtdcMarketNameType		MarketName ;	/**<市场名称 */
	TThostFtdcPriceType				PreSettle ;			/**<昨结算 */
	TThostFtdcPriceType				PreClose ;			/**<昨收盘 */
	TThostFtdcPriceType				Open ;				/**<开盘价 */
	TThostFtdcPriceType				High ;				/**<最高价 */
	TThostFtdcPriceType				Low ;				/**<最低价 */
	TThostFtdcPriceType				Last ;				/**<最新价 */
	TThostFtdcPriceType				Close ;				/**<收盘价 */
	TThostFtdcPriceType				Bid1 ;				/**<最高买价一 */
	TThostFtdcVolumeType			BidLot1 ;			/**<最高买量一 */
	TThostFtdcPriceType				Ask1 ;				/**<最低卖价一 */
	TThostFtdcVolumeType			AskLot1 ;			/**<最低卖量一 */
	TThostFtdcPriceType				Bid2 ;				/**<最高买价二 */
	TThostFtdcVolumeType			BidLot2 ;			/**<最高买量二 */
	TThostFtdcPriceType				Ask2 ;				/**<最低卖价二 */
	TThostFtdcVolumeType			AskLot2 ;			/**<最低卖量二 */
	TThostFtdcPriceType				Bid3 ;				/**<最高买价三 */
	TThostFtdcVolumeType			BidLot3 ;			/**<最高买量三 */
	TThostFtdcPriceType				Ask3 ;				/**<最低卖价三 */
	TThostFtdcVolumeType			AskLot3 ;			/**<最低卖量三 */
	TThostFtdcPriceType				Bid4 ;				/**<最高买价四 */
	TThostFtdcVolumeType			BidLot4 ;			/**<最高买量四 */
	TThostFtdcPriceType				Ask4 ;				/**<最低卖价四 */
	TThostFtdcVolumeType			AskLot4 ;			/**<最低卖量四 */
	TThostFtdcPriceType				Bid5 ;				/**<最高买价五 */
	TThostFtdcVolumeType			BidLot5 ;			/**<最高买量五 */
	TThostFtdcPriceType				Ask5 ;				/**<最低卖价五 */
	TThostFtdcVolumeType			AskLot5 ;			/**<最低卖量五 */
	TThostFtdcVolumeType			Volume ;			/**<成交量（双边） */
	TThostFtdcVolumeType			OpenInt ;			/**<持仓量（双边） */
	TThostFtdcPriceType				UpDown ;			/**<涨跌 */
	TThostFtdcMoneyType				Turnover ;			/**<成交额 */
	TThostFtdcPriceType				Settle ;			/**<结算价 */
	TThostFtdcPriceType				Average ;			/**<均价 */
	TThostFtdcDateType				QuoteDate ;			/**<行情日期 */
	TThostFtdcTimeType				QuoteTime ;			/**<行情时间 */
	TThostFtdcWeightType			weight;			//成交（双边）重量
	TThostFtdcPriceType				highLimit;			//涨停板
	TThostFtdcPriceType				lowLimit;			//跌停板
	TThostFtdcRateType				UpDownRate;				//涨跌幅度
};


///输入报单
struct CThostFtdcInputOrderField
{
	TThostFtdcSeatIDType			seatID;          //2		席位号	是	
	TThostFtdcClientIDType			tradeCode;        //3		交易编码	是		
	TThostFtdcInstrumentIDType      instID;          //5		品种代码	是	
	TThostFtdcBsFlagType			buyOrSell;       //6		买卖方向	是
	TThostFtdcOffsetFlagType		offsetFlag;      //7		开平标志	是	
	TThostFtdcVolumeType			amount;          //8		委托数量	是	
	TThostFtdcByteType				middleFlag;      //9		中立仓标志	是	常量为0	
	TThostFtdcByteType				priceFlag;       //11		条件委托价格类型	是	
	TThostFtdcPriceType				price;           //12		预委托价格	是	
	TThostFtdcPriceType				trigPrice;	      //13       预委托触发价格	是	
	TThostFtdcMarketIDType			marketID;        //14		市场代码	是	
	TThostFtdcOrderRefType			LocalOrderNo;	 //			本地报单号
	TThostFtdcTradeWayType			tradeWay;		 //19		交易渠道	是	
};

///报单
struct CThostFtdcOrderField
{
	TThostFtdcOrderNoType			orderNo;				//1		系统报单号	是	
	TThostFtdcOrderRefType			localOrderNo;;			//2		本地报单号	是	
	TThostFtdcMarketIDType			marketID;				//4		市场代码	是	
	TThostFtdcInstrumentIDType      instID;				//5		合约代码	是	
	TThostFtdcBsFlagType			buyOrSell;				//7		买卖方向	是	
	TThostFtdcOffsetFlagType		offsetFlag;			 //8		开平标志	是	
	TThostFtdcVolumeType			amount;				//9		委托数量	是	
	TThostFtdcWeightType			weight;				//10		委托重量	是	常量为0
	TThostFtdcPriceType				price;					//11		委托价格	是	
	TThostFtdcVolumeType			matchQty;				//12		成交手数	是	
	TThostFtdcWeightType			matchWeight;			 //13		成交重量	是	
	TThostFtdcOrderStatusType		status;				//14       委托状态	是	
	TThostFtdcTimeType				entrustTime;				//15		委托时间	是	
	TThostFtdcByteType				forceoffset_flag;			 //16		强平标志	是	
	TThostFtdcVolumeType			cancelQty;			//17		撤单手数	是	
	TThostFtdcTimeType				cancelTime;			 //18撤单时间
	TThostFtdcTradeWayType			tradeWay;				//19		交易渠道	是	
};

///报单撤单回报
struct CThostFtdcOrderRtnField
{
	TThostFtdcOrderNoType			orderNo;				//1		系统报单号	是	
	TThostFtdcOrderRefType			localOrderNo;;			//2		本地报单号	是	
	TThostFtdcOrderStatusType		status;					//14    委托状态	是	
	TThostFtdcVolumeType			cancelQty;				//17	撤单手数	是
};


///输入报单操作(cancel order)
struct CThostFtdcInputOrderActionField
{
	TThostFtdcOrderRefType		localOrderNo;     //1		本地报单号	是
	TThostFtdcMarketIDType		marketID;		  //2		市场代码	是
	TThostFtdcOrderStatusType	status;			  //14      委托状态	
};

///报单操作
struct CThostFtdcOrderActionField
{
	TThostFtdcOrderRefType		localOrderNo;     //1		本地报单号	是	
	TThostFtdcByteType			orderFlag;       //2		委托标志	是	
	TThostFtdcMarketIDType		marketID;		  //3		市场代码	是	
	TThostFtdcTraderIDType		traderID;         //6		撤单操作员	是	
	TThostFtdcTradeWayType      tradeWay;         //7		委托渠道	是	写死"5"
};
///成交
struct CThostFtdcTradeField
{
	TThostFtdcOrderNoType			orderNo;           //1		系统报单号	是	
	TThostFtdcMatchNoType			matchNo;           //2		成交单编号	是	
	TThostFtdcInstrumentIDType		instID;            //3		合约代码	是	
	TThostFtdcBsFlagType			buyOrSell;	     //5		买卖方向	是	
	TThostFtdcOffsetFlagType		offSetFlag;     //6		开平标志	是	
	TThostFtdcPriceType				price;             //7		成交价格	是	
	TThostFtdcVolumeType			volume;            //8		成交手数	是	
	TThostFtdcMoneyType				amount;            //9		成交金额	是	
	TThostFtdcWeightType			weight;            //10		成交重量	是	
	TThostFtdcByteType				order_flag;        //11		委托类型	是	
	TThostFtdcDateType				matchDate;	     //12		成交日期	是	
	TThostFtdcTimeType				matchTime;         //13		成交时间	是	
	TThostFtdcOrderRefType			localOrderNo;	     //14		本地报单号	是	
	TThostFtdcMarketIDType			marketID;	     //15		市场代码	是	
	TThostFtdcMoneyType				trade_fee;         //16		手续费	是	
	TThostFtdcByteType				forceoffset_flag;  //17		强平标志	是	
	TThostFtdcVolumeType			forcebatchnum ;    //18		强平批次号	是
	TThostFtdcTradeWayType			tradeWay;          //渠道标志
};

///查询合约
struct CThostFtdcQryInstrumentField
{
	TThostFtdcContractIDType  ContractID;          /*合约号*/
	TThostFtdcProductIDType   ProductID;           /*产品代码*/
};


///查询成交
struct CThostFtdcQryTradeField
{
	TThostFtdcMatchNoType		matchNo;			//成交编号
	TThostFtdcInstrumentIDType  instID;				//合约代码
	TThostFtdcMarketIDType		marketID;			//市场代码
	TThostFtdcOrderRefType		localOrderNo;		//本地报单编号
};


///查询报单
struct CThostFtdcQryOrderField
{
	TThostFtdcInstrumentIDType  instID;				//合约代码
	TThostFtdcMarketIDType		marketID;			//市场代码
	TThostFtdcOrderRefType		localOrderNo;		//本地报单编号
};




///查询投资者持仓
struct CThostFtdcQryInvestorPositionField
{
	TThostFtdcMarketIDType		marketID;			//市场代码
	TThostFtdcInstrumentIDType	instID;         //合约代码
};


///查询库存
struct CThostFtdcQryStorageField
{
	TThostFtdcVarietyIDType  varietyID;            //交割品种代码
};

//库存应答
struct CThostFtdcStorageField
{
	TThostFtdcVarietyIDType  varietyID;            //3		交割品种代码	是	
	TThostFtdcAbbrType       varietyName;          //4		交割品种简称	是	
	TThostFtdcWeightType     totalStorage;         //6		库存总量	是	
	TThostFtdcWeightType     availableStorage;     //7		可用库存	是	
	TThostFtdcWeightType     frozenStorage;	      //8		现货冻结库存	是	
	TThostFtdcWeightType     pendStorage;          //9		待提库存	是	
	TThostFtdcWeightType     todayBuy;             //10		当日买入	是	
	TThostFtdcWeightType     todaySell;	          //11		当日卖出	是	
	TThostFtdcWeightType     todayDeposit;         //12		当日存入	是	
	TThostFtdcWeightType     todayRealDeposit;     //13		当日提出	是	
	TThostFtdcWeightType     todayBorrow;          //14		当日借入	是	
	TThostFtdcWeightType     todayLend;	          //15		当日借出	是	
	TThostFtdcWeightType     impawnStorage;        //16		质押库存	是	
	TThostFtdcWeightType     lawFrozen;            //17		法律冻结库存	是	
	TThostFtdcWeightType     bankFrozen;           //18		银行冻结库存	是	
	TThostFtdcByteType       customType;           //19		客户类别	是	
	TThostFtdcWeightType     storageCost;          //20		库存成本	是	
	TThostFtdcWeightType     impawnFrozen;        //22		质押冻结库存	是	
};

//市场状态
struct CThostFtdcMarketStatusField
{
	TThostFtdcMktStatusType   MktStatus;           /*市场状态*/
	TThostFtdcMarketIDType    marketID;         /*市场代码*/
};
///指定的合约
struct CThostFtdcSpecificInstrumentField
{
	///合约代码
	TThostFtdcInstrumentIDType	InstrumentID;
};


//}	// end of namespace KingstarAPI

#endif
