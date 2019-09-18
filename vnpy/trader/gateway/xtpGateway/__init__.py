# encoding: UTF-8

from __future__ import absolute_import
from vnpy.trader import vtConstant
from .xtpGateway import XtpGateway

gatewayClass = XtpGateway
gatewayName = 'XTP'
gatewayDisplayName = 'XTP'
gatewayType = vtConstant.GATEWAYTYPE_EQUITY
gatewayQryEnabled = True
