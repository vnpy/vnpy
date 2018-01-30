# encoding: UTF-8

from vnpy.trader.app.ctaStrategy.ctaEngine import CtaEngine
from vnpy.trader.app.ctaStrategy.uiCtaWidget import CtaEngineManager

appName = 'CtaStrategy'
appDisplayName = u'CTA策略'
appEngine = CtaEngine
appWidget = CtaEngineManager
appIco = 'cta.ico'