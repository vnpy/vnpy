#include <stdio.h>
#include <stdlib.h>

#ifndef _T2SDK_INTERFACE_H
# define _T2SDK_INTERFACE_H

#ifdef _WIN32
	#if !defined( FUNCTION_CALL_MODE )
	#define FUNCTION_CALL_MODE		__stdcall
	#endif
#else
	#define FUNCTION_CALL_MODE
#endif

#ifndef HS_IKNOWN_SDK
#define HS_IKNOWN_SDK
struct IKnown
{
    virtual unsigned long  FUNCTION_CALL_MODE QueryInterface(const char *iid, IKnown **ppv) = 0;

    virtual unsigned long  FUNCTION_CALL_MODE AddRef() = 0;

    virtual unsigned long  FUNCTION_CALL_MODE Release() =  0;
    
    ~IKnown(){}
};
#endif

#include <string.h>

#ifdef _WIN32
typedef unsigned int		uint32;
#else
#include <sys/types.h>
#if defined(__linux__)
#include <stdint.h>
#endif
typedef uint32_t			uint32;
#endif

///ESB组名长度，名字为可见字符，不能包含实例分隔符、空格、分号;
#define IDENTITY_NAME_LENGTH	32
///实例编号最大占位长度
#define ID_LENGTH               4 
///节点名全长,定义时使用char sName[ID_STR_LEN+1]
#define ID_STR_LEN		       (IDENTITY_NAME_LENGTH + ID_LENGTH + 1)


//	插件接口名的最大长度,定义时使用char sName[PLUGINID_LENGTH+1]
#define PLUGINID_LENGTH	256
//	插件实例名的最大长度,定义时使用char sName[PLUGIN_NAME_LENGTH+1]
#define PLUGIN_NAME_LENGTH	(PLUGINID_LENGTH+ID_LENGTH+1)
//	进程名最大长度.定义时使用char sName[SVR_NAME_LENGTH+1]
#define SVR_NAME_LENGTH	256
//	进程实例名最大长度.定义时使用char sName[PLUGINID_NAME_LENGTH+1]
#define SVRINSTANCE_NAME_LENGTH	(SVR_NAME_LENGTH+ID_LENGTH+1)

//文件更新列表字段
/** 文件更新：以下宏为API库中文件更新功能与界面间交互的打包器中的字段 */
#define PACKER_INT_FILE_LIST            "file_list"     /**< 文件列表 */
#define PACKER_INT_FILE_ID              "file_id"       /**< 文件id */
#define PACKER_INT_FILE_SIZE            "file_size"     /**< 文件大小 */
#define PACKER_INT_TIME                 "time"          /**< 文件时间 */
#define PACKER_STRING_FILE_NAME         "file_name"     /**< 文件名 */
#define PACKER_STRING_FILE_PATH         "file_path"     /**< 文件路径 */
#define PACKER_STRING_LOCAL_PATH        "local_path"    /**< 本地文件路径 */
#define PACKER_STRING_MD5_CODE          "md5_code"      /**< 文件md5值 */
#define PACKER_STRING_FILE_FLAG         "file_flag"     /**< 文件标识 */

//业务消息类型
//请求
#define REQUEST_PACKET 0 
//应答
#define ANSWER_PACKET  1 
//20110302 xuxp 增加路由信息的结构体定义
typedef struct tagRouteInfo
{
	char ospfName[ID_STR_LEN+1];
	char nbrName[ID_STR_LEN+1];
	char svrName[SVRINSTANCE_NAME_LENGTH+1];
	char pluginID[PLUGIN_NAME_LENGTH+1];
	int connectID;
	int memberNO;

	tagRouteInfo()
	{
		memset(this,0,sizeof(tagRouteInfo));
	}
}Route_Info;


//20101228 xuxp 为了发送和返回订阅推送信息而增加的结构体的定义
typedef struct tagRequestData
{	
	int sequeceNo;
	int issueType;
	void* lpKeyInfo;
	int keyInfoLen;
	void* lpFileHead;
	int fileHeadLen;
	int packetType;//20100111 xuxp 新加的包类型
	Route_Info routeInfo;//20110302 xuxp 请求里面增加路由信息
	int iSubSystemNo;//20130508 xuxp 参数中增加子系统号传入
	int iCompanyID;//20140114 xuxp 增加公司编号
}REQ_DATA, *LPREQ_DATA;
typedef struct tagRespondData
{
	int functionID;
	int returnCode;
	int errorNo;
	char* errorInfo;
	int issueType;
	void* lpKeyInfo;
	int keyInfoLen;
	Route_Info sendInfo;//20110302 xuxp 应答里面增加发送者信息
}RET_DATA, *LPRET_DATA;

//20150209 majc  增加宏定义
#define T2SDK_MAX_BRANCH_NO_LEN  256 
#define T2SDK_MAX_COMPANY_NO_LEN 256 
#define T2SDK_MAX_OSPF_LEN       256

//20150209 majc 增加创建订阅者时，指定路由参数结构体定义
typedef struct tagSubRouteInfo
{
	int iSystemNo;                       //系统号
	int iSubSystemNo;                    //子系统号
	char szBranchNo[T2SDK_MAX_BRANCH_NO_LEN+1];       //分支号
	char szCompanyNo[T2SDK_MAX_COMPANY_NO_LEN+1];        //公司编号
	char szOspfName[T2SDK_MAX_OSPF_LEN+1];         //OSPF
	tagSubRouteInfo()
	{
		memset(this,0,sizeof(tagSubRouteInfo));
	}
}SUB_ROUTER_INFO;

///解包器接口
struct IF2ResultSet : public IKnown
{

	///取字段数
    /**@return 返回字段数.
      */
    virtual int FUNCTION_CALL_MODE GetColCount()=0;

    ///取字段名
    /** @param column:字段序号(以0为基数)
      * @return 返回字段名  下标越界 返回NULL
      */
    virtual const char * FUNCTION_CALL_MODE GetColName(int column)=0;

    //取字段数据类型
    /** @param column:字段序号(以0为基数)
      * @return:见上面常量定义;下标越界 返回-1
      */
    virtual char FUNCTION_CALL_MODE GetColType(int column)=0;


   ///取数字型字段小数位数
   /** @param column:字段序号(以0为基数)
     * @return int 返回字段数据小数位数 下标越界 返回-1
     */
   virtual int FUNCTION_CALL_MODE GetColScale(int column)=0;
  
   //取字段允许存放数据的最大宽度.
   /** @param column:字段序号(以0为基数)
     * @return int 返回字段宽度 下标越界 返回-1
     */
   virtual int FUNCTION_CALL_MODE GetColWidth(int column) = 0;

   ///取字段名对应的字段序号
   /**@param columnName: 字段名
     *@return 返回字段序号. 不存在返回-1
     */
   virtual int  FUNCTION_CALL_MODE FindColIndex(const char * columnName)=0;

    //
    //按字段序号(以0为基数)，取字段值(字符串)
    /**@param column:字段序号(以0为基数)
      *@return 字符串型字段值,下标越界返回NULL
      */
    virtual const char *  FUNCTION_CALL_MODE GetStrByIndex(int column)=0;

    //按字段名，取字段值(字符串)
    /**@param columnName: 字段名
      *@return 字符串型字段值,不存在返回NULL
      */
    virtual const char *  FUNCTION_CALL_MODE GetStr(const char * columnName)=0;

    //按字段序号(以0为基数)，取字段值
    /**@param column:字段序号(以0为基数)
      *@return 字符型字段值,下标越界返回'\0'.
      */
     virtual char  FUNCTION_CALL_MODE  GetCharByIndex(int column)=0;

    //按字段名，取字段值
    /**@param columnName: 字段名
     *@return 字符型字段值,不存在返回'\0'
     */
    virtual char   FUNCTION_CALL_MODE GetChar(const char * columnName)=0;

    //按字段序号，取字段值
    /**@param column:字段序号(以0为基数)
      *@return double型字段值,下标越界返回0
      */
    virtual double  FUNCTION_CALL_MODE GetDoubleByIndex( int column)=0;
    
	///按字段名，取字段值
    /**@param columnName:字段名
      *@return double型字段值,不存在返回0
      */
    virtual double  FUNCTION_CALL_MODE GetDouble(const char * columnName)=0;

    ///按字段序号，取字段值
    /**@param column:字段序号(以0为基数)
      *@return int型字段值,下标越界返回0
      */
    virtual int  FUNCTION_CALL_MODE GetIntByIndex(int column)=0;

    ///按字段名，取字段值
    /**@param columnName:字段名
      *@return int型字段值,不存在返回0
      */
    virtual int FUNCTION_CALL_MODE GetInt(const char * columnName)=0;

	///按字段序号获得字段值,二进制数据
	/**@param column: 字段序号(以0为基数)
	*@param   lpRawLen: [out]数据长度
	*@return : 数据首地址
	*/
	virtual void *  FUNCTION_CALL_MODE GetRawByIndex(int column,int * lpRawLen) = 0;

	///按字段名，取字段值
	/**@param columnName:字段名
	*@param   lpRawLen: [out]数据长度
	*@return : 数据首地址
	*/
	virtual void *  FUNCTION_CALL_MODE GetRaw(const char * columnName,int * lpRawLen) = 0;


	///最后一次取的字段值是否为NULL
   /**@return 0 是， 1不是
   */
    virtual int  FUNCTION_CALL_MODE WasNull()=0;

    ///取下一条记录
    virtual void  FUNCTION_CALL_MODE Next()=0;

    ///判断是否为结尾
    /**@return 1 是，0 不是;
      */
    virtual int  FUNCTION_CALL_MODE IsEOF()=0;
   
	///判断是否为空
    /**@return 1 是，0 不是;
      */
    virtual int  FUNCTION_CALL_MODE IsEmpty()=0;
    
    virtual void * FUNCTION_CALL_MODE Destroy() = 0;
};

struct IF2UnPacker;

///多结果集打包接口(一个包可有多个异构结果集)
/**执行序列:
 *
 * 0、准备(可选, 若不进行该操作, 则由IF2Packer内部申请内存缓冲)： SetBuffer(),如果打包缓存区由调用者提供,则必须在BeginPack()之前准备;
 *
 * 1、开始:  BeginPack(),打包器复位;
 *
 * 2、第一个结果集打包：
 *
 *(a)添加字段名列表域：AddField()
 *
 *(b)按照结果集二维表顺序，逐字段，逐条记录按字段类型添加内容：AddStr() {AddInt(), AddDouble(), AddRaw()}
 *
 * 3、设置结果集的返回码(可选，若不设置, 则返回码为0) SetReturnCode()
 *
 * 4、打下一个结果集(可选) NewDataSet()，此处同时设置了该结果集的返回码；
 * 
 * 5、参考第2步实现下一个结果集打包(可选)；
 *
 * 6、结束：EndPack(),重复调用会导致加入空结果集;
 *
 * 7、取打包结果(缓存区，缓存区大小，数据长度)
 *    打包结果也可以直接解包UnPack()返回解包接口
 *
 *使用注意事项:IF2Packer所使用的内存缓存区，由调用者负责回收；
 *             结果集附带的返回码，只有在包格式版本0x21及以上时有效；
 */
struct IF2Packer : public IKnown
{
    ///打包器初始化(使用调用者的缓存区)
	/** 第一次使用打包器时，可先使用本方法设置好缓冲区(数据长度被置为iDataLen)
	 *@param  char * pBuf  缓冲区地址
 	 *@param  int iBufSize  缓冲区空间
 	 *@param  int iDataLen  已有数据长度，新增数据加在已有数据之后（只对V1.0格式的包有效） 	 
 	 */
	virtual void FUNCTION_CALL_MODE SetBuffer(void * pBuf,int iBufSize,int iDataLen=0 )=0;

	///复位，重新开始打另一个包(字段数与记录数置为0行0例)
	/**
	 * 功能：开始打包，把包长度清零(重复使用已有的缓存区空间)
	 *@return 无
	 */
	virtual void FUNCTION_CALL_MODE BeginPack(void)=0;

	///开始打一个结果集
	/**在打单结果集的包时，可以不调用本方法,均取默认值
	 *@param const char *szDatasetName 0x20版打包需要指明结果集名字
	 *@param int iReturnCode           0x20版打包需要为每个结果集指明返回值
	 */
	virtual int FUNCTION_CALL_MODE NewDataset(const char *szDatasetName, int iReturnCode = 0)=0;

	/**
	 * 功能：向包添加字段
	 *
	 *有执行次序要求:在 NewDataset()或Reset(),SetBuffer()之后,逐个字段按顺序添加;
	 *
	 *@param szFieldName：字段名
	 *@param cFieldType ：字段类型:I整数，D浮点数，C字符，S字符串，R任意二进制数据
	 *@param iFieldWidth ：字段宽度（所占最大字节数）
	 *@param iFieldScale ：字段精度,即cFieldType='D'时的小数位数(缺省为4位小数)
	 *@return 负数表示失败，否则为目前包的长度
	 */
	virtual int FUNCTION_CALL_MODE AddField(const char *szFieldName,char cFieldType ='S',int iFieldWidth=255,int iFieldScale=4)=0;

	/**
	 * 功能：向包添加字符串数据
     * 有执行次序要求:必须在所有字段增加完之后,逐个字段按顺序添加;
	 *@param       szValue：字符串数据
	 *@return 负数表示失败，否则为目前包的长度
	 */
	virtual int FUNCTION_CALL_MODE AddStr(const char *szValue)=0;

	/**
     * 功能：向包添加整数数据
 	 *@param       iValue：整数数据
	 *@return 负数表示失败，否则为目前包的长度
	 */
	virtual int FUNCTION_CALL_MODE AddInt(int iValue)=0;
	
    /**
	 * 功能：向包添加浮点数据
	 *@param       fValue：浮点数据
	 *@return 负数表示失败，否则为目前包的长度
	 */
	virtual int FUNCTION_CALL_MODE AddDouble(double fValue)=0;

	/**
	 * 功能：向包添加一个字符
	 *@param		 cValue：字符
	 *@return 负数表示失败，否则为目前包的长度
	 */
	virtual int FUNCTION_CALL_MODE AddChar(char cValue)=0;

	/**
	 * 功能：向包添加一个大对象
	 *@param	void * lpBuff 数据区
	 *@param	int iLen  数据长度	 
	 *@return 负数表示失败，否则为目前包的长度
	 */
	virtual int FUNCTION_CALL_MODE AddRaw(void * lpBuff,int iLen)=0;

    ///结束打包
	virtual void FUNCTION_CALL_MODE EndPack()=0;
 
	/**
     * 功能：取打包结果指针
	 *@return 打包结果指针
     */
	virtual void * FUNCTION_CALL_MODE GetPackBuf(void) = 0;
	
	/**
     * 功能：取打包结果长度
     *@return 打包结果长度
	 */
	virtual int FUNCTION_CALL_MODE GetPackLen(void) = 0;
	
	/**
	 * 功能：取打包结果缓冲区大小
     *@return 打包结果缓冲区大小
	 */
	virtual int FUNCTION_CALL_MODE GetPackBufSize(void) = 0;
	
	/**
	 * 功能：取打包格式版本
     *@return 版本
	 */
	virtual int FUNCTION_CALL_MODE GetVersion(void) = 0;
	
	///设置结果集的返回码(0x20版以上要求)，错误结果集需要设置
	/**返回码取缺省值0，则不设置，如果设置，则必须在EndPack()之前调用
     *@return 版本
	 */
	virtual void FUNCTION_CALL_MODE SetReturnCode(unsigned long dwRetCode) = 0;

	/**直接返回当前打包结果的解包接口,必须在EndPack()之后才能调用,在打包器释放时相应的解包器实例也释放
     *@return 解包器接口，此解包接口不能调用 destroy()来释放
	 */
	virtual IF2UnPacker * FUNCTION_CALL_MODE UnPack(void) = 0;

	/**
	 *
	 */
	virtual void FUNCTION_CALL_MODE FreeMem(void* lpBuf) = 0;

	/**
	 *
	 */
	virtual void FUNCTION_CALL_MODE ClearValue() = 0;
	
	
	//20110302 xuxp 增加一个接口函数，用来传递第一个结果集的名字
	///复位，重新开始打另一个包(字段数与记录数置为0行0例)
	/**
	 * 功能：开始打包，把包长度清零(重复使用已有的缓存区空间)
	 *@return 无
	 */
	virtual void FUNCTION_CALL_MODE BeginPackEx(char* szName = NULL) = 0;

	//20110324 dongpf 增加一个接口函数，用来复位当前结果集
	///复位当前结果集(字段数与记录数置为0行0例)，不影响其他结果集
	/**
	 * 功能：复位当前结果集
	 *@return 无
	 */
	virtual void FUNCTION_CALL_MODE ClearDataSet() = 0;
};

///解包器接口
struct IF2UnPacker : public IF2ResultSet
{
	/**取打包格式版本
     *@return 版本
	 */
	virtual int FUNCTION_CALL_MODE GetVersion(void) = 0;

	/**取解包数据长度
     *@return 							0 表示成功， 其它为失败
	 */
	virtual int FUNCTION_CALL_MODE Open(void * lpBuffer,unsigned int iLen) = 0;

    ///取结果集个数(0x20以上版本支持)
    virtual int FUNCTION_CALL_MODE GetDatasetCount()=0;

    ///设置当前结果集(0x20以上版本支持)
    /**
	 *@param  int nIndex				结果集编号
	 *@return int						非0 表示成功，否则为失败
	 */
    virtual int FUNCTION_CALL_MODE SetCurrentDatasetByIndex(int nIndex)=0;

    ///设置当前结果集 (0x20以上版本支持)
    /**
	 *@param  const char *szDatasetName	结果集名称
	 *@return int						非0 表示成功，否则为失败
	 */
    virtual int FUNCTION_CALL_MODE SetCurrentDataset(const char *szDatasetName)=0;

	/** 取解包数据区指针
	 *@return 数据区指针
     */
	virtual void * FUNCTION_CALL_MODE GetPackBuf(void) = 0;

	/** 取解包数据长度
     *@return 解包数据长度
	 */
	virtual unsigned int FUNCTION_CALL_MODE GetPackLen(void) = 0;

	/**取解包数据记录条数,20051207以后版本支持
     *@return 记录条数
	 */
	virtual unsigned int FUNCTION_CALL_MODE GetRowCount(void) = 0;
	
	///结果集行记录游标接口：取结果集的首条记录
    virtual void FUNCTION_CALL_MODE First() = 0;

    ///结果集行记录游标接口：取结果集的最后一条记录
    virtual void FUNCTION_CALL_MODE Last() = 0;

    ///结果集行记录游标接口：取结果集的第n条记录，取值范围[1, GetRowCount()]
    virtual void FUNCTION_CALL_MODE Go(int nRow) = 0;
	
	///获取当前结果集名字的接口,没有名字返回""
	virtual const char* FUNCTION_CALL_MODE GetDatasetName() = 0;
	
	virtual int FUNCTION_CALL_MODE OpenAndCopy(void * lpBuffer,unsigned int iLen) = 0;
	
	//20140623 majc 增加根据名字获取字段类型，字段精度，字段最大长度
	//取字段数据类型
    /** @param columnName:字段名
      * @return:见上面常量定义;列名不存在 默认返回'S'
      */
    virtual char FUNCTION_CALL_MODE GetColTypeByName(const char * columnName)=0;


   ///取数字型字段小数位数
   /** @param columnName:字段名
     * @return int 返回字段数据小数位数 列名不存在 返回0 
     */
   virtual int FUNCTION_CALL_MODE GetColScaleByName(const char * columnName)=0;
  
   //取字段允许存放数据的最大宽度.
   /** @param columnName:字段名
     * @return int 返回字段宽度 列名不存在 返回1
     */
   virtual int FUNCTION_CALL_MODE GetColWidthByName(const char * columnName) = 0;
};

///连接对象 CConnectionInterface 的参数配置对象CConfigInterface
/**
* 包括从文件加载、保存到文件，读写操作
*/
class CConfigInterface: public IKnown
{
public:
	/**
    * 从文件加载
    * @param szFileName 文件名，格式类似ini，具体参考开发包示例
    * @return 返回0表示成功，否则失败
    */
    virtual int FUNCTION_CALL_MODE Load(const char *szFileName) = 0;

    /**
    * 保存到文件
    * @param szFileName 文件名
    * @return 返回0表示成功，否则失败
    */
    virtual int FUNCTION_CALL_MODE Save(const char *szFileName) = 0;

    /**
    * 取字符串值
    * @param szSection 节名
    * @param szEntry   变量名
    * @param szDefault 缺省值
    * @return 字符串值，没有找到时返回szDefault
    */
    virtual const char * FUNCTION_CALL_MODE GetString(const char *szSection, const char *szEntry, const char *szDefault) = 0;

    /**
    * 取整数值
    * @param szSection 节名
    * @param szEntry   变量名
    * @param iDefault  缺省值
    * @return 整数值，没有找到时返回iDefault
    */
    virtual int FUNCTION_CALL_MODE GetInt(const char *szSection, const char *szEntry, int iDefault) = 0;

    /**
    * 设置字符串值
    * @param szSection 节名
    * @param szEntry   变量名
    * @param szValue   值
    * @return 0表示成功，否则失败
    */
    virtual int FUNCTION_CALL_MODE SetString(const char *szSection, const char *szEntry, const char *szValue) = 0;

    /**
    * 设置整数值
    * @param szSection 节名
    * @param szEntry   变量名
    * @param iValue    值
    * @return 0表示成功，否则失败
    */
    virtual int FUNCTION_CALL_MODE SetInt(const char *szSection, const char *szEntry, int iValue) = 0;
};


typedef struct tagBizRouteInfo
{
	char ospfName[ID_STR_LEN+1];//路由目标节点中间件名字
	char nbrName[ID_STR_LEN+1];//中间件节点的邻居名字
	char svrName[SVRINSTANCE_NAME_LENGTH+1];//中间件的进程名字
	char pluginID[PLUGIN_NAME_LENGTH+1];//中间件插件名
	int connectID;//连接号
	int memberNO;//成员编号
	
	tagBizRouteInfo()
	{
		memset(this,0,sizeof(tagBizRouteInfo));
	}
}BIZROUTE_INFO;


struct IBizMessage : public IKnown
{
	//设置功能号
	virtual void FUNCTION_CALL_MODE SetFunction(const int nFUnctionNo) = 0;
	//获取功能号
	virtual int FUNCTION_CALL_MODE GetFunction() = 0;

	//设置包类型
	virtual void FUNCTION_CALL_MODE SetPacketType(const int nPacketType) = 0;
	//获取包类型
	virtual int FUNCTION_CALL_MODE GetPacketType() = 0;

	//设置营业部号
	virtual void FUNCTION_CALL_MODE SetBranchNo(const int nBranchNo) = 0;
	//获取营业部号
	virtual int FUNCTION_CALL_MODE GetBranchNo() = 0;

	//设置系统号
	virtual void FUNCTION_CALL_MODE SetSystemNo(const int nSystemNo) = 0;
	//获取系统号
	virtual int FUNCTION_CALL_MODE GetSystemNo() = 0;

	//设置子系统号
	virtual void FUNCTION_CALL_MODE SetSubSystemNo(const int nSubSystemNo) = 0;
	//获取子系统号
	virtual int FUNCTION_CALL_MODE GetSubSystemNo() = 0;

	//设置发送者编号
	virtual void FUNCTION_CALL_MODE SetSenderId(const int nSenderId) = 0;
	//获取发送者编号
	virtual int FUNCTION_CALL_MODE GetSenderId() = 0;

	//设置包序号
	virtual void FUNCTION_CALL_MODE SetPacketId(const int nPacketId) = 0;
	//获取包序号
	virtual int FUNCTION_CALL_MODE GetPacketId() = 0;

	//设置目的地路由
	virtual void FUNCTION_CALL_MODE SetTargetInfo(const BIZROUTE_INFO targetInfo) = 0;
	//获取目的地路由
	virtual void FUNCTION_CALL_MODE GetTargetInfo(BIZROUTE_INFO& targetInfo) = 0;
	
	//设置发送者路由
	virtual void FUNCTION_CALL_MODE SetSendInfo(const BIZROUTE_INFO sendInfo) = 0;
	//获取发送者路由
	virtual void FUNCTION_CALL_MODE GetSendInfo(BIZROUTE_INFO& sendInfo) = 0;

	//设置错误号
	virtual void FUNCTION_CALL_MODE SetErrorNo(const int nErrorNo) = 0;
	//获取错误号
	virtual int FUNCTION_CALL_MODE GetErrorNo() = 0;
	
	//设置错误信息
	virtual void FUNCTION_CALL_MODE SetErrorInfo(const char* strErrorInfo) = 0;
	//获取错误信息
	virtual const char* FUNCTION_CALL_MODE GetErrorInfo() = 0;
	
	//设置返回码
	virtual void FUNCTION_CALL_MODE SetReturnCode(const int nReturnCode) = 0;
	//获取返回码
	virtual int FUNCTION_CALL_MODE GetReturnCode() = 0;

	//设置业务内容
	virtual void FUNCTION_CALL_MODE SetContent(void* lpContent,int iLen) = 0;
	//获取业务内容
	virtual const void* FUNCTION_CALL_MODE GetContent(int& iLen) = 0;

	//以下接口用于消息中心1.0的订阅
	//设置订阅类型
	virtual void FUNCTION_CALL_MODE SetIssueType(const int nIssueType) = 0;
	//获取订阅类型
	virtual int FUNCTION_CALL_MODE GetIssueType() = 0;

	//设置序号
	virtual void FUNCTION_CALL_MODE SetSequeceNo(const int nSequeceNo) = 0;
	//获取序号
	virtual int FUNCTION_CALL_MODE GetSequeceNo() = 0;

	//设置关键字段信息
	virtual void FUNCTION_CALL_MODE SetKeyInfo(void* lpKeyData,int iLen) = 0;
	//获取关键字段信息
	virtual const void* FUNCTION_CALL_MODE GetKeyInfo(int& iLen) = 0;

	//设置附加数据，订阅推送时原样返回
	virtual void FUNCTION_CALL_MODE SetAppData(const void* lpAppdata,int nAppLen) = 0;
	//获取附加数据，订阅推送时原样返回
	virtual const void* FUNCTION_CALL_MODE GetAppData(int& nAppLen) = 0;

	//请求转应答
	virtual int	FUNCTION_CALL_MODE ChangeReq2AnsMessage() = 0;

	//获取二进制
	virtual void* FUNCTION_CALL_MODE GetBuff(int& nBuffLen) = 0;
	//解析二进制
	virtual int	FUNCTION_CALL_MODE SetBuff(const void* lpBuff,int nBuffLen) = 0;

	//清除消息内的字段，可以下次复用。
	virtual void FUNCTION_CALL_MODE ReSet() = 0;
	
	//设置公司编号
	virtual void FUNCTION_CALL_MODE SetCompanyID(const int nCompanyID) = 0;
	//获取公司编号
	virtual int FUNCTION_CALL_MODE GetCompanyID() = 0;
	
	//设置发送者公司编号
	virtual void FUNCTION_CALL_MODE SetSenderCompanyID(const int nSenderCompanyID) = 0;
	//获取发送者公司编号
	virtual int FUNCTION_CALL_MODE GetSenderCompanyID() = 0;
};

#define IDENTITY_NAME_LENGTH    32  /**< 客户端名字长度 */
#define MAX_MACADDRESS_LEN	    18  /**< MAC 地址长度 */
#define MAX_RAND_LEN	        4   /**< 随机数长度 */

/** 客户标识长度 */
#define MAX_BIZNAME_LEN \
	IDENTITY_NAME_LENGTH+1+MAX_MACADDRESS_LEN+1+MAX_RAND_LEN+2

#define INIT_RECVQ_LEN 256          /**< 接收队列初始长度 */
#define STEP_RECVQ_LEN 512          /**< 接收队列扩展步长 */
#define SIMPLIFIED_CHINESE      0   /**< 错误信息语言:简体中文 */
#define ENGLISH                 1   /**< 错误信息语言:英文 */
#define MAX_FILTERFIELD_LEN 63      /**< 过滤字段长度 */

/** 主题可靠等级 */
enum ReliableLevel
{
    LEVEL_DOBEST            = 0,    /**< 尽力而为 */
    LEVEL_DOBEST_BYSEQ      = 1,    /**< 尽力有序 */
    LEVEL_MEM               = 2,    /**< 内存 */
    LEVEL_FILE              = 3,    /**< 文件 */
    LEVEL_SYSTEM            = 4     /**< 系统 */
};

/** 
 * 过滤器接口
 */
class CFilterInterface:public IKnown
{
public:
   /**
    * 根据下标获取过滤条件的名字
    * @param index 对应的过滤条件下标
    * @return 返回对应的下标过滤条件的名字，否则返回NULL.
    */
    virtual char* FUNCTION_CALL_MODE GetFilterNameByIndex(int index) = 0;

   /**
    * 根据下标获取过滤条件的值
    * @param index 对应的过滤条件下标
    * @return 返回对应的下标过滤条件的值，否则返回NULL.
    */
    virtual char* FUNCTION_CALL_MODE GetFilterValueByIndex(int index)= 0;

   /**
    * 根据过滤条件的名字获取过滤条件的值
    * @param fileName 对应的过滤条件名字
    * @return 返回对应的过滤条件名字的条件值，否则返回NULL.
    */
    virtual char* FUNCTION_CALL_MODE GetFilterValue(char*  fileName)= 0;

   /**
    * 获取过滤条件的个数
    * @return 返回对应过滤条件的个数，没有返回0
    */
    virtual int   FUNCTION_CALL_MODE GetCount() = 0;

   /**
    * 设置过滤条件，根据过滤条件名字和值
    * @param filterName 对应的过滤条件名字
    * @param filterValue 对应的过滤条件名字的值
    */
    virtual void FUNCTION_CALL_MODE  SetFilter(char* filterName,char* filterValue) =0;
};

/**
 * 订阅参数类接口
 */
class CSubscribeParamInterface:public IKnown
{
public:

   /**
    * 设置主题名字
    * @param szName 对应的主题名字
    */
    virtual void FUNCTION_CALL_MODE  SetTopicName(char* szName) =0;

   /**
    * 设置附加数据
    * @param lpData 附加数据的首地址
    * @param iLen 附加数据的长度
    */
    virtual void FUNCTION_CALL_MODE  SetAppData(void* lpData,int iLen)=0;
    
   /**
    * 添加过滤条件
    * @param filterName 过滤条件的名字
    * @param filterValue 过滤条件的值
    */
    virtual void FUNCTION_CALL_MODE  SetFilter(char* filterName,char* filterValue)=0;

   /**
    * 添加返回字段
    * @param filedName 需要添加的返回字段
    */
    virtual void FUNCTION_CALL_MODE  SetReturnFiled(char* filedName)=0;

   /**
    * 设置是否补缺标志
    * @param bFromNow true表示需要之前的数据，也就是补缺，false表示不需要补缺
    */
    virtual void FUNCTION_CALL_MODE  SetFromNow(bool bFromNow)=0;

   /**
    * 设置覆盖订阅标志
    * @param bReplace true表示覆盖订阅，取消之前的所有订阅，只保留当前的订阅，false表示追加订阅
    */
    virtual void FUNCTION_CALL_MODE  SetReplace(bool bReplace)=0;

   /**
    * 设置发送间隔
    * @param nSendInterval 单位是秒
    */
    virtual void FUNCTION_CALL_MODE  SetSendInterval(int nSendInterval)=0;

   /**
    * 获取主题名字
    * @return 返回主题名字信息
    */
    virtual char* FUNCTION_CALL_MODE  GetTopicName() =0;

   /**
    * 获取附加数据
    * @param iLen 出参，表示附加数据的长度
    * @return 返回附加数据首地址，没有返回NULL
    */
    virtual void* FUNCTION_CALL_MODE  GetAppData(int *iLen) =0;

   /**
    * 获取对应的过滤字段的名字
    * @param index 对应的过滤条件下标
    * @return 返回对应的下标过滤条件的名字，否则返回NULL.
    */
    virtual char* FUNCTION_CALL_MODE  GetFilterNameByIndex(int index) = 0;

   /**
    * 根据下标获取过滤条件的值
    * @param index 对应的过滤条件下标
    * @return 返回对应的下标过滤条件的值，否则返回NULL.
    */
    virtual char* FUNCTION_CALL_MODE  GetFilterValueByIndex(int index)= 0;

   /**
    * 根据过滤条件的名字获取过滤条件的值
    * @param fileName 对应的过滤条件名字
    * @return 返回对应的过滤条件名字的条件值，否则返回NULL.
    */
    virtual char* FUNCTION_CALL_MODE  GetFilterValue(char*  fileName)= 0;

   /**
    * 获取过滤条件的个数
    * @return 返回对应过滤条件的个数，没有返回0
    */
    virtual int   FUNCTION_CALL_MODE  GetFilterCount() = 0;

   /**
    * 获取返回字段
    * @return 返回对应的返回字段信息
    */
    virtual char* FUNCTION_CALL_MODE  GetReturnFiled()=0;

   /**
    * 获取是否补缺的标志
    * @return 返回对应的补缺标志
    */
    virtual bool  FUNCTION_CALL_MODE  GetFromNow()=0 ;

   /**
    * 获取是否覆盖订阅的标志
    * @return 返回对应的覆盖订阅标志
    */
    virtual bool  FUNCTION_CALL_MODE  GetReplace() =0;

   /**
    * 获取对应的发送频率
    * @return 返回对应的发送间隔
    */
    virtual int   FUNCTION_CALL_MODE  GetSendInterval()=0;
    
	/**
    * 设置是否更新消息序号
    * @param bUpdate true表示需要更新消息序号，false表示不更新
    */
    virtual void FUNCTION_CALL_MODE  SetUpdateMsgNo(bool bUpdate)=0;

	/**
    * 获取是否更新消息序号
    * @return 返回是否更新消息序号
    */
    virtual bool  FUNCTION_CALL_MODE  GetUpdateMsgNo()=0;
};

class CSubscribeInterface;

/**
 * @brief 订阅回调接口返回的数据定义，除了订阅需要的业务体之外，还需要返回的数据
 */
typedef struct tagSubscribeRecvData
{
	char* lpFilterData;     /**< 过滤字段的数据头指针，用解包器解包 */
	int iFilterDataLen;     /**< 过滤字段的数据长度 */
	char* lpAppData;        /**< 附加数据的数据头指针 */
	int iAppDataLen;        /**< 附加数据的长度 */
	char szTopicName[260];  /**< 主题名字 */
	
   /**
    * tagSubscribeRecvData 构造函数
    */
	tagSubscribeRecvData()
	{
		memset(this,0,sizeof(tagSubscribeRecvData));
	}
}SUBSCRIBE_RECVDATA, *LPSUBSCRIBE_RECVDATA;

/**
 * 订阅回调接口，上层应用通过这个接口，接收主推过来的消息
 */
class CSubCallbackInterface: public IKnown
{
public:

   /**
    * 收到发布消息的回调
    * @param lpSub 回调的订阅指针
    * @param subscribeIndex 消息对应的订阅标识，这个标识来自于SubscribeTopic函数的返回
    * @param lpData 返回消息的二进制指针，一般是消息的业务体打包内容
    * @param nLength 二进制数据的长度
	* @param lpRecvData 主推消息的其他字段返回，主要包含了附加数据，过滤信息，主题名字，详细参看前面结构体定义
    * @return 无
    */
    virtual void FUNCTION_CALL_MODE OnReceived(CSubscribeInterface *lpSub,int subscribeIndex, const void *lpData, int nLength,LPSUBSCRIBE_RECVDATA lpRecvData) = 0;

   /**
    * 收到剔除订阅项的消息回调，一般在拥有踢人策略的主题下会回调这个接口,这个回调里面不需要取消订阅，底层已经取消这个订阅，只是一个通知接口
    * @param lpSub 回调的订阅指针
    * @param subscribeIndex 消息对应的订阅标识，这个标识来自于SubscribeTopic函数的返回
    * @param TickMsgInfo 踢人的错误信息，主要是包含具体重复的订阅项位置信息
    * @return 无
    */
    virtual void FUNCTION_CALL_MODE OnRecvTickMsg(CSubscribeInterface *lpSub,int subscribeIndex,const char* TickMsgInfo) = 0;
};


/**
 * 订阅接口的定义
 */
class CSubscribeInterface: public IKnown
{
public:

   /**
    * 订阅主题
    * @param lpSubscribeParamInter 上面定义的订阅参数结构
    * @param uiTimeout 超时时间
    * @param lppBizUnPack 业务校验时，失败返回的业务错误信息，如果订阅成功没有返回，输出参数，需要外面调用Release释放
                          如果接受业务校验的错误信息，写法如下：
                          IF2UnPacker* lpBizUnPack =NULL;
                          SubscribeTopic(...,&lpBizUnPack);
                          最后根据返回值，如果是失败的就判断 lpBizUnPack 是不是NULL.
                          最后错误信息获取完之后,释放
                          lpBizUnPack->Release();
    * @param lpBizPack 业务校验需要增加的业务字段以及值，没有就根据过滤属性作为业务校验字段
    * @return 返回值大于0，表示当前订阅成功的订阅标识，外面要记住这个标识和订阅项之间的映射关系，这个标识需要用于取消订阅和接收消息的回调里面.
	*		  返回其他值，根据错误号获取错误信息.
    */
    virtual int FUNCTION_CALL_MODE SubscribeTopic(CSubscribeParamInterface* lpSubscribeParamInter ,unsigned int uiTimeout,IF2UnPacker** lppBizUnPack=NULL,IF2Packer* lpBizPack=NULL) = 0;

   /**
    * 取消订阅主题
    * @param subscribeIndex 消息对应的订阅标识，这个标识来自于SubscribeTopic函数的返回
    * @return 返回0表示取消订阅成功，返回其他值，根据错误号获取错误信息.
    */
    virtual int FUNCTION_CALL_MODE CancelSubscribeTopic(int subscribeIndex) = 0;


	/**
    * 取消订阅主题
    * @param topicName 主题名字
    * @param lpFilterInterface 对应的过滤条件
    * @return 返回0表示取消订阅成功，返回其他值，根据错误号获取错误信息.
    */
    virtual int FUNCTION_CALL_MODE CancelSubscribeTopicEx(char* topicName,CFilterInterface* lpFilterInterface) = 0;



   /**
    * 获取当前订阅接口已经订阅的所有主题以及过滤条件信息
    * @param lpPack 外面传入的打包器
    * @note packer报文字段
        - SubcribeIndex
        - IsBornTopic
        - TopicName
        - TopicNo
        - FilterRaw
        - Appdata
        - SendInterval
        - ReturnFileds
        - isReplace
        - isFromNow
    */
    virtual void FUNCTION_CALL_MODE GetSubcribeTopic(IF2Packer* lpPack)=0;
	
	
	/**
    * 取服务器地址
    * @param lpPort 输出的服务器端口，可以为NULL
    * @return 返回服务器地址
    */
    virtual const char * FUNCTION_CALL_MODE GetServerAddress(int *lpPort) = 0;
	 /**
    * 获取服务端的所有主题信息
    * @param byForce 是否强制从后台获取
    * @param iTimeOut 超时时间
    * @return 成功就返回所有主题信息
    * @note 解包器外面需要调用release接口进行释放.
    * @note packer返回字段
    * - TopicName
    * - TopicNo
    * - ReliableLevel
    * - IssuePriority
    * - MsgLifetime
    * - Stutas 
    * - TickStrategy 
    * - BusinessVerify
    * - Local
    * - FilterField1 
    * - FilterField2 
    * - FilterField3 
    * - FilterField4 
    * - FilterField5 
    * - FilterField6
	* - FilterField7
	* - FilterField8
	* - FilterField9
	* - FilterField10
	* - FilterField11
	* - FilterField12
	* - FilterField13
	* - FilterField14
	* - FilterField15
	* - FilterField16
    * - SubscribeStr 
    * - PublishStr
    */
    virtual IF2UnPacker* FUNCTION_CALL_MODE GetTopic(bool byForce,int iTimeOut) = 0;


	/**
	*批量订阅的接口
	*@param lpSubReqUnpack 批量参数的集合，采用unpack的形式传入
	*传入的解包器必须包含的字段如下：
	*TopicName SendInterval  ReturnFileds isFromNow AppData
	*FilterField1 FilterValue1 FilterField2 FilterValue2 FilterField3 FilterValue3 FilterField4 FilterValue4
	*FilterField5 FilterValue5 FilterField6 FilterValue6 FilterField7 FilterValue7 FilterField8 FilterValue8
	*FilterField9 FilterValue9 FilterField10 FilterValue10 FilterField11 FilterValue11 FilterField12 FilterValue12
	*FilterField13 FilterValue13 FilterField14 FilterValue14 FilterField15 FilterValue15 FilterField16 FilterValue16
	*BizCheckPack(用于订阅相应主题的业务校验unpack，二进制格式存放)
	*@param lpSubAnsPacker 订阅结果的返回，由外部申请一个空的打包器，函数内部把每个订阅结果打入打包器。
	*传出的打包器包含的字段如下：
	*TopicName SendInterval  ReturnFileds isFromNow AppData
	*FilterField1 FilterValue1 FilterField2 FilterValue2 FilterField3 FilterValue3 FilterField4 FilterValue4
	*FilterField5 FilterValue5 FilterField6 FilterValue6 FilterField7 FilterValue7 FilterField8 FilterValue8
	*FilterField9 FilterValue9 FilterField10 FilterValue10 FilterField11 FilterValue11 FilterField12 FilterValue12
	*FilterField13 FilterValue13 FilterField14 FilterValue14 FilterField15 FilterValue15 FilterField16 FilterValue16
	*BizCheckPack SubscribeIndex NotifyStatus ErrorNo ErrorInfo 
	*@param uiTimeout 订阅的超时时间,单位毫秒
	*@return 成功就返回0，其他值表示失败，通过错误号获取错误信息，具体每个订阅的失败原因可以查看lpSubAnsPacker内容。
	//////////////////////////////////////////////////////////////////////////////
	*调用实例：
	*IF2Packer* lpSubReqPack =NewPacker(2);
	*lpSubReqPack->AddRef();
	*添加多天需要订阅的参数，按照参数说面添加。
	*IF2Packer* lpSubAnsPack =NewPacker(2);
	*lpSubAnsPack->AddRef();
	*lpSubAnsPack->BeginPack();
	*BatchSubscribeTopic(lpSubReqPack->Unpack(),lpSubAnsPack,10000);
	*lpSubAnsPack->EndPack();
	*IF2UnPacker* lpAnsUnPack=lpSubAnsPack->Unpack();
	*根据返回参数获取对应的订阅应答
	*lpSubReqPack->FreeMem(lpSubReqPack->GetPackBuf());
	*lpSubReqPack->Release();
	*lpSubAnsPack->FreeMem(lpSubAnsPack->GetPackBuf());
	*lpSubAnsPack->Release();
	//////////////////////////////////////////////////////////////////////////////
	*/
	virtual int FUNCTION_CALL_MODE BatchSubscribeTopic(IF2UnPacker* lpSubReqUnpack,IF2Packer* lpSubAnsPacker,unsigned int uiTimeout) = 0;

	/**
    * 获取订阅会话状态
    * @return 0		 与消息中心连接断开 
			  1		 正在与消息中心建立连接 
			  2		 与消息中心连接已建立 
    */
    virtual int FUNCTION_CALL_MODE GetSessionStatus() = 0;
};

/**
 * 发布接口
 */
class CPublishInterface: public IKnown
{
public:

   /**
    * 业务打包格式的内容发布接口
    * @param topicName 主题名字，不知道名字就传NULL
    * @param lpUnPacker 具体的内容
    * @param iTimeOut 超时时间
    * @param lppBizUnPack 业务校验时，失败返回的业务错误信息，如果发布成功没有返回，输出参数，需要外面调用Release释放
                            如果接受业务校验的错误信息，写法如下：
                            IF2UnPacker* lpBizUnPack =NULL;
                            PubMsgByPacker(...,&lpBizUnPack);
                            最后根据返回值，如果是失败的就判断 lpBizUnPack 是不是NULL.
                            最后错误信息获取完之后,释放
                            lpBizUnPack->Release();
    * @param bAddTimeStamp 是否添加时间戳，配合单笔性能查找
    * @return 返回0表示成功，返回其他值，根据错误号获取错误信息.
    */
    virtual int FUNCTION_CALL_MODE PubMsgByPacker(char* topicName ,IF2UnPacker* lpUnPacker,int iTimeOut=-1,
        IF2UnPacker** lppBizUnPack=NULL,bool bAddTimeStamp=false) = 0;
    
   /**
    * 非业务打包格式的内容发布接口，一般二进制格式报文发布
    * @param topicName 主题名字，不知道名字就传NULL
    * @param lpFilterInterface 过滤条件，需要上层自己指定，否则默认没有过滤条件
    * @param lpData 具体的内容
    * @param nLength 内容长度
    * @param iTimeOut 超时时间
    * @param lppBizUnPack 业务校验时，失败返回的业务错误信息，如果发布成功没有返回，输出参数，需要外面调用Release释放
                            如果接受业务校验的错误信息，写法如下：
                            IF2UnPacker* lpBizUnPack =NULL;
                            PubMsgByPacker(...,&lpBizUnPack);
                            最后根据返回值，如果是失败的就判断 lpBizUnPack 是不是NULL.
                            最后错误信息获取完之后,释放
                            lpBizUnPack->Release();
    * @param bAddTimeStamp 是否添加时间戳，配合单笔性能查找
    * @return 返回0表示成功，返回其他值，根据错误号获取错误信息.
    */
    virtual int FUNCTION_CALL_MODE PubMsg(char* topicName, CFilterInterface* lpFilterInterface, const void *lpData, int nLength,int iTimeOut=-1,
        IF2UnPacker** lppBizUnPack=NULL,bool bAddTimeStamp=false) = 0;

   /**
    * 返回当前主题的发布序号
    * @param topicName 主题名字
    * @return 返回0表示没有对应的主题，返回其他值表示成功
    */
    virtual uint32 FUNCTION_CALL_MODE GetMsgNoByTopicName(char* topicName)=0;

   /**
    * 取服务器地址
    * @param lpPort 输出的服务器端口，可以为NULL
    * @return 返回服务器地址
    */
    virtual const char * FUNCTION_CALL_MODE GetServerAddress(int *lpPort) = 0;
};
/**
 * 文件更新回调接口
 */
class CFileUpdateCallbackInterface: public IKnown
{
public:

   /**
    * 收到更新文件列表的回调
    * @param lpData 返回二进制指针
    * @param nLength 二进制数据的长度，如果为负数则为错误码
	* @param lpErrorInfo 如果不为NULL则为错误信息，发生错误，应该先去看错误信息，如果没有再去拿错误码信息
    * @return 无
    */
    virtual void FUNCTION_CALL_MODE OnRecvFileList(const void *lpData, int nLength, const char * lpErrorInfo) = 0;

   /**
    * 收到通知文件更新进度
    * @param iOneFileProcessBar 当前文件进度
    * @param iTotalProcessBar 总进度
	* @param lpErrorInfo 如果不为NULL则为错误信息，发生错误，应该先去看错误信息，如果没有再去拿错误码信息
    * @return 无
    */
    virtual void FUNCTION_CALL_MODE OnShowProcessBar(int iOneFileProcessBar, int iTotalProcessBar, const char * lpErrorInfo) = 0;
	
	/**
    * 收到成功取消文件更新
    * @return 无
    */
    virtual void FUNCTION_CALL_MODE OnCancel() = 0;


};
/**
 * 文件更新接口
 */
class CFileUpdateInterface: public IKnown
{
public:

   /**
    * 根据前面回调显示的文件列表，由用户选择后下发需要更新的文件列表
    * @param lpPack 更新文件列表指针
    * @return 返回0表示成功，其他值表示失败.
    */
    virtual int FUNCTION_CALL_MODE UpdateFile(IF2Packer* lpPack) = 0;

   /**
    * 界面取消正在更新中的更新动作
    * @return 返回0表示成功，其他值表示失败
    */
    virtual int FUNCTION_CALL_MODE CancelUpdateFile() = 0;

   /**
    * 获取更新文件列表
    * @return 文件列表解包器，不允许外部操作，只能读，不能释放
	* @note 解包器里面的字段见该文件define字段,注意：在OnRecvFileList回调以后该方法有效
    */
    virtual IF2UnPacker* FUNCTION_CALL_MODE GetFileUpdateList() = 0;
};
class CConnectionInterface;

///连接对象 CConnectionInterface 需要的回调对象接口定义
/**
* 包括连接成功、连接断开、发送完成、收到数据等事件    
*/
class CCallbackInterface: public IKnown
{
public:
    /**
    * 套接字连接成功
    * @param lpConnection 发生该事件的连接对象
    */
    virtual void FUNCTION_CALL_MODE OnConnect(CConnectionInterface *lpConnection) = 0;

    /**
    * 完成安全连接
    * @param lpConnection 发生该事件的连接对象
    */
    virtual void FUNCTION_CALL_MODE OnSafeConnect(CConnectionInterface *lpConnection) = 0;

    /**
    * 完成注册
    * @param lpConnection 发生该事件的连接对象
    */
    virtual void FUNCTION_CALL_MODE OnRegister(CConnectionInterface *lpConnection) = 0;

    /**
    * 连接被断开
    * @param lpConnection 发生该事件的连接对象
    */
    virtual void FUNCTION_CALL_MODE OnClose(CConnectionInterface *lpConnection) = 0;

    /**
    * 发送完成
    * @param lpConnection 发生该事件的连接对象
    * @param hSend        发送句柄
    * @param reserved1    保留字段
    * @param reserved2    保留字段
    * @param nQueuingData 发送队列中剩余个数，使用者可以用此数值控制发送的速度，即小于某值时进行发送
    * @see Send()
    */
    virtual void FUNCTION_CALL_MODE OnSent(CConnectionInterface *lpConnection, int hSend, void *reserved1, void *reserved2, int nQueuingData) = 0;

    virtual void FUNCTION_CALL_MODE Reserved1(void *a, void *b, void *c, void *d) = 0;

    virtual void FUNCTION_CALL_MODE Reserved2(void *a, void *b, void *c, void *d) = 0;

    virtual int  FUNCTION_CALL_MODE Reserved3() = 0;

    virtual void FUNCTION_CALL_MODE Reserved4() = 0;

    virtual void FUNCTION_CALL_MODE Reserved5() = 0;

    virtual void FUNCTION_CALL_MODE Reserved6() = 0;

    virtual void FUNCTION_CALL_MODE Reserved7() = 0;

    /**
    * 收到SendBiz异步发送的请求的应答
    * @param lpConnection    发生该事件的连接对象
    * @param hSend           发送句柄
    * @param lpUnPackerOrStr 指向解包器指针或者错误信息
    * @param nResult         收包结果
    * 如果nResult等于0，表示业务数据接收成功，并且业务操作成功，lpUnPackerOrStr指向一个解包器，此时应首先将该指针转换为IF2UnPacker *。
    * 如果nResult等于1，表示业务数据接收成功，但业务操作失败了，lpUnPackerOrStr指向一个解包器，此时应首先将该指针转换为IF2UnPacker *。
    * 如果nResult等于2，表示收到非业务错误信息，lpUnPackerOrStr指向一个可读的字符串错误信息。
    * 如果nResult等于3，表示业务包解包失败。lpUnPackerOrStr指向NULL。
    * 如果nResult等于4，表示业务包为空。lpUnpackerOrStr指向NULL。lpRetData这部分结果还会存在
    */
    virtual void FUNCTION_CALL_MODE OnReceivedBiz(CConnectionInterface *lpConnection, int hSend, const void *lpUnPackerOrStr, int nResult) = 0;

		/**
    * 收到SendBiz异步发送的请求的应答
    * @param lpConnection    发生该事件的连接对象
    * @param hSend           发送句柄
    * @param lpRetData 其他需要返回的应答内容，根据需要获取
    * @param lpUnPackerOrStr 指向解包器指针或者错误信息
    * @param nResult         收包结果
    * 如果nResult等于0，表示业务数据接收成功，并且业务操作成功，lpUnpackerOrStr指向一个解包器，此时应首先将该指针转换为IF2UnPacker *。
    * 如果nResult等于1，表示业务数据接收成功，但业务操作失败了，lpUnpackerOrStr指向一个解包器，此时应首先将该指针转换为IF2UnPacker *。
    * 如果nResult等于2，表示收到非业务错误信息，lpUnpackerOrStr指向一个可读的字符串错误信息。
    * 如果nResult等于3，表示业务包解包失败。lpUnpackerOrStr指向NULL。
    * 如果nResult等于4，表示业务包为空。lpUnpackerOrStr指向NULL。lpRetData这部分结果还会存在
    */
    virtual void FUNCTION_CALL_MODE OnReceivedBizEx(CConnectionInterface *lpConnection, int hSend, LPRET_DATA lpRetData, const void *lpUnpackerOrStr, int nResult) = 0;
	//20130624 xuxp 回调增加BizMessage接口
		/**
		* 收到发送时指定了ReplyCallback选项的请求的应答或者是没有对应请求的数据
		* @param lpConnection 发生该事件的连接对象
		* @param hSend        发送句柄
		* @param lpMsg        业务消息指针
		*/
	virtual void FUNCTION_CALL_MODE OnReceivedBizMsg(CConnectionInterface *lpConnection, int hSend, IBizMessage* lpMsg) = 0;

	//20150709 majc 增加回调类的析构
	~CCallbackInterface(){}

};

///T2_SDK连接对象接口
/**
* 连接的对象是线程不安全，同时一个连接最好是归于一个线程所用，不要多线程使用！！！
* 包括连接、断开、发送、接收等
*/
class CConnectionInterface: public IKnown
{
public:
    ///连接状态，可组合
    enum ConnectionStatus
    {
        Disconnected	= 0x0000, /**< 未连接 */
        Connecting		= 0x0001, /**< socket正在连接 */
        Connected		= 0x0002, /**< socket已连接 */
        SafeConnecting	= 0x0004, /**< 正在建立安全连接 */
        SafeConnected	= 0x0008, /**< 已建立安全连接 */
        Registering		= 0x0010, /**< 正注册 */
        Registered		= 0x0020, /**< 已注册 */
        Rejected		= 0x0040  /**< 被拒绝，将被关闭 */
    };

    ///接收选项（可组合，0表示接收超时时，不删除包ID，仍可再次调用RecvBiz方法来尝试接收）
    enum RecvFlags
    {
        JustRemoveHandle = 0x0001   /**< 当接收超时时，把packet_id删除 */
    };

    /**
    * 初始化连接对象
    * @param lpCallback 回调对象
    * @return 返回0表示成功，否则表示失败，通过调用GetErrorMsg可以获取详细错误信息
    * 如果应用不需要任何回调方法，则可向该方法传递NULL，而不必自定义回调类和对象
    */
    virtual int FUNCTION_CALL_MODE Create(CCallbackInterface *lpCallback) = 0;

    /**
    * 开始连接/注册
    * @param uiTimeout 超时时间，单位毫秒，0表示不等待（使用代理连接服务器时，该参数不起作用）
    * @return 返回0表示成功，否则表示失败，通过调用GetErrorMsg可以获取详细错误信息
    */
    virtual int FUNCTION_CALL_MODE Connect(unsigned int uiTimeout) = 0;

    /**
    * 断开连接
    * @return 返回0表示成功，否则表示失败，通过调用GetErrorMsg可以获取详细错误信息
    */
    virtual int FUNCTION_CALL_MODE Close() = 0;

    virtual int FUNCTION_CALL_MODE Reserved1() = 0;

    virtual int FUNCTION_CALL_MODE Reserved2() = 0;

    virtual int FUNCTION_CALL_MODE Reserved3() = 0;

    virtual int FUNCTION_CALL_MODE Reserved4() = 0;

    virtual int FUNCTION_CALL_MODE Reserved5() = 0;

    virtual int FUNCTION_CALL_MODE Reserved6() = 0;

    /**
    * 取服务器地址
    * @param lpPort 输出的服务器端口，可以为NULL
    * @return 返回服务器地址
    */
    virtual const char * FUNCTION_CALL_MODE GetServerAddress(int *lpPort) = 0;

    /**
    * 取连接状态
    * @return 返回连接状态
    */
    virtual int FUNCTION_CALL_MODE GetStatus() = 0;

    /**
    * 取服务器负载，使用者可以同时创建多个连接实例同时连接不同的服务器，根据完成连接的时间以及负载决定使用哪个服务器
    * @return 返回服务器负载（非负数），越大表示越繁忙，否则表示失败，通过调用GetErrorMsg可以获取详细错误信息
    */
    virtual int FUNCTION_CALL_MODE GetServerLoad() = 0;

    /**
    * 取错误码对应的错误信息，目前支持简体中文和英文，支持其他语言可以通过连接对象配置errormsg
    * @param nErrorCode 错误码
    * @return 返回错误信息
    */
    virtual const char * FUNCTION_CALL_MODE GetErrorMsg(int nErrorCode) = 0;

    /**
    * 取连接错误号，当连接无法与服务端完成注册时，既可通过Connect的返回值获取错误号，
    * 也可通过调用本方法来获取错误号，然后用该错误号调用GetErrorMsg可获取可读的错误信息
    * @return 返回连接错误号
    */
    virtual int FUNCTION_CALL_MODE GetConnectError() = 0;

    /**
    * 发送业务数据
    * @param iFunID      功能号
    * @param lpPacker    打包器指针
    * @param nAsy        0表示同步，否则表示异步
    * @param iSystemNo   如果iSystemNo > 0则设置系统号
    * @param nCompressID 对业务包体进行压缩的压缩算法ID，目前只支持ID = 1的压缩算法。
    * ID = 0表示不压缩。注意，压缩只是向SDK提出建议，是否真正压缩还取决于包的实际大小。
    * 同步发送的包，通过调用RecvBiz来接收，异步发送的包，当收到应答包后，自动触发回调函数OnReceivedBiz。
    * @return 返回发送句柄（正数），否则表示失败，通过调用GetErrorMsg可以获取详细错误信息
    */
    virtual int FUNCTION_CALL_MODE SendBiz(int iFunID, IF2Packer *lpPacker, int nAsy = 0, int iSystemNo = 0, int nCompressID = 1) = 0;

    /**
    * 接收业务数据
    * @param hSend            发送句柄（SendBiz的成功返回值）
    * @param lppUnPackerOrStr 如果返回值等于0，表示业务数据接收成功，并且业务操作成功，*lppUnPackerOrStr指向一个解包器，此时应首先将该指针转换为IF2UnPacker *。
    *                         如果返回值等于1，表示业务数据接收成功，但业务操作失败了，*lppUnPackerOrStr指向一个解包器，此时应首先将该指针转换为IF2UnPacker *。
    *                         如果返回值等于2，表示收到非业务错误信息，*lppUnPackerOrStr指向一个可读的字符串错误信息。
    *                         如果返回值等于3，表示业务包解包失败。*lppUnPackerOrStr原先所指向的内容不会被改变。
    * @param uiTimeout        超时时间，单位毫秒。
    * @param uiFlag           接收选项，0表示接收超时后仍可继续调用RecvBiz来接收，
    *                         JustRemoveHandle表示当接收超时后，把hSend相关数据删除
    * @return 小于0表示RecvBiz操作本身失败，通过调用GetErrorMsg可以获取详细错误信息
    * 注意！外部指针所指向的解包器的内存由SDK内部管理，外部切勿释放！
	* 注意！lppUnPackerOrStr对应的解包器是临时的，上层不可以缓存指针，再次调用这个连接的RecvBiz，指针指向的内容就会改变
	* 如果要拷贝，需要调用解包器的GetPackBuf方法，二进制拷贝出去，其他线程需要再解包
    */
    virtual int FUNCTION_CALL_MODE RecvBiz(int hSend, void **lppUnPackerOrStr, unsigned uiTimeout = 1000, unsigned uiFlag = 0) = 0;
    
   //20101228 xuxp 新增发送和接受的两个接口函数，用于订阅和推送
	/**
    * 发送业务数据
    * @param iFunID      功能号
    * @param lpPacker    打包器指针
	* @param svrName     指定中间件的节点
    * @param nAsy        0表示同步，否则表示异步。
    * @param iSystemNo   如果iSystemNo > 0则设置系统号
    * @param nCompressID 对业务包体进行压缩的压缩算法ID，目前只支持ID = 1的压缩算法。
    * ID = 0表示不压缩。注意，压缩只是向SDK提出建议，是否真正压缩还取决于包的实际大小。
    * 同步发送的包，通过调用RecvBizEx来接收，异步发送的包，当收到应答包后，自动触发回调函数OnReceivedBizEx。
    * @param branchNo  营业部号。
    * @param lpRequest  请求里面的其他内容，根据结构体定义赋值。
    * @return 返回发送句柄（正数），否则表示失败，通过调用GetErrorMsg可以获取详细错误信息
    */
    virtual int FUNCTION_CALL_MODE SendBizEx(int iFunID, IF2Packer *lpPacker,char* svrName, int nAsy = 0, int iSystemNo = 0, int nCompressID = 1,int branchNo=0,LPREQ_DATA lpRequest=NULL) = 0;
    
    /**
    * 接收业务数据
    * @param hSend            发送句柄（SendBiz的成功返回值）
    * @param lppUnPackerOrStr 如果返回值等于0，表示业务数据接收成功，并且业务操作成功，*lppUnPackerOrStr指向一个解包器，此时应首先将该指针转换为IF2UnPacker *。
    *                         如果返回值等于1，表示业务数据接收成功，但业务操作失败了，*lppUnPackerOrStr指向一个解包器，此时应首先将该指针转换为IF2UnPacker *。
    *                         如果返回值等于2，表示收到非业务错误信息，*lppUnPackerOrStr指向一个可读的字符串错误信息。
    *                         如果返回值等于3，表示业务包解包失败。*lppUnPackerOrStr原先所指向的内容不会被改变。
    * @param lpRetData 其他需要返回的应答内容，根据需要获取
    * @param uiTimeout        超时时间，单位毫秒，0表示不等待。
    * @param uiFlag           接收选项，0表示接收超时后仍可继续调用RecvBiz来接收，
    *                         JustRemoveHandle表示当接收超时后，把hSend相关数据删除
    * @return 小于0表示RecvBizEx操作本身失败，通过调用GetErrorMsg可以获取详细错误信息
    * 注意！外部指针所指向的解包器的内存由SDK内部管理，外部切勿释放！
	* 注意！外部指针所指向的LPRET_DATA的内存由SDK内部管理，外部切勿释放！
	* 注意！lppUnPackerOrStr对应的解包器和LPRET_DATA都是临时的，上层不可以缓存指针，再次调用这个连接的RecvBizEx，这两个指针指向的内容就会改变
	* 如果要拷贝，需要调用解包器的GetPackBuf方法，二进制拷贝出去，其他线程需要再解包；
	* LPRET_DATA拷贝，就需要做结构体复制
    */
    virtual int FUNCTION_CALL_MODE RecvBizEx(int hSend, void **lppUnpackerOrStr, LPRET_DATA* lpRetData, unsigned uiTimeout = 1000, unsigned uiFlag = 0) = 0;


	//20101228 xuxp 新增Create函数，来保证回调用新的OnReceivedBizEx的接口
	/**
	* 初始化连接对象
	* @param lpCallback 回调对象
	* @return 返回0表示成功，否则表示失败，通过调用GetErrorMsg可以获取详细错误信息
    * 如果应用不需要任何回调方法，则可向该方法传递NULL，而不必自定义回调类和对象
	*/
	virtual int FUNCTION_CALL_MODE CreateEx(CCallbackInterface *lpCallback) = 0;
	
	
	//20120111 dongpf 新增GetRealAddress函数，来获取服务端上自己的ip地址和端口
	/**
	* 获取ip地址和端口
	* @return 获取ip地址和端口，格式：ip地址+端口
	*/
	virtual const char* FUNCTION_CALL_MODE GetRealAddress() = 0;
	
	
	virtual int FUNCTION_CALL_MODE Reserved8() = 0;
	virtual int FUNCTION_CALL_MODE Reserved9() = 0;
	
	//20130527 xuxp 新增GetSelfAddress函数，来获取自己本地的IP和端口
	/**
	* 获取ip地址和端口
	* @return 获取ip地址和端口，格式：ip地址+端口
	*/
	virtual const char* FUNCTION_CALL_MODE GetSelfAddress() = 0;

	//20130529 xuxp 新增GetSelfMac函数，来获取自己本地使用的网卡MAC
	/**
	* 获取MAC地址
	* @return MAC的地址字符串格式，类似“D067E5556D83”,中间没有分隔符
	*/
	virtual const char* FUNCTION_CALL_MODE GetSelfMac() = 0;
	
	//20130609 xuxp 新增订阅发布接口
	///////////////////////////////////下面增加订阅发布的接口///////////////////////////////////////

	/**
    * 创建一个订阅者
    * @param lpCallback 回调接口
    * @param SubScribeName 订阅者名字，多订阅者的名字必须不一样，不可以相同.最大长度32个字节
    * @param iTimeOut 超时时间
    * @param iInitRecvQLen 初始化接收队列的长度
    * @param iStepRecvQLen 接受队列的扩展步长
    * @return 返回订阅接口实例，一个会话接口对应一个回调.
    */
    virtual CSubscribeInterface* FUNCTION_CALL_MODE NewSubscriber(CSubCallbackInterface *lpCallback,char* SubScribeName,int iTimeOut,
        int iInitRecvQLen=INIT_RECVQ_LEN,int iStepRecvQLen=STEP_RECVQ_LEN) = 0;
    
   /**
    * 获取发布者
    * @param PublishName 发布者业务名
    * @param msgCount 本地缓存消息的个数
	  * @param iTimeOut 初始化的时候的超时时间
    * @param bResetNo 是否重置序
    * @return 返回发送接口实例，返回对应的指针
    */
    //virtual CPublishInterface* FUNCTION_CALL_MODE GetPublisher(int msgCount,int iTimeOut,bool bResetNo = false) = 0;
    virtual CPublishInterface* FUNCTION_CALL_MODE NewPublisher(char* PublishName,int msgCount,int iTimeOut,bool bResetNo = false) = 0;
    
  


   /**
    * 获取服务端的所有主题信息
    * @param byForce 是否强制从后台获取
    * @param iTimeOut 超时时间
    * @return 成功就返回所有主题信息
    * @note 解包器外面需要调用release接口进行释放.
    * @note packer返回字段
    * - TopicName
    * - TopicNo
    * - ReliableLevel
    * - IssuePriority
    * - MsgLifetime
    * - Stutas 
    * - TickStrategy 
    * - BusinessVerify
    * - Local
    * - FilterField1 
    * - FilterField2 
    * - FilterField3 
    * - FilterField4 
    * - FilterField5 
    * - FilterField6
	* - FilterField7 
	* - FilterField8 
	* - FilterField9 
	* - FilterField10 
	* - FilterField11 
	* - FilterField12
	* - FilterField13 
	* - FilterField14 
	* - FilterField15 
	* - FilterField16
    * - SubscribeStr 
    * - PublishStr
	
    */
    virtual IF2UnPacker* FUNCTION_CALL_MODE GetTopic(bool byForce,int iTimeOut) = 0;
	
	/**
	* 获取订阅发布的最后错误
	*/
	virtual const char* FUNCTION_CALL_MODE GetMCLastError() = 0;
	////////////////////////////////////////////////////////////////////////////////

	//20130624 xuxp 连接接口增加下面三个接口，用来作为服务端的接口，客户端开发也推荐使用
	///////////////////////////////////新的一套操作接口///////////////////////////////////////
	/**
	* 初始化连接对象
	* @param lpCallback 回调对象
	* @return 返回0表示成功，否则表示失败，通过调用GetErrorMsg可以获取详细错误信息
    * 如果应用不需要任何回调方法，则可向该方法传递NULL，而不必自定义回调类和对象
	*/
	virtual int FUNCTION_CALL_MODE Create2BizMsg(CCallbackInterface *lpCallback) = 0;

	/**
    * 发送业务数据
    * @param lpMsg       业务消息接口指针
    * @param nAsy        0表示同步，否则表示异步。
    * 同步发送的包，通过调用RecvBizMsg来接收，异步发送的包，当收到应答包后，自动触发回调函数OnReceivedBizMsg。
    * @return 返回发送句柄（正数），否则表示失败，通过调用GetErrorMsg可以获取详细错误信息
    */
	virtual int FUNCTION_CALL_MODE SendBizMsg(IBizMessage* lpMsg,int nAsy = 0) = 0;
	
	/**
	* 接收数据
	* @param hSend     发送句柄
	* @param lpMsg	   收到业务消息指针的地址
	* @param uiTimeout 超时时间，单位毫秒，0表示不等待
	* @param uiFlag    接收选项，0表示接收超时后仍可继续调用Receive来接收，
    *                  JustRemoveHandle表示当接收超时时，把packet_id删除（以后再收到，则会以异步的方式收到）
	* @return 返回0表示成功，否则表示失败，通过调用GetErrorMsg可以获取详细错误信息
	* 注意！外部指针所指向的IBizMessage的内存由SDK内部管理，外部切勿释放！
	* 注意！lpMsg对应的消息指针是临时的，上层不可以缓存指针，再次调用这个连接的RecvBizMsg，这个指针指向的内容就会改变
	* 如果要拷贝，需要调用IBizMessage的GetBuff方法，二进制拷贝出去，其他线程需要再调用SetBuff；
	*/
	virtual int FUNCTION_CALL_MODE RecvBizMsg(int hSend, IBizMessage** lpMsg, unsigned uiTimeout = 1000, unsigned uiFlag = 0) = 0;
	
	//20141117 majc 增加文件更新目录过滤字段
	/**
    * 获取文件更新,一个连接里面只有一个文件更新，如果存在就返回之前的接口
    * @param szTopicName 文件更新主题，来自于服务端消息中心文件更新主题 
	* @param lpCallBack 回调接口
	* @param szScanDir 扫描文件根目录
    * @param szUpdateDir 文件更新存放根目录
	* @param iTimeOut 超时时间
	* @param szDirFilter 目录过滤条件，如果有多个目录用;号隔开
    * @return 返回文件更新接口指针
    */
	virtual CFileUpdateInterface* FUNCTION_CALL_MODE NewFileUpdate(const char* szTopicName,CFileUpdateCallbackInterface* lpCallBack ,const char* szScanDir,const char* szUpdateDir,unsigned int uiTimeOut = 5000, const char * szDirFilter = NULL) = 0;

	/**
	* 获取文件更新的最后错误
	*/
	virtual const char* FUNCTION_CALL_MODE GetFileUpdateLastError() = 0;
	
	//20140618 majc 增加获取最后一个应答错误的详细信息接口
	/**
	* 取返回错误消息的详细信息
	* @param bAsyError 0表示同步(默认)，否则表示异步。
	* @return 返回详细错误信息
	* @note 返回信息格式：packType:xxx;funtionId:xxx;branchNo:zxx;systemNo:xxx;subSystemNO:xxx;packId:xxx;routerInfo:xxx,xxx,xxx,xxx,xxx,xxx;sendPath:xxx,xxx,xxx,xxx,xxx,xxx;returnCode:xxx;errorNo:xxx;errorInfo:xxx
	* packType-包类型
	* funtionId-功能号
	* branchNo-分支号
	* systemNo-系统号
	* subSystemNO-子系统号
	* packId-包序号
	* routerInfo-目标路由
	* sendPath-发送者路由
	* returnCode-返回错误码
	* errorNo-错误号
	* errorInfo-错误信息
	* 调用说明：1：同步调用时，方法Receive返回的lppData解析ESBMessage后RetuenCode不为0时调用；方法RecvBiz、RecvBizEx是在返回值为1、2、3、4时调用；方法RecvBizMsg是在GetReturnCode()不为0时调用
	*           2：异步调用时，回调OnReceived的lpData解析ESBMessage后RetuenCode不为0时调用；回调OnReceivedBiz、OnReceivedBizEx的nResult为1、2、3、4时调用；回调OnReceivedBizMsg的lpMsg在GetReturnCode()不为0时调用
	*/
	virtual const char * FUNCTION_CALL_MODE GetLastAnsError(bool bAsyError = 0) = 0;

	////////////////////////////////////////////////////////////////////////////////
	//20150209 majc 新增订阅接口
	/**
    * 创建一个订阅者
    * @param lpCallback 回调接口
    * @param SubScribeName 订阅者名字，多订阅者的名字必须不一样，不可以相同.最大长度32个字节
	* @param subRoterInfo  创建时指定路由
    * @param iTimeOut 超时时间
    * @param iInitRecvQLen 初始化接收队列的长度
    * @param iStepRecvQLen 接受队列的扩展步长
    * @return 返回订阅接口实例，一个会话接口对应一个回调.
    */
    virtual CSubscribeInterface* FUNCTION_CALL_MODE NewSubscriberEx(CSubCallbackInterface *lpCallback,char* SubScribeName,SUB_ROUTER_INFO &subRoterInfo,int iTimeOut,
        int iInitRecvQLen=INIT_RECVQ_LEN,int iStepRecvQLen=STEP_RECVQ_LEN) = 0;
	//20150514 majc 增加连接user_token设置
	virtual void FUNCTION_CALL_MODE SetUserToken(const char* szUserToken) = 0;
	////////////////////////////////////////////////////////////////////////////////

	//20150610 xuxp 新增集群订阅者创建的接口
	/**
    * 创建一个集群订阅者
    * @param lpCallback 回调接口
    * @param SubScribeName 订阅者名字，多订阅者的名字必须不一样，不可以相同.最大长度32个字节
    * @param iTimeOut 超时时间
    * @param iInitRecvQLen 初始化接收队列的长度
    * @param iStepRecvQLen 接受队列的扩展步长
    * @return 返回订阅接口实例，一个会话接口对应一个回调.
    */
    virtual CSubscribeInterface* FUNCTION_CALL_MODE NewClusterSubscriber(CSubCallbackInterface *lpCallback,char* SubScribeName,SUB_ROUTER_INFO &subRoterInfo,int iTimeOut,
        int iInitRecvQLen=INIT_RECVQ_LEN,int iStepRecvQLen=STEP_RECVQ_LEN) = 0;

    ///20150812 liuzl 返回所连接的服务器的节点名,如ar#0,支持F5
	///20160614 zhouwh 修改接口定义，增加FUNCTION_CALL_MODE
    //virtual const char *GetServerNodeName() = 0;
	virtual const char * FUNCTION_CALL_MODE GetServerNodeName() = 0;

	//20160614 zhouwh 主动回收同步模式的队列缓存
	// note: 主动回收模式下，该接口必须调用，否则存在内存泄露
	/**
		@param lpData 同步receive时返回的数据指针
	*/
	virtual void FUNCTION_CALL_MODE RecycleDataBuf(void *lpData) = 0;

	//20161028 majc  增加接口设置唯一序号前缀
	/**
	* @param lpPrefix 唯一序号前缀，最大支持255字节
	*/
	virtual void FUNCTION_CALL_MODE SetUniquePrefix(const char* lpPrefix) = 0;

	//20161223 huxb  增加主动断开连接接口
	/**
	* @param bSafe 是否为安全停止，默认为非安全停止
	* @param uiTimeout 安全停止超时时间，单位为ms
	*/
	virtual int FUNCTION_CALL_MODE ActiveClose(bool bSafe = false, unsigned int uiTimeout = 5000) = 0;

	//20161223 huxb  增加重新设置服务器地址接口
	//注：必须单线程调用
	/**
	* @param szServers 新的服务器地址
	*/
	virtual int FUNCTION_CALL_MODE SetServers(const char * szServers) = 0;
};

extern "C"
{
    /**
	* 获取T2_SDK的版本号
	* @return 当前T2_SDK的版本号
	* 譬如：版本为0x10000002表示1.0.0.2
	*/
    int FUNCTION_CALL_MODE GetVersionInfo();

    /**
	* 获取一个实现CConfigInterface接口的类的指针
	* @return 实现CConfigInterface接口的类的指针
	*/
CConfigInterface* FUNCTION_CALL_MODE NewConfig();

    /**
	* 获取一个实现CConnectionInterface接口的类的指针
	* @param CConfigInterface 实现CConfigInterface接口的类的指针
	* @return实现CConnectionInterface接口的类的指针
	*/
CConnectionInterface* FUNCTION_CALL_MODE NewConnection(CConfigInterface *lpConfig);

/**
* @param int iVersion 业务包格式版本(取值:1 字串版,其他值 0x20版)
* 推荐使用0x20版
* @return IPacker * 打包器接口指针
*/
IF2Packer * FUNCTION_CALL_MODE NewPacker(int iVersion);

/**
* @param void * lpBuffer 要解包的数据（不含AR通信包头）
* @param unsigned int iLen 数据长度
* @return IUnPacker * 版本2结果集操作接口指针
*/
IF2UnPacker * FUNCTION_CALL_MODE NewUnPacker(void * lpBuffer, unsigned int iLen);

/**
* @param void * lpBuffer 要解包的数据（不含AR通信包头）
* @param unsigned int iLen 数据长度
* @return IUnPacker * 版本1结果集操作接口指针
*/
IF2UnPacker * FUNCTION_CALL_MODE NewUnPackerV1(void * lpBuffer, unsigned int iLen);

/**
* @param void * lpBuffer 要解包的数据（不含AR通信包头）
* @return 1表示版本1的结果集数据，0x21~0x2F 版本2的结果集数据
*/
int FUNCTION_CALL_MODE GetPackVersion(const void *lpBuffer);
/**
* @param char *EncodePass 传出的散列结果，字符串，长度不超过16（包括'\0'）
* @param const char* Password 传入的待散列的密码
* @param int nReserve 保留参数，采用默认值
* @return char * 传出的散列结果地址，同EncodePass
*/
char * FUNCTION_CALL_MODE Encode(char *EncodePass, const char* Password, int nReserve = 0 );


/**
*利用一部提供的加密函数来对密码进行加密
* @param const char* pIn 传入的待加密的字符串
* @param const char* pOut 输出参数，长度和传入的字符串大小一样，由外部申请
* @return 
*/
int FUNCTION_CALL_MODE EncodeEx(const char *pIn, char *pOut);


/**
* 构造一个过滤器接口指针
* @return 返回NULL表示失败.
*/
CFilterInterface* FUNCTION_CALL_MODE NewFilter();
    
/**
* 构造一个订阅属性接口指针
* @return 返回NULL表示失败.
*/
CSubscribeParamInterface* FUNCTION_CALL_MODE NewSubscribeParam();

//20130625 xuxp 构造业务消息
IBizMessage* FUNCTION_CALL_MODE NewBizMessage();

//20160317 zhouwh 构造业务消息，添加压缩标志
IBizMessage* FUNCTION_CALL_MODE NewBizMessageEx(int nCompressID = 1);

//20161027 majc 导出测速端口
/**
*lpRequest：传入字段：address port
*lpResult： 传出字段：成功：conn_count net_delay net_speed  last_error 失败：error_no error_info
*uiTimeOut：超时时间
* 返回值：0 成功，非0失败
*/
int FUNCTION_CALL_MODE GetMultiNetWorkSpeed(IF2UnPacker * lpRequest, IF2Packer * lpResult, unsigned int uiTimeOut);
}

#endif
