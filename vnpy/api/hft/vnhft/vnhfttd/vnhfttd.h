//系统
#ifdef WIN32
#include "pch.h"
#endif

#include "vnhft.h"
#include "pybind11/pybind11.h"
#include "hft/hft_trader_api.h"


using namespace pybind11;
using namespace HFT;



///-------------------------------------------------------------------------------------
///C++ SPI的回调函数方法实现
///-------------------------------------------------------------------------------------

//API的继承实现
class TdApi : public TraderSpi
{
private:
	TraderApi* api;            //API对象
    bool active = false;       //工作状态

public:
    TdApi()
    {
    };

    ~TdApi()
    {
        if (this->active)
        {
            this->exit();
        }
    };

    //-------------------------------------------------------------------------------------
    //API回调函数
    //-------------------------------------------------------------------------------------

	/**
	 * 连接断开时回调
	 */
	virtual void OnDisconnect();

	/**
	 * 错误消息回调，系统出错时才会回调
	 *
	 * @param error_info    错误信息
	 * @param request_id    对应请求时传入的序列号，如果不是请求触发的错误，此字段值为0
	 */
	virtual void OnError(ErrorInfo* error_info, int request_id = 0);

	/**
	 * 风控告警信息通知回调
	 *
	 * @param risk_notify   风控告警信息
	 */
	virtual void OnRiskNotify(RiskNotify* risk_notify);

	/**
	 * 登录成功或失败时回调
	 *
	 * @param rsp           登录应答数据，包含客户号、客户姓名、股东代码等信息
	 * @param error_info    错误信息
	 */
	virtual void OnLogin(LoginRsp* rsp, ErrorInfo* error_info);

	/**
	 * 成交回报回调
	 *
	 * @param trade_detail  回调的成交详情对象
	 */
	virtual void OnTradeReport(TradeDetail* trade_detail);

	/**
	 * 订单状态变化回调
	 *
	 * @param order_detail  回调的订单对象
	 */
	virtual void OnOrderStatus(OrderDetail* order_detail);

	/**
	 * 订单委托的响应
	 *
	 * @param order_rsp     订单委托应答
	 * @param error_info    应答的错误信息
	 * @param request_id    对应请求时传入的序列号
	 * @param is_last       是否是本次请求的最后一笔响应
	 */
	virtual void OnOrderRsp(OrderRsp* order_rsp, ErrorInfo* error_info,
		int request_id, bool is_last);

	/**
	 * 撤单的响应
	 *
	 * @param cancel_rsp    撤单应答
	 * @param error_info    应答的错误信息
	 * @param request_id    对应请求时传入的序列号
	 * @param is_last       是否是本次请求的最后一笔响应
	 */
	virtual void OnCancelRsp(CancelRsp* cancel_rsp, ErrorInfo* error_info,
		int request_id, bool is_last);

	/**
	 * 查询当日订单详情的响应，一次返回一个订单详情
	 * QueryOrder、QueryOrderByCode、QueryOrders均由此接口响应
	 *
	 * @param order_detail  订单详情
	 * @param error_info    应答的错误信息
	 * @param request_id    对应请求时传入的序列号
	 * @param is_last       是否是本次请求的最后一笔响应
	 * @param pos_str       本次查询最后一条记录的定位串，用于下一次查询
	 */
	virtual void OnQueryOrderRsp(OrderDetail* order_detail,
		ErrorInfo* error_info, int request_id,
		bool is_last, const char* pos_str);

	/**
	 * 查询当日成交详情的响应，一次返回一个成交详情
	 * QueryTradeByCode、QueryTradeByOrderId、QueryTrades、QueryETFTrades均由此接口响应
	 *
	 * @param trade_detail  成交详情
	 * @param error_info    应答的错误信息
	 * @param request_id    对应请求时传入的序列号
	 * @param is_last       是否是本次请求的最后一笔响应
	 * @param pos_str       本次查询最后一条记录的定位串，用于下一次查询
	 */
	virtual void OnQueryTradeRsp(TradeDetail* trade_detail,
		ErrorInfo* error_info, int request_id,
		bool is_last, const char* pos_str);

	/**
	 * 查询当日持仓详情的响应，一次返回一个持仓详情
	 * QueryPosition、QueryPositions由此接口响应
	 *
	 * @param position_detail   持仓详情
	 * @param error_info        应答的错误信息
	 * @param request_id        对应请求时传入的序列号
	 * @param is_last           是否是最后一笔响应
	 * @param pos_str           本次查询最后一条记录的定位串，用于下一次查询
	 */
	virtual void OnQueryPositionRsp(PositionDetail* position_detail,
		ErrorInfo* error_info, int request_id,
		bool is_last, const char* pos_str);

	/**
	 * 查询当日资金的响应
	 *
	 * @param cash_detail   资金详情
	 * @param error_info    应答的错误信息
	 * @param request_id    对应请求时传入的序列号
	 */
	virtual void OnQueryCashRsp(CashDetail* cash_detail, ErrorInfo* error_info,
		int request_id);

	/**
	 * 查集中交易系统可用资金
	 *
	 * @param avail_balance 可用资金，单位：人民币
	 * @param error_info    应答的错误信息
	 * @param request_id    请求序列号，用于匹配响应，由用户自定义，非0
	 */
	virtual void OnQueryJZJYAvailFundRsp(int64_t avail_balance,
		ErrorInfo* error_info,
		int request_id);

	/**
	 * 集中交易柜台与快速柜台之间资金转入转出
	 *
	 * @param transfer_value    划转金额
	 * @param error_info        应答的错误信息
	 * @param request_id        请求序列号，用于匹配响应，由用户自定义
	 */
	virtual void OnTransferFundInAndOutRsp(int64_t transfer_value,
		ErrorInfo* error_info,
		int request_id);

	/**
	 * 针对同一个资金账号，一户两地之间资金划转
	 *
	 * @param transfer_value    划转金额
	 * @param error_info        应答的错误信息
	 * @param request_id        请求序列号，用于匹配响应，由用户自定义
	 */
	virtual void OnTransferFundBetweenSecuidRsp(int64_t transfer_value,
		ErrorInfo* error_info,
		int request_id);

	/**
	 * 查询ETF基本信息的响应，每次返回一个ETF信息
	 *
	 * @param etf_detail    ETF基本信息详情
	 * @param error_info    应答的错误信息
	 * @param request_id    对应请求时传入的序列号
	 * @param is_last       是否是本次请求的最后一笔响应
	 */
	virtual void OnQueryETFRsp(ETFDetail* etf_detail, ErrorInfo* error_info,
		int request_id, bool is_last);

	/**
	 * 查询一个ETF股票篮子的响应，每次返回ETF的一个股票信息
	 *
	 * @param etf_stock_detail      ETF的一个股票信息
	 * @param error_info            应答的错误信息
	 * @param request_id            对应请求时传入的序列号
	 * @param is_last               是否是本次请求的最后一笔响应
	 */
	virtual void OnQueryETFStockRsp(ETFStockDetail* etf_stock_detail,
		ErrorInfo* error_info, int request_id,
		bool is_last);

	/**
	 * 查询最大可委托数量回调
	 *
	 * @param detail        最大可委托数量数据
	 * @param error_info    应答的错误信息
	 * @param request_id    请求序列号，用于匹配响应，由用户自定义，非0
	 */
	virtual void OnQueryMaxOrderQtyRsp(MaxOrderQtyDetail* detail,
		ErrorInfo* error_info, int request_id);

	/**
	 * 查询新股可申购额度的响应
	 *
	 * @param detail        新股可申购额度数据
	 * @param error_info    应答的错误信息
	 * @param request_id    对应请求时传入的序列号
	 */
	virtual void OnQueryIPOMaxPurchaseRsp(IPOMaxPurchaseDetail* detail,
		ErrorInfo* error_info, int request_id,
		bool is_last);

	/**
	 * 查询新股的响应
	 *
	 * @param detail        新股数据
	 * @param error_info    应答的错误信息
	 * @param request_id    对应请求时传入的序列号
	 */
	virtual void OnQueryIPOStockRsp(IPOStockDetail* detail,
		ErrorInfo* error_info, int request_id,
		bool is_last);

	/**
	 * 查询新股配号的响应
	 *
	 * @param detail        新股配号数据
	 * @param error_info    应答的错误信息
	 * @param request_id    对应请求时传入的序列号
	 * @param is_last       是否是本次请求的最后一笔响应
	 * @param pos_str       本次查询最后一条记录的定位串，用于下一次查询
	 */
	virtual void OnQueryIPODistributionRsp(IPODistributionDetail* detail,
		ErrorInfo* error_info,
		int request_id, bool is_last,
		const char* pos_str);

	/**
	 * 查询新股中签的响应
	 *
	 * @param detail        新股中签数据
	 * @param error_info    应答的错误信息
	 * @param request_id    对应请求时传入的序列号
	 * @param is_last       是否是本次请求的最后一笔响应
	 * @param pos_str       本次查询最后一条记录的定位串，用于下一次查询
	 */
	virtual void OnQueryIPOLotteryRsp(IPOLotteryDetail* detail,
		ErrorInfo* error_info, int request_id,
		bool is_last, const char* pos_str);

	/**
	* 查询证券信息的响应
	*
	* @param detail            证券信息
	* @param error_info        应答的错误信息
	* @param request_id        对应请求时传入的序列号
	* @param is_last           是否是最后一笔响应
	*/
	virtual void OnQuerySecurityBaseInfoRsp(SecurityBaseInfo* detail, ErrorInfo* error_info,
		int request_id, bool is_last);

	/**
	 * 担保品转入转出应答回调
	 *
	 * @param rsp           担保品转入转出应答
	 * @param error_info    应答的错误信息
	 * @param request_id    对应请求时传入的序列号
	 */
	virtual void OnCreditMortgageInOutRsp(CreditMortgageInOutRsp* rsp,
		ErrorInfo* error_info,
		int request_id);

	/**
	 * 现券还券应答回调
	 *
	 * @param rsp           现券还券应答
	 * @param error_info    应答的错误信息
	 * @param request_id    对应请求时传入的序列号
	 */
	virtual void OnCreditStockBackRsp(CreditStockBackRsp* rsp,
		ErrorInfo* error_info, int request_id);

	/**
	 * 直接还款应答回调
	 *
	 * @param rsp           直接还款应答
	 * @param error_info    应答的错误信息
	 * @param request_id    对应请求时传入的序列号
	 */
	virtual void OnCreditPayBackRsp(CreditPayBackRsp* rsp,
		ErrorInfo* error_info, int request_id);

	/**
	 * 指定合约直接还款
	 *
	 * @param rsp           还款信息
	 * @param error_info    应答的错误信息
	 * @param request_id    请求序列号，用于匹配响应，由用户自定义
	 */
	virtual void OnCreditPayBackByOrderRsp(CreditPayBackRsp* rsp,
		ErrorInfo* error_info,
		int request_id);

	/**
	 * 信用标的券应答回调
	 *
	 * @param detail        信用标的券数据
	 * @param error_info    应答的错误信息
	 * @param request_id    对应请求时传入的序列号
	 * @param is_last       是否是本次请求的最后一笔响应
	 * @param pos_str       本次查询最后一条记录的定位串，用于下一次查询
	 */
	virtual void OnQueryCreditStockRsp(CreditStockDetail* detail,
		ErrorInfo* error_info, int request_id,
		bool is_last, const char* pos_str);

	/**
	 * 查询担保品券回调
	 *
	 * @param detail        担保品券信息
	 * @param error_info    应答的错误信息
	 * @param request_id    请求序列号，用于匹配响应，由用户自定义，非0
	 * @param is_last       是否是本次请求的最后一笔响应
	 * @param pos_str       本次查询最后一条记录的定位串，用于下一次查询
	 */
	virtual void OnQueryCreditMortgageHoldRsp(CreditMortgageHoldDetail* detail,
		ErrorInfo* error_info,
		int request_id, bool is_last,
		const char* pos_str);

	/**
	 * 信用资产查询应答回调
	 *
	 * @param detail        信用资产数据
	 * @param error_info    应答的错误信息
	 * @param request_id    对应请求时传入的序列号
	 */
	virtual void OnQueryCreditAssetsRsp(CreditAssetsDetail* detail,
		ErrorInfo* error_info, int request_id);

	/**
	 * 查询融资合约应答回调
	 *
	 * @param detail        融资合约数据
	 * @param error_info    应答的错误信息
	 * @param request_id    对应请求时传入的序列号
	 * @param is_last       是否是本次请求的最后一笔响应
	 * @param pos_str       本次查询最后一条记录的定位串，用于下一次查询
	 */
	virtual void OnQueryCreditFinanceRsp(CreditFinanceDetail* detail,
		ErrorInfo* error_info, int request_id,
		bool is_last, const char* pos_str);

	/**
	 * 查询融券合约应答回调
	 *
	 * @param detail        融券合约数据
	 * @param error_info    应答的错误信息
	 * @param request_id    对应请求时传入的序列号
	 * @param is_last       是否是本次请求的最后一笔响应
	 * @param pos_str       本次查询最后一条记录的定位串，用于下一次查询
	 */
	virtual void OnQueryCreditShortsellRsp(CreditShortsellDetail* detail,
		ErrorInfo* error_info,
		int request_id, bool is_last,
		const char* pos_str);

	/**
	 * 查询可还融资负债金额应答回调
	 *
	 * @param detail        可还金额数据
	 * @param error_info    应答的错误信息
	 * @param request_id    对应请求时传入的序列号
	 */
	virtual void OnQueryCreditRepayAmountRsp(CreditRepayAmountDetail* detail,
		ErrorInfo* error_info,
		int request_id);

	/**
	 * 查询信用融券负债数量应答回调
	 *
	 * @param detail        可还数据
	 * @param error_info    应答的错误信息
	 * @param request_id    对应请求时传入的序列号
	 * @param is_last       是否是本次请求的最后一笔响应
	 * @param pos_str       本次查询最后一条记录的定位串，用于下一次查询
	 */
	virtual void OnQueryCreditRepayStockRsp(CreditRepayStockDetail* detail,
		ErrorInfo* error_info,
		int request_id, bool is_last,
		const char* pos_str);

	/**
	 * 查询可融券卖出数量，此数量是指锁券的可用量
	 *
	 * @param rsp               查询数量信息
	 * @param error_info        应答的错误信息
	 * @param request_id        请求序列号，用于匹配响应，由用户自定义
	 * @param is_last           是否是本次请求的最后一笔响应
	 */
	virtual void OnQueryCreditSecuritySellQtyRsp(CreditSecuritySellQtyRsp* rsp,
		ErrorInfo* error_info,
		int request_id, bool is_last);

	/**
	 * 查询账户交易权限回调
	 *
	 * @param market        市场,如"SZ SH",原样返回的请求参数
	 * @param secuid_right  权限类型,如创业板,原样返回的请求参数
	 * @param error_info    应答的错误信息
	 * @param sign_flag     签署权限标志,true即有权限
	 * @param request_id    请求序列号，用于匹配响应，由用户自定义，非0
	 */
	virtual void OnQuerySecuidRightRsp(const char* market, int16_t secuid_right,
		ErrorInfo* error_info, bool sign_flag,
		int request_id);

	// 沪港通、深港通特有接口
	/**
	 * 查询沪港通参考汇率的响应
	 *
	 * @param detail        沪港通参考汇率数据
	 * @param error_info    应答的错误信息
	 * @param request_id    对应请求时传入的序列号
	 * @param is_last       是否是本次请求的最后一笔响应
	 */
	virtual void OnQueryHKRateRsp(HKRateDetail* detail, ErrorInfo* error_info,
		int request_id, bool is_last);

	/**
	 * 查询沪港通标的券的响应
	 *
	 * @param detail        沪港通标的券数据
	 * @param error_info    应答的错误信息
	 * @param request_id    对应请求时传入的序列号
	 * @param is_last       是否是本次请求的最后一笔响应
	 */
	virtual void OnQueryHKStockRsp(HKStockDetail* detail, ErrorInfo* error_info,
		int request_id, bool is_last);

	/**
	 * 查询沪港通辅资金表资产的响应
	 *
	 * @param detail        沪港通辅资金表资产数据
	 * @param error_info    应答的错误信息
	 * @param request_id    对应请求时传入的序列号
	 */
	virtual void OnQueryHKFundRsp(HKFundDetail* detail, ErrorInfo* error_info,
		int request_id);

	/**
	 * 查询沪港通最小价差的响应
	 *
	 * @param detail        沪港通最小价差数据
	 * @param error_info    应答的错误信息
	 * @param request_id    对应请求时传入的序列号
	 * @param is_last       是否是本次请求的最后一笔响应
	 */
	virtual void OnQueryHKMinPriceUnitRsp(HKMinPriceUnitDetail* detail,
		ErrorInfo* error_info, int request_id,
		bool is_last);

	/**
	 * 查询沪港通交易日历的响应
	 *
	 * @param detail        沪港通交易日历数据
	 * @param error_info    应答的错误信息
	 * @param request_id    对应请求时传入的序列号
	 * @param is_last       是否是本次请求的最后一笔响应
	 */
	virtual void OnQueryHKTradeCalendarRsp(HKTradeCalendarDetail* detail,
		ErrorInfo* error_info,
		int request_id, bool is_last);

	/**
	 * 查询锁券明细应答
	 *
	 * @param detail        锁券明细数据
	 * @param error_info    应答的错误信息
	 * @param request_id    对应请求时传入的序列号
	 * @param is_last       是否是本次请求的最后一笔响应
	 */
	virtual void OnQueryLockSecurityDetailRsp(LockSecurityDetail* detail,
		ErrorInfo* error_info,
		int request_id, bool is_last);

	/**
	 * 展期应答
	 *
	 * @param apply_sno     申请编号
	 * @param apply_date    申请日期
	 * @param error_info    应答的错误信息
	 * @param request_id    请求序列号，用于匹配响应，由用户自定义，非0
	 */
	virtual void OnExtendLockSecurityRsp(int32_t apply_sno, int32_t apply_date,
		ErrorInfo* error_info,
		int request_id);

	/**
	 * 查询展期申请应答
	 *
	 * @param detail        展期明细数据
	 * @param error_info    应答的错误信息
	 * @param request_id    对应请求时传入的序列号
	 * @param is_last       是否是本次请求的最后一笔响应
	 */
	virtual void OnQueryLockSecurityExtensionRsp(
		LockSecurityExtensionDetail* detail, ErrorInfo* error_info,
		int request_id, bool is_last);

	/**
	 * 撤销锁券展期申请应答
	 *
	 * @param apply_date    申请日期，如20190415
	 * @param apply_sno     申请序号
	 * @param cancel_sno    撤销序号
	 * @param error_info    应答的错误信息
	 * @param request_id    对应请求时传入的序列号
	 */
	virtual void OnCancelExtendLockSecurityRsp(int apply_date,
		const char* apply_sno,
		const char* cancel_sno,
		ErrorInfo* error_info,
		int request_id);

	/**
	 * 查询资金划转流水的响应
	 *
	 * @param detail        资金划转明细数据
	 * @param error_info    应答的错误信息
	 * @param request_id    对应请求时传入的序列号
		 * @param is_last       是否是本次请求的最后一笔响应
		 */
	virtual void OnQueryTransferFundHistoryRsp(TransferFundDetail* detail,
		ErrorInfo* error_info,
		int request_id, bool is_last);



    //-------------------------------------------------------------------------------------
    //data：回调函数的数据字典
    //error：回调函数的错误字典
    //id：请求id
    //last：是否为最后返回
    //i：整数
    //-------------------------------------------------------------------------------------
	virtual void onDisconnect() {};

	virtual void onError(const dict &error, int request_id) {};

	virtual void onRiskNotify(const dict &data) {};

	virtual void onLogin(const dict &data, const dict &error) {};

	virtual void onTradeReport(const dict &data) {};

	virtual void onOrderStatus(const dict &data) {};

	virtual void onOrderRsp(const dict &data, const dict &error, int request_id, bool last) {};

	virtual void onCancelRsp(const dict &data, const dict &error, int request_id, bool last) {};

	virtual void onQueryOrderRsp(const dict &data, const dict &error, int request_id, bool last, string pos_str) {};

	virtual void onQueryTradeRsp(const dict &data, const dict &error, int request_id, bool last, string pos_str) {};

	virtual void onQueryPositionRsp(const dict &data, const dict &error, int request_id, bool last, string pos_str) {};

	virtual void onQueryCashRsp(const dict &data, const dict &error, int request_id) {};

	virtual void onQueryJZJYAvailFundRsp(int64_t avail_balance, const dict &error, int request_id) {};

	virtual void onTransferFundInAndOutRsp(int64_t transfer_value, const dict &error, int request_id) {};

	virtual void onTransferFundBetweenSecuidRsp(int64_t transfer_value, const dict &error, int request_id) {};

	virtual void onQueryETFRsp(const dict &data, const dict &error, int request_id, bool last) {};

	virtual void onQueryETFStockRsp(const dict &data, const dict &error, int request_id, bool last) {};

	virtual void onQueryMaxOrderQtyRsp(const dict &data, const dict &error, int request_id) {};

	virtual void onQueryIPOMaxPurchaseRsp(const dict &data, const dict &error, int request_id, bool last) {};

	virtual void onQueryIPOStockRsp(const dict &data, const dict &error, int request_id, bool last) {};

	virtual void onQueryIPODistributionRsp(const dict &data, const dict &error, int request_id, bool last, string pos_str) {};

	virtual void onQueryIPOLotteryRsp(const dict &data, const dict &error, int request_id, bool last, string pos_str) {};

	virtual void onQuerySecurityBaseInfoRsp(const dict &data, const dict &error, int request_id, bool last) {};

	virtual void onCreditMortgageInOutRsp(const dict &data, const dict &error, int request_id) {};

	virtual void onCreditStockBackRsp(const dict &data, const dict &error, int request_id) {};

	virtual void onCreditPayBackRsp(const dict &data, const dict &error, int request_id) {};

	virtual void onCreditPayBackByOrderRsp(const dict &data, const dict &error, int request_id) {};

	virtual void onQueryCreditStockRsp(const dict &data, const dict &error, int request_id, bool last, string pos_str) {};

	virtual void onQueryCreditMortgageHoldRsp(const dict &data, const dict &error, int request_id, bool last, string pos_str) {};

	virtual void onQueryCreditAssetsRsp(const dict &data, const dict &error, int request_id) {};

	virtual void onQueryCreditFinanceRsp(const dict &data, const dict &error, int request_id, bool last, string pos_str) {};

	virtual void onQueryCreditShortsellRsp(const dict &data, const dict &error, int request_id, bool last, string pos_str) {};

	virtual void onQueryCreditRepayAmountRsp(const dict &data, const dict &error, int request_id) {};

	virtual void onQueryCreditRepayStockRsp(const dict &data, const dict &error, int request_id, bool last, string pos_str) {};

	virtual void onQueryCreditSecuritySellQtyRsp(const dict &data, const dict &error, int request_id, bool last) {};

	virtual void onQuerySecuidRightRsp(string market, int secuid_right, const dict &error, bool last, int request_id) {};

	virtual void onQueryHKRateRsp(const dict &data, const dict &error, int request_id, bool last) {};

	virtual void onQueryHKStockRsp(const dict &data, const dict &error, int request_id, bool last) {};

	virtual void onQueryHKFundRsp(const dict &data, const dict &error, int request_id) {};

	virtual void onQueryHKMinPriceUnitRsp(const dict &data, const dict &error, int request_id, bool last) {};

	virtual void onQueryHKTradeCalendarRsp(const dict &data, const dict &error, int request_id, bool last) {};

	virtual void onQueryLockSecurityDetailRsp(const dict &data, const dict &error, int request_id, bool last) {};

	virtual void onExtendLockSecurityRsp(int apply_sno, int apply_date, const dict &error, int request_id) {};

	virtual void onQueryLockSecurityExtensionRsp(const dict &data, const dict &error, int request_id, bool last) {};

	virtual void onCancelExtendLockSecurityRsp(int apply_date, string apply_sno, string cancel_sno, const dict &error, int request_id) {};

	virtual void onQueryTransferFundHistoryRsp(const dict &data, const dict &error, int request_id, bool last) {};

    //-------------------------------------------------------------------------------------
    //req:主动函数的请求字典
    //-------------------------------------------------------------------------------------
	void setLogConfig(string log_path);

    void createTraderApi();

    void release();

    int exit();

    string getApiVersion();

	int login(string svr_ip, int svr_port, const dict &req, string terminal_info);

	int getCounterType();

	pybind11::list getSecuidInfo();

	dict getApiLocalAddr();

	int order(const dict &req, int request_id);

	int batchOrder(const dict &req, int count, int request_id);

	int cancelOrder(const dict &req, int request_id);

	int batchCancelOrder(const dict &req, int count, int request_id);

	int queryOrder(string order_id, int request_id, string market);

	int queryOrderByCode(string symbol, int request_id);

	int queryOrders(string pos_str, int query_num, int request_id, int query_flag);

	int queryTradeByOrderId(string order_id, int request_id, string market);

	int queryTradeByCode(string symbol, int request_id);

	int queryTrades(string pos_str, int query_num, int request_id);

	int queryETFTrades(string pos_str, int query_num, int request_id, string market);

	int queryPosition(string symbol, int request_id);

	int queryPositions(string pos_str, int query_num, int request_id);

	int queryCash(int request_id);

	int queryJZJYAvailFund(int request_id);

	int transferFundInAndOut(int transfer_side, int transfer_value, int request_id, string market);

	int transferFundBetweenSecuid(string fund_out_market, string fund_in_market, int transfer_value, int request_id);

	int queryETFs(int request_id);

	int queryETFStocks(string first_symbol, int request_id);

	int queryMaxOrderQty(string symbol, int order_type, int side, int price, int request_id);

	int queryIPOMaxPurchase(int request_id);

	int queryIPOStock(int request_id, int query_flag);

	int queryIPODistribution(int start_date, int end_date, string pos_str, int query_num, int request_id);

	int queryIPOLottery(int start_date, int end_date, string pos_str, int query_num, int request_id);

	int querySecurityBaseInfo(int request_id, string symbol);

	int creditMortgageInOut(const dict &req, int request_id);

	int creditStockBack(const dict &req, int request_id);

	int creditPayBack(int back_amt, int request_id);

	int creditPayBackByOrder(string order_id, int order_date, int back_amt, int request_id);

	int queryCreditStock(string pos_str, int query_num, int request_id);

	int queryCreditMortgageHold(string pos_str, int query_num, int request_id);

	int queryCreditAssets(int request_id);

	int queryCreditFinance(string pos_str, int query_num, int request_id);

	int queryCreditShortsell(string pos_str, int query_num, int request_id);

	int queryCreditRepayAmount(int request_id);

	int queryCreditRepayStock(string market, string code, int request_id);

	int queryCreditSecuritySellQty(string market, string code, int request_id);

	int querySecuidRight(string market, int secuid_right, int request_id);

	int queryHKRate(string market, int request_id);

	int queryHKStock(string market, int request_id);

	int queryHKFund(int request_id);

	int queryHKMinPriceUnit(string market, int request_id);

	int queryHKTradeCalendar(int start_date, int end_date, int request_id);

	int queryLockSecurityDetail(int begin_date, int end_date, int request_id, string market, string code);

	int extendLockSecurity(const dict &req, int request_id);

	int queryLockSecurityExtension(int begin_date, int end_date, int request_id);

	int cancelExtendLockSecurity(int apply_date, string apply_sno, int request_id);

	int queryTransferFundHistory(int request_id);



};
