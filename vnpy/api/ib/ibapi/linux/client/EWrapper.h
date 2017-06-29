/* Copyright (C) 2013 Interactive Brokers LLC. All rights reserved. This code is subject to the terms
 * and conditions of the IB API Non-Commercial License or the IB API Commercial License, as applicable. */

#pragma once
#ifndef ewrapper_def
#define ewrapper_def

#include "CommonDefs.h"
#include "SoftDollarTier.h"
#include <string>
#include <set>

enum TickType { BID_SIZE, BID, ASK, ASK_SIZE, LAST, LAST_SIZE,
				HIGH, LOW, VOLUME, CLOSE,
				BID_OPTION_COMPUTATION,
				ASK_OPTION_COMPUTATION,
				LAST_OPTION_COMPUTATION,
				MODEL_OPTION,
				OPEN,
				LOW_13_WEEK,
				HIGH_13_WEEK,
				LOW_26_WEEK,
				HIGH_26_WEEK,
				LOW_52_WEEK,
				HIGH_52_WEEK,
				AVG_VOLUME,
				OPEN_INTEREST,
				OPTION_HISTORICAL_VOL,
				OPTION_IMPLIED_VOL,
				OPTION_BID_EXCH,
				OPTION_ASK_EXCH,
				OPTION_CALL_OPEN_INTEREST,
				OPTION_PUT_OPEN_INTEREST,
				OPTION_CALL_VOLUME,
				OPTION_PUT_VOLUME,
				INDEX_FUTURE_PREMIUM,
				BID_EXCH,
				ASK_EXCH,
				AUCTION_VOLUME,
				AUCTION_PRICE,
				AUCTION_IMBALANCE,
				MARK_PRICE,
				BID_EFP_COMPUTATION,
				ASK_EFP_COMPUTATION,
				LAST_EFP_COMPUTATION,
				OPEN_EFP_COMPUTATION,
				HIGH_EFP_COMPUTATION,
				LOW_EFP_COMPUTATION,
				CLOSE_EFP_COMPUTATION,
				LAST_TIMESTAMP,
				SHORTABLE,
				FUNDAMENTAL_RATIOS,
				RT_VOLUME,
				HALTED,
				BID_YIELD,
				ASK_YIELD,
				LAST_YIELD,
				CUST_OPTION_COMPUTATION,
				TRADE_COUNT,
				TRADE_RATE,
				VOLUME_RATE,
				LAST_RTH_TRADE,
				RT_HISTORICAL_VOL,
				IB_DIVIDENDS,
				BOND_FACTOR_MULTIPLIER,
				REGULATORY_IMBALANCE,
				NEWS_TICK,
				SHORT_TERM_VOLUME_3_MIN,
				SHORT_TERM_VOLUME_5_MIN,
				SHORT_TERM_VOLUME_10_MIN,
				DELAYED_BID,
				DELAYED_ASK,
				DELAYED_LAST,
				DELAYED_BID_SIZE,
				DELAYED_ASK_SIZE,
				DELAYED_LAST_SIZE,
				DELAYED_HIGH,
				DELAYED_LOW,
				DELAYED_VOLUME,
				DELAYED_CLOSE,
				DELAYED_OPEN,
				RT_TRD_VOLUME,
				CREDITMAN_MARK_PRICE,
				CREDITMAN_SLOW_MARK_PRICE,
				NOT_SET };

inline bool isPrice( TickType tickType) {
	return tickType == BID || tickType == ASK || tickType == LAST;
}

struct Contract;
struct ContractDetails;
struct Order;
struct OrderState;
struct Execution;
struct UnderComp;
struct CommissionReport;

class EWrapper
{
public:
   virtual ~EWrapper() {};

   virtual void tickPrice( TickerId tickerId, TickType field, double price, int canAutoExecute) = 0;
   virtual void tickSize( TickerId tickerId, TickType field, int size) = 0;
   virtual void tickOptionComputation( TickerId tickerId, TickType tickType, double impliedVol, double delta,
	   double optPrice, double pvDividend, double gamma, double vega, double theta, double undPrice) = 0;
   virtual void tickGeneric(TickerId tickerId, TickType tickType, double value) = 0;
   virtual void tickString(TickerId tickerId, TickType tickType, const std::string& value) = 0;
   virtual void tickEFP(TickerId tickerId, TickType tickType, double basisPoints, const std::string& formattedBasisPoints,
	   double totalDividends, int holdDays, const std::string& futureLastTradeDate, double dividendImpact, double dividendsToLastTradeDate) = 0;
   virtual void orderStatus( OrderId orderId, const std::string& status, double filled,
	   double remaining, double avgFillPrice, int permId, int parentId,
	   double lastFillPrice, int clientId, const std::string& whyHeld) = 0;
   virtual void openOrder( OrderId orderId, const Contract&, const Order&, const OrderState&) = 0;
   virtual void openOrderEnd() = 0;
   virtual void winError( const std::string& str, int lastError) = 0;
   virtual void connectionClosed() = 0;
   virtual void updateAccountValue(const std::string& key, const std::string& val,
   const std::string& currency, const std::string& accountName) = 0;
   virtual void updatePortfolio( const Contract& contract, double position,
      double marketPrice, double marketValue, double averageCost,
      double unrealizedPNL, double realizedPNL, const std::string& accountName) = 0;
   virtual void updateAccountTime(const std::string& timeStamp) = 0;
   virtual void accountDownloadEnd(const std::string& accountName) = 0;
   virtual void nextValidId( OrderId orderId) = 0;
   virtual void contractDetails( int reqId, const ContractDetails& contractDetails) = 0;
   virtual void bondContractDetails( int reqId, const ContractDetails& contractDetails) = 0;
   virtual void contractDetailsEnd( int reqId) = 0;
   virtual void execDetails( int reqId, const Contract& contract, const Execution& execution) =0;
   virtual void execDetailsEnd( int reqId) =0;
   virtual void error(const int id, const int errorCode, const std::string errorString) = 0;
   virtual void updateMktDepth(TickerId id, int position, int operation, int side,
      double price, int size) = 0;
   virtual void updateMktDepthL2(TickerId id, int position, std::string marketMaker, int operation,
      int side, double price, int size) = 0;
   virtual void updateNewsBulletin(int msgId, int msgType, const std::string& newsMessage, const std::string& originExch) = 0;
   virtual void managedAccounts( const std::string& accountsList) = 0;
   virtual void receiveFA(faDataType pFaDataType, const std::string& cxml) = 0;
   virtual void historicalData(TickerId reqId, const std::string& date, double open, double high, 
	   double low, double close, int volume, int barCount, double WAP, int hasGaps) = 0;
   virtual void scannerParameters(const std::string& xml) = 0;
   virtual void scannerData(int reqId, int rank, const ContractDetails& contractDetails,
	   const std::string& distance, const std::string& benchmark, const std::string& projection,
	   const std::string& legsStr) = 0;
   virtual void scannerDataEnd(int reqId) = 0;
   virtual void realtimeBar(TickerId reqId, long time, double open, double high, double low, double close,
	   long volume, double wap, int count) = 0;
   virtual void currentTime(long time) = 0;
   virtual void fundamentalData(TickerId reqId, const std::string& data) = 0;
   virtual void deltaNeutralValidation(int reqId, const UnderComp& underComp) = 0;
   virtual void tickSnapshotEnd( int reqId) = 0;
   virtual void marketDataType( TickerId reqId, int marketDataType) = 0;
   virtual void commissionReport( const CommissionReport& commissionReport) = 0;
   virtual void position( const std::string& account, const Contract& contract, double position, double avgCost) = 0;
   virtual void positionEnd() = 0;
   virtual void accountSummary( int reqId, const std::string& account, const std::string& tag, const std::string& value, const std::string& curency) = 0;
   virtual void accountSummaryEnd( int reqId) = 0;
   virtual void verifyMessageAPI( const std::string& apiData) = 0;
   virtual void verifyCompleted( bool isSuccessful, const std::string& errorText) = 0;
   virtual void displayGroupList( int reqId, const std::string& groups) = 0;
   virtual void displayGroupUpdated( int reqId, const std::string& contractInfo) = 0;
   virtual void verifyAndAuthMessageAPI( const std::string& apiData, const std::string& xyzChallange) = 0;
   virtual void verifyAndAuthCompleted( bool isSuccessful, const std::string& errorText) = 0;
   virtual void connectAck() = 0;
   virtual void positionMulti( int reqId, const std::string& account,const std::string& modelCode, const Contract& contract, double pos, double avgCost) = 0;
   virtual void positionMultiEnd( int reqId) = 0;
   virtual void accountUpdateMulti( int reqId, const std::string& account, const std::string& modelCode, const std::string& key, const std::string& value, const std::string& currency) = 0;
   virtual void accountUpdateMultiEnd( int reqId) = 0;
   virtual void securityDefinitionOptionalParameter(int reqId, const std::string& exchange, int underlyingConId, const std::string& tradingClass, const std::string& multiplier, std::set<std::string> expirations, std::set<double> strikes) = 0;
   virtual void securityDefinitionOptionalParameterEnd(int reqId) = 0;
   virtual void softDollarTiers(int reqId, const std::vector<SoftDollarTier> &tiers) = 0;
};


#endif
