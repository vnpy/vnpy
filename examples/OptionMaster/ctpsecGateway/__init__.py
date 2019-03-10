# encoding: UTF-8

from vnpy.trader import vtConstant
from vnpy.trader.gateway.ctpGateway import CtpGateway

gatewayClass = CtpGateway
gatewayName = 'CTPSEC'
gatewayDisplayName = 'CTP证券'
gatewayType = vtConstant.GATEWAYTYPE_FUTURES
gatewayQryEnabled = True
