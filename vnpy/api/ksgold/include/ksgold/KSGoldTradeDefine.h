#ifndef __KSGOLDTRADEDEFINE_H__
#define __KSGOLDTRADEDEFINE_H__
//市场类型 变量名:TMarketType
#define KS_SPOT			"00"     //现货
#define KS_DEFER		"10"     //递延
#define KS_FUTURES		"11"     //期货
#define KS_FORWARD		"01"     //远期
#define KS_DELIVERY		"AP"	 //交割
#define KS_MIDDLE		"MD"	 //中立仓

//合约状态
#define KS_I_INITING		'0'     //初始化中
#define KS_I_INIT			'1'     //初始化完成
#define KS_I_BEGIN			'2'     //开盘
#define KS_I_GRP_ORDER		'3'     //竞价报单
#define KS_I_GRP_MATCH		'4'     //竞价撮合
#define KS_I_NORMAL			'5'     //连续交易
#define KS_I_PAUSE			'6'     //暂停
#define KS_I_DERY_APP		'7'     //交割申报
#define KS_I_DERY_MATCH		'8'     //交割申报结束
#define KS_I_MID_APP		'9'     //中立仓申报
#define KS_I_MID_MATCH		'A'     //交割申报撮合
#define KS_I_END			'B'     //收盘

//市场状态
#define KS_M_INITING	'0'     //初始化中
#define KS_M_INIT		'1'     //初始化完成
#define KS_M_OPEN		'2'     //开市
#define KS_M_TRADE		'3'     //交易
#define KS_M_PAUSE		'4'     //暂停
#define KS_M_CLOSE		'5'     //收市
 
//普通委托单状态
#define KS_Entrust_Sending				'1'			//已经发送；
#define KS_Entrust_Waiting				'2'			//等待报入
#define KS_Entrust_In					'3'			//已经报入；
#define KS_Entrust_All_Cancel			'4'			//全部撤销；
#define KS_Entrust_All_Done				'5'			//全部成交；
#define KS_Entrust_Part_Done			'6'			//部分成交；
#define KS_Entrust_Part_Done_Cancel		'7'			//部成部撤
#define KS_Entrust_Wait_Cancel			'8'			//等待撤销
#define KS_Entrust_Error				'9'			//错误委托
#define KS_Entrust_By_Exch				'A'			//场内撤单
#define KS_Entrust_By_Emergency			'B'			//应急撤单
#define KS_Entrust_By_Auto_Cancel		'C'			//自动撤单

//条件单委托价格类型
#define  KS_CONDITION_MARKET_PRICE       '0'		//市价
#define  KS_CONDITION_BUYFIVE_PRICE		 '1'		//买五档
#define  KS_CONDITION_SELLFIVE_PRICE	 '2'		//卖五档
#define  KS_CONDITION_COMMON_PRICE		 '3'        //普通委托(手输)
#define  KS_CONDITION_BUYONE_PRICE		 '4'		//买一价
#define  KS_CONDITION_SELLONE_PRICE		 '5'		//卖一价
#define  KS_CONDITION_BUYTWO_PRICE		 '6'		//买二价
#define  KS_CONDITION_SELLTWO_PRICE		 '7'		//卖二价
#define  KS_CONDITION_BUYTHREE_PRICE	 '8'		//买三价
#define  KS_CONDITION_SELLTHREE_PRICE	 '9'		//卖三价
#define  KS_CONDITION_BUYFOUR_PRICE		 'a'		//买四价
#define  KS_CONDITION_SELLFOUR_PRICE	 'b'		//卖四价 

//条件单委托类型
#define	 KS_CONDITION_PROFIT_ORDER       '0'		//止盈单,大于等于触发价
#define	 KS_CONDITION_LOSS_ORDER         '1'		//止损单,小于等于触发价

//条件单委托状态
#define  KS_CONDITION_ORDER_NOTTRIGGER	 '0'		//未触发
#define  KS_CONDITION_ORDER_SUCCESS		 '1'		//已触发-报入成功
#define  KS_CONDITION_ORDER_STATUS		 '2'		//已触发-报入失败
#define  KS_CONDITION_ORDER_NOTUSE		 '3'		//已作废-客户作废
#define  KS_CONDITION_ORDER_EXPIRED		 '4'		//已作废-系统过期作废
#define  KS_CONDITION_ORDER_PROCESSING	 '5'		//正在处理

//开平仓标志 变量名:TOffsetFlag
#define KS_P_OPEN		    '0'     //开仓
#define KS_P_OFFSET			'1'     //平仓


//买卖方向标志 变量名:TBSFlag
#define KS_BUY		'0'     //买
#define KS_SELL		'1'     //卖

//委托类型
#define  KS_SPOT_ENTRUST     '0' //现货
#define  KS_TN_ENTRUST       '4' //现货T+N
#define  KS_DEFER_ENTRUST    '1' //现货延期
#define  KS_DELIVERY_ENTRUST '2' //交割
#define  KS_MIDDLE_ENTRUST   '3' //中立仓

//渠道类型
#define  KS_COUNTER_CHANNEL  '1' //柜台
#define  KS_TEL_CHANNEL      '2' //电话银行
#define  KS_NET_CHANNEL      '3' //网银
#define  KS_TRADER_CHANNEL   '4' //交易员
#define  KS_SELF_CHANNEL	 '5' //自助终端
#define  KS_PHONE_CHANNEL	 '6' //手机银行
#define  KS_TRADEAPI_CHANNEL '7' //交易API

//客户类别
#define KS_CLIENT_SPOT    '0' //现货
#define KS_CLIENT_FUTURE  '1' //期货
#define KS_CLIENT_GENERAL '2' //通用

//登录类型
#define KS_BANKACC_TYPE   "1" //银行账号登录
#define KS_TRADECODE_TYPE "2" //交易编码登录

//活跃标志
#define KS_ACTIVITY_ON '1' //询价合约

//品种类别
#define KS_VARIETY_CODE_GOLD   0    //黄金
#define KS_VARIETY_CODE_AG     1    //白银
#define KS_VARIETY_CODE_PT     2    //铂金

#define KS_LOG_CLEAR_DAY 3 // 过期日志清除天数

// 日志起始符
#define KS_BEGIN_	  "$" 
// 日志分隔符
#define KS_SPLIT_	  "|" 

//API连接状态标识
#define KS_FRONTCONNECTED		1		//已连接
#define KS_DISCONNECTED			2       //断开连接
#define KS_RECONNECTING			3       //断线重连
#define KS_ONSTATUSCHANGE		4       //状态改变

//API状态机标识
#define KS_STATE_INIT			'0'		//初始状态
#define KS_STATE_READY			'1'		//就绪状态
#define KS_STATE_ONLINE			'2'		//在线状态
#define	KS_STATE_LOGON			'3'		//录入状态

//指令类型
#define KS_COMM_INSTRUCTION		   '0'     //普通指令
#define KS_FOK_INSTRUCTION		   '1'     //FOK指令
#define KS_FAK_INSTRUCTION		   '2'     //FAK指令
#define KS_MP2FP_INSTUCTION        '3'	   //市价剩余转限价
#define KS_MPFOK_INSTUCTION        '4'     //市价FOK指令
#define KS_MPFAK_INSTUCTION        '5'     //市价FAK指令	

//ETF交易类型
#define ETF_SCRIPTION           "020"   //认购
#define ETF_PURCHASE            "022"   //申购
#define ETF_REDEEM              "024"   //赎回

//ETF交易状态
#define ETF_PURCHASE_REQ					"101"   //申购请求
#define ETF_PURCHASE_RETURN_SUCCESS         "102"   //申购回报成功
#define ETF_PURCHASE_RETURN_FAIL            "103"   //申购回报失败
#define ETF_PURCHASE_CONFIRM_SUCCESS        "104"   //申购确认成功
#define ETF_PURCHASE_CONFIRM_FAIL           "105"   //申购确认失败
#define ETF_SCRIPTION_REQ					"201"   //认购请求
#define ETF_SCRIPTION_RETURN_SUCCESS        "202"   //认购回报成功
#define ETF_SCRIPTION_RETURN_FAIL           "203"   //认购回报失败
#define ETF_SCRIPTION_SUCCESS				"204"   //认购成功
#define ETF_SCRIPTION_FAIL					"205"   //认购失败
#define ETF_SCRIPTION_CONFIRM_SUCCESS	    "206"   //认购确认成功
#define ETF_SCRIPTION_CONFIRM_FAIL          "207"   //认购确认失败
#define ETF_TRANSFER_REQ			        "208"   //过户请求
#define ETF_REDEEM_REQ						"301"   //赎回请求
#define ETF_REDEEM_CONFIRM_SUCCESS          "304"   //赎回确认成功
#define ETF_REDEEM_TRANSFER_FAIL			"305"   //赎回过户失败
#define ETF_FROZEN_REQ						"401"   //冻结请求
#define ETF_FROZEN_SUCCESS					"402"   //冻结成功
#define ETF_FROZEN_FAIL						"403"   //冻结失败
#define ETF_TRANSFER_SUCCESS				"404"   //过户成功S
#define ETF_TRANSFER_FAIL					"405"   //过户失败
#define ETF_UNFROZEN_SUCCESS				"406"   //解冻成功
#define ETF_UNFROZEN_FAIL					"407"   //解冻失败
#define ETF_FUNDUNIT_DECREASE_REQ           "501"   //份额增加请求
#define ETF_FUNDUNIT_DECREASE_SUCCESS       "502"   //份额增加成功
#define ETF_FUNDUNIT_DECREASE_FAIL          "503"   //份额增加失败
#define ETF_FUNDUNIT_INCREASE_REQ           "601"   //份额减少请求
#define ETF_FUNDUNIT_INCREASE_SUCCESS		"602"   //份额减少成功
#define ETF_FUNDUNIT_INCREASE_FAIL          "603"   //份额减少失败
#define ETF_ERR_ENTRUST                     "901"   //错误委托


#define ETF_ACCOUNT_UNBINDING                               "000"   //未绑定
#define ETF_ACCOUNT_BINDING_WAITIN_GCONFIRM                 "701"   //绑定待确认
#define ETF_ACCOUNT_BINDING_FINISH                          "702"   //绑定已完成
#define ETF_ACCOUNT_BINDING_FAIL                            "703"   //绑定已失败
#define ETF_ACCOUNT_BINDING_SEND                            "704"   //绑定已发送
#define ETF_ACCOUNT_UNBINDING_WAITIN_GCONFIRM               "801"   //解绑定待确认
#define ETF_ACCOUNT_UNBINDING_FINISH                        "802"   //解绑定已完成
#define ETF_ACCOUNT_UNBINDING_FAIL                          "803"   //解绑定已失败
#define ETF_ACCOUNT_UNBINDING_SEND                          "804"   //解绑定已发送

//API条件判断类型
#define KS_CONDITION_FIRSTLOGIN	1		//首次登录

#endif //__KSGOLDTRADEDEFINE_H__
