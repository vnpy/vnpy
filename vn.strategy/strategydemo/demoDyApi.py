# encoding: UTF-8

"""
通联数据接口，Demo
"""

import sys
import time

import requests
import json
import functools
from eventEngine import *
from PyQt4 import QtCore
from pymongo import MongoClient

Default_token = '44ebc0f058981f85382595f9f15f9670c7eaf2695de30dd752e8f33e9022baa0'

########################################################################
class dyApi(object):
	"""
	行情API封装，以期货tick数据为例。
	请求web数据，通过QTimer实现每秒推送式的订阅。
	暴露函数为subscribe。
	"""

	#----------------------------------------------------------------------
	def __init__(self, eventEngine, token=Default_token):
		"""初始化"""
		# 事件引擎，分发数据。
		self.__eventEngine = eventEngine

		# url头部部分
		self.__host = 'http://api.wmcloud.com/data/v1'
		# 用户token
		self.__token = token

		# HTTP请求头，其中token是必要的
		self.__header = {
              'Connection': 'keep-alive',
              'Authorization': 'Bearer '+ token}

        # 所订阅的合约
		self.__subscribedInstuments = []

		# 计时器，用来触发计时器事件
		self.__currtimer = QtCore.QTimer()

	#----------------------------------------------------------------------
	def getFutureTick(self, instrumentListStr):
		"""请求行情"""

		# url，其中instrumentListStr是所请求的合约，为字符串
		# 可以一次请求多只，例如：instrumentListStr ＝ 'IF1508,IF1512'
		url = self.__host + '/api/market/getFutureTickRTSnapshot.json?instrumentID=%s&field=' % instrumentListStr

		# HTTP response，使用内建方法.json()返回json格式数据。
		# response.json['data']是个字典列表，须加上index得到字典。
		# 其他操作见requests库。
		response = requests.get(url, headers=self.__header)
		data = response.json()['data'][0]

		# 装填事件引擎，一般行情事件
		event = Event(type_=EVENT_DYFUTURETICK)
		event.dict_ = {'data': data}
		self.__eventEngine.put(event)

		# 特定合约行情事件
		event = Event(type_=EVENT_DYFUTURETICK_CONTRACT+data['instrumentID'])
		event.dict_ = {'data': data}
		self.__eventEngine.put(event)

	#----------------------------------------------------------------------
	def subscribeFuture(self, instrumentID):
		"""
		订阅合约
		＃ 这里使用了和vnpy中其他Api相似的订阅方法，即一次订阅一只。
		＃ 这样不同instrument通过不同event来区分。
		＃ 而单个event.dict_中就都是单个字典。
		"""
		# 销毁上一个计时器
		if self.__currtimer:
		    self.__currtimer.stop()
		    self.__currtimer.deleteLater()

		# 向订阅列表中加入合约
		if instrumentID not in self.__subscribedInstuments:
			self.__subscribedInstuments.append(instrumentID)

		# 新计时器连接各个get函数
		# QTimer.connect中似乎不能传参数(?)我这里用functools向其中传参数。
		self.__currtimer = QtCore.QTimer()
		timerCallbacks = [functools.partial(self.getFutureTick, 
						instrumentListStr=instrumentID) for instrumentID in self.__subscribedInstuments]
		[self.__currtimer.timeout.connect(f) for f in timerCallbacks]
		self.__currtimer.start(1000)

	#----------------------------------------------------------------------
	def unsubscribeFuture(self, instrumentID):
		"""
		取消订阅合约
		＃ 移除所选合约后再调用一次subscribe
		"""
		if instrumentID in self.__subscribedInstuments:
			self.__subscribedInstuments.remove(instrumentID)
		if self.__subscribedInstuments:
			self.subscribeFuture(self.__subscribedInstuments[0])


########################################################################
class Wrapper:
	"""
	小规模的二次封装，整合了订阅、注册事件、数据库等
	"""
	#----------------------------------------------------------------------
	def __init__(self):
		"""初始化"""
		self.__eventEngine = EventEngine()

		self.__dyApi = dyApi(self.__eventEngine)

		self.__mongoConnected = False
		self.__mongoClient = None
		self.__mongoTickDB = None

		self.__eventEngine.start()

		self.connectDB()
		self.registerAll()

    #----------------------------------------------------------------------
	def connectDB(self):
		"""连接数据库"""
		try:
			self.__mongoClient = MongoClient()
			self.__mongoTickDB = self.MongoClient['tickDB']
			self.__mongoConnected = True
			self.writeLog('Mongodb is on.')
		except Exception,e:
			self.writeLog('Unable to connect mongodb.')

    #----------------------------------------------------------------------
	def registerAll(self):
		"""初始化，注册事件"""
		self.__eventEngine.register(EVENT_DYFUTURETICK, self.updateMarketData)

	#----------------------------------------------------------------------
	def register(self, eventType, func):
		"""注册事件"""
		self.__eventEngine.register(eventType, func)

	#----------------------------------------------------------------------
	def subscribe(self, instrumentID):
		self.__dyApi.subscribeFuture(instrumentID)

	#----------------------------------------------------------------------
	def unsubscribe(self, instrumentID):
		self.__dyApi.unsubscribeFuture(instrumentID)

	#----------------------------------------------------------------------
	def writeLog(self, log):
	    event = Event(type_=EVENT_LOG)
	    event.dict_['log'] = log
	    self.__eventEngine.put(event)

	#----------------------------------------------------------------------
	def updateMarketData(self, event):
	    """行情更新"""
	    data = event.dict_['data']

	    if self.__mongoConnected:
	        symbol = data['instrumentID']
	        self.__mongoTickDB[symbol].insert(data)

	    # do something..


########################################################################
#----------------------------------------------------------------------
def printdata1(event):
	"""For test"""
	print '\n'
	print '##### 1'

	# json.dumps()是json包里面一个编码解码json的函数，
	# 下面这一行的作用是以展开的形式print tickdata，便于查看数据结构。

	print json.dumps(event.dict_['data'], sort_keys=True,
						   indent=4, separators=(',', ': '))
	print '\n'
	
def printdata2(event):
	"""For test"""
	print '\n'
	print '***** 2'
	print event.dict_['data']
	print '\n'

#----------------------------------------------------------------------
def test1():
	app = QtCore.QCoreApplication(sys.argv)

	engine = Wrapper()
	engine.register(EVENT_DYFUTURETICK_CONTRACT+'IF1512', printdata1)
	engine.register(EVENT_DYFUTURETICK_CONTRACT+'IF1508', printdata2)
	engine.subscribe('IF1508')
	engine.subscribe('IF1512')

	sys.exit(app.exec_())


if __name__=='__main__':
	test1()





