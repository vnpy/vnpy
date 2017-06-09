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

case ONRSPQRYORDER:
{
	this->processRspQryOrder(task);
	break;
}

case ONRSPQRYTRADINGACCOUNT:
{
	this->processRspQryTradingAccount(task);
	break;
}

case ONRSPQRYINVESTOR:
{
	this->processRspQryInvestor(task);
	break;
}

case ONRSPQRYINSTRUMENT:
{
	this->processRspQryInstrument(task);
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

case ONRTNINSTRUMENTSTATUS:
{
	this->processRtnInstrumentStatus(task);
	break;
}

case ONRSPQRYINVESTORPOSITIONDETAIL:
{
	this->processRspQryInvestorPositionDetail(task);
	break;
}

case ONRSPQRYINVESTORPOSITION:
{
	this->processRspQryInvestorPosition(task);
	break;
}

