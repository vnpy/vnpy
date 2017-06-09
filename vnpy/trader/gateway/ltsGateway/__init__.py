# encoding: UTF-8

from vnpy.trader import vtConstant
from ltsGateway import LtsGateway

gatewayClass = LtsGateway
gatewayName = 'LTS'
gatewayDisplayName = gatewayName
gatewayType = vtConstant.GATEWAYTYPE_EQUITY
gatewayQryEnabled = True