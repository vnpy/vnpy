from vnpy.app.factor_maker.template import FactorTemplate

class MA10_BASE(FactorTemplate):

    def calculate(self):
        value=0
        return value

class MA10_F1(FactorTemplate):
    def __init__(self, settings):
        self.factor_name = 'ma10'
        self.symbol = settings['symbol']

        self.vt_symbol = ''

        self.dependencies = ['open', 'volume', 'macd']

class MA10_F2(FactorTemplate):
    def __init__(self, settings):
        self.factor_name = 'ma10'
        self.symbol = settings['symbol']

        self.vt_symbol = ''

        self.dependencies = ['open', 'volume', 'macd']


class MA10_F3(FactorTemplate):
    def __init__(self, settings):
        self.factor_name = 'ma10'
        self.symbol = settings['symbol']

        self.vt_symbol = ''

        self.dependencies = ['open', 'volume', 'macd']