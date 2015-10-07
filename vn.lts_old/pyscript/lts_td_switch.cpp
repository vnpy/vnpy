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

case ONRSPQRYEXCHANGE:
{
	this->processRspQryExchange(task);
	break;
}

case ONRSPQRYINSTRUMENT:
{
	this->processRspQryInstrument(task);
	break;
}

case ONRSPQRYINVESTOR:
{
	this->processRspQryInvestor(task);
	break;
}

case ONRSPQRYTRADINGCODE:
{
	this->processRspQryTradingCode(task);
	break;
}

case ONRSPQRYTRADINGACCOUNT:
{
	this->processRspQryTradingAccount(task);
	break;
}

case ONRSPQRYDEPTHMARKETDATA:
{
	this->processRspQryDepthMarketData(task);
	break;
}

case ONRSPQRYBONDINTEREST:
{
	this->processRspQryBondInterest(task);
	break;
}

case ONRSPQRYMARKETRATIONINFO:
{
	this->processRspQryMarketRationInfo(task);
	break;
}

case ONRSPQRYINSTRUMENTCOMMISSIONRATE:
{
	this->processRspQryInstrumentCommissionRate(task);
	break;
}

case ONRSPQRYETFINSTRUMENT:
{
	this->processRspQryETFInstrument(task);
	break;
}

case ONRSPQRYETFBASKET:
{
	this->processRspQryETFBasket(task);
	break;
}

case ONRSPQRYOFINSTRUMENT:
{
	this->processRspQryOFInstrument(task);
	break;
}

case ONRSPQRYSFINSTRUMENT:
{
	this->processRspQrySFInstrument(task);
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

case ONRSPQRYINVESTORPOSITION:
{
	this->processRspQryInvestorPosition(task);
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

case ONRSPQRYFUNDTRANSFERSERIAL:
{
	this->processRspQryFundTransferSerial(task);
	break;
}

case ONRSPFUNDINTERTRANSFER:
{
	this->processRspFundInterTransfer(task);
	break;
}

case ONRSPQRYFUNDINTERTRANSFERSERIAL:
{
	this->processRspQryFundInterTransferSerial(task);
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

