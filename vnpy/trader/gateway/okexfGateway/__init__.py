# encoding: UTF-8

from __future__ import absolute_import
from vnpy.trader import vtConstant
from .okexfGateway import OkexfGateway

gatewayClass = OkexfGateway
gatewayName = "OKEXF"
gatewayDisplayName = "OKEXF"
gatewayType = vtConstant.GATEWAYTYPE_BTC
gatewayQryEnabled = True
