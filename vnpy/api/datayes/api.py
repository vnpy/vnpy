#encoding: UTF-8
import os
import json
import time
import requests
import pymongo
import pandas as pd

from datetime import datetime, timedelta
from Queue import Queue, Empty
from threading import Thread, Timer
from pymongo import MongoClient

from requests.exceptions import ConnectionError
from errors import (VNPAST_ConfigError, VNPAST_RequestError,
VNPAST_DataConstructorError)

class Config(object):
	"""
	Json-like config object.

	The Config contains all kinds of settings and user info that 
	could be useful in the implementation of Api wrapper.

	privates
	--------
	* head: string; the name of config file.
	* token: string; user's token.
	* body: dictionary; the main content of config.
			- domain: string, api domain.
			- ssl:  boolean, specifes http or https usage.
			- version: string, version of the api. Currently 'v1'.
			- header: dictionary; the request header which contains 
					  authorization infomation.

	"""
	head = 'my config'

	toke_ = '44ebc0f058981f85382595f9f15f967' + \
			'0c7eaf2695de30dd752e8f33e9022baa0'

	token = '575593eb7696aec7339224c0fac2313780d8645f68b77369dcb35f8bcb419a0b'

	body = {
		'ssl': False,
		'domain': 'api.wmcloud.com/data',
		'version': 'v1',
		'header': {
			'Connection' : 'keep-alive',
			'Authorization': 'Bearer ' + token
		}
	}

	def __init__(self, head=None, token=None, body=None):
		""" 
		Reloaded constructor. 

		parameters
		----------
		* head: string; the name of config file. Default is None.
		* token: string; user's token.
		* body: dictionary; the main content of config
		"""
		if head:
			self.head = head
		if token: 
			self.token = token
		if body:
			self.body = body

	def view(self):
		""" Prettify printing method. """
		config_view = {
			'config_head' : self.head,
			'config_body' : self.body,
			'user_token' : self.token
		}
		print json.dumps(config_view, 
						 indent=4, 
						 sort_keys=True)

#----------------------------------------------------------------------
# Data containers.

class BaseDataContainer(object):
	"""
	Basic data container. The fundamental of all other data 
	container objects defined within this module.

	privates
	--------
	* head: string; the head(type) of data container.
	* body: dictionary; data content. Among all sub-classes that inherit 
	BaseDataContainer, type(body) varies according to the financial meaning
	that the child data container stands for. 
		- History:
		- Bar

	"""
	head = 'ABSTRACT_DATA'
	body = dict()
	pass

class History(BaseDataContainer):
	"""
	Historical data container. The foundation of all other pandas
	DataFrame-like two dimensional data containers for this module.

	privates
	--------
	* head: string; the head(type) of data container.
	* body: pd.DataFrame object; contains data contents.

	"""
	head = 'HISTORY'
	body = pd.DataFrame()

	def __init__(self, data):
		"""
		Reloaded constructor. 

		parameters
		----------
		* data: dictionary; usually a Json-like response from
		  web based api. For our purposes, data is exactly resp.json()
		  where resp is the response from datayes developer api.

		  		- example: {'data': [
								{
									'closePrice': 15.88,
									'date': 20150701, ...
								},
								{
									'closePrice': 15.99,
									'date': 20150702, ...
								}, ...], 
							'retCode': 1, 
							'retMsg': 'Success'}.

		  So the body of data is actually in data['data'], which is
		  our target when constructing the container.

		"""
		try:
			assert 'data' in data
			self.body = pd.DataFrame(data['data'])
		except AssertionError:
			msg = '[{}]: Unable to construct history data; '.format(
					self.head) + 'input is not a dataframe.'
			raise VNPAST_DataConstructorError(msg)
		except Exception,e:
			msg = '[{}]: Unable to construct history data; '.format(
					self.head) + str(e)
			raise VNPAST_DataConstructorError(msg)

class Bar(History):
	"""
	Historical Bar data container. Inherits from History()
	DataFrame-like two dimensional data containers for Bar data.

	privates
	--------
	* head: string; the head(type) of data container.
	* body: pd.DataFrame object; contains data contents.
	"""
	head = 'HISTORY_BAR'
	body = pd.DataFrame()

	def __init__(self, data):
		"""
		Reloaded constructor. 

		parameters
		----------
		* data: dictionary; usually a Json-like response from
		  web based api. For our purposes, data is exactly resp.json()
		  where resp is the response from datayes developer api.

		  		- example: {'data': [{
		  					'exchangeCD': 'XSHG', 
		  					'utcOffset': '+08:00', 
		  					'unit': 1, 
		  					'currencyCD': 'CNY', 
		  					'barBodys': [
			  						{
			  							'closePrice': 15.88,
										'date': 20150701, ...
			  						},
			  						{
			  							'closePrice': 15.99,
										'date': 20150702, ...
			  						}, ... ],
			  				'ticker': '000001', 
			  				'shortNM': u'\u4e0a\u8bc1\u6307\u6570'
			  				}, ...(other tickers) ],
							'retCode': 1, 
							'retMsg': 'Success'}.

		  When requesting 1 ticker, json['data'] layer has only one element;
		  we expect that this is for data collectioning for multiple tickers,
		  which is currently impossible nevertheless.
 
		  So we want resp.json()['data'][0]['barBodys'] for Bar data contents,
		  and that is what we go into when constructing Bar.
		"""
		try:
			assert 'data' in data
			assert 'barBodys' in data['data'][0]
			self.body = pd.DataFrame(data['data'][0]['barBodys'])
		except AssertionError:
			msg = '[{}]: Unable to construct history data; '.format(
					self.head) + 'input is not a dataframe.'
			raise VNPAST_DataConstructorError(msg)
		except Exception,e:
			msg = '[{}]: Unable to construct history data; '.format(
					self.head) + str(e)
			raise VNPAST_DataConstructorError(msg)


#----------------------------------------------------------------------
# Datayes Api class

class PyApi(object):
	"""
	Python based Datayes Api object.

	PyApi should be initialized with a Config json. The config must be complete,
	in that once constructed, the private variables like request headers, 
	tokens, etc. become constant values (inherited from config), and will be 
	consistantly referred to whenever make requests.


	privates
	--------
	* _config: Config object; a container of all useful settings when making 
	  requests.
	* _ssl, _domain, _domain_stream, _version, _header, _account_id: 
	  boolean, string, string, string, dictionary, integer;
	  just private references to the items in Config. See the docs of Config().
	* _session: requests.session object.


	examples
	--------


	"""
	_config = Config()

	# request stuffs
	_ssl = False
	_domain = ''
	_version = 'v1'
	_header = dict()
	_token = None

	_session = requests.session()

	def __init__(self, config):
		"""
		Constructor.

		parameters
		----------
		* config: Config object; specifies user and connection configs.
		"""
		if config.body:
			try:
				self._config = config
				self._ssl = config.body['ssl']
				self._domain = config.body['domain']
				self._version = config.body['version']
				self._header = config.body['header']
			except KeyError:
				msg = '[API]: Unable to configure api; ' + \
					  'config file is incomplete.'
				raise VNPAST_ConfigError(msg)
			except Exception,e:
				msg = '[API]: Unable to configure api; ' + str(e)
				raise VNPAST_ConfigError(msg)

		# configure protocol
		if self._ssl:
			self._domain = 'https://' + self._domain
		else:
			self._domain = 'http://' + self._domain

	def __access(self, url, params, method='GET'):
		"""
		request specific data from given url with parameters.

		parameters
		----------
		* url: string.
		* params: dictionary.
		* method: string; 'GET' or 'POST', request method.

		"""
		try:
			assert type(url) == str
			assert type(params) == dict
		except AssertionError,e:
			raise e('[API]: Unvalid url or parameter input.')
		if not self._session:
			s = requests.session()
		else: s = self._session

		# prepare and send the request.
		try:
			req = requests.Request(method,
								   url = url,
								   headers = self._header,
								   params = params)
			prepped = s.prepare_request(req) # prepare the request
			resp = s.send(prepped, stream=False, verify=True)
			if method == 'GET':
				assert resp.status_code == 200
			elif method == 'POST':
				assert resp.status_code == 201
			return resp
		except AssertionError:
			msg = '[API]: Bad request, unexpected response status: ' + \
				  str(resp.status_code)
			raise VNPAST_RequestError(msg)
			pass
		except Exception,e:
			msg = '[API]: Bad request.' + str(e)
			raise VNPAST_RequestError(msg)

	#----------------------------------------------------------------------
	# directly get methods - Market data

	def get_equity_M1_one(self,
					  	  start='', end='', secID='000001.XSHG'):
		"""
		Get 1-minute intraday bar data of one security.

		parameters
		----------
		* start, end: string; Time mark formatted in 'HH:MM'. Specifies the 
		  start/end point of bar. Note that the requested date is the 
		  latest trading day (only one day), and the default start/end time is
		  '09:30' and min(now, '15:00'). Effective minute bars range from 
		  09:30 - 11:30 in the morning and 13:01 - 15:00 in the afternoon.
		* secID: string; the security ID in the form of '000001.XSHG', i.e.
		  ticker.exchange

		"""
		url = '{}/{}/api/market/getBarRTIntraDay.json'.format(
			   self._domain, self._version)
		params = {
			'startTime': start,
			'endTime': end,
			'securityID': secID,
		}
		try:
			resp = self.__access(url=url, params=params)
			assert len(resp.json()) > 0
			print resp.json()
			data = Bar(resp.json())
			return data
		except AssertionError: return 0


	def get_equity_M1(self, field='', start='20130701', end='20130730', 
					  secID='000001.XSHG', output='df'):
		"""
		1-minute bar in a month, currently unavailable.

		parameters
		----------
		* field: string; variables that are to be requested.
		* start, end: string; Time mark formatted in 'YYYYMMDD'.
		* secID: string; the security ID in the form of '000001.XSHG', i.e.
		  ticker.exchange
		* output: enumeration of strings; the format of output that will be 
		  returned. default is 'df', optionals are:
		  		- 'df': returns History object, 
		  			  where ret.body is a dataframe.
		  		- 'list': returns a list of dictionaries.

		"""
		url = '{}/{}/api/market/getBarHistDateRange.json'.format(
			   self._domain, self._version)
		params = {
			'field': field,
			'startDate': start,
			'endDate': end,
			'securityID': secID,
		}
		try:
			resp = self.__access(url=url, params=params)
			assert len(resp.json()) > 0
			if output == 'df':
				data = Bar(resp.json())
			elif output == 'list':
				data = resp.json()['data'][0]['barBodys']
			return data
		except AssertionError: return 0


	def get_equity_D1(self, field='', start='', end='', secID='',
					  ticker='', one=20150513, output='df'):
		"""
		Get 1-day interday bar data of one security.

		parameters
		----------
		* field: string; variables that are to be requested. Available variables
		  are: (* is unique for securities)

		  		- secID 				string.
		  		- tradeDate 			date(?).
		  		- ticker 				string.
		  		- secShortName 			string.
		  		- exchangeCD 			string.
		  		- preClosePrice 		double.
		  		- actPreClosePrice*		double.
		  		- openPrice		 		double.
		  		- highestPrice	 		double.
		  		- lowestPrice 			double.
		  		- closePrice 			double.
		  		- turnoverVol 			double.
		  		- turnoverValue 		double.
		  		- dealAmount* 			integer.
		  		- turnoverRate	 		double.
		  		- accumAdjFactor* 		double.
		  		- negMarketValue* 		double.
		  		- marketValue* 			double.
		  		- PE* 					double.
		  		- PE1* 					double.
		  		- PB* 					double.

		  Field is an optional parameter, default setting returns all fields.

		* start, end: string; Date mark formatted in 'YYYYMMDD'. Specifies the 
		  start/end point of bar. Start and end are optional parameters. If 
		  start, end and ticker are all specified, default 'one' value will be
		  abandoned.

		* secID: string; the security ID in the form of '000001.XSHG', i.e.
		  ticker.exchange.

		* ticker: string; the trading code in the form of '000001'.

		* one: string; Date mark formatted in 'YYYYMMDD'. 
		  Specifies one date on which data of all tickers are to be requested. 
		  Note that to get effective json data response, at least one parameter 
		  in {secID, ticker, tradeDate} should be entered.

		* output: enumeration of strings; the format of output that will be 
		  returned. default is 'df', optionals are:
		  		- 'df': returns History object, 
		  			  where ret.body is a dataframe.
		  		- 'list': returns a list of dictionaries.

		"""
		if start and end and ticker:
			one = '' # while user specifies start/end, covers tradeDate.

		url = '{}/{}/api/market/getMktEqud.json'.format(
			   self._domain, self._version)
		params = {
			'field': field,
			'beginDate': start,
			'endDate': end,
			'secID': secID,
			'ticker': ticker,
			'tradeDate': one
		}
		try:
			resp = self.__access(url=url, params=params)
			assert len(resp.json()) > 0
			if output == 'df':
				data = History(resp.json())
			elif output == 'list':
				data = resp.json()['data']
			return data
			#return resp
		except AssertionError: return 0

	def get_block_D1(self, field='', start='', end='', secID='',
					 ticker='', one=20150513):
		"""

		"""
		pass

	def get_repo_D1(self, field='', start='', end='', secID='',
					ticker='', one=20150513):
		"""

		"""
		pass

	def get_bond_D1(self, field='', start='', end='', secID='',
					ticker='', one=20150513, output='df'):
		"""
		Get 1-day interday bar data of one bond instrument.

		parameters
		----------

		* field: string; variables that are to be requested. Available variables
		  are: (* is unique for bonds)

		  		- secID 				string.
		  		- tradeDate 			date(?).
		  		- ticker 				string.
		  		- secShortName 			string.
		  		- exchangeCD 			string.
		  		- preClosePrice 		double.
		  		- openPrice		 		double.
		  		- highestPrice	 		double.
		  		- lowestPrice 			double.
		  		- closePrice 			double.
		  		- turnoverVol 			double.
		  		- turnoverValue 		double.
		  		- turnoverRate	 		double.
		  		- dealAmount*			integer.
		  		- accrInterest*			double.
		  		- YTM(yieldToMaturity)* double.	

		  Field is an optional parameter, default setting returns all fields.

		* start, end, secID, ticker, one, output
		  string, string, string, string, string, string(enum)
		  Same as above, reference: get_equity_D1().

		"""
		if start and end and ticker:
			one = '' # while user specifies start/end, covers tradeDate.

		url = '{}/{}/api/market/getMktBondd.json'.format(
			   self._domain, self._version)
		params = {
			'field': field,
			'beginDate': start,
			'endDate': end,
			'secID': secID,
			'ticker': ticker,
			'tradeDate': one
		}
		try:
			resp = self.__access(url=url, params=params)
			assert len(resp.json()) > 0
			if output == 'df':
				data = History(resp.json())
			elif output == 'list':
				data = resp.json()['data']
			return data
		except AssertionError: return 0

	def get_future_D1(self, field='', start='', end='', secID='',
					ticker='', one=20150513, output='df'):
		"""
		Get 1-day interday bar data of one future contract.

		parameters
		----------

		* field: string; variables that are to be requested. Available variables
		  are: (* is unique for future contracts)

		  		- secID 				string.
		  		- tradeDate 			date(?).
		  		- ticker 				string.
		  		- secShortName 			string.
		  		- exchangeCD 			string.
		  		- contractObject*		string.
		  		- contractMark*			string.
		  		- preSettlePrice*		double.
		  		- preClosePrice 		double.
		  		- openPrice		 		double.
		  		- highestPrice	 		double.
		  		- lowestPrice 			double.
		  		- closePrice 			double.
		  		- settlePrice* 			double.
		  		- turnoverVol 			integer.
		  		- turnoverValue 		integer.
		  		- openInt*				integer.
		  		- CHG* 					double.
		  		- CHG1* 				double.
		  		- CHGPct*				double.
		  		- mainCon*				integer (0/1 flag).
		  		- smainCon*				integer (0/1 flag).

		  Field is an optional parameter, default setting returns all fields.

		* start, end, secID, ticker, one, output
		  string, string, string, string, string, string(enum)
		  Same as above, reference: get_equity_D1().
		"""
		if start and end and ticker:
			one = '' # while user specifies start/end, covers tradeDate.

		url = '{}/{}/api/market/getMktFutd.json'.format(
			   self._domain, self._version)
		params = {
			'field': field,
			'beginDate': start,
			'endDate': end,
			'secID': secID,
			'ticker': ticker,
			'tradeDate': one
		}
		try:
			resp = self.__access(url=url, params=params)
			assert len(resp.json()) > 0
			if output == 'df':
				data = History(resp.json())
			elif output == 'list':
				data = resp.json()['data']
			return data
		except AssertionError: return 0

	def get_future_main_D1(self, field='', start='', end='', mark='',
						   obj='', main=1, one=20150513):
		"""

		"""
		pass

	def get_fund_D1(self, field='', start='', end='', secID='',
					ticker='', one=20150513, output='df'):
		"""
		Get 1-day interday bar data of one mutual fund.

		parameters
		----------

		* field: string; variables that are to be requested. Available variables
		  are: (* is unique for funds)

		  		- secID 				string.
		  		- tradeDate 			date(?).
		  		- ticker 				string.
		  		- secShortName 			string.
		  		- exchangeCD 			string.
		  		- preClosePrice 		double.
		  		- openPrice		 		double.
		  		- highestPrice	 		double.
		  		- lowestPrice 			double.
		  		- closePrice 			double.
		  		- turnoverVol 			double.
		  		- turnoverValue 		double.
		  		- CHG* 					double.
		  		- CHGPct*				double.
		  		- discount* 			double.
		  		- discountRatio*		double.
		  		- circulationShares*	double.

		  Field is an optional parameter, default setting returns all fields.

		* start, end, secID, ticker, one, output
		  string, string, string, string, string, string(enum)
		  Same as above, reference: get_equity_D1().

		"""
		if start and end and ticker:
			one = '' # while user specifies start/end, covers tradeDate.

		url = '{}/{}/api/market/getMktFundd.json'.format(
			   self._domain, self._version)
		params = {
			'field': field,
			'beginDate': start,
			'endDate': end,
			'secID': secID,
			'ticker': ticker,
			'tradeDate': one
		}
		try:
			resp = self.__access(url=url, params=params)
			assert len(resp.json()) > 0
			if output == 'df':
				data = History(resp.json())
			elif output == 'list':
				data = resp.json()['data']
			return data
		except AssertionError: return 0

	def get_index_D1(self, field='', start='', end='', indexID='',
					 ticker='', one=20150513, output='df'):
		"""
		Get 1-day interday bar data of one stock index.

		parameters
		----------

		* field: string; variables that are to be requested. Available variables
		  are: (* is unique for indices)

		  		- indexID 				string.
		  		- tradeDate 			date(?).
		  		- ticker 				string.
		  		- secShortName 			string.
		  		- porgFullName*			string.
		  		- exchangeCD 			string.
		  		- preCloseIndex 		double.
		  		- openIndex		 		double.
		  		- highestIndex	 		double.
		  		- lowestIndex 			double.
		  		- closeIndex 			double.
		  		- turnoverVol 			double.
		  		- turnoverValue 		double.
		  		- CHG* 					double.
		  		- CHGPct*				double.

		  Field is an optional parameter, default setting returns all fields.

		* start, end, secID, ticker, one, output
		  string, string, string, string, string, string(enum)
		  Same as above, reference: get_equity_D1().

		"""
		if start and end and ticker:
			one = '' # while user specifies start/end, covers tradeDate.

		url = '{}/{}/api/market/getMktIdxd.json'.format(
			   self._domain, self._version)
		params = {
			'field': field,
			'beginDate': start,
			'endDate': end,
			'indexID': indexID,
			'ticker': ticker,
			'tradeDate': one
		}
		try:
			resp = self.__access(url=url, params=params)
			assert len(resp.json()) > 0
			if output == 'df':
				data = History(resp.json())
			elif output == 'list':
				data = resp.json()['data']
			return data
		except AssertionError: return 0

	def get_option_D1(self, field='', start='', end='', secID='',
					  optID='' ,ticker='', one=20150513, output='df'):
		"""
		Get 1-day interday bar data of one option contact.

		parameters
		----------

		* field: string; variables that are to be requested. Available variables
		  are: (* is unique for options)

		  		- secID 				string.
		  		- optID* 				string.
		  		- tradeDate 			date(?).
		  		- ticker 				string.
		  		- secShortName 			string.
		  		- exchangeCD 			string.
		  		- preClosePrice 		double.
		  		- openPrice		 		double.
		  		- highestPrice	 		double.
		  		- lowestPrice 			double.
		  		- closePrice 			double.
		  		- settlePrice*			double.
		  		- turnoverVol 			double.
		  		- turnoverValue 		double.
		  		- openInt*				integer.

		  Field is an optional parameter, default setting returns all fields.

		* start, end, secID, ticker, one, output
		  string, string, string, string, string, string(enum)
		  Same as above, reference: get_equity_D1().

		"""
		if start and end and ticker:
			one = '' # while user specifies start/end, covers tradeDate.

		url = '{}/{}/api/market/getMktOptd.json'.format(
			   self._domain, self._version)
		params = {
			'field': field,
			'beginDate': start,
			'endDate': end,
			'secID': secID,
			'optID': optID,
			'ticker': ticker,
			'tradeDate': one
		}
		try:
			resp = self.__access(url=url, params=params)
			assert len(resp.json()) > 0
			if output == 'df':
				data = History(resp.json())
			elif output == 'list':
				data = resp.json()['data']
			return data
		except AssertionError: return 0

	def get_stockFactor_D1(self, field='', secID='',
					  	   ticker='000001', start=20130701, end=20130801):
		"""
		Get 1-day interday factor data for stocks.

		parameters
		----------

		* field: string; variables that are to be requested. 
		  Field is an optional parameter, default setting returns all fields.

		* start, end, secID, ticker, one, output
		  string, string, string, string, string, string(enum)
		  Same as above, reference: get_equity_D1().
		"""
		url = '{}/{}/api/market/getStockFactorsDateRange.json'.format(
			   self._domain, self._version)
		params = {
			'field': field,
			'beginDate': start,
			'endDate': end,
			'secID': secID,
			'ticker': ticker
		}
		try:
			resp = self.__access(url=url, params=params)
			assert len(resp.json()) > 0
			data = History(resp.json())
			return data
		except AssertionError: return 0
		
	#----------------------------------------------------------------------
	# directly get methods - Fundamental Data

	def get_balanceSheet(self, field='', secID='',
						 start='', end='', pubStart='', pubEnd='',
						 reportType='', ticker='000001'):
		"""

		"""
		url = '{}/{}/api/fundamental/getFdmtBS.json'.format(
			  self._domain, self._version)
		params = {
			'field': field,
			'secID': secID,
			'ticker': ticker,
			'beginDate': start,
			'endDate': end,
			'publishDateBegin': pubStart,
			'publishDateEnd': pubEnd,
			'reportType': reportType
		}
		try:
			resp = self.__access(url=url, params=params)
			assert len(resp.json()) > 0
			data = History(resp.json())
			return data
		except AssertionError: return 0

	def get_balanceSheet_bnk(self):
		"""

		"""
		pass

	def get_balanceSheet_sec(self):
		"""

		"""
		pass

	def get_balanceSheet_ins(self):
		"""

		"""
		pass

	def get_balanceSheet_ind(self):
		"""

		"""
		pass

	def get_cashFlow(self, field='', secID='',
					 start='', end='', pubStart='', pubEnd='',
					 reportType='', ticker='000001'):
		"""

		"""
		url = '{}/{}/api/fundamental/getFdmtCF.json'.format(
			  self._domain, self._version)
		params = {
			'field': field,
			'secID': secID,
			'ticker': ticker,
			'beginDate': start,
			'endDate': end,
			'publishDateBegin': pubStart,
			'publishDateEnd': pubEnd,
			'reportType': reportType
		}
		try:
			resp = self.__access(url=url, params=params)
			assert len(resp.json()) > 0
			data = History(resp.json())
			return data
		except AssertionError: return 0

	def get_cashFlow_bnk(self):
		"""

		"""
		pass

	def get_cashFlow_sec(self):
		"""

		"""
		pass

	def get_cashFlow_ins(self):
		"""

		"""
		pass

	def get_cashFlow_ind(self):
		"""

		"""
		pass

	def get_incomeStatement(self, field='', secID='',
					 		start='', end='', pubStart='', pubEnd='',
					 		reportType='', ticker='000001'):
		"""

		"""
		url = '{}/{}/api/fundamental/getFdmtIS.json'.format(
			  self._domain, self._version)
		params = {
			'field': field,
			'secID': secID,
			'ticker': ticker,
			'beginDate': start,
			'endDate': end,
			'publishDateBegin': pubStart,
			'publishDateEnd': pubEnd,
			'reportType': reportType
		}
		try:
			resp = self.__access(url=url, params=params)
			assert len(resp.json()) > 0
			data = History(resp.json())
			return data
		except AssertionError: return 0

	def get_incomeStatement_bnk(self):
		"""

		"""
		pass

	def get_incomeStatement_sec(self):
		"""

		"""
		pass

	def get_incomeStatement_ins(self):
		"""

		"""
		pass

	def get_incomeStatement_ind(self):
		"""

		"""
		pass

	#----------------------------------------------------------------------
	# multi-threading download for database storage.

	def __drudgery(self, id, db, indexType,
				  start, end, tasks, target):
		"""
		basic drudgery function.
		This method loops over a list of tasks(tickers) and get data using
		target api.get_# method for all those tickers.
		A new feature 'date' or 'dateTime'(for intraday) will be automatically
		added into every json-like documents, and specifies the datetime.
		datetime() formatted date(time) mark. With the setting of MongoDB
		in this module, this feature should be the unique index for all 
		collections.

		By programatically assigning creating and assigning tasks to drudgery
		functions, multi-threading download of data can be achieved.

		parameters
		----------
		* id: integer; the ID of Drudgery session.

		* db: pymongo.db object; the database which collections of bars will
		  go into.

		* indexType: string(enum): 'date' or 'datetime', specifies what
		  is the collection index formatted.

		* start, end: string; Date mark formatted in 'YYYYMMDD'. Specifies the 
		  start/end point of collections of bars.

		* tasks: list of strings; the tickers that this drudgery function
		  loops over.

		* target: method; the api.get_# method that is to be called by 
		  drudgery function.
		"""
		if len(tasks) == 0:
			return 0

		# str to datetime inline functions.
		if indexType == 'date':
			todt = lambda str_dt: datetime.strptime(str_dt,'%Y-%m-%d')
			update_dt = lambda d: d.update({'date':todt(d['tradeDate'])})
		elif indexType == 'datetime':
			todt = lambda str_d, str_t: datetime.strptime(
				str_d + ' ' + str_t,'%Y-%m-%d %H:%M')
			update_dt = lambda d: d.update(
				{'dateTime':todt(d['dataDate'], d['barTime'])})
		else:
			raise ValueError

		# loop over all tickers in task list.
		k, n = 1, len(tasks)
		for ticker in tasks:
			try:
				data = target(start = start,
							  end = end, 
							  ticker = ticker,
							  output = 'list')
				assert len(data) >= 1
				map(update_dt, data) # add datetime feature to docs.
				coll = db[ticker]
				coll.insert_many(data)
				print '[API|Session{}]: '.format(id) + \
					  'Finished {} in {}.'.format(k, n)
				k += 1
			except AssertionError:
				msg = '[API|Session{}]: '.format(id) + \
					  'Empty dataset in the response.'
				print msg
				pass
			except Exception, e:
				msg = '[API|Session{}]: '.format(id) + \
					  'Exception encountered when ' + \
					  'requesting data; ' + str(e)
				print msg
				pass

	def get_equity_D1_drudgery(self, id, db, start, end, tasks=[]):
		"""
		call __drudgery targeting at get_equity_D1()
		"""
		self.__drudgery(id=id, db=db,
					   indexType = 'date',
					   start = start, 
					   end = end, 
					   tasks = tasks,
					   target = self.get_equity_D1)

	def get_future_D1_drudgery(self, id, db, start, end, tasks=[]):
		"""
		call __drudgery targeting at get_future_D1()
		"""
		self.__drudgery(id=id, db=db, 
					   indexType = 'date',
					   start = start, 
					   end = end, 
					   tasks = tasks,
					   target = self.get_future_D1)

	def get_index_D1_drudgery(self, id, db, start, end, tasks=[]):
		"""
		call __drudgery targeting at get_index_D1()
		"""
		self.__drudgery(id=id, db=db, 
					   indexType = 'date',
					   start = start, 
					   end = end, 
					   tasks = tasks,
					   target = self.get_index_D1)

	def get_bond_D1_drudgery(self, id, db, start, end, tasks=[]):
		"""
		call __drudgery targeting at get_bond_D1()
		"""
		self.__drudgery(id=id, db=db, 
					   indexType = 'date',
					   start = start, 
					   end = end, 
					   tasks = tasks,
					   target = self.get_bond_D1)

	def get_fund_D1_drudgery(self, id, db, start, end, tasks=[]):
		"""
		call __drudgery targeting at get_fund_D1()
		"""
		self.__drudgery(id=id, db=db, 
					   indexType = 'date',
					   start = start, 
					   end = end, 
					   tasks = tasks,
					   target = self.get_fund_D1)

	def get_option_D1_drudgery(self, id, db, start, end, tasks=[]):
		"""
		call __drudgery targeting at get_option_D1()
		"""
		self.__drudgery(id=id, db=db, 
					   indexType = 'date',
					   start = start, 
					   end = end, 
					   tasks = tasks,
					   target = self.get_option_D1)

	#----------------------------------------------------------------------

	def __overlord(self, db, start, end, dName, 
				   target1, target2, sessionNum):
		"""
		Basic controller of multithreading request.
		Generates a list of all tickers, creates threads and distribute 
		tasks to individual #_drudgery() functions.

		parameters
		----------
		* db: pymongo.db object; the database which collections of bars will
		  go into. Note that this database will be transferred to every 
		  drudgery functions created by controller.

		* start, end: string; Date mark formatted in 'YYYYMMDD'. Specifies the 
		  start/end point of collections of bars.

		* dName: string; the path of file where all tickers' infomation
		  are stored in. 

		* target1: method; targetting api method that overlord calls
		  to get tasks list.

		* target2: method; the corresponding drudgery function.

		* sessionNum: integer; the number of threads that will be deploied.
		  Concretely, the list of all tickers will be sub-divided into chunks,
		  where chunkSize = len(allTickers)/sessionNum.

		"""
		if os.path.isfile(dName):
			# if directory exists, read from it.
			jsonFile = open(dName,'r')
			allTickers = json.loads(jsonFile.read())
			jsonFile.close()
		else:
			data = target1()
			allTickers = list(data.body['ticker'])
		
		chunkSize = len(allTickers)/sessionNum
		taskLists = [allTickers[k:k+chunkSize] for k in range(
						0, len(allTickers), chunkSize)]
		k = 0
		for tasks in taskLists:
			thrd = Thread(target = target2,
						  args = (k, db, start, end, tasks))
			thrd.start()
			k += 1
		return 1

	def get_equity_D1_mongod(self, db, start, end, sessionNum=30):
		"""
		Controller of get equity D1 method.
		"""
		self.__overlord(db = db,
						start = start,
						end = end,
						dName = 'names/equTicker.json',
						target1 = self.get_equity_D1,
						target2 = self.get_equity_D1_drudgery,
						sessionNum = sessionNum)

	def get_future_D1_mongod(self, db, start, end, sessionNum=30):
		"""
		Controller of get future D1 method.
		"""
		self.__overlord(db = db,
						start = start,
						end = end,
						dName = 'names/futTicker.json',
						target1 = self.get_future_D1,
						target2 = self.get_future_D1_drudgery,
						sessionNum = sessionNum)

	def get_index_D1_mongod(self, db, start, end, sessionNum=30):
		"""
		Controller of get index D1 method.
		"""
		self.__overlord(db = db,
						start = start,
						end = end,
						dName = 'names/idxTicker.json',
						target1 = self.get_index_D1,
						target2 = self.get_index_D1_drudgery,
						sessionNum = sessionNum)

	def get_bond_D1_mongod(self, db, start, end, sessionNum=30):
		"""
		Controller of get bond D1 method.
		"""
		self.__overlord(db = db,
						start = start,
						end = end,
						dName = 'names/bndTicker.json',
						target1 = self.get_bond_D1,
						target2 = self.get_bond_D1_drudgery,
						sessionNum = sessionNum)

	def get_fund_D1_mongod(self, db, start, end, sessionNum=30):
		"""
		Controller of get fund D1 method.
		"""
		self.__overlord(db = db,
						start = start,
						end = end,
						dName = 'names/fudTicker.json',
						target1 = self.get_fund_D1,
						target2 = self.get_fund_D1_drudgery,
						sessionNum = sessionNum)

	def get_option_D1_mongod(self, db, start, end, sessionNum=30):
		"""
		Controller of get option D1 method.
		"""
		self.__overlord(db = db,
						start = start,
						end = end,
						dName = 'names/optTicker.json',
						target1 = self.get_option_D1,
						target2 = self.get_option_D1_drudgery,
						sessionNum = sessionNum)

	def get_equity_D1_mongod_(self, db, start, end, sessionNum=30):
		"""
		Outer controller of get equity D1 method. 
		Generates a list of all tickers, creates threads and distribute 
		tasks to individual get_equity_D1_drudgery() functions.

		parameters
		----------
		* db: pymongo.db object; the database which collections of bars will
		  go into. Note that this database will be transferred to every 
		  drudgery functions created by controller.
		* start, end: string; Date mark formatted in 'YYYYMMDD'. Specifies the 
		  start/end point of collections of bars.
		* sessionNum: integer; the number of threads that will be deploied.
		  Concretely, the list of all tickers will be sub-divided into chunks,
		  where chunkSize = len(allTickers)/sessionNum.

		"""
		# initialize task list.
		dName = 'names/equTicker.json'
		if os.path.isfile(dName):
			# if directory exists, read from it.
			jsonFile = open(dName,'r')
			allTickers = json.loads(jsonFile.read())
			jsonFile.close()
		else:
			data = self.get_equity_D1()
			allTickers = list(data.body['ticker'])
			
		chunkSize = len(allTickers)/sessionNum
		taskLists = [allTickers[k:k+chunkSize] for k in range(
						0, len(allTickers), chunkSize)]
		k = 0
		for tasks in taskLists:
			thrd = Thread(target = self.get_equity_D1_drudgery,
						  args = (k, db, start, end, tasks))
			thrd.start()
			k += 1
		return 1


	#----------------------------------------------------------------------#
	# to be deprecated

	def get_equity_D1_drudgery_(self, id, db, 
							    start, end, tasks=[]):
		"""
		Drudgery function of getting equity_D1 bars.
		This method loops over a list of tasks(tickers) and get D1 bar
		for all these tickers. A new feature 'date' will be automatically
		added into every json-like documents, and specifies the datetime.
		datetime() formatted date mark. With the default setting of MongoDB
		in this module, this feature should be the unique index for all 
		collections.

		By programatically assigning creating and assigning tasks to drudgery
		functions, multi-threading download of data can be achieved.

		parameters
		----------
		* id: integer; the ID of Drudgery session.
		* db: pymongo.db object; the database which collections of bars will
		  go into.
		* start, end: string; Date mark formatted in 'YYYYMMDD'. Specifies the 
		  start/end point of collections of bars.
		* tasks: list of strings; the tickers that this drudgery function
		  loops over.

		"""
		if len(tasks) == 0:
			return 0
		# str to datetime inline functions.
		todt = lambda str_dt: datetime.strptime(str_dt,'%Y-%m-%d')
		update_dt = lambda d: d.update({'date':todt(d['tradeDate'])})
		# loop over all tickers in task list.
		k, n = 1, len(tasks)
		for ticker in tasks:
			try:
				data = self.get_equity_D1(start = start,
										  end = end, 
										  ticker = ticker,
										  output = 'list')
				assert len(data) >= 1
				map(update_dt, data) # add datetime feature to docs.
				coll = db[ticker]
				coll.insert_many(data)
				print '[API|Session{}]: '.format(id) + \
					  'Finished {} in {}.'.format(k, n)
				k += 1
			except ConnectionError:
			# If choke connection, standby for 1sec an invoke again.
				time.sleep(1)
				self.get_equity_D1_drudgery(
					 id, db, start, end, tasks)
			except AssertionError:
				msg = '[API|Session{}]: '.format(id) + \
					  'Empty dataset in the response.'
				print msg
				pass
			except Exception, e:
				msg = '[API|Session{}]: '.format(id) + \
					  'Exception encountered when ' + \
					  'requesting data; ' + str(e)
				print msg
				pass

	def get_equity_D1_mongod_(self, db, start, end, sessionNum=30):
		"""
		Outer controller of get equity D1 method. 
		Generates a list of all tickers, creates threads and distribute 
		tasks to individual get_equity_D1_drudgery() functions.

		parameters
		----------
		* db: pymongo.db object; the database which collections of bars will
		  go into. Note that this database will be transferred to every 
		  drudgery functions created by controller.
		* start, end: string; Date mark formatted in 'YYYYMMDD'. Specifies the 
		  start/end point of collections of bars.
		* sessionNum: integer; the number of threads that will be deploied.
		  Concretely, the list of all tickers will be sub-divided into chunks,
		  where chunkSize = len(allTickers)/sessionNum.

		"""
		# initialize task list.
		dName = 'names/equTicker.json'
		if os.path.isfile(dName):
			# if directory exists, read from it.
			jsonFile = open(dName,'r')
			allTickers = json.loads(jsonFile.read())
			jsonFile.close()
		else:
			data = self.get_equity_D1()
			allTickers = list(data.body['ticker'])
			
		chunkSize = len(allTickers)/sessionNum
		taskLists = [allTickers[k:k+chunkSize] for k in range(
						0, len(allTickers), chunkSize)]
		k = 0
		for tasks in taskLists:
			thrd = Thread(target = self.get_equity_D1_drudgery,
						  args = (k, db, start, end, tasks))
			thrd.start()
			k += 1
		return 1

	#----------------------------------------------------------------------#

	def get_equity_M1_drudgery(self, id, db, 
							   start, end, tasks=[]):
		"""
		Drudgery function of getting equity_D1 bars.
		This method loops over a list of tasks(tickers) and get D1 bar
		for all these tickers. A new feature 'dateTime', combined by Y-m-d 
		formatted date part and H:M time part, will be automatically added into 
		every json-like documents. It would be a datetime.datetime() timestamp 
		object. In this module, this feature should be the unique index for all 
		collections.

		By programatically assigning creating and assigning tasks to drudgery
		functions, multi-threading download of data can be achieved.

		parameters
		----------
		* id: integer; the ID of Drudgery session.
		* db: pymongo.db object; the database which collections of bars will
		  go into.
		* start, end: string; Date mark formatted in 'YYYYMMDD'. Specifies the 
		  start/end point of collections of bars. Note that to ensure the 
		  success of every requests, the range amid start and end had better be 
		  no more than one month. 
		* tasks: list of strings; the tickers that this drudgery function
		  loops over.

		"""
		if len(tasks) == 0:
			return 0

		# str to datetime inline functions.
		todt = lambda str_d, str_t: datetime.strptime(
				str_d + ' ' + str_t,'%Y-%m-%d %H:%M')
		update_dt = lambda d: d.update(
				{'dateTime':todt(d['dataDate'], d['barTime'])})

		k, n = 1, len(tasks)
		for secID in tasks:
			try:
				data = self.get_equity_M1(start = start,
										  end = end, 
										  secID = secID,
										  output = 'list')
				map(update_dt, data) # add datetime feature to docs.
				coll = db[secID]
				coll.insert_many(data)
				print '[API|Session{}]: '.format(id) + \
					  'Finished {} in {}.'.format(k, n)
				k += 1
			except ConnectionError:
			# If choke connection, standby for 1sec an invoke again.
				time.sleep(1)
				self.get_equity_D1_drudgery(
					 id, db, start, end, tasks)
			except AssertionError:
				msg = '[API|Session{}]: '.format(id) + \
					  'Empty dataset in the response.'
				print msg
				pass
			except Exception, e:
				msg = '[API|Session{}]: '.format(id) + \
					  'Exception encountered when ' + \
					  'requesting data; ' + str(e)
				print msg
				pass

	def get_equity_M1_interMonth(self, db, id,
							     startYr=datetime.now().year-2, 
							     endYr=datetime.now().year, 
							     tasks=[]):
		"""
		Mid-level wrapper of get equity M1 method. 
		Get 1-minute bar between specified start year and ending year for
		more than one tickers in tasks list. 

		parameters
		----------
		* db: pymongo.db object; the database which collections of bars will
		  go into. Note that this database will be transferred to every 
		  drudgery functions created by controller.
		* id: integer; the ID of wrapper session.
		* startYr, endYr: integer; the start and ending year amid which the
		  1-minute bar data is gotten one month by another employing 
		  get_equity_M1_drudgery() function. 
		  Default values are this year and two years before now. 
		  the complete time range will be sub-divided into months. And threads
		  are deployed for each of these months.

		  		- example
		  		  -------
		  		  Suppose .now() is Auguest 15th 2015. (20150815)
		  		  startYr, endYr = 2014, 2015.
		  		  then two list of strings will be generated:
		  		  ymdStringStart = ['20140102','20140202', ... '20150802']
		  		  ymdStringEnd = ['20140101','20140201', ... '20150801']
		  		  the sub-timeRanges passed to drudgeries will be:
		  		  (start, end): (20140102, 20140201), (20140202, 20140301),
		  		  ..., (20150702, 20150801).
		  		  So the actual time range is 20140102 - 20150801.

		* sessionNum: integer; the number of threads that will be deploied.
		  Concretely, the list of all tickers will be sub-divided into chunks,
		  where chunkSize = len(allTickers)/sessionNum.

		"""
		# Construct yyyymmdd strings.(as ymdStrings list)
		now = datetime.now()
		years = [str(y) for y in range(startYr, endYr+1)]
		monthDates = [(2-len(str(k)))*'0'+str(k)+'02' for k in range(1,13)]
		ymdStringStart = [y+md for y in years for md in monthDates if (
					  	  datetime.strptime(y+md,'%Y%m%d')<=now)]
		monthDates = [(2-len(str(k)))*'0'+str(k)+'01' for k in range(1,13)]
		ymdStringEnd = [y+md for y in years for md in monthDates if (
					  	datetime.strptime(y+md,'%Y%m%d')<=now)]
		k = 0
		for t in range(len(ymdStringEnd)-1):
			start = ymdStringStart[t]
			end = ymdStringEnd[t+1]
			subID = str(id) + '_' + str(k)
			thrd = Thread(target = self.get_equity_M1_drudgery,
						  args = (subID, db, start, end, tasks))
			thrd.start()
			k += 1


	def get_equity_M1_all(self, db, 
							 startYr=datetime.now().year-2, 
							 endYr=datetime.now().year, 
							 splitNum=10):
		"""


		"""
		"""
		# initialize task list.
		data = self.get_equity_D1()
		allTickers = list(data.body['ticker'])
		exchangeCDs = list(data.body['exchangeCD'])
		allSecIds = [allTickers[k]+'.'+exchangeCDs[k] for k in range(
						len(allTickers))]
		chunkSize = len(allSecIds)/splitNum
		taskLists = [allSecIds[k:k+chunkSize] for k in range(
						0, len(allSecIds), chunkSize)]

		# Construct yyyymmdd strings.(as ymdStrings list)
		now = datetime.now()
		years = [str(y) for y in range(startYr, endYr+1)]
		monthDates = [(2-len(str(k)))*'0'+str(k)+'01' for k in range(1,13)]
		ymdStrings = [y+md for y in years for md in monthDates if (
					  datetime.strptime(y+md,'%Y%m%d')<=now)]

		print taskLists[0]
		print ymdStrings
		
		k = 0
		for t in range(len(ymdStrings)-1):
			start = ymdStrings[t]
			end = ymdStrings[t+1]
			thrd = Thread(target = self.get_equity_M1_drudgery,
							  args = (k, db, start, end, taskLists[0]))
			thrd.start()
			k += 1
		return 1
		"""
		pass
		