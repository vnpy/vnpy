# encoding: UTF-8

from __future__ import absolute_import
from vnpy.trader import vtConstant
from .ctpGateway import CtpGateway

gatewayClass = CtpGateway
gatewayName = 'CTP'
gatewayDisplayName = 'CTP'
gatewayType = vtConstant.GATEWAYTYPE_FUTURES
gatewayQryEnabled = True
