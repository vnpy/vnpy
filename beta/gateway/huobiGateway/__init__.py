# encoding: UTF-8

from vnpy.trader import vtConstant
from huobiGateway import huobiGateway , HuobiTradeApi , HuobiDataApi , HuobiSocketDataApi

gatewayClass = huobiGateway
gatewayName = 'HUOBI'
gatewayDisplayName = u'HUOBI'
gatewayType = vtConstant.GATEWAYTYPE_BTC
gatewayQryEnabled = True

