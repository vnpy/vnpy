# encoding: UTF-8

import os,sys
from datetime import datetime
import json
import uuid
import shutil
from collections import OrderedDict
from vnpy.trader.app.ctaStrategy.ctaBase import *
from vnpy.trader.vtConstant import *
import traceback

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
    180420, 增加CtaLegacyGridTrade(传统网格：上网格做多，下网格做空)
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

    def __init__(self, direction, openprice, closeprice, stopprice=EMPTY_FLOAT, volume=1, type=EMPTY_STRING, vtSymbol=EMPTY_STRING):

        self.id = str(uuid.uuid1())
        self.direction = direction      # 交易方向（LONG：多，正套；SHORT：空，反套）
        self.openPrice = openprice      # 开仓价格
        self.closePrice = closeprice    # 平仓价格
        self.stopPrice = stopprice      # 止损价格

        self.vtSymbol = vtSymbol   # 品种合约
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

        j = OrderedDict()
        j['id'] = self.id
        j['direction'] = self.direction
        j['openPrice'] = self.openPrice      # 开仓价格
        j['closePrice'] = self.closePrice    # 平仓价格
        j['stopPrice'] = self.stopPrice      # 止损价格

        j['vtSymbol'] = self.vtSymbol        # 品种数量
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

    def fromJson(self,j):
        """从JSON恢复"""
        try:
            self.id = j.get('id',None)
            if self.id is None:
                self.id = str(uuid.uuid1())
            self.direction = j.get('direction',EMPTY_STRING)
            self.closePrice = j.get('closePrice', EMPTY_FLOAT)
            self.openPrice =  j.get('openPrice', EMPTY_FLOAT)
            self.stopPrice =  j.get('stopPrice', EMPTY_FLOAT)
            self.orderStatus = j.get('orderStatus',False)  # 挂单状态: True,已挂单，False，未挂单
            self.orderRef = j.get('orderRef',EMPTY_STRING)  # OrderId
            self.openStatus = j.get('openStatus',False)  # 开仓状态
            self.closeStatus = j.get('closeStatus',False)  # 平仓状态

            strTime = j.get('openDatetime',None)
            if strTime == EMPTY_STRING or strTime is None:
                self.openDatetime = None
            else:
                self.openDatetime = datetime.strptime(strTime, '%Y-%m-%d %H:%M:%S')

            self.vtSymbol = j.get('vtSymbol',EMPTY_STRING)
            self.volume = j.get('volume',EMPTY_FLOAT)
            self.tradedVolume = j.get('tradedVolume',EMPTY_FLOAT)  # 已交易的合约数量
            self.lockGrids = j.get('lockGrids',[])
            self.type = j.get('type',EMPTY_STRING)
            if self.type == False:
               self.type = EMPTY_STRING
            self.reuse = j.get('reuse',False)
            self.openPrices =  j.get('openPrices',{})
            self.snapshot = j.get('snapshot',{})
        except Exception as ex:
            print('CtaGrid fromJson Exception:{} {}'.format(str(ex),traceback.format_exc()),file=sys.stderr)

    def toStr(self):
        """输入字符串"""

        str = u'o:{}/{};c:{}/{},r:{}/opentime:{}/ordertime:{}'\
            .format(self.openPrice, self.openStatus, self.closePrice,
                    self.closeStatus, self.orderRef, self.openDatetime, self.orderDatetime)
        if len(self.vtSymbol) > 0:
            return u'{} {}'.format(self.vtSymbol,str)
        else:
            return str

    def __eq__(self,other):

        return self.id == other.id

class CtaGridTrade(object):
    """网格交易类
    包括两个方向的网格队列，
    v1, 基本版
    v2，增加更新最小价格跳动，增加动态上下网格间距
    v3, 合并up/dn为一个文件
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

        self.json_file_path = os.path.join(self.get_data_folder(), u'{}_Grids.json'.format(self.jsonName))    # 网格的路径

    def changeGridHeight(self, grid_height=EMPTY_FLOAT, grid_win=EMPTY_FLOAT):
        self.gridHeight = grid_height
        self.gridWin = grid_win

    def getVolumeRate(self, gridIndex=EMPTY_INT):
        """获取网格索引对应的开仓数量比例"""
        if gridIndex >= len(self.volumeList) or gridIndex < 0:
            return 1
        rate = self.volumeList[gridIndex]

        if rate == 0:
            return 1
        else:
            return rate

    def initGrid(self, upline=EMPTY_FLOAT, dnline=EMPTY_FLOAT, max_lots=EMPTY_INT, reuse= False):
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
                self.writeCtaLog(u'上网格从文件{}加载完成'.format(self.json_file_path))
            else:
                # 做空，开仓价为上阻力线+网格高度*i，平仓价为开仓价-止盈高度，开仓数量为缺省
                for i in range(0, lots, 1):
                    grid = CtaGrid(direction=DIRECTION_SHORT,
                                   openprice=upline+self.gridHeight*i,
                                   closeprice=upline+self.gridHeight*i-self.gridWin,
                                   volume=self.volume*self.getVolumeRate(i))
                    if reuse:
                        grid.reuse = reuse
                    self.upGrids.append(grid)

                self.writeCtaLog(u'上网格{0}~{1}初始化完成'.format(upline,upline+self.gridHeight*self.maxLots))
                self.save(direction=DIRECTION_SHORT)

        # 初始化下网格列表
        if len(self.dnGrids) == 0:
            self.dnGrids = self.load(direction= DIRECTION_LONG)
            if len(self.dnGrids) > 0:
                self.writeCtaLog(u'下网格从文件{}加载完成'.format(self.json_file_path))
            else:
                for i in range(0, lots, 1):
                    # 做多，开仓价为下阻力线-网格高度*i，平仓价为开仓价+止盈高度，开仓数量为缺省
                    grid = CtaGrid(direction=DIRECTION_LONG,
                                   openprice=dnline - self.gridHeight * i,
                                   closeprice=dnline - self.gridHeight * i + self.gridWin,
                                   volume=self.volume*self.getVolumeRate(i))
                    if reuse:
                        grid.reuse = reuse
                    self.dnGrids.append(grid)

                self.writeCtaLog(u'下网格{0}~{1}初始化完成'.format(dnline,dnline-self.gridHeight*self.maxLots))
                self.save(direction=DIRECTION_LONG)

    def writeCtaLog(self, log):
        self.strategy.writeCtaLog(log)

    def toStr(self, direction):
        """显示网格"""

        pendingCloseList = u''      # 平仓清单
        pendingOpenList = u''       # 开仓清单
        deactiveList = u''          # 待激活清单
        openedVolumeDict = {}    # 开仓数量汇总

        if direction == DIRECTION_LONG:
            for grid in self.dnGrids:
                t = EMPTY_STRING
                if grid.type == LOCK_GRID:
                    t = u'L:'
                elif grid.type == TREND_GRID:
                    t = u'T:'
                elif grid.type == PERIOD_GRID:
                    t = u'P:'
                else:
                    t = grid.type
                # 待平仓
                if grid.openStatus:
                    opened_volume = 0
                    if grid.tradedVolume == EMPTY_INT:
                        pendingCloseList = pendingCloseList + u'{}[{}->{},sp:{},v:{}];'\
                            .format(t,grid.openPrice, grid.closePrice, grid.stopPrice, grid.volume)
                        opened_volume = grid.volume
                    else:
                        pendingCloseList = pendingCloseList + u'[{}{}->{},sp:{},v:{}/{}];'\
                            .format(t, grid.openPrice, grid.closePrice, grid.volume, grid.stopPrice, grid.tradedVolume)
                        opened_volume = grid.volume - grid.tradedVolume

                    if grid.type != EMPTY_STRING:
                        openedVolumeDict[grid.type] = opened_volume if grid.type not in openedVolumeDict else opened_volume + openedVolumeDict[grid.type]
                    openedVolumeDict['All'] = opened_volume if 'All' not in openedVolumeDict else opened_volume + openedVolumeDict['All']

                # 待开仓成交
                elif not grid.openStatus and grid.orderStatus:
                    if grid.tradedVolume == EMPTY_INT:
                        pendingOpenList = pendingOpenList + u'[{}{},v:{}];'.format(t, grid.openPrice, grid.volume)
                    else:
                        pendingOpenList = pendingOpenList + u'[{} {},v:{}/{}];'\
                            .format(t, grid.openPrice, grid.volume, grid.tradedVolume)

                # 等待挂单
                else:
                    deactiveList = deactiveList + u'[{}{}];'.format(t, grid.openPrice)

            return u'多:待平:[{}],{};开:{};待:{}'.format(openedVolumeDict, pendingCloseList, pendingOpenList, deactiveList)

        if direction == DIRECTION_SHORT:
            for grid in self.upGrids:
                t = EMPTY_STRING
                if grid.type == LOCK_GRID:
                    t = u'L:'
                elif grid.type == TREND_GRID:
                    t = u'T:'
                elif grid.type == PERIOD_GRID:
                    t = u'P:'
                else:
                    t = grid.type
                # 待平仓
                if grid.openStatus:
                    opened_volume = 0
                    if grid.tradedVolume == EMPTY_INT:
                        pendingCloseList = pendingCloseList + u'[{} {}->{},sp:{},v:{}];'\
                            .format(t,grid.openPrice, grid.closePrice, grid.stopPrice, grid.volume)
                        opened_volume = grid.volume
                    else:
                        pendingCloseList = pendingCloseList + u'[{} {}->{},sp:{}, v:{}/{}];'\
                            .format(t,grid.openPrice, grid.closePrice, grid.stopPrice, grid.volume, grid.tradedVolume)
                        opened_volume = grid.volume - grid.tradedVolume
                    if grid.type != EMPTY_STRING:
                        openedVolumeDict[grid.type] = opened_volume if grid.type not in openedVolumeDict else opened_volume + openedVolumeDict[grid.type]
                    openedVolumeDict['All'] = opened_volume if 'All' not in openedVolumeDict else opened_volume + openedVolumeDict['All']
                # 待开仓成交
                elif not grid.openStatus and grid.orderStatus:
                    if grid.tradedVolume == EMPTY_INT:
                        pendingOpenList = pendingOpenList + u'[{} {},v:{}];'.format(t, grid.openPrice, grid.volume)
                    else:
                        pendingOpenList = pendingOpenList + u'[{} {},v:{}/{}];'\
                            .format(t, grid.openPrice, grid.volume, grid.tradedVolume)

                # 等待挂单
                else:
                    deactiveList = deactiveList + u'[{}{}];'.format(t, grid.openPrice)

            return u'空:待平:[{}],{};开:{};待:{}'.format(openedVolumeDict, pendingCloseList,pendingOpenList,deactiveList)

    def getGridsWithTypes(self, direction, types=[]):
        """获取符合类型的网格
        direction:做多、做空方向: 做多方向时，从dnGrids中获取;  做空方向时，从upGrids中获取
        type：网格类型列表，
        """
        # 状态一致，价格大于最低价格
        if direction == DIRECTION_LONG:
            grids = [x for x in self.dnGrids
                     if x.type in types]
            return grids

        # 状态一致，开仓价格小于最高价格
        if direction == DIRECTION_SHORT:
            grids = [x for x in self.upGrids
                     if x.type in types]
            return grids

    def getOpenedGridsWithTypes(self, direction, types=[]):
        """获取符合类型的持仓网格
        direction:做多、做空方向: 做多方向时，从dnGrids中获取;  做空方向时，从upGrids中获取
        type：网格类型列表，
        """
        # 状态一致，价格大于最低价格
        if direction == DIRECTION_LONG:
            grids = [x for x in self.dnGrids
                     if x.openStatus == True and x.type in types]
            return grids

        # 状态一致，开仓价格小于最高价格
        if direction == DIRECTION_SHORT:
            grids = [x for x in self.upGrids
                     if x.openStatus == True and x.type in types]
            return grids

    def getOpenedGrids(self, direction,allow_empty_volume = False):
        """获取已开仓的网格
        direction:做多、做空方向: 做多方向时，从dnGrids中获取;  做空方向时，从upGrids中获取
        """
        # 状态一致，价格大于最低价格
        if direction == DIRECTION_LONG:
            grids = [x for x in self.dnGrids
                     if x.openStatus == True and (x.volume - x.tradedVolume > 0 or allow_empty_volume)]

            return grids

        # 状态一致，开仓价格小于最高价格
        if direction == DIRECTION_SHORT:
            grids = [x for x in self.upGrids
                     if x.openStatus == True and (x.volume - x.tradedVolume > 0 or allow_empty_volume)]
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

    def getGridById(self,direction, id):
        """寻找指定id的网格"""
        if id == EMPTY_STRING or len(id) <1:
            return
        if direction == DIRECTION_LONG:
            for x in self.dnGrids[:]:
                if x.id == id:
                    self.writeCtaLog(u'找到下网格[open={},close={},stop={},volume={}]'.format(x.openPrice,x.closePrice,x.stopPrice,x.volume))
                    return x

        if direction == DIRECTION_SHORT:
            for x in self.upGrids[:]:
                if x.id == id:
                    self.writeCtaLog(u'找到上网格[open={},close={},stop={},volume={}]'.format(x.openPrice,x.closePrice,x.stopPrice,x.volume))
                    return x

        return None

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

        self.writeCtaLog(u'异常，getGrid找不到网格[direction={0},oepnPrice={1},closePrice={2},orderRef={3},t={4}]'.format(direction, openPrice, closePrice, orderRef, t))
        return None

    def getFirstLastGrid(self, direction,type = EMPTY_STRING):
        """获取最前/后一个的网格"""
        # 做空网格：,first =开仓价最高一个,last= 最低一个
        if direction == DIRECTION_SHORT:
            short_grids = self.getGridsWithTypes(direction=direction, types=[type])
            if short_grids is None or len(short_grids) ==0 :
                return None, None

            if len(short_grids) == 1:
                return short_grids[0],short_grids[0]

            # 价格由低至高排列
            sortedGrids = sorted(short_grids, key=lambda g:g.openPrice)
            return sortedGrids[-1], sortedGrids[0]

        # 做多网格： first =最低一个,last= 开仓价最高一个
        if direction == DIRECTION_LONG:
            long_grids = self.getGridsWithTypes(direction=direction, types=[type])
            if long_grids is None or len(long_grids) ==0:
                return None, None

            if len(long_grids) == 1:
                return long_grids[0], long_grids[0]

            sortedGrids = sorted(long_grids, key=lambda g: g.openPrice)
            return sortedGrids[0], sortedGrids[-1]

        return None,None

    def getLastOpenedGrid(self, direction,type = EMPTY_STRING, orderby_asc=True):
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
                    self.writeCtaLog(u'清除下网格[open={},close={},stop={},volume={}]'.format(x.openPrice,x.closePrice,x.stopPrice,x.volume))
                    self.dnGrids.remove(x)

        if direction == DIRECTION_SHORT:
            for x in self.upGrids[:]:
                if x.id == id:
                    self.writeCtaLog(u'清除上网格[open={},close={},stop={},volume={}]'.format(x.openPrice,x.closePrice,x.stopPrice,x.volume))
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

    def moveGrids(self, direction, pricedelta, type=EMPTY_STRING):
        """按pricedelta平移所有网格"""
        if direction == DIRECTION_LONG:
            for x in self.dnGrids[:]:
                x.openPrice += pricedelta  # 开仓价格
                x.closePrice += pricedelta  # 平仓价格
                x.stopPrice += pricedelta  # 止损价格
                x.type = type  # 网格类型标签
                # self.openPrices = {}  # 套利使用，开仓价格，symbol:price

        if direction == DIRECTION_SHORT:
            for x in self.upGrids[:]:
                x.openPrice += pricedelta  # 开仓价格
                x.closePrice += pricedelta  # 平仓价格
                x.stopPrice += pricedelta  # 止损价格
                x.type = type  # 网格类型标签
                # self.openPrices = {}  # 套利使用，开仓价格，symbol:price

    def rebuildGrids(self, direction, upline=EMPTY_FLOAT, dnline=EMPTY_FLOAT, midline=EMPTY_FLOAT, upRate=1, dnRate=1, reuse=False, useVariableSteps=False):
        """重新拉网
        清除未挂单的网格，
        在上轨/下轨位置重新挂单
        upRate , 上轨网格高度比率
        dnRate， 下轨网格高度比率
        """
        self.writeCtaLog(u'重新拉网:direction:{},upline:{},dnline:{}'.format(direction, upline, dnline))

        # 检查上下网格的高度比率，不能低于0.5
        if upRate < 0.5 or dnRate < 0.5:
            upRate = max(0.5, upRate)
            dnRate = max(0.5, dnRate)

        # 计算每个网格的高度。如果使用变高的网格，则每过5格把网格搞的增加(self.gridHeight/2)
        gridSteps = [0]*self.maxLots
        for i in range(1, self.maxLots, 1):
            if useVariableSteps == False:
                gridSteps[i] = self.gridHeight * i
            else:
                j = int(i / 5)
                gridSteps[i] = gridSteps[i-1] + self.gridHeight + self.gridHeight / 2 * j

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
                    open_price = int((dnline - gridSteps[i+remainLots] * dnRate) / self.minDiff ) * self.minDiff
                    close_price = int((open_price + self.gridWin* dnRate)/self.minDiff) * self.minDiff

                    grid = CtaGrid(direction=DIRECTION_LONG,
                                   openprice=open_price,
                                   closeprice=close_price,
                                   volume=self.volume*self.getVolumeRate(remainLots + i))
                    grid.reuse = reuse
                    self.dnGrids.append(grid)
                self.writeCtaLog(u'重新拉下网格:[{0}~{1}]'.format(dnline, dnline - gridSteps[-1] * dnRate))

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
                    open_price = int((upline + gridSteps[i+remainLots] * upRate) / self.minDiff) * self.minDiff
                    close_price = int((open_price - self.gridWin * upRate) / self.minDiff) * self.minDiff

                    grid = CtaGrid(direction=DIRECTION_SHORT,
                                   openprice=open_price,
                                   closeprice=close_price,
                                   volume=self.volume*self.getVolumeRate(remainLots + i))
                    grid.reuse = reuse
                    self.upGrids.append(grid)

                self.writeCtaLog(u'重新拉上网格:[{0}~{1}]'.format(upline, upline + gridSteps[-1] * upRate))

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

    def clearDuplicateGrids(self, direction=EMPTY_STRING, type=EMPTY_STRING):
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

    def save(self, direction=None):
        """
        保存网格至本地Json文件"
        2017/11/23 update: 保存时，空的列表也保存
        :param direction: 
        :return: 
        """""

        # 更新开仓均价
        self.recount_avg_open_price()
        grids_save_path = self.get_data_folder()

        # 确保json名字与策略一致
        if self.jsonName != self.strategy.name:
            self.writeCtaLog(u'JsonName {} 与 上层策略名{} 不一致.'.format(self.jsonName, self.strategy.name))
            self.jsonName = self.strategy.name

        # 移除旧版上/下网格列表
        old_up_json_file = os.path.join(grids_save_path, u'{0}_upGrids.json'.format(self.jsonName))
        old_dn_json_file = os.path.join(grids_save_path, u'{0}_dnGrids.json'.format(self.jsonName))
        if os.path.exists(old_up_json_file):
            try:
                os.remove(old_up_json_file)
            except:
                pass

        if os.path.exists(old_dn_json_file):
            try:
                os.remove(old_dn_json_file)
            except:
                pass

        # 新版网格持久化文件
        grid_json_file = os.path.join(grids_save_path, u'{}_Grids.json'.format(self.jsonName))
        self.json_file_path = grid_json_file

        data = {}
        up_grids = []
        for grid in self.upGrids:
            up_grids.append(grid.toJson())
        dn_grids = []
        for grid in self.dnGrids:
            dn_grids.append(grid.toJson())
        data[u'up_grids'] = up_grids
        data[u'dn_grids'] = dn_grids

        with open(grid_json_file, 'w') as f:
            json_data = json.dumps(data, indent=4)
            f.write(json_data)

        self.writeCtaLog(u'GrideTrade保存文件{}完成'.format(grid_json_file))

    def load(self, direction, openStatusFilter=[]):
        """
        加载本地Json至网格
        :param direction: DIRECTION_SHORT,做空网格；DIRECTION_LONG，做多网格
        :param openStatusFilter: 缺省，不做过滤；True，只提取已开仓的数据，False，只提取未开仓的数据
        :return:
        """
        data = {}
        grids_save_path = self.get_data_folder()

        if self.jsonName != self.strategy.name:
            self.writeCtaLog(u'JsonName {} 与 上层策略名{} 不一致.'.format(self.jsonName, self.strategy.name))
            self.jsonName = self.strategy.name

        # 移除旧版上/下网格列表
        old_up_json_file = os.path.join(grids_save_path, u'{0}_upGrids.json'.format(self.jsonName))
        old_dn_json_file = os.path.join(grids_save_path, u'{0}_dnGrids.json'.format(self.jsonName))

        if os.path.exists(old_up_json_file):
            try:
                with open(old_up_json_file, 'r', encoding='utf8') as f:
                    # 解析json文件
                    data['up_grids'] = json.load(f)
            except IOError:
                self.writeCtaLog(u'读取网格{}出错'.format(old_up_json_file))
                data['up_grids'] = []
            try:    # 移除旧版上网格文件
                os.remove(old_up_json_file)
            except:
                pass

        if os.path.exists(old_dn_json_file):
            try:
                with open(old_dn_json_file, 'r', encoding='utf8') as f:
                    # 解析json文件
                    data['dn_grids'] = json.load(f)
            except IOError as ex:
                self.writeCtaLog(u'读取网格{}出错,ex:{}'.format(old_dn_json_file,str(ex)))
                data['dn_grids'] = []
            try:    # 移除旧版下网格文件
                os.remove(old_dn_json_file)
            except:
                pass

        # 若新版文件不存在，就保存；若存在，就优先使用新版数据文件
        grid_json_file = os.path.join(grids_save_path, u'{}_Grids.json'.format(self.jsonName))
        if not os.path.exists(grid_json_file):
            if len(data) == 0:
                data['up_grids'] = []
                data['dn_grids'] = []
                self.writeCtaLog(u'{}不存在，保存'.format(grid_json_file))
            else:
                self.writeCtaLog(u'{}不存在，保存'.format(grid_json_file))
            try:
                with open(grid_json_file, 'w') as f:
                    json_data = json.dumps(data, indent=4)
                    f.write(json_data)
            except Exception as ex:
                self.writeCtaLog(u'写入网格文件{}异常:{}'.format(grid_json_file,str(ex)))
        else:
            # 读取json文件
            try:
                with open(grid_json_file, 'r', encoding='utf8') as f:
                    data = json.load(f)
            except Exception as ex:
                self.writeCtaLog(u'读取网格文件{}异常:{}'.format(grid_json_file,str(ex)))

        #  从文件获取数据
        json_grids = []
        if direction == DIRECTION_SHORT :
            json_grids = data['up_grids'] if 'up_grids' in data else []

        elif direction == DIRECTION_LONG:
            json_grids = data['dn_grids'] if 'dn_grids' in data else []

        grids = []
        for i in json_grids:

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

        # 更新开仓均价
        self.recount_avg_open_price()
        return grids

    def get_data_folder(self):
        """获取数据目录"""
        # 工作目录
        currentFolder = os.path.abspath(os.path.join(os.getcwd(), u'data'))
        if os.path.isdir(currentFolder):
            # 如果工作目录下，存在data子目录，就使用data子目录
            return currentFolder
        else:
            # 否则，使用缺省保存目录 vnpy/trader/app/ctaStrategy/data
            return os.path.abspath(os.path.join(os.path.dirname(__file__), u'data'))

    def changeStrategyName(self, old_name, new_name):
        """
        在线更换策略实例名称，需要把Json文件也转移
        :param old_name:
        :param new_name:
        :return:
        """
        if old_name == new_name:
            self.writeCtaLog(u'更换策略实例名称失败,old:{} =>new:{}'.format(old_name, new_name))
            return

        data_folder = self.get_data_folder()

        self.jsonName = new_name
        # 旧文件
        old_up_json_file = os.path.join(data_folder, u'{0}_upGrids.json'.format(old_name))
        old_dn_json_file = os.path.join(data_folder, u'{0}_dnGrids.json'.format(old_name))
        old_json_file = os.path.join(data_folder, u'{0}_Grids.json'.format(old_name))

        # 新文件
        self.json_file_path = os.path.join(data_folder, u'{0}_Grids.json'.format(new_name))
        if os.path.isfile(self.json_file_path):         # 新文件若存在，移除
            try:
                os.remove(self.json_file_path)
            except Exception as ex:
                self.writeCtaLog(u'GridTrade.changeStrategyName 删除文件：{}异常:{}'.format(old_up_json_file,str(ex)))

        # 移动文件
        if os.path.isfile(old_json_file):
            try:
                shutil.move(old_json_file, self.json_file_path)
                return
            except Exception as ex:
                self.writeCtaLog(u'GridTrade.changeStrategyName 移动文件：{}=》{}异常:{}'.format(old_up_json_file, self.json_file_path, str(ex)))
        else:
            data = {}
            if os.path.isfile(old_up_json_file):
                try:
                    with open(old_up_json_file, 'r', encoding='utf8') as f:
                        # 解析json文件
                        data['up_grids'] = json.load(f)
                except IOError:
                    self.writeCtaLog(u'读取网格{}出错'.format(old_up_json_file))
                    data['up_grids'] = []
                try:    # 移除旧版上网格文件
                    os.remove(old_up_json_file)
                except IOError:
                    self.writeCtaLog(u'移除网格{}出错'.format(old_up_json_file))

            else:
                data['up_grids'] = []
            if os.path.isfile(old_dn_json_file):
                try:
                    with open(old_dn_json_file, 'r', encoding='utf8') as f:
                        # 解析json文件
                        data['dn_grids'] = json.load(f)
                except IOError:
                    self.writeCtaLog(u'读取网格{}出错'.format(old_dn_json_file))
                    data['dn_grids'] = []
                try:    # 移除旧版上网格文件
                    os.remove(old_dn_json_file)
                except IOError:
                    self.writeCtaLog(u'移除网格{}出错'.format(old_dn_json_file))
            else:
                data['dn_grids'] = []

            try:
                with open(self.json_file_path, 'w') as f:
                    json_data = json.dumps(data, indent=4)
                    f.write(json_data)
            except IOError as ex:
                self.writeCtaLog(u'写入网格文件{}异常:{}'.format(self.json_file_path, str(ex)))

    def getJsonFilePath(self):
        """
        返回上下网格的文件路径
        :return:
        """
        return self.json_file_path

    def getTypesOfOpenedGrids(self, direction, include_empty=False):
        """
        获取开仓的网格类型列表
        :param direction:
        :param include_empty: 是否包含空值的类型
        :return:
        """
        grids = self.getOpenedGrids(direction)
        type_list = []
        for g in grids:
            if g.type not in type_list and (g.type !=EMPTY_STRING if not include_empty else True):
                type_list.append(g.type)

        return type_list

class CtaLegacyGridTrade(object):
    """网格交易类
    包括两个方向的网格队列，
    v1, 传统网格：上网格做多，下网格做空
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
        self.jsonName = self.strategy.origName  #策略名称
        self.useMongoDb = True

        self.maxLots = maxlots      # 缺省网格数量
        self.gridHeight = height    # 最小网格高度
        self.gridWin = win          # 最小止盈高度

        self.volume = vol           # 每次网格开仓数量
        self.volumeList = [1, 1, 1, 1, 1, 1, 1, 1, 1, 1]    # 梯级开仓数量比例

        self.upGrids = []           # 上网格列表，专门做多
        self.dnGrids = []           # 下网格列表，专门做空

        self.avg_up_open_price = EMPTY_FLOAT        # 上网格开仓均价
        self.avg_dn_open_price = EMPTY_FLOAT        # 下网格开仓均价

        self.max_up_open_price = EMPTY_FLOAT  # 上网格开仓均价
        self.min_dn_open_price = EMPTY_FLOAT  # 下网格开仓均价

        self.up_json_file_path = None    # 下网格（做多网格）的路径
        self.dn_json_file_path = None   # 下网格（做多网格）的路径

        self.fixedGrids = False         # Set grids with fixed price or not
        self.fixedGridInitPrice = EMPTY_FLOAT
        self.gridBufferLength = 5       # Close grids only when (# of grids >= this value)

    def enableFixedGrids(self, price, gridbufferlen=5):
        self.fixedGrids = True
        self.fixedGridInitPrice = price
        self.gridBufferLength = gridbufferlen

    def disableFixedGrids(self, price):
        self.fixedGrids = False
        self.fixedGridInitPrice = 0

    def changeGridHeight(self, grid_height=EMPTY_FLOAT, grid_win=EMPTY_FLOAT):
        self.gridHeight = grid_height
        self.gridWin = grid_win

    def getVolumeRate(self, gridIndex=EMPTY_INT):
        """获取网格索引对应的开仓数量比例"""
        if gridIndex >= len(self.volumeList) or gridIndex < 0:
            return 1
        rate = self.volumeList[gridIndex]

        if rate == 0:
            return 1
        else:
            return rate

    def initGrid(self, upline=EMPTY_FLOAT, dnline=EMPTY_FLOAT, max_lots=EMPTY_INT, reuse=False):
        """初始化网格队列，突破开仓
        upline，上阻力线
        dnline，下支撑线
        """
        if max_lots > EMPTY_INT:
            lots = max_lots
        else:
            lots = self.maxLots

        newupline = upline
        newdnline = dnline
        if self.fixedGrids is True:
            if abs(self.fixedGridInitPrice - upline) % self.gridHeight > 0:
                newupline = upline - abs(self.fixedGridInitPrice - upline) % self.gridHeight + self.gridHeight  # >= current value
                newdnline = dnline - abs(self.fixedGridInitPrice - dnline) % self.gridHeight                    # <= current value

        self.writeCtaLog(u'初始化网格队列，upline:{}({}),dnline:{}({}), '.format(upline, newupline, dnline, newdnline))
        upline = newupline
        dnline = newdnline

        # 初始化上网格列表
        if len(self.upGrids) == 0:
            self.upGrids = self.load(direction= DIRECTION_LONG)
            if len(self.upGrids) > 0:
                self.writeCtaLog(u'上网格从文件{}加载完成'.format(self.up_json_file_path))
            else:
                # 做多，开仓价为上阻力线+网格高度*i，平仓价为开仓价+止盈高度，开仓数量为缺省
                for i in range(0, lots, 1):
                    grid = CtaGrid(direction=DIRECTION_LONG,
                                   openprice=upline + self.gridHeight*i,
                                   closeprice=upline + self.gridHeight*i - self.gridWin,
                                   volume=self.volume*self.getVolumeRate(i))
                    if reuse:
                        grid.reuse = reuse
                    self.upGrids.append(grid)

                self.writeCtaLog(u'上网格{0}~{1}初始化完成'.format(upline,upline+self.gridHeight*self.maxLots))
                self.save(direction=DIRECTION_LONG)

        # 初始化下网格列表
        if len(self.dnGrids) == 0:
            self.dnGrids = self.load(direction= DIRECTION_SHORT)
            if len(self.dnGrids) > 0:
                self.writeCtaLog(u'下网格从文件{}加载完成'.format(self.dn_json_file_path))
            else:
                for i in range(0, lots, 1):
                    # 做空，开仓价为下阻力线-网格高度*i，平仓价为开仓价-止盈高度，开仓数量为缺省
                    grid = CtaGrid(direction=DIRECTION_SHORT,
                                   openprice=dnline - self.gridHeight * i,
                                   closeprice=dnline - self.gridHeight * i + self.gridWin,
                                   volume=self.volume*self.getVolumeRate(i))
                    if reuse:
                        grid.reuse = reuse
                    self.dnGrids.append(grid)

                self.writeCtaLog(u'下网格{0}~{1}初始化完成'.format(dnline,dnline-self.gridHeight*self.maxLots))
                self.save(direction=DIRECTION_SHORT)

    def writeCtaLog(self, log):
        self.strategy.writeCtaLog(log)

    def toStr(self,direction):
        """显示网格"""

        pendingCloseList = u''      # 平仓清单
        pendingOpenList = u''       # 开仓清单
        deactiveList = u''          # 待激活清单
        openedVolumeDict = {}    # 开仓数量汇总

        if direction == DIRECTION_SHORT:
            numDeactivated = 0
            for grid in self.dnGrids:
                t = EMPTY_STRING
                if grid.type == LOCK_GRID:
                    t = u'L:'
                elif grid.type == TREND_GRID:
                    t = u'T:'
                elif grid.type == PERIOD_GRID:
                    t = u'P:'
                else:
                    t = grid.type
                # 待平仓
                if grid.openStatus :
                    opened_volume = 0
                    if grid.tradedVolume == EMPTY_INT:
                        pendingCloseList = pendingCloseList + u'{}[{}->{},sp:{},v:{}];'\
                            .format(t,grid.openPrice, grid.closePrice, grid.stopPrice, grid.volume)
                        opened_volume = grid.volume
                    else:
                        pendingCloseList = pendingCloseList + u'[{}{}->{},sp:{},v:{}/{}];'\
                            .format(t, grid.openPrice, grid.closePrice, grid.volume, grid.stopPrice, grid.tradedVolume)
                        opened_volume = grid.volume - grid.tradedVolume

                    if grid.type != EMPTY_STRING:
                        openedVolumeDict[grid.type] = opened_volume if grid.type not in openedVolumeDict else opened_volume + openedVolumeDict[grid.type]
                    openedVolumeDict['All'] = opened_volume if 'All' not in openedVolumeDict else opened_volume + openedVolumeDict['All']

                # 待开仓成交
                elif not grid.openStatus and grid.orderStatus:
                    if grid.tradedVolume == EMPTY_INT:
                        pendingOpenList = pendingOpenList + u'[{}{},v:{}];'.format(t, grid.openPrice, grid.volume)
                    else:
                        pendingOpenList = pendingOpenList + u'[{}{},v:{}/{}];'\
                            .format(t, grid.openPrice, grid.volume, grid.tradedVolume)

                # 等待挂单
                else:
                    if numDeactivated < 5:
                        deactiveList = deactiveList + u'[{}{}];'.format(t,grid.openPrice)
                        numDeactivated += 1
                    else:
                        break

            return u'Short:空:待平:[{}],{};开:{};待:{}'.format(openedVolumeDict, pendingCloseList, pendingOpenList, deactiveList)

        if direction == DIRECTION_LONG:
            numDeactivated = 0
            for grid in self.upGrids:
                t = EMPTY_STRING
                if grid.type == LOCK_GRID:
                    t = u'L:'
                elif grid.type == TREND_GRID:
                    t = u'T:'
                elif grid.type == PERIOD_GRID:
                    t = u'P:'
                else:
                    t = grid.type
                # 待平仓
                if grid.openStatus:
                    opened_volume = 0
                    if grid.tradedVolume == EMPTY_INT:
                        pendingCloseList = pendingCloseList + u'[{} {}->{},sp:{},v:{}];'\
                            .format(t,grid.openPrice, grid.closePrice, grid.stopPrice, grid.volume)
                        opened_volume = grid.volume
                    else:
                        pendingCloseList = pendingCloseList + u'[{} {}->{},sp:{}, v:{}/{}];'\
                            .format(t,grid.openPrice, grid.closePrice, grid.stopPrice, grid.volume, grid.tradedVolume)
                        opened_volume = grid.volume - grid.tradedVolume
                    if grid.type != EMPTY_STRING:
                        openedVolumeDict[grid.type] = opened_volume if grid.type not in openedVolumeDict else opened_volume + openedVolumeDict[grid.type]
                    openedVolumeDict['All'] = opened_volume if 'All' not in openedVolumeDict else opened_volume + openedVolumeDict['All']
                # 待开仓成交
                elif not grid.openStatus and grid.orderStatus:
                    if grid.tradedVolume == EMPTY_INT:
                        pendingOpenList = pendingOpenList + u'[{}{},v:{}];'.format(t, grid.openPrice, grid.volume)
                    else:
                        pendingOpenList = pendingOpenList + u'[{}{},v:{}/{}];'\
                            .format(t, grid.openPrice, grid.volume, grid.tradedVolume)

                # 等待挂单
                else:
                    if numDeactivated < 5:
                        deactiveList = deactiveList + u'[{}{}];'.format(t, grid.openPrice)
                        numDeactivated += 1
                    else:
                        break

            return u'Long:多:待平:[{}],{};开:{};待:{}'.format(openedVolumeDict, pendingCloseList,pendingOpenList,deactiveList)

    def getGridsWithTypes(self, direction, types=[]):
        """获取符合类型的网格
        direction:做多、做空方向: 做多方向时，从dnGrids中获取;  做空方向时，从upGrids中获取
        type：网格类型列表，
        """
        # 状态一致，价格大于最低价格
        if direction == DIRECTION_SHORT:
            grids = [x for x in self.dnGrids
                     if x.type in types]
            return grids

        # 状态一致，开仓价格小于最高价格
        if direction == DIRECTION_LONG:
            grids = [x for x in self.upGrids
                     if x.type in types]
            return grids

    def getOpenedGridsWithTypes(self, direction, types=[]):
        """获取符合类型的持仓网格
        direction:做多、做空方向: 做多方向时，从dnGrids中获取;  做空方向时，从upGrids中获取
        type：网格类型列表，
        """
        # 状态一致，价格大于最低价格
        if direction == DIRECTION_SHORT:
            grids = [x for x in self.dnGrids
                     if x.openStatus == True and x.type in types]
            return grids

        # 状态一致，开仓价格小于最高价格
        if direction == DIRECTION_LONG:
            grids = [x for x in self.upGrids
                     if x.openStatus == True and x.type in types]
            return grids

    def getOpenedGrids(self, direction):
        """获取已开仓的网格
        direction:做多、做空方向: 做多方向时，从dnGrids中获取;  做空方向时，从upGrids中获取
        """
        # 状态一致，价格大于最低价格
        if direction == DIRECTION_SHORT:
            grids = [x for x in self.dnGrids
                     if x.openStatus == True]

            return grids

        # 状态一致，开仓价格小于最高价格
        if direction == DIRECTION_LONG:
            grids = [x for x in self.upGrids
                     if x.openStatus == True]
            return grids

    def getGrids(self, direction, ordered=False, opened=False, closed=False, begin=EMPTY_FLOAT, end=EMPTY_FLOAT, type=EMPTY_STRING, delta=0):
        """获取未挂单的网格
        direction:做多、做空方向: 做空方向时，从dnGrids中获取;  做多方向时，从upGrids中获取
        ordered:是否已提交至服务器
        opened：是否已开仓
        closed：是否已平仓
        begin：开始价格,
        end：结束价格，
        delta：基于begin价格的偏移，处理滑点，得到更好的开仓点位
        """

        # 状态一致，价格大于最低价格
        if direction == DIRECTION_SHORT:
            if begin == EMPTY_FLOAT: begin = sys.maxsize
            if end == EMPTY_FLOAT: end = 0-sys.maxsize
            begin += delta
            grids = [x for x in self.dnGrids
                     if x.orderStatus == ordered
                     and x.openStatus == opened
                     and x.closeStatus == closed
                     and x.openPrice >= begin
                     and x.openPrice <= end
                     and x.type == type]

            return grids

        # 状态一致，开仓价格小于最高价格
        if direction == DIRECTION_LONG:
            if begin == EMPTY_FLOAT: begin = 0-sys.maxsize
            if end == EMPTY_FLOAT: end = sys.maxsize
            begin -= delta
            grids = [x for x in self.upGrids
                     if x.orderStatus == ordered
                     and x.openStatus == opened
                     and x.closeStatus == closed
                     and x.openPrice <= begin
                     and x.openPrice >= end
                     and x.type == type]
            return grids

    def getGridById(self,direction, id):
        """寻找指定id的网格"""
        if id == EMPTY_STRING or len(id) <1:
            return
        if direction == DIRECTION_SHORT:
            for x in self.dnGrids[:]:
                if x.id == id:
                    self.writeCtaLog(u'找到下网格[open={},close={},stop={},volume={}]'.format(x.openPrice,x.closePrice,x.stopPrice,x.volume))
                    return x

        if direction == DIRECTION_LONG:
            for x in self.upGrids[:]:
                if x.id == id:
                    self.writeCtaLog(u'找到上网格[open={},close={},stop={},volume={}]'.format(x.openPrice,x.closePrice,x.stopPrice,x.volume))
                    return x

        return None

    def getPosition(self,direction, type=EMPTY_STRING):
        """获取特定类型的网格持仓"""
        if direction == DIRECTION_SHORT:
            long_vol = [x.volume-x.tradedVolume for x in self.dnGrids if x.openStatus and x.type == type]
            return  sum(long_vol)

        if direction == DIRECTION_LONG:
            short_vol = [x.volume - x.tradedVolume for x in self.upGrids if x.openStatus and x.type == type]
            return sum(short_vol)

    def updateOrderRef(self, direction, openPrice, orderRef):
        """更新网格的orderId"""
        if direction == DIRECTION_SHORT:
            for x in self.dnGrids:
                if x.openPrice == openPrice:
                    x.orderRef = orderRef
                    x.orderStatus = True

        if direction == DIRECTION_LONG:
            for x in self.upGrids:
                if x.openPrice == openPrice:
                    x.orderRef = orderRef
                    x.orderStatus = True

    def cancelOrderRef(self,direction, openPrice):
        """网格撤单"""
        if direction == DIRECTION_SHORT:
            for x in self.dnGrids:
                if x.openPrice == openPrice and x.orderRef != EMPTY_STRING and x.orderStatus==True and x.openStatus==False:
                    x.orderRef = EMPTY_STRING
                    x.orderStatus = False
                    self.writeCtaLog(u'下网格撤单[{0}]'.format(x.openPrice))

        if direction == DIRECTION_LONG:
            for x in self.upGrids:
                if x.openPrice == openPrice and x.orderRef != EMPTY_STRING and x.orderStatus==True and x.openStatus==False:
                    x.orderRef = EMPTY_STRING
                    x.orderStatus = False
                    self.writeCtaLog(u'上网格撤单[{0}]'.format(x.openPrice))

    def getGridbyOpenPrice(self, direction, openPrice, orderRef = EMPTY_STRING):
        """通过开仓价和委托状态获取网格"""
        if direction == DIRECTION_SHORT:
            for x in self.dnGrids:
                # 优先匹配价格
                if x.orderRef == orderRef and x.openPrice == openPrice:
                    return x

        if direction == DIRECTION_LONG:
            for x in self.upGrids:
                # 优先匹配价格
                if x.orderRef == orderRef and x.openPrice == openPrice:
                    return x

        self.writeCtaLog(u'异常，getGridbyOpenPrice找不到网格[{0},openprice={1},orderRef={2}]'.format(direction, openPrice, orderRef))
        return None

    def getGrid(self, direction, openPrice=EMPTY_FLOAT, closePrice=EMPTY_FLOAT, orderRef=EMPTY_STRING, t=EMPTY_STRING):
        """获取网格"""
        if direction == DIRECTION_SHORT:
            for x in self.dnGrids:
                # 优先匹配价格
                if t == u'OpenPrice' and x.openPrice == openPrice:
                    return x
                elif t == u'ClosePrice' and x.closePrice == closePrice:
                    return x
                elif t == u'OrderRef' and x.orderRef == orderRef:
                    return x

        if direction == DIRECTION_LONG:
            for x in self.upGrids:
                # 优先匹配价格
                if t == u'OpenPrice' and x.openPrice == openPrice:
                    return x
                elif t == u'ClosePrice' and x.closePrice == closePrice:
                    return x
                elif t == u'OrderRef' and x.orderRef == orderRef:
                    return x

        self.writeCtaLog(u'异常，getGrid找不到网格[direction={0},oepnPrice={1},closePrice={2},orderRef={3},t={4}]'.format(direction, openPrice, closePrice, orderRef, t))
        return None

    def updateClosePrice(self, direction, closePrice=EMPTY_FLOAT, type=EMPTY_STRING):
        """获取网格"""
        # if num(opened Grids) <= 5: set closePrice to 0
        # else: set closePrice to the specified one (should be the closePrice of the newest Grid)
        numChanged = 0
        newPrice = EMPTY_FLOAT
        if direction == DIRECTION_SHORT:
            for x in self.dnGrids:
                if x.type == type and x.openStatus is True:
                    x.closePrice = newPrice
                    numChanged += 1
            if numChanged >= self.gridBufferLength:
                newPrice = closePrice
                for x in self.dnGrids:
                    if x.type == type and x.openStatus is True:
                        x.closePrice = newPrice

        if direction == DIRECTION_LONG:
            for x in self.upGrids:
                if  x.type == type and x.openStatus is True:
                    x.closePrice = newPrice
                    numChanged += 1
            if numChanged >= self.gridBufferLength:
                newPrice = closePrice
                for x in self.upGrids:
                    if x.type == type and x.openStatus is True:
                        x.closePrice = newPrice

        self.writeCtaLog(u'updateClosePrice() {}: update closePrice to {} for all opened grids({})'.format(direction, newPrice, numChanged))

    def getFirstLastGrid(self, direction,type = EMPTY_STRING):
        """获取最前/后一个的网格"""
        # 做多网格：,first =开仓价最高一个,last= 最低一个
        if direction == DIRECTION_LONG:
            short_grids = self.getGridsWithTypes(direction=direction, types=[type])
            if short_grids is None or len(short_grids) ==0 :
                return None, None

            if len(short_grids) == 1:
                return short_grids[0],short_grids[0]

            # 价格由低至高排列
            sortedGrids = sorted(short_grids, key=lambda g:g.openPrice)
            return sortedGrids[-1], sortedGrids[0]

        # 做空网格： first =最低一个,last= 开仓价最高一个
        if direction == DIRECTION_SHORT:
            long_grids = self.getGridsWithTypes(direction=direction, types=[type])
            if long_grids is None or len(long_grids) ==0:
                return None, None

            if len(long_grids) == 1:
                return long_grids[0], long_grids[0]

            sortedGrids = sorted(long_grids, key=lambda g: g.openPrice)
            return sortedGrids[0], sortedGrids[-1]

        return None,None

    def getLastOpenedGrid(self, direction,type = EMPTY_STRING,orderby_asc=True):
        """获取最后一个开仓的网格"""
        if direction == DIRECTION_LONG:
            opened_long_grids = self.getGrids(direction=direction, opened=True,type=type)
            if opened_long_grids is None or len(opened_long_grids) ==0 :
                return None
            if len(opened_long_grids) > 1:
                sortedGrids = sorted(opened_long_grids, key=lambda g:g.openPrice)
                if orderby_asc:
                    # 取价格最高的一格
                    opened_long_grids = sortedGrids[-1:]
                else:
                    # 取价格最低的一格
                    opened_long_grids = sortedGrids[0:1]

            return opened_long_grids[0]

        if direction == DIRECTION_SHORT:
            opened_short_grids = self.getGrids(direction=direction, opened=True,type=type)
            if opened_short_grids is None or len(opened_short_grids) ==0:
                return None
            if len(opened_short_grids) > 1:
                sortedGrids = sorted(opened_short_grids, key=lambda g: g.openPrice)
                if orderby_asc:
                    # 取价格最低的一格
                    opened_short_grids = sortedGrids[0:1]
                else:
                    # 取价格最高的一格
                    opened_short_grids = sortedGrids[-1:]

            return opened_short_grids[0]

    def closeGrid(self, direction, closePrice, closeVolume):
        """网格交易结束"""
        if direction == DIRECTION_SHORT:
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

        if direction == DIRECTION_LONG:
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
        if direction == DIRECTION_SHORT:
            for x in self.dnGrids[:]:
                if x.id == id:
                    self.writeCtaLog(u'清除下网格[open={},close={},stop={},volume={}]'.format(x.openPrice,x.closePrice,x.stopPrice,x.volume))
                    self.dnGrids.remove(x)

        if direction == DIRECTION_LONG:
            for x in self.upGrids[:]:
                if x.id == id:
                    self.writeCtaLog(u'清除上网格[open={},close={},stop={},volume={}]'.format(x.openPrice,x.closePrice,x.stopPrice,x.volume))
                    self.upGrids.remove(x)

    def removeGrids(self, direction, priceline, type=EMPTY_STRING):
        """清除价格线以下的网格"""
        if direction == DIRECTION_SHORT:
            for x in self.dnGrids[:]:
                if x.openPrice < priceline and not x.orderStatus and not x.openStatus and not x.closeStatus and x.type==type:
                    self.writeCtaLog(u'清除下网格[open={0}]'.format(x.openPrice))
                    self.dnGrids.remove(x)

        if direction == DIRECTION_LONG:
            for x in self.upGrids[:]:
                if x.openPrice > priceline and not x.orderStatus and not x.openStatus and not x.closeStatus and x.type==type:
                    self.writeCtaLog(u'清除上网格[open={0}]'.format(x.openPrice))
                    self.upGrids.remove(x)

    def moveGrids(self, direction, pricedelta, type=EMPTY_STRING):
        """按pricedelta平移所有网格"""
        if direction == DIRECTION_SHORT:
            for x in self.dnGrids[:]:
                x.openPrice += pricedelta  # 开仓价格
                if x.closePrice != 0:
                    x.closePrice += pricedelta  # 平仓价格
                x.stopPrice += pricedelta  # 止损价格
                x.type = type  # 网格类型标签
                # self.openPrices = {}  # 套利使用，开仓价格，symbol:price

        if direction == DIRECTION_LONG:
            for x in self.upGrids[:]:
                x.openPrice += pricedelta  # 开仓价格
                if x.closePrice != 0:
                    x.closePrice += pricedelta  # 平仓价格
                x.stopPrice += pricedelta  # 止损价格
                x.type = type  # 网格类型标签
                # self.openPrices = {}  # 套利使用，开仓价格，symbol:price

    def rebuildGrids(self, direction, upline=EMPTY_FLOAT, dnline=EMPTY_FLOAT, midline=EMPTY_FLOAT, upRate=1, dnRate=1, reuse=False, useVariableSteps=False):
        """重新拉网
        清除未挂单的网格，
        在上轨/下轨位置重新挂单
        upRate , 上轨网格高度比率
        dnRate， 下轨网格高度比率
        """
        result = True
        newupline = upline
        newdnline = dnline
        if self.fixedGrids is True:
            if abs(self.fixedGridInitPrice - upline) % self.gridHeight > 0:
                newupline = upline - abs(self.fixedGridInitPrice - upline) % self.gridHeight + 2*self.gridHeight  # ceil(current value, gridHeight) + gridHeight
                newdnline = dnline - abs(self.fixedGridInitPrice - dnline) % self.gridHeight - self.gridHeight    # floor(current value, gridHeight) - gridHeight
            else:
                newupline = upline + self.gridHeight
                newdnline = dnline - self.gridHeight

        if direction == DIRECTION_SHORT:
            self.writeCtaLog(u'DEBUG- rebuildGrids Short, 重新拉网:direction:{},upline:{}({}),dnline:{}({})'.format(direction, upline, newupline, dnline, newdnline))
        else:
            self.writeCtaLog(u'DEBUG- rebuildGrids Long, 重新拉网:direction:{},upline:{}({}),dnline:{}({})'.format(direction, upline, newupline, dnline, newdnline))
        uplineDelta = newupline - upline
        dnlineDelta = newdnline - dnline
        upline = newupline
        dnline = newdnline

        # 检查上下网格的高度比率，不能低于0.5
        if upRate < 0.5 or dnRate < 0.5:
            upRate = max(0.5, upRate)
            dnRate = max(0.5, dnRate)

        # 计算每个网格的高度。如果使用变高的网格，则每过5格把网格搞的增加(self.gridHeight/2)
        gridSteps = [0]*self.maxLots
        for i in range(1, self.maxLots, 1):
            if useVariableSteps == False:
                gridSteps[i] = self.gridHeight * i
            else:
                j = int(i / 5)
                gridSteps[i] = gridSteps[i-1] + self.gridHeight + self.gridHeight / 2 * j

        # 重建下网格(向下移动开仓的网格)
        if direction == DIRECTION_SHORT:
            min_long_price = midline
            remove_grids = []
            opened_grids = []
            temp_dnGrids = []
            if self.fixedGrids is True:
                # 如果价格没变，不需要重新布网格
                if dnline == self.dnGrids[0].openPrice:
                    self.writeCtaLog(u'DEBUG- rebuildGrids Short, dnline not changed, no need to rebuild.')
                    result = False
                    return result

                # 重建的网格数量(所有网格)
                remainLots = 0
                lots = self.maxLots - remainLots
                self.writeCtaLog(u'需要重建的网格数量:{0},起点:{1}'.format(lots, dnline))
                if lots > 0:
                    for i in range(0, lots, 1):
                        # 做空，开仓价为下阻力线-网格高度*i，平仓价为开仓价+止盈高度，开仓数量为缺省
                        open_price = int((dnline - gridSteps[i+remainLots] * dnRate) / self.minDiff ) * self.minDiff
                        close_price = int((open_price + self.gridWin * dnRate)/self.minDiff) * self.minDiff

                        grid = CtaGrid(direction=DIRECTION_SHORT,
                                       openprice=open_price,
                                       closeprice=close_price,
                                       volume=self.volume*self.getVolumeRate(remainLots + i))
                        grid.reuse = reuse
                        temp_dnGrids.append(grid)

                    self.writeCtaLog(u'重新拉下网格:[{0}~{1}]'.format(dnline, dnline - gridSteps[-1] * dnRate))

                # 移除旧的下网格,保留开仓的网格状态
                for m in range(0, len(self.dnGrids)):
                    x = self.dnGrids[m]
                    if not x.orderStatus and not x.openStatus and not x.closeStatus:
                        if len(remove_grids) < 6:
                            remove_grids.append(u'{}=>{}'.format(x.openPrice, x.closePrice))
                    else:
                        if len(opened_grids) < 6:
                            opened_grids.append(u'{}=>{}'.format(x.openPrice, x.closePrice))
                        temp_dnGrids[m].orderStatus = x.orderStatus
                        temp_dnGrids[m].orderStatus = x.orderStatus
                        temp_dnGrids[m].volume = x.volume
                        temp_dnGrids[m].tradedVolume = x.tradedVolume
                        temp_dnGrids[m].orderStatus = x.orderStatus
                        temp_dnGrids[m].orderRef = x.orderRef
                        temp_dnGrids[m].openStatus = x.openStatus
                        temp_dnGrids[m].closeStatus = x.closeStatus
                        temp_dnGrids[m].openDatetime = x.openDatetime
                        temp_dnGrids[m].orderDatetime = x.orderDatetime
                        temp_dnGrids[m].lockGrids = x.lockGrids
                        temp_dnGrids[m].reuse = x.reuse
                        temp_dnGrids[m].type = x.type
                        temp_dnGrids[m].openPrices = x.openPrices
                        temp_dnGrids[m].snapshot = x.snapshot
                        if x.closePrice > 0:
                            temp_dnGrids[m].closePrice = x.closePrice + dnlineDelta
                        else:
                            temp_dnGrids[m].closePrice = 0

                if len(remove_grids) > 0:
                    self.writeCtaLog(u'清除下网格[{}]'.format(remove_grids))
                if len(opened_grids) > 0:
                    self.writeCtaLog(u'保留下网格[{}]'.format(opened_grids))

                for x in self.dnGrids[:]:
                    self.dnGrids.remove(x)
                # self.dnGrids.clear()
                self.dnGrids = temp_dnGrids

                self.writeCtaLog(u'DEBUG- rebuildGrids Short: lots:{},upline:{},dnline:{} [{}~{}]'.format(lots, upline, dnline, dnline, dnline - gridSteps[-1] * dnRate))

            else:
                # 移除未挂单的下网格
                for x in self.dnGrids[:]:
                    if not x.orderStatus and not x.openStatus and not x.closeStatus:
                        if len(remove_grids) < 6:
                            remove_grids.append(u'{}=>{}'.format(x.openPrice, x.closePrice))
                        self.dnGrids.remove(x)
                    else:
                        if len(opened_grids) < 6:
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
                remainLots = 0   # WJ: correction for the rebuild price

                dnline = min(dnline, min_long_price-self.gridHeight*dnRate)
                self.writeCtaLog(u'需要重建的网格数量:{0},起点:{1}'.format(lots, dnline))

                if lots > 0:
                    for i in range(0, lots, 1):
                        # 做空，开仓价为下阻力线-网格高度*i，平仓价为开仓价+止盈高度，开仓数量为缺省
                        open_price = int((dnline - gridSteps[i+remainLots] * dnRate) / self.minDiff ) * self.minDiff
                        close_price = int((open_price + self.gridWin * dnRate)/self.minDiff) * self.minDiff

                        grid = CtaGrid(direction=DIRECTION_SHORT,
                                       openprice=open_price,
                                       closeprice=close_price,
                                       volume=self.volume*self.getVolumeRate(remainLots + i))
                        grid.reuse = reuse
                        self.dnGrids.append(grid)

                    self.writeCtaLog(u'重新拉下网格:[{0}~{1}]'.format(dnline, dnline - gridSteps[-1] * dnRate))
                self.writeCtaLog(u'DEBUG- rebuildGrids Short, lots:{},upline:{},dnline:{} [{}~{}]'.format(lots, upline, dnline, dnline, dnline - gridSteps[-1] * dnRate))

        # 重建上网格(向上移动开仓的网格)
        if direction == DIRECTION_LONG:
            max_short_price = midline               # 最高开空价
            remove_grids = []                       # 移除的网格列表
            opened_grids = []                       # 已开仓的网格列表            temp_dnGrids = {}
            temp_upGrids = []
            if self.fixedGrids is True:
                # 如果价格没变，不需要重新布网格
                if upline == self.upGrids[0].openPrice:
                    self.writeCtaLog(u'DEBUG- rebuildGrids Long, upline not changed, no need to rebuild.')
                    result = False
                    return result

                # 重建的网格数量(所有网格)
                remainLots = 0
                lots = self.maxLots - remainLots
                self.writeCtaLog(u'需要重建的网格数量:{0},起点:{1}'.format(lots, upline))
                if lots > 0:
                    # 做多，开仓价为上阻力线+网格高度*i，平仓价为开仓价-止盈高度，开仓数量为缺省
                    for i in range(0, lots, 1):
                        open_price = int((upline + gridSteps[i+remainLots] * upRate) / self.minDiff) * self.minDiff
                        close_price = int((open_price - self.gridWin * upRate) / self.minDiff) * self.minDiff

                        grid = CtaGrid(direction=DIRECTION_LONG,
                                       openprice=open_price,
                                       closeprice=close_price,
                                       volume=self.volume*self.getVolumeRate(remainLots + i))
                        grid.reuse = reuse
                        temp_upGrids.append(grid)

                    self.writeCtaLog(u'重新拉上网格:[{0}~{1}]'.format(upline, upline + gridSteps[-1] * upRate))

                # 移除旧的上网格,保留开仓的网格状态
                for m in range(0, len(self.upGrids)):
                    x = self.upGrids[m]
                    if not x.orderStatus and not x.openStatus and not x.closeStatus:
                        if len(remove_grids) < 6:
                            remove_grids.append(u'{}=>{}'.format(x.openPrice, x.closePrice))
                    else:
                        if len(opened_grids) < 6:
                            opened_grids.append(u'{}=>{}'.format(x.openPrice, x.closePrice))
                        temp_upGrids[m].orderStatus = x.orderStatus
                        temp_upGrids[m].orderStatus = x.orderStatus
                        temp_upGrids[m].volume = x.volume
                        temp_upGrids[m].tradedVolume = x.tradedVolume
                        temp_upGrids[m].orderStatus = x.orderStatus
                        temp_upGrids[m].orderRef = x.orderRef
                        temp_upGrids[m].openStatus = x.openStatus
                        temp_upGrids[m].closeStatus = x.closeStatus
                        temp_upGrids[m].openDatetime = x.openDatetime
                        temp_upGrids[m].orderDatetime = x.orderDatetime
                        temp_upGrids[m].lockGrids = x.lockGrids
                        temp_upGrids[m].reuse = x.reuse
                        temp_upGrids[m].type = x.type
                        temp_upGrids[m].openPrices = x.openPrices
                        temp_upGrids[m].snapshot = x.snapshot
                        if x.closePrice > 0:
                            temp_upGrids[m].closePrice = x.closePrice + uplineDelta
                        else:
                            temp_upGrids[m].closePrice = 0

                if len(remove_grids) > 0:
                    self.writeCtaLog(u'清除上网格[{}]'.format(remove_grids))
                if len(opened_grids) > 0:
                    self.writeCtaLog(u'保留上网格[{}]'.format(opened_grids))

                for x in self.upGrids[:]:
                    self.upGrids.remove(x)
                # self.upGrids.clear()
                self.upGrids = temp_upGrids

                self.writeCtaLog(u'DEBUG- rebuildGrids Long, lots:{},upline:{},dnline:{} [{}~{}]'.format(lots, upline, dnline, upline, upline + gridSteps[-1] * upRate))


            else:
                # 移除未挂单的上网格
                for x in self.upGrids[:]:
                    if not x.orderStatus and not x.openStatus and not x.closeStatus:
                        if len(remove_grids) < 6:
                            remove_grids.append(u'{}=>{}'.format(x.openPrice, x.closePrice))
                        self.upGrids.remove(x)
                    else:
                        if len(opened_grids) < 6:
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
                remainLots = 0   # WJ: correction for the rebuild price

                upline = max(upline, max_short_price+self.gridHeight*upRate)
                self.writeCtaLog(u'需要重建的网格数量:{0},起点:{1}'.format(lots, upline))

                if lots > 0:
                    # 做多，开仓价为上阻力线+网格高度*i，平仓价为开仓价-止盈高度，开仓数量为缺省
                    for i in range(0, lots, 1):
                        open_price = int((upline + gridSteps[i+remainLots] * upRate) / self.minDiff) * self.minDiff
                        close_price = int((open_price - self.gridWin * upRate) / self.minDiff) * self.minDiff

                        grid = CtaGrid(direction=DIRECTION_LONG,
                                       openprice=open_price,
                                       closeprice=close_price,
                                       volume=self.volume*self.getVolumeRate(remainLots + i))
                        grid.reuse = reuse
                        self.upGrids.append(grid)

                    self.writeCtaLog(u'重新拉上网格:[{0}~{1}]'.format(upline, upline + gridSteps[-1] * upRate))
                self.writeCtaLog(u'DEBUG- rebuildGrids Long, lots:{},upline:{},dnline:{} [{}~{}]'.format(lots, upline, dnline, upline, upline + gridSteps[-1] * upRate))
        return result

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

    def save(self, direction=None):
        """
        保存网格至本地Json文件"
        2017/11/23 update: 保存时，空的列表也保存
        :param direction: 
        :return: 
        """""

        # 更新开仓均价
        self.recount_avg_open_price()
        grids_save_path = self.get_data_folder()

        # 确保json名字与策略一致
        if self.jsonName != self.strategy.name:
            self.writeCtaLog(u'JsonName {} 与 上层策略名{} 不一致.'.format(self.jsonName, self.strategy.name))
            self.jsonName = self.strategy.name

        # 移除旧版上/下网格列表
        old_up_json_file = os.path.join(grids_save_path, u'{0}_upGrids.json'.format(self.jsonName))
        old_dn_json_file = os.path.join(grids_save_path, u'{0}_dnGrids.json'.format(self.jsonName))
        if os.path.exists(old_up_json_file):
            try:
                os.remove(old_up_json_file)
            except:
                pass

        if os.path.exists(old_dn_json_file):
            try:
                os.remove(old_dn_json_file)
            except:
                pass

        # 新版网格持久化文件
        grid_json_file = os.path.join(grids_save_path, u'{}_Grids.json'.format(self.jsonName))
        self.json_file_path = grid_json_file

        data = {}
        up_grids = []
        for grid in self.upGrids:
            up_grids.append(grid.toJson())
        dn_grids = []
        for grid in self.dnGrids:
            dn_grids.append(grid.toJson())
        data[u'up_grids'] = up_grids
        data[u'dn_grids'] = dn_grids

        with open(grid_json_file, 'w') as f:
            json_data = json.dumps(data, indent=4)
            f.write(json_data)

        self.writeCtaLog(u'GrideTrade保存文件{}完成'.format(grid_json_file))

    def load(self, direction, openStatusFilter=[]):
        """
        加载本地Json至网格
        :param direction: DIRECTION_SHORT,做空网格；DIRECTION_LONG，做多网格
        :param openStatusFilter: 缺省，不做过滤；True，只提取已开仓的数据，False，只提取未开仓的数据
        :return: 
        """
        data = {}
        grids_save_path = self.get_data_folder()

        if self.jsonName != self.strategy.name:
            self.writeCtaLog(u'JsonName {} 与 上层策略名{} 不一致.'.format(self.jsonName, self.strategy.name))
            self.jsonName = self.strategy.name

        # 移除旧版上/下网格列表
        old_up_json_file = os.path.join(grids_save_path, u'{0}_upGrids.json'.format(self.jsonName))
        old_dn_json_file = os.path.join(grids_save_path, u'{0}_dnGrids.json'.format(self.jsonName))

        if os.path.exists(old_up_json_file):
            try:
                with open(old_up_json_file, 'r', encoding='utf8') as f:
                    # 解析json文件
                    data['up_grids'] = json.load(f)
            except IOError:
                self.writeCtaLog(u'读取网格{}出错'.format(old_up_json_file))
                data['up_grids'] = []
            try:    # 移除旧版上网格文件
                os.remove(old_up_json_file)
            except:
                pass

        if os.path.exists(old_dn_json_file):
            try:
                with open(old_dn_json_file, 'r', encoding='utf8') as f:
                    # 解析json文件
                    data['dn_grids'] = json.load(f)
            except IOError as ex:
                self.writeCtaLog(u'读取网格{}出错,ex:{}'.format(old_dn_json_file,str(ex)))
                data['dn_grids'] = []
            try:    # 移除旧版下网格文件
                os.remove(old_dn_json_file)
            except:
                pass

        # 若新版文件不存在，就保存；若存在，就优先使用新版数据文件
        grid_json_file = os.path.join(grids_save_path, u'{}_Grids.json'.format(self.jsonName))
        if not os.path.exists(grid_json_file):
            if len(data) == 0:
                data['up_grids'] = []
                data['dn_grids'] = []
                self.writeCtaLog(u'{}不存在，保存'.format(grid_json_file))
            else:
                self.writeCtaLog(u'{}不存在，保存'.format(grid_json_file))
            try:
                with open(grid_json_file, 'w') as f:
                    json_data = json.dumps(data, indent=4)
                    f.write(json_data)
            except Exception as ex:
                self.writeCtaLog(u'写入网格文件{}异常:{}'.format(grid_json_file,str(ex)))
        else:
            # 读取json文件
            try:
                with open(grid_json_file, 'r', encoding='utf8') as f:
                    data = json.load(f)
            except Exception as ex:
                self.writeCtaLog(u'读取网格文件{}异常:{}'.format(grid_json_file,str(ex)))

        #  从文件获取数据
        json_grids = []
        if direction == DIRECTION_SHORT :
            json_grids = data['up_grids'] if 'up_grids' in data else []

        elif direction == DIRECTION_LONG:
            json_grids = data['dn_grids'] if 'dn_grids' in data else []

        grids = []
        ids = []
        for i in json_grids:
            closePrice = float(i['closePrice'])
            openPrice = float(i['openPrice'])
            stopPrice = float(i['stopPrice'])
            id = i.get('id')
            self.writeCtaLog(u'load Grid:open:{0},close:{1},stop:{2}'.format(openPrice, closePrice, stopPrice))

            grid = CtaGrid(direction=i['direction'], openprice=openPrice, closeprice=closePrice,
                               stopprice=stopPrice, volume=i['volume'])
            if id is not None and id not in ids:
                grid.id = id
            ids.append(id)

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

        # 更新开仓均价
        self.recount_avg_open_price()
        return grids

    def get_data_folder(self):
        """获取数据目录"""
        # 工作目录
        currentFolder = os.path.abspath(os.path.join(os.getcwd(), u'data'))
        if os.path.isdir(currentFolder):
            # 如果工作目录下，存在data子目录，就使用data子目录
            return currentFolder
        else:
            # 否则，使用缺省保存目录 vnpy/trader/app/ctaStrategy/data
            return os.path.abspath(os.path.join(os.path.dirname(__file__), u'data'))

    def changeStrategyName(self, old_name, new_name):
        """
        在线更换策略实例名称，需要把Json文件也转移
        :param old_name: 
        :param new_name: 
        :return: 
        """
        if old_name == new_name:
            self.writeCtaLog(u'更换策略实例名称失败,old:{} =>new:{}'.format(old_name, new_name))
            return

        data_folder = self.get_data_folder()

        self.jsonName = new_name
        # 旧文件
        old_up_json_file = os.path.join(data_folder, u'{0}_upGrids.json'.format(old_name))
        old_dn_json_file = os.path.join(data_folder, u'{0}_dnGrids.json'.format(old_name))
        old_json_file = os.path.join(data_folder, u'{0}_Grids.json'.format(old_name))

        # 新文件
        self.json_file_path = os.path.join(data_folder, u'{0}_Grids.json'.format(new_name))
        if os.path.isfile(self.json_file_path):         # 新文件若存在，移除
            try:
                os.remove(self.json_file_path)
            except Exception as ex:
                self.writeCtaLog(u'GridTrade.changeStrategyName 删除文件：{}异常:{}'.format(old_up_json_file,str(ex)))

        # 移动文件
        if os.path.isfile(old_json_file):
            try:
                shutil.move(old_json_file, self.json_file_path)
                return
            except Exception as ex:
                self.writeCtaLog(u'GridTrade.changeStrategyName 移动文件：{}=》{}异常:{}'.format(old_up_json_file, self.json_file_path, str(ex)))
        else:
            data = {}
            if os.path.isfile(old_up_json_file):
                try:
                    with open(old_up_json_file, 'r', encoding='utf8') as f:
                        # 解析json文件
                        data['up_grids'] = json.load(f)
                except IOError:
                    self.writeCtaLog(u'读取网格{}出错'.format(old_up_json_file))
                    data['up_grids'] = []
                try:    # 移除旧版上网格文件
                    os.remove(old_up_json_file)
                except IOError:
                    self.writeCtaLog(u'移除网格{}出错'.format(old_up_json_file))

            else:
                data['up_grids'] = []
            if os.path.isfile(old_dn_json_file):
                try:
                    with open(old_dn_json_file, 'r', encoding='utf8') as f:
                        # 解析json文件
                        data['dn_grids'] = json.load(f)
                except IOError:
                    self.writeCtaLog(u'读取网格{}出错'.format(old_dn_json_file))
                    data['dn_grids'] = []
                try:    # 移除旧版上网格文件
                    os.remove(old_dn_json_file)
                except IOError:
                    self.writeCtaLog(u'移除网格{}出错'.format(old_dn_json_file))
            else:
                data['dn_grids'] = []

            try:
                with open(self.json_file_path, 'w') as f:
                    json_data = json.dumps(data, indent=4)
                    f.write(json_data)
            except IOError as ex:
                self.writeCtaLog(u'写入网格文件{}异常:{}'.format(self.json_file_path, str(ex)))

    def getJsonFilePath(self):
        """
        返回上下网格的文件路径
        :return: 
        """
        return self.json_file_path

    def getTypesOfOpenedGrids(self, direction, include_empty=False):
        """
        获取开仓的网格类型列表
        :param direction:
        :param include_empty: 是否包含空值的类型
        :return:
        """
        grids = self.getOpenedGrids(direction)
        type_list = []
        for g in grids:
            if g.type not in type_list and (g.type !=EMPTY_STRING if not include_empty else True):
                type_list.append(g.type)

        return type_list

ARBITRAGE_LONG =  u'正套'
ARBITRAGE_SHORT = u'反套'

class ArbitrageGrid(object):
    """套利网格"""
    def __init__(self,direction, openprice, closeprice, stopprice=EMPTY_FLOAT, type=EMPTY_STRING):
        self.leg1 = None
        self.leg2 = None

        self.id = str(uuid.uuid1())
        self.direction = direction          # 正套(ARBITRAGE_LONG) 反套(ARBITRAGE_SHORT)
        self.openPrice = openprice          # 开仓价格/价比
        self.closePrice = closeprice        # 平仓价格/价比
        self.stopPrice = stopprice          # 止损价格/价比
        self.type = type                    # 套利类型(自定义)
        self.snapshot = {}

    def update_leg1(self,grid):
        """
        添加腿1
        :param grid:
        :return:
        """
        if isinstance(grid, CtaGrid):
            self.leg1 = grid
        else:
            print(u'leg1 不是CtaGrid类型')

    def update_leg2(self, grid):
        """
        添加腿2
        :param grid:
        :return:
        """
        if isinstance(grid, CtaGrid):
            self.leg2 = grid
        else:
            print(u'leg2 不是CtaGrid类型')

    def toJson(self):
        j = OrderedDict()

        j['id'] = self.id
        j['direction'] = self.direction
        j['openPrices'] = self.openPrice
        j['closePrice'] = self.closePrice
        j['stopPrice']  = self.stopPrice
        j['type'] = self.type
        j['snapshot'] = self.snapshot  # 切片数据

        try:
            if self.leg1 is not None:
                j['leg1'] = self.leg1.toJson()

            if self.leg2 is not None:
                j['leg2'] = self.leg2.toJson()
        except Exception as ex:
            print(u'Arbitrage Grid toJson exception:{} {}'.format(str(ex), traceback.format_exc()),file=sys.stderr)

        return j

    def fromJson(self,j):
        if 'id' in j:
            self.id = j.get('id')
        self.direction = j.get('direction',EMPTY_STRING)
        self.openPrice = j.get('openPrice',EMPTY_FLOAT)
        self.closePrice = j.get('closePrice',EMPTY_FLOAT)
        self.stopPrice = j.get('stopPrice',EMPTY_FLOAT)
        self.type = j.get('type',EMPTY_STRING)
        self.snapshot = j.get('snapshot',{})

        if 'leg1' in j:
            if self.leg1 is None:
                self.leg1 = CtaGrid(direction=EMPTY_STRING,openprice=EMPTY_FLOAT,closeprice=EMPTY_FLOAT)
            self.leg1.fromJson(j.get('leg1'))

        if 'leg2' in j:
            if self.leg2 is None:
                self.leg2 = CtaGrid(direction=EMPTY_STRING,openprice=EMPTY_FLOAT,closeprice=EMPTY_FLOAT)
            self.leg2.fromJson(j.get('leg2'))


class ArbitrageTrade(object):
    """
    套利交易网格,仅用于持久化记录价差/价比/跨市场/期现套利等
    它包含正套网格/反套网格两个队列
    """

    def __init__(self, strategy, leg1_settings, leg2_settings):
        """
        构造函数
        :param strategy: 上层调用策略
        """
        self.strategy = strategy
        # 交易合约
        self.leg1_symbol = leg1_settings.get('vtSymbol', EMPTY_STRING)
        self.leg2_symbol = leg2_settings.get('vtSymbol', EMPTY_STRING)

        # 交易合约的杠杆比率
        self.leg1_size = leg1_settings.get('size', 1)
        self.leg2_size = leg2_settings.get('size', 1)

        # 正套队列
        self.long_list = []

        # 反套队列
        self.short_list = []

    def writeCtaLog(self, log):
        """
        写入日志
        :param log:
        :return:
        """
        if self.strategy and hasattr(self.strategy,'writeCtaLog'):
            self.strategy.writeCtaLog(log)
        else:
            print(log)

    def writeCtaError(self, log):
        """
        写入错误日志
        :param log:
        :return:
        """
        if self.strategy and hasattr(self.strategy, 'writeCtaError'):
            self.strategy.writeCtaError(log)
        else:
            print(log,file=sys.stderr)

    def toJson(self):
        """
        => json object
        :return:
        """
        j = OrderedDict()

        j['leg1_symbol'] = self.leg1_symbol
        j['leg1_size'] = self.leg1_size
        j['long_list'] = [g.toJson() for g in self.long_list]

        j['leg2_symbol'] = self.leg2_symbol
        j['leg2_size'] = self.leg2_size
        j['short_list'] = [g.toJson() for g in self.short_list]
        return j

    def fromJson(self,j):
        """
        从Json格式恢复数据
        :param j:
        :return:
        """
        self.writeCtaLog(u'数据将从Json恢复')
        self.leg1_symbol = j.get('leg1_symbol',EMPTY_STRING)
        self.leg2_symbol = j.get('leg2_symbol',EMPTY_STRING)

        self.leg1_size = j.get('leg1_size',1)
        self.leg2_size = j.get('leg2_size',1)

        self.long_list = []
        for long_json in j.get('long_list',[]):
            g = ArbitrageGrid(direction=ARBITRAGE_LONG,openprice=long_json.get('openPrice',EMPTY_FLOAT),closeprice=long_json.get('closePrice',EMPTY_FLOAT))
            g.fromJson(long_json)
            self.long_list.append(g)

        self.short_list = []
        for short_json in j.get('short_list', []):
            g = ArbitrageGrid(direction=ARBITRAGE_SHORT, openprice=short_json.get('openPrice', EMPTY_FLOAT),
                              closeprice=short_json.get('closePrice', EMPTY_FLOAT))
            g.fromJson(short_json)
            self.short_list.append(g)

        self.writeCtaLog(u'数据恢复完毕')

    def get_data_folder(self):
        """获取数据目录"""
        # 工作目录
        currentFolder = os.path.abspath(os.path.join(os.getcwd(), u'data'))
        if os.path.isdir(currentFolder):
            # 如果工作目录下，存在data子目录，就使用data子目录
            return currentFolder
        else:
            # 否则，使用缺省保存目录 vnpy/trader/app/ctaStrategy/data
            currentFolder = os.path.abspath(os.path.join(os.path.dirname(__file__), u'data'))
            if os.path.exists(currentFolder):
                if os.path.isdir(currentFolder):
                    return currentFolder
                else:
                    return os.path.dirname(__file__)
            else:
                os.mkdir(currentFolder)
                return currentFolder

    def save(self,db=EMPTY_STRING):
        """
        持久化到json文件
        :return:
        """
        if not self.strategy:
            self.writeCtaError(u'策略对象为空，不能保存')
            return

        json_file = os.path.abspath(
            os.path.join(self.get_data_folder(), u'{}_AGrids.json'.format(self.strategy.name)))

        try:
            json_data = self.toJson()

            with open(json_file, 'w') as f:
                data = json.dumps(json_data, indent=4)
                f.write(data)

        except IOError as ex:
            self.writeCtaError(u'写入AGrids文件{}出错,ex:{}'.format(json_file, str(ex)))

    def load(self,db=EMPTY_STRING):
        """
        数据从Json文件加载
        :return:
        """
        if not self.strategy:
            self.writeCtaError(u'策略对象为空，不能加载')
            return

        json_file = os.path.abspath(os.path.join(self.get_data_folder(), u'{}_AGrids.json'.format(self.strategy.name)))

        json_data = {}
        if os.path.exists(json_file):
            try:
                with open(json_file, 'r', encoding='utf8') as f:
                    # 解析json文件
                    json_data = json.load(f)
            except IOError as ex:
                self.writeCtaError(u'读取AGrids文件{}出错,ex:{}'.format(json_file, str(ex)))
                json_data = {}

        # 从持久化文件恢复数据
        self.fromJson(json_data)

    def addGrid(self,grid):
        """
        添加正套/反套网格
        :param grid:
        :return:
        """
        if not isinstance(grid,ArbitrageGrid):
            self.writeCtaError(u'添加网格不是套利网格ArbitrageGrid类型')
            return

        if grid.direction == ARBITRAGE_LONG:
            if grid.id in [g.id for g in self.long_list]:
                self.writeCtaError('添加{}网格 id{}已存在，不能添加'.format(ARBITRAGE_LONG, grid.id))
                return
            self.long_list.append(grid)
            return

        if grid.direction == ARBITRAGE_SHORT:
            if grid.id in [g.id for g in self.short_list]:
                self.writeCtaError(u'添加{}网格 id{}已存在，不能添加'.format(ARBITRAGE_SHORT, grid.id))
                return
            self.short_list.append(grid)
