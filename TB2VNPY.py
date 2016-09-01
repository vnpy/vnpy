#coding:utf-8
import csv
import os
for filename in os.listdir(os.getcwd()):
    if "csv" in filename:
         path=os.getcwd()+'/'+filename
         print path
         csvfile=file(path,'rb')
         csvfile_out=file(os.getcwd()+"/output/"+filename,'wb')
         reader=csv.reader(csvfile)
         writer=csv.writer(csvfile_out)
         writer.writerow(('Date','Time','Open','High','Low','Close','TotalVolume'))
         for line in reader:
            a,b,c,d,e,f,g=line
            #print "a:%s,b:%s,c:%s,d:%s,e:%s,f:%s,g:%s"%(a,b,c,d,e,f,g)
            date=a.split(' ')[0]
            time=a.split(' ')[1]
            writer.writerow((date,time,b,c,d,e,f))
    csvfile.close()
    csvfile_out.close()