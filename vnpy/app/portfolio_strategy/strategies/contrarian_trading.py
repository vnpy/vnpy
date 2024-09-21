from vnpy.app.portfolio_strategy import StrategyTemplate


class ContrarianStrategy(StrategyTemplate):
    """"""

    author = 'chen'

    # Define parameters
    trailing_percent = 0.6
    profit_taking = 2.0
    stop_loss = 2.0

    # Define variables
    btc_ratio = 0.7
    index_return = 0.0

    # Define factors
    close_price: dict[str, float] = {}

    # Define variables
    parameters = [
        'trailing_percent',
        'profit_taking',
        'stop_loss'
    ]

    variables = [
        'btc_ratio',
        'index_return'
    ]

    factors = [
        'close_price',
    ]

    def __init__(self, strategy_engine, strategy_name, vt_symbols, setting):
        """"""
        super().__init__(strategy_engine, strategy_name, vt_symbols, setting)

        for vt_symbol in vt_symbols:
            self.close_price[vt_symbol] = 0.0

    def on_factor_updated(self) -> None:
        """"""
        self.write_log('factor ready')
        return



