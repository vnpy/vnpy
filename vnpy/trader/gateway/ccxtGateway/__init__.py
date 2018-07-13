# encoding: UTF-8

from vnpy.trader import vtConstant
from .ccxtGateway import CcxtGateway

gatewayClass = CcxtGateway
gatewayName = 'CCXT'
gatewayDisplayName = 'CCXT'
gatewayType = vtConstant.GATEWAYTYPE_BTC
gatewayQryEnabled = True