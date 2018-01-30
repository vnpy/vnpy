# encoding: UTF-8
# 定义Tick数据的格式
# 默认空值
EMPTY_STRING = ''
EMPTY_UNICODE = u''
EMPTY_INT = 0
EMPTY_FLOAT = 0.0


class CtaTickData(object):
    """Tick数据"""

    # ----------------------------------------------------------------------
    def __init__(self):
        """Constructor"""
        self.vtSymbol = EMPTY_STRING  # vt系统代码 CF705
        self.symbol = EMPTY_STRING  # 合约代码   CF1705
        self.exchange = EMPTY_STRING  # 交易所代码

        # 成交数据
        self.lastPrice = EMPTY_FLOAT  # 最新成交价
        self.volume = EMPTY_INT  # 最新成交量
        self.preOpenInterest = EMPTY_INT  # 昨持仓量
        self.openInterest = EMPTY_INT  # 持仓量

        self.upperLimit = EMPTY_FLOAT  # 涨停价
        self.lowerLimit = EMPTY_FLOAT  # 跌停价

        # tick的时间
        self.tradingDay = EMPTY_STRING  # 交易日期
        self.date = EMPTY_STRING  # 日期
        self.time = EMPTY_STRING  # 时间
        self.datetime = None  # python的datetime时间对象

        # 五档行情
        self.bidPrice1 = EMPTY_FLOAT
        self.bidPrice2 = EMPTY_FLOAT
        self.bidPrice3 = EMPTY_FLOAT
        self.bidPrice4 = EMPTY_FLOAT
        self.bidPrice5 = EMPTY_FLOAT

        self.askPrice1 = EMPTY_FLOAT
        self.askPrice2 = EMPTY_FLOAT
        self.askPrice3 = EMPTY_FLOAT
        self.askPrice4 = EMPTY_FLOAT
        self.askPrice5 = EMPTY_FLOAT

        self.bidVolume1 = EMPTY_INT
        self.bidVolume2 = EMPTY_INT
        self.bidVolume3 = EMPTY_INT
        self.bidVolume4 = EMPTY_INT
        self.bidVolume5 = EMPTY_INT

        self.askVolume1 = EMPTY_INT
        self.askVolume2 = EMPTY_INT
        self.askVolume3 = EMPTY_INT
        self.askVolume4 = EMPTY_INT
        self.askVolume5 = EMPTY_INT


from pymongo import MongoClient

mongodb_host = '192.168.0.202'
mongodb_port = 27017
mongodb_user = 'vnpy'
mongodb_pwd = 'vnpy'


class mongodb_client(object):
    def __init__(self):
        self.dbClient = None

    # ----------------------------------------------------------------------
    def writeLog(self, content):
        """日志"""
        print( content)

    # ----------------------------------------------------------------------
    def dbConnect(self):
        """连接MongoDB数据库"""
        if not self.dbClient:

            try:
                # 设置MongoDB操作的超时时间为0.5秒
                self.dbClient = MongoClient(mongodb_host, mongodb_port, serverSelectionTimeoutMS=500)

                # 这里使用了ticks这个库来验证用户账号和密码
                self.dbClient.ticks.authenticate(mongodb_user, mongodb_pwd, mechanism='SCRAM-SHA-1')

                # 调用server_info查询服务器状态，防止服务器异常并未连接成功
                self.dbClient.server_info()

                self.writeLog(u'MongoDB连接成功')
            except Exception as ex:
                self.writeLog(u'MongoDB连接失败{0}'.format(ex))

    # ----------------------------------------------------------------------
    def dbInsert(self, dbName, collectionName, d):
        """向MongoDB中插入数据，d是具体数据"""
        if self.dbClient:
            db = self.dbClient[dbName]
            collection = db[collectionName]
            collection.insert(d)

    # ----------------------------------------------------------------------
    def dbInsertMany(self, dbName, collectionName, dataList):
        """向MongoDB中插入Multi数据，dataList是具体数据List"""
        if self.dbClient:
            db = self.dbClient[dbName]
            collection = db.getCollection(collectionName)
            collection.insertMany(dataList)\

    # ----------------------------------------------------------------------
    def dbQuery(self, dbName, collectionName, d):
        """从MongoDB中读取数据，d是查询要求，返回的是数据库查询的指针"""
        if self.dbClient:
            db = self.dbClient[dbName]
            collection = db[collectionName]
            cursor = collection.find(d)
            return cursor
        else:
            return None


from datetime import datetime
from collections import OrderedDict
import os
import pandas as pd


def load_ticks_from_csv_file(file_name, symbol, trading_day):
    """从csv tick文件中UnicodeDictReader读取tick
    file_name,文件全路径
    symbol，合约代码，RB01, RBMI 等
    trading_day,交易日字符串
    """
    # 先读取数据到Dict，以日期时间为key
    ticks = OrderedDict()

    if not os.path.isfile(file_name):
        print( u'{0}文件不存在'.format(file_name))
        return ticks
    dt = None

    start_time = datetime.now()
    df = pd.read_csv(file_name, encoding='gbk', parse_dates=False)
    df.columns = ['date', 'time', 'lastPrice', 'lastVolume', 'totalInterest', 'position',
                  'bidPrice1', 'bidVolume1', 'bidPrice2', 'bidVolume2', 'bidPrice3', 'bidVolume3',
                  'askPrice1', 'askVolume1', 'askPrice2', 'askVolume2', 'askPrice3', 'askVolume3', 'BS']
    readed_ticks = len(df)

    position = 0

    for i in range(0, len(df)):
        # 日期, 时间, 成交价, 成交量, 总量, 属性(持仓增减), B1价, B1量, B2价, B2量, B3价, B3量, S1价, S1量, S2价, S2量, S3价, S3量, BS
        # 0    1      2      3       4      5               6     7    8     9     10     11    12    13    14   15    16   17    18
        row = df.iloc[i].to_dict()
        tick = CtaTickData()

        tick.vtSymbol = symbol
        tick.symbol = symbol

        tick.date = row['date']
        tick.tradingDay = trading_day
        tick.time = row['time']

        try:
            tick.datetime = datetime.strptime(tick.date + ' ' + tick.time, '%Y-%m-%d %H:%M:%S')
        except Exception as ex:
            print( u'日期转换错误:{0},{1}:{2}'.format(tick.date + ' ' + tick.time, Exception, ex))
            continue

        tick.date = tick.datetime.strftime('%Y%m%d')
        # 修正毫秒
        if tick.datetime.replace(microsecond=0) == dt:
            # 与上一个tick的时间（去除毫秒后）相同,修改为500毫秒
            tick.datetime = tick.datetime.replace(microsecond=500)
            tick.time = tick.datetime.strftime('%H:%M:%S.%f')

        else:
            tick.datetime = tick.datetime.replace(microsecond=0)
            tick.time = tick.datetime.strftime('%H:%M:%S.%f')

        dt = tick.datetime

        tick.lastPrice = float(row['lastPrice'])
        tick.volume = int(float(row['lastVolume']))
        tick.bidPrice1 = float(row['bidPrice1'])  # 叫买价（价格低）
        tick.bidVolume1 = int(float(row['bidVolume1']))
        tick.askPrice1 = float(row['askPrice1'])  # 叫卖价（价格高）
        tick.askVolume1 = int(float(row['askVolume1']))

        tick.dayVolume = int(float(row['totalInterest']))  # 当日累计成交量

        position += int(float(row['position']))   # 持仓量
        tick.openInterest = position  # 持仓量

        dtStr = tick.date + ' ' + tick.time

        if dtStr not in ticks:
            ticks[dtStr] = tick
    if len(ticks) != readed_ticks:
        print( u'分析tick对象数量{0}与读取数据数量{1}不一致'.format(len(ticks), readed_ticks))

    print( u'读取{0},共加载{1}条数据，耗时:{2}seconds'.format(file_name, readed_ticks, str(datetime.now() - start_time)))

    return ticks

import csv

def load_ticks_from_txt_file(file_name, symbol, trading_day):
    """
    读取中金所txt 格式的tick文件
    file_name,文件全路径
    symbol，合约代码，IC1601 等
    trading_day,交易日字符串    
    返回ctatick对象dict，无内容返回空的dict
    """
    # 先读取数据到Dict，以日期时间为key
    ticks = OrderedDict()

    if not os.path.isfile(file_name):
        print( u'{0}文件不存在'.format(file_name))
        return []

    last_tick_datetime = None
    # 文件句柄
    csv_read_file = open(file_name, 'rb',encoding='utf8')

    # 通过csv模块的DictReader，一次性读取所有数据
    reader = csv.DictReader(csv_read_file, delimiter=",")

    start_time = datetime.now()
    # 逐行数据处理
    for row in reader:
        tick = CtaTickData()
        # vtSymbol：CF1705， symbol：CF1705
        tick.vtSymbol = symbol
        tick.symbol = symbol

        # 日期格式为 '20170120',交易日期，在夜盘时，交易日期为下一交易日
        tick.date = trading_day
        tick.tradingDay = tick.date
        tick.time = row['Time']

        # 转换为datetime格式
        try:
            tick.datetime = datetime.strptime(tick.date + ' ' + tick.time, '%Y%m%d %H:%M:%S.%f')
        except Exception as ex:
            # 抛弃本tick
            print( u'日期转换错误:{0},{1}:{2}'.format(tick.date + ' ' + tick.time, Exception, ex))
            continue

        # 修正毫秒
        if tick.datetime.replace(microsecond=0) == last_tick_datetime:
            # 与上一个tick的时间（去除毫秒后）相同,修改为500毫秒
            tick.datetime = tick.datetime.replace(microsecond=500)
            tick.time = tick.datetime.strftime('%H:%M:%S.%f')

        else:
            tick.datetime = tick.datetime.replace(microsecond=0)
            tick.time = tick.datetime.strftime('%H:%M:%S.%f')

        # 记录最新tick的时间
        last_tick_datetime = tick.datetime

        tick.lastPrice = float(row['LastPrice'])             # 最新价
        tick.volume = int(float(row['LVolume']))             # 成交量
        tick.bidPrice1 = float(row['BidPrice'])              # 叫买价（价格低）
        tick.bidVolume1 = int(float(row['BidVolume']))       # 叫买量
        tick.askPrice1 = float(row['AskPrice'])              # 叫卖价（价格高）
        tick.askVolume1 = int(float(row['AskVolume']))       # 叫卖量

        tick.openInterest = int(float(row['OpenInterest']))  # 持仓量
        tick.dayVolume = int(float(row['TradeVolume']))      # 当日累计成交量

        dtStr = tick.date + ' ' + tick.time
        if dtStr not in ticks:
            ticks[dtStr] = tick

    print( u'读取{0},共加载{1}条数据，耗时:{2}seconds'.format(file_name, len(ticks), str(datetime.now() - start_time)))

    return ticks

import re

def import_ticks_from_folder(folder_path):
    branch_time = datetime.now()
    for dirpath, folder_names, file_names in os.walk(folder_path):
        for file_name in file_names:
            file_path = os.path.join(dirpath, file_name)
            start_time = datetime.now()
            # 处理csb格式
            if file_name.lower().find('.csv') != -1:
                s = file_name.replace('.csv', '').split('_')
                if len(s) != 2:
                    print( u'{0} not match format'.format(file_path))
                    continue

                file_symbol = s[0]
                file_trading_day = s[1]
                # print('{0} {1}'.format(file_symbol,file_trading_day))
                if len(file_trading_day) != 8:
                    print( u'{0} trading_day not match format'.format(file_path))
                    continue
                try:
                    ticks = load_ticks_from_csv_file(file_name=file_path, symbol=file_symbol, trading_day=file_trading_day)

                    insert_list = [x.__dict__ for x in ticks.values()]
                    mc.dbInsert(dbName='ticks', collectionName=file_symbol, d=insert_list)
                    print( u'写入完成，共{0}条,耗时:{1}seconds'.format(len(insert_list), str(datetime.now() - start_time)))
                except Exception as ex:
                    print( u'{0} load ticks and insert exception'.format(file_path))
                    continue

            elif file_name.lower().find('.txt') != -1:

                symbol_name = file_name.replace('.txt', '')
                if symbol_name.lower().find('survey') != -1:
                    print( '{0} not import'.format(file_name))
                    continue
                p = re.compile(r"([A-Z]+)[0-9]+", re.I)
                short_symbol = p.match(symbol_name)
                if short_symbol is None:
                    print( '{0} not import'.format(file_name))
                    continue
                short_symbol = short_symbol.group(1)
                collection_name = short_symbol + symbol_name[-2:]
                path_list = dirpath.split('/')
                if path_list[-2] != short_symbol:
                    print( '{0} not import'.format(file_name))
                    continue

                trading_day = path_list[-4] + path_list[-1]

                #print collection_name, trading_day
                try:
                    ticks = load_ticks_from_txt_file(file_name=file_path, symbol=symbol_name, trading_day=trading_day)
                    insert_list = [x.__dict__ for x in ticks.values()]
                    mc.dbInsert(dbName='ticks', collectionName=collection_name, d=insert_list)
                    print( u'写入完成，共{0}条,耗时:{1}seconds'.format(len(insert_list), str(datetime.now() - start_time)))
                except Exception as ex:
                    print( u'{0} load ticks and insert exception'.format(file_path))
                    continue
    print( '完成 {0} ticks ,耗时:{1}seconds'.format(folder_path, str(datetime.now() - branch_time)))


mc=mongodb_client()
mc.dbConnect()

#import_ticks_from_folder('/home/ubuntu/Ticks/ZZ/2016/201612')
#import_ticks_from_folder('/home/ubuntu/Ticks/ZZ/2016/201611')
#import_ticks_from_folder('/home/ubuntu/Ticks/ZZ/2016/201610')
#import_ticks_from_folder('/home/ubuntu/Ticks/ZZ/2016/201609')
#import_ticks_from_folder('/home/ubuntu/Ticks/ZZ/2016/201608')
#import_ticks_from_folder('/home/ubuntu/Ticks/ZZ/2016/201607')
#import_ticks_from_folder('/home/ubuntu/Ticks/ZZ/2016/201606')
#import_ticks_from_folder('/home/ubuntu/Ticks/ZZ/2016/201605')
#import_ticks_from_folder('/home/ubuntu/Ticks/ZZ/2016/201604')
#import_ticks_from_folder('/home/ubuntu/Ticks/ZZ/2016/201603')
#import_ticks_from_folder('/home/ubuntu/Ticks/ZZ/2016/201602')
#import_ticks_from_folder('/home/ubuntu/Ticks/ZZ/2016/201601')
#import_ticks_from_folder('/home/ubuntu/Ticks/ZZ/2015')
#import_ticks_from_folder('/home/ubuntu/Ticks/ZZ/2014')
#import_ticks_from_folder('/home/ubuntu/Ticks/ZZ/2013')
#import_ticks_from_folder('/home/ubuntu/Ticks/ZZ/2012')
import_ticks_from_folder('/home/ubuntu/Ticks/ZZ/2011')
import_ticks_from_folder('/home/ubuntu/Ticks/ZZ/2010')