from collections import deque
from abc import abstractmethod
from typing import Optional, Dict, Tuple, Any

from vnpy.app.factor_maker.engine import FactorEngine
from vnpy.trader.constant import Exchange, Interval
from vnpy.trader.object import TickData, BarData, FactorData
import polars as pl


class FactorTemplate(object):
    """"""
    VTSYMBOL_TEMPLATE_FACTOR = "factor_{}_{}_{}.{}"  # interval, symbol(ticker), name(factor name), exchange

    author: str = ""
    parameters: list = []
    variables: list = []

    factor_name: str = ""
    freq: Optional[Interval] = None
    symbol: str = ""
    exchange: Exchange = None

    dependencies_factor: list[str] = []
    dependencies_freq: list[Interval] = []
    dependencies_symbol: list[str] = []
    dependencies_exchange: list[Exchange] = []

    def __init__(self, engine, setting: dict, **kwargs):
        """
        Initialize the factor template with the given engine and settings.

        Parameters:
            engine (FactorEngine): The factor engine instance.
            setting (dict): Settings for the factor.
        """
        self.engine = engine  # Type: FactorEngine
        self.setting: Dict[str, Any] = setting

        # Update instance attributes based on settings
        self.update_setting(setting)

        # Unique identifier for the factor
        self.factor_key: str = self.VTSYMBOL_TEMPLATE_FACTOR.format(
            interval=self.freq.value if self.freq else "",
            symbol=self.symbol,
            factor_name=self.factor_name,
            exchange=self.exchange.value
        )

        # Status of dependencies (if any)
        self.status: Dict[Tuple[str, str], bool] = {
            (dep_symbol, dep_factor): False
            for dep_symbol in self.dependencies_symbol
            for dep_factor in self.dependencies_factor
        }

        # Internal state
        self.inited: bool = False
        self.trading: bool = False

    def update_setting(self, setting: Dict[str, Any]) -> None:
        """
        Update the factor's settings.

        Parameters:
            setting (dict): Dictionary of settings to update.
        """
        for key in self.parameters:
            if key in setting:
                setattr(self, key, setting[key])

    def set_params(self, params: Dict[str, Any]) -> None:
        """
        Set the factor's parameters dynamically.

        Parameters:
            params (dict): Dictionary of parameter names and values to set.
        """
        for key, value in params.items():
            setattr(self, key, value)

    def on_init(self) -> None:
        """
        Callback when the factor is initialized.
        """
        self.inited = True
        self.engine.write_log(f"{self.factor_key} initialized.")

    def on_start(self) -> None:
        """
        Callback when the factor starts.
        """
        self.trading = True
        self.engine.write_log(f"{self.factor_key} started.")

    def on_stop(self) -> None:
        """
        Callback when the factor stops.
        """
        self.trading = False
        self.engine.write_log(f"{self.factor_key} stopped.")

    @abstractmethod
    def on_tick(self, tick: TickData) -> None:
        """
        Callback of new tick data update.

        Parameters:
            tick (TickData): Tick data.
        """
        pass

    @abstractmethod
    def on_bar(self, bar: BarData) -> None:
        """
        Callback of new bar data update.

        Parameters:
            bar (BarData): Bar data.
        """
        pass

    @abstractmethod
    def on_factor(self, factor: FactorData) -> None:
        """
        Callback of new factor data update (from dependencies).

        Parameters:
            factor (FactorData): Factor data.
        """
        pass

    def on_timer(self) -> None:
        """
        Callback of timer update.
        """
        pass

    def wrap_data(self, bar: BarData, value: float) -> FactorData:
        """
        Wrap bar data and factor value into a FactorData object.

        Parameters:
            bar (BarData): Bar data.
            value (float): Factor value.

        Returns:
            FactorData: Wrapped factor data.
        """
        return FactorData(
            symbol=bar.symbol,
            exchange=bar.exchange,
            datetime=bar.datetime,
            interval=bar.interval,
            value=value,
            factor_name=self.factor_name,
            gateway_name="factor_template"
        )

    def on_bars(self, bars: dict[str, BarData]) -> None:
        """"""
        pass

    def get_parameters(self) -> Dict[str, Any]:
        """
        Get the parameters of the factor.

        Returns:
            dict: Dictionary of parameter names and values.
        """
        return {name: getattr(self, name) for name in self.parameters}

    def get_variables(self) -> Dict[str, Any]:
        """
        Get the variables of the factor.

        Returns:
            dict: Dictionary of variable names and values.
        """
        return {name: getattr(self, name) for name in self.variables if name not in ["inited", "trading"]}

    @classmethod
    def get_class_parameters(cls) -> Dict[str, Any]:
        """
        Get the default parameters of the factor class.

        Returns:
            dict: Dictionary of default parameter names and values.
        """
        return {name: getattr(cls, name) for name in cls.parameters}

    def get_data(self) -> Dict[str, Any]:
        """
        Get the data representing the factor's state.

        Returns:
            dict: Dictionary containing factor data.
        """
        return {
            "factor_name": self.factor_key,
            "class_name": self.__class__.__name__,
            "author": self.author,
            "parameters": self.get_parameters(),
            "variables": self.get_variables()
        }

    @abstractmethod
    def calculate_polars(self, input_data: pl.DataFrame, *args, **kwargs) -> Any:
        """
        Calculate the factor value using Polars DataFrame.

        Parameters:
            input_data (pl.DataFrame): Input data for calculation.

        Returns:
            Any: Calculated factor value(s).
        """
        pass

    @abstractmethod
    def make_factor(self, bar_data_dict: dict[str, pl.DataFrame]) -> pl.DataFrame:
        """
        Generate factor values from historical bar data.

        Parameters:
            bar_data_dict (dict[str, pl.DataFrame]): Historical bar data.

        Returns:
            pl.DataFrame: Factor values.
        """
        pass
