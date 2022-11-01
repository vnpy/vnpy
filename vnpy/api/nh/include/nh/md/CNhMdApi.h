/*************************
*摘要：南华期货交易系统
*文件：NhMdApi.h
*      定义了客户端接口
*作者：南华期货软件部
*时间：20130604
**************************/

#ifndef __CNH_MD_API_H__
#define __CNH_MD_API_H__

#ifdef WIN32
#define MD_API_EXPORT __declspec(dllexport)
#else
#define MD_API_EXPORT
#endif

#include "NHUserApiStruct.h"
#include "NHUserApiErrCode.h"

class CNhMdSpi
{
public:
	///当客户端与行情网关建立起通信连接时（还未登录前），该方法被调用。
	virtual void OnFrontConnected(){};
	
	///当客户端与行情网关通信连接断开时，该方法被调用。
	virtual void OnFrontDisConnected(){};

	///心跳超时警告。当长时间未收到报文时，该方法被调用。
	/* \param nTimeLapse 距离上次接收报文的时间
	****************************************/
	virtual void OnHeartBeatWarning(int nTimeLapse){};

	/***************************************
	/* \fn    OnRspError
	/* \brief 错误应答
	/* \param ERRORMSGINFO_t & req,错误应答消息
	/* \param TSequenceIDType nRequestID，如果是由于request引起的错误，则为对应请求ID，否则，为0
	/* \return void
	****************************************/
	virtual void OnRspError(ERRORMSGINFO_t &pRspInfo,TSequenceIDType nRequestID) {};

	///行情通知
	virtual void OnRtnMarketData(STKMarketData_t &pData) {};

	/***************************************
	/* \fn    OnRspUtpLogin
	/* \brief 登录南华统一交易平台UTP请求时响应
	/* \param RspUtpLoginField_t & req
	/* \param TSequenceIDType nRequestID，
	/* \return void
	****************************************/
	virtual void OnRspUtpLogin(const RspUtpLoginField_t& rsp,TSequenceIDType nRequestID){};
	
	/***************************************
	/* \fn    OnRspUtpLogout
	/* \brief 登录南华统一交易平台UTP请求时响应
	/* \param RspUtpLogoutField_t & req
	/* \param TSequenceIDType nRequestID
	/* \return void
	****************************************/
	virtual void OnRspUtpLogout(const RspUtpLogoutField_t& rsp,TSequenceIDType nRequestID){};
	
	/***************************************
	/* \fn    OnRspSubscribe
	/* \brief 订阅行情数据请求时响应
	/* \param RspSubscribeField_t & req
	/* \param TSequenceIDType nRequestID
	/* \return void
	****************************************/
	virtual void OnRspSubscribe(const RspSubscribeField_t& rsp,TSequenceIDType nRequestID){};
	
	/***************************************
	/* \fn    OnRspUnSubscribe
	/* \brief 取消订阅行情数据请求时响应
	/* \param RspUnSubscribeField_t & req
	/* \param TSequenceIDType nRequestID
	/* \return void
	****************************************/
	virtual void OnRspUnSubscribe(const RspUnSubscribeField_t& rsp,TSequenceIDType nRequestID){};

	/***************************************
	* \fn    OnRspQryExchange
	* \brief 查询交易所请求时响应
	* \param RspQryExchangeField_t & rsp
	* \param TSequenceIDType nRequestID
	* \return void
	****************************************/
	virtual void OnRspQryExchange(const RspQryExchangeField_t& rsp,TSequenceIDType nRequestID){};

	/***************************************
	* \fn    OnRspQryInstrument
	* \brief 查询合约请求时响应
	* \param RspQryInstrumentField_t & rsp
	* \param TSequenceIDType nRequestID
	* \return void
	****************************************/
	virtual void OnRspQryInstrument(const RspQryInstrumentField_t& rsp,TSequenceIDType nRequestID){};
};

class MD_API_EXPORT CNhMdApi
{
public:
	/***************************************
	/* \brief 创建MdApi
	/* \return 创建出的UserApi
	****************************************/
	static CNhMdApi *CreateMdApi();

	/***************************************
	/* \brief 删除接口对象本身
	/* \remark 不再使用本接口对象时,调用该函数删除接口对象
	****************************************/
	virtual void Release() = 0;

	/***************************************
	/* \brief 初始化
	/* \remark 初始化运行环境,只有调用后,接口才开始工作
	****************************************/
	virtual void Init() = 0;

	/***************************************
	/* \brief 获取系统版本号
	/* \param nMajorVersion 主版本号
	/* \param nMinorVersion 子版本号
	/* \return 系统标识字符串
	****************************************/
	virtual const char *GetVersion(int &nMajorVersion, int &nMinorVersion) = 0;

	/***************************************
	/* \brief 注册前置机网络地址
	/* \param pszFrontAddress：前置机网络地址。
	/* \remark 网络地址的格式为：“protocol://ipaddress:port”，如：”tcp://127.0.0.1:17001”。 
	/* \remark “tcp”代表传输协议，“127.0.0.1”代表服务器地址。”17001”代表服务器端口号。
	****************************************/
	virtual void RegisterFront(char *pszFrontAddress) = 0;

	/***************************************
	/* \brief 注册名字服务器网络地址(暂未使用)
	/* \param pszNsAddress：名字服务器网络地址。
	/* \remark 网络地址的格式为：“protocol://ipaddress:port”，如：”tcp://127.0.0.1:12001”。 
	/* \remark “tcp”代表传输协议，“127.0.0.1”代表服务器地址。”12001”代表服务器端口号。
	/* \remark RegisterNameServer优先于RegisterFront
	****************************************/
	virtual void RegisterNameServer(char *pszNsAddress) = 0;
	
	/***************************************
	/*注册回调接口
	/* \param pSpi 派生自回调接口类的实例
	****************************************/
	virtual void RegisterSpi(CNhMdSpi *pSpi) = 0;

	/***************************************
	/* \brief 设置心跳超时时间。
	/* \param timeout 心跳超时时间(秒)  
	****************************************/
	virtual void SetHeartbeatTimeout(unsigned int timeout) = 0;
	
	/***************************************
	/* \fn    UtpLoginRequest
	/* \brief 发送登录南华统一交易平台UTP请求
	/* \param TSequenceIDType nRequestID 请求序号
	/* \return 0:成功，其他失败,返回成功只表明请求发送成功
	/*			 处理结果在对应回调函数中检查
	****************************************/
	virtual int ReqUtpLogin(ReqUtpLoginField_t& req, TSequenceIDType nRequestID) = 0;

	/***************************************
	* \fn    UtpLogoutRequest
	* \brief 发送登出南华统一交易平台UTP请求
	* \param TSequenceIDType nRequestID 请求序号
	* \return 0:成功，其他失败,返回成功只表明请求发送成功
	*			 处理结果在对应回调函数中检查
	****************************************/
	virtual int ReqUtpLogout(TSequenceIDType nRequestID) = 0;

	/***************************************
	* \fn    SubscribeRequest
	* \brief 发送订阅行情数据请求,当行情数据订阅成功以后，如果网络断开则，需要重新订阅
	* \当用户成功logout以后，系统会自动取消订阅所有的行情信息。
	* \param ReqSubscribeField_t & req
	* \param TSequenceIDType nRequestID 请求序号
	* \return 0:成功，其他失败,返回成功只表明请求发送成功
	*			 处理结果在对应回调函数中检查
	****************************************/
	virtual int ReqSubscribe(ReqSubscribeField_t& req,TSequenceIDType nRequestID) = 0;

	/***************************************
	* \fn    UnSubscribeRequest
	* \brief 发送取消订阅行情数据请求
	* \param ReqUnSubscribeField_t & req
	* \param TSequenceIDType nRequestID 请求序号
	* \return 0:成功，其他失败,返回成功只表明请求发送成功
	*			 处理结果在对应回调函数中检查
	****************************************/
	virtual int ReqUnSubscribe(ReqUnSubscribeField_t& req,TSequenceIDType nRequestID) = 0;

	/***************************************
	* \fn    AuthUserPassworRequest(该方法暂时未用)
	* \brief 发送用户验证数据请求
	* \param ReqAuthUserPassworField_t & req
	* \param TSequenceIDType nRequestID 请求序号
	* \return 0:成功，其他失败,返回成功只表明请求发送成功
	*			 处理结果在对应回调函数中检查
	****************************************/
	virtual int ReqAuthUserPasswor(ReqAuthUserPassworField_t& req,TSequenceIDType nRequestID) = 0;
		
	/***************************************
	* \fn    ReqQryExchange
	* \brief 发送查询交易所请求
	* \param ReqQryExchangeField_t & req
	* \param TSequenceIDType nRequestID 请求序号
	* \return 0:成功，其他失败,返回成功只表明请求发送成功
	*			 处理结果在对应回调函数中检查
	****************************************/
	virtual int ReqQryExchange(const ReqQryExchangeField_t& req,TSequenceIDType nRequestID) = 0;
	
	/***************************************
	* \fn    ReqQryInstrument
	* \brief 发送查询合约请求
	* \param ReqQryInstrumentField_t & req
	* \param TSequenceIDType nRequestID 请求序号
	* \return 0:成功，其他失败,返回成功只表明请求发送成功
	*			 处理结果在对应回调函数中检查
	****************************************/
	virtual int ReqQryInstrument(const ReqQryInstrumentField_t& req,TSequenceIDType nRequestID) = 0;
protected:
	~CNhMdApi();
};

#endif
