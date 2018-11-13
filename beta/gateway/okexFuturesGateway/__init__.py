# encoding: UTF-8

from __future__ import absolute_import
from vnpy.trader import vtConstant
from .okexFuturesGateway import OkexFuturesGateway

gatewayClass = OkexFuturesGateway
gatewayName = "OKEXFUTURES"
gatewayDisplayName = "OKEXFUTURES"
gatewayType = vtConstant.GATEWAYTYPE_BTC
gatewayQryEnabled = True
