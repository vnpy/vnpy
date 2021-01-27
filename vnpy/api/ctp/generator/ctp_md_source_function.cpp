int MdApi::reqUserLogin(const dict &req, int reqid)
{
    CThostFtdcReqUserLoginField myreq = CThostFtdcReqUserLoginField();
    memset(&myreq, 0, sizeof(myreq));
    getString(req, "TradingDay", myreq.TradingDay);
    getString(req, "BrokerID", myreq.BrokerID);
    getString(req, "UserID", myreq.UserID);
    getString(req, "Password", myreq.Password);
    getString(req, "UserProductInfo", myreq.UserProductInfo);
    getString(req, "InterfaceProductInfo", myreq.InterfaceProductInfo);
    getString(req, "ProtocolInfo", myreq.ProtocolInfo);
    getString(req, "MacAddress", myreq.MacAddress);
    getString(req, "OneTimePassword", myreq.OneTimePassword);
    getString(req, "ClientIPAddress", myreq.ClientIPAddress);
    getString(req, "LoginRemark", myreq.LoginRemark);
    getInt(req, "ClientIPPort", &myreq.ClientIPPort);
    int i = this->api->ReqUserLogin(&myreq, reqid);
    return i;
};

int MdApi::reqUserLogout(const dict &req, int reqid)
{
    CThostFtdcUserLogoutField myreq = CThostFtdcUserLogoutField();
    memset(&myreq, 0, sizeof(myreq));
    getString(req, "BrokerID", myreq.BrokerID);
    getString(req, "UserID", myreq.UserID);
    int i = this->api->ReqUserLogout(&myreq, reqid);
    return i;
};

