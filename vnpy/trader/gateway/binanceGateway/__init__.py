# encoding: UTF-8

from vnpy.trader import vtConstant
from .binanceGateway import BinanceGateway

gatewayClass = BinanceGateway
gatewayName = 'BINANCE'
gatewayDisplayName = u'币安'
gatewayType = vtConstant.GATEWAYTYPE_BTC
gatewayQryEnabled = True