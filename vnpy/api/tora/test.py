#!/usr/bin/python
# -*- coding: UTF-8 -*-

import sys
import sptraderapi
import time
import threading

def usage():
	print("Please select what you want to do:")
	print("1> login")
	print("2> insert order")
	print("3> query security")
	print("4> query trading account")
	print("5> quit")
	return input("")


class SPTraderSpi(sptraderapi.CTORATstpSPTraderSpi):
	def __init__(self,api,app):
		sptraderapi.CTORATstpSPTraderSpi.__init__(self)
		self.__api=api
		self.__req_id=0
		self.__app=app

	def OnFrontConnected(self):
		#print("OnFrontConnected")
		self.__app.wake_up()
		

	def OnRspUserLogin(self, pRspUserLoginField, pRspInfo, nRequestID):
		print("OnRspUserLogin: ErrorID[%d] ErrorMsg[%s] RequestID[%d]" % (pRspInfo['ErrorID'], pRspInfo['ErrorMsg'], nRequestID))
		if pRspInfo['ErrorID'] == 0:
			self.__app.wake_up()
	
	def OnRspOrderInsert(self, pInputOrderField, pRspInfo, nRequestID):
		print("OnRspOrderInsert: ErrorID[%d] ErrorMsg[%s] RequestID[%d]" % (pRspInfo['ErrorID'], pRspInfo['ErrorMsg'], nRequestID))
		print("\tInvestorID[%s] OrderRef[%d] OrderSysID[%s]" % (
														pInputOrderField['InvestorID'],
														pInputOrderField['OrderRef'],
														pInputOrderField['OrderSysID']))
		self.__app.wake_up()

	def OnRtnOrder(self, pOrder):
		print("OnRtnOrder: InvestorID[%s] SecurityID[%s] OrderRef[%d] OrderLocalID[%s] Price[%.2f] VolumeTotalOriginal[%d] OrderSysID[%s] OrderStatus[%s]" % (
			pOrder['InvestorID'],
			pOrder['SecurityID'],
			pOrder['OrderRef'],
			pOrder['OrderLocalID'],
			pOrder['Price'],
			pOrder['VolumeTotalOriginal'],
			pOrder['OrderSysID'],
			pOrder['OrderStatus']))
		
	def OnRtnTrade(self, pTrade):
		print("OnRtnTrade: TradeID[%s] InvestorID[%s] SecurityID[%s] OrderRef[%d] OrderLocalID[%s] Price[%.2f] Volume[%d]" % (
			pTrade['TradeID'],
			pTrade['InvestorID'],
			pTrade['SecurityID'],
			pTrade['OrderRef'],
			pTrade['OrderLocalID'],
			pTrade['Price'],
			pTrade['Volume']
		))

	def OnErrRtnOrderInsert(self, pInputOrder, pRspInfo, nRequestID):
		print("OnErrRtnOrderInsert")

	def OnRspQrySecurity(self, pSecurity, pRspInfo, nRequestID, bIsLast):
		print("OnRspQrySecurity: ErrorID[%d] ErrorMsg[%s] RequestID[%d] IsLast[%d]" %(
															pRspInfo['ErrorID'],
															pRspInfo['ErrorMsg'],
															nRequestID,
															bIsLast))

		if bIsLast!=1:
			print("SecurityID[%s] SecurityName[%s] UnderlyingSecurityID[%s] StrikeDate[%s]" % (
															pSecurity['SecurityID'],
															pSecurity['SecurityName'],
															pSecurity['UnderlyingSecurityID'],
															pSecurity['StrikeDate']))
		else:
			self.__app.wake_up()

	def OnRspQryTradingAccount(self, pTradingAccount, pRspInfo, nRequestID, bIsLast):
		print("OnRspQryTradingAccount")
		if bIsLast!=1:
			print("AccountID[%s]" %(pTradingAccount['AccountID']))
		else:
			self.__app.wake_up()
		
	def auto_increase_reqid(self):
		self.__req_id = self.__req_id + 1;

	def test_req_user_login(self):
		#请求编号自增
		self.auto_increase_reqid()
		#请求登录
		login_req = sptraderapi.CTORATstpSPReqUserLoginField()
		login_req.LogInAccount=input("input login user:")
		login_req.LogInAccountType = sptraderapi.TORA_TSTP_SP_LACT_UserID
		login_req.Password=input("input login password:")
		
		ret=self.__api.ReqUserLogin(login_req, self.__req_id)
		if ret!=0:
			print("ReqUserLogin ret[%d]" %(ret))
			self.__app.wake_up()

	def test_req_order_insert(self):
		#请求编号自增
		self.auto_increase_reqid()

		order_insert_field = sptraderapi.CTORATstpSPInputOrderField()

		order_insert_field.ShareholderID = input("ShareholderID:")
		order_insert_field.SecurityID = input("SecurityID:")
		order_insert_field.ExchangeID = input("ExchangeID:")
		order_insert_field.OrderRef = 0
		order_insert_field.OrderPriceType = sptraderapi.TORA_TSTP_SP_OPT_LimitPrice
		order_insert_field.Direction = sptraderapi.TORA_TSTP_SP_D_Buy
		order_insert_field.CombOffsetFlag = sptraderapi.TORA_TSTP_SP_OF_Open
		order_insert_field.CombHedgeFlag = sptraderapi.TORA_TSTP_SP_HF_Speculation
		order_insert_field.LimitPrice = float(input("LimitPrice:"))
		order_insert_field.VolumeTotalOriginal = int(input("VolumeTotalOriginal:"))
		order_insert_field.TimeCondition = sptraderapi.TORA_TSTP_SP_TC_GFD
		order_insert_field.VolumeCondition = sptraderapi.TORA_TSTP_SP_VC_AV
		
		

		ret=self.__api.ReqOrderInsert(order_insert_field, self.__req_id)
		if ret!=0:
			print("ReqOrderInsert ret[%d]" %(ret))
			self.__app.wake_up()

	def test_req_qry_security(self):
		#请求编号自增
		self.auto_increase_reqid()
		qry_security_field = sptraderapi.CTORATstpSPQrySecurityField()
		qry_security_field.SecurityID=input("SecurityID:")
		ret=self.__api.ReqQrySecurity(qry_security_field, self.__req_id)
		if ret!=0:
			print("ReqQrySecurity ret[%d]" %(ret))
			self.__app.wake_up()

	def test_req_qry_trading_account(self):
		#请求编号自增
		self.auto_increase_reqid()
		qry_trading_account_field = sptraderapi.CTORATstpSPQryTradingAccountField()
		ret=self.__api.ReqQryTradingAccount(qry_trading_account_field, self.__req_id)
		if ret!=0:
			print("ReqQryTradingAccount ret[%d]" %(ret))
			self.__app.wake_up()

	def OnRtnExercise(self, pExercise):
		print("OnRtnExercise")

	def OnErrRtnExerciseInsert(self, pInputExercise, pRspInfo, nRequestID):
		print("OnErrRtnExerciseInsert")

	def OnComRtnExercise(self, pExercise):
		pass

	def OnErrRtnComExerciseInsert(self, pInputComExercise, pRspInfo, nRequestID):
		pass

class TestApp(threading.Thread):
	def __init__(self, name, address):
		threading.Thread.__init__(self)
		self.__name = name
		self.__api = None
		self.__spi = None
		self.__address = address
		self.__lock = threading.Lock()
		self.__lock.acquire()

	def run(self):
		while True:
			if self.__api is None:
				print(sptraderapi.CTORATstpSPTraderApi_GetApiVersion())
				self.__api = sptraderapi.CTORATstpSPTraderApi.CreateTstpSPTraderApi()
				self.__spi = SPTraderSpi(self.__api, self)
				self.__api.RegisterSpi(self.__spi)
				self.__api.RegisterFront(self.__address)

				#订阅私有流
				self.__api.SubscribePrivateTopic(sptraderapi.TORA_TERT_RESTART)
				#订阅公有流
				self.__api.SubscribePublicTopic(sptraderapi.TORA_TERT_RESTART)

				#启动接口对象
				self.__api.Init()
			
			else:
				self.__lock.acquire()
				
				exit=False
				while True:
					choice=usage()
					if choice=="1":
						self.__spi.test_req_user_login()
						break
					elif choice=="2":
						self.__spi.test_req_order_insert()
						break
					elif choice=="3":
						self.__spi.test_req_qry_security()
						break
					elif choice=="4":
						self.__spi.test_req_qry_trading_account()
						break
					elif choice=="5":
						exit=True
						break
					else:
						print("invalid choice!")
						continue
				
				if exit == True:
					break


	def wake_up(self):
		self.__lock.release()

	def stop(self):
		self.__running=False

if __name__ == "__main__":
	print("###########1")
	app=TestApp("thread", "tcp://127.0.0.1:8500")
	print("#############2")

	app.start()
	print("#############3")

	app.join()