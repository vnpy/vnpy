# encoding: UTF-8

from __future__ import absolute_import
from vnpy.trader import vtConstant
from .sgitGateway import SgitGateway

gatewayClass = SgitGateway
gatewayName = 'SGIT'
gatewayDisplayName = u'飞鼠'
gatewayType = vtConstant.GATEWAYTYPE_FUTURES
gatewayQryEnabled = True
