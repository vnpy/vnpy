# encoding: UTF-8

from __future__ import absolute_import
from vnpy.trader import vtConstant
from .xspeedGateway import XspeedGateway

gatewayClass = XspeedGateway
gatewayName = 'XSPEED'
gatewayDisplayName = u'飞创'
gatewayType = vtConstant.GATEWAYTYPE_FUTURES
gatewayQryEnabled = True