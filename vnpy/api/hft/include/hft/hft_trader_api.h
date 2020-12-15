/**
 * @file    hft_trader_api.h
 * @brief   现货交易相关接口定义
 */

#ifndef _HFT_TRADER_API_H_
#define _HFT_TRADER_API_H_

#include <vector>
#include "hft_trader_struct.h"

/**
 * 统一说明接口中关于交易终端信息字段terminal_info格式要求：
 * PC终端格式如下：
 *     PC;IIP=xxx.xxx.xxx.xxx;IPORT=xxxxx;LIP=xxx.xxx.xxx.xxx;MAC=xxxxxxxxx^xxxxxxxxx;HD=xxxxxxxxx;CPU=xxxxxxxxx@ClientName;V1.0.1
 * 字段含义：
 *     PC===>终端类型为PC电脑
 *     IIP==>公网IP；IPORT==>公网端口（若没有公网接入则填写内网IP和端口号）
 *     LIP==>内网IP；MAC==>网卡MAC地址，可支持多个，使用^分隔
 *     HD==>硬盘序列号；CPU==>CPU序列号
 *     ClientName===>PC终端名称；V1.0.1===>PC终端版本号
 *
 * 手机终端格式如下：
 *     Android终端信息示例：
 *     MA;IIP=xxx.xxx.xxx.xxx;IPORT=xxxxx;LIP=xxx.xxx.xxx.xxx;MAC=xxxxxxxxx^xxxxxxxxx;IMEI=xxxxxxxxx;RMPN=xxxxxxxxx;UMPN=xxxxxxxxx@MobileAppName;V1.0.1
 *     iOS终端信息示例：
 *     MI;IIP=xxx.xxx.xxx.xxx;IPORT=xxxxx;LIP=xxx.xxx.xxx.xxx;MAC=xxxxxxxxx^xxxxxxxxx;IDFV=xxxxxxxxx;RMPN=xxxxxxxxx;UMPN=xxxxxxxxx@MobileAppName;V1.0.1
 * 字段含义：
 *     移动终端类型包括：MI===>iOS终端； MA===>Android终端；OH===>其他移动终端类型，包含Windows Phone
 *     IIP==>公网IP；IPORT==>公网端口（若没有公网接入则填写内网IP和端口号）
 *     LIP==>内网IP；MAC==>网卡MAC地址，可支持多个，使用^分隔
 *     IMEI==>移动Android端的标识符
 *     IDFV==>应商标识符（Identifier For Vendor），是指移动应用程序开发商用于识别用户的标识符。在同一iOS系统移动终端设备上，同一开发商的不同移动应用程序共用同一IDFV；在不同iOS系统移动终端设备上IDFV不同，由36位数字或字母组成
 *     RMPN==>注册手机号码；UMPN==>实际使用手机号码
 *     MobileAppName==>移动终端名称；V1.0.1==>移动终端版本号
 */

namespace HFT {

// 回调接口类定义
class TraderSpi {
   public:
    virtual ~TraderSpi() {}

    /**
     * 连接断开时回调
     */
    virtual void OnDisconnect() {}

    /**
     * 错误消息回调，系统出错时才会回调
     * 
     * @param error_info    错误信息
     * @param request_id    对应请求时传入的序列号，如果不是请求触发的错误，此字段值为0
     */
    virtual void OnError(ErrorInfo* error_info, int request_id = 0) {}

    /**
     * 风控告警信息通知回调
     * 
     * @param risk_notify   风控告警信息
     */
    virtual void OnRiskNotify(RiskNotify* risk_notify) {}

    /**
     * 登录成功或失败时回调
     * 
     * @param rsp           登录应答数据，包含客户号、客户姓名、股东代码等信息
     * @param error_info    错误信息
     */
    virtual void OnLogin(LoginRsp* rsp, ErrorInfo* error_info) {}

    /**
     * 成交回报回调
     *
     * @param trade_detail  回调的成交详情对象
     */
    virtual void OnTradeReport(TradeDetail* trade_detail) {}

    /**
     * 订单状态变化回调
     *
     * @param order_detail  回调的订单对象
     */
    virtual void OnOrderStatus(OrderDetail* order_detail) {}

    /**
     * 订单委托的响应
     *
     * @param order_rsp     订单委托应答
     * @param error_info    应答的错误信息
     * @param request_id    对应请求时传入的序列号
     * @param is_last       是否是本次请求的最后一笔响应
     */
    virtual void OnOrderRsp(OrderRsp* order_rsp, ErrorInfo* error_info,
                            int request_id, bool is_last) {}

    /**
     * 撤单的响应
     *
     * @param cancel_rsp    撤单应答
     * @param error_info    应答的错误信息
     * @param request_id    对应请求时传入的序列号
     * @param is_last       是否是本次请求的最后一笔响应
     */
    virtual void OnCancelRsp(CancelRsp* cancel_rsp, ErrorInfo* error_info,
                             int request_id, bool is_last) {}

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
                                 bool is_last, const char* pos_str) {}

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
                                 bool is_last, const char* pos_str) {}

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
                                    bool is_last, const char* pos_str) {}

    /**
     * 查询当日资金的响应
     * 
     * @param cash_detail   资金详情
     * @param error_info    应答的错误信息
     * @param request_id    对应请求时传入的序列号
     */
    virtual void OnQueryCashRsp(CashDetail* cash_detail, ErrorInfo* error_info,
                                int request_id) {}

    /**
     * 查集中交易系统可用资金
     *
     * @param avail_balance 可用资金，单位：人民币
     * @param error_info    应答的错误信息
     * @param request_id    请求序列号，用于匹配响应，由用户自定义，非0
     */
    virtual void OnQueryJZJYAvailFundRsp(int64_t avail_balance,
                                         ErrorInfo* error_info,
                                         int request_id) {}

    /**
     * 集中交易柜台与快速柜台之间资金转入转出
     *
     * @param transfer_value    划转金额
     * @param error_info        应答的错误信息
     * @param request_id        请求序列号，用于匹配响应，由用户自定义
     */
    virtual void OnTransferFundInAndOutRsp(int64_t transfer_value,
                                           ErrorInfo* error_info,
                                           int request_id) {}

    /**
     * 针对同一个资金账号，一户两地之间资金划转
     *
     * @param transfer_value    划转金额
     * @param error_info        应答的错误信息
     * @param request_id        请求序列号，用于匹配响应，由用户自定义
     */
    virtual void OnTransferFundBetweenSecuidRsp(int64_t transfer_value,
                                                ErrorInfo* error_info,
                                                int request_id) {}

    /**
     * 查询ETF基本信息的响应，每次返回一个ETF信息
     * 
     * @param etf_detail    ETF基本信息详情
     * @param error_info    应答的错误信息
     * @param request_id    对应请求时传入的序列号
     * @param is_last       是否是本次请求的最后一笔响应
     */
    virtual void OnQueryETFRsp(ETFDetail* etf_detail, ErrorInfo* error_info,
                               int request_id, bool is_last) {}

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
                                    bool is_last) {}

    /**
     * 查询最大可委托数量回调
     *
     * @param detail        最大可委托数量数据
     * @param error_info    应答的错误信息
     * @param request_id    请求序列号，用于匹配响应，由用户自定义，非0
     */
    virtual void OnQueryMaxOrderQtyRsp(MaxOrderQtyDetail* detail,
                                       ErrorInfo* error_info, int request_id) {}

    /**
     * 查询新股可申购额度的响应
     *
     * @param detail        新股可申购额度数据
     * @param error_info    应答的错误信息
     * @param request_id    对应请求时传入的序列号
     */
    virtual void OnQueryIPOMaxPurchaseRsp(IPOMaxPurchaseDetail* detail,
                                          ErrorInfo* error_info, int request_id,
                                          bool is_last) {}

    /**
     * 查询新股的响应
     *
     * @param detail        新股数据
     * @param error_info    应答的错误信息
     * @param request_id    对应请求时传入的序列号
     */
    virtual void OnQueryIPOStockRsp(IPOStockDetail* detail,
                                    ErrorInfo* error_info, int request_id,
                                    bool is_last) {}

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
                                           const char* pos_str) {}

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
                                      bool is_last, const char* pos_str) {}

    /**
    * 查询证券信息的响应
    *
    * @param detail            证券信息
    * @param error_info        应答的错误信息
    * @param request_id        对应请求时传入的序列号
    * @param is_last           是否是最后一笔响应
    */
    virtual void OnQuerySecurityBaseInfoRsp(SecurityBaseInfo* detail, ErrorInfo* error_info,
                                            int request_id, bool is_last) {}

    /**
     * 担保品转入转出应答回调
     *
     * @param rsp           担保品转入转出应答
     * @param error_info    应答的错误信息
     * @param request_id    对应请求时传入的序列号
     */
    virtual void OnCreditMortgageInOutRsp(CreditMortgageInOutRsp* rsp,
                                          ErrorInfo* error_info,
                                          int request_id) {}

    /**
     * 现券还券应答回调
     *
     * @param rsp           现券还券应答
     * @param error_info    应答的错误信息
     * @param request_id    对应请求时传入的序列号
     */
    virtual void OnCreditStockBackRsp(CreditStockBackRsp* rsp,
                                      ErrorInfo* error_info, int request_id) {}

    /**
     * 直接还款应答回调
     *
     * @param rsp           直接还款应答
     * @param error_info    应答的错误信息
     * @param request_id    对应请求时传入的序列号
     */
    virtual void OnCreditPayBackRsp(CreditPayBackRsp* rsp,
                                    ErrorInfo* error_info, int request_id) {}

    /**
     * 指定合约直接还款
     *
     * @param rsp           还款信息
     * @param error_info    应答的错误信息
     * @param request_id    请求序列号，用于匹配响应，由用户自定义
     */
    virtual void OnCreditPayBackByOrderRsp(CreditPayBackRsp* rsp,
                                           ErrorInfo* error_info,
                                           int request_id) {}

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
                                       bool is_last, const char* pos_str) {}

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
                                              const char* pos_str) {}

    /**
     * 信用资产查询应答回调
     *
     * @param detail        信用资产数据
     * @param error_info    应答的错误信息
     * @param request_id    对应请求时传入的序列号
     */
    virtual void OnQueryCreditAssetsRsp(CreditAssetsDetail* detail,
                                        ErrorInfo* error_info, int request_id) {
    }

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
                                         bool is_last, const char* pos_str) {}

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
                                           const char* pos_str) {}

    /**
     * 查询可还融资负债金额应答回调
     *
     * @param detail        可还金额数据
     * @param error_info    应答的错误信息
     * @param request_id    对应请求时传入的序列号
     */
    virtual void OnQueryCreditRepayAmountRsp(CreditRepayAmountDetail* detail,
                                             ErrorInfo* error_info,
                                             int request_id) {}

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
                                            const char* pos_str) {}

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
                                                 int request_id, bool is_last) {
    }

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
                                       int request_id) {}

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
                                  int request_id, bool is_last) {}

    /**
     * 查询沪港通标的券的响应
     *
     * @param detail        沪港通标的券数据
     * @param error_info    应答的错误信息
     * @param request_id    对应请求时传入的序列号
     * @param is_last       是否是本次请求的最后一笔响应
     */
    virtual void OnQueryHKStockRsp(HKStockDetail* detail, ErrorInfo* error_info,
                                   int request_id, bool is_last) {}

    /**
     * 查询沪港通辅资金表资产的响应
     *
     * @param detail        沪港通辅资金表资产数据
     * @param error_info    应答的错误信息
     * @param request_id    对应请求时传入的序列号
     */
    virtual void OnQueryHKFundRsp(HKFundDetail* detail, ErrorInfo* error_info,
                                  int request_id) {}

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
                                          bool is_last) {}

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
                                           int request_id, bool is_last) {}

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
                                              int request_id, bool is_last) {}

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
                                         int request_id) {}

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
        int request_id, bool is_last) {}

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
                                               int request_id) {}

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
												   int request_id, bool is_last) {}
};

// 交易接口类定义
class HFT_TRADER_EXPORT TraderApi {
   public:
    /**
     * 获取TraderApi实例，此实例与登录的交易账号相关联
     * 
     * @return              返回TraderApi实例
     */
    static TraderApi* CreateTraderApi();

    /**
     * 获取API的版本信息
     */
    static const char* GetApiVersion();

    /**
     * 设置日志路径和日志级别，只需调用一次，在调用CreateTraderApi之前调用
     * 
     * @param log_path      日志文件存放目录，默认相对可执行程序所在的目录
     *                      路径包含中文，Windows上使用GBK，Linux上使用UTF8
     * @param log_level     日志级别，默认为LogLevel_Info
     */
    static void SetLogConfig(const char* log_path,
                             LogLevel log_level = LogLevel_Info);

    /**
     * 不再使用本接口对象时，调用该函数删除接口对象
     */
    virtual void Release() = 0;

    /**
     * 获取最新一次错误信息
     */
    virtual ErrorInfo* GetApiLastError() = 0;

    /**
     * 注册回调接口实例，需在Login之前调用
     * 
     * @param spi           派生自回调接口类的实例
     */
    virtual void RegisterSpi(TraderSpi* spi) = 0;

    /**
     * 发起用户登录请求
     *
     * @param svr_ip        交易服务器ip地址
     * @param svr_port      交易服务器端口
     * @param account       接入方交易账户相关信息
     * @param terminal_info 交易终端信息，格式需满足交易所要求，格式请见接口说明文档
     * 
     * @return              0表示发起登录成功，非0表示发起登录失败，通过GetApiLastError获取错误信息
     */
    virtual int Login(const char* svr_ip, int svr_port,
                      const AccountInfo* account_info,
                      const char* terminal_info) = 0;

    /**
     * 获取资金账号绑定的柜台类型，登陆成功后可获取
     * 
     * @return              返回柜台类型，请参考CounterType定义
     */
    virtual int GetCounterType() = 0;

    /**
     * 获取资金账号的股东账号信息，登陆成功后可获取
     *
     * @param secuids       指向股东账号数组的指针，需调用方分配数组内存
     * @param count         股东账号数组大小，count会返回实际的数组大小
     *
     * @return              成功返回0，失败返回错误码，通过GetApiLastError获取错误信息
     */
    virtual int GetSecuidInfo(SecuidInfo* secuids, int* count) = 0;

    /**
     * 获取接口连接网关时本地地址，登录成功后可获取
     * 内网连接时获取的是内网地址，外网连接时是外网地址
     *
     * @param localAddr     接口连接网关时本地地址
     */
    virtual int GetApiLocalAddr(IpAddr* localAddr) = 0;

    /**
     * 股票、场内基金、质押式回购下单、新股申购、ETF申购赎回
     *
     * @param order         传入下单请求对象
     * @param request_id    请求序列号，用于匹配响应，由用户自定义，非0
     *
     * @return              成功返回0，失败返回错误码，通过GetApiLastError获取错误信息
     */
    virtual int Order(OrderReq* order, int request_id) = 0;

    /**
     * 股票、场内基金、质押式回购下单、新股申购、ETF申购赎回，最大支持500个
     *
     * @param orders        传入下单请求对象数组
     * @param count         传入下单请求对象数组大小
     * @param request_id    请求序列号，用于匹配响应，由用户自定义，非0
     *
     * @return              成功返回0，失败返回错误码，通过GetApiLastError获取错误信息
     */
    virtual int BatchOrder(OrderReq* orders, int count, int request_id) = 0;

    /**
     * 单个撤单
     *
     * @param cancel        传入撤单请求对象
     * @param request_id    请求序列号，用于匹配响应，由用户自定义，非0
     *
     * @return              成功返回0，失败返回错误码，错误码定义在error.h文件
     */
    virtual int CancelOrder(CancelReq* cancel, int request_id) = 0;

    /**
     * 批量撤单，最大支持500个
     *
     * @param cancels       传入撤单请求对象数组
     * @param count         传入撤单请求对象数组大小
     * @param request_id    请求序列号，用于匹配响应，由用户自定义，非0
     *
     * @return              成功返回0，失败返回错误码，错误码定义在error.h文件
     */
    virtual int BatchCancelOrder(CancelReq* cancels, int count,
                                 int request_id) = 0;

    /**
     * 查询当日单个订单详情
     *
     * @param order_id      后台系统的订单id
     * @param request_id    请求序列号，用于匹配响应，由用户自定义，非0
     * @param market        市场，默认是查上海和深圳市场的委托，查询港股通委托需传HK，
     *                      深港通传SZHK，沪港通传SHHK，传SH或SZ是查上海或深圳的委托，大小写不敏感
     *
     * @return              成功返回0，失败返回错误码，通过GetApiLastError获取错误信息
     */
    virtual int QueryOrder(const char* order_id, int request_id,
                           const char* market = NULL) = 0;

    /**
     * 查当日指定标的委托列表
     *
     * @param symbol        标的代码，例如SH.600000
     * @param request_id    请求序列号，用于匹配响应，由用户自定义，非0
     *
     * @return              成功返回0，失败返回错误码，通过GetApiLastError获取错误信息
     */
    virtual int QueryOrderByCode(const char* symbol, int request_id) = 0;

    /**
     * 查询当日订单列表，支持定位串增量查询
     *
     * @param pos_str       查询定位串，第一次查询传入空，后续查询使用前一次查询返回的定位串
     * @param query_num     查询的数量，最大支持500个
     * @param request_id    请求序列号，用于匹配响应，由用户自定义，非0
     * @param query_flag    查询标识，默认是0表示查全部委托，1表示查可撤单委托，2表示仅查非撤单委托，
                            参考OrderQueryFlag定义
     * @param market        市场，默认是查上海和深圳市场的委托，查询港股通委托需传HK，
     *                      深港通传SZHK，沪港通传SHHK，传SH或SZ是查上海或深圳的委托，大小写不敏感
     *
     * @return              成功返回0，失败返回错误码，通过GetApiLastError获取错误信息
     */
    virtual int QueryOrders(const char* pos_str, int query_num, int request_id,
                            int query_flag = 0, const char* market = NULL) = 0;

    /**
     * 查询当日单个订单成交列表
     *
     * @param order_id      后台系统生成的订单id
     * @param request_id    请求序列号，用于匹配响应，由用户自定义，非0
     * @param market        市场，默认是查上海和深圳市场的委托，查询港股通委托需传HK，
     *                      深港通传SZHK，沪港通传SHHK，传SH或SZ是查上海或深圳的委托，大小写不敏感
     *
     * @return              成功返回0，失败返回错误码，通过GetApiLastError获取错误信息
     */
    virtual int QueryTradeByOrderId(const char* order_id, int request_id,
                                    const char* market = NULL) = 0;

    /**
     * 查当日指定标的成交列表
     *
     * @param symbol        标的代码，例如SH.600000
     * @param request_id    请求序列号，用于匹配响应，由用户自定义，非0
     *
     * @return              成功返回0，失败返回错误码，通过GetApiLastError获取错误信息
     */
    virtual int QueryTradeByCode(const char* symbol, int request_id) = 0;

    /**
     * 查询当日成交列表，支持定位串增量查询
     * 
     * @param pos_str       查询定位串，第一次查询传入空，后续查询使用前一次查询返回的定位串
     * @param query_num     查询的数量，最大支持500个
     * @param request_id    请求序列号，用于匹配响应，由用户自定义，非0
     * @param market        市场，默认是查上海和深圳市场的成交，查询港股通成交需传HK，
     *                      深港通传SZHK，沪港通传SHHK，传SH或SZ是查上海或深圳的成交，大小写不敏感
     * @param filter_etf    是否过滤掉ETF申赎及成分股的成交数据，不返回
     *
     * @return              成功返回0，失败返回错误码，通过GetApiLastError获取错误信息
     */
    virtual int QueryTrades(const char* pos_str, int query_num, int request_id,
                            const char* market = NULL,
                            bool filter_etf = false) = 0;

    /**
     * 查询当日ETF申赎及成分股成交列表，支持定位串增量查询，仅君睿柜台需要
     * 
     * @param pos_str       查询定位串，第一次查询传入空，后续查询使用前一次查询返回的定位串
     * @param query_num     查询的数量，最大支持500个
     * @param request_id    请求序列号，用于匹配响应，由用户自定义，非0
     * @param market        市场，默认是查上海和深圳市场的成交，大小写不敏感
     *
     * @return              成功返回0，失败返回错误码，通过GetApiLastError获取错误信息
     */
    virtual int QueryETFTrades(const char* pos_str, int query_num,
                               int request_id, const char* market = NULL) = 0;

    /**
     * 查当日指定标的持仓
     *
     * @param symbol        标的代码，例如SH.600000
     * @param request_id    请求序列号，用于匹配响应，由用户自定义，非0
     *
     * @return              成功返回0，失败返回错误码，通过GetApiLastError获取错误信息
     */
    virtual int QueryPosition(const char* symbol, int request_id) = 0;

    /**
     * 查询当日账户持仓列表，支持定位串增量查询
     *
     * @param pos_str       查询定位串，第一次查询传入空，后续查询使用前一次查询返回的定位串
     * @param query_num     查询的数量，最大支持500个
     * @param request_id    请求序列号，用于匹配响应，由用户自定义，非0
     * @param market        市场，君睿柜台一户两地时使用，查对应市场的持仓，
     *                      传SH或SZ是查上海或深圳的持仓，大小写不敏感
     *
     * @return              成功返回0，失败返回错误码，通过GetApiLastError获取错误信息
     */
    virtual int QueryPositions(const char* pos_str, int query_num,
                               int request_id, const char* market = NULL) = 0;

    /**
     * 查询当日账户资产详情
     * 
     * @param request_id    请求序列号，用于匹配响应，由用户自定义，非0
     * @param market        市场，君睿柜台一户两地时使用，查对应市场的资金，
     *                      传SH或SZ是查上海或深圳的资金，大小写不敏感，默认查上海的资金
     *
     * @return              成功返回0，失败返回错误码，通过GetApiLastError获取错误信息
     */
    virtual int QueryCash(int request_id, const char* market = NULL) = 0;

    /**
     * 查集中交易系统可用资金
     *
     * @param request_id    请求序列号，用于匹配响应，由用户自定义，非0
     *
     * @return              成功返回0，失败返回错误码，通过GetApiLastError获取错误信息
     */
    virtual int QueryJZJYAvailFund(int request_id) = 0;

    /**
     * 针对同一个资金账号在集中交易柜台与快速柜台之间资金转入转出
     *
     * @param transfer_side     划转方向，请参考TransferFundSide
     * @param transfer_value    划转金额，扩大一万倍，币种人民币
     * @param request_id        请求序列号，用于匹配响应，由用户自定义，非0
     * @param market            市场，君睿柜台一户两地时使用，
     *                          传SH或SZ是集中柜台与快速柜台上海或深圳之间资金转入转出，大小写不敏感
     *
     * @return                  成功返回0，失败返回错误码，通过GetApiLastError获取错误信息
     */
    virtual int TransferFundInAndOut(int transfer_side, int64_t transfer_value,
                                     int request_id,
                                     const char* market = NULL) = 0;

    /**
     * 针对同一个资金账号，一户两地之间资金划转，仅君睿柜台支持
     *
     * @param fund_out_market   资金转出的市场，传SH或SZ
     * @param fund_in_market    资金转入的市场，传SH或SZ
     * @param transfer_value    划转金额，扩大一万倍，币种人民币
     * @param request_id        请求序列号，用于匹配响应，由用户自定义，非0
     *
     * @return                  成功返回0，失败返回错误码，通过GetApiLastError获取错误信息
     */
    virtual int TransferFundBetweenSecuid(const char* fund_out_market,
                                          const char* fund_in_market,
                                          int64_t transfer_value,
                                          int request_id) = 0;

    /**
     * 查询ETF基本信息列表，只返回可申赎的ETF列表
     * 
     * @param request_id    请求序列号，用于匹配响应，由用户自定义，非0
     * 
     * @return              成功返回0，失败返回错误码，通过GetApiLastError获取错误信息
     */
    virtual int QueryETFs(int request_id) = 0;

    /**
     * 查询一个ETF股票篮子信息
     * 
     * @param first_symbol  ETF的一级市场代码，格式为市场.证券ID或市场.合约ID
     * @param request_id    请求序列号，用于匹配响应，由用户自定义，非0
     * 
     * @return              成功返回0，失败返回错误码，通过GetApiLastError获取错误信息
     */
    virtual int QueryETFStocks(const char* first_symbol, int request_id) = 0;

    /**
     * 查询最大可委托数量
     *
     * @param symbol        交易标的，格式为市场.证券ID或市场.合约ID
     * @param order_type    订单类型，参考OrderType定义
     * @param side          买卖方向，参考OrderSide定义
     * @param price         订单委托价，限价单使用，扩大一万倍，市价填写0
     * @param request_id    请求序列号，用于匹配响应，由用户自定义，非0
     *
     * @return              成功返回0，失败返回错误码，通过GetApiLastError获取错误信息
     */
    virtual int QueryMaxOrderQty(const char* symbol, int16_t order_type,
                                 int16_t side, int64_t price,
                                 int request_id) = 0;

    /**
     * 查询新股可申购额度
     *
     * @param request_id    请求序列号，用于匹配响应，由用户自定义，非0
     *
     * @return              成功返回0，失败返回错误码，通过GetApiLastError获取错误信息
     */
    virtual int QueryIPOMaxPurchase(int request_id) = 0;

    /**
     * 查询新股新债
     * 
     * @param request_id    请求序列号，用于匹配响应，由用户自定义，非0
     * @param query_flag    查询标志，1：查询新股，2：查询新债，定义请参考IPOQueryFlag
     *
     * @return              成功返回0，失败返回错误码，通过GetApiLastError获取错误信息
     */
    virtual int QueryIPOStock(int request_id, int query_flag = 1) = 0;

    /**
     * 查询配号，支持定位串增量查询
     *
     * @param start_date    开始日期，如20190415
     * @param end_date      结束日期，如20190418
     * @param pos_str       查询定位串，第一次查询传入空，后续查询使用前一次查询返回的定位串
     * @param query_num     查询的数量，最大支持500个
     * @param request_id    请求序列号，用于匹配响应，由用户自定义，非0
     *
     * @return              成功返回0，失败返回错误码，通过GetApiLastError获取错误信息
     */
    virtual int QueryIPODistribution(int start_date, int end_date,
                                     const char* pos_str, int query_num,
                                     int request_id) = 0;

    /**
     * 查询中签，支持定位串增量查询
     *
     * @param start_date    开始日期，如20190415
     * @param end_date      结束日期，如20190418
     * @param pos_str       查询定位串，第一次查询传入空，后续查询使用前一次查询返回的定位串
     * @param query_num     查询的数量，最大支持500个
     * @param request_id    请求序列号，用于匹配响应，由用户自定义，非0
     *
     * @return              成功返回0，失败返回错误码，通过GetApiLastError获取错误信息
     */
    virtual int QueryIPOLottery(int start_date, int end_date,
                                const char* pos_str, int query_num,
                                int request_id) = 0;

    /**
    * 查询证券信息
    *
    * @param request_id    请求序列号，用于匹配响应，由用户自定义，非0
    * @param symbol        合约代码，格式为市场.证券ID或市场.合约ID, 默认查询所有
    *
    * @return              成功返回0，失败返回错误码，通过GetApiLastError获取错误信息
    */
    virtual int QuerySecurityBaseInfo(int request_id,
                                      const char* symbol = NULL) = 0;

    /**
     * 担保品转入转出
     * 
     * @param req           担保品划转请求对象
     * @param request_id    请求序列号，用于匹配响应，由用户自定义，非0
     * 
     * @return              成功返回0，失败返回错误码，通过GetApiLastError获取错误信息
     */
    virtual int CreditMortgageInOut(CreditMortgageInOutReq* req,
                                    int request_id) = 0;

    /**
     * 现券还券
     * 
     * @param req           现券还券请求对象
     * @param request_id    请求序列号，用于匹配响应，由用户自定义，非0
     * 
     * @return              成功返回0，失败返回错误码，通过GetApiLastError获取错误信息
     */
    virtual int CreditStockBack(CreditStockBackReq* req, int request_id) = 0;

    /**
     * 直接还款
     * 
     * @param back_amt      还款金额,扩大一万倍
     * @param request_id    请求序列号，用于匹配响应，由用户自定义，非0
     * 
     * @return              成功返回0，失败返回错误码，通过GetApiLastError获取错误信息
     */
    virtual int CreditPayBack(int64_t back_amt, int request_id) = 0;

    /**
     * 指定合约直接还款
     *
     * @param order_id      指定合约的委托号
     * @param order_date    指定合约的发生日期(委托日期)
     * @param back_amt      指定合约的还款金额，扩大一万倍
     * @param request_id    请求序列号，用于匹配响应，由用户自定义，非0
     *
     * @return              成功返回0，失败返回错误码，通过GetApiLastError获取错误信息
     */
    virtual int CreditPayBackByOrder(const char* order_id, int order_date,
                                     int64_t back_amt, int request_id) = 0;

    /**
     * 查询信用标的券，支持定位串增量查询
     *
     * @param pos_str       查询定位串，第一次查询传入空，后续查询使用前一次查询返回的定位串
     * @param query_num     查询的数量
     * @param request_id    请求序列号，用于匹配响应，由用户自定义，非0
     *
     * @return              成功返回0，失败返回错误码，通过GetApiLastError获取错误信息
     */
    virtual int QueryCreditStock(const char* pos_str, int query_num,
                                 int request_id) = 0;

    /**
     * 查询担保品券，支持定位串增量查询
     *
     * @param pos_str       查询定位串，第一次查询传入空，后续查询使用前一次查询返回的定位串
     * @param query_num     查询的数量
     * @param request_id    请求序列号，用于匹配响应，由用户自定义，非0
     *
     * @return              成功返回0，失败返回错误码，通过GetApiLastError获取错误信息
     */
    virtual int QueryCreditMortgageHold(const char* pos_str, int query_num,
                                        int request_id) = 0;

    /**
     * 查询信用资产
     * 
     * @param request_id    请求序列号，用于匹配响应，由用户自定义，非0
     *
     * @return              成功返回0，失败返回错误码，通过GetApiLastError获取错误信息
     */
    virtual int QueryCreditAssets(int request_id) = 0;

    /**
     * 查询信用融资合约，支持定位串增量查询
     *
     * @param pos_str       查询定位串，第一次查询传入空，后续查询使用前一次查询返回的定位串
     * @param query_num     查询的数量
     * @param request_id    请求序列号，用于匹配响应，由用户自定义，非0
     *
     * @return              成功返回0，失败返回错误码，通过GetApiLastError获取错误信息
     */
    virtual int QueryCreditFinance(const char* pos_str, int query_num,
                                   int request_id) = 0;

    /**
     * 查询信用融券合约，支持定位串增量查询
     *
     * @param pos_str       查询定位串，第一次查询传入空，后续查询使用前一次查询返回的定位串
     * @param query_num     查询的数量
     * @param request_id    请求序列号，用于匹配响应，由用户自定义，非0
     *
     * @return              成功返回0，失败返回错误码，通过GetApiLastError获取错误信息
     */
    virtual int QueryCreditShortsell(const char* pos_str, int query_num,
                                     int request_id) = 0;

    /**
     * 查询信用融资负债金额
     * 
     * @param request_id    请求序列号，用于匹配响应，由用户自定义，非0
     *
     * @return              成功返回0，失败返回错误码，通过GetApiLastError获取错误信息
     */
    virtual int QueryCreditRepayAmount(int request_id) = 0;

    /**
     * 查询信用融券负债数量
     *
     * @param market        市场，如"SZ SH"，默认查所有市场
     * @param code          证券代码，如"600000"，默认查全部
     * @param request_id    请求序列号，用于匹配响应，由用户自定义，非0
     *
     * @return              成功返回0，失败返回错误码，通过GetApiLastError获取错误信息
     */
    virtual int QueryCreditRepayStock(const char* market, const char* code,
                                      int request_id) = 0;

    /**
     * 查询可融券卖出数量，即查询锁券的证券总数量和可用数量
     *
     * @param market        市场，如"SZ SH"，默认查所有市场
     * @param code          证券代码，如"600000"，默认查全部
     * @param request_id    请求序列号，用于匹配响应，由用户自定义，非0
     *
     * @return              成功返回0，失败返回错误码，通过GetApiLastError获取错误信息
     */
    virtual int QueryCreditSecuritySellQty(const char* market, const char* code,
                                           int request_id) = 0;

    /**
     * 查询账户账户交易权限
     *
     * @param market        市场，如"SZ SH"
     * @param secuid_right  权限类型，如创业板，参考SecuidRight定义
     * @param request_id    请求序列号，用于匹配响应，由用户自定义，非0
     *
     * @return              成功返回0，失败返回错误码，通过GetApiLastError获取错误信息
     */
    virtual int QuerySecuidRight(const char* market, int16_t secuid_right,
                                 int request_id) = 0;

    // 沪港通、深港通特有接口
    /**
     * 查询沪港通参考汇率
     *
     * @param market        市场，深港通传SZHK，沪港通传SHHK，大小写不敏感
     * @param request_id    请求序列号，用于匹配响应，由用户自定义，非0
     *
     * @return              成功返回0，失败返回错误码，通过GetApiLastError获取错误信息
     */
    virtual int QueryHKRate(const char* market, int request_id) = 0;

    /**
     * 查询沪港通标的券
     *
     * @param market        市场，深港通传SZHK，沪港通传SHHK，大小写不敏感
     * @param request_id    请求序列号，用于匹配响应，由用户自定义，非0
     * @return              成功返回0，失败返回错误码，通过GetApiLastError获取错误信息
     */
    virtual int QueryHKStock(const char* market, int request_id) = 0;

    /**
     * 查询沪港通辅资金表资产
     *
     * @param request_id    请求序列号，用于匹配响应，由用户自定义，非0
     *
     * @return              成功返回0，失败返回错误码，通过GetApiLastError获取错误信息
     */
    virtual int QueryHKFund(int request_id) = 0;

    /**
     * 查询沪港通最小价差
     *
     * @param market        市场，深港通传SZHK，沪港通传SHHK，大小写不敏感
     * @param request_id    请求序列号，用于匹配响应，由用户自定义，非0
     * @return              成功返回0，失败返回错误码，通过GetApiLastError获取错误信息
     */
    virtual int QueryHKMinPriceUnit(const char* market, int request_id) = 0;

    /**
     * 查询沪港通交易日历，查询结果包括起始日期
     *
     * @param start_date    开始日期，如20190415
     * @param end_date      结束日期，如20190418
     * @param request_id    请求序列号，用于匹配响应，由用户自定义，非0
     *
     * @return              成功返回0，失败返回错误码，通过GetApiLastError获取错误信息
     */
    virtual int QueryHKTradeCalendar(int start_date, int end_date,
                                     int request_id) = 0;

    /**
     * 查询锁券明细信息请求
     *
     * @param begin_date    开始日期，如20190415
     * @param end_date      结束日期，如20190418   
     * @param request_id    请求序列号，用于匹配响应，由用户自定义，非0
     * @param market        市场，可选填
     * @param code          代码，可选填
     *
     * @return              成功返回0，失败返回错误码，通过GetApiLastError获取错误信息
     */
    virtual int QueryLockSecurityDetail(int begin_date, int end_date,
                                        int request_id,
                                        const char* market = NULL,
                                        const char* code = NULL) = 0;

    /**
     * 锁券展期申请
     *
     * @param req           锁券展期请求对象
     * @param request_id    请求序列号，用于匹配响应，由用户自定义，非0
     *
     * @return              成功返回0，失败返回错误码，通过GetApiLastError获取错误信息
     */
    virtual int ExtendLockSecurity(ExtendLockSecurityReq* req,
                                   int request_id) = 0;

    /**
     * 查询锁券展期申请请求
     *
     * @param begin_date    开始日期，如20190415
     * @param end_date      结束日期，如20190418
     * @param request_id    请求序列号，用于匹配响应，由用户自定义，非0
     *
     * @return              成功返回0，失败返回错误码，通过GetApiLastError获取错误信息
     */
    virtual int QueryLockSecurityExtension(int begin_date, int end_date,
                                           int request_id) = 0;

    /**
     * 撤销锁券展期申请请求
     *
     * @param apply_date    申请日期，如20190415
     * @param apply_sno     申请序号
     * @param request_id    请求序列号，用于匹配响应，由用户自定义，非0
     *
     * @return              成功返回0，失败返回错误码，通过GetApiLastError获取错误信息
     */
    virtual int CancelExtendLockSecurity(int apply_date, const char* apply_sno,
                                         int request_id) = 0;

    /**
     * 查询极速柜台与集中交易之间的资金划转流水，仅支持顶点现货
     *
     * @param request_id    请求序列号，用于匹配响应，由用户自定义，非0
     *
     * @return              成功返回0，失败返回错误码，通过GetApiLastError获取错误信息
     */
    virtual int QueryTransferFundHistory(int request_id) = 0;

   protected:
    virtual ~TraderApi(){};
};

}  // namespace HFT

#endif  // _HFT_TRADER_API_H_
