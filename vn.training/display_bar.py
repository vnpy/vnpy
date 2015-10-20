# encoding: UTF-8

import MySQLdb
import numpy as np
import matplotlib.pyplot as plt

try:
    #连接数据库
    conn = MySQLdb.connect(host='vnpy.cloudapp.net', user='stockcn', passwd='7uhb*IJN', db='BackTest', port=3306)

    #获取指针
    cur = conn.cursor(MySQLdb.cursors.DictCursor)

    symbol = 'a'

    #执行脚本，返回记录数
    count = cur.execute('select open,high,low, close,datetime from TB_Bar where Id=\'20151019-161753\'')
    print 'there has %s rows record' % count


    results = cur.fetchall()


    t = []

    o = []

    i = 0

    for r in results:
        i = i+1
        t.append(i)
        # t.append(r['datetime'])
        o.append(r['open'])


    #关闭指针，关闭连接
    cur.close()
    conn.close()

    plt.plot(t,o,label='data')
    plt.xlabel('Time')
    plt.ylabel('price')
    plt.show()

except MySQLdb.Error, e:
     print "Mysql Error %d: %s" % (e.args[0], e.args[1])