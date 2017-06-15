// vnctpmd.cpp : 定义 DLL 应用程序的导出函数。
//

#include "stdafx.h"
#include "vnshzd.h"

///-------------------------------------------------------------------------------------
///C++的回调函数将数据保存到队列中
///-------------------------------------------------------------------------------------

int ShzdApi::OnReceiveTradeInfo(const CShZdMessage * re)
{
	if (re)
	{
		CShZdMessage *msg = new CShZdMessage();
		*msg = *re;

		Task *task = new Task();
		task->task_name = ONRECEIVETRADEINFO;
		task->task_data = msg;
		this->task_queue.push(task);
	}

	return 0;
};

int ShzdApi::OnReceiveMarketInfo(const CShZdMessage * re)
{
	if (re)
	{
		CShZdMessage *msg = new CShZdMessage();
		*msg = *re;

		Task *task = new Task();
		task->task_name = ONRECEIVEMARKETINFO;
		task->task_data = msg;
		this->task_queue.push(task);
	}

	return 0;
};

int ShzdApi::OnReceiveErrorInfo(int errorCode, const char* re)
{
	Task *task = new Task();
	task->task_name = ONRECEIVEERRORINFO;
	task->task_errcode = errorCode;
	task->task_errmsg = string(re);
	this->task_queue.push(task);

	return 0;
};


///-------------------------------------------------------------------------------------
///工作线程从队列中取出数据，转化为python对象后，进行推送
///-------------------------------------------------------------------------------------

void ShzdApi::processTask()
{
	while (1)
	{
		Task *task = this->task_queue.wait_and_pop();

		switch (task->task_name)
		{
			case ONRECEIVETRADEINFO:
			{
				this->processTradeInfo(task);
				break;
			}

			case ONRECEIVEMARKETINFO:
			{
				this->processMarketInfo(task);
				break;
			}

			case ONRECEIVEERRORINFO:
			{
				this->processErrorInfo(task);
				break;
			}
		};
	}
};


void ShzdApi::processTradeInfo(Task* task)
{
	PyLock lock;
	
	dict data;
	CShZdMessage *tr = (CShZdMessage*)task->task_data;
	
	//读取信息类型
	string type = tr->GetMesgType();
	data["msgtype"] = type;

	//读取具体数据
	string allstr = tr->GetAllString();
	vector<string> strvector;
	boost::split(strvector, allstr, boost::is_any_of(","));			//首先基于","把字符串分解

	for (int i = 0; i < strvector.size(); i++)						//遍历上一步分解的段落，再用"="分解每段
	{
		string temp = strvector[i];
		if (temp.find("=") != string::npos)							//忽略没有"="的段落
		{
			vector<string> tempvector;
			boost::split(tempvector, temp, boost::is_any_of("="));
			data[tempvector[0]] = tempvector[1];
		}
	}

	this->onReceiveTradeInfo(data);

	delete task->task_data;
	delete task;
};

void ShzdApi::processMarketInfo(Task* task)
{
	PyLock lock;

	dict data;
	CShZdMessage *tr = (CShZdMessage*)task->task_data;

	//读取信息类型
	string type = tr->GetMesgType();
	data["msgtype"] = type;

	//读取具体数据
	string allstr = tr->GetAllString();
	vector<string> strvector;
	boost::split(strvector, allstr, boost::is_any_of(","));			//首先基于","把字符串分解

	for (int i = 0; i < strvector.size(); i++)						//遍历上一步分解的段落，再用"="分解每段
	{
		string temp = strvector[i];
		if (temp.find("=") != string::npos)							//忽略没有"="的段落
		{
			vector<string> tempvector;
			boost::split(tempvector, temp, boost::is_any_of("="));
			data[tempvector[0]] = tempvector[1];
		}
	}

	this->onReceiveMarketInfo(data);

	delete task->task_data;
	delete task;
};

void ShzdApi::processErrorInfo(Task* task)
{
	PyLock lock;

	this->onReceiveErrorInfo(task->task_errcode, task->task_errmsg);
	
	delete task;
};



///-------------------------------------------------------------------------------------
///主动函数
///-------------------------------------------------------------------------------------

void ShzdApi::release()
{
	this->api->Release();
};

int ShzdApi::initShZdServer()
{
	this->api = GetShZdTradeLib();
	int n = this->api->InitShZdServer();
	this->api->RegisterOutLib(this);
	return n;
};


int ShzdApi::registerFront(string address, int port)
{
	return this->api->RegisterFront(address.c_str(), port);
};


int ShzdApi::registerMarket(string address, int port)
{
	return this->api->RegisterMarket(address.c_str(), port);
};

int ShzdApi::shzdSendInfoToTrade(dict data)
{
	CShZdMessage msg = CShZdMessage();

	//插入信息类型
	if (data.has_key("msgtype"))
	{
		object msgtype = data["msgtype"];
		extract<string> x(msgtype);
		if (x.check())
		{
			string typestr = x();
			msg.SetMsgType(typestr.c_str());
		}
	}
	
	//插入字段
	boost::python::list keyList = data.keys();
	boost::python::list valueList = data.values();

	for (int n = 0; n < len(keyList); n++)		
	{
		//声明
		int keyint = 0;
		string valuestr = "";
		
		//获取整数型的key
		object key = keyList[n];
		extract<string> x1(key);
		if (x1.check())
		{
			string keystr = x1();
			stringstream ss;
			ss << keystr;
			ss >> keyint;
		}

		//获取字符串的value
		object value = valueList[n];
		extract<string> x2(value);
		if (x2.check())
		{
			valuestr = x2();
		}

		//添加到msg中
		msg.SetTag(keyint, valuestr.c_str());
	}

	return this->api->ShZdSendInfoToTrade(&msg);
};

int ShzdApi::shzdSendInfoToMarket(dict data)
{
	CShZdMessage msg = CShZdMessage();

	//插入信息类型
	if (data.has_key("msgtype"))
	{
		object msgtype = data["msgtype"];
		extract<string> x(msgtype);
		if (x.check())
		{
			string typestr = x();
			msg.SetMsgType(typestr.c_str());
		}
	}

	//插入字段
	boost::python::list keyList = data.keys();
	boost::python::list valueList = data.values();

	for (int n = 0; n < len(keyList); n++)
	{
		//声明
		int keyint = 0;
		string valuestr = "";

		//获取整数型的key
		object key = keyList[n];
		extract<string> x1(key);
		if (x1.check())
		{
			string keystr = x1();
			stringstream ss;
			ss << keystr;
			ss >> keyint;
		}

		//获取字符串的value
		object value = valueList[n];
		extract<string> x2(value);
		if (x2.check())
		{
			valuestr = x2();
		}

		//添加到msg中
		msg.SetTag(keyint, valuestr.c_str());
	}

	return this->api->ShZdSendInfoToMarket(&msg);
};



///-------------------------------------------------------------------------------------
///Boost.Python封装
///-------------------------------------------------------------------------------------

struct ShzdApiWrap : ShzdApi, wrapper < ShzdApi >
{
	virtual void onReceiveTradeInfo(dict data)
	{
		//以下的try...catch...可以实现捕捉python环境中错误的功能，防止C++直接出现原因未知的崩溃
		try
		{
			this->get_override("onReceiveTradeInfo")(data);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void onReceiveMarketInfo(dict data)
	{
		try
		{
			this->get_override("onReceiveMarketInfo")(data);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void onReceiveErrorInfo(int errcode, string errmsg)
	{
		try
		{
			this->get_override("onReceiveErrorInfo")(errcode, errmsg);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};
};


BOOST_PYTHON_MODULE(vnshzd)
{
	PyEval_InitThreads();	//导入时运行，保证先创建GIL

	class_<ShzdApiWrap, boost::noncopyable>("ShzdApi")
		.def("release", &ShzdApiWrap::release)
		.def("initShZdServer", &ShzdApiWrap::initShZdServer)
		.def("registerFront", &ShzdApiWrap::registerFront)
		.def("registerMarket", &ShzdApiWrap::registerMarket)
		.def("shzdSendInfoToTrade", &ShzdApiWrap::shzdSendInfoToTrade)
		.def("shzdSendInfoToMarket", &ShzdApiWrap::shzdSendInfoToMarket)

		.def("onReceiveTradeInfo", pure_virtual(&ShzdApiWrap::onReceiveTradeInfo))
		.def("onReceiveMarketInfo", pure_virtual(&ShzdApiWrap::onReceiveMarketInfo))
		.def("onReceiveErrorInfo", pure_virtual(&ShzdApiWrap::onReceiveErrorInfo))
		;
};
