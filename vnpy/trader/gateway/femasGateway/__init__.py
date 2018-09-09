# encoding: UTF-8

from __future__ import absolute_import
from vnpy.trader import vtConstant
from .femasGateway import FemasGateway

gatewayClass = FemasGateway
gatewayName = 'FEMAS'
gatewayDisplayName = u'飞马'
gatewayType = vtConstant.GATEWAYTYPE_FUTURES
gatewayQryEnabled = True
