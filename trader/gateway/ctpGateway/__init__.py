# encoding: UTF-8

import sys
import os

import trader.vtConstant

print u'init {0}'.format(os.path.dirname(__file__))

from ctpGateway import CtpGateway as gateway

gatewayName = 'CTP'
gatewayDisplayName = gatewayName
gatewayType = trader.vtConstant.GATEWAYTYPE_FUTURES
gatewayQryEnabled = True

