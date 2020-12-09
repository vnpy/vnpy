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

case ONHEARTBEATWARNING:
{
	this->processHeartBeatWarning(&task);
	break;
}

case ONRSPAUTHENTICATE:
{
	this->processRspAuthenticate(&task);
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

case ONRSPTRADINGACCOUNTPASSWORDUPDATE:
{
	this->processRspTradingAccountPasswordUpdate(&task);
	break;
}

case ONRSPORDERINSERT:
{
	this->processRspOrderInsert(&task);
	break;
}

case ONRSPPARKEDORDERINSERT:
{
	this->processRspParkedOrderInsert(&task);
	break;
}

case ONRSPPARKEDORDERACTION:
{
	this->processRspParkedOrderAction(&task);
	break;
}

case ONRSPORDERACTION:
{
	this->processRspOrderAction(&task);
	break;
}

case ONRSPQUERYMAXORDERVOLUME:
{
	this->processRspQueryMaxOrderVolume(&task);
	break;
}

case ONRSPSETTLEMENTINFOCONFIRM:
{
	this->processRspSettlementInfoConfirm(&task);
	break;
}

case ONRSPREMOVEPARKEDORDER:
{
	this->processRspRemoveParkedOrder(&task);
	break;
}

case ONRSPREMOVEPARKEDORDERACTION:
{
	this->processRspRemoveParkedOrderAction(&task);
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

case ONRSPFORQUOTEINSERT:
{
	this->processRspForQuoteInsert(&task);
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

case ONRSPBATCHORDERACTION:
{
	this->processRspBatchOrderAction(&task);
	break;
}

case ONRSPOPTIONSELFCLOSEINSERT:
{
	this->processRspOptionSelfCloseInsert(&task);
	break;
}

case ONRSPOPTIONSELFCLOSEACTION:
{
	this->processRspOptionSelfCloseAction(&task);
	break;
}

case ONRSPCOMBACTIONINSERT:
{
	this->processRspCombActionInsert(&task);
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

case ONRSPQRYTRADINGACCOUNT:
{
	this->processRspQryTradingAccount(&task);
	break;
}

case ONRSPQRYINVESTOR:
{
	this->processRspQryInvestor(&task);
	break;
}

case ONRSPQRYTRADINGCODE:
{
	this->processRspQryTradingCode(&task);
	break;
}

case ONRSPQRYINSTRUMENTMARGINRATE:
{
	this->processRspQryInstrumentMarginRate(&task);
	break;
}

case ONRSPQRYINSTRUMENTCOMMISSIONRATE:
{
	this->processRspQryInstrumentCommissionRate(&task);
	break;
}

case ONRSPQRYEXCHANGE:
{
	this->processRspQryExchange(&task);
	break;
}

case ONRSPQRYPRODUCT:
{
	this->processRspQryProduct(&task);
	break;
}

case ONRSPQRYINSTRUMENT:
{
	this->processRspQryInstrument(&task);
	break;
}

case ONRSPQRYDEPTHMARKETDATA:
{
	this->processRspQryDepthMarketData(&task);
	break;
}

case ONRSPQRYSETTLEMENTINFO:
{
	this->processRspQrySettlementInfo(&task);
	break;
}

case ONRSPQRYTRANSFERBANK:
{
	this->processRspQryTransferBank(&task);
	break;
}

case ONRSPQRYINVESTORPOSITIONDETAIL:
{
	this->processRspQryInvestorPositionDetail(&task);
	break;
}

case ONRSPQRYNOTICE:
{
	this->processRspQryNotice(&task);
	break;
}

case ONRSPQRYSETTLEMENTINFOCONFIRM:
{
	this->processRspQrySettlementInfoConfirm(&task);
	break;
}

case ONRSPQRYINVESTORPOSITIONCOMBINEDETAIL:
{
	this->processRspQryInvestorPositionCombineDetail(&task);
	break;
}

case ONRSPQRYCFMMCTRADINGACCOUNTKEY:
{
	this->processRspQryCFMMCTradingAccountKey(&task);
	break;
}

case ONRSPQRYEWARRANTOFFSET:
{
	this->processRspQryEWarrantOffset(&task);
	break;
}

case ONRSPQRYINVESTORPRODUCTGROUPMARGIN:
{
	this->processRspQryInvestorProductGroupMargin(&task);
	break;
}

case ONRSPQRYEXCHANGEMARGINRATE:
{
	this->processRspQryExchangeMarginRate(&task);
	break;
}

case ONRSPQRYEXCHANGEMARGINRATEADJUST:
{
	this->processRspQryExchangeMarginRateAdjust(&task);
	break;
}

case ONRSPQRYEXCHANGERATE:
{
	this->processRspQryExchangeRate(&task);
	break;
}

case ONRSPQRYSECAGENTACIDMAP:
{
	this->processRspQrySecAgentACIDMap(&task);
	break;
}

case ONRSPQRYPRODUCTEXCHRATE:
{
	this->processRspQryProductExchRate(&task);
	break;
}

case ONRSPQRYPRODUCTGROUP:
{
	this->processRspQryProductGroup(&task);
	break;
}

case ONRSPQRYMMINSTRUMENTCOMMISSIONRATE:
{
	this->processRspQryMMInstrumentCommissionRate(&task);
	break;
}

case ONRSPQRYMMOPTIONINSTRCOMMRATE:
{
	this->processRspQryMMOptionInstrCommRate(&task);
	break;
}

case ONRSPQRYINSTRUMENTORDERCOMMRATE:
{
	this->processRspQryInstrumentOrderCommRate(&task);
	break;
}

case ONRSPQRYSECAGENTTRADINGACCOUNT:
{
	this->processRspQrySecAgentTradingAccount(&task);
	break;
}

case ONRSPQRYSECAGENTCHECKMODE:
{
	this->processRspQrySecAgentCheckMode(&task);
	break;
}

case ONRSPQRYOPTIONINSTRTRADECOST:
{
	this->processRspQryOptionInstrTradeCost(&task);
	break;
}

case ONRSPQRYOPTIONINSTRCOMMRATE:
{
	this->processRspQryOptionInstrCommRate(&task);
	break;
}

case ONRSPQRYEXECORDER:
{
	this->processRspQryExecOrder(&task);
	break;
}

case ONRSPQRYFORQUOTE:
{
	this->processRspQryForQuote(&task);
	break;
}

case ONRSPQRYQUOTE:
{
	this->processRspQryQuote(&task);
	break;
}

case ONRSPQRYOPTIONSELFCLOSE:
{
	this->processRspQryOptionSelfClose(&task);
	break;
}

case ONRSPQRYINVESTUNIT:
{
	this->processRspQryInvestUnit(&task);
	break;
}

case ONRSPQRYCOMBINSTRUMENTGUARD:
{
	this->processRspQryCombInstrumentGuard(&task);
	break;
}

case ONRSPQRYCOMBACTION:
{
	this->processRspQryCombAction(&task);
	break;
}

case ONRSPQRYTRANSFERSERIAL:
{
	this->processRspQryTransferSerial(&task);
	break;
}

case ONRSPQRYACCOUNTREGISTER:
{
	this->processRspQryAccountregister(&task);
	break;
}

case ONRSPFORQUOTE:
{
	this->processRspForQuote(&task);
	break;
}

case ONRSPERROR:
{
	this->processRspError(&task);
	break;
}

case ONRTNORDER:
{
	this->processRtnOrder(&task);
	break;
}

case ONRTNTRADE:
{
	this->processRtnTrade(&task);
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

case ONRTNBULLETIN:
{
	this->processRtnBulletin(&task);
	break;
}

case ONRTNTRADINGNOTICE:
{
	this->processRtnTradingNotice(&task);
	break;
}

case ONRTNERRORCONDITIONALORDER:
{
	this->processRtnErrorConditionalOrder(&task);
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

case ONERRRTNFORQUOTEINSERT:
{
	this->processErrRtnForQuoteInsert(&task);
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

case ONRTNCFMMCTRADINGACCOUNTTOKEN:
{
	this->processRtnCFMMCTradingAccountToken(&task);
	break;
}

case ONERRRTNBATCHORDERACTION:
{
	this->processErrRtnBatchOrderAction(&task);
	break;
}

case ONRTNOPTIONSELFCLOSE:
{
	this->processRtnOptionSelfClose(&task);
	break;
}

case ONERRRTNOPTIONSELFCLOSEINSERT:
{
	this->processErrRtnOptionSelfCloseInsert(&task);
	break;
}

case ONERRRTNOPTIONSELFCLOSEACTION:
{
	this->processErrRtnOptionSelfCloseAction(&task);
	break;
}

case ONRTNCOMBACTION:
{
	this->processRtnCombAction(&task);
	break;
}

case ONERRRTNCOMBACTIONINSERT:
{
	this->processErrRtnCombActionInsert(&task);
	break;
}

case ONRSPQRYCONTRACTBANK:
{
	this->processRspQryContractBank(&task);
	break;
}

case ONRSPQRYPARKEDORDER:
{
	this->processRspQryParkedOrder(&task);
	break;
}

case ONRSPQRYPARKEDORDERACTION:
{
	this->processRspQryParkedOrderAction(&task);
	break;
}

case ONRSPQRYTRADINGNOTICE:
{
	this->processRspQryTradingNotice(&task);
	break;
}

case ONRSPQRYBROKERTRADINGPARAMS:
{
	this->processRspQryBrokerTradingParams(&task);
	break;
}

case ONRSPQRYBROKERTRADINGALGOS:
{
	this->processRspQryBrokerTradingAlgos(&task);
	break;
}

case ONRSPQUERYCFMMCTRADINGACCOUNTTOKEN:
{
	this->processRspQueryCFMMCTradingAccountToken(&task);
	break;
}

case ONRTNFROMBANKTOFUTUREBYBANK:
{
	this->processRtnFromBankToFutureByBank(&task);
	break;
}

case ONRTNFROMFUTURETOBANKBYBANK:
{
	this->processRtnFromFutureToBankByBank(&task);
	break;
}

case ONRTNREPEALFROMBANKTOFUTUREBYBANK:
{
	this->processRtnRepealFromBankToFutureByBank(&task);
	break;
}

case ONRTNREPEALFROMFUTURETOBANKBYBANK:
{
	this->processRtnRepealFromFutureToBankByBank(&task);
	break;
}

case ONRTNFROMBANKTOFUTUREBYFUTURE:
{
	this->processRtnFromBankToFutureByFuture(&task);
	break;
}

case ONRTNFROMFUTURETOBANKBYFUTURE:
{
	this->processRtnFromFutureToBankByFuture(&task);
	break;
}

case ONRTNREPEALFROMBANKTOFUTUREBYFUTUREMANUAL:
{
	this->processRtnRepealFromBankToFutureByFutureManual(&task);
	break;
}

case ONRTNREPEALFROMFUTURETOBANKBYFUTUREMANUAL:
{
	this->processRtnRepealFromFutureToBankByFutureManual(&task);
	break;
}

case ONRTNQUERYBANKBALANCEBYFUTURE:
{
	this->processRtnQueryBankBalanceByFuture(&task);
	break;
}

case ONERRRTNBANKTOFUTUREBYFUTURE:
{
	this->processErrRtnBankToFutureByFuture(&task);
	break;
}

case ONERRRTNFUTURETOBANKBYFUTURE:
{
	this->processErrRtnFutureToBankByFuture(&task);
	break;
}

case ONERRRTNREPEALBANKTOFUTUREBYFUTUREMANUAL:
{
	this->processErrRtnRepealBankToFutureByFutureManual(&task);
	break;
}

case ONERRRTNREPEALFUTURETOBANKBYFUTUREMANUAL:
{
	this->processErrRtnRepealFutureToBankByFutureManual(&task);
	break;
}

case ONERRRTNQUERYBANKBALANCEBYFUTURE:
{
	this->processErrRtnQueryBankBalanceByFuture(&task);
	break;
}

case ONRTNREPEALFROMBANKTOFUTUREBYFUTURE:
{
	this->processRtnRepealFromBankToFutureByFuture(&task);
	break;
}

case ONRTNREPEALFROMFUTURETOBANKBYFUTURE:
{
	this->processRtnRepealFromFutureToBankByFuture(&task);
	break;
}

case ONRSPFROMBANKTOFUTUREBYFUTURE:
{
	this->processRspFromBankToFutureByFuture(&task);
	break;
}

case ONRSPFROMFUTURETOBANKBYFUTURE:
{
	this->processRspFromFutureToBankByFuture(&task);
	break;
}

case ONRSPQUERYBANKACCOUNTMONEYBYFUTURE:
{
	this->processRspQueryBankAccountMoneyByFuture(&task);
	break;
}

case ONRTNOPENACCOUNTBYBANK:
{
	this->processRtnOpenAccountByBank(&task);
	break;
}

case ONRTNCANCELACCOUNTBYBANK:
{
	this->processRtnCancelAccountByBank(&task);
	break;
}

case ONRTNCHANGEACCOUNTBYBANK:
{
	this->processRtnChangeAccountByBank(&task);
	break;
}

