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

case ONRSPQRYTRADINGCODE:
{
	this->processRspQryTradingCode(task);
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

case ONRSPQRYCOMPLIANCEPARAM:
{
	this->processRspQryComplianceParam(task);
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

