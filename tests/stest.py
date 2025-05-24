from vnpy.event.engine import EventEngine
from vnpy.strategy.engine import StrategyEngine
from vnpy.trader.engine import MainEngine


if __name__ == '__main__':
    event_engine = EventEngine()
    main_engine = MainEngine(event_engine)
    main_engine.write_log("Main engine created successfully")
    main_engine.vt_symbols = ['btcusdt.BINANCE', 'ethusdt.BINANCE']

    # start factor engine
    strategy_engine: StrategyEngine = main_engine.add_engine(StrategyEngine)
    strategy_engine.init_engine()
    print(strategy_engine.strategies.__class__)
    strategy_engine.close()
    exit(0)
