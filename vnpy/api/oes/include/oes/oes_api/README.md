# Swordfish-OES API    {#mainpage}

箭鱼快速订单系统API使用说明


---
### Quick Start

#### 1.1 示例代码

- 参见 oes_api/samples/c_sample 目录下的样例文件
	- 配置文件样例 <oes_client_sample.conf>
	- 代码样例 <oes_client_sample.c>
	- 用于样例代码编译的 <Makefile.sample>

oes_client_sample.c 摘录如下：
~~~{.c}

/**
 * 发送委托请求
 *
 * 提示:
 * - 可以通过 OesApi_GetClEnvId() 方法获得到当前通道所使用的客户端环境号(clEnvId), 如:
 *   <code>int8 clEnvId = OesApi_GetClEnvId(pOrdChannel);</code>
 *
 * @param   pOrdChannel     委托通道的会话信息
 * @param   mktId           市场代码 (必填) @see eOesMarketIdT
 * @param   pSecurityId     股票代码 (必填)
 * @param   pInvAcctId      股东账户代码 (可不填)
 * @param   ordType         委托类型 (必填) @see eOesOrdTypeT, eOesOrdTypeShT, eOesOrdTypeSzT
 * @param   bsType          买卖类型 (必填) @see eOesBuySellTypeT
 * @param   ordQty          委托数量 (必填, 单位为股/张)
 * @param   ordPrice        委托价格 (必填, 单位精确到元后四位，即1元 = 10000)
 * @return  大于等于0，成功；小于0，失败（错误号）
 */
static inline int32
_OesApiSample_SendOrderReq(OesApiSessionInfoT *pOrdChannel,
        uint8 mktId, const char *pSecurityId, const char *pInvAcctId,
        uint8 ordType, uint8 bsType, int32 ordQty, int32 ordPrice) {
    OesOrdReqT          ordReq = {NULLOBJ_OES_ORD_REQ};

    SLOG_ASSERT2(pOrdChannel
            && mktId > 0 && mktId < __OES_MKT_ID_MAX
            && pSecurityId && ordType < __OES_ORD_TYPE_FOK_MAX
            && bsType > 0 && bsType < __OES_BS_TYPE_MAX_TRADING
            && ordQty > 0 && ordPrice >= 0,
            "pOrdChannel[%p], mktId[%hhu], pSecurityId[%s], " \
            "ordType[%hhu], bsType[%hhu], ordQty[%d], ordPrice[%d]",
            pOrdChannel, mktId, pSecurityId ? pSecurityId : "NULL",
            ordType, bsType, ordQty, ordPrice);

    ordReq.clSeqNo = (int32) ++pOrdChannel->lastOutMsgSeq;
    ordReq.mktId = mktId;
    ordReq.ordType = ordType;
    ordReq.bsType = bsType;

    strncpy(ordReq.securityId, pSecurityId, sizeof(ordReq.securityId) - 1);
    if (pInvAcctId) {
        /* 股东账户可不填 */
        strncpy(ordReq.invAcctId, pInvAcctId, sizeof(ordReq.invAcctId) - 1);
    }

    ordReq.ordQty = ordQty;
    ordReq.ordPrice = ordPrice;

    return OesApi_SendOrderReq(pOrdChannel, &ordReq);
}


/**
 * 发送撤单请求
 *
 * @param   pOrdChannel     委托通道的会话信息
 * @param   mktId           被撤委托的市场代码 (必填) @see eOesMarketIdT
 * @param   pSecurityId     被撤委托的股票代码 (选填, 若不为空则校验待撤订单是否匹配)
 * @param   pInvAcctId      被撤委托的股东账户代码 (选填, 若不为空则校验待撤订单是否匹配)
 * @param   origClSeqNo     被撤委托的流水号 (若使用 origClOrdId, 则不必填充该字段)
 * @param   origClEnvId     被撤委托的客户端环境号 (小于等于0, 则使用当前会话的 clEnvId)
 * @param   origClOrdId     被撤委托的客户订单编号 (若使用 origClSeqNo, 则不必填充该字段)
 * @return  大于等于0，成功；小于0，失败（错误号）
 */
static inline int32
_OesApiSample_SendOrderCancelReq(OesApiSessionInfoT *pOrdChannel,
        uint8 mktId, const char *pSecurityId, const char *pInvAcctId,
        int32 origClSeqNo, int8 origClEnvId, int64 origClOrdId) {
    OesOrdCancelReqT    cancelReq = {NULLOBJ_OES_ORD_CANCEL_REQ};

    SLOG_ASSERT2(pOrdChannel && mktId > 0 && mktId < __OES_MKT_ID_MAX,
            "pOrdChannel[%p], mktId[%hhu]", pOrdChannel, mktId);

    cancelReq.clSeqNo = (int32) ++pOrdChannel->lastOutMsgSeq;
    cancelReq.mktId = mktId;

    if (pSecurityId) {
        /* 撤单时被撤委托的股票代码可不填 */
        strncpy(cancelReq.securityId, pSecurityId, sizeof(cancelReq.securityId) - 1);
    }

    if (pInvAcctId) {
        /* 撤单时被撤委托的股东账户可不填 */
        strncpy(cancelReq.invAcctId, pInvAcctId, sizeof(cancelReq.invAcctId) - 1);
    }

    cancelReq.origClSeqNo = origClSeqNo;
    cancelReq.origClEnvId = origClEnvId;
    cancelReq.origClOrdId = origClOrdId;

    return OesApi_SendOrderCancelReq(pOrdChannel, &cancelReq);
}


/**
 * 对执行报告消息进行处理的回调函数
 *
 * @param   pRptChannel     回报通道的会话信息
 * @param   pMsgHead        消息头
 * @param   pMsgBody        消息体数据
 * @param   pCallbackParams 外部传入的参数
 * @return  大于等于0，成功；小于0，失败（错误号）
 */
static inline int32
_OesApiSample_HandleReportMsg(OesApiSessionInfoT *pRptChannel,
        SMsgHeadT *pMsgHead, void *pMsgBody, void *pCallbackParams) {
    OesRspMsgBodyT      *pRspMsg = (OesRspMsgBodyT *) pMsgBody;
    OesRptMsgT          *pRptMsg = &pRspMsg->rptMsg;

    assert(pRptChannel && pMsgHead && pRspMsg);

    switch (pMsgHead->msgId) {
    case OESMSG_RPT_ORDER_INSERT:               /* OES委托已生成 (已通过风控检查) */
        printf(">>> Recv OrdInsertRsp: {clSeqNo: %d, clOrdId: %lld}\n",
                pRptMsg->rptBody.ordInsertRsp.clSeqNo,
                pRptMsg->rptBody.ordInsertRsp.clOrdId);
        break;

    case OESMSG_RPT_BUSINESS_REJECT:            /* OES业务拒绝 (未通过风控检查等) */
        printf(">>> Recv OrdRejectRsp: {clSeqNo: %d, ordRejReason: %d}\n",
                pRptMsg->rptBody.ordRejectRsp.clSeqNo,
                pRptMsg->rptHead.ordRejReason);
        break;

    case OESMSG_RPT_ORDER_REPORT:               /* 交易所委托回报 (包括交易所委托拒绝、委托确认和撤单完成通知) */
        printf(">>> Recv OrdCnfm: {clSeqNo: %d, clOrdId: %lld}\n",
                pRptMsg->rptBody.ordCnfm.clSeqNo,
                pRptMsg->rptBody.ordCnfm.clOrdId);
        break;

    case OESMSG_RPT_REPORT_SYNCHRONIZATION:     /* 回报同步响应 */
    case ...:
         ...
    }

    return 0;
}


/**
 * 回报采集处理 (可以做为线程的主函数运行)
 *
 * @param   pRptChannel     回报通道的会话信息
 * @return  TRUE 处理成功; FALSE 处理失败
 */
void*
OesApiSample_ReportThreadMain(OesApiClientEnvT *pClientEnv) {
    static const int32  THE_TIMEOUT_MS = 1000;

    OesApiSessionInfoT  *pRptChannel = &pClientEnv->rptChannel;
    int32               ret = 0;

    while (1) {
        /* 等待回报消息到达, 并通过回调函数对消息进行处理 */
        ret = OesApi_WaitReportMsg(pRptChannel, THE_TIMEOUT_MS,
                _OesApiSample_HandleReportMsg, NULL);
        if (__spk_unlikely(ret < 0)) {
            if (__spk_likely(SPK_IS_NEG_ETIMEDOUT(ret))) {
                /* 执行超时检查 (检查会话是否已超时) */
                if (__spk_likely(_OesApiSample_OnTimeout(pClientEnv) == 0)) {
                    continue;
                }

                /* 会话已超时 */
                goto ON_ERROR;
            }

            if (SPK_IS_NEG_EPIPE(ret)) {
                /* 连接已断开 */
            }
            goto ON_ERROR;
        }
    }

    return (void *) TRUE;

ON_ERROR:
    return (void *) FALSE;
}

~~~


#### 1.2 示例代码的编译和运行

1. 进入样例代码目录
	- ``cd oes_libs-xxx/include/oes_api/samples/c_sample``

2. 编译代码
	- ``make -f Makefile.sample``

3. 修改配置文件，确认服务地址、用户名等正确
	- ``vi oes_client_sample.conf``

4. 运行样例程序
	- ``./oes_client_sample``


---
### 版本升级指引及修改历史

- 版本升级指引参见 <@ref update_guide>
- 版本修改历史参见 <@ref changelog>


---
### 常见问题

- 价格和金额单位
  - OES中的所有价格均为`int32`类型的整型数值，单位精确到元后四位，即: 1元=10000
  - OES中的所有金额均为`int64`类型的整型数值，单位精确到元后四位，即: 1元=10000

- 份额单位
  - OES中的所有委托数量、成交数量等份额单位均为`int32`或`int64`类型的整型数值，不带小数位
  - OES中债券交易的份额单位是 <b>'张'</b>，股票交易份额单位是 <b>'股'</b>

- 报价单位不在合法区间？
	- OES中的所有价格均为`int32`类型的整型数值，单位精确到元后四位，即: 1元=10000

- 怎么分辨出查询返回的最后一条记录？
  <br>OesApi_QueryOrder是同步函数，它返回了代表查询到的所有委托信息回调完成，在Action_OnQryOrdItem
  回调函数中没有想过最后一条的标识，返回值>=0代表查询到的记录数量。

- 如何查看OrdRejectRsp的拒绝原因？
  <br>用OesApi_GetErrorMsg(rptHead.ordRejReason)去获取相关错误信息，消息头中的status、detailStatus
  主要返回通信层的错误。

- clEnvId 作用？
	- clEnvId 是客户端环境号，用于区分不同客户端实例上报的委托。即可以为每个客户端实例分配不同的 clEnvId，这样这些客户端实例就可以各自维护自己的 clSeqNo 而不会相互干扰
	- 不同客户端实例可以使用同一 clEnvId 登录服务端。此时这些使用了同一 clEnvId 的客户端实例共享同一个 clSeqNo 序列
	- clEnvId 客户端的取值范围是 __[0~99]__ ([100~127] 为保留区间，客户端应避免使用)
	- 可以通过 OesApi_GetClEnvId() 接口获得本客户端实例绑定的 clEnvId
	- 服务端维护的委托信息中，会记录发送此委托的源客户端实例所绑定的 clEnvId。委托回报消息(OesOrdCnfmT.clEnvId) 和 委托查询应答(OesOrdItemT.clEnvId) 会携带此信息
	- 配置文件相关设置请参考 oes_client_sample.conf 中 [oes_client].clEnvId 参数的设置


---
### OES错误码表

| 错误码 | 错误说明                            |
| :---- | :--------------------------------- |
| 1001  | 报文格式错误                         |
| 1002  | 当前主机不是主节点                    |
| 1003  | 主存库操作失败                       |
| 1004  | 因状态等基础数据不匹配，无法更新数据     |
| 1005  | 协议版本不兼容                       |
| 1006  | 数据不存在                           |
| 1007  | 非服务开放时间                       |
| 1008  | 非法的定位游标                       |
| 1009  | 非法的客户端登录用户名称               |
| 1010  | 非法的证券代码                       |
| 1011  | 非法的客户代码                       |
| 1012  | 非法的客户端类型                      |
| 1013  | 客户端已被禁用                       |
| 1014  | 客户端密码不正确                      |
| 1015  | 客户端重复登录                       |
| 1016  | 客户端连接数量过多                    |
| 1017  | 客户端未经授权操作他人账户             |
| 1018  | 数据超出修改范围                      |
| 1019  | 非法的应用系统名称                    |
| 1020  | 请求条件有冲突                       |
| 1021  | 非法的客户端IP/MAC地址格式            |
| 1022  | 尚不支持或尚未开通此业务               |
| 1023  | 非法的客户端环境号                    |
| 1024  | 交易所拒绝                           |
| 1025  | 主柜拒绝                            |
| 1026  | 流量超出限制范围                      |
| 1027  | 禁止使用API登录                      |
| 1028  | 非法的私募基金产品代码                 |
| 1029  | 密码未改变                           |
| 1030  | 非法的来源分类                       |
| 1031  | 非法的加密类型                       |
| 1032  | 非法的客户端设备序列号                 |
| 1033  | 无可用节点                           |
| 1034  | 密码强度不足                         |
| 1035  | 非法的产品类型                       |
| 1036  | 未通过黑白名单检查                     |
| 1037  | 集群编号不匹配                       |
| 1038  | 无此操作权限                        |
| 1101  | 登录柜台失败                         |
| 1102  | 上报至柜台失败                       |
| 1103  | 从柜台获取状态失败                    |
| 1201  | 非法的证券账户代码                    |
| 1202  | 非法的资金账户代码                    |
| 1203  | 非法的出入金方向                      |
| 1204  | 非法的市场代码                       |
| 1205  | 非法的证券类别                       |
| 1206  | 非法的买卖类型                       |
| 1207  | 非法的币种                           |
| 1208  | 非法的委托类型                       |
| 1209  | 无效的账户状态                       |
| 1210  | 未找到委托信息                       |
| 1211  | 未找到持仓信息                       |
| 1212  | 未找到出入金流水                      |
| 1213  | 流水号重复                           |
| 1214  | 当前时段不能报价                      |
| 1215  | 没有操作权限                         |
| 1216  | 可用/可取资金余额不足                 |
| 1217  | 可用持仓不足                         |
| 1218  | 委托数量不在合法区间内                 |
| 1219  | 非数量单位的整数倍                    |
| 1220  | 非法的PBU代码                        |
| 1221  | 价格不在合法区间内                    |
| 1222  | 非价格单位的整数倍                    |
| 1223  | 无涨停价市价委托失败                  |
| 1224  | 当前时段不支持市价委托                 |
| 1225  | 无效的订单状态                       |
| 1226  | 撤单信息与原始委托不符                 |
| 1227  | 重复撤单                            |
| 1228  | 未通过限仓检查                       |
| 1229  | 未通过限购检查                       |
| 1230  | 超过了ETF最大现金替代比例              |
| 1231  | 非行权日                            |
| 1232  | 证券停牌                            |
| 1233  | 合约限制开仓                         |
| 1234  | 当日累计申购或赎回数量超过限额          |
| 1235  | 当日累计净申购或净赎回数量超过限额       |
| 1236  | 找不到前收盘价                       |
| 1237  | 超过报撤比限制                       |
| 1238  | 委托请求过于频繁                      |
| 1239  | 非法的出入金转账金额                  |
| 1240  | 重复的认购委托                       |
| 1241  | 认购委托份数超过认购额度               |
| 1242  | 出入金笔数超过限制                    |
| 1243  | 禁止同时做多笔出入金                  |
| 1244  | 非法的新股配号、中签记录类型            |
| 1245  | 限制股东账户进行买交易                 |
| 1246  | 限制股东账户进行卖交易                 |
| 1247  | 限制股东账户进行逆回购交易             |
| 1248  | 限制股东账户进行新股认购交易            |
| 1249  | 股东账户没有市价委托交易的权限          |
| 1250  | 股东账户没有交易创业板证券的权限        |
| 1251  | 股东账户没有交易分级基金的权限          |
| 1252  | 股东账户没有债券合格投资者的权限        |
| 1253  | 客户风险评级低于交易证券需求的风险等级   |
| 1254  | 股东账户没有交易风险警示证券的权限       |
| 1255  | 股东账户没有交易退市整理证券的权限       |
| 1256  | 股东账户没有交易单市场ETF的权限         |
| 1257  | 股东账户没有交易跨市场ETF的权限         |
| 1258  | 股东账户没有交易货币基金ETF的权限       |
| 1259  | 股东账户没有交易跨境ETF的权限          |
| 1260  | 仅允许合格投资者投资该证券             |
| 1261  | 仅允许合格机构投资者投资该证券          |
| 1262  | 出入金执行异常，待人工干预             |
| 1263  | 交易日不在证券的发行期内               |
| 1264  | 该ETF禁止申购                        |
| 1265  | 该ETF禁止赎回                        |
| 1266  | 限制股东账户进行撤指定                 |
| 1267  | 限制股东账户进行转托管                 |
| 1268  | 机构客户/主柜业务不支持银行转帐         |
| 1269  | 禁止私募基金产品交易此证券             |
| 1270  | 禁止客户交易此证券                    |
| 1271  | 股东账户没有交易存托凭证的权限          |
| 1272  | 股东账户没有交易创新企业股票的权限       |
| 1273  | 非法的出入金转账类型                  |
| 1274  | 股东账户没有交易沪伦通存托凭证的权限     |
| 1275  | 股东账户没有交易科创板的权限            |
| 1276  | 个股持仓比例超过限制                 |
| 1277  | 营业部委托流水号超出有效范围          |
| 1278  | 结算单未确认                        |
| 1279  | 结算单重复确认                       |
| 1280  | 有未成交的卖出委托时禁止买入          |
| 1281  | 有未成交的买入委托时禁止卖出          |
| 1282  | 客户当日交易总量超出限制              |
| 1283  | 委托数量超出报备的单笔委托数量限制     |
| 1331  | 非法的持仓类型                       |
| 1332  | 合约限制开仓                        |
| 1333  | 客户权利仓持仓限额不足               |
| 1334  | 客户总持仓限额不足                 |
| 1335  | 客户单日买入开仓限额不足              |
| 1336  | 客户买入额度不足 (限购)              |
| 1337  | 券商总持仓限额不足                 |
| 1338  | 券商总保证金额度不足                 |
| 1339  | 非法的标的锁定指令类型                 |
| 1340  | 禁止买入开仓                        |
| 1341  | 禁止卖出平仓                        |
| 1342  | 禁止卖出开仓                        |
| 1343  | 禁止买入平仓                        |
| 1344  | 禁止备兑开仓                        |
| 1345  | 禁止备兑平仓                        |
| 1346  | 禁止标的锁定                        |
| 1347  | 禁止标的解锁                        |
| 1348  | 禁止期权行权                        |
| 1349  | 非行权日                           |
