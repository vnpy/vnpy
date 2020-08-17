//系统
#ifdef WIN32
#include "pch.h"
#endif

#include "vnes.h"
#include "pybind11/pybind11.h"
#include "es/TapQuoteAPI.h"


using namespace pybind11;

//常量
#define ONRSPLOGIN 0
#define ONAPIREADY 1
#define ONDISCONNECT 2
#define ONRSPQRYCOMMODITY 3
#define ONRSPQRYCONTRACT 4
#define ONRSPSUBSCRIBEQUOTE 5
#define ONRSPUNSUBSCRIBEQUOTE 6
#define ONRTNQUOTE 7


///-------------------------------------------------------------------------------------
///C++ SPI的回调函数方法实现
///-------------------------------------------------------------------------------------

//API的继承实现
class MdApi : public ITapQuoteAPINotify
{
private:
	ITapQuoteAPI* api;				//API对象
	thread task_thread;					//工作线程指针（向python中推送数据）
	TaskQueue task_queue;			    //任务队列
	bool active = false;				//工作状态

public:
	MdApi()
	{
	};

	~MdApi()
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
	* @brief	系统登录过程回调。
	* @details	此函数为Login()登录函数的回调，调用Login()成功后建立了链路连接，然后API将向服务器发送登录认证信息，
	*			登录期间的数据发送情况和登录的回馈信息传递到此回调函数中。
	* @param[in] errorCode 返回错误码,0表示成功。
	* @param[in] info 登陆应答信息，如果errorCode!=0，则info=NULL。
	* @attention	该回调返回成功，说明用户登录成功。但是不代表API准备完毕。需要等到OnAPIReady才能进行查询与订阅请求。
	* @ingroup G_Q_Login
	*/
	virtual void TAP_CDECL OnRspLogin(TAPIINT32 errorCode, const TapAPIQuotLoginRspInfo *info);
	/**
	* @brief	通知用户API准备就绪。
	* @details	只有用户回调收到此就绪通知时才能进行后续的各种行情数据查询操作。\n
	*			此回调函数是API能否正常工作的标志。
	* @attention  就绪后才可以进行后续正常操作
	* @ingroup G_Q_Login
	*/
	virtual void TAP_CDECL OnAPIReady();
	/**
	* @brief	API和服务失去连接的回调
	* @details	在API使用过程中主动或者被动与服务器服务失去连接后都会触发此回调通知用户与服务器的连接已经断开。
	* @param[in] reasonCode 断开原因代码。具体原因请参见错误码列表 \n
	* @ingroup G_Q_Disconnect
	*/
	virtual void TAP_CDECL OnDisconnect(TAPIINT32 reasonCode);
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
	virtual void TAP_CDECL OnRspQryCommodity(TAPIUINT32 sessionID, TAPIINT32 errorCode, TAPIYNFLAG isLast, const TapAPIQuoteCommodityInfo *info);
	/**
	* @brief 返回系统中合约信息
	* @param[in] sessionID 请求的会话ID；
	* @param[in] errorCode 错误码，当errorCode!=0时,info为NULL；
	* @param[in] isLast 标示是否是最后一批数据；
	* @param[in] info		指向返回的信息结构体。当errorCode不为0时，info为空。
	* @attention 不要修改和删除info所指示的数据；函数调用结束，参数不再有效。
	* @ingroup G_Q_Contract
	*/
	virtual void TAP_CDECL OnRspQryContract(TAPIUINT32 sessionID, TAPIINT32 errorCode, TAPIYNFLAG isLast, const TapAPIQuoteContractInfo *info);
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
	virtual void TAP_CDECL OnRspSubscribeQuote(TAPIUINT32 sessionID, TAPIINT32 errorCode, TAPIYNFLAG isLast, const TapAPIQuoteWhole *info);
	/**
	* @brief 退订指定合约的行情的结果回调
	* @param[in] sessionID 请求的会话ID；
	* @param[in] errorCode 错误码，当errorCode!=0时,info为NULL；
	* @param[in] isLast 标示是否是最后一批数据；
	* @param[in] info		指向返回的信息结构体。当errorCode不为0时，info为空。
	* @attention  不要修改和删除info所指示的数据；函数调用结束，参数不再有效。
	* @ingroup G_Q_Quote
	*/
	virtual void TAP_CDECL OnRspUnSubscribeQuote(TAPIUINT32 sessionID, TAPIINT32 errorCode, TAPIYNFLAG isLast, const TapAPIContract *info);
	/**
	* @brief	返回订阅行情的变化内容。
	* @details	此回调接口用来通知用户行情信息产生了变化，并向用户提交新的行情全文。
	* @param[in] info 最新的行情全文内容
	* @attention 不要修改和删除Quote指示的数据；函数调用结束，参数不再有效。
	* @ingroup G_Q_Quote
	*/
	virtual void TAP_CDECL OnRtnQuote(const TapAPIQuoteWhole *info);

	//-------------------------------------------------------------------------------------
	//task：任务
	//-------------------------------------------------------------------------------------

	void processTask();

	void processRspLogin(Task *task);

	void processAPIReady(Task *task);

	void processDisconnect(Task *task);

	void processRspQryCommodity(Task *task);

	void processRspQryContract(Task *task);

	void processRspSubscribeQuote(Task *task);

	void processRspUnSubscribeQuote(Task *task);

	void processRtnQuote(Task *task);


	//-------------------------------------------------------------------------------------
	//data：回调函数的数据字典
	//error：回调函数的错误字典
	//id：请求id
	//last：是否为最后返回
	//i：整数
	//-------------------------------------------------------------------------------------

	virtual void onRspLogin(int error, const dict &data) {};

	virtual void onAPIReady() {};

	virtual void onDisconnect(int reason) {};

	virtual void onRspQryCommodity(unsigned int session, int error, char last, const dict &data) {};

	virtual void onRspQryContract(unsigned int session, int error, char last, const dict &data) {};

	virtual void onRspSubscribeQuote(unsigned int session, int error, char last, const dict &data) {};

	virtual void onRspUnSubscribeQuote(unsigned int session, int error, char last, const dict &data) {};

	virtual void onRtnQuote(const dict &data) {};

	//-------------------------------------------------------------------------------------
	//req:主动函数的请求字典
	//-------------------------------------------------------------------------------------

	void createTapQuoteAPI(const dict &req, int &iResult);

	void release();

	void init();

	int exit();

	string getTapQuoteAPIVersion();

	int setTapQuoteAPIDataPath(string path);

	int setTapQuoteAPILogLevel(string level); //1

	int setHostAddress(string IP, int port); //2

	int login(const dict &req);

	int disconnect();

	int subscribeQuote(const dict &req); //3

	int qryCommodity();

	int qryContract(const dict &req);
};

