# encoding: UTF-8

from __future__ import absolute_import
from vnpy.trader import vtConstant
from .zbGateway import zbGateway

gatewayClass = zbGateway
gatewayName = 'ZB'
gatewayDisplayName = u'ZB'
gatewayType = vtConstant.GATEWAYTYPE_BTC
gatewayQryEnabled = True

