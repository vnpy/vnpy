from abc import abstractmethod, ABC
from typing import Optional, Dict, Any, Union, List, Type
import importlib
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

    @property
    def factor_key(self) -> str:
        """
        Get the factor name key.
        """
        return f"{self.factor_name}@{self.params.to_str(with_value=True)}"

    def __init_dependencies__(self):
        dependencies_factor_initialized = []
        for f_setting in self.dependencies_factor:  # list of dicts
            for module_name, module_setting in f_setting.items():
                f_class: Type[FactorTemplate] = getattr(self.module, module_setting["class_name"])
                f_class = f_class({module_name: module_setting}, **module_setting["params"])  # recursion
                dependencies_factor_initialized.append(f_class)

        self.dependencies_factor = dependencies_factor_initialized

    def __init__(self, setting: Optional[dict] = None, **kwargs):
        """
        Initialize the factor template with the given engine and settings.

        Parameters:
            setting (dict): Settings for the factor.
            kwargs: Additional parameters.
        """
        self.params: FactorParameters = FactorParameters()  # 新增字段, 希望用一个class来存储参数数据, 并且能方便地save json/load json
        self.module = importlib.import_module(".factors", package=__package__)
        self.from_dict(setting)
        self.set_params(
            kwargs)  # 这里是把setting里面的参数设置到self.params里面, 也就是FactorParameters这个类里面, 如果有和setting['params']重复的参数, 那么就会覆盖
        self.__init_dependencies__()  # 比如macd, 需要ma10和ma20, 那么这里就要初始化ma, 生成两个ma实例, 并且把这两个ma实例加入到dependencies_factor里面

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
            if hasattr(self, key):
                if value is not None:
                    print(f"Parameter {key} is updated: {getattr(self, key)} -> {value}")
                    # setattr(self.params.set_parameters({key:value}), key, value)
                    self.params.set_parameters({key: value})
            else:
                self.add_params(key)
                print(f"Parameter {key} is set: {value}")
                #                 setattr(self.params.set_parameters({key:value}), key, value)
                self.params.set_parameters({key: value})
            # if key in self.params:
            #     print(f"Parameter {key} is updated: {getattr(self, key)} -> {value}")
            #     setattr(self, key, value)
            # else:
            #     # why raise error here? Because we want to make sure the parameter is correctly set in the factor,
            #     # and we can't set a parameter that is not defined in the factor
            #     raise ValueError(f"Parameter {key} is not recognized.")

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

    def calculate(self, input_data: Optional[Union[pl.DataFrame, Dict[str, Any]]], *args, **kwargs) -> Any:
        """unified api for calculating factor value

        Parameters:
            input_data (pl.DataFrame): Input data for calculation.

        Returns:
            Any: Calculated factor value(s).
        """
        if isinstance(input_data, pl.DataFrame):
            return self.calculate_polars(input_data, *args, **kwargs)
        else:
            raise NotImplementedError("Only polars DataFrame is supported for now.")

    @abstractmethod
    def calculate_polars(self, input_data: pl.DataFrame, *args, **kwargs) -> Any:
        pass

    def from_dict(self, dic: Optional[dict] = None) -> None:
        """
        load factor from `factor_maker_setting.json`
        """
        if dic is None:
            return
        for factor_key, factor_setting in dic.items():
            self.freq = Interval(factor_setting.get("freq", None))
            self.params.set_parameters(factor_setting.get("params", {}))
            # load factor settings, and init them in __init_dependencies__
            self.dependencies_factor = factor_setting.get("dependencies_factor", [])
            self.dependencies_freq = factor_setting.get("dependencies_freq", [])
            self.dependencies_symbol = factor_setting.get("dependencies_symbol", [])
            self.dependencies_exchange = factor_setting.get("dependencies_exchange", [])

    def to_dict(self) -> dict:
        """
        Convert the factor template to a dictionary.
        """
        # freq = str(self.freq.value) if self.freq is not None else None
        d = {
            self.factor_key: {
                "class_name": self.__class__.__name__,
                "freq": str(self.freq.value) if self.freq is not None else None,
                "params": self.params.get_all_parameters(),
                "dependencies_factor": [f.to_dict() for f in self.dependencies_factor],
                "dependencies_freq": self.dependencies_freq,
                "dependencies_symbol": self.dependencies_symbol,
                "dependencies_exchange": self.dependencies_exchange
            }
        }
        return d
