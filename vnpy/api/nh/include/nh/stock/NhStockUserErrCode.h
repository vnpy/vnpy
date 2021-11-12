
#ifndef __DC_API_ERRCODE_H__
#define __DC_API_ERRCODE_H__

///////////////////////////////////////////////////////////////////////////
//成功
const int Err_Success									= 0;
//表示交易所网络连接失败
const int Err_DisConnect							=-1;
//表示交易所未处理请求超过许可数
const int Err_Untreated_Request				=-2;									
//表示交易所每秒发送请求数超过许可数
const int Err_PreSecond_Request			=-3;
//表示交易所服务器未登录成功
const int Err_Exchange_Not_Login			=3;
//用户未登录
const int Err_User_Not_Login					=4;
//非本交易所API登录
const int Err_Version =5;
//API版本信息出错
const int Err_ApiVersion =6;
//系统正在初始化
const int Err_System_Init =7;
//重复的登录
const int Err_RepeatLogin =8;
//密码错
const int Err_PassWord =9;
//用户未找到
const int Err_UserNotExist=10;
//更新密码失败
const int Err_Update_Pwd_Failed = 12;
//生成密码失败
const int Err_Create_Pwd_Failed		= 13;
//查询信息失败
const int Err_Query_Failed		= 14;
//撤单时未找到原始报单
const int Err_DelOrder_Err1		= 16;
//报单在发往交易所之前被撤单
const int Err_DelOrder_Err2		= 17;
//报单状态为已撤单状态不可撤单
const int Err_DelOrder_Err3		= 18;
//报单状态为全部成交状态不可撤单
const int Err_DelOrder_Err4		= 19;
//报单为错单不可撤单
const int Err_DelOrder_Err5		= 20;
//撤单时原始报单为不可撤单状态
const int Err_DelOrder_Err6		= 21;
//重复的报单
const int Err_Order_Err1		= 22;
//报单时未找到对应的合约信息
const int Err_Order_Err2		= 23;
//报单时买卖方向字段错误
const int Err_Order_Err3		= 24;
//报单时有效期类型字段错误
const int Err_Order_Err4		= 25;
//报单时价格字段错误
const int Err_Order_Err5		= 26;
//报单时数量字段错误
const int Err_Order_Err6		= 27;
//报单价格条件错误
const int Err_Order_Err7		= 28;
//报单时未获取到客户对应的资金信息
const int Err_Order_Err8		= 29;
//报单时资金不足
const int Err_Order_Err9		= 30;
//不能撤销其他客户报单
const int Err_Order_Err11	= 32;
//报单时价格信息不符合最小价位变动要求
const int Err_Order_Err12	= 33;
//报单时数量信息不符合最小数量变动要求
const int Err_Order_Err13	= 34;
//市价单金额不符合系统要求
const int Err_Order_Err14	= 35;
//用户信息验证失败
const int Err_UserInfo_Failed = 36;
//服务器分配会话信息失败
const int Err_Create_Session			=37;
//日内过度交易行为
const int Err_Excessive_Trading			=38;
//大额报撤单行为
const int Err_Large_Del			=39;
//频繁撤单行为
const int Err_Frequent_Del			=40;
//最后交割日的合约不允许开仓
const int Err_EndDelivDate			=41;
//投机套保标记错误
const int Err_Order_Err15	= 42;
//开平标志错误
const int Err_Order_Err16	= 43;
//买卖方向错误
const int Err_Order_Err17	= 44;
//报单价格条件错误
const int Err_Order_Err18	= 45;
//有效期类型错误
const int Err_Order_Err19	= 46;
//成交量类型错误
const int Err_Order_Err20	= 47;
//触发条件错误
const int Err_Order_Err21	= 48;
//当前状态禁止此项操作
const int Err_Order_Err22	= 49;
//平仓时客户持仓不足
const int Err_Order_Err23	= 50;
//价格超出涨停板
const int Err_Order_Err24	= 51;
//价格跌破跌停板
const int Err_Order_Err25	= 52;
//操作标志错误
const int Err_Order_Err26	= 53;
//不支持该交易所报单或交易所字段不正确
const int Err_Order_Err27	= 54;
//获取客户端连接地址信息时出错
const int Err_Order_Err55 = 55;
//合约类型不对
const int Err_Order_Err56 = 56;
//备兑只能是卖开或买平
const int Err_Order_Err57 = 57;
//备兑开仓时标的合约持仓不足
const int Err_Order_Err58 = 58;
//距离交割日时间太短不允许开义务仓
const int Err_Order_Err59 = 59;
//组合或拆分标志错
const int Err_Order_Err60 = 60;
//不支持该组合策略
const int Err_Order_Err61 = 61;
//不支持行权操作
const int Err_Order_Err63 = 63;

#endif
