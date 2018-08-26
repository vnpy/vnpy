# encoding: UTF-8

from vnpy.trader import vtConstant
from .bitmexGateway import BitmexGateway

gatewayClass = BitmexGateway
gatewayName = 'BITMEX'
gatewayDisplayName = 'BITMEX'
gatewayType = vtConstant.GATEWAYTYPE_BTC
gatewayQryEnabled = False