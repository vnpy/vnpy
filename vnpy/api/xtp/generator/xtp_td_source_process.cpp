void TdApi::processDisconnected(Task *task)
{
	gil_scoped_acquire acquire;
	this->onDisconnected(task->task_extra, task->task_extra);
};

void TdApi::processError(Task *task)
{
	gil_scoped_acquire acquire;
	dict error;
	if (task->task_error)
	{
		XTPRI *task_error = (XTPRI*)task->task_error;
		error["error_id"] = task_error->error_id;
		error["error_msg"] = toUtf(task_error->error_msg);
		delete task_error;
	}
	this->onError(error);
};

void TdApi::processOrderEvent(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		XTPOrderInfo *task_data = (XTPOrderInfo*)task->task_data;
		data["order_xtp_id"] = task_data->order_xtp_id;
		data["order_client_id"] = task_data->order_client_id;
		data["order_cancel_client_id"] = task_data->order_cancel_client_id;
		data["order_cancel_xtp_id"] = task_data->order_cancel_xtp_id;
		data["ticker"] = toUtf(task_data->ticker);
		data["market"] = task_data->market;
		data["price"] = task_data->price;
		data["quantity"] = task_data->quantity;
		data["price_type"] = task_data->price_type;
		data["side"] = task_data->side;
		data["position_effect"] = task_data->position_effect;
		data["business_type"] = task_data->business_type;
		data["qty_traded"] = task_data->qty_traded;
		data["qty_left"] = task_data->qty_left;
		data["insert_time"] = task_data->insert_time;
		data["update_time"] = task_data->update_time;
		data["cancel_time"] = task_data->cancel_time;
		data["trade_amount"] = task_data->trade_amount;
		data["order_local_id"] = toUtf(task_data->order_local_id);
		data["order_status"] = task_data->order_status;
		data["order_submit_status"] = task_data->order_submit_status;
		data["order_type"] = toUtf(task_data->order_type);
		delete task_data;
	}
	dict error;
	if (task->task_error)
	{
		XTPRI *task_error = (XTPRI*)task->task_error;
		error["error_id"] = task_error->error_id;
		error["error_msg"] = toUtf(task_error->error_msg);
		delete task_error;
	}
	this->onOrderEvent(data, error, task->task_extra);
};

void TdApi::processTradeEvent(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		XTPTradeReport *task_data = (XTPTradeReport*)task->task_data;
		data["order_xtp_id"] = task_data->order_xtp_id;
		data["order_client_id"] = task_data->order_client_id;
		data["ticker"] = toUtf(task_data->ticker);
		data["market"] = task_data->market;
		data["local_order_id"] = task_data->local_order_id;
		data["exec_id"] = toUtf(task_data->exec_id);
		data["price"] = task_data->price;
		data["quantity"] = task_data->quantity;
		data["trade_time"] = task_data->trade_time;
		data["trade_amount"] = task_data->trade_amount;
		data["report_index"] = task_data->report_index;
		data["order_exch_id"] = toUtf(task_data->order_exch_id);
		data["trade_type"] = toUtf(task_data->trade_type);
		data["side"] = task_data->side;
		data["position_effect"] = task_data->position_effect;
		data["business_type"] = task_data->business_type;
		data["branch_pbu"] = toUtf(task_data->branch_pbu);
		delete task_data;
	}
	this->onTradeEvent(data, task->task_extra);
};

void TdApi::processCancelOrderError(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		XTPOrderCancelInfo *task_data = (XTPOrderCancelInfo*)task->task_data;
		data["order_cancel_xtp_id"] = task_data->order_cancel_xtp_id;
		data["order_xtp_id"] = task_data->order_xtp_id;
		delete task_data;
	}
	dict error;
	if (task->task_error)
	{
		XTPRI *task_error = (XTPRI*)task->task_error;
		error["error_id"] = task_error->error_id;
		error["error_msg"] = toUtf(task_error->error_msg);
		delete task_error;
	}
	this->onCancelOrderError(data, error, task->task_extra);
};

void TdApi::processQueryOrder(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		XTPQueryOrderRsp *task_data = (XTPQueryOrderRsp*)task->task_data;
		data["order_xtp_id"] = task_data->order_xtp_id;
		data["order_client_id"] = task_data->order_client_id;
		data["order_cancel_client_id"] = task_data->order_cancel_client_id;
		data["order_cancel_xtp_id"] = task_data->order_cancel_xtp_id;
		data["ticker"] = toUtf(task_data->ticker);
		data["market"] = task_data->market;
		data["price"] = task_data->price;
		data["quantity"] = task_data->quantity;
		data["price_type"] = task_data->price_type;
		data["side"] = task_data->side;
		data["position_effect"] = task_data->position_effect;
		data["business_type"] = task_data->business_type;
		data["qty_traded"] = task_data->qty_traded;
		data["qty_left"] = task_data->qty_left;
		data["insert_time"] = task_data->insert_time;
		data["update_time"] = task_data->update_time;
		data["cancel_time"] = task_data->cancel_time;
		data["trade_amount"] = task_data->trade_amount;
		data["order_local_id"] = toUtf(task_data->order_local_id);
		data["order_status"] = task_data->order_status;
		data["order_submit_status"] = task_data->order_submit_status;
		data["order_type"] = toUtf(task_data->order_type);
		delete task_data;
	}
	dict error;
	if (task->task_error)
	{
		XTPRI *task_error = (XTPRI*)task->task_error;
		error["error_id"] = task_error->error_id;
		error["error_msg"] = toUtf(task_error->error_msg);
		delete task_error;
	}
	this->onQueryOrder(data, error, task->task_id, task->task_last, task->task_extra);
};

void TdApi::processQueryTrade(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		XTPQueryTradeRsp *task_data = (XTPQueryTradeRsp*)task->task_data;
		data["order_xtp_id"] = task_data->order_xtp_id;
		data["order_client_id"] = task_data->order_client_id;
		data["ticker"] = toUtf(task_data->ticker);
		data["market"] = task_data->market;
		data["local_order_id"] = task_data->local_order_id;
		data["exec_id"] = toUtf(task_data->exec_id);
		data["price"] = task_data->price;
		data["quantity"] = task_data->quantity;
		data["trade_time"] = task_data->trade_time;
		data["trade_amount"] = task_data->trade_amount;
		data["report_index"] = task_data->report_index;
		data["order_exch_id"] = toUtf(task_data->order_exch_id);
		data["trade_type"] = toUtf(task_data->trade_type);
		data["side"] = task_data->side;
		data["position_effect"] = task_data->position_effect;
		data["business_type"] = task_data->business_type;
		data["branch_pbu"] = toUtf(task_data->branch_pbu);
		delete task_data;
	}
	dict error;
	if (task->task_error)
	{
		XTPRI *task_error = (XTPRI*)task->task_error;
		error["error_id"] = task_error->error_id;
		error["error_msg"] = toUtf(task_error->error_msg);
		delete task_error;
	}
	this->onQueryTrade(data, error, task->task_id, task->task_last, task->task_extra);
};

void TdApi::processQueryPosition(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		XTPQueryStkPositionRsp *task_data = (XTPQueryStkPositionRsp*)task->task_data;
		data["ticker"] = toUtf(task_data->ticker);
		data["ticker_name"] = toUtf(task_data->ticker_name);
		data["market"] = task_data->market;
		data["total_qty"] = task_data->total_qty;
		data["sellable_qty"] = task_data->sellable_qty;
		data["avg_price"] = task_data->avg_price;
		data["unrealized_pnl"] = task_data->unrealized_pnl;
		data["yesterday_position"] = task_data->yesterday_position;
		data["purchase_redeemable_qty"] = task_data->purchase_redeemable_qty;
		data["position_direction"] = task_data->position_direction;
		data["reserved1"] = task_data->reserved1;
		data["executable_option"] = task_data->executable_option;
		data["lockable_position"] = task_data->lockable_position;
		data["executable_underlying"] = task_data->executable_underlying;
		data["locked_position"] = task_data->locked_position;
		data["usable_locked_position"] = task_data->usable_locked_position;
		data["unknown"] = task_data->unknown;
		delete task_data;
	}
	dict error;
	if (task->task_error)
	{
		XTPRI *task_error = (XTPRI*)task->task_error;
		error["error_id"] = task_error->error_id;
		error["error_msg"] = toUtf(task_error->error_msg);
		delete task_error;
	}
	this->onQueryPosition(data, error, task->task_id, task->task_last, task->task_extra);
};

void TdApi::processQueryAsset(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		XTPQueryAssetRsp *task_data = (XTPQueryAssetRsp*)task->task_data;
		data["total_asset"] = task_data->total_asset;
		data["buying_power"] = task_data->buying_power;
		data["security_asset"] = task_data->security_asset;
		data["fund_buy_amount"] = task_data->fund_buy_amount;
		data["fund_buy_fee"] = task_data->fund_buy_fee;
		data["fund_sell_amount"] = task_data->fund_sell_amount;
		data["fund_sell_fee"] = task_data->fund_sell_fee;
		data["withholding_amount"] = task_data->withholding_amount;
		data["account_type"] = task_data->account_type;
		data["frozen_margin"] = task_data->frozen_margin;
		data["frozen_exec_cash"] = task_data->frozen_exec_cash;
		data["frozen_exec_fee"] = task_data->frozen_exec_fee;
		data["pay_later"] = task_data->pay_later;
		data["preadva_pay"] = task_data->preadva_pay;
		data["orig_banlance"] = task_data->orig_banlance;
		data["banlance"] = task_data->banlance;
		data["deposit_withdraw"] = task_data->deposit_withdraw;
		data["trade_netting"] = task_data->trade_netting;
		data["captial_asset"] = task_data->captial_asset;
		data["force_freeze_amount"] = task_data->force_freeze_amount;
		data["preferred_amount"] = task_data->preferred_amount;
		data["repay_stock_aval_banlance"] = task_data->repay_stock_aval_banlance;
		data["unknown"] = task_data->unknown;
		delete task_data;
	}
	dict error;
	if (task->task_error)
	{
		XTPRI *task_error = (XTPRI*)task->task_error;
		error["error_id"] = task_error->error_id;
		error["error_msg"] = toUtf(task_error->error_msg);
		delete task_error;
	}
	this->onQueryAsset(data, error, task->task_id, task->task_last, task->task_extra);
};

void TdApi::processQueryStructuredFund(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		XTPStructuredFundInfo *task_data = (XTPStructuredFundInfo*)task->task_data;
		data["exchange_id"] = task_data->exchange_id;
		data["sf_ticker"] = toUtf(task_data->sf_ticker);
		data["sf_ticker_name"] = toUtf(task_data->sf_ticker_name);
		data["ticker"] = toUtf(task_data->ticker);
		data["ticker_name"] = toUtf(task_data->ticker_name);
		data["split_merge_status"] = task_data->split_merge_status;
		data["ratio"] = task_data->ratio;
		data["min_split_qty"] = task_data->min_split_qty;
		data["min_merge_qty"] = task_data->min_merge_qty;
		data["net_price"] = task_data->net_price;
		delete task_data;
	}
	dict error;
	if (task->task_error)
	{
		XTPRI *task_error = (XTPRI*)task->task_error;
		error["error_id"] = task_error->error_id;
		error["error_msg"] = toUtf(task_error->error_msg);
		delete task_error;
	}
	this->onQueryStructuredFund(data, error, task->task_id, task->task_last, task->task_extra);
};

void TdApi::processQueryFundTransfer(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		XTPFundTransferNotice *task_data = (XTPFundTransferNotice*)task->task_data;
		data["serial_id"] = task_data->serial_id;
		data["transfer_type"] = task_data->transfer_type;
		data["amount"] = task_data->amount;
		data["oper_status"] = task_data->oper_status;
		data["transfer_time"] = task_data->transfer_time;
		delete task_data;
	}
	dict error;
	if (task->task_error)
	{
		XTPRI *task_error = (XTPRI*)task->task_error;
		error["error_id"] = task_error->error_id;
		error["error_msg"] = toUtf(task_error->error_msg);
		delete task_error;
	}
	this->onQueryFundTransfer(data, error, task->task_id, task->task_last, task->task_extra);
};

void TdApi::processFundTransfer(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		XTPFundTransferNotice *task_data = (XTPFundTransferNotice*)task->task_data;
		data["serial_id"] = task_data->serial_id;
		data["transfer_type"] = task_data->transfer_type;
		data["amount"] = task_data->amount;
		data["oper_status"] = task_data->oper_status;
		data["transfer_time"] = task_data->transfer_time;
		delete task_data;
	}
	dict error;
	if (task->task_error)
	{
		XTPRI *task_error = (XTPRI*)task->task_error;
		error["error_id"] = task_error->error_id;
		error["error_msg"] = toUtf(task_error->error_msg);
		delete task_error;
	}
	this->onFundTransfer(data, error, task->task_extra);
};

void TdApi::processQueryETF(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		XTPQueryETFBaseRsp *task_data = (XTPQueryETFBaseRsp*)task->task_data;
		data["market"] = task_data->market;
		data["etf"] = toUtf(task_data->etf);
		data["subscribe_redemption_ticker"] = toUtf(task_data->subscribe_redemption_ticker);
		data["unit"] = task_data->unit;
		data["subscribe_status"] = task_data->subscribe_status;
		data["redemption_status"] = task_data->redemption_status;
		data["max_cash_ratio"] = task_data->max_cash_ratio;
		data["estimate_amount"] = task_data->estimate_amount;
		data["cash_component"] = task_data->cash_component;
		data["net_value"] = task_data->net_value;
		data["total_amount"] = task_data->total_amount;
		delete task_data;
	}
	dict error;
	if (task->task_error)
	{
		XTPRI *task_error = (XTPRI*)task->task_error;
		error["error_id"] = task_error->error_id;
		error["error_msg"] = toUtf(task_error->error_msg);
		delete task_error;
	}
	this->onQueryETF(data, error, task->task_id, task->task_last, task->task_extra);
};

void TdApi::processQueryETFBasket(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		XTPQueryETFComponentRsp *task_data = (XTPQueryETFComponentRsp*)task->task_data;
		data["market"] = task_data->market;
		data["ticker"] = toUtf(task_data->ticker);
		data["component_ticker"] = toUtf(task_data->component_ticker);
		data["component_name"] = toUtf(task_data->component_name);
		data["quantity"] = task_data->quantity;
		data["component_market"] = task_data->component_market;
		data["replace_type"] = task_data->replace_type;
		data["premium_ratio"] = task_data->premium_ratio;
		data["amount"] = task_data->amount;
		delete task_data;
	}
	dict error;
	if (task->task_error)
	{
		XTPRI *task_error = (XTPRI*)task->task_error;
		error["error_id"] = task_error->error_id;
		error["error_msg"] = toUtf(task_error->error_msg);
		delete task_error;
	}
	this->onQueryETFBasket(data, error, task->task_id, task->task_last, task->task_extra);
};

void TdApi::processQueryIPOInfoList(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		XTPQueryIPOTickerRsp *task_data = (XTPQueryIPOTickerRsp*)task->task_data;
		data["market"] = task_data->market;
		data["ticker"] = toUtf(task_data->ticker);
		data["ticker_name"] = toUtf(task_data->ticker_name);
		data["price"] = task_data->price;
		data["unit"] = task_data->unit;
		data["qty_upper_limit"] = task_data->qty_upper_limit;
		delete task_data;
	}
	dict error;
	if (task->task_error)
	{
		XTPRI *task_error = (XTPRI*)task->task_error;
		error["error_id"] = task_error->error_id;
		error["error_msg"] = toUtf(task_error->error_msg);
		delete task_error;
	}
	this->onQueryIPOInfoList(data, error, task->task_id, task->task_last, task->task_extra);
};

void TdApi::processQueryIPOQuotaInfo(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		XTPQueryIPOQuotaRsp *task_data = (XTPQueryIPOQuotaRsp*)task->task_data;
		data["market"] = task_data->market;
		data["quantity"] = task_data->quantity;
		delete task_data;
	}
	dict error;
	if (task->task_error)
	{
		XTPRI *task_error = (XTPRI*)task->task_error;
		error["error_id"] = task_error->error_id;
		error["error_msg"] = toUtf(task_error->error_msg);
		delete task_error;
	}
	this->onQueryIPOQuotaInfo(data, error, task->task_id, task->task_last, task->task_extra);
};

void TdApi::processQueryOptionAuctionInfo(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		XTPQueryOptionAuctionInfoRsp *task_data = (XTPQueryOptionAuctionInfoRsp*)task->task_data;
		data["ticker"] = toUtf(task_data->ticker);
		data["security_id_source"] = task_data->security_id_source;
		data["symbol"] = toUtf(task_data->symbol);
		data["contract_id"] = toUtf(task_data->contract_id);
		data["underlying_security_id"] = toUtf(task_data->underlying_security_id);
		data["underlying_security_id_source"] = task_data->underlying_security_id_source;
		data["list_date"] = task_data->list_date;
		data["last_trade_date"] = task_data->last_trade_date;
		data["ticker_type"] = task_data->ticker_type;
		data["day_trading"] = task_data->day_trading;
		data["call_or_put"] = task_data->call_or_put;
		data["delivery_day"] = task_data->delivery_day;
		data["delivery_month"] = task_data->delivery_month;
		data["exercise_type"] = task_data->exercise_type;
		data["exercise_begin_date"] = task_data->exercise_begin_date;
		data["exercise_end_date"] = task_data->exercise_end_date;
		data["exercise_price"] = task_data->exercise_price;
		data["qty_unit"] = task_data->qty_unit;
		data["contract_unit"] = task_data->contract_unit;
		data["contract_position"] = task_data->contract_position;
		data["prev_close_price"] = task_data->prev_close_price;
		data["prev_clearing_price"] = task_data->prev_clearing_price;
		data["lmt_buy_max_qty"] = task_data->lmt_buy_max_qty;
		data["lmt_buy_min_qty"] = task_data->lmt_buy_min_qty;
		data["lmt_sell_max_qty"] = task_data->lmt_sell_max_qty;
		data["lmt_sell_min_qty"] = task_data->lmt_sell_min_qty;
		data["mkt_buy_max_qty"] = task_data->mkt_buy_max_qty;
		data["mkt_buy_min_qty"] = task_data->mkt_buy_min_qty;
		data["mkt_sell_max_qty"] = task_data->mkt_sell_max_qty;
		data["mkt_sell_min_qty"] = task_data->mkt_sell_min_qty;
		data["price_tick"] = task_data->price_tick;
		data["upper_limit_price"] = task_data->upper_limit_price;
		data["lower_limit_price"] = task_data->lower_limit_price;
		data["sell_margin"] = task_data->sell_margin;
		data["margin_ratio_param1"] = task_data->margin_ratio_param1;
		data["margin_ratio_param2"] = task_data->margin_ratio_param2;
		data["unknown"] = task_data->unknown;
		delete task_data;
	}
	dict error;
	if (task->task_error)
	{
		XTPRI *task_error = (XTPRI*)task->task_error;
		error["error_id"] = task_error->error_id;
		error["error_msg"] = toUtf(task_error->error_msg);
		delete task_error;
	}
	this->onQueryOptionAuctionInfo(data, error, task->task_id, task->task_last, task->task_extra);
};

void TdApi::processCreditCashRepay(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		XTPCrdCashRepayRsp *task_data = (XTPCrdCashRepayRsp*)task->task_data;
		data["xtp_id"] = task_data->xtp_id;
		data["request_amount"] = task_data->request_amount;
		data["cash_repay_amount"] = task_data->cash_repay_amount;
		delete task_data;
	}
	dict error;
	if (task->task_error)
	{
		XTPRI *task_error = (XTPRI*)task->task_error;
		error["error_id"] = task_error->error_id;
		error["error_msg"] = toUtf(task_error->error_msg);
		delete task_error;
	}
	this->onCreditCashRepay(data, error, task->task_extra);
};

void TdApi::processQueryCreditCashRepayInfo(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		XTPCrdCashRepayInfo *task_data = (XTPCrdCashRepayInfo*)task->task_data;
		data["xtp_id"] = task_data->xtp_id;
		data["status"] = task_data->status;
		data["request_amount"] = task_data->request_amount;
		data["cash_repay_amount"] = task_data->cash_repay_amount;
		data["position_effect"] = task_data->position_effect;
		data["error_info"] = task_data->error_info;
		delete task_data;
	}
	dict error;
	if (task->task_error)
	{
		XTPRI *task_error = (XTPRI*)task->task_error;
		error["error_id"] = task_error->error_id;
		error["error_msg"] = toUtf(task_error->error_msg);
		delete task_error;
	}
	this->onQueryCreditCashRepayInfo(data, error, task->task_id, task->task_last, task->task_extra);
};

void TdApi::processQueryCreditFundInfo(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		XTPCrdFundInfo *task_data = (XTPCrdFundInfo*)task->task_data;
		data["maintenance_ratio"] = task_data->maintenance_ratio;
		data["all_asset"] = task_data->all_asset;
		data["all_debt"] = task_data->all_debt;
		data["line_of_credit"] = task_data->line_of_credit;
		data["guaranty"] = task_data->guaranty;
		data["position_amount"] = task_data->position_amount;
		delete task_data;
	}
	dict error;
	if (task->task_error)
	{
		XTPRI *task_error = (XTPRI*)task->task_error;
		error["error_id"] = task_error->error_id;
		error["error_msg"] = toUtf(task_error->error_msg);
		delete task_error;
	}
	this->onQueryCreditFundInfo(data, error, task->task_id, task->task_extra);
};

void TdApi::processQueryCreditDebtInfo(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		XTPCrdDebtInfo *task_data = (XTPCrdDebtInfo*)task->task_data;
		data["debt_type"] = task_data->debt_type;
		data["debt_id"] = toUtf(task_data->debt_id);
		data["position_id"] = task_data->position_id;
		data["order_xtp_id"] = task_data->order_xtp_id;
		data["debt_status"] = task_data->debt_status;
		data["market"] = task_data->market;
		data["ticker"] = toUtf(task_data->ticker);
		data["order_date"] = task_data->order_date;
		data["end_date"] = task_data->end_date;
		data["orig_end_date"] = task_data->orig_end_date;
		data["is_extended"] = task_data->is_extended;
		data["remain_amt"] = task_data->remain_amt;
		data["remain_qty"] = task_data->remain_qty;
		data["remain_principal"] = task_data->remain_principal;
		data["due_right_qty"] = task_data->due_right_qty;
		data["unknown"] = task_data->unknown;
		delete task_data;
	}
	dict error;
	if (task->task_error)
	{
		XTPRI *task_error = (XTPRI*)task->task_error;
		error["error_id"] = task_error->error_id;
		error["error_msg"] = toUtf(task_error->error_msg);
		delete task_error;
	}
	this->onQueryCreditDebtInfo(data, error, task->task_id, task->task_last, task->task_extra);
};

void TdApi::processQueryCreditTickerDebtInfo(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		XTPCrdDebtStockInfo *task_data = (XTPCrdDebtStockInfo*)task->task_data;
		data["market"] = task_data->market;
		data["ticker"] = toUtf(task_data->ticker);
		data["remain_quantity"] = task_data->remain_quantity;
		data["order_withhold_quantity"] = task_data->order_withhold_quantity;
		delete task_data;
	}
	dict error;
	if (task->task_error)
	{
		XTPRI *task_error = (XTPRI*)task->task_error;
		error["error_id"] = task_error->error_id;
		error["error_msg"] = toUtf(task_error->error_msg);
		delete task_error;
	}
	this->onQueryCreditTickerDebtInfo(data, error, task->task_id, task->task_last, task->task_extra);
};

void TdApi::processQueryCreditAssetDebtInfo(Task *task)
{
	gil_scoped_acquire acquire;
	dict error;
	if (task->task_error)
	{
		XTPRI *task_error = (XTPRI*)task->task_error;
		error["error_id"] = task_error->error_id;
		error["error_msg"] = toUtf(task_error->error_msg);
		delete task_error;
	}
	this->onQueryCreditAssetDebtInfo(task->task_extra, error, task->task_id, task->task_extra);
};

void TdApi::processQueryCreditTickerAssignInfo(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		XTPClientQueryCrdPositionStkInfo *task_data = (XTPClientQueryCrdPositionStkInfo*)task->task_data;
		data["market"] = task_data->market;
		data["ticker"] = toUtf(task_data->ticker);
		data["limit_qty"] = task_data->limit_qty;
		data["yesterday_qty"] = task_data->yesterday_qty;
		data["left_qty"] = task_data->left_qty;
		data["frozen_qty"] = task_data->frozen_qty;
		delete task_data;
	}
	dict error;
	if (task->task_error)
	{
		XTPRI *task_error = (XTPRI*)task->task_error;
		error["error_id"] = task_error->error_id;
		error["error_msg"] = toUtf(task_error->error_msg);
		delete task_error;
	}
	this->onQueryCreditTickerAssignInfo(data, error, task->task_id, task->task_last, task->task_extra);
};

void TdApi::processQueryCreditExcessStock(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		XTPClientQueryCrdSurplusStkRspInfo *task_data = (XTPClientQueryCrdSurplusStkRspInfo*)task->task_data;
		data["market"] = task_data->market;
		data["ticker"] = toUtf(task_data->ticker);
		data["transferable_quantity"] = task_data->transferable_quantity;
		data["transferred_quantity"] = task_data->transferred_quantity;
		delete task_data;
	}
	dict error;
	if (task->task_error)
	{
		XTPRI *task_error = (XTPRI*)task->task_error;
		error["error_id"] = task_error->error_id;
		error["error_msg"] = toUtf(task_error->error_msg);
		delete task_error;
	}
	this->onQueryCreditExcessStock(data, error, task->task_id, task->task_extra);
};

