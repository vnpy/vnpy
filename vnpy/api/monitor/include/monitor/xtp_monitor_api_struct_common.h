/////////////////////////////////////////////////////////////////////////
///@author 中泰证券股份有限公司
///@file xtp_host_api_struct_common.h
///@brief 定义业务公共数据结构
/////////////////////////////////////////////////////////////////////////

#ifndef _XTP_HOST_API_STRUCT_COMMON_H_
#define _XTP_HOST_API_STRUCT_COMMON_H_

#ifndef _XTP_API_STRUCT_COMMON_H_

#if defined(_MSC_VER) && _MSC_VER<1600
typedef signed char        int8_t;
typedef short              int16_t;
typedef int                int32_t;
typedef long long          int64_t;
typedef unsigned char      uint8_t;
typedef unsigned short     uint16_t;
typedef unsigned int       uint32_t;
typedef unsigned long long uint64_t;
#else
#include <stdint.h>

#endif
#endif


#pragma pack(8)

///错误信息的字符串长度
#define XTP_HOST_ERR_MSG_LEN  124
///响应信息
typedef struct XTPHostErrorInfoStruct
{
	///错误代码
	int32_t	error_id;
	///错误信息
	char	error_msg[XTP_HOST_ERR_MSG_LEN];
} XTPHRI;

#pragma pack()

#endif // !_XTP_HOST_API_STRUCT_COMMON_H_
