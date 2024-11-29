from abc import abstractmethod, ABC
from typing import Optional, Dict, Any, Union, List

import polars as pl

from vnpy.app.factor_maker.base import FactorMode
from vnpy.trader.constant import Exchange, Interval


class FactorParameters(object):

    def __init__(self, params: Optional[Dict[str, Any]] = None) -> None:
        if params is not None:
            for key, value in params.items():
                setattr(self, key, value)

    def __str__(self):
        # 思考了一下还是应该带上参数值, 这样才能唯一地标识一个factor
        if len(self.__dict__) == 0:
            return "noparams"
        return "-".join([f"{k}_{v}" for k, v in self.__dict__.items()])

    def __iter__(self):
        return iter(self.__dict__.items())

    def __contains__(self, item):
        return hasattr(self, item)

    def set_parameters(self, params: Dict[str, Any]) -> None:
        # assert params is not None and len(params) > 0
        for key, value in params.items():
            if getattr(self, key, None) is not None:
                print(f"Parameter {key} is updated: {getattr(self, key)} -> {value}")
            setattr(self, key, value)

    def get_parameter(self, key: str) -> Any:
        p = getattr(self, key)
        return p

    def get_all_parameters(self) -> Dict[str, Any]:
        return self.__dict__

    def del_parameters(self, key: Union[str, List[str]]) -> None:
        if isinstance(key, str):
            if key in self.__dict__.keys():
                delattr(self, key)
        elif isinstance(key, list):
            for k in key:
                if k in self.__dict__.keys():
                    delattr(self, k)

    def to_str(self, with_value=True) -> str:
        """Convert the parameters to a string.

        Parameters
        ----------
        with_value : bool
            Whether to include the value of the parameters.
        """
        if with_value:
            return self.__str__()
        else:
            if len(self.__dict__) == 0:
                return "noparams"
            return "-".join([f"{k}" for k in self.__dict__.keys()])

    def items(self):
        return self.__dict__.items()


class FactorTemplate(ABC):
    """
    Each factor inherited from this class must implement:
    1. add_params: add parameters to the attribute "params", so that we can recognize this parameter later
    2. @property, @getter, @setter: define the getter and setter of the parameter

    Examples
    --------
    >>> @property
    >>> def window(self):
    >>>     return self.params.get_parameter("window")
    >>> @window.setter
    >>> def window(self, value):
    >>>     self.params.set_parameters({"window": value})
    >>> @window.getter
    >>> def window(self):
    >>>     return self.params.get_parameter("window")
    >>> def __init__(self, **kwargs):
    >>>     super().__init__(**kwargs)
    >>>     self.add_params(
    >>>         ["window"])  # add parameters to the attribute "params", so that we can recognize this parameter later

    """
    # VTSYMBOL_TEMPLATE_FACTOR = "factor_{}_{}_{}.{}"  # interval, symbol(ticker), name(factor name), exchange

    author: str = ""
    params: FactorParameters = FactorParameters()  # 新增字段, 希望用一个class来存储参数数据, 并且能方便地save json/load json

    factor_name: str = ""
    freq: Optional[Interval] = None
    symbol: str = ""
    exchange: Exchange = Exchange.TEST

    dependencies_factor: list[str] = []
    dependencies_freq: list[Interval] = []
    dependencies_symbol: list[str] = []
    dependencies_exchange: list[Exchange] = []

    factor_mode: FactorMode = None

    @property
    def factor_key(self) -> str:
        """
        Get the factor name key.
        """
        return f"{self.factor_name}@{self.params.to_str(with_value=True)}"

    def __init__(self, setting: Optional[Dict] = None, **kwargs):
        """
        Initialize the factor template with the given engine and settings.

        Parameters:
            setting (dict): Settings for the factor.
            kwargs: Additional parameters.
        """
        self.from_dict(setting)
        self.set_params(kwargs)

        # Internal state
        self.inited: bool = False
        self.trading: bool = False

    def add_params(self, param_names: Union[str, List[str]], auto_property: bool = True) -> None:
        """
        Add parameters to the factor.

        This method registers new parameters by setting them in the `params` object.
        If `auto_property` is True, it automatically creates properties (getter and setter)
        for each parameter if they are not already defined.

        Parameters
        ----------
        param_names : Union[str, List[str]]
            Name(s) of the parameter(s) to add.
        auto_property : bool, optional
            If True, automatically creates properties (getter and setter) for the parameter(s).

        Notes
        -----
        This method can be used during the factor's initialization or dynamically
        during runtime to add new parameters.

        Raises
        ------
        AttributeError
            If a parameter does not have a corresponding property and `auto_property` is False.
        """
        # Ensure param_names is a list
        if isinstance(param_names, str):
            param_names = [param_names]

        # Add parameters to the params object
        self.params.set_parameters({param: None for param in param_names})

        # Ensure each parameter has a property
        for attr_name in param_names:
            attr = getattr(self.__class__, attr_name, None)

            # If the property doesn't exist, create it if auto_property is True
            if not isinstance(attr, property):
                if auto_property:
                    # Define getter and setter dynamically
                    def getter(self, name=attr_name):
                        return self.params.get_parameter(name)

                    def setter(self, value, name=attr_name):
                        self.params.set_parameters({name: value})

                    # Attach the property dynamically to the class
                    setattr(self.__class__, attr_name, property(getter, setter))
                    print(f"Created property for parameter: {attr_name}")
                else:
                    raise AttributeError(
                        f"The parameter '{attr_name}' must have a corresponding property "
                        f"(with a getter and setter) defined in the class, or set `auto_property=True`."
                    )
            else:
                # Check and log existing property parts
                print(f"{attr_name} is a property")
                if attr.fget:
                    print(f"  - Getter is defined")
                if attr.fset:
                    print(f"  - Setter is defined")
                if attr.fdel:
                    print(f"  - Deleter is defined")

    def set_params(self, params_dict: Dict[str, Any]) -> None:
        """
        Set the parameters of the factor.
        """
        for key, value in params_dict.items():
            if key in self.params:
                setattr(self, key, value)
            else:
                raise ValueError(f"Parameter {key} is not recognized.")

    def get_params(self):
        """
        Get the parameters of the factor.

        Returns:
            dict: Dictionary of parameter names and values.
        """
        return self.params.items()

    def on_init(self) -> None:
        """
        Callback when the factor is initialized.
        """
        if self.factor_mode == FactorMode.Backtest:
            pass
        self.inited = True

    def on_start(self) -> None:
        """
        Callback when the factor starts.
        """
        if self.factor_mode == FactorMode.Backtest:
            pass
        self.trading = True

    def on_stop(self) -> None:
        """
        Callback when the factor stops.
        """
        if self.factor_mode == FactorMode.Backtest:
            pass
        self.trading = False

    @abstractmethod
    def calculate(self, input_data: pl.DataFrame, *args, **kwargs) -> Any:
        """
        Calculate the factor value

        Parameters:
            input_data (pl.DataFrame): Input data for calculation.

        Returns:
            Any: Calculated factor value(s).
        """
        pass

    def from_dict(self, dic: Optional[Dict] = None) -> None:
        """
        Restore the factor template from a dictionary.
        """
        if dic is None:
            return
        self.params.set_parameters(dic.get("params", {}))
        self.dependencies_factor = dic.get("dependencies_factor", [])
        self.dependencies_freq = dic.get("dependencies_freq", [])
        self.dependencies_symbol = dic.get("dependencies_symbol", [])
        self.dependencies_exchange = dic.get("dependencies_exchange", [])

    def to_dict(self) -> dict:
        """
        Convert the factor template to a dictionary.
        """
        return {
            self.factor_key: {
                "class_name": self.__class__.__name__,
                "params": self.params.get_all_parameters(),
                "dependencies_factor": self.dependencies_factor,
                "dependencies_freq": self.dependencies_freq,
                "dependencies_symbol": self.dependencies_symbol,
                "dependencies_exchange": self.dependencies_exchange
            }
        }
