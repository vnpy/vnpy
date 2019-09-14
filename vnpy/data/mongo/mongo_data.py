# encoding: UTF-8

# Mongodb 数据服务


import sys,os,traceback

from datetime import datetime,timedelta
from pymongo import MongoClient, ASCENDING
from pymongo.errors import ConnectionFailure,AutoReconnect
from time import sleep

from vnpy.trader.vtFunction import loadMongoSetting
from vnpy.trader.setup_logger import setup_logger

class MongoData(object):
    dbClient = None
    db_has_connected = False

    def __init__(self):
        self.dbConnect()

    def dbConnect(self, force=False):
        if (self.dbClient is None or self.db_has_connected == False) or force:
            host, port, logging = loadMongoSetting()
            print('connecting to Mongo:{}:{}'.format(host, port))
            try:
                # 设置MongoDB操作的超时时间为0.5秒
                self.dbClient = MongoClient(host, port, connectTimeoutMS=500)
                # 调用server_info查询服务器状态，防止服务器异常并未连接成功
                self.dbClient.server_info()

                self.db_has_connected = True
                print('mongo db connected')

            except Exception as ex:
                self.dbClient = None
                self.db_has_connected = False
                self.writeError(u'connect to mongo {}:{} exception:{}'.format(host,port,str(ex)))

    def writeLog(self,content):
        print(content)

    def writeError(self,content):
        print(content,file=sys.stderr)

    # ----------------------------------------------------------------------
    def dbInsert(self, dbName, collectionName, d):
        """向MongoDB中插入数据，d是具体数据"""
        try:
            if self.dbClient:
                db = self.dbClient[dbName]
                collection = db[collectionName]
                collection.insert_one(d)
            else:
                self.writeError(u'db insert fail')
                if self.db_has_connected:
                    self.writeLog(u'重新尝试连接数据库')
                    self.dbConnect(force=True)

        except AutoReconnect as ex:
            self.writeLog(u'数据库连接断开重连:{}'.format(str(ex)))
            sleep(1)
        except ConnectionFailure:
            self.dbClient = None
            self.writeError(u'数据库连接断开')
            if self.db_has_connected:
                self.writeLog(u'重新尝试连接数据库')
                self.dbConnect(force=True)
        except Exception as ex:
            self.writeError(u'dbInsert exception:{}'.format(str(ex)))

    def dbInsertMany(self,dbName, collectionName, data_list,ordered=True):
        """
        向MongoDB中插入数据，data_list是具体数据 列表
        :param dbName:
        :param collectionName:
        :param data_list:
        :param ordered: 是否忽略insert error
        :return:
        """
        if not isinstance(data_list, list):
            self.writeError('data_list should be a list')
            return
        try:
            if self.dbClient:
                db = self.dbClient[dbName]
                collection = db[collectionName]
                collection.insert_many(data_list, ordered = ordered)
            else:
                self.writeError('db insert many fail')
                if self.db_has_connected:
                    self.writeLog(u'重新尝试连接数据库')
                    self.dbConnect(force=True)

        except AutoReconnect as ex:
            self.writeError(u'数据库连接断开重连:{}'.format(str(ex)))
            sleep(1)
        except ConnectionFailure:
            self.dbClient = None
            self.writeError(u'数据库连接断开')
            if self.db_has_connected:
                self.writeLog(u'重新尝试连接数据库')
                self.dbConnect(force=True)
        except Exception as ex:
            self.writeError(u'dbInsertMany exception:{}'.format(str(ex)))


    # ----------------------------------------------------------------------
    def dbQueryOne(self, dbName, collectionName, flt):
        """从MongoDB中读取数据，d是查询要求，返回的是一个结果"""
        try:
            if self.dbClient:
                db = self.dbClient[dbName]
                collection = db[collectionName]

                return collection.find_one(flt)

            else:
                self.writeLog('db query fail')
                if self.db_has_connected:
                    self.writeLog(u'重新尝试连接数据库')
                    self.dbConnect()

        except AutoReconnect as ex:
            self.writeError(u'数据库连接断开重连:{}'.format(str(ex)))
            sleep(1)
        except ConnectionFailure:
            self.dbClient = None
            self.writeError(u'数据库连接断开')
            if self.db_has_connected:
                self.writeLog(u'重新尝试连接数据库')
                self.dbConnect()
        except Exception as ex:
            self.writeError(u'dbQuery exception:{}'.format(str(ex)))

        return None

    # ----------------------------------------------------------------------
    def dbQuery(self, dbName, collectionName, d, sortKey='', sortDirection=ASCENDING):
        """从MongoDB中读取数据，d是查询要求，返回的是数据库查询的指针"""
        try:
            if self.dbClient:
                db = self.dbClient[dbName]
                collection = db[collectionName]

                if sortKey:
                    cursor = collection.find(d).sort(sortKey, sortDirection)  # 对查询出来的数据进行排序
                else:
                    cursor = collection.find(d)

                if cursor:
                    return list(cursor)
                else:
                        return []
            else:
                self.writeLog('db query fail')
                if self.db_has_connected:
                    self.writeLog(u'重新尝试连接数据库')
                    self.dbConnect()

        except AutoReconnect as ex:
            self.writeError(u'数据库连接断开重连:{}'.format(str(ex)))
            sleep(1)
        except ConnectionFailure:
            self.dbClient = None
            self.writeError(u'数据库连接断开')
            if self.db_has_connected:
                self.writeLog(u'重新尝试连接数据库')
                self.dbConnect()
        except Exception as ex:
            self.writeError(u'dbQuery exception:{}'.format(str(ex)))

        return []

    def dbQueryBySort(self, dbName, collectionName, d, sortName, sortType, limitNum=0):
        """从MongoDB中读取数据，d是查询要求，sortName是排序的字段,sortType是排序类型
          返回的是数据库查询的指针"""
        try:
            if self.dbClient:
                db = self.dbClient[dbName]
                collection = db[collectionName]
                if limitNum > 0:
                    cursor = collection.find(d).sort(sortName, sortType).limit(limitNum)
                else:
                    cursor = collection.find(d).sort(sortName, sortType)
                if cursor:
                    return list(cursor)
                else:
                    return []
            else:
                self.writeLog('db query fail')
                if self.db_has_connected:
                    self.writeLog(u'重新尝试连接数据库')
                    self.dbConnect()

        except AutoReconnect as ex:
            self.writeError(u'数据库连接断开重连:{}'.format(str(ex)))
            sleep(1)
        except ConnectionFailure:
            self.dbClient = None
            self.writeError(u'数据库连接断开')
            if self.db_has_connected:
                self.writeLog(u'重新尝试连接数据库')
                self.dbConnect()
        except Exception as ex:
            self.writeError(u'dbQueryBySort exception:{}'.format(str(ex)))

        return []

    # ----------------------------------------------------------------------
    def dbUpdate(self, dbName, collectionName, d, flt, upsert=False,replace=True):
        """向MongoDB中更新数据，d是具体数据，flt是过滤条件，upsert代表若无是否要插入"""
        try:
            if self.dbClient:
                db = self.dbClient[dbName]
                collection = db[collectionName]
                if replace:
                    rtn =collection.replace_one(flt, d, upsert)
                else:
                    rtn = collection.update_one(flt, {'$set':d}, upsert)

                return rtn

            else:
                self.writeLog('db update fail')
                if self.db_has_connected:
                    self.writeLog(u'重新尝试连接数据库')
                    self.dbConnect()

        except AutoReconnect as ex:
            self.writeError(u'数据库连接断开重连:{}'.format(str(ex)))
            sleep(1)
        except ConnectionFailure:
            self.dbClient = None
            self.writeError(u'数据库连接断开')
            if self.db_has_connected:
                self.writeLog(u'重新尝试连接数据库')
                self.dbConnect()
        except Exception as ex:
            self.writeError(u'dbUpdate exception:{}'.format(str(ex)))

        return None

    def dbDelete(self,dbName, collectionName, flt):
        """
        向mongodb中，删除数据，flt是过滤条件
        :param dbName:
        :param collectionName:
        :param flt:
        :return:
        """
        try:
            if self.dbClient:
                db = self.dbClient[dbName]
                collection = db[collectionName]
                collection.delete_many(flt)
            else:
                self.writeLog('db delete fail')
                if self.db_has_connected:
                    self.writeLog(u'重新尝试连接数据库')
                    self.dbConnect()
        except ConnectionFailure:
            self.dbClient = None
            self.writeError(u'数据库连接断开')
            if self.db_has_connected:
                self.writeLog(u'重新尝试连接数据库')
                self.dbConnect()
        except Exception as ex:
            self.writeError(u'dbDelete exception:{}'.format(str(ex)))
