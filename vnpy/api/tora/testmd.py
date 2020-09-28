#!/usr/bin/python
# -*- coding: UTF-8 -*-

import sys
import spmdapi


class SPMdSpi(spmdapi.CTORATstpSPMdSpi):
	def __init__(self,api):
		spmdapi.CTORATstpSPMdSpi.__init__(self)
		self.__api=api

	def OnFrontConnected(self):
		print("OnFrontConnected")
		#请求登录
		login_req = spmdapi.CTORATstpSPReqUserLoginField()
		self.__api.ReqUserLogin(login_req,1) 

	def OnRspUserLogin(self, pRspUserLogin, pRspInfo, nRequestID):
		print("OnRspUserLogin: ErrorID[%d] ErrorMsg[%s] RequestID[%d]" % (pRspInfo['ErrorID'], pRspInfo['ErrorMsg'], nRequestID))
		if pRspInfo['ErrorID'] == 0:
			#订阅行情
			sub_list=[b'00000000']
			self.__api.SubscribeMarketData(sub_list, spmdapi.TORA_TSTP_SP_EXD_SSE)

	def OnRspSubMarketData(self, pSpecificSecurity, pRspInfo, nRequestID, bIsLast):
		print("OnRspSubMarketData")

	def OnRtnDepthMarketData(self, pDepthMarketData):
		print("OnRtnDepthMarketData SecurityID[%s] TradingDay[%s] LastPrice[%.2f] Volume[%d] Turnover[%.2f] BidPrice1[%.2f] BidVolume1[%d] AskPrice1[%.2f] AskVolume1[%d]" % (pDepthMarketData['SecurityID'],
																	pDepthMarketData['TradingDay'],
																	pDepthMarketData['LastPrice'],
																	pDepthMarketData['Volume'],
																	pDepthMarketData['Turnover'],
																	pDepthMarketData['BidPrice1'],
																	pDepthMarketData['BidVolume1'],
																	pDepthMarketData['AskPrice1'],
																	pDepthMarketData['AskVolume1']))

if __name__ == "__main__":
	print(spmdapi.CTORATstpSPMdApi_GetApiVersion())
	api = spmdapi.CTORATstpSPMdApi_CreateTstpSPMdApi()
	spi = SPMdSpi(api)
	api.RegisterSpi(spi)
	api.RegisterFront("tcp://127.0.0.1:8402")
	api.Init()
	print("finish init md")
	str = input("")