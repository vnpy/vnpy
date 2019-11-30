#!/usr/bin/python
# -*- coding: utf-8 -*-

import os
import platform

# 保存进程ID => logs/pid.txt
# 运行开始时，检查是否存在之前得pid进程

# 日志文件路径
logs_path = os.path.abspath(os.path.join(os.getcwd(), 'logs'))
if not os.path.isdir(logs_path):
    os.mkdir(logs_path)
assert os.path.isdir(logs_path)

# 记录pid得文件
pid_file = os.path.abspath(os.path.join(logs_path, 'pid.txt'))


def _check_pid(pid):
    """
    检查pid是否与当前进程pid一致
    :param pid:
    :return:
    """
    cur_pid = os.getpid()
    if cur_pid != pid:
        return False
    return True


def _check_status():
    """
    检查状态
    :return:
    """
    if os.path.exists(pid_file):
        with open(pid_file, 'r') as f:
            pid = f.read().strip()
            # print(pid)
        if pid != "":
            if _check_pid(pid):
                return pid
    return None


def _save_pid(log=True):
    """
    保存pid
    :param log:
    :return:
    """
    plat = str(platform.system())
    if plat == 'Windows':
        pid = os.getpid()
    else:   # unix
        pid = os.getpid()
    if log:
        print('pid={}'.format(pid))

    with open(pid_file, 'w') as f:
        f.write(str(pid))
    if log:
        print(u'wrote pid file:{}'.format(pid_file))


def update_pid():
    """
    更新pid
    :return:
    """
    _save_pid(log=False)


# 执行检查
if _check_status():
    import sys
    print(u'another service is already running...', file=sys.stderr)
    exit(0)

_save_pid()
