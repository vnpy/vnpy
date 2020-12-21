    void TdApi::OnDisconnect() 
{
	gil_scoped_acquire acquire;
	this->onDisconnect();
};

    void TdApi::OnError(ErrorInfo* error_info, int request_id = 0) 
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
		data["secuid_array"] = rsp->secuid_array;
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

    void TdApi::OnQueryPositionRsp(PositionDetail* position_detail,ErrorInfo* error_info, int request_id,bool is_last, const char* pos_str) 
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

    void TdApi::OnQueryCashRsp(CashDetail* cash_detail, ErrorInfo* error_info,int request_id) 
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

    void TdApi::OnQueryJZJYAvailFundRsp(int64_t avail_balance,ErrorInfo* error_info,int request_id) 
{
	gil_scoped_acquire acquire;
	dict error;
	{
		error["err_code"] = error_info->err_code;
		error["err_msg"] = toUtf(error_info->err_msg);
	}
	this->onQueryJZJYAvailFundRsp(avail_balance, error, request_id);
};

    void TdApi::OnTransferFundInAndOutRsp(int64_t transfer_value,ErrorInfo* error_info,int request_id) 
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
		data["credit_fund_ctrl"] = toUtf(detail->credit_fund_ctrl);
		data["credit_stk_ctrl"] = toUtf(detail->credit_stk_ctrl);
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

    void TdApi::OnQueryCreditAssetsRsp(CreditAssetsDetail* detail, ErrorInfo* error_info, int request_id) {
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

    void TdApi::OnQueryCreditSecuritySellQtyRsp(CreditSecuritySellQtyRsp* rsp, ErrorInfo* error_info, int request_id, bool is_last) {
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

