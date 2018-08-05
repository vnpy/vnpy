# encoding: UTF-8

from __future__ import absolute_import
from .jsEngine import JsEngine
from .uiJsWidget import JsEngineManager

appName = 'JaqsService'
appDisplayName = u'Jaqs服务'
appEngine = JsEngine
appWidget = JsEngineManager
appIco = 'js.ico'