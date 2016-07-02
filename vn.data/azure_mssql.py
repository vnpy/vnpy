# encoding: UTF-8
#!/usr/bin/env python
#-------------------------------------------------------------------------------
# Name: azure_mssql.py
# Purpose: 使用 pymssql库链接Azure的MSSQL
#
# Author: IncenseLee@hotmail.com
#
# Created: 09/19/2015
#-------------------------------------------------------------------------------

import pymssql


class azure_mssql:
    """
    对pymssql的简单封装
    pymssql库，该库到这里下载：http://www.lfd.uci.edu/~gohlke/pythonlibs/#pymssql
    使用该库时，需要在Sql Server Configuration Manager里面将TCP/IP协议开启

    http://pymssql.sourceforge.net/ref_pymssql.php

    sql语句中有中文的时候进行encode
    insertSql = "insert into WeiBo([UserId],[WeiBoContent],[PublishDate]) values(1,'测试','2012/2/1')".encode("utf8")
    连接的时候加入charset设置信息
    pymssql.connect(host=self.host,user=self.user,password=self.pwd,database=self.db,charset="utf8")
    用法：

    """

    def __init__(self,host,user,pwd,db):
        self.host = host
        self.user = user
        self.pwd = pwd
        self.db = db

    def __get_connect(self):
        """
        得到连接信息
        返回: conn.cursor()
        """
        if not self.db:
            raise(NameError,"没有设置数据库信息")
        self.conn = pymssql.connect(host=self.host, user=self.user, password=self.pwd, database=self.db, charset="utf8")
        cur = self.conn.cursor()
        if not cur:
            raise(NameError,"连接数据库失败")
        else:
            return cur

    def exec_query(self,sql):
        """
        执行查询语句
        返回的是一个包含tuple的list，list的元素是记录行，tuple的元素是每行记录的字段

        调用示例：
                ms = azure_mssql(host="stock.database.windows.net",user="sqladmin",pwd="7uhb*IJN",db="stockcn")
                resList = ms.ExecQuery("SELECT id,NickName FROM WeiBoUser")
                for (id,NickName) in resList:
                    print str(id),NickName
        """
        cur = self.__get_connect()
        cur.execute(sql)
        resList = cur.fetchall()

        #查询完毕后必须关闭连接
        self.conn.close()
        return resList

    def exec_non_query(self,sql):
        """
        执行非查询语句

        调用示例：
            cur = self.__GetConnect()
            cur.execute(sql)
            self.conn.commit()
            self.conn.close()
        """
        cur = self.__get_connect()
        cur.execute(sql)
        self.conn.commit()
        self.conn.close()

def main():
## ms = azure_mssql(host="stock.database.windows.net",user="sqladmin",pwd="7uhb*IJN",db="stockcn")
## #返回的是一个包含tuple的list，list的元素是记录行，tuple的元素是每行记录的字段
## ms.ExecNonQuery("insert into WeiBoUser values('2','3')")

    ms = azure_mssql(host="stock.database.windows.net:1433", user="sqladmin", pwd="7uhb*IJN", db="stockcn")
    resList = ms.exec_query("SELECT  count(*) as recordcounts  FROM tb_ami")
    for (recordcounts) in resList:
        print str(recrodcounts).decode("utf8")

if __name__ == '__main__':
    main()