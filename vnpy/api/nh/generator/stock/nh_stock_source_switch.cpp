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

case ONRSPSUBSCRIBETOPIC:
{
	this->processRspSubscribeTopic(&task);
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

case ONRSPSTOCKINSERT:
{
	this->processRspStockInsert(&task);
	break;
}

case ONRSPSTOCKCANCEL:
{
	this->processRspStockCancel(&task);
	break;
}

case ONRSPOPTIONSINSERT:
{
	this->processRspOptionsInsert(&task);
	break;
}

case ONRSPOPTIONSCANCEL:
{
	this->processRspOptionsCancel(&task);
	break;
}

case ONRSPQUOTEINSERT:
{
	this->processRspQuoteInsert(&task);
	break;
}

case ONRSPFORQUOTE:
{
	this->processRspForQuote(&task);
	break;
}

case ONRSPQUOTECANCEL:
{
	this->processRspQuoteCancel(&task);
	break;
}

case ONRSPSTOCKLOCK:
{
	this->processRspStockLock(&task);
	break;
}

case ONRSPEXERCISE:
{
	this->processRspExercise(&task);
	break;
}

case ONRSPEXERCISECANCEL:
{
	this->processRspExerciseCancel(&task);
	break;
}

case ONRSPQRYPARTACCOUNT:
{
	this->processRspQryPartAccount(&task);
	break;
}

case ONRSPQRYSTOCKORDER:
{
	this->processRspQryStockOrder(&task);
	break;
}

case ONRSPQRYOPTIONSORDER:
{
	this->processRspQryOptionsOrder(&task);
	break;
}

case ONRSPQRYQUOTEORDER:
{
	this->processRspQryQuoteOrder(&task);
	break;
}

case ONRSPQRYSTOCKTRADE:
{
	this->processRspQryStockTrade(&task);
	break;
}

case ONRSPQRYOPTIONSTRADE:
{
	this->processRspQryOptionsTrade(&task);
	break;
}

case ONRSPQRYPOSITION:
{
	this->processRspQryPosition(&task);
	break;
}

case ONRSPQRYTOPIC:
{
	this->processRspQryTopic(&task);
	break;
}

case ONRSPQRYSTOCK:
{
	this->processRspQryStock(&task);
	break;
}

case ONRSPQRYOPTIONS:
{
	this->processRspQryOptions(&task);
	break;
}

case ONRTNOPTIONSORDER:
{
	this->processRtnOptionsOrder(&task);
	break;
}

case ONRTNSTOCKORDER:
{
	this->processRtnStockOrder(&task);
	break;
}

case ONRTNQUOTEORDER:
{
	this->processRtnQuoteOrder(&task);
	break;
}

case ONRTNOPTIONSTRADE:
{
	this->processRtnOptionsTrade(&task);
	break;
}

case ONRTNSTOCKTRADE:
{
	this->processRtnStockTrade(&task);
	break;
}

case ONRTNEXERCISE:
{
	this->processRtnExercise(&task);
	break;
}

case ONRSPQRYRATE:
{
	this->processRspQryRate(&task);
	break;
}

case ONRSPQRYCLIENT:
{
	this->processRspQryClient(&task);
	break;
}

case ONRSPQRYCLIENTMARGIN:
{
	this->processRspQryClientMargin(&task);
	break;
}

case ONRSPQRYEXERCISE:
{
	this->processRspQryExercise(&task);
	break;
}

case ONRTNWITHDRAWDEPOSIT:
{
	this->processRtnWithdrawDeposit(&task);
	break;
}

case ONRSPMARGINCOMBACTION:
{
	this->processRspMarginCombAction(&task);
	break;
}

case ONRTNMARGINCOMBACTION:
{
	this->processRtnMarginCombAction(&task);
	break;
}

case ONRSPQRYSSECOMBPOSITION:
{
	this->processRspQrySseCombPosition(&task);
	break;
}

case ONRSPCOMBEXERCISE:
{
	this->processRspCombExercise(&task);
	break;
}

