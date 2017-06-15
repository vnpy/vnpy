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

case ONRSPFETCHAUTHRANDCODE:
{
	this->processRspFetchAuthRandCode(task);
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

case ONRSPUSERPASSWORDUPDATE:
{
	this->processRspUserPasswordUpdate(task);
	break;
}

case ONRSPTRADINGACCOUNTPASSWORDUPDATE:
{
	this->processRspTradingAccountPasswordUpdate(task);
	break;
}

case ONRTNORDER:
{
	this->processRtnOrder(task);
	break;
}

case ONRTNTRADE:
{
	this->processRtnTrade(task);
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

case ONRSPFUNDOUTBYLIBER:
{
	this->processRspFundOutByLiber(task);
	break;
}

case ONRTNFUNDOUTBYLIBER:
{
	this->processRtnFundOutByLiber(task);
	break;
}

case ONERRRTNFUNDOUTBYLIBER:
{
	this->processErrRtnFundOutByLiber(task);
	break;
}

case ONRTNFUNDINBYBANK:
{
	this->processRtnFundInByBank(task);
	break;
}

case ONRSPFUNDINTERTRANSFER:
{
	this->processRspFundInterTransfer(task);
	break;
}

case ONRTNFUNDINTERTRANSFERSERIAL:
{
	this->processRtnFundInterTransferSerial(task);
	break;
}

case ONERRRTNFUNDINTERTRANSFER:
{
	this->processErrRtnFundInterTransfer(task);
	break;
}

