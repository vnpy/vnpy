#!/usr/bin/python
# -*- coding: utf-8 -*-
from __future__ import print_function
import sys
import time

# import commands
import os
import subprocess

# python 3 环境

python = "/usr/bin/python"
bash = "/bin/bash"
valid_time_span = "08:45:00~19:00:00,20:45:00~03:00:00"
base_path = os.path.dirname(os.path.realpath(__file__))
gpid_file = os.path.join(base_path, "gpid.txt")
tmp_cron_file = os.path.join(base_path, "cron.tmp")

program_file = os.path.join(base_path, "activate.sh")
error_file = os.path.join(base_path, "cerr.log")
null_file = "/dev/null"

cron_content = "* * * * * {} {} schedule >{} 2>{} &".format(python, os.path.realpath(__file__), null_file, null_file)
program_command = "nohup {} {} >{} 2>{} &".format(bash, program_file, null_file, error_file)

def _check_gpid(gpid):
    try:
        p = subprocess.Popen(["ps", "-A", "-o", "pgrp="], stdin=subprocess.PIPE,
                stdout=subprocess.PIPE, stderr=subprocess.PIPE, shell=False)
        returncode = p.wait()
    except OSError as e:
        print("cant't find shell command ps")
        exit(1)
    try:
        p2 = subprocess.Popen("uniq", stdin=p.stdout, stdout=subprocess.PIPE,
                stderr=subprocess.PIPE, shell=False)
        returncode = p2.wait()
    except OSError as e:
        print("cant't find shell command uniq")
        exit(1)
    for i in p2.stdout.readlines():
        if i.decode().strip() == gpid:
            # print(i.decode())
            return True
    return False

def _status():
    if os.path.exists(gpid_file):
        # print(gpid_file)
        with open(gpid_file, 'r') as f:
            gpid = f.read().strip()
            # print(gpid)
        if gpid != "" and _check_gpid(gpid):
            return gpid

    return None


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
            print("it's not in valid time span, will kill the service[gpid={}]".format(gpid))
            import signal
            # 杀死进程组
            os.killpg(int(gpid), signal.SIGKILL)
            while _status():
                time.sleep(1)
            print("already stop the service[gpid={}]".format(gpid))
        else:
            print("it's not in valid time span, can't start the service")
    else:
        if not gpid:
            print("it's in valid time span, will start the service")
            os.popen(program_command)

            while True:
                gpid = _status()
                if gpid:
                    break
                time.sleep(1)
            print("already start the service[gpid={}]".format(gpid))
        else:
            print("it's in valid time span, the service is running...")


def schedule():
    print("======schedule========")
    _start()


def status():
    print("======status========")

    gpid = _status()
    if gpid:
        print("the service[gpid={}] is running...".format(gpid))
    else:
        print("the service is not running...")


# operate的可选字符串为：add, del
def operate_crontab(operate):
    try:
        p = subprocess.Popen(["crontab", "-l"], stdin=subprocess.PIPE,
                             stdout=subprocess.PIPE, stderr=subprocess.PIPE, shell=False)
        returncode = p.wait()
    except OSError as e:
        print("cant't find shell command crontab")
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
        print("add new crontab item: {}".format(cron_content))

    if operate == "del" and exist_flag:
        with open(tmp_cron_file, 'wb') as f:
            for i in remain_cron_list:
                f.write(i.encode("utf-8"))
        os.popen("crontab {}".format(tmp_cron_file))
        print("del old crontab item: {}".format(old_cron_content))

    # os.remove(tmp_cron_file)


def start():
    print("======start========")
    operate_crontab("add")
    _start()
    print("start service done!!!")


def _stop():
    gpid = _status()
    if gpid:
        import signal
        # 杀死进程组
        os.killpg(int(gpid), signal.SIGKILL)
        while _status():
            time.sleep(1)
        print("already stop the service[gpid={}]".format(gpid))
    else:
        print("the service is not running...")


def stop():
    print("======stop========")
    operate_crontab("del")
    _stop()
    print("stop service done!!!")


def restart():
    print("======restart========")
    _stop()
    time.sleep(1)
    operate_crontab("add")
    _start()
    print("restart service done!!!")


if __name__ == '__main__':
    if len(sys.argv) >= 2:
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
        print("Usage: {} (status|start|stop|restart)".format(os.path.basename(__file__)))
