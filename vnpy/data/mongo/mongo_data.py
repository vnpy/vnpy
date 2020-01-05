# encoding: UTF-8

# Mongodb 数据服务

import sys
from time import sleep
from pymongo import MongoClient, ASCENDING
from pymongo.errors import ConnectionFailure, AutoReconnect


class MongoData(object):

    db_client = None  # 全局连接对象
    db_has_connected = False  # 是否已经连接

    def __init__(self, host: str, port: int):
        self.host = host
        self.port = port
        self.db_connect()

    def db_connect(self, force=False):
        if (self.db_client is None or not self.db_has_connected) or force:
            print('connecting to Mongo:{}:{}'.format(self.host, self.port))
            try:
                # 设置MongoDB操作的超时时间为0.5秒
                self.db_client = MongoClient(self.host, self.port, connectTimeoutMS=500)
                # 调用server_info查询服务器状态，防止服务器异常并未连接成功
                self.db_client.server_info()

                self.db_has_connected = True
                print('mongo db connected')

            except Exception as ex:
                self.db_client = None
                self.db_has_connected = False
                self.write_error(u'connect to mongo {}:{} exception:{}'.format(self.host, self.port, str(ex)))

    def write_log(self, content):
        print(content)

    def write_error(self, content):
        print(content, file=sys.stderr)

    # ----------------------------------------------------------------------
    def db_insert(self, db_name, col_name, d):
        """向MongoDB中插入数据，d是具体数据"""
        try:
            if self.db_client:
                db = self.db_client[db_name]
                collection = db[col_name]
                collection.insert_one(d)
            else:
                self.write_error(u'db insert fail')
                if self.db_has_connected:
                    self.write_log(u'重新尝试连接数据库')
                    self.db_connect(force=True)

        except AutoReconnect as ex:
            self.write_log(u'数据库连接断开重连:{}'.format(str(ex)))
            sleep(1)
            return False
        except ConnectionFailure:
            self.db_client = None
            self.write_error(u'数据库连接断开')
            if self.db_has_connected:
                self.write_log(u'重新尝试连接数据库')
                self.db_connect(force=True)
            return False
        except Exception as ex:
            self.write_error(u'dbInsert exception:{}'.format(str(ex)))
            return False
        return True

    def db_insert_many(self, db_name, col_name, data_list, ordered=True):
        """
        向MongoDB中插入数据，data_list是具体数据 列表
        :param db_name:
        :param col_name:
        :param data_list:
        :param ordered: 是否忽略insert error
        :return:
        """
        if not isinstance(data_list, list):
            self.write_error('data_list should be a list')
            return
        try:
            if self.db_client:
                db = self.db_client[db_name]
                collection = db[col_name]
                collection.insert_many(data_list, ordered=ordered)
            else:
                self.write_error('db insert many fail')
                if self.db_has_connected:
                    self.write_log(u'重新尝试连接数据库')
                    self.db_connect(force=True)

        except AutoReconnect as ex:
            self.write_error(u'数据库连接断开重连:{}'.format(str(ex)))
            sleep(1)
        except ConnectionFailure:
            self.db_client = None
            self.write_error(u'数据库连接断开')
            if self.db_has_connected:
                self.write_log(u'重新尝试连接数据库')
                self.db_connect(force=True)
        except Exception as ex:
            self.write_error(u'dbInsertMany exception:{}'.format(str(ex)))

    # ----------------------------------------------------------------------
    def db_query_one(self, db_name, col_name, flt):
        """从MongoDB中读取数据，d是查询要求，返回的是一个结果"""
        try:
            if self.db_client:
                db = self.db_client[db_name]
                collection = db[col_name]

                return collection.find_one(flt)

            else:
                self.write_log('db query fail')
                if self.db_has_connected:
                    self.write_log(u'重新尝试连接数据库')
                    self.db_connect()

        except AutoReconnect as ex:
            self.write_error(u'数据库连接断开重连:{}'.format(str(ex)))
            sleep(1)
        except ConnectionFailure:
            self.db_client = None
            self.write_error(u'数据库连接断开')
            if self.db_has_connected:
                self.write_log(u'重新尝试连接数据库')
                self.db_connect()
        except Exception as ex:
            self.write_error(u'dbQuery exception:{}'.format(str(ex)))

        return None

    # ----------------------------------------------------------------------
    def db_query(self, db_name, col_name, filter_dict, sort_key='', sort_type=ASCENDING):
        """从MongoDB中读取数据，d是查询要求，返回的是数据库查询的指针"""
        try:
            if self.db_client:
                db = self.db_client[db_name]
                collection = db[col_name]

                if sort_key:
                    cursor = collection.find(filter_dict).sort(sort_key, sort_type)  # 对查询出来的数据进行排序
                else:
                    cursor = collection.find(filter_dict)

                if cursor:
                    return list(cursor)
                else:
                    return []
            else:
                self.write_log('db query fail')
                if self.db_has_connected:
                    self.write_log(u'重新尝试连接数据库')
                    self.db_connect()

        except AutoReconnect as ex:
            self.write_error(u'数据库连接断开重连:{}'.format(str(ex)))
            sleep(1)
        except ConnectionFailure:
            self.db_client = None
            self.write_error(u'数据库连接断开')
            if self.db_has_connected:
                self.write_log(u'重新尝试连接数据库')
                self.db_connect()
        except Exception as ex:
            self.write_error(u'dbQuery exception:{}'.format(str(ex)))

        return []

    def db_query_by_sort(self, db_name, col_name, filter_dict, sort_name, sort_type, limitNum=0):
        """从MongoDB中读取数据，d是查询要求，sortName是排序的字段,sortType是排序类型
          返回的是数据库查询的指针"""
        try:
            if self.db_client:
                db = self.db_client[db_name]
                collection = db[col_name]
                if limitNum > 0:
                    cursor = collection.find(filter_dict).sort(sort_name, sort_type).limit(limitNum)
                else:
                    cursor = collection.find(filter_dict).sort(sort_name, sort_type)
                if cursor:
                    return list(cursor)
                else:
                    return []
            else:
                self.write_log('db query fail')
                if self.db_has_connected:
                    self.write_log(u'重新尝试连接数据库')
                    self.db_connect()

        except AutoReconnect as ex:
            self.write_error(u'数据库连接断开重连:{}'.format(str(ex)))
            sleep(1)
        except ConnectionFailure:
            self.db_client = None
            self.write_error(u'数据库连接断开')
            if self.db_has_connected:
                self.write_log(u'重新尝试连接数据库')
                self.db_connect()
        except Exception as ex:
            self.write_error(u'dbQueryBySort exception:{}'.format(str(ex)))

        return []

    # ----------------------------------------------------------------------
    def db_update(self, db_name, col_name, data_dict, filter_dict, upsert=False, replace=False):
        """向MongoDB中更新数据，d是具体数据，flt是过滤条件，upsert代表若无是否要插入"""
        try:
            if self.db_client:
                db = self.db_client[db_name]
                collection = db[col_name]
                if replace:
                    rtn = collection.replace_one(filter_dict, data_dict, upsert)
                else:
                    rtn = collection.update_one(filter_dict, {'$set': data_dict}, upsert)

                return rtn

            else:
                self.write_log('db update fail')
                if self.db_has_connected:
                    self.write_log(u'重新尝试连接数据库')
                    self.db_connect()

        except AutoReconnect as ex:
            self.write_error(u'数据库连接断开重连:{}'.format(str(ex)))
            sleep(1)
        except ConnectionFailure:
            self.db_client = None
            self.write_error(u'数据库连接断开')
            if self.db_has_connected:
                self.write_log(u'重新尝试连接数据库')
                self.db_connect()
        except Exception as ex:
            self.write_error(u'dbUpdate exception:{}'.format(str(ex)))

        return None

    def db_delete(self, db_name, col_name, flt):
        """
        向mongodb中，删除数据，flt是过滤条件
        :param db_name:
        :param col_name:
        :param flt:
        :return:
        """
        try:
            if self.db_client:
                db = self.db_client[db_name]
                collection = db[col_name]
                collection.delete_many(flt)
            else:
                self.write_log('db delete fail')
                if self.db_has_connected:
                    self.write_log(u'重新尝试连接数据库')
                    self.db_connect()
        except ConnectionFailure:
            self.db_client = None
            self.write_error(u'数据库连接断开')
            if self.db_has_connected:
                self.write_log(u'重新尝试连接数据库')
                self.db_connect()
        except Exception as ex:
            self.write_error(u'dbDelete exception:{}'.format(str(ex)))

    def db_create_index(self, dbName, collectionName, indexName, sortType):
        """创建一个字段的索引"""
        try:
            if self.db_client:
                db = self.db_client[dbName]
                collection = db[collectionName]
                index_info = collection.index_information()
                key_name = '_'.join([indexName, str(sortType)])
                if key_name not in index_info:
                    collection.create_index([(indexName, sortType)], name=key_name, background=True)
                    index_info = collection.index_information()
                    print(u'created index:{}'.format(index_info))

        except Exception as ex:
            self.write_error(u'dbCreateIndex exception:{}'.format(str(ex)))

    def db_create_multi_index(self, db_name, col_name, index_list):
        """创建多个字段的索引"""
        try:
            if len(index_list) == 0:
                self.write_error(u'index_list 不能为空')
                return

            if self.db_client:
                key_name = '_'.join(['_'.join([indexName, str(sortType)]) for (indexName, sortType) in index_list])
                db = self.db_client[db_name]
                collection = db[col_name]
                index_info = collection.index_information()
                if key_name not in index_info:
                    collection.create_index(index_list, name=key_name, unique=True, background=True)
                    index_info = collection.index_information()
                    print(u'created index:{}'.format(index_info))

        except Exception as ex:
            self.write_error(u'dbCreateIndex exception:{}'.format(str(ex)))


if __name__ == "__main__":
    m = MongoData(host='localhost', port=27017)
    m.db_create_index('FutureRenko_Db', 'AU_5', 'datetime', 1)
