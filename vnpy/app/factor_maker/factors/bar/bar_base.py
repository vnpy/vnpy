from typing import Any

import polars as pl

from vnpy.app.factor_maker.base import RollingDataFrame
from vnpy.app.factor_maker.template import FactorTemplate


class BarFactor(FactorTemplate):
    factor_name = ""
    dependencies_factor = []

    def __init__(self, freq, **kwargs):
        super().__init__(**kwargs)
        self.add_params("freq")

        self.freq = freq


class OPEN(BarFactor):
    factor_name = 'open'

    def __init__(self, **kwargs):
        super().__init__(**kwargs)


class HIGH(BarFactor):
    factor_name = 'high'

    def __init__(self, **kwargs):
        super().__init__(**kwargs)


class LOW(BarFactor):
    factor_name = 'low'

    def __init__(self, **kwargs):
        super().__init__(**kwargs)


class CLOSE(BarFactor):
    factor_name = 'close'

    def __init__(self, **kwargs):
        super().__init__(**kwargs)


class VOLUME(BarFactor):
    factor_name = 'volume'

    def __init__(self, **kwargs):
        super().__init__(**kwargs)
