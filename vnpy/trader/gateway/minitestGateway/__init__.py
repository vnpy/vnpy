# encoding: UTF-8

from __future__ import absolute_import
from vnpy.trader import vtConstant
from .minitestGateway import MinitestGateway

gatewayClass = MinitestGateway
gatewayName = 'MINITEST'
gatewayDisplayName = 'MINITEST'
gatewayType = vtConstant.GATEWAYTYPE_FUTURES
gatewayQryEnabled = True
