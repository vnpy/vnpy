#ifndef TAPDATACOLLECTAPI_H
#define TAPDATACOLLECTAPI_H

//! 成功
const int TAPIERROR_DataCollect_SUCCEED                                = 0;
//! 获取IP失败
const int TAPIERROR_IP                                                 = -1;
//! 获取MAC失败
const int TAPIERROR_MAC                                                = -2;
//! 获取设备名称失败
const int TAPIERROR_ComputerName                                       = -3;
//! 获取操作系统版本失败
const int TAPIERROR_OSVersion                                          = -4;
//! 获取硬盘序列号失败
const int TAPIERROR_HDID                                               = -5;
//! 获取CPU序列号失败
const int TAPIERROR_CPUSerialID                                        = -6;
//! 获取BIOS序列号失败
const int TAPIERROR_BIOSSerailID                                       = -7;
//! 获取系统分盘信息失败
const int TAPIERROR_SysDiskInfo                                        = -8;
//! 获取MacOS设备序列号失败
const int TAPIERROR_MacOsSerialID                                      = -9;

#if defined WIN32 || defined _WIN64
#define TAP_CDECL __cdecl
#define TAP_DLLEXPORT __declspec(dllexport)
#else
#define TAP_CDECL
#define TAP_DLLEXPORT
#endif

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus
  
	
TAP_DLLEXPORT int TAP_CDECL esunny_getsysteminfo(char* pSystemInfo, int* nLen, int* nVer);
	

#ifdef __cplusplus
}
#endif // __cplusplus

#endif /* TAPDATACOLLECTAPI_H */

