# encoding: UTF-8

structDict = {}






























#新订单请求
XTPOrderInsertInfo = {}
# ///XTP系统订单ID
XTPOrderInsertInfo["order_xtp_id"] = "int"
# ///报单引用,由客户自定义
XTPOrderInsertInfo["order_client_id"] = "int"
# ///合约代码 客户端请求不带空格
XTPOrderInsertInfo["ticker"] = "string"
# ///交易市场
XTPOrderInsertInfo["market"] = "int"
# ///价格
XTPOrderInsertInfo["price"] = "float"
# ///止损价（保留字段）
XTPOrderInsertInfo["stop_price"] = "float"
# ///数量
XTPOrderInsertInfo["quantity"] = "int"
# ///报单价格
XTPOrderInsertInfo["price_type"] = "int"
# ///买卖方向
XTPOrderInsertInfo["side"] = "int"
structDict['XTPOrderInsertInfo'] = XTPOrderInsertInfo


#撤单
XTPOrderCancel = {}
# ///XTP系统订单ID
XTPOrderCancel["order_cancel_xtp_id"] = "int"
# ///报单操作引用
XTPOrderCancel["order_cancel_client_id"] = "int"
# ///合约代码
XTPOrderCancel["ticker"] = "string"
# ///交易市场
XTPOrderCancel["market"] = "int"
# ///操作时间
XTPOrderCancel["action_time"] = "int"
# ///报单引用
XTPOrderCancel["order_client_id"] = "int"
# ///操作对象订单的序号
XTPOrderCancel["order_xtp_id"] = "int"
structDict['XTPOrderCancel'] = XTPOrderCancel



#撤单失败响应消息
XTPOrderCancelInfo = {}
# ///撤单XTPID
XTPOrderCancelInfo["order_cancel_xtp_id"] = "int"
# ///原始订单XTPID
XTPOrderCancelInfo["order_xtp_id"] = "int"
structDict['XTPOrderCancelInfo'] = XTPOrderCancelInfo



#报单响应结构体
XTPOrderInfo = {}
# ///XTP系统订单ID
XTPOrderInfo["order_xtp_id"] = "int"
#报单引用，用户自定义
XTPOrderInfo["order_client_id"] = "int"
# ///报单操作引用，用户自定义
XTPOrderInfo["order_cancel_client_id"] = "int"
# ///撤单在XTP系统中的id
XTPOrderInfo["order_cancel_xtp_id"] = "int"
#合约代码
XTPOrderInfo["ticker"] = "string"
#交易市场
XTPOrderInfo["market"] = "int"
#价格
XTPOrderInfo["price"] = "float"
#数量
XTPOrderInfo["quantity"] = "int"
#报单价格条件
XTPOrderInfo["price_type"] = "int"
#买卖方向
XTPOrderInfo["side"] = "int"
#今成交数量
XTPOrderInfo["qty_traded"] = "int"
#剩余数量
XTPOrderInfo["qty_left"] = "int"
#委托时间
XTPOrderInfo["insert_time"] = "int"
#最后修改时间
XTPOrderInfo["update_time"] = "int"
#撤销时间
XTPOrderInfo["cancel_time"] = "int"
#成交金额
XTPOrderInfo["trade_amount"] = "float"
#本地报单编号 OMS生成的单号
XTPOrderInfo["order_local_id"] = "string"
#报单状态
XTPOrderInfo["order_status"] = "int"
#报单提交状态
XTPOrderInfo["order_submit_status"] = "int"
#报单类型
XTPOrderInfo["order_type"] = "char"
structDict['XTPOrderInfo'] = XTPOrderInfo




#报单成交结构体
XTPTradeReport = {}
# ///XTP系统订单ID
XTPTradeReport["order_xtp_id"] = "int"
# ///报单引用
XTPTradeReport["order_client_id"] = "int"
# ///合约代码
XTPTradeReport["ticker"] = "string"
# ///交易市场
XTPTradeReport["market"] = "int"
# ///订单号
XTPTradeReport["local_order_id"] = "int"
# ///成交编号
XTPTradeReport["exec_id"] = "int"
# ///价格
XTPTradeReport["price"] = "float"
# ///数量
XTPTradeReport["quantity"] = "int"
# ///成交时间
XTPTradeReport["trade_time"] = "int"
# ///成交金额
XTPTradeReport["trade_amount"] = "float"
# ///成交序号 --回报记录号
XTPTradeReport["report_index"] = "int"
# ///报单编号 --交易所单号
XTPTradeReport["order_exch_id"] = "string"
# ///成交类型  --成交回报中的执行类型
XTPTradeReport["trade_type"] = "char"
# ///买卖方向
XTPTradeReport["side"] = "int"
# ///交易所交易员代码 
XTPTradeReport["branch_pbu"] = "string"
structDict['XTPTradeReport'] = XTPTradeReport



#///////////////////////////////////////////////////////////////////////
#报单查询
#///////////////////////////////////////////////////////////////////////
#报单查询请求-条件查询
XTPQueryOrderReq = {}
# ///证券代码，可以为空，如果为空，则默认查询时间段内的所有成交回报
XTPQueryOrderReq["ticker"] = "string"
# ///格式为YYYYMMDDHHMMSSsss，为0则默认当前交易日0点
XTPQueryOrderReq["begin_time"] = "int"
# ///格式为YYYYMMDDHHMMSSsss，为0则默认当前时间
XTPQueryOrderReq["end_time"] = "int"
structDict['XTPQueryOrderReq'] = XTPQueryOrderReq


#报单查询响应结构体



#///////////////////////////////////////////////////////////////////////
#成交回报查询
#///////////////////////////////////////////////////////////////////////
#查询成交报告请求-根据执行编号查询（保留字段）
XTPQueryReportByExecIdReq = {}
# ///XTP订单系统ID
XTPQueryReportByExecIdReq["order_xtp_id"] = "int"
# ///成交执行编号
XTPQueryReportByExecIdReq["exec_id"] = "int"
structDict['XTPQueryReportByExecIdReq'] = XTPQueryReportByExecIdReq


#查询成交回报请求-查询条件
XTPQueryTraderReq = {}
# ///证券代码，可以为空，如果为空，则默认查询时间段内的所有成交回报
XTPQueryTraderReq["ticker"] = "string"
# ///开始时间，格式为YYYYMMDDHHMMSSsss，为0则默认当前交易日0点
XTPQueryTraderReq["begin_time"] = "int"
# ///结束时间，格式为YYYYMMDDHHMMSSsss，为0则默认当前时间
XTPQueryTraderReq["end_time"] = "int"
structDict['XTPQueryTraderReq'] = XTPQueryTraderReq


#成交回报查询响应结构体




#///////////////////////////////////////////////////////////////////////
#账户资金查询响应结构体
#///////////////////////////////////////////////////////////////////////
XTPQueryAssetRsp = {}
#总资产
XTPQueryAssetRsp["total_asset"] = "float"
# ///可用资金
XTPQueryAssetRsp["buying_power"] = "float"
#证券资产
XTPQueryAssetRsp["security_asset"] = "float"
# ///累计买入成交证券占用资金（保留字段）
XTPQueryAssetRsp["fund_buy_amount"] = "float"
# ///累计买入成交交易费用（保留字段）
XTPQueryAssetRsp["fund_buy_fee"] = "float"
# ///累计卖出成交证券所得资金（保留字段）
XTPQueryAssetRsp["fund_sell_amount"] = "float"
# ///累计卖出成交交易费用（保留字段）
XTPQueryAssetRsp["fund_sell_fee"] = "float"
structDict['XTPQueryAssetRsp'] = XTPQueryAssetRsp




#///////////////////////////////////////////////////////////////////////
#查询股票持仓情况
#///////////////////////////////////////////////////////////////////////
XTPQueryStkPositionRsp = {}
# ///证券代码
XTPQueryStkPositionRsp["ticker"] = "string"
# ///证券名称
XTPQueryStkPositionRsp["ticker_name"] = "string"
# ///当前持仓
XTPQueryStkPositionRsp["total_qty"] = "int"
# ///可用股份数
XTPQueryStkPositionRsp["sellable_qty"] = "int"
# ///持仓成本
XTPQueryStkPositionRsp["avg_price"] = "float"
# ///浮动盈亏
XTPQueryStkPositionRsp["unrealized_pnl"] = "float"
structDict['XTPQueryStkPositionRsp'] = XTPQueryStkPositionRsp







