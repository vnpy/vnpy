/////////////////////////////////////////////////////////////////////////
///@author 中泰证券股份有限公司
///@file xtp_api_struct_common.h
///@brief 定义业务公共数据结构
/////////////////////////////////////////////////////////////////////////

#ifndef _XTP_API_STRUCT_COMMON_H_
#define _XTP_API_STRUCT_COMMON_H_

#include <stdint.h>
#include "xtp_api_data_type.h"

///响应信息
#define XTP_ERR_MSG_LEN  76
typedef struct XTPRspInfoStruct
{
	///错误代码
	int32_t	error_id;
	///错误信息
	char	error_msg[XTP_ERR_MSG_LEN];
} XTPRI;

#endif // !_XTP_API_STRUCT_COMMON_H_
