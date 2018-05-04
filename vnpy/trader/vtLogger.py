# encoding: UTF-8

import time

from vnpy.event import *

from vnpy.trader.vtEvent import *
from vnpy.trader.vtConstant import *
from vnpy.trader.vtObject import *

from vnpy.trader.vtGateway import *

from datetime import datetime

class VtLogger(object):
    #----------------------------------------------------------------------
    def __init__(self,  logName , in_debug = True , open_md = "w"):
        self.now_debug = in_debug
        if self.now_debug:
            self.f = open( logName , open_md)

    #----------------------------------------------------------------------
    def error(self, msg , error_id):
        if self.now_debug:
            self.f.write(datetime.now().strftime("%Y-%m-%d %H:%M:%S") + " : " + "Error msg %s: %s " % (str(error_id) , msg) + "\n")
            self.f.flush()

    #----------------------------------------------------------------------
    def info(self, msg):
        if self.now_debug:
            self.f.write(datetime.now().strftime("%Y-%m-%d %H:%M:%S") + " : " + msg + "\n")
            self.f.flush()
