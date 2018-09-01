# encoding: UTF-8

from vnpy.trader.app.cmaStrategy.cmaEngine import CmaEngine
from vnpy.trader.app.cmaStrategy.uiCmaWidget import CmaEngineManager

appName = 'CrossMarketArbitrage'
appDisplayName = u'跨市场套利'
appEngine = CmaEngine
appWidget = CmaEngineManager
appIco = 'cma.ico'