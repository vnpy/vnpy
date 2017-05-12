#ifndef API_ERROR_H
#define API_ERROR_H
#define ERR_SUCCESS				0	//成功
#define ERR_UNKNOWN				-1	//未知错误
#define ERR_API_NOT_INITED		-2	//API未启动
#define ERR_NOT_CONNECTED		-3	//未连接
#define ERR_NOT_LOGIN			-4	//未登录
#define ERR_ALREADY_LOGIN		-5	//已经登录
#define ERR_TIME_OUT			-6	//超时
#define ERR_STREAM_CONTROL		-7//受到流控
#define ERR_LOGON_GATEWAY		-8//登陆网关失败
#define ERR_REGISTER_QUOT		-9//注册行情推送服务失败
#define ERR_QUERY_QUOTSERVER_LIST   -10//查询行情服务站点失败
#define ERR_LOGOUT_BACK         -11            //登出失败,后台返回
#define ERR_LOGOUT_FORE         -12           //登出失败,前台返回
#define ERR_QRY_DATA            -13            //查询错误
#define ERR_ORDER_INSERT        -14            //下单失败
#define ERR_ORDER_CANCEL        -15            //撤单失败
#define ERR_EMPTY_PUBLICKEY		-16			   //公钥为空
#define ERR_PASSWD_FORMAT       -17			   //密码格式不正确
#define ERR_REPEAT_INITED       -18         //api重复初始化
#define ERR_NET_INIT            -19         //网络初始化错误
#define ERR_GATEWAY_INIT        -20         //网关初始化错误
#define ERR_CHECK_VERSION       -21         //版本验证失败
#endif
