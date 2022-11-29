        void MdApi::OnFrontConnected()
{
	Task task = Task();
	task.task_name = ONFRONTCONNECTED;
	this->task_queue.push(task);
};

        void MdApi::OnFrontDisconnected(int nReason)
{
	Task task = Task();
	task.task_name = ONFRONTDISCONNECTED;
	task.task_id = nReason;
	this->task_queue.push(task);
};

        void MdApi::OnRtnNotice(DFITCSECRspNoticeField *pNotice) 
{
	Task task = Task();
	task.task_name = ONRTNNOTICE;
	if (pNotice)
	{
		DFITCSECRspNoticeField *task_data = new DFITCSECRspNoticeField();
		*task_data = *pNotice;
		task.task_data = task_data;
	}
	this->task_queue.push(task);
};

        void MdApi::OnRspError(struct DFITCSECRspInfoField *pRspInfo) 
{
	Task task = Task();
	task.task_name = ONRSPERROR;
	if (pRspInfo)
	{
		DFITCSECRspInfoField *task_error = new DFITCSECRspInfoField();
		*task_error = *pRspInfo;
		task.task_error = task_error;
	}
	this->task_queue.push(task);
};

        void MdApi::OnRspStockUserLogin(struct DFITCSECRspUserLoginField * pRspUserLogin, struct DFITCSECRspInfoField * pRspInfo) 
{
	Task task = Task();
	task.task_name = ONRSPSTOCKUSERLOGIN;
	if (pRspUserLogin)
	{
		DFITCSECRspUserLoginField *task_data = new DFITCSECRspUserLoginField();
		*task_data = *pRspUserLogin;
		task.task_data = task_data;
	}
	if (pRspInfo)
	{
		DFITCSECRspInfoField *task_error = new DFITCSECRspInfoField();
		*task_error = *pRspInfo;
		task.task_error = task_error;
	}
	this->task_queue.push(task);
};

        void MdApi::OnRspStockUserLogout(struct DFITCSECRspUserLogoutField * pRspUsrLogout, struct DFITCSECRspInfoField * pRspInfo) 
{
	Task task = Task();
	task.task_name = ONRSPSTOCKUSERLOGOUT;
	if (pRspUsrLogout)
	{
		DFITCSECRspUserLogoutField *task_data = new DFITCSECRspUserLogoutField();
		*task_data = *pRspUsrLogout;
		task.task_data = task_data;
	}
	if (pRspInfo)
	{
		DFITCSECRspInfoField *task_error = new DFITCSECRspInfoField();
		*task_error = *pRspInfo;
		task.task_error = task_error;
	}
	this->task_queue.push(task);
};

        void MdApi::OnRspSOPUserLogin(struct DFITCSECRspUserLoginField * pRspUserLogin, struct DFITCSECRspInfoField * pRspInfo) 
{
	Task task = Task();
	task.task_name = ONRSPSOPUSERLOGIN;
	if (pRspUserLogin)
	{
		DFITCSECRspUserLoginField *task_data = new DFITCSECRspUserLoginField();
		*task_data = *pRspUserLogin;
		task.task_data = task_data;
	}
	if (pRspInfo)
	{
		DFITCSECRspInfoField *task_error = new DFITCSECRspInfoField();
		*task_error = *pRspInfo;
		task.task_error = task_error;
	}
	this->task_queue.push(task);
};

        void MdApi::OnRspSOPUserLogout(struct DFITCSECRspUserLogoutField * pRspUsrLogout, struct DFITCSECRspInfoField * pRspInfo) 
{
	Task task = Task();
	task.task_name = ONRSPSOPUSERLOGOUT;
	if (pRspUsrLogout)
	{
		DFITCSECRspUserLogoutField *task_data = new DFITCSECRspUserLogoutField();
		*task_data = *pRspUsrLogout;
		task.task_data = task_data;
	}
	if (pRspInfo)
	{
		DFITCSECRspInfoField *task_error = new DFITCSECRspInfoField();
		*task_error = *pRspInfo;
		task.task_error = task_error;
	}
	this->task_queue.push(task);
};

        void MdApi::OnRspFASLUserLogin(struct DFITCSECRspUserLoginField * pRspUserLogin, struct DFITCSECRspInfoField * pRspInfo) 
{
	Task task = Task();
	task.task_name = ONRSPFASLUSERLOGIN;
	if (pRspUserLogin)
	{
		DFITCSECRspUserLoginField *task_data = new DFITCSECRspUserLoginField();
		*task_data = *pRspUserLogin;
		task.task_data = task_data;
	}
	if (pRspInfo)
	{
		DFITCSECRspInfoField *task_error = new DFITCSECRspInfoField();
		*task_error = *pRspInfo;
		task.task_error = task_error;
	}
	this->task_queue.push(task);
};

        void MdApi::OnRspFASLUserLogout(struct DFITCSECRspUserLogoutField * pRspUsrLogout, struct DFITCSECRspInfoField * pRspInfo) 
{
	Task task = Task();
	task.task_name = ONRSPFASLUSERLOGOUT;
	if (pRspUsrLogout)
	{
		DFITCSECRspUserLogoutField *task_data = new DFITCSECRspUserLogoutField();
		*task_data = *pRspUsrLogout;
		task.task_data = task_data;
	}
	if (pRspInfo)
	{
		DFITCSECRspInfoField *task_error = new DFITCSECRspInfoField();
		*task_error = *pRspInfo;
		task.task_error = task_error;
	}
	this->task_queue.push(task);
};

        void MdApi::OnRspStockSubMarketData(struct DFITCSECSpecificInstrumentField * pSpecificInstrument, struct DFITCSECRspInfoField * pRspInfo) 
{
	Task task = Task();
	task.task_name = ONRSPSTOCKSUBMARKETDATA;
	if (pSpecificInstrument)
	{
		DFITCSECSpecificInstrumentField *task_data = new DFITCSECSpecificInstrumentField();
		*task_data = *pSpecificInstrument;
		task.task_data = task_data;
	}
	if (pRspInfo)
	{
		DFITCSECRspInfoField *task_error = new DFITCSECRspInfoField();
		*task_error = *pRspInfo;
		task.task_error = task_error;
	}
	this->task_queue.push(task);
};

        void MdApi::OnRspStockUnSubMarketData(struct DFITCSECSpecificInstrumentField * pSpecificInstrument, struct DFITCSECRspInfoField * pRspInfo) 
{
	Task task = Task();
	task.task_name = ONRSPSTOCKUNSUBMARKETDATA;
	if (pSpecificInstrument)
	{
		DFITCSECSpecificInstrumentField *task_data = new DFITCSECSpecificInstrumentField();
		*task_data = *pSpecificInstrument;
		task.task_data = task_data;
	}
	if (pRspInfo)
	{
		DFITCSECRspInfoField *task_error = new DFITCSECRspInfoField();
		*task_error = *pRspInfo;
		task.task_error = task_error;
	}
	this->task_queue.push(task);
};

        void MdApi::OnRspSOPSubMarketData(struct DFITCSECSpecificInstrumentField * pSpecificInstrument, struct DFITCSECRspInfoField * pRspInfo) 
{
	Task task = Task();
	task.task_name = ONRSPSOPSUBMARKETDATA;
	if (pSpecificInstrument)
	{
		DFITCSECSpecificInstrumentField *task_data = new DFITCSECSpecificInstrumentField();
		*task_data = *pSpecificInstrument;
		task.task_data = task_data;
	}
	if (pRspInfo)
	{
		DFITCSECRspInfoField *task_error = new DFITCSECRspInfoField();
		*task_error = *pRspInfo;
		task.task_error = task_error;
	}
	this->task_queue.push(task);
};

        void MdApi::OnRspSOPUnSubMarketData(struct DFITCSECSpecificInstrumentField * pSpecificInstrument, struct DFITCSECRspInfoField * pRspInfo) 
{
	Task task = Task();
	task.task_name = ONRSPSOPUNSUBMARKETDATA;
	if (pSpecificInstrument)
	{
		DFITCSECSpecificInstrumentField *task_data = new DFITCSECSpecificInstrumentField();
		*task_data = *pSpecificInstrument;
		task.task_data = task_data;
	}
	if (pRspInfo)
	{
		DFITCSECRspInfoField *task_error = new DFITCSECRspInfoField();
		*task_error = *pRspInfo;
		task.task_error = task_error;
	}
	this->task_queue.push(task);
};

        void MdApi::OnStockMarketData(struct DFITCStockDepthMarketDataField * pMarketDataField) 
{
	Task task = Task();
	task.task_name = ONSTOCKMARKETDATA;
	if (pMarketDataField)
	{
		DFITCStockDepthMarketDataField *task_data = new DFITCStockDepthMarketDataField();
		*task_data = *pMarketDataField;
		task.task_data = task_data;
	}
	this->task_queue.push(task);
};

        void MdApi::OnSOPMarketData(struct DFITCSOPDepthMarketDataField * pMarketDataField) 
{
	Task task = Task();
	task.task_name = ONSOPMARKETDATA;
	if (pMarketDataField)
	{
		DFITCSOPDepthMarketDataField *task_data = new DFITCSOPDepthMarketDataField();
		*task_data = *pMarketDataField;
		task.task_data = task_data;
	}
	this->task_queue.push(task);
};

        void MdApi::OnRspStockAvailableQuot(struct DFITCRspQuotQryField * pAvailableQuotInfo, struct DFITCSECRspInfoField * pRspInfo,bool flag) 
{
	Task task = Task();
	task.task_name = ONRSPSTOCKAVAILABLEQUOT;
	if (pAvailableQuotInfo)
	{
		DFITCRspQuotQryField *task_data = new DFITCRspQuotQryField();
		*task_data = *pAvailableQuotInfo;
		task.task_data = task_data;
	}
	if (pRspInfo)
	{
		DFITCSECRspInfoField *task_error = new DFITCSECRspInfoField();
		*task_error = *pRspInfo;
		task.task_error = task_error;
	}
	task.task_last = flag;
	this->task_queue.push(task);
};

        void MdApi::OnRspSopAvailableQuot(struct DFITCRspQuotQryField * pAvailableQuotInfo, struct DFITCSECRspInfoField * pRspInfo,bool flag) 
{
	Task task = Task();
	task.task_name = ONRSPSOPAVAILABLEQUOT;
	if (pAvailableQuotInfo)
	{
		DFITCRspQuotQryField *task_data = new DFITCRspQuotQryField();
		*task_data = *pAvailableQuotInfo;
		task.task_data = task_data;
	}
	if (pRspInfo)
	{
		DFITCSECRspInfoField *task_error = new DFITCSECRspInfoField();
		*task_error = *pRspInfo;
		task.task_error = task_error;
	}
	task.task_last = flag;
	this->task_queue.push(task);
};

        void MdApi::OnRspUserMDPasswordUpdate(struct DFITCSECRspMDPasswordUpdateField *pMDPasswordUpdate,struct DFITCSECRspInfoField * pRspInfo)
{
	Task task = Task();
	task.task_name = ONRSPUSERMDPASSWORDUPDATE;
	if (pMDPasswordUpdate)
	{
		DFITCSECRspMDPasswordUpdateField *task_data = new DFITCSECRspMDPasswordUpdateField();
		*task_data = *pMDPasswordUpdate;
		task.task_data = task_data;
	}
	if (pRspInfo)
	{
		DFITCSECRspInfoField *task_error = new DFITCSECRspInfoField();
		*task_error = *pRspInfo;
		task.task_error = task_error;
	}
	this->task_queue.push(task);
};

