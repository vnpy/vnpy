#ifndef TAP_QUOTE_API_H
#define TAP_QUOTE_API_H

#include "TapQuoteAPIDataType.h"

#ifdef _WIN32
#define TAP_CDECL  __cdecl
#define TAP_DLLEXPORT __declspec(dllexport)
#else
#define TAP_CDECL
#define TAP_DLLEXPORT
#endif

//TapQuoteAPI.h
//文件定义了TapQuoteAPI提供给开发者的对外接口、函数和回调接口。

//TapQuoteAPI 的回调通知接口。
class ITapQuoteAPINotify
{
public:
	/**
	* @brief	系统登录过程回调。
	* @details	此函数为Login()登录函数的回调，调用Login()成功后建立了链路连接，然后API将向服务器发送登录认证信息，
	*			登录期间的数据发送情况和登录的回馈信息传递到此回调函数中。
	* @param[in] errorCode 返回错误码,0表示成功。
	* @param[in] info 登陆应答信息，如果errorCode!=0，则info=NULL。
	* @attention	该回调返回成功，说明用户登录成功。但是不代表API准备完毕。需要等到OnAPIReady才能进行查询与订阅请求。
	* @ingroup G_Q_Login
	*/
	virtual void TAP_CDECL OnRspLogin(TAPIINT32 errorCode, const TapAPIQuotLoginRspInfo *info) = 0;
	/**
	* @brief	通知用户API准备就绪。
	* @details	只有用户回调收到此就绪通知时才能进行后续的各种行情数据查询操作。\n
	*			此回调函数是API能否正常工作的标志。
	* @attention  就绪后才可以进行后续正常操作
	* @ingroup G_Q_Login
	*/
	virtual void TAP_CDECL OnAPIReady() = 0;
	/**
	* @brief	API和服务失去连接的回调
	* @details	在API使用过程中主动或者被动与服务器服务失去连接后都会触发此回调通知用户与服务器的连接已经断开。
	* @param[in] reasonCode 断开原因代码。具体原因请参见错误码列表 \n
	* @ingroup G_Q_Disconnect
	*/
	virtual void TAP_CDECL OnDisconnect(TAPIINT32 reasonCode) = 0;
	/**
	* @brief	返回所有品种信息。
	* @details	此回调接口用于向用户返回得到的所有品种信息。
	* @param[in] sessionID 请求的会话ID
	* @param[in] errorCode 错误码，当errorCode!=0时,info为NULL；
	* @param[in] isLast 标示是否是最后一批数据；
	* @param[in] info 返回的信息数组的起始指针。
	* @attention  不要修改和删除info所指示的数据；函数调用结束，参数不再有效。
	* @ingroup G_Q_Commodity
	*/
	virtual void TAP_CDECL OnRspQryCommodity(TAPIUINT32 sessionID, TAPIINT32 errorCode, TAPIYNFLAG isLast, const TapAPIQuoteCommodityInfo *info) = 0;
	/**
	* @brief 返回系统中合约信息
	* @param[in] sessionID 请求的会话ID；
	* @param[in] errorCode 错误码，当errorCode!=0时,info为NULL；
	* @param[in] isLast 标示是否是最后一批数据；
	* @param[in] info		指向返回的信息结构体。当errorCode不为0时，info为空。
	* @attention 不要修改和删除info所指示的数据；函数调用结束，参数不再有效。
	* @ingroup G_Q_Contract
	*/
	virtual void TAP_CDECL OnRspQryContract(TAPIUINT32 sessionID, TAPIINT32 errorCode, TAPIYNFLAG isLast, const TapAPIQuoteContractInfo *info) = 0;
	/**
	* @brief	返回订阅行情的全文。
	* @details	此回调接口用来返回订阅行情的全文。全文为当前时间的行情信息。
	* @param[in] sessionID 请求的会话ID；
	* @param[in] isLast 标示是否是最后一批数据；
	* @param[in] errorCode 错误码，当errorCode!=0时,info为NULL；
	* @param[in] info		指向返回的信息结构体。当errorCode不为0时，info为空。
	* @attention  不要修改和删除info所指示的数据；函数调用结束，参数不再有效。
	* @ingroup G_Q_Quote
	*/
	virtual void TAP_CDECL OnRspSubscribeQuote(TAPIUINT32 sessionID, TAPIINT32 errorCode, TAPIYNFLAG isLast, const TapAPIQuoteWhole *info) = 0;
	/**
	* @brief 退订指定合约的行情的结果回调
	* @param[in] sessionID 请求的会话ID；
	* @param[in] errorCode 错误码，当errorCode!=0时,info为NULL；
	* @param[in] isLast 标示是否是最后一批数据；
	* @param[in] info		指向返回的信息结构体。当errorCode不为0时，info为空。
	* @attention  不要修改和删除info所指示的数据；函数调用结束，参数不再有效。
	* @ingroup G_Q_Quote
	*/
	virtual void TAP_CDECL OnRspUnSubscribeQuote(TAPIUINT32 sessionID, TAPIINT32 errorCode, TAPIYNFLAG isLast, const TapAPIContract *info) = 0;
	/**
	* @brief	返回订阅行情的变化内容。
	* @details	此回调接口用来通知用户行情信息产生了变化，并向用户提交新的行情全文。
	* @param[in] info 最新的行情全文内容
	* @attention 不要修改和删除Quote指示的数据；函数调用结束，参数不再有效。
	* @ingroup G_Q_Quote
	*/
	virtual void TAP_CDECL OnRtnQuote(const TapAPIQuoteWhole *info) = 0;
};

//TapQuoteAPI 对外功能接口。包含了用户可以调用的功能函数。
class ITapQuoteAPI
{
public:
	/**
	* @brief	设置API的回调接口对象。
	* @details	系统对API的通知将通过设置的回调对象通知给使用者。
	*			ITapQuoteAPINofify是API的回调接口，用户需要继承实现此接口类对象来完成用户需要的功能。
	*			如果用户没有设置回调接口，则API不会向用户返回任何有用的信息。\n
	*			ITapQuoteAPINotify类的详细内容请查看TapQuoteAPI.h 文件。
	* @param[in] apiNotify 实现了ITapQuoteAPINotify接口的对象指针。
	* @operationtype 同步操作
	* @ingroup G_Q_Login
	*/
	virtual TAPIINT32 TAP_CDECL SetAPINotify(ITapQuoteAPINotify *apiNotify) = 0;
	/**
	* @brief 设置服务器的IP地址和端口。等到调用Login时真正发起连接。
	* @param[in] IP   IP地址
	* @param[in] port 端口号
	* @operationtype 同步操作
	* @ingroup G_Q_Login
	*/
	virtual TAPIINT32 TAP_CDECL SetHostAddress(const TAPICHAR *IP, TAPIUINT16 port) = 0;
	/**
	* @brief	发起登录请求。API将先连接服务，建立链路，发起登录认证。
	* @details	在使用函数函数前用户需要完成服务器的设置SetHostAddress()，并且创建TapAPIQuoteLoginAuth类型的用户信息，
	*			并且需要设置好回调接口。\n
	*			连接建立后的用户验证回馈信息通过回调OnLogin()返回给用户。\n
	*			登录成功后API会自动进行API的初始化，API向服务器请求基础数据，查询完以后会通过回调OnAPIReady()
	*			指示用户API初始化完成，可以进行后续的操作了。
	* @param[in] loginAuth 登录验证信息结构指针。包含登录需要的验证信息。
	* @retval 0 登录成功，API开始准备后台数据
	* @retval 非0 错误码
	* @attention 登录成功与否要根据OnLogin回调判断。
	* @operationtype 异步操作
	* @warning	Login()函数调用成功只是代表于服务器建立了链路连接，只有回调OnLogin()的返回能指示用户是否成功登录了。
	* @ingroup G_Q_Login
	*/
	virtual TAPIINT32 TAP_CDECL Login(const TapAPIQuoteLoginAuth *loginAuth) = 0;
	/**
	* @brief	断开和服务器的链路连接。
	* @details	调用函数后API将登出并断开与服务器的连接。
	* @operationtype 异步操作
	* @ingroup G_Q_Disconnect
	*/
	virtual TAPIINT32 TAP_CDECL Disconnect() = 0;
	/**
	* @brief 得到所有品种
	* @param[out] sessionID 返回请求的会话ID。
	* @retval 0 请求成功
	* @retval 非0 错误码
	* @operationtype 异步操作
	* @ingroup G_Q_Commodity
	*/
	virtual TAPIINT32 TAP_CDECL QryCommodity(TAPIUINT32 *sessionID) = 0;
	/**
	* @brief	查询系统中指定品种的合约信息
	* @details	使用此函数前需要先QryCommodity()取得品种信息，
	*			然后选择需要的品种将信息填入TapAPICommodity结构体中完成查询请求。
	* @param[out] sessionID 返回请求的会话ID;
	* @param[in] qryReq 查询系统中指定品种的合约信息请求的结构体指针;\n
	*				    该参数各字段为可选字段，可以用以下方法查询：\n
	*					1.全部留空：查所有合约\n
	*					2.仅交易所编码有效：查该交易所下所有品种的合约\n
	*					3.交易所编码和品种类型有效：查该交易所下指定品种类型的合约\n
	*					4.交易所编码、品种类型和品种编码都有效：查该品种下的所有合约
	* @retval 0 请求成功
	* @retval 非0 错误码
	* @operationtype 异步操作
	* @ingroup G_Q_Contract
	*/
	virtual TAPIINT32 TAP_CDECL QryContract(TAPIUINT32 *sessionID, const TapAPICommodity *qryReq) = 0;
	/**
	* @brief	订阅指定合约的行情
	* @details	函数向服务器请求contract描述的合约的行情信息，行情订阅成功后服务器将持续向用户推送行情信息，
	*			直到用户退订行情信息或者断开于服务器的通信。\n
	*			调用此函数前先获取合约信息，然后从合约信息中取出合约填入contract。\n
	* @param[out] sessionID 返回请求的会话ID。
	* @param[in] contract 指定合约。
	* @retval 0 请求成功
	* @retval 非0 错误码
	* @operationtype 异步操作
	* @ingroup G_Q_Quote
	*/
	virtual TAPIINT32 TAP_CDECL SubscribeQuote(TAPIUINT32 *sessionID, const TapAPIContract *contract) = 0;
	/**
	* @brief	退订指定合约的行情
	* @details	退订已经订阅的行情信息。
	* @param[out] sessionID 返回请求的会话ID；
	* @param[in]	contract 指定合约。
	* @retval 0 请求成功
	* @retval 非0 错误码
	* @operationtype 异步操作
	* @ingroup G_Q_Quote
	*/
	virtual TAPIINT32 TAP_CDECL UnSubscribeQuote(TAPIUINT32 *sessionID, const TapAPIContract *contract) = 0;
};

//-----------------------------TapQuoteAPI导出函数------------------------------------


#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

/**
* @brief	创建TapQuoteAPI的接口对象。
* @details	创建整个行情API的接口
* @param[in] appInfo 应用程序相关信息。
* @param[in] iResult 创建接口的错误码。
* @retval NULL	创建失败。
* @retval !NULL	实现了ITapQuoteAPI接口的对象指针。
* @ingroup G_Q_API
*/
TAP_DLLEXPORT ITapQuoteAPI *TAP_CDECL CreateTapQuoteAPI(const TapAPIApplicationInfo *appInfo, TAPIINT32 &iResult);
/**
* @brief	销毁通过CreateTapQuoteAPI函数创建的ITapQuoteAPI对象。
* @param[in] apiObj ITapQuoteAPI对象指针。
* @ingroup G_Q_API
*/
TAP_DLLEXPORT void TAP_CDECL FreeTapQuoteAPI(ITapQuoteAPI *apiObj);
/**
* @brief	获取TapQuoteAPI的版本信息
* @ingroup G_Q_API
*/
TAP_DLLEXPORT const TAPICHAR *TAP_CDECL GetTapQuoteAPIVersion();
/**
* @brief	设置API自身保存数据目录
* @details	调用函数的同时会在path描述的目录下打开以年月日（格式TapQuoteAPI[YYYYMMDD].log)命名的文件，\n
*			没有此文件的情况下会试图创建此文件。\n
*			文件中保存的数据为API接收到的重要数据和API的使用和错误日志。
* @param[in] path 目录。必须可用，目录符号Window下为”\\”或者”/”, Linux下为”/”。
* @retval 0 成功
* @retval 非0 错误码
* @operationtype 同步操作
* @ingroup G_Q_LogConfig
*/
TAP_DLLEXPORT TAPIINT32 TAP_CDECL SetTapQuoteAPIDataPath(const TAPICHAR *path);
/**
* @brief	设置API的日志级别
* @details	设定日志的输出级别，只有当实际日志级别与此处设定的级别相同或更高时，才会将日志写入SetTapQuoteAPIDataPath()函数打开的日志文件。\n
* @param[in]	level 日志级别：\n
*					APILOGLEVEL_NONE	：不记录日志\n
*					APILOGLEVEL_ERROR	：记录Error日志\n
*					APILOGLEVEL_WARNING	：记录Error和Warning日志\n
*					APILOGLEVEL_DEBUG	：记录Error、Warning和Debug日志\n
* @retval 0 设定成功
* @retval 非0 错误码
* @operationtype 同步操作
* @ingroup G_Q_LogConfig
*/
TAP_DLLEXPORT TAPIINT32 TAP_CDECL SetTapQuoteAPILogLevel(TAPILOGLEVEL level);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // TAP_QUOTE_API_H