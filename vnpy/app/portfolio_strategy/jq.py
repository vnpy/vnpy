# -*- coding:utf-8 -*-
"""
@author: fsksf

@since: 2022/4/27 9:59
"""
import contextlib
from jqdatasdk import auth, logout
from vnpy.trader.setting import SETTINGS
username = SETTINGS['datafeed.username']
password = SETTINGS['datafeed.password']

JOINQUANT_USING = False


def joinquant_init():
    print(f'logging in joinquant with username: {username}')
    auth(username, password)


@contextlib.contextmanager
def login_jq():
    global JOINQUANT_USING
    joinquant_init()
    JOINQUANT_USING = True
    yield
    try:
        logout()
    except AttributeError:
        pass
    JOINQUANT_USING = False
    return