from vnpy.app.cta_strategy import CtaTemplate


class DoubleMaStrategy(CtaTemplate):
    author = "用Python的交易员"

    fast_window = 10
    slow_window = 20.10

    fast_ma = 0.0
    slow_ma = 0.0

    parameters = ["fast_window", "slow_window"]
    variables = ["fast_ma", "slow_ma"]

    def __init__(self, cta_engine, strategy_name, vt_symbol, setting):
        """"""
        super(DoubleMaStrategy, self).__init__(
            cta_engine, strategy_name, vt_symbol, setting
        )
