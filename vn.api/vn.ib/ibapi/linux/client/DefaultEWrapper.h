/* Copyright (C) 2013 Interactive Brokers LLC. All rights reserved. This code is subject to the terms
 * and conditions of the IB API Non-Commercial License or the IB API Commercial License, as applicable. */

#pragma once
#include "EWrapper.h"

class TWSAPIDLLEXP DefaultEWrapper :
    public EWrapper
{
public:
   virtual void tickPrice( TickerId tickerId, TickType field, double price, int canAutoExecute);
   virtual void tickSize( TickerId tickerId, TickType field, int size);
   virtual void tickOptionComputation( TickerId tickerId, TickType tickType, double impliedVol, double delta,
	   double optPrice, double pvDividend, double gamma, double vega, double theta, double undPrice);
   virtual void tickGeneric(TickerId tickerId, TickType tickType, double value);
   virtual void tickString(TickerId tickerId, TickType tickType, const std::string& value);
   virtual void tickEFP(TickerId tickerId, TickType tickType, double basisPoints, const std::string& formattedBasisPoints,
	   double totalDividends, int holdDays, const std::string& futureLastTradeDate, double dividendImpact, double dividendsToLastTradeDate);
   virtual void orderStatus( OrderId orderId, const std::string& status, double filled,
	   double remaining, double avgFillPrice, int permId, int parentId,
	   double lastFillPrice, int clientId, const std::string& whyHeld);
   virtual void openOrder( OrderId orderId, const Contract&, const Order&, const OrderState&);
   virtual void openOrderEnd();
   virtual void winError( const std::string& str, int lastError);
   virtual void connectionClosed();
   virtual void updateAccountValue(const std::string& key, const std::string& val,
   const std::string& currency, const std::string& accountName);
   virtual void updatePortfolio( const Contract& contract, double position,
      double marketPrice, double marketValue, double averageCost,
      double unrealizedPNL, double realizedPNL, const std::string& accountName);
   virtual void updateAccountTime(const std::string& timeStamp);
   virtual void accountDownloadEnd(const std::string& accountName);
   virtual void nextValidId( OrderId orderId);
   virtual void contractDetails( int reqId, const ContractDetails& contractDetails);
   virtual void bondContractDetails( int reqId, const ContractDetails& contractDetails);
   virtual void contractDetailsEnd( int reqId);
   virtual void execDetails( int reqId, const Contract& contract, const Execution& execution);
   virtual void execDetailsEnd( int reqId);
   virtual void error(const int id, const int errorCode, const std::string errorString);
   virtual void updateMktDepth(TickerId id, int position, int operation, int side,
      double price, int size);
   virtual void updateMktDepthL2(TickerId id, int position, std::string marketMaker, int operation,
      int side, double price, int size);
   virtual void updateNewsBulletin(int msgId, int msgType, const std::string& newsMessage, const std::string& originExch);
   virtual void managedAccounts( const std::string& accountsList);
   virtual void receiveFA(faDataType pFaDataType, const std::string& cxml);
   virtual void historicalData(TickerId reqId, const std::string& date, double open, double high, 
	   double low, double close, int volume, int barCount, double WAP, int hasGaps);
   virtual void scannerParameters(const std::string& xml);
   virtual void scannerData(int reqId, int rank, const ContractDetails& contractDetails,
	   const std::string& distance, const std::string& benchmark, const std::string& projection,
	   const std::string& legsStr);
   virtual void scannerDataEnd(int reqId);
   virtual void realtimeBar(TickerId reqId, long time, double open, double high, double low, double close,
	   long volume, double wap, int count);
   virtual void currentTime(long time);
   virtual void fundamentalData(TickerId reqId, const std::string& data);
   virtual void deltaNeutralValidation(int reqId, const UnderComp& underComp);
   virtual void tickSnapshotEnd( int reqId);
   virtual void marketDataType( TickerId reqId, int marketDataType);
   virtual void commissionReport( const CommissionReport& commissionReport);
   virtual void position( const std::string& account, const Contract& contract, double position, double avgCost);
   virtual void positionEnd();
   virtual void accountSummary( int reqId, const std::string& account, const std::string& tag, const std::string& value, const std::string& curency);
   virtual void accountSummaryEnd( int reqId);
   virtual void verifyMessageAPI( const std::string& apiData);
   virtual void verifyCompleted( bool isSuccessful, const std::string& errorText);
   virtual void displayGroupList( int reqId, const std::string& groups);
   virtual void displayGroupUpdated( int reqId, const std::string& contractInfo);
   virtual void verifyAndAuthMessageAPI( const std::string& apiData, const std::string& xyzChallange);
   virtual void verifyAndAuthCompleted( bool isSuccessful, const std::string& errorText);
   virtual void connectAck();
   virtual void positionMulti( int reqId, const std::string& account,const std::string& modelCode, const Contract& contract, double pos, double avgCost);
   virtual void positionMultiEnd( int reqId);
   virtual void accountUpdateMulti( int reqId, const std::string& account, const std::string& modelCode, const std::string& key, const std::string& value, const std::string& currency);
   virtual void accountUpdateMultiEnd( int reqId);
   virtual void securityDefinitionOptionalParameter(int reqId, const std::string& exchange, int underlyingConId, const std::string& tradingClass, const std::string& multiplier, std::set<std::string> expirations, std::set<double> strikes);
   virtual void securityDefinitionOptionalParameterEnd(int reqId);
   virtual void softDollarTiers(int reqId, const std::vector<SoftDollarTier> &tiers);
};

