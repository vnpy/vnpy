/* Copyright (C) 2013 Interactive Brokers LLC. All rights reserved. This code is subject to the terms
 * and conditions of the IB API Non-Commercial License or the IB API Commercial License, as applicable. */

#pragma once
#ifndef eclient_h__INCLUDED
#define eclient_h__INCLUDED


#include <memory>
#include <string>
#include <vector>
#include <iosfwd>
#include "CommonDefs.h"
#include "TagValue.h"

namespace ibapi {
namespace client_constants {

/////////////////////////////////////////////////////////////////////////////////
// SOCKET CLIENT VERSION CHANGE LOG : Incremented when the format of incomming
//                                    server responses change
/////////////////////////////////////////////////////////////////////////////////
// constants
// 6 = Added parentId to orderStatus
// 7 = The new execDetails event returned for an order filled status and reqExecDetails
//     Also added market depth support.
// 8 = Added 'lastFillPrice' to orderStatus and 'permId' to execDetails
// 9 = Added 'avgCost', 'unrealizedPNL', and 'unrealizedPNL' to updatePortfolio event
// 10 = Added 'serverId' to the 'open order' & 'order status' events.
//      We send back all the API open orders upon connection.
//      Added new methods reqAllOpenOrders, reqAutoOpenOrders()
//      Added FA support - reqExecution has filter.
//                       - reqAccountUpdates takes acct code.
// 11 = Added permId to openOrder event.
// 12 = Added IgnoreRth, hidden, and discretionaryAmt
// 13 = Added GoodAfterTime
// 14 = always send size on bid/ask/last tick
// 15 = send allocation string with open order
// 16 = can receive account name in account and portfolio updates, and fa params in openOrder
// 17 = can receive liquidation field in exec reports, and notAutoAvailable field in mkt data
// 18 = can receive good till date field in open order messages, and send backfill requests
// 19 = can receive new extended order attributes in OPEN_ORDER
// 20 = expects TWS time string on connection after server version >= 20, and parentId in open order
// 21 = can receive bond contract details.
// 22 = can receive price magnifier in contract details
// 23 = support for scanner
// 24 = can receive volatility order parameters in open order messages
// 25 = can receive HMDS query start and end times
// 26 = can receive option vols in option market data messages
// 27 = can receive delta neutral order type and delta neutral aux price
// 28 = can receive option model computation ticks
// 29 = can receive trail stop limit price in open order and can place them: API 8.91
// 30 = can receive extended bond contract def, new ticks, and trade count in bars
// 31 = can receive EFP extensions to scanner and market data, and combo legs on open orders
//    ; can receive RT bars
// 32 = can receive TickType.LAST_TIMESTAMP
// 33 = can receive ScaleNumComponents and ScaleComponentSize is open order messages
// 34 = can receive whatIf orders / order state
// 35 = can receive contId field for Contract objects
// 36 = can receive outsideRth field for Order objects
// 37 = can receive clearingAccount and clearingIntent for Order objects
// 38 = can receive multipier and primaryExchange in portfolio updates
//    ; can receive cumQty and avgPrice in execution
//    ; can receive fundamental data
//    ; can receive underComp for Contract objects
//    ; can receive reqId and end marker in contractDetails/bondContractDetails
//    ; can receive ScaleInitComponentSize and ScaleSubsComponentSize for Order objects
// 39 = can receive underConId in contractDetails
// 40 = can receive algoStrategy/algoParams in openOrder
// 41 = can receive end marker for openOrder
//    ; can receive end marker for account download
//    ; can receive end marker for executions download
// 42 = can receive deltaNeutralValidation
// 43 = can receive longName(companyName)
//    ; can receive listingExchange
//    ; can receive RTVolume tick
// 44 = can receive end market for ticker snapshot
// 45 = can receive notHeld field in openOrder
// 46 = can receive contractMonth, industry, category, subcategory fields in contractDetails
//    ; can receive timeZoneId, tradingHours, liquidHours fields in contractDetails
// 47 = can receive gamma, vega, theta, undPrice fields in TICK_OPTION_COMPUTATION
// 48 = can receive exemptCode in openOrder
// 49 = can receive hedgeType and hedgeParam in openOrder
// 50 = can receive optOutSmartRouting field in openOrder
// 51 = can receive smartComboRoutingParams in openOrder
// 52 = can receive deltaNeutralConId, deltaNeutralSettlingFirm, deltaNeutralClearingAccount and deltaNeutralClearingIntent in openOrder
// 53 = can receive orderRef in execution
// 54 = can receive scale order fields (PriceAdjustValue, PriceAdjustInterval, ProfitOffset, AutoReset,
//      InitPosition, InitFillQty and RandomPercent) in openOrder
// 55 = can receive orderComboLegs (price) in openOrder
// 56 = can receive trailingPercent in openOrder
// 57 = can receive commissionReport message
// 58 = can receive CUSIP/ISIN/etc. in contractDescription/bondContractDescription
// 59 = can receive evRule, evMultiplier in contractDescription/bondContractDescription/executionDetails
//      can receive multiplier in executionDetails
// 60 = can receive deltaNeutralOpenClose, deltaNeutralShortSale, deltaNeutralShortSaleSlot
//      and deltaNeutralDesignatedLocation in openOrder
//      can receive position, positionEnd, accountSummary and accountSummaryEnd
// 61 = can receive multiplier in openOrder
//      can receive tradingClass in openOrder, updatePortfolio, execDetails and position
// 62 = can receive avgCost in position message
// 63 = can receive verifyMessageAPI, verifyCompleted, displayGroupList and displayGroupUpdated messages
// 64 = can receive solicited attrib in openOrder message
// 65 = can receive verifyAndAuthMessageAPI and verifyAndAuthCompleted messages
// 66 = can receive randomize size and randomize price order fields

const int CLIENT_VERSION    = 66;


// outgoing msg id's
const int REQ_MKT_DATA                  = 1;
const int CANCEL_MKT_DATA               = 2;
const int PLACE_ORDER                   = 3;
const int CANCEL_ORDER                  = 4;
const int REQ_OPEN_ORDERS               = 5;
const int REQ_ACCT_DATA                 = 6;
const int REQ_EXECUTIONS                = 7;
const int REQ_IDS                       = 8;
const int REQ_CONTRACT_DATA             = 9;
const int REQ_MKT_DEPTH                 = 10;
const int CANCEL_MKT_DEPTH              = 11;
const int REQ_NEWS_BULLETINS            = 12;
const int CANCEL_NEWS_BULLETINS         = 13;
const int SET_SERVER_LOGLEVEL           = 14;
const int REQ_AUTO_OPEN_ORDERS          = 15;
const int REQ_ALL_OPEN_ORDERS           = 16;
const int REQ_MANAGED_ACCTS             = 17;
const int REQ_FA                        = 18;
const int REPLACE_FA                    = 19;
const int REQ_HISTORICAL_DATA           = 20;
const int EXERCISE_OPTIONS              = 21;
const int REQ_SCANNER_SUBSCRIPTION      = 22;
const int CANCEL_SCANNER_SUBSCRIPTION   = 23;
const int REQ_SCANNER_PARAMETERS        = 24;
const int CANCEL_HISTORICAL_DATA        = 25;
const int REQ_CURRENT_TIME              = 49;
const int REQ_REAL_TIME_BARS            = 50;
const int CANCEL_REAL_TIME_BARS         = 51;
const int REQ_FUNDAMENTAL_DATA          = 52;
const int CANCEL_FUNDAMENTAL_DATA       = 53;
const int REQ_CALC_IMPLIED_VOLAT        = 54;
const int REQ_CALC_OPTION_PRICE         = 55;
const int CANCEL_CALC_IMPLIED_VOLAT     = 56;
const int CANCEL_CALC_OPTION_PRICE      = 57;
const int REQ_GLOBAL_CANCEL             = 58;
const int REQ_MARKET_DATA_TYPE          = 59;
const int REQ_POSITIONS                 = 61;
const int REQ_ACCOUNT_SUMMARY           = 62;
const int CANCEL_ACCOUNT_SUMMARY        = 63;
const int CANCEL_POSITIONS              = 64;
const int VERIFY_REQUEST                = 65;
const int VERIFY_MESSAGE                = 66;
const int QUERY_DISPLAY_GROUPS          = 67;
const int SUBSCRIBE_TO_GROUP_EVENTS     = 68;
const int UPDATE_DISPLAY_GROUP          = 69;
const int UNSUBSCRIBE_FROM_GROUP_EVENTS = 70;
const int START_API                     = 71;
const int VERIFY_AND_AUTH_REQUEST       = 72;
const int VERIFY_AND_AUTH_MESSAGE       = 73;
const int REQ_POSITIONS_MULTI           = 74;
const int CANCEL_POSITIONS_MULTI        = 75;
const int REQ_ACCOUNT_UPDATES_MULTI     = 76;
const int CANCEL_ACCOUNT_UPDATES_MULTI  = 77;
const int REQ_SEC_DEF_OPT_PARAMS		= 78;
const int REQ_SOFT_DOLLAR_TIERS			= 79;

// TWS New Bulletins constants
const int NEWS_MSG              = 1;    // standard IB news bulleting message
const int EXCHANGE_AVAIL_MSG    = 2;    // control message specifing that an exchange is available for trading
const int EXCHANGE_UNAVAIL_MSG  = 3;    // control message specifing that an exchange is unavailable for trading

} // namespace client_constants
} // namespace ibapi

struct Contract;
struct Order;
struct ExecutionFilter;
struct ScannerSubscription;
struct ETransport;

class EWrapper;
typedef std::vector<char> BytesVec;


class TWSAPIDLLEXP EClient
{
public:

	explicit EClient(EWrapper *ptr, ETransport *pTransport);
	~EClient();

	virtual void eDisconnect() = 0;

	int clientId() const { return m_clientId; }

	const std::string& optionalCapabilities() const;
	void setOptionalCapabilities(const std::string& optCapts);

	void setConnectOptions(const std::string& connectOptions);
	void disableUseV100Plus();
	bool usingV100Plus();

protected:

	void eConnectBase();
	void eDisconnectBase();

public:

	enum ConnState {
		CS_DISCONNECTED,
		CS_CONNECTING,
		CS_CONNECTED,
		CS_REDIRECT
	};

	// connection state
	ConnState connState() const;
	bool isConnected() const;

	const std::string& host() const { return m_host; }
	unsigned port() const { return m_port; }

public:

	// access to protected variables
	EWrapper * getWrapper() const;
protected:
	void setClientId( int clientId);
	void setExtraAuth( bool extraAuth);
	void setHost( const std::string& host);
	void setPort( unsigned port);

public:

	bool isInBufferEmpty() const;

	// override virtual funcs from EClient
	int serverVersion();
	std::string TwsConnectionTime();
	void reqMktData(TickerId id, const Contract& contract,
		const std::string& genericTicks, bool snapshot, const TagValueListSPtr& mktDataOptions);
	void cancelMktData(TickerId id);
	void placeOrder(OrderId id, const Contract& contract, const Order& order);
	void cancelOrder(OrderId id) ;
	void reqOpenOrders();
	void reqAccountUpdates(bool subscribe, const std::string& acctCode);
	void reqExecutions(int reqId, const ExecutionFilter& filter);
	void reqIds(int numIds);
	void reqContractDetails(int reqId, const Contract& contract);
	void reqMktDepth(TickerId tickerId, const Contract& contract, int numRows, const TagValueListSPtr& mktDepthOptions);
	void cancelMktDepth(TickerId tickerId);
	void reqNewsBulletins(bool allMsgs);
	void cancelNewsBulletins();
	void setServerLogLevel(int level);
	void reqAutoOpenOrders(bool bAutoBind);
	void reqAllOpenOrders();
	void reqManagedAccts();
	void requestFA(faDataType pFaDataType);
	void replaceFA(faDataType pFaDataType, const std::string& cxml);
	void reqHistoricalData( TickerId id, const Contract& contract,
		const std::string& endDateTime, const std::string& durationStr,
		const std::string&  barSizeSetting, const std::string& whatToShow,
		int useRTH, int formatDate, const TagValueListSPtr& chartOptions);
	void exerciseOptions(TickerId tickerId, const Contract& contract,
		int exerciseAction, int exerciseQuantity,
		const std::string& account, int override);
	void cancelHistoricalData(TickerId tickerId );
	void reqRealTimeBars(TickerId id, const Contract& contract, int barSize,
		const std::string& whatToShow, bool useRTH, const TagValueListSPtr& realTimeBarsOptions);
	void cancelRealTimeBars(TickerId tickerId );
	void cancelScannerSubscription(int tickerId);
	void reqScannerParameters();
	void reqScannerSubscription(int tickerId, const ScannerSubscription& subscription, const TagValueListSPtr& scannerSubscriptionOptions);
	void reqCurrentTime();
	void reqFundamentalData(TickerId reqId, const Contract&, const std::string& reportType);
	void cancelFundamentalData(TickerId reqId);
	void calculateImpliedVolatility(TickerId reqId, const Contract& contract, double optionPrice, double underPrice);
	void calculateOptionPrice(TickerId reqId, const Contract& contract, double volatility, double underPrice);
	void cancelCalculateImpliedVolatility(TickerId reqId);
	void cancelCalculateOptionPrice(TickerId reqId);
	void reqGlobalCancel();
	void reqMarketDataType(int marketDataType);
	void reqPositions();
	void cancelPositions();
	void reqAccountSummary( int reqId, const std::string& groupName, const std::string& tags);
	void cancelAccountSummary( int reqId);
	void verifyRequest( const std::string& apiName, const std::string& apiVersion);
	void verifyMessage( const std::string& apiData);
	void verifyAndAuthRequest( const std::string& apiName, const std::string& apiVersion, const std::string& opaqueIsvKey);
	void verifyAndAuthMessage( const std::string& apiData, const std::string& xyzResponse);
	void queryDisplayGroups( int reqId);
	void subscribeToGroupEvents( int reqId, int groupId);
	void updateDisplayGroup( int reqId, const std::string& contractInfo);
	void unsubscribeFromGroupEvents( int reqId);
	void reqPositionsMulti( int reqId, const std::string& account, const std::string& modelCode);
	void cancelPositionsMulti( int reqId);
	void reqAccountUpdatessMulti( int reqId, const std::string& account, const std::string& modelCode, bool ledgerAndNLV);
	void cancelAccountUpdatesMulti( int reqId);
	void reqSecDefOptParams(int reqId, const std::string& underlyingSymbol, const std::string& futFopExchange, const std::string& underlyingSecType, int underlyingConId);
	void reqSoftDollarTiers(int reqId);

private:

	virtual int receive(char* buf, size_t sz) = 0;

protected:

	virtual void prepareBufferImpl(std::ostream&) const = 0;
	virtual void prepareBuffer(std::ostream&) const = 0;
	virtual bool closeAndSend(std::string msg, unsigned offset = 0) = 0;
	virtual int bufferedSend(const std::string& msg);

protected:
	int bufferedRead();

	// try to process connection request ack
private:
	// try to process single msg
	int processMsgImpl(const char*& ptr, const char* endPtr);
	int processMsg(const char*& ptr, const char* endPtr);

	typedef int (EClient::*messageHandler)(const char*& ptr, const char* endPtr);
	int processOnePrefixedMsg(const char*& ptr, const char* endPtr, messageHandler);

public:
	void startApi();


	// encoders
	template<class T> static void EncodeField(std::ostream&, T);

	// "max" encoders
	static void EncodeFieldMax(std::ostream& os, int);
	static void EncodeFieldMax(std::ostream& os, double);

	// socket state
private:
	virtual bool isSocketOK() const = 0;

protected:

	bool isConnecting() const;
	int sendConnectRequest();
    bool extraAuth();

protected:

	EWrapper *m_pEWrapper;
    std::auto_ptr<ETransport> m_transport;

private:
	BytesVec m_inBuffer;

	std::string m_host;
	int m_port;

	int m_clientId;

	ConnState m_connState;
	bool m_extraAuth;

protected:
	int m_serverVersion;
	std::string m_TwsTime;

private:
	std::string m_optionalCapabilities;

	std::string m_connectOptions;

protected:
	bool m_useV100Plus;

};

template<> void EClient::EncodeField<bool>(std::ostream& os, bool);
template<> void EClient::EncodeField<double>(std::ostream& os, double);

#define ENCODE_FIELD(x) EClient::EncodeField(msg, x);
#define ENCODE_FIELD_MAX(x) EClient::EncodeFieldMax(msg, x);


#endif
