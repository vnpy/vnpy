# encoding: UTF-8

from __future__ import absolute_import
from vnpy.trader import vtConstant
from .ctptestGateway import CtptestGateway

gatewayClass = CtptestGateway
gatewayName = 'CTPTEST'
gatewayDisplayName = 'CTPTEST'
gatewayType = vtConstant.GATEWAYTYPE_FUTURES
gatewayQryEnabled = True
