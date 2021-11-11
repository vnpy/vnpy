/*************************
*摘要：南华期货交易系统
*文件：NhUserApiErrCode.h
*      定义了客户端接口错误码
*作者：南华期货软件部
*时间：20100220
**************************/

#ifndef __NH_USERAPI_ERRCODE_H__
#define __NH_USERAPI_ERRCODE_H__

#include "NHUserApiDataType.h"

///////////////////////////////////////////////////////////////////////////
//未知错误
const TErrorCodeType Err_Unknown									= -1;
//成功
const TErrorCodeType Err_Succeed									= 0;
//超时
const TErrorCodeType Err_TimeOut									= 10;
//接收到的数据格式错误
const TErrorCodeType Err_ReceiveMsg								= 11;
//连接数达到最大值
const TErrorCodeType Err_ConnectNum								= 12;
//发送数据出错
const TErrorCodeType Err_SendData									= 13;
//网络未连接
const TErrorCodeType Err_DisConnect								= 14;
//原始请求已超时
const TErrorCodeType Err_Request_TimeOUt					= 15;
//用户已登录
const TErrorCodeType Err_User_Login								= 16;
//用户未登录
const TErrorCodeType Err_User_Not_Login							= 17;
//参数缺少必填字段
const TErrorCodeType Err_Param_Necess								= 18;
//查询信息失败
const TErrorCodeType Err_Query_Failed								= 19;

#endif
