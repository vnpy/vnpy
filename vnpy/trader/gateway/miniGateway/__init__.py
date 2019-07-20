# encoding: UTF-8

from __future__ import absolute_import
from vnpy.trader import vtConstant
from .miniGateway import MiniGateway

gatewayClass = MiniGateway
gatewayName = 'MINI'
gatewayDisplayName = 'MINI'
gatewayType = vtConstant.GATEWAYTYPE_FUTURES
gatewayQryEnabled = True
