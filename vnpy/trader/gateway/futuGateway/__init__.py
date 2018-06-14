# encoding: UTF-8

from __future__ import absolute_import
from vnpy.trader import vtConstant
from .futuGateway import FutuGateway

gatewayClass = FutuGateway
gatewayName = 'FUTU'
gatewayDisplayName = u'富途证券'
gatewayType = vtConstant.GATEWAYTYPE_INTERNATIONAL
gatewayQryEnabled = True
