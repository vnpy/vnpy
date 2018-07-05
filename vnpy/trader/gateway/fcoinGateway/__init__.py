# encoding: UTF-8

from vnpy.trader import vtConstant
from .fcoinGateway import FcoinGateway

gatewayClass = FcoinGateway
gatewayName = 'FCOIN'
gatewayDisplayName = 'FCOIN'
gatewayType = vtConstant.GATEWAYTYPE_BTC
gatewayQryEnabled = True