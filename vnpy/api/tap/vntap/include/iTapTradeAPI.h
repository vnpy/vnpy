#ifndef ITAP_TRADE_API_H
#define ITAP_TRADE_API_H

#include "iTapTradeAPIDataType.h"
//#include "TapProtocol.h"

#if defined WIN32 || defined WIN64
#define TAP_CDECL __cdecl
#define TAP_DLLEXPORT __declspec(dllexport)
#else
#define TAP_CDECL
#define TAP_DLLEXPORT
#endif
//TapTradeAPI.h
//文件定义了TapTradeAPI提供给开发者的对外接口、函数和回调接口。

//TapTradeAPI 的回调通知接口。
namespace ITapTrade
{
    class ITapTradeAPINotify
    {
    public:
        /**
        * @brief 连接成功回调通知
        * @ingroup G_T_Login
        */
        virtual void TAP_CDECL OnConnect() = 0;
        /**
        * @brief    系统登录过程回调。
        * @details    此函数为Login()登录函数的回调，调用Login()成功后建立了链路连接，然后API将向服务器发送登录认证信息，
        *            登录期间的数据发送情况和登录的回馈信息传递到此回调函数中。
        * @param[in] errorCode 返回错误码,0表示成功。
        * @param[in] loginRspInfo 登陆应答信息，如果errorCode!=0，则loginRspInfo=NULL。
        * @attention    该回调返回成功，说明用户登录成功。但是不代表API准备完毕。
        * @ingroup G_T_Login
        */
        virtual void TAP_CDECL OnRspLogin(ITapTrade::TAPIINT32 errorCode, const ITapTrade::TapAPITradeLoginRspInfo *loginRspInfo) = 0;
        /**
        * @brief    二次认证联系方式通知。
        * @details    登录完成后，如果需要二次认证（9.2.7后台），会收到联系方式的通知，可以选择通知消息的一个联系方式（邮箱或者电话）
        *            请求发送二次认证授权码（RequestVertificateCode）。
        * @param[in] errorCode 返回错误码,0表示成功。如果账户没有绑定二次认证联系方式，则返回10016错误。
        * @param[in] isLast,标识是否是最后一条联系信息。
        * @param[in]  认证方式信息，如果errorCode!=0，则ContactInfo为空。
        * @attention    该回调返回成功，说明需要二次认证，并且需要选择一个联系方式然后调用RequestVertificateCode。
        * @ingroup G_T_Login
        */
        virtual void TAP_CDECL OnRtnContactInfo(ITapTrade::TAPIINT32 errorCode, ITapTrade::TAPIYNFLAG isLast, const ITapTrade::TAPISTR_40 ContactInfo) = 0;

        /**
        * @brief    请求发送二次认证码应答。
        * @details    请求获取二次认证授权码，后台发送邮件或者短信，并给出应答，包含发送序号以及认证码有效期。
        *            
        * @param[in] sessionID 请求二次认证码会话ID。
        * @param[in]  errorCode 如果没有绑定联系，返回10016错误.
        * @param[in]  rsp二次认证码有效期，以秒返回，在二次认证有效期内，可以重复设置二次认证码，但是不能再重新申请二次认证码。
        * @attention    该回调返回成功，说明需要二次认证，并且需要选择一个联系方式然后调用RequestVertificateCode。
        * @ingroup G_T_Login
        */
        virtual void TAP_CDECL OnRspRequestVertificateCode(ITapTrade::TAPIUINT32 sessionID,ITapTrade::TAPIINT32 errorCode, const TapAPIRequestVertificateCodeRsp *rsp) = 0;

        /**
        * @brief    API到期提醒回调
        * @details    此函数为Login()登录成功后，如果到期日与当前日期小于30天，则进行回调提醒。
        * @param[in] date 返回API授权到期日。
        * @param[in] days 返回还有几天授权到期。
        * @attention    该函数回调，则说明授权在一个月之内到期。否则不产生该回调。
        * @ingroup G_T_Login
        */
        virtual void TAP_CDECL OnExpriationDate(ITapTrade::TAPIDATE date, int days) = 0;

        /**
        * @brief    通知用户API准备就绪。
        * @details    只有用户回调收到此就绪通知时才能进行后续的各种行情数据查询操作。\n
        *            此回调函数是API能否正常工作的标志。
        * @attention 就绪后才可以进行后续正常操作
        * @ingroup G_T_Login
        */
        virtual void TAP_CDECL OnAPIReady(ITapTrade::TAPIINT32 errorCode) = 0;
        /**
        * @brief    API和服务失去连接的回调
        * @details    在API使用过程中主动或者被动与服务器服务失去连接后都会触发此回调通知用户与服务器的连接已经断开。
        * @param[in] reasonCode 断开原因代码。
        * @ingroup G_T_Disconnect
        */
        virtual void TAP_CDECL OnDisconnect(ITapTrade::TAPIINT32 reasonCode) = 0;
        /**
        * @brief 通知用户密码修改结果
        * @param[in] sessionID 修改密码的会话ID,和ChangePassword返回的会话ID对应。
        * @param[in] errorCode 返回错误码，0表示成功。
        * @ingroup G_T_UserInfo
        */
        virtual void TAP_CDECL OnRspChangePassword(ITapTrade::TAPIUINT32 sessionID, ITapTrade::TAPIINT32 errorCode) = 0;

        /**
        * @brief 认证账户密码反馈
        * @param[in] sessionID 修改密码的会话ID,和AuthPassword返回的会话ID对应。
        * @param[in] errorCode 返回错误码，0表示成功。
        * @ingroup G_T_UserInfo
        */
        virtual void TAP_CDECL OnRspAuthPassword(ITapTrade::TAPIUINT32 sessionID, ITapTrade::TAPIINT32 errorCode) = 0;

        /**
        * @brief    返回系统交易日期和当天LME到期日
        * @param[in] sessionID 请求的会话ID；
        * @param[in] errorCode 错误码。0 表示成功。
        * @param[in] info 指向返回的信息结构体。当errorCode不为0时，info为空。
        * @attention 不要修改和删除info所指示的数据；函数调用结束，参数不再有效。
        * @ingroup G_T_UserRight
        */

        virtual void TAP_CDECL OnRspQryTradingDate(ITapTrade::TAPIUINT32 sessionID, ITapTrade::TAPIINT32 errorCode, const ITapTrade::TapAPITradingCalendarQryRsp *info) = 0;
        /**
        * @brief 设置用户预留信息反馈
        * @param[in] sessionID 设置用户预留信息的会话ID
        * @param[in] errorCode 返回错误码，0表示成功。
        * @param[in] info 指向返回的信息结构体。当errorCode不为0时，info为空。
        * @attention 不要修改和删除info所指示的数据；函数调用结束，参数不再有效。
        * @note 该接口暂未实现
        * @ingroup G_T_UserInfo
        */
        virtual void TAP_CDECL OnRspSetReservedInfo(ITapTrade::TAPIUINT32 sessionID, ITapTrade::TAPIINT32 errorCode, const ITapTrade::TAPISTR_50 info) = 0;


        /**
        * @brief    返回用户信息
        * @details    此回调接口向用户返回查询的资金账号的详细信息。用户有必要将得到的账号编号保存起来，然后在后续的函数调用中使用。
        * @param[in] sessionID 请求的会话ID；
        * @param[in] errorCode 错误码。0 表示成功。
        * @param[in] isLast 标示是否是最后一批数据；
        * @param[in] info 指向返回的信息结构体。当errorCode不为0时，info为空。
        * @attention 不要修改和删除info所指示的数据；函数调用结束，参数不再有效。
        * @ingroup G_T_AccountInfo
        */
        virtual void TAP_CDECL OnRspQryAccount(ITapTrade::TAPIUINT32 sessionID, ITapTrade::TAPIUINT32 errorCode, ITapTrade::TAPIYNFLAG isLast, const ITapTrade::TapAPIAccountInfo *info) = 0;
        /**
        * @brief 返回资金账户的资金信息
        * @param[in] sessionID 请求的会话ID；
        * @param[in] errorCode 错误码。0 表示成功。
        * @param[in] isLast     标示是否是最后一批数据；
        * @param[in] info        指向返回的信息结构体。当errorCode不为0时，info为空。
        * @attention 不要修改和删除info所指示的数据；函数调用结束，参数不再有效。
        * @ingroup G_T_AccountDetails
        */
        virtual void TAP_CDECL OnRspQryFund(ITapTrade::TAPIUINT32 sessionID, ITapTrade::TAPIINT32 errorCode, ITapTrade::TAPIYNFLAG isLast, const ITapTrade::TapAPIFundData *info) = 0;
        /**
        * @brief    用户资金变化通知
        * @details    用户的委托成交后会引起资金数据的变化，因此需要向用户实时反馈。
        * @param[in] info        指向返回的信息结构体。当errorCode不为0时，info为空。
        * @note 如果不关注此项内容，可以设定Login时的NoticeIgnoreFlag以屏蔽。
        * @attention 不要修改和删除info所指示的数据；函数调用结束，参数不再有效。
        * @ingroup G_T_AccountDetails
        */
        virtual void TAP_CDECL OnRtnFund(const ITapTrade::TapAPIFundData *info) = 0;
        /**
        * @brief 返回系统中的交易所信息
        * @param[in] sessionID 请求的会话ID；
        * @param[in] errorCode 错误码。0 表示成功。
        * @param[in] isLast     标示是否是最后一批数据；
        * @param[in] info        指向返回的信息结构体。当errorCode不为0时，info为空。
        * @attention 不要修改和删除info所指示的数据；函数调用结束，参数不再有效。
        * @ingroup G_T_TradeSystem
        */
        virtual void TAP_CDECL OnRspQryExchange(ITapTrade::TAPIUINT32 sessionID, ITapTrade::TAPIINT32 errorCode, ITapTrade::TAPIYNFLAG isLast, const ITapTrade::TapAPIExchangeInfo *info) = 0;
        /**
        * @brief    返回系统中品种信息
        * @details    此回调接口用于向用户返回得到的所有品种信息。
        * @param[in] sessionID 请求的会话ID，和GetAllCommodities()函数返回对应；
        * @param[in] errorCode 错误码。0 表示成功。
        * @param[in] isLast     标示是否是最后一批数据；
        * @param[in] info        指向返回的信息结构体。当errorCode不为0时，info为空。
        * @attention 不要修改和删除info所指示的数据；函数调用结束，参数不再有效。
        * @ingroup G_T_Commodity
        */
        virtual void TAP_CDECL OnRspQryCommodity(ITapTrade::TAPIUINT32 sessionID, ITapTrade::TAPIINT32 errorCode, ITapTrade::TAPIYNFLAG isLast, const ITapTrade::TapAPICommodityInfo *info) = 0;
        /**
        * @brief 返回系统中合约信息
        * @param[in] sessionID 请求的会话ID；
        * @param[in] errorCode 错误码。0 表示成功。
        * @param[in] isLast     标示是否是最后一批数据；
        * @param[in] info        指向返回的信息结构体。当errorCode不为0时，info为空。
        * @attention 不要修改和删除info所指示的数据；函数调用结束，参数不再有效。
        * @ingroup G_T_Contract
        */
        virtual void TAP_CDECL OnRspQryContract(ITapTrade::TAPIUINT32 sessionID, ITapTrade::TAPIINT32 errorCode, ITapTrade::TAPIYNFLAG isLast, const ITapTrade::TapAPITradeContractInfo *info) = 0;
        /**
        * @brief    返回新增合约信息
        * @details    向用户推送新的合约。主要用来处理在交易时间段中服务器添加了新合约时，向用户发送这个合约的信息。
        * @param[in] info        指向返回的信息结构体。当errorCode不为0时，info为空。
        * @attention 不要修改和删除info所指示的数据；函数调用结束，参数不再有效。
        * @ingroup G_T_Contract
        */
        virtual void TAP_CDECL OnRtnContract(const ITapTrade::TapAPITradeContractInfo *info) = 0;
                /**
        * @brief    订单操作应答
        * @details    下单、撤单、改单应答。下单都会有次应答回调，如果下单请求结构中没有填写合约或者资金账号，则仅返回错误号。
                 * 撤单、改单错误由应答和OnRtnOrder，成功仅返回OnRtnOrder回调。
                 * sessionID标识请求对应的sessionID，以便确定该笔应答对应的请求。
                 * 
        * @param[in] sessionID 请求的会话ID；
        * @param[in] errorCode 错误码。0 表示成功。
        * @param[in] info 订单应答具体类型，包含订单操作类型和订单信息指针。
                 * 订单信息指针部分情况下可能为空，如果为空，可以通过SessiuonID找到对应请求获取请求类型。
        * @attention 不要修改和删除info所指示的数据；函数调用结束，参数不再有效。
        * @ingroup G_T_TradeActions
        */
        virtual void TAP_CDECL OnRspOrderAction(ITapTrade::TAPIUINT32 sessionID, ITapTrade::TAPIINT32 errorCode, const ITapTrade::TapAPIOrderActionRsp *info) = 0;
        /**
        * @brief 返回新委托。新下的或者其他地方下的推送过来的。
        * @details    服务器接收到客户下的委托内容后就会保存起来等待触发，同时向用户回馈一个
        *            新委托信息说明服务器正确处理了用户的请求，返回的信息中包含了全部的委托信息，
        *            同时有一个用来标示此委托的委托号。
        * @param[in] info 指向返回的信息结构体。当errorCode不为0时，info为空。
        * @note 如果不关注此项内容，可以设定Login时的NoticeIgnoreFlag以屏蔽。
        * @attention 不要修改和删除info所指示的数据；函数调用结束，参数不再有效。
        * @ingroup G_T_TradeActions
        */
        virtual void TAP_CDECL OnRtnOrder(const ITapTrade::TapAPIOrderInfoNotice *info) = 0;
        /**
        * @brief    返回查询的委托信息
        * @details    返回用户查询的委托的具体信息。
        * @param[in] sessionID 请求的会话ID；
        * @param[in] errorCode 错误码。0 表示成功。
        * @param[in] isLast 标示是否是最后一批数据；
        * @param[in] info 指向返回的信息结构体。当errorCode不为0时，info为空。
        * @attention 不要修改和删除info所指示的数据；函数调用结束，参数不再有效。
        * @ingroup G_T_TradeInfo
        */
        virtual void TAP_CDECL OnRspQryOrder(ITapTrade::TAPIUINT32 sessionID, ITapTrade::TAPIINT32 errorCode, ITapTrade::TAPIYNFLAG isLast, const ITapTrade::TapAPIOrderInfo *info) = 0;
        /**
        * @brief 返回查询的委托变化流程信息
        * @param[in] sessionID 请求的会话ID；
        * @param[in] errorCode 错误码，当errorCode==0时，info指向返回的委托变化流程结构体，不然为NULL；
        * @param[in] isLast 标示是否是最后一批数据；
        * @param[in] info 返回的委托变化流程指针。
        * @attention 不要修改和删除info所指示的数据；函数调用结束，参数不再有效。
        * @ingroup G_T_TradeInfo
        */
        virtual void TAP_CDECL OnRspQryOrderProcess(ITapTrade::TAPIUINT32 sessionID, ITapTrade::TAPIINT32 errorCode, ITapTrade::TAPIYNFLAG isLast, const ITapTrade::TapAPIOrderInfo *info) = 0;
        /**
        * @brief 返回查询的成交信息
        * @param[in] sessionID 请求的会话ID；
        * @param[in] errorCode 错误码。0 表示成功。
        * @param[in] isLast     标示是否是最后一批数据；
        * @param[in] info        指向返回的信息结构体。当errorCode不为0时，info为空。
        * @attention 不要修改和删除info所指示的数据；函数调用结束，参数不再有效。
        * @ingroup G_T_TradeInfo
        */
        virtual void TAP_CDECL OnRspQryFill(ITapTrade::TAPIUINT32 sessionID, ITapTrade::TAPIINT32 errorCode, ITapTrade::TAPIYNFLAG isLast, const ITapTrade::TapAPIFillInfo *info) = 0;
        /**
        * @brief    推送来的成交信息
        * @details    用户的委托成交后将向用户推送成交信息。
        * @param[in] info        指向返回的信息结构体。当errorCode不为0时，info为空。
        * @note 如果不关注此项内容，可以设定Login时的NoticeIgnoreFlag以屏蔽。
        * @attention 不要修改和删除info所指示的数据；函数调用结束，参数不再有效。
        * @ingroup G_T_TradeActions
        */
        virtual void TAP_CDECL OnRtnFill(const ITapTrade::TapAPIFillInfo *info) = 0;
        /**
        * @brief 返回查询的持仓
        * @param[in] sessionID 请求的会话ID；
        * @param[in] errorCode 错误码。0 表示成功。
        * @param[in] isLast     标示是否是最后一批数据；
        * @param[in] info        指向返回的信息结构体。当errorCode不为0时，info为空。
        * @attention 不要修改和删除info所指示的数据；函数调用结束，参数不再有效。
        * @ingroup G_T_TradeInfo
        */
        virtual void TAP_CDECL OnRspQryPosition(ITapTrade::TAPIUINT32 sessionID, ITapTrade::TAPIINT32 errorCode, ITapTrade::TAPIYNFLAG isLast, const ITapTrade::TapAPIPositionInfo *info) = 0;
        /**
        * @brief 持仓变化推送通知
        * @param[in] info        指向返回的信息结构体。当errorCode不为0时，info为空。
        * @note 如果不关注此项内容，可以设定Login时的NoticeIgnoreFlag以屏蔽。
        * @attention 不要修改和删除info所指示的数据；函数调用结束，参数不再有效。
        * @ingroup G_T_TradeActions
        */
        virtual void TAP_CDECL OnRtnPosition(const ITapTrade::TapAPIPositionInfo *info) = 0;
        /**
        * @brief 返回查询的持仓汇总
        * @param[in] sessionID 请求的会话ID；
        * @param[in] errorCode 错误码。0 表示成功。
        * @param[in] isLast     标示是否是最后一批数据；
        * @param[in] info        指向返回的信息结构体。当errorCode不为0时，info为空。
        * @attention 不要修改和删除info所指示的数据；函数调用结束，参数不再有效。
        * @ingroup G_T_TradeInfo
        */
        virtual void TAP_CDECL OnRspQryPositionSummary(TAPIUINT32 sessionID, TAPIINT32 errorCode, TAPIYNFLAG isLast, const TapAPIPositionSummary *info) = 0;
        
        /**
        * @brief 持仓汇总变化推送通知
        * @param[in] info        指向返回的信息结构体。当errorCode不为0时，info为空。
        * @note 如果不关注此项内容，可以设定Login时的NoticeIgnoreFlag以屏蔽。
        * @attention 不要修改和删除info所指示的数据；函数调用结束，参数不再有效。
        * @ingroup G_T_TradeActions
        */
        virtual void TAP_CDECL OnRtnPositionSummary(const TapAPIPositionSummary *info) = 0;
        /**
        * @brief 持仓盈亏通知
        * @param[in] info        指向返回的信息结构体。当errorCode不为0时，info为空。
        * @note 如果不关注此项内容，可以设定Login时的NoticeIgnoreFlag以屏蔽。
        * @attention 不要修改和删除info所指示的数据；函数调用结束，参数不再有效。
        * @ingroup G_T_TradeActions
        */
        virtual void TAP_CDECL OnRtnPositionProfit(const ITapTrade::TapAPIPositionProfitNotice *info) = 0;


        /**
        * @brief 返回系统中的币种信息
        * @param[in] sessionID 请求的会话ID；
        * @param[in] errorCode 错误码。0 表示成功。
        * @param[in] isLast     标示是否是最后一批数据；
        * @param[in] info        指向返回的信息结构体。当errorCode不为0时，info为空。
        * @attention 不要修改和删除info所指示的数据；函数调用结束，参数不再有效。
        * @ingroup G_T_TradeSystem
        */
        virtual void TAP_CDECL OnRspQryCurrency(ITapTrade::TAPIUINT32 sessionID, ITapTrade::TAPIINT32 errorCode, ITapTrade::TAPIYNFLAG isLast, const ITapTrade::TapAPICurrencyInfo *info) = 0;

        /**
        * @brief    交易消息通知
        * @details    返回查询的用户资金状态信息。信息说明了用户的资金状态，用户需要仔细查看这些信息。
        * @param[in] sessionID 请求的会话ID；
        * @param[in] errorCode 错误码。0 表示成功。
        * @param[in] isLast     标示是否是最后一批数据；
        * @param[in] info        指向返回的信息结构体。当errorCode不为0时，info为空。
        * @attention 不要修改和删除info所指示的数据；函数调用结束，参数不再有效。
        * @ingroup G_T_AccountDetails
        */
        virtual void TAP_CDECL OnRspQryTradeMessage(ITapTrade::TAPIUINT32 sessionID, ITapTrade::TAPIINT32 errorCode, ITapTrade::TAPIYNFLAG isLast, const ITapTrade::TapAPITradeMessage *info) = 0;
        /**
        * @brief    交易消息通知
        * @details    用户在交易过程中可能因为资金、持仓、平仓的状态变动使账户处于某些危险状态，或者某些重要的信息需要向用户通知。
        * @param[in] info        指向返回的信息结构体。当errorCode不为0时，info为空。
        * @attention 不要修改和删除info所指示的数据；函数调用结束，参数不再有效。
        * @ingroup G_T_AccountDetails
        */
        virtual void TAP_CDECL OnRtnTradeMessage(const ITapTrade::TapAPITradeMessage *info) = 0;
        /**
        * @brief 历史委托查询应答
        * @param[in] sessionID 请求的会话ID；
        * @param[in] errorCode 错误码。0 表示成功。
        * @param[in] isLast     标示是否是最后一批数据
        * @param[in] info        指向返回的信息结构体。当errorCode不为0时，info为空。
        * @attention 不要修改和删除info所指示的数据；函数调用结束，参数不再有效。
        * @ingroup G_T_HisInfo
        */
        virtual void TAP_CDECL OnRspQryHisOrder(ITapTrade::TAPIUINT32 sessionID, ITapTrade::TAPIINT32 errorCode, ITapTrade::TAPIYNFLAG isLast, const ITapTrade::TapAPIHisOrderQryRsp *info) = 0;
        /**
        * @brief 历史委托流程查询应答
        * @param[in] sessionID 请求的会话ID；
        * @param[in] errorCode 错误码。0 表示成功。
        * @param[in] isLast     标示是否是最后一批数据
        * @param[in] info        指向返回的信息结构体。当errorCode不为0时，info为空。
        * @attention 不要修改和删除info所指示的数据；函数调用结束，参数不再有效。
        * @ingroup G_T_HisInfo
        */
        virtual void TAP_CDECL OnRspQryHisOrderProcess(ITapTrade::TAPIUINT32 sessionID, ITapTrade::TAPIINT32 errorCode, ITapTrade::TAPIYNFLAG isLast, const ITapTrade::TapAPIHisOrderProcessQryRsp *info) = 0;
        /**
        * @brief 历史成交查询应答
        * @param[in] sessionID 请求的会话ID；
        * @param[in] errorCode 错误码。0 表示成功。
        * @param[in] isLast     标示是否是最后一批数据
        * @param[in] info        指向返回的信息结构体。当errorCode不为0时，info为空。
        * @attention 不要修改和删除info所指示的数据；函数调用结束，参数不再有效。
        * @ingroup G_T_HisInfo
        */
        virtual void TAP_CDECL OnRspQryHisMatch(ITapTrade::TAPIUINT32 sessionID, ITapTrade::TAPIINT32 errorCode, ITapTrade::TAPIYNFLAG isLast, const ITapTrade::TapAPIHisMatchQryRsp *info) = 0;
        /**
        * @brief 历史持仓查询应答
        * @param[in] sessionID 请求的会话ID；
        * @param[in] errorCode 错误码。0 表示成功。
        * @param[in] isLast     标示是否是最后一批数据
        * @param[in] info        指向返回的信息结构体。当errorCode不为0时，info为空。
        * @attention 不要修改和删除info所指示的数据；函数调用结束，参数不再有效。
        * @ingroup G_T_HisInfo
        */
        virtual void TAP_CDECL OnRspQryHisPosition(ITapTrade::TAPIUINT32 sessionID, ITapTrade::TAPIINT32 errorCode, ITapTrade::TAPIYNFLAG isLast, const ITapTrade::TapAPIHisPositionQryRsp *info) = 0;
        /**
        * @brief 历史交割查询应答
        * @param[in] sessionID 请求的会话ID；
        * @param[in] errorCode 错误码。0 表示成功。
        * @param[in] isLast     标示是否是最后一批数据
        * @param[in] info        指向返回的信息结构体。当errorCode不为0时，info为空。
        * @attention 不要修改和删除info所指示的数据；函数调用结束，参数不再有效。
        * @ingroup G_T_HisInfo
        */
        virtual void TAP_CDECL OnRspQryHisDelivery(ITapTrade::TAPIUINT32 sessionID, ITapTrade::TAPIINT32 errorCode, ITapTrade::TAPIYNFLAG isLast, const ITapTrade::TapAPIHisDeliveryQryRsp *info) = 0;
        /**
        * @brief 资金调整查询应答
        * @param[in] sessionID 请求的会话ID；
        * @param[in] errorCode 错误码。0 表示成功。
        * @param[in] isLast     标示是否是最后一批数据
        * @param[in] info        指向返回的信息结构体。当errorCode不为0时，info为空。
        * @attention 不要修改和删除info所指示的数据；函数调用结束，参数不再有效。
        * @ingroup G_T_HisInfo
        */
        virtual void TAP_CDECL OnRspQryAccountCashAdjust(ITapTrade::TAPIUINT32 sessionID, ITapTrade::TAPIINT32 errorCode, ITapTrade::TAPIYNFLAG isLast, const ITapTrade::TapAPIAccountCashAdjustQryRsp *info) = 0;
        /**
        * @brief 查询用户账单应答 Add:2013.12.11
        * @param[in] sessionID 请求的会话ID；
        * @param[in] errorCode 错误码。0 表示成功。
        * @param[in] info        指向返回的信息结构体。当errorCode不为0时，info为空。
        * @attention 不要修改和删除info所指示的数据；函数调用结束，参数不再有效。
        * @ingroup G_T_Bill
        */
        virtual void TAP_CDECL OnRspQryBill(ITapTrade::TAPIUINT32 sessionID, ITapTrade::TAPIINT32 errorCode, ITapTrade::TAPIYNFLAG isLast, const ITapTrade::TapAPIBillQryRsp *info) = 0;
        /**
        * @brief 查询账户手续费计算参数 Add:2017.01.14
        * @param[in] sessionID 请求的会话ID；
        * @param[in] errorCode 错误码。0 表示成功。
        * @param[in] info        指向返回的信息结构体。当errorCode不为0时，info为空。
        * @attention 不要修改和删除info所指示的数据；函数调用结束，参数不再有效。
        * @ingroup G_T_Rent
        */
        virtual void TAP_CDECL OnRspQryAccountFeeRent(ITapTrade::TAPIUINT32 sessionID, ITapTrade::TAPIINT32 errorCode, ITapTrade::TAPIYNFLAG isLast, const ITapTrade::TapAPIAccountFeeRentQryRsp *info) = 0;
        /**
        * @brief 查询账户保证金计算参数 Add:2017.01.14
        * @param[in] sessionID 请求的会话ID；
        * @param[in] errorCode 错误码。0 表示成功。
        * @param[in] info        指向返回的信息结构体。当errorCode不为0时，info为空。
        * @attention 不要修改和删除info所指示的数据；函数调用结束，参数不再有效。
        * @ingroup G_T_Rent
        */
        virtual void TAP_CDECL OnRspQryAccountMarginRent(ITapTrade::TAPIUINT32 sessionID, ITapTrade::TAPIINT32 errorCode, ITapTrade::TAPIYNFLAG isLast, const ITapTrade::TapAPIAccountMarginRentQryRsp *info) = 0;

        /**
        * @brief 港交所做市商双边报价应答 Add:2017.08.29
        * @param[in] sessionID 请求的会话ID；
        * @param[in] errorCode 错误码。0 表示成功。
        * @param[in] info        指向返回的信息结构体。当errorCode不为0时，info为空。
        * @attention 不要修改和删除info所指示的数据；函数调用结束，参数不再有效。
        * @ingroup G_T_HKMarket
        */
        virtual void TAP_CDECL OnRspHKMarketOrderInsert(ITapTrade::TAPIUINT32 sessionID, ITapTrade::TAPIINT32 errorCode,  const ITapTrade::TapAPIOrderMarketInsertRsp *info) = 0;

        /**
        * @brief 港交所做市商双边撤单应答 Add:2017.08.29
        * @param[in] sessionID 请求的会话ID；
        * @param[in] errorCode 错误码。0 表示成功。
        * @param[in] info        指向返回的信息结构体。当errorCode不为0时，info为空。
        * @attention 不要修改和删除info所指示的数据；函数调用结束，参数不再有效。
        * @ingroup G_T_HKMarket
        */
        virtual void TAP_CDECL OnRspHKMarketOrderDelete(ITapTrade::TAPIUINT32 sessionID, ITapTrade::TAPIINT32 errorCode, const ITapTrade::TapAPIOrderMarketDeleteRsp *info) = 0;

        /**
        * @brief 港交所询价通知 Add:2017.08.29
        * @param[in] info        指向返回的信息结构体。当errorCode不为0时，info为空。
        * @attention 不要修改和删除info所指示的数据；函数调用结束，参数不再有效。
        * @ingroup G_T_HKMarket
        */
        virtual void TAP_CDECL OnHKMarketQuoteNotice( const ITapTrade::TapAPIOrderQuoteMarketNotice *info) = 0;


        /**
        * @brief 订单删除应答 Add:2017.12.05
        * @param[in] sessionID 请求的会话ID；
        * @param[in] errorCode 错误码。0 表示成功。
        * @param[in] info        指向返回的信息结构体。当errorCode不为0时，info为空。
        * @attention 不要修改和删除info所指示的数据；函数调用结束，参数不再有效。
        * @ingroup G_T_LocalAction
        */
        virtual void TAP_CDECL OnRspOrderLocalRemove(ITapTrade::TAPIUINT32 sessionID, ITapTrade::TAPIINT32 errorCode, const ITapTrade::TapAPIOrderLocalRemoveRsp *info) = 0;

        /**
        * @brief 订单录入应答 Add:2017.12.05
        * @param[in] sessionID 请求的会话ID；
        * @param[in] errorCode 错误码。0 表示成功。
        * @param[in] info        指向返回的信息结构体。当errorCode不为0时，info为空。
        * @attention 不要修改和删除info所指示的数据；函数调用结束，参数不再有效。
        * @ingroup G_T_LocalAction
        */
        virtual void TAP_CDECL OnRspOrderLocalInput(ITapTrade::TAPIUINT32 sessionID, ITapTrade::TAPIINT32 errorCode, const ITapTrade::TapAPIOrderLocalInputRsp *info) = 0;

        /**
        * @brief 订单修改应答 Add:2017.12.05
        * @param[in] sessionID 请求的会话ID；
        * @param[in] errorCode 错误码。0 表示成功。
        * @param[in] info        指向返回的信息结构体。当errorCode不为0时，info为空。
        * @attention 不要修改和删除info所指示的数据；函数调用结束，参数不再有效。
        * @ingroup G_T_LocalAction
        */
        virtual void TAP_CDECL OnRspOrderLocalModify(ITapTrade::TAPIUINT32 sessionID, ITapTrade::TAPIINT32 errorCode, const ITapTrade::TapAPIOrderLocalModifyRsp *info) = 0;

        /**
        * @brief 订单转移应答 Add:2017.12.05
        * @param[in] sessionID 请求的会话ID；
        * @param[in] errorCode 错误码。0 表示成功。
        * @param[in] info        指向返回的信息结构体。当errorCode不为0时，info为空。
        * @attention 不要修改和删除info所指示的数据；函数调用结束，参数不再有效。
        * @ingroup G_T_LocalAction
        */
        virtual void TAP_CDECL OnRspOrderLocalTransfer(ITapTrade::TAPIUINT32 sessionID, ITapTrade::TAPIINT32 errorCode, const ITapTrade::TapAPIOrderLocalTransferRsp *info) = 0;

        /**
        * @brief 成交录入应答 Add:2017.12.05
        * @param[in] sessionID 请求的会话ID；
        * @param[in] errorCode 错误码。0 表示成功。
        * @param[in] info        指向返回的信息结构体。当errorCode不为0时，info为空。
        * @attention 不要修改和删除info所指示的数据；函数调用结束，参数不再有效。
        * @ingroup G_T_LocalAction
        */
        virtual void TAP_CDECL OnRspFillLocalInput(ITapTrade::TAPIUINT32 sessionID, ITapTrade::TAPIINT32 errorCode, const ITapTrade::TapAPIFillLocalInputRsp *info) = 0;

        /**
        * @brief 订单删除应答 Add:2017.12.05
        * @param[in] sessionID 请求的会话ID；
        * @param[in] errorCode 错误码。0 表示成功。
        * @param[in] info        指向返回的信息结构体。当errorCode不为0时，info为空。
        * @attention 不要修改和删除info所指示的数据；函数调用结束，参数不再有效。
        * @ingroup G_T_LocalAction
        */
        virtual void TAP_CDECL OnRspFillLocalRemove(ITapTrade::TAPIUINT32 sessionID, ITapTrade::TAPIINT32 errorCode, const ITapTrade::TapAPIFillLocalRemoveRsp *info) = 0;



    };



    //TapTradeAPI 对外功能接口。包含了用户可以调用的功能函数。
    class ITapTradeAPI
    {
    public:
        /**
        * @brief    设置API的回调接口对象。
        * @details    系统对API的通知将通过设置的回调对象通知给使用者。
        *            ITapTradeAPINotify是API的回调接口，用户需要继承实现此接口类对象来完成用户需要的功能。
        *            如果用户没有设置回调接口，则API不会向用户返回任何有用的信息。\n
        *            ITapTradeAPINotify类的详细内容请查看TapTradeAPI.h 文件。
        * @param[in] apiNotify 实现了ITapTradeAPINotify接口的对象指针。
        * @operationtype 同步操作
        * @ingroup G_T_Login
        */
        virtual ITapTrade::TAPIINT32 TAP_CDECL SetAPINotify(ITapTrade::ITapTradeAPINotify *pSpi) = 0;
        /**
        * @brief 设置服务器的IP地址和端口。
        * @param[in] IP   IP地址
        * @param[in] port 端口号
        * @operationtype 同步操作
        * @ingroup G_T_Login
        */
        virtual ITapTrade::TAPIINT32 TAP_CDECL SetHostAddress(const ITapTrade::TAPICHAR *IP, ITapTrade::TAPIUINT16 port,bool bSSL=false) = 0;
        /**
        * @brief    发起登录请求。API将先连接服务，建立链路，发起登录认证。
        * @details    在使用函数前用户需要完成服务器的设置SetHostAddress()，并且创建TapAPITradeLoginAuth类型的用户信息，
        *            并且需要设置好回调接口。\n
        *            登录过程中建立连接的返回信息通过回调OnConnect返回给用户。\n
        *            连接建立后的用户验证回馈信息通过回调OnLogin()返回给用户。\n
        *            登录成功后API会自动进行API的初始化，API向服务器请求基础数据，查询完以后会通过回调OnAPIReady()
        *            指示用户API初始化完成，可以进行后续的操作了。
        * @param[in] loginAuth 登录验证信息结构指针。包含登录需要的验证信息。
        * @retval 0 登录成功，API开始准备后台数据
        * @retval 非0 错误码
        * @operationtype 异步操作
        * @note TapAPITradeLoginAuth中的NoticeIgnoreFlag用于标记是否忽略特定的通知回调。\n
        *       例如：不需要接收OnRtnFund和OnRtnPositionProfit,可以这么设定：\n
        *       NoticeIgnoreFlag = TAPI_NOTICE_IGNORE_FUND | TAPI_NOTICE_IGNORE_POSITIONPROFIT;
        * @attention Login()函数调用成功只是代表于服务器建立了链路连接，只有回调OnLogin()的返回能指示用户是否成功登录了。
        * @ingroup G_T_Login
        */
        virtual ITapTrade::TAPIINT32 TAP_CDECL Login(const ITapTrade::TapAPITradeLoginAuth *loginAuth) = 0;

        /**
        * @brief    请求发送二次认证认证码
        * @details    此函数需要9.2.7后台，根据回掉函数OnRtnContactInfo中的联系方式，选择其中一个请求二次认证吗，
        *            收到正确应答后可以通过SetVertificateCode 设置二次认证授权码完成登陆过程。
        * @param[out] sessionID本次请求的会话ID。
        * @param[in]  ContractInfo,要接收二次认证吗的邮箱或者电话。
        * @attention 该函数调用需要在登陆应答后返回10003错误，API会回调客户二次 认证的联系方式，用户选择其中一个联系方式（邮箱或者电话）请求二次认证。再通过设置二次认证授权码完成登陆。
        */
        virtual ITapTrade::TAPIINT32 TAP_CDECL RequestVertificateCode(ITapTrade::TAPIUINT32 *sessionID,ITapTrade::TAPISTR_40 ContactInfo) = 0;
        /**
        * @brief    设置二次认证信息。
        * @details    登录完成后，如果系统配置需要进行二次认证码输入，则登录后会提示需要进行二次认证。
        *            此时调用该函数输入二次认证来完成登录。
        *            登录完成后不允许再调用此函数。其他原因引起的登录失败也不能调用次函数，否则会返回对应的错误信息。
        *            调用此接口后，会返回登录应答成功与否的标记，如果成功表示登录完成，可以等待OnAPIReady API完成回调。
        *            如果超时，回调完成后API会主动断开链接，需要再次进行登录操作。
        *            如果验证码错误，则可以再次调用此函数输入正确的验证码进行验证。
        * @param[in] VertificateCode二次认证码。
        * @retval 0 发送认证码成功
        * @retval 非0 错误码
        * @operationtype 异步操作
        * @ingroup G_T_Login
        */
        virtual ITapTrade::TAPIINT32 TAP_CDECL SetVertificateCode(TAPISTR_10 VertificateCode) = 0;
        
        /**
        * @brief    断开和服务器的链路连接。
        * @details    调用函数后API将登出并断开与服务器的连接。
        * @operationtype 同步操作
        * @ingroup G_T_Disconnect
        */
        virtual ITapTrade::TAPIINT32 TAP_CDECL Disconnect() = 0;
        /**
        * @brief    修改密码。
        * @details    成功后用户密码将被设置成newPassword。
        * @param[out]    sessionID 返回此次修改密码的会话ID;
        * @param[in]    req 请求修改密码的结构体指针
        * @retval 0 成功
        * @retval 非0 错误码
        * @operationtype 异步操作
        * @ingroup G_T_UserInfo
        */
        virtual ITapTrade::TAPIINT32 TAP_CDECL ChangePassword(ITapTrade::TAPIUINT32 *sessionID, const ITapTrade::TapAPIChangePasswordReq *req) = 0;


        /**
        * @brief    认证密码。
        * @details    交易员认证某个账户密码是否正确。
        * @param[out]    sessionID 返回此次修改密码的会话ID;
        * @param[in]    req 请求认证密码的结构体指针
        * @retval 0 成功
        * @retval 非0 错误码
        * @operationtype 异步操作
        * @ingroup G_T_UserInfo
        */
        virtual ITapTrade::TAPIINT32 TAP_CDECL AuthPassword(ITapTrade::TAPIUINT32 *sessionID, const ITapTrade::TapAPIAuthPasswordReq *req) = 0;


        /**
        * @brief    判断登录用户是否具有某权限。
        * @details    用户的权限在用户登录时已经传递给API，所以此函数执行的是本地的查询。
        * @param[in] rightID 权限ID。
        * @retval 0 不具有权限
        * @retval 非0 具有权限
        * @operationtype 同步操作
        * @ingroup G_T_UserRight
        */
        virtual ITapTrade::TAPIINT32 TAP_CDECL HaveCertainRight(ITapTrade::TAPIRightIDType rightID) = 0;


        /**
        * @brief    查询系统日历。
        * @details    获取当前交易日，上次结算日，LME到期日，和上日LME到期日
        * @param[out]    sessionID 返回请求的会话ID;
        * @retval 0 请求成功
        * @retval 非0 错误码
        * @operationtype 异步操作
        * @note 该接口暂未实现
        * @ingroup G_T_UserRight
        */
        virtual ITapTrade::TAPIINT32 TAP_CDECL QryTradingDate(ITapTrade::TAPIUINT32 *sessionID) = 0;
        /**
        * @brief    设置用户预留信息。
        * @details    用户可以设置一个长度为50以内的字符信息，下次登录后可以得到这个信息。
        *            这个功能主要是用来让用户确认是自己的账号，主要是用来进行防伪。
        * @param[out]    sessionID 返回请求的会话ID;
        * @param[in] info    预留信息字符串指针
        * @retval 0 请求成功
        * @retval 非0 错误码
        * @operationtype 异步操作
        * @note 该接口暂未实现
        * @ingroup G_T_UserInfo
        */
        virtual ITapTrade::TAPIINT32 TAP_CDECL SetReservedInfo(ITapTrade::TAPIUINT32 *sessionID, const ITapTrade::TAPISTR_50 info) = 0;
        /**
        * @brief 查询用户下属的资金账号
        * @details    TapAPIAccQryReq是包含资金账号结构的结构体，用户需要实例化此结构体，
        *            但是不需要填写，这个结构体主要是用来提醒用户保存资金账号，资金账号
        *            在后续的函数调用中很多函数都需要使用到。
        * @param[out]    sessionID 返回请求的会话ID;
        * @param[in]    qryReq 查询用户下属的资金账号的结构体指针
        * @retval 0 请求成功
        * @retval 非0 错误码
        * @operationtype 异步操作
        * @ingroup G_T_AccountInfo
        */
        virtual ITapTrade::TAPIINT32 TAP_CDECL QryAccount(ITapTrade::TAPIUINT32 *sessionID, const ITapTrade::TapAPIAccQryReq *qryReq) = 0;
        /**
        * @brief    查询客户资金
        * @details    TapAPIFundReq需要QryAccount()获取的资金账号。
        *            函数的回调将返回资金账号的资金信息。\n
        * @param[out] sessionID 返回请求的会话ID;
        * @param[in] qryReq    查询客户资金请求的结构体指针
        * @retval 0 请求成功
        * @retval 非0 错误码
        * @operationtype 异步操作
        * @ingroup G_T_AccountDetails
        * @attention 每次登陆，该接口只能进行一次调用。建议初始化时调用一次，后续的通知通过OnRtnFund取得。
        */
        virtual ITapTrade::TAPIINT32 TAP_CDECL QryFund(ITapTrade::TAPIUINT32 *sessionID, const ITapTrade::TapAPIFundReq *qryReq) = 0;
        /**
        * @brief 查询交易系统交易所信息
        * @param[out] sessionID 返回请求的会话ID;
        * @retval 0 请求成功
        * @retval 非0 错误码
        * @operationtype 异步操作
        * @ingroup G_T_TradeSystem
        */
        virtual ITapTrade::TAPIINT32 TAP_CDECL QryExchange(ITapTrade::TAPIUINT32 *sessionID) = 0;
        /**
        * @brief    查询系统品种信息
        * @details    函数请求获取所有的品种信息。
        * @param[out] sessionID 返回请求的会话ID;
        * @retval 0 请求成功
        * @retval 非0 错误码
        * @operationtype 异步操作
        * @ingroup G_T_Commodity
        */
        virtual ITapTrade::TAPIINT32 TAP_CDECL QryCommodity(ITapTrade::TAPIUINT32 *sessionID) = 0;
        /**
        * @brief    查询系统中指定品种的合约信息
        * @details    使用此函数前需要先Qrycommodity()取得品种信息，
        *            然后选择需要的品种将信息填入TapAPICommodity结构体中完成查询请求。
        *            或者TapAPICommodity不填，则返回所有信息。
        * @param[out] sessionID 返回请求的会话ID;
        * @param[in] qryReq 查询系统中指定品种的合约信息请求的结构体指针;\n
        *                    该参数各字段为可选字段，可以用以下方法查询：\n
        *                    1.全部留空：查所有合约\n
        *                    2.仅交易所编码有效：查该交易所下所有品种的合约\n
        *                    3.交易所编码和品种类型有效：查该交易所下指定品种类型的合约\n
        *                    4.交易所编码、品种类型和品种编码都有效：查该品种下的所有合约
        * @retval 0 请求成功
        * @retval 非0 错误码
        * @operationtype 异步操作
        * @ingroup G_T_Contract
        */
        virtual ITapTrade::TAPIINT32 TAP_CDECL QryContract(ITapTrade::TAPIUINT32 *sessionID, const ITapTrade::TapAPICommodity *qryReq) = 0;

        /**
        * @brief    下单
        * @details    用户下单的操作函数。
        *            用户的下单操作会造成用户的资金、持仓、平仓、资金、风控标记等多种数据的变化，所以用户下的单成交后，
        *            会有多个回调通知来向用户展示数据的变化。
        * @param[out]    sessionID 返回请求的会话ID;
        * @param[out]    ClientOrderNo 返回客户本地委托号。
        * @param[in]    order 新的委托
        * @retval 0 请求成功
        * @retval 非0 错误码
        * @operationtype 异步操作
        * @ingroup G_T_TradeActions
        */
        virtual ITapTrade::TAPIINT32 TAP_CDECL InsertOrder(ITapTrade::TAPIUINT32 *sessionID,ITapTrade::TAPISTR_50 *ClientOrderNo, const ITapTrade::TapAPINewOrder *order) = 0;

        /**
        * @brief    撤单
        * @details    用户委托没有完全成交之前撤销剩余的委托。
        * @param[out]    sessionID 返回请求的会话ID;
        * @param[in]    order 撤销的委托
        * @retval 0 请求成功
        * @retval 非0 错误码
        * @operationtype 异步操作
        * @ingroup G_T_TradeActions
        */
        virtual ITapTrade::TAPIINT32 TAP_CDECL CancelOrder(ITapTrade::TAPIUINT32 *sessionID, const ITapTrade::TapAPIOrderCancelReq *order) = 0;

        /**
        * @brief    改单
        * @details    用户的委托没有完全成交之前可以进行改单操作来修改剩余的未成交的委托。\n
        *            用户填写新的委托来修改原来的未成交的部分。报单的修改会对比已经成交的部分来扣除成交部分。
        * @param[out]    sessionID 返回请求的会话ID;
        * @param[in]    order 修改的委托
        * @retval 0 请求成功
        * @retval 非0 错误码
        * @operationtype 异步操作
        * @ingroup G_T_TradeActions
        */
        virtual ITapTrade::TAPIINT32 TAP_CDECL AmendOrder(ITapTrade::TAPIUINT32 *sessionID, const ITapTrade::TapAPIAmendOrder *order) = 0;

        /**
        * @brief 订单激活
        * @details 用户的埋单需要发送时需要进行激活。或者港交所已挂起的订单。
        * @param[out]    sessionID 返回请求的会话ID;
        * @param[in]    order 要激活的订单
        * @retval 0 请求成功
        * @retval 非0 错误码
        * @operationtype 异步操作
        * @ingroup G_T_TradeActions
        */
        virtual TAPIINT32 TAP_CDECL ActivateOrder(TAPIUINT32 * sessionID, const TapAPIOrderActivateReq * order) = 0;
        
        /**
        * @brief    查询委托信息
        * @details    返回当前的委托信息，可以查询所有委托，也可以查询所有未结束的委托。\n
        * @retval 0 请求成功
        * @retval 非0 错误码
        * @operationtype 异步操作
        * @ingroup G_T_TradeInfo
        * @attention 每次登陆，该接口只能进行一次调用。建议初始化时调用一次，后续的通知通过OnRtnOrder取得。
        */
        virtual ITapTrade::TAPIINT32 TAP_CDECL QryOrder(ITapTrade::TAPIUINT32 *sessionID, const ITapTrade::TapAPIOrderQryReq *qryReq) = 0;
        /**
        * @brief    查询委托变化流程
        * @details    查询用户的委托的变化流程，查询将返回委托的每一次的变化。
        * @param[out] sessionID 返回请求的会话ID;
        * @param[in] qryReq 委托流程查询信息结构体指针。
        * @retval 0 请求成功
        * @retval 非0 错误码
        * @operationtype 异步操作
        * @ingroup G_T_TradeInfo
        */
        virtual ITapTrade::TAPIINT32 TAP_CDECL QryOrderProcess(ITapTrade::TAPIUINT32 *sessionID, const ITapTrade::TapAPIOrderProcessQryReq *qryReq) = 0;
        /**
        * @brief 查询成交信息
        * @details    查询系统中成交的信息。
        * @param[out] sessionID 返回请求的会话ID;
        * @param[in] qryReq 成交查询信息结构体指针。
        * @retval 0 请求成功
        * @retval 非0 错误码
        * @operationtype 异步操作
        * @ingroup G_T_TradeInfo
        * @attention 每次登陆，该接口只能进行一次调用。建议初始化时调用一次，后续的通知通过OnRtnFill取得。
        */
        virtual ITapTrade::TAPIINT32 TAP_CDECL QryFill(ITapTrade::TAPIUINT32 *sessionID, const ITapTrade::TapAPIFillQryReq *qryReq) = 0;
        /**
        * @brief    查询用户持仓
        * @details    查询用户的所有持仓信息。
        * @param[out] sessionID 返回请求的会话ID;
        * @param[in] qryReq    查询用户持仓请求的结构体指针
        * @retval 0 请求成功
        * @retval 非0 错误码
        * @operationtype 异步操作
        * @ingroup G_T_TradeInfo
        * @attention 每次登陆，该接口只能进行一次调用。建议初始化时调用一次，后续的通知通过OnRtnPosition取得。
        */
        virtual ITapTrade::TAPIINT32 TAP_CDECL QryPosition(ITapTrade::TAPIUINT32 *sessionID, const ITapTrade::TapAPIPositionQryReq *qryReq) = 0;

        /**
        * @brief    查询用户持仓汇总
        * @details    查询用户的所有持仓信息。
        * @param[out] sessionID 返回请求的会话ID;
        * @param[in] qryReq    查询用户持仓请求的结构体指针
        * @retval 0 请求成功
        * @retval 非0 错误码
        * @operationtype 异步操作
        * @ingroup G_T_TradeInfo
        * @attention 每次登陆，该接口只能进行一次调用。建议初始化时调用一次，后续的通知通过OnRtnPosition取得。
        */
        virtual ITapTrade::TAPIINT32 TAP_CDECL QryPositionSummary(ITapTrade::TAPIUINT32 *sessionID, const ITapTrade::TapAPIPositionQryReq *qryReq) = 0;

        /**
        * @brief 获取交易所用币种的信息
        * @param[out] sessionID 返回请求的会话ID;
        * @retval 0 请求成功
        * @retval 非0 错误码
        * @operationtype 异步操作
        * @ingroup G_T_TradeSystem
        */
        virtual ITapTrade::TAPIINT32 TAP_CDECL QryCurrency(ITapTrade::TAPIUINT32 *sessionID) = 0;
        /**
        * @brief 客户资金调整查询请求
        * @param[out] sessionID 返回请求的会话ID;
        * @param[in]    Req    客户资金调整查询请求的结构体指针
        * @retval 0 请求成功
        * @retval 非0 错误码
        * @operationtype 异步操作
        * @ingroup G_T_HisInfo
        */
        virtual ITapTrade::TAPIINT32 TAP_CDECL QryAccountCashAdjust(ITapTrade::TAPIUINT32 *sessionID, const ITapTrade::TapAPIAccountCashAdjustQryReq *qryReq) = 0;
        /**
        * @brief    获取交易或风控消息
        * @details    此函数用来主动获取账号的交易或者风控消息。交易或者风控消息用来标识账号的状态。
        * @param[out] sessionID 返回请求的会话ID;
        * @param[in] qryReq 获取交易或风控消息请求的结构体指针;
        * @retval 0 请求成功
        * @retval 非0 错误码
        * @operationtype 异步操作
        说明：易盛保留接口
        * @ingroup G_T_AccountDetails
        */
        virtual ITapTrade::TAPIINT32 TAP_CDECL QryTradeMessage(ITapTrade::TAPIUINT32 *sessionID, const ITapTrade::TapAPITradeMessageReq *qryReq) = 0;
        /**
        * @brief 查询用户账单
        * @param[out]    sessionID 返回请求的会话ID;
        * @param[in]    qryReq    查询帐单请求的结构体指针
        * @retval 0 请求成功
        * @retval 非0 错误码
        * @operationtype 异步操作
        * @ingroup G_T_Bill
        */
        virtual ITapTrade::TAPIINT32 TAP_CDECL QryBill(ITapTrade::TAPIUINT32 *sessionID, const ITapTrade::TapAPIBillQryReq *qryReq) = 0;
        /**
        * @brief 历史委托查询请求
        * @param[out]    sessionID 返回请求的会话ID;
        * @param[in]    Req    历史委托查询请求的结构体指针
        * @retval 0 请求成功
        * @retval 非0 错误码
        * @operationtype 异步操作
        * @ingroup G_T_HisInfo
        */
        virtual ITapTrade::TAPIINT32 TAP_CDECL QryHisOrder(ITapTrade::TAPIUINT32 *sessionID, const ITapTrade::TapAPIHisOrderQryReq *qryReq) = 0;
        /**
        * @brief 历史委托流程查询请求
        * @param[out] sessionID 返回请求的会话ID;
        * @param[in]    Req    历史委托流程查询请求的结构体指针
        * @retval 0 请求成功
        * @retval 非0 错误码
        * @operationtype 异步操作
        * @ingroup G_T_HisInfo
        */
        virtual ITapTrade::TAPIINT32 TAP_CDECL QryHisOrderProcess(ITapTrade::TAPIUINT32 *sessionID, const ITapTrade::TapAPIHisOrderProcessQryReq *qryReq) = 0;
        /**
        * @brief 历史成交查询请求
        * @param[out] sessionID 返回请求的会话ID;
        * @param[in]    Req    历史成交查询请求的结构体指针
        * @retval 0 请求成功
        * @retval 非0 错误码
        * @operationtype 异步操作
        * @ingroup G_T_HisInfo
        */
        virtual ITapTrade::TAPIINT32 TAP_CDECL QryHisMatch(ITapTrade::TAPIUINT32 *sessionID, const ITapTrade::TapAPIHisMatchQryReq *qryReq) = 0;
        /**
        * @brief 历史持仓查询请求
        * @param[out] sessionID 返回请求的会话ID;
        * @param[in]    Req    历史持仓查询请求的结构体指针
        * @retval 0 请求成功
        * @retval 非0 错误码
        * @operationtype 异步操作
        * @ingroup G_T_HisInfo
        */
        virtual ITapTrade::TAPIINT32 TAP_CDECL QryHisPosition(ITapTrade::TAPIUINT32 *sessionID, const ITapTrade::TapAPIHisPositionQryReq *qryReq) = 0;
        /**
        * @brief 历史交割查询请求
        * @param[out] sessionID 返回请求的会话ID;
        * @param[in]    Req    历史交割查询请求的结构体指针
        * @retval 0 请求成功
        * @retval 非0 错误码
        * @operationtype 异步操作
        * @ingroup G_T_HisInfo
        */
        virtual ITapTrade::TAPIINT32 TAP_CDECL QryHisDelivery(ITapTrade::TAPIUINT32 *sessionID, const ITapTrade::TapAPIHisDeliveryQryReq *qryReq) = 0;

        /**
        * @brief 客户手续费计算参数查询请求
        * @param[out] sessionID 返回请求的会话ID;
        * @param[in]    Req    客户手续费计算参数查询请求结构
        * @retval 0 请求成功
        * @retval 非0 错误码
        * @operationtype 异步操作
        * @ingroup G_T_Rent
        */
        virtual ITapTrade::TAPIINT32 TAP_CDECL QryAccountFeeRent(ITapTrade::TAPIUINT32 *sessionID, const ITapTrade::TapAPIAccountFeeRentQryReq *qryReq) = 0;
        /**
        * @brief 客户保证金计算参数查询请求
        * @param[out] sessionID 返回请求的会话ID;
        * @param[in]    Req    客户保证金计算参数查询请求结构
        * @retval 0 请求成功
        * @retval 非0 错误码
        * @operationtype 异步操作
        * @ingroup G_T_Rent
        */
        virtual ITapTrade::TAPIINT32 TAP_CDECL QryAccountMarginRent(ITapTrade::TAPIUINT32 *sessionID, const ITapTrade::TapAPIAccountMarginRentQryReq *qryReq) = 0;
        /**
        * @brief 港交所做市商双边报价指令
        * @param[out] sessionID 返回当前请求的SessionID;
        * @param[out] ClientBuyOrderNo返回港交所双边报价中买单的客户本地委托号;
        * @param[out] ClientSellOrderNo返回港交所双边报价中卖单的客户本地委托号;
        * @param[in] order双边报价请求结构;
        * @retval 0 请求成功
        * @retval 非0 错误码
        * @operationtype 异步操作
        * @ingroup G_T_HKMarket
        */
        virtual ITapTrade::TAPIINT32 TAP_CDECL InsertHKMarketOrder(TAPIUINT32 *sessionID, TAPISTR_50 *ClientBuyOrderNo, TAPISTR_50 *ClientSellOrderNo, const TapAPIOrderMarketInsertReq *order) = 0;

        /**
        * @brief 港交所做市商双边撤单指令
        * @param[out] sessionID 返回当前请求的sessionID。
        * @param[in] order 港交所做市商撤单指令请求结构。 
        * @retval 0 请求成功
        * @retval 非0 错误码
        * @operationtype 异步操作
        * @ingroup G_T_HKMarket
        */
        virtual ITapTrade::TAPIINT32 TAP_CDECL CancelHKMarketOrder(TAPIUINT32 *sessionID, const TapAPIOrderMarketDeleteReq *order) = 0;

        /**
        * @brief 订单删除指令
        * @param[out] sessionID 返回当前请求的sessionID。
        * @param[in] order 要订单删除的订单。
        * @retval 0 请求成功
        * @retval 非0 错误码
        * @operationtype 异步操作
        * @ingroup G_T_LocalActions
        */
        virtual ITapTrade::TAPIINT32 TAP_CDECL OrderLocalRemove(TAPIUINT32 *sessionID, const TapAPIOrderLocalRemoveReq *order) = 0;
        /**
        * @brief 订单录入指令
        * @param[out] sessionID 返回当前请求的sessionID。
        * @param[in] order 订单录入请求信息。
        * @retval 0 请求成功
        * @retval 非0 错误码
        * @operationtype 异步操作
        * @ingroup G_T_LocalActions
        */
        virtual  ITapTrade::TAPIINT32 TAP_CDECL OrderLocalInput(TAPIUINT32 *sessionID, const TapAPIOrderLocalInputReq *order) = 0;
        /**
        * @brief 订单修改指令
        * @param[out] sessionID 返回当前请求的sessionID。
        * @param[in] order 订单修改请求结构
        * @retval 0 请求成功
        * @retval 非0 错误码
        * @operationtype 异步操作
        * @ingroup G_T_LocalActions
        */
        virtual  ITapTrade::TAPIINT32 TAP_CDECL OrderLocalModify(TAPIUINT32 *sessionID, const TapAPIOrderLocalModifyReq *order) = 0;
        /**
        * @brief  订单转移指令
        * @param[out] sessionID 返回当前请求的sessionID。
        * @param[in] 订单转移请求信息。
        * @retval 0 请求成功
        * @retval 非0 错误码
        * @operationtype 异步操作
        * @ingroup G_T_LocalActions
        */
        virtual  ITapTrade::TAPIINT32 TAP_CDECL OrderLocalTransfer(TAPIUINT32 *sessionID, const TapAPIOrderLocalTransferReq *order) = 0;
        /**
        * @brief 成交录入指令
        * @param[out] sessionID 返回当前请求的sessionID。
        * @param[in] 要录入的成交信息
        * @retval 0 请求成功
        * @retval 非0 错误码
        * @operationtype 异步操作
        * @ingroup G_T_LocalActions
        */
        virtual ITapTrade::TAPIINT32 TAP_CDECL FillLocalInput(TAPIUINT32 *sessionID, const TapAPIFillLocalInputReq *fill) = 0;
        /**
        * @brief 成交删除指令
        * @param[out] sessionID 返回当前请求的sessionID。
        * @param[in] 成交删除请求信息
        * @retval 0 请求成功
        * @retval 非0 错误码
        * @operationtype 异步操作
        * @ingroup G_T_LocalActions
        */
        virtual ITapTrade::TAPIINT32 TAP_CDECL FillLocalRemove(TAPIUINT32 *sessionID, const TapAPIFillLocalRemoveReq *fill) = 0;
    };
};

    //-----------------------------TapTradeAPI导出函数------------------------------------


    #ifdef __cplusplus
    extern "C" {
    #endif // __cplusplus

    /**
    * @brief    创建TapTradeAPI的接口对象。
    * @details    创建整个交易API的接口
    * @param[in] appInfo 应用程序相关信息。
    * @param[in] iResult 创建接口的错误码。
    * @retval NULL    创建失败，具体原因可通过输出参数iResult判断。
    * @retval !NULL    实现了ITapTradeAPI接口的对象指针。
    * @ingroup G_T_API
    */
        TAP_DLLEXPORT ITapTrade::ITapTradeAPI *TAP_CDECL CreateITapTradeAPI(const ITapTrade::TapAPIApplicationInfo *appInfo, ITapTrade::TAPIINT32 &iResult);
    /**
    * @brief    销毁通过CreateTapTradeAPI函数创建的ITapTradeAPI对象。
    * @param[in] apiObj ITapTradeAPI对象指针。
    * @ingroup G_T_API
    */
        TAP_DLLEXPORT void TAP_CDECL FreeITapTradeAPI(ITapTrade::ITapTradeAPI *apiObj);
    /**
    * @brief    获取TapTradeAPI的版本信息
    * @ingroup G_T_API
    */
        TAP_DLLEXPORT const ITapTrade::TAPICHAR *TAP_CDECL GetITapTradeAPIVersion();
    /**
    * @brief    设置API自身保存数据目录
    * @details    调用函数的同时会在path描述的目录下打开以年月日（格式TapTradeAPI[YYYYMMDD].log)命名的文件，\n
    *            没有此文件的情况下会试图创建此文件。\n
    *            文件中保存的数据为API接收到的重要数据和API的使用和错误日志。
    * @param[in] path 目录。必须可用，目录符号Window下为”\\”或者”/”, Linux下为”/”。
    * @retval 0 成功
    * @retval 非0 错误码
    * @operationtype 同步操作
    * @ingroup G_T_LogConfig
    */
        TAP_DLLEXPORT ITapTrade::TAPIINT32 TAP_CDECL SetITapTradeAPIDataPath(const ITapTrade::TAPICHAR *path);
    /**
    * @brief    设置API的日志级别
    * @details    设定日志的输出级别，只有当实际日志级别与此处设定的级别相同或更高时，才会将日志写入SetTapTradeAPIDataPath()函数打开的日志文件。\n
    * @param[in]    level 日志级别：\n
    *                    APILOGLEVEL_NONE    ：不记录日志\n
    *                    APILOGLEVEL_ERROR    ：记录Error日志\n
    *                    APILOGLEVEL_WARNING    ：记录Error和Warning日志\n
    *                    APILOGLEVEL_DEBUG    ：记录Error、Warning和Debug日志\n
    * @retval 0 设定成功
    * @retval 非0 错误码
    * @operationtype 同步操作
    * @ingroup G_T_LogConfig
    */
        TAP_DLLEXPORT ITapTrade::TAPIINT32 TAP_CDECL SetITapTradeAPILogLevel(ITapTrade::TAPILOGLEVEL level);

        /**
        * @brief    根据错误码获取错误信息。在创建完API指针后即可调用，否则返回空值。
        * @details    根据错误码可以获取到对应的错误信息，
        * @param[in]    errorCode 错误码
        * @retval 返回错误描述信息
        * @operationtype 同步操作
        * @ingroup G_T_Error
        */

        TAP_DLLEXPORT const char  * TAP_CDECL GetITapErrorDescribe(ITapTrade::TAPIINT32 errorCode);

    #ifdef __cplusplus
    }
    #endif // __cplusplus


#endif // TAP_TRADE_API_H