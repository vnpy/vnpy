# encoding: UTF-8

from __future__ import absolute_import
from vnpy.trader import vtConstant
from .ksotpGateway import KsotpGateway

gatewayClass = KsotpGateway
gatewayName = 'KSOTP'
gatewayDisplayName = u'金仕达期权'
gatewayType = vtConstant.GATEWAYTYPE_EQUITY
gatewayQryEnabled = True

