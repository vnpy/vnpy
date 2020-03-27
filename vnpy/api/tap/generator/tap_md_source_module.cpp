.def("qryCommodity", &MdApi::qryCommodity)
.def("qryContract", &MdApi::qryContract)

.def("onRspLogin", &MdApi::onRspLogin)
.def("onAPIReady", &MdApi::onAPIReady)
.def("onDisconnect", &MdApi::onDisconnect)
.def("onRspQryCommodity", &MdApi::onRspQryCommodity)
.def("onRspQryContract", &MdApi::onRspQryContract)
.def("onRspSubscribeQuote", &MdApi::onRspSubscribeQuote)
.def("onRspUnSubscribeQuote", &MdApi::onRspUnSubscribeQuote)
.def("onRtnQuote", &MdApi::onRtnQuote)
;
