case ONFRONTCONNECTED:
{
	this->processFrontConnected(&task);
	break;
}

case ONFRONTDISCONNECTED:
{
	this->processFrontDisconnected(&task);
	break;
}

case ONRTNNOTICE:
{
	this->processRtnNotice(&task);
	break;
}

case ONRSPERROR:
{
	this->processRspError(&task);
	break;
}

case ONRSPSTOCKUSERLOGIN:
{
	this->processRspStockUserLogin(&task);
	break;
}

case ONRSPSTOCKUSERLOGOUT:
{
	this->processRspStockUserLogout(&task);
	break;
}

case ONRSPSOPUSERLOGIN:
{
	this->processRspSOPUserLogin(&task);
	break;
}

case ONRSPSOPUSERLOGOUT:
{
	this->processRspSOPUserLogout(&task);
	break;
}

case ONRSPFASLUSERLOGIN:
{
	this->processRspFASLUserLogin(&task);
	break;
}

case ONRSPFASLUSERLOGOUT:
{
	this->processRspFASLUserLogout(&task);
	break;
}

case ONRSPSTOCKSUBMARKETDATA:
{
	this->processRspStockSubMarketData(&task);
	break;
}

case ONRSPSTOCKUNSUBMARKETDATA:
{
	this->processRspStockUnSubMarketData(&task);
	break;
}

case ONRSPSOPSUBMARKETDATA:
{
	this->processRspSOPSubMarketData(&task);
	break;
}

case ONRSPSOPUNSUBMARKETDATA:
{
	this->processRspSOPUnSubMarketData(&task);
	break;
}

case ONSTOCKMARKETDATA:
{
	this->processStockMarketData(&task);
	break;
}

case ONSOPMARKETDATA:
{
	this->processSOPMarketData(&task);
	break;
}

case ONRSPSTOCKAVAILABLEQUOT:
{
	this->processRspStockAvailableQuot(&task);
	break;
}

case ONRSPSOPAVAILABLEQUOT:
{
	this->processRspSopAvailableQuot(&task);
	break;
}

case ONRSPUSERMDPASSWORDUPDATE:
{
	this->processRspUserMDPasswordUpdate(&task);
	break;
}

