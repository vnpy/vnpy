# encoding: UTF-8

from ctaBase import *
from vtConstant import *
import json
import os
from datetime import datetime

DEBUGCTALOG = True

"""
    网格交易，用于套利单
    作者：李来佳，QQ/Wechat:28888502
ChangeLog:
    0713,修改closeGrid，增加volume字段，关闭网格时，根据价格和交易量进行双重匹配.
    0715,增加保存json和重启后加载本地json文件
"""

class CtaGrid(object):
    """网格类
    它是网格交易的最小单元
    包括交易方向，开仓价格，平仓价格，止损价格，开仓状态，平仓状态

    """

    def __init__(self, direction, openprice, closeprice, stopprice=EMPTY_FLOAT, volume=1):

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

    def toJson(self):
        """输出JSON"""

        j = {}
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

class CtaGridTrade(object):
    """网格交易类
    包括两个方向的网格队列，
    """

    def __init__(self, strategy, maxlots=5, height=2, win=2, vol=1):
        """初始化
        maxlots,最大网格数
        height，网格高度（绝对值，包含minDiff）
        win，盈利数（包含minDiff）
        vol，网格开仓数
        """

        self.strategy = strategy

        self.jsonName = self.strategy.name  #策略名称

        self.maxLots = maxlots      # 缺省网格数量
        self.gridHeight = height    # 最小网格高度
        self.gridWin = win          # 最小止盈高度

        self.volume = vol           # 每次网格开仓数量
        self.volumeList = [1, 1, 1, 1, 1, 1, 1, 1, 1, 1]    # 梯级开仓数量比例

        self.upGrids = []           # 上网格列表，专门做空
        self.dnGrids = []           # 下网格列表，专门做多

        self.avg_up_open_price = EMPTY_FLOAT        # 上网格开仓均价
        self.avg_dn_open_price = EMPTY_FLOAT        # 下网格开仓均价

    def getVolume(self, gridIndex=EMPTY_INT):
        """获取网格索引对应的开仓数量比例"""

        if gridIndex >= len(self.volumeList) or gridIndex < 0:
            return 1
        rate = self.volumeList[gridIndex]

        if rate == 0:
            return 1
        else:
            return rate

    def initGrid(self, upline=EMPTY_FLOAT, dnline=EMPTY_FLOAT):
        """初始化网格队列
        upline，上支撑线
        dnline，下阻力线
        """
        self.writeCtaLog(u'初始化网格队列，upline:{0},dnline:{1}'.format(upline, dnline))
        # 初始化上网格列表
        if len(self.upGrids) == 0:

            self.upGrids = self.load(direction= DIRECTION_SHORT)

            if len(self.upGrids) >0:
                self.writeCtaLog(u'上网格从文件加载完成')
            else:
                # 做空，开仓价为上阻力线+网格高度*i，平仓价为开仓价-止盈高度，开仓数量为缺省
                for i in range(0, self.maxLots, 1):
                    grid = CtaGrid(direction=DIRECTION_SHORT,
                                   openprice=upline+self.gridHeight*i,
                                   closeprice=upline+self.gridHeight*i-self.gridWin,
                                   volume=self.volume*self.getVolume(i))
                    self.upGrids.append(grid)

                self.writeCtaLog(u'上网格{0}~{1}初始化完成'.format(upline,upline+self.gridHeight*self.maxLots))
                self.save(direction=DIRECTION_SHORT)


        # 初始化下网格列表
        if len(self.dnGrids) == 0:

            self.dnGrids = self.load(direction= DIRECTION_LONG)

            if len(self.dnGrids) >0:
                self.writeCtaLog(u'下网格从文件加载完成')
            else:

                for i in range(0, self.maxLots, 1):

                    # 做多，开仓价为下阻力线-网格高度*i，平仓价为开仓价+止盈高度，开仓数量为缺省
                    grid = CtaGrid(direction=DIRECTION_LONG,
                                   openprice=dnline - self.gridHeight * i,
                                   closeprice=dnline - self.gridHeight * i + self.gridWin,
                                   volume=self.volume*self.getVolume(i))
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
                # 待平仓
                if grid.openStatus :

                    if grid.tradedVolume == EMPTY_INT:
                        pendingCloseList = pendingCloseList + u'[{0}->{1},v:{2}];'\
                            .format(grid.openPrice, grid.closePrice, grid.volume)
                    else:
                        pendingCloseList = pendingCloseList + u'[{0}->{1},v:{2}/{3}];'\
                            .format(grid.openPrice, grid.closePrice, grid.volume, grid.tradedVolume)

                # 待开仓成交
                elif not grid.openStatus and grid.orderStatus:
                    if grid.tradedVolume == EMPTY_INT:
                        pendingOpenList = pendingOpenList + u'[{0},v:{1}];'.format(grid.openPrice, grid.volume)
                    else:
                        pendingOpenList = pendingOpenList + u'[{0},v:{1}/{2}];'\
                            .format(grid.openPrice, grid.volume, grid.tradedVolume)

                # 等待挂单
                else:
                    deactiveList = deactiveList + u'[{0}];'.format(grid.openPrice)


            return u'多:待平:{0};开:{1};待:{2}'.format(pendingCloseList,pendingOpenList,deactiveList)

        if direction == DIRECTION_SHORT:
            for grid in self.upGrids:
                # 待平仓
                if grid.openStatus:
                    if grid.tradedVolume == EMPTY_INT:
                        pendingCloseList = pendingCloseList + u'[{0}->{1},v:{2}];'\
                            .format(grid.openPrice, grid.closePrice, grid.volume)
                    else:
                        pendingCloseList = pendingCloseList + u'[{0}->{1},v:{2}/{3}];'\
                            .format(grid.openPrice, grid.closePrice, grid.volume, grid.tradedVolume)

                # 待开仓成交
                elif not grid.openStatus and grid.orderStatus:
                    if grid.tradedVolume == EMPTY_INT:
                        pendingOpenList = pendingOpenList + u'[{0},v:{1}];'.format(grid.openPrice, grid.volume)
                    else:
                        pendingOpenList = pendingOpenList + u'[{0},v:{1}/{2}];'\
                            .format(grid.openPrice, grid.volume, grid.tradedVolume)

                # 等待挂单
                else:
                    deactiveList = deactiveList + u'[{0}];'.format(grid.openPrice)

            return u'空:待平:{0};开:{1};待:{2}'.format(pendingCloseList,pendingOpenList,deactiveList)

    def getGrids(self, direction, ordered=False, opened=False, closed=False, begin=EMPTY_FLOAT, end=EMPTY_FLOAT):
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
            if begin == EMPTY_FLOAT: begin = 99999
            if end == EMPTY_FLOAT: end = - 99999
            grids = [x for x in self.dnGrids
                     if x.orderStatus == ordered
                     and x.openStatus == opened
                     and x.closeStatus == closed
                     and x.openPrice <= begin
                     and x.openPrice >= end]

            return grids

        # 状态一致，开仓价格小于最高价格
        if direction == DIRECTION_SHORT:
            if begin == EMPTY_FLOAT: begin = -99999
            if end == EMPTY_FLOAT: end = 99999
            grids = [x for x in self.upGrids
                     if x.orderStatus == ordered
                     and x.openStatus == opened
                     and x.closeStatus == closed
                     and x.openPrice >= begin
                     and x.openPrice <= end]

            return grids

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

        self.writeCtaLog(u'异常，找不到网格[{0},{1},{2},{3},{4}]'.format(direction, openPrice, closePrice, orderRef, t))
        return None

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


    def removeGrids(self, direction, priceline):
        """清除网格"""
        if direction == DIRECTION_LONG:
            for x in self.dnGrids[:]:
                if x.openPrice > priceline and not x.orderStatus and not x.openStatus and not x.closeStatus:
                    self.writeCtaLog(u'清除下网格[open={0}]'.format(x.openPrice))
                    self.dnGrids.remove(x)

        if direction == DIRECTION_SHORT:
            for x in self.upGrids[:]:
                if x.openPrice < priceline and not x.orderStatus and not x.openStatus and not x.closeStatus:
                    self.writeCtaLog(u'清除上网格[open={0}]'.format(x.openPrice))
                    self.upGrids.remove(x)

    def rebuildGrids(self, direction, upline=EMPTY_FLOAT, dnline=EMPTY_FLOAT, midline=EMPTY_FLOAT):
        """重新拉网
        清除未挂单的网格，
        在上轨/下轨位置重新挂单
        """
        self.writeCtaLog(u'重新拉网:upline:{0},dnline:{1}'.format(upline, dnline))

        if direction == DIRECTION_LONG:
            minPriceInOrder = midline
            removePrices = []
            # 移除未挂单的下网格
            for x in self.dnGrids[:]:
                if not x.orderStatus and not x.openStatus and not x.closeStatus:
                    removePrices.append(x.openPrice)
                    self.dnGrids.remove(x)
                else:
                    self.writeCtaLog(u'保留网格[open={0}]'.format(x.openPrice))
                    if x.openPrice < minPriceInOrder :
                        minPriceInOrder = x.openPrice

            self.writeCtaLog(u'清除下网格[{0}]'.format(removePrices))

            # 需要重建的剩余网格数量
            remainLots = len(self.dnGrids)
            lots = self.maxLots - remainLots

            dnline = min(dnline, minPriceInOrder-self.gridHeight)
            self.writeCtaLog(u'需要重建的网格数量:{0},起点:{1}'.format(lots, dnline))

            if lots > 0:

                for i in range(0, lots, 1):
                    # 做多，开仓价为下阻力线-网格高度*i，平仓价为开仓价+止盈高度，开仓数量为缺省
                    grid = CtaGrid(direction=DIRECTION_LONG,
                                   openprice=dnline - self.gridHeight * i,
                                   closeprice=dnline - self.gridHeight * i + self.gridWin,
                                   volume=self.volume*self.getVolume(remainLots+i))

                    self.dnGrids.append(grid)
                self.writeCtaLog(u'重新拉下网格:[{0}~{1}]'.format(dnline, dnline-self.gridHeight * lots))

        if direction == DIRECTION_SHORT:
            maxPriceInOrder = midline
            removePrices = []
            # 移除未挂单的上网格
            for x in self.upGrids[:]:
                if not x.orderStatus and not x.openStatus and not x.closeStatus:
                    removePrices.append(x.openPrice)
                    self.upGrids.remove(x)
                else:
                    self.writeCtaLog(u'保留网格[open={0}]'.format(x.openPrice))
                    if x.openPrice > maxPriceInOrder :
                        maxPriceInOrder = x.openPrice

            self.writeCtaLog(u'清除上网格[{0}]'.format(removePrices))

            # 需要重建的剩余网格数量
            remainLots = len(self.upGrids)
            lots = self.maxLots - remainLots
            upline = max(upline, maxPriceInOrder+self.gridHeight)
            self.writeCtaLog(u'需要重建的网格数量:{0},起点:{1}'.format(lots, upline))

            if lots > 0:
                # 做空，开仓价为上阻力线+网格高度*i，平仓价为开仓价-止盈高度，开仓数量为缺省
                for i in range(0, lots, 1):
                    grid = CtaGrid(direction=DIRECTION_SHORT,
                                   openprice=upline+self.gridHeight*i,
                                   closeprice=upline+self.gridHeight*i-self.gridWin,
                                   volume=self.volume*self.getVolume(remainLots+i))
                    self.upGrids.append(grid)

                self.writeCtaLog(u'重新拉上网格:[{0}~{1}]'.format(upline, upline+self.gridHeight * lots))

    def recount_avg_open_price(self):
        """计算网格的平均开仓价"""
        up_open_list = [ x for x in self.upGrids if x.openStatus]

        total_price = EMPTY_FLOAT
        total_volume = EMPTY_INT
        for x in up_open_list:
            total_price += x.openPrice*x.volume
            total_volume += x.volume

        if total_volume > 0:
            self.avg_up_open_price = total_price/total_volume

        total_price = EMPTY_FLOAT
        total_volume = EMPTY_INT

        dn_open_list = [x for x in self.dnGrids if x.openStatus]
        for x in dn_open_list:
            total_price += x.openPrice*x.volume
            total_volume += x.volume

        if total_volume > 0:
            self.avg_dn_open_price = total_price/total_volume

    def save(self, direction):
        """保存网格至本地Json文件"""
        path = os.path.abspath(os.path.dirname(__file__))

        # 保存上网格列表
        if len(self.upGrids) > 0 and direction == DIRECTION_SHORT:
            jsonFileName = os.path.join(path, u'data', u'{0}_upGrids.json'.format(self.jsonName))

            l = []
            for grid in self.upGrids:
                l.append(grid.toJson())

            with open(jsonFileName, 'w') as f:

                jsonL = json.dumps(l, indent=4)
                f.write(jsonL)

            #self.writeCtaLog(u'上网格保存文件{0}完成'.format(jsonFileName))

        # 保存上网格列表
        if len(self.dnGrids) > 0 and direction == DIRECTION_LONG:
            jsonFileName = os.path.join(path, u'data', u'{0}_dnGrids.json'.format(self.jsonName))

            l = []
            for grid in self.dnGrids:
                l.append(grid.toJson())

            with open(jsonFileName, 'w') as f:

                jsonL = json.dumps(l, indent=4)
                f.write(jsonL)

            #self.writeCtaLog(u'下网格保存文件{0}完成'.format(jsonFileName))

    def load(self, direction):
        """加载本地Json至网格"""

        path = os.path.abspath(os.path.dirname(__file__))

        if direction == DIRECTION_SHORT:
            jsonFileName = os.path.join(path, u'data', u'{0}_upGrids.json'.format(self.jsonName))
            self.writeCtaLog(u'开始加载上网格文件{0}'.format(jsonFileName))
        if direction == DIRECTION_LONG:
            jsonFileName = os.path.join(path, u'data', u'{0}_dnGrids.json'.format(self.jsonName))
            self.writeCtaLog(u'开始加载上网格文件{0}'.format(jsonFileName))

        if not os.path.isfile(jsonFileName):
            self.writeCtaLog(u'网格保存文件{0}不存在'.format(jsonFileName))
            return []

        try:
            f = file(jsonFileName)
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

                self.writeCtaLog(grid.toStr())

                grids.append(grid)

        else:
            self.writeCtaLog(u'解析网格出错，设置为空列表')

        f.close()
        return grids






