# encoding: UTF-8

from __future__ import absolute_import
from vnpy.trader import vtConstant
from .okexGateway import OkexGateway

gatewayClass = OkexGateway
gatewayName = 'OKEX'
gatewayDisplayName = u'OKEX'
gatewayType = vtConstant.GATEWAYTYPE_BTC
gatewayQryEnabled = True

