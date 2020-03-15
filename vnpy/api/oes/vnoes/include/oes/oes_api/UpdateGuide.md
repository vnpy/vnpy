# OES-API Update Guide    {#update_guide}

OES_0.15.9 / 2019-05-31
-----------------------------------

### 1. API更新概要

  1.  服务端兼容 v0.15.5.1 版本API, 客户可以选择不升级 (建议升级, 以支持科创版业务)
  2.  fix: 修复API无法支持取值大于1024的文件描述符的问题
  3.  新增证券子类型
      - 科创板股票 (OES_SUB_SECURITY_TYPE_STOCK_KSH)
      - 科创板存托凭证 (OES_SUB_SECURITY_TYPE_STOCK_KCDR)
      - 沪伦通CDR (OES_SUB_SECURITY_TYPE_STOCK_HLTCDR)
  4.  新增配股认购对应的买卖类型 OES_BS_TYPE_ALLOTMENT, 以支持配股业务
  5.  新增产品类型属性的定义, 并在如下结构中体现:
      - 证券信息 (OesStockBaseInfoT/OesStockItemT)
      - 证券发行信息 (OesIssueBaseInfoT/OesIssueItemT)
      - 股票持仓信息 (OesStkHoldingBaseInfoT/OesStkHoldingItemT)
      - 委托回报 (OesOrdCnfmT/OesOrdItemT)
      - 成交回报 (OesTrdCnfmT/OesTrdItemT)
      - 证券发行信息查询接口(OesApi_QueryIssue)的过滤条件
      - 股票持仓信息查询接口(OesApi_QueryStkHolding)的过滤条件
  6.  为了支持科创板, 扩展以下数据结构以及相应的查询结果 (兼容之前版本的API)
      - 证券账户基础信息 (OesInvAcctBaseInfoT, OesInvAcctItemT) 中增加如下字段:
          - 科创板权益 (kcSubscriptionQuota)
      - 现货产品基础信息 (OesStockBaseInfoT, OesStockItemT) 中增加如下字段:
          - 限价买数量上限 (lmtBuyMaxQty)
          - 限价买数量下限 (lmtBuyMinQty)
          - 限价卖数量上限 (lmtSellMaxQty)
          - 限价卖数量下限 (lmtSellMinQty)
          - 市价买数量上限 (mktBuyMaxQty)
          - 市价买数量下限 (mktBuyMinQty)
          - 市价卖数量上限 (mktSellMaxQty)
          - 市价卖数量下限 (mktSellMinQty)
      - 客户端总览信息中的股东账户总览 (OesInvAcctOverviewT) 中增加如下字段:
          - 科创板权益 (kcSubscriptionQuota)
  7.  重构涨跌停价格、价格档位字段命名, 为这些字段增加新的别名 (兼容之前版本的API)
      - ceilPrice => upperLimitPrice
      - floorPrice => lowerLimitPrice
      - priceUnit => priceTick
  8.  调整上证委托类型 (eOesOrdTypeShT)
      - 增加 '对手方最优价格申报 (OES_ORD_TYPE_SH_MTL_BEST)' 类型 (仅适用于科创板)
      - 增加 '本方最优价格申报 (OES_ORD_TYPE_SH_MTL_SAMEPATY_BEST)' 类型 (仅适用于科创板)
  9.  股东账户交易权限枚举(eOesTradingPermissionT)中新增
      - 科创板交易权限 (OES_PERMIS_KSH)
  10. 新增错误码1035、1036、1274、1275, 调整错误码1007、1022的描述信息
      | 错误码 | 描述
      | ---- | ---------------
      | 1007 | 非服务开放时间
      | 1022 | 尚不支持或尚未开通此业务
      | 1035 | 非法的产品类型
      | 1036 | 未通过黑白名单检查
      | 1274 | 股东账户没有交易沪伦通存托凭证的权限
      | 1275 | 股东账户没有交易科创板的权限

### 2. 服务端更新概要

  1. 支持配股申购业务
  2. 支持对客户设置禁止买入和限制卖出某支证券
  3. 支持逆回购闭市时间延后到15:30
  4. 支持科创板业务
  5. 修复其他系统缺陷, 完善安全机制

### 3. 科创板市价委托保护限价说明

  1. 在进行科创板市价委托交易时, 保护限价填在委托请求中的ordPrice字段内 (对于主板的市价委托, 委托请求中的ordPrice字段无意义)
  2. 对于上市前五日、无涨跌幅限制的科创板证券, 市价委托的保护限价必填, 且保护限价需符合价格变动单位
  3. 对于上市五日后、有涨跌幅限制的科创板证券, 市价委托的保护限价可填写有效值或者0
     - 对于市价买委托, 委托请求中ordPrice填0将使用涨停价作为其保护限价
     - 对于市价卖委托, 委托请求中ordPrice填0将使用跌停价作为其保护限价
  4. 对于有涨跌幅限制的科创板证券:
     - 当市价买委托的保护限价高于涨停价时, 将使用涨停价冻结交易资金, 委托正常处理
     - 当市价买委托的保护限价低于涨停价时, 将使用保护限价冻结交易资金
     - 当市价买委托的保护限价低于跌停价时, 委托将被拒绝
     - 当市价卖委托的保护限价低于跌停价时, 委托正常处理
     - 当市价卖委托的保护限价高于涨停价时, 委托将被拒绝


---

OES_0.15.7.4 / 2018-09-28
-----------------------------------

### 1. API更新概要

  1. 服务端兼容 v0.15.5.1 版本API，客户可以选择不升级 (建议升级)
  2. fix: 修复当多个线程同时初始化API日志时, 会导致日志信息重复输出的问题
  3. API新增如下接口
    | API                          | 描述
    | ---------------------------- | ---------------
    | OesApi_SendBatchOrdersReq    | 批量委托
    | OesApi_SendBatchOrdersReq2   | 批量委托
    | OesApi_SendChangePasswordReq | 修改客户端登录密码，仅支持15:00之后修改
    | OesApi_SetLastError          | 设置当前线程的API错误号
    | OesApi_GetLastError          | 获取当前线程最近一次API调用失败的错误号
    | OesApi_SetCustomizedDriverId | 获取已设置的设备序列号
    | OesApi_GetCustomizedDriverId | 设置设备序列号
    | OesApi_GetClientOverview     | 获取客户端总览信息
    | OesApi_QueryCounterCash      | 查询主柜资金信息(仅支持部分主柜台)
    | OesApi_QueryMarketState      | 查询市场状态(目前仅能获取到深圳市场状态)
    | OesApi_HasMoreCachedData     | 获取回报通道中尚未被回调函数处理的缓存数据长度
    | OesApi_SetThreadUsername     | 设置当前线程的登录用户名
    | OesApi_SetThreadPassword     | 设置当前线程的登录密码
    | OesApi_SetThreadEnvId        | 设置当前线程的客户端环境号
  4. 回报通道新增一类推送消息: 市场状态推送(目前仅推送深圳市场的状态)，默认订阅条件不会订阅此消息
  5. 新增存托凭证对应的证券子类别 OES_SUB_SECURITY_TYPE_STOCK_CDR
  6. 回报的消息头结构(OesRptMsgHeadT)中增加 execType 字段，用于表明回报执行类型(参考eOesExecTypeT定义)。
  7. 查询证券信息接口(OesApi_QueryStock)中新增过滤条件“证券类别”、“证券子类别”
  8. 查询委托接口(OesApi_QueryOrder)中新增过滤条件“证券类别”、“买卖类型”
  9. 查询成交接口(OesApi_QueryTrade)中新增过滤条件“证券类别”、“买卖类型”
  10. 查询股票持仓接口(OesApi_QueryStkHolding)中新增过滤条件“证券类别”
  11. 调整出入金委托请求接口, 支持银行和主柜之间的银证转账
  12. 客户资金信息中增加是否禁止出入金的标识
  13. 客户股东信息中增加是否禁止交易的标识
  14. 成交信息中增加证券子类型、原始委托数量、原始委托价格
  15. 新增部分错误码
    | 错误码 | 描述
    | ---- | ---------------
    | 1029 | 密码未改变
    | 1030 | 非法的来源分类
    | 1031 | 非法的加密类型
    | 1032 | 非法的客户端设备序列号
    | 1033 | 无可用节点
    | 1271 | 股东账户没有交易存托凭证的权限
    | 1272 | 股东账户没有交易创新企业股票的权限
    | 1273 | 非法的出入金转账类型

### 2. 服务端更新概要

  1. 支持修改密码
  2. 支持批量委托
  3. 支持CDR交易、创新企业股票交易
  4. 在监控管理端新增应急撤单功能
  5. 系统增加盘前开工和盘后收工操作。开工前（9:00）可以查询数据，但不受理交易和出入金。收工后（15:10）不受理交易，但可以执行出入金、修改密码和查询数据。
  6. 修复系统缺陷，完善管理功能和故障恢复处理


---

OES_0.15.5.16 / 2018-09-28
-----------------------------------

### 1. API更新概要

  1. 服务端兼容 v0.15.5.1 版本API, 客户可以选择不升级 (建议升级)
  2. fix: 修复当多个线程同时初始化API日志时, 会导致日志信息重复输出的问题
  3. 增加 OesApi_HasMoreCachedData 接口, 用于返回已经接收到但尚未被回调函数处理的缓存数据长度
  4. 增加 OesApi_GetLastError 接口, 用于返回最近一次API调用失败的错误号
  5. 增加 OesApi_QueryCounterCash 接口, 用于查询主柜的资金信息 (仅支持部分主柜)
  6. 增加 OesApi_GetClientOverview 接口, 用于查询客户端总览信息
  7. 增加设置当前线程登录用户名/登录密码/客户端环境号的接口
  8. 查询现货产品信息接口的过滤条件中新增证券类型、证券子类型的过滤条件
  9. 调整出入金委托请求接口, 支持银行和主柜之间的银证转账
  10. 客户资金信息中增加是否禁止出入金的标识
  11. 客户股东信息中增加是否禁止交易的标识
  12. 成交信息中增加证券子类型、原始委托数量、原始委托价格

### 2. 服务端更新概要

  1. 支持CDR交易、创新企业股票交易
  2. 新增监控管理端的应急撤单功能
  3. 修复系统缺陷, 完善管理功能和故障恢复处理


---

OES_0.15.5.11 / 2018-06-20
-----------------------------------

### 1. API更新概要

  1. API没有变化
  2. 服务端兼容 v0.15.5.1 版本API, 客户可以选择不升级 (建议升级)

### 2. 服务端更新概要

  1. 修复系统缺陷
  2. 完善容错处理
  3. 其它功能性更新


---

OES_0.15.5.4 / 2018-02-22
-----------------------------------

### 1. API更新概要

  1. 服务端兼容 v0.15.5.1 版本API, 客户可以选择不升级
  2. fix: 解决在Windows下的兼容性问题
  3. fix: 修正注释信息中的错误 ('佣金查询结果 (OesCommissionRateItemT)' 中 feeRate 字段精度描述不正确)
  4. API将优先使用自动获取到的ip/mac信息，只有自动获取到的ip/mac信息非法时，才会使用客户自设的ip/mac
  5. 修正ETF产品信息中的字段拼写错误 (preTrdaingDay => preTradingDay)
  6. 增加 OesApi_GetLastRecvTime、OesApi_GetLastSendTime 接口, 用于获取通道最新发送/接受消息的时间
  7. 登录失败时, 可以通过 errno/SPK_GET_ERRNO() 获取到具体失败原因

### 2. 服务端更新概要

  1. fix: 优化回报推送，改善推送服务的公平性
  2. fix: 修复在委托确认时没有回填 exchOrdId 的问题
  3. 服务端将拒绝来自本地回环地址以及非法IP/MAC地址的登录


---

OES_0.15.5 / 2017-11-12
-----------------------------------

### 1. 更新概要

  1. API中增加客户端环境号(clEnvId)，不同客户端环境号(clEnvId)下的委托顺序号(clSeqNo)序列互不影响
  2. 增加独立的撤单接口，支持通过 clEnvId+clSeqNo 进行撤单
  3. 回报通道支持消息订阅功能，默认情况下订阅所有类型的回报消息
  4. 回报消息新增两类：资金变动通知、持仓变动通知
  5. 撤单委托执行成功后，补充被撤委托的状态推送
  6. 查询接口回调方法类型定义调整，查询回调接口中增加 isEnd 标志
  7. 持仓信息中增加持仓成本相关字段，将影响持仓查询返回结构和持仓变动通知结构
  8. API退出时在日志中输出延迟统计信息

### 2. 详细更新内容

#### 2.1 API中增加客户端环境号(clEnvId)

  - clEnvId 是客户端环境号，用于区分不同客户端实例上报的委托。即可以为每个客户端实例分配不同的 clEnvId，这样这些客户端实例就可以各自维护自己的 clSeqNo 而不会相互干扰
  - 不同客户端实例可以使用同一 clEnvId 登录服务端。此时这些使用了同一 clEnvId 的客户端实例共享同一个 clSeqNo 序列
  - clEnvId 客户端的取值范围是 __[0~99]__ ([100~127] 为保留区间，客户端应避免使用)
  - 可以通过 OesApi_GetClEnvId() 接口获得本客户端实例绑定的 clEnvId
  - 服务端维护的委托信息中，会记录发送此委托的源客户端实例所绑定的 clEnvId。委托回报消息(OesOrdCnfmT.clEnvId) 和 委托查询应答(OesOrdItemT.clEnvId) 会携带此信息
  - 配置文件相关设置请参考 oes_client_sample.conf 中 [oes_client].clEnvId 参数的设置

#### 2.2 增加独立的撤单接口

  - 增加独立的撤单接口 OesApi_SendOrderCancelReq()
  - 接口中 pCancelReq 参数的 pCancelReq->mktId 必填
  - 接口中 pCancelReq 参数的 pCancelReq->invAcctId、pCancelReq->securityId 选填。如果填写则会与被撤委托作匹配
  - 仍保留通过被撤委托 clOrdId 的方式进行撤单。倘若接口中 pCancelReq->origClOrdId > 0，则优先通过pCancelReq->origClOrdId 来匹配被撤委托进行撤单
  - 在通过被撤委托 clEnvId+clSeqNo 进行撤单的场景，倘若接口中 pCancelReq->origClEnvId = 0，则默认使用当前客户端实例绑定的 clEnvId 作为被撤委托的 clEnvId 进行撤单。也就是说，对于本客户端实例发出的委托进行撤单，撤单时 pCancelReq->origClEnvId 可以写0； __如果要对其他客户端实例发出的委托进行撤单，需要准确写撤单接口中的 pCancelReq->origClEnvId 字段__

#### 2.3 回报通道支持消息订阅功能

  - 默认情况下，订阅所有类型的回报消息
  - 配置文件相关设置请参考oes_client_sample.conf 中 [oes_client].rpt.subcribeRptTypes  参数的设置

#### 2.4 新增资金变动、持仓变动通知

  - 回报新增两个推送消息：OESMSG_RPT_CASH_ASSET_VARIATION (资金变动通知)、OESMSG_RPT_STOCK_HOLDING_VARIATION (持仓变动通知)
  - 当因委托请求、委托成交、委托撤单而引起可用资金、可用持仓变动时，会触发回报通道的资金变动/持仓变动通知
  - 以一笔买委托为例，OES服务端将会依次推送如下消息：
    1. OESMSG_RPT_ORDER_INSERT 消息 (新委托触发)
    2. OESMSG_RPT_CASH_ASSET_VARIATION 消息（因资金冻结触发）
    3. OESMSG_RPT_ORDER_REPORT 消息（因交易所委托回报触发）
    4. OESMSG_RPT_TRADE_REPORT 消息（因交易所成交回报触发）
    5. OESMSG_RPT_CASH_ASSET_VARIATION 消息（因成交引起资金扣减触发）
    6. OESMSG_RPT_STOCK_HOLDING_VARIATION 消息（因成交引起持仓增加触发）

#### 2.5 补充被撤委托的状态推送

  - 以一笔买委托被成功撤单为例，回报通道会依次推送如下回报消息：
    1. 撤单委托的 OESMSG_RPT_ORDER_INSERT 消息
    2. 撤单委托的 OESMSG_RPT_ORDER_REPORT 消息
    3. __被撤__ 委托的 OESMSG_RPT_ORDER_REPORT 消息
    5. OESMSG_RPT_CASH_ASSET_VARIATION 消息（因释放冻结资金触发）

#### 2.6 查询接口回调方法类型定义调整

  - 调整查询接口回调方法类型定义 F_OESAPI_ONMSG_T => F_OESAPI_ON_QRY_MSG_T
  - 查询接口回调方法中增加参数 OesQryCursorT *pQryCursor，使用 pQryCursor->isEnd 判断是否是查询的最后一条

#### 2.7 持仓信息中增加持仓成本相关字段

  - '股票持仓信息 (OesStkHoldingItemT)' 结构体中增加字段:
    1. 日初总持仓成本 (originalCostAmt)
    2. 日中累计买入金额 (totalBuyAmt)
    3. 日中累计卖出金额 (totalSellAmt)
    4. 日中累计买入费用 (totalBuyFee)
    5. 日中累计卖出费用 (totalSellFee)
    6. 持仓成本价 (costPrice)

#### 2.8 回报接口回调方法类型定义调整

  - 回报接口回调方法类型定义调整 F_OESAPI_ONMSG_T => F_OESAPI_ON_RPT_MSG_T
  - 回报接口回调方法实际参数列表没有变化

#### 2.9 其他调整

  - 委托回报信息中增加独立的交易所错误码字段
    1. 原错误码字段 OesOrdCnfmT.ordRejReason 保持不变
    2. 当委托被交易所打回废单后，OesOrdCnfmT.ordRejReason 释义为 “交易所拒绝”，此时具体错误原因需要参考 OesOrdCnfmT.exchErrCode，此字段携带交易所定义的错误码
  - 委托状态定义调整
    1. 删除 'OES_ORD_STATUS_DECLARING (正报)' 状态
    2. 重命名 OES_ORD_STATUS_NORMAL => OES_ORD_STATUS_NEW (新订单)
    3. 保留 OES_ORD_STATUS_NORMAL 定义作为版本切换间的兼容
  - 回报消息类型定义调整
    1. 重命名回报消息类型 OESMSG_RPT_ORDER_REJECT => OESMSG_RPT_BUSINESS_REJECT (OES业务拒绝, 委托/撤单未通过风控检查等)
    2. 保留 OESMSG_RPT_ORDER_REJECT 定义作为版本切换间的兼容
  - 调整 '资金信息(OesCashAssetItemT)' 中部分字段:
    3. '当前余额'字段重命名 currentBal => currentTotalBal
  - 新增API接口 '获取API的发行版本号 (OesApi_GetApiVersion)'
  - 新增API接口 '获取当前交易日 (OesApi_GetTradingDay)'
  - 调整佣金查询结果中feeRate字段的精度，当佣金计算模式为 ‘按金额’ 时，feeRate 字段所代表的比率精度由 '百万分之一' => '千万分之一'


---

OES_0.15.3 / 2017-08-14
-----------------------------------

### 更新内容

  1. 现货产品基础信息(OesStockBaseInfoT) 中
    - 调整字段 isQualificationRequired => qualificationClass,
        取值请参考 eOesQualificationClassT
    - 新增字段 产品风险等级(securityRiskLevel)，取值请参考 eOesSecurityRiskLevelT
    - 新增字段 逆回购期限(repoExpirationDays)
    - 新增字段 占款天数(cashHoldDays) 字段
  2. 客户资金基础信息(OesCashAssetBaseInfoT) 中
    - 字段重命名 期初余额(originalBal => beginningBal)
    - 新增字段 期初可用余额(beginningAvailableBal)
    - 新增字段 期初可取余额(beginningDrawableBal)
    - 新增字段 当前冲正金额(红冲蓝补的资金净额, reversalAmt)
    - 新增字段 当前余额(currentBal)
    - 字段重命名 当前可用余额(tradeAvlAmt => currentAvailableBal)
    - 字段重命名 当前可取余额(withdrawAvlAmt => currentDrawableBal)
  3. 客户基础信息(OesCustBaseInfoT) 中
    - 新增 机构标志(institutionFlag) 字段
    - 新增 投资者分类(investorClass) 字段
  4. 证券账户基础信息(OesInvAcctBaseInfoT) 中
    - 调整字段 '(股东账户权限限制, acctLimit)'
        - 类型 uint32 => uint64
        - 重命名 acctLimit => Limits
    - 调整字段 '(股东权限/客户权限, acctRight)'
        - 类型 uint32 => uint64
        - 重命名 acctRight => permissions
  5. API接口中新增 发送出入金委托请求(OesApi_SendFundTrsfReq) 接口
  6. API接口中新增 查询新股配号、中签信息(OesApi_QueryLotWinning) 接口
  7. 新增 ‘新股认购、中签信息查询’ 相关报文定义
    - 新增字段 查询新股认购、中签信息过滤条件(OesQryLotWinningFilterT)
    - 新增字段 新股认购、中签信息内容(OesLotWinningItemT)
    - 新增字段 查询新股认购、中签信息请求(OesQryLotWinningReqT)
    - 新增字段 查询新股认购、中签信息应答(OesQryLotWinningRspT)
  8. 出入金业务拒绝消息类型变更 OesFundTrsfReqT => OesFundTrsfRejectT
  9. 出入金委托回报的结构体(OesFundTrsfReportT) 中新增字段 错误码信息(errorInfo)
  10. 出入金委托状态(eOesFundTrsfStatusT) 中
    - 调整宏定义 OES_FUND_TRSF_STS_RECV => OES_FUND_TRSF_STS_UNDECLARED
    - 调整宏定义 OES_FUND_TRSF_STS_DCLR => OES_FUND_TRSF_STS_DECLARED
    - 新增状态 指令已报到主柜前待回滚(OES_FUND_TRSF_STS_UNDECLARED_ROLLBACK)
    - 新增状态 指令已报到主柜后待回滚(OES_FUND_TRSF_STS_DECLARED_ROLLBACK)
    - 新增状态 出入金指令完成，等待事务结束(OES_FUND_TRSF_STS_WAIT_DONE)
    - 新增状态 出入金执行的挂起状态(OES_FUND_TRSF_STS_SUSPENDED)
  11. 权限不足交易失败时的错误码细分(详情请见 README 错误码表部分)


---

OES_0.12.9 / 2017-06-06
-----------------------------------

### 更新内容

  1. 使用API发起新股认购时，认购委托的bsType需要填成 ‘OES_BS_TYPE_SUBSCRIPTION’
  2. 可以使用API的查询股东账户接口(OesApi_QueryInvAcct)获取该股东账户的新股认购额度(OesInvAcctItemT.subscriptionQuota)
  3. 可以使用API的查询证券发行产品信息接口(OesApi_QueryIssue)获取当日可认购的新股信息(OesIssueItemT)
  4. 可以使用API的查询现货产品信息接口(OesApi_QueryStock)获取债券的每百元应计利息额(OesStockItemT.bondInterest)，
    此字段精确到元后八位，即123400000相当于一元二角三分四厘
  5. 买卖国债委托涉及的利息，可以参考‘委托确认信息(OesOrdCnfmT)’中的‘冻结利息(frzInterest)’、‘已发生利息(cumInterest)’字段
  6. 买卖国债成交涉及的利息，可以参考‘成交确认信息(OesTrdCnfmT)’中的‘已发生利息(cumInterest)’字段
  7. ‘买卖类型’的宏定义重命名，具体请参考OES_0.12.8.2版本修改历史。原始宏定义将在下一个版本之后被废弃


---

OES_0.12.7 / 2017-04-13
-----------------------------------

### 1. 主要更新内容
  1. 使用API发逆回购委托时，逆回购委托的bsType需要赋值成 ‘OES_BS_TYPE_CS’，而不是普通的‘卖出’。
  2. 使用API发逆回购委托时，ordQty 字段代表的单位是‘张’而不是‘手’。
  3. 回报通道增加两类消息：‘出入金委托响应-业务拒绝（OESMSG_RPT_FUND_TRSF_REJECT）’
    和‘出入金委托执行报告(OESMSG_RPT_FUND_TRSF_REPORT)’ 。
    - 出入金委托业务拒绝回报消息的回报消息体结构为 OesFundTrsfReqT，
    - 出入金委托执行报告回报消息的回报消息体结构为 OesFundTrsfReportT，
    - 如果不在oes系统内做出入金可以忽略这两类回报消息
  4. 在mds_api.h、oes_api.h中增加sutil库头文件的引用，API使用者只需引用mds_api.h、oes_api.h，
    不再需要显式引用sutil库的头文件

### 2. 其他调整：
  1. 不再有独立的出入金通道，client的配置中可以去掉62**端口的配置了
  2. 调整佣金查询结果中feeRate字段的精度，当佣金计算模式为 ‘按金额’ 时，
     feeRate 字段所代表的比率精度由 '十万分之一' => '百万分之一'
  3. ‘费用计算模式’ 的宏定义名称的调整 eOesCalFeeModeT => eOesCalcFeeModeT
  4. 新增债券、基金的证券类别，调整ETF证券类别宏定义的取值
  5. 新增证券子类别定义
  6. 现货产品基础信息中增加“证券子类别”字段，并且重命名“买入单位”、“卖出单位”字段
  7. ETF产品基础信息中增加“证券类别”、“证券子类别”字段
  8. ETF成分股基础信息中增加“证券子类别”字段
