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
///API中的部分组件
///-------------------------------------------------------------------------------------

//GIL全局锁简化获取用，
//用于帮助C++线程获得GIL锁，从而防止python崩溃
class PyLock
{
private:
	PyGILState_STATE gil_state;

public:
	//在某个函数方法中创建该对象时，获得GIL锁
	PyLock()
	{
		gil_state = PyGILState_Ensure();
	}

	//在某个函数完成后销毁该对象时，解放GIL锁
	~PyLock()
	{
		PyGILState_Release(gil_state);
	}
};



///-------------------------------------------------------------------------------------
///封装类
///-------------------------------------------------------------------------------------

class CsHsHlp
{
private:
	HSHLPCFGHANDLE cfgHandle;		//配置指针
	HSHLPHANDLE handle;				//操作对象指针
	thread *task_thread;			//工作线程指针（向python中推送数据）

public:
	CsHsHlp()
	{
		function0<void> f = boost::bind(&CsHsHlp::processMsg, this);
		//thread t(f);
		//this->task_thread = &t;
	};

	~CsHsHlp()
	{

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
	virtual void onMsg(dict data) {};
};
