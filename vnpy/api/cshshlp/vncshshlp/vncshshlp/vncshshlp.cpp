// vncshshlp.cpp : 定义 DLL 应用程序的导出函数。
//

#include "stdafx.h"
#include "vncshshlp.h"

//------------------------------------------------------------------------
//主动函数部分
//------------------------------------------------------------------------

//读取配置文件
int CsHsHlp::loadConfig(string fileName)
{
	int i = CITICs_HsHlp_LoadConfig(&this->cfgHandle, fileName.c_str());
	return i;
};

//初始化
int CsHsHlp::init()
{
	int i = CITICs_HsHlp_Init(&this->handle, this->cfgHandle);
	return i;
};

//连接服务器
int CsHsHlp::connectServer()
{
	int i = CITICs_HsHlp_ConnectServer(this->handle);

	if (this->active == false)
	{
		this->active = true;
		function0<void> f = boost::bind(&CsHsHlp::processMsg, this);
		thread t(f);
		this->task_thread = &t;
	}

	return i;
};

//获取错误信息
string CsHsHlp::getErrorMsg()
{
	int i;
	char msg[512];
	CITICs_HsHlp_GetErrorMsg(this->handle, &i, msg);
	string errorMsg = msg;
	return errorMsg;
};

//初始化发包请求
int CsHsHlp::beginParam()
{
	int i = CITICs_HsHlp_BeginParam(this->handle);
	return i;
};

//设置发包的参数字段名称和值
int CsHsHlp::setValue(string key, string value)
{
	int i = CITICs_HsHlp_SetValue(this->handle, key.c_str(), value.c_str());
	return i;
};

//异步发包
int CsHsHlp::bizCallAndCommit(int iFuncID)
{
	int i = CITICs_HsHlp_BizCallAndCommit(this->handle, iFuncID, NULL, BIZCALL_ASYNC, NULL);
	return i;
};

//订阅
boost::python::list CsHsHlp::subscribeData(int iFuncID)
{
	int i = CITICs_HsHlp_BizCallAndCommit(this->handle, iFuncID, NULL, BIZCALL_SUBSCRIBE, NULL);
	
	//订阅为同步调用，读取返回的结果
	int row = CITICs_HsHlp_GetRowCount(this->handle);		//获取msg行数（有多少个回应）
	int col = CITICs_HsHlp_GetColCount(this->handle);		//获取msg列数（有哪些字段）
	char key[64] = { 0 };
	char value[512] = { 0 };

	boost::python::list data;

	for (int i = 0; i < row; i++)
	{
		if (0 == CITICs_HsHlp_GetNextRow(this->handle))
		{
			dict d;
			for (int j = 0; j < col; j++)
			{
				CITICs_HsHlp_GetColName(this->handle, j, key);
				CITICs_HsHlp_GetValueByIndex(this->handle, j, value);

				string str_key = key;
				string str_value = value;
				d[str_key] = str_value;
			}
			data.append(d);
		}
	}

	return data;
};

//断开服务器
int CsHsHlp::disconnect()
{
	int i = CITICs_HsHlp_DisConnect(this->handle);
	return i;
};

//退出
int CsHsHlp::exit()
{
	this->active = false;
	int i = CITICs_HsHlp_Exit(this->handle);
	return i;
};


//------------------------------------------------------------------------
//异步消息处理线程
//------------------------------------------------------------------------

//连续运行的消息处理函数
void CsHsHlp::processMsg()
{
	LPMSG_CTRL msgCtrl;			//控制信息
	int type = 0;				//消息类型
	int reqNo = 0;				//异步请求编号
	int errorNo = 0;			//错误代码
	string errorInfo = "";		//错误信息

	int row = 0;				//行数
	int col = 0;				//列数
	char key[64] = {0};			//键
	char value[512] = {0};		//值

	PyGILState_STATE gil_state;	//GIL全局锁

	//连续运行
	while (this->active)
	{
		//初始化指针
		msgCtrl = new MSG_CTRL();

		//读取消息
		int i = CITICs_HsHlp_QueueGetMsg(this->handle, msgCtrl, -1);

		//读取信息
		if (msgCtrl->nIssueType)
		{
			type = msgCtrl->nIssueType;
		}
		else
		{
			type = msgCtrl->nFuncID;
		}

		reqNo = msgCtrl->nReqNo;
		errorNo = msgCtrl->nErrorNo;
		errorInfo = msgCtrl->szErrorInfo;

		row = CITICs_HsHlp_GetRowCount(this->handle, msgCtrl);		//获取msg行数（有多少个回应）
		col = CITICs_HsHlp_GetColCount(this->handle, msgCtrl);		//获取msg列数（有哪些字段）

		//生成字典并推送到Python中
		gil_state = PyGILState_Ensure();		//创建Python对象前先锁定GIL

		boost::python::list data;

		for (int i = 0; i < row; i++)
		{	
			if (0 == CITICs_HsHlp_GetNextRow(this->handle, msgCtrl))
			{
				dict d;
				for (int j = 0; j < col; j++)
				{
					CITICs_HsHlp_GetColName(this->handle, j, key, msgCtrl);
					CITICs_HsHlp_GetValueByIndex(this->handle, j, value, msgCtrl);

					string str_key = key;
					string str_value = value;					
					d[str_key] = str_value;
				}
				data.append(d);
			}
		}

		this->onMsg(type, data, reqNo, errorNo, errorInfo);

		PyGILState_Release(gil_state);			//推送Python对象完成后释放GIL

		//从队列删除消息
		CITICs_HsHlp_QueueEraseMsg(this->handle, msgCtrl);

		//删除指针
		delete msgCtrl;
	}
};


///-------------------------------------------------------------------------------------
///Boost.Python封装
///-------------------------------------------------------------------------------------

struct CsHsHlpWrap : CsHsHlp, wrapper < CsHsHlp >
{
	virtual void onMsg(int type, boost::python::list data, int reqNo, int errorNo, string errorInfo)
	{
		//以下的try...catch...可以实现捕捉python环境中错误的功能，防止C++直接出现原因未知的崩溃
		try
		{
			this->get_override("onMsg")(type, data, reqNo, errorNo, errorInfo);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};
};


BOOST_PYTHON_MODULE(vncshshlp)
{
	PyEval_InitThreads();	//导入时运行，保证先创建GIL

	class_<CsHsHlpWrap, boost::noncopyable>("CsHsHlp")
		.def("loadConfig", &CsHsHlpWrap::loadConfig)
		.def("init", &CsHsHlpWrap::init)
		.def("connectServer", &CsHsHlpWrap::connectServer)
		.def("getErrorMsg", &CsHsHlpWrap::getErrorMsg)
		.def("beginParam", &CsHsHlpWrap::beginParam)
		.def("setValue", &CsHsHlpWrap::setValue)
		.def("bizCallAndCommit", &CsHsHlpWrap::bizCallAndCommit)
		.def("disconnect", &CsHsHlpWrap::disconnect)
		.def("exit", &CsHsHlpWrap::exit)
		.def("subscribeData", &CsHsHlpWrap::subscribeData)

		.def("onMsg", pure_virtual(&CsHsHlpWrap::onMsg))
		;
};