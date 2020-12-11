void MdApi::OnLog(int32_t level, const char *source, const char *slog)
{
	gil_scoped_acquire acquire;
	this->onLog(level, source, slog);
};

void MdApi::OnDisconnect(int32_t chn)
{
	gil_scoped_acquire acquire;
	this->onDisconnect(chn);
};

void MdApi::OnSubscribe(ErrMsg *errmsg)
{
	gil_scoped_acquire acquire;
	dict error;
	{
		error["channel"] = errmsg->channel;
		error["errcode"] = errmsg->errcode;
		error["errstr"] = toUtf(errmsg->errstr);
		error["mktype"] = errmsg->mktype;
		error["datatype"] = errmsg->datatype;
		error["usize"] = errmsg->usize;
		error["codes"] = toUtf(errmsg->codes);
	}
	this->onSubscribe(error);
};

void MdApi::OnUnSubscribe(ErrMsg *errmsg)
{
	gil_scoped_acquire acquire;
	dict error;
	{
		error["channel"] = errmsg->channel;
		error["errcode"] = errmsg->errcode;
		error["errstr"] = toUtf(errmsg->errstr);
		error["mktype"] = errmsg->mktype;
		error["datatype"] = errmsg->datatype;
		error["usize"] = errmsg->usize;
		error["codes"] = toUtf(errmsg->codes);
	}
	this->onUnSubscribe(error);
};

void MdApi::OnDepthMarketData(MKtype mk_type, char *code, Stock_MarketData *dataL2)
{
	gil_scoped_acquire acquire;
	dict data;
	{
		data["nTime"] = dataL2->nTime;
		data["nStatus"] = dataL2->nStatus;
		data["uPreClose"] = dataL2->uPreClose;
		data["uOpen"] = dataL2->uOpen;
		data["uHigh"] = dataL2->uHigh;
		data["uLow"] = dataL2->uLow;
		data["uMatch"] = dataL2->uMatch;
		data["uAskPrice"] = dataL2->uAskPrice;
		data["uAskVol"] = dataL2->uAskVol;
		data["uBidPrice"] = dataL2->uBidPrice;
		data["uBidVol"] = dataL2->uBidVol;
		data["uNumTrades"] = dataL2->uNumTrades;
		data["iVolume"] = dataL2->iVolume;
		data["iTurnover"] = dataL2->iTurnover;
		data["iTotalBidVol"] = dataL2->iTotalBidVol;
		data["iTotalAskVol"] = dataL2->iTotalAskVol;
		data["uWeightedAvgBidPrice"] = dataL2->uWeightedAvgBidPrice;
		data["uWeightedAvgAskPrice"] = dataL2->uWeightedAvgAskPrice;
		data["nIOPV"] = dataL2->nIOPV;
		data["nYieldToMaturity"] = dataL2->nYieldToMaturity;
		data["uHighLimited"] = dataL2->uHighLimited;
		data["uLowLimited"] = dataL2->uLowLimited;
		data["sPrefix"] = toUtf(dataL2->sPrefix);
		data["nSyl1"] = dataL2->nSyl1;
		data["nSyl2"] = dataL2->nSyl2;
		data["nSD2"] = dataL2->nSD2;
		data["sTradingPhraseCode"] = toUtf(dataL2->sTradingPhraseCode);
		data["nPreIOPV"] = dataL2->nPreIOPV;
	}
	this->onDepthMarketData(mk_type, code, data);
};

void MdApi::OnMarketData(MKtype mk_type, char *code, StockMarketDataL1 *dataL1)
{
	gil_scoped_acquire acquire;
	dict data;
	{
		data["nTime"] = dataL1->nTime;
		data["nStatus"] = dataL1->nStatus;
		data["uPreClose"] = dataL1->uPreClose;
		data["uOpen"] = dataL1->uOpen;
		data["uHigh"] = dataL1->uHigh;
		data["uLow"] = dataL1->uLow;
		data["uMatch"] = dataL1->uMatch;
		data["uAskPrice"] = dataL1->uAskPrice;
		data["uAskVol"] = dataL1->uAskVol;
		data["uBidPrice"] = dataL1->uBidPrice;
		data["uBidVol"] = dataL1->uBidVol;
		data["uNumTrades"] = dataL1->uNumTrades;
		data["iVolume"] = dataL1->iVolume;
		data["iTurnover"] = dataL1->iTurnover;
		data["uHighLimited"] = dataL1->uHighLimited;
		data["uLowLimited"] = dataL1->uLowLimited;
		data["sTradingPhraseCode"] = toUtf(dataL1->sTradingPhraseCode);
		data["nPreIOPV"] = dataL1->nPreIOPV;
		data["nIOPV"] = dataL1->nIOPV;
	}
	this->onMarketData(mk_type, code, data);
};

void MdApi::OnIndexData(MKtype mk_type, char *code, Stock_IndexData *stockindex)
{
	gil_scoped_acquire acquire;
	dict data;
	{
		data["nTime"] = stockindex->nTime;
		data["nOpenIndex"] = stockindex->nOpenIndex;
		data["nHighIndex"] = stockindex->nHighIndex;
		data["nLowIndex"] = stockindex->nLowIndex;
		data["nLastIndex"] = stockindex->nLastIndex;
		data["iTotalVolume"] = stockindex->iTotalVolume;
		data["iTurnover"] = stockindex->iTurnover;
		data["nPreCloseIndex"] = stockindex->nPreCloseIndex;
	}
	this->onIndexData(mk_type, code, data);
};

void MdApi::OnOrderQueue(MKtype mk_type, char *code, StockOrderQueue *orderqueue)
{
	gil_scoped_acquire acquire;
	dict data;
	{
		data["tHead"] = orderqueue->tHead;
		data["tItem"] = orderqueue->tItem;
	}
	this->onOrderQueue(mk_type, code, data);
};

void MdApi::OnSHTrade(char *code, t_SH_StockStepTrade *steptrade)
{
	gil_scoped_acquire acquire;
	dict data;
	{
		data["nTradeIndex"] = steptrade->nTradeIndex;
		data["nTradeChannel"] = steptrade->nTradeChannel;
		data["nTradeTime"] = steptrade->nTradeTime;
		data["nTradePrice"] = steptrade->nTradePrice;
		data["iTradeQty"] = steptrade->iTradeQty;
		data["iTradeMoney"] = steptrade->iTradeMoney;
		data["iTradeBuyNo"] = steptrade->iTradeBuyNo;
		data["iTradeSellNo"] = steptrade->iTradeSellNo;
		data["cTradeBSflag"] = toUtf(steptrade->cTradeBSflag);
		data["sRes"] = toUtf(steptrade->sRes);
	}
	this->onSHTrade(code, data);
};

void MdApi::OnSZTrade(char *code, T_SZ_STEPTRADE *steptrade)
{
	gil_scoped_acquire acquire;
	dict data;
	{
		data["usChannelNo"] = steptrade->usChannelNo;
		data["i64ApplSeqNum"] = steptrade->i64ApplSeqNum;
		data["sMDStreamID"] = toUtf(steptrade->sMDStreamID);
		data["i64BidApplSeqNum"] = steptrade->i64BidApplSeqNum;
		data["i64OfferApplSeqNum"] = steptrade->i64OfferApplSeqNum;
		data["sSecurityID"] = toUtf(steptrade->sSecurityID);
		data["sSecurityIDSource"] = toUtf(steptrade->sSecurityIDSource);
		data["i64LastPx"] = steptrade->i64LastPx;
		data["i64LastQty"] = steptrade->i64LastQty;
		data["cExecType"] = toUtf(steptrade->cExecType);
		data["i64TransactTime"] = steptrade->i64TransactTime;
		data["sExtendFields"] = toUtf(steptrade->sExtendFields);
	}
	this->onSZTrade(code, data);
};

void MdApi::OnSZOrder(char *code, T_SZ_STEPORDER *steporder)
{
	gil_scoped_acquire acquire;
	dict data;
	{
		data["usChannelNo"] = steporder->usChannelNo;
		data["i64ApplSeqNum"] = steporder->i64ApplSeqNum;
		data["sMDStreamID"] = toUtf(steporder->sMDStreamID);
		data["sSecurityID"] = toUtf(steporder->sSecurityID);
		data["sSecurityIDSource"] = toUtf(steporder->sSecurityIDSource);
		data["i64Price"] = steporder->i64Price;
		data["i64OrderQty"] = steporder->i64OrderQty;
		data["cSide"] = toUtf(steporder->cSide);
		data["i64TransactTime"] = steporder->i64TransactTime;
		data["sExtendFields"] = toUtf(steporder->sExtendFields);
	}
	this->onSZOrder(code, data);
};

void MdApi::OnSHBaseInfo(char *code, T_SH_BaseInfo *baseinfodata)
{
	gil_scoped_acquire acquire;
	dict data;
	{
		data["szStkCode"] = toUtf(baseinfodata->szStkCode);
		data["szISIN"] = toUtf(baseinfodata->szISIN);
		data["uUpdateTime"] = baseinfodata->uUpdateTime;
		data["szStkNameZN"] = toUtf(baseinfodata->szStkNameZN);
		data["szStkNameEn"] = toUtf(baseinfodata->szStkNameEn);
		data["szUnderlyingCode"] = toUtf(baseinfodata->szUnderlyingCode);
		data["szMktClass"] = toUtf(baseinfodata->szMktClass);
		data["szStkClass"] = toUtf(baseinfodata->szStkClass);
		data["szStkSubClass"] = toUtf(baseinfodata->szStkSubClass);
		data["szCurrency"] = toUtf(baseinfodata->szCurrency);
		data["i64FaceValue"] = baseinfodata->i64FaceValue;
		data["i64MatchQty"] = baseinfodata->i64MatchQty;
		data["szLastDate"] = toUtf(baseinfodata->szLastDate);
		data["uListingData"] = baseinfodata->uListingData;
		data["uProductSETId"] = baseinfodata->uProductSETId;
		data["i64BuyNumUnit"] = baseinfodata->i64BuyNumUnit;
		data["i64SellNumUnit"] = baseinfodata->i64SellNumUnit;
		data["i64DecalaredLowestNum"] = baseinfodata->i64DecalaredLowestNum;
		data["i64DecalaredHightestNum"] = baseinfodata->i64DecalaredHightestNum;
		data["i64PreClosePrice"] = baseinfodata->i64PreClosePrice;
		data["i64PriceLevel"] = baseinfodata->i64PriceLevel;
		data["cPriceLimitsType"] = toUtf(baseinfodata->cPriceLimitsType);
		data["i64UpLimitsPrice"] = baseinfodata->i64UpLimitsPrice;
		data["i64LowerLimitPrice"] = baseinfodata->i64LowerLimitPrice;
		data["i64DividendRatio"] = baseinfodata->i64DividendRatio;
		data["i64DividendAmount"] = baseinfodata->i64DividendAmount;
		data["cFinaSubjectFlag"] = toUtf(baseinfodata->cFinaSubjectFlag);
		data["cMarginSubjectFlag"] = toUtf(baseinfodata->cMarginSubjectFlag);
		data["szProdStatusFlag"] = toUtf(baseinfodata->szProdStatusFlag);
		data["i64MPDecalaredLowestNum"] = baseinfodata->i64MPDecalaredLowestNum;
		data["i64MPDecalaredHightestNum"] = baseinfodata->i64MPDecalaredHightestNum;
		data["szStkNameZNLong"] = toUtf(baseinfodata->szStkNameZNLong);
		data["szNote"] = toUtf(baseinfodata->szNote);
	}
	this->onSHBaseInfo(code, data);
};

void MdApi::OnKline(MKtype mk_type, char *code, T_Kline *kline)
{
	gil_scoped_acquire acquire;
	dict data;
	{
		data["uDay"] = kline->uDay;
		data["nTime"] = kline->nTime;
		data["nPreClose"] = kline->nPreClose;
		data["nValOpen"] = kline->nValOpen;
		data["nValHigh"] = kline->nValHigh;
		data["nValLow"] = kline->nValLow;
		data["nValClose"] = kline->nValClose;
		data["i64Volume"] = kline->i64Volume;
		data["i64ValTotal"] = kline->i64ValTotal;
		data["i64TotalVol"] = kline->i64TotalVol;
		data["i64TotalTurnOver"] = kline->i64TotalTurnOver;
		data["nTurover"] = kline->nTurover;
		data["nValIncrease"] = kline->nValIncrease;
	}
	this->onKline(mk_type, code, data);
};

void MdApi::OnEtfExtData(MKtype mk_type, char *code, T_ETFEXTENDS *etfextdata)
{
	gil_scoped_acquire acquire;
	dict data;
	{
		data["nTime"] = etfextdata->nTime;
		data["nIOPV"] = etfextdata->nIOPV;
		data["nEtfBuyNum"] = etfextdata->nEtfBuyNum;
		data["i64EtfBuyAmount"] = etfextdata->i64EtfBuyAmount;
		data["i64EtfBuyMoney"] = etfextdata->i64EtfBuyMoney;
		data["nEtfSellNum"] = etfextdata->nEtfSellNum;
		data["i64EtfSellAmount"] = etfextdata->i64EtfSellAmount;
		data["i64EtfSellMoney"] = etfextdata->i64EtfSellMoney;
		data["nWithDrawBuyNum"] = etfextdata->nWithDrawBuyNum;
		data["i64WithDrawBuyAmount"] = etfextdata->i64WithDrawBuyAmount;
		data["i64WithDrawBuyMoney"] = etfextdata->i64WithDrawBuyMoney;
		data["nWithDrawSellNum"] = etfextdata->nWithDrawSellNum;
		data["i64WithDrawSellAmount"] = etfextdata->i64WithDrawSellAmount;
		data["i64WithDrawSellMoney"] = etfextdata->i64WithDrawSellMoney;
	}
	this->onEtfExtData(mk_type, code, data);
};

