case ONRSPLOGIN:
{
	this->processRspLogin(&task);
	break;
}

case ONAPIREADY:
{
	this->processAPIReady(&task);
	break;
}

case ONDISCONNECT:
{
	this->processDisconnect(&task);
	break;
}

case ONRSPQRYCOMMODITY:
{
	this->processRspQryCommodity(&task);
	break;
}

case ONRSPQRYCONTRACT:
{
	this->processRspQryContract(&task);
	break;
}

case ONRSPSUBSCRIBEQUOTE:
{
	this->processRspSubscribeQuote(&task);
	break;
}

case ONRSPUNSUBSCRIBEQUOTE:
{
	this->processRspUnSubscribeQuote(&task);
	break;
}

case ONRTNQUOTE:
{
	this->processRtnQuote(&task);
	break;
}

