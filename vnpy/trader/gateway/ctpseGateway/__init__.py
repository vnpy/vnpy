# encoding: UTF-8

import os

print( u'init path:{0}'.format(os.path.dirname(__file__)))
from vnpy.trader import vtConstant
from vnpy.trader.gateway.ctpseGateway.ctpseGateway import CtpseGateway

gatewayClass = CtpseGateway
gatewayName = 'CTPSE'
gatewayDisplayName = 'CTPSE'
gatewayType = vtConstant.GATEWAYTYPE_FUTURES
gatewayQryEnabled = True
