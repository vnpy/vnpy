//说明部分

//系统
#include "stdafx.h"
#include <string>
#include <queue>

//Boost
#define BOOST_PYTHON_STATIC_LIB
#include <boost/python/module.hpp>	//python封装
#include <boost/python/def.hpp>		//python封装
#include <boost/python/dict.hpp>	//python封装
#include <boost/python/list.hpp>	//python封装
#include <boost/python/object.hpp>	//python封装
#include <boost/python.hpp>			//python封装
#include <boost/thread.hpp>			//任务队列的线程功能
#include <boost/bind.hpp>			//任务队列的线程功能
#include <boost/any.hpp>			//任务队列的任务实现

//API
#include "CITICs_HsT2Hlp.h"

//命名空间
using namespace std;
using namespace boost::python;
using namespace boost;


///-------------------------------------------------------------------------------------
///封装类
///-------------------------------------------------------------------------------------

class CsHsHlp
{
private:
	HSHLPCFGHANDLE cfgHandle;		//配置指针
	HSHLPHANDLE handle;				//操作对象指针
	thread *task_thread;			//工作线程指针（向python中推送数据）
	bool active;					//工作状态

public:
	CsHsHlp()
	{
		this->active = false;
	};

	~CsHsHlp()
	{
		this->active = false;
	};

	//------------------------------------------------------------------------
	//主动函数部分
	//------------------------------------------------------------------------

	//读取配置文件
	int loadConfig(string fileName);

	//初始化
	int init();

	//连接服务器
	int connectServer();

	//获取错误信息
	string getErrorMsg();

	//初始化发包请求
	int beginParam();

	//设置发包的参数字段名称和值
	int setValue(string key, string value);

	//发包
	int bizCallAndCommit(int iFuncID);

	//订阅
	boost::python::list subscribeData(int iFuncID);

	//断开服务器
	int disconnect();

	//退出
	int exit();

	//------------------------------------------------------------------------
	//异步消息处理线程
	//------------------------------------------------------------------------

	//连续运行的消息处理函数
	void processMsg();

	//------------------------------------------------------------------------
	//Python中继承的回调函数
	//------------------------------------------------------------------------
	
	//向Python中推送消息的函数
	virtual void onMsg(int type, boost::python::list data, int reqNo, int errorNo, string errorInfo) {};
};
