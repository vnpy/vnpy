# my_factor_library.py

import polars as pl
from typing import Dict, List, Any, Optional

# Assuming FactorTemplate, FactorMemory are correctly importable
from ..template import FactorTemplate
from ..memory import FactorMemory
from vnpy.trader.constant import Interval

# Define constants if not readily available from FactorEngine's context for standalone clarity
DEFAULT_DATETIME_COL = "datetime"
try:
    from vnpy.trader.database import DB_TZ # Timezone for datetime columns
except ImportError:
    DB_TZ = None


class EMAFactor(FactorTemplate):
    """
    Calculates the Exponential Moving Average (EMA) for each symbol.
    """
    author = "VN Trader Community"
    factor_name = "EMAFactor"  # Default, can be overridden by factor_name in settings

    def __init__(self, setting: Optional[dict] = None, vt_symbols: Optional[List[str]] = None, **kwargs):
        """
        Initializes EMAFactor.
        Expects 'period' in parameters.
        `vt_symbols` is a list of symbol strings for which the factor will generate outputs.
        """
        super().__init__(setting, **kwargs) # FactorTemplate.__init__ handles params
        self.vt_symbols: List[str] = vt_symbols if vt_symbols else []

        if not hasattr(self.params, 'period'):
            raise ValueError(f"EMAFactor ({self.factor_key}) requires 'period' parameter.")
        try:
            self.period: int = int(self.params.period)
            if self.period <= 0:
                raise ValueError("Period must be positive.")
        except ValueError as e:
            raise ValueError(f"EMAFactor ({self.factor_key}): Invalid 'period' parameter: {e}")

    def get_output_schema(self) -> Dict[str, pl.DataType]:
        """
        Defines the output schema: a datetime column and one Float64 column for each symbol.
        Column names for symbols are the vt_symbol strings themselves.
        """
        schema = {DEFAULT_DATETIME_COL: pl.Datetime(time_unit="us", timezone=DB_TZ if DB_TZ else None)}
        if not self.vt_symbols:
            # Consider logging a warning if no symbols are provided, FactorMemory might need at least one value column.
            # For now, allows schema with only datetime if vt_symbols is empty.
            pass
        for symbol in self.vt_symbols:
            schema[symbol] = pl.Float64
        return schema

    def calculate(self,
                  input_data: Dict[str, pl.DataFrame],  # Expects {"close": df_close_wide, ...}
                  memory: FactorMemory) -> pl.DataFrame:
        """
        Calculates EMA based on 'close' prices.
        `input_data` provides historical OHLCV data in wide format.
        Returns a wide DataFrame: datetime | SYM1_ema | SYM2_ema | ...
        """
        df_close = input_data.get("close")

        empty_df_schema = self.get_output_schema()
        if df_close is None or df_close.is_empty():
            return pl.DataFrame(data={}, schema=empty_df_schema)

        if DEFAULT_DATETIME_COL not in df_close.columns:
            # Log error or raise, then return empty
            print(f"Warning: '{DEFAULT_DATETIME_COL}' missing in 'close' data for {self.factor_key}. Returning empty.")
            return pl.DataFrame(data={}, schema=empty_df_schema)

        datetime_series = df_close.select(pl.col(DEFAULT_DATETIME_COL))
        calculated_emas: List[pl.Series] = []

        for symbol_col_name in df_close.columns:
            if symbol_col_name == DEFAULT_DATETIME_COL:
                continue
            
            # Only calculate for symbols intended for output (in self.vt_symbols used for schema)
            if self.vt_symbols and symbol_col_name not in self.vt_symbols:
                continue

            ema_series = df_close.get_column(symbol_col_name).ewm_mean(span=self.period, adjust=False).alias(symbol_col_name)
            calculated_emas.append(ema_series)

        if not calculated_emas and not datetime_series.is_empty():
             # Only datetime column, no value columns produced (e.g. no matching symbols)
             return datetime_series.clone().with_columns([
                 pl.lit(None, dtype=empty_df_schema.get(s_col, pl.Float64)).alias(s_col)
                 for s_col in empty_df_schema if s_col != DEFAULT_DATETIME_COL
             ])
        if not calculated_emas and datetime_series.is_empty():
            return pl.DataFrame(data={}, schema=empty_df_schema)

        result_df = pl.concat([datetime_series] + calculated_emas, how="horizontal")
        return result_df


class MACDFactor(FactorTemplate):
    """
    Calculates MACD (Moving Average Convergence Divergence).
    Depends on two EMAFactor instances (fast and slow).
    """
    author = "VN Trader Community"
    factor_name = "MACDFactor"

    def __init__(self, setting: Optional[dict] = None, vt_symbols: Optional[List[str]] = None, **kwargs):
        """
        Initializes MACDFactor.
        Expects 'fast_period', 'slow_period', 'signal_period' in parameters.
        `vt_symbols` is a list of symbol strings for which the factor will generate outputs.
        """
        super().__init__(setting, **kwargs)
        self.vt_symbols: List[str] = vt_symbols if vt_symbols else []

        param_names = ["fast_period", "slow_period", "signal_period"]
        periods = {}
        for p_name in param_names:
            if not hasattr(self.params, p_name):
                raise ValueError(f"MACDFactor ({self.factor_key}) requires '{p_name}' parameter.")
            try:
                periods[p_name] = int(getattr(self.params, p_name))
                if periods[p_name] <= 0:
                    raise ValueError(f"Period '{p_name}' must be positive.")
            except ValueError as e:
                raise ValueError(f"MACDFactor ({self.factor_key}): Invalid '{p_name}' parameter: {e}")

        self.fast_period: int = periods["fast_period"]
        self.slow_period: int = periods["slow_period"]
        self.signal_period: int = periods["signal_period"]

        if self.fast_period >= self.slow_period:
            raise ValueError(f"MACDFactor ({self.factor_key}): fast_period ({self.fast_period}) "
                             f"must be less than slow_period ({self.slow_period}).")

    def get_output_schema(self) -> Dict[str, pl.DataType]:
        """
        Defines output schema: datetime and, for each symbol,
        columns for macd, signal, and histogram values.
        e.g., SYM1_macd, SYM1_signal, SYM1_histogram
        """
        schema = {DEFAULT_DATETIME_COL: pl.Datetime(time_unit="us", timezone=DB_TZ if DB_TZ else None)}
        for symbol in self.vt_symbols:
            schema[f"{symbol}_macd"] = pl.Float64
            schema[f"{symbol}_signal"] = pl.Float64
            schema[f"{symbol}_histogram"] = pl.Float64
        return schema

    def calculate(self,
                  input_data: Dict[str, pl.DataFrame],  # Expects {ema_fast_key: df_ema_fast, ema_slow_key: df_ema_slow}
                  memory: FactorMemory) -> pl.DataFrame:
        """
        Calculates MACD lines using input from two dependency EMA factors.
        Returns a wide DataFrame: datetime | SYM1_macd | SYM1_signal | SYM1_hist | SYM2_macd | ...
        """
        empty_df_schema = self.get_output_schema()
        if len(self.dependencies_factor) < 2:
            print(f"Warning: MACDFactor ({self.factor_key}) requires two EMA dependency factors. Returning empty.")
            return pl.DataFrame(data={}, schema=empty_df_schema)

        ema_fast_instance: Optional[FactorTemplate] = None
        ema_slow_instance: Optional[FactorTemplate] = None

        for dep_factor in self.dependencies_factor:
            if hasattr(dep_factor, 'params') and hasattr(dep_factor.params, 'period'):
                dep_period = int(dep_factor.params.period)
                if dep_period == self.fast_period:
                    ema_fast_instance = dep_factor
                elif dep_period == self.slow_period:
                    ema_slow_instance = dep_factor
        
        if not ema_fast_instance or not ema_slow_instance:
            print(f"Warning: MACDFactor ({self.factor_key}) could not identify fast/slow EMA dependencies. Returning empty.")
            return pl.DataFrame(data={}, schema=empty_df_schema)

        df_ema_fast = input_data.get(ema_fast_instance.factor_key)
        df_ema_slow = input_data.get(ema_slow_instance.factor_key)

        if df_ema_fast is None or df_ema_fast.is_empty() or df_ema_slow is None or df_ema_slow.is_empty():
            return pl.DataFrame(data={}, schema=empty_df_schema)
        
        if DEFAULT_DATETIME_COL not in df_ema_fast.columns or DEFAULT_DATETIME_COL not in df_ema_slow.columns:
            print(f"Warning: '{DEFAULT_DATETIME_COL}' missing in dependency EMA data for {self.factor_key}. Returning empty.")
            return pl.DataFrame(data={}, schema=empty_df_schema)

        # For robust merging, explicitly join on datetime and handle suffixes if any column name clashes (unlikely for symbols)
        # However, since EMA output is "datetime | SYM1 | SYM2", direct access is fine if aligned.
        # Assume alignment for simplicity. A production system might use an asof join or ensure exact datetime matches.
        datetime_series = df_ema_fast.select(pl.col(DEFAULT_DATETIME_COL)) # Assume same datetimes as df_ema_slow
        
        output_components: List[pl.Series] = [datetime_series.get_column(DEFAULT_DATETIME_COL)]

        symbols_in_fast = set(df_ema_fast.columns) - {DEFAULT_DATETIME_COL}
        symbols_in_slow = set(df_ema_slow.columns) - {DEFAULT_DATETIME_COL}
        
        # Calculate for symbols present in both EMA inputs and intended for output
        symbols_to_process = sorted(list(symbols_in_fast.intersection(symbols_in_slow)))
        if self.vt_symbols: # If specific output symbols are defined, filter by them
            symbols_to_process = [s for s in symbols_to_process if s in self.vt_symbols]

        for symbol in symbols_to_process:
            fast_ema_values = df_ema_fast.get_column(symbol)
            slow_ema_values = df_ema_slow.get_column(symbol)
            
            macd_line_values = fast_ema_values - slow_ema_values
            signal_line_values = macd_line_values.ewm_mean(span=self.signal_period, adjust=False)
            histogram_values = macd_line_values - signal_line_values
            
            output_components.append(macd_line_values.alias(f"{symbol}_macd"))
            output_components.append(signal_line_values.alias(f"{symbol}_signal"))
            output_components.append(histogram_values.alias(f"{symbol}_histogram"))
        
        if len(output_components) == 1: # Only datetime column, no value columns
            return datetime_series.clone().with_columns([
                 pl.lit(None, dtype=empty_df_schema.get(s_col, pl.Float64)).alias(s_col)
                 for s_col in empty_df_schema if s_col != DEFAULT_DATETIME_COL
             ])

        result_df = pl.concat(output_components, how="horizontal")
        return result_df


class MyCustomFactor(FactorTemplate):
    """
    Example custom factor: Calculates a rolling mean on a specified source column (e.g., 'open', 'close').
    """
    author = "User"
    factor_name = "CustomRollingMean"

    def __init__(self, setting: Optional[dict] = None, vt_symbols: Optional[List[str]] = None, **kwargs):
        """
        Initializes MyCustomFactor.
        Expects 'length' (int) and 'source' (str like "open", "close") in parameters.
        `vt_symbols` is a list of symbol strings for which the factor will generate outputs.
        """
        super().__init__(setting, **kwargs)
        self.vt_symbols: List[str] = vt_symbols if vt_symbols else []

        if not hasattr(self.params, 'length') or not hasattr(self.params, 'source'):
            raise ValueError(f"MyCustomFactor ({self.factor_key}) requires 'length' and 'source' parameters.")
        
        try:
            self.length: int = int(self.params.length)
            if self.length <= 0:
                raise ValueError("Length must be positive.")
        except ValueError as e:
            raise ValueError(f"MyCustomFactor ({self.factor_key}): Invalid 'length' parameter: {e}")
            
        self.source_column_name: str = str(self.params.source).lower()
        if self.source_column_name not in ["open", "high", "low", "close", "volume"]:
            raise ValueError(f"MyCustomFactor ({self.factor_key}): 'source' parameter must be one of open, high, low, close, volume.")

    def get_output_schema(self) -> Dict[str, pl.DataType]:
        """
        Defines output schema: datetime and one Float64 column for each symbol (named by symbol string).
        """
        schema = {DEFAULT_DATETIME_COL: pl.Datetime(time_unit="us", timezone=DB_TZ if DB_TZ else None)}
        for symbol in self.vt_symbols:
            schema[symbol] = pl.Float64
        return schema

    def calculate(self,
                  input_data: Dict[str, pl.DataFrame],  # Expects {"open": df_o, "close": df_c ...}
                  memory: FactorMemory) -> pl.DataFrame:
        """
        Calculates rolling mean on the specified source column.
        Returns a wide DataFrame: datetime | SYM1_custom_value | SYM2_custom_value | ...
        """
        df_source = input_data.get(self.source_column_name)
        
        empty_df_schema = self.get_output_schema()
        if df_source is None or df_source.is_empty():
            return pl.DataFrame(data={}, schema=empty_df_schema)

        if DEFAULT_DATETIME_COL not in df_source.columns:
            print(f"Warning: '{DEFAULT_DATETIME_COL}' missing in '{self.source_column_name}' data for {self.factor_key}. Returning empty.")
            return pl.DataFrame(data={}, schema=empty_df_schema)

        datetime_series = df_source.select(pl.col(DEFAULT_DATETIME_COL))
        calculated_values: List[pl.Series] = []

        for symbol_col_name in df_source.columns:
            if symbol_col_name == DEFAULT_DATETIME_COL:
                continue
            
            if self.vt_symbols and symbol_col_name not in self.vt_symbols:
                continue
            
            # min_periods=1 allows output even if window isn't full. Can be self.length for strict full window.
            mean_series = df_source.get_column(symbol_col_name).rolling_mean(window_size=self.length, min_periods=1).alias(symbol_col_name)
            calculated_values.append(mean_series)

        if not calculated_values and not datetime_series.is_empty():
             return datetime_series.clone().with_columns([
                 pl.lit(None, dtype=empty_df_schema.get(s_col, pl.Float64)).alias(s_col)
                 for s_col in empty_df_schema if s_col != DEFAULT_DATETIME_COL
             ])
        if not calculated_values and datetime_series.is_empty():
            return pl.DataFrame(data={}, schema=empty_df_schema)


        result_df = pl.concat([datetime_series] + calculated_values, how="horizontal")
        return result_df