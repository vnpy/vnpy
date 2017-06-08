# encoding: UTF-8

from strategyEngine import *
from backtestingEngine import *
from demoStrategy import SimpleEmaStrategy



# 回测脚本    
if __name__ == '__main__':
    symbol = 'IF1506'
    
    # 创建回测引擎
    be = BacktestingEngine()
    
    # 创建策略引擎对象
    se = StrategyEngine(be.eventEngine, be, backtesting=True)
    be.setStrategyEngine(se)
    
    # 初始化回测引擎
    be.connectMongo()
    be.loadDataHistory(symbol, datetime(2015,5,1), datetime.today())
    
    # 创建策略对象
    setting = {}
    setting['fastAlpha'] = 0.2
    setting['slowAlpha'] = 0.05
    setting['startDate'] = datetime(year=2015, month=5, day=20)
    se.createStrategy(u'EMA演示策略', symbol, SimpleEmaStrategy, setting)
    
    # 启动所有策略
    se.startAll()
    
    # 开始回测
    be.startBacktesting()
    

