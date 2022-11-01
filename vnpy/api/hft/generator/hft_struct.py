RiskNotify = {
    "secuid": "char",
    "alarm_score": "char",
    "alarm_status": "char",
    "alarm_rule": "char",
    "alarm_time": "char",
    "alarm_msg": "char",
}

OrderReq = {
    "cl_order_id": "char",
    "symbol": "char",
    "order_type": "int16_t",
    "side": "int16_t",
    "volume": "int64_t",
    "price": "int64_t",
    "order_flag": "int16_t",
}

OrderRsp = {
    "account_id": "char",
    "account_type": "int16_t",
    "order_date": "int32_t",
    "order_id": "char",
    "cl_order_id": "char",
}

CancelReq = {
    "order_id": "char",
    "cl_order_id": "char",
    "cl_cancel_id": "char",
}

CancelRsp = {
    "account_id": "char",
    "account_type": "int16_t",
    "order_id": "char",
    "cl_order_id": "char",
    "cl_cancel_id": "char",
}

OrderDetail = {
    "account_id": "char",
    "account_type": "int16_t",
    "order_id": "char",
    "cl_order_id": "char",
    "orig_order_id": "char",
    "symbol": "char",
    "order_status": "int16_t",
    "order_type": "int16_t",
    "side": "int16_t",
    "volume": "int64_t",
    "price": "int64_t",
    "filled_volume": "int64_t",
    "filled_turnover": "int64_t",
    "filled_price": "int64_t",
    "cancel_volume": "int64_t",
    "cancel_flag": "int16_t",
    "order_date": "int32_t",
    "order_time": "int32_t",
    "err_code": "int32_t",
    "err_msg": "char",
    "secuid": "char",
    "name": "char",
    "freeze_amount": "int64_t",
}

TradeDetail = {
    "account_id": "char",
    "account_type": "int16_t",
    "order_id": "char",
    "cl_order_id": "char",
    "symbol": "char",
    "order_type": "int16_t",
    "side": "int16_t",
    "report_type": "int16_t",
    "report_no": "char",
    "volume": "int64_t",
    "price": "int64_t",
    "turnover": "int64_t",
    "trade_date": "int32_t",
    "trade_time": "int32_t",
    "err_code": "int32_t",
    "err_msg": "char",
    "secuid": "char",
    "name": "char",
}

PositionDetail = {
    "account_id": "char",
    "account_type": "int16_t",
    "symbol": "char",
    "side": "int16_t",
    "volume": "int64_t",
    "avail_volume": "int64_t",
    "init_volume": "int64_t",
    "market_value": "int64_t",
    "today_buy_volume": "int64_t",
    "today_sell_volume": "int64_t",
    "secuid": "char",
    "cost_price": "int32_t",
    "buy_cost": "int64_t",
    "last_price": "int32_t",
    "income": "int64_t",
    "total_income": "int64_t",
    "profit_cost": "int64_t",
    "today_avail_pr_volume": "int64_t",
    "market": "int32_t",
    "security_type": "int32_t",
    "freeze_volume": "int64_t",
    "name": "char",
}

CashDetail = {
    "account_id": "char",
    "account_type": "int16_t",
    "currency_type": "int16_t",
    "total_amount": "int64_t",
    "avail_amount": "int64_t",
    "total_asset": "int64_t",
    "market_value": "int64_t",
}

AccountInfo = {
    "account_id": "char",
    "account_type": "int16_t",
    "account_pwd": "char",
    "cust_orgid": "char",
    "cust_branchid": "char",
    "cl_system_id": "char",
}

SecuidInfo = {
    "market": "char",
    "secuid": "char",
}

LoginRsp = {
    "account_id": "char",
    "account_type": "int16_t",
    "cust_orgid": "char",
    "cust_branchid": "char",
    "cust_id": "char",
    "cust_name": "char",
    "secuid_array": "SecuidInfo",
    "cif_account": "char",
}

ETFDetail = {
    "name": "char",
    "first_symbol": "char",
    "second_symbol": "char",
    "trade_unit": "int32_t",
    "cash_component": "int64_t",
    "max_cash_ratio": "int64_t",
    "trade_state": "int32_t",
    "record_num": "int32_t",
    "trade_day": "int32_t",
    "pre_trade_day": "int32_t",
    "nav_percu": "int64_t",
    "nav": "int64_t",
    "creation_limituser": "int64_t",
    "redemption_limituser": "int64_t",
    "net_creation_limituser": "int64_t",
    "net_redemption_limituser": "int64_t",
    "creation_limit": "int64_t",
    "redemption_limit": "int64_t",
    "net_creation_limit": "int64_t",
    "net_redemption_limit": "int64_t",
}

ETFStockDetail = {
    "first_symbol": "char",
    "name": "char",
    "symbol": "char",
    "volume": "int32_t",
    "replace_flag": "int16_t",
    "over_price_rate": "int64_t",
    "replace_amt": "int64_t",
}

MaxOrderQtyDetail = {
    "account_id": "char",
    "account_type": "int16_t",
    "max_qty": "int64_t",
    "actual_max_qty": "int64_t",
}

IPOMaxPurchaseDetail = {
    "account_id": "char",
    "account_type": "int16_t",
    "market": "char",
    "max_qty": "int64_t",
    "stib_max_qty": "int64_t",
}

IPOStockDetail = {
    "symbol": "char",
    "name": "char",
    "currency_type": "int16_t",
    "ipo_price": "int64_t",
    "max_num": "int64_t",
    "min_num": "int64_t",
}

IPODistributionDetail = {
    "account_id": "char",
    "account_type": "int16_t",
    "biz_date": "int32_t",
    "symbol": "char",
    "name": "char",
    "mate_no": "char",
    "match_qty": "int64_t",
}

IPOLotteryDetail = {
    "account_id": "char",
    "account_type": "int16_t",
    "biz_date": "int32_t",
    "symbol": "char",
    "name": "char",
    "match_price": "int64_t",
    "match_qty": "int64_t",
}

SecurityBaseInfo = {
    "symbol": "char",
    "name": "char",
    "security_type": "int32_t",
    "security_status": "int32_t",
    "price_tick": "int64_t",
    "limit_up": "int64_t",
    "limit_down": "int64_t",
    "max_qty": "int64_t",
    "min_qty": "int64_t",
    "buy_tick": "int64_t",
    "sale_tick": "int64_t",
    "has_price_limit": "int32_t",
    "max_rise_rate": "int32_t",
    "is_registration": "int32_t",
}

HKRateDetail = {
    "market": "char",
    "buy_rate": "int64_t",
    "sale_rate": "int64_t",
    "mid_rate": "int64_t",
    "set_rate": "int64_t",
    "sys_date": "int32_t",
}

HKStockDetail = {
    "symbol": "char",
    "name": "char",
    "stktype": "int16_t",
    "currency_type": "int16_t",
}

HKFundDetail = {
    "account_id": "char",
    "account_type": "int16_t",
    "currency_type": "int16_t",
    "fund_uncomeavl": "int64_t",
    "fund_buy": "int64_t",
    "fund_sale": "int64_t",
    "fund_uncomebuy": "int64_t",
    "fund_uncomesale": "int64_t",
}

HKMinPriceUnitDetail = {
    "stktype": "int16_t",
    "begin_price": "int64_t",
    "end_price": "int64_t",
    "price_unit": "int32_t",
}

HKTradeCalendarDetail = {
    "date": "int32_t",
    "business_flag": "int16_t",
    "commit_flag": "int16_t",
}

CreditMortgageInOutReq = {
    "cl_order_id": "char",
    "symbol": "char",
    "side": "int16_t",
    "volume": "int32_t",
}

CreditMortgageInOutRsp = {
    "account_id": "char",
    "account_type": "int16_t",
    "cl_order_id": "char",
    "order_id": "char",
}

CreditStockBackReq = {
    "cl_order_id": "char",
    "symbol": "char",
    "volume": "int32_t",
}

CreditStockBackRsp = {
    "account_id": "char",
    "account_type": "int16_t",
    "cl_order_id": "char",
    "order_id": "char",
}

CreditPayBackRsp = {
    "account_id": "char",
    "account_type": "int16_t",
    "real_back_amt": "int64_t",
}

CreditStockDetail = {
    "symbol": "char",
    "name": "char",
    "currency_type": "int16_t",
    "credit_fund_ctrl": "char",
    "credit_stk_ctrl": "char",
    "margin_rate_fund": "int64_t",
    "margin_rate_stk": "int64_t",
    "sep_rem_qty": "int32_t",
}

CreditAssetsDetail = {
    "account_id": "char",
    "account_type": "int16_t",
    "currency_type": "int16_t",
    "avail_balance": "int64_t",
    "fetch_balance": "int64_t",
    "frozen_balance": "int64_t",
    "stock_balance": "int64_t",
    "fund_balance": "int64_t",
    "asset_balance": "int64_t",
    "avail_margin": "int64_t",
    "credit_quota": "int64_t",
    "finance_quota": "int64_t",
    "shortsell_quota": "int64_t",
    "assure_ratio": "int64_t",
    "total_debt": "int64_t",
    "fund_debt": "int64_t",
    "stock_debt": "int64_t",
    "fund_interest_fee": "int64_t",
    "stock_interest_fee": "int64_t",
    "shortsell_total_balance": "int64_t",
    "shortsell_avail_balance": "int64_t",
    "shortsell_frozen_balance": "int64_t",
    "enbuyback_avail_balance": "int64_t",
    "fund_margin_profit": "int64_t",
    "stock_margin_profit": "int64_t",
    "fund_interest": "int64_t",
    "stock_interest": "int64_t",
    "fund_margin_balance": "int64_t",
    "stock_margin_balance": "int64_t",
    "fund_floating_deficit": "int64_t",
    "stock_floating_deficit": "int64_t",
    "fund_margin_profit_conversion": "int64_t",
    "stock_margin_profit_conversion": "int64_t",
}

CreditFinanceDetail = {
    "account_id": "char",
    "account_type": "int16_t",
    "symbol": "char",
    "name": "char",
    "order_id": "char",
    "currency_type": "int16_t",
    "debt_status": "int16_t",
    "occur_date": "int32_t",
    "total_balance": "int64_t",
    "cur_balance": "int64_t",
    "total_interest_fee": "int64_t",
    "cur_interest_fee": "int64_t",
    "interest_rate": "int64_t",
    "repayable_balance": "int64_t",
    "f_deal_bal": "int64_t",
    "f_exp_cet_intr": "int64_t",
    "credit_repay_unfrz": "int64_t",
    "all_fee_unfrz": "int64_t",
    "market": "int32_t",
}

CreditShortsellDetail = {
    "account_id": "char",
    "account_type": "int16_t",
    "symbol": "char",
    "name": "char",
    "order_id": "char",
    "currency_type": "int16_t",
    "debt_status": "int16_t",
    "occur_date": "int32_t",
    "total_qty": "int64_t",
    "cur_qty": "int64_t",
    "total_interest_fee": "int64_t",
    "cur_interest_fee": "int64_t",
    "interest_rate": "int64_t",
    "d_stk_bal": "int64_t",
    "market": "int32_t",
    "all_fee_unfrz": "int64_t",
    "stk_repay_unfrz": "int64_t",
    "end_date": "int32_t",
}

CreditRepayAmountDetail = {
    "account_id": "char",
    "account_type": "int16_t",
    "max_back_amt": "int64_t",
}

CreditRepayStockDetail = {
    "account_id": "char",
    "account_type": "int16_t",
    "symbol": "char",
    "name": "char",
    "total_qty": "int64_t",
    "max_back_qty": "int64_t",
    "returned_qty": "int64_t",
}

CreditMortgageHoldDetail = {
    "account_id": "char",
    "account_type": "int16_t",
    "symbol": "char",
    "name": "char",
    "currency_type": "int16_t",
    "pledge_rate": "int64_t",
}

CreditSecuritySellQtyRsp = {
    "account_id": "char",
    "account_type": "int16_t",
    "symbol": "char",
    "total_qty": "int64_t",
    "avail_qty": "int64_t",
}

OptionCashDetail = {
    "account_id": "char",
    "account_type": "int16_t",
    "currency_type": "int16_t",
    "init_amount": "int64_t",
    "total_amount": "int64_t",
    "avail_amount": "int64_t",
    "fetch_amount": "int64_t",
    "frozen_amount": "int64_t",
    "used_margin": "int64_t",
    "exercise_frozen": "int64_t",
    "deposit_amount": "int64_t",
    "withdraw_amount": "int64_t",
    "royalty_in": "int64_t",
    "royalty_out": "int64_t",
    "commission": "int64_t",
    "frozen_commission": "int64_t",
}

OptionPositionDetail = {
    "account_id": "char",
    "account_type": "int16_t",
    "symbol": "char",
    "side": "int16_t",
    "init_volume": "int64_t",
    "init_avail_volume": "int64_t",
    "init_comb_volume": "int64_t",
    "volume": "int64_t",
    "avail_volume": "int64_t",
    "comb_volume": "int64_t",
    "open_volume": "int64_t",
    "close_volume": "int64_t",
    "exercise_frozen": "int64_t",
    "buy_cost": "int64_t",
    "secuid": "char",
}

ExerciseReq = {
    "cl_order_id": "char",
    "symbol": "char",
    "volume": "int64_t",
    "exercise_type": "int16_t",
}

ExerciseRsp = {
    "account_id": "char",
    "account_type": "int16_t",
    "cl_order_id": "char",
    "order_id": "char",
    "exercise_type": "int16_t",
}

CancelExerciseReq = {
    "order_id": "char",
    "cl_order_id": "char",
    "cl_cancel_id": "char",
}

CancelExerciseRsp = {
    "account_id": "char",
    "account_type": "int16_t",
    "order_id": "char",
    "cl_order_id": "char",
    "cl_cancel_id": "char",
}

ExerciseDetail = {
    "account_id": "char",
    "account_type": "int16_t",
    "exercise_type": "int16_t",
    "cl_order_id": "char",
    "order_id": "char",
    "counter_order_date": "int32_t",
    "counter_order_time": "int32_t",
    "counter_cancel_time": "int32_t",
    "exercise_status": "int32_t",
    "oper_status": "int32_t",
    "symbol": "char",
    "volume": "int32_t",
    "cancel_volume": "int32_t",
    "err_code": "int32_t",
    "err_msg": "char",
}

ContractInfo = {
    "contract_id": "char",
    "exch_contract_id": "char",
    "contract_name": "char",
    "underlying_contract_id": "char",
    "underlying_contract_name": "char",
    "underlying_multiplier": "int32_t",
    "strike_mode": "int32_t",
    "options_type": "int32_t",
    "order_unit": "int32_t",
    "buy_trading_unit": "int32_t",
    "sell_trading_unit": "int32_t",
    "max_market_order_buy_volume": "int32_t",
    "min_market_order_buy_volume": "int32_t",
    "max_limit_order_buy_volume": "int32_t",
    "min_limit_order_buy_volume": "int32_t",
    "max_market_order_sell_volume": "int32_t",
    "min_market_order_sell_volume": "int32_t",
    "max_limit_order_sell_volume": "int32_t",
    "min_limit_order_sell_volume": "int32_t",
    "volume_multiplier": "int32_t",
    "price_tick": "int64_t",
    "contract_status": "int32_t",
    "strike_price": "int64_t",
    "first_date": "int32_t",
    "last_date": "int32_t",
    "strike_date": "int32_t",
    "expire_date": "int32_t",
    "deliv_date": "int32_t",
    "is_up_down_limit": "int32_t",
    "margin_unit": "int64_t",
    "pre_settlement_price": "int64_t",
    "pre_close_price": "int64_t",
    "underlying_pre_close_price": "int64_t",
}

TransferStockReq = {
    "symbol": "char",
    "transfer_type": "int16_t",
    "transfer_side": "int16_t",
    "transfer_qty": "int64_t",
}

TransferStockRsp = {
    "account_id": "char",
    "account_type": "int16_t",
    "symbol": "char",
    "transfer_type": "int16_t",
    "transfer_side": "int16_t",
    "transfer_qty": "int64_t",
}

TransferStockDetail = {
    "account_id": "char",
    "account_type": "int16_t",
    "serial_number": "char",
    "symbol": "char",
    "transact_date": "int32_t",
    "transact_time": "int32_t",
    "transfer_type": "int16_t",
    "transfer_side": "int16_t",
    "transfer_status": "int16_t",
    "yesterday_volume": "int64_t",
    "today_bs_volume": "int64_t",
    "today_pr_volume": "int64_t",
    "stock_cust_id": "char",
    "stock_secuid": "char",
    "status_msg": "char",
}

LockOrderReq = {
    "cl_order_id": "char",
    "symbol": "char",
    "lock_type": "int16_t",
    "volume": "int64_t",
}

LockOrderRsp = {
    "account_id": "char",
    "account_type": "int16_t",
    "lock_type": "int16_t",
    "order_id": "char",
    "cl_order_id": "char",
}

LockOrderDetail = {
    "account_id": "char",
    "account_type": "int16_t",
    "symbol": "char",
    "cl_order_id": "char",
    "order_id": "char",
    "order_date": "int32_t",
    "order_time": "int32_t",
    "cancel_time": "int32_t",
    "lock_type": "int16_t",
    "lock_status": "int16_t",
    "volume": "int64_t",
    "cancel_volume": "int64_t",
    "err_code": "int32_t",
    "err_msg": "char",
}

CombOrderReq = {
    "cl_order_id": "char",
    "symbol": "char",
    "comb_type": "int16_t",
    "comb_strategy": "int16_t",
    "volume": "int64_t",
    "exch_comb_id": "char",
}

CombOrderRsp = {
    "account_id": "char",
    "account_type": "int16_t",
    "comb_type": "int16_t",
    "order_id": "char",
    "cl_order_id": "char",
}

CombExerciseReq = {
    "cl_order_id": "char",
    "call_symbol": "char",
    "put_symbol": "char",
    "volume": "int64_t",
}

CombExerciseRsp = {
    "account_id": "char",
    "account_type": "int16_t",
    "cl_order_id": "char",
    "order_id": "char",
}

CancelCombExerciseReq = {
    "order_id": "char",
    "cl_order_id": "char",
    "cl_cancel_id": "char",
}

CancelCombExerciseRsp = {
    "account_id": "char",
    "account_type": "int16_t",
    "order_id": "char",
    "cl_order_id": "char",
    "cl_cancel_id": "char",
}

CombOrderDetail = {
    "account_id": "char",
    "account_type": "int16_t",
    "symbol": "char",
    "exch_comb_id": "char",
    "comb_type": "int16_t",
    "comb_strategy": "int16_t",
    "cl_order_id": "char",
    "order_id": "char",
    "order_date": "int32_t",
    "order_time": "int32_t",
    "cancel_time": "int32_t",
    "order_status": "int16_t",
    "oper_status": "int16_t",
    "volume": "int64_t",
    "cancel_volume": "int64_t",
    "err_code": "int32_t",
    "err_msg": "char",
}

CombExerciseDetail = {
    "account_id": "char",
    "account_type": "int16_t",
    "call_symbol": "char",
    "put_symbol": "char",
    "cl_order_id": "char",
    "order_id": "char",
    "order_date": "int32_t",
    "order_time": "int32_t",
    "cancel_time": "int32_t",
    "exercise_status": "int16_t",
    "oper_status": "int16_t",
    "volume": "int64_t",
    "cancel_volume": "int64_t",
    "err_code": "int32_t",
    "err_msg": "char",
}

CombPositionDetail = {
    "account_id": "char",
    "account_type": "int16_t",
    "symbol": "char",
    "comb_strategy": "int16_t",
    "volume": "int64_t",
    "avail_volume": "int64_t",
    "yesterday_volume": "int64_t",
    "yesterday_avail_volume": "int64_t",
    "today_volume": "int64_t",
    "today_avail_volume": "int64_t",
    "margin": "int64_t",
    "frozen_margin": "int64_t",
    "commission": "int64_t",
    "frozen_commission": "int64_t",
}

CombContractInfo = {
    "contract_id": "char",
    "comb_strategy": "int16_t",
    "leg1_contract_id": "char",
    "leg1_name": "char",
    "leg1_side": "int16_t",
    "leg2_contract_id": "char",
    "leg2_name": "char",
    "leg2_side": "int16_t",
}

LockSecurityDetail = {
    "account_id": "char",
    "account_type": "int16_t",
    "sys_date": "int32_t",
    "sno": "char",
    "symbol": "char",
    "name": "char",
    "lock_type": "int16_t",
    "used_fee_rate": "int64_t",
    "unused_fee_rate": "int64_t",
    "lock_qty": "int32_t",
    "used_qty": "int32_t",
    "back_qty": "int32_t",
    "begin_date": "int32_t",
    "back_date": "int32_t",
    "end_date": "int32_t",
}

ExtendLockSecurityReq = {
    "sys_date": "int32_t",
    "sno": "char",
    "apply_delay_days": "int32_t",
    "apply_used_fee_rate": "int64_t",
    "apply_unused_fee_rate": "int64_t",
    "apply_delay_qty": "int32_t",
    "symbol": "char",
}

LockSecurityExtensionDetail = {
    "account_id": "char",
    "account_type": "int16_t",
    "apply_date": "int32_t",
    "apply_sno": "int32_t",
    "sys_date": "int32_t",
    "sno": "char",
    "symbol": "char",
    "name": "char",
    "apply_end_date": "int32_t",
    "apply_delay_qty": "int32_t",
    "approval_used_fee_rate": "int64_t",
    "approval_unused_fee_rate": "int64_t",
    "approval_status": "int16_t",
    "approval_remark": "char",
}

TransferFundDetail = {
    "account_id": "char",
    "account_type": "int16_t",
    "serial_number": "char",
    "transact_date": "int32_t",
    "transact_time": "int32_t",
    "transfer_value": "int64_t",
    "transfer_side": "int16_t",
    "transfer_status": "int16_t",
    "remark": "char",
}
