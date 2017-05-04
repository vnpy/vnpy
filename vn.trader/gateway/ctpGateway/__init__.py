# encoding: UTF-8

import sys
import os

trader_path = os.path.abspath(os.path.join(os.path.dirname(__file__), '..', '..'))
sys.path.append(trader_path)
import vtConstant

print u'init {0}'.format(os.path.dirname(__file__))

from ctpGateway import CtpGateway as gateway

gatewayName = 'CTP'
gatewayDisplayName = gatewayName
gatewayType = vtConstant.GATEWAYTYPE_FUTURES
gatewayQryEnabled = True

