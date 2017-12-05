void MdApi::processFrontDisconnected(Task *task)
{
	PyLock lock;
	this->onFrontDisconnected();
	delete task;
};

void MdApi::processRtnNotice(Task *task)
{
	PyLock lock;
	dict data;
	if (task->task_data)
	{
		DFITCSECRspNoticeField *task_data = (DFITCSECRspNoticeField*)task->task_data;
		data["noticeMsg"] = task_data->noticeMsg;
		delete task->task_data;
	}

	this->onRtnNotice(data);
	delete task;
};

void MdApi::processRspError(Task *task)
{
	PyLock lock;
	dict error;
	if (task->task_error)
	{
		DFITCSECRspInfoField *task_error = (DFITCSECRspInfoField*)task->task_error;
		error["requestID"] = task_error->requestID;
		error["sessionID"] = task_error->sessionID;
		error["accountID"] = task_error->accountID;
		error["errorID"] = task_error->errorID;
		error["localOrderID"] = task_error->localOrderID;
		error["spdOrderID"] = task_error->spdOrderID;
		error["errorMsg"] = task_error->errorMsg;
		delete task->task_error;
	}

	this->onRspError(error);
	delete task;
};

void MdApi::processRspStockUserLogin(Task *task)
{
	PyLock lock;
	dict data;
	if (task->task_data)
	{
		DFITCSECRspUserLoginField *task_data = (DFITCSECRspUserLoginField*)task->task_data;
		data["requestID"] = task_data->requestID;
		data["accountID"] = task_data->accountID;
		data["sessionID"] = task_data->sessionID;
		data["frontID"] = task_data->frontID;
		data["localOrderID"] = task_data->localOrderID;
		data["loginTime"] = task_data->loginTime;
		data["tradingDay"] = task_data->tradingDay;
		data["result"] = task_data->result;
		data["rtnMsg"] = task_data->rtnMsg;
		delete task->task_data;
	}

	dict error;
	if (task->task_error)
	{
		DFITCSECRspInfoField *task_error = (DFITCSECRspInfoField*)task->task_error;
		error["requestID"] = task_error->requestID;
		error["sessionID"] = task_error->sessionID;
		error["accountID"] = task_error->accountID;
		error["errorID"] = task_error->errorID;
		error["localOrderID"] = task_error->localOrderID;
		error["spdOrderID"] = task_error->spdOrderID;
		error["errorMsg"] = task_error->errorMsg;
		delete task->task_error;
	}

	this->onRspStockUserLogin(data, error);
	delete task;
};

void MdApi::processRspStockUserLogout(Task *task)
{
	PyLock lock;
	dict data;
	if (task->task_data)
	{
		DFITCSECRspUserLogoutField *task_data = (DFITCSECRspUserLogoutField*)task->task_data;
		data["requestID"] = task_data->requestID;
		data["accountID"] = task_data->accountID;
		data["result"] = task_data->result;
		data["rtnMsg"] = task_data->rtnMsg;
		delete task->task_data;
	}

	dict error;
	if (task->task_error)
	{
		DFITCSECRspInfoField *task_error = (DFITCSECRspInfoField*)task->task_error;
		error["requestID"] = task_error->requestID;
		error["sessionID"] = task_error->sessionID;
		error["accountID"] = task_error->accountID;
		error["errorID"] = task_error->errorID;
		error["localOrderID"] = task_error->localOrderID;
		error["spdOrderID"] = task_error->spdOrderID;
		error["errorMsg"] = task_error->errorMsg;
		delete task->task_error;
	}

	this->onRspStockUserLogout(data, error);
	delete task;
};

void MdApi::processRspSOPUserLogin(Task *task)
{
	PyLock lock;
	dict data;
	if (task->task_data)
	{
		DFITCSECRspUserLoginField *task_data = (DFITCSECRspUserLoginField*)task->task_data;
		data["requestID"] = task_data->requestID;
		data["accountID"] = task_data->accountID;
		data["sessionID"] = task_data->sessionID;
		data["frontID"] = task_data->frontID;
		data["localOrderID"] = task_data->localOrderID;
		data["loginTime"] = task_data->loginTime;
		data["tradingDay"] = task_data->tradingDay;
		data["result"] = task_data->result;
		data["rtnMsg"] = task_data->rtnMsg;
		delete task->task_data;
	}

	dict error;
	if (task->task_error)
	{
		DFITCSECRspInfoField *task_error = (DFITCSECRspInfoField*)task->task_error;
		error["requestID"] = task_error->requestID;
		error["sessionID"] = task_error->sessionID;
		error["accountID"] = task_error->accountID;
		error["errorID"] = task_error->errorID;
		error["localOrderID"] = task_error->localOrderID;
		error["spdOrderID"] = task_error->spdOrderID;
		error["errorMsg"] = task_error->errorMsg;
		delete task->task_error;
	}

	this->onRspSOPUserLogin(data, error);
	delete task;
};

void MdApi::processRspSOPUserLogout(Task *task)
{
	PyLock lock;
	dict data;
	if (task->task_data)
	{
		DFITCSECRspUserLogoutField *task_data = (DFITCSECRspUserLogoutField*)task->task_data;
		data["requestID"] = task_data->requestID;
		data["accountID"] = task_data->accountID;
		data["result"] = task_data->result;
		data["rtnMsg"] = task_data->rtnMsg;
		delete task->task_data;
	}

	dict error;
	if (task->task_error)
	{
		DFITCSECRspInfoField *task_error = (DFITCSECRspInfoField*)task->task_error;
		error["requestID"] = task_error->requestID;
		error["sessionID"] = task_error->sessionID;
		error["accountID"] = task_error->accountID;
		error["errorID"] = task_error->errorID;
		error["localOrderID"] = task_error->localOrderID;
		error["spdOrderID"] = task_error->spdOrderID;
		error["errorMsg"] = task_error->errorMsg;
		delete task->task_error;
	}

	this->onRspSOPUserLogout(data, error);
	delete task;
};

void MdApi::processRspFASLUserLogin(Task *task)
{
	PyLock lock;
	dict data;
	if (task->task_data)
	{
		DFITCSECRspUserLoginField *task_data = (DFITCSECRspUserLoginField*)task->task_data;
		data["requestID"] = task_data->requestID;
		data["accountID"] = task_data->accountID;
		data["sessionID"] = task_data->sessionID;
		data["frontID"] = task_data->frontID;
		data["localOrderID"] = task_data->localOrderID;
		data["loginTime"] = task_data->loginTime;
		data["tradingDay"] = task_data->tradingDay;
		data["result"] = task_data->result;
		data["rtnMsg"] = task_data->rtnMsg;
		delete task->task_data;
	}

	dict error;
	if (task->task_error)
	{
		DFITCSECRspInfoField *task_error = (DFITCSECRspInfoField*)task->task_error;
		error["requestID"] = task_error->requestID;
		error["sessionID"] = task_error->sessionID;
		error["accountID"] = task_error->accountID;
		error["errorID"] = task_error->errorID;
		error["localOrderID"] = task_error->localOrderID;
		error["spdOrderID"] = task_error->spdOrderID;
		error["errorMsg"] = task_error->errorMsg;
		delete task->task_error;
	}

	this->onRspFASLUserLogin(data, error);
	delete task;
};

void MdApi::processRspFASLUserLogout(Task *task)
{
	PyLock lock;
	dict data;
	if (task->task_data)
	{
		DFITCSECRspUserLogoutField *task_data = (DFITCSECRspUserLogoutField*)task->task_data;
		data["requestID"] = task_data->requestID;
		data["accountID"] = task_data->accountID;
		data["result"] = task_data->result;
		data["rtnMsg"] = task_data->rtnMsg;
		delete task->task_data;
	}

	dict error;
	if (task->task_error)
	{
		DFITCSECRspInfoField *task_error = (DFITCSECRspInfoField*)task->task_error;
		error["requestID"] = task_error->requestID;
		error["sessionID"] = task_error->sessionID;
		error["accountID"] = task_error->accountID;
		error["errorID"] = task_error->errorID;
		error["localOrderID"] = task_error->localOrderID;
		error["spdOrderID"] = task_error->spdOrderID;
		error["errorMsg"] = task_error->errorMsg;
		delete task->task_error;
	}

	this->onRspFASLUserLogout(data, error);
	delete task;
};

void MdApi::processRspStockSubMarketData(Task *task)
{
	PyLock lock;
	dict data;
	if (task->task_data)
	{
		DFITCSECSpecificInstrumentField *task_data = (DFITCSECSpecificInstrumentField*)task->task_data;
		data["requestID"] = task_data->requestID;
		data["securityID"] = task_data->securityID;
		data["exchangeID"] = task_data->exchangeID;
		delete task->task_data;
	}

	dict error;
	if (task->task_error)
	{
		DFITCSECRspInfoField *task_error = (DFITCSECRspInfoField*)task->task_error;
		error["requestID"] = task_error->requestID;
		error["sessionID"] = task_error->sessionID;
		error["accountID"] = task_error->accountID;
		error["errorID"] = task_error->errorID;
		error["localOrderID"] = task_error->localOrderID;
		error["spdOrderID"] = task_error->spdOrderID;
		error["errorMsg"] = task_error->errorMsg;
		delete task->task_error;
	}

	this->onRspStockSubMarketData(data, error);
	delete task;
};

void MdApi::processRspStockUnSubMarketData(Task *task)
{
	PyLock lock;
	dict data;
	if (task->task_data)
	{
		DFITCSECSpecificInstrumentField *task_data = (DFITCSECSpecificInstrumentField*)task->task_data;
		data["requestID"] = task_data->requestID;
		data["securityID"] = task_data->securityID;
		data["exchangeID"] = task_data->exchangeID;
		delete task->task_data;
	}

	dict error;
	if (task->task_error)
	{
		DFITCSECRspInfoField *task_error = (DFITCSECRspInfoField*)task->task_error;
		error["requestID"] = task_error->requestID;
		error["sessionID"] = task_error->sessionID;
		error["accountID"] = task_error->accountID;
		error["errorID"] = task_error->errorID;
		error["localOrderID"] = task_error->localOrderID;
		error["spdOrderID"] = task_error->spdOrderID;
		error["errorMsg"] = task_error->errorMsg;
		delete task->task_error;
	}

	this->onRspStockUnSubMarketData(data, error);
	delete task;
};

void MdApi::processRspSOPSubMarketData(Task *task)
{
	PyLock lock;
	dict data;
	if (task->task_data)
	{
		DFITCSECSpecificInstrumentField *task_data = (DFITCSECSpecificInstrumentField*)task->task_data;
		data["requestID"] = task_data->requestID;
		data["securityID"] = task_data->securityID;
		data["exchangeID"] = task_data->exchangeID;
		delete task->task_data;
	}

	dict error;
	if (task->task_error)
	{
		DFITCSECRspInfoField *task_error = (DFITCSECRspInfoField*)task->task_error;
		error["requestID"] = task_error->requestID;
		error["sessionID"] = task_error->sessionID;
		error["accountID"] = task_error->accountID;
		error["errorID"] = task_error->errorID;
		error["localOrderID"] = task_error->localOrderID;
		error["spdOrderID"] = task_error->spdOrderID;
		error["errorMsg"] = task_error->errorMsg;
		delete task->task_error;
	}

	this->onRspSOPSubMarketData(data, error);
	delete task;
};

void MdApi::processRspSOPUnSubMarketData(Task *task)
{
	PyLock lock;
	dict data;
	if (task->task_data)
	{
		DFITCSECSpecificInstrumentField *task_data = (DFITCSECSpecificInstrumentField*)task->task_data;
		data["requestID"] = task_data->requestID;
		data["securityID"] = task_data->securityID;
		data["exchangeID"] = task_data->exchangeID;
		delete task->task_data;
	}

	dict error;
	if (task->task_error)
	{
		DFITCSECRspInfoField *task_error = (DFITCSECRspInfoField*)task->task_error;
		error["requestID"] = task_error->requestID;
		error["sessionID"] = task_error->sessionID;
		error["accountID"] = task_error->accountID;
		error["errorID"] = task_error->errorID;
		error["localOrderID"] = task_error->localOrderID;
		error["spdOrderID"] = task_error->spdOrderID;
		error["errorMsg"] = task_error->errorMsg;
		delete task->task_error;
	}

	this->onRspSOPUnSubMarketData(data, error);
	delete task;
};

void MdApi::processStockMarketData(Task *task)
{
	PyLock lock;
	dict data;
	if (task->task_data)
	{
		DFITCStockDepthMarketDataField *task_data = (DFITCStockDepthMarketDataField*)task->task_data;
		delete task->task_data;
	}

	this->onStockMarketData(data);
	delete task;
};

void MdApi::processSOPMarketData(Task *task)
{
	PyLock lock;
	dict data;
	if (task->task_data)
	{
		DFITCSOPDepthMarketDataField *task_data = (DFITCSOPDepthMarketDataField*)task->task_data;
		delete task->task_data;
	}

	this->onSOPMarketData(data);
	delete task;
};

void MdApi::processRspStockAvailableQuot(Task *task)
{
	PyLock lock;
	dict data;
	if (task->task_data)
	{
		DFITCRspQuotQryField *task_data = (DFITCRspQuotQryField*)task->task_data;
		data["requestID"] = task_data->requestID;
		data["accountID"] = task_data->accountID;
		data["exchangeID"] = task_data->exchangeID;
		data["securityID"] = task_data->securityID;
		data["securityName"] = task_data->securityName;
		delete task->task_data;
	}

	dict error;
	if (task->task_error)
	{
		DFITCSECRspInfoField *task_error = (DFITCSECRspInfoField*)task->task_error;
		error["requestID"] = task_error->requestID;
		error["sessionID"] = task_error->sessionID;
		error["accountID"] = task_error->accountID;
		error["errorID"] = task_error->errorID;
		error["localOrderID"] = task_error->localOrderID;
		error["spdOrderID"] = task_error->spdOrderID;
		error["errorMsg"] = task_error->errorMsg;
		delete task->task_error;
	}

	this->onRspStockAvailableQuot(data, error, task->task_last);
	delete task;
};

void MdApi::processRspSopAvailableQuot(Task *task)
{
	PyLock lock;
	dict data;
	if (task->task_data)
	{
		DFITCRspQuotQryField *task_data = (DFITCRspQuotQryField*)task->task_data;
		data["requestID"] = task_data->requestID;
		data["accountID"] = task_data->accountID;
		data["exchangeID"] = task_data->exchangeID;
		data["securityID"] = task_data->securityID;
		data["securityName"] = task_data->securityName;
		delete task->task_data;
	}

	dict error;
	if (task->task_error)
	{
		DFITCSECRspInfoField *task_error = (DFITCSECRspInfoField*)task->task_error;
		error["requestID"] = task_error->requestID;
		error["sessionID"] = task_error->sessionID;
		error["accountID"] = task_error->accountID;
		error["errorID"] = task_error->errorID;
		error["localOrderID"] = task_error->localOrderID;
		error["spdOrderID"] = task_error->spdOrderID;
		error["errorMsg"] = task_error->errorMsg;
		delete task->task_error;
	}

	this->onRspSopAvailableQuot(data, error, task->task_last);
	delete task;
};

void MdApi::processRspUserMDPasswordUpdate(Task *task)
{
	PyLock lock;
	dict data;
	if (task->task_data)
	{
		DFITCSECRspMDPasswordUpdateField *task_data = (DFITCSECRspMDPasswordUpdateField*)task->task_data;
		data["requestID"] = task_data->requestID;
		data["accountID"] = task_data->accountID;
		data["result"] = task_data->result;
		data["rtnMsg"] = task_data->rtnMsg;
		delete task->task_data;
	}

	dict error;
	if (task->task_error)
	{
		DFITCSECRspInfoField *task_error = (DFITCSECRspInfoField*)task->task_error;
		error["requestID"] = task_error->requestID;
		error["sessionID"] = task_error->sessionID;
		error["accountID"] = task_error->accountID;
		error["errorID"] = task_error->errorID;
		error["localOrderID"] = task_error->localOrderID;
		error["spdOrderID"] = task_error->spdOrderID;
		error["errorMsg"] = task_error->errorMsg;
		delete task->task_error;
	}

	this->onRspUserMDPasswordUpdate(data, error);
	delete task;
};

