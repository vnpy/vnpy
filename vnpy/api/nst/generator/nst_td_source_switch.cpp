case ONFRONTCONNECTED:
{
	this->processFrontConnected(&task);
	break;
}

case ONRSPUSERLOGIN:
{
	this->processRspUserLogin(&task);
	break;
}

case ONANSORDERINSERT:
{
	this->processAnsOrderInsert(&task);
	break;
}

case ONRSPORDERINSERT:
{
	this->processRspOrderInsert(&task);
	break;
}

case ONANSORDERACTION:
{
	this->processAnsOrderAction(&task);
	break;
}

case ONRSPORDERACTION:
{
	this->processRspOrderAction(&task);
	break;
}

case ONORDERRTN:
{
	this->processOrderRtn(&task);
	break;
}

case ONTRADERTN:
{
	this->processTradeRtn(&task);
	break;
}

case ONRSPTRADINGACCOUNT:
{
	this->processRspTradingAccount(&task);
	break;
}

case ONRSPERROR:
{
	this->processRspError(&task);
	break;
}

case ONRSPQRYORDER:
{
	this->processRspQryOrder(&task);
	break;
}

case ONRSPQRYTRADE:
{
	this->processRspQryTrade(&task);
	break;
}

case ONRSPQRYINVESTORPOSITION:
{
	this->processRspQryInvestorPosition(&task);
	break;
}

case ONRSPQRYCHANGEPWD:
{
	this->processRspQryChangePwd(&task);
	break;
}

case ONRSPLOGOUT:
{
	this->processRspLogout(&task);
	break;
}

case ONRTNINSTRUMENTSTATUS:
{
	this->processRtnInstrumentStatus(&task);
	break;
}

case ONRSPTEST:
{
	this->processRspTest(&task);
	break;
}

case ONERRRTNORDERINSERT:
{
	this->processErrRtnOrderInsert(&task);
	break;
}

case ONERRRTNORDERACTION:
{
	this->processErrRtnOrderAction(&task);
	break;
}

