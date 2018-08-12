# encoding: UTF-8

from vnpy.trader import vtConstant
from .bigoneGateway import BigoneGateway

gatewayClass = BigoneGateway
gatewayName = 'BIGONE'
gatewayDisplayName = 'BIGONE'
gatewayType = vtConstant.GATEWAYTYPE_BTC
gatewayQryEnabled = True