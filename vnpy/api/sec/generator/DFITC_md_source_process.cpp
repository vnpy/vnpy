void MdApi::processFrontConnected(Task *task)
{
	gil_scoped_acquire acquire;
	this->onFrontConnected();
};

void MdApi::processFrontDisconnected(Task *task)
{
	gil_scoped_acquire acquire;
	this->onFrontDisconnected(task->task_id);
};

void MdApi::processRtnNotice(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		DFITCSECRspNoticeField *task_data = (DFITCSECRspNoticeField*)task->task_data;
		data["noticeMsg"] = toUtf(task_data->noticeMsg);
		delete task_data;
	}
	this->onRtnNotice(data);
};

void MdApi::processRspError(Task *task)
{
	gil_scoped_acquire acquire;
	dict error;
	if (task->task_error)
	{
		DFITCSECRspInfoField *task_error = (DFITCSECRspInfoField*)task->task_error;
		error["requestID"] = task_error->requestID;
		error["sessionID"] = task_error->sessionID;
		error["accountID"] = toUtf(task_error->accountID);
		error["errorID"] = task_error->errorID;
		error["localOrderID"] = task_error->localOrderID;
		error["spdOrderID"] = task_error->spdOrderID;
		error["errorMsg"] = toUtf(task_error->errorMsg);
		delete task_error;
	}
	this->onRspError(error);
};

void MdApi::processRspStockUserLogin(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		DFITCSECRspUserLoginField *task_data = (DFITCSECRspUserLoginField*)task->task_data;
		data["requestID"] = task_data->requestID;
		data["accountID"] = toUtf(task_data->accountID);
		data["sessionID"] = task_data->sessionID;
		data["frontID"] = task_data->frontID;
		data["localOrderID"] = task_data->localOrderID;
		data["loginTime"] = toUtf(task_data->loginTime);
		data["tradingDay"] = task_data->tradingDay;
		data["result"] = task_data->result;
		data["rtnMsg"] = toUtf(task_data->rtnMsg);
		delete task_data;
	}
	dict error;
	if (task->task_error)
	{
		DFITCSECRspInfoField *task_error = (DFITCSECRspInfoField*)task->task_error;
		error["requestID"] = task_error->requestID;
		error["sessionID"] = task_error->sessionID;
		error["accountID"] = toUtf(task_error->accountID);
		error["errorID"] = task_error->errorID;
		error["localOrderID"] = task_error->localOrderID;
		error["spdOrderID"] = task_error->spdOrderID;
		error["errorMsg"] = toUtf(task_error->errorMsg);
		delete task_error;
	}
	this->onRspStockUserLogin(data, error);
};

void MdApi::processRspStockUserLogout(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		DFITCSECRspUserLogoutField *task_data = (DFITCSECRspUserLogoutField*)task->task_data;
		data["requestID"] = task_data->requestID;
		data["accountID"] = toUtf(task_data->accountID);
		data["result"] = task_data->result;
		data["rtnMsg"] = toUtf(task_data->rtnMsg);
		delete task_data;
	}
	dict error;
	if (task->task_error)
	{
		DFITCSECRspInfoField *task_error = (DFITCSECRspInfoField*)task->task_error;
		error["requestID"] = task_error->requestID;
		error["sessionID"] = task_error->sessionID;
		error["accountID"] = toUtf(task_error->accountID);
		error["errorID"] = task_error->errorID;
		error["localOrderID"] = task_error->localOrderID;
		error["spdOrderID"] = task_error->spdOrderID;
		error["errorMsg"] = toUtf(task_error->errorMsg);
		delete task_error;
	}
	this->onRspStockUserLogout(data, error);
};

void MdApi::processRspSOPUserLogin(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		DFITCSECRspUserLoginField *task_data = (DFITCSECRspUserLoginField*)task->task_data;
		data["requestID"] = task_data->requestID;
		data["accountID"] = toUtf(task_data->accountID);
		data["sessionID"] = task_data->sessionID;
		data["frontID"] = task_data->frontID;
		data["localOrderID"] = task_data->localOrderID;
		data["loginTime"] = toUtf(task_data->loginTime);
		data["tradingDay"] = task_data->tradingDay;
		data["result"] = task_data->result;
		data["rtnMsg"] = toUtf(task_data->rtnMsg);
		delete task_data;
	}
	dict error;
	if (task->task_error)
	{
		DFITCSECRspInfoField *task_error = (DFITCSECRspInfoField*)task->task_error;
		error["requestID"] = task_error->requestID;
		error["sessionID"] = task_error->sessionID;
		error["accountID"] = toUtf(task_error->accountID);
		error["errorID"] = task_error->errorID;
		error["localOrderID"] = task_error->localOrderID;
		error["spdOrderID"] = task_error->spdOrderID;
		error["errorMsg"] = toUtf(task_error->errorMsg);
		delete task_error;
	}
	this->onRspSOPUserLogin(data, error);
};

void MdApi::processRspSOPUserLogout(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		DFITCSECRspUserLogoutField *task_data = (DFITCSECRspUserLogoutField*)task->task_data;
		data["requestID"] = task_data->requestID;
		data["accountID"] = toUtf(task_data->accountID);
		data["result"] = task_data->result;
		data["rtnMsg"] = toUtf(task_data->rtnMsg);
		delete task_data;
	}
	dict error;
	if (task->task_error)
	{
		DFITCSECRspInfoField *task_error = (DFITCSECRspInfoField*)task->task_error;
		error["requestID"] = task_error->requestID;
		error["sessionID"] = task_error->sessionID;
		error["accountID"] = toUtf(task_error->accountID);
		error["errorID"] = task_error->errorID;
		error["localOrderID"] = task_error->localOrderID;
		error["spdOrderID"] = task_error->spdOrderID;
		error["errorMsg"] = toUtf(task_error->errorMsg);
		delete task_error;
	}
	this->onRspSOPUserLogout(data, error);
};

void MdApi::processRspFASLUserLogin(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		DFITCSECRspUserLoginField *task_data = (DFITCSECRspUserLoginField*)task->task_data;
		data["requestID"] = task_data->requestID;
		data["accountID"] = toUtf(task_data->accountID);
		data["sessionID"] = task_data->sessionID;
		data["frontID"] = task_data->frontID;
		data["localOrderID"] = task_data->localOrderID;
		data["loginTime"] = toUtf(task_data->loginTime);
		data["tradingDay"] = task_data->tradingDay;
		data["result"] = task_data->result;
		data["rtnMsg"] = toUtf(task_data->rtnMsg);
		delete task_data;
	}
	dict error;
	if (task->task_error)
	{
		DFITCSECRspInfoField *task_error = (DFITCSECRspInfoField*)task->task_error;
		error["requestID"] = task_error->requestID;
		error["sessionID"] = task_error->sessionID;
		error["accountID"] = toUtf(task_error->accountID);
		error["errorID"] = task_error->errorID;
		error["localOrderID"] = task_error->localOrderID;
		error["spdOrderID"] = task_error->spdOrderID;
		error["errorMsg"] = toUtf(task_error->errorMsg);
		delete task_error;
	}
	this->onRspFASLUserLogin(data, error);
};

void MdApi::processRspFASLUserLogout(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		DFITCSECRspUserLogoutField *task_data = (DFITCSECRspUserLogoutField*)task->task_data;
		data["requestID"] = task_data->requestID;
		data["accountID"] = toUtf(task_data->accountID);
		data["result"] = task_data->result;
		data["rtnMsg"] = toUtf(task_data->rtnMsg);
		delete task_data;
	}
	dict error;
	if (task->task_error)
	{
		DFITCSECRspInfoField *task_error = (DFITCSECRspInfoField*)task->task_error;
		error["requestID"] = task_error->requestID;
		error["sessionID"] = task_error->sessionID;
		error["accountID"] = toUtf(task_error->accountID);
		error["errorID"] = task_error->errorID;
		error["localOrderID"] = task_error->localOrderID;
		error["spdOrderID"] = task_error->spdOrderID;
		error["errorMsg"] = toUtf(task_error->errorMsg);
		delete task_error;
	}
	this->onRspFASLUserLogout(data, error);
};

void MdApi::processRspStockSubMarketData(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		DFITCSECSpecificInstrumentField *task_data = (DFITCSECSpecificInstrumentField*)task->task_data;
		data["requestID"] = task_data->requestID;
		data["securityID"] = toUtf(task_data->securityID);
		data["exchangeID"] = toUtf(task_data->exchangeID);
		delete task_data;
	}
	dict error;
	if (task->task_error)
	{
		DFITCSECRspInfoField *task_error = (DFITCSECRspInfoField*)task->task_error;
		error["requestID"] = task_error->requestID;
		error["sessionID"] = task_error->sessionID;
		error["accountID"] = toUtf(task_error->accountID);
		error["errorID"] = task_error->errorID;
		error["localOrderID"] = task_error->localOrderID;
		error["spdOrderID"] = task_error->spdOrderID;
		error["errorMsg"] = toUtf(task_error->errorMsg);
		delete task_error;
	}
	this->onRspStockSubMarketData(data, error);
};

void MdApi::processRspStockUnSubMarketData(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		DFITCSECSpecificInstrumentField *task_data = (DFITCSECSpecificInstrumentField*)task->task_data;
		data["requestID"] = task_data->requestID;
		data["securityID"] = toUtf(task_data->securityID);
		data["exchangeID"] = toUtf(task_data->exchangeID);
		delete task_data;
	}
	dict error;
	if (task->task_error)
	{
		DFITCSECRspInfoField *task_error = (DFITCSECRspInfoField*)task->task_error;
		error["requestID"] = task_error->requestID;
		error["sessionID"] = task_error->sessionID;
		error["accountID"] = toUtf(task_error->accountID);
		error["errorID"] = task_error->errorID;
		error["localOrderID"] = task_error->localOrderID;
		error["spdOrderID"] = task_error->spdOrderID;
		error["errorMsg"] = toUtf(task_error->errorMsg);
		delete task_error;
	}
	this->onRspStockUnSubMarketData(data, error);
};

void MdApi::processRspSOPSubMarketData(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		DFITCSECSpecificInstrumentField *task_data = (DFITCSECSpecificInstrumentField*)task->task_data;
		data["requestID"] = task_data->requestID;
		data["securityID"] = toUtf(task_data->securityID);
		data["exchangeID"] = toUtf(task_data->exchangeID);
		delete task_data;
	}
	dict error;
	if (task->task_error)
	{
		DFITCSECRspInfoField *task_error = (DFITCSECRspInfoField*)task->task_error;
		error["requestID"] = task_error->requestID;
		error["sessionID"] = task_error->sessionID;
		error["accountID"] = toUtf(task_error->accountID);
		error["errorID"] = task_error->errorID;
		error["localOrderID"] = task_error->localOrderID;
		error["spdOrderID"] = task_error->spdOrderID;
		error["errorMsg"] = toUtf(task_error->errorMsg);
		delete task_error;
	}
	this->onRspSOPSubMarketData(data, error);
};

void MdApi::processRspSOPUnSubMarketData(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		DFITCSECSpecificInstrumentField *task_data = (DFITCSECSpecificInstrumentField*)task->task_data;
		data["requestID"] = task_data->requestID;
		data["securityID"] = toUtf(task_data->securityID);
		data["exchangeID"] = toUtf(task_data->exchangeID);
		delete task_data;
	}
	dict error;
	if (task->task_error)
	{
		DFITCSECRspInfoField *task_error = (DFITCSECRspInfoField*)task->task_error;
		error["requestID"] = task_error->requestID;
		error["sessionID"] = task_error->sessionID;
		error["accountID"] = toUtf(task_error->accountID);
		error["errorID"] = task_error->errorID;
		error["localOrderID"] = task_error->localOrderID;
		error["spdOrderID"] = task_error->spdOrderID;
		error["errorMsg"] = toUtf(task_error->errorMsg);
		delete task_error;
	}
	this->onRspSOPUnSubMarketData(data, error);
};

void MdApi::processStockMarketData(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		DFITCStockDepthMarketDataField *task_data = (DFITCStockDepthMarketDataField*)task->task_data;
		data["specificDataField"] = task_data->specificDataField;
		data["staticDataField"] = task_data->staticDataField;
		data["sharedDataField"] = task_data->sharedDataField;
		delete task_data;
	}
	this->onStockMarketData(data);
};

void MdApi::processSOPMarketData(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		DFITCSOPDepthMarketDataField *task_data = (DFITCSOPDepthMarketDataField*)task->task_data;
		data["specificDataField"] = task_data->specificDataField;
		data["staticDataField"] = task_data->staticDataField;
		data["sharedDataField"] = task_data->sharedDataField;
		delete task_data;
	}
	this->onSOPMarketData(data);
};

void MdApi::processRspStockAvailableQuot(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		DFITCRspQuotQryField *task_data = (DFITCRspQuotQryField*)task->task_data;
		data["requestID"] = task_data->requestID;
		data["accountID"] = toUtf(task_data->accountID);
		data["exchangeID"] = toUtf(task_data->exchangeID);
		data["securityID"] = toUtf(task_data->securityID);
		data["securityName"] = toUtf(task_data->securityName);
		delete task_data;
	}
	dict error;
	if (task->task_error)
	{
		DFITCSECRspInfoField *task_error = (DFITCSECRspInfoField*)task->task_error;
		error["requestID"] = task_error->requestID;
		error["sessionID"] = task_error->sessionID;
		error["accountID"] = toUtf(task_error->accountID);
		error["errorID"] = task_error->errorID;
		error["localOrderID"] = task_error->localOrderID;
		error["spdOrderID"] = task_error->spdOrderID;
		error["errorMsg"] = toUtf(task_error->errorMsg);
		delete task_error;
	}
	this->onRspStockAvailableQuot(data, error, task->task_last);
};

void MdApi::processRspSopAvailableQuot(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		DFITCRspQuotQryField *task_data = (DFITCRspQuotQryField*)task->task_data;
		data["requestID"] = task_data->requestID;
		data["accountID"] = toUtf(task_data->accountID);
		data["exchangeID"] = toUtf(task_data->exchangeID);
		data["securityID"] = toUtf(task_data->securityID);
		data["securityName"] = toUtf(task_data->securityName);
		delete task_data;
	}
	dict error;
	if (task->task_error)
	{
		DFITCSECRspInfoField *task_error = (DFITCSECRspInfoField*)task->task_error;
		error["requestID"] = task_error->requestID;
		error["sessionID"] = task_error->sessionID;
		error["accountID"] = toUtf(task_error->accountID);
		error["errorID"] = task_error->errorID;
		error["localOrderID"] = task_error->localOrderID;
		error["spdOrderID"] = task_error->spdOrderID;
		error["errorMsg"] = toUtf(task_error->errorMsg);
		delete task_error;
	}
	this->onRspSopAvailableQuot(data, error, task->task_last);
};

void MdApi::processRspUserMDPasswordUpdate(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		DFITCSECRspMDPasswordUpdateField *task_data = (DFITCSECRspMDPasswordUpdateField*)task->task_data;
		data["requestID"] = task_data->requestID;
		data["accountID"] = toUtf(task_data->accountID);
		data["result"] = task_data->result;
		data["rtnMsg"] = toUtf(task_data->rtnMsg);
		delete task_data;
	}
	dict error;
	if (task->task_error)
	{
		DFITCSECRspInfoField *task_error = (DFITCSECRspInfoField*)task->task_error;
		error["requestID"] = task_error->requestID;
		error["sessionID"] = task_error->sessionID;
		error["accountID"] = toUtf(task_error->accountID);
		error["errorID"] = task_error->errorID;
		error["localOrderID"] = task_error->localOrderID;
		error["spdOrderID"] = task_error->spdOrderID;
		error["errorMsg"] = toUtf(task_error->errorMsg);
		delete task_error;
	}
	this->onRspUserMDPasswordUpdate(data, error);
};

