#!/usr/bin/python
# -*- coding: utf-8 -*-
import subprocess
import os
import sys
import platform

gpid_file = os.path.abspath(os.path.join(os.path.dirname(__file__), 'logs','gpid.txt'))

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
        if gpid != "" and _check_gpid(gpid):
            return gpid

    return None

if _status():
    print( u'another service is already running...')
    exit(0)

def _save_gpid():

    plat = str(platform.system())
    if plat == 'Windows':
        gpid = os.getpid()
    else:   # unix
        gpid = os.getpgrp()
    print( 'gpid={}'.format(gpid))

    with open(gpid_file, 'w') as f:
        f.write(str(gpid))

_save_gpid()
