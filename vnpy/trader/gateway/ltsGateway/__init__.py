# encoding: UTF-8

from __future__ import absolute_import
from vnpy.trader import vtConstant
from .ltsGateway import LtsGateway

gatewayClass = LtsGateway
gatewayName = 'LTS'
gatewayDisplayName = gatewayName
gatewayType = vtConstant.GATEWAYTYPE_EQUITY
gatewayQryEnabled = True