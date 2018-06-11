#pragma once

#include <map>
using namespace std;
#ifndef ShZdMessage_H
#define ShZdMessage_H

#ifdef DLL_FILE
 class _declspec(dllexport) CShZdMessage  //导出类CShZdMessage
#else
 class _declspec(dllimport) CShZdMessage  //导入类CShZdMessage
#endif
{
public:
	CShZdMessage(void);
	~CShZdMessage(void);
	bool SetTag(const int tag,const char* value);	
	char* GetString(int tag);
	bool SetAllRead(int read);//设置所有信息结构体为已读或未读
	const char* GetMesgType();
	bool SetMsgType(const char *msgType);
	string GetAllString();//返回所有的字符串
private:	
	map<int,string> MsgBody;//信息体
};

#endif 