# encoding: UTF-8

import os

print u'init path:{0}'.format(os.path.dirname(__file__))
from vnpy.trader import vtConstant
from ctpGateway import CtpGateway

gatewayClass = CtpGateway
gatewayName = 'CTP'
gatewayDisplayName = 'CTP'
gatewayType = vtConstant.GATEWAYTYPE_FUTURES
gatewayQryEnabled = True
