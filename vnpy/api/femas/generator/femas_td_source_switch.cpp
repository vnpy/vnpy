case ONFRONTCONNECTED:
{
	this->processFrontConnected(&task);
	break;
}

case ONQRYFRONTCONNECTED:
{
	this->processQryFrontConnected(&task);
	break;
}

case ONFRONTDISCONNECTED:
{
	this->processFrontDisconnected(&task);
	break;
}

case ONQRYFRONTDISCONNECTED:
{
	this->processQryFrontDisconnected(&task);
	break;
}

case ONHEARTBEATWARNING:
{
	this->processHeartBeatWarning(&task);
	break;
}

case ONPACKAGESTART:
{
	this->processPackageStart(&task);
	break;
}

case ONPACKAGEEND:
{
	this->processPackageEnd(&task);
	break;
}

case ONRSPERROR:
{
	this->processRspError(&task);
	break;
}

case ONRSPUSERLOGIN:
{
	this->processRspUserLogin(&task);
	break;
}

case ONRSPUSERLOGOUT:
{
	this->processRspUserLogout(&task);
	break;
}

case ONRSPUSERPASSWORDUPDATE:
{
	this->processRspUserPasswordUpdate(&task);
	break;
}

case ONRSPORDERINSERT:
{
	this->processRspOrderInsert(&task);
	break;
}

case ONRSPORDERACTION:
{
	this->processRspOrderAction(&task);
	break;
}

case ONRSPQUOTEINSERT:
{
	this->processRspQuoteInsert(&task);
	break;
}

case ONRSPQUOTEACTION:
{
	this->processRspQuoteAction(&task);
	break;
}

case ONRSPFORQUOTE:
{
	this->processRspForQuote(&task);
	break;
}

case ONRSPMARGINCOMBACTION:
{
	this->processRspMarginCombAction(&task);
	break;
}

case ONRSPUSERDEPOSIT:
{
	this->processRspUserDeposit(&task);
	break;
}

case ONRTNFLOWMESSAGECANCEL:
{
	this->processRtnFlowMessageCancel(&task);
	break;
}

case ONRTNTRADE:
{
	this->processRtnTrade(&task);
	break;
}

case ONRTNORDER:
{
	this->processRtnOrder(&task);
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

case ONRTNINSTRUMENTSTATUS:
{
	this->processRtnInstrumentStatus(&task);
	break;
}

case ONRTNINVESTORACCOUNTDEPOSIT:
{
	this->processRtnInvestorAccountDeposit(&task);
	break;
}

case ONRTNQUOTE:
{
	this->processRtnQuote(&task);
	break;
}

case ONERRRTNQUOTEINSERT:
{
	this->processErrRtnQuoteInsert(&task);
	break;
}

case ONERRRTNQUOTEACTION:
{
	this->processErrRtnQuoteAction(&task);
	break;
}

case ONRTNFORQUOTE:
{
	this->processRtnForQuote(&task);
	break;
}

case ONRTNMARGINCOMBINATIONLEG:
{
	this->processRtnMarginCombinationLeg(&task);
	break;
}

case ONRTNMARGINCOMBACTION:
{
	this->processRtnMarginCombAction(&task);
	break;
}

case ONRTNUSERDEPOSIT:
{
	this->processRtnUserDeposit(&task);
	break;
}

case ONRSPQUERYUSERLOGIN:
{
	this->processRspQueryUserLogin(&task);
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

case ONRSPQRYUSERINVESTOR:
{
	this->processRspQryUserInvestor(&task);
	break;
}

case ONRSPQRYTRADINGCODE:
{
	this->processRspQryTradingCode(&task);
	break;
}

case ONRSPQRYINVESTORACCOUNT:
{
	this->processRspQryInvestorAccount(&task);
	break;
}

case ONRSPQRYINSTRUMENT:
{
	this->processRspQryInstrument(&task);
	break;
}

case ONRSPQRYEXCHANGE:
{
	this->processRspQryExchange(&task);
	break;
}

case ONRSPQRYINVESTORPOSITION:
{
	this->processRspQryInvestorPosition(&task);
	break;
}

case ONRSPQRYCOMPLIANCEPARAM:
{
	this->processRspQryComplianceParam(&task);
	break;
}

case ONRSPQRYINVESTORFEE:
{
	this->processRspQryInvestorFee(&task);
	break;
}

case ONRSPQRYINVESTORMARGIN:
{
	this->processRspQryInvestorMargin(&task);
	break;
}

case ONRSPQRYINVESTORCOMBPOSITION:
{
	this->processRspQryInvestorCombPosition(&task);
	break;
}

case ONRSPQRYINVESTORLEGPOSITION:
{
	this->processRspQryInvestorLegPosition(&task);
	break;
}

case ONRSPQRYINSTRUMENTGROUP:
{
	this->processRspQryInstrumentGroup(&task);
	break;
}

case ONRSPQRYCLIENTMARGINCOMBTYPE:
{
	this->processRspQryClientMarginCombType(&task);
	break;
}

case ONRSPEXECORDERINSERT:
{
	this->processRspExecOrderInsert(&task);
	break;
}

case ONRSPEXECORDERACTION:
{
	this->processRspExecOrderAction(&task);
	break;
}

case ONRTNEXECORDER:
{
	this->processRtnExecOrder(&task);
	break;
}

case ONERRRTNEXECORDERINSERT:
{
	this->processErrRtnExecOrderInsert(&task);
	break;
}

case ONERRRTNEXECORDERACTION:
{
	this->processErrRtnExecOrderAction(&task);
	break;
}

case ONRTNTRANSFERMONEY:
{
	this->processRtnTransferMoney(&task);
	break;
}

case ONRSPQRYSYSTEMTIME:
{
	this->processRspQrySystemTime(&task);
	break;
}

case ONRSPQRYMARGINPREFPARAM:
{
	this->processRspQryMarginPrefParam(&task);
	break;
}

case ONRSPDSUSERCERTIFICATION:
{
	this->processRspDSUserCertification(&task);
	break;
}

case ONRSPDSPROXYSUBMITINFO:
{
	this->processRspDSProxySubmitInfo(&task);
	break;
}

