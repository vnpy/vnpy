# encoding: UTF-8

from __future__ import absolute_import
from vnpy.trader import vtConstant
from .lbankGateway import LbankGateway

gatewayClass = LbankGateway
gatewayName = 'LBANK'
gatewayDisplayName = u'LBANK'
gatewayType = vtConstant.GATEWAYTYPE_BTC
gatewayQryEnabled = True
