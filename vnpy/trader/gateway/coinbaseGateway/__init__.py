# encoding: UTF-8

from vnpy.trader import vtConstant
from .coinbaseGateway import CoinbaseGateway

gatewayClass = CoinbaseGateway
gatewayName = 'COINBASE'
gatewayDisplayName = 'COINBASE'
gatewayType = vtConstant.GATEWAYTYPE_BTC
gatewayQryEnabled = True