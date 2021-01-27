.def("reqUserLogin", &MarketApi::reqUserLogin)
.def("reqBrokerData", &MarketApi::reqBrokerData)
.def("reqMarketData", &MarketApi::reqMarketData)

.def("onFrontConnected", &MarketApi::onFrontConnected)
.def("onFrontDisconnected", &MarketApi::onFrontDisconnected)
.def("onHeartBeatWarning", &MarketApi::onHeartBeatWarning)
.def("onRspRawData", &MarketApi::onRspRawData)
.def("onRspUserLogin", &MarketApi::onRspUserLogin)
.def("onRspTradeDate", &MarketApi::onRspTradeDate)
.def("onRspBrokerData", &MarketApi::onRspBrokerData)
.def("onRspMarketData", &MarketApi::onRspMarketData)
;
