# encoding: UTF-8

from vnpy.trader import vtConstant
from .fcoinGateway import FcoinGateay

gatewayClass = FcoinGateay
gatewayName = 'FCOIN'
gatewayDisplayName = 'FCOIN'
gatewayType = vtConstant.GATEWAYTYPE_BTC
gatewayQryEnabled = True