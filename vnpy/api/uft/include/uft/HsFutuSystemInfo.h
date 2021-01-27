#ifndef _HSFUTU_MONITOR_INFO_H
#define _HSFUTU_MONITOR_INFO_H

#ifdef WIN32
#define EXPORT
#else
#define EXPORT  __attribute__((visibility("default")))
#endif

//调用规约
#ifdef _WIN32
#  ifndef HSAPI
#  define HSAPI __stdcall
#  endif
#else
#  define HSAPI 
#endif


#ifdef __cplusplus
extern "C"
{
#endif
/* 加密session_id
*@param   in   需要加密的字符串
*@param   inLen 需要加密的字符串长度
*@param   out   输出加密后的指针,此缓冲区长度需要大于 ((inLen+16)/3+1)*4
*@param	  outlen 加密后的字符串长度
*@param   key   即本地授权码
*@return  0: 成功 非0:失败
*/
EXPORT int HSAPI hundsun_encrypt(char* in, int inLen, char* out, int* outLen, char* key);

/*采集系统信息
*@param pszSysInfo:  加密后的采集信息, 缓冲区长度至少492字节
*@param iSysInfoLen:  加密后的采集信息的长度
*@param pszSysInfoIntegrity:   采集信息完整度，缓冲区长度至少300字节
*@param iSysInfoIntegrityLen:   采集信息完整度的长度
*@return 0：正常1：终端信息采集为空2：终端采集数据加密密钥版本异常3：终端信息数据异常	
*/
EXPORT int HSAPI hundsun_getsysteminfo(char* pszSysInfo, int* iSysInfoLen, char* pszSysInfoIntegrity, int* iSysInfoIntegrityLen);

/*获取指标采集详细错误信息【只有HUNDSUN_getsysteminfo的返回值异常标识为的时候调用这个获取具体错误信息才有意义】
*@param pszSysInfoIntegrity:HUNDSUN_getsysteminfo函数返回的采集信息完整度
*@param pszDetailInfo:详细错误信息，缓冲区长度至少150字节
*@param iDetailInfoLen:详细错误信息长度
*@return true：获取成功 false：获取失败
*/
EXPORT bool HSAPI hundsun_getdetailerror(char* pszSysInfoIntegrity, char* pszDetailInfo, int* iDetailInfoLen);

/*获取采集库版本号
*@return :字符串形式的版本号
*/
EXPORT const char* HSAPI hundsun_getversion();
#ifdef __cplusplus
}
#endif

#endif