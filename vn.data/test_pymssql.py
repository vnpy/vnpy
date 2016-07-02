import pymssql
conn = pymssql.connect(server='stock.database.windows.net', port='1433',user='sqladmin@stock', password='7uhb*IJN', database='StockCn', charset="UTF-8", azure=True)
cur = conn.cursor()
cur.execute('CREATE TABLE persons(id INT, name VARCHAR(100))')
cur.executemany("INSERT INTO persons VALUES(%d, %s)", \
    [ (1, 'John Doe'), (2, 'Jane Doe') ])
conn.commit()

cur.execute('SELECT * FROM persons WHERE salesrep=%s', 'John Doe')
row = cur.fetchone()
while row:
    print "ID=%d, Name=%s" % (row[0], row[1])
    row = cur.fetchone()

conn.close()

