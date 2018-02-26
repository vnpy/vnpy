#!/usr/bin/python
# -*- coding: utf-8 -*-

# python 3 环境
# 激活 activate.sh (激活py35 env，启动运行程序

import sys
import time
from datetime import datetime
# import commands
import os
import subprocess

# 将repostory的目录i，作为根目录，添加到系统环境中。
ROOT_PATH = os.path.abspath(os.path.join(os.path.dirname(__file__), '..', '..'))
sys.path.append(ROOT_PATH)

try:
    import vnpy.trader.util_mail as sendmail
except :
    pass

# python容器文件
python_path = '/home/tensorflow/anaconda3/envs/py35/bin/python'
# 运行时间段
valid_time_span = '08:55:00~15:30:00,20:45:00~02:35:00'

# 日志目录
log_path = os.path.abspath(os.path.join(os.getcwd(), 'logs'))
if os.path.isdir(log_path):
    # 如果工作目录下，存在logs子目录，就使用logs子目录
    base_path = os.getcwd()
else:
    # 使用service.py所在得目录
    base_path = os.path.abspath(os.path.dirname(os.path.realpath(__file__)))

# 进程组id保存文件
gpid_file = os.path.abspath(os.path.join(base_path, 'logs', 'gpid.txt'))

tmp_cron_file = os.path.abspath(os.path.join(base_path, 'logs', 'cron.tmp'))

program_file = os.path.join(base_path, 'activate.sh')
log_file = os.path.abspath(os.path.join(base_path,'logs', 'service.log'))
error_file = os.path.abspath(os.path.join(base_path, 'logs', 'service-error.log'))
null_file = "/dev/null"

cron_content = "* * * * * {} {} schedule >{} 2>{}".format(python_path, os.path.realpath(__file__), log_file, error_file)
program_command = "nohup {} {} >{} 2>{} &".format(python_path, program_file, log_file, error_file)

def _check_gpid(gpid):
    """
    检查进程组ID
    :param gpid: 
    :return: 
    """
    try:
        # 通过系统子进程，打开ps命令，找到gpid下得所有进程
        p = subprocess.Popen(["ps", "-A", "-o", "pgrp="], stdin=subprocess.PIPE,
                stdout=subprocess.PIPE, stderr=subprocess.PIPE, shell=False)
        returncode = p.wait()
    except OSError as e:
        print('找不到shell运行命令ps', file=sys.stderr)
        exit(1)

    try:
        p2 = subprocess.Popen("uniq", stdin=p.stdout, stdout=subprocess.PIPE,
                stderr=subprocess.PIPE, shell=False)
        returncode = p2.wait()
    except OSError as e:
        print(u'找不到shell运行命令uniq', file=sys.stderr)
        exit(1)
    for i in p2.stdout.readlines():
        if i.decode().strip() == gpid:
            return True
    return False

def _status():
    """
    查询当前状态
    :return: 
    """
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
    """
    当前时间是否属于停止运行
    :return: True：属于停止运行期间；False：不属于
    """
    time_span_list = []
    for time_span in valid_time_span.split(","):
        time_pair = tuple([item.strip() for item in time_span.split("~")])
        time_span_list.append(time_pair)
    time_span_list.sort(key=lambda pair: pair[0])
    if len(time_span_list) == 0:
        return False
    import datetime
    now_time = datetime.datetime.now()
    a = now_time.replace(hour=2, minute=35, second=0, microsecond=0)
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
    """
    启动服务
    :return: 
    """
    # 获取进程组id
    gpid = _status()

    if _check_stop_time():
        # 属于停止运行期间
        if gpid:
            print(u'现在属于停止运行时间，进程组ID存在,将杀死服务进程:[gpid={}]'.format(gpid))
            import signal
            # 杀死进程组
            os.killpg(int(gpid), signal.SIGKILL)
            while _status():
                time.sleep(1)
            print('进程组已停止运行[gpid={}]'.format(gpid))
            try:
                sendmail.sendmail(subject='Notification: {0}目录下服务 killed by service.py'.format(base_path),
                                  msgcontent='停止运行时间,已将进程组[gpid={}]杀死.'.format(gpid))
            except:
                print(u'发送通知邮件失败', file=sys.stderr)
                pass
        else:
            print(u'现在属于停止运行时间，不启动服务')
    else:
        # 属于运行时间
        if not gpid:
            print(u'属于运行时间,将启动服务')
            os.popen(program_command)
            while True:
                gpid = _status()
                if gpid:
                    print('属于运行时间,成功启动服务[gpid={}]'.format(gpid))
                    try:
                        sendmail.sendmail(
                            subject='Notification: {0}目录下进程启动'.format(base_path),
                            msgcontent='属于运行时间,已启动服务[gpid={}]'.format(gpid))
                    except:
                        print(u'发送通知邮件失败', file=sys.stderr)
                        pass
                    break
                time.sleep(1)
        else:
            print(u'属于运行时间,服务已运行')


def schedule():
    """
    crontab 计划执行
    :return: 
    """
    print( '======schedule========')
    _start()


def status():
    """查看状态"""
    print('======status========')

    gpid = _status()
    if gpid:
        print('服务进程[gpid={}]正在运行'.format(gpid))
    else:
        print('服务进程没有运行.')

# operate的可选字符串为：add, del
def operate_crontab(operate):
    """
    操作crontab
    :param operate: add , del
    :return: 
    """

    try:
        # 从系统命令中，获取定时任务
        p = subprocess.Popen(["crontab", "-l"], stdin=subprocess.PIPE,
                             stdout=subprocess.PIPE, stderr=subprocess.PIPE, shell=False)
        returncode = p.wait()
    except OSError as e:
        print(u"找不到shell运行命令crontab", file=sys.stderr)
        exit(1)

    remain_cron_list = []
    exist_flag = False
    for i in p.stdout.readlines():
        if i.decode("utf-8").find(os.path.realpath(__file__) + " schedule") >= 0:
            old_cron_content = i.decode("utf-8")
            exist_flag = True
        else:
            remain_cron_list.append(i.decode("utf-8"))

    if operate == "add" and not exist_flag:
        remain_cron_list.append(cron_content)
        remain_cron_list.append("\n")
        with open(tmp_cron_file, 'wb') as f:
            for i in remain_cron_list:
                f.write(i.encode("utf-8"))
        os.popen("crontab {}".format(tmp_cron_file))
        print(u'添加crontab项: {}'.format(cron_content), file=sys.stderr)

    if operate == "del" and exist_flag:
        with open(tmp_cron_file, 'wb') as f:
            for i in remain_cron_list:
                f.write(i.encode("utf-8"))
        os.popen("crontab {}".format(tmp_cron_file))
        print(u'删除crontab item: {}'.format(old_cron_content), file=sys.stderr)

        # os.remove(tmp_cron_file)

def start():
    print(u'======start========')
    # 往任务表增加定时计划
    operate_crontab("add")
    # 执行启动
    _start()
    print(u'启动服务执行完毕')

def _stop():
    print(u'======stop========')
    # 在任务表删除定时计划
    operate_crontab("del")

    # 查询进程组id
    gpid = _status()
    if gpid:
        # 进程组存在，杀死进程
        import signal
        # 杀死进程组
        os.killpg(int(gpid), signal.SIGKILL)
        while _status():
            time.sleep(1)
        print(u'成功停止服务[gpid={}]'.format(gpid))
        try:
            sendmail.sendmail(subject='Notification: {}目录下服务进程停止'.format(base_path),
                              msgcontent= '服务进程[gpid={}]停止'.format(gpid))
        except:
            print(u'发送通知邮件失败')
            pass
    else:
        print(u'服务进程没有运行')

def stop():
    """
    停止服务
    :return: 
    """
    print(u'======stop========')
    _stop()
    print(u'执行停止服务完成')


def restart():
    print(u'======restart========')
    _stop()
    _start()
    print('执行重启服务完成')


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
        print( u'Usage: {} (status|start|stop|restart)'.format(os.path.basename(__file__)))
