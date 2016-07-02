# encoding: UTF-8

import datetime

startDate = datetime.date(2012,6,1)
endDate = datetime.date(2012,12,31)
for i in range (0,(endDate - startDate).days +1, 10):
    d1 = startDate + datetime.timedelta(days= i  )

    if (endDate - d1).days > 10:
        d2 = startDate + datetime.timedelta(days= i+9 )
    else:
        d2 = endDate

    i = i + 10

    print str(d1),str(d2)