# encoding: UTF-8

from vnpy.trader import vtConstant
from .bitfinexGateway import BitfinexGateay

gatewayClass = BitfinexGateay
gatewayName = 'BITFINEX'
gatewayDisplayName = u'BITFINEX'
gatewayType = vtConstant.GATEWAYTYPE_BTC
gatewayQryEnabled = True