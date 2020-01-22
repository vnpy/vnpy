.def("reqDepthMarketDataSubscribe", &MdApi::reqDepthMarketDataSubscribe)
.def("reqDepthMarketDataCancel", &MdApi::reqDepthMarketDataCancel)

.def("onFrontConnected", &MdApi::onFrontConnected)
.def("onFrontDisconnected", &MdApi::onFrontDisconnected)
.def("onRspDepthMarketDataSubscribe", &MdApi::onRspDepthMarketDataSubscribe)
.def("onRspDepthMarketDataCancel", &MdApi::onRspDepthMarketDataCancel)
.def("onRtnDepthMarketData", &MdApi::onRtnDepthMarketData)
;
