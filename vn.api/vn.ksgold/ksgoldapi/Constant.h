#ifndef _NEWCONSTANT_H
#define _NEWCONSTANT_H
//市场类型 变量名:TMarketType
#define SPOT		"00"     //现货
#define DEFER		"10"     //递延
#define FUTURES		"11"     //期货
#define FORWARD		"01"     //远期
#define DELIVERY	"AP"	 //交割
#define MIDDLE		"MD"	 //中立仓


//市场状态
#define M_INITING	'0'     //初始化中
#define M_INIT		'1'     //初始化完成
#define M_OPEN		'2'     //开市
#define M_TRADE		'3'     //交易
#define M_PAUSE		'4'     //暂停
#define M_CLOSE		'5'     //收市

//委托单状态
#define Entrust_Sending				'1'			//1：已经发送；
#define Entrust_Waiting				'2'			//2：等待报入
#define Entrust_In				'3'			//3：已经报入；
#define Entrust_All_Cancel			'4'			//4：全部撤销；
#define Entrust_All_Done			'5'			//5：全部成交；
#define Entrust_Part_Done			'6'			//6：部分成交；
#define Entrust_Part_Done_Cancel		'7'			//7：部成部撤
#define Entrust_Wait_Cancel			'8'			//等待撤销
#define Entrust_Error				'9'			//错误委托
#define Entrust_By_Exch				'A'			//场内撤单
#define Entrust_By_Emergency			'B'			//应急撤单


//开平仓标志 变量名:TOffsetFlag
#define P_OPEN		    '0'     //开仓
#define p_OFFSET	    '1'     //平仓


//买卖方向标志 变量名:TBSFlag
#define BUY		'0'     //买
#define SELL	'1'     //卖

//委托类型
#define  SPOT_ENTRUST     '0' //现货
#define  TN_ENTRUST       '4' //现货T+N
#define  DEFER_ENTRUST    '1' //现货延期
#define  DELIVERY_ENTRUST '2' //交割
#define  MIDDLE_ENTRUST   '3' //中立仓

//渠道类型
#define  COUNTER_CHANNEL  '1' //柜台
#define  TEL_CHANNEL      '2' //电话银行
#define  NET_CHANNEL      '3' //网银
#define  TRADER_CHANNEL   '4' //交易员
#define  SELF_CHANNEL	  '5' //自助终端
#define  PHONE_CHANNEL	  '6' //手机银行
#define  TRADEAPI_CHANNEL '7' //交易API

//客户类别
#define CLIENT_SPOT    '0' //现货
#define CLIENT_FUTURE  '1' //期货
#define CLIENT_GENERAL '2' //通用

//登录类型
#define BANKACC_TYPE   "1" //银行账号登录
#define TRADECODE_TYPE "2" //交易编码登录

//活跃标志
#define ACTIVITY_ON '1' //询价合约

#endif _NEWCONSTANT_H
