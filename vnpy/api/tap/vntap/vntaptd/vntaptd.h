//系统
#ifdef WIN32
#include "stdafx.h"
#endif

#include "vntap.h"
#include "pybind11/pybind11.h"
#include "tap/iTapTradeAPI.h"


using namespace pybind11;
using namespace ITapTrade;

//常量
#define ONCONNECT 0
#define ONRSPLOGIN 1
#define ONRTNCONTACTINFO 2
#define ONRSPREQUESTVERTIFICATECODE 3
#define ONEXPRIATIONDATE 4
#define ONAPIREADY 5
#define ONDISCONNECT 6
#define ONRSPCHANGEPASSWORD 7
#define ONRSPAUTHPASSWORD 8
#define ONRSPQRYTRADINGDATE 9
#define ONRSPSETRESERVEDINFO 10
#define ONRSPQRYACCOUNT 11
#define ONRSPQRYFUND 12
#define ONRTNFUND 13
#define ONRSPQRYEXCHANGE 14
#define ONRSPQRYCOMMODITY 15
#define ONRSPQRYCONTRACT 16
#define ONRTNCONTRACT 17
#define ONRSPORDERACTION 18
#define ONRTNORDER 19
#define ONRSPQRYORDER 20
#define ONRSPQRYORDERPROCESS 21
#define ONRSPQRYFILL 22
#define ONRTNFILL 23
#define ONRSPQRYPOSITION 24
#define ONRTNPOSITION 25
#define ONRSPQRYPOSITIONSUMMARY 26
#define ONRTNPOSITIONSUMMARY 27
#define ONRTNPOSITIONPROFIT 28
#define ONRSPQRYCURRENCY 29
#define ONRSPQRYTRADEMESSAGE 30
#define ONRTNTRADEMESSAGE 31
#define ONRSPQRYHISORDER 32
#define ONRSPQRYHISORDERPROCESS 33
#define ONRSPQRYHISMATCH 34
#define ONRSPQRYHISPOSITION 35
#define ONRSPQRYHISDELIVERY 36
#define ONRSPQRYACCOUNTCASHADJUST 37
#define ONRSPQRYBILL 38
#define ONRSPQRYACCOUNTFEERENT 39
#define ONRSPQRYACCOUNTMARGINRENT 40
#define ONRSPHKMARKETORDERINSERT 41
#define ONRSPHKMARKETORDERDELETE 42
#define ONHKMARKETQUOTENOTICE 43
#define ONRSPORDERLOCALREMOVE 44
#define ONRSPORDERLOCALINPUT 45
#define ONRSPORDERLOCALMODIFY 46
#define ONRSPORDERLOCALTRANSFER 47
#define ONRSPFILLLOCALINPUT 48
#define ONRSPFILLLOCALREMOVE 49


///-------------------------------------------------------------------------------------
///C++ SPI的回调函数方法实现
///-------------------------------------------------------------------------------------

//API的继承实现
class TdApi : public ITapTradeAPINotify
{
private:
	ITapTradeAPI* api;            //API对象
    thread task_thread;                    //工作线程指针（向python中推送数据）
    TaskQueue task_queue;                //任务队列
    bool active = false;                //工作状态

public:
    TdApi()
    {
    };

    ~TdApi()
    {
        if (this->active)
        {
            this->exit();
        }
    };

    //-------------------------------------------------------------------------------------
    //API回调函数
    //-------------------------------------------------------------------------------------

		/**
		* @brief 连接成功回调通知
		* @ingroup G_T_Login
		*/
	virtual void OnConnect();
	/**
	* @brief    系统登录过程回调。
	* @details    此函数为Login()登录函数的回调，调用Login()成功后建立了链路连接，然后API将向服务器发送登录认证信息，
	*            登录期间的数据发送情况和登录的回馈信息传递到此回调函数中。
	* @param[in] errorCode 返回错误码,0表示成功。
	* @param[in] loginRspInfo 登陆应答信息，如果errorCode!=0，则loginRspInfo=NULL。
	* @attention    该回调返回成功，说明用户登录成功。但是不代表API准备完毕。
	* @ingroup G_T_Login
	*/
	virtual void OnRspLogin(int errorCode, TapAPITradeLoginRspInfo *loginRspInfo);
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
	virtual void OnRtnContactInfo(int errorCode, char isLast, string ContactInfo);

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
	virtual void OnRspRequestVertificateCode(unsigned int sessionID, int errorCode, TapAPIRequestVertificateCodeRsp *rsp);

	/**
	* @brief    API到期提醒回调
	* @details    此函数为Login()登录成功后，如果到期日与当前日期小于30天，则进行回调提醒。
	* @param[in] date 返回API授权到期日。
	* @param[in] days 返回还有几天授权到期。
	* @attention    该函数回调，则说明授权在一个月之内到期。否则不产生该回调。
	* @ingroup G_T_Login
	*/
	virtual void OnExpriationDate(string date, int days);

	/**
	* @brief    通知用户API准备就绪。
	* @details    只有用户回调收到此就绪通知时才能进行后续的各种行情数据查询操作。\n
	*            此回调函数是API能否正常工作的标志。
	* @attention 就绪后才可以进行后续正常操作
	* @ingroup G_T_Login
	*/
	virtual void OnAPIReady(int errorCode);
	/**
	* @brief    API和服务失去连接的回调
	* @details    在API使用过程中主动或者被动与服务器服务失去连接后都会触发此回调通知用户与服务器的连接已经断开。
	* @param[in] reasonCode 断开原因代码。
	* @ingroup G_T_Disconnect
	*/
	virtual void OnDisconnect(int reasonCode);
	/**
	* @brief 通知用户密码修改结果
	* @param[in] sessionID 修改密码的会话ID,和ChangePassword返回的会话ID对应。
	* @param[in] errorCode 返回错误码，0表示成功。
	* @ingroup G_T_UserInfo
	*/
	virtual void OnRspChangePassword(unsigned int sessionID, int errorCode);

	/**
	* @brief 认证账户密码反馈
	* @param[in] sessionID 修改密码的会话ID,和AuthPassword返回的会话ID对应。
	* @param[in] errorCode 返回错误码，0表示成功。
	* @ingroup G_T_UserInfo
	*/
	virtual void OnRspAuthPassword(unsigned int sessionID, int errorCode);

	/**
	* @brief    返回系统交易日期和当天LME到期日
	* @param[in] sessionID 请求的会话ID；
	* @param[in] errorCode 错误码。0 表示成功。
	* @param[in] info 指向返回的信息结构体。当errorCode不为0时，info为空。
	* @attention 不要修改和删除info所指示的数据；函数调用结束，参数不再有效。
	* @ingroup G_T_UserRight
	*/

	virtual void OnRspQryTradingDate(unsigned int sessionID, int errorCode, TapAPITradingCalendarQryRsp *info);
	/**
	* @brief 设置用户预留信息反馈
	* @param[in] sessionID 设置用户预留信息的会话ID
	* @param[in] errorCode 返回错误码，0表示成功。
	* @param[in] info 指向返回的信息结构体。当errorCode不为0时，info为空。
	* @attention 不要修改和删除info所指示的数据；函数调用结束，参数不再有效。
	* @note 该接口暂未实现
	* @ingroup G_T_UserInfo
	*/
	virtual void OnRspSetReservedInfo(unsigned int sessionID, int errorCode, string info);


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
	virtual void OnRspQryAccount(unsigned int sessionID, unsigned int errorCode, char isLast, TapAPIAccountInfo *info);
	/**
	* @brief 返回资金账户的资金信息
	* @param[in] sessionID 请求的会话ID；
	* @param[in] errorCode 错误码。0 表示成功。
	* @param[in] isLast     标示是否是最后一批数据；
	* @param[in] info        指向返回的信息结构体。当errorCode不为0时，info为空。
	* @attention 不要修改和删除info所指示的数据；函数调用结束，参数不再有效。
	* @ingroup G_T_AccountDetails
	*/
	virtual void OnRspQryFund(unsigned int sessionID, int errorCode, char isLast, TapAPIFundData *info);
	/**
	* @brief    用户资金变化通知
	* @details    用户的委托成交后会引起资金数据的变化，因此需要向用户实时反馈。
	* @param[in] info        指向返回的信息结构体。当errorCode不为0时，info为空。
	* @note 如果不关注此项内容，可以设定Login时的NoticeIgnoreFlag以屏蔽。
	* @attention 不要修改和删除info所指示的数据；函数调用结束，参数不再有效。
	* @ingroup G_T_AccountDetails
	*/
	virtual void OnRtnFund(TapAPIFundData *info);
	/**
	* @brief 返回系统中的交易所信息
	* @param[in] sessionID 请求的会话ID；
	* @param[in] errorCode 错误码。0 表示成功。
	* @param[in] isLast     标示是否是最后一批数据；
	* @param[in] info        指向返回的信息结构体。当errorCode不为0时，info为空。
	* @attention 不要修改和删除info所指示的数据；函数调用结束，参数不再有效。
	* @ingroup G_T_TradeSystem
	*/
	virtual void OnRspQryExchange(unsigned int sessionID, int errorCode, char isLast, TapAPIExchangeInfo *info);
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
	virtual void OnRspQryCommodity(unsigned int sessionID, int errorCode, char isLast, TapAPICommodityInfo *info);
	/**
	* @brief 返回系统中合约信息
	* @param[in] sessionID 请求的会话ID；
	* @param[in] errorCode 错误码。0 表示成功。
	* @param[in] isLast     标示是否是最后一批数据；
	* @param[in] info        指向返回的信息结构体。当errorCode不为0时，info为空。
	* @attention 不要修改和删除info所指示的数据；函数调用结束，参数不再有效。
	* @ingroup G_T_Contract
	*/
	virtual void OnRspQryContract(unsigned int sessionID, int errorCode, char isLast, TapAPITradeContractInfo *info);
	/**
	* @brief    返回新增合约信息
	* @details    向用户推送新的合约。主要用来处理在交易时间段中服务器添加了新合约时，向用户发送这个合约的信息。
	* @param[in] info        指向返回的信息结构体。当errorCode不为0时，info为空。
	* @attention 不要修改和删除info所指示的数据；函数调用结束，参数不再有效。
	* @ingroup G_T_Contract
	*/
	virtual void OnRtnContract(TapAPITradeContractInfo *info);
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
	virtual void OnRspOrderAction(unsigned int sessionID, int errorCode, TapAPIOrderActionRsp *info);
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
	virtual void OnRtnOrder(TapAPIOrderInfoNotice *info);
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
	virtual void OnRspQryOrder(unsigned int sessionID, int errorCode, char isLast, TapAPIOrderInfo *info);
	/**
	* @brief 返回查询的委托变化流程信息
	* @param[in] sessionID 请求的会话ID；
	* @param[in] errorCode 错误码，当errorCode==0时，info指向返回的委托变化流程结构体，不然为NULL；
	* @param[in] isLast 标示是否是最后一批数据；
	* @param[in] info 返回的委托变化流程指针。
	* @attention 不要修改和删除info所指示的数据；函数调用结束，参数不再有效。
	* @ingroup G_T_TradeInfo
	*/
	virtual void OnRspQryOrderProcess(unsigned int sessionID, int errorCode, char isLast, TapAPIOrderInfo *info);
	/**
	* @brief 返回查询的成交信息
	* @param[in] sessionID 请求的会话ID；
	* @param[in] errorCode 错误码。0 表示成功。
	* @param[in] isLast     标示是否是最后一批数据；
	* @param[in] info        指向返回的信息结构体。当errorCode不为0时，info为空。
	* @attention 不要修改和删除info所指示的数据；函数调用结束，参数不再有效。
	* @ingroup G_T_TradeInfo
	*/
	virtual void OnRspQryFill(unsigned int sessionID, int errorCode, char isLast, TapAPIFillInfo *info);
	/**
	* @brief    推送来的成交信息
	* @details    用户的委托成交后将向用户推送成交信息。
	* @param[in] info        指向返回的信息结构体。当errorCode不为0时，info为空。
	* @note 如果不关注此项内容，可以设定Login时的NoticeIgnoreFlag以屏蔽。
	* @attention 不要修改和删除info所指示的数据；函数调用结束，参数不再有效。
	* @ingroup G_T_TradeActions
	*/
	virtual void OnRtnFill(TapAPIFillInfo *info);
	/**
	* @brief 返回查询的持仓
	* @param[in] sessionID 请求的会话ID；
	* @param[in] errorCode 错误码。0 表示成功。
	* @param[in] isLast     标示是否是最后一批数据；
	* @param[in] info        指向返回的信息结构体。当errorCode不为0时，info为空。
	* @attention 不要修改和删除info所指示的数据；函数调用结束，参数不再有效。
	* @ingroup G_T_TradeInfo
	*/
	virtual void OnRspQryPosition(unsigned int sessionID, int errorCode, char isLast, TapAPIPositionInfo *info);
	/**
	* @brief 持仓变化推送通知
	* @param[in] info        指向返回的信息结构体。当errorCode不为0时，info为空。
	* @note 如果不关注此项内容，可以设定Login时的NoticeIgnoreFlag以屏蔽。
	* @attention 不要修改和删除info所指示的数据；函数调用结束，参数不再有效。
	* @ingroup G_T_TradeActions
	*/
	virtual void OnRtnPosition(TapAPIPositionInfo *info);
	/**
	* @brief 返回查询的持仓汇总
	* @param[in] sessionID 请求的会话ID；
	* @param[in] errorCode 错误码。0 表示成功。
	* @param[in] isLast     标示是否是最后一批数据；
	* @param[in] info        指向返回的信息结构体。当errorCode不为0时，info为空。
	* @attention 不要修改和删除info所指示的数据；函数调用结束，参数不再有效。
	* @ingroup G_T_TradeInfo
	*/
	virtual void OnRspQryPositionSummary(unsigned int sessionID, int errorCode, char isLast, TapAPIPositionSummary *info);

	/**
	* @brief 持仓汇总变化推送通知
	* @param[in] info        指向返回的信息结构体。当errorCode不为0时，info为空。
	* @note 如果不关注此项内容，可以设定Login时的NoticeIgnoreFlag以屏蔽。
	* @attention 不要修改和删除info所指示的数据；函数调用结束，参数不再有效。
	* @ingroup G_T_TradeActions
	*/
	virtual void OnRtnPositionSummary(TapAPIPositionSummary *info);
	/**
	* @brief 持仓盈亏通知
	* @param[in] info        指向返回的信息结构体。当errorCode不为0时，info为空。
	* @note 如果不关注此项内容，可以设定Login时的NoticeIgnoreFlag以屏蔽。
	* @attention 不要修改和删除info所指示的数据；函数调用结束，参数不再有效。
	* @ingroup G_T_TradeActions
	*/
	virtual void OnRtnPositionProfit(TapAPIPositionProfitNotice *info);


	/**
	* @brief 返回系统中的币种信息
	* @param[in] sessionID 请求的会话ID；
	* @param[in] errorCode 错误码。0 表示成功。
	* @param[in] isLast     标示是否是最后一批数据；
	* @param[in] info        指向返回的信息结构体。当errorCode不为0时，info为空。
	* @attention 不要修改和删除info所指示的数据；函数调用结束，参数不再有效。
	* @ingroup G_T_TradeSystem
	*/
	virtual void OnRspQryCurrency(unsigned int sessionID, int errorCode, char isLast, TapAPICurrencyInfo *info);

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
	virtual void OnRspQryTradeMessage(unsigned int sessionID, int errorCode, char isLast, TapAPITradeMessage *info);
	/**
	* @brief    交易消息通知
	* @details    用户在交易过程中可能因为资金、持仓、平仓的状态变动使账户处于某些危险状态，或者某些重要的信息需要向用户通知。
	* @param[in] info        指向返回的信息结构体。当errorCode不为0时，info为空。
	* @attention 不要修改和删除info所指示的数据；函数调用结束，参数不再有效。
	* @ingroup G_T_AccountDetails
	*/
	virtual void OnRtnTradeMessage(TapAPITradeMessage *info);
	/**
	* @brief 历史委托查询应答
	* @param[in] sessionID 请求的会话ID；
	* @param[in] errorCode 错误码。0 表示成功。
	* @param[in] isLast     标示是否是最后一批数据
	* @param[in] info        指向返回的信息结构体。当errorCode不为0时，info为空。
	* @attention 不要修改和删除info所指示的数据；函数调用结束，参数不再有效。
	* @ingroup G_T_HisInfo
	*/
	virtual void OnRspQryHisOrder(unsigned int sessionID, int errorCode, char isLast, TapAPIHisOrderQryRsp *info);
	/**
	* @brief 历史委托流程查询应答
	* @param[in] sessionID 请求的会话ID；
	* @param[in] errorCode 错误码。0 表示成功。
	* @param[in] isLast     标示是否是最后一批数据
	* @param[in] info        指向返回的信息结构体。当errorCode不为0时，info为空。
	* @attention 不要修改和删除info所指示的数据；函数调用结束，参数不再有效。
	* @ingroup G_T_HisInfo
	*/
	virtual void OnRspQryHisOrderProcess(unsigned int sessionID, int errorCode, char isLast, TapAPIHisOrderProcessQryRsp *info);
	/**
	* @brief 历史成交查询应答
	* @param[in] sessionID 请求的会话ID；
	* @param[in] errorCode 错误码。0 表示成功。
	* @param[in] isLast     标示是否是最后一批数据
	* @param[in] info        指向返回的信息结构体。当errorCode不为0时，info为空。
	* @attention 不要修改和删除info所指示的数据；函数调用结束，参数不再有效。
	* @ingroup G_T_HisInfo
	*/
	virtual void OnRspQryHisMatch(unsigned int sessionID, int errorCode, char isLast, TapAPIHisMatchQryRsp *info);
	/**
	* @brief 历史持仓查询应答
	* @param[in] sessionID 请求的会话ID；
	* @param[in] errorCode 错误码。0 表示成功。
	* @param[in] isLast     标示是否是最后一批数据
	* @param[in] info        指向返回的信息结构体。当errorCode不为0时，info为空。
	* @attention 不要修改和删除info所指示的数据；函数调用结束，参数不再有效。
	* @ingroup G_T_HisInfo
	*/
	virtual void OnRspQryHisPosition(unsigned int sessionID, int errorCode, char isLast, TapAPIHisPositionQryRsp *info);
	/**
	* @brief 历史交割查询应答
	* @param[in] sessionID 请求的会话ID；
	* @param[in] errorCode 错误码。0 表示成功。
	* @param[in] isLast     标示是否是最后一批数据
	* @param[in] info        指向返回的信息结构体。当errorCode不为0时，info为空。
	* @attention 不要修改和删除info所指示的数据；函数调用结束，参数不再有效。
	* @ingroup G_T_HisInfo
	*/
	virtual void OnRspQryHisDelivery(unsigned int sessionID, int errorCode, char isLast, TapAPIHisDeliveryQryRsp *info);
	/**
	* @brief 资金调整查询应答
	* @param[in] sessionID 请求的会话ID；
	* @param[in] errorCode 错误码。0 表示成功。
	* @param[in] isLast     标示是否是最后一批数据
	* @param[in] info        指向返回的信息结构体。当errorCode不为0时，info为空。
	* @attention 不要修改和删除info所指示的数据；函数调用结束，参数不再有效。
	* @ingroup G_T_HisInfo
	*/
	virtual void OnRspQryAccountCashAdjust(unsigned int sessionID, int errorCode, char isLast, TapAPIAccountCashAdjustQryRsp *info);
	/**
	* @brief 查询用户账单应答 Add:2013.12.11
	* @param[in] sessionID 请求的会话ID；
	* @param[in] errorCode 错误码。0 表示成功。
	* @param[in] info        指向返回的信息结构体。当errorCode不为0时，info为空。
	* @attention 不要修改和删除info所指示的数据；函数调用结束，参数不再有效。
	* @ingroup G_T_Bill
	*/
	virtual void OnRspQryBill(unsigned int sessionID, int errorCode, char isLast, TapAPIBillQryRsp *info);
	/**
	* @brief 查询账户手续费计算参数 Add:2017.01.14
	* @param[in] sessionID 请求的会话ID；
	* @param[in] errorCode 错误码。0 表示成功。
	* @param[in] info        指向返回的信息结构体。当errorCode不为0时，info为空。
	* @attention 不要修改和删除info所指示的数据；函数调用结束，参数不再有效。
	* @ingroup G_T_Rent
	*/
	virtual void OnRspQryAccountFeeRent(unsigned int sessionID, int errorCode, char isLast, TapAPIAccountFeeRentQryRsp *info);
	/**
	* @brief 查询账户保证金计算参数 Add:2017.01.14
	* @param[in] sessionID 请求的会话ID；
	* @param[in] errorCode 错误码。0 表示成功。
	* @param[in] info        指向返回的信息结构体。当errorCode不为0时，info为空。
	* @attention 不要修改和删除info所指示的数据；函数调用结束，参数不再有效。
	* @ingroup G_T_Rent
	*/
	virtual void OnRspQryAccountMarginRent(unsigned int sessionID, int errorCode, char isLast, TapAPIAccountMarginRentQryRsp *info);

	/**
	* @brief 港交所做市商双边报价应答 Add:2017.08.29
	* @param[in] sessionID 请求的会话ID；
	* @param[in] errorCode 错误码。0 表示成功。
	* @param[in] info        指向返回的信息结构体。当errorCode不为0时，info为空。
	* @attention 不要修改和删除info所指示的数据；函数调用结束，参数不再有效。
	* @ingroup G_T_HKMarket
	*/
	virtual void OnRspHKMarketOrderInsert(unsigned int sessionID, int errorCode, TapAPIOrderMarketInsertRsp *info);

	/**
	* @brief 港交所做市商双边撤单应答 Add:2017.08.29
	* @param[in] sessionID 请求的会话ID；
	* @param[in] errorCode 错误码。0 表示成功。
	* @param[in] info        指向返回的信息结构体。当errorCode不为0时，info为空。
	* @attention 不要修改和删除info所指示的数据；函数调用结束，参数不再有效。
	* @ingroup G_T_HKMarket
	*/
	virtual void OnRspHKMarketOrderDelete(unsigned int sessionID, int errorCode, TapAPIOrderMarketDeleteRsp *info);

	/**
	* @brief 港交所询价通知 Add:2017.08.29
	* @param[in] info        指向返回的信息结构体。当errorCode不为0时，info为空。
	* @attention 不要修改和删除info所指示的数据；函数调用结束，参数不再有效。
	* @ingroup G_T_HKMarket
	*/
	virtual void OnHKMarketQuoteNotice(TapAPIOrderQuoteMarketNotice *info);


	/**
	* @brief 订单删除应答 Add:2017.12.05
	* @param[in] sessionID 请求的会话ID；
	* @param[in] errorCode 错误码。0 表示成功。
	* @param[in] info        指向返回的信息结构体。当errorCode不为0时，info为空。
	* @attention 不要修改和删除info所指示的数据；函数调用结束，参数不再有效。
	* @ingroup G_T_LocalAction
	*/
	virtual void OnRspOrderLocalRemove(unsigned int sessionID, int errorCode, TapAPIOrderLocalRemoveRsp *info);

	/**
	* @brief 订单录入应答 Add:2017.12.05
	* @param[in] sessionID 请求的会话ID；
	* @param[in] errorCode 错误码。0 表示成功。
	* @param[in] info        指向返回的信息结构体。当errorCode不为0时，info为空。
	* @attention 不要修改和删除info所指示的数据；函数调用结束，参数不再有效。
	* @ingroup G_T_LocalAction
	*/
	virtual void OnRspOrderLocalInput(unsigned int sessionID, int errorCode, TapAPIOrderLocalInputRsp *info);

	/**
	* @brief 订单修改应答 Add:2017.12.05
	* @param[in] sessionID 请求的会话ID；
	* @param[in] errorCode 错误码。0 表示成功。
	* @param[in] info        指向返回的信息结构体。当errorCode不为0时，info为空。
	* @attention 不要修改和删除info所指示的数据；函数调用结束，参数不再有效。
	* @ingroup G_T_LocalAction
	*/
	virtual void OnRspOrderLocalModify(unsigned int sessionID, int errorCode, TapAPIOrderLocalModifyRsp *info);

	/**
	* @brief 订单转移应答 Add:2017.12.05
	* @param[in] sessionID 请求的会话ID；
	* @param[in] errorCode 错误码。0 表示成功。
	* @param[in] info        指向返回的信息结构体。当errorCode不为0时，info为空。
	* @attention 不要修改和删除info所指示的数据；函数调用结束，参数不再有效。
	* @ingroup G_T_LocalAction
	*/
	virtual void OnRspOrderLocalTransfer(unsigned int sessionID, int errorCode, TapAPIOrderLocalTransferRsp *info);

	/**
	* @brief 成交录入应答 Add:2017.12.05
	* @param[in] sessionID 请求的会话ID；
	* @param[in] errorCode 错误码。0 表示成功。
	* @param[in] info        指向返回的信息结构体。当errorCode不为0时，info为空。
	* @attention 不要修改和删除info所指示的数据；函数调用结束，参数不再有效。
	* @ingroup G_T_LocalAction
	*/
	virtual void OnRspFillLocalInput(unsigned int sessionID, int errorCode, TapAPIFillLocalInputRsp *info);

	/**
	* @brief 订单删除应答 Add:2017.12.05
	* @param[in] sessionID 请求的会话ID；
	* @param[in] errorCode 错误码。0 表示成功。
	* @param[in] info        指向返回的信息结构体。当errorCode不为0时，info为空。
	* @attention 不要修改和删除info所指示的数据；函数调用结束，参数不再有效。
	* @ingroup G_T_LocalAction
	*/
	virtual void OnRspFillLocalRemove(unsigned int sessionID, int errorCode, TapAPIFillLocalRemoveRsp *info);



    //-------------------------------------------------------------------------------------
    //task：任务
    //-------------------------------------------------------------------------------------

	void processTask();

	void processConnect(Task *task);

	void processRspLogin(Task *task);

	void processRtnContactInfo(Task *task);

	void processRspRequestVertificateCode(Task *task);

	void processExpriationDate(Task *task);

	void processAPIReady(Task *task);

	void processDisconnect(Task *task);

	void processRspChangePassword(Task *task);

	void processRspAuthPassword(Task *task);

	void processRspQryTradingDate(Task *task);

	void processRspSetReservedInfo(Task *task);

	void processRspQryAccount(Task *task);

	void processRspQryFund(Task *task);

	void processRtnFund(Task *task);

	void processRspQryExchange(Task *task);

	void processRspQryCommodity(Task *task);

	void processRspQryContract(Task *task);

	void processRtnContract(Task *task);

	void processRspOrderAction(Task *task);

	void processRtnOrder(Task *task);

	void processRspQryOrder(Task *task);

	void processRspQryOrderProcess(Task *task);

	void processRspQryFill(Task *task);

	void processRtnFill(Task *task);

	void processRspQryPosition(Task *task);

	void processRtnPosition(Task *task);

	void processRspQryPositionSummary(Task *task);

	void processRtnPositionSummary(Task *task);

	void processRtnPositionProfit(Task *task);

	void processRspQryCurrency(Task *task);

	void processRspQryTradeMessage(Task *task);

	void processRtnTradeMessage(Task *task);

	void processRspQryHisOrder(Task *task);

	void processRspQryHisOrderProcess(Task *task);

	void processRspQryHisMatch(Task *task);

	void processRspQryHisPosition(Task *task);

	void processRspQryHisDelivery(Task *task);

	void processRspQryAccountCashAdjust(Task *task);

	void processRspQryBill(Task *task);

	void processRspQryAccountFeeRent(Task *task);

	void processRspQryAccountMarginRent(Task *task);

	void processRspHKMarketOrderInsert(Task *task);

	void processRspHKMarketOrderDelete(Task *task);

	void processHKMarketQuoteNotice(Task *task);

	void processRspOrderLocalRemove(Task *task);

	void processRspOrderLocalInput(Task *task);

	void processRspOrderLocalModify(Task *task);

	void processRspOrderLocalTransfer(Task *task);

	void processRspFillLocalInput(Task *task);

	void processRspFillLocalRemove(Task *task);



    //-------------------------------------------------------------------------------------
    //data：回调函数的数据字典
    //error：回调函数的错误字典
    //id：请求id
    //last：是否为最后返回
    //i：整数
    //-------------------------------------------------------------------------------------
    
	virtual void onConnect() {};

	virtual void onRspLogin(int error, const dict &data) {};

	virtual void onRtnContactInfo(int error, char last, string ContactInfo) {};

	virtual void onRspRequestVertificateCode(unsigned int session, int error, const dict &data) {};

	virtual void onExpriationDate(string date, int days) {};

	virtual void onAPIReady(int error) {};

	virtual void onDisconnect(int reason) {};

	virtual void onRspChangePassword(unsigned int session, int error) {};

	virtual void onRspAuthPassword(unsigned int session, int error) {};

	virtual void onRspQryTradingDate(unsigned int session, int error, const dict &data) {};

	virtual void onRspSetReservedInfo(unsigned int session, int error, string info) {};

	virtual void onRspQryAccount(unsigned int session, int error, char last, const dict &data) {};

	virtual void onRspQryFund(unsigned int session, int error, char last, const dict &data) {};

	virtual void onRtnFund(const dict &data) {};

	virtual void onRspQryExchange(unsigned int session, int error, char last, const dict &data) {};

	virtual void onRspQryCommodity(unsigned int session, int error, char last, const dict &data) {};

	virtual void onRspQryContract(unsigned int session, int error, char last, const dict &data) {};

	virtual void onRtnContract(const dict &data) {};

	virtual void onRspOrderAction(unsigned int session, int error, const dict &data) {};

	virtual void onRtnOrder(const dict &data) {};

	virtual void onRspQryOrder(unsigned int session, int error, char last, const dict &data) {};

	virtual void onRspQryOrderProcess(unsigned int session, int error, char last, const dict &data) {};

	virtual void onRspQryFill(unsigned int session, int error, char last, const dict &data) {};

	virtual void onRtnFill(const dict &data) {};

	virtual void onRspQryPosition(unsigned int session, int error, char last, const dict &data) {};

	virtual void onRtnPosition(const dict &data) {};

	virtual void onRspQryPositionSummary(unsigned int session, int error, char last, const dict &data) {};

	virtual void onRtnPositionSummary(const dict &data) {};

	virtual void onRtnPositionProfit(const dict &data) {};

	virtual void onRspQryCurrency(unsigned int session, int error, char last, const dict &data) {};

	virtual void onRspQryTradeMessage(unsigned int session, int error, char last, const dict &data) {};

	virtual void onRtnTradeMessage(const dict &data) {};

	virtual void onRspQryHisOrder(unsigned int session, int error, char last, const dict &data) {};

	virtual void onRspQryHisOrderProcess(unsigned int session, int error, char last, const dict &data) {};

	virtual void onRspQryHisMatch(unsigned int session, int error, char last, const dict &data) {};

	virtual void onRspQryHisPosition(unsigned int session, int error, char last, const dict &data) {};

	virtual void onRspQryHisDelivery(unsigned int session, int error, char last, const dict &data) {};

	virtual void onRspQryAccountCashAdjust(unsigned int session, int error, char last, const dict &data) {};

	virtual void onRspQryBill(unsigned int session, int error, char last, const dict &data) {};

	virtual void onRspQryAccountFeeRent(unsigned int session, int error, char last, const dict &data) {};

	virtual void onRspQryAccountMarginRent(unsigned int session, int error, char last, const dict &data) {};

	virtual void onRspHKMarketOrderInsert(unsigned int session, int error, const dict &data) {};

	virtual void onRspHKMarketOrderDelete(unsigned int session, int error, const dict &data) {};

	virtual void onHKMarketQuoteNotice(const dict &data) {};

	virtual void onRspOrderLocalRemove(unsigned int session, int error, const dict &data) {};

	virtual void onRspOrderLocalInput(unsigned int session, int error, const dict &data) {};

	virtual void onRspOrderLocalModify(unsigned int session, int error, const dict &data) {};

	virtual void onRspOrderLocalTransfer(unsigned int session, int error, const dict &data) {};

	virtual void onRspFillLocalInput(unsigned int session, int error, const dict &data) {};

	virtual void onRspFillLocalRemove(unsigned int session, int error, const dict &data) {};



    //-------------------------------------------------------------------------------------
    //req:主动函数的请求字典
    //-------------------------------------------------------------------------------------
	void CreateITapTradeAPI(const dict &req, int &iResult);

	void release();

	void init();

	int exit();

	string getITapTradeAPIVersion();

	int setTapQuoteAPIDataPath(string path);

	int setTapQuoteAPILogLevel(string level);


	int setAPINotify(ITapTradeAPINotify *pSpi); //1





	int setHostAddress(TAPICHAR *IP, TAPIUINT16 port, bool bSSL = false); //2

	int login(TapAPITradeLoginAuth *loginAuth); //3

	int requestVertificateCode(unsigned int *sessionID, string ContactInfo); //4

	int setVertificateCode(TAPISTR_10 VertificateCode); //5

	int disconnect();

	int changePassword(unsigned int *sessionID, TapAPIChangePasswordReq *req);

	int authPassword(unsigned int *sessionID, TapAPIAuthPasswordReq *req); //6

	int haveCertainRight(TAPIRightIDType rightID);

	int setReservedInfo(unsigned int *sessionID, string info);

	int insertOrder(unsigned int *sessionID, string *ClientOrderNo, TapAPINewOrder *order); //7

	int cancelOrder(unsigned int *sessionID, TapAPIOrderCancelReq *order); //8

	int amendOrder(unsigned int *sessionID, TapAPIAmendOrder *order); //9

	int activateOrder(unsigned int * sessionID, TapAPIOrderActivateReq * order);

	int insertHKMarketOrder(unsigned int *sessionID, string *ClientBuyOrderNo, string *ClientSellOrderNo, TapAPIOrderMarketInsertReq *order);

	int cancelHKMarketOrder(unsigned int *sessionID, TapAPIOrderMarketDeleteReq *order);

	int orderLocalRemove(unsigned int *sessionID, TapAPIOrderLocalRemoveReq *order);

	int orderLocalInput(unsigned int *sessionID, TapAPIOrderLocalInputReq *order);

	int orderLocalModify(unsigned int *sessionID, TapAPIOrderLocalModifyReq *order);

	int orderLocalTransfer(unsigned int *sessionID, TapAPIOrderLocalTransferReq *order);

	int fillLocalInput(unsigned int *sessionID, TapAPIFillLocalInputReq *fill);

	int fillLocalRemove(unsigned int *sessionID, TapAPIFillLocalRemoveReq *fill);



	int qryTradingDate(unsigned int session);

	int qryAccount(unsigned int *session, const dict &data);

	int qryFund(unsigned int *session, const dict &data);

	int qryExchange(unsigned int *session);

	int qryCommodity(unsigned int *session);

	int qryContract(unsigned int *session, const dict &data);

	int qryOrder(unsigned int *session, const dict &data);

	int qryOrderProcess(unsigned int *session, const dict &data);

	int qryFill(unsigned int *session, const dict &data);

	int qryPosition(unsigned int *session, const dict &data);

	int qryPositionSummary(unsigned int *session, const dict &data);

	int qryCurrency(unsigned int *session);

	int qryAccountCashAdjust(unsigned int *session, const dict &data);

	int qryTradeMessage(unsigned int *session, const dict &data);

	int qryBill(unsigned int *session, const dict &data);

	int qryHisOrder(unsigned int *session, const dict &data);

	int qryHisOrderProcess(unsigned int *session, const dict &data);

	int qryHisMatch(unsigned int *session, const dict &data);

	int qryHisPosition(unsigned int *session, const dict &data);

	int qryHisDelivery(unsigned int *session, const dict &data);

	int qryAccountFeeRent(unsigned int *session, const dict &data);

	int qryAccountMarginRent(unsigned int *session, const dict &data);


};
