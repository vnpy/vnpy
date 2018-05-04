# encoding: UTF-8

from okex_error_info import *
from vnpy.trader import vtConstant
from okexGateway import okexGateway , Api_contract , Api_Spot


gatewayClass = okexGateway
gatewayName = 'OKEX'
gatewayDisplayName = u'OKEX'
gatewayType = vtConstant.GATEWAYTYPE_BTC
gatewayQryEnabled = True

