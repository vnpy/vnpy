# encoding: UTF-8

from __future__ import absolute_import
from vnpy.trader import vtConstant
from .huobiGateway import HuobiGateway

gatewayClass = HuobiGateway
gatewayName = 'HUOBI'
gatewayDisplayName = u'火币'
gatewayType = vtConstant.GATEWAYTYPE_BTC
gatewayQryEnabled = True