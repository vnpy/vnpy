#!/usr/bin/python
# -*- coding: utf-8 -*-

# python2 环境

import sys
import time
from datetime import datetime
# import commands
import os
import subprocess

try:
    import util_mail as sendmail
except :
    pass

python_path = '/home/trade/anaconda2/bin/python'
valid_time_span = '08:55:00~15:30:00,20:45:00~02:35:00'
base_path = os.path.abspath(os.path.dirname(os.path.realpath(__file__)))
gpid_file = os.path.abspath(os.path.join(base_path, 'logs', 'gpid.txt'))
tmp_cron_file = os.path.abspath(os.path.join(base_path, 'logs', 'cron.tmp'))
ctp_gateway_name = 'CTP_JR'
program_file = os.path.abspath(os.path.join(base_path, '{0}.py'.format(ctp_gateway_name)))
log_file = os.path.abspath(os.path.join(base_path,'logs', 'service.log'))
error_file = os.path.abspath(os.path.join(base_path, 'logs', 'service-error.log'))
null_file = "/dev/null"

cron_content = "* * * * * {} {} schedule >{} 2>{}".format(python_path, os.path.realpath(__file__), null_file, null_file)
program_command = "nohup {} {} >{} 2>{} &".format(python_path, program_file, log_file, error_file)

def _check_gpid(gpid):
    try:
        p = subprocess.Popen(["ps", "-A", "-o", "pgrp="], stdin=subprocess.PIPE,
                stdout=subprocess.PIPE, stderr=subprocess.PIPE, shell=False)
        returncode = p.wait()
    except OSError as e:
        print('cant not find shell command ps')
        exit(1)
    try:
        p2 = subprocess.Popen("uniq", stdin=p.stdout, stdout=subprocess.PIPE,
                stderr=subprocess.PIPE, shell=False)
        returncode = p2.wait()
    except OSError as e:
        print( 'cant not find shell command uniq')
        exit(1)
    for i in p2.stdout.readlines():
        if i.decode().strip() == gpid:
            return True
    return False

def _status():
    if os.path.exists(gpid_file):
        with open(gpid_file, 'r') as f:
            gpid = f.read().strip()
            # print(gpid)
        if gpid != "" and _check_gpid(gpid):
            return gpid

    return None

def trade_off():
    """检查现在是否为非交易时间"""
    now = datetime.now()
    a = datetime.now().replace(hour=2, minute=35, second=0, microsecond=0)
    b = datetime.now().replace(hour=8, minute=55, second=0, microsecond=0)
    c = datetime.now().replace(hour=15, minute=30, second=0, microsecond=0)
    d = datetime.now().replace(hour=20, minute=55, second=0, microsecond=0)
    weekend = (now.isoweekday() == 6 and now >= a) or (now.isoweekday() == 7)
    off = (a<= now <= b) or (c <= now <= d) or weekend
    return off


def _check_stop_time():
    time_span_list = []
    for time_span in valid_time_span.split(","):
        time_pair = tuple([item.strip() for item in time_span.split("~")])
        time_span_list.append(time_pair)
    time_span_list.sort(key=lambda pair: pair[0])
    if len(time_span_list) == 0:
        return False
    import datetime
    now_time = datetime.datetime.now()
    a = datetime.now().replace(hour=2, minute=35, second=0, microsecond=0)
    weekend = (now_time.isoweekday() == 6 and now_time >= a) or (now_time.isoweekday() == 7)
    if weekend:
        return True

    now_time_str = now_time.strftime('%H:%M:%S')
    stop_flag = True
    if time_span_list[-1][1] > now_time_str:
        stop_flag = False
    else:
        watch_flag = False
        for item in time_span_list:
            if item[0] > now_time_str:
                stop_flag = True
                watch_flag = True
                break
            if item[1] > now_time_str:
                stop_flag = False
                watch_flag = True
                break

        if not watch_flag:
            if time_span_list[-1][1] < time_span_list[0][0]:
                stop_flag = False
            else:
                stop_flag = True

    return stop_flag


def _start():
    gpid = _status()
    if _check_stop_time():
        if gpid:
            print('it is not in valid time span, will kill the service[gpid={}]'.format(gpid))
            import signal
            # 杀死进程组
            os.killpg(int(gpid), signal.SIGKILL)
            while _status():
                time.sleep(1)
            print( 'already stop the service[gpid={}]'.format(gpid))
            try:
                sendmail.sendmail(subject='{0} killed by service.py'.format(ctp_gateway_name),
                                  msgcontent='already stop the service[gpid={}]'.format(gpid))
            except:
                pass
        else:
            print( 'it is not in valid time span, can not start the service')
    else:
        if not gpid:
            print( 'it is in valid time span, will start the service')
            os.popen(program_command)
            while True:
                gpid = _status()
                if gpid:
                    break
                time.sleep(1)
            print( 'already start the service[gpid={}]'.format(gpid))
        else:
            print( 'it is in valid time span, the service is running...')


def schedule():
    print( '======schedule========')
    _start()


def status():
    print( '======status========')

    gpid = _status()
    if gpid:
        print( 'the service[gpid={}] is running...'.format(gpid))
    else:
        print( 'the service is not running...')

# operate的可选字符串为：add, del
def operate_crontab(operate):
    os.popen("crontab -l > {}".format(tmp_cron_file))

    remain_cron_list = []
    with open(tmp_cron_file, 'r') as f:
        exist_flag = False
        for i in f.readlines():
            if i.find(os.path.realpath(__file__) + " schedule") >= 0:
                old_cron_content = i
                exist_flag = True
            else:
                remain_cron_list.append(i)

    if operate == "add" and not exist_flag:
        # with open(tmp_cron_file, 'a') as f:
            # f.write("\n" + cron_content)
            # f.flush()
        
        # 追加方式比上面好，能自动判断上行是否有回车
        os.popen('echo "{}" >> {}'.format(cron_content, tmp_cron_file))
        print( ' add new crontab item: {}'.format(cron_content))
        os.popen("crontab {}".format(tmp_cron_file))

    if operate == "del" and exist_flag:
        with open(tmp_cron_file, 'w') as f:
            f.writelines(remain_cron_list)

        os.popen("crontab {}".format(tmp_cron_file))
        print( 'del old crontab item: {}'.format(old_cron_content))
    
    # os.remove(tmp_cron_file)


def start():
    print( '======start========')
    operate_crontab("add")
    _start()
    print( 'start service done!!!')


def _stop():
    operate_crontab("del")
    gpid = _status()
    if gpid:
        import signal
        # 杀死进程组
        os.killpg(int(gpid), signal.SIGKILL)
        while _status():
            time.sleep(1)
        print( 'already stop the service[gpid={}]'.format(gpid))
        try:
            sendmail.sendmail(subject='{0} stopped by service.py'.format(ctp_gateway_name),msgcontent= 'already stop the service[gpid={}]'.format(gpid))
        except:
            pass
    else:
        print( 'the service is not running...')


def stop():
    print('======stop========')
    _stop()
    print( 'stop service done!!!')


def restart():
    print( '======restart========')
    _stop()
    _start()
    print('restart service done!!!')


if __name__ == '__main__':
    if len(sys.argv) >=2:
        fun = sys.argv[1]
    else:
        fun = ''
    if fun == 'status':
        status()
    elif fun == 'start':
        start()
    elif fun == 'stop':
        stop()
    elif fun == 'restart':
        restart()
    elif fun == 'schedule':
        schedule()
    else:
        print( 'Usage: {} (status|start|stop|restart)'.format(os.path.basename(__file__)))
