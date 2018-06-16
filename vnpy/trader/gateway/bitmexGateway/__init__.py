# encoding: UTF-8

from vnpy.trader import vtConstant
from .bitmexGateway import BitmexGateay

gatewayClass = BitmexGateay
gatewayName = 'BITMEX'
gatewayDisplayName = 'BITMEX'
gatewayType = vtConstant.GATEWAYTYPE_BTC
gatewayQryEnabled = False