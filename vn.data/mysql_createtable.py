# encoding: UTF-8

import MySQLdb

#----------------------------------------------------------------------




def main():

    try:
        #连接数据库
        conn = MySQLdb.connect(host='vnpy.cloudapp.net', user='stockcn', passwd='7uhb*IJN', db='stockcn', port=3306)

        #获取指针
        cur = conn.cursor(MySQLdb.cursors.DictCursor)

        listSymbol = ['ag','al','au','ax','ay','b','bb','bu','c','cf','cs','cu','er','fb','fg','fu','hc','i','j','jd','jm','jr','l','lr','m','ma','me','ni','oi','p','pb','pm','pp','rb','ri','rm','ro','rs','ru','sf','sm','sn','sr9','sr','srx','sry','ta','tc','v','wh','wr','ws9','ws','wt','y','zn']

        strSQL = 'CREATE TABLE if not exists TB_{0}{1}(	' \
                 'datetime datetime not null,' \
                 '	date date Not NULL,' \
                 '	time time Not NULL,' \
                 '	open numeric(18, 3) NULL,' \
                 '	high numeric(18, 3) NULL,' \
                 '	low numeric(18, 3) NULL,' \
                 '	close numeric(18, 3) NULL,' \
                 '	volume int null,' \
                 ' CONSTRAINT  PK_TB_{0}{1}  PRIMARY KEY (datetime)' \
                 ' );'

        for symbol in listSymbol:

            print symbol, 'M1'
            #执行脚本
            cur.execute(strSQL.format(symbol, 'M1'))
            conn.commit

            print symbol, 'M5'
            cur.execute(strSQL.format(symbol, 'M5'))
            conn.commit


        #关闭指针，关闭连接
        cur.close()
        conn.close()
    except MySQLdb.Error, e:
         print "Mysql Error %d: %s" % (e.args[0], e.args[1])

if __name__ == '__main__':
    main()
