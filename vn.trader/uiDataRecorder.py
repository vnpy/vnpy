# encoding: UTF-8

'''
1. 合约选择
Contracts_init.json中写入需要订阅的期货品种，如需要订阅pp和IF，写入
{
    "pp": "0"，
    "IF": "0"
}
2. 主力合约判断
运行程序后，点击‘合约初始化’按钮，程序会获取通联的期货数据，自动判断主力合约。并写入Contracts_init.json中。
注：通联选择的是持仓量判断主力，本程序选择的是昨日成交量判断，两者不同时会给出提示。
3. 合约订阅
4. Tick存储
'''
import json
import os
import pymongo
import tushare as ts
ts.set_token('575593eb7696aec7339224c0fac2313780d8645f68b77369dcb35f8bcb419a0b')
import time

from uiBasicWidget import QtGui, QtCore, BasicCell
from eventEngine import *

from ctaAlgo.ctaBase import *
from vtConstant import *
from vtGateway import VtSubscribeReq
########################################################################
class DataRecorder(QtGui.QFrame):
    """
    用来记录历史数据的工具（基于CTA策略），
    可单独运行，
    本工具会记录Tick数据。
    """

    # 策略的基本参数
    name = u'期货合约Tick订阅@存储'            # 策略实例名称

    tickDbName = TICK_DB_NAME
    # barDbName = MINUTE_DB_NAME

    signal = QtCore.pyqtSignal(type(Event()))

    #----------------------------------------------------------------------
    def __init__(self, mainEngine, eventEngine, parent=None):
        """Constructor"""
        super(DataRecorder, self).__init__(parent)

        self.mainEngine = mainEngine
        self.eventEngine = eventEngine
        self.ctaEngine = self.mainEngine.ctaEngine

        self.ctpConnected = False       # 是否登录CTP
        self.contractsDict = {}     # 保存订阅symbol主力合约的字典

        self.initUi()
        self.registerEvent()

        # 记录日志
        self.writeCtaLog(u'CTA引擎启动成功')

    #----------------------------------------------------------------------
    def initUi(self):
        """初始化界面"""
        self.setWindowTitle(u'CTA@ Tick订阅&存储')

        # 按钮
        ctpButton = QtGui.QPushButton(u'登录CTP')
        mongoButton = QtGui.QPushButton(u'连接数据库')
        initButton = QtGui.QPushButton(u'合约初始化 (判断主力合约)')
        startButton = QtGui.QPushButton(u'启动订阅')
        stopButton = QtGui.QPushButton(u'停止订阅')

        ctpButton.clicked.connect(self.ctpConnect)
        mongoButton.clicked.connect(self.dbConnect)
        initButton.clicked.connect(self.contractsInit)      # 初始化合约，主力合约判断
        startButton.clicked.connect(self.startAll)
        stopButton.clicked.connect(self.stopAll)

        # 放置订阅合约（由于订阅的合约较多，所以选择了两个monitor展示订阅的合约）
        self.symbolMonitor1 = SymbolMonitor()
        self.symbolMonitor2 = SymbolMonitor()

        # CTA组件的日志监控
        self.ctaLogMonitor = QtGui.QTextEdit()
        self.ctaLogMonitor.setReadOnly(True)
        self.ctaLogMonitor.setMaximumHeight(200)

        # 设置布局
        hbox1 = QtGui.QHBoxLayout()
        hbox1.addWidget(ctpButton)
        hbox1.addWidget(mongoButton)
        hbox1.addWidget(initButton)
        hbox1.addStretch()

        # hbox2 = QtGui.QHBoxLayout()
        # hbox2.addWidget(initButton)
        # hbox2.addStretch()

        hbox3 = QtGui.QHBoxLayout()
        hbox3.addWidget(startButton)
        hbox3.addWidget(stopButton)
        hbox3.addStretch()

        hbox4 = QtGui.QHBoxLayout()
        hbox4.addWidget(self.symbolMonitor1)
        hbox4.addWidget(self.symbolMonitor2)

        vbox = QtGui.QVBoxLayout()
        vbox.addLayout(hbox1)
        # vbox.addLayout(hbox2)
        vbox.addLayout(hbox3)
        vbox.addLayout(hbox4)
        vbox.addWidget(self.ctaLogMonitor)
        self.setLayout(vbox)


    #----------------------------------------------------------------------
    def dbConnect(self):
        """连接MongoDB数据库"""
        if not self.mainEngine.dbClient:
            try:
                self.mainEngine.dbConnect()
                self.writeCtaLog(u'MongoDB连接成功')
            except pymongo.errors.ConnectionFailure:
                self.writeCtaLog(u'MongoDB连接失败')

    #----------------------------------------------------------------------
    def ctpConnect(self):
        # 登录CTP
        self.mainEngine.connect('CTP')
        self.ctpConnected = True
        self.writeCtaLog(u'CTP登录成功')

    #----------------------------------------------------------------------
    def contractsInit(self):
        """获取期货合约"""

        # 载入json文件
        fileName = 'Contracts_init.json'

        try:
            f = open(fileName, 'r')
        except IOError:
            self.writeCtaLog(u'读取合约初始化信息出错，请检查')
            return

        # 解析json文件
        self.contractsDict = json.load(f)
        f.close()

        # 获取上个交易日lastDate
        todayDate = time.strftime('%Y-%m-%d',time.localtime())
        mt = ts.Master()
        Cal = mt.TradeCal(exchangeCD='XSGE',beginDate=''.join(todayDate.split('-')),endDate=''.join(todayDate.split('-')),field='')
        lastDate = Cal.at[0, 'prevTradeDate']
        lastDate = ''.join(lastDate.split('-'))

        # 获取主力合约
        st = ts.Market()
        for contract in self.contractsDict.keys():
            data = st.MktMFutd(tradeDate=lastDate,contractObject=contract,field='ticker,mainCon,turnoverVol')
            # 通联持仓主力
            ticker1 = data[data['mainCon'] == 1]['ticker'].values
            # 昨日成交量主力
            ticker2 = data.at[data['turnoverVol'].argmax(), 'ticker']

            # 默认选择成交量主力
            self.contractsDict[contract] = unicode(ticker2)

            # 当成交量主力于持仓主力不一致时，输出信息
            if ticker1 != ticker2:
                self.writeCtaLog(u'期货 %s: 请确认主力合约(默认使用成交量):\n                    %s -通联持仓主力\n                    %s -昨日成交量主力' % (contract, ticker1, ticker2))
                print u'期货 %s: 请确认主力合约(默认使用成交量):\n        %s -通联持仓主力\n        %s -昨日成交量主力' % (contract, ticker1, ticker2)
                print data

        # 写入文件
        f = json.dumps(self.contractsDict)
        file = open(fileName, 'w')
        file.write(f)
        file.close()
        self.writeCtaLog(u'合约初始化成功')

        # （由于本人订阅的合约较多，所以选择了两个monitor展示订阅的合约）
        # 另外只展示了主力合约代码，没有展示tick最新更新时间等信息，个人感觉用处不大
        contractsDict1 = {}
        contractsDict2 = {}
        total = len(self.contractsDict)
        self.writeCtaLog(u'订阅合约数量: %s' % total)
        for i, (symbol, contract) in enumerate(self.contractsDict.items()):
            if i < (total + 1) / 2:
                contractsDict1[symbol] = contract
            else:
                contractsDict2[symbol] = contract

        # 写入Monitor
        self.symbolMonitor1.contractsDict = contractsDict1
        self.symbolMonitor1.updateTable()

        self.symbolMonitor2.contractsDict = contractsDict2
        self.symbolMonitor2.updateTable()

    #----------------------------------------------------------------------
    def startAll(self):
        if self.ctpConnected is False:
            self.writeCtaLog(u'未登录CTP, 期货Tick 订阅失败')
            return
        if self.mainEngine.dbClient is None:
            self.writeCtaLog(u'未连接数据库, 期货Tick 订阅失败')
            return

        # 订阅合约
        print self.contractsDict.values()       # 打印所有订阅合约
        for contract in self.contractsDict.values():
            try:
                # print contract
                req = VtSubscribeReq()
                req.symbol = contract
                self.mainEngine.subscribe(req, 'CTP')
            except:
                self.writeCtaLog(u'期货Tick , 合约%s 订阅失败' %(contract))

        self.eventEngine.register(EVENT_TICK, self.procecssTickEvent)
        self.writeCtaLog(u'期货Tick 订阅成功')
    #----------------------------------------------------------------------
    def stopAll(self):
        # 取消订阅
        self.eventEngine.unregister(EVENT_TICK, self.procecssTickEvent)
        self.writeCtaLog(u'期货Tick 取消订阅')

    #----------------------------------------------------------------------
    def insertTick(self, tick, symbol):
        """向数据库中插入tick数据"""
        self.ctaEngine.insertData(self.tickDbName, symbol, tick)

    #----------------------------------------------------------------------
    def insertBar(self, bar, symbol):
        """向数据库中插入bar数据"""
        self.ctaEngine.insertData(self.barDbName, symbol, bar)

    #----------------------------------------------------------------------
    def procecssTickEvent(self, event):
        """处理行情推送"""
        tick = event.dict_['data']
        self.onTick(tick)
    #----------------------------------------------------------------------
    def onTick(self, tick):
        """收到行情TICK推送"""
        # 收到Tick后，首先插入到数据库里
        # print tick.symbol, 'tick.symbol'
        self.insertTick(tick, tick.symbol)

        # # 计算K线
        # tickMinute = tick.datetime.minute
        #
        # if tickMinute != self.barMinute:    # 如果分钟变了，则把旧的K线插入数据库，并生成新的K线
        #     if self.bar:
        #         self.onBar(self.bar)
        #
        #     bar = CtaBarData()              # 创建新的K线，目的在于防止之前K线对象在插入Mongo中被再次修改，导致出错
        #     bar.vtSymbol = tick.vtSymbol
        #     bar.symbol = tick.symbol
        #     bar.exchange = tick.exchange
        #
        #     bar.open = tick.lastPrice
        #     bar.high = tick.lastPrice
        #     bar.low = tick.lastPrice
        #     bar.close = tick.lastPrice
        #
        #     bar.date = tick.date
        #     bar.time = tick.time
        #     bar.datetime = tick.datetime    # K线的时间设为第一个Tick的时间
        #
        #     bar.volume = tick.volume
        #     bar.openInterest = tick.openInterest
        #
        #     self.bar = bar                  # 这种写法为了减少一层访问，加快速度
        #     self.barMinute = tickMinute     # 更新当前的分钟
        #
        # else:                               # 否则继续累加新的K线
        #     bar = self.bar                  # 写法同样为了加快速度
        #
        #     bar.high = max(bar.high, tick.lastPrice)
        #     bar.low = min(bar.low, tick.lastPrice)
        #     bar.close = tick.lastPrice
        #
        #     bar.volume = bar.volume + tick.volume   # 成交量是累加的
        #     bar.openInterest = tick.openInterest    # 持仓量直接更新

    #----------------------------------------------------------------------
    def writeCtaLog(self, content):
        """记录CTA日志"""
        # content = self.name + ':' + content
        self.ctaEngine.writeCtaLog(content)

    #----------------------------------------------------------------------
    def updateCtaLog(self, event):
        """更新CTA相关日志"""
        log = event.dict_['data']
        content = '\t'.join([log.logTime, log.logContent])
        self.ctaLogMonitor.append(content)

    #----------------------------------------------------------------------
    def registerEvent(self):
        """注册事件监听"""
        self.signal.connect(self.updateCtaLog)
        self.eventEngine.register(EVENT_CTA_LOG, self.signal.emit)


########################################################################
class SymbolMonitor(QtGui.QTableWidget):

    #----------------------------------------------------------------------
    def __init__(self, parent=None):
        """Constructor"""
        super(SymbolMonitor, self).__init__(parent)
        self.contractsDict = {}
        self.initTable()
    #----------------------------------------------------------------------
    def initTable(self):
        """初始化表格"""
        # 设置表格的列数
        self.setColumnCount(2)

        # 设置列表头
        labels = [u'品种', u'合约']
        self.setHorizontalHeaderLabels(labels)

        # 关闭左边的垂直表头
        self.verticalHeader().setVisible(False)

        # 设为不可编辑
        self.setEditTriggers(self.NoEditTriggers)

        # 设为行交替颜色
        self.setAlternatingRowColors(True)
    #----------------------------------------------------------------------
    def updateTable(self):
        for i in range(self.rowCount()):
            self.removeRow(0)

        for symbol, contract in self.contractsDict.items():
            self.insertRow(0)
            # print symbol, contract
            self.setItem(0, 0, BasicCell(symbol))
            self.setItem(0, 1, BasicCell(contract))

        # self.horizontalHeader().resizeSections(QtGui.QHeaderView.ResizeToContents)




if __name__ == '__main__':
    pass
    # dr = DataRecorder()
    # dr.contractsInit()