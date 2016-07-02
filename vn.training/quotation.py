# -*- coding: utf-8 -*-


#!/usr/bin/python

import sys
import random
from PyQt4 import QtGui, QtCore,Qt

import tushare as ts

class report_painter:
    '''绘制行情类'''
    def __init__(self,parent):

        #初始化
        self.parent = parent
        self.paint = QtGui.QPainter()
        self.paint.begin(self.parent)

        #设置抗锯齿
        #self.paint.setRenderHint(QtGui.QPainter.Antialiasing)
        #度量尺对象
        self.metrics = self.paint.fontMetrics()

        #设置字体库
        self.fonts = dict()
        self.fonts['default'] = QtGui.QFont('Serif', 9, QtGui.QFont.Light)
        self.fonts['yahei_14_bold']= QtGui.QFont('Serif',12,QtGui.QFont.Bold)
        self.fonts['yahei_14']= QtGui.QFont('Serif',12,QtGui.QFont.Light)
        self.setFont('default')

        #设置笔刷样式库
        self.pens = dict()

        #红色 1px粗  1px点 2px距 线条
        self.pens['red_1px_dashline'] =  QtGui.QPen( QtCore.Qt.red, 1, QtCore.Qt.DashLine)
        self.pens['red_1px_dashline'].setDashPattern([1,2])

        #红色 1px粗 实线条
        self.pens['red'] = QtGui.QPen( QtCore.Qt.red, 1, QtCore.Qt.SolidLine)
        #红色 3px粗 实线条
        self.pens['red_2px'] = QtGui.QPen( QtCore.Qt.red, 2, QtCore.Qt.SolidLine)
        #红色 2px粗 实线条
        self.pens['red_3px'] = QtGui.QPen( QtCore.Qt.red, 3, QtCore.Qt.SolidLine)
        #黄色 1px粗 实线条
        self.pens['yellow'] = QtGui.QPen( QtCore.Qt.yellow, 1, QtCore.Qt.SolidLine)
        #白色 1px粗 实线条
        self.pens['white']  = QtGui.QPen( QtCore.Qt.white , 1, QtCore.Qt.SolidLine)
        #灰色 1px粗 实线条
        self.pens['gray']   = QtGui.QPen( QtCore.Qt.gray, 1, QtCore.Qt.SolidLine)
        #绿色 1px粗 实线条
        self.pens['green']   = QtGui.QPen( QtCore.Qt.green, 1, QtCore.Qt.SolidLine)
        #绿色 3px粗 实线条
        self.pens['green_2px']   = QtGui.QPen( QtCore.Qt.green, 2, QtCore.Qt.SolidLine)
        #亮蓝 1px粗  1px点 2px距 线条
        self.pens['cyan_1px_dashline'] =  QtGui.QPen( QtCore.Qt.cyan, 1, QtCore.Qt.DashLine)
        self.pens['cyan_1px_dashline'].setDashPattern([3,2])
        #获得窗口的长和宽
        size      = self.parent.size()
        self.w    = size.width()
        self.h    = size.height()

        #设置grid的上下左右补丁边距
        self.grid_padding_left   = 45  #左侧补丁边距
        self.grid_padding_right  = 245 #右侧补丁边距
        self.grid_padding_top    = 25  #顶部补丁边距
        self.grid_padding_bottom = 17  #底部补丁边距

        #开始绘制
        self.start_paint()


        self.paint.end()   #结束
    '''绘制流程步骤'''
    def start_paint(self):
        self.PriceGridPaint()
        self.rightGridPaint()
        self.timelinePaint()
        self.topInfoPaint()
        self.rulerPaint()
        self.VolumeGridPaint()
        self.volumePaint()
        self.pricePaint()
        self.xyPaint()
    '''设置使用的字体'''
    def setFont(self,code='default'):
        self.paint.setFont(self.fonts[code])

    '''设置使用的笔刷'''
    def setPen(self,code='default'):
        self.paint.setPen(self.pens[code])

    '''绘制股价走势表格'''
    def PriceGridPaint(self):
        self.setPen('red')
        self.paint.setBrush(QtCore.Qt.NoBrush)

        sum_width  = self.grid_padding_left+self.grid_padding_right
        sum_height = self.grid_padding_top+self.grid_padding_bottom

        grid_height = self.h-sum_height

        #画边框
        self.paint.drawRect(self.grid_padding_left,self.grid_padding_top,
                            self.w-sum_width,self.h-sum_height)
        #成交量和走势的分界线
        self.paint.drawLine(self.grid_padding_left,grid_height*0.7+self.grid_padding_top,
                            self.w-self.grid_padding_right,grid_height*0.7+self.grid_padding_top)

        #股票昨收中间线
        self.paint.drawLine(self.grid_padding_left+1,
                            grid_height*0.35+self.grid_padding_top,
                            self.w-self.grid_padding_right
                            ,grid_height*0.35+self.grid_padding_top)

        #其他线条
        self.paint.drawLine(0,self.h-self.grid_padding_bottom,self.w-self.grid_padding_right+44,self.h-self.grid_padding_bottom)
        self.paint.drawLine(0,self.h-self.grid_padding_bottom+16,self.w,self.h-self.grid_padding_bottom+16)

        self.paint.drawLine(self.w-self.grid_padding_right,0,
                            self.w-self.grid_padding_right,self.h-self.grid_padding_bottom+16)
        self.paint.drawLine(self.w-self.grid_padding_right+44,0,
                            self.w-self.grid_padding_right+44,self.h-self.grid_padding_bottom+16)
        self.setPen('yellow')
        self.paint.drawText(self.w-self.grid_padding_right+5,self.h-self.grid_padding_bottom-4,QtCore.QString(u'成交量'))
        self.setPen('white')
        #右下角文字
        self.paint.drawText(self.w-self.grid_padding_right+12,self.h-self.grid_padding_bottom+12,QtCore.QString(u'实时'))
    '''绘制成交量走势表格'''
    def VolumeGridPaint(self):
        sum_width  = self.grid_padding_left + self.grid_padding_right
        sum_height = self.grid_padding_top  + self.grid_padding_bottom

        grid_height = self.h-sum_height
        max_volume = self.parent.stk_data['max_vol']

        px_h_radio = max_volume/(grid_height*0.3)

        self.setPen('red_1px_dashline')


        grid_num = 6
        x = grid_num
        cnt = grid_height*0.3/grid_num
        for i in range(0,grid_num):
            self.setPen('red_1px_dashline')
            #计算坐标
            y1 = self.grid_padding_top+(grid_height*0.7)+i*cnt
            x1 = self.grid_padding_left
            x2 = self.grid_padding_left+self.w-sum_width

            self.paint.drawLine(x1,y1,x2,y1) #画价位虚线

            vol_int = int(cnt*x*px_h_radio)
            vol_str = str(vol_int)
            fw = self.metrics.width(vol_str) #获得文字宽度
            fh = self.metrics.height()/2   #获得文字高度
            self.setPen('yellow')
            self.paint.drawText(x2+40-fw,y1+fh,vol_str) #写入文字
            self.setPen('white')
            self.paint.drawText(x1-2-self.metrics.width(str(x)),y1+fh,str(x))    #写入文字
            x-=1


    '''绘制左侧信息栏和盘口等内容'''
    def rightGridPaint(self):
        self.setPen('red')
        #绘制信息内容之间的分割线
        _h = 0
        _x = self.w-self.grid_padding_right+44
        self.paint.drawLine(self.w-1,0,self.w-1,self.h-self.grid_padding_bottom+16)
        self.paint.drawLine(0,0,0,self.h-self.grid_padding_bottom+16)
        self.paint.drawLine(0,_h,self.w,_h)
        _h+=23
        self.paint.drawLine(_x,_h,self.w,_h)
        _h+=24
        self.paint.drawLine(_x,_h,self.w,_h)

        _h+=93
        self.paint.drawLine(_x,_h,self.w,_h)
        _h+=20
        self.paint.drawLine(_x,_h,self.w,_h)
        _h+=93
        self.paint.drawLine(_x,_h,self.w,_h)
        _h+=123
        self.paint.drawLine(_x,_h,self.w,_h)
        _h+=23
        self.paint.drawLine(_x,_h,self.w,_h)
        #股票名称和代码
        self.setFont('yahei_14_bold')
        self.setPen('yellow')
        name_str = QtCore.QString(u'%s %s'%(self.parent.stk_info['code'],self.parent.stk_info['name']))
        self.paint.drawText(_x+35,18,name_str)
        #委比和委差
        self.setFont('yahei_14')
        zx_str = QtCore.QString(u'最新')
        self.paint.drawText(_x+3  ,156,zx_str)
        self.setPen('gray')
        wb_str = QtCore.QString(u'委比')
        wc_str = QtCore.QString(u'委差')
        xs_str = QtCore.QString(u'现手')
        self.paint.drawText(_x+3  ,39,wb_str)
        self.paint.drawText(_x+100,39,wc_str)
        self.paint.drawText(_x+100,156,xs_str)
        fh = self.metrics.height()

        left_field_list = [u'涨跌',u'涨幅',u'振幅',u'总手',u'总额',u'换手',u'分笔']
        i = 1
        for field in left_field_list:
            field_str = QtCore.QString(field)
            self.paint.drawText(_x+3,253+(i*17),field_str)
            i+=1

        right_field_list = [u'均价',u'前收',u'今开',u'最高',u'最低',u'量比',u'均量']

        i = 1
        for field in right_field_list:
            field_str = QtCore.QString(field)
            self.paint.drawText(_x+100,253+(i*17),field_str)
            i+=1

        wp_str = QtCore.QString(u'外盘')
        np_str = QtCore.QString(u'内盘')
        self.paint.drawText(_x+3,395,wp_str)
        self.paint.drawText(_x+100,395,np_str)
        #卖①②③④⑤

        i = 0
        sell_queue = [u'卖⑤',u'卖④',u'卖③',u'卖②',u'卖①']
        for sell in sell_queue:
            sell_str = QtCore.QString(sell)
            self.paint.drawText(_x+3,62+(i*18),sell_str)
            i+=1
        #买①②③④⑤
        buy_queue = [u'买①',u'买②',u'买③',u'买④',u'买⑤']
        for buy in buy_queue:
            buy_str = QtCore.QString(buy)
            self.paint.drawText(_x+3,87+(i*18),buy_str)
            i+=1

        self.setPen('red_2px')
        self.paint.drawLine(_x+1,377,_x+99,377)
        self.paint.drawLine(_x+1,46,_x+65,46)
        self.setPen('green_2px')
        self.paint.drawLine(_x+102,377,_x+199,377)
        self.paint.drawLine(_x+67,46,_x+199,46)
        self.setFont('default')

    '''绘制左右侧的价格刻度'''
    def rulerPaint(self):

        sum_width  = self.grid_padding_left+self.grid_padding_right
        sum_height = self.grid_padding_top+self.grid_padding_bottom

        grid_height = self.h-sum_height

        high = self.parent.stk_data['high']
        low  = self.parent.stk_data['low']
        lastclose = self.parent.stk_data['lastclose']

        top = high-lastclose
        bottom = lastclose-low
        if top>bottom:
            padding = top
        else:
            padding = bottom

        limit_top = lastclose+padding
        limit_low = lastclose-padding


        px_h_radio = (grid_height*0.7)/((limit_top-limit_low)*100)


        self.setPen('red_1px_dashline')

        grid_num = 16
        cnt = grid_height*0.7/grid_num

        for i in range(0,grid_num):
            self.setPen('red_1px_dashline')
            #计算坐标
            y1 = self.grid_padding_top+i*cnt
            x1 = self.grid_padding_left
            x2 = self.grid_padding_left+self.w-sum_width

            self.paint.drawLine(x1,y1,x2,y1) #画价位虚线

            price_float = (limit_top - ((i*cnt)/px_h_radio/100)) #计算价格
            price = '%4.2f'%(price_float) #格式化价格成str

            fw = self.metrics.width(price) #获得文字宽度
            fh = self.metrics.height()/2   #获得文字高度

            radio_float = (price_float/lastclose-1)*100 #计算波动百分比
            radio_str   = "%2.2f%%"%(radio_float)      #格式化百分比成str

            r_fw = self.metrics.width(radio_str)
            r_fh = self.metrics.height()/2
            #判断文字使用的颜色
            if price_float == lastclose:
                self.setPen('white')
            if price_float < lastclose:
                self.setPen('green')

            self.paint.drawText(x1-fw-2,y1+fh,price) #写入文字
            self.paint.drawText(x2+40-r_fw,y1+r_fh,radio_str) #写入文字
    '''绘制x,y准星'''
    def xyPaint(self):
        if self.parent.m_x >= self.grid_padding_left and self.parent.m_x<=self.w-self.grid_padding_right and self.parent.m_y>=self.grid_padding_top and self.parent.m_y<=self.h-self.grid_padding_bottom:
            self.setPen('gray')
            x1 = self.grid_padding_left
            x2 = self.w-self.grid_padding_right
            y1 = self.grid_padding_top
            y2 = self.h-self.grid_padding_bottom
            self.paint.drawLine(x1+1,self.parent.m_y,x2-1,self.parent.m_y)
            self.paint.drawLine(self.parent.m_x,y1+1,self.parent.m_x,y2-1)



    '''绘制时间轴刻度'''
    def timelinePaint(self):

        fw = self.metrics.width(u'00:00') #计算文字的宽度

        sum_width  = self.grid_padding_left+self.grid_padding_right
        sum_height = self.grid_padding_top+self.grid_padding_bottom

        grid_width = self.w-sum_width-2


        y1 = self.grid_padding_top
        y2 = y1+(self.h-sum_height)

        #时间轴中线
        self.setPen('red')
        x_pos = grid_width/2+self.grid_padding_left

        self.paint.drawLine(x_pos,y1,x_pos,y2)
        self.paint.drawText(x_pos-fw/2,y2+12,QtCore.QString(u'13:00'))

        #时间轴09点30分
        x_pos = self.grid_padding_left
        self.paint.drawText(x_pos,y2+12,QtCore.QString(u'09:30'))

        #时间轴10点30分
        x_pos = grid_width*0.25+self.grid_padding_left
        self.paint.drawLine(x_pos,y1,x_pos,y2)
        self.paint.drawText(x_pos-fw/2,y2+12,QtCore.QString(u'10:30'))

        #时间轴14点00分
        x_pos = grid_width*0.75+self.grid_padding_left
        self.paint.drawLine(x_pos,y1,x_pos,y2)
        self.paint.drawText(x_pos-fw/2,y2+12,QtCore.QString(u'14:00'))

        #时间轴15点00分
        x_pos = grid_width+self.grid_padding_left
        self.paint.drawText(x_pos-fw,y2+12,QtCore.QString(u'15:00'))

        #时间虚线 by 30min
        self.setPen('red_1px_dashline')
        x_pos_array = [0.125,0.375,0.625,0.875]
        for i in x_pos_array:
            x_pos = grid_width*i+self.grid_padding_left
            self.paint.drawLine(x_pos,y1,x_pos,y2)


    '''绘制表格上方的股票信息'''
    def topInfoPaint(self):
        self.setPen('yellow')
        self.paint.drawText(4+self.grid_padding_left,self.grid_padding_top-4
                            ,QtCore.QString(self.parent.stk_info['name'])) #股票名称
        self.paint.drawText(4+self.grid_padding_left+120,self.grid_padding_top-4
                            ,QtCore.QString(u'均价线：')) #均价线
        lastclose = self.parent.stk_data['lastclose']
        close     = self.parent.stk_data['close']
        mma       = self.parent.stk_data['list']['mma'][-1]

        if lastclose>close:
            self.setPen('green')
            str_1 = '%.2f -%.2f'%(close,lastclose-close)
        if lastclose==close:
            self.setPen('white')
            str_1 = '%.2f +%.2f'%(close,0.00)
        if lastclose<close:
            self.setPen('red')
            str_1 = '%.2f +%.2f'%(close,close-lastclose)

        if mma>close:
            self.setPen('green')
        if mma==close:
            self.setPen('white')
        if mma<close:
            self.setPen('red')

        self.paint.drawText(4+self.grid_padding_left+55,self.grid_padding_top-4,QtCore.QString(str_1))
        self.paint.drawText(4+self.grid_padding_left+165,self.grid_padding_top-4,QtCore.QString('%.2f'%mma)) #均价

        #涨停价
        self.setPen('red')
        self.paint.drawText(4+self.grid_padding_left+200,self.grid_padding_top-4,QtCore.QString(u'涨停价:%.2f'%(lastclose*1.1))) #均价
        #跌停价
        self.setPen('green')
        self.paint.drawText(4+self.grid_padding_left+280,self.grid_padding_top-4,QtCore.QString(u'跌停价:%.2f'%(lastclose*0.9))) #均价
    '''绘制股价走势'''
    def pricePaint(self):
        sum_width  = self.grid_padding_left+self.grid_padding_right
        sum_height = self.grid_padding_top+self.grid_padding_bottom

        grid_height = self.h-sum_height-2

        high = self.parent.stk_data['high']
        low  = self.parent.stk_data['low']
        lastclose = self.parent.stk_data['lastclose']

        top = high-lastclose
        bottom = lastclose-low
        if top>bottom:
            padding = top
        else:
            padding = bottom

        limit_top = lastclose+padding
        limit_low = lastclose-padding

        h_radio = (grid_height*0.7)/((limit_top-limit_low)*100)

        w_radio = (self.w-sum_width-2)/240.00
        w = self.grid_padding_left

        self.setPen('white')
        path = QtGui.QPainterPath()
        path.moveTo(w,(limit_top-self.parent.stk_data['open'])*100*h_radio+self.grid_padding_top)
        i  = 1
        for price in self.parent.stk_data['list']['close']:
            w = i*w_radio+self.grid_padding_left
            y = (limit_top-price)*100*h_radio+self.grid_padding_top
            path.lineTo(w,y)
            i+=1
        self.paint.drawPath(path)
        self.setPen('cyan_1px_dashline')
        self.paint.drawLine(self.grid_padding_left+1,y,w-1,y)
        self.setPen('yellow')
        path = QtGui.QPainterPath()
        w = self.grid_padding_left
        path.moveTo(w,(limit_top-self.parent.stk_data['open'])*100*h_radio+self.grid_padding_top)
        i  = 1
        for price in self.parent.stk_data['list']['mma']:
            w = i*w_radio+self.grid_padding_left
            y = (limit_top-price)*100*h_radio+self.grid_padding_top
            path.lineTo(w,y)
            i+=1
        self.paint.drawPath(path)


    '''绘制成交量'''
    def volumePaint(self):
        sum_width  = self.grid_padding_left + self.grid_padding_right
        sum_height = self.grid_padding_top  + self.grid_padding_bottom

        max_volume = self.parent.stk_data['max_vol'] #最大分钟成交量

        w_radio = (self.w-sum_width-2)/240.00
        h_radio = ((self.h-sum_height-2)*0.3)/max_volume

        y = (self.h-sum_height)+self.grid_padding_top

        self.setPen('yellow')



        for i in range(1,len(self.parent.stk_data['list']['vol'])+1):
            x = i*w_radio+self.grid_padding_left
            y2 = h_radio*self.parent.stk_data['list']['vol'][i-1]
            self.paint.drawLine(x,y-1,x,y-y2)

class Test(QtGui.QWidget):
    def __init__(self, parent=None):
        QtGui.QWidget.__init__(self, parent)
        self.setMinimumSize(640, 430) #设置窗口最小尺寸
        self.setGeometry(300, 300, 960, 650)
        self.setWindowTitle(QtCore.QString(u'超级狙击手[内部开发测试版]-行情实时走势'))
        self.setStyleSheet("QWidget { background-color: black }")
        self.setWindowIcon(QtGui.QIcon('ruby.png'))
        self.setMouseTracking(True)
        self.m_x = 0 #光标x轴位置
        self.m_y = 0 #光标y轴位置

        self.stk_info = {}

        self.stk_info['name'] = u'浙江东方'
        self.stk_info['code'] = u'600120'
        self.stk_info['market'] = 'SH'

        self.stk_data = {}
        self.stk_data['list'] = {} #股价序列
        self.stk_data['list']['time']  = [] #时间
        self.stk_data['list']['open']  = [] #开盘价
        self.stk_data['list']['high']  = [] #最高价
        self.stk_data['list']['low']   = [] #最低价
        self.stk_data['list']['close'] = [] #收盘价
        self.stk_data['list']['vol']   = [] #成交量
        self.stk_data['list']['amount']= [] #成交额
        self.stk_data['list']['mma']= []   #分时均价

        self.stk_data['list']['buy_port'] = [(0.00,0),(0.00,0),(0.00,0),(0.00,0),(0.00,0)]  #买盘前五
        self.stk_data['list']['sell_port'] = [(0.00,0),(0.00,0),(0.00,0),(0.00,0),(0.00,0)] #卖盘前五

        #读取数据
        # f = open('SH600120.txt','r')
        # data = f.readlines()
        # f.close ()

        data = ts.get_hist_data('600120') #一次性获取全部日k线数据




        #for row in data:
        #    vars = row.split(' ')
        #    self.stk_data['list']['time'].append(vars[1])
        #    self.stk_data['list']['open'].append(float(vars[2]))
        #    self.stk_data['list']['high'].append(float(vars[3]))
        #    self.stk_data['list']['low'].append(float(vars[4]))
        #    self.stk_data['list']['close'].append(float(vars[5]))
        #    self.stk_data['list']['vol'].append(int(float(vars[6])))
        #    self.stk_data['list']['amount'].append(int(float(vars[7])))
#
        #    sum_vol = sum(self.stk_data['list']['vol'])
        #    sum_amt = sum(self.stk_data['list']['amount'])
#
        #    self.stk_data['list']['mma'].append(float(sum_amt)/(sum_vol*100.00))
        self.stk_data['list'] = data.datetime
        self.stk_data['list']
        self.stk_data['list']
        self.stk_data['list']
        self.stk_data['list']
        self.stk_data['list']
        self.stk_data['list']

        self.stk_data['lastclose'] = 10.12 #上一个交易日收盘价
        self.stk_data['open'] = self.stk_data['list']['open'][0]       #开盘价
        self.stk_data['high'] = max(self.stk_data['list']['high'])     #最高价
        self.stk_data['low']  = min(self.stk_data['list']['low'])      #最低价
        self.stk_data['close']= self.stk_data['list']['close'][-1]     #收盘价
        self.stk_data['max_vol']  = max(self.stk_data['list']['vol'])  #当日最高成交量


    def mouseMoveEvent(self, event):
        self.m_x =  int(event.x())
        self.m_y =  int(event.y())
        self.repaint()
    def paintEvent(self, event):
        report_painter(self)

app = QtGui.QApplication(sys.argv)
dt = Test()
dt.show()
app.exec_()