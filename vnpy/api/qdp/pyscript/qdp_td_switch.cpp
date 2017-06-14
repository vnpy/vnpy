case ONFRONTCONNECTED:
{
	this->processFrontConnected(task);
	break;
}

case ONFRONTDISCONNECTED:
{
	this->processFrontDisconnected(task);
	break;
}

case ONHEARTBEATWARNING:
{
	this->processHeartBeatWarning(task);
	break;
}

case ONPACKAGESTART:
{
	this->processPackageStart(task);
	break;
}

case ONPACKAGEEND:
{
	this->processPackageEnd(task);
	break;
}

case ONRSPERROR:
{
	this->processRspError(task);
	break;
}

case ONRSPUSERLOGIN:
{
	this->processRspUserLogin(task);
	break;
}

case ONRSPUSERLOGOUT:
{
	this->processRspUserLogout(task);
	break;
}

case ONRSPUSERPASSWORDUPDATE:
{
	this->processRspUserPasswordUpdate(task);
	break;
}

case ONRSPORDERINSERT:
{
	this->processRspOrderInsert(task);
	break;
}

case ONRSPORDERACTION:
{
	this->processRspOrderAction(task);
	break;
}

case ONRSPFROMBANKTOFUTUREBYFUTURE:
{
	this->processRspFromBankToFutureByFuture(task);
	break;
}

case ONRSPFROMFUTURETOBANKBYFUTURE:
{
	this->processRspFromFutureToBankByFuture(task);
	break;
}

case ONRTNFLOWMESSAGECANCEL:
{
	this->processRtnFlowMessageCancel(task);
	break;
}

case ONRTNTRADE:
{
	this->processRtnTrade(task);
	break;
}

case ONRTNORDER:
{
	this->processRtnOrder(task);
	break;
}

case ONERRRTNORDERINSERT:
{
	this->processErrRtnOrderInsert(task);
	break;
}

case ONERRRTNORDERACTION:
{
	this->processErrRtnOrderAction(task);
	break;
}

case ONRTNINSTRUMENTSTATUS:
{
	this->processRtnInstrumentStatus(task);
	break;
}

case ONRTNINVESTORACCOUNTDEPOSIT:
{
	this->processRtnInvestorAccountDeposit(task);
	break;
}

case ONRTNMESSAGENOTIFY:
{
	this->processRtnMessageNotify(task);
	break;
}

case ONERRRTNQUERYBANKBALANCEBYFUTURE:
{
	this->processErrRtnQueryBankBalanceByFuture(task);
	break;
}

case ONERRRTNBANKTOFUTUREBYFUTURE:
{
	this->processErrRtnBankToFutureByFuture(task);
	break;
}

case ONERRRTNFUTURETOBANKBYFUTURE:
{
	this->processErrRtnFutureToBankByFuture(task);
	break;
}

case ONRTNQUERYBANKBALANCEBYFUTURE:
{
	this->processRtnQueryBankBalanceByFuture(task);
	break;
}

case ONRTNFROMBANKTOFUTUREBYFUTURE:
{
	this->processRtnFromBankToFutureByFuture(task);
	break;
}

case ONRTNFROMFUTURETOBANKBYFUTURE:
{
	this->processRtnFromFutureToBankByFuture(task);
	break;
}

case ONRTNSGEDEFERRATE:
{
	this->processRtnSGEDeferRate(task);
	break;
}

case ONRSPQRYORDER:
{
	this->processRspQryOrder(task);
	break;
}

case ONRSPQRYTRADE:
{
	this->processRspQryTrade(task);
	break;
}

case ONRSPQRYUSERINVESTOR:
{
	this->processRspQryUserInvestor(task);
	break;
}

case ONRSPQRYINVESTORACCOUNT:
{
	this->processRspQryInvestorAccount(task);
	break;
}

case ONRSPQRYINSTRUMENT:
{
	this->processRspQryInstrument(task);
	break;
}

case ONRSPQRYEXCHANGE:
{
	this->processRspQryExchange(task);
	break;
}

case ONRSPQRYINVESTORPOSITION:
{
	this->processRspQryInvestorPosition(task);
	break;
}

case ONRSPSUBSCRIBETOPIC:
{
	this->processRspSubscribeTopic(task);
	break;
}

case ONRSPQRYTOPIC:
{
	this->processRspQryTopic(task);
	break;
}

case ONRSPQRYINVESTORFEE:
{
	this->processRspQryInvestorFee(task);
	break;
}

case ONRSPQRYINVESTORMARGIN:
{
	this->processRspQryInvestorMargin(task);
	break;
}

case ONRSPQRYEXCHANGEDIFFTIME:
{
	this->processRspQryExchangeDiffTime(task);
	break;
}

case ONRSPQRYCONTRACTBANK:
{
	this->processRspQryContractBank(task);
	break;
}

case ONRSPQUERYBANKACCOUNTMONEYBYFUTURE:
{
	this->processRspQueryBankAccountMoneyByFuture(task);
	break;
}

case ONRSPQRYTRANSFERSERIAL:
{
	this->processRspQryTransferSerial(task);
	break;
}

case ONRSPQRYSGEDEFERRATE:
{
	this->processRspQrySGEDeferRate(task);
	break;
}

case ONRSPQRYMARKETDATA:
{
	this->processRspQryMarketData(task);
	break;
}

