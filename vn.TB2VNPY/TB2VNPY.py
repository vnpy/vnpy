#coding:utf-8
#直接在TB2VNPY目录中丢下csv文件运行即可
#输出文件在output目录之中
import csv
import os
if os.path.exists('./output')==False:
    os.mkdir('./output')
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
            time=a.split(' ')[1]+":00"
            writer.writerow((date,time,b,c,d,e,f))
         csvfile.close()
         csvfile_out.close()
