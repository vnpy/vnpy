from abc import abstractmethod, ABC
from datetime import datetime
from typing import Optional, Dict, Any, Union, List, Type, TypeVar
import importlib
import polars as pl
from dask.delayed import Delayed

from vnpy.app.factor_maker.base import FactorMode
from vnpy.trader.constant import Exchange, Interval
from vnpy.config import VTSYMBOL_FACTOR


class FactorParameters(object):

    def __init__(self, params: Optional[Dict[str, Any]] = None) -> None:
        """
        Initialize the FactorParameters object.

        Parameters:
            params (Optional[Dict[str, Any]]): A dictionary of parameter names and values.
        """
        if params is not None:
            for key, value in params.items():
                setattr(self, key, value)

    def __str__(self) -> str:
        """
        Convert the parameters to a string representation.

        Returns:
            str: A string representation of the parameters.
        """
        if len(self.__dict__) == 0:
            return "noparams"
        return "-".join([f"{k}_{v}" for k, v in self.__dict__.items()])

    def __iter__(self):
        """
        Iterate over the parameters.

        Returns:
            Iterator: An iterator over the parameter items.
        """
        return iter(self.__dict__.items())

    def __contains__(self, item):
        """
        Check if a parameter exists.

        Parameters:
            item (str): The parameter name.

        Returns:
            bool: True if the parameter exists, False otherwise.
        """
        return hasattr(self, item)

    def set_parameters(self, params: Dict[str, Any]) -> None:
        """
        Set or update parameters.

        Parameters:
            params (Dict[str, Any]): A dictionary of parameter names and values.
        """
        for key, value in params.items():
            if getattr(self, key, None) is not None:
                print(f"Parameter {key} is updated: {getattr(self, key)} -> {value}")
            setattr(self, key, value)

    def get_parameter(self, key: str) -> Any:
        """
        Get the value of a parameter.

        Parameters:
            key (str): The parameter name.

        Returns:
            Any: The value of the parameter.
        """
        return getattr(self, key)
        
    def get_all_parameters(self) -> Dict[str, Any]:
        """
        Get all parameters as a dictionary.

        Returns:
            Dict[str, Any]: A dictionary of all parameters.
        """
        return self.__dict__

    def del_parameters(self, key: Union[str, List[str]]) -> None:
        """
        Delete one or more parameters.

        Parameters:
            key (Union[str, List[str]]): The parameter name(s) to delete.
        """
        if isinstance(key, str):
            if key in self.__dict__.keys():
                delattr(self, key)
        elif isinstance(key, list):
            for k in key:
                if k in self.__dict__.keys():
                    delattr(self, k)

    def to_str(self, with_value: bool = True) -> str:
        """
        Convert the parameters to a string.

        Parameters:
        with_value (bool): Whether to include the values of the parameters.

        Returns:
            str: A string representation of the parameters.
        """
        if with_value:
            return self.__str__()
        else:
            if len(self.__dict__) == 0:
                return "noparams"
            return "-".join([f"{k}" for k in self.__dict__.keys()])

    def items(self):
        """
        Get all parameter items.

        Returns:
            ItemsView: A view of the parameter items.
        """
        return self.__dict__.items()


class FactorTemplate(ABC):
    """
    """
    # VTSYMBOL_TEMPLATE_FACTOR = "factor_{}_{}_{}.{}"  # interval, symbol(ticker), name(factor name), exchange

    author: str = ""
    module = None  # import all factors in the factors folder, get the class by getattr(module, class_name)

    factor_name: str = ""
    freq: Optional[Interval] = None
    symbol: str = ""
    exchange: Exchange = Exchange.TEST

    dependencies_factor: List[Any] = []
    dependencies_freq: List[Interval] = []
    dependencies_symbol: List[str] = []
    dependencies_exchange: List[Exchange] = []

    factor_mode: FactorMode = None
    VTSYMBOL_TEMPLATE: str = VTSYMBOL_FACTOR

    @property
    def factor_key(self) -> str:
        """
        Get the unique key for the factor.

        Returns:
            str: The unique key for the factor.
        """
        return f"{self.VTSYMBOL_TEMPLATE.format(interval=self.freq.value, factorname=self.factor_name)}@{self.params.to_str(with_value=True)}"  # 20250208 modified

    def __init_dependencies__(self):
        """
        1. Initialize the dependencies_factor list with the given settings.
        2. binding dependencies with explicit indicator.
            e.g. macd depends on ma10 and ma20, so we need to initialize ma10 and ma20 first. then bind them to fast and slow
        Returns
        -------

        """
        dependencies_factor_initialized = []
        for f_setting in self.dependencies_factor:  # list of dicts
            for module_name, module_setting in f_setting.items():
                f_class: Type[TV_FactorTemplate] = getattr(self.module, module_setting["class_name"])
                f_class = f_class(module_setting, **module_setting["params"])  # recursion
                dependencies_factor_initialized.append(f_class)

        self.dependencies_factor = dependencies_factor_initialized

    def __init__(self, setting: Optional[dict] = None, **kwargs):
        """
        Initialize the factor template with the given engine and settings.

        Parameters:
            setting (dict): Settings for the factor.
            kwargs: Additional parameters.
        """
        self.params: FactorParameters = FactorParameters()
        self.module = importlib.import_module(".factors", package=__package__)
        self.from_setting(setting)
        self.set_params(kwargs)
        self.__init_dependencies__()

        # Internal state
        self.inited: bool = False
        self.trading: bool = False

        self.on_init()
        self.on_start()

        self.run_datetime: str = self.update_datetime()

    def update_datetime(self) -> str:
        """
        Update the run datetime.

        Returns:
            str: The updated run datetime.
        """
        run_datetime = datetime.now().strftime("%Y-%m-%d %H:%M:%S")
        return run_datetime
    
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
                else:
                    raise AttributeError(
                        f"The parameter '{attr_name}' must have a corresponding property "
                        f"(with a getter and setter) defined in the class, or set `auto_property=True`."
                    )
            else:
                return  # If the property already exists, do nothing

    def set_params(self, params_dict: Dict[str, Any]) -> None:
        """
        Set the parameters of the factor.

        Parameters:
            params_dict (Dict[str, Any]): A dictionary of parameter names and values.
        """
        for key, value in params_dict.items():
            if hasattr(self, key):
                if value is not None:
                    print(f"Parameter {key} is updated: {getattr(self, key)} -> {value}")
                    # setattr(self.params.set_parameters({key:value}), key, value)
                    self.params.set_parameters({key: value})
            else:
                self.add_params(key)
                print(f"Parameter {key} is set: {value}")
                self.params.set_parameters({key: value})

    def get_params(self):
        """
        Get the parameters of the factor.

        Returns:
            dict: Dictionary of parameter names and values.
        """
        return self.params.items()

    def get_param(self, key: str) -> Any:
        """
        Get the value of a parameter.

        Parameters:
            key (str): Name of the parameter.

        Returns:
            Any: Value of the parameter.
        """
        return self.params.get_parameter(key)

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
        self.run_datetime: str = self.update_datetime()

    def on_stop(self) -> None:
        """
        Callback when the factor stops.
        """
        if self.factor_mode == FactorMode.Backtest:
            pass
        self.trading = False

    @abstractmethod
    def calculate(self, 
                 input_data: Dict[str, Union[pl.DataFrame, Delayed]],
                 memory: Optional[pl.DataFrame] = None,
                 *args, **kwargs) -> pl.DataFrame:
        """
        Enhanced abstract method for calculating factor values with Dask support.

        Parameters
        ----------
        input_data : Dict[str, Union[pl.DataFrame, Delayed]]
            Input data for calculation. Can be either direct DataFrames or Dask Delayed objects
        memory : Optional[pl.DataFrame]
            Historical data for calculation
        
        Returns
        -------
        pl.DataFrame
            Calculated factor values

        Notes
        -----
        - Implementations should handle both direct DataFrames and Dask Delayed objects
        - Use chunking for large datasets
        - Implement error handling for data quality issues
        """
        pass

    def calculate_polars(self, input_data: pl.DataFrame, *args, **kwargs) -> Any:
        """
        Calculate the factor value using Polars DataFrame.

        Parameters:
            input_data (pl.DataFrame): Input data for calculation.

        Returns:
            Any: The calculated factor value(s).
        """
        pass

    def from_setting(self, setting: Optional[dict] = None) -> None:
        """
        Load factor settings from a dictionary.

        Parameters:
            setting (Optional[dict]): The factor settings.
        """
        if setting is None:
            return
        # for factor_key, factor_setting in setting.items():
        factor_setting = setting
        if isinstance(factor_setting.get("freq", Interval.UNKNOWN), str):
            self.freq = Interval(factor_setting.get("freq", Interval.UNKNOWN))
        elif isinstance(factor_setting.get("freq", Interval.UNKNOWN), Interval):
            self.freq = factor_setting.get("freq", Interval.UNKNOWN)
        else:
            raise ValueError("The freq must be a string or an Interval object.")
        # if params appear in setting, then set it. But if kwargs get the same param, it will overwrite the previous one, the one in setting
        self.params.set_parameters(factor_setting.get("params", {}))
        # load factor settings, and init them in __init_dependencies__
        self.dependencies_factor = factor_setting.get("dependencies_factor", [])
        self.dependencies_freq = factor_setting.get("dependencies_freq", [])
        self.dependencies_symbol = factor_setting.get("dependencies_symbol", [])
        self.dependencies_exchange = factor_setting.get("dependencies_exchange", [])
        self.run_datetime = factor_setting.get("last_run_datetime", self.update_datetime())

    def to_setting(self) -> dict:
        """
        Convert the factor to a settings dictionary.

        Returns:
            dict: The factor settings.
        """
        return self.to_dict()

    def to_dict(self) -> dict:
        """
        Convert the factor to a dictionary.

        Returns:
            dict: A dictionary representation of the factor.
        """
        d = {
            self.factor_key: {
                "class_name": self.__class__.__name__,
                "freq": str(self.freq.value) if self.freq is not None else Interval.UNKNOWN.value,
                "params": self.params.get_all_parameters(),
                "dependencies_factor": [f.to_dict() for f in self.dependencies_factor],
                "dependencies_freq": self.dependencies_freq,
                "dependencies_symbol": self.dependencies_symbol,
                "dependencies_exchange": self.dependencies_exchange,
                "last_run_datetime": self.run_datetime,
            }
        }
        return d

    def validate_inputs(self, input_data: Dict[str, Any], memory: Optional[pl.DataFrame] = None) -> None:
        """
        Validate input data before calculation.

        Parameters
        ----------
        input_data : Dict[str, Any]
            Input data to validate
        memory : Optional[pl.DataFrame]
            Historical data to validate
        
        Raises
        ------
        ValueError
            If input data is invalid
        """
        if not input_data:
            raise ValueError("Input data cannot be empty")
            
        required_columns = {'datetime'}  # Add other required columns
        if memory is not None:
            if not isinstance(memory, pl.DataFrame):
                raise ValueError("Memory must be a Polars DataFrame")
            if not required_columns.issubset(memory.columns):
                raise ValueError(f"Memory missing required columns: {required_columns}")

TV_FactorTemplate = TypeVar('TV_FactorTemplate', bound=FactorTemplate)
