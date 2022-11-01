# Swordfish-MDS API    {#mainpage}

箭鱼行情数据服务系统API使用说明


---
### Quick Start

#### 1.1 示例代码

- 参见 samples/mds_sample 目录下的样例文件
	- 配置文件样例 <mds_client_sample.conf>
	- TCP行情对接的样例代码 (基于异步API实现) <01_mds_async_tcp_sample.c>
	- TCP行情对接的样例代码 (精简版本, 基于异步API实现) <02_mds_async_tcp_sample.minimal.c>
	- UDP行情对接的样例代码 (基于异步API实现) <03_mds_async_udp_sample.c>
	- TCP行情对接的样例代码 (基于同步API实现) <04_mds_sync_tcp_sample.c>
	- UDP行情对接的样例代码 (基于同步API实现) <05_mds_sync_udp_sample.c>
	- 证券静态信息查询和快照行情查询的样例代码 <06_mds_query_sample.c>
	- 用于样例代码编译的 Makefile <Makefile.sample>

04_mds_sync_tcp_sample.c 摘录如下：
~~~{.c}

/**
 * 通过证券代码列表, 重新订阅行情数据 (根据代码后缀区分所属市场, 如果没有指定后缀, 则默认为上证股票)
 *
 * @param   pTcpChannel         会话信息
 * @param   pCodeListString     证券代码列表字符串 (以空格或逗号/分号/竖线分割的字符串)
 * @return  TRUE 成功; FALSE 失败
 */
static BOOL
MdsApiSample_ResubscribeByCodePostfix(MdsApiSessionInfoT *pTcpChannel,
        const char *pCodeListString) {
    return MdsApi_SubscribeByString(pTcpChannel,
            pCodeListString, (char *) NULL,
            MDS_EXCH_SSE, MDS_MD_PRODUCT_TYPE_STOCK, MDS_SUB_MODE_SET,
            MDS_SUB_DATA_TYPE_L1_SNAPSHOT
                    | MDS_SUB_DATA_TYPE_L2_SNAPSHOT
                    | MDS_SUB_DATA_TYPE_L2_BEST_ORDERS);
}


/**
 * 进行消息处理的回调函数
 *
 * @param   pSessionInfo    会话信息
 * @param   pMsgHead        消息头
 * @param   pMsgBody        消息体数据
 * @param   pCallbackParams 外部传入的参数
 * @return  大于等于0，成功；小于0，失败（错误号）
 */
static int32
MdsApiSample_HandleMsg(MdsApiSessionInfoT *pSessionInfo,
        SMsgHeadT *pMsgHead, void *pMsgBody, void *pCallbackParams) {
    MdsMktRspMsgBodyT   *pRspMsg = (MdsMktRspMsgBodyT *) pMsgBody;

    /*
     * 根据消息类型对行情消息进行处理
     */
    switch (pMsgHead->msgId) {
    case MDS_MSGTYPE_L2_MARKET_DATA_SNAPSHOT:
    case MDS_MSGTYPE_L2_BEST_ORDERS_SNAPSHOT:
        /* 处理Level2快照行情消息 */
        printf("... 接收到Level2快照行情消息 (exchId[%hhu], instrId[%d])\n",
                pRspMsg->mktDataSnapshot.head.exchId,
                pRspMsg->mktDataSnapshot.head.instrId);
        break;

    case MDS_MSGTYPE_L2_TRADE:
    case ...:
         ...
    }

    return 0;
}


int
main(int argc, char *argv[]) {
    /* 配置文件 */
    static const char   THE_CONFIG_FILE_NAME[] = "mds_client_sample.conf";
    /* 尝试等待行情消息到达的超时时间 (毫秒) */
    static const int32  THE_TIMEOUT_MS = 1000;

    MdsApiClientEnvT    cliEnv = {NULLOBJ_MDSAPI_CLIENT_ENV};
    int32               ret = 0;

    /* 初始化客户端环境 (配置文件参见: mds_client_sample.conf) */
    if (! MdsApi_InitAllByConvention(&cliEnv, THE_CONFIG_FILE_NAME)) {
        return -1;
    }

    /* 根据证券代码列表重新订阅行情 (根据代码后缀区分所属市场) */
    if (! MdsApiSample_ResubscribeByCodePostfix(&cliEnv.tcpChannel,
            "600000.SH, 600001.SH, 000001.SZ, 0000002.SZ")) {
        goto ON_ERROR;
    }

    while (1) {
        /* 等待行情消息到达, 并通过回调函数对消息进行处理 */
        ret = MdsApi_WaitOnMsg(&cliEnv.tcpChannel, THE_TIMEOUT_MS,
                MdsApiSample_HandleMsg, NULL);
        if (__spk_unlikely(ret < 0)) {
            if (__spk_likely(SPK_IS_NEG_ETIMEDOUT(ret))) {
                /* 执行超时检查 (检查会话是否已超时) */
                continue;
            }

            if (SPK_IS_NEG_EPIPE(ret)) {
                /* 连接已断开 */
            }
            goto ON_ERROR;
        }
    }

    MdsApi_LogoutAll(&cliEnv, TRUE);
    return 0;

ON_ERROR:
    MdsApi_DestoryAll(&cliEnv);
    return -1;
}

~~~


#### 1.2 示例代码的编译和运行

1. 进入样例代码目录
	- ``cd mds_libs-xxx/samples/mds_sample/``

2. 编译代码
	- ``make -f Makefile.sample``

3. 修改配置文件，确认服务地址、用户名等正确
	- ``vi mds_client_sample.conf``

4. 运行样例程序
	- ``./mds_subscribe_sample``
	- ``./mds_async_api_sample``
	- ``./mds_async_udp_sample``


---
### 版本升级指引及修改历史

- 版本升级指引参见 <@ref update_guide>
- 版本修改历史参见 <@ref changelog>


---
### 常见问题

- 价格和金额单位
	- MDS中的所有价格均为`int32`类型的整型数值，单位精确到元后四位, 即: 1元=10000
	- MDS中的所有金额均为`int64`类型的整型数值，单位精确到元后四位, 即: 1元=10000

- 份额单位
	- MDS中的所有委托数量、成交数量等份额单位均为`int32`或`int64`类型的整型数值，不带小数位
	- **注意:** 上海债券的份额单位是 <b>'手'</b>，而不是 '张'，与其它不同

- MDS中的行情时间(updateTime)是交易所时间吗？
	- 是的，该时间来源于交易所，是行情数据的生成时间或者上游发送时间（如果采集不到行情生成时间的话）


---
### MDS错误码表

| 错误码 | 错误说明                            |
| :---- | :--------------------------------- |
| 1001  | 报文格式错误                       |
| 1002  | 当前主机不是主节点                  |
| 1003  | 主存库操作失败                     |
| 1004  | 因状态等基础数据不匹配，无法更新数据   |
| 1005  | 协议版本不兼容                     |
| 1006  | 数据不存在                         |
| 1007  | 非服务开放时间                     |
| 1008  | 非法的定位游标                     |
| 1009  | 非法的客户端登录用户名称             |
| 1010  | 非法的证券代码                     |
| 1011  | 非法的客户代码                     |
| 1012  | 非法的客户端类型                    |
| 1013  | 客户端已被禁用                     |
| 1014  | 客户端密码不正确                    |
| 1015  | 客户端重复登录                     |
| 1016  | 客户端连接数量过多                  |
| 1017  | 客户端未经授权操作他人账户           |
| 1018  | 数据超出修改范围                    |
| 1019  | 非法的应用系统名称                  |
| 1020  | 查询条件不匹配                     |
| 1021  | 客户端ip/mac地址格式错误            |
| 1022  | 尚不支持或尚未开通此业务             |
| 1029  | 密码未改变                         |
| 1031  | 非法的加密类型                     |
| 1033  | 无可用节点                         |
| 1034  | 密码强度不足                       |
| 1035  | 非法的产品类型                     |
| 1036  | 未通过黑白名单检查                 |
| 1037  | 集群编号不匹配                 |
| 1038  | 无此操作权限                 |
| 1301  | 行情订阅失败                       |
