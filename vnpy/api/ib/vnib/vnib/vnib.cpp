// vnctpmd.cpp : 定义 DLL 应用程序的导出函数。
//

#include "StdAfx.h"
#include "vnib.h"

#include "Contract.h"
#include "OrderState.h"
#include "Execution.h"
#include "CommissionReport.h"
#include "ScannerSubscription.h"
#include "TagValue.h"
#include "Order.h"


///-------------------------------------------------------------------------------------
///C++的回调函数将数据保存到队列中
///-------------------------------------------------------------------------------------

void IbWrapper::tickPrice(TickerId tickerId, TickType field, double price, int canAutoExecute)
{
	PyLock lock;
	this->api->tickPrice(tickerId, field, price, canAutoExecute);
};

void IbWrapper::tickSize(TickerId tickerId, TickType field, int size)
{
	PyLock lock;
	this->api->tickSize(tickerId, field, size);
};

void IbWrapper::tickOptionComputation(TickerId tickerId, TickType tickType, double impliedVol, double delta, double optPrice, double pvDividend, double gamma, double vega, double theta, double undPrice)
{
	PyLock lock;
	this->api->tickOptionComputation(tickerId, tickType, impliedVol, delta, optPrice, pvDividend, gamma, vega, theta, undPrice);
};

void IbWrapper::tickGeneric(TickerId tickerId, TickType tickType, double value)
{
	PyLock lock;
	this->api->tickGeneric(tickerId, tickType, value);
};

void IbWrapper::tickString(TickerId tickerId, TickType tickType, const std::string& value)
{
	PyLock lock;
	this->api->tickString(tickerId, tickType, value);
};

void IbWrapper::tickEFP(TickerId tickerId, TickType tickType, double basisPoints, const std::string& formattedBasisPoints, double totalDividends, int holdDays, const std::string& futureLastTradeDate, double dividendImpact, double dividendsToLastTradeDate)
{
	PyLock lock;
	this->api->tickEFP(tickerId, tickType, basisPoints, formattedBasisPoints, totalDividends, holdDays, futureLastTradeDate, dividendImpact, dividendsToLastTradeDate);
};

void IbWrapper::orderStatus(OrderId orderId, const std::string& status, double filled, double remaining, double avgFillPrice, int permId, int parentId, double lastFillPrice, int clientId, const std::string& whyHeld)
{
	PyLock lock;
	this->api->orderStatus(orderId, status, filled, remaining, avgFillPrice, permId, parentId, lastFillPrice, clientId, whyHeld);
};

void IbWrapper::openOrder(OrderId orderId, const Contract& contract, const Order& order, const OrderState& orderState)
{
	PyLock lock;
	this->api->openOrder(orderId, contract, order, orderState);
};

void IbWrapper::openOrderEnd()
{
	PyLock lock;
	this->api->openOrderEnd();
};

void IbWrapper::winError(const std::string& str, int lastError)
{
	PyLock lock;
	this->api->winError(str, lastError);
};

void IbWrapper::connectionClosed()
{
	PyLock lock;
	this->api->connectionClosed();
};

void IbWrapper::updateAccountValue(const std::string& key, const std::string& val, const std::string& currency, const std::string& accountName)
{
	PyLock lock;
	this->api->updateAccountValue(key, val, currency, accountName);
};

void IbWrapper::updatePortfolio(const Contract& contract, double position, double marketPrice, double marketValue, double averageCost, double unrealizedPNL, double realizedPNL, const std::string& accountName)
{
	PyLock lock;
	this->api->updatePortfolio(contract, position, marketPrice, marketValue, averageCost, unrealizedPNL, realizedPNL, accountName);
};

void IbWrapper::updateAccountTime(const std::string& timeStamp)
{
	PyLock lock;
	this->api->updateAccountTime(timeStamp);
};

void IbWrapper::accountDownloadEnd(const std::string& accountName)
{
	PyLock lock;
	this->api->accountDownloadEnd(accountName);
};

void IbWrapper::nextValidId(OrderId orderId)
{
	PyLock lock;
	this->api->nextValidId(orderId);
};

void IbWrapper::contractDetails(int reqId, const ContractDetails& contractDetails)
{
	PyLock lock;
	this->api->contractDetails(reqId, contractDetails);
};

void IbWrapper::bondContractDetails(int reqId, const ContractDetails& contractDetails)
{
	PyLock lock;
	this->api->bondContractDetails(reqId, contractDetails);
};

void IbWrapper::contractDetailsEnd(int reqId)
{
	PyLock lock;
	this->api->contractDetailsEnd(reqId);
};

void IbWrapper::execDetails(int reqId, const Contract& contract, const Execution& execution)
{
	PyLock lock;
	this->api->execDetails(reqId, contract, execution);
};

void IbWrapper::execDetailsEnd(int reqId)
{
	PyLock lock;
	this->api->execDetailsEnd(reqId);
};

void IbWrapper::error(const int id, const int errorCode, const std::string errorString)
{
	PyLock lock;
	this->api->error(id, errorCode, errorString);
};

void IbWrapper::updateMktDepth(TickerId id, int position, int operation, int side, double price, int size)
{
	PyLock lock;
	this->api->updateMktDepth(id, position, operation, side, price, size);
};

void IbWrapper::updateMktDepthL2(TickerId id, int position, std::string marketMaker, int operation, int side, double price, int size)
{
	PyLock lock;
	this->api->updateMktDepthL2(id, position, marketMaker, operation, side, price, size);
};

void IbWrapper::updateNewsBulletin(int msgId, int msgType, const std::string& newsMessage, const std::string& originExch)
{
	PyLock lock;
	this->api->updateNewsBulletin(msgId, msgType, newsMessage, originExch);
};

void IbWrapper::managedAccounts(const std::string& accountsList)
{
	PyLock lock;
	this->api->managedAccounts(accountsList);
};

void IbWrapper::receiveFA(faDataType pFaDataType, const std::string& cxml)
{
	PyLock lock;
	this->api->receiveFA(pFaDataType, cxml);
};

void IbWrapper::historicalData(TickerId reqId, const std::string& date, double open, double high, double low, double close, int volume, int barCount, double WAP, int hasGaps)
{
	PyLock lock;
	this->api->historicalData(reqId, date, open, high, low, close, volume, barCount, WAP, hasGaps);
};

void IbWrapper::scannerParameters(const std::string& xml)
{
	PyLock lock;
	this->api->scannerParameters(xml);
};

void IbWrapper::scannerData(int reqId, int rank, const ContractDetails& contractDetails, const std::string& distance, const std::string& benchmark, const std::string& projection, const std::string& legsStr)
{
	PyLock lock;
	this->api->scannerData(reqId, rank, contractDetails, distance, benchmark, projection, legsStr);
};

void IbWrapper::scannerDataEnd(int reqId)
{
	PyLock lock;
	this->api->scannerDataEnd(reqId);
};

void IbWrapper::realtimeBar(TickerId reqId, long time, double open, double high, double low, double close, long volume, double wap, int count)
{
	PyLock lock;
	this->api->realtimeBar(reqId, time, open, high, low, close, volume, wap, count);
};

void IbWrapper::currentTime(long time)
{
	PyLock lock;
	this->api->currentTime(time);
};

void IbWrapper::fundamentalData(TickerId reqId, const std::string& data)
{
	PyLock lock;
	this->api->fundamentalData(reqId, data);
};

void IbWrapper::deltaNeutralValidation(int reqId, const UnderComp& underComp)
{
	PyLock lock;
	this->api->deltaNeutralValidation(reqId, underComp);
};

void IbWrapper::tickSnapshotEnd(int reqId)
{
	PyLock lock;
	this->api->tickSnapshotEnd(reqId);
};

void IbWrapper::marketDataType(TickerId reqId, int marketDataType)
{
	PyLock lock;
	this->api->marketDataType(reqId, marketDataType);
};

void IbWrapper::commissionReport(const CommissionReport& commissionReport)
{
	PyLock lock;
	this->api->commissionReport(commissionReport);
};

void IbWrapper::position(const std::string& account, const Contract& contract, double position, double avgCost)
{
	PyLock lock;
	this->api->position(account, contract, position, avgCost);
};

void IbWrapper::positionEnd()
{
	PyLock lock;
	this->api->positionEnd();
};

void IbWrapper::accountSummary(int reqId, const std::string& account, const std::string& tag, const std::string& value, const std::string& curency)
{
	PyLock lock;
	this->api->accountSummary(reqId, account, tag, value, curency);
};

void IbWrapper::accountSummaryEnd(int reqId)
{
	PyLock lock;
	this->api->accountSummaryEnd(reqId);
};

void IbWrapper::verifyMessageAPI(const std::string& apiData)
{
	PyLock lock;
	this->api->verifyMessageAPI(apiData);
};

void IbWrapper::verifyCompleted(bool isSuccessful, const std::string& errorText)
{
	PyLock lock;
	this->api->verifyCompleted(isSuccessful, errorText);
};

void IbWrapper::displayGroupList(int reqId, const std::string& groups)
{
	PyLock lock;
	this->api->displayGroupList(reqId, groups);
};

void IbWrapper::displayGroupUpdated(int reqId, const std::string& contractInfo)
{
	PyLock lock;
	this->api->displayGroupUpdated(reqId, contractInfo);
};

void IbWrapper::verifyAndAuthMessageAPI(const std::string& apiData, const std::string& xyzChallange)
{
	PyLock lock;
	this->api->verifyAndAuthMessageAPI(apiData, xyzChallange);
};

void IbWrapper::verifyAndAuthCompleted(bool isSuccessful, const std::string& errorText)
{
	PyLock lock;
	this->api->verifyAndAuthCompleted(isSuccessful, errorText);
};

void IbWrapper::connectAck()
{
	PyLock lock;
	this->api->connectAck();
};

void IbWrapper::positionMulti(int reqId, const std::string& account, const std::string& modelCode, const Contract& contract, double pos, double avgCost)
{
	PyLock lock;
	this->api->positionMulti(reqId, account, modelCode, contract, pos, avgCost);
};

void IbWrapper::positionMultiEnd(int reqId)
{
	PyLock lock;
	this->api->positionMultiEnd(reqId);
}

void IbWrapper::accountUpdateMulti(int reqId, const std::string& account, const std::string& modelCode, const std::string& key, const std::string& value, const std::string& currency)
{
	PyLock lock;
	this->api->accountUpdateMulti(reqId, account, modelCode, key, value, currency);
};

void IbWrapper::accountUpdateMultiEnd(int reqId)
{
	PyLock lock;
	this->api->accountUpdateMultiEnd(reqId);
}

void IbWrapper::securityDefinitionOptionalParameter(int reqId, const std::string& exchange, int underlyingConId, const std::string& tradingClass, const std::string& multiplier, std::set<std::string> expirations, std::set<double> strikes)
{
	PyLock lock;

	//这里因为boost.python中没有提供std::set的封装，因此选择转化成vector
	std::vector<std::string> expirationsVector(expirations.begin(), expirations.end());
	std::vector<double> strikesVector(strikes.begin(), strikes.end());

	this->api->securityDefinitionOptionalParameter(reqId, exchange, underlyingConId, tradingClass, multiplier, expirationsVector, strikesVector);
};

void IbWrapper::securityDefinitionOptionalParameterEnd(int reqId)
{
	PyLock lock;
	this->api->securityDefinitionOptionalParameterEnd(reqId);
};

void IbWrapper::softDollarTiers(int reqId, const std::vector<SoftDollarTier> &tiers)
{
	PyLock lock;
	this->api->softDollarTiers(reqId, tiers);
};

///-------------------------------------------------------------------------------------
///负责调用processMsgs的线程工作函数
///-------------------------------------------------------------------------------------
void VnIbApi::run()
{
	while (this->client->isConnected())
	{
		this->reader->checkClient();
		signal.waitForSignal();
		this->reader->processMsgs();
	}
};


///-------------------------------------------------------------------------------------
///主动函数
///-------------------------------------------------------------------------------------

bool VnIbApi::eConnect(string host, int port, int clientId, bool extraAuth)
{
	bool r = this->client->eConnect(host.c_str(), port, clientId, extraAuth);

	if (r)
	{
		//启动EReader从socket读取信息
		this->reader = new EReader(this->client, &this->signal);
		this->reader->start();

		//启动数据推送线程
		function0<void> f = boost::bind(&VnIbApi::run, this);
		thread t(f);
		this->worker = &t;
	};

	return r;
};

void VnIbApi::eDisconnect()
{
	this->client->eDisconnect();
};

std::string VnIbApi::TwsConnectionTime()
{
	return this->client->TwsConnectionTime();
};

void VnIbApi::reqMktData(TickerId id, const Contract& contract, const std::string& genericTicks, bool snapshot, const TagValueListSPtr& mktDataOptions)
{
	this->client->reqMktData(id, contract, genericTicks, snapshot, mktDataOptions);
};

void VnIbApi::cancelMktData(TickerId id)
{
	this->client->cancelMktData(id);
};

void VnIbApi::placeOrder(OrderId id, const Contract& contract, const Order& order)
{
	this->client->placeOrder(id, contract, order);
};

void VnIbApi::cancelOrder(OrderId id)
{
	this->client->cancelOrder(id);
};

void VnIbApi::reqOpenOrders()
{
	this->client->reqOpenOrders();
};

void VnIbApi::reqAccountUpdates(bool subscribe, const std::string& acctCode)
{
	this->client->reqAccountUpdates(subscribe, acctCode);
};

void VnIbApi::reqExecutions(int reqId, const ExecutionFilter& filter)
{
	this->client->reqExecutions(reqId, filter);
};

void VnIbApi::reqIds(int numIds)
{
	this->client->reqIds(numIds);
};

void VnIbApi::reqContractDetails(int reqId, const Contract& contract)
{
	this->client->reqContractDetails(reqId, contract);
};

void VnIbApi::reqMktDepth(TickerId tickerId, const Contract& contract, int numRows, const TagValueListSPtr& mktDepthOptions)
{
	this->client->reqMktDepth(tickerId, contract, numRows, mktDepthOptions);
};

void VnIbApi::cancelMktDepth(TickerId tickerId)
{
	this->client->cancelMktDepth(tickerId);
};

void VnIbApi::reqNewsBulletins(bool allMsgs)
{
	this->client->reqNewsBulletins(allMsgs);
};

void VnIbApi::cancelNewsBulletins()
{
	this->client->cancelNewsBulletins();
};

void VnIbApi::setServerLogLevel(int level)
{
	this->client->setServerLogLevel(level);
};

void VnIbApi::reqAutoOpenOrders(bool bAutoBind)
{
	this->client->reqAutoOpenOrders(bAutoBind);
};

void VnIbApi::reqAllOpenOrders()
{
	this->client->reqAllOpenOrders();
};

void VnIbApi::reqManagedAccts()
{
	this->client->reqManagedAccts();
};

void VnIbApi::requestFA(faDataType pFaDataType)
{
	this->client->requestFA(pFaDataType);
};

void VnIbApi::replaceFA(faDataType pFaDataType, const std::string& cxml)
{
	this->client->replaceFA(pFaDataType, cxml);
};

void VnIbApi::reqHistoricalData(TickerId id, const Contract& contract, const std::string& endDateTime, const std::string& durationStr, const std::string&  barSizeSetting, const std::string& whatToShow, int useRTH, int formatDate, const TagValueListSPtr& chartOptions)
{
	this->client->reqHistoricalData(id, contract, endDateTime, durationStr, barSizeSetting, whatToShow, useRTH, formatDate, chartOptions);
};

void VnIbApi::exerciseOptions(TickerId tickerId, const Contract& contract, int exerciseAction, int exerciseQuantity, const std::string& account, int override)
{
	this->client->exerciseOptions(tickerId, contract, exerciseAction, exerciseQuantity, account, override);
};

void VnIbApi::cancelHistoricalData(TickerId tickerId)
{
	this->client->cancelHistoricalData(tickerId);
};

void VnIbApi::reqRealTimeBars(TickerId id, const Contract& contract, int barSize, const std::string& whatToShow, bool useRTH, const TagValueListSPtr& realTimeBarsOptions)
{
	this->client->reqRealTimeBars(id, contract, barSize, whatToShow, useRTH, realTimeBarsOptions);
};

void VnIbApi::cancelRealTimeBars(TickerId tickerId)
{
	this->client->cancelRealTimeBars(tickerId);
};

void VnIbApi::cancelScannerSubscription(int tickerId)
{
	this->client->cancelScannerSubscription(tickerId);
};

void VnIbApi::reqScannerParameters()
{
	this->client->reqScannerParameters();
};

void VnIbApi::reqScannerSubscription(int tickerId, const ScannerSubscription& subscription, const TagValueListSPtr& scannerSubscriptionOptions)
{
	this->client->reqScannerSubscription(tickerId, subscription, scannerSubscriptionOptions);
};

void VnIbApi::reqCurrentTime()
{
	this->client->reqCurrentTime();
};

void VnIbApi::reqFundamentalData(TickerId reqId, const Contract& contract, const std::string& reportType)
{
	this->client->reqFundamentalData(reqId, contract, reportType);
};

void VnIbApi::cancelFundamentalData(TickerId reqId)
{
	this->client->cancelFundamentalData(reqId);
};

void VnIbApi::calculateImpliedVolatility(TickerId reqId, const Contract& contract, double optionPrice, double underPrice)
{
	this->client->calculateImpliedVolatility(reqId, contract, optionPrice, underPrice);
};

void VnIbApi::calculateOptionPrice(TickerId reqId, const Contract& contract, double volatility, double underPrice)
{
	this->client->calculateOptionPrice(reqId, contract, volatility, underPrice);
};

void VnIbApi::cancelCalculateImpliedVolatility(TickerId reqId)
{
	this->client->cancelCalculateImpliedVolatility(reqId);
};

void VnIbApi::cancelCalculateOptionPrice(TickerId reqId)
{
	this->client->cancelCalculateOptionPrice(reqId);
};

void VnIbApi::reqGlobalCancel()
{
	this->client->reqGlobalCancel();
};

void VnIbApi::reqMarketDataType(int marketDataType)
{
	this->client->reqMarketDataType(marketDataType);
};

void VnIbApi::reqPositions()
{
	this->client->reqPositions();
};

void VnIbApi::cancelPositions()
{
	this->client->cancelPositions();
};

void VnIbApi::reqAccountSummary(int reqId, const std::string& groupName, const std::string& tags)
{
	this->client->reqAccountSummary(reqId, groupName, tags);
};

void VnIbApi::cancelAccountSummary(int reqId)
{
	this->client->cancelAccountSummary(reqId);
};

void VnIbApi::verifyRequest(const std::string& apiName, const std::string& apiVersion)
{
	this->client->verifyRequest(apiName, apiVersion);
};

void VnIbApi::verifyMessage(const std::string& apiData)
{
	this->client->verifyMessage(apiData);
};

void VnIbApi::verifyAndAuthRequest(const std::string& apiName, const std::string& apiVersion, const std::string& opaqueIsvKey)
{
	this->client->verifyAndAuthRequest(apiName, apiVersion, opaqueIsvKey);
};

void VnIbApi::verifyAndAuthMessage(const std::string& apiData, const std::string& xyzResponse)
{
	this->client->verifyAndAuthMessage(apiData, xyzResponse);
};

void VnIbApi::queryDisplayGroups(int reqId)
{
	this->client->queryDisplayGroups(reqId);
};

void VnIbApi::subscribeToGroupEvents(int reqId, int groupId)
{
	this->client->subscribeToGroupEvents(reqId, groupId);
};

void VnIbApi::updateDisplayGroup(int reqId, const std::string& contractInfo)
{
	this->client->updateDisplayGroup(reqId, contractInfo);
};

void VnIbApi::unsubscribeFromGroupEvents(int reqId)
{
	this->client->unsubscribeFromGroupEvents(reqId);
};

void VnIbApi::reqPositionsMulti(int reqId, const std::string& account, const std::string& modelCode)
{
	this->client->reqPositionsMulti(reqId, account, modelCode);
};

void VnIbApi::cancelPositionsMulti(int reqId)
{
	this->client->cancelPositionsMulti(reqId);
};

void VnIbApi::reqAccountUpdatessMulti(int reqId, const std::string& account, const std::string& modelCode, bool ledgerAndNLV)
{
	this->client->reqAccountUpdatessMulti(reqId, account, modelCode, ledgerAndNLV);
};

void VnIbApi::cancelAccountUpdatesMulti(int reqId)
{
	this->client->cancelAccountUpdatesMulti(reqId);
};

void VnIbApi::reqSecDefOptParams(int reqId, const std::string& underlyingSymbol, const std::string& futFopExchange, const std::string& underlyingSecType, int underlyingConId)
{
	this->client->reqSecDefOptParams(reqId, underlyingSymbol, futFopExchange, underlyingSecType, underlyingConId);
};

void VnIbApi::reqSoftDollarTiers(int reqId)
{
	this->client->reqSoftDollarTiers(reqId);
};

///-------------------------------------------------------------------------------------
///Boost.Python封装
///-------------------------------------------------------------------------------------

struct IbApiWrap : VnIbApi, wrapper < VnIbApi >
{

	virtual void nextValidId(OrderId orderId)
	{
		try
		{
			this->get_override("nextValidId")(orderId);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void currentTime(long time)
	{
		try
		{
			this->get_override("currentTime")(time);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void connectAck()
	{
		try
		{
			this->get_override("connectAck")();
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void error(const int id, const int errorCode, const std::string errorString)
	{
		try
		{
			this->get_override("error")(id, errorCode, errorString);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void accountSummary(int reqId, const std::string& account, const std::string& tag, const std::string& value, const std::string& curency)
	{
		try
		{
			this->get_override("accountSummary")(reqId, account, tag, value, curency);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void accountSummaryEnd(int reqId)
	{
		try
		{
			this->get_override("accountSummaryEnd")(reqId);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void tickPrice(TickerId tickerId, TickType field, double price, int canAutoExecute)
	{
		try
		{
			this->get_override("tickPrice")(tickerId, field, price, canAutoExecute);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void tickSize(TickerId tickerId, TickType field, int size)
	{
		try
		{
			this->get_override("tickSize")(tickerId, field, size);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void tickOptionComputation(TickerId tickerId, TickType tickType, double impliedVol, double delta, double optPrice, double pvDividend, double gamma, double vega, double theta, double undPrice)
	{
		try
		{
			this->get_override("tickOptionComputation")(tickerId, tickType, impliedVol, delta, optPrice, pvDividend, gamma, vega, theta, undPrice);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void tickGeneric(TickerId tickerId, TickType tickType, double value)
	{
		try
		{
			this->get_override("tickGeneric")(tickerId, tickType, value);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void tickString(TickerId tickerId, TickType tickType, const std::string& value)
	{
		try
		{
			this->get_override("tickString")(tickerId, tickType, value);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void tickEFP(TickerId tickerId, TickType tickType, double basisPoints, const std::string& formattedBasisPoints, double totalDividends, int holdDays, const std::string& futureLastTradeDate, double dividendImpact, double dividendsToLastTradeDate)
	{
		try
		{
			this->get_override("tickEFP")(tickerId, tickType, basisPoints, formattedBasisPoints, totalDividends, holdDays, futureLastTradeDate, dividendImpact, dividendsToLastTradeDate);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void orderStatus(OrderId orderId, const std::string& status, double filled, double remaining, double avgFillPrice, int permId, int parentId, double lastFillPrice, int clientId, const std::string& whyHeld)
	{
		try
		{
			this->get_override("orderStatus")(orderId, status, filled, remaining, avgFillPrice, permId, parentId, lastFillPrice, clientId, whyHeld);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void openOrder(OrderId orderId, const Contract& contract, const Order& order, const OrderState& orderState)
	{
		try
		{
			this->get_override("openOrder")(orderId, contract, order, orderState);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void openOrderEnd()
	{
		try
		{
			this->get_override("openOrderEnd")();
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void winError(const std::string& str, int lastError)
	{
		try
		{
			this->get_override("winError")(str, lastError);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void connectionClosed()
	{
		try
		{
			this->get_override("connectionClosed")();
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void updateAccountValue(const std::string& key, const std::string& val, const std::string& currency, const std::string& accountName)
	{
		try
		{
			this->get_override("updateAccountValue")(key, val, currency, accountName);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void updatePortfolio(const Contract& contract, double position, double marketPrice, double marketValue, double averageCost, double unrealizedPNL, double realizedPNL, const std::string& accountName)
	{
		try
		{
			this->get_override("updatePortfolio")(contract, position, marketPrice, marketValue, averageCost, unrealizedPNL, realizedPNL, accountName);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void updateAccountTime(const std::string& timeStamp)
	{
		try
		{
			this->get_override("updateAccountTime")(timeStamp);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void accountDownloadEnd(const std::string& accountName)
	{
		try
		{
			this->get_override("accountDownloadEnd")(accountName);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void contractDetails(int reqId, const ContractDetails& contractDetails)
	{
		try
		{
			this->get_override("contractDetails")(reqId, contractDetails);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void bondContractDetails(int reqId, const ContractDetails& contractDetails)
	{
		try
		{
			this->get_override("bondContractDetails")(reqId, contractDetails);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void contractDetailsEnd(int reqId)
	{
		try
		{
			this->get_override("contractDetailsEnd")(reqId);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void execDetails(int reqId, const Contract& contract, const Execution& execution)
	{
		try
		{
			this->get_override("execDetails")(reqId, contract, execution);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void execDetailsEnd(int reqId)
	{
		try
		{
			this->get_override("execDetailsEnd")(reqId);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void updateMktDepth(TickerId id, int position, int operation, int side, double price, int size)
	{
		try
		{
			this->get_override("updateMktDepth")(id, position, operation, side, price, size);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void updateMktDepthL2(TickerId id, int position, std::string marketMaker, int operation, int side, double price, int size)
	{
		try
		{
			this->get_override("updateMktDepthL2")(id, position, marketMaker, operation, side, price, size);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void updateNewsBulletin(int msgId, int msgType, const std::string& newsMessage, const std::string& originExch)
	{
		try
		{
			this->get_override("updateNewsBulletin")(msgId, msgType, newsMessage, originExch);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void managedAccounts(const std::string& accountsList)
	{
		try
		{
			this->get_override("managedAccounts")(accountsList);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void receiveFA(faDataType pFaDataType, const std::string& cxml)
	{
		try
		{
			this->get_override("receiveFA")(pFaDataType, cxml);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void historicalData(TickerId reqId, const std::string& date, double open, double high, double low, double close, int volume, int barCount, double WAP, int hasGaps)
	{
		try
		{
			this->get_override("historicalData")(reqId, date, open, high, low, close, volume, barCount, WAP, hasGaps);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void scannerParameters(const std::string& xml)
	{
		try
		{
			this->get_override("scannerParameters")(xml);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void scannerData(int reqId, int rank, const ContractDetails& contractDetails, const std::string& distance, const std::string& benchmark, const std::string& projection, const std::string& legsStr)
	{
		try
		{
			this->get_override("scannerData")(reqId, rank, contractDetails, distance, benchmark, projection, legsStr);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void scannerDataEnd(int reqId)
	{
		try
		{
			this->get_override("scannerDataEnd")(reqId);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void realtimeBar(TickerId reqId, long time, double open, double high, double low, double close, long volume, double wap, int count)
	{
		try
		{
			this->get_override("realtimeBar")(reqId, time, open, high, low, close, volume, wap, count);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void fundamentalData(TickerId reqId, const std::string& data)
	{
		try
		{
			this->get_override("fundamentalData")(reqId, data);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void deltaNeutralValidation(int reqId, const UnderComp& underComp)
	{
		try
		{
			this->get_override("deltaNeutralValidation")(reqId, underComp);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void tickSnapshotEnd(int reqId)
	{
		try
		{
			this->get_override("tickSnapshotEnd")(reqId);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void marketDataType(TickerId reqId, int marketDataType)
	{
		try
		{
			this->get_override("marketDataType")(reqId, marketDataType);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void commissionReport(const CommissionReport& commissionReport)
	{
		try
		{
			this->get_override("commissionReport")(commissionReport);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void position(const std::string& account, const Contract& contract, double position, double avgCost)
	{
		try
		{
			this->get_override("position")(account, contract, position, avgCost);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void positionEnd()
	{
		try
		{
			this->get_override("positionEnd")();
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void verifyMessageAPI(const std::string& apiData)
	{
		try
		{
			this->get_override("verifyMessageAPI")(apiData);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void verifyCompleted(bool isSuccessful, const std::string& errorText)
	{
		try
		{
			this->get_override("verifyCompleted")(isSuccessful, errorText);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void displayGroupList(int reqId, const std::string& groups)
	{
		try
		{
			this->get_override("displayGroupList")(reqId, groups);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void displayGroupUpdated(int reqId, const std::string& contractInfo)
	{
		try
		{
			this->get_override("displayGroupUpdated")(reqId, contractInfo);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void verifyAndAuthMessageAPI(const std::string& apiData, const std::string& xyzChallange)
	{
		try
		{
			this->get_override("verifyAndAuthMessageAPI")(apiData, xyzChallange);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void verifyAndAuthCompleted(bool isSuccessful, const std::string& errorText)
	{
		try
		{
			this->get_override("verifyAndAuthCompleted")(isSuccessful, errorText);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void positionMulti(int reqId, const std::string& account, const std::string& modelCode, const Contract& contract, double pos, double avgCost)
	{
		try
		{
			this->get_override("positionMulti")(reqId, account, modelCode, contract, pos, avgCost);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void positionMultiEnd(int reqId)
	{
		try
		{
			this->get_override("positionMultiEnd")(reqId);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void accountUpdateMulti(int reqId, const std::string& account, const std::string& modelCode, const std::string& key, const std::string& value, const std::string& currency)
	{
		try
		{
			this->get_override("accountUpdateMulti")(reqId, account, modelCode, key, value, currency);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void accountUpdateMultiEnd(int reqId)
	{
		try
		{
			this->get_override("accountUpdateMultiEnd")(reqId);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	//virtual void securityDefinitionOptionalParameter(int reqId, const std::string& exchange, int underlyingConId, const std::string& tradingClass, const std::string& multiplier, std::set<std::string> expirations, std::set<double> strikes)
	virtual void securityDefinitionOptionalParameter(int reqId, const std::string& exchange, int underlyingConId, const std::string& tradingClass, const std::string& multiplier, std::vector<std::string> expirations, std::vector<double> strikes)
	{
		try
		{
			this->get_override("securityDefinitionOptionalParameter")(reqId, exchange, underlyingConId, tradingClass, multiplier, expirations, strikes);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};

	virtual void securityDefinitionOptionalParameterEnd(int reqId)
	{
		try
		{
			this->get_override("securityDefinitionOptionalParameterEnd")(reqId);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};


	virtual void softDollarTiers(int reqId, const std::vector<SoftDollarTier> &tiers)
	{
		try
		{
			this->get_override("softDollarTiers")(reqId, tiers);
		}
		catch (error_already_set const &)
		{
			PyErr_Print();
		}
	};
};


// 将ibapi自带的智能指针注册到boost.python的环境中，让boost.python实现自动识别
namespace boost {
	namespace python {
		template <class T> struct pointee< ibapi::shared_ptr<T> >
		{
			typedef T type;
		};
	}
}

template<class T> inline T * get_pointer(ibapi::shared_ptr<T> const & p)
{
	return p.get();
}


// 封装模块
BOOST_PYTHON_MODULE(vnib)
{
	using namespace boost::python;

	//导入时运行，保证先创建GIL
	PyEval_InitThreads();	

	//API类封装
	class_<IbApiWrap, boost::noncopyable>("IbApi")
		.def("eConnect", &IbApiWrap::eConnect)
		.def("eDisconnect", &IbApiWrap::eDisconnect)
		.def("TwsConnectionTime", &IbApiWrap::TwsConnectionTime)
		.def("reqMktData", &IbApiWrap::reqMktData)
		.def("cancelMktData", &IbApiWrap::cancelMktData)
		.def("placeOrder", &IbApiWrap::placeOrder)
		.def("cancelOrder", &IbApiWrap::cancelOrder)
		.def("reqOpenOrders", &IbApiWrap::reqOpenOrders)
		.def("reqAccountUpdates", &IbApiWrap::reqAccountUpdates)
		.def("reqExecutions", &IbApiWrap::reqExecutions)
		.def("reqIds", &IbApiWrap::reqIds)
		.def("reqContractDetails", &IbApiWrap::reqContractDetails)
		.def("reqMktDepth", &IbApiWrap::reqMktDepth)
		.def("cancelMktDepth", &IbApiWrap::cancelMktDepth)
		.def("reqNewsBulletins", &IbApiWrap::reqNewsBulletins)
		.def("cancelNewsBulletins", &IbApiWrap::cancelNewsBulletins)
		.def("setServerLogLevel", &IbApiWrap::setServerLogLevel)
		.def("reqAutoOpenOrders", &IbApiWrap::reqAutoOpenOrders)
		.def("reqAllOpenOrders", &IbApiWrap::reqAllOpenOrders)
		.def("reqManagedAccts", &IbApiWrap::reqManagedAccts)
		.def("requestFA", &IbApiWrap::requestFA)
		.def("replaceFA", &IbApiWrap::replaceFA)
		.def("reqHistoricalData", &IbApiWrap::reqHistoricalData)
		.def("exerciseOptions", &IbApiWrap::exerciseOptions)
		.def("cancelHistoricalData", &IbApiWrap::cancelHistoricalData)
		.def("reqRealTimeBars", &IbApiWrap::reqRealTimeBars)
		.def("cancelRealTimeBars", &IbApiWrap::cancelRealTimeBars)
		.def("cancelScannerSubscription", &IbApiWrap::cancelScannerSubscription)
		.def("reqScannerParameters", &IbApiWrap::reqScannerParameters)
		.def("reqScannerSubscription", &IbApiWrap::reqScannerSubscription)
		.def("reqCurrentTime", &IbApiWrap::reqCurrentTime)
		.def("reqFundamentalData", &IbApiWrap::reqFundamentalData)
		.def("cancelFundamentalData", &IbApiWrap::cancelFundamentalData)
		.def("calculateImpliedVolatility", &IbApiWrap::calculateImpliedVolatility)
		.def("calculateOptionPrice", &IbApiWrap::calculateOptionPrice)
		.def("cancelCalculateImpliedVolatility", &IbApiWrap::cancelCalculateImpliedVolatility)
		.def("cancelCalculateOptionPrice", &IbApiWrap::cancelCalculateOptionPrice)
		.def("reqGlobalCancel", &IbApiWrap::reqGlobalCancel)
		.def("reqMarketDataType", &IbApiWrap::reqMarketDataType)
		.def("reqPositions", &IbApiWrap::reqPositions)
		.def("cancelPositions", &IbApiWrap::cancelPositions)
		.def("reqAccountSummary", &IbApiWrap::reqAccountSummary)
		.def("cancelAccountSummary", &IbApiWrap::cancelAccountSummary)
		.def("verifyRequest", &IbApiWrap::verifyRequest)
		.def("verifyMessage", &IbApiWrap::verifyMessage)
		.def("verifyAndAuthRequest", &IbApiWrap::verifyAndAuthRequest)
		.def("verifyAndAuthMessage", &IbApiWrap::verifyAndAuthMessage)
		.def("queryDisplayGroups", &IbApiWrap::queryDisplayGroups)
		.def("subscribeToGroupEvents", &IbApiWrap::subscribeToGroupEvents)
		.def("updateDisplayGroup", &IbApiWrap::updateDisplayGroup)
		.def("unsubscribeFromGroupEvents", &IbApiWrap::unsubscribeFromGroupEvents)
		.def("reqPositionsMulti", &IbApiWrap::reqPositionsMulti)
		.def("cancelPositionsMulti", &IbApiWrap::cancelPositionsMulti)
		.def("reqAccountUpdatessMulti", &IbApiWrap::reqAccountUpdatessMulti)
		.def("cancelAccountUpdatesMulti", &IbApiWrap::cancelAccountUpdatesMulti)
		.def("reqSecDefOptParams", &IbApiWrap::reqSecDefOptParams)
		.def("reqSoftDollarTiers", &IbApiWrap::reqSoftDollarTiers)

		.def("tickPrice", pure_virtual(&IbApiWrap::tickPrice))
		.def("tickSize", pure_virtual(&IbApiWrap::tickSize))
		.def("tickOptionComputation", pure_virtual(&IbApiWrap::tickOptionComputation))
		.def("tickGeneric", pure_virtual(&IbApiWrap::tickGeneric))
		.def("tickString", pure_virtual(&IbApiWrap::tickString))
		.def("tickEFP", pure_virtual(&IbApiWrap::tickEFP))
		.def("orderStatus", pure_virtual(&IbApiWrap::orderStatus))
		.def("openOrder", pure_virtual(&IbApiWrap::openOrder))
		.def("openOrderEnd", pure_virtual(&IbApiWrap::openOrderEnd))
		.def("winError", pure_virtual(&IbApiWrap::winError))
		.def("connectionClosed", pure_virtual(&IbApiWrap::connectionClosed))
		.def("updateAccountValue", pure_virtual(&IbApiWrap::updateAccountValue))
		.def("updatePortfolio", pure_virtual(&IbApiWrap::updatePortfolio))
		.def("updateAccountTime", pure_virtual(&IbApiWrap::updateAccountTime))
		.def("accountDownloadEnd", pure_virtual(&IbApiWrap::accountDownloadEnd))
		.def("nextValidId", pure_virtual(&IbApiWrap::nextValidId))
		.def("contractDetails", pure_virtual(&IbApiWrap::contractDetails))
		.def("bondContractDetails", pure_virtual(&IbApiWrap::bondContractDetails))
		.def("contractDetailsEnd", pure_virtual(&IbApiWrap::contractDetailsEnd))
		.def("execDetails", pure_virtual(&IbApiWrap::execDetails))
		.def("execDetailsEnd", pure_virtual(&IbApiWrap::execDetailsEnd))
		.def("error", pure_virtual(&IbApiWrap::error))
		.def("updateMktDepth", pure_virtual(&IbApiWrap::updateMktDepth))
		.def("updateMktDepthL2", pure_virtual(&IbApiWrap::updateMktDepthL2))
		.def("updateNewsBulletin", pure_virtual(&IbApiWrap::updateNewsBulletin))
		.def("managedAccounts", pure_virtual(&IbApiWrap::managedAccounts))
		.def("receiveFA", pure_virtual(&IbApiWrap::receiveFA))
		.def("historicalData", pure_virtual(&IbApiWrap::historicalData))
		.def("scannerParameters", pure_virtual(&IbApiWrap::scannerParameters))
		.def("scannerData", pure_virtual(&IbApiWrap::scannerData))
		.def("scannerDataEnd", pure_virtual(&IbApiWrap::scannerDataEnd))
		.def("realtimeBar", pure_virtual(&IbApiWrap::realtimeBar))
		.def("currentTime", pure_virtual(&IbApiWrap::currentTime))
		.def("fundamentalData", pure_virtual(&IbApiWrap::fundamentalData))
		.def("deltaNeutralValidation", pure_virtual(&IbApiWrap::deltaNeutralValidation))
		.def("tickSnapshotEnd", pure_virtual(&IbApiWrap::tickSnapshotEnd))
		.def("marketDataType", pure_virtual(&IbApiWrap::marketDataType))
		.def("commissionReport", pure_virtual(&IbApiWrap::commissionReport))
		.def("position", pure_virtual(&IbApiWrap::position))
		.def("positionEnd", pure_virtual(&IbApiWrap::positionEnd))
		.def("accountSummary", pure_virtual(&IbApiWrap::accountSummary))
		.def("accountSummaryEnd", pure_virtual(&IbApiWrap::accountSummaryEnd))
		.def("verifyMessageAPI", pure_virtual(&IbApiWrap::verifyMessageAPI))
		.def("verifyCompleted", pure_virtual(&IbApiWrap::verifyCompleted))
		.def("displayGroupList", pure_virtual(&IbApiWrap::displayGroupList))
		.def("displayGroupUpdated", pure_virtual(&IbApiWrap::displayGroupUpdated))
		.def("verifyAndAuthMessageAPI", pure_virtual(&IbApiWrap::verifyAndAuthMessageAPI))
		.def("verifyAndAuthCompleted", pure_virtual(&IbApiWrap::verifyAndAuthCompleted))
		.def("connectAck", pure_virtual(&IbApiWrap::connectAck))
		.def("positionMulti", pure_virtual(&IbApiWrap::positionMulti))
		.def("positionMultiEnd", pure_virtual(&IbApiWrap::positionMultiEnd))
		.def("accountUpdateMulti", pure_virtual(&IbApiWrap::accountUpdateMulti))
		.def("accountUpdateMultiEnd", pure_virtual(&IbApiWrap::accountUpdateMultiEnd))
		.def("securityDefinitionOptionalParameter", pure_virtual(&IbApiWrap::securityDefinitionOptionalParameter))
		.def("securityDefinitionOptionalParameterEnd", pure_virtual(&IbApiWrap::securityDefinitionOptionalParameterEnd))
		.def("softDollarTiers", pure_virtual(&IbApiWrap::softDollarTiers))
		;

	//结构体相关的封装
	class_<OrderState>("OrderState")
		.def_readwrite("status", &OrderState::status)
		.def_readwrite("initMargin", &OrderState::initMargin)
		.def_readwrite("maintMargin", &OrderState::maintMargin)
		.def_readwrite("equityWithLoan", &OrderState::equityWithLoan)
		.def_readwrite("commission", &OrderState::commission)
		.def_readwrite("minCommission", &OrderState::minCommission)
		.def_readwrite("maxCommission", &OrderState::maxCommission)
		.def_readwrite("commissionCurrency", &OrderState::commissionCurrency)
		.def_readwrite("warningText  ", &OrderState::warningText)
		;

	class_<Execution>("Execution")
		.def_readwrite("execId", &Execution::execId)
		.def_readwrite("time", &Execution::time)
		.def_readwrite("acctNumber", &Execution::acctNumber)
		.def_readwrite("exchange", &Execution::exchange)
		.def_readwrite("side", &Execution::side)
		.def_readwrite("shares", &Execution::shares)
		.def_readwrite("price", &Execution::price)
		.def_readwrite("permId", &Execution::permId)
		.def_readwrite("clientId", &Execution::clientId)
		.def_readwrite("orderId", &Execution::orderId)
		.def_readwrite("liquidation", &Execution::liquidation)
		.def_readwrite("cumQty", &Execution::cumQty)
		.def_readwrite("avgPrice", &Execution::avgPrice)
		.def_readwrite("orderRef", &Execution::orderRef)
		.def_readwrite("evRule", &Execution::evRule)
		.def_readwrite("evMultiplier", &Execution::evMultiplier)
		.def_readwrite("modelCode", &Execution::modelCode)
		;

	class_<UnderComp>("UnderComp")
		.def_readwrite("conId", &UnderComp::conId)
		.def_readwrite("delta", &UnderComp::delta)
		.def_readwrite("price", &UnderComp::price)
		;

	class_<CommissionReport>("CommissionReport")
		.def_readwrite("execId", &CommissionReport::execId)
		.def_readwrite("commission", &CommissionReport::commission)
		.def_readwrite("currency", &CommissionReport::currency)
		.def_readwrite("realizedPNL", &CommissionReport::realizedPNL)
		.def_readwrite("yield", &CommissionReport::yield)
		.def_readwrite("yieldRedemptionDate", &CommissionReport::yieldRedemptionDate)
		;

	class_<ExecutionFilter>("ExecutionFilter")
		.def_readwrite("m_clientId", &ExecutionFilter::m_clientId)
		.def_readwrite("m_acctCode", &ExecutionFilter::m_acctCode)
		.def_readwrite("m_time", &ExecutionFilter::m_time)
		.def_readwrite("m_symbol", &ExecutionFilter::m_symbol)
		.def_readwrite("m_secType", &ExecutionFilter::m_secType)
		.def_readwrite("m_exchange", &ExecutionFilter::m_exchange)
		.def_readwrite("m_side", &ExecutionFilter::m_side)
		;

	class_<ScannerSubscription>("ScannerSubscription")
		.def_readwrite("numberOfRows", &ScannerSubscription::numberOfRows)
		.def_readwrite("instrument", &ScannerSubscription::instrument)
		.def_readwrite("locationCode", &ScannerSubscription::locationCode)
		.def_readwrite("scanCode", &ScannerSubscription::scanCode)
		.def_readwrite("abovePrice", &ScannerSubscription::abovePrice)
		.def_readwrite("belowPrice", &ScannerSubscription::belowPrice)
		.def_readwrite("aboveVolume", &ScannerSubscription::aboveVolume)
		.def_readwrite("marketCapAbove", &ScannerSubscription::marketCapAbove)
		.def_readwrite("marketCapBelow", &ScannerSubscription::marketCapBelow)
		.def_readwrite("moodyRatingAbove", &ScannerSubscription::moodyRatingAbove)
		.def_readwrite("moodyRatingBelow", &ScannerSubscription::moodyRatingBelow)
		.def_readwrite("spRatingAbove", &ScannerSubscription::spRatingAbove)
		.def_readwrite("spRatingBelow", &ScannerSubscription::spRatingBelow)
		.def_readwrite("maturityDateAbove", &ScannerSubscription::maturityDateAbove)
		.def_readwrite("maturityDateBelow", &ScannerSubscription::maturityDateBelow)
		.def_readwrite("couponRateAbove", &ScannerSubscription::couponRateAbove)
		.def_readwrite("couponRateBelow", &ScannerSubscription::couponRateBelow)
		.def_readwrite("excludeConvertible", &ScannerSubscription::excludeConvertible)
		.def_readwrite("averageOptionVolumeAbove", &ScannerSubscription::averageOptionVolumeAbove)
		.def_readwrite("scannerSettingPairs", &ScannerSubscription::scannerSettingPairs)
		.def_readwrite("stockTypeFilter", &ScannerSubscription::stockTypeFilter)
		;

	class_<TagValue, TagValueSPtr>("TagValue")
		.def_readwrite("tag", &TagValue::tag)
		.def_readwrite("value", &TagValue::value)
		;

	class_<ComboLeg, ComboLegSPtr>("ComboLeg")
		.def_readwrite("conId", &ComboLeg::conId)
		.def_readwrite("ratio", &ComboLeg::ratio)
		.def_readwrite("action", &ComboLeg::action)
		.def_readwrite("exchange", &ComboLeg::exchange)
		.def_readwrite("openClose", &ComboLeg::openClose)
		.def_readwrite("shortSaleSlot", &ComboLeg::shortSaleSlot)
		.def_readwrite("designatedLocation", &ComboLeg::designatedLocation)
		.def_readwrite("exemptCode", &ComboLeg::exemptCode)
		;

	class_<Contract>("Contract")
		.def_readwrite("conId", &Contract::conId)
		.def_readwrite("symbol", &Contract::symbol)
		.def_readwrite("secType", &Contract::secType)
		.def_readwrite("lastTradeDateOrContractMonth", &Contract::lastTradeDateOrContractMonth)
		.def_readwrite("strike", &Contract::strike)
		.def_readwrite("right", &Contract::right)
		.def_readwrite("multiplier", &Contract::multiplier)
		.def_readwrite("exchange", &Contract::exchange)
		.def_readwrite("primaryExchange", &Contract::primaryExchange)
		.def_readwrite("currency", &Contract::currency)
		.def_readwrite("localSymbol", &Contract::localSymbol)
		.def_readwrite("tradingClass", &Contract::tradingClass)
		.def_readwrite("includeExpired", &Contract::includeExpired)
		.def_readwrite("secIdType", &Contract::secIdType)
		.def_readwrite("secId", &Contract::secId)
		.def_readwrite("comboLegsDescrip", &Contract::comboLegsDescrip)
		.def_readwrite("comboLegs", &Contract::comboLegs)
		.def_readwrite("underComp", &Contract::underComp)
		;

	class_<ContractDetails>("ContractDetails")
		.def_readwrite("summary", &ContractDetails::summary)
		.def_readwrite("marketName", &ContractDetails::marketName)
		.def_readwrite("minTick", &ContractDetails::minTick)
		.def_readwrite("orderTypes", &ContractDetails::orderTypes)
		.def_readwrite("validExchanges", &ContractDetails::validExchanges)
		.def_readwrite("priceMagnifier", &ContractDetails::priceMagnifier)
		.def_readwrite("underConId", &ContractDetails::underConId)
		.def_readwrite("longName", &ContractDetails::longName)
		.def_readwrite("contractMonth", &ContractDetails::contractMonth)
		.def_readwrite("industry", &ContractDetails::industry)
		.def_readwrite("category", &ContractDetails::category)
		.def_readwrite("subcategory", &ContractDetails::subcategory)
		.def_readwrite("timeZoneId", &ContractDetails::timeZoneId)
		.def_readwrite("tradingHours", &ContractDetails::tradingHours)
		.def_readwrite("liquidHours", &ContractDetails::liquidHours)
		.def_readwrite("evRule", &ContractDetails::evRule)
		.def_readwrite("evMultiplier", &ContractDetails::evMultiplier)
		.def_readwrite("secIdList", &ContractDetails::secIdList)
		.def_readwrite("cusip", &ContractDetails::cusip)
		.def_readwrite("ratings", &ContractDetails::ratings)
		.def_readwrite("descAppend", &ContractDetails::descAppend)
		.def_readwrite("bondType", &ContractDetails::bondType)
		.def_readwrite("couponType", &ContractDetails::couponType)
		.def_readwrite("callable", &ContractDetails::callable)
		.def_readwrite("putable", &ContractDetails::putable)
		.def_readwrite("coupon", &ContractDetails::coupon)
		.def_readwrite("convertible", &ContractDetails::convertible)
		.def_readwrite("maturity", &ContractDetails::maturity)
		.def_readwrite("issueDate", &ContractDetails::issueDate)
		.def_readwrite("nextOptionDate", &ContractDetails::nextOptionDate)
		.def_readwrite("nextOptionType", &ContractDetails::nextOptionType)
		.def_readwrite("nextOptionPartial", &ContractDetails::nextOptionPartial)
		.def_readwrite("notes", &ContractDetails::notes)
		;
	
	class_<OrderCondition>("OrderCondition")			//实现不完全，暂时不清楚作用
		.def("toString", &OrderCondition::toString)
		.def("type", &OrderCondition::type)
		;

	class_<OrderComboLeg, OrderComboLegSPtr>("OrderComboLeg")
		.def_readwrite("price", &OrderComboLeg::price)
		;

	class_<Order>("Order")
		.def_readwrite("orderId", &Order::orderId)
		.def_readwrite("clientId", &Order::clientId)
		.def_readwrite("permId", &Order::permId)
		.def_readwrite("action", &Order::action)
		.def_readwrite("totalQuantity", &Order::totalQuantity)
		.def_readwrite("orderType", &Order::orderType)
		.def_readwrite("lmtPrice", &Order::lmtPrice)
		.def_readwrite("auxPrice", &Order::auxPrice)
		.def_readwrite("tif", &Order::tif)
		.def_readwrite("activeStartTime", &Order::activeStartTime)
		.def_readwrite("activeStopTime", &Order::activeStopTime)
		.def_readwrite("ocaGroup", &Order::ocaGroup)
		.def_readwrite("ocaType", &Order::ocaType)
		.def_readwrite("orderRef", &Order::orderRef)
		.def_readwrite("transmit", &Order::transmit)
		.def_readwrite("parentId", &Order::parentId)
		.def_readwrite("blockOrder", &Order::blockOrder)
		.def_readwrite("sweepToFill", &Order::sweepToFill)
		.def_readwrite("displaySize", &Order::displaySize)
		.def_readwrite("triggerMethod", &Order::triggerMethod)
		.def_readwrite("outsideRth", &Order::outsideRth)
		.def_readwrite("hidden", &Order::hidden)
		.def_readwrite("goodAfterTime", &Order::goodAfterTime)
		.def_readwrite("goodTillDate", &Order::goodTillDate)
		.def_readwrite("rule80A", &Order::rule80A)
		.def_readwrite("allOrNone", &Order::allOrNone)
		.def_readwrite("minQty", &Order::minQty)
		.def_readwrite("percentOffset", &Order::percentOffset)
		.def_readwrite("overridePercentageConstraints", &Order::overridePercentageConstraints)
		.def_readwrite("trailStopPrice", &Order::trailStopPrice)
		.def_readwrite("trailingPercent", &Order::trailingPercent)
		.def_readwrite("faGroup", &Order::faGroup)
		.def_readwrite("faProfile", &Order::faProfile)
		.def_readwrite("faMethod", &Order::faMethod)
		.def_readwrite("faPercentage", &Order::faPercentage)
		.def_readwrite("openClose", &Order::openClose)
		.def_readwrite("origin", &Order::origin)
		.def_readwrite("shortSaleSlot", &Order::shortSaleSlot)
		.def_readwrite("designatedLocation", &Order::designatedLocation)
		.def_readwrite("exemptCode", &Order::exemptCode)
		.def_readwrite("discretionaryAmt", &Order::discretionaryAmt)
		.def_readwrite("eTradeOnly", &Order::eTradeOnly)
		.def_readwrite("firmQuoteOnly", &Order::firmQuoteOnly)
		.def_readwrite("nbboPriceCap", &Order::nbboPriceCap)
		.def_readwrite("optOutSmartRouting", &Order::optOutSmartRouting)
		.def_readwrite("auctionStrategy", &Order::auctionStrategy)
		.def_readwrite("startingPrice", &Order::startingPrice)
		.def_readwrite("stockRefPrice", &Order::stockRefPrice)
		.def_readwrite("delta", &Order::delta)
		.def_readwrite("stockRangeLower", &Order::stockRangeLower)
		.def_readwrite("stockRangeUpper", &Order::stockRangeUpper)
		.def_readwrite("randomizeSize", &Order::randomizeSize)
		.def_readwrite("randomizePrice", &Order::randomizePrice)
		.def_readwrite("volatility", &Order::volatility)
		.def_readwrite("volatilityType", &Order::volatilityType)
		.def_readwrite("deltaNeutralOrderType", &Order::deltaNeutralOrderType)
		.def_readwrite("deltaNeutralAuxPrice", &Order::deltaNeutralAuxPrice)
		.def_readwrite("deltaNeutralConId", &Order::deltaNeutralConId)
		.def_readwrite("deltaNeutralSettlingFirm", &Order::deltaNeutralSettlingFirm)
		.def_readwrite("deltaNeutralClearingAccount", &Order::deltaNeutralClearingAccount)
		.def_readwrite("deltaNeutralClearingIntent", &Order::deltaNeutralClearingIntent)
		.def_readwrite("deltaNeutralOpenClose", &Order::deltaNeutralOpenClose)
		.def_readwrite("deltaNeutralShortSale", &Order::deltaNeutralShortSale)
		.def_readwrite("deltaNeutralShortSaleSlot", &Order::deltaNeutralShortSaleSlot)
		.def_readwrite("deltaNeutralDesignatedLocation", &Order::deltaNeutralDesignatedLocation)
		.def_readwrite("continuousUpdate", &Order::continuousUpdate)
		.def_readwrite("referencePriceType", &Order::referencePriceType)
		.def_readwrite("basisPoints", &Order::basisPoints)
		.def_readwrite("basisPointsType", &Order::basisPointsType)
		.def_readwrite("scaleInitLevelSize", &Order::scaleInitLevelSize)
		.def_readwrite("scaleSubsLevelSize", &Order::scaleSubsLevelSize)
		.def_readwrite("scalePriceIncrement", &Order::scalePriceIncrement)
		.def_readwrite("scalePriceAdjustValue", &Order::scalePriceAdjustValue)
		.def_readwrite("scalePriceAdjustInterval", &Order::scalePriceAdjustInterval)
		.def_readwrite("scaleProfitOffset", &Order::scaleProfitOffset)
		.def_readwrite("scaleAutoReset", &Order::scaleAutoReset)
		.def_readwrite("scaleInitPosition", &Order::scaleInitPosition)
		.def_readwrite("scaleInitFillQty", &Order::scaleInitFillQty)
		.def_readwrite("scaleRandomPercent", &Order::scaleRandomPercent)
		.def_readwrite("scaleTable", &Order::scaleTable)
		.def_readwrite("hedgeType", &Order::hedgeType)
		.def_readwrite("hedgeParam", &Order::hedgeParam)
		.def_readwrite("account", &Order::account)
		.def_readwrite("settlingFirm", &Order::settlingFirm)
		.def_readwrite("clearingAccount", &Order::clearingAccount)
		.def_readwrite("clearingIntent", &Order::clearingIntent)
		.def_readwrite("algoStrategy", &Order::algoStrategy)
		.def_readwrite("algoParams", &Order::algoParams)
		.def_readwrite("smartComboRoutingParams", &Order::smartComboRoutingParams)
		.def_readwrite("algoId", &Order::algoId)
		.def_readwrite("whatIf", &Order::whatIf)
		.def_readwrite("notHeld", &Order::notHeld)
		.def_readwrite("solicited", &Order::solicited)
		.def_readwrite("modelCode", &Order::modelCode)
		.def_readwrite("orderComboLegs", &Order::orderComboLegs)
		.def_readwrite("orderMiscOptions", &Order::orderMiscOptions)
		.def_readwrite("referenceContractId", &Order::referenceContractId)
		.def_readwrite("peggedChangeAmount", &Order::peggedChangeAmount)
		.def_readwrite("isPeggedChangeAmountDecrease", &Order::isPeggedChangeAmountDecrease)
		.def_readwrite("referenceChangeAmount", &Order::referenceChangeAmount)
		.def_readwrite("referenceExchangeId", &Order::referenceExchangeId)
		.def_readwrite("adjustedOrderType", &Order::adjustedOrderType)
		.def_readwrite("triggerPrice", &Order::triggerPrice)
		.def_readwrite("adjustedStopPrice", &Order::adjustedStopPrice)
		.def_readwrite("adjustedStopLimitPrice", &Order::adjustedStopLimitPrice)
		.def_readwrite("adjustedTrailingAmount", &Order::adjustedTrailingAmount)
		.def_readwrite("adjustableTrailingUnit", &Order::adjustableTrailingUnit)
		.def_readwrite("lmtPriceOffset", &Order::lmtPriceOffset)
		.def_readwrite("conditions", &Order::conditions)
		.def_readwrite("conditionsCancelOrder", &Order::conditionsCancelOrder)
		.def_readwrite("conditionsIgnoreRth", &Order::conditionsIgnoreRth)
		.def_readwrite("extOperator", &Order::extOperator)
		;

	class_<SoftDollarTier, boost::noncopyable>("SoftDollarTier")
		.def("name", &SoftDollarTier::name)
		.def("val", &SoftDollarTier::val)
		.def("displayName", &SoftDollarTier::displayName)
		;

	//vector相关的封装
	class_<TagValueList, TagValueListSPtr>("TagValueList")
		.def(vector_indexing_suite<TagValueList, true>());    //这个true非常重要

	class_<Contract::ComboLegList, Contract::ComboLegListSPtr>("ComboLegList")
		.def(vector_indexing_suite<Contract::ComboLegList, true>());

	class_<Order::OrderComboLegList, Order::OrderComboLegListSPtr>("OrderComboLegList")
		.def(vector_indexing_suite<Order::OrderComboLegList, true>());

	class_<std::vector<ibapi::shared_ptr<OrderCondition>>>("OrderConditionList")
		.def(vector_indexing_suite<std::vector<ibapi::shared_ptr<OrderCondition>>, true>());

	class_<std::vector<std::string>>("StringList")
		.def(vector_indexing_suite<std::vector<std::string>, true>());

	class_<std::vector<double>>("DoubleList")
		.def(vector_indexing_suite<std::vector<double>, true>());

	class_<std::vector<SoftDollarTier>>("SoftDollarTierList")
		.def(vector_indexing_suite<std::vector<SoftDollarTier>, true>());

	//enum相关的封装
	enum_<OrderCondition::OrderConditionType>("OrderConditionType")
		.value("Price", OrderCondition::Price)
		.value("Time", OrderCondition::Time)
		.value("Margin", OrderCondition::Margin)
		.value("Execution", OrderCondition::Execution)
		.value("Volume", OrderCondition::Volume)
		.value("PercentChange", OrderCondition::PercentChange)
		;

	enum_<TickType>("TickType")
		.value("BID_SIZE", BID_SIZE)
		.value("BID", BID)
		.value("ASK", ASK)
		.value("ASK_SIZE", ASK_SIZE)
		.value("LAST", LAST)
		.value("LAST_SIZE", LAST_SIZE)
		.value("HIGH", HIGH)
		.value("BID_OPTION_COMPUTATION", BID_OPTION_COMPUTATION)
		.value("ASK_OPTION_COMPUTATION", ASK_OPTION_COMPUTATION)
		.value("LAST_OPTION_COMPUTATION", LAST_OPTION_COMPUTATION)
		.value("MODEL_OPTION", MODEL_OPTION)
		.value("OPEN", OPEN)
		.value("LOW_13_WEEK", LOW_13_WEEK)
		.value("HIGH_13_WEEK", HIGH_13_WEEK)
		.value("LOW_26_WEEK", LOW_26_WEEK)
		.value("HIGH_26_WEEK", HIGH_26_WEEK)
		.value("LOW_52_WEEK", LOW_52_WEEK)
		.value("HIGH_52_WEEK", HIGH_52_WEEK)
		.value("AVG_VOLUME", AVG_VOLUME)
		.value("OPEN_INTEREST", OPEN_INTEREST)
		.value("OPTION_HISTORICAL_VOL", OPTION_HISTORICAL_VOL)
		.value("OPTION_IMPLIED_VOL", OPTION_IMPLIED_VOL)
		.value("OPTION_BID_EXCH", OPTION_BID_EXCH)
		.value("OPTION_ASK_EXCH", OPTION_ASK_EXCH)
		.value("OPTION_CALL_OPEN_INTEREST", OPTION_CALL_OPEN_INTEREST)
		.value("OPTION_PUT_OPEN_INTEREST", OPTION_PUT_OPEN_INTEREST)
		.value("OPTION_CALL_VOLUME", OPTION_CALL_VOLUME)
		.value("OPTION_PUT_VOLUME", OPTION_PUT_VOLUME)
		.value("INDEX_FUTURE_PREMIUM", INDEX_FUTURE_PREMIUM)
		.value("BID_EXCH", BID_EXCH)
		.value("ASK_EXCH", ASK_EXCH)
		.value("AUCTION_VOLUME", AUCTION_VOLUME)
		.value("AUCTION_PRICE", AUCTION_PRICE)
		.value("AUCTION_IMBALANCE", AUCTION_IMBALANCE)
		.value("MARK_PRICE", MARK_PRICE)
		.value("BID_EFP_COMPUTATION", BID_EFP_COMPUTATION)
		.value("ASK_EFP_COMPUTATION", ASK_EFP_COMPUTATION)
		.value("LAST_EFP_COMPUTATION", LAST_EFP_COMPUTATION)
		.value("OPEN_EFP_COMPUTATION", OPEN_EFP_COMPUTATION)
		.value("HIGH_EFP_COMPUTATION", HIGH_EFP_COMPUTATION)
		.value("LOW_EFP_COMPUTATION", LOW_EFP_COMPUTATION)
		.value("CLOSE_EFP_COMPUTATION", CLOSE_EFP_COMPUTATION)
		.value("LAST_TIMESTAMP", LAST_TIMESTAMP)
		.value("SHORTABLE", SHORTABLE)
		.value("FUNDAMENTAL_RATIOS", FUNDAMENTAL_RATIOS)
		.value("RT_VOLUME", RT_VOLUME)
		.value("HALTED", HALTED)
		.value("BID_YIELD", BID_YIELD)
		.value("ASK_YIELD", ASK_YIELD)
		.value("LAST_YIELD", LAST_YIELD)
		.value("CUST_OPTION_COMPUTATION", CUST_OPTION_COMPUTATION)
		.value("TRADE_COUNT", TRADE_COUNT)
		.value("TRADE_RATE", TRADE_RATE)
		.value("VOLUME_RATE", VOLUME_RATE)
		.value("LAST_RTH_TRADE", LAST_RTH_TRADE)
		.value("RT_HISTORICAL_VOL", RT_HISTORICAL_VOL)
		.value("IB_DIVIDENDS", IB_DIVIDENDS)
		.value("BOND_FACTOR_MULTIPLIER", BOND_FACTOR_MULTIPLIER)
		.value("REGULATORY_IMBALANCE", REGULATORY_IMBALANCE)
		.value("NEWS_TICK", NEWS_TICK)
		.value("SHORT_TERM_VOLUME_3_MIN", SHORT_TERM_VOLUME_3_MIN)
		.value("SHORT_TERM_VOLUME_5_MIN", SHORT_TERM_VOLUME_5_MIN)
		.value("SHORT_TERM_VOLUME_10_MIN", SHORT_TERM_VOLUME_10_MIN)
		.value("DELAYED_BID", DELAYED_BID)
		.value("DELAYED_ASK", DELAYED_ASK)
		.value("DELAYED_LAST", DELAYED_LAST)
		.value("DELAYED_BID_SIZE", DELAYED_BID_SIZE)
		.value("DELAYED_ASK_SIZE", DELAYED_ASK_SIZE)
		.value("DELAYED_LAST_SIZE", DELAYED_LAST_SIZE)
		.value("DELAYED_HIGH", DELAYED_HIGH)
		.value("DELAYED_LOW", DELAYED_LOW)
		.value("DELAYED_VOLUME", DELAYED_VOLUME)
		.value("DELAYED_CLOSE", DELAYED_CLOSE)
		.value("DELAYED_OPEN", DELAYED_OPEN)
		.value("NOT_SET", NOT_SET)
		;

	//注册智能指针到boost.python环境中，暂时无用
	//register_ptr_to_python<TagValueSPtr>();
	//register_ptr_to_python<TagValueListSPtr>();
	//register_ptr_to_python<OrderComboLegSPtr>();
};

