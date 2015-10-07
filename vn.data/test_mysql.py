# encoding: UTF-8

import MySQLdb

try:
    #连接数据库
    conn = MySQLdb.connect(host='vnpy.cloudapp.net', user='stockcn', passwd='7uhb*IJN', db='stockcn', port=3306)

    #获取指针
    cur = conn.cursor(MySQLdb.cursors.DictCursor)

    symbol = 'a'

    #执行脚本，返回记录数
    count = cur.execute(' select \'{0}\' as InstrumentID, str_to_date(concat(ndate,\' \', ntime),\'%Y-%m-%d %H:%i:%s\') as UpdateTime,price as LastPrice,vol as Volume,position_vol as OpenInterest,bid1_price as BidPrice1,bid1_vol as BidVolume1, sell1_price as AskPrice1, sell1_vol as AskVolume1 from TB_{0}MI limit 0,100;'.format(symbol))
    print 'there has %s rows record' % count


    #取回第一条记录
    result = cur.fetchone()
    print result

    #取回5条记录
    results = cur.fetchmany(5)
    for r in results:
        print r

    print '=='*10
    cur.scroll(0, mode = 'absolute')

    results = cur.fetchall()

    desc = cur.description
    print 'cur.description:', desc

    for r in results:
        #InstrumentID, UpdateTime, LastPrice, Volume, OpenInterest, BidPrice1, BidVolume1, AskPrice1, AskVolume1 = r
        #print InstrumentID, UpdateTime
        #print LastPrice*Volume;
        print r['InstrumentID'], float(r['LastPrice'])

    
    #关闭指针，关闭连接
    cur.close()
    conn.close()
except MySQLdb.Error, e:
     print "Mysql Error %d: %s" % (e.args[0], e.args[1])