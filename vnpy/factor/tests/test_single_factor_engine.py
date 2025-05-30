import unittest
from unittest.mock import patch, MagicMock, PropertyMock
from pathlib import Path
import tempfile
import shutil
import polars as pl
from datetime import datetime
from typing import Dict, Any

from vnpy.factor.template import FactorTemplate, FactorParameters
from vnpy.trader.constant import Interval
from vnpy.factor.backtesting.backtesting import BacktestEngine, DEFAULT_DATETIME_COL
from vnpy.factor.optimizer import FactorBacktestEstimator
from sklearn.model_selection import GridSearchCV, TimeSeriesSplit # For patching
import numpy as np
import re # For MockNestableFactor

class MockFactor(FactorTemplate):
    factor_name = "mockfactor"

    def get_output_schema(self) -> Dict[str, pl.DataType]:
        schema = {DEFAULT_DATETIME_COL: pl.Datetime}
        # self.vt_symbols is set when factor is initialized by engine or manually
        for symbol in getattr(self, 'vt_symbols', []): 
            schema[symbol] = pl.Float64
        return schema

    def calculate(self, input_data: Dict[str, pl.DataFrame], memory: Any) -> pl.DataFrame:
        # input_data is expected to be engine.memory_bar, a dict of DataFrames like {"close": df_close, ...}
        # df_close has columns: DEFAULT_DATETIME_COL, SYM1.TEST, SYM2.TEST, ...
        
        close_prices_df = input_data.get("close")

        # Ensure vt_symbols are available for schema generation fallback
        current_vt_symbols = getattr(self, 'vt_symbols', [])

        if close_prices_df is None or close_prices_df.is_empty() or DEFAULT_DATETIME_COL not in close_prices_df.columns:
            # Return empty DataFrame matching schema if essential input is missing
            empty_data = {DEFAULT_DATETIME_COL: pl.Series(DEFAULT_DATETIME_COL, [], dtype=pl.Datetime)}
            for symbol in current_vt_symbols: # Use symbols this factor instance is configured for
                empty_data[symbol] = pl.Series(symbol, [], dtype=pl.Float64)
            # Explicitly pass schema to handle case where current_vt_symbols might be empty if not properly init'd before schema call
            return pl.DataFrame(empty_data, schema=self.get_output_schema() or {DEFAULT_DATETIME_COL: pl.Datetime})


        # Prepare output data dictionary
        output_df_data = {
            DEFAULT_DATETIME_COL: close_prices_df[DEFAULT_DATETIME_COL]
        }

        for symbol in current_vt_symbols: # Iterate over symbols this factor instance is configured for
            if symbol in close_prices_df.columns:
                output_df_data[symbol] = close_prices_df[symbol] * 1.05 # Dummy calculation
            else:
                # If symbol data not in close_prices, fill with nulls or default
                output_df_data[symbol] = pl.Series(symbol, [None] * len(close_prices_df), dtype=pl.Float64)
        
        # Ensure column order and presence as per schema
        # This is important if current_vt_symbols caused schema to be different or if a symbol was missing
        final_schema_keys = list(self.get_output_schema().keys())
        
        # Create DataFrame with available data
        temp_df = pl.DataFrame(output_df_data)
        
        # Select columns based on schema to ensure correct structure
        # For any symbol in schema but not in temp_df (e.g. if close_prices_df was missing it), it will be error
        # So, ensure all schema keys are present in output_df_data before this step if possible
        # The current loop for current_vt_symbols should ensure this.
        
        select_cols = []
        for col_name in final_schema_keys:
            if col_name in temp_df.columns:
                select_cols.append(col_name)
            elif col_name == DEFAULT_DATETIME_COL: # Should always be there if close_prices_df was valid
                 select_cols.append(DEFAULT_DATETIME_COL)
            # If a symbol from schema is NOT in temp_df columns, it implies an issue or it wasn't in current_vt_symbols.
            # The current logic (iterating current_vt_symbols) should mean all configured symbols are in output_df_data.

        return temp_df.select(select_cols)


class TestSingleFactorEngine(unittest.TestCase):
    def setUp(self):
        """Set up test fixtures, if any."""
        self.temp_dir = tempfile.mkdtemp()
        self.vt_symbols = ["SYM1.TEST", "SYM2.TEST"]
        self.start_date = datetime(2023, 1, 1)
        self.end_date = datetime(2023, 1, 10)
        
        # Mock the factor module loading in BacktestEngine if factors are loaded by string name
        # For pre-initialized factors, this might not be strictly necessary but good for consistency
        patcher = patch('vnpy.factor.backtesting.backtesting.importlib.import_module')
        self.mock_import_module = patcher.start()
        self.addCleanup(patcher.stop)
        
        # Simulate a factor module that can provide MockFactor if needed by name
        # Though for this test, we pass an instance directly.
        mock_factor_module = MagicMock()
        mock_factor_module.MockFactor = MockFactor 
        self.mock_import_module.return_value = mock_factor_module

        self.engine = BacktestEngine(
            vt_symbols=self.vt_symbols, # Default symbols for engine if not overridden by run_single_factor
            output_data_dir=self.temp_dir,
            factor_module_name="vnpy.factor.factors" # Dummy, as we provide factor instance
        )
        # Ensure load_bar_data is patched to prevent actual data loading
        # and to control the dummy data provided
        patch_load_bar = patch.object(self.engine, 'load_bar_data', self.mock_load_bar_data)
        self.mock_load_bar_method = patch_load_bar.start()
        self.addCleanup(patch_load_bar.stop)

    def mock_load_bar_data(self, start: datetime, end: datetime, interval: Any) -> bool:
        """Controlled mock for load_bar_data."""
        # This method will be called by run_single_factor_backtest
        # We need to populate self.engine.memory_bar["close"] and self.engine.num_data_rows
        # The symbols used here should ideally match self.engine.vt_symbols set by run_single_factor_backtest
        
        # `run_single_factor_backtest` updates `self.engine.vt_symbols` based on `vt_symbols_for_factor`
        # So, use `self.engine.vt_symbols` which reflects the symbols for the current test run.
        active_symbols = self.engine.vt_symbols 
        
        num_days = (end - start).days + 1 # Inclusive of end date for daily
        if interval == Interval.DAILY:
            dates = [start + pl.duration(days=i) for i in range(num_days)]
        else: # Default to minute-like frequency if not daily for placeholder
            num_minutes = num_days * 24 * 60 
            dates = [start + pl.duration(minutes=i) for i in range(num_minutes)]

        if not dates: # Should not happen with valid start/end
            self.engine.num_data_rows = 0
            self.engine.memory_bar = {}
            return False

        self.engine.num_data_rows = len(dates)
        
        close_data = {DEFAULT_DATETIME_COL: pl.Series(DEFAULT_DATETIME_COL, dates, dtype=pl.Datetime)}
        for symbol in active_symbols: # Use symbols relevant to the current engine configuration
            # Generate some deterministic but varying data
            close_data[symbol] = pl.Series(symbol, [100 + (i % 10) + (active_symbols.index(symbol) * 5) for i in range(len(dates))], dtype=pl.Float64)
        
        self.engine.memory_bar = {"close": pl.DataFrame(close_data)}
        self.engine.write_log(f"Mock load_bar_data: Populated memory_bar['close'] with {self.engine.num_data_rows} rows for symbols: {active_symbols}", level=10) # DEBUG level
        return True


    def tearDown(self):
        """Tear down test fixtures, if any."""
        shutil.rmtree(self.temp_dir)

    def test_run_with_preinitialized_factor(self):
        """Test running backtest with a pre-initialized factor instance."""
        symbols_for_this_test = [self.vt_symbols[0]] # Test with only one symbol

        # Create and configure the MockFactor instance
        mock_factor_instance = MockFactor(engine=None) # engine can be None for init
        mock_factor_instance.vt_symbols = symbols_for_this_test # Manually set symbols for this factor
        mock_factor_instance.params = FactorParameters({"window": 5}) # Dummy params

        report_path = self.engine.run_single_factor_backtest(
            factor_definition=mock_factor_instance,
            start_datetime=self.start_date,
            end_datetime=self.end_date,
            vt_symbols_for_factor=symbols_for_this_test, # Engine will use these symbols
            data_interval=Interval.DAILY
        )

        self.assertIsNotNone(report_path, "Report path should not be None")
        self.assertTrue(Path(report_path).exists(), "Report file should exist")

        self.assertIsNotNone(self.engine.quantile_analysis_results, "Quantile analysis results should exist")
        if self.engine.quantile_analysis_results: # Check to satisfy type checker
            self.assertIn("overall_average", self.engine.quantile_analysis_results)
            self.assertIn("by_time", self.engine.quantile_analysis_results)
            # Check if overall_average DataFrame is not empty if it exists
            overall_avg_df = self.engine.quantile_analysis_results.get("overall_average")
            self.assertIsNotNone(overall_avg_df, "Overall average quantile returns DF should exist")
            if overall_avg_df is not None: # Keep mypy happy
                 self.assertFalse(overall_avg_df.is_empty(), "Overall average quantile returns DF should not be empty")


        self.assertIsNotNone(self.engine.long_short_portfolio_returns_df, "L-S portfolio returns DF should exist")
        if self.engine.long_short_portfolio_returns_df is not None: # Keep mypy happy
            self.assertFalse(self.engine.long_short_portfolio_returns_df.is_empty(), "L-S portfolio returns DF should not be empty")

        self.assertIsNotNone(self.engine.long_short_stats, "L-S stats should exist")
        if self.engine.long_short_stats: # Keep mypy happy
            self.assertIn("t_statistic", self.engine.long_short_stats)
            # With deterministic data, t-stat might not be NaN if there's variance
            # self.assertIsNotNone(self.engine.long_short_stats.get("t_statistic"), "T-statistic should not be None/NaN")


        self.assertIsNotNone(self.engine.performance_metrics, "Performance metrics should exist")
        if self.engine.performance_metrics: # Keep mypy happy
            self.assertIn("sharpe", self.engine.performance_metrics)
            # Sharpe can be 0 or NaN depending on returns variance.
            # self.assertIsNotNone(self.engine.performance_metrics.get("sharpe"), "Sharpe ratio should not be None/NaN")

    def test_factor_backtest_estimator_fit_score(self):
        """Test FactorBacktestEstimator's fit and score methods."""
        mock_engine_instance = MagicMock(spec=BacktestEngine)
        mock_engine_instance.factor_datetime_col = DEFAULT_DATETIME_COL
        # Mock write_log to prevent console output during tests unless debugging
        mock_engine_instance.write_log = MagicMock()


        mock_full_bar_data = {
            "close": pl.DataFrame({
                DEFAULT_DATETIME_COL: [datetime(2023, 1, 1), datetime(2023, 1, 2), datetime(2023,1,3)],
                "SYM1.TEST": [10.0, 10.1, 10.2],
                "SYM2.TEST": [20.0, 20.1, 20.2]
            }),
            "open": pl.DataFrame({ # Estimator's fit logic expects dict of DFs, so provide more keys
                DEFAULT_DATETIME_COL: [datetime(2023, 1, 1), datetime(2023, 1, 2), datetime(2023,1,3)],
                "SYM1.TEST": [9.9, 10.0, 10.1],
                "SYM2.TEST": [19.9, 20.0, 20.1]
            })
        }
        initial_factor_params = {"window": 10, "fixed_param": 5}

        estimator = FactorBacktestEstimator(
            backtesting_engine=mock_engine_instance,
            factor_class_name="MockFactor", # Assuming MockFactor is defined in the test file
            full_bar_data_for_slicing=mock_full_bar_data,
            **initial_factor_params
        )

        # Test if initial params are set
        self.assertEqual(estimator.window, 10)
        self.assertEqual(estimator.fixed_param, 5)

        # Simulate GridSearchCV setting a parameter
        estimator.set_params(window=20)
        self.assertEqual(estimator.window, 20) # Check if set_params worked

        mock_indices = np.array([0, 1]) # Slice first two rows

        # Configure mock engine's methods
        mock_engine_instance.init_single_factor.return_value = True
        
        # Dummy factor data DF needs to match the symbols in the sliced data and datetime col
        # Sliced data will have SYM1.TEST, SYM2.TEST
        dummy_factor_output_df = pl.DataFrame({
            DEFAULT_DATETIME_COL: mock_full_bar_data["close"][DEFAULT_DATETIME_COL][mock_indices],
            "SYM1.TEST": [0.5, 0.6],
            "SYM2.TEST": [-0.2, 0.3]
        })
        mock_engine_instance.calculate_single_factor_data.return_value = dummy_factor_output_df
        mock_engine_instance.prepare_symbol_returns.return_value = True
        mock_engine_instance.perform_long_short_analysis.return_value = True
        mock_engine_instance.calculate_performance_metrics.return_value = True
        
        # Using PropertyMock if performance_metrics is a property, else direct assignment
        # For this subtask, assuming performance_metrics is a direct attribute that can be set.
        mock_engine_instance.performance_metrics = {"sharpe": 1.23}

        # Mock methods involved in graph rebuilding
        # _complete_factor_tree is called on the engine instance
        mock_engine_instance._complete_factor_tree = MagicMock(return_value={
            estimator.root_factor_for_optimization.factor_key: estimator.root_factor_for_optimization
        })
        # _topological_sort is also called on the engine instance
        mock_engine_instance._topological_sort = MagicMock(return_value=[
            estimator.root_factor_for_optimization.factor_key
        ])

        # Action
        result_estimator = estimator.fit(X_indices_for_fold=mock_indices)
        self.assertIs(result_estimator, estimator) # fit should return self

        # Assertions for the new fit logic:
        # 1. init_single_factor should NOT be called from within fit
        mock_engine_instance.init_single_factor.assert_not_called() # From previous test this was called by estimator's __init__

        # 2. Engine state setup
        self.assertIs(mock_engine_instance.target_factor_instance, estimator.root_factor_for_optimization)
        self.assertIn(estimator.root_factor_for_optimization.factor_key, mock_engine_instance.stacked_factors)
        mock_engine_instance._complete_factor_tree.assert_called_once_with(mock_engine_instance.stacked_factors)
        mock_engine_instance._topological_sort.assert_called_once() # Argument is a graph dict
        
        # Check vt_symbols on engine
        self.assertEqual(set(mock_engine_instance.vt_symbols), {"SYM1.TEST", "SYM2.TEST"})


        # 3. Pipeline methods called
        mock_engine_instance.calculate_single_factor_data.assert_called_once()
        mock_engine_instance.prepare_symbol_returns.assert_called_once()
        mock_engine_instance.perform_long_short_analysis.assert_called_once()
        mock_engine_instance.calculate_performance_metrics.assert_called_once()
        
        # 4. Score
        self.assertEqual(estimator.current_score, 1.23)
        self.assertEqual(estimator.score(None), 1.23)
        
        # Test case where Sharpe is None or non-finite
        # Reset relevant mocks for a new fit call
        mock_engine_instance.calculate_single_factor_data.reset_mock()
        mock_engine_instance.prepare_symbol_returns.reset_mock()
        mock_engine_instance.perform_long_short_analysis.reset_mock()
        mock_engine_instance.calculate_performance_metrics.reset_mock()
        mock_engine_instance._complete_factor_tree.reset_mock()
        mock_engine_instance._topological_sort.reset_mock()
        
        mock_engine_instance.performance_metrics = {"sharpe": np.nan} # Set Sharpe to NaN for this trial
        estimator.fit(X_indices_for_fold=mock_indices) # Call fit again
        self.assertEqual(estimator.current_score, -np.inf)


    @patch('vnpy.factor.backtesting.backtesting.GridSearchCV') # Patch where GridSearchCV is USED
    @patch('vnpy.factor.backtesting.backtesting.TimeSeriesSplit') # Patch where TimeSeriesSplit is USED
    def test_engine_optimize_factor_parameters(self, MockTimeSeriesSplit, MockGridSearchCV):
        """Test BacktestEngine's optimize_factor_parameters method."""
        
        # Configure MockTimeSeriesSplit
        mock_ts_splitter_instance = MockTimeSeriesSplit.return_value
        
        # Configure MockGridSearchCV
        mock_grid_search_instance = MockGridSearchCV.return_value
        mock_grid_search_instance.fit.return_value = None # or mock_grid_search_instance
        mock_grid_search_instance.best_params_ = {"window": 25}
        mock_grid_search_instance.best_score_ = 1.55
        mock_grid_search_instance.cv_results_ = {
            "mean_test_score": np.array([1.55, 1.45]), 
            "std_test_score": np.array([0.1, 0.05]),
            "params": [{"window": 25}, {"window": 15}]
        }

        # Prepare data for the engine method
        # self.engine is from setUp, already has load_bar_data patched.
        # optimize_factor_parameters expects full_bar_data directly.
        test_full_bar_data = {
            "close": pl.DataFrame({
                DEFAULT_DATETIME_COL: [datetime(2023, 1, i+1) for i in range(20)], # 20 days of data
                "SYM1.TEST": [100 + i for i in range(20)],
                "SYM2.TEST": [200 - i for i in range(20)]
            }),
            "open": pl.DataFrame({
                 DEFAULT_DATETIME_COL: [datetime(2023, 1, i+1) for i in range(20)],
                "SYM1.TEST": [99 + i for i in range(20)],
                "SYM2.TEST": [199 - i for i in range(20)]
            })
        }
        
        initial_settings = {"window": 10, "period": 30} # 'period' is a fixed param here
        param_grid = {"window": [15, 25]} # 'window' is the param to optimize
        
        # Call the method to test
        n_cv_splits = 3
        best_params_result = self.engine.optimize_factor_parameters(
            factor_class_name="MockFactor", 
            initial_factor_settings=initial_settings,
            parameter_grid=param_grid,
            full_bar_data=test_full_bar_data,
            n_splits_for_cv=n_cv_splits
        )

        # Assertions
        MockTimeSeriesSplit.assert_called_once_with(n_splits=n_cv_splits)
        
        MockGridSearchCV.assert_called_once()
        args_gscv, kwargs_gscv = MockGridSearchCV.call_args
        
        self.assertIsInstance(kwargs_gscv['estimator'], FactorBacktestEstimator)
        self.assertEqual(kwargs_gscv['estimator'].factor_class_name, "MockFactor")
        self.assertEqual(kwargs_gscv['estimator'].window, 10) # Initial window
        self.assertEqual(kwargs_gscv['estimator'].period, 30) # Initial fixed param
        self.assertIs(kwargs_gscv['estimator'].full_bar_data_for_slicing, test_full_bar_data)
        
        self.assertEqual(kwargs_gscv['param_grid'], param_grid)
        self.assertIs(kwargs_gscv['cv'], mock_ts_splitter_instance)
        self.assertEqual(kwargs_gscv['n_jobs'], 1) # Hardcoded in optimize_factor_parameters

        mock_grid_search_instance.fit.assert_called_once()
        # Check X passed to grid_search.fit (should be np.arange(num_samples))
        args_fit, _ = mock_grid_search_instance.fit.call_args
        expected_indices = np.arange(test_full_bar_data["close"].height)
        np.testing.assert_array_equal(args_fit[0], expected_indices)

        self.assertEqual(best_params_result, {"window": 25})
        
        self.assertIsNotNone(self.engine.optimization_results)
        if self.engine.optimization_results: # For type checker
            self.assertEqual(self.engine.optimization_results["best_score"], 1.55)
            self.assertEqual(self.engine.optimization_results["best_params"], {"window": 25})
            self.assertIn("cv_results_summary", self.engine.optimization_results)
            summary = self.engine.optimization_results["cv_results_summary"]
            self.assertEqual(summary["mean_test_score"], [1.55, 1.45]) # Check .tolist() conversion
            self.assertEqual(summary["params"], ['{\'window\': 25}', '{\'window\': 15}']) # Check str(p) conversion


# Helper Mock Factor for testing nested parameter handling
class MockNestableFactor(FactorTemplate):
    factor_name = "nestable_mock"

    def __init__(self, params: Dict[str, Any], dependencies_factor: List[FactorTemplate] = None, setting: Dict = None):
        # Simplified init for testing; real FactorTemplate init is more complex
        self.params = FactorParameters(params)
        self.dependencies_factor = dependencies_factor or []
        # Mock essential attributes if not calling super().__init__ fully
        if setting: # Allow passing a setting dict for name, etc.
            self.from_setting(setting)
        if not self.factor_name and 'factor_name' not in (setting or {}):
             self.factor_name = self.__class__.__name__


    def get_params(self) -> Dict[str, Any]:
        return self.params.get_all_parameters()

    def set_params(self, new_params: Dict[str, Any]) -> None:
        self.params.set_parameters(new_params)
        # In a real factor, might need to trigger re-computation or state reset

    # get_output_schema and calculate are abstract, but might not be called in these specific tests
    def get_output_schema(self) -> Dict[str, pl.DataType]:
        # Output schema includes datetime and one column for each symbol this factor processes
        schema = {DEFAULT_DATETIME_COL: pl.Datetime(time_unit="us")} # Ensure time_unit for polars
        # vt_symbols should be set on the instance if it's used by the engine
        # For testing, we might need to manually set it or have __init__ handle it.
        # Let's assume vt_symbols is set by the engine or test setup.
        active_symbols = getattr(self, 'vt_symbols', []) 
        if not active_symbols and hasattr(self,'params') and self.params.get_parameter('vt_symbols'):
            active_symbols = self.params.get_parameter('vt_symbols')

        for symbol in active_symbols:
            schema[symbol] = pl.Float64
        if not active_symbols: # Fallback if no symbols, add a generic 'value' column
            schema["value"] = pl.Float64
        return schema

    def calculate(self, input_data: Dict[str, pl.DataFrame], memory: Any) -> pl.DataFrame:
        # For testing, assume 'close' prices are the primary input if no dependencies.
        # If dependencies exist, their output will be in input_data.
        
        # Determine which symbols this factor instance should process.
        # This should ideally be set by the engine during initialization (e.g. in init_single_factor)
        # based on the data slice being processed.
        active_symbols = getattr(self, 'vt_symbols', [])
        if not active_symbols and hasattr(self,'params') and self.params.get_parameter('vt_symbols'):
            active_symbols = self.params.get_parameter('vt_symbols')

        # Try to get datetime series from an input source
        datetime_series = None
        source_df_for_datetime = None

        if self.dependencies_factor:
            # If has dependencies, use the first dependency's output as source for datetime and symbols
            first_dep_key = self.dependencies_factor[0].factor_key
            if first_dep_key in input_data and isinstance(input_data[first_dep_key], pl.DataFrame):
                source_df_for_datetime = input_data[first_dep_key]
        
        if source_df_for_datetime is None: # Fallback to 'close' data if no deps or dep data missing
            if "close" in input_data and isinstance(input_data["close"], pl.DataFrame):
                source_df_for_datetime = input_data["close"]
        
        if source_df_for_datetime is not None and DEFAULT_DATETIME_COL in source_df_for_datetime.columns:
            datetime_series = source_df_for_datetime[DEFAULT_DATETIME_COL]
        else: # Cannot proceed without datetime
            # Return empty DataFrame matching schema
            empty_schema = self.get_output_schema()
            empty_data = {col: pl.Series(col, [], dtype=dtype) for col, dtype in empty_schema.items()}
            return pl.DataFrame(empty_data, schema=empty_schema)

        if not active_symbols and source_df_for_datetime is not None: # Try to infer from source_df if not set
            active_symbols = [col for col in source_df_for_datetime.columns if col != DEFAULT_DATETIME_COL]
            if not getattr(self, 'vt_symbols', []): # Set it on self if not already set, for schema consistency
                 self.vt_symbols = active_symbols


        output_dict = {DEFAULT_DATETIME_COL: datetime_series}
        param_multiplier = self.params.get_parameter("p_root", self.params.get_parameter("p_dep", 1.0)) # Get relevant param

        for symbol in active_symbols:
            base_values = None
            if self.dependencies_factor:
                # Example: Sum outputs of all dependencies for each symbol
                # This is a very simple aggregation logic.
                symbol_sum = pl.Series(symbol, [0.0] * len(datetime_series), dtype=pl.Float64)
                for dep_factor in self.dependencies_factor:
                    dep_output_df = input_data.get(dep_factor.factor_key)
                    if dep_output_df is not None and symbol in dep_output_df.columns:
                        symbol_sum = symbol_sum + dep_output_df[symbol].fill_null(0.0)
                base_values = symbol_sum
            elif "close" in input_data and symbol in input_data["close"].columns:
                base_values = input_data["close"][symbol]
            
            if base_values is not None:
                output_dict[symbol] = base_values * param_multiplier
            else: # Fill with NaNs or default if no data source for this symbol
                output_dict[symbol] = pl.Series(symbol, [None] * len(datetime_series), dtype=pl.Float64)
        
        final_df = pl.DataFrame(output_dict)
        
        # Ensure schema, especially if active_symbols was empty and "value" column was used
        expected_schema = self.get_output_schema()
        final_columns = []
        for col_name, col_type in expected_schema.items():
            if col_name in final_df.columns:
                final_columns.append(pl.col(col_name).cast(col_type, strict=False))
            else: # Add null column if missing from calculation but expected in schema
                final_columns.append(pl.lit(None, dtype=col_type).alias(col_name))
        
        if not final_columns and DEFAULT_DATETIME_COL not in final_df.columns and DEFAULT_DATETIME_COL in expected_schema:
             # Handle case where final_df might be totally empty from bad inputs
             final_columns.append(pl.lit(None, dtype=expected_schema[DEFAULT_DATETIME_COL]).alias(DEFAULT_DATETIME_COL))


        if not final_columns: # If schema was empty and df also empty
             return pl.DataFrame(schema=expected_schema)


        # If final_df is empty but has columns (e.g. from empty datetime_series), select will fail.
        # If final_df has no rows, select can still work if columns exist.
        if final_df.is_empty() and not final_df.columns: # Truly empty DF
            return pl.DataFrame(schema=expected_schema) # Return empty DF with schema
        
        # If final_df has columns but no rows, select might be okay.
        # If final_df has rows, select is okay.
        return final_df.select(final_columns) if final_columns else pl.DataFrame(schema=expected_schema)


    def get_nested_params_for_optimizer(self, current_path_prefix: str = "") -> Dict[str, Any]:
        nested_params: Dict[str, Any] = {}
        own_params = self.get_params()
        for param_name, param_value in own_params.items():
            key_path = f"{current_path_prefix}{param_name}"
            nested_params[key_path] = param_value

        if hasattr(self, 'dependencies_factor') and self.dependencies_factor:
            for i, dep_factor_instance in enumerate(self.dependencies_factor):
                if isinstance(dep_factor_instance, MockNestableFactor): # Check for MockNestableFactor for testing
                    new_prefix_for_child = f"{current_path_prefix}dependencies_factor[{i}]."
                    child_params = dep_factor_instance.get_nested_params_for_optimizer(
                        current_path_prefix=new_prefix_for_child
                    )
                    nested_params.update(child_params)
        return nested_params

    def set_nested_params_for_optimizer(self, nested_params_dict: Dict[str, Any]) -> None:
        own_params_to_set: Dict[str, Any] = {}
        deps_params_to_set_grouped: Dict[int, Dict[str, Any]] = {}

        for path_key, value in nested_params_dict.items():
            match = re.match(r"dependencies_factor\[(\d+)\]\.(.+)", path_key)
            if match:
                dep_index = int(match.group(1))
                remainder_path_for_child = match.group(2)
                if dep_index not in deps_params_to_set_grouped:
                    deps_params_to_set_grouped[dep_index] = {}
                deps_params_to_set_grouped[dep_index][remainder_path_for_child] = value
            else:
                own_params_to_set[path_key] = value

        if own_params_to_set:
            self.set_params(own_params_to_set)

        if hasattr(self, 'dependencies_factor') and self.dependencies_factor:
            for dep_index, params_for_dep_dict in deps_params_to_set_grouped.items():
                if 0 <= dep_index < len(self.dependencies_factor):
                    dep_instance = self.dependencies_factor[dep_index]
                    if isinstance(dep_instance, MockNestableFactor): # Check for MockNestableFactor for testing
                        dep_instance.set_nested_params_for_optimizer(params_for_dep_dict)


class TestFactorBacktestEstimatorStandalone(unittest.TestCase): # New test class for cleaner separation
    def setUp(self):
        self.mock_engine = MagicMock(spec=BacktestEngine)
        self.mock_engine.factor_datetime_col = DEFAULT_DATETIME_COL
        self.mock_engine.write_log = MagicMock() # Suppress logs

        # Mock full_bar_data (minimal for __init__ of estimator)
        self.mock_bar_data = {
            "close": pl.DataFrame({
                DEFAULT_DATETIME_COL: [datetime(2023,1,1)], "SYM1.TEST": [1.0]
            })
        }
        
        # Mock for FactorTemplate's _init_dependency_instances if called by MockNestableFactor's __init__
        # This might be needed if MockNestableFactor's __init__ calls super() or related methods
        # For this test, MockNestableFactor has a simplified __init__ so this might not be essential.
        patcher = patch('vnpy.factor.template.init_factors') 
        self.mock_init_factors = patcher.start()
        self.addCleanup(patcher.stop)


    def test_estimator_get_params(self):
        """Test FactorBacktestEstimator.get_params with nested factors."""
        # Setup factor tree
        dep_dep_factor = MockNestableFactor(params={"gamma": 0.01})
        dep_factor1 = MockNestableFactor(params={"beta": 200}, dependencies_factor=[dep_dep_factor])
        dep_factor2 = MockNestableFactor(params={"delta": 300})
        root_params = {"alpha": 100, "common": 50}
        
        # We need to mock how init_single_factor sets up the root_factor_for_optimization
        # For this test, we'll manually create the root factor and assign it.
        # The FactorBacktestEstimator's __init__ tries to call engine.init_single_factor
        
        # Mock what engine.init_single_factor would do:
        # 1. Create the root factor instance
        # 2. Set it to engine.target_factor_instance
        
        # Path 1: Let estimator's __init__ try to create it.
        # This requires self.mock_engine.init_single_factor to be configured to return True
        # and to set self.mock_engine.target_factor_instance correctly.
        
        # Create the fully formed root factor instance that init_single_factor would produce
        mock_root_factor_instance = MockNestableFactor(params=root_params, dependencies_factor=[dep_factor1, dep_factor2])
        
        self.mock_engine.init_single_factor.return_value = True
        self.mock_engine.target_factor_instance = mock_root_factor_instance

        initial_def_dict = { # This would be the definition for the root factor
            "class_name": "MockNestableFactor", 
            "params": root_params,
            # Dependencies would be defined here in a real scenario,
            # but MockNestableFactor takes instances directly for easier testing setup
        }

        estimator = FactorBacktestEstimator(
            backtesting_engine=self.mock_engine,
            initial_factor_definition_dict=initial_def_dict,
            full_bar_data_for_slicing=self.mock_bar_data
        )
        # Ensure __init__ assigned it
        self.assertIs(estimator.root_factor_for_optimization, mock_root_factor_instance)

        # Action
        params_retrieved = estimator.get_params()

        # Assertion
        expected_params = {
            "backtesting_engine": self.mock_engine,
            "initial_factor_definition_dict": initial_def_dict,
            "full_bar_data_for_slicing": self.mock_bar_data,
            "alpha": 100,
            "common": 50,
            "dependencies_factor[0].beta": 200,
            "dependencies_factor[0].dependencies_factor[0].gamma": 0.01,
            "dependencies_factor[1].delta": 300
        }
        self.assertEqual(params_retrieved, expected_params)

    def test_estimator_set_params(self):
        """Test FactorBacktestEstimator.set_params delegates to factor tree."""
        # Setup factor tree with mocks for set_nested_params_for_optimizer
        mock_root_factor = MockNestableFactor(params={"alpha": 10})
        # Spy on the method of the actual instance
        mock_root_factor.set_nested_params_for_optimizer = MagicMock() 
        
        # Configure estimator's __init__ process
        self.mock_engine.init_single_factor.return_value = True
        self.mock_engine.target_factor_instance = mock_root_factor
        
        initial_def_dict = {"class_name": "MockNestableFactor", "params": {"alpha": 10}}

        estimator = FactorBacktestEstimator(
            backtesting_engine=self.mock_engine,
            initial_factor_definition_dict=initial_def_dict,
            full_bar_data_for_slicing=self.mock_bar_data
        )
        self.assertIs(estimator.root_factor_for_optimization, mock_root_factor)

        # Test params
        params_to_set_on_estimator = {
            "alpha": 20, # For root
            "dependencies_factor[0].beta": 200, # For a dependency
            "full_bar_data_for_slicing": {"new_data": pl.DataFrame()} # Estimator's own param
        }

        # Action
        estimator.set_params(**params_to_set_on_estimator)

        # Assertion for estimator's own parameter
        self.assertEqual(estimator.full_bar_data_for_slicing, {"new_data": pl.DataFrame()})
        
        # Assertion for factor tree parameters
        expected_factor_params_delegated = {
            "alpha": 20,
            "dependencies_factor[0].beta": 200
        }
        mock_root_factor.set_nested_params_for_optimizer.assert_called_once_with(expected_factor_params_delegated)


    def test_run_single_factor_backtest_with_optimization(self):
        """Test end-to-end run_single_factor_backtest with optimization enabled."""
        
        # 1. Setup: MockNestableFactor instances
        # Dependency factor
        dep_factor_params = {"p_dep": 10.0}
        # Must pass a setting dict for factor_name to be usable in factor_key for dependencies
        dep_factor = MockNestableFactor(params=dep_factor_params, setting={"factor_name": "DepFactor"}) 
        
        # Root factor
        root_factor_params = {"p_root": 1.0}
        root_factor = MockNestableFactor(
            params=root_factor_params, 
            dependencies_factor=[dep_factor],
            setting={"factor_name": "RootFactor"}
        )
        # Manually set vt_symbols for the root factor as the engine would in init_single_factor
        # This is needed for MockNestableFactor.calculate and get_output_schema.
        # The run_single_factor_backtest will set self.engine.vt_symbols based on vt_symbols_for_factor arg.
        # The estimator's __init__ will then derive symbols from full_bar_data.
        # And fit will derive from the current slice.
        # For this test, ensure the mock_load_bar_data uses symbols consistent with this.
        root_factor.vt_symbols = self.vt_symbols # self.vt_symbols is ["SYM1.TEST", "SYM2.TEST"] from setUp

        # 2. Parameter Grid
        parameter_grid = {
            "p_root": [1.0, 2.0],  # Parameter for the root factor
            "dependencies_factor[0].p_dep": [10.0, 20.0]  # Parameter for the first dependency
        }

        # 3. Action: Call run_single_factor_backtest
        # The self.engine from setUp has load_bar_data patched.
        # mock_load_bar_data in setUp will provide data for SYM1.TEST, SYM2.TEST
        report_path = self.engine.run_single_factor_backtest(
            factor_definition=root_factor, # Pass the root factor instance
            start_datetime=self.start_date,
            end_datetime=self.end_date,
            vt_symbols_for_factor=self.vt_symbols, # Symbols for the overall run
            data_interval=Interval.DAILY,
            perform_optimization=True,
            parameter_grid=parameter_grid,
            n_splits_for_optimization_cv=2, # Small number of splits for faster test
            test_set_size_ratio=0.5 # Split data into 50% train, 50% test
        )

        # 4. Assertions
        self.assertIsNotNone(report_path, "A report path should be returned.")
        self.assertTrue(Path(report_path).exists(), "Report file should exist.")

        self.assertIsNotNone(self.engine.optimization_results, "Optimization results should be stored in the engine.")
        
        best_params = self.engine.optimization_results.get("best_params")
        self.assertIsNotNone(best_params, "Best parameters should be found.")
        
        # Check if best_params is one of the combinations from the grid
        # Example: {"p_root": 1.0, "dependencies_factor[0].p_dep": 10.0}
        #          {"p_root": 1.0, "dependencies_factor[0].p_dep": 20.0}
        #          {"p_root": 2.0, "dependencies_factor[0].p_dep": 10.0}
        #          {"p_root": 2.0, "dependencies_factor[0].p_dep": 20.0}
        self.assertIn(best_params["p_root"], parameter_grid["p_root"])
        self.assertIn(best_params["dependencies_factor[0].p_dep"], parameter_grid["dependencies_factor[0].p_dep"])

        # Verify that the best parameters were used for the final run on the test set.
        # self.engine.target_factor_instance should be the root factor from the best_estimator
        final_root_factor = self.engine.target_factor_instance
        self.assertIsInstance(final_root_factor, MockNestableFactor, "Engine's target factor should be a MockNestableFactor.")
        
        if final_root_factor: # Keep mypy happy
            self.assertEqual(final_root_factor.get_params().get("p_root"), best_params["p_root"])
            self.assertTrue(hasattr(final_root_factor, 'dependencies_factor') and final_root_factor.dependencies_factor, "Final root factor should have dependencies.")
            if final_root_factor.dependencies_factor:
                final_dep_factor = final_root_factor.dependencies_factor[0]
                self.assertIsInstance(final_dep_factor, MockNestableFactor, "Dependency should be MockNestableFactor.")
                self.assertEqual(final_dep_factor.get_params().get("p_dep"), best_params["dependencies_factor[0].p_dep"])

        # Check if final analysis results are available (run on test set)
        self.assertIsNotNone(self.engine.performance_metrics, "Performance metrics for the final run should be available.")
        # The actual values of performance_metrics will be somewhat random due to prepare_symbol_returns
        # but we can check if they exist.
        self.assertIn("sharpe", self.engine.performance_metrics)


if __name__ == '__main__':
    unittest.main()
