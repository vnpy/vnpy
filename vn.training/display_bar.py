# encoding: UTF-8

import MySQLdb
import numpy as np
import matplotlib.pyplot as plt

try:
    #连接数据库
    conn = MySQLdb.connect(host='vnpy.cloudapp.net', user='vnpy', passwd='vnpy', db='BackTest', port=3306)

    #获取指针
    cur = conn.cursor(MySQLdb.cursors.DictCursor)

    symbol = 'a'

    backtestingId = '20151021-170626'

    #执行脚本，返回记录数
    count = cur.execute('select open,high,low, close,datetime from TB_Bar where Id=\'{0}\''.format(backtestingId))
    print 'there has %s rows bar record' % count

    results = cur.fetchall()

    t1 = []
    o = []
    i = 0

    for r in results:
        i = i+1
        t1.append(i)
        # t.append(r['datetime'])
        o.append(r['open'])

    count = cur.execute('select fastEMA,slowEMA,datetime from TB_Ema where Id=\'{0}\''.format(backtestingId))
    print 'there has %s rows ema record' % count

    results = cur.fetchall()

    fastEma = []
    slowEma = []
    t2 = []
    i = 0

    for r in results:
        i = i+1
        t2.append(i)

        fastEma.append(r['fastEMA'])
        slowEma.append(r['slowEMA'])


    #关闭指针，关闭连接
    cur.close()
    conn.close()

    plt.plot(t1,o,label='data')
    plt.plot(t2,fastEma,label='fastEma')
    plt.plot(t2,slowEma,label='slowEma')
    plt.xlabel('Time')
    plt.ylabel('price')
    plt.show()

except MySQLdb.Error, e:
     print "Mysql Error %d: %s" % (e.args[0], e.args[1])