/* Copyright (C) 2013 Interactive Brokers LLC. All rights reserved. This code is subject to the terms
 * and conditions of the IB API Non-Commercial License or the IB API Commercial License, as applicable. */

#include "StdAfx.h"
#include "DefaultEWrapper.h"

void DefaultEWrapper::tickPrice( TickerId tickerId, TickType field, double price, int canAutoExecute) { }
void DefaultEWrapper::tickSize( TickerId tickerId, TickType field, int size) { }
void DefaultEWrapper::tickOptionComputation( TickerId tickerId, TickType tickType, double impliedVol, double delta,
	   double optPrice, double pvDividend, double gamma, double vega, double theta, double undPrice) { }
void DefaultEWrapper::tickGeneric(TickerId tickerId, TickType tickType, double value) { }
void DefaultEWrapper::tickString(TickerId tickerId, TickType tickType, const std::string& value) { }
void DefaultEWrapper::tickEFP(TickerId tickerId, TickType tickType, double basisPoints, const std::string& formattedBasisPoints,
	   double totalDividends, int holdDays, const std::string& futureLastTradeDate, double dividendImpact, double dividendsToLastTradeDate) { }
void DefaultEWrapper::orderStatus( OrderId orderId, const std::string& status, double filled,
	   double remaining, double avgFillPrice, int permId, int parentId,
	   double lastFillPrice, int clientId, const std::string& whyHeld) { }
void DefaultEWrapper::openOrder( OrderId orderId, const Contract&, const Order&, const OrderState&) { }
void DefaultEWrapper::openOrderEnd() { }
void DefaultEWrapper::winError( const std::string& str, int lastError) { }
void DefaultEWrapper::connectionClosed() { }
void DefaultEWrapper::updateAccountValue(const std::string& key, const std::string& val,
   const std::string& currency, const std::string& accountName) { }
void DefaultEWrapper::updatePortfolio( const Contract& contract, double position,
      double marketPrice, double marketValue, double averageCost,
      double unrealizedPNL, double realizedPNL, const std::string& accountName) { }
void DefaultEWrapper::updateAccountTime(const std::string& timeStamp) { }
void DefaultEWrapper::accountDownloadEnd(const std::string& accountName) { }
void DefaultEWrapper::nextValidId( OrderId orderId) { }
void DefaultEWrapper::contractDetails( int reqId, const ContractDetails& contractDetails) { }
void DefaultEWrapper::bondContractDetails( int reqId, const ContractDetails& contractDetails) { }
void DefaultEWrapper::contractDetailsEnd( int reqId) { }
void DefaultEWrapper::execDetails( int reqId, const Contract& contract, const Execution& execution) { }
void DefaultEWrapper::execDetailsEnd( int reqId) { }
void DefaultEWrapper::error(const int id, const int errorCode, const std::string errorString) { }
void DefaultEWrapper::updateMktDepth(TickerId id, int position, int operation, int side,
      double price, int size) { }
void DefaultEWrapper::updateMktDepthL2(TickerId id, int position, std::string marketMaker, int operation,
      int side, double price, int size) { }
void DefaultEWrapper::updateNewsBulletin(int msgId, int msgType, const std::string& newsMessage, const std::string& originExch) { }
void DefaultEWrapper::managedAccounts( const std::string& accountsList) { }
void DefaultEWrapper::receiveFA(faDataType pFaDataType, const std::string& cxml) { }
void DefaultEWrapper::historicalData(TickerId reqId, const std::string& date, double open, double high, 
	   double low, double close, int volume, int barCount, double WAP, int hasGaps) { }
void DefaultEWrapper::scannerParameters(const std::string& xml) { }
void DefaultEWrapper::scannerData(int reqId, int rank, const ContractDetails& contractDetails,
	   const std::string& distance, const std::string& benchmark, const std::string& projection,
	   const std::string& legsStr) { }
void DefaultEWrapper::scannerDataEnd(int reqId) { }
void DefaultEWrapper::realtimeBar(TickerId reqId, long time, double open, double high, double low, double close,
	   long volume, double wap, int count) { }
void DefaultEWrapper::currentTime(long time) { }
void DefaultEWrapper::fundamentalData(TickerId reqId, const std::string& data) { }
void DefaultEWrapper::deltaNeutralValidation(int reqId, const UnderComp& underComp) { }
void DefaultEWrapper::tickSnapshotEnd( int reqId) { }
void DefaultEWrapper::marketDataType( TickerId reqId, int marketDataType) { }
void DefaultEWrapper::commissionReport( const CommissionReport& commissionReport) { }
void DefaultEWrapper::position( const std::string& account, const Contract& contract, double position, double avgCost) { }
void DefaultEWrapper::positionEnd() { }
void DefaultEWrapper::accountSummary( int reqId, const std::string& account, const std::string& tag, const std::string& value, const std::string& curency) { }
void DefaultEWrapper::accountSummaryEnd( int reqId) { }
void DefaultEWrapper::verifyMessageAPI( const std::string& apiData) { }
void DefaultEWrapper::verifyCompleted( bool isSuccessful, const std::string& errorText) { }
void DefaultEWrapper::displayGroupList( int reqId, const std::string& groups) { }
void DefaultEWrapper::displayGroupUpdated( int reqId, const std::string& contractInfo) { }
void DefaultEWrapper::verifyAndAuthMessageAPI( const std::string& apiData, const std::string& xyzChallange) { }
void DefaultEWrapper::verifyAndAuthCompleted( bool isSuccessful, const std::string& errorText) { }
void DefaultEWrapper::connectAck() { }
void DefaultEWrapper::positionMulti( int reqId, const std::string& account,const std::string& modelCode, const Contract& contract, double pos, double avgCost) { }
void DefaultEWrapper::positionMultiEnd( int reqId) { }
void DefaultEWrapper::accountUpdateMulti( int reqId, const std::string& account, const std::string& modelCode, const std::string& key, const std::string& value, const std::string& currency) { }
void DefaultEWrapper::accountUpdateMultiEnd( int reqId) { }
void DefaultEWrapper::securityDefinitionOptionalParameter(int reqId, const std::string& exchange, int underlyingConId, const std::string& tradingClass, const std::string& multiplier, std::set<std::string> expirations, std::set<double> strikes) { }
void DefaultEWrapper::securityDefinitionOptionalParameterEnd(int reqId) { }
void DefaultEWrapper::softDollarTiers(int reqId, const std::vector<SoftDollarTier> &tiers) { }


