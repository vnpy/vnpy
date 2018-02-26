# encoding: UTF-8


import os,sys
from datetime import datetime
import json
import uuid
from vnpy.trader.app.ctaStrategy.ctaBase import *
from vnpy.trader.vtConstant import *

DEBUGCTALOG = True

"""
    网格交易，用于套利单
    作者：李来佳，QQ/Wechat:28888502
ChangeLog:
    160713,修改closeGrid，增加volume字段，关闭网格时，根据价格和交易量进行双重匹配.
    160715,增加保存json和重启后加载本地json文件
    170504，增加锁单网格
    170707，增加重用选项
    170719, 增加网格类型
    171208，增加openPrices/snapshot    
"""

# 网格类型
SPREAD_GRID = 'spread'      # 价差回归网格
PERIOD_GRID = 'period'      # 周期网格
TREND_GRID = 'trend'        # 趋势网格
LOCK_GRID   = 'lock'        # 对锁网格

class CtaGrid(object):
    """网格类
    它是网格交易的最小单元
    包括交易方向，开仓价格，平仓价格，止损价格，开仓状态，平仓状态

    """

    def __init__(self, direction, openprice, closeprice, stopprice=EMPTY_FLOAT, volume=1, type=EMPTY_STRING):

        self.id = str(uuid.uuid1())
        self.direction = direction      # 交易方向（LONG：多，正套；SHORT：空，反套）
        self.openPrice = openprice      # 开仓价格
        self.closePrice = closeprice    # 平仓价格
        self.stopPrice = stopprice      # 止损价格

        self.volume = volume            # 开仓数量
        self.tradedVolume = EMPTY_INT   # 成交数量 开仓时，为开仓数量，平仓时，为平仓数量

        self.orderStatus = False        # 挂单状态: True,已挂单，False，未挂单
        self.orderRef = EMPTY_STRING    # OrderId
        self.openStatus = False         # 开仓状态
        self.closeStatus = False        # 平仓状态

        self.openDatetime = None
        self.orderDatetime = None       # 委托时间

        self.lockGrids = []             # 锁单的网格，[openPrice,openPrice]
        self.reuse = False              # 是否重用（平仓后是否删除）
        self.type = type                # 网格类型标签
        self.openPrices = {}            # 套利使用，开仓价格，symbol:price
        self.snapshot = {}              # 切片数据，如记录开仓点时的某些状态数据

    def toJson(self):
        """输出JSON"""

        j = {}
        j['id'] = self.id
        j['direction'] = self.direction
        j['openPrice'] = self.openPrice      # 开仓价格
        j['closePrice'] = self.closePrice    # 平仓价格
        j['stopPrice'] = self.stopPrice      # 止损价格

        j['volume'] = self.volume            # 开仓数量

        j['tradedVolume'] = self.tradedVolume # 成交数量

        j['orderStatus'] = self.orderStatus        # 挂单状态: True,已挂单，False，未挂单
        j['orderRef'] = self.orderRef           # OrderId
        j['openStatus'] = self.openStatus         # 开仓状态
        j['closeStatus'] = self.closeStatus        # 平仓状态
        j['lockGrids'] = self.lockGrids         # 对锁的网格
        j['reuse'] = self.reuse                 # 是否重用
        j['type'] = self.type                # 类型

        j['openPrices'] = self.openPrices       # 套利中，两腿的开仓价格
        j['snapshot'] = self.snapshot           # 切片数据

        if type(self.openDatetime) == type(None):
            j['openDatetime'] = EMPTY_STRING
        else:
            try:
                j['openDatetime'] = self.openDatetime.strftime('%Y-%m-%d %H:%M:%S')
            except Exception:
                j['openDatetime'] = EMPTY_STRING

        return j

    def toStr(self):
        """输入字符串"""

        str = u'o:{0}/{1};c:{2}/{3},r:{4}/opentime:{5}/ordertime:{6}'\
            .format(self.openPrice, self.openStatus, self.closePrice,
                    self.closeStatus, self.orderRef, self.openDatetime, self.orderDatetime)
        return str
    def __eq__(self,other):
        return self.id == other.id

class CtaGridTrade(object):
    """网格交易类
    包括两个方向的网格队列，
    v1, 基本版
    v2，增加更新最小价格跳动，增加动态上下网格间距
    v3, 增加持久化到Mongo数据库
    """

    def __init__(self, strategy, maxlots=5, height=2, win=2, vol=1, minDiff = 1):
        """初始化
        maxlots,最大网格数
        height，网格高度（绝对值，包含minDiff）
        win，盈利数（包含minDiff）
        vol，网格开仓数
        minDiff, 最小价格跳动
        """
        self.minDiff = minDiff
        self.strategy = strategy
        self.jsonName = self.strategy.name  #策略名称
        self.useMongoDb = True

        self.maxLots = maxlots      # 缺省网格数量
        self.gridHeight = height    # 最小网格高度
        self.gridWin = win          # 最小止盈高度

        self.volume = vol           # 每次网格开仓数量
        self.volumeList = [1, 1, 1, 1, 1, 1, 1, 1, 1, 1]    # 梯级开仓数量比例

        self.upGrids = []           # 上网格列表，专门做空
        self.dnGrids = []           # 下网格列表，专门做多

        self.avg_up_open_price = EMPTY_FLOAT        # 上网格开仓均价
        self.avg_dn_open_price = EMPTY_FLOAT        # 下网格开仓均价

        self.max_up_open_price = EMPTY_FLOAT  # 上网格开仓均价
        self.min_dn_open_price = EMPTY_FLOAT  # 下网格开仓均价

    def getVolumeRate(self, gridIndex=EMPTY_INT):
        """获取网格索引对应的开仓数量比例"""
        if gridIndex >= len(self.volumeList) or gridIndex < 0:
            return 1
        rate = self.volumeList[gridIndex]

        if rate == 0:
            return 1
        else:
            return rate

    def initGrid(self, upline=EMPTY_FLOAT, dnline=EMPTY_FLOAT, max_lots=EMPTY_INT):
        """初始化网格队列
        upline，上支撑线
        dnline，下阻力线
        """
        if max_lots > EMPTY_INT:
            lots = max_lots
        else:
            lots = self.maxLots

        self.writeCtaLog(u'初始化网格队列，upline:{0},dnline:{1}'.format(upline, dnline))
        # 初始化上网格列表
        if len(self.upGrids) == 0:
            self.upGrids = self.load(direction= DIRECTION_SHORT)
            if len(self.upGrids) > 0:
                self.writeCtaLog(u'上网格从文件加载完成')
            else:
                # 做空，开仓价为上阻力线+网格高度*i，平仓价为开仓价-止盈高度，开仓数量为缺省
                for i in range(0, lots, 1):
                    grid = CtaGrid(direction=DIRECTION_SHORT,
                                   openprice=upline+self.gridHeight*i,
                                   closeprice=upline+self.gridHeight*i-self.gridWin,
                                   volume=self.volume*self.getVolumeRate(i))
                    self.upGrids.append(grid)

                self.writeCtaLog(u'上网格{0}~{1}初始化完成'.format(upline,upline+self.gridHeight*self.maxLots))
                self.save(direction=DIRECTION_SHORT)

        # 初始化下网格列表
        if len(self.dnGrids) == 0:
            self.dnGrids = self.load(direction= DIRECTION_LONG)
            if len(self.dnGrids) > 0:
                self.writeCtaLog(u'下网格从文件加载完成')
            else:
                for i in range(0, lots, 1):
                    # 做多，开仓价为下阻力线-网格高度*i，平仓价为开仓价+止盈高度，开仓数量为缺省
                    grid = CtaGrid(direction=DIRECTION_LONG,
                                   openprice=dnline - self.gridHeight * i,
                                   closeprice=dnline - self.gridHeight * i + self.gridWin,
                                   volume=self.volume*self.getVolumeRate(i))
                    self.dnGrids.append(grid)

                self.writeCtaLog(u'下网格{0}~{1}初始化完成'.format(dnline,dnline-self.gridHeight*self.maxLots))
                self.save(direction=DIRECTION_LONG)

    def writeCtaLog(self, log):
        self.strategy.writeCtaLog(log)

    def toStr(self,direction):
        """显示网格"""

        pendingCloseList = u''      # 平仓清单
        pendingOpenList = u''       # 开仓清单
        deactiveList = u''          # 待激活清单

        if direction == DIRECTION_LONG:
            for grid in self.dnGrids:
                t = EMPTY_STRING
                if grid.type == LOCK_GRID:
                    t = u'L:'
                elif grid.type == TREND_GRID:
                    t = u'T:'
                elif grid.type == PERIOD_GRID:
                    t = u'P:'
                # 待平仓
                if grid.openStatus :
                    if grid.tradedVolume == EMPTY_INT:
                        pendingCloseList = pendingCloseList + u'{}[{}->{},v:{}];'\
                            .format(t,grid.openPrice, grid.closePrice, grid.volume)
                    else:
                        pendingCloseList = pendingCloseList + u'[{}{}->{},v:{}/{}];'\
                            .format(t, grid.openPrice, grid.closePrice, grid.volume, grid.tradedVolume)

                # 待开仓成交
                elif not grid.openStatus and grid.orderStatus:
                    if grid.tradedVolume == EMPTY_INT:
                        pendingOpenList = pendingOpenList + u'[{}{},v:{}];'.format(t, grid.openPrice, grid.volume)
                    else:
                        pendingOpenList = pendingOpenList + u'[{}{},v:{}/{}];'\
                            .format(t, grid.openPrice, grid.volume, grid.tradedVolume)

                # 等待挂单
                else:
                    deactiveList = deactiveList + u'[{}{}];'.format(t,grid.openPrice)

            return u'多:待平:{0};开:{1};待:{2}'.format(pendingCloseList,pendingOpenList,deactiveList)

        if direction == DIRECTION_SHORT:
            for grid in self.upGrids:
                t = EMPTY_STRING
                if grid.type == LOCK_GRID:
                    t = u'L:'
                elif grid.type == TREND_GRID:
                    t = u'T:'
                elif grid.type == PERIOD_GRID:
                    t = u'P:'
                # 待平仓
                if grid.openStatus:
                    if grid.tradedVolume == EMPTY_INT:
                        pendingCloseList = pendingCloseList + u'[{}{}->{},v:{}];'\
                            .format(t,grid.openPrice, grid.closePrice, grid.volume)
                    else:
                        pendingCloseList = pendingCloseList + u'[{}{}->{},v:{}/{}];'\
                            .format(t,grid.openPrice, grid.closePrice, grid.volume, grid.tradedVolume)

                # 待开仓成交
                elif not grid.openStatus and grid.orderStatus:
                    if grid.tradedVolume == EMPTY_INT:
                        pendingOpenList = pendingOpenList + u'[{}{},v:{}];'.format(t, grid.openPrice, grid.volume)
                    else:
                        pendingOpenList = pendingOpenList + u'[{}{},v:{}/{}];'\
                            .format(t, grid.openPrice, grid.volume, grid.tradedVolume)

                # 等待挂单
                else:
                    deactiveList = deactiveList + u'[{}{}];'.format(t, grid.openPrice)

            return u'空:待平:{0};开:{1};待:{2}'.format(pendingCloseList,pendingOpenList,deactiveList)

    def getGridsWithType(self, direction, type=EMPTY_STRING):
        """获取符合类型的网格
        direction:做多、做空方向: 做多方向时，从dnGrids中获取;  做空方向时，从upGrids中获取
        type：网格类型，
        """
        # 状态一致，价格大于最低价格
        if direction == DIRECTION_LONG:
            grids = [x for x in self.dnGrids
                     if x.type == type]
            return grids

        # 状态一致，开仓价格小于最高价格
        if direction == DIRECTION_SHORT:
            grids = [x for x in self.upGrids
                     if x.type == type]
            return grids

    def getGrids(self, direction, ordered=False, opened=False, closed=False, begin=EMPTY_FLOAT, end=EMPTY_FLOAT, type=EMPTY_STRING):
        """获取未挂单的网格
        direction:做多、做空方向: 做多方向时，从dnGrids中获取;  做空方向时，从upGrids中获取
        ordered:是否已提交至服务器
        opened：是否已开仓
        closed：是否已平仓
        begin：开始价格,
        end：结束价格，
        """

        # 状态一致，价格大于最低价格
        if direction == DIRECTION_LONG:
            if begin == EMPTY_FLOAT: begin = sys.maxsize
            if end == EMPTY_FLOAT: end = 0-sys.maxsize
            grids = [x for x in self.dnGrids
                     if x.orderStatus == ordered
                     and x.openStatus == opened
                     and x.closeStatus == closed
                     and x.openPrice <= begin
                     and x.openPrice >= end
                     and x.type == type]

            return grids

        # 状态一致，开仓价格小于最高价格
        if direction == DIRECTION_SHORT:
            if begin == EMPTY_FLOAT: begin = 0-sys.maxsize
            if end == EMPTY_FLOAT: end = sys.maxsize
            grids = [x for x in self.upGrids
                     if x.orderStatus == ordered
                     and x.openStatus == opened
                     and x.closeStatus == closed
                     and x.openPrice >= begin
                     and x.openPrice <= end
                     and x.type == type]
            return grids

    def getPosition(self,direction, type=EMPTY_STRING):
        """获取特定类型的网格持仓"""
        if direction == DIRECTION_LONG:
            long_vol = [x.volume-x.tradedVolume for x in self.dnGrids if x.openStatus and x.type == type]
            return  sum(long_vol)

        if direction == DIRECTION_SHORT:
            short_vol = [x.volume - x.tradedVolume for x in self.upGrids if x.openStatus and x.type == type]
            return sum(short_vol)

    def updateOrderRef(self, direction, openPrice, orderRef):
        """更新网格的orderId"""
        if direction == DIRECTION_LONG:
            for x in self.dnGrids:
                if x.openPrice == openPrice:
                    x.orderRef = orderRef
                    x.orderStatus = True

        if direction == DIRECTION_SHORT:
            for x in self.upGrids:
                if x.openPrice == openPrice:
                    x.orderRef = orderRef
                    x.orderStatus = True

    def cancelOrderRef(self,direction, openPrice):
        """网格撤单"""
        if direction == DIRECTION_LONG:
            for x in self.dnGrids:
                if x.openPrice == openPrice and x.orderRef != EMPTY_STRING and x.orderStatus==True and x.openStatus==False:
                    x.orderRef = EMPTY_STRING
                    x.orderStatus = False
                    self.writeCtaLog(u'下网格撤单[{0}]'.format(x.openPrice))

        if direction == DIRECTION_SHORT:
            for x in self.upGrids:
                if x.openPrice == openPrice and x.orderRef != EMPTY_STRING and x.orderStatus==True and x.openStatus==False:
                    x.orderRef = EMPTY_STRING
                    x.orderStatus = False
                    self.writeCtaLog(u'上网格撤单[{0}]'.format(x.openPrice))

    def getGridbyOpenPrice(self, direction, openPrice, orderRef = EMPTY_STRING):
        """通过开仓价和委托状态获取网格"""
        if direction == DIRECTION_LONG:
            for x in self.dnGrids:
                # 优先匹配价格
                if x.orderRef == orderRef and x.openPrice == openPrice:
                    return x

        if direction == DIRECTION_SHORT:
            for x in self.upGrids:
                # 优先匹配价格
                if x.orderRef == orderRef and x.openPrice == openPrice:
                    return x

        self.writeCtaLog(u'异常，getGridbyOpenPrice找不到网格[{0},openprice={1},orderRef={2}]'.format(direction, openPrice, orderRef))
        return None

    def getGrid(self, direction, openPrice=EMPTY_FLOAT, closePrice=EMPTY_FLOAT, orderRef=EMPTY_STRING, t=EMPTY_STRING):
        """获取网格"""
        if direction == DIRECTION_LONG:
            for x in self.dnGrids:
                # 优先匹配价格
                if t == u'OpenPrice' and x.openPrice == openPrice:
                    return x
                elif t == u'ClosePrice' and x.closePrice == closePrice:
                    return x
                elif t == u'OrderRef' and x.orderRef == orderRef:
                    return x

        if direction == DIRECTION_SHORT:
            for x in self.upGrids:
                # 优先匹配价格
                if t == u'OpenPrice' and x.openPrice == openPrice:
                    return x
                elif t == u'ClosePrice' and x.closePrice == closePrice:
                    return x
                elif t == u'OrderRef' and x.orderRef == orderRef:
                    return x

        self.writeCtaLog(u'异常，（）getGrid找不到网格[direction={0},oepnPrice={1},closePrice={2},orderRef={3},t={4}]'.format(direction, openPrice, closePrice, orderRef, t))
        return None

    def getFirstLastGrid(self, direction,type = EMPTY_STRING):
        """获取最前/后一个的网格"""
        # 做空网格：,first =开仓价最高一个,last= 最低一个
        if direction == DIRECTION_SHORT:
            short_grids = self.getGridsWithType(direction=direction, type=type)
            if short_grids is None or len(short_grids) ==0 :
                return None, None

            if len(short_grids) == 1:
                return short_grids[0],short_grids[0]

            # 价格由低至高排列
            sortedGrids = sorted(short_grids, key=lambda g:g.openPrice)
            return sortedGrids[-1], sortedGrids[0]

        # 做多网格： first =最低一个,last= 开仓价最高一个
        if direction == DIRECTION_LONG:
            long_grids = self.getGridsWithType(direction=direction, type=type)
            if long_grids is None or len(long_grids) ==0:
                return None, None

            if len(long_grids) == 1:
                return long_grids[0], long_grids[0]

            sortedGrids = sorted(long_grids, key=lambda g: g.openPrice)
            return sortedGrids[0], sortedGrids[-1]

        return None,None

    def getLastOpenedGrid(self, direction,type = EMPTY_STRING,orderby_asc=True):
        """获取最后一个开仓的网格"""
        # highest_short_price_grid = getLastOpenedGrid(DIRECTION_SHORT
        if direction == DIRECTION_SHORT:

            opened_short_grids = self.getGrids(direction=direction, opened=True,type=type)
            if opened_short_grids is None or len(opened_short_grids) ==0 :
                return None
            if len(opened_short_grids) > 1:
                sortedGrids = sorted(opened_short_grids, key=lambda g:g.openPrice)
                if orderby_asc:
                    # 取价格最高的一格
                    opened_short_grids = sortedGrids[-1:]
                else:
                    # 取价格最低的一格
                    opened_short_grids = sortedGrids[0:1]

            return opened_short_grids[0]

        if direction == DIRECTION_LONG:
            opened_long_grids = self.getGrids(direction=direction, opened=True,type=type)
            if opened_long_grids is None or len(opened_long_grids) ==0:
                return None
            if len(opened_long_grids) > 1:
                sortedGrids = sorted(opened_long_grids, key=lambda g: g.openPrice)
                if orderby_asc:
                    # 取价格最低的一格
                    opened_long_grids = sortedGrids[0:1]
                else:
                    # 取价格最高的一格
                    opened_long_grids = sortedGrids[-1:]

            return opened_long_grids[0]

    def closeGrid(self, direction, closePrice, closeVolume):
        """网格交易结束"""
        if direction == DIRECTION_LONG:
            for x in self.dnGrids:
                if x.closePrice == closePrice and x.openStatus and x.volume == closeVolume:
                    self.writeCtaLog(u'下网格交易结束[{0}->{1}]，仓位:{2},移除网格'.format(x.openPrice, x.closePrice,closeVolume))
                    self.dnGrids.remove(x)
                    return

                if x.closePrice == closePrice and x.openStatus and x.volume > closeVolume:
                    self.writeCtaLog(u'下网格交易部分结束[{0}->{1}],减少仓位:{2}'.format(x.openPrice, x.closePrice,closeVolume))
                    x.volume = x.volume - closeVolume

                if x.closePrice == closePrice and x.openStatus and x.volume < closeVolume:
                    self.writeCtaLog(u'下网格交易结束[{0}->{1}],移除网格，剩余仓位:{2}'.format(x.openPrice, x.closePrice, closeVolume-x.volume))
                    closeVolume = closeVolume - x.volume
                    self.dnGrids.remove(x)

        if direction == DIRECTION_SHORT:
            for x in self.upGrids:
                if x.closePrice == closePrice and x.openStatus and x.volume == closeVolume:
                    self.writeCtaLog(u'上网格交易结束[{0}->{1}]，仓位:{2},移除网格'.format(x.openPrice, x.closePrice,closeVolume))
                    self.upGrids.remove(x)
                    return

                if x.closePrice == closePrice and x.openStatus and x.volume > closeVolume:
                   self.writeCtaLog(u'上网格交易结束[{0}->{1}]，仓位减少:{2}'.format(x.openPrice, x.closePrice,closeVolume))
                   x.volume = x.volume - closeVolume

                if x.closePrice == closePrice and x.openStatus and x.volume < closeVolume:
                    self.writeCtaLog(u'上网格交易结束[{0}->{1}]，移除网格，剩余仓位:{2}'.format(x.openPrice, x.closePrice,closeVolume-x.volume))
                    closeVolume = closeVolume - x.volume
                    self.upGrids.remove(x)

    def removeGridById(self,direction, id):
        """移除指定id的网格"""
        if id == EMPTY_STRING or len(id) <1:
            return
        if direction == DIRECTION_LONG:
            for x in self.dnGrids[:]:
                if x.id == id:
                    self.writeCtaLog(u'清除下网格[open={0}]'.format(x.openPrice))
                    self.dnGrids.remove(x)

        if direction == DIRECTION_SHORT:
            for x in self.upGrids[:]:
                if x.id == id:
                    self.writeCtaLog(u'清除上网格[open={0}]'.format(x.openPrice))
                    self.upGrids.remove(x)

    def removeGrids(self, direction, priceline, type=EMPTY_STRING):
        """清除价格线以下的网格"""
        if direction == DIRECTION_LONG:
            for x in self.dnGrids[:]:
                if x.openPrice > priceline and not x.orderStatus and not x.openStatus and not x.closeStatus and x.type==type:
                    self.writeCtaLog(u'清除下网格[open={0}]'.format(x.openPrice))
                    self.dnGrids.remove(x)

        if direction == DIRECTION_SHORT:
            for x in self.upGrids[:]:
                if x.openPrice < priceline and not x.orderStatus and not x.openStatus and not x.closeStatus and x.type==type:
                    self.writeCtaLog(u'清除上网格[open={0}]'.format(x.openPrice))
                    self.upGrids.remove(x)

    def rebuildGrids(self, direction, upline=EMPTY_FLOAT, dnline=EMPTY_FLOAT, midline=EMPTY_FLOAT, upRate=1, dnRate = 1):
        """重新拉网
        清除未挂单的网格，
        在上轨/下轨位置重新挂单
        upRate , 上轨网格高度比率
        dnRate， 下轨网格高度比率
        """
        self.writeCtaLog(u'重新拉网:upline:{0},dnline:{1}'.format(upline, dnline))

        # 检查上下网格的高度比率，不能低于0.5
        if upRate < 0.5 or dnRate < 0.5:
            upRate = max(0.5, upRate)
            dnRate = max(0.5, dnRate)

        # 重建下网格(移除未挂单、保留开仓得网格、在最低价之下才增加网格
        if direction == DIRECTION_LONG:
            min_long_price = midline
            remove_grids = []
            opened_grids = []
            # 移除未挂单的下网格
            for x in self.dnGrids[:]:
                if not x.orderStatus and not x.openStatus and not x.closeStatus:
                    remove_grids.append(u'{}=>{}'.format(x.openPrice, x.closePrice))
                    self.dnGrids.remove(x)
                else:
                    opened_grids.append(u'{}=>{}'.format(x.openPrice, x.closePrice))
                    if x.openPrice < min_long_price:
                        min_long_price = x.openPrice

            if len(remove_grids) > 0:
                self.writeCtaLog(u'清除下网格[{}]'.format(remove_grids))
            if len(opened_grids) > 0:
                self.writeCtaLog(u'保留下网格[{}]'.format(opened_grids))

            # 需要重建的剩余网格数量
            remainLots = len(self.dnGrids)
            lots = self.maxLots - remainLots

            dnline = min(dnline, min_long_price-self.gridHeight*dnRate)
            self.writeCtaLog(u'需要重建的网格数量:{0},起点:{1}'.format(lots, dnline))

            if lots > 0:
                for i in range(0, lots, 1):
                    # 做多，开仓价为下阻力线-网格高度*i，平仓价为开仓价+止盈高度，开仓数量为缺省
                    open_price = int((dnline - self.gridHeight * i * dnRate) / self.minDiff ) * self.minDiff
                    close_price = int((open_price + self.gridWin* dnRate)/self.minDiff) * self.minDiff

                    grid = CtaGrid(direction=DIRECTION_LONG,
                                   openprice=open_price,
                                   closeprice=close_price,
                                   volume=self.volume*self.getVolumeRate(remainLots + i))

                    self.dnGrids.append(grid)
                self.writeCtaLog(u'重新拉下网格:[{0}~{1}]'.format(dnline, dnline-self.gridHeight * lots))

        # 重建上网格(移除未挂单、保留开仓得网格、在最高价之上才增加网格
        if direction == DIRECTION_SHORT:
            max_short_price = midline               # 最高开空价
            remove_grids = []                       # 移除的网格列表
            opened_grids = []                       # 已开仓的网格列表
            # 移除未挂单的上网格
            for x in self.upGrids[:]:
                if not x.orderStatus and not x.openStatus and not x.closeStatus:
                    remove_grids.append(u'{}=>{}'.format(x.openPrice, x.closePrice))
                    self.upGrids.remove(x)
                else:
                    opened_grids.append(u'{}=>{}'.format(x.openPrice, x.closePrice))

                    if x.openPrice > max_short_price:
                        max_short_price = x.openPrice

            if len(remove_grids) > 0:
                self.writeCtaLog(u'清除上网格[{}]'.format(remove_grids))
            if len(opened_grids) > 0:
                self.writeCtaLog(u'保留上网格[{}]'.format(opened_grids))

            # 需要重建的剩余网格数量
            remainLots = len(self.upGrids)
            lots = self.maxLots - remainLots
            upline = max(upline, max_short_price+self.gridHeight*upRate)
            self.writeCtaLog(u'需要重建的网格数量:{0},起点:{1}'.format(lots, upline))

            if lots > 0:
                # 做空，开仓价为上阻力线+网格高度*i，平仓价为开仓价-止盈高度，开仓数量为缺省
                for i in range(0, lots, 1):
                    open_price = int((upline + self.gridHeight * i * upRate) / self.minDiff) * self.minDiff
                    close_price = int((open_price - self.gridWin * upRate) / self.minDiff) * self.minDiff

                    grid = CtaGrid(direction=DIRECTION_SHORT,
                                   openprice=open_price,
                                   closeprice=close_price,
                                   volume=self.volume*self.getVolumeRate(remainLots + i))
                    self.upGrids.append(grid)

                self.writeCtaLog(u'重新拉上网格:[{0}~{1}]'.format(upline, upline+self.gridHeight * lots))

    def recount_avg_open_price(self):
        """计算网格的平均开仓价"""
        up_open_list = [x for x in self.upGrids if x.openStatus]

        self.max_up_open_price = 0 - sys.maxsize
        self.avg_up_open_price = 0 - sys.maxsize
        self.min_dn_open_price = sys.maxsize
        self.avg_dn_open_price = sys.maxsize

        total_price = EMPTY_FLOAT
        total_volume = EMPTY_INT
        for x in up_open_list:
            self.max_up_open_price = max(self.max_up_open_price, x.openPrice)
            total_price += x.openPrice*x.volume
            total_volume += x.volume

        if total_volume > 0:
            self.avg_up_open_price = total_price/total_volume

        total_price = EMPTY_FLOAT
        total_volume = EMPTY_INT

        dn_open_list = [x for x in self.dnGrids if x.openStatus]
        for x in dn_open_list:
            self.min_dn_open_price = min(self.min_dn_open_price,x.openPrice)
            total_price += x.openPrice*x.volume
            total_volume += x.volume

        if total_volume > 0:
            self.avg_dn_open_price = total_price/total_volume

    def count_avg_open_price(self, grid_list):
        """计算平均开仓价"""
        total_price = EMPTY_FLOAT
        total_volume = EMPTY_INT
        avg_price = EMPTY_FLOAT

        for g in grid_list:
            total_price += g.openPrice * g.volume
            total_volume += g.volume

        if total_volume > EMPTY_INT:
            avg_price = total_price / total_volume
        return avg_price

    def combineOpenedGrids(self,direction,type=EMPTY_STRING):
        """合并已开仓的网格"""
        total_open_price = EMPTY_FLOAT
        total_close_price = EMPTY_FLOAT
        total_volume = EMPTY_INT
        saved_grid = None

        if direction == DIRECTION_SHORT:
            opened_short_grids = self.getGrids(direction=direction, opened=True, ordered=False, type = type)

            if len(opened_short_grids)<=1:
                return
            self.writeCtaLog(u'{}个空网格合并为1个'.format(len(opened_short_grids)))
            saved_grid = opened_short_grids[-1]

            for g in opened_short_grids:
                total_open_price += g.openPrice * g.volume
                total_close_price += g.closePrice * g.volume
                total_volume += g.volume
                if g != saved_grid:
                    self.writeCtaLog(u'删除空网格 {}=>{},v:{}'.format(g.openPrice, g.closePrice, g.volume))
                    self.upGrids.remove(g)
                else:
                    self.writeCtaLog(u'保留空网格 {}=>{},v:{}'.format(g.openPrice, g.closePrice, g.volume))

            # 更新网格的开仓价和仓位数量
            saved_grid.openPrice = int((total_open_price / total_volume)/self.minDiff)*self.minDiff
            saved_grid.volume = total_volume
            saved_grid.closePrice = int((total_close_price / total_volume)/self.minDiff)*self.minDiff

            self.writeCtaLog(u'合并后空网格为{}=>{},v:{}'.format(saved_grid.openPrice, saved_grid.closePrice, saved_grid.volume))

        elif direction == DIRECTION_LONG:
            opened_long_grids = self.getGrids(direction=direction, opened=True, ordered=False, type=type)

            if len(opened_long_grids) <= 1:
                return
            self.writeCtaLog(u'{}个多网格合并为1个'.format(len(opened_long_grids)))
            saved_grid = opened_long_grids[-1]

            for g in opened_long_grids:
                total_open_price += g.openPrice * g.volume
                total_close_price += g.closePrice * g.volume
                total_volume += g.volume
                if g != saved_grid:
                    self.writeCtaLog(u'删除多网格 {}=>{},v:{}'.format(g.openPrice, g.closePrice, g.volume))
                    self.dnGrids.remove(g)
                else:
                    self.writeCtaLog(u'保留多网格 {}=>{},v:{}'.format(g.openPrice, g.closePrice, g.volume))

            # 更新网格的开仓价和仓位数量
            saved_grid.openPrice = int((total_open_price / total_volume) / self.minDiff) * self.minDiff
            saved_grid.volume = total_volume
            saved_grid.closePrice = int((total_close_price / total_volume) / self.minDiff) * self.minDiff

            self.writeCtaLog(
                u'合并后多网格为{}=>{},v:{}'.format(saved_grid.openPrice, saved_grid.closePrice, saved_grid.volume))

    def clearDuplicateGrids(self,direction=EMPTY_STRING,type=EMPTY_STRING):
        """去除重复开仓价的未开仓网格"""

        if direction == DIRECTION_SHORT or direction==EMPTY_STRING:
            if len(self.upGrids) < 2:
                return
            checking_grids = self.getGrids(direction=DIRECTION_SHORT, opened=False,ordered=False,type=type)

            if len(checking_grids) < 2:
                return

            open_price_list = []
            remove_grids = []

            for g in checking_grids:
                if g.openPrice in open_price_list:
                    remove_grids.append(g)
                    continue

                open_price_list.append(g.openPrice)

            for rg in remove_grids:
                try:
                    self.upGrids.remove(rg)
                except:
                    pass

        if direction == DIRECTION_LONG or direction==EMPTY_STRING:
            if len(self.dnGrids) < 2:
                return
            checking_grids = self.getGrids(direction=DIRECTION_LONG, opened=False, ordered=False, type=type)

            if len(checking_grids) < 2:
                return

            open_price_list = []
            remove_grids = []
            for g in checking_grids:
                if g.openPrice in open_price_list:
                    remove_grids.append(g)
                    continue

                open_price_list.append(g.openPrice)

            for rg in remove_grids:
                try:
                    self.dnGrids.remove(rg)
                except:
                    pass

    def save(self, direction):
        """
        保存网格至本地Json文件"
        2017/11/23 update: 保存时，空的列表也保存
        :param direction: 
        :return: 
        """""

        # 更新开仓均价
        self.recount_avg_open_price()

        # 工作目录
        currentFolder = os.path.abspath(os.path.join(os.getcwd(), u'data'))
        if os.path.isdir(currentFolder):
            # 如果工作目录下，存在data子目录，就使用data子目录
            path = currentFolder
        else:
            # 否则，使用缺省保存目录 vnpy/trader/app/ctaStrategy/data
            path = os.path.abspath(os.path.join(os.path.dirname(__file__), u'data'))

        # 保存上网格列表
        if direction == DIRECTION_SHORT:
            jsonFileName = os.path.join(path, u'{0}_upGrids.json'.format(self.jsonName))

            l = []
            for grid in self.upGrids:
                l.append(grid.toJson())

            with open(jsonFileName, 'w') as f:
                jsonL = json.dumps(l, indent=4)
                f.write(jsonL)

            #self.writeCtaLog(u'上网格保存文件{0}完成'.format(jsonFileName))

        # 保存上网格列表
        if direction == DIRECTION_LONG:
            jsonFileName = os.path.join(path, u'{0}_dnGrids.json'.format(self.jsonName))

            l = []
            for grid in self.dnGrids:
                l.append(grid.toJson())

            with open(jsonFileName, 'w') as f:
                jsonL = json.dumps(l, indent=4)
                f.write(jsonL)

            #self.writeCtaLog(u'下网格保存文件{0}完成'.format(jsonFileName))

    def load(self, direction, openStatusFilter=[]):
        """
        加载本地Json至网格
        :param direction: DIRECTION_SHORT,做空网格；DIRECTION_LONG，做多网格
        :param openStatusFilter: 缺省，不做过滤；True，只提取已开仓的数据，False，只提取未开仓的数据
        :return: 
        """

        # 工作目录
        currentFolder = os.path.abspath(os.path.join(os.getcwd(), u'data'))
        if os.path.isdir(currentFolder):
            # 如果工作目录下，存在data子目录，就使用data子目录
            path = currentFolder
        else:
            # 否则，使用缺省保存目录 vnpy/trader/app/ctaStrategy/data
            path = os.path.abspath(os.path.join(os.path.dirname(__file__), u'data'))

        if direction == DIRECTION_SHORT:
            jsonFileName = os.path.join(path, '{0}_upGrids.json'.format(self.jsonName))
            self.writeCtaLog(u'开始加载上网格文件{0}'.format(jsonFileName))
        if direction == DIRECTION_LONG:
            jsonFileName = os.path.join(path, u'{0}_dnGrids.json'.format(self.jsonName))
            self.writeCtaLog(u'开始加载上网格文件{0}'.format(jsonFileName))

        if not os.path.isfile(jsonFileName):
            self.writeCtaLog(u'网格保存文件{0}不存在'.format(jsonFileName))
            return []

        try:
            f = open(jsonFileName,'r',encoding='utf8')
        except IOError:
            self.writeCtaLog(u'读取网格出错，请检查')
            return []

        # 解析json文件
        l = json.load(f)
        grids = []

        if len(l) > 0:

            for i in l:

                closePrice = float(i['closePrice'])
                openPrice = float(i['openPrice'])
                stopPrice = float(i['stopPrice'])

                self.writeCtaLog(u'load Grid:open:{0},close:{1},stop:{2}'.format(openPrice, closePrice, stopPrice))

                grid = CtaGrid(direction=i['direction'], openprice=openPrice, closeprice=closePrice,
                                   stopprice=stopPrice, volume=i['volume'])
                grid.orderStatus = i['orderStatus']       # 挂单状态: True,已挂单，False，未挂单
                grid.orderRef = i['orderRef']           # OrderId
                grid.openStatus = i['openStatus']         # 开仓状态
                grid.closeStatus = i['closeStatus']         # 平仓状态

                strTime = i['openDatetime']
                if strTime == EMPTY_STRING or type(strTime)==type(None):
                    grid.openDatetime = None
                else:
                    grid.openDatetime = datetime.strptime(strTime, '%Y-%m-%d %H:%M:%S')

                try:
                    grid.tradedVolume = i['tradedVolume']   # 已交易的合约数量
                except KeyError:
                    grid.tradedVolume = EMPTY_INT
                try:
                    grid.lockGrids = i['lockGrids']
                except KeyError:
                    grid.lockGrids = []

                try:
                    grid.type = i['type']
                    if grid.type == False:
                        grid.type = EMPTY_STRING
                except KeyError:
                    grid.type = EMPTY_STRING

                try:
                    grid.reuse = i['reuse']
                except KeyError:
                    grid.reuse = False

                try:
                    grid.openPrices = i['openPrices']
                except KeyError:
                    grid.openPrices = {}

                try:
                    grid.snapshot = i['snapshot']
                except KeyError:
                    grid.snapshot = {}

                self.writeCtaLog(grid.toStr())

                # 增加对开仓状态的过滤，满足某些策略只提取已开仓的网格数据
                if len(openStatusFilter) > 0:
                    if grid.openStatus not in openStatusFilter:
                        continue

                grids.append(grid)

        else:
            self.writeCtaLog(u'解析网格出错，设置为空列表')

        f.close()

        # 更新开仓均价
        self.recount_avg_open_price()

        return grids






