# encoding: UTF-8

from __future__ import absolute_import
from .rmEngine import RmEngine
from .uiRmWidget import RmEngineManager

appName = 'RiskManager'
appDisplayName = u'风险管理'
appEngine = RmEngine
appWidget = RmEngineManager
appIco = 'rm.ico'
