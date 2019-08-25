# encoding: UTF-8

'''
套利交易模块相关的GUI控制组件
'''

from vnpy.trader.vtConstant import DIRECTION_LONG, DIRECTION_SHORT
from vnpy.trader.uiBasicWidget import QtWidgets, QtGui, QtCore
from vnpy.trader.vtEvent import *
from vnpy.trader.app.ctaStrategy.ctaGridTrade import *

########################################################################
class SplitLine(QtWidgets.QFrame):
    """水平分割线"""

    #----------------------------------------------------------------------
    def __init__(self):
        """Constructor"""
        super(SplitLine, self).__init__()
        self.setFrameShape(self.HLine)
        self.setFrameShadow(self.Sunken)

class SpreadTradeManager(QtWidgets.QWidget):
    # ----------------------------------------------------------------------
    def __init__(self, ctaEngine, eventEngine, parent=None):
        super(SpreadTradeManager, self).__init__(parent)
        self.ctaEngine = ctaEngine
        self.eventEngine = eventEngine
        self.strategy_name_list = []
        self.strategy = None

        self.directionList = [DIRECTION_LONG, DIRECTION_SHORT]
        self.initUi()

    # ----------------------------------------------------------------------
    def initUi(self):
        """初始化界面"""
        self.setWindowTitle(u'套利交易')

        # 连接运行中的套利测试（策略名称[下拉菜单]，连接按钮）
        self.btnSwitchConnectStatus = QtWidgets.QPushButton(u'套利策略未连接')
        self.btnSwitchConnectStatus.clicked.connect(self.btnSwitchClick)

        Label = QtWidgets.QLabel
        grid = QtWidgets.QGridLayout()
        grid.addWidget(Label(u'状态'), 0, 0)
        grid.addWidget(self.btnSwitchConnectStatus, 0, 1)

        self.spreadStraty = QtWidgets.QComboBox()
        self.strategy_name_list = self.ctaEngine.strategyDict.keys()
        self.spreadStraty.addItems(self.strategy_name_list)

        grid.addWidget(Label(u'套利策略'), 1, 0)
        grid.addWidget(self.spreadStraty, 1, 1)


        # 网格信息+操作（新增，删除，更新）

        grid.addWidget(Label(u'方向'), 2, 0)
        self.gridDirection = QtWidgets.QComboBox()
        self.gridDirection.addItems(self.directionList)
        grid.addWidget(self.gridDirection, 2, 1)

        self.spinOpenPrice = QtWidgets.QDoubleSpinBox()
        self.spinOpenPrice.setDecimals(4)
        self.spinOpenPrice.setMinimum(-10000)    # 原来是0，为支持套利，改为-10000
        self.spinOpenPrice.setMaximum(100000)
        self.spinOpenPrice.valueChanged.connect(self.spinOpenPrice_valueChanged)

        grid.addWidget(Label(u'开仓价'), 3, 0)
        grid.addWidget(self.spinOpenPrice, 3, 1)

        self.spinClosePrice = QtWidgets.QDoubleSpinBox()
        self.spinClosePrice.setDecimals(4)
        self.spinClosePrice.setMinimum(-10000)  # 原来是0，为支持套利，改为-10000
        self.spinClosePrice.setMaximum(100000)

        grid.addWidget(Label(u'平仓价'), 4, 0)
        grid.addWidget(self.spinClosePrice, 4, 1)

        self.spinOrderVolume = QtWidgets.QSpinBox()
        self.spinOrderVolume.setMinimum(0)
        self.spinClosePrice.setDecimals(4)
        self.spinOrderVolume.setMaximum(1000)

        grid.addWidget(Label(u'委托数量'), 5, 0)
        grid.addWidget(self.spinOrderVolume, 5, 1)

        self.spinTradedVolume = QtWidgets.QSpinBox()
        self.spinTradedVolume.setMinimum(0)
        self.spinTradedVolume.setMaximum(1000)

        grid.addWidget(Label(u'成交数量'), 6, 0)
        grid.addWidget(self.spinTradedVolume, 6, 1)

        self.openStatus = QtWidgets.QCheckBox(u'')  # 开仓状态
        grid.addWidget(Label(u'开仓状态'), 7, 0)
        grid.addWidget(self.openStatus, 7, 1)

        self.orderStatus = QtWidgets.QCheckBox(u'')  # 委托状态
        grid.addWidget(Label(u'委托状态'), 8, 0)
        grid.addWidget(self.orderStatus, 8, 1)

        self.closeStatus = QtWidgets.QCheckBox(u'')  # 平仓状态
        grid.addWidget(Label(u'平仓状态'), 9, 0)
        grid.addWidget(self.closeStatus, 9, 1)

        self.reuseStatus = QtWidgets.QCheckBox(u'')  # 平仓状态
        grid.addWidget(Label(u'重用网格'), 10, 0)
        grid.addWidget(self.reuseStatus, 10, 1)

        btnAddGrid = QtWidgets.QPushButton(u'增加')
        btnAddGrid.clicked.connect(self.btnAddGridClick)
        btnUpdateGrid = QtWidgets.QPushButton(u'更新')
        btnUpdateGrid.clicked.connect(self.btnUpdateGridClick)
        btnRemoveGrid = QtWidgets.QPushButton(u'删除')
        btnRemoveGrid.clicked.connect(self.btnRemoveGridClick)
        btnRemoveAll = QtWidgets.QPushButton(u'全删除')
        btnRemoveAll.clicked.connect(self.btnRemoveAllClick)

        hbox = QtWidgets.QHBoxLayout()
        hbox.addWidget(btnAddGrid)
        hbox.addWidget(btnUpdateGrid)
        hbox.addStretch()
        hbox.addWidget(btnRemoveGrid)
        hbox.addWidget(btnRemoveAll)

        vbox = QtWidgets.QVBoxLayout()
        vbox.addLayout(grid)
        vbox.addLayout(hbox)

        # 状态信息（通过定时器，显示 上网格清单，下网格清单）

        #日志监控
        self.logMsgs = QtWidgets.QTextEdit()
        self.logMsgs.setReadOnly(True)
        self.logMsgs.setMaximumHeight(200)
        vbox.addWidget(self.logMsgs)

        self.setLayout(vbox)

    def btnSwitchClick(self):
        """策略连接按钮"""
        if self.ctaEngine is None:
            self.log(u'没有连接CTA引擎')
            return

        strategy_name = self.spreadStraty.currentText()

        if strategy_name is None or len(strategy_name) == 0:
            if len(self.strategy_name_list)==0:
                self.strategy_name_list = self.ctaEngine.strategyDict.keys()
                self.spreadStraty.addItems(self.strategy_name_list)
            return

        self.strategy = self.ctaEngine.strategyDict[strategy_name]

        if self.strategy.trading:
            self.btnSwitchConnectStatus.setText(u'连接成功、启动')
            self.log(u'连接{0}成功、启动'.format(strategy_name))

        else:
            self.btnSwitchConnectStatus.setText(u'连接成功，未启动')
            self.log(u'连接{0}成功，但策略未启动'.format(strategy_name))

        self.displayGrids()

    def btnAddGridClick(self):
        """网格新增按钮"""
        if self.ctaEngine is None:
            self.log(u'没有连接CTA引擎')
            return

        if self.strategy is None:
            self.log(u'没有连接策略')
            return

        direction = self.gridDirection.currentText()
        if direction is None or len(direction) ==0:
            self.log(u'先选择方向')
            return

        open_price = self.spinOpenPrice.value()
        close_price = self.spinClosePrice.value()
        if open_price == close_price:
            self.log(u'开仓价和平仓价不能相同')
            return

        order_volume = self.spinOrderVolume.value()
        grid = CtaGrid(direction=direction,
                openprice=open_price,
                closeprice=close_price,
                volume=order_volume)

        grid.reuse = self.reuseStatus.isChecked()

        if direction == DIRECTION_LONG:
            self.strategy.gt.dnGrids.append(grid)

        else:
            self.strategy.gt.upGrids.append(grid)

        self.strategy.gt.save(direction=direction)
        self.strategy.recheckPositions = True
        grids_info = self.strategy.gt.toStr(direction=direction)
        self.log(grids_info)

    def displayGrids(self):
        up_grids_info = self.strategy.gt.toStr(direction=DIRECTION_SHORT)
        self.log(up_grids_info)
        dn_grids_info = self.strategy.gt.toStr(direction=DIRECTION_LONG)
        self.log(dn_grids_info)

    def spinOpenPrice_valueChanged(self):
        """查询网格"""
        if self.ctaEngine is None:
            self.log(u'没有连接CTA引擎')
            return

        if self.strategy is None:
            self.log(u'没有连接策略')
            return

        direction = self.gridDirection.currentText()
        if direction is None or len(direction) == 0:
            self.log(u'先选择方向');
            return

        open_price = self.spinOpenPrice.value()
        grid = self.strategy.gt.getGrid(direction=direction, openPrice=open_price, t=u'OpenPrice')

        if grid is None:
            self.log(u'没有找到{0}方向的网格:{1}'.format(direction, open_price))
            return

        self.spinClosePrice.setValue(grid.closePrice)
        self.spinOrderVolume.setValue(grid.volume)
        self.spinTradedVolume.setValue(grid.tradedVolume)
        self.openStatus.setChecked(grid.openStatus)
        self.orderStatus.setChecked(grid.orderStatus)
        self.closeStatus.setChecked(grid.closeStatus)
        self.reuseStatus.setChecked(grid.reuse)

    def btnUpdateGridClick(self):
        """更新网格"""
        if self.ctaEngine is None:
            self.log(u'没有连接CTA引擎')
            return

        if self.strategy is None:
            self.log(u'没有连接策略')
            return

        direction = self.gridDirection.currentText()
        if direction is None or len(direction) ==0:
            self.log(u'先选择方向')
            return

        open_price = self.spinOpenPrice.value()
        grid = self.strategy.gt.getGrid(direction=direction, openPrice=open_price, t=u'OpenPrice')

        if grid is None:
            self.log(u'没有找到{0}方向的网格:{1}'.format(direction,open_price))
            return

        grid.openPrice = open_price
        grid.closePrice = self.spinClosePrice.value()
        grid.volume = self.spinOrderVolume.value()
        grid.tradedVolume = self.spinTradedVolume.value()
        grid.openStatus = self.openStatus.isChecked()
        grid.orderStatus = self.orderStatus.isChecked()
        grid.closeStatus = self.closeStatus.isChecked()
        grid.reuse = self.reuseStatus.isChecked()

        self.strategy.gt.save(direction=direction)
        self.strategy.recheckPositions = True
        self.displayGrids()

    def btnRemoveGridClick(self):
        """删除网格(指定开仓价以下的废格)"""
        if self.ctaEngine is None:
            self.log(u'没有连接CTA引擎')
            return

        if self.strategy is None:
            self.log(u'没有连接策略')
            return


        direction = self.gridDirection.currentText()
        if direction is None or len(direction) == 0:
            self.log(u'先选择方向')
            return

        open_price = self.spinOpenPrice.value()
        if (direction == DIRECTION_LONG and len(self.strategy.gt.dnGrids) < 2) or \
                (direction == DIRECTION_SHORT and len(self.strategy.gt.upGrids) < 2):
            self.log(u'{0}方向的网格只有一个，不能删除'.format(direction))
            return

        grid = self.strategy.gt.getGrid(direction=direction, openPrice=open_price, t=u'OpenPrice')
        if grid is None:
            self.log(u'没有找到{0}方向的网格:{1},删除{1}范围内的非开仓网格'.format(direction, open_price))

            self.strategy.gt.removeGrids(direction=direction, priceline=open_price)
            self.strategy.gt.save(direction=direction)
            self.log(u'成功移除{0}方向{1}以内网格'.format(direction, open_price))
            self.displayGrids()
            return

        if grid.id is not None:
            self.strategy.gt.removeGridById(direction=direction,id= grid.id)
            self.log(u'成功移除{0}方向的网格:{1}'.format(direction, open_price))
            self.strategy.gt.save(direction=direction)
            self.displayGrids()

    def btnRemoveAllClick(self):
        """删除所有网格"""
        if self.ctaEngine is None:
            self.log(u'没有连接CTA引擎')
            return

        if self.strategy is None:
            self.log(u'没有连接策略')
            return

        direction = self.gridDirection.currentText()
        if direction is None or len(direction) == 0:
            self.log(u'先选择方向')
            return

        if direction == DIRECTION_LONG:
            self.strategy.gt.dnGrids = self.strategy.gt.dnGrids [-1:]
            self.strategy.gt.save(direction=direction)
            self.log(u'成功移除{0}方向的网格,只保留最后一个'.format(direction))
        else:
            self.strategy.gt.upGrids = self.strategy.gt.dnGrids [-1:]
            self.strategy.gt.save(direction=direction)
            self.log(u'成功移除{0}方向的网格,只保留最后一个'.format(direction))

        self.displayGrids()

    def log(self, content):
        self.logMsgs.append(content)

