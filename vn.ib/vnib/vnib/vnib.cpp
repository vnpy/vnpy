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


///-------------------------------------------------------------------------------------
///C++的回调函数将数据保存到队列中
///-------------------------------------------------------------------------------------

void IbWrapper::tickPrice(TickerId tickerId, TickType field, double price, int canAutoExecute){};

void IbWrapper::tickSize(TickerId tickerId, TickType field, int size){};

void IbWrapper::tickOptionComputation(TickerId tickerId, TickType tickType, double impliedVol, double delta,
	double optPrice, double pvDividend, double gamma, double vega, double theta, double undPrice){};

void IbWrapper::tickGeneric(TickerId tickerId, TickType tickType, double value){};

void IbWrapper::tickString(TickerId tickerId, TickType tickType, const std::string& value){};

void IbWrapper::tickEFP(TickerId tickerId, TickType tickType, double basisPoints, const std::string& formattedBasisPoints,
	double totalDividends, int holdDays, const std::string& futureLastTradeDate, double dividendImpact, double dividendsToLastTradeDate){};

void IbWrapper::orderStatus(OrderId orderId, const std::string& status, double filled,
	double remaining, double avgFillPrice, int permId, int parentId,
	double lastFillPrice, int clientId, const std::string& whyHeld){};

void IbWrapper::openOrder(OrderId orderId, const Contract&, const Order&, const OrderState&){};

void IbWrapper::openOrderEnd(){};

void IbWrapper::winError(const std::string& str, int lastError){};

void IbWrapper::connectionClosed(){};

void IbWrapper::updateAccountValue(const std::string& key, const std::string& val,
	const std::string& currency, const std::string& accountName){};

void IbWrapper::updatePortfolio(const Contract& contract, double position,
	double marketPrice, double marketValue, double averageCost,
	double unrealizedPNL, double realizedPNL, const std::string& accountName){};

void IbWrapper::updateAccountTime(const std::string& timeStamp){};

void IbWrapper::accountDownloadEnd(const std::string& accountName){};

void IbWrapper::nextValidId(OrderId orderId)
{
	PyLock lock;
	this->api->nextValidId(orderId);
};

void IbWrapper::contractDetails(int reqId, const ContractDetails& contractDetails){};

void IbWrapper::bondContractDetails(int reqId, const ContractDetails& contractDetails){};

void IbWrapper::contractDetailsEnd(int reqId){};

void IbWrapper::execDetails(int reqId, const Contract& contract, const Execution& execution){};

void IbWrapper::execDetailsEnd(int reqId){};

void IbWrapper::error(const int id, const int errorCode, const std::string errorString)
{
	PyLock lock;
	this->api->error(id, errorCode, errorString);
};

void IbWrapper::updateMktDepth(TickerId id, int position, int operation, int side,
	double price, int size){};

void IbWrapper::updateMktDepthL2(TickerId id, int position, std::string marketMaker, int operation,
	int side, double price, int size){};

void IbWrapper::updateNewsBulletin(int msgId, int msgType, const std::string& newsMessage, const std::string& originExch){};

void IbWrapper::managedAccounts(const std::string& accountsList){};

void IbWrapper::receiveFA(faDataType pFaDataType, const std::string& cxml){};

void IbWrapper::historicalData(TickerId reqId, const std::string& date, double open, double high,

	double low, double close, int volume, int barCount, double WAP, int hasGaps){};

void IbWrapper::scannerParameters(const std::string& xml){};

void IbWrapper::scannerData(int reqId, int rank, const ContractDetails& contractDetails,
	const std::string& distance, const std::string& benchmark, const std::string& projection,
	const std::string& legsStr){};

void IbWrapper::scannerDataEnd(int reqId){};

void IbWrapper::realtimeBar(TickerId reqId, long time, double open, double high, double low, double close,
	long volume, double wap, int count){};

void IbWrapper::currentTime(long time)
{
	PyLock lock;
	this->api->currentTime(time);
};

void IbWrapper::fundamentalData(TickerId reqId, const std::string& data){};

void IbWrapper::deltaNeutralValidation(int reqId, const UnderComp& underComp){};

void IbWrapper::tickSnapshotEnd(int reqId){};

void IbWrapper::marketDataType(TickerId reqId, int marketDataType){};

void IbWrapper::commissionReport(const CommissionReport& commissionReport){};

void IbWrapper::position(const std::string& account, const Contract& contract, double position, double avgCost){};

void IbWrapper::positionEnd(){};

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

void IbWrapper::verifyMessageAPI(const std::string& apiData){};

void IbWrapper::verifyCompleted(bool isSuccessful, const std::string& errorText){};

void IbWrapper::displayGroupList(int reqId, const std::string& groups){};

void IbWrapper::displayGroupUpdated(int reqId, const std::string& contractInfo){};

void IbWrapper::verifyAndAuthMessageAPI(const std::string& apiData, const std::string& xyzChallange){};

void IbWrapper::verifyAndAuthCompleted(bool isSuccessful, const std::string& errorText){};

void IbWrapper::connectAck()
{
	PyLock lock;
	this->api->connectAck();
};

void IbWrapper::positionMulti(int reqId, const std::string& account, const std::string& modelCode, const Contract& contract, double pos, double
	avgCost){};

void IbWrapper::positionMultiEnd(int reqId){};

void IbWrapper::accountUpdateMulti(int reqId, const std::string& account, const std::string& modelCode, const std::string& key, const std::string&
	value, const std::string& currency){};

void IbWrapper::accountUpdateMultiEnd(int reqId){};

void IbWrapper::securityDefinitionOptionalParameter(int reqId, const std::string& exchange, int underlyingConId, const std::string& tradingClass,
	const std::string& multiplier, std::set<std::string> expirations, std::set<double> strikes){};

void IbWrapper::securityDefinitionOptionalParameterEnd(int reqId){};



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

int VnIbApi::serverVersion()
{
};

std::string VnIbApi::TwsConnectionTime()
{
	return this->client->TwsConnectionTime();
};

void VnIbApi::reqMktData(TickerId id, const Contract& contract,
	const std::string& genericTicks, bool snapshot, const TagValueListSPtr& mktDataOptions){};

void VnIbApi::cancelMktData(TickerId id){};

void VnIbApi::placeOrder(OrderId id, const Contract& contract, const Order& order){};

void VnIbApi::cancelOrder(OrderId id){};

void VnIbApi::reqOpenOrders(){};

void VnIbApi::reqAccountUpdates(bool subscribe, const std::string& acctCode){};

void VnIbApi::reqExecutions(int reqId, const ExecutionFilter& filter){};

void VnIbApi::reqIds(int numIds){};

void VnIbApi::reqContractDetails(int reqId, const Contract& contract){};

void VnIbApi::reqMktDepth(TickerId tickerId, const Contract& contract, int numRows, const TagValueListSPtr& mktDepthOptions){};

void VnIbApi::cancelMktDepth(TickerId tickerId){};

void VnIbApi::reqNewsBulletins(bool allMsgs){};

void VnIbApi::cancelNewsBulletins(){};

void VnIbApi::setServerLogLevel(int level){};

void VnIbApi::reqAutoOpenOrders(bool bAutoBind){};

void VnIbApi::reqAllOpenOrders(){};

void VnIbApi::reqManagedAccts(){};

void VnIbApi::requestFA(faDataType pFaDataType){};

void VnIbApi::replaceFA(faDataType pFaDataType, const std::string& cxml){};

void VnIbApi::reqHistoricalData(TickerId id, const Contract& contract,
	const std::string& endDateTime, const std::string& durationStr,
	const std::string&  barSizeSetting, const std::string& whatToShow,
	int useRTH, int formatDate, const TagValueListSPtr& chartOptions){};

void VnIbApi::exerciseOptions(TickerId tickerId, const Contract& contract,
	int exerciseAction, int exerciseQuantity,
	const std::string& account, int override){};

void VnIbApi::cancelHistoricalData(TickerId tickerId){};

void VnIbApi::reqRealTimeBars(TickerId id, const Contract& contract, int barSize,
	const std::string& whatToShow, bool useRTH, const TagValueListSPtr& realTimeBarsOptions){};

void VnIbApi::cancelRealTimeBars(TickerId tickerId){};

void VnIbApi::cancelScannerSubscription(int tickerId){};

void VnIbApi::reqScannerParameters(){};

void VnIbApi::reqScannerSubscription(int tickerId, const ScannerSubscription& subscription, const TagValueListSPtr& scannerSubscriptionOptions){};

void VnIbApi::reqCurrentTime()
{
	this->client->reqCurrentTime();
};

void VnIbApi::reqFundamentalData(TickerId reqId, const Contract&, const std::string& reportType){};

void VnIbApi::cancelFundamentalData(TickerId reqId){};

void VnIbApi::calculateImpliedVolatility(TickerId reqId, const Contract& contract, double optionPrice, double underPrice){};

void VnIbApi::calculateOptionPrice(TickerId reqId, const Contract& contract, double volatility, double underPrice){};

void VnIbApi::cancelCalculateImpliedVolatility(TickerId reqId){};

void VnIbApi::cancelCalculateOptionPrice(TickerId reqId){};

void VnIbApi::reqGlobalCancel(){};

void VnIbApi::reqMarketDataType(int marketDataType){};

void VnIbApi::reqPositions(){};

void VnIbApi::cancelPositions(){};

void VnIbApi::reqAccountSummary(int reqId, const std::string& groupName, const std::string& tags)
{
	this->client->reqAccountSummary(reqId, groupName, tags);
};

void VnIbApi::cancelAccountSummary(int reqId){};

void VnIbApi::verifyRequest(const std::string& apiName, const std::string& apiVersion){};

void VnIbApi::verifyMessage(const std::string& apiData){};

void VnIbApi::verifyAndAuthRequest(const std::string& apiName, const std::string& apiVersion, const std::string& opaqueIsvKey){};

void VnIbApi::verifyAndAuthMessage(const std::string& apiData, const std::string& xyzResponse){};

void VnIbApi::queryDisplayGroups(int reqId){};

void VnIbApi::subscribeToGroupEvents(int reqId, int groupId){};

void VnIbApi::updateDisplayGroup(int reqId, const std::string& contractInfo){};

void VnIbApi::unsubscribeFromGroupEvents(int reqId){};

void VnIbApi::reqPositionsMulti(int reqId, const std::string& account, const std::string& modelCode){};

void VnIbApi::cancelPositionsMulti(int reqId){};

void VnIbApi::reqAccountUpdatessMulti(int reqId, const std::string& account, const std::string& modelCode, bool ledgerAndNLV){};

void VnIbApi::cancelAccountUpdatesMulti(int reqId){};

void VnIbApi::reqSecDefOptParams(int reqId, const std::string& underlyingSymbol, const std::string& futFopExchange, const std::string&
	underlyingSecType, int underlyingConId){};

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


	virtual void accountSummary(int reqId, const std::string& account, const std::string& tag, const std::string& value, const std::string &curency)
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
};




struct TagValue_Wrapper : TagValue
{
	TagValue_Wrapper(PyObject* self_) : self(self_) {}
	PyObject* self;
};


// 特殊封装相关
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

/*
template<class T>
bool ibapi::shared_ptr::operator==(ibapi::shared_ptr<T> const & a)
{
	return a.get() == this->get();
}

template<class T>
bool ibapi::shared_ptr::operator!=(ibapi::shared_ptr<T> const & a)
{
	return a.get() != this->get();
}
*/

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
		.def("reqCurrentTime", &IbApiWrap::reqCurrentTime)
		.def("reqAccountSummary", &IbApiWrap::reqAccountSummary)


		.def("nextValidId", pure_virtual(&IbApiWrap::nextValidId))
		.def("currentTime", pure_virtual(&IbApiWrap::currentTime))
		.def("connectAck", pure_virtual(&IbApiWrap::connectAck))
		.def("error", pure_virtual(&IbApiWrap::error))
		.def("accountSummary", pure_virtual(&IbApiWrap::accountSummary))
		.def("accountSummaryEnd", pure_virtual(&IbApiWrap::accountSummaryEnd))
		;

	//结构体封装
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
		.def_readwrite("clientId  ", &Execution::clientId)
		.def_readwrite("orderId  ", &Execution::orderId)
		.def_readwrite("liquidation  ", &Execution::liquidation)
		.def_readwrite("cumQty  ", &Execution::cumQty)
		.def_readwrite("avgPrice  ", &Execution::avgPrice)
		.def_readwrite("orderRef  ", &Execution::orderRef)
		.def_readwrite("evRule  ", &Execution::evRule)
		.def_readwrite("evMultiplier  ", &Execution::evMultiplier)
		.def_readwrite("modelCode  ", &Execution::modelCode)
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
	//class_<TagValue>("TagValue")
		.def_readwrite("tag", &TagValue::tag)
		.def_readwrite("value", &TagValue::value)
		;

	class_<TagValueList, TagValueListSPtr>("TagValueList")
	//class_<TagValueList>("TagValueList")
		.def(vector_indexing_suite<TagValueList, true>());    //这个true非常重要

	//register_ptr_to_python<TagValueSPtr>();
	//register_ptr_to_python<TagValueListSPtr>();

	class_<ComboLeg>("ComboLeg")
		.def_readwrite("conId", &ComboLeg::conId)
		.def_readwrite("ratio", &ComboLeg::ratio)
		.def_readwrite("action", &ComboLeg::action)
		.def_readwrite("exchange", &ComboLeg::exchange)
		.def_readwrite("openClose", &ComboLeg::openClose)
		.def_readwrite("shortSaleSlot", &ComboLeg::shortSaleSlot)
		.def_readwrite("designatedLocation", &ComboLeg::designatedLocation)
		.def_readwrite("exemptCode", &ComboLeg::exemptCode)
		;
};

