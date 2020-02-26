# flake8: noqa

import pyqtgraph as pg
import datetime as dt
import traceback
from qtpy import QtCore
from pyqtgraph.Point import Point
import pandas as pd


# 十字光标支持
class Crosshair(QtCore.QObject):
    """
    此类给pg.PlotWidget()添加crossHair功能,PlotWidget实例需要初始化时传入
    """
    signal = QtCore.Signal(type(tuple([])))
    signalInfo = QtCore.Signal(float, float)

    def __init__(self, parent, master):
        """Constructor"""
        self.__view = parent  # PlatWidget
        self.master = master  # KLineWidget
        super(Crosshair, self).__init__()

        self.xAxis = 0
        self.yAxis = 0

        self.datas = None

        self.yAxises = [0 for i in range(3)]
        self.leftX = [0 for i in range(3)]
        self.showHLine = [False for i in range(3)]
        self.textPrices = [pg.TextItem('', anchor=(1, 1)) for i in range(3)]
        # 取得 widget上的：主图/成交量/副图指标
        self.views = [parent.centralWidget.getItem(i + 1, 0) for i in range(3)]
        self.rects = [self.views[i].sceneBoundingRect() for i in range(3)]
        self.vLines = [pg.InfiniteLine(angle=90, movable=False) for i in range(3)]
        self.hLines = [pg.InfiniteLine(angle=0, movable=False) for i in range(3)]

        # mid 在y轴动态跟随最新价显示最新价和最新时间
        self.__textDate = pg.TextItem('date', anchor=(1, 1))  # 文本：日期/时间
        self.__textInfo = pg.TextItem('lastBarInfo')  # 文本：bar信息
        self.__text_main_indicators = pg.TextItem('lastIndicatorsInfo', anchor=(1, 0))  # 文本：主图指标
        self.__text_sub_indicators = pg.TextItem('lastSubIndicatorsInfo', anchor=(1, 0))  # 文本： 副图指标
        self.__textVolume = pg.TextItem('lastBarVolume', anchor=(1, 0))  # 文本: 成交量

        self.__textDate.setZValue(2)
        self.__textInfo.setZValue(2)
        self.__text_main_indicators.setZValue(2)
        self.__text_sub_indicators.setZValue(2)
        self.__textVolume.setZValue(2)
        self.__textInfo.border = pg.mkPen(color=(230, 255, 0, 255), width=1.2)

        for i in range(3):
            self.textPrices[i].setZValue(2)
            self.vLines[i].setPos(0)
            self.hLines[i].setPos(0)
            self.vLines[i].setZValue(0)
            self.hLines[i].setZValue(0)
            self.views[i].addItem(self.vLines[i])
            self.views[i].addItem(self.hLines[i])
            self.views[i].addItem(self.textPrices[i])

        self.views[0].addItem(self.__textInfo, ignoreBounds=True)
        self.views[0].addItem(self.__text_main_indicators, ignoreBounds=True)

        # 添加成交量的提示信息到 volume view
        if self.master.display_vol:
            self.views[1].addItem(self.__textVolume, ignoreBounds=True)

        # 添加 副图指标/日期信息到 副图
        if self.master.display_sub:
            self.views[2].addItem(self.__textDate, ignoreBounds=True)
            self.views[2].addItem(self.__text_sub_indicators, ignoreBounds=True)
        else:
            # 没有启用副图，日期信息放在主图
            self.views[0].addItem(self.__textDate, ignoreBounds=True)

        self.proxy = pg.SignalProxy(self.__view.scene().sigMouseMoved, rateLimit=360, slot=self.__mouseMoved)
        # 跨线程刷新界面支持
        self.signal.connect(self.update)
        self.signalInfo.connect(self.plotInfo)

    def update(self, pos):
        """刷新界面显示"""
        try:
            xAxis, yAxis = pos
            xAxis, yAxis = (self.xAxis, self.yAxis) if xAxis is None else (xAxis, yAxis)
            self.moveTo(xAxis, yAxis)
        except Exception as ex:
            print(u'Crosshair.update() exception:{},trace:{}'.format(str(ex), traceback.format_exc()))

    def __mouseMoved(self, evt):
        """鼠标移动回调"""
        try:
            pos = evt[0]
            self.rects = [self.views[i].sceneBoundingRect() for i in range(3)]
            for i in range(3):
                self.showHLine[i] = False
                if i == 1 and not self.master.display_vol:
                    continue

                if i == 2 and not self.master.display_sub:
                    continue

                if self.rects[i].contains(pos):
                    mousePoint = self.views[i].vb.mapSceneToView(pos)
                    xAxis = mousePoint.x()
                    yAxis = mousePoint.y()
                    self.yAxises[i] = yAxis
                    self.showHLine[i] = True
                    self.moveTo(xAxis, yAxis)
        except Exception as ex:
            print(u'_mouseMove() exception:{},trace:{}'.format(str(ex), traceback.format_exc()))

    def moveTo(self, xAxis, yAxis):
        """
        移动
        :param xAxis:
        :param yAxis:
        :return:
        """
        try:
            xAxis, yAxis = (self.xAxis, self.yAxis) if xAxis is None else (int(xAxis), yAxis)
            self.rects = [self.views[i].sceneBoundingRect() for i in range(3)]
            if not xAxis or not yAxis:
                return
            self.xAxis = xAxis
            self.yAxis = yAxis
            self.vhLinesSetXY(xAxis, yAxis)
            self.plotInfo(xAxis, yAxis)
            self.master.pi_volume.update()
        except Exception as ex:
            print(u'_mouseMove() exception:{},trace:{}'.format(str(ex), traceback.format_exc()))

    def vhLinesSetXY(self, xAxis, yAxis):
        """水平和竖线位置设置"""
        for i in range(3):
            self.vLines[i].setPos(xAxis)
            if self.showHLine[i]:
                self.hLines[i].setPos(yAxis if i == 0 else self.yAxises[i])
                self.hLines[i].show()
            else:
                self.hLines[i].hide()

    def plotInfo(self, xAxis, yAxis):
        """
        被嵌入的plotWidget在需要的时候通过调用此方法显示K线信息
        """
        if self.datas is None or xAxis >= len(self.datas):
            return

        tickDatetime = None
        openPrice = 0
        closePrice = 0
        highPrice = 0
        lowPrice = 0
        preClosePrice = 0
        volume = 0
        # open_interest = 0

        try:
            # 获取K线数据
            data = self.datas[xAxis]
            lastdata = self.datas[xAxis - 1]
            tickDatetime = pd.to_datetime(data['datetime'])
            openPrice = data['open']
            closePrice = data['close']
            lowPrice = data['low']
            highPrice = data['high']
            volume = int(data['volume'])
            # open_interest = int(data['open_interest'])
            preClosePrice = lastdata['close']

        except Exception as ex:
            print(u'exception:{},trace:{}'.format(str(ex), traceback.format_exc()))
            return

        if (isinstance(tickDatetime, dt.datetime)):
            datetimeText = dt.datetime.strftime(tickDatetime, '%Y-%m-%d %H:%M:%S')
            dateText = dt.datetime.strftime(tickDatetime, '%Y-%m-%d')
            timeText = dt.datetime.strftime(tickDatetime, '%H:%M:%S')
        else:
            datetimeText = ""
            dateText = ""
            timeText = ""

        # 显示所有的主图技术指标
        html = u'<div style="text-align: right">'
        for indicator in self.master.main_indicator_data:
            val = self.master.main_indicator_data[indicator][xAxis]
            col = self.master.main_indicator_colors[indicator]
            html += u'<span style="color: %s;  font-size: 18px;">&nbsp;&nbsp;%s：%.2f</span>' % (col, indicator, val)
        html += u'</div>'
        self.__text_main_indicators.setHtml(html)

        # 显示所有的主图技术指标
        html = u'<div style="text-align: right">'
        for indicator in self.master.sub_indicator_data:
            val = self.master.sub_indicator_data[indicator][xAxis]
            col = self.master.sub_indicator_colors[indicator]
            html += u'<span style="color: %s;  font-size: 18px;">&nbsp;&nbsp;%s：%.2f</span>' % (col, indicator, val)
        html += u'</div>'
        self.__text_sub_indicators.setHtml(html)

        # 和上一个收盘价比较，决定K线信息的字符颜色
        cOpen = 'red' if openPrice > preClosePrice else 'green'
        cClose = 'red' if closePrice > preClosePrice else 'green'
        cHigh = 'red' if highPrice > preClosePrice else 'green'
        cLow = 'red' if lowPrice > preClosePrice else 'green'

        self.__textInfo.setHtml(
            u'<div style="text-align: center; background-color:#000">\
                <span style="color: white;  font-size: 16px;">日期</span><br>\
                <span style="color: yellow; font-size: 16px;">%s</span><br>\
                <span style="color: white;  font-size: 16px;">时间</span><br>\
                <span style="color: yellow; font-size: 16px;">%s</span><br>\
                <span style="color: white;  font-size: 16px;">价格</span><br>\
                <span style="color: %s;     font-size: 16px;">(开) %.3f</span><br>\
                <span style="color: %s;     font-size: 16px;">(高) %.3f</span><br>\
                <span style="color: %s;     font-size: 16px;">(低) %.3f</span><br>\
                <span style="color: %s;     font-size: 16px;">(收) %.3f</span><br>\
                <span style="color: white;  font-size: 16px;">成交量</span><br>\
                <span style="color: yellow; font-size: 16px;">(量) %d</span><br>\
            </div>' \
            % (dateText, timeText, cOpen, openPrice, cHigh, highPrice,
               cLow, lowPrice, cClose, closePrice, volume))
        self.__textDate.setHtml(
            '<div style="text-align: center">\
                <span style="color: yellow; font-size: 12px;">%s</span>\
            </div>' \
            % (datetimeText))

        self.__textVolume.setHtml(
            '<div style="text-align: right">\
                <span style="color: white; font-size: 12px;">VOL : %.3f</span>\
            </div>' \
            % (volume))
        # 坐标轴宽度
        rightAxisWidth = self.views[0].getAxis('right').width()
        bottomAxisHeight = self.views[2].getAxis('bottom').height()
        offset = QtCore.QPointF(rightAxisWidth, bottomAxisHeight)

        # 各个顶点
        t1 = [None, None, None]
        br = [None, None, None]
        t1[0] = self.views[0].vb.mapSceneToView(self.rects[0].topLeft())
        br[0] = self.views[0].vb.mapSceneToView(self.rects[0].bottomRight() - offset)

        if self.master.display_vol:
            t1[1] = self.views[1].vb.mapSceneToView(self.rects[1].topLeft())
            br[1] = self.views[1].vb.mapSceneToView(self.rects[1].bottomRight() - offset)
        if self.master.display_sub:
            t1[2] = self.views[2].vb.mapSceneToView(self.rects[2].topLeft())
            br[2] = self.views[2].vb.mapSceneToView(self.rects[2].bottomRight() - offset)

        # 显示价格
        for i in range(3):
            if self.showHLine[i] and t1[i] is not None and br[i] is not None:
                self.textPrices[i].setHtml(
                    '<div style="text-align: right">\
                         <span style="color: yellow; font-size: 18px;">\
                           %0.3f\
                         </span>\
                     </div>' \
                    % (yAxis if i == 0 else self.yAxises[i]))
                self.textPrices[i].setPos(br[i].x(), yAxis if i == 0 else self.yAxises[i])
                self.textPrices[i].show()
            else:
                self.textPrices[i].hide()

        # 设置坐标
        self.__textInfo.setPos(t1[0])
        self.__text_main_indicators.setPos(br[0].x(), t1[0].y())
        if self.master.display_sub:
            self.__text_sub_indicators.setPos(br[2].x(), t1[2].y())
        if self.master.display_vol:
            self.__textVolume.setPos(br[1].x(), t1[1].y())

        # 修改对称方式防止遮挡
        self.__textDate.anchor = Point((1, 1)) if xAxis > self.master.index else Point((0, 1))
        if br[2] is not None:
            self.__textDate.setPos(xAxis, br[2].y())
        elif br[1] is not None:
            self.__textDate.setPos(xAxis, br[1].y())
        else:
            self.__textDate.setPos(xAxis, br[0].y())
