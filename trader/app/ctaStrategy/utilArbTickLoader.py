# encoding: UTF-8


import os
import cPickle
import csv
import logging
import pandas
import copy


from datetime import datetime, timedelta
from ctaBase import *

class UtilArbTickLoader(object):
    """一个套利tick的数据加载工具类"""
    # ----------------------------------------------------------------------
    def __init__(self, ticksFolder, symbol):
        # tick 存放的文件系统路径
        if not ticksFolder:
            self.ticksFolder = u'z:\\ticks'
        else:
            self.ticksFolder = ticksFolder

        self.symbol = symbol

    def writeCtaLog(self, content):
        """记录日志"""
        # log = str(self.dt) + ' ' + content
        # self.logList.append(log)

        # 写入本地log日志
        logging.info(content)

    def writeCtaError(self, content):
        """记录异常"""
        self.output(content)
        self.writeCtaLog(content)

    def output(self, content):
        """输出内容"""
        print str(datetime.now()) + "\t" + content

    # ----------------------------------------------------------------------

    def loadArbTicks(self, mainPath, dtDate, leg1Symbol, leg2Symbol):

        self.writeCtaLog(u'加载日期:{0}\{1}的价差tick'.format(mainPath, dtDate))
        cachefilename = u'{0}_{1}_{2}_{3}_{4}'.\
            format(self.symbol, leg1Symbol, leg2Symbol, mainPath, dtDate.strftime('%Y%m%d'))
        arbTicks = self.__loadArbTicksFromLocalCache(cachefilename)

        dt = None

        if len(arbTicks) < 1:

            leg1File = self.ticksFolder + u'\\{0}\\{1}\\{2}\\{3}\\{4}.txt' \
                .format(mainPath, dtDate.strftime('%Y%m'), self.symbol, dtDate.strftime('%m%d'), leg1Symbol)
            if not os.path.isfile(leg1File):
                self.writeCtaLog(u'{0}文件不存在'.format(leg1File))
                return []

            leg2File = self.ticksFolder + u'\\{0}\\{1}\\{2}\\{3}\\{4}.txt' \
                .format(mainPath, dtDate.strftime('%Y%m'), self.symbol, dtDate.strftime('%m%d'), leg2Symbol)
            if not os.path.isfile(leg2File):
                self.writeCtaLog(u'{0}文件不存在'.format(leg2File))
                return []

            # 先读取leg2的数据到目录，以日期时间为key
            leg2Ticks = {}

            leg2CsvReadFile = file(leg2File, 'rb')
            #reader = csv.DictReader((line.replace('\0',' ') for line in leg2CsvReadFile), delimiter=",")
            reader = csv.DictReader(leg2CsvReadFile, delimiter=",")
            self.writeCtaLog(u'加载{0}'.format(leg2File))
            for row in reader:
                tick = CtaTickData()

                tick.vtSymbol = self.symbol
                tick.symbol = self.symbol

                tick.date = dtDate.strftime('%Y%m%d')
                tick.tradingDay = tick.date
                tick.time = row['Time']

                try:
                    tick.datetime = datetime.strptime(tick.date + ' ' + tick.time, '%Y%m%d %H:%M:%S.%f')
                except Exception as ex:
                    self.writeCtaError(u'日期转换错误:{0},{1}:{2}'.format(tick.date + ' ' + tick.time, Exception, ex))
                    continue

                # 修正毫秒
                if tick.datetime.replace(microsecond = 0) == dt:
                    # 与上一个tick的时间（去除毫秒后）相同,修改为500毫秒
                    tick.datetime=tick.datetime.replace(microsecond = 500)
                    tick.time = tick.datetime.strftime('%H:%M:%S.%f')

                else:
                    tick.datetime = tick.datetime.replace(microsecond=0)
                    tick.time = tick.datetime.strftime('%H:%M:%S.%f')

                dt = tick.datetime

                tick.lastPrice = float(row['LastPrice'])
                tick.volume = int(float(row['LVolume']))
                tick.bidPrice1 = float(row['BidPrice'])  # 叫买价（价格低）
                tick.bidVolume1 = int(float(row['BidVolume']))
                tick.askPrice1 = float(row['AskPrice'])  # 叫卖价（价格高）
                tick.askVolume1 = int(float(row['AskVolume']))

                # 排除涨停/跌停的数据
                if (tick.bidPrice1 == float('1.79769E308') and tick.bidVolume1 == 0) \
                    or (tick.askPrice1 == float('1.79769E308') and tick.askVolume1 == 0):
                    continue

                dtStr = tick.date + ' ' + tick.time
                if dtStr in leg2Ticks:
                    self.writeCtaError(u'日内数据重复，异常,数据时间为:{0}'.format(dtStr))
                else:
                    leg2Ticks[dtStr] = tick

            leg1CsvReadFile = file(leg1File, 'rb')
            #reader = csv.DictReader((line.replace('\0',' ') for line in leg1CsvReadFile), delimiter=",")
            reader = csv.DictReader(leg1CsvReadFile, delimiter=",")
            self.writeCtaLog(u'加载{0}'.format(leg1File))

            dt = None
            for row in reader:

                arbTick = CtaTickData()

                arbTick.date = dtDate.strftime('%Y%m%d')
                arbTick.time = row['Time']
                try:
                    arbTick.datetime = datetime.strptime(arbTick.date + ' ' + arbTick.time, '%Y%m%d %H:%M:%S.%f')
                except Exception as ex:
                    self.writeCtaError(u'日期转换错误:{0},{1}:{2}'.format(arbTick.date + ' ' + arbTick.time, Exception, ex))
                    continue

                # 修正毫秒
                if arbTick.datetime.replace(microsecond=0) == dt:
                    # 与上一个tick的时间（去除毫秒后）相同,修改为500毫秒
                    arbTick.datetime = arbTick.datetime.replace(microsecond=500)
                    arbTick.time = arbTick.datetime.strftime('%H:%M:%S.%f')

                else:
                    arbTick.datetime = arbTick.datetime.replace(microsecond=0)
                    arbTick.time = arbTick.datetime.strftime('%H:%M:%S.%f')

                dt = arbTick.datetime
                dtStr = ' '.join([arbTick.date, arbTick.time])

                if dtStr in leg2Ticks:
                    leg2Tick = leg2Ticks[dtStr]

                    arbTick.vtSymbol = self.symbol
                    arbTick.symbol = self.symbol

                    arbTick.lastPrice = EMPTY_FLOAT
                    arbTick.volume = EMPTY_INT

                    leg1AskPrice1 = float(row['AskPrice'])
                    leg1AskVolume1 = int(float(row['AskVolume']))

                    leg1BidPrice1 = float(row['BidPrice'])
                    leg1BidVolume1 = int(float(row['BidVolume']))

                    # 排除涨停/跌停的数据
                    if ((leg1AskPrice1 == float('1.79769E308') or leg1AskPrice1 == 0) and leg1AskVolume1 == 0) \
                            or ((leg1BidPrice1 == float('1.79769E308') or leg1BidPrice1 == 0) and leg1BidVolume1 == 0):
                        continue

                    # 叫卖价差=leg1.askPrice1 - leg2.bidPrice1，volume为两者最小
                    arbTick.askPrice1 = leg1AskPrice1 - leg2Tick.bidPrice1
                    arbTick.askVolume1 = min(leg1AskVolume1, leg2Tick.bidVolume1)

                    # 叫买价差=leg1.bidPrice1 - leg2.askPrice1，volume为两者最小
                    arbTick.bidPrice1 = leg1BidPrice1 - leg2Tick.askPrice1
                    arbTick.bidVolume1 = min(leg1BidVolume1, leg2Tick.askVolume1)

                    arbTicks.append(arbTick)

                    del leg2Ticks[dtStr]

            # 保存到历史目录
            if len(arbTicks) > 0:
                self.__saveArbTicksToLocalCache(cachefilename, arbTicks)

        return arbTicks

    def __loadArbTicksFromLocalCache(self, filename):
        """从本地缓存中，加载数据"""
        # 运行路径下cache子目录
        cacheFolder = os.getcwd() + '/cache'

        # cache文件
        cacheFile = u'{0}/{1}.pickle'. \
            format(cacheFolder, filename)

        if not os.path.isfile(cacheFile):
            return []
        else:
            # 从cache文件加载
            cache = open(cacheFile, mode='r')
            l = cPickle.load(cache)
            cache.close()
            return l

    def __saveArbTicksToLocalCache(self, filename, arbticks):
        """保存价差tick到本地缓存目录"""
        # 运行路径下cache子目录
        cacheFolder = os.getcwd() + '/cache'

        # 创建cache子目录
        if not os.path.isdir(cacheFolder):
            os.mkdir(cacheFolder)

        # cache 文件名
        cacheFile = u'{0}/{1}.pickle'. \
            format(cacheFolder, filename)

        # 重复存在 返回
        if os.path.isfile(cacheFile):
            return False

        else:
            # 写入cache文件
            cache = open(cacheFile, mode='w')
            cPickle.dump(arbticks, cache)
            cache.close()
            return True

    def convert_to_dataframe(self, ticklist):
        """转换为dataframe格式"""
        variables = ['date', 'time', 'askPrice1', 'askVolume1', 'bidPrice1', 'bidVolume1']
        dataframe = pandas.DataFrame([[getattr(i, j) for j in variables] for i in ticklist], columns=variables)
        return dataframe

    def __saveArbTicksToLocalCsv(self, filename, df):
        """保存为本地csv文件"""
        # 运行路径下cache子目录
        cacheFolder = os.getcwd() + '/cache'

        # 创建cache子目录
        if not os.path.isdir(cacheFolder):
            os.mkdir(cacheFolder)

        # cache 文件名
        cacheFile = u'{0}/{1}.csv'. \
            format(cacheFolder, filename)

        # 重复存在 返回
        if os.path.isfile(cacheFile):
            return False
        df.to_csv(cacheFile, index=False)

    def __loadArbTicksFromLocalCsv(self ,filename):
        """从本地缓存csv中，加载数据"""
        # 运行路径下cache子目录
        cacheFolder = os.getcwd() + '/cache'

        # cache文件
        cacheFile = u'{0}/{1}.csv'. \
            format(cacheFolder, filename)

        if not os.path.isfile(cacheFile):
            return None
        else:
            # 从cache文件加载
            df = pandas.read_csv(cacheFile)
            return df

    def loadDataFrame(self, mainPath, dtDate, leg1Symbol, leg2Symbol):

        self.writeCtaLog(u'加载日期:{0}\{1}的价差tick dataframe'.format(mainPath, dtDate))
        cachefilename = u'{0}_{1}_{2}_{3}_{4}'. \
            format(self.symbol, leg1Symbol, leg2Symbol, mainPath, dtDate.strftime('%Y%m%d'))
        df = self.__loadArbTicksFromLocalCsv(cachefilename)

        if df is None:
            ticks = self.loadArbTicks(mainPath, dtDate, leg1Symbol, leg2Symbol)
            if len(ticks) >0:
                df = self.convert_to_dataframe(ticks)
                self.__saveArbTicksToLocalCsv(cachefilename,df)

        return df

    def loadDataFrame2(self, mainPath, beginDate, endDate, leg1Symbol, leg2Symbol):

        dayIntervals = (endDate- beginDate).days

        if dayIntervals < 1:
            self.writeCtaLog(u'时间不足')
            return None

        df = None

        cachefilename = u'{0}_{1}_{2}_{3}_{4}'. \
            format(self.symbol, leg1Symbol, leg2Symbol, beginDate.strftime('%Y%m%d'), endDate.strftime('%Y%m%d'))
        df = self.__loadArbTicksFromLocalCsv(cachefilename)

        if df is not None:
            return df

        for i in range(0, dayIntervals):
            getDate = beginDate + timedelta(days=i)

            self.output(u'取数据日期:{0}'.format(getDate))

            df1,df2 =None,None

            # 白天数据
            df1 = self.loadDataFrame(mainPath, getDate, leg1Symbol, leg2Symbol)

            if df1 is not None and df is None:
                df = copy.copy(df1)
                self.output(u'数据{0}行'.format(len(df)))
            elif df1 is not None and df is not None:
                df = pandas.concat([df,df1], ignore_index=True)
                self.output(u'数据增加{0}行,共{1}行'.format(len(df1),len(df)))

            # 夜盘数据
            df2 = self.loadDataFrame(mainPath + '_night', getDate, leg1Symbol, leg2Symbol)
            if df2 is not None and df is None:
                df = copy.copy(df2)
                self.output(u'数据{0}行'.format(len(df)))
            elif df2 is not None and df is not None:
                df =  pandas.concat([df,df2], ignore_index=True)
                self.output(u'数据增加{0}行,共{1}行'.format(len(df2), len(df)))

        self.__saveArbTicksToLocalCsv(cachefilename, df)

        return df


if __name__ == '__main__':

    loader = UtilArbTickLoader(ticksFolder='z://ticks', symbol='RB')

    """只取tick对象队列"""
    #ticks = loader.loadArbTicks(mainPath='SHFE',dtDate=datetime.strptime('20140801', '%Y%m%d'),
    #                            leg1Symbol='RB1501', leg2Symbol='RB1505')
    #df = loader.convert_to_dataframe(ticks)

    """取单日dataframe"""
    #df = loader.loadDataFrame(mainPath='SHFE',dtDate=datetime.strptime('20140801', '%Y%m%d'),
    #                            leg1Symbol='RB1501', leg2Symbol='RB1505')


    """取一段日期内的dataframe"""
    df = loader.loadDataFrame2(mainPath='SHFE', beginDate=datetime.strptime('20140801', '%Y%m%d'),
                                endDate=datetime.strptime('20141030', '%Y%m%d'),
                                leg1Symbol='RB1501', leg2Symbol='RB1505')


    #print df
