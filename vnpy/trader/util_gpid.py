#!/usr/bin/python
# -*- coding: utf-8 -*-
import subprocess
import os
import sys
import platform
import psutil

# changelog
# 记录gpid，修改为pid

run_path = os.path.abspath(os.path.join(os.getcwd(), 'logs'))
if not os.path.isdir(run_path):
    os.mkdir(run_path)
assert os.path.isdir(run_path)

gpid_file = os.path.abspath(os.path.join(run_path, 'gpid.txt'))

USE_GPID = False

def _check_pid(pid):

    cur_pid = os.getpid()
    if cur_pid != pid:
        return False
    return True

def _check_gpid(gpid):
    plat = str(platform.system())
    if plat == 'Windows':
        cur_pid = os.getpid()

        if cur_pid != gpid:
            return False
        return True

    try:
        p = subprocess.Popen(["ps", "-A", "-o", "pgrp="], stdin=subprocess.PIPE,
                stdout=subprocess.PIPE, stderr=subprocess.PIPE, shell=False)
        returncode = p.wait()
    except OSError as e:
        print( u'can not find shell command ps')
        exit(1)
    try:
        p2 = subprocess.Popen("uniq", stdin=p.stdout, stdout=subprocess.PIPE,
                stderr=subprocess.PIPE, shell=False)
        returncode = p2.wait()
    except OSError as e:
        print(u'can not find shell command uniq')
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
        if gpid != "" :
            if USE_GPID:
                if _check_gpid(gpid):
                    return gpid
            else:
                if _check_pid(gpid):
                    return gpid
    return None

if _status():
    print( u'another service is already running...')
    exit(0)

def _save_gpid(log=True):

    plat = str(platform.system())
    if plat == 'Windows':
        gpid = os.getpid()
    else:   # unix
        gpid = os.getpgrp() if USE_GPID else os.getpid()
    if log:
        print( 'gpid={}'.format(gpid))

    with open(gpid_file, 'w') as f:
        f.write(str(gpid))
    if log:
        print(u'wrote gpid file:{}'.format(gpid_file))

def update_gpid():
    _save_gpid(log=False)

_save_gpid()

if __name__ == '__main__':
    test_pid = 20671
    print('check pid:{}:result:{}'.format(test_pid, _check_pid(test_pid)))

    if psutil.pid_exists(test_pid):
        print('pid:{} exist:'.format(test_pid))