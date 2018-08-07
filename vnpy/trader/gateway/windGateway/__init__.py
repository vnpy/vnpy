# encoding: UTF-8

from __future__ import absolute_import
from vnpy.trader import vtConstant
from .windGateway import WindGateway

gatewayClass = WindGateway
gatewayName = 'WIND'
gatewayDisplayName = u'万得'
gatewayType = vtConstant.GATEWAYTYPE_DATA
gatewayQryEnabled = False
