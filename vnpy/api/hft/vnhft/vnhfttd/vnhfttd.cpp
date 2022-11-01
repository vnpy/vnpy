// vnctpmd.cpp : 定义 DLL 应用程序的导出函数。
//

#include "vnhfttd.h"


///-------------------------------------------------------------------------------------
///C++的回调函数将数据保存到队列中
///-------------------------------------------------------------------------------------

void TdApi::OnDisconnect()
{
	gil_scoped_acquire acquire;
	this->onDisconnect();
};

void TdApi::OnError(ErrorInfo* error_info, int request_id)
{
	gil_scoped_acquire acquire;
	dict error;
	{
		error["err_code"] = error_info->err_code;
		error["err_msg"] = toUtf(error_info->err_msg);
	}
	this->onError(error, request_id);
};

void TdApi::OnRiskNotify(RiskNotify* risk_notify)
{
	gil_scoped_acquire acquire;
	dict data;
	{
		data["secuid"] = toUtf(risk_notify->secuid);
		data["alarm_score"] = toUtf(risk_notify->alarm_score);
		data["alarm_status"] = toUtf(risk_notify->alarm_status);
		data["alarm_rule"] = toUtf(risk_notify->alarm_rule);
		data["alarm_time"] = toUtf(risk_notify->alarm_time);
		data["alarm_msg"] = toUtf(risk_notify->alarm_msg);
	}
	this->onRiskNotify(data);
};

void TdApi::OnLogin(LoginRsp* rsp, ErrorInfo* error_info)
{
	gil_scoped_acquire acquire;
	dict data;
	{
		data["account_id"] = toUtf(rsp->account_id);
		data["account_type"] = rsp->account_type;
		data["cust_orgid"] = toUtf(rsp->cust_orgid);
		data["cust_branchid"] = toUtf(rsp->cust_branchid);
		data["cust_id"] = toUtf(rsp->cust_id);
		data["cust_name"] = toUtf(rsp->cust_name);
		data["market"] = toUtf(rsp->secuid_array->market);
		data["secuid"] = toUtf(rsp->secuid_array->secuid);
		data["bank_code"] = toUtf(rsp->secuid_array->bank_code);
		data["cif_account"] = toUtf(rsp->cif_account);
	}
	dict error;
	{
		error["err_code"] = error_info->err_code;
		error["err_msg"] = toUtf(error_info->err_msg);
	}
	this->onLogin(data, error);
};

void TdApi::OnTradeReport(TradeDetail* trade_detail)
{
	gil_scoped_acquire acquire;
	dict data;
	{
		data["account_id"] = toUtf(trade_detail->account_id);
		data["account_type"] = trade_detail->account_type;
		data["order_id"] = toUtf(trade_detail->order_id);
		data["cl_order_id"] = toUtf(trade_detail->cl_order_id);
		data["symbol"] = toUtf(trade_detail->symbol);
		data["order_type"] = trade_detail->order_type;
		data["side"] = trade_detail->side;
		data["report_type"] = trade_detail->report_type;
		data["report_no"] = toUtf(trade_detail->report_no);
		data["volume"] = trade_detail->volume;
		data["price"] = trade_detail->price;
		data["turnover"] = trade_detail->turnover;
		data["trade_date"] = trade_detail->trade_date;
		data["trade_time"] = trade_detail->trade_time;
		data["err_code"] = trade_detail->err_code;
		data["err_msg"] = toUtf(trade_detail->err_msg);
		data["secuid"] = toUtf(trade_detail->secuid);
		data["name"] = toUtf(trade_detail->name);
	}
	this->onTradeReport(data);
};

void TdApi::OnOrderStatus(OrderDetail* order_detail)
{
	gil_scoped_acquire acquire;
	dict data;
	{
		data["account_id"] = toUtf(order_detail->account_id);
		data["account_type"] = order_detail->account_type;
		data["order_id"] = toUtf(order_detail->order_id);
		data["cl_order_id"] = toUtf(order_detail->cl_order_id);
		data["orig_order_id"] = toUtf(order_detail->orig_order_id);
		data["symbol"] = toUtf(order_detail->symbol);
		data["order_status"] = order_detail->order_status;
		data["order_type"] = order_detail->order_type;
		data["side"] = order_detail->side;
		data["volume"] = order_detail->volume;
		data["price"] = order_detail->price;
		data["filled_volume"] = order_detail->filled_volume;
		data["filled_turnover"] = order_detail->filled_turnover;
		data["filled_price"] = order_detail->filled_price;
		data["cancel_volume"] = order_detail->cancel_volume;
		data["cancel_flag"] = order_detail->cancel_flag;
		data["order_date"] = order_detail->order_date;
		data["order_time"] = order_detail->order_time;
		data["err_code"] = order_detail->err_code;
		data["err_msg"] = toUtf(order_detail->err_msg);
		data["secuid"] = toUtf(order_detail->secuid);
		data["name"] = toUtf(order_detail->name);
		data["freeze_amount"] = order_detail->freeze_amount;
	}
	this->onOrderStatus(data);
};

void TdApi::OnOrderRsp(OrderRsp* order_rsp, ErrorInfo* error_info, int request_id, bool is_last)
{
	gil_scoped_acquire acquire;
	dict data;
	{
		data["account_id"] = toUtf(order_rsp->account_id);
		data["account_type"] = order_rsp->account_type;
		data["order_date"] = order_rsp->order_date;
		data["order_id"] = toUtf(order_rsp->order_id);
		data["cl_order_id"] = toUtf(order_rsp->cl_order_id);
	}
	dict error;
	{
		error["err_code"] = error_info->err_code;
		error["err_msg"] = toUtf(error_info->err_msg);
	}
	this->onOrderRsp(data, error, request_id, is_last);
};

void TdApi::OnCancelRsp(CancelRsp* cancel_rsp, ErrorInfo* error_info, int request_id, bool is_last)
{
	gil_scoped_acquire acquire;
	dict data;
	{
		data["account_id"] = toUtf(cancel_rsp->account_id);
		data["account_type"] = cancel_rsp->account_type;
		data["order_id"] = toUtf(cancel_rsp->order_id);
		data["cl_order_id"] = toUtf(cancel_rsp->cl_order_id);
		data["cl_cancel_id"] = toUtf(cancel_rsp->cl_cancel_id);
	}
	dict error;
	{
		error["err_code"] = error_info->err_code;
		error["err_msg"] = toUtf(error_info->err_msg);
	}
	this->onCancelRsp(data, error, request_id, is_last);
};

void TdApi::OnQueryOrderRsp(OrderDetail* order_detail, ErrorInfo* error_info, int request_id, bool is_last, const char* pos_str)
{
	gil_scoped_acquire acquire;
	dict data;
	{
		data["account_id"] = toUtf(order_detail->account_id);
		data["account_type"] = order_detail->account_type;
		data["order_id"] = toUtf(order_detail->order_id);
		data["cl_order_id"] = toUtf(order_detail->cl_order_id);
		data["orig_order_id"] = toUtf(order_detail->orig_order_id);
		data["symbol"] = toUtf(order_detail->symbol);
		data["order_status"] = order_detail->order_status;
		data["order_type"] = order_detail->order_type;
		data["side"] = order_detail->side;
		data["volume"] = order_detail->volume;
		data["price"] = order_detail->price;
		data["filled_volume"] = order_detail->filled_volume;
		data["filled_turnover"] = order_detail->filled_turnover;
		data["filled_price"] = order_detail->filled_price;
		data["cancel_volume"] = order_detail->cancel_volume;
		data["cancel_flag"] = order_detail->cancel_flag;
		data["order_date"] = order_detail->order_date;
		data["order_time"] = order_detail->order_time;
		data["err_code"] = order_detail->err_code;
		data["err_msg"] = toUtf(order_detail->err_msg);
		data["secuid"] = toUtf(order_detail->secuid);
		data["name"] = toUtf(order_detail->name);
		data["freeze_amount"] = order_detail->freeze_amount;
	}
	dict error;
	{
		error["err_code"] = error_info->err_code;
		error["err_msg"] = toUtf(error_info->err_msg);
	}
	this->onQueryOrderRsp(data, error, request_id, is_last, pos_str);
};

void TdApi::OnQueryTradeRsp(TradeDetail* trade_detail, ErrorInfo* error_info, int request_id, bool is_last, const char* pos_str)
{
	gil_scoped_acquire acquire;
	dict data;
	{
		data["account_id"] = toUtf(trade_detail->account_id);
		data["account_type"] = trade_detail->account_type;
		data["order_id"] = toUtf(trade_detail->order_id);
		data["cl_order_id"] = toUtf(trade_detail->cl_order_id);
		data["symbol"] = toUtf(trade_detail->symbol);
		data["order_type"] = trade_detail->order_type;
		data["side"] = trade_detail->side;
		data["report_type"] = trade_detail->report_type;
		data["report_no"] = toUtf(trade_detail->report_no);
		data["volume"] = trade_detail->volume;
		data["price"] = trade_detail->price;
		data["turnover"] = trade_detail->turnover;
		data["trade_date"] = trade_detail->trade_date;
		data["trade_time"] = trade_detail->trade_time;
		data["err_code"] = trade_detail->err_code;
		data["err_msg"] = toUtf(trade_detail->err_msg);
		data["secuid"] = toUtf(trade_detail->secuid);
		data["name"] = toUtf(trade_detail->name);
	}
	dict error;
	{
		error["err_code"] = error_info->err_code;
		error["err_msg"] = toUtf(error_info->err_msg);
	}
	this->onQueryTradeRsp(data, error, request_id, is_last, pos_str);
};

void TdApi::OnQueryPositionRsp(PositionDetail* position_detail, ErrorInfo* error_info, int request_id, bool is_last, const char* pos_str)
{
	gil_scoped_acquire acquire;
	dict data;
	{
		data["account_id"] = toUtf(position_detail->account_id);
		data["account_type"] = position_detail->account_type;
		data["symbol"] = toUtf(position_detail->symbol);
		data["side"] = position_detail->side;
		data["volume"] = position_detail->volume;
		data["avail_volume"] = position_detail->avail_volume;
		data["init_volume"] = position_detail->init_volume;
		data["market_value"] = position_detail->market_value;
		data["today_buy_volume"] = position_detail->today_buy_volume;
		data["today_sell_volume"] = position_detail->today_sell_volume;
		data["secuid"] = toUtf(position_detail->secuid);
		data["cost_price"] = position_detail->cost_price;
		data["buy_cost"] = position_detail->buy_cost;
		data["last_price"] = position_detail->last_price;
		data["income"] = position_detail->income;
		data["total_income"] = position_detail->total_income;
		data["profit_cost"] = position_detail->profit_cost;
		data["today_avail_pr_volume"] = position_detail->today_avail_pr_volume;
		data["market"] = position_detail->market;
		data["security_type"] = position_detail->security_type;
		data["freeze_volume"] = position_detail->freeze_volume;
		data["name"] = toUtf(position_detail->name);
	}
	dict error;
	{
		error["err_code"] = error_info->err_code;
		error["err_msg"] = toUtf(error_info->err_msg);
	}
	this->onQueryPositionRsp(data, error, request_id, is_last, pos_str);
};

void TdApi::OnQueryCashRsp(CashDetail* cash_detail, ErrorInfo* error_info, int request_id)
{
	gil_scoped_acquire acquire;
	dict data;
	{
		data["account_id"] = toUtf(cash_detail->account_id);
		data["account_type"] = cash_detail->account_type;
		data["currency_type"] = cash_detail->currency_type;
		data["total_amount"] = cash_detail->total_amount;
		data["avail_amount"] = cash_detail->avail_amount;
		data["total_asset"] = cash_detail->total_asset;
		data["market_value"] = cash_detail->market_value;
	}
	dict error;
	{
		error["err_code"] = error_info->err_code;
		error["err_msg"] = toUtf(error_info->err_msg);
	}
	this->onQueryCashRsp(data, error, request_id);
};

void TdApi::OnQueryJZJYAvailFundRsp(int64_t avail_balance, ErrorInfo* error_info, int request_id)
{
	gil_scoped_acquire acquire;
	dict error;
	{
		error["err_code"] = error_info->err_code;
		error["err_msg"] = toUtf(error_info->err_msg);
	}
	this->onQueryJZJYAvailFundRsp(avail_balance, error, request_id);
};

void TdApi::OnTransferFundInAndOutRsp(int64_t transfer_value, ErrorInfo* error_info, int request_id)
{
	gil_scoped_acquire acquire;
	dict error;
	{
		error["err_code"] = error_info->err_code;
		error["err_msg"] = toUtf(error_info->err_msg);
	}
	this->onTransferFundInAndOutRsp(transfer_value, error, request_id);
};

void TdApi::OnTransferFundBetweenSecuidRsp(int64_t transfer_value, ErrorInfo* error_info, int request_id)
{
	gil_scoped_acquire acquire;
	dict error;
	{
		error["err_code"] = error_info->err_code;
		error["err_msg"] = toUtf(error_info->err_msg);
	}
	this->onTransferFundBetweenSecuidRsp(transfer_value, error, request_id);
};

void TdApi::OnQueryETFRsp(ETFDetail* etf_detail, ErrorInfo* error_info, int request_id, bool is_last)
{
	gil_scoped_acquire acquire;
	dict data;
	{
		data["name"] = toUtf(etf_detail->name);
		data["first_symbol"] = toUtf(etf_detail->first_symbol);
		data["second_symbol"] = toUtf(etf_detail->second_symbol);
		data["trade_unit"] = etf_detail->trade_unit;
		data["cash_component"] = etf_detail->cash_component;
		data["max_cash_ratio"] = etf_detail->max_cash_ratio;
		data["trade_state"] = etf_detail->trade_state;
		data["record_num"] = etf_detail->record_num;
		data["trade_day"] = etf_detail->trade_day;
		data["pre_trade_day"] = etf_detail->pre_trade_day;
		data["nav_percu"] = etf_detail->nav_percu;
		data["nav"] = etf_detail->nav;
		data["creation_limituser"] = etf_detail->creation_limituser;
		data["redemption_limituser"] = etf_detail->redemption_limituser;
		data["net_creation_limituser"] = etf_detail->net_creation_limituser;
		data["net_redemption_limituser"] = etf_detail->net_redemption_limituser;
		data["creation_limit"] = etf_detail->creation_limit;
		data["redemption_limit"] = etf_detail->redemption_limit;
		data["net_creation_limit"] = etf_detail->net_creation_limit;
		data["net_redemption_limit"] = etf_detail->net_redemption_limit;
	}
	dict error;
	{
		error["err_code"] = error_info->err_code;
		error["err_msg"] = toUtf(error_info->err_msg);
	}
	this->onQueryETFRsp(data, error, request_id, is_last);
};

void TdApi::OnQueryETFStockRsp(ETFStockDetail* etf_stock_detail, ErrorInfo* error_info, int request_id, bool is_last)
{
	gil_scoped_acquire acquire;
	dict data;
	{
		data["first_symbol"] = toUtf(etf_stock_detail->first_symbol);
		data["name"] = toUtf(etf_stock_detail->name);
		data["symbol"] = toUtf(etf_stock_detail->symbol);
		data["volume"] = etf_stock_detail->volume;
		data["replace_flag"] = etf_stock_detail->replace_flag;
		data["over_price_rate"] = etf_stock_detail->over_price_rate;
		data["replace_amt"] = etf_stock_detail->replace_amt;
	}
	dict error;
	{
		error["err_code"] = error_info->err_code;
		error["err_msg"] = toUtf(error_info->err_msg);
	}
	this->onQueryETFStockRsp(data, error, request_id, is_last);
};

void TdApi::OnQueryMaxOrderQtyRsp(MaxOrderQtyDetail* detail, ErrorInfo* error_info, int request_id)
{
	gil_scoped_acquire acquire;
	dict data;
	{
		data["account_id"] = toUtf(detail->account_id);
		data["account_type"] = detail->account_type;
		data["max_qty"] = detail->max_qty;
		data["actual_max_qty"] = detail->actual_max_qty;
	}
	dict error;
	{
		error["err_code"] = error_info->err_code;
		error["err_msg"] = toUtf(error_info->err_msg);
	}
	this->onQueryMaxOrderQtyRsp(data, error, request_id);
};

void TdApi::OnQueryIPOMaxPurchaseRsp(IPOMaxPurchaseDetail* detail, ErrorInfo* error_info, int request_id, bool is_last)
{
	gil_scoped_acquire acquire;
	dict data;
	{
		data["account_id"] = toUtf(detail->account_id);
		data["account_type"] = detail->account_type;
		data["market"] = toUtf(detail->market);
		data["max_qty"] = detail->max_qty;
		data["stib_max_qty"] = detail->stib_max_qty;
	}
	dict error;
	{
		error["err_code"] = error_info->err_code;
		error["err_msg"] = toUtf(error_info->err_msg);
	}
	this->onQueryIPOMaxPurchaseRsp(data, error, request_id, is_last);
};

void TdApi::OnQueryIPOStockRsp(IPOStockDetail* detail, ErrorInfo* error_info, int request_id, bool is_last)
{
	gil_scoped_acquire acquire;
	dict data;
	{
		data["symbol"] = toUtf(detail->symbol);
		data["name"] = toUtf(detail->name);
		data["currency_type"] = detail->currency_type;
		data["ipo_price"] = detail->ipo_price;
		data["max_num"] = detail->max_num;
		data["min_num"] = detail->min_num;
	}
	dict error;
	{
		error["err_code"] = error_info->err_code;
		error["err_msg"] = toUtf(error_info->err_msg);
	}
	this->onQueryIPOStockRsp(data, error, request_id, is_last);
};

void TdApi::OnQueryIPODistributionRsp(IPODistributionDetail* detail, ErrorInfo* error_info, int request_id, bool is_last, const char* pos_str)
{
	gil_scoped_acquire acquire;
	dict data;
	{
		data["account_id"] = toUtf(detail->account_id);
		data["account_type"] = detail->account_type;
		data["biz_date"] = detail->biz_date;
		data["symbol"] = toUtf(detail->symbol);
		data["name"] = toUtf(detail->name);
		data["mate_no"] = toUtf(detail->mate_no);
		data["match_qty"] = detail->match_qty;
	}
	dict error;
	{
		error["err_code"] = error_info->err_code;
		error["err_msg"] = toUtf(error_info->err_msg);
	}
	this->onQueryIPODistributionRsp(data, error, request_id, is_last, pos_str);
};

void TdApi::OnQueryIPOLotteryRsp(IPOLotteryDetail* detail, ErrorInfo* error_info, int request_id, bool is_last, const char* pos_str)
{
	gil_scoped_acquire acquire;
	dict data;
	{
		data["account_id"] = toUtf(detail->account_id);
		data["account_type"] = detail->account_type;
		data["biz_date"] = detail->biz_date;
		data["symbol"] = toUtf(detail->symbol);
		data["name"] = toUtf(detail->name);
		data["match_price"] = detail->match_price;
		data["match_qty"] = detail->match_qty;
	}
	dict error;
	{
		error["err_code"] = error_info->err_code;
		error["err_msg"] = toUtf(error_info->err_msg);
	}
	this->onQueryIPOLotteryRsp(data, error, request_id, is_last, pos_str);
};

void TdApi::OnQuerySecurityBaseInfoRsp(SecurityBaseInfo* detail, ErrorInfo* error_info, int request_id, bool is_last)
{
	gil_scoped_acquire acquire;
	dict data;
	{
		data["symbol"] = toUtf(detail->symbol);
		data["name"] = toUtf(detail->name);
		data["security_type"] = detail->security_type;
		data["security_status"] = detail->security_status;
		data["price_tick"] = detail->price_tick;
		data["limit_up"] = detail->limit_up;
		data["limit_down"] = detail->limit_down;
		data["max_qty"] = detail->max_qty;
		data["min_qty"] = detail->min_qty;
		data["buy_tick"] = detail->buy_tick;
		data["sale_tick"] = detail->sale_tick;
		data["has_price_limit"] = detail->has_price_limit;
		data["max_rise_rate"] = detail->max_rise_rate;
		data["is_registration"] = detail->is_registration;
	}
	dict error;
	{
		error["err_code"] = error_info->err_code;
		error["err_msg"] = toUtf(error_info->err_msg);
	}
	this->onQuerySecurityBaseInfoRsp(data, error, request_id, is_last);
};

void TdApi::OnCreditMortgageInOutRsp(CreditMortgageInOutRsp* rsp, ErrorInfo* error_info, int request_id)
{
	gil_scoped_acquire acquire;
	dict data;
	{
		data["account_id"] = toUtf(rsp->account_id);
		data["account_type"] = rsp->account_type;
		data["cl_order_id"] = toUtf(rsp->cl_order_id);
		data["order_id"] = toUtf(rsp->order_id);
	}
	dict error;
	{
		error["err_code"] = error_info->err_code;
		error["err_msg"] = toUtf(error_info->err_msg);
	}
	this->onCreditMortgageInOutRsp(data, error, request_id);
};

void TdApi::OnCreditStockBackRsp(CreditStockBackRsp* rsp, ErrorInfo* error_info, int request_id)
{
	gil_scoped_acquire acquire;
	dict data;
	{
		data["account_id"] = toUtf(rsp->account_id);
		data["account_type"] = rsp->account_type;
		data["cl_order_id"] = toUtf(rsp->cl_order_id);
		data["order_id"] = toUtf(rsp->order_id);
	}
	dict error;
	{
		error["err_code"] = error_info->err_code;
		error["err_msg"] = toUtf(error_info->err_msg);
	}
	this->onCreditStockBackRsp(data, error, request_id);
};

void TdApi::OnCreditPayBackRsp(CreditPayBackRsp* rsp, ErrorInfo* error_info, int request_id)
{
	gil_scoped_acquire acquire;
	dict data;
	{
		data["account_id"] = toUtf(rsp->account_id);
		data["account_type"] = rsp->account_type;
		data["real_back_amt"] = rsp->real_back_amt;
	}
	dict error;
	{
		error["err_code"] = error_info->err_code;
		error["err_msg"] = toUtf(error_info->err_msg);
	}
	this->onCreditPayBackRsp(data, error, request_id);
};

void TdApi::OnCreditPayBackByOrderRsp(CreditPayBackRsp* rsp, ErrorInfo* error_info, int request_id)
{
	gil_scoped_acquire acquire;
	dict data;
	{
		data["account_id"] = toUtf(rsp->account_id);
		data["account_type"] = rsp->account_type;
		data["real_back_amt"] = rsp->real_back_amt;
	}
	dict error;
	{
		error["err_code"] = error_info->err_code;
		error["err_msg"] = toUtf(error_info->err_msg);
	}
	this->onCreditPayBackByOrderRsp(data, error, request_id);
};

void TdApi::OnQueryCreditStockRsp(CreditStockDetail* detail, ErrorInfo* error_info, int request_id, bool is_last, const char* pos_str)
{
	gil_scoped_acquire acquire;
	dict data;
	{
		data["symbol"] = toUtf(detail->symbol);
		data["name"] = toUtf(detail->name);
		data["currency_type"] = detail->currency_type;
		data["credit_fund_ctrl"] = detail->credit_fund_ctrl;
		data["credit_stk_ctrl"] = detail->credit_stk_ctrl;
		data["margin_rate_fund"] = detail->margin_rate_fund;
		data["margin_rate_stk"] = detail->margin_rate_stk;
		data["sep_rem_qty"] = detail->sep_rem_qty;
	}
	dict error;
	{
		error["err_code"] = error_info->err_code;
		error["err_msg"] = toUtf(error_info->err_msg);
	}
	this->onQueryCreditStockRsp(data, error, request_id, is_last, pos_str);
};

void TdApi::OnQueryCreditMortgageHoldRsp(CreditMortgageHoldDetail* detail, ErrorInfo* error_info, int request_id, bool is_last, const char* pos_str)
{
	gil_scoped_acquire acquire;
	dict data;
	{
		data["account_id"] = toUtf(detail->account_id);
		data["account_type"] = detail->account_type;
		data["symbol"] = toUtf(detail->symbol);
		data["name"] = toUtf(detail->name);
		data["currency_type"] = detail->currency_type;
		data["pledge_rate"] = detail->pledge_rate;
	}
	dict error;
	{
		error["err_code"] = error_info->err_code;
		error["err_msg"] = toUtf(error_info->err_msg);
	}
	this->onQueryCreditMortgageHoldRsp(data, error, request_id, is_last, pos_str);
};

void TdApi::OnQueryCreditAssetsRsp(CreditAssetsDetail* detail, ErrorInfo* error_info, int request_id)
{
	gil_scoped_acquire acquire;
	dict data;
	{
		data["account_id"] = toUtf(detail->account_id);
		data["account_type"] = detail->account_type;
		data["currency_type"] = detail->currency_type;
		data["avail_balance"] = detail->avail_balance;
		data["fetch_balance"] = detail->fetch_balance;
		data["frozen_balance"] = detail->frozen_balance;
		data["stock_balance"] = detail->stock_balance;
		data["fund_balance"] = detail->fund_balance;
		data["asset_balance"] = detail->asset_balance;
		data["avail_margin"] = detail->avail_margin;
		data["credit_quota"] = detail->credit_quota;
		data["finance_quota"] = detail->finance_quota;
		data["shortsell_quota"] = detail->shortsell_quota;
		data["assure_ratio"] = detail->assure_ratio;
		data["total_debt"] = detail->total_debt;
		data["fund_debt"] = detail->fund_debt;
		data["stock_debt"] = detail->stock_debt;
		data["fund_interest_fee"] = detail->fund_interest_fee;
		data["stock_interest_fee"] = detail->stock_interest_fee;
		data["shortsell_total_balance"] = detail->shortsell_total_balance;
		data["shortsell_avail_balance"] = detail->shortsell_avail_balance;
		data["shortsell_frozen_balance"] = detail->shortsell_frozen_balance;
		data["enbuyback_avail_balance"] = detail->enbuyback_avail_balance;
		data["fund_margin_profit"] = detail->fund_margin_profit;
		data["stock_margin_profit"] = detail->stock_margin_profit;
		data["fund_interest"] = detail->fund_interest;
		data["stock_interest"] = detail->stock_interest;
		data["fund_margin_balance"] = detail->fund_margin_balance;
		data["stock_margin_balance"] = detail->stock_margin_balance;
		data["fund_floating_deficit"] = detail->fund_floating_deficit;
		data["stock_floating_deficit"] = detail->stock_floating_deficit;
		data["fund_margin_profit_conversion"] = detail->fund_margin_profit_conversion;
		data["stock_margin_profit_conversion"] = detail->stock_margin_profit_conversion;
	}
	dict error;
	{
		error["err_code"] = error_info->err_code;
		error["err_msg"] = toUtf(error_info->err_msg);
	}
	this->onQueryCreditAssetsRsp(data, error, request_id);
};

void TdApi::OnQueryCreditFinanceRsp(CreditFinanceDetail* detail, ErrorInfo* error_info, int request_id, bool is_last, const char* pos_str)
{
	gil_scoped_acquire acquire;
	dict data;
	{
		data["account_id"] = toUtf(detail->account_id);
		data["account_type"] = detail->account_type;
		data["symbol"] = toUtf(detail->symbol);
		data["name"] = toUtf(detail->name);
		data["order_id"] = toUtf(detail->order_id);
		data["currency_type"] = detail->currency_type;
		data["debt_status"] = detail->debt_status;
		data["occur_date"] = detail->occur_date;
		data["total_balance"] = detail->total_balance;
		data["cur_balance"] = detail->cur_balance;
		data["total_interest_fee"] = detail->total_interest_fee;
		data["cur_interest_fee"] = detail->cur_interest_fee;
		data["interest_rate"] = detail->interest_rate;
		data["repayable_balance"] = detail->repayable_balance;
		data["f_deal_bal"] = detail->f_deal_bal;
		data["f_exp_cet_intr"] = detail->f_exp_cet_intr;
		data["credit_repay_unfrz"] = detail->credit_repay_unfrz;
		data["all_fee_unfrz"] = detail->all_fee_unfrz;
		data["market"] = detail->market;
	}
	dict error;
	{
		error["err_code"] = error_info->err_code;
		error["err_msg"] = toUtf(error_info->err_msg);
	}
	this->onQueryCreditFinanceRsp(data, error, request_id, is_last, pos_str);
};

void TdApi::OnQueryCreditShortsellRsp(CreditShortsellDetail* detail, ErrorInfo* error_info, int request_id, bool is_last, const char* pos_str)
{
	gil_scoped_acquire acquire;
	dict data;
	{
		data["account_id"] = toUtf(detail->account_id);
		data["account_type"] = detail->account_type;
		data["symbol"] = toUtf(detail->symbol);
		data["name"] = toUtf(detail->name);
		data["order_id"] = toUtf(detail->order_id);
		data["currency_type"] = detail->currency_type;
		data["debt_status"] = detail->debt_status;
		data["occur_date"] = detail->occur_date;
		data["total_qty"] = detail->total_qty;
		data["cur_qty"] = detail->cur_qty;
		data["total_interest_fee"] = detail->total_interest_fee;
		data["cur_interest_fee"] = detail->cur_interest_fee;
		data["interest_rate"] = detail->interest_rate;
		data["d_stk_bal"] = detail->d_stk_bal;
		data["market"] = detail->market;
		data["all_fee_unfrz"] = detail->all_fee_unfrz;
		data["stk_repay_unfrz"] = detail->stk_repay_unfrz;
		data["end_date"] = detail->end_date;
	}
	dict error;
	{
		error["err_code"] = error_info->err_code;
		error["err_msg"] = toUtf(error_info->err_msg);
	}
	this->onQueryCreditShortsellRsp(data, error, request_id, is_last, pos_str);
};

void TdApi::OnQueryCreditRepayAmountRsp(CreditRepayAmountDetail* detail, ErrorInfo* error_info, int request_id)
{
	gil_scoped_acquire acquire;
	dict data;
	{
		data["account_id"] = toUtf(detail->account_id);
		data["account_type"] = detail->account_type;
		data["max_back_amt"] = detail->max_back_amt;
	}
	dict error;
	{
		error["err_code"] = error_info->err_code;
		error["err_msg"] = toUtf(error_info->err_msg);
	}
	this->onQueryCreditRepayAmountRsp(data, error, request_id);
};

void TdApi::OnQueryCreditRepayStockRsp(CreditRepayStockDetail* detail, ErrorInfo* error_info, int request_id, bool is_last, const char* pos_str)
{
	gil_scoped_acquire acquire;
	dict data;
	{
		data["account_id"] = toUtf(detail->account_id);
		data["account_type"] = detail->account_type;
		data["symbol"] = toUtf(detail->symbol);
		data["name"] = toUtf(detail->name);
		data["total_qty"] = detail->total_qty;
		data["max_back_qty"] = detail->max_back_qty;
		data["returned_qty"] = detail->returned_qty;
	}
	dict error;
	{
		error["err_code"] = error_info->err_code;
		error["err_msg"] = toUtf(error_info->err_msg);
	}
	this->onQueryCreditRepayStockRsp(data, error, request_id, is_last, pos_str);
};

void TdApi::OnQueryCreditSecuritySellQtyRsp(CreditSecuritySellQtyRsp* rsp, ErrorInfo* error_info, int request_id, bool is_last)
{
	gil_scoped_acquire acquire;
	dict data;
	{
		data["account_id"] = toUtf(rsp->account_id);
		data["account_type"] = rsp->account_type;
		data["symbol"] = toUtf(rsp->symbol);
		data["total_qty"] = rsp->total_qty;
		data["avail_qty"] = rsp->avail_qty;
	}
	dict error;
	{
		error["err_code"] = error_info->err_code;
		error["err_msg"] = toUtf(error_info->err_msg);
	}
	this->onQueryCreditSecuritySellQtyRsp(data, error, request_id, is_last);
};

void TdApi::OnQuerySecuidRightRsp(const char* market, int16_t secuid_right, ErrorInfo* error_info, bool sign_flag, int request_id)
{
	gil_scoped_acquire acquire;
	dict error;
	{
		error["err_code"] = error_info->err_code;
		error["err_msg"] = toUtf(error_info->err_msg);
	}
	this->onQuerySecuidRightRsp(market, secuid_right, error, sign_flag, request_id);
};

void TdApi::OnQueryHKRateRsp(HKRateDetail* detail, ErrorInfo* error_info, int request_id, bool is_last)
{
	gil_scoped_acquire acquire;
	dict data;
	{
		data["market"] = toUtf(detail->market);
		data["buy_rate"] = detail->buy_rate;
		data["sale_rate"] = detail->sale_rate;
		data["mid_rate"] = detail->mid_rate;
		data["set_rate"] = detail->set_rate;
		data["sys_date"] = detail->sys_date;
	}
	dict error;
	{
		error["err_code"] = error_info->err_code;
		error["err_msg"] = toUtf(error_info->err_msg);
	}
	this->onQueryHKRateRsp(data, error, request_id, is_last);
};

void TdApi::OnQueryHKStockRsp(HKStockDetail* detail, ErrorInfo* error_info, int request_id, bool is_last)
{
	gil_scoped_acquire acquire;
	dict data;
	{
		data["symbol"] = toUtf(detail->symbol);
		data["name"] = toUtf(detail->name);
		data["stktype"] = detail->stktype;
		data["currency_type"] = detail->currency_type;
	}
	dict error;
	{
		error["err_code"] = error_info->err_code;
		error["err_msg"] = toUtf(error_info->err_msg);
	}
	this->onQueryHKStockRsp(data, error, request_id, is_last);
};

void TdApi::OnQueryHKFundRsp(HKFundDetail* detail, ErrorInfo* error_info, int request_id)
{
	gil_scoped_acquire acquire;
	dict data;
	{
		data["account_id"] = toUtf(detail->account_id);
		data["account_type"] = detail->account_type;
		data["currency_type"] = detail->currency_type;
		data["fund_uncomeavl"] = detail->fund_uncomeavl;
		data["fund_buy"] = detail->fund_buy;
		data["fund_sale"] = detail->fund_sale;
		data["fund_uncomebuy"] = detail->fund_uncomebuy;
		data["fund_uncomesale"] = detail->fund_uncomesale;
	}
	dict error;
	{
		error["err_code"] = error_info->err_code;
		error["err_msg"] = toUtf(error_info->err_msg);
	}
	this->onQueryHKFundRsp(data, error, request_id);
};

void TdApi::OnQueryHKMinPriceUnitRsp(HKMinPriceUnitDetail* detail, ErrorInfo* error_info, int request_id, bool is_last)
{
	gil_scoped_acquire acquire;
	dict data;
	{
		data["stktype"] = detail->stktype;
		data["begin_price"] = detail->begin_price;
		data["end_price"] = detail->end_price;
		data["price_unit"] = detail->price_unit;
	}
	dict error;
	{
		error["err_code"] = error_info->err_code;
		error["err_msg"] = toUtf(error_info->err_msg);
	}
	this->onQueryHKMinPriceUnitRsp(data, error, request_id, is_last);
};

void TdApi::OnQueryHKTradeCalendarRsp(HKTradeCalendarDetail* detail, ErrorInfo* error_info, int request_id, bool is_last)
{
	gil_scoped_acquire acquire;
	dict data;
	{
		data["date"] = detail->date;
		data["business_flag"] = detail->business_flag;
		data["commit_flag"] = detail->commit_flag;
	}
	dict error;
	{
		error["err_code"] = error_info->err_code;
		error["err_msg"] = toUtf(error_info->err_msg);
	}
	this->onQueryHKTradeCalendarRsp(data, error, request_id, is_last);
};

void TdApi::OnQueryLockSecurityDetailRsp(LockSecurityDetail* detail, ErrorInfo* error_info, int request_id, bool is_last)
{
	gil_scoped_acquire acquire;
	dict data;
	{
		data["account_id"] = toUtf(detail->account_id);
		data["account_type"] = detail->account_type;
		data["sys_date"] = detail->sys_date;
		data["sno"] = toUtf(detail->sno);
		data["symbol"] = toUtf(detail->symbol);
		data["name"] = toUtf(detail->name);
		data["lock_type"] = detail->lock_type;
		data["used_fee_rate"] = detail->used_fee_rate;
		data["unused_fee_rate"] = detail->unused_fee_rate;
		data["lock_qty"] = detail->lock_qty;
		data["used_qty"] = detail->used_qty;
		data["back_qty"] = detail->back_qty;
		data["begin_date"] = detail->begin_date;
		data["back_date"] = detail->back_date;
		data["end_date"] = detail->end_date;
	}
	dict error;
	{
		error["err_code"] = error_info->err_code;
		error["err_msg"] = toUtf(error_info->err_msg);
	}
	this->onQueryLockSecurityDetailRsp(data, error, request_id, is_last);
};

void TdApi::OnExtendLockSecurityRsp(int32_t apply_sno, int32_t apply_date, ErrorInfo* error_info, int request_id)
{
	gil_scoped_acquire acquire;
	dict error;
	{
		error["err_code"] = error_info->err_code;
		error["err_msg"] = toUtf(error_info->err_msg);
	}
	this->onExtendLockSecurityRsp(apply_sno, apply_date, error, request_id);
};

void TdApi::OnQueryLockSecurityExtensionRsp(LockSecurityExtensionDetail* detail, ErrorInfo* error_info, int request_id, bool is_last)
{
	gil_scoped_acquire acquire;
	dict data;
	{
		data["account_id"] = toUtf(detail->account_id);
		data["account_type"] = detail->account_type;
		data["apply_date"] = detail->apply_date;
		data["apply_sno"] = detail->apply_sno;
		data["sys_date"] = detail->sys_date;
		data["sno"] = toUtf(detail->sno);
		data["symbol"] = toUtf(detail->symbol);
		data["name"] = toUtf(detail->name);
		data["apply_end_date"] = detail->apply_end_date;
		data["apply_delay_qty"] = detail->apply_delay_qty;
		data["approval_used_fee_rate"] = detail->approval_used_fee_rate;
		data["approval_unused_fee_rate"] = detail->approval_unused_fee_rate;
		data["approval_status"] = detail->approval_status;
		data["approval_remark"] = toUtf(detail->approval_remark);
	}
	dict error;
	{
		error["err_code"] = error_info->err_code;
		error["err_msg"] = toUtf(error_info->err_msg);
	}
	this->onQueryLockSecurityExtensionRsp(data, error, request_id, is_last);
};

void TdApi::OnCancelExtendLockSecurityRsp(int apply_date, const char* apply_sno, const char* cancel_sno, ErrorInfo* error_info, int request_id)
{
	gil_scoped_acquire acquire;
	dict error;
	{
		error["err_code"] = error_info->err_code;
		error["err_msg"] = toUtf(error_info->err_msg);
	}
	this->onCancelExtendLockSecurityRsp(apply_date, apply_sno, cancel_sno, error, request_id);
};

void TdApi::OnQueryTransferFundHistoryRsp(TransferFundDetail* detail, ErrorInfo* error_info, int request_id, bool is_last)
{
	gil_scoped_acquire acquire;
	dict data;
	{
		data["account_id"] = toUtf(detail->account_id);
		data["account_type"] = detail->account_type;
		data["serial_number"] = toUtf(detail->serial_number);
		data["transact_date"] = detail->transact_date;
		data["transact_time"] = detail->transact_time;
		data["transfer_value"] = detail->transfer_value;
		data["transfer_side"] = detail->transfer_side;
		data["transfer_status"] = detail->transfer_status;
		data["remark"] = toUtf(detail->remark);
	}
	dict error;
	{
		error["err_code"] = error_info->err_code;
		error["err_msg"] = toUtf(error_info->err_msg);
	}
	this->onQueryTransferFundHistoryRsp(data, error, request_id, is_last);
};


///-------------------------------------------------------------------------------------
///主动函数
///-------------------------------------------------------------------------------------

void TdApi::setLogConfig(string log_path)
{
	this->api->SetLogConfig(log_path.c_str(), LogLevel_Info);
}

void TdApi::createTraderApi()
{
    this->api = TraderApi::CreateTraderApi();
    this->api->RegisterSpi(this);
	this->active = true;
};

void TdApi::release()
{
    this->api->Release();
};


int TdApi::exit()
{
    this->api->RegisterSpi(NULL);
    this->api->Release();
    this->api = NULL;
    return 1;
};

string TdApi::getApiVersion()
{
	string i = this->api->GetApiVersion();
	return i;
}
int TdApi::login(string svr_ip, int svr_port, const dict &req, string terminal_info)
{
	AccountInfo myreq = AccountInfo();
	memset(&myreq, 0, sizeof(myreq));
	getString(req, "account_id", myreq.account_id);
	getInt16_t(req, "account_type", &myreq.account_type);
	getString(req, "account_pwd", myreq.account_pwd);
	getString(req, "cust_orgid", myreq.cust_orgid);
	getString(req, "cust_branchid", myreq.cust_branchid);
	getString(req, "cl_system_id", myreq.cl_system_id);
	int i = this->api->Login(svr_ip.c_str(), svr_port, &myreq, terminal_info.c_str());
	return i;
};

int TdApi::getCounterType()
{
	int i = this->api->GetCounterType();
	return i;
};

pybind11::list TdApi::getSecuidInfo()
{
	SecuidInfo info[20];
	int count;
	int i = this->api->GetSecuidInfo(info, &count);

	pybind11::list data;

	for (int i = 0; i < count; i++)
	{
		dict d;
		d["market"] = info[i].market;
		d["secuid"] = info[i].secuid;
		d["bank_code"] = info[i].bank_code;
		data.append(d);
	}

	return data;
};

dict TdApi::getApiLocalAddr()
{
	IpAddr localAddr;
	int i = this->api->GetApiLocalAddr(&localAddr);

	dict data;
	data["ip"] = localAddr.ip;
	data["port"] = localAddr.port;
	return data;
};
int TdApi::order(const dict &req, int request_id)
{
	OrderReq myreq = OrderReq();
	memset(&myreq, 0, sizeof(myreq));
	getString(req, "cl_order_id", myreq.cl_order_id);
	getString(req, "symbol", myreq.symbol);
	getInt16_t(req, "order_type", &myreq.order_type);
	getInt16_t(req, "side", &myreq.side);
	getInt64_t(req, "volume", &myreq.volume);
	getInt64_t(req, "price", &myreq.price);
	getInt16_t(req, "order_flag", &myreq.order_flag);
	int i = this->api->Order(&myreq, request_id);
	return i;
};

int TdApi::batchOrder(const dict &req, int count, int request_id)
{
	OrderReq myreq = OrderReq();
	memset(&myreq, 0, sizeof(myreq));
	getString(req, "cl_order_id", myreq.cl_order_id);
	getString(req, "symbol", myreq.symbol);
	getInt16_t(req, "order_type", &myreq.order_type);
	getInt16_t(req, "side", &myreq.side);
	getInt64_t(req, "volume", &myreq.volume);
	getInt64_t(req, "price", &myreq.price);
	getInt16_t(req, "order_flag", &myreq.order_flag);
	int i = this->api->BatchOrder(&myreq, count, request_id);
	return i;
};

int TdApi::cancelOrder(const dict &req, int request_id)
{
	CancelReq myreq = CancelReq();
	memset(&myreq, 0, sizeof(myreq));
	getString(req, "order_id", myreq.order_id);
	getString(req, "cl_order_id", myreq.cl_order_id);
	getString(req, "cl_cancel_id", myreq.cl_cancel_id);
	int i = this->api->CancelOrder(&myreq, request_id);
	return i;
};

int TdApi::batchCancelOrder(const dict &req, int count, int request_id)
{
	CancelReq myreq = CancelReq();
	memset(&myreq, 0, sizeof(myreq));
	getString(req, "order_id", myreq.order_id);
	getString(req, "cl_order_id", myreq.cl_order_id);
	getString(req, "cl_cancel_id", myreq.cl_cancel_id);
	int i = this->api->BatchCancelOrder(&myreq, count, request_id);
	return i;
};

int TdApi::queryOrder(string order_id, int request_id, string market)
{
	int i = this->api->QueryOrder(order_id.c_str(), request_id, market.c_str());
	return i;
};

int TdApi::queryOrderByCode(string symbol, int request_id)
{
	int i = this->api->QueryOrderByCode(symbol.c_str(), request_id);
	return i;
};

int TdApi::queryOrders(string pos_str, int query_num, int request_id, int query_flag)
{
	int i = this->api->QueryOrders(pos_str.c_str(), query_num, request_id, query_flag);
	return i;
};

int TdApi::queryTradeByOrderId(string order_id, int request_id, string market)
{
	int i = this->api->QueryTradeByOrderId(order_id.c_str(), request_id, market.c_str());
	return i;
};

int TdApi::queryTradeByCode(string symbol, int request_id)
{
	int i = this->api->QueryTradeByCode(symbol.c_str(), request_id);
	return i;
};

int TdApi::queryTrades(string pos_str, int query_num, int request_id)
{
	int i = this->api->QueryTrades(pos_str.c_str(), query_num, request_id);
	return i;
};

int TdApi::queryETFTrades(string pos_str, int query_num, int request_id, string market)
{
	int i = this->api->QueryETFTrades(pos_str.c_str(), query_num, request_id, market.c_str());
	return i;
};

int TdApi::queryPosition(string symbol, int request_id)
{
	int i = this->api->QueryPosition(symbol.c_str(), request_id);
	return i;
};

int TdApi::queryPositions(string pos_str, int query_num, int request_id)
{
	int i = this->api->QueryPositions(pos_str.c_str(), query_num, request_id);
	return i;
};

int TdApi::queryCash(int request_id)
{
	int i = this->api->QueryCash(request_id);
	return i;
};

int TdApi::queryJZJYAvailFund(int request_id)
{
	int i = this->api->QueryJZJYAvailFund(request_id);
	return i;
};

int TdApi::transferFundInAndOut(int transfer_side, int transfer_value, int request_id, string market)
{
	int i = this->api->TransferFundInAndOut(transfer_side, transfer_value, request_id, market.c_str());
	return i;
};

int TdApi::transferFundBetweenSecuid(string fund_out_market, string fund_in_market, int transfer_value, int request_id)
{
	int i = this->api->TransferFundBetweenSecuid(fund_out_market.c_str(), fund_in_market.c_str(), transfer_value, request_id);
	return i;
};

int TdApi::queryETFs(int request_id)
{
	int i = this->api->QueryETFs(request_id);
	return i;
};

int TdApi::queryETFStocks(string first_symbol, int request_id)
{
	int i = this->api->QueryETFStocks(first_symbol.c_str(), request_id);
	return i;
};

int TdApi::queryMaxOrderQty(string symbol, int order_type, int side, int price, int request_id)
{
	int i = this->api->QueryMaxOrderQty(symbol.c_str(), order_type, side, price, request_id);
	return i;
};

int TdApi::queryIPOMaxPurchase(int request_id)
{
	int i = this->api->QueryIPOMaxPurchase(request_id);
	return i;
};

int TdApi::queryIPOStock(int request_id, int query_flag)
{
	int i = this->api->QueryIPOStock(request_id, query_flag);
	return i;
};

int TdApi::queryIPODistribution(int start_date, int end_date, string pos_str, int query_num, int request_id)
{
	int i = this->api->QueryIPODistribution(start_date, end_date, pos_str.c_str(), query_num, request_id);
	return i;
};

int TdApi::queryIPOLottery(int start_date, int end_date, string pos_str, int query_num, int request_id)
{
	int i = this->api->QueryIPOLottery(start_date, end_date, pos_str.c_str(), query_num, request_id);
	return i;
};

int TdApi::querySecurityBaseInfo(int request_id, string symbol)
{
	int i = this->api->QuerySecurityBaseInfo(request_id, symbol.c_str());
	return i;
};

int TdApi::creditMortgageInOut(const dict &req, int request_id)
{
	CreditMortgageInOutReq myreq = CreditMortgageInOutReq();
	memset(&myreq, 0, sizeof(myreq));
	getString(req, "cl_order_id", myreq.cl_order_id);
	getString(req, "symbol", myreq.symbol);
	getInt16_t(req, "side", &myreq.side);
	getInt32_t(req, "volume", &myreq.volume);
	int i = this->api->CreditMortgageInOut(&myreq, request_id);
	return i;
};

int TdApi::creditStockBack(const dict &req, int request_id)
{
	CreditStockBackReq myreq = CreditStockBackReq();
	memset(&myreq, 0, sizeof(myreq));
	getString(req, "cl_order_id", myreq.cl_order_id);
	getString(req, "symbol", myreq.symbol);
	getInt32_t(req, "volume", &myreq.volume);
	int i = this->api->CreditStockBack(&myreq, request_id);
	return i;
};

int TdApi::creditPayBack(int back_amt, int request_id)
{
	int i = this->api->CreditPayBack(back_amt, request_id);
	return i;
};

int TdApi::creditPayBackByOrder(string order_id, int order_date, int back_amt, int request_id)
{
	int i = this->api->CreditPayBackByOrder(order_id.c_str(), order_date, back_amt, request_id);
	return i;
};

int TdApi::queryCreditStock(string pos_str, int query_num, int request_id)
{
	int i = this->api->QueryCreditStock(pos_str.c_str(), query_num, request_id);
	return i;
};

int TdApi::queryCreditMortgageHold(string pos_str, int query_num, int request_id)
{
	int i = this->api->QueryCreditMortgageHold(pos_str.c_str(), query_num, request_id);
	return i;
};

int TdApi::queryCreditAssets(int request_id)
{
	int i = this->api->QueryCreditAssets(request_id);
	return i;
};

int TdApi::queryCreditFinance(string pos_str, int query_num, int request_id)
{
	int i = this->api->QueryCreditFinance(pos_str.c_str(), query_num, request_id);
	return i;
};

int TdApi::queryCreditShortsell(string pos_str, int query_num, int request_id)
{
	int i = this->api->QueryCreditShortsell(pos_str.c_str(), query_num, request_id);
	return i;
};

int TdApi::queryCreditRepayAmount(int request_id)
{
	int i = this->api->QueryCreditRepayAmount(request_id);
	return i;
};

int TdApi::queryCreditRepayStock(string market, string code, int request_id)
{
	int i = this->api->QueryCreditRepayStock(market.c_str(), code.c_str(), request_id);
	return i;
};

int TdApi::queryCreditSecuritySellQty(string market, string code, int request_id)
{
	int i = this->api->QueryCreditSecuritySellQty(market.c_str(), code.c_str(), request_id);
	return i;
};

int TdApi::querySecuidRight(string market, int secuid_right, int request_id)
{
	int i = this->api->QuerySecuidRight(market.c_str(), secuid_right, request_id);
	return i;
};

int TdApi::queryHKRate(string market, int request_id)
{
	int i = this->api->QueryHKRate(market.c_str(), request_id);
	return i;
};

int TdApi::queryHKStock(string market, int request_id)
{
	int i = this->api->QueryHKStock(market.c_str(), request_id);
	return i;
};

int TdApi::queryHKFund(int request_id)
{
	int i = this->api->QueryHKFund(request_id);
	return i;
};

int TdApi::queryHKMinPriceUnit(string market, int request_id)
{
	int i = this->api->QueryHKMinPriceUnit(market.c_str(), request_id);
	return i;
};

int TdApi::queryHKTradeCalendar(int start_date, int end_date, int request_id)
{
	int i = this->api->QueryHKTradeCalendar(start_date, end_date, request_id);
	return i;
};

int TdApi::queryLockSecurityDetail(int begin_date, int end_date, int request_id, string market, string code)
{
	int i = this->api->QueryLockSecurityDetail(begin_date, end_date, request_id, market.c_str(), code.c_str());
	return i;
};

int TdApi::extendLockSecurity(const dict &req, int request_id)
{
	ExtendLockSecurityReq myreq = ExtendLockSecurityReq();
	memset(&myreq, 0, sizeof(myreq));
	getInt32_t(req, "sys_date", &myreq.sys_date);
	getString(req, "sno", myreq.sno);
	getInt32_t(req, "apply_delay_days", &myreq.apply_delay_days);
	getInt64_t(req, "apply_used_fee_rate", &myreq.apply_used_fee_rate);
	getInt64_t(req, "apply_unused_fee_rate", &myreq.apply_unused_fee_rate);
	getInt32_t(req, "apply_delay_qty", &myreq.apply_delay_qty);
	getString(req, "symbol", myreq.symbol);
	int i = this->api->ExtendLockSecurity(&myreq, request_id);
	return i;
};

int TdApi::queryLockSecurityExtension(int begin_date, int end_date, int request_id)
{
	int i = this->api->QueryLockSecurityExtension(begin_date, end_date, request_id);
	return i;
};

int TdApi::cancelExtendLockSecurity(int apply_date, string apply_sno, int request_id)
{
	int i = this->api->CancelExtendLockSecurity(apply_date, apply_sno.c_str(), request_id);
	return i;
};

int TdApi::queryTransferFundHistory(int request_id)
{
	int i = this->api->QueryTransferFundHistory(request_id);
	return i;
};



///-------------------------------------------------------------------------------------
///Boost.Python封装
///-------------------------------------------------------------------------------------

class PyTdApi : public TdApi
{
public:
    using TdApi::TdApi;
    
	void onDisconnect() override
	{
		try
		{
			PYBIND11_OVERLOAD(void, TdApi, onDisconnect);
		}
		catch (const error_already_set &e)
		{
			cout << e.what() << endl;
		}
	};

	void onError(const dict &error, int request_id) override
	{
		try
		{
			PYBIND11_OVERLOAD(void, TdApi, onError, error, request_id);
		}
		catch (const error_already_set &e)
		{
			cout << e.what() << endl;
		}
	};

	void onRiskNotify(const dict &data) override
	{
		try
		{
			PYBIND11_OVERLOAD(void, TdApi, onRiskNotify, data);
		}
		catch (const error_already_set &e)
		{
			cout << e.what() << endl;
		}
	};

	void onLogin(const dict &data, const dict &error) override
	{
		try
		{
			PYBIND11_OVERLOAD(void, TdApi, onLogin, data, error);
		}
		catch (const error_already_set &e)
		{
			cout << e.what() << endl;
		}
	};

	void onTradeReport(const dict &data) override
	{
		try
		{
			PYBIND11_OVERLOAD(void, TdApi, onTradeReport, data);
		}
		catch (const error_already_set &e)
		{
			cout << e.what() << endl;
		}
	};

	void onOrderStatus(const dict &data) override
	{
		try
		{
			PYBIND11_OVERLOAD(void, TdApi, onOrderStatus, data);
		}
		catch (const error_already_set &e)
		{
			cout << e.what() << endl;
		}
	};

	void onOrderRsp(const dict &data, const dict &error, int request_id, bool last) override
	{
		try
		{
			PYBIND11_OVERLOAD(void, TdApi, onOrderRsp, data, error, request_id, last);
		}
		catch (const error_already_set &e)
		{
			cout << e.what() << endl;
		}
	};

	void onCancelRsp(const dict &data, const dict &error, int request_id, bool last) override
	{
		try
		{
			PYBIND11_OVERLOAD(void, TdApi, onCancelRsp, data, error, request_id, last);
		}
		catch (const error_already_set &e)
		{
			cout << e.what() << endl;
		}
	};

	void onQueryOrderRsp(const dict &data, const dict &error, int request_id, bool last, string pos_str) override
	{
		try
		{
			PYBIND11_OVERLOAD(void, TdApi, onQueryOrderRsp, data, error, request_id, last, pos_str);
		}
		catch (const error_already_set &e)
		{
			cout << e.what() << endl;
		}
	};

	void onQueryTradeRsp(const dict &data, const dict &error, int request_id, bool last, string pos_str) override
	{
		try
		{
			PYBIND11_OVERLOAD(void, TdApi, onQueryTradeRsp, data, error, request_id, last, pos_str);
		}
		catch (const error_already_set &e)
		{
			cout << e.what() << endl;
		}
	};

	void onQueryPositionRsp(const dict &data, const dict &error, int request_id, bool last, string pos_str) override
	{
		try
		{
			PYBIND11_OVERLOAD(void, TdApi, onQueryPositionRsp, data, error, request_id, last, pos_str);
		}
		catch (const error_already_set &e)
		{
			cout << e.what() << endl;
		}
	};

	void onQueryCashRsp(const dict &data, const dict &error, int request_id) override
	{
		try
		{
			PYBIND11_OVERLOAD(void, TdApi, onQueryCashRsp, data, error, request_id);
		}
		catch (const error_already_set &e)
		{
			cout << e.what() << endl;
		}
	};

	void onQueryJZJYAvailFundRsp(int64_t avail_balance, const dict &error, int request_id) override
	{
		try
		{
			PYBIND11_OVERLOAD(void, TdApi, onQueryJZJYAvailFundRsp, avail_balance, error, request_id);
		}
		catch (const error_already_set &e)
		{
			cout << e.what() << endl;
		}
	};

	void onTransferFundInAndOutRsp(int64_t transfer_value, const dict &error, int request_id) override
	{
		try
		{
			PYBIND11_OVERLOAD(void, TdApi, onTransferFundInAndOutRsp, transfer_value, error, request_id);
		}
		catch (const error_already_set &e)
		{
			cout << e.what() << endl;
		}
	};

	void onTransferFundBetweenSecuidRsp(int64_t transfer_value, const dict &error, int request_id) override
	{
		try
		{
			PYBIND11_OVERLOAD(void, TdApi, onTransferFundBetweenSecuidRsp, transfer_value, error, request_id);
		}
		catch (const error_already_set &e)
		{
			cout << e.what() << endl;
		}
	};

	void onQueryETFRsp(const dict &data, const dict &error, int request_id, bool last) override
	{
		try
		{
			PYBIND11_OVERLOAD(void, TdApi, onQueryETFRsp, data, error, request_id, last);
		}
		catch (const error_already_set &e)
		{
			cout << e.what() << endl;
		}
	};

	void onQueryETFStockRsp(const dict &data, const dict &error, int request_id, bool last) override
	{
		try
		{
			PYBIND11_OVERLOAD(void, TdApi, onQueryETFStockRsp, data, error, request_id, last);
		}
		catch (const error_already_set &e)
		{
			cout << e.what() << endl;
		}
	};

	void onQueryMaxOrderQtyRsp(const dict &data, const dict &error, int request_id) override
	{
		try
		{
			PYBIND11_OVERLOAD(void, TdApi, onQueryMaxOrderQtyRsp, data, error, request_id);
		}
		catch (const error_already_set &e)
		{
			cout << e.what() << endl;
		}
	};

	void onQueryIPOMaxPurchaseRsp(const dict &data, const dict &error, int request_id, bool last) override
	{
		try
		{
			PYBIND11_OVERLOAD(void, TdApi, onQueryIPOMaxPurchaseRsp, data, error, request_id, last);
		}
		catch (const error_already_set &e)
		{
			cout << e.what() << endl;
		}
	};

	void onQueryIPOStockRsp(const dict &data, const dict &error, int request_id, bool last) override
	{
		try
		{
			PYBIND11_OVERLOAD(void, TdApi, onQueryIPOStockRsp, data, error, request_id, last);
		}
		catch (const error_already_set &e)
		{
			cout << e.what() << endl;
		}
	};

	void onQueryIPODistributionRsp(const dict &data, const dict &error, int request_id, bool last, string pos_str) override
	{
		try
		{
			PYBIND11_OVERLOAD(void, TdApi, onQueryIPODistributionRsp, data, error, request_id, last, pos_str);
		}
		catch (const error_already_set &e)
		{
			cout << e.what() << endl;
		}
	};

	void onQueryIPOLotteryRsp(const dict &data, const dict &error, int request_id, bool last, string pos_str) override
	{
		try
		{
			PYBIND11_OVERLOAD(void, TdApi, onQueryIPOLotteryRsp, data, error, request_id, last, pos_str);
		}
		catch (const error_already_set &e)
		{
			cout << e.what() << endl;
		}
	};

	void onQuerySecurityBaseInfoRsp(const dict &data, const dict &error, int request_id, bool last) override
	{
		try
		{
			PYBIND11_OVERLOAD(void, TdApi, onQuerySecurityBaseInfoRsp, data, error, request_id, last);
		}
		catch (const error_already_set &e)
		{
			cout << e.what() << endl;
		}
	};

	void onCreditMortgageInOutRsp(const dict &data, const dict &error, int request_id) override
	{
		try
		{
			PYBIND11_OVERLOAD(void, TdApi, onCreditMortgageInOutRsp, data, error, request_id);
		}
		catch (const error_already_set &e)
		{
			cout << e.what() << endl;
		}
	};

	void onCreditStockBackRsp(const dict &data, const dict &error, int request_id) override
	{
		try
		{
			PYBIND11_OVERLOAD(void, TdApi, onCreditStockBackRsp, data, error, request_id);
		}
		catch (const error_already_set &e)
		{
			cout << e.what() << endl;
		}
	};

	void onCreditPayBackRsp(const dict &data, const dict &error, int request_id) override
	{
		try
		{
			PYBIND11_OVERLOAD(void, TdApi, onCreditPayBackRsp, data, error, request_id);
		}
		catch (const error_already_set &e)
		{
			cout << e.what() << endl;
		}
	};

	void onCreditPayBackByOrderRsp(const dict &data, const dict &error, int request_id) override
	{
		try
		{
			PYBIND11_OVERLOAD(void, TdApi, onCreditPayBackByOrderRsp, data, error, request_id);
		}
		catch (const error_already_set &e)
		{
			cout << e.what() << endl;
		}
	};

	void onQueryCreditStockRsp(const dict &data, const dict &error, int request_id, bool last, string pos_str) override
	{
		try
		{
			PYBIND11_OVERLOAD(void, TdApi, onQueryCreditStockRsp, data, error, request_id, last, pos_str);
		}
		catch (const error_already_set &e)
		{
			cout << e.what() << endl;
		}
	};

	void onQueryCreditMortgageHoldRsp(const dict &data, const dict &error, int request_id, bool last, string pos_str) override
	{
		try
		{
			PYBIND11_OVERLOAD(void, TdApi, onQueryCreditMortgageHoldRsp, data, error, request_id, last, pos_str);
		}
		catch (const error_already_set &e)
		{
			cout << e.what() << endl;
		}
	};

	void onQueryCreditAssetsRsp(const dict &data, const dict &error, int request_id) override
	{
		try
		{
			PYBIND11_OVERLOAD(void, TdApi, onQueryCreditAssetsRsp, data, error, request_id);
		}
		catch (const error_already_set &e)
		{
			cout << e.what() << endl;
		}
	};

	void onQueryCreditFinanceRsp(const dict &data, const dict &error, int request_id, bool last, string pos_str) override
	{
		try
		{
			PYBIND11_OVERLOAD(void, TdApi, onQueryCreditFinanceRsp, data, error, request_id, last, pos_str);
		}
		catch (const error_already_set &e)
		{
			cout << e.what() << endl;
		}
	};

	void onQueryCreditShortsellRsp(const dict &data, const dict &error, int request_id, bool last, string pos_str) override
	{
		try
		{
			PYBIND11_OVERLOAD(void, TdApi, onQueryCreditShortsellRsp, data, error, request_id, last, pos_str);
		}
		catch (const error_already_set &e)
		{
			cout << e.what() << endl;
		}
	};

	void onQueryCreditRepayAmountRsp(const dict &data, const dict &error, int request_id) override
	{
		try
		{
			PYBIND11_OVERLOAD(void, TdApi, onQueryCreditRepayAmountRsp, data, error, request_id);
		}
		catch (const error_already_set &e)
		{
			cout << e.what() << endl;
		}
	};

	void onQueryCreditRepayStockRsp(const dict &data, const dict &error, int request_id, bool last, string pos_str) override
	{
		try
		{
			PYBIND11_OVERLOAD(void, TdApi, onQueryCreditRepayStockRsp, data, error, request_id, last, pos_str);
		}
		catch (const error_already_set &e)
		{
			cout << e.what() << endl;
		}
	};

	void onQueryCreditSecuritySellQtyRsp(const dict &data, const dict &error, int request_id, bool last) override
	{
		try
		{
			PYBIND11_OVERLOAD(void, TdApi, onQueryCreditSecuritySellQtyRsp, data, error, request_id, last);
		}
		catch (const error_already_set &e)
		{
			cout << e.what() << endl;
		}
	};

	void onQuerySecuidRightRsp(string market, int secuid_right, const dict &error, bool last, int request_id) override
	{
		try
		{
			PYBIND11_OVERLOAD(void, TdApi, onQuerySecuidRightRsp, market, secuid_right, error, last, request_id);
		}
		catch (const error_already_set &e)
		{
			cout << e.what() << endl;
		}
	};

	void onQueryHKRateRsp(const dict &data, const dict &error, int request_id, bool last) override
	{
		try
		{
			PYBIND11_OVERLOAD(void, TdApi, onQueryHKRateRsp, data, error, request_id, last);
		}
		catch (const error_already_set &e)
		{
			cout << e.what() << endl;
		}
	};

	void onQueryHKStockRsp(const dict &data, const dict &error, int request_id, bool last) override
	{
		try
		{
			PYBIND11_OVERLOAD(void, TdApi, onQueryHKStockRsp, data, error, request_id, last);
		}
		catch (const error_already_set &e)
		{
			cout << e.what() << endl;
		}
	};

	void onQueryHKFundRsp(const dict &data, const dict &error, int request_id) override
	{
		try
		{
			PYBIND11_OVERLOAD(void, TdApi, onQueryHKFundRsp, data, error, request_id);
		}
		catch (const error_already_set &e)
		{
			cout << e.what() << endl;
		}
	};

	void onQueryHKMinPriceUnitRsp(const dict &data, const dict &error, int request_id, bool last) override
	{
		try
		{
			PYBIND11_OVERLOAD(void, TdApi, onQueryHKMinPriceUnitRsp, data, error, request_id, last);
		}
		catch (const error_already_set &e)
		{
			cout << e.what() << endl;
		}
	};

	void onQueryHKTradeCalendarRsp(const dict &data, const dict &error, int request_id, bool last) override
	{
		try
		{
			PYBIND11_OVERLOAD(void, TdApi, onQueryHKTradeCalendarRsp, data, error, request_id, last);
		}
		catch (const error_already_set &e)
		{
			cout << e.what() << endl;
		}
	};

	void onQueryLockSecurityDetailRsp(const dict &data, const dict &error, int request_id, bool last) override
	{
		try
		{
			PYBIND11_OVERLOAD(void, TdApi, onQueryLockSecurityDetailRsp, data, error, request_id, last);
		}
		catch (const error_already_set &e)
		{
			cout << e.what() << endl;
		}
	};

	void onExtendLockSecurityRsp(int apply_sno, int apply_date, const dict &error, int request_id) override
	{
		try
		{
			PYBIND11_OVERLOAD(void, TdApi, onExtendLockSecurityRsp, apply_sno, apply_date, error, request_id);
		}
		catch (const error_already_set &e)
		{
			cout << e.what() << endl;
		}
	};

	void onQueryLockSecurityExtensionRsp(const dict &data, const dict &error, int request_id, bool last) override
	{
		try
		{
			PYBIND11_OVERLOAD(void, TdApi, onQueryLockSecurityExtensionRsp, data, error, request_id, last);
		}
		catch (const error_already_set &e)
		{
			cout << e.what() << endl;
		}
	};

	void onCancelExtendLockSecurityRsp(int apply_date, string apply_sno, string cancel_sno, const dict &error, int request_id) override
	{
		try
		{
			PYBIND11_OVERLOAD(void, TdApi, onCancelExtendLockSecurityRsp, apply_date, apply_sno, cancel_sno, error, request_id);
		}
		catch (const error_already_set &e)
		{
			cout << e.what() << endl;
		}
	};

	void onQueryTransferFundHistoryRsp(const dict &data, const dict &error, int request_id, bool last) override
	{
		try
		{
			PYBIND11_OVERLOAD(void, TdApi, onQueryTransferFundHistoryRsp, data, error, request_id, last);
		}
		catch (const error_already_set &e)
		{
			cout << e.what() << endl;
		}
	};



};


PYBIND11_MODULE(vnhfttd, m)
{
    class_<TdApi, PyTdApi> TdApi(m, "TdApi", module_local());
    TdApi
        .def(init<>())
        .def("createTraderApi", &TdApi::createTraderApi)
        .def("release", &TdApi::release)
        .def("exit", &TdApi::exit)
        .def("getApiVersion", &TdApi::getApiVersion)
        .def("setLogConfig", &TdApi::setLogConfig)

		.def("login", &TdApi::login)
		.def("getCounterType", &TdApi::getCounterType)
		.def("getSecuidInfo", &TdApi::getSecuidInfo)
		.def("getApiLocalAddr", &TdApi::getApiLocalAddr)
		.def("order", &TdApi::order)
		.def("batchOrder", &TdApi::batchOrder)
		.def("cancelOrder", &TdApi::cancelOrder)
		.def("batchCancelOrder", &TdApi::batchCancelOrder)
		.def("queryOrder", &TdApi::queryOrder)
		.def("queryOrderByCode", &TdApi::queryOrderByCode)
		.def("queryOrders", &TdApi::queryOrders)
		.def("queryTradeByOrderId", &TdApi::queryTradeByOrderId)
		.def("queryTradeByCode", &TdApi::queryTradeByCode)
		.def("queryTrades", &TdApi::queryTrades)
		.def("queryETFTrades", &TdApi::queryETFTrades)
		.def("queryPosition", &TdApi::queryPosition)
		.def("queryPositions", &TdApi::queryPositions)
		.def("queryCash", &TdApi::queryCash)
		.def("queryJZJYAvailFund", &TdApi::queryJZJYAvailFund)
		.def("transferFundInAndOut", &TdApi::transferFundInAndOut)
		.def("transferFundBetweenSecuid", &TdApi::transferFundBetweenSecuid)
		.def("queryETFs", &TdApi::queryETFs)
		.def("queryETFStocks", &TdApi::queryETFStocks)
		.def("queryMaxOrderQty", &TdApi::queryMaxOrderQty)
		.def("queryIPOMaxPurchase", &TdApi::queryIPOMaxPurchase)
		.def("queryIPOStock", &TdApi::queryIPOStock)
		.def("queryIPODistribution", &TdApi::queryIPODistribution)
		.def("queryIPOLottery", &TdApi::queryIPOLottery)
		.def("querySecurityBaseInfo", &TdApi::querySecurityBaseInfo)
		.def("creditMortgageInOut", &TdApi::creditMortgageInOut)
		.def("creditStockBack", &TdApi::creditStockBack)
		.def("creditPayBack", &TdApi::creditPayBack)
		.def("creditPayBackByOrder", &TdApi::creditPayBackByOrder)
		.def("queryCreditStock", &TdApi::queryCreditStock)
		.def("queryCreditMortgageHold", &TdApi::queryCreditMortgageHold)
		.def("queryCreditAssets", &TdApi::queryCreditAssets)
		.def("queryCreditFinance", &TdApi::queryCreditFinance)
		.def("queryCreditShortsell", &TdApi::queryCreditShortsell)
		.def("queryCreditRepayAmount", &TdApi::queryCreditRepayAmount)
		.def("queryCreditRepayStock", &TdApi::queryCreditRepayStock)
		.def("queryCreditSecuritySellQty", &TdApi::queryCreditSecuritySellQty)
		.def("querySecuidRight", &TdApi::querySecuidRight)
		.def("queryHKRate", &TdApi::queryHKRate)
		.def("queryHKStock", &TdApi::queryHKStock)
		.def("queryHKFund", &TdApi::queryHKFund)
		.def("queryHKMinPriceUnit", &TdApi::queryHKMinPriceUnit)
		.def("queryHKTradeCalendar", &TdApi::queryHKTradeCalendar)
		.def("queryLockSecurityDetail", &TdApi::queryLockSecurityDetail)
		.def("extendLockSecurity", &TdApi::extendLockSecurity)
		.def("queryLockSecurityExtension", &TdApi::queryLockSecurityExtension)
		.def("cancelExtendLockSecurity", &TdApi::cancelExtendLockSecurity)
		.def("queryTransferFundHistory", &TdApi::queryTransferFundHistory)

		.def("onDisconnect", &TdApi::onDisconnect)
		.def("onError", &TdApi::onError)
		.def("onRiskNotify", &TdApi::onRiskNotify)
		.def("onLogin", &TdApi::onLogin)
		.def("onTradeReport", &TdApi::onTradeReport)
		.def("onOrderStatus", &TdApi::onOrderStatus)
		.def("onOrderRsp", &TdApi::onOrderRsp)
		.def("onCancelRsp", &TdApi::onCancelRsp)
		.def("onQueryOrderRsp", &TdApi::onQueryOrderRsp)
		.def("onQueryTradeRsp", &TdApi::onQueryTradeRsp)
		.def("onQueryPositionRsp", &TdApi::onQueryPositionRsp)
		.def("onQueryCashRsp", &TdApi::onQueryCashRsp)
		.def("onQueryJZJYAvailFundRsp", &TdApi::onQueryJZJYAvailFundRsp)
		.def("onTransferFundInAndOutRsp", &TdApi::onTransferFundInAndOutRsp)
		.def("onTransferFundBetweenSecuidRsp", &TdApi::onTransferFundBetweenSecuidRsp)
		.def("onQueryETFRsp", &TdApi::onQueryETFRsp)
		.def("onQueryETFStockRsp", &TdApi::onQueryETFStockRsp)
		.def("onQueryMaxOrderQtyRsp", &TdApi::onQueryMaxOrderQtyRsp)
		.def("onQueryIPOMaxPurchaseRsp", &TdApi::onQueryIPOMaxPurchaseRsp)
		.def("onQueryIPOStockRsp", &TdApi::onQueryIPOStockRsp)
		.def("onQueryIPODistributionRsp", &TdApi::onQueryIPODistributionRsp)
		.def("onQueryIPOLotteryRsp", &TdApi::onQueryIPOLotteryRsp)
		.def("onQuerySecurityBaseInfoRsp", &TdApi::onQuerySecurityBaseInfoRsp)
		.def("onCreditMortgageInOutRsp", &TdApi::onCreditMortgageInOutRsp)
		.def("onCreditStockBackRsp", &TdApi::onCreditStockBackRsp)
		.def("onCreditPayBackRsp", &TdApi::onCreditPayBackRsp)
		.def("onCreditPayBackByOrderRsp", &TdApi::onCreditPayBackByOrderRsp)
		.def("onQueryCreditStockRsp", &TdApi::onQueryCreditStockRsp)
		.def("onQueryCreditMortgageHoldRsp", &TdApi::onQueryCreditMortgageHoldRsp)
		.def("onQueryCreditAssetsRsp", &TdApi::onQueryCreditAssetsRsp)
		.def("onQueryCreditFinanceRsp", &TdApi::onQueryCreditFinanceRsp)
		.def("onQueryCreditShortsellRsp", &TdApi::onQueryCreditShortsellRsp)
		.def("onQueryCreditRepayAmountRsp", &TdApi::onQueryCreditRepayAmountRsp)
		.def("onQueryCreditRepayStockRsp", &TdApi::onQueryCreditRepayStockRsp)
		.def("onQueryCreditSecuritySellQtyRsp", &TdApi::onQueryCreditSecuritySellQtyRsp)
		.def("onQuerySecuidRightRsp", &TdApi::onQuerySecuidRightRsp)
		.def("onQueryHKRateRsp", &TdApi::onQueryHKRateRsp)
		.def("onQueryHKStockRsp", &TdApi::onQueryHKStockRsp)
		.def("onQueryHKFundRsp", &TdApi::onQueryHKFundRsp)
		.def("onQueryHKMinPriceUnitRsp", &TdApi::onQueryHKMinPriceUnitRsp)
		.def("onQueryHKTradeCalendarRsp", &TdApi::onQueryHKTradeCalendarRsp)
		.def("onQueryLockSecurityDetailRsp", &TdApi::onQueryLockSecurityDetailRsp)
		.def("onExtendLockSecurityRsp", &TdApi::onExtendLockSecurityRsp)
		.def("onQueryLockSecurityExtensionRsp", &TdApi::onQueryLockSecurityExtensionRsp)
		.def("onCancelExtendLockSecurityRsp", &TdApi::onCancelExtendLockSecurityRsp)
		.def("onQueryTransferFundHistoryRsp", &TdApi::onQueryTransferFundHistoryRsp)
		;

}
