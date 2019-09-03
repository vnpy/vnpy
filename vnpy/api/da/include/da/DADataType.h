/////////////////////////////////////////////////////////////////////////
/// DriectAccess Trade Engine
/// Copyright (C) Shanghai DirectAccess Technology Co., Ltd.
/// Last Modify 2019/3/18
/// Define DataType For API
/// Author (c) Wang Jian Quan (Franklin)
/////////////////////////////////////////////////////////////////////////

#pragma once

#define DA_STR_SIZE					256

#define MAX_BROKER					4096

#define DAAPI_VERSION				"1.12"

#ifdef _WIN32 
#define OS_NAME						"Windows"
#else
#define OS_NAME						"Linux"
#endif

#ifdef _WIN32 
#ifdef LIB_DA_API_EXPORT
#define DA_API_EXPORT				__declspec(dllexport)
#else
#define DA_API_EXPORT				__declspec(dllimport)
#endif
#else
#define DA_API_EXPORT
#endif

typedef char						TDACharType;
typedef char						TDAStringType[DA_STR_SIZE];
typedef char						TDABrokerType[MAX_BROKER];

typedef int							TDAIntType;
typedef int							TDAVolumeType;

typedef double						TDADoubleType;
typedef double						TDAPriceType;
typedef double						TDAMoneyType;

/// 单次最大订阅退订数
#define MAX_SUB_COUNT				20

/////////////////////////////////////////////////////////////////////////
/// 订阅行情种类
/////////////////////////////////////////////////////////////////////////

/// 股票
#define DAF_TYPE_Stock				'S'
/// 期货
#define DAF_TYPE_Future				'D'
/// 未知
#define DAF_TYPE_Unknown			 0

/////////////////////////////////////////////////////////////////////////
/// 订阅类型
/////////////////////////////////////////////////////////////////////////

/// 追加订阅
#define DAF_SUB_Append				'1'
/// 替换订阅
#define DAF_SUB_Replace				'2'
/// 退订
#define DAF_SUB_Unsubcribe			'3'
/// 退订所有
#define DAF_SUB_UnsubcribeAll		'4'

/////////////////////////////////////////////////////////////////////////
/// 行情数据类型
/////////////////////////////////////////////////////////////////////////

/// 完整行情数据
#define DAF_Market_Full				'Z'
/// 成交行情数据
#define DAF_Market_Fill				'Y'

