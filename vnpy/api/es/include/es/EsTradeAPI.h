//============================================================================
/* 新易盛统一交易API接口
 * 该文件定义了EsTradeAPI 使用的接口函数和功能
 * 版本信息:2018-05-21 郭晓刚 创建该文件
 */
//=============================================================================
#ifndef ES_TRADE_API_H
#define ES_TRADE_API_H

#include "EsTradeAPIStruct.h"
    
#if defined WIN32 || defined _WIN64
#define ES_CDECL __cdecl
#define ES_DLLEXPORT __declspec(dllexport)
#else
#define ES_CDECL
#define ES_DLLEXPORT
#endif

//EsTradeAPI.h
//文件定义了EsTradeAPI提供给开发者的对外接口、函数和回调接口。
namespace EsTradeAPI
{
    
//EsTradeAPI 的回调通知接口
class IEsTradeAPINotify
{
public:
    /**
    * @brief 某一个登录用户连接成功回调通知
    * @param[in] UserNo 登录用户UserNo。
    * @ingroup G_T_Login
    */
    virtual void ES_CDECL OnConnect(const TAPISTR_20 UserNo) = 0;
    /**
    * @brief    系统登录过程回调。
    * @details    此函数为Login()登录函数的回调，调用Login()成功后建立了链路连接，然后API将向服务器发送登录认证信息，
    *            登录期间的数据发送情况和登录的回馈信息传递到此回调函数中。
    * @param[in] UserNo 登录用户UserNo。
    * @param[in] nErrorCode 返回错误码,0表示成功。
    * @param[in] pLoginRspInfo 登陆应答信息，如果nErrorCode!=0，则loginRspInfo=NULL。
    * @attention    该回调返回成功，说明用户登录成功。但是不代表当前登录用户准备完毕。
    * @ingroup G_T_Login
    */
    virtual void ES_CDECL OnRspLogin(const TAPISTR_20 UserNo, TAPIINT32 nErrorCode, const TapAPITradeLoginRspInfo *pLoginRspInfo) = 0;
    /**
    * @brief    二次认证联系方式通知。(北斗星专用)
    * @details    登录完成后，如果需要二次认证，会收到联系方式的通知，可以选择通知消息的一个联系方式（邮箱或者电话）
    *            请求发送二次认证授权码（RequestVertificateCode）。
    * @param[in] UserNo 登录用户UserNo。
    * @param[in] nErrorCode 返回错误码,0表示成功。如果账户没有绑定二次认证联系方式，则返回10055错误。
    * @param[in] isLast 标识是否是最后一条联系信息。
    * @param[in] pInfo 认证方式信息，如果errorCode!=0，则ContactInfo为空。
    * @attention    该回调返回成功，说明需要二次认证，并且需要选择一个联系方式然后调用RequestVertificateCode。
    * @ingroup G_T_Login
    */
    virtual void ES_CDECL OnRtnContactInfo(const TAPISTR_20 UserNo, TAPIINT32 nErrorCode, TAPIYNFLAG isLast, const TapAPISecondInfo* pInfo) = 0;
    /**
    * @brief    请求发送二次认证码应答。(北斗星专用)
    * @details    请求获取二次认证授权码，后台发送邮件或者短信，并给出应答，包含发送序号以及认证码有效期。
    * @param[in] UserNo 登录用户UserNo。
    * @param[in] nSessionID 请求二次认证码会话ID。
    * @param[in] nErrorCode 如果没有绑定联系，返回错误.
    * @param[in] isLast 标识是否是最后一条联系信息。
    * @param[in] pInfo 二次认证码有效期，以分钟返回，在二次认证有效期内，可以重复设置二次认证码，但是不能再重新申请二次认证码。
    * @attention 该回调返回成功，然后调用SetVertificateCode。
    * @ingroup G_T_Login
    */
    virtual void ES_CDECL OnRspRequestVertificateCode(const TAPISTR_20 UserNo, TAPIUINT32 nSessionID, TAPIINT32 nErrorCode, TAPIYNFLAG isLast, const TapAPIVertificateCode *pInfo) = 0;
    /**
    * @brief 重要错误信息提示
    * @details 当API内部出现严重错误时提示用户错误信息。
    * @param[in] UserNo 登录用户UserNo。
    * @param[in] ErrorMsg 错误提示信息。
    * @attention 该函数回调，则说明API运行时存在严重错误。
    * @ingroup G_T_TradeSystem
    */
    virtual void ES_CDECL OnRtnErrorMsg(const TAPISTR_20 UserNo, const TAPISTR_500 ErrorMsg) = 0;
    /**
    * @brief    通知用户API准备就绪。
    * @details    只有用户回调收到此就绪通知时才能进行对应登录用户后续的各种操作。此回调函数是某个登录用户能否正常工作的标志。
    * @param[in] UserNo 登录用户UserNo。
    * @attention 就绪后才可以进行后续操作
    * @ingroup G_T_Login
    */
    virtual void ES_CDECL OnAPIReady(const TAPISTR_20 UserNo) = 0;
    /**
    * @brief API和服务失去连接的回调
    * @details 在API使用过程中主动或者被动与服务器服务失去连接后都会触发此回调通知用户与服务器的连接已经断开。
    * @param[in] UserNo 登录用户UserNo。
    * @param[in] nReasonCode 断开原因代码。
    * @ingroup G_T_Disconnect
    */
    virtual void ES_CDECL OnDisconnect(const TAPISTR_20 UserNo, TAPIINT32 nReasonCode) = 0;
    /**
    * @brief 通知用户提交用户登录信息结果(启明星专用)
    * @param[in] UserNo 指向该信息对应的UserNo 
    * @param[in] nSessionID 提交用户登录信息的请求ID,和SubmitUserLoginInfo返回的请求ID对应。
    * @param[in] pRspInfo 指向返回的信息结构体。
    * @attention 不要修改和删除pRspInfo所指示的数据；函数调用结束，参数不再有效。
    * @ingroup G_T_UserInfo
    */
    virtual void ES_CDECL OnRspSubmitUserLoginInfo(const TAPISTR_20 UserNo, TAPIUINT32 nSessionID, const TapAPISubmitUserLoginInfoRsp *pRspInfo) = 0;
    /**
    * @brief 用户密码修改应答(启明星、北斗星专用)
    * @param[in] UserNo 指向该信息对应的UserNo
    * @param[in] nSessionID 修改密码的请求ID,和ChangePassword的请求ID对应。
    * @param[in] nErrorCode 返回错误码，0表示成功。
    * @ingroup G_T_UserInfo
    */
    virtual void ES_CDECL OnRspChangePassword(const TAPISTR_20 UserNo, TAPIUINT32 nSessionID, TAPIINT32 nErrorCode) = 0;
    /**
    * @brief 设置用户预留信息反馈
    * @param[in] UserNo 指向该信息对应的UserNo
    * @param[in] nSessionID 设置用户预留信息的请求ID
    * @param[in] nErrorCode 返回错误码，0表示成功。
    * @param[in] info 指向返回的信息结构体。当nErrorCode不为0时，info为空。
    * @attention 不要修改和删除info所指示的数据；函数调用结束，参数不再有效。
    * @note 该接口暂未实现
    * @ingroup G_T_UserInfo
    */
    virtual void ES_CDECL OnRspSetReservedInfo(const TAPISTR_20 UserNo, TAPIUINT32 nSessionID, TAPIINT32 nErrorCode, const TAPISTR_50 info) = 0;
    /**
    * @brief    返回新增合约信息(启明星、北斗星专用)
    * @details    向用户推送新的合约。主要用来处理在交易时间段中服务器添加了新合约时，向用户发送这个合约的信息。
    * @param[in] UserNo 指向该信息对应的UserNo
    * @param[in] pRtnInfo    指向返回的信息结构体。
    * @attention 不要修改和删除pRspInfo所指示的数据；函数调用结束，参数不再有效。
    * @ingroup G_T_Contract
    */
    virtual void ES_CDECL OnRtnContract(const TAPISTR_20 UserNo, const TapAPITradeContractInfo *pRtnInfo) = 0;
    /**
    * @brief 用户资金变化通知
    * @details 用户的委托成交后会引起资金数据的变化，因此需要向用户实时反馈。
    * @param[in] UserNo 指向该信息对应的UserNo
    * @param[in] pRtnInfo 指向返回的信息结构体。
    * @note 如果不关注此项内容，可以设定Login时的NoticeIgnoreFlag以屏蔽。
    * @attention 不要修改和删除pRspInfo所指示的数据；函数调用结束，参数不再有效。
    * @ingroup G_T_FundInfo
    */
    virtual void ES_CDECL OnRtnFund(const TAPISTR_20 UserNo, const TapAPIFundData *pRtnInfo) = 0;
    /**
    * @brief 返回新委托。新下的或者其他地方下的推送过来的。
    * @details 服务器接收到客户下的委托内容后就会触发委托处理逻辑，同时向用户回馈一个委托应答说明服务器正确处理了用户的请求，返回的信息中包含了全部的委托信息，
    *            同时有一个用来标示此委托的委托号。如果是本地发出去的委托，委托应答中会返回请求ID
    * @param[in] UserNo 指向该信息对应的UserNo
    * @param[in] nRequestID 请求的会话ID；
    * @param[in] pRtnInfo 指向返回的信息结构体
    * @note 如果不关注此项内容，可以设定Login时的NoticeIgnoreFlag以屏蔽。
    * @attention 不要修改和删除pRspInfo所指示的数据；函数调用结束，参数不再有效。
    * @ingroup G_T_TradeActions
    */
    virtual void ES_CDECL OnRtnOrder(const TAPISTR_20 UserNo, TAPIUINT32 nRequestID, const TapAPIOrderInfo *pRtnInfo) = 0;
    /**
    * @brief 返回查询的委托变化流程信息(启明星、北斗星专用)
    * @param[in] UserNo 指向该信息对应的UserNo
    * @param[in] nRequestID 请求的会话ID；
    * @param[in] nErrorCode 错误码，当nErrorCode=0时，pRspInfo指向返回的委托变化流程结构体，不然为NULL；
    * @param[in] isLast 标示是否是最后一批数据；
    * @param[in] pRspInfo 返回的委托变化流程指针。
    * @attention 不要修改和删除pRspInfo所指示的数据；函数调用结束，参数不再有效。
    * @ingroup G_T_TradeInfo
    */
    virtual void ES_CDECL OnRspQryOrderProcess(const TAPISTR_20 UserNo, TAPIUINT32 nRequestID, TAPIINT32 nErrorCode, TAPIYNFLAG isLast, const TapAPIOrderInfo *pRspInfo) = 0;
    /**
    * @brief 推送来的成交信息
    * @details 用户的委托成交后将向用户推送成交信息。
    * @param[in] UserNo 指向该信息对应的UserNo
    * @param[in] pRtnInfo 指向返回的信息结构体。
    * @note 如果不关注此项内容，可以设定Login时的NoticeIgnoreFlag以屏蔽。
    * @attention 不要修改和删除pRspInfo所指示的数据；函数调用结束，参数不再有效。
    * @ingroup G_T_TradeActions
    */
    virtual void ES_CDECL OnRtnFill(const TAPISTR_20 UserNo, const TapAPIFillInfo *pRtnInfo) = 0;
    /**
    * @brief 持仓变化推送通知
    * @param[in] UserNo 指向该信息对应的UserNo
    * @param[in] pRtnInfo 指向返回的信息结构体。
    * @note 如果不关注此项内容，可以设定Login时的NoticeIgnoreFlag以屏蔽。
    * @attention 不要修改和删除pRspInfo所指示的数据；函数调用结束，参数不再有效。
    * @ingroup G_T_TradeActions
    */
    virtual void ES_CDECL OnRtnPosition(const TAPISTR_20 UserNo, const TapAPIPositionInfo *pRtnInfo) = 0;
    /**
    * @brief 平仓数据变化推送(启明星专用)
    * @param[in] UserNo 指向该信息对应的UserNo
    * @param[in] pRtnInfo 指向返回的信息结构体。
    * @note 如果不关注此项内容，可以设定Login时的NoticeIgnoreFlag以屏蔽。
    * @attention 不要修改和删除pRspInfo所指示的数据；函数调用结束，参数不再有效。
    * @ingroup G_T_TradeActions
    */
    virtual void ES_CDECL OnRtnClose(const TAPISTR_20 UserNo, const TapAPICloseInfo *pRtnInfo) = 0;
    /**
    * @brief 持仓盈亏通知(启明星、北斗星专用)
    * @param[in] UserNo 指向该信息对应的UserNo
    * @param[in] pRtnInfo 指向返回的信息结构体。
    * @note 如果不关注此项内容，可以设定Login时的NoticeIgnoreFlag以屏蔽。
    * @attention 不要修改和删除pRspInfo所指示的数据；函数调用结束，参数不再有效。
    * @ingroup G_T_TradeActions
    */
    virtual void ES_CDECL OnRtnPositionProfit(const TAPISTR_20 UserNo, const TapAPIPositionProfitNotice *pRtnInfo) = 0;
    /**
    * @brief 深度行情查询应答(启明星专用)
    * @param[in] UserNo 指向该信息对应的UserNo
    * @param[in] nRequestID 请求ID
    * @param[in] nErrorCode 错误码。0 表示成功。
    * @param[in] isLast 标示是否是最后一批数据；
    * @param[in] pRspInfo 指向返回的深度行情信息结构体。当nErrorCode不为0时，pRspInfo为空。
    * @attention 不要修改和删除pRspInfo所指示的数据；函数调用结束，参数不再有效。
    * @ingroup G_T_DeepQuote
    */
    virtual void ES_CDECL OnRspQryDeepQuote(const TAPISTR_20 UserNo, TAPIUINT32 nRequestID, TAPIINT32 nErrorCode, TAPIYNFLAG isLast, const TapAPIDeepQuoteQryRsp *pRspInfo) = 0;
    /**
    * @brief 交易所时间状态信息通知    (启明星，手机专用)
    * @param[out] UserNo 指向该信息对应的UserNo
    * @param[out] pRtnInfo 指向返回的信息结构体。
    * @attention 不要修改和删除pRspInfo所指示的数据；函数调用结束，参数不再有效。
    * @ingroup G_T_TradeSystem
    */
    virtual void ES_CDECL OnRtnExchangeStateInfo(const TAPISTR_20 UserNo, const TapAPIExchangeStateInfoNotice *pRtnInfo) = 0;
    /**
    * @brief 询价通知(启明星、北斗星专用)
    * @param[in] UserNo 指向该信息对应的UserNo
    * @param[in] pRtnInfo 指向返回的信息结构体。
    * @attention 不要修改和删除pRspInfo所指示的数据；函数调用结束，参数不再有效。
    * @ingroup G_T_TradeActions
    */
    virtual void ES_CDECL OnRtnReqQuoteNotice(const TAPISTR_20 UserNo, const TapAPIReqQuoteNotice *pRtnInfo) = 0;
    /**
    * @brief 客户最终费率应答(启明星专用)
    * @details 保证金比例计算方式：手数*每手乘数*计算参数*价格
    *          保证金定额计算方式：手数*计算参数
    *          手续费绝对方式计算方式：手数*按手数计算参数+手数*每手乘数*价格*按金额计算参数
    * @param[in] UserNo 指向该信息对应的UserNo
    * @param[in] nRequestID 请求ID；
    * @param[in] nErrorCode 错误码。0 表示成功。
    * @param[in] isLast     标示是否是最后一批数据
    * @param[in] pRspInfo    指向返回的信息结构体。当nErrorCode不为0时，pRspInfo为空。
    * @attention  不要修改和删除pRspInfo所指示的数据；函数调用结束，参数不再有效。
    * @ingroup G_T_AccountRentInfo
    */
    virtual void ES_CDECL OnRspAccountRentInfo(const TAPISTR_20 UserNo, TAPIUINT32 nRequestID, TAPIINT32 nErrorCode, TAPIYNFLAG isLast, const TapAPIAccountRentInfo *pRspInfo) = 0;
    /**
    * @brief    交易消息查询应答(启明星、北斗星专用)
    * @details    用户可以查询相关的交易消息。
    * @param[in] UserNo 指向该信息对应的UserNo
    * @param[in] nRequestID 请求ID；
    * @param[in] nErrorCode 错误码。0 表示成功。
    * @param[in] isLast     标示是否是最后一批数据
    * @param[in] pRspInfo    指向返回的信息结构体。
    * @attention 不要修改和删除pInfo所指示的数据；函数调用结束，参数不再有效。
    * @ingroup G_T_TradeSystem
    */
    virtual void ES_CDECL OnRspTradeMessage(const TAPISTR_20 UserNo, TAPIUINT32 nRequestID, TAPIINT32 nErrorCode, TAPIYNFLAG isLast, const TapAPITradeMessage *pRspInfo) = 0;
    /**
    * @brief    交易消息通知(启明星、北斗星专用)
    * @details    用户在交易过程中可能因为资金、持仓、平仓的状态变动使账户处于某些危险状态，或者某些重要的信息需要向用户通知。
    * @param[in] UserNo 指向该信息对应的UserNo
    * @param[in] pRtnInfo    指向返回的信息结构体。
    * @attention 不要修改和删除pInfo所指示的数据；函数调用结束，参数不再有效。
    * @ingroup G_T_TradeSystem
    */
    virtual void ES_CDECL OnRtnTradeMessage(const TAPISTR_20 UserNo, const TapAPITradeMessage *pRtnInfo) = 0;
    /**
    * @brief 历史委托查询应答(北斗星专用)
    * @param[in] UserNo 指向该信息对应的UserNo
    * @param[in] nRequestID 请求的会话ID；
    * @param[in] nErrorCode 错误码。0 表示成功。
    * @param[in] isLast     标示是否是最后一批数据
    * @param[in] pInfo        指向返回的信息结构体。当nErrorCode不为0时，pInfo为空。
    * @attention 不要修改和删除pInfo所指示的数据；函数调用结束，参数不再有效。
    * @ingroup G_T_HisInfo
    */
    virtual void ES_CDECL OnRspQryHisOrder(const TAPISTR_20 UserNo, TAPIUINT32 nRequestID, TAPIINT32 nErrorCode, TAPIYNFLAG isLast, const TapAPIHisOrderQryRsp *pInfo) = 0;
    /**
    * @brief 历史委托流程查询应答(北斗星专用)
    * @param[in] UserNo 指向该信息对应的UserNo
    * @param[in] nRequestID 请求的会话ID；
    * @param[in] nErrorCode 错误码。0 表示成功。
    * @param[in] isLast     标示是否是最后一批数据
    * @param[in] pInfo        指向返回的信息结构体。当nErrorCode不为0时，pInfo为空。
    * @attention 不要修改和删除pInfo所指示的数据；函数调用结束，参数不再有效。
    * @ingroup G_T_HisInfo
    */
    virtual void ES_CDECL OnRspQryHisOrderProcess(const TAPISTR_20 UserNo, TAPIUINT32 nRequestID, TAPIINT32 nErrorCode, TAPIYNFLAG isLast, const TapAPIHisOrderProcessQryRsp *pInfo) = 0;
    /**
    * @brief 历史成交查询应答(北斗星专用)
    * @param[in] UserNo 指向该信息对应的UserNo
    * @param[in] nRequestID 请求的会话ID；
    * @param[in] nErrorCode 错误码。0 表示成功。
    * @param[in] isLast     标示是否是最后一批数据
    * @param[in] pInfo        指向返回的信息结构体。当nErrorCode不为0时，pInfo为空。
    * @attention 不要修改和删除pInfo所指示的数据；函数调用结束，参数不再有效。
    * @ingroup G_T_HisInfo
    */
    virtual void ES_CDECL OnRspQryHisFill(const TAPISTR_20 UserNo, TAPIUINT32 nRequestID, TAPIINT32 nErrorCode, TAPIYNFLAG isLast, const TapAPIHisFillQryRsp *pInfo) = 0;
    /**
    * @brief 历史持仓查询应答(北斗星专用)
    * @param[in] UserNo 指向该信息对应的UserNo
    * @param[in] nRequestID 请求的会话ID；
    * @param[in] nErrorCode 错误码。0 表示成功。
    * @param[in] isLast     标示是否是最后一批数据
    * @param[in] pInfo        指向返回的信息结构体。当nErrorCode不为0时，pInfo为空。
    * @attention 不要修改和删除pInfo所指示的数据；函数调用结束，参数不再有效。
    * @ingroup G_T_HisInfo
    */
    virtual void ES_CDECL OnRspQryHisPosition(const TAPISTR_20 UserNo, TAPIUINT32 nRequestID, TAPIINT32 nErrorCode, TAPIYNFLAG isLast, const TapAPIHisPositionQryRsp *pInfo) = 0;
    /**
    * @brief 历史交割查询应答(北斗星专用)
    * @param[in] UserNo 指向该信息对应的UserNo
    * @param[in] nRequestID 请求的会话ID；
    * @param[in] nErrorCode 错误码。0 表示成功。
    * @param[in] isLast     标示是否是最后一批数据
    * @param[in] pInfo        指向返回的信息结构体。当nErrorCode不为0时，pInfo为空。
    * @attention 不要修改和删除pInfo所指示的数据；函数调用结束，参数不再有效。
    * @ingroup G_T_HisInfo
    */
    virtual void ES_CDECL OnRspQryHisDelivery(const TAPISTR_20 UserNo, TAPIUINT32 nRequestID, TAPIINT32 nErrorCode, TAPIYNFLAG isLast, const TapAPIHisDeliveryQryRsp *pInfo) = 0;
    /**
    * @brief 资金调整查询应答(北斗星专用)
    * @param[in] UserNo 指向该信息对应的UserNo
    * @param[in] nRequestID 请求的会话ID；
    * @param[in] nErrorCode 错误码。0 表示成功。
    * @param[in] isLast     标示是否是最后一批数据
    * @param[in] pInfo        指向返回的信息结构体。当nErrorCode不为0时，pInfo为空。
    * @attention 不要修改和删除pInfo所指示的数据；函数调用结束，参数不再有效。
    * @ingroup G_T_FundInfo
    */
    virtual void ES_CDECL OnRspQryAccountCashAdjust(const TAPISTR_20 UserNo, TAPIUINT32 nRequestID, TAPIINT32 nErrorCode, TAPIYNFLAG isLast, const TapAPIAccountCashAdjustQryRsp *pInfo) = 0;
    /**
    * @brief 查询用户账单应答(北斗星专用)
    * @param[in] UserNo 指向该信息对应的UserNo
    * @param[in] nRequestID 请求的会话ID；
    * @param[in] nErrorCode 错误码。0 表示成功。
    * @param[in] isLast     标示是否是最后一批数据
    * @param[in] pInfo        指向返回的信息结构体。当nErrorCode不为0时，pInfo为空。
    * @attention 不要修改和删除pInfo所指示的数据；函数调用结束，参数不再有效。
    * @ingroup G_T_Bill
    */
    virtual void ES_CDECL OnRspQryBill(const TAPISTR_20 UserNo, TAPIUINT32 nRequestID, TAPIINT32 nErrorCode, TAPIYNFLAG isLast, const TapAPIBillQryRsp *pInfo) = 0;
    /**
    * @brief 查询用户手续费参数(北斗星专用)
    * @param[in] UserNo 指向该信息对应的UserNo
    * @param[in] nRequestID 请求的会话ID；
    * @param[in] nErrorCode 错误码。0 表示成功。
    * @param[in] isLast     标示是否是最后一批数据
    * @param[in] pInfo        指向返回的信息结构体。当nErrorCode不为0时，pInfo为空。
    * @attention 不要修改和删除pInfo所指示的数据；函数调用结束，参数不再有效。
    * @ingroup G_T_AccountRentInfo
    */
    virtual void ES_CDECL OnRspAccountFeeRent(const TAPISTR_20 UserNo, TAPIUINT32 nRequestID, TAPIINT32 nErrorCode, TAPIYNFLAG isLast, const TapAPIAccountFeeRentQryRsp *pInfo) = 0;
    /**
    * @brief 查询用户保证金参数(北斗星专用)
    * @param[in] UserNo 指向该信息对应的UserNo
    * @param[in] nRequestID 请求的会话ID；
    * @param[in] nErrorCode 错误码。0 表示成功。
    * @param[in] isLast     标示是否是最后一批数据
    * @param[in] pInfo        指向返回的信息结构体。当nErrorCode不为0时，pInfo为空。
    * @attention 不要修改和删除pInfo所指示的数据；函数调用结束，参数不再有效。
    * @ingroup G_T_AccountRentInfo
    */
    virtual void ES_CDECL OnRspAccountMarginRent(const TAPISTR_20 UserNo, TAPIUINT32 nRequestID, TAPIINT32 nErrorCode, TAPIYNFLAG isLast, const TapAPIAccountMarginRentQryRsp *pInfo) = 0;
    /**
    * @brief 登录用户手机设备增加应答(北斗星专用)
    * @param[in] UserNo 登录用户UserNo
    * @param[in] nRequestID 请求ID
    * @param[in] nErrorCode 错误码。0 表示成功。
    * @param[in] isLast     标示是否是最后一批数据
    * @param[in] pInfo        指向返回的信息结构体。当nErrorCode不为0时，pInfo为空。
    * @attention 不要修改和删除pInfo所指示的数据；函数调用结束，参数不再有效。
    * @operationtype 异步操作
    * @ingroup G_T_Cellphone
    */
    virtual void ES_CDECL OnRspAddMobileDevice(const TAPISTR_20 UserNo, TAPIUINT32 nRequestID, TAPIINT32 nErrorCode, TAPIYNFLAG isLast, const TapAPIMobileDeviceAddRsp *pInfo) = 0;
    /**
    * @brief 管理日志查询(北斗星专用)
    * @param[in] UserNo 登录用户UserNo
    * @param[in] nRequestID 请求ID
    * @param[in] nErrorCode 错误码。0 表示成功。
    * @param[in] isLast     标示是否是最后一批数据
    * @param[in] pInfo        指向返回的信息结构体。当nErrorCode不为0时，pInfo为空。
    * @attention 不要修改和删除pInfo所指示的数据；函数调用结束，参数不再有效。
    * @operationtype 异步操作
    * @ingroup G_T_Cellphone
    */
    virtual void ES_CDECL OnRspQryManageInfoForEStar(const TAPISTR_20 UserNo, TAPIUINT32 nRequestID, TAPIINT32 nErrorCode, TAPIYNFLAG isLast, const TapAPIManageInfo *pInfo) = 0;
    /**
    * @brief 系统参数查询(北斗星专用)
    * @param[in] UserNo 登录用户UserNo
    * @param[in] nRequestID 请求ID
    * @param[in] nErrorCode 错误码。0 表示成功。
    * @param[in] isLast     标示是否是最后一批数据
    * @param[in] pInfo        指向返回的信息结构体。当nErrorCode不为0时，pInfo为空。
    * @attention 不要修改和删除pInfo所指示的数据；函数调用结束，参数不再有效。
    * @operationtype 异步操作
    * @ingroup G_T_Cellphone
    */
    virtual void ES_CDECL OnRspQrySystemParameter(const TAPISTR_20 UserNo, TAPIUINT32 nRequestID, TAPIINT32 nErrorCode, TAPIYNFLAG isLast, const TapAPISystemParameterInfo *pInfo) = 0;
    /**
    * @brief 交易中心前置地址信息查询(北斗星专用)
    * @param[in] UserNo 登录用户UserNo
    * @param[in] nRequestID 请求ID
    * @param[in] nErrorCode 错误码。0 表示成功。
    * @param[in] isLast     标示是否是最后一批数据
    * @param[in] pInfo        指向返回的信息结构体。当nErrorCode不为0时，pInfo为空。
    * @attention 不要修改和删除pInfo所指示的数据；函数调用结束，参数不再有效。
    * @operationtype 异步操作
    * @ingroup G_T_Cellphone
    */
    virtual void ES_CDECL OnRspQryTradeCenterFrontAddress(const TAPISTR_20 UserNo, TAPIUINT32 nRequestID, TAPIINT32 nErrorCode, TAPIYNFLAG isLast, const TapAPITradeCenterFrontAddressInfo *pInfo) = 0;
    /**
    * @brief 品种信息通知(北斗星专用)
    * @param[out] UserNo 指向该信息对应的UserNo
    * @param[out] pInfo    指向返回的信息结构体。
    * @attention  不要修改和删除pRspInfo所指示的数据；函数调用结束，参数不再有效。
    * @ingroup G_T_Commodity
    */
    virtual void ES_CDECL OnRtnCommodityInfo(const TAPISTR_20 UserNo, const TapAPICommodityInfo *pInfo) = 0;
    /**
    * @brief 币种信息通知(北斗星专用)
    * @param[out] UserNo 指向该信息对应的UserNo
    * @param[out] pInfo    指向返回的信息结构体。
    * @attention  不要修改和删除pRspInfo所指示的数据；函数调用结束，参数不再有效。
    * @ingroup G_T_TradeSystem
    */
    virtual void ES_CDECL OnRtnCurrencyInfo(const TAPISTR_20 UserNo, const TapAPICurrencyInfo *pInfo) = 0;
};

//EsTradeAPI 对外功能接口。包含了用户可以调用的功能函数。
class IEsTradeAPI
{
public:
    /**
    * @brief    设置API的回调接口对象。
    * @details    系统对API的通知将通过设置的回调对象通知给使用者。
    *            IEsTradeAPINotify是API的回调接口，用户需要继承实现此接口类对象来完成用户需要的功能。
    *           如果用户没有设置回调接口，则API不会向用户返回任何有用的信息。
    * @param[in] pApiNotify 实现了IEsTradeAPINotify接口的对象指针。
    * @operationtype 同步操作
    * @ingroup G_T_Login
    */
    virtual TAPIINT32 ES_CDECL SetAPINotify(IEsTradeAPINotify *pApiNotify) = 0;
    /**
    * @brief    设置API自身保存数据目录
    * @details    调用函数的同时会在path描述的目录下创建以年月日（格式EsTradeAPIYYYYMMDD.log)命名的文件。
    *            文件中保存的数据为API接收到的重要数据和API的使用和错误日志。
    * @param[in] pPath 目录。必须可用，目录符号Window下为”\\”或者”/”, Linux下为”/”。
    * @retval 0 设置成功；非0 错误码
    * @operationtype 同步操作
    * @ingroup G_T_LogConfig
    */
    virtual TAPIINT32 ES_CDECL SetEsTradeAPIDataPath(const TAPICHAR *pPath) = 0;
    /**
    * @brief    设置API的日志级别
    * @details    设定日志的输出级别，只有当实际日志级别与此处设定的级别相同或更高时，才会将日志写入SetEsTradeAPIDataPath()函数打开的日志文件。
    *            默认日志级别为APILOGLEVEL_ERROR。
    * @param[in] LogLevel 日志级别：
    *            APILOGLEVEL_ERROR    ：只记录Error日志(API自身认为的错误日志)
    *            APILOGLEVEL_NORMAL    ：记录Error日志和普通日志
    *            APILOGLEVEL_DEBUG    ：记录Error日志和Debug日志
    * @retval 0 设定成功；非0 错误码
    * @operationtype 同步操作
    * @ingroup G_T_LogConfig
    * @remark 本API自身一定会在EsTradeAPIYYYYMMDD.log日志文件中记录一些API认为必须要记录的日志。
    */
    virtual TAPIINT32 ES_CDECL SetEsTradeAPILogLevel(TAPILOGLEVEL LogLevel) = 0;
    /**
    * @brief        设置登录用户信息。API支持多登陆，可以多次调用该接口。
    * @param[in]    pUserInfo 登录用户信息
    * @retval        0 设置成功，非0 错误码
    * @operationtype 同步操作
    * @ingroup G_T_Login
    */
    virtual TAPIINT32 ES_CDECL SetUserInfo(const TapAPITradeUserInfo *pUserInfo) = 0;
    /**
    * @brief    启动某一个用户，开始工作。API内部将连接服务，建立链路，发起登录认证，维护链路信息。
    *            如果出现链路断开，API内部会自动重连，并且在重连成功后再次自动发起登录认证。
    *            如果出现登录失败，API内部会停止重复登录（比如密码错误），此时需要API使用者先调用StopUser，然后再次使用正确的登录信息调用StartUser
    * @details    在使用函数前用户需要完成登录用户信息的设置SetUserInfo()，并且创建EsTdAPITradeLoginAuth类型的用户信息，
    *            并且需要设置好回调接口。
    *            登录过程中建立连接的返回信息通过回调OnConnect返回给用户。
    *            连接建立后的用户验证回馈信息通过回调OnLogin()返回给用户。
    *            登录成功后API会自动进行API的初始化，API向服务器请求基础数据，查询完以后会通过回调OnAPIReady()
    *            指示用户API初始化完成，可以进行后续的操作了。
    * @param[in] UserNo 登录用户UserNo
    * @param[in] pLoginAuth 登录验证信息结构指针。包含登录需要的验证信息
    * @retval 0 登录成功，API开始准备后台数据;非0 错误码
    * @operationtype 异步操作
    * @note EsTdAPITradeLoginAuth中的NoticeIgnoreFlag用于标记是否忽略特定的通知回调。
    *       例如：不需要接收OnRtnFund和OnRtnPositionProfit,可以这么设定：
    *       NoticeIgnoreFlag = TAPI_NOTICE_IGNORE_FUND | TAPI_NOTICE_IGNORE_POSITIONPROFIT;
    * @attention Login()函数调用成功只是代表于服务器建立了链路连接，只有回调OnLogin()的返回能指示用户是否成功登录了。
    * @ingroup G_T_Login
    */
    virtual TAPIINT32 ES_CDECL StartUser(const TAPISTR_20 UserNo, const TapAPITradeLoginAuth *pLoginAuth) = 0;
    /**
    * @brief 停止某一个用户。API将用户退出并断开链接，停止续连。
    * @details 调用函数后API将登出并断开与服务器的连接。
    * @param[in] UserNo 登录用户UserNo
    * @operationtype 同步操作
    * @ingroup G_T_Disconnect
    */
    virtual TAPIINT32 ES_CDECL StopUser(const TAPISTR_20 UserNo) = 0;
    /**
    * @brief    请求发送二次认证认证码(北斗星专用)
    * @details    根据回掉函数OnRtnContactInfo中的联系方式，选择其中一个请求二次认证吗，
    *            收到正确应答后可以通过SetVertificateCode 设置二次认证授权码完成登陆过程。
    * @param[in]    UserNo 登录用户UserNo
    * @param[in] nSessionID 本次请求的会话ID。
    * @param[in]  pReqInfo 要接收二次认证的邮箱或者电话。
    * @attention 该函数调用需要在登陆应答后返回10003错误，API会回调客户二次认证的联系方式，用户选择其中一个联系方式（邮箱或者电话）请求二次认证。再通过设置二次认证授权码完成登陆。
    * @ingroup G_T_Login
    */
    virtual TAPIINT32 ES_CDECL RequestVertificateCode(const TAPISTR_20 UserNo, TAPIUINT32 nSessionID, const TapAPISecondInfo *pReqInfo) = 0;
    /**
    * @brief    设置二次认证信息。(c)
    * @details    登录完成后，如果系统配置需要进行二次认证码输入，则登录后会提示需要进行二次认证。
    *            此时调用该函数输入二次认证来完成登录。
    *            登录完成后不允许再调用此函数。其他原因引起的登录失败也不能调用此函数，否则会返回对应的错误信息。
    *            调用此接口后，会返回登录应答成功与否的标记，如果成功表示登录完成，可以等待OnAPIReady API完成回调。
    *            如果超时，回调完成后API会主动断开链接，需要再次进行登录操作。
    *            如果验证码错误，则可以再次调用此函数输入正确的验证码进行验证。
    * @param[in] UserNo 登录用户UserNo
    * @param[in] nSessionID 本次请求的会话ID。
    * @param[in] VertificateCode 二次认证码。
    * @retval 0 发送认证码成功
    * @retval 非0 错误码
    * @operationtype 异步操作
    * @ingroup G_T_Login
    */
    virtual TAPIINT32 ES_CDECL SetVertificateCode(const TAPISTR_20 UserNo, TAPIUINT32 nSessionID, TAPISTR_10 VertificateCode) = 0;
    /**
    * @brief 中继用户提交用户登录信息。(启明星专用)
    * @details 登录成功后只有中继用户才能使用该函数。
    * @param[in] UserNo 登录用户UserNo
    * @param[in] nRequestID 此次提交用户登录信息的请求ID 
    * @param[in] pUserLoginInfo 用户登录信息
    * @retval 0 成功；非0 错误码
    * @operationtype 异步操作
    * @ingroup G_T_UserInfo
    */
    virtual TAPIINT32 ES_CDECL SubmitUserLoginInfo(const TAPISTR_20 UserNo, TAPIUINT32 nRequestID, const TapAPISubmitUserLoginInfo* pUserLoginInfo) = 0;
    /**
    * @brief 修改密码。(启明星、北斗星)
    * @details 成功后用户密码将被设置成newPassword。
    * @param[in] UserNo 登录用户UserNo
    * @param[in] nRequestID 此次修改密码的请求ID
    * @param[in] pReqInfo 请求修改密码的结构体指针
    * @retval 0 成功；非0 错误码
    * @operationtype 异步操作
    * @ingroup G_T_UserInfo
    */
    virtual TAPIINT32 ES_CDECL ChangePassword(const TAPISTR_20 UserNo, TAPIUINT32 nRequestID, const TapAPIChangePasswordReq *pReqInfo) = 0;
    /**
    * @brief 获取登录用户是否具有某权限。(启明星、北斗星)
    * @details 用户的权限在用户登录时已经传递给API，所以此函数执行的是本地的查询。
    * @param[in] UserNo 登录用户UserNo
    * @param[in] nRightID 权限ID
    * @retval 0 不具有权限， 非0 具有权限
    * @operationtype 同步操作
    * @ingroup G_T_UserRight
    */
    virtual TAPIINT32 ES_CDECL HaveCertainRight(const TAPISTR_20 UserNo, TAPIRightIDType nRightID) = 0;
    /**
    * @brief 设置用户预留信息。
    * @details 用户可以设置一个长度为50以内的字符信息，下次登录后可以得到这个信息。这个功能主要是用来让用户确认是自己的账号，主要是用来进行防伪。
    * @param[in] UserNo 登录用户UserNo
    * @param[in] nRequestID 请求ID
    * @param[in] info 预留信息字符串指针
    * @retval 0 请求成功；非0 错误码
    * @operationtype 异步操作
    * @note 该接口暂未实现
    * @ingroup G_T_UserInfo
    */
    virtual TAPIINT32 ES_CDECL SetReservedInfo(const TAPISTR_20 UserNo, TAPIUINT32 nRequestID, const TAPISTR_50 info) = 0;
    /**
    * @brief 获取用户下属的所有资金账号。从SeqID开始查询，每次最多返回nOutLen条。如果没有结束，需要下次继续从查询到的最后一个数据的SeqID+1继续查询。(启明星、北斗星)
    * @details 此函数执行的是本地的查询,运行中不会删除已经从后台获取到的资金账号信息。
    * @param[in] UserNo 登录用户UserNo
    * @param[in] nDataSeqID 起始查询数据编号（1表示第一个数据，本次查询包含这个编号的数据）
    * @param[in] pOutInfo 本次查询应答信息指针数组的起始地址
    * @param[in] nOutLen 本次查询应答信息指针数组的长度
    * @param[out] isLast 标示满足本次查询的应答信息是否填充完毕
    * @retval retval>=0 本次查询到的符合条件的应答信息的总个数，retval可以作为续查时的一个依据; retval<0 本次查询失败，表示错误码
    * @operationtype 同步操作
    * @ingroup G_T_AccountInfo
    */
    virtual TAPIINT32 ES_CDECL GetAccount(const TAPISTR_20 UserNo, TAPIUINT32 nDataSeqID, TapAPIAccountInfo* pOutInfo[], TAPIUINT32 nOutLen, TAPIYNFLAG& isLast) = 0;
    /**
    * @brief 获取指定用户下的所有交易所信息。从SeqID开始，每次最多返回nOutLen条。如果没有结束，需要下次继续从查询到的最后一个数据的SeqID+1继续查询。(启明星、北斗星)
    * @details 此函数执行的是本地的查询,运行中不会删除已经从后台获取到的交易所信息。
    * @param[in] UserNo 登录用户UserNo
    * @param[in] nDataSeqID 起始查询数据编号（1表示第一个数据，本次查询包含这个编号的数据）
    * @param[in] pOutInfo 本次查询应答信息指针数组的起始地址
    * @param[in] nOutLen 本次查询应答信息指针数组的长度
    * @param[out] isLast 标示满足本次查询的应答信息是否填充完毕
    * @retval retval>=0 本次查询到的符合条件的应答信息的总个数，retval可以作为续查时的一个依据; retval<0 本次查询失败，表示错误码
    * @operationtype 同步操作
    * @ingroup G_T_TradeSystem
    */
    virtual TAPIINT32 ES_CDECL GetExchange(const TAPISTR_20 UserNo, TAPIUINT32 nDataSeqID, TapAPIExchangeInfo* pOutInfo[], TAPIUINT32 nOutLen, TAPIYNFLAG& isLast) = 0;
    /**
    * @brief 获取指定用户下的所有品种信息。从SeqID开始，每次最多返回nOutLen条。如果没有结束，需要下次继续从查询到的最后一个数据的SeqID+1继续查询。(启明星、北斗星)
    * @details 此函数执行的是本地的查询,运行中不会删除已经从后台获取到的品种信息。
    * @param[in] UserNo 登录用户UserNo
    * @param[in] nDataSeqID 起始查询数据编号（1表示第一个数据，本次查询包含这个编号的数据）
    * @param[in] pOutInfo 本次查询应答信息指针数组的起始地址
    * @param[in] nOutLen 本次查询应答信息指针数组的长度
    * @param[out] isLast 标示满足本次查询的应答信息是否填充完毕
    * @retval retval>=0 本次查询到的符合条件的应答信息的总个数，retval可以作为续查时的一个依据; retval<0 本次查询失败，表示错误码
    * @operationtype 同步操作
    * @ingroup G_T_Commodity
    */
    virtual TAPIINT32 ES_CDECL GetCommodity(const TAPISTR_20 UserNo, TAPIUINT32 nDataSeqID, TapAPICommodityInfo* pOutInfo[], TAPIUINT32 nOutLen, TAPIYNFLAG& isLast) = 0;
    /**
    * @brief 获取指定用户下的指定品种的合约信息。从SeqID开始查询，每次最多返回nOutLen条。如果没有结束，需要下次继续从查询到的最后一个数据的SeqID+1继续查询。(启明星、北斗星)
    * @details 此函数执行的是本地的查询,运行中不会删除已经从后台获取到的合约信息。
    * @param[in] UserNo 登录用户UserNo
    * @param[in] pReqInfo 查询用户下指定品种的合约信息请求的结构体指针;
    *                    该参数各字段为可选字段，可以用以下方法查询：
    *                    1.交易所为空：查所有合约
    *                    2.交易所编码有效、品种编码为空：查该交易所下所有的合约
    *                    3.交易所编码有效、品种编码有效：查该交易所下指定品种的所有合约
    *                    4.交易所编码有效、品种编码有效、品种类型有效：查该品种下指定品种类型的所有合约
    * @param[in] nDataSeqID 起始查询数据编号（1表示第一个数据，本次查询包含这个编号的数据）
    * @param[in] pOutInfo 本次查询应答信息指针数组的起始地址
    * @param[in] nOutLen 本次查询应答信息指针数组的长度
    * @param[out] isLast 标示满足本次查询的应答信息是否填充完毕
    * @retval retval>=0 本次查询到的符合条件的应答信息的总个数，retval可以作为续查时的一个依据; retval<0 本次查询失败，表示错误码
    * @operationtype 同步操作
    * @ingroup G_T_Contract
    */
    virtual TAPIINT32 ES_CDECL GetContract(const TAPISTR_20 UserNo, const TapAPICommodity *pReqInfo, TAPIUINT32 nDataSeqID, TapAPITradeContractInfo* pOutInfo[], TAPIUINT32 nOutLen,  TAPIYNFLAG& isLast) = 0;
    /**
    * @brief 下单
    * @details 用户下单的操作函数。用户的下单操作会造成用户的资金、持仓、平仓、资金、风控标记等多种数据的变化，所以用户下的单成交后，会有多个回调通知来向用户展示数据的变化。
    * @param[in] UserNo 登录用户UserNo
    * @param[in] nRequestID 请求ID
    * @param[in] pOrder 新的委托
    * @retval 0 请求成功;非0 错误码
    * @operationtype 异步操作
    * @ingroup G_T_TradeActions
    */
    virtual TAPIINT32 ES_CDECL InsertOrder(const TAPISTR_20 UserNo, TAPIUINT32 nRequestID, const TapAPINewOrder *pOrder) = 0;
    /**
    * @brief 撤单
    * @details 用户委托没有完全成交之前撤销剩余的委托。
    * @param[in] UserNo 登录用户UserNo
    * @param[in] nRequestID 请求ID
    * @param[in] pOrder 撤销的委托
    * @retval 0 请求成功;非0 错误码
    * @operationtype 异步操作
    * @ingroup G_T_TradeActions
    */
    virtual TAPIINT32 ES_CDECL CancelOrder(const TAPISTR_20 UserNo, TAPIUINT32 nRequestID, const TapAPIOrderCancelReq *pOrder) = 0;
    /**
    * @brief 订单修改指令(北斗星专用)
    * @param[in] UserNo 登录用户UserNo
    * @param[in] nRequestID 请求ID
    * @param[in] pOrder 订单修改请求结构
    * @retval 0 请求成功;非0 错误码
    * @operationtype 异步操作
    * @ingroup G_T_TradeActions
    */
    virtual TAPIINT32 ES_CDECL ModifyOrder(const TAPISTR_20 UserNo, TAPIUINT32 nRequestID, const TapAPIOrderModifyReq *pOrder) = 0;
    /**
    * @brief 激活报单(启明星、北斗星)
    * @details 激活挂起的报单。委托将可以重新开始触发成交。
    * @param[in] UserNo 登录用户UserNo
    * @param[in] nRequestID 请求ID
    * @param[in] pOrder 激活的委托
    * @retval 0 请求成功;非0 错误码
    * @operationtype 异步操作
    * @ingroup G_T_TradeActions
    */
    virtual TAPIINT32 ES_CDECL ActivateOrder(const TAPISTR_20 UserNo, TAPIUINT32 nRequestID, const TapAPIOrderActivateReq *pOrder) = 0;
    /**
    * @brief 获取指定用户下指定资金账户的当前最新资金信息
    * @details TapAPIFundReq需要填写QryAccount()获取的资金账号。TapAPIFundReq还需要填写查询数据的起始流号。
    * @details 此函数查询的是本地的查询,运行中不会删除已经从后台获取到的资金账号下的资金数据。 
    * @param[in] UserNo 登录用户UserNo
    * @param[in] pReqInfo 查询客户资金请求的结构体指针
    * @param[in] pOutInfo 本次查询应答信息指针数组的起始地址
    * @param[in] nOutLen 本次查询应答信息指针数组的长度
    * @param[out] isLast 标示满足本次查询的应答信息是否填充完毕
    * @retval retval>=0 本次查询到的符合条件的应答信息的总个数，retval可以作为续查时的一个依据; retval<0 本次查询失败，表示错误码
    * @operationtype 同步操作
    * @ingroup G_T_FundInfo
    */
    virtual TAPIINT32 ES_CDECL GetFund(const TAPISTR_20 UserNo, const TapAPIFundReq *pReqInfo, TapAPIFundData* pOutInfo[], TAPIUINT32 nOutLen, TAPIYNFLAG& isLast) = 0;
    /**
    * @brief 获取指定用户下指定条件的当前最新委托信息。可以查询所有委托，也可以查询所有未结束的委托。
    * @details 此函数查询的是本地的查询,用户和后台断开重连后会清空本地数据。
    * @param[in] UserNo 登录用户UserNo
    * @param[in] pReqInfo 查询客户委托请求的结构体指针
    * @param[in] pOutInfo 本次查询应答信息指针数组的起始地址
    * @param[in] nOutLen 本次查询应答信息指针数组的长度
    * @param[out] isLast 标示满足本次查询的应答信息是否填充完毕
    * @retval retval>=0 本次查询到的符合条件的应答信息的总个数，retval可以作为续查时的一个依据; retval<0 本次查询失败，表示错误码
    * @operationtype 同步操作
    * @ingroup G_T_TradeInfo
    */
    virtual TAPIINT32 ES_CDECL GetOrder(const TAPISTR_20 UserNo, const TapAPIOrderQryReq *pReqInfo, TapAPIOrderInfo pOutInfo[], TAPIUINT32 nOutLen, TAPIYNFLAG& isLast) = 0;
    /**
    * @brief 查询委托变化流程(启明星、北斗星)
    * @details 查询用户的委托的变化流程，查询将返回委托的每一次的变化。
    * @param[in] UserNo 登录用户UserNo
    * @param[in] nRequestID 请求ID
    * @param[in] pReqInfo 委托流程查询信息结构体指针。
    * @retval 0 请求成功；非0 错误码
    * @operationtype 异步操作
    * @ingroup G_T_TradeInfo
    */
    virtual TAPIINT32 ES_CDECL QryOrderProcess(const TAPISTR_20 UserNo, TAPIUINT32 nRequestID, const TapAPIOrderProcessQryReq *pReqInfo) = 0;
    /**
    * @brief 获取指定用户下指定条件的成交信息
    * @details 此函数查询的是本地的查询,用户和后台断开重连后会清空本地数据。
    * @param[in] UserNo 登录用户UserNo
    * @param[in] pReqInfo 查询客户委托请求的结构体指针
    * @param[in] pOutInfo 本次查询应答信息指针数组的起始地址
    * @param[in] nOutLen 本次查询应答信息指针数组的长度
    * @param[out] isLast 标示满足本次查询的应答信息是否填充完毕
    * @retval retval>=0 本次查询到的符合条件的应答信息的总个数，retval可以作为续查时的一个依据; retval<0 本次查询失败，表示错误码
    * @operationtype 同步操作
    * @ingroup G_T_TradeInfo
    */
    virtual TAPIINT32 ES_CDECL GetFill(const TAPISTR_20 UserNo, const TapAPIFillQryReq *pReqInfo, TapAPIFillInfo pOutInfo[], TAPIUINT32 nOutLen, TAPIYNFLAG& isLast) = 0;
    /**
    * @brief 获取指定用户下指定条件的持仓信息
    * @details 此函数查询的是本地的查询,用户和后台断开重连后会清空本地数据。
    * @param[in] UserNo 登录用户UserNo
    * @param[in] pReqInfo 查询客户委托请求的结构体指针
    * @param[in] pOutInfo 本次查询应答信息指针数组的起始地址
    * @param[in] nOutLen 本次查询应答信息指针数组的长度
    * @param[out] isLast 标示满足本次查询的应答信息是否填充完毕
    * @retval retval>=0 本次查询到的符合条件的应答信息的总个数，retval可以作为续查时的一个依据; retval<0 本次查询失败，表示错误码
    * @operationtype 同步操作
    * @ingroup G_T_TradeInfo
    */
    virtual TAPIINT32 ES_CDECL GetPosition(const TAPISTR_20 UserNo, const TapAPIPositionQryReq *pReqInfo, TapAPIPositionInfo pOutInfo[], TAPIUINT32 nOutLen, TAPIYNFLAG& isLast) = 0;
    /**
    * @brief 获取指定用户下指定条件的平仓记录(启明星专用)
    * @details 此函数查询的是本地的查询,用户和后台断开重连后会清空本地数据。
    * @param[in] UserNo 登录用户UserNo
    * @param[in] pReqInfo 查询客户委托请求的结构体指针
    * @param[in] pOutInfo 本次查询应答信息指针数组的起始地址
    * @param[in] nOutLen 本次查询应答信息指针数组的长度
    * @param[out] isLast 标示满足本次查询的应答信息是否填充完毕
    * @retval retval>=0 本次查询到的符合条件的应答信息的总个数，retval可以作为续查时的一个依据; retval<0 本次查询失败，表示错误码
    * @operationtype 同步操作
    * @ingroup G_T_TradeInfo
    */
    virtual TAPIINT32 ES_CDECL GetClose(const TAPISTR_20 UserNo, const TapAPICloseQryReq *pReqInfo, TapAPICloseInfo pOutInfo[], TAPIUINT32 nOutLen, TAPIYNFLAG& isLast) = 0;
    /**
    * @brief 查询深度行情(启明星专用)
    * @param[in] UserNo 登录用户UserNo
    * @param[in] nRequestID 请求ID
    * @param[in] pReqInfo 查询深度行情的请求结构体指针，第二个合约留空。
    * @retval 0 请求成功；非0 错误码
    * @operationtype 异步操作
    * @ingroup G_T_DeepQuote
    */
    virtual TAPIINT32 ES_CDECL QryDeepQuote(const TAPISTR_20 UserNo, TAPIUINT32 nRequestID, const TapAPIContract *pReqInfo) = 0;
    /**
    * @brief 获取指定用户下的交易所时间状态信息(启明星)。从SeqID开始，每次最多返回nOutLen条。如果没有结束，需要下次继续从查询到的最后一个数据的SeqID+1继续查询。
    * @details 此函数执行的是本地的查询,运行中不会删除已经从后台获取到的交易所信息。
    * @param[in] UserNo 登录用户UserNo
    * @param[in] nDataSeqID 起始查询数据编号（1表示第一个数据，本次查询包含这个编号的数据）
    * @param[in] pOutInfo 本次查询应答信息指针数组的起始地址
    * @param[in] nOutLen 本次查询应答信息指针数组的长度
    * @param[out] isLast 标示满足本次查询的应答信息是否填充完毕
    * @retval retval>=0 本次查询到的符合条件的应答信息的总个数，retval可以作为续查时的一个依据; retval<0 本次查询失败，表示错误码
    * @operationtype 同步操作
    * @ingroup G_T_TradeSystem
    */
    virtual TAPIINT32 ES_CDECL GetExchangeStateInfo(const TAPISTR_20 UserNo, TAPIUINT32 nDataSeqID, TapAPIExchangeStateInfo* pOutInfo[], TAPIUINT32 nOutLen, TAPIYNFLAG& isLast) = 0;
    /**
    * @brief 获取指定用户下的上手信息,主要是用于客户下单时指定通道号，方便主动选择单子进入交易所前置机(启明星专用)
    * @details 此函数执行的是本地的查询,运行中不会删除已经从后台获取到的上手通道信息。
    * @param[in] UserNo 登录用户UserNo
    * @param[in] nDataSeqID 起始查询数据编号（1表示第一个数据，本次查询包含这个编号的数据）
    * @param[in] pOutInfo 本次查询应答信息指针数组的起始地址
    * @param[in] nOutLen 本次查询应答信息指针数组的长度
    * @param[out] isLast 标示满足本次查询的应答信息是否填充完毕
    * @retval retval>=0 本次查询到的符合条件的应答信息的总个数，retval可以作为续查时的一个依据; retval<0 本次查询失败，表示错误码
    * @operationtype 同步操作
    * @ingroup G_T_UpperChannelInfo
    */
    virtual TAPIINT32 ES_CDECL GetUpperChannel(const TAPISTR_20 UserNo, TAPIUINT32 nDataSeqID, TapAPIUpperChannelInfo* pOutInfo[], TAPIUINT32 nOutLen, TAPIYNFLAG& isLast) = 0;
    /**
    * @brief 获取指定用户下所有的币种的信息。从SeqID开始查询，每次最多返回100条，如果没有结束，需要下次继续从查询到的最后一个数据的SeqID继续查询（北斗星专用）
    * @details 此函数执行的是本地的查询,运行中不会删除已经从后台获取到的币种信息数据。
    * @param[in] UserNo 登录用户UserNo
    * @param[in] nDataSeqID 起始查询数据编号（1表示第一个数据，本次查询包含这个编号的数据）
    * @param[in] pOutInfo 本次查询应答信息指针数组的起始地址
    * @param[in] nOutLen 本次查询应答信息指针数组的长度
    * @param[out] isLast 标示满足本次查询的应答信息是否填充完毕
    * @retval retval>=0 本次查询到的符合条件的应答信息的总个数，retval可以作为续查时的一个依据; retval<0 本次查询失败，表示错误码
    * @operationtype 同步操作
    * @ingroup G_T_TradeSystem
    */
    virtual TAPIINT32 ES_CDECL GetCurrency(const TAPISTR_20 UserNo, TAPIUINT32 nDataSeqID, TapAPICurrencyInfo* pOutInfo[], TAPIUINT32 nOutLen, TAPIYNFLAG& isLast) = 0;
    /**
    * @brief 查询客户最终费率（启明星专用）
    * @param[in] UserNo 登录用户UserNo
    * @param[in] nRequestID 请求ID
    * @param[in] pReqInfo 客户最终费率查询请求结构体指针
    * @retval 0 请求成功；非0 错误码
    * @operationtype 异步操作
    * @ingroup G_T_AccountRentInfo
    */
    virtual TAPIINT32 ES_CDECL QryAccountRent(const TAPISTR_20 UserNo, TAPIUINT32 nRequestID, const TapAPIAccountRentQryReq *pReqInfo) = 0;
    /**
    * @brief 查询客户手续费参数（北斗星专用）
    * @param[in] UserNo 登录用户UserNo
    * @param[in] nRequestID 请求ID
    * @param[in] pReqInfo 客户最终费率查询请求结构体指针
    * @retval 0 请求成功；非0 错误码
    * @operationtype 异步操作
    * @ingroup G_T_AccountRentInfo
    */
    virtual TAPIINT32 ES_CDECL QryAccountFeeRent(const TAPISTR_20 UserNo, TAPIUINT32 nRequestID, const TapAPIAccountFeeRentQryReq *pReqInfo) = 0;
    /**
    * @brief 查询客户保证金参数（北斗星专用）
    * @param[in] UserNo 登录用户UserNo
    * @param[in] nRequestID 请求ID
    * @param[in] pReqInfo 客户最终费率查询请求结构体指针
    * @retval 0 请求成功；非0 错误码
    * @operationtype 异步操作
    * @ingroup G_T_AccountRentInfo
    */
    virtual TAPIINT32 ES_CDECL QryAccountMarginRent(const TAPISTR_20 UserNo, TAPIUINT32 nRequestID, const TapAPIAccountMarginRentQryReq *pReqInfo) = 0;
    /**
    * @brief 客户资金调整查询请求(北斗星专用)
    * @param[in] UserNo 登录用户UserNo
    * @param[in] nRequestID 请求ID
    * @param[in] pReqInfo 客户资金调整查询请求结构体指针
    * @retval 0 请求成功;非0 错误码
    * @operationtype 异步操作
    * @ingroup G_T_FundInfo
    */
    virtual TAPIINT32 ES_CDECL QryAccountCashAdjust(const TAPISTR_20 UserNo, TAPIUINT32 nRequestID, const TapAPIAccountCashAdjustQryReq *pReqInfo) = 0;
    /**
    * @brief 查询用户账单(北斗星专用)
    * @param[in] UserNo 登录用户UserNo
    * @param[in] nRequestID 请求ID
    * @param[in] pReqInfo 客户用户账单查询请求结构体指针
    * @retval 0 请求成功;非0 错误码
    * @operationtype 异步操作
    * @ingroup G_T_Bill
    */
    virtual TAPIINT32 ES_CDECL QryBill(const TAPISTR_20 UserNo, TAPIUINT32 nRequestID, const TapAPIBillQryReq *pReqInfo) = 0;
    /**
    * @brief 历史委托查询请求(北斗星专用)
    * @param[in] UserNo 登录用户UserNo
    * @param[in] nRequestID 请求ID
    * @param[in] pReqInfo 客户历史委托查询请求结构体指针
    * @retval 0 请求成功;非0 错误码
    * @operationtype 异步操作
    * @ingroup G_T_HisInfo
    */
    virtual TAPIINT32 ES_CDECL QryHisOrder(const TAPISTR_20 UserNo, TAPIUINT32 nRequestID, const TapAPIHisOrderQryReq *pReqInfo) = 0;
    /**
    * @brief 历史委托流程查询请求(北斗星专用)
    * @param[in] UserNo 登录用户UserNo
    * @param[in] nRequestID 请求ID
    * @param[in] pReqInfo 客户历史委托流程查询请求结构体指针
    * @retval 0 请求成功;非0 错误码
    * @operationtype 异步操作
    * @ingroup G_T_HisInfo
    */
    virtual TAPIINT32 ES_CDECL QryHisOrderProcess(const TAPISTR_20 UserNo, TAPIUINT32 nRequestID, const TapAPIHisOrderProcessQryReq *pReqInfo) = 0;
    /**
    * @brief 历史成交查询请求(北斗星专用)
    * @param[in] UserNo 登录用户UserNo
    * @param[in] nRequestID 请求ID
    * @param[in] pReqInfo 客户历史成交查询请求结构体指针
    * @retval 0 请求成功;非0 错误码
    * @operationtype 异步操作
    * @ingroup G_T_HisInfo
    */
    virtual TAPIINT32 ES_CDECL QryHisFill(const TAPISTR_20 UserNo, TAPIUINT32 nRequestID, const TapAPIHisFillQryReq *pReqInfo) = 0;
    /**
    * @brief 历史持仓查询请求(北斗星专用)
    * @param[in] UserNo 登录用户UserNo
    * @param[in] nRequestID 请求ID
    * @param[in] pReqInfo 客户历史持仓查询请求结构体指针
    * @retval 0 请求成功;非0 错误码
    * @operationtype 异步操作
    * @ingroup G_T_HisInfo
    */
    virtual TAPIINT32 ES_CDECL QryHisPosition(const TAPISTR_20 UserNo, TAPIUINT32 nRequestID, const TapAPIHisPositionQryReq *pReqInfo) = 0;
    /**
    * @brief 历史交割查询请求(北斗星专用)
    * @param[in] UserNo 登录用户UserNo
    * @param[in] nRequestID 请求ID
    * @param[in] pReqInfo 客户历史交割查询请求结构体指针
    * @retval 0 请求成功;非0 错误码
    * @operationtype 异步操作
    * @ingroup G_T_HisInfo
    */
    virtual TAPIINT32 ES_CDECL QryHisDelivery(const TAPISTR_20 UserNo, TAPIUINT32 nRequestID, const TapAPIHisDeliveryQryReq *pReqInfo) = 0;
    /**
    * @brief 登录用户手机设备增加(北斗星专用)
    * @param[in]    UserNo 登录用户UserNo
    * @param[in]    nRequestID 请求ID
    * @param[in]    pReqInfo 登录用户手机设备增加请求结构
    * @retval        0 请求成功;非0 错误码
    * @operationtype 异步操作
    * @ingroup G_T_Cellphone
    */
    virtual TAPIINT32 ES_CDECL AddMobileDevice(const TAPISTR_20 UserNo, TAPIUINT32 nRequestID, const TapAPIMobileDeviceAddReq *pReqInfo) = 0;
    /**
    * @brief 管理日志查询(北斗星专用)
    * @param[in]    UserNo 登录用户UserNo
    * @param[in]    nRequestID 请求ID
    * @param[in]    pReqInfo 管理日志查询请求结构
    * @retval        0 请求成功;非0 错误码
    * @operationtype 异步操作
    * @ingroup G_T_Cellphone
    */
    virtual TAPIINT32 ES_CDECL QryManageInfoForEStar(const TAPISTR_20 UserNo, TAPIUINT32 nRequestID, const TapAPIManageInfoQryReq *pReqInfo) = 0;
    /**
    * @brief 系统参数查询(北斗星专用)
    * @param[in]    UserNo 登录用户UserNo
    * @param[in]    nRequestID 请求ID
    * @param[in]    pReqInfo 系统参数查询请求结构
    * @retval        0 请求成功;非0 错误码
    * @operationtype 异步操作
    * @ingroup G_T_Cellphone
    */
    virtual TAPIINT32 ES_CDECL QrySystemParameter(const TAPISTR_20 UserNo, TAPIUINT32 nRequestID, const TapAPISystemParameterQryReq *pReqInfo) = 0;
    /**
    * @brief 交易中心前置地址信息查询(北斗星专用)
    * @param[in]    UserNo 登录用户UserNo
    * @param[in]    nRequestID 请求ID
    * @param[in]    pReqInfo 交易中心前置地址信息查询请求结构
    * @retval        0 请求成功;非0 错误码
    * @operationtype 异步操作
    * @ingroup G_T_Cellphone
    */
    virtual TAPIINT32 ES_CDECL QryTradeCenterFrontAddress(const TAPISTR_20 UserNo, TAPIUINT32 nRequestID, const TapAPITradeCenterFrontAddressQryReq *pReqInfo) = 0;
    /**
    * @brief 交易消息查询(北斗星专用)
    * @param[in]    UserNo 登录用户UserNo
    * @param[in]    nRequestID 请求ID
    * @param[in]    pReqInfo 交易消息查询请求结构
    * @retval        0 请求成功;非0 错误码
    * @operationtype 异步操作
    * @ingroup G_T_TradeSystem
    */
    virtual TAPIINT32 ES_CDECL QryTradeMessage(const TAPISTR_20 UserNo, TAPIUINT32 nRequestID, const TapAPITradeMessageQryReq *pReqInfo) = 0;
};

}

//-----------------------------EsTradeAPI导出函数------------------------------------
#ifdef __cplusplus
extern "C" {
#endif // __cplusplus
/**
* @brief    创建EsTradeAPI的接口对象。
* @details    创建整个交易API的接口
* @param[in] nResult 创建接口的错误码。
* @retval NULL 创建失败，具体原因可通过输出参数nResult判断。
* @retval !NULL    实现了IEsTradeAPI接口的对象指针。
* @ingroup G_T_API
*/
ES_DLLEXPORT EsTradeAPI::IEsTradeAPI *ES_CDECL CreateEsTradeAPI(EsTradeAPI::TAPIINT32& nResult);
/**
* @brief    销毁通过CreateEsTradeAPI函数创建的IEsTradeAPI对象。
* @param[in] pApiObj IEsTradeAPI对象指针。
* @ingroup G_T_API
*/
ES_DLLEXPORT void ES_CDECL FreeEsTradeAPI(EsTradeAPI::IEsTradeAPI *pApiObj);
/**
* @brief    获取EsTradeAPI的版本信息
* @param[out] pVersion 外部声明字符数组，保存API版本号。
* @param[in] nVersionLen 字符数组长度，不少于50个字符。
* @ingroup G_T_API
*/
ES_DLLEXPORT void ES_CDECL GetEsTradeAPIVersion(char* pVersion, int nVersionLen);
#ifdef __cplusplus
}
#endif // __cplusplus

#endif // ES_TRADE_API_H