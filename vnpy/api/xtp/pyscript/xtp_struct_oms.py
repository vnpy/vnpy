# encoding: UTF-8

structDict = {}








#新订单请求
XTPOrderInsertInfo = {}
# ///XTP系统订单ID，无需用户填写，在XTP系统中唯一
XTPOrderInsertInfo["order_xtp_id"] = "uint64_t"
# ///报单引用，由客户自定义
XTPOrderInsertInfo["order_client_id"] = "uint32_t"
# ///合约代码 客户端请求不带空格，以'\0'结尾
XTPOrderInsertInfo["ticker"] = "string"
# ///交易市场
XTPOrderInsertInfo["market"] = "enum"
# ///价格
XTPOrderInsertInfo["price"] = "float"
# ///止损价（保留字段）
XTPOrderInsertInfo["stop_price"] = "float"
# ///数量
XTPOrderInsertInfo["quantity"] = "int64_t"
# ///报单价格
XTPOrderInsertInfo["price_type"] = "enum"
# ///买卖方向
XTPOrderInsertInfo["side"] = "enum"
#业务类型
XTPOrderInsertInfo["business_type"] = "enum"



structDict['XTPOrderInsertInfo'] = XTPOrderInsertInfo

structDict['XTPOrderInsertInfo'] = XTPOrderInsertInfo



#撤单失败响应消息
XTPOrderCancelInfo = {}
# ///撤单XTPID
XTPOrderCancelInfo["order_cancel_xtp_id"] = "uint64_t"
# ///原始订单XTPID
XTPOrderCancelInfo["order_xtp_id"] = "uint64_t"
structDict['XTPOrderCancelInfo'] = XTPOrderCancelInfo



#报单响应结构体
XTPOrderInfo = {}
# ///XTP系统订单ID，在XTP系统中唯一
XTPOrderInfo["order_xtp_id"] = "uint64_t"
#报单引用，用户自定义
XTPOrderInfo["order_client_id"] = "uint32_t"
# ///报单操作引用，用户自定义（暂未使用）
XTPOrderInfo["order_cancel_client_id"] = "uint32_t"
# ///撤单在XTP系统中的id，在XTP系统中唯一
XTPOrderInfo["order_cancel_xtp_id"] = "uint64_t"
#合约代码
XTPOrderInfo["ticker"] = "string"
#交易市场
XTPOrderInfo["market"] = "enum"
#价格
XTPOrderInfo["price"] = "float"
#数量，此订单的报单数量
XTPOrderInfo["quantity"] = "int64_t"
#报单价格条件
XTPOrderInfo["price_type"] = "enum"
#买卖方向
XTPOrderInfo["side"] = "enum"
#业务类型
XTPOrderInfo["business_type"] = "enum"
#今成交数量，为此订单累计成交数量
XTPOrderInfo["qty_traded"] = "int64_t"
#剩余数量，当撤单成功时，表示撤单数量
XTPOrderInfo["qty_left"] = "int64_t"
#委托时间，格式为YYYYMMDDHHMMSSsss
XTPOrderInfo["insert_time"] = "int64_t"
#最后修改时间，格式为YYYYMMDDHHMMSSsss
XTPOrderInfo["update_time"] = "int64_t"
#撤销时间，格式为YYYYMMDDHHMMSSsss
XTPOrderInfo["cancel_time"] = "int64_t"
#成交金额，为此订单的成交总金额
XTPOrderInfo["trade_amount"] = "float"
#本地报单编号 OMS生成的单号，不等同于order_xtp_id，为服务器传到报盘的单号
XTPOrderInfo["order_local_id"] = "string"
#报单状态，订单响应中没有部分成交状态的推送，在查询订单结果中，会有部分成交状态
XTPOrderInfo["order_status"] = "enum"
#报单提交状态，OMS内部使用，用户无需关心
XTPOrderInfo["order_submit_status"] = "enum"
#报单类型
XTPOrderInfo["order_type"] = "char"



structDict['XTPOrderInfo'] = XTPOrderInfo

structDict['XTPOrderInfo'] = XTPOrderInfo




#报单成交结构体
XTPTradeReport = {}
# ///XTP系统订单ID，此成交回报相关的订单ID，在XTP系统中唯一
XTPTradeReport["order_xtp_id"] = "uint64_t"
# ///报单引用
XTPTradeReport["order_client_id"] = "uint32_t"
# ///合约代码
XTPTradeReport["ticker"] = "string"
# ///交易市场
XTPTradeReport["market"] = "enum"
# ///订单号，引入XTPID后，该字段实际和order_xtp_id重复。接口中暂时保留。
XTPTradeReport["local_order_id"] = "uint64_t"
# ///成交编号，深交所唯一，上交所每笔交易唯一，当发现2笔成交回报拥有相同的exec_id，则可以认为此笔交易自成交
XTPTradeReport["exec_id"] = "string"
# ///价格，此次成交的价格
XTPTradeReport["price"] = "float"
# ///数量，此次成交的数量，不是累计数量
XTPTradeReport["quantity"] = "int64_t"
# ///成交时间，格式为YYYYMMDDHHMMSSsss
XTPTradeReport["trade_time"] = "int64_t"
# ///成交金额，此次成交的总金额 = price*quantity
XTPTradeReport["trade_amount"] = "float"
# ///成交序号 --回报记录号，每个交易所唯一,report_index+market字段可以组成唯一标识表示成交回报
XTPTradeReport["report_index"] = "uint64_t"
# ///报单编号 --交易所单号，上交所为空，深交所有此字段
XTPTradeReport["order_exch_id"] = "string"
# ///成交类型  --成交回报中的执行类型
XTPTradeReport["trade_type"] = "char"
# ///买卖方向
XTPTradeReport["side"] = "enum"
#业务类型
XTPTradeReport["business_type"] = "enum"
# ///交易所交易员代码
XTPTradeReport["branch_pbu"] = "string"



structDict['XTPTradeReport'] = XTPTradeReport

structDict['XTPTradeReport'] = XTPTradeReport



#///////////////////////////////////////////////////////////////////////
#报单查询
#///////////////////////////////////////////////////////////////////////
#报单查询请求-条件查询
XTPQueryOrderReq = {}
# ///证券代码，可以为空，如果为空，则默认查询时间段内的所有成交回报
XTPQueryOrderReq["ticker"] = "string"
# ///格式为YYYYMMDDHHMMSSsss，为0则默认当前交易日0点
XTPQueryOrderReq["begin_time"] = "int64_t"
# ///格式为YYYYMMDDHHMMSSsss，为0则默认当前时间
XTPQueryOrderReq["end_time"] = "int64_t"
structDict['XTPQueryOrderReq'] = XTPQueryOrderReq


#报单查询响应结构体



#///////////////////////////////////////////////////////////////////////
#成交回报查询
#///////////////////////////////////////////////////////////////////////
#查询成交报告请求-根据执行编号查询（保留字段）
XTPQueryReportByExecIdReq = {}
# ///XTP订单系统ID
XTPQueryReportByExecIdReq["order_xtp_id"] = "uint64_t"
# ///成交执行编号
XTPQueryReportByExecIdReq["exec_id"] = "string"
structDict['XTPQueryReportByExecIdReq'] = XTPQueryReportByExecIdReq


#查询成交回报请求-查询条件
XTPQueryTraderReq = {}
# ///证券代码，可以为空，如果为空，则默认查询时间段内的所有成交回报
XTPQueryTraderReq["ticker"] = "string"
# ///开始时间，格式为YYYYMMDDHHMMSSsss，为0则默认当前交易日0点
XTPQueryTraderReq["begin_time"] = "int64_t"
# ///结束时间，格式为YYYYMMDDHHMMSSsss，为0则默认当前时间
XTPQueryTraderReq["end_time"] = "int64_t"
structDict['XTPQueryTraderReq'] = XTPQueryTraderReq


#成交回报查询响应结构体




#///////////////////////////////////////////////////////////////////////
#账户资金查询响应结构体
#///////////////////////////////////////////////////////////////////////
XTPQueryAssetRsp = {}
#总资产(=可用资金 + 证券资产（目前为0）+ 预扣的资金)
XTPQueryAssetRsp["total_asset"] = "float"
# ///可用资金
XTPQueryAssetRsp["buying_power"] = "float"
#证券资产（保留字段，目前为0）
XTPQueryAssetRsp["security_asset"] = "float"
# ///累计买入成交证券占用资金
XTPQueryAssetRsp["fund_buy_amount"] = "float"
# ///累计买入成交交易费用
XTPQueryAssetRsp["fund_buy_fee"] = "float"
# ///累计卖出成交证券所得资金
XTPQueryAssetRsp["fund_sell_amount"] = "float"
# ///累计卖出成交交易费用
XTPQueryAssetRsp["fund_sell_fee"] = "float"
#XTP系统预扣的资金（包括购买卖股票时预扣的交易资金+预扣手续费）
XTPQueryAssetRsp["withholding_amount"] = "float"
structDict['XTPQueryAssetRsp'] = XTPQueryAssetRsp




#///////////////////////////////////////////////////////////////////////
#查询股票持仓情况
#///////////////////////////////////////////////////////////////////////
XTPQueryStkPositionRsp = {}
# ///证券代码
XTPQueryStkPositionRsp["ticker"] = "string"
# ///证券名称
XTPQueryStkPositionRsp["ticker_name"] = "string"
# ///交易市场
XTPQueryStkPositionRsp["market"] = "enum"
# ///当前持仓
XTPQueryStkPositionRsp["total_qty"] = "int64_t"
# ///可用股份数
XTPQueryStkPositionRsp["sellable_qty"] = "int64_t"
# ///买入成本价
XTPQueryStkPositionRsp["avg_price"] = "float"
# ///浮动盈亏（保留字段）
XTPQueryStkPositionRsp["unrealized_pnl"] = "float"
structDict['XTPQueryStkPositionRsp'] = XTPQueryStkPositionRsp




#//////////////////////////////////////////////////////////////////////
#资金内转流水通知
#//////////////////////////////////////////////////////////////////////
XTPFundTransferNotice = {}
# ///资金内转编号
XTPFundTransferNotice["serial_id"] = "uint64_t"
# ///内转类型
XTPFundTransferNotice["transfer_type"] = "enum"
# ///金额
XTPFundTransferNotice["amount"] = "float"
# ///操作结果 
XTPFundTransferNotice["oper_status"] = "enum"
# ///操作时间
XTPFundTransferNotice["transfer_time"] = "uint64_t"
structDict['XTPFundTransferNotice'] = XTPFundTransferNotice






#//////////////////////////////////////////////////////////////////////
#资金内转流水查询请求与响应
#//////////////////////////////////////////////////////////////////////
XTPQueryFundTransferLogReq = {}
# ///资金内转编号
XTPQueryFundTransferLogReq["serial_id"] = "uint64_t"

structDict['XTPQueryFundTransferLogReq'] = XTPQueryFundTransferLogReq


#//////////////////////////////////////////////////////////////////////
#资金内转流水记录结构体
#//////////////////////////////////////////////////////////////////////










structDict['XTPQueryOrderRsp'] = XTPOrderInfo

structDict['XTPQueryTradeRsp'] = XTPTradeReport

