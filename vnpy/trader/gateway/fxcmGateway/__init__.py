# encoding: UTF-8

from __future__ import absolute_import
from vnpy.trader import vtConstant
from .fxcmGateway import FxcmGateway

gatewayClass = FxcmGateway
gatewayName = 'FXCM'
gatewayDisplayName = u'福汇'
gatewayType = vtConstant.GATEWAYTYPE_INTERNATIONAL
gatewayQryEnabled = False
