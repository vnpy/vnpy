# encoding: UTF-8

from __future__ import absolute_import
from vnpy.trader import vtConstant
from .oandaGateway import OandaGateway

gatewayClass = OandaGateway
gatewayName = "OANDA"
gatewayDisplayName = gatewayName
gatewayType = vtConstant.GATEWAYTYPE_INTERNATIONAL
gatewayQryEnabled = True
