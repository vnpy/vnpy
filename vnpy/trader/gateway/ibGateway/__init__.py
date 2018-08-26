# encoding: UTF-8

from __future__ import absolute_import
from vnpy.trader import vtConstant
from .ibGateway import IbGateway

gatewayClass = IbGateway
gatewayName = 'IB'
gatewayDisplayName = gatewayName
gatewayType = vtConstant.GATEWAYTYPE_INTERNATIONAL
gatewayQryEnabled = False