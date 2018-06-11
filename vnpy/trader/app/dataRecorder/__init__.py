# encoding: UTF-8

from __future__ import absolute_import
from .drEngine import DrEngine
from .uiDrWidget import DrEngineManager

appName = 'DataRecorder'
appDisplayName = u'行情记录'
appEngine = DrEngine
appWidget = DrEngineManager
appIco = 'dr.ico'