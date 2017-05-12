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
	return i;
};

//获取错误信息
string CsHsHlp::getErrorMsg()
{
	char msg[512];
	CITICs_HsHlp_GetErrorMsg(this->handle, NULL, msg);
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

//发包
int CsHsHlp::bizCallAndCommit(int iFuncID)
{
	int i = CITICs_HsHlp_BizCallAndCommit(this->handle, iFuncID, NULL, BIZCALL_ASYNC);
	return i;
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
	int i = CITICs_HsHlp_Exit(this->handle);
	return i;
};


//------------------------------------------------------------------------
//异步消息处理线程
//------------------------------------------------------------------------

//连续运行的消息处理函数
void CsHsHlp::processMsg()
{
	LPMSG_CTRL msg;
	int row = 0;
	int col = 0;
	char key[64] = {0};
	char value[512] = {0};
	memset(&msg, 0, sizeof(msg));

	while (1)
	{
		//读取消息
		CITICs_HsHlp_QueueGetMsg(this->handle, msg, -1);

		//生成字典并推送到Python中
		row = CITICs_HsHlp_GetRowCount(this->handle, msg);		//获取msg行数（有多少个回应）
		col = CITICs_HsHlp_GetColCount(this->handle, msg);		//获取msg列数（有哪些字段）

		for (int i = 0; i < row; i++)
		{
			if (0 == CITICs_HsHlp_GetNextRow(this->handle, msg))
			{
				dict data;
				for (int j = 0; j < col; j++)
				{
					CITICs_HsHlp_GetColName(this->handle, j, key);
					CITICs_HsHlp_GetValueByIndex(this->handle, j, value);
					string str_key = key;
					string str_value = value;
					data[str_key] = str_value;
					this->onMsg(data);
				}
			}
		}

		//从队列删除消息
		CITICs_HsHlp_QueueEraseMsg(this->handle, msg);
	}
};



///-------------------------------------------------------------------------------------
///Boost.Python封装
///-------------------------------------------------------------------------------------

struct CsHsHlpWrap : CsHsHlp, wrapper < CsHsHlp >
{
	virtual void onMsg(dict data)
	{
		//在向python环境中调用回调函数推送数据前，需要先获取全局锁GIL，防止解释器崩溃
		PyLock lock;

		//以下的try...catch...可以实现捕捉python环境中错误的功能，防止C++直接出现原因未知的崩溃
		try
		{
			this->get_override("onMsg")(data);
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

		.def("onMsg", pure_virtual(&CsHsHlpWrap::onMsg))
		;
};