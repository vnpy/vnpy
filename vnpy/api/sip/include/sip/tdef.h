
#ifndef _DATATYPE_DEFINE_H_
#define _DATATYPE_DEFINE_H_
// 接口使用的公共定义和结构
// tdef.h LINUX版/Windows版兼容
// ver 1.0

// LINUX中 GCC类型长度(字节)
// type         x86_sizeof(type)    x64_sizeof(type)
// char         1                   1
// short        2                   2
// int          4                   4
// long         4                   8
// void*        4                   8
// long long    8                   8
// float        4                   4
// double       8                   8

//__GNUC__
//linux
//__i386__  是x86
//__x86_64__  是X64


//windows VC编译器
// type         x86_sizeof(type)    x64_sizeof(type)
// char         1                   1
// short        2                   2
// int          4                   4
// long         4                   4
// void*        4                   8
// long long    8                   8
// float        4                   4
// double       8                   8

//_WIN32
//  Defined for applications for Win32 and Win64. Always defined.
//_WIN64
//  Defined for applications for Win64.
//_WINDOWS_ 在Windows.h中定义的#ifndef _WINDOWS_
//#define _WINDOWS_





// 基本数据类型
typedef char                    T_I8;
typedef unsigned char           T_U8;

typedef short int               T_I16;
typedef unsigned short int      T_U16;

typedef int                     T_I32;
typedef unsigned int            T_U32;

typedef long long               T_I64;
typedef unsigned long long      T_U64;

typedef float                   T_F32;
typedef double                  T_F64;

#ifdef linux    // linux
    #define UNALIGNED
    #define __stdcall

    typedef  long               T_HANDLE;  // so接口用的句柄，可与指针类型互转
    typedef long                T_PARAM;  // 用于回调参数，可与指针类型互转

    //{{ windows习惯的定义
    typedef int                 SOCKET;

    #define FALSE               0
    #define TRUE                1
    #define BOOL                bool

    #define INVALID_SOCKET      (-1)
    #define SOCKET_ERROR        (-1)
    #define INVALID_HANDLE_FILE (-1)
    #define stricmp(a,b)        strcasecmp(a,b)

    #ifndef max
        #define max(a,b)        (((a) > (b)) ? (a) : (b))
    #endif

    #ifndef min
        #define min(a,b)        (((a) < (b)) ? (a) : (b))
    #endif
    //}}
#else // windows
    #ifdef _WIN64
        typedef long long       T_HANDLE;
        typedef long long       T_PARAM;  // 用于回调参数，可与指针类型互转
    #else
        typedef  long           T_HANDLE;
        typedef long            T_PARAM;  // 用于回调参数，可与指针类型互转
    #endif //WIN64
#endif



#endif // _DATATYPE_DEFINE_H_
