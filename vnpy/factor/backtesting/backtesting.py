from dataclasses import dataclass
import importlib
import gc
import json
import shutil
import time
import traceback
from datetime import datetime
from logging import INFO, DEBUG, WARNING, ERROR
from loguru import logger  # Add this import at the top with other imports
from typing import Any, Dict, Optional, List, Union, Tuple
from threading import Lock
from pathlib import Path
import re
import numpy as np
import pandas as pd
import polars as pl # Ensure polars is imported
import quantstats as qs
import psutil
import dask
from dask.delayed import Delayed
import dask.diagnostics
from scipy import stats

from vnpy.factor.memory import FactorMemory
from vnpy.factor.template import FactorTemplate
from vnpy.trader.constant import Interval
from vnpy.trader.setting import SETTINGS
from vnpy.factor.base import APP_NAME, FactorMode # Import FactorMode
# FactorTemplate and FactorMemory are assumed to be defined above or importable
from vnpy.factor.utils.factor_utils import init_factors, load_factor_setting, apply_params_to_definition_dict # Ensure these utils are compatible
from vnpy.factor.setting import get_factor_path, get_factor_setting
from sklearn.model_selection import GridSearchCV, TimeSeriesSplit
# from vnpy.factor.optimizer import FactorBacktestEstimator # Imported dynamically in method

# DEFAULT_FACTOR_MODULE_NAME = SETTINGS.get('factor.module_name', 'vnpy.factor.factors') # This is used by self.factor_module_name
DEFAULT_DATETIME_COL = "datetime" # Standard datetime column name for FactorMemory


    @staticmethod
    def _split_data_dict(
        data_dict: Dict[str, pl.DataFrame], 
        test_size_ratio: float, 
        dt_col: str # datetime column name
    ) -> Tuple[Dict[str, pl.DataFrame], Dict[str, pl.DataFrame], Optional[datetime], Optional[datetime], Optional[datetime], Optional[datetime]]:
        if not (0.0 <= test_size_ratio < 1.0): # test_size_ratio cannot be 1 (no training data)
            raise ValueError("test_size_ratio must be between 0.0 (inclusive) and 1.0 (exclusive).")

        if "close" not in data_dict or not isinstance(data_dict["close"], pl.DataFrame) or data_dict["close"].is_empty():
            # Cannot determine split sizes or date ranges if 'close' is missing/empty
            # Return empty dicts and None for dates, let caller handle this error.
            return {}, {}, None, None, None, None 

        n_total_rows = data_dict["close"].height
        n_test_rows = int(n_total_rows * test_size_ratio)
        n_train_rows = n_total_rows - n_test_rows

        train_data_dict = {}
        test_data_dict = {}

        for key, df in data_dict.items():
            if isinstance(df, pl.DataFrame) and not df.is_empty() and df.height == n_total_rows:
                train_data_dict[key] = df.slice(0, n_train_rows)
                if n_test_rows > 0:
                    test_data_dict[key] = df.slice(n_train_rows, n_test_rows)
                else: # No test rows, create empty DF preserving schema
                    test_data_dict[key] = df.clear() 
            else: # Pass through non-DF items or DFs not matching n_total_rows (e.g. metadata)
                  # For test_data_dict, create an empty version if it was a DF, else None or empty construct.
                train_data_dict[key] = df 
                if isinstance(df, pl.DataFrame):
                    test_data_dict[key] = df.clear()
                elif callable(type(df)) and hasattr(type(df), '__init__'): # Check if it's a class instance that can be "emptied"
                    try: # Attempt to create an empty instance if it's a common collection type
                        test_data_dict[key] = type(df)() if not isinstance(df, (str, int, float, bool)) else df
                    except TypeError: # Handle cases where default constructor might not work as expected
                        test_data_dict[key] = None 
                else: # For basic types or non-callable types
                    test_data_dict[key] = None


        train_start_dt = train_data_dict["close"][dt_col].min() if n_train_rows > 0 and not train_data_dict["close"].is_empty() else None
        train_end_dt = train_data_dict["close"][dt_col].max() if n_train_rows > 0 and not train_data_dict["close"].is_empty() else None
        test_start_dt = test_data_dict.get("close")[dt_col].min() if n_test_rows > 0 and test_data_dict.get("close") is not None and not test_data_dict["close"].is_empty() else None
        test_end_dt = test_data_dict.get("close")[dt_col].max() if n_test_rows > 0 and test_data_dict.get("close") is not None and not test_data_dict["close"].is_empty() else None
        
        return train_data_dict, test_data_dict, train_start_dt, train_end_dt, test_start_dt, test_end_dt

def safe_filename(name: str) -> str:
    name = re.sub(r'[^\w\.\-@]', '_', name)
    return name

@dataclass
class CalculationMetrics:
    calculation_time: float
    memory_usage: float # System memory usage delta
    cache_hits: int # For external caches if used, Dask handles its own
    error_count: int

class BacktestEngine:
    """
    A batch backtesting engine for financial factors using Dask.
    It loads all historical data for a specified period, calculates the full
    history of all configured factors, and stores them.
    """
    engine_name = APP_NAME + "BatchBacktester"

    def __init__(
        self,
        vt_symbols: List[str],
        factor_settings_path: Optional[str] = None,
        factor_module_name: Optional[str] = None,
        output_data_dir: Optional[str] = None
    ) -> None:
        # Use provided paths or defaults from settings
        self.factor_settings_path = Path(factor_settings_path) if factor_settings_path else get_factor_path("factor_settings")
        self.factor_module_name = factor_module_name or get_factor_setting("module_name")
        self.output_data_dir = Path(output_data_dir) if output_data_dir else get_factor_path("backtest_data_cache")

        try:
            self.module_factors = importlib.import_module(self.factor_module_name)
        except ImportError as e:
            self.write_log(f"Could not import factor module '{self.factor_module_name}': {e}. "
                           "Factor loading will fail.", level=ERROR)
            raise # Critical error, re-raise

        self.vt_symbols: List[str] = sorted(list(set(vt_symbols))) # Ensure unique and sorted

        self.stacked_factors: Dict[str, FactorTemplate] = {}
        self.flattened_factors: Dict[str, FactorTemplate] = {}
        self.sorted_factor_keys: List[str] = [] # For ordered initialization/processing

        # self.memory_bar will store the *full* historical OHLCV data for the batch
        self.memory_bar: Dict[str, pl.DataFrame] = {}
        self.num_data_rows: int = 0 # Number of rows/timestamps in loaded OHLCV data

        self.factor_memory_instances: Dict[str, FactorMemory] = {}
        self.target_factor_instance: Optional[FactorTemplate] = None
        self.symbol_returns_df: Optional[pl.DataFrame] = None
        self.quantile_analysis_results: Optional[Dict[str, pl.DataFrame]] = None
        self.long_short_portfolio_returns_df: Optional[pl.DataFrame] = None
        self.long_short_stats: Optional[Dict[str, float]] = None
        self.performance_metrics: Optional[Dict[str, Any]] = None
        self.optimization_results: Optional[Dict[str, Any]] = None
        
        self.dask_tasks: Dict[str, Delayed] = {}
        self.calculation_lock = Lock() # To prevent concurrent Dask graph executions if called multiple times
        
        self.factor_datetime_col = DEFAULT_DATETIME_COL
        self.metrics: Dict[str, CalculationMetrics] = {} # For storing calculation metrics

    def _prepare_output_directory(self) -> None:
        """Clears and recreates the output directory for this backtest run."""
        if self.output_data_dir.exists():
            self.write_log(f"Clearing existing output data directory: {self.output_data_dir}")
            try:
                shutil.rmtree(self.output_data_dir)
            except OSError as e:
                self.write_log(f"Error clearing directory {self.output_data_dir}: {e}. Please check permissions.", level=ERROR)
                # Depending on desired behavior, you might raise here or try to continue
        self.output_data_dir.mkdir(parents=True, exist_ok=True)
        self.write_log(f"Factor data for this run will be stored in: {self.output_data_dir}")

    def _initialize_all_factors(self) -> bool:
        """Loads factor settings and initializes FactorTemplate instances."""
        self.write_log("Initializing factors...", level=INFO)
        try:
            factor_settings_list = load_factor_setting(str(self.factor_settings_path))
            if not factor_settings_list:
                self.write_log("No factor settings found. Aborting.", level=WARNING); return False
        except Exception as e:
            self.write_log(f"Error loading factor settings from '{self.factor_settings_path}': {e}", level=ERROR); return False

        processed_settings = []
        for setting_dict in factor_settings_list:
            setting_copy = setting_dict.copy()
            setting_copy["factor_mode"] = FactorMode.BACKTEST.name # Ensure backtest mode
            if "params" not in setting_copy: setting_copy["params"] = {}
            # Pass vt_symbols to params; FactorTemplate.__init__ -> set_params
            # and specific factor __init__ (like EMAFactor) should pick up 'vt_symbols'
            setting_copy["params"]["vt_symbols"] = self.vt_symbols
            processed_settings.append(setting_copy)

        try:
            inited_instances = init_factors(
                self.module_factors,
                processed_settings,
                dependencies_module_lookup_for_instances=self.module_factors
            )
            self.stacked_factors = {f.factor_key: f for f in inited_instances}
            self.write_log(f"Initialized {len(self.stacked_factors)} stacked factors.")
            return True
        except Exception as e:
            self.write_log(f"Error during init_factors: {e}\n{traceback.format_exc()}", level=ERROR)
            return False

    def _flatten_and_sort_factors(self) -> bool:
        """Flattens the dependency tree and topologically sorts factors."""
        if not self.stacked_factors:
             self.write_log("No stacked factors to flatten.", INFO)
             self.flattened_factors = {}; self.sorted_factor_keys = []; return True

        self.flattened_factors = self._complete_factor_tree(self.stacked_factors)
        dependency_graph: Dict[str, List[str]] = {
            fk: [dep.factor_key for dep in fi.dependencies_factor if isinstance(dep, FactorTemplate)]
            for fk, fi in self.flattened_factors.items()
        }
        try:
            self.sorted_factor_keys = self._topological_sort(dependency_graph)
            self.write_log(f"Flattened and sorted {len(self.flattened_factors)} factors.") # Removed verbose list of keys
            return True
        except ValueError as e: # Circular dependency
            self.write_log(f"Circular dependency in factor graph: {e}", level=ERROR); return False


    def _initialize_factor_memory(self) -> bool:
        """Initializes FactorMemory instances for each factor."""
        self.write_log("Initializing factor memory...", level=INFO) # Changed from DEBUG to INFO and made concise
        if self.num_data_rows <= 0:
            self.write_log("Number of data rows is 0. FactorMemory max_rows will be 1. "
                           "Ensure data was loaded correctly if this is unexpected.", level=WARNING)
        
        # For batch, max_rows is the total number of data points to store full history
        max_rows_for_memory = self.num_data_rows if self.num_data_rows > 0 else 1 # FactorMemory requires max_rows > 0

        self.factor_memory_instances.clear()
        for factor_key in self.sorted_factor_keys: # Use sorted keys
            factor_instance = self.flattened_factors[factor_key]
            try:
                # Ensure factor_instance.vt_symbols is populated before calling get_output_schema,
                # as the schema generation might depend on the symbols.
                # This handles cases where a factor might not have explicitly set its own vt_symbols
                # during its __init__ (e.g., if not passed via params or not handled by FactorTemplate).
                if not hasattr(factor_instance, 'vt_symbols') or not factor_instance.vt_symbols:
                    # Attempt to set from its own parameters if 'vt_symbols' exists there
                    if hasattr(factor_instance, 'params') and factor_instance.params.get_parameter('vt_symbols'):
                        factor_instance.vt_symbols = factor_instance.params.get_parameter('vt_symbols')
                    else:
                        # Fallback to the engine's list of symbols for this backtest run.
                        factor_instance.vt_symbols = self.vt_symbols

                output_schema = factor_instance.get_output_schema()
                if self.factor_datetime_col not in output_schema:
                    raise ValueError(f"Factor '{factor_key}' schema missing datetime col '{self.factor_datetime_col}'.")

                # For batch backtesting, FactorMemory instances use the full length of loaded data.
                # Factor-specific overrides for max_rows are less common in this mode but could be
                # supported if FactorTemplate had a standard way to declare 'factor_memory_max_rows'.
                # For now, all instances use max_rows_for_memory.
                current_max_rows = max_rows_for_memory

                file_path = self.output_data_dir.joinpath(f"{safe_filename(factor_key)}.arrow")
                self.factor_memory_instances[factor_key] = FactorMemory(
                    file_path=file_path,
                    max_rows=current_max_rows,
                    schema=output_schema,
                    datetime_col=self.factor_datetime_col
                )
            except Exception as e:
                self.write_log(f"Failed to init FactorMemory for {factor_key}: {e}\n{traceback.format_exc()}", level=ERROR)
                return False
        self.write_log(f"Initialized {len(self.factor_memory_instances)} FactorMemory instances with max_rows={max_rows_for_memory}.")
        return True

    def _build_dask_computational_graph(self) -> bool:
        """Builds the Dask computational graph for all factors."""
        self.write_log("Building Dask computational graph...", level=INFO) # Changed from DEBUG to INFO and made concise
        
        # Prepare the full historical OHLCV data as a Dask Delayed object
        # Pass a copy to ensure Dask operates on a snapshot if self.memory_bar were to change (it shouldn't in batch)
        delayed_full_ohlcv_input = dask.delayed(self.memory_bar.copy())()

        self.dask_tasks.clear()
        for factor_key in self.sorted_factor_keys: # Iterate in sorted order
            self._create_dask_task(factor_key, self.flattened_factors, self.dask_tasks, delayed_full_ohlcv_input)
        
        if not self.dask_tasks and self.flattened_factors:
            self.write_log("Dask graph is empty but factors exist. Check task creation.", level=ERROR)
            return False
        self.write_log(f"Built Dask graph with {len(self.dask_tasks)} tasks.")
        return True

    def _execute_batch_dask_graph(self) -> bool:
        """Executes the full Dask graph and updates FactorMemory instances."""
        if not self.dask_tasks:
            self.write_log("No Dask tasks to execute.", level=INFO)
            return True # Not an error if no tasks

        self.write_log(f"Executing Dask computation graph for all {len(self.dask_tasks)} factors...", level=INFO)
        
        with self.calculation_lock: # Ensure only one Dask computation at a time if method is re-entrant
            start_time = time.time()
            # initial_resources = self._monitor_resources() # Optional

            try:
                with dask.diagnostics.ProgressBar(): # Provides visual feedback
                    # Compute all tasks. Results will be a list of DataFrames.
                    computed_results = dask.compute(*self.dask_tasks.values(), optimize_graph=True, scheduler='threads')
                
                end_time = time.time()
                calc_time = end_time - start_time
                self.write_log(f"Dask computation finished in {calc_time:.3f}s.", level=INFO)

                error_count = 0
                computation_errors: List[str] = []
                memory_update_errors: List[str] = []
                missing_memory_errors: List[str] = []

                for factor_key, result_df in zip(self.dask_tasks.keys(), computed_results):
                    if result_df is None:
                        computation_errors.append(f"Factor {factor_key}: computation returned None.")
                        error_count +=1; continue
                    if not isinstance(result_df, pl.DataFrame):
                        computation_errors.append(f"Factor {factor_key}: returned non-DataFrame type {type(result_df)}.")
                        error_count +=1; continue

                    fm_instance = self.factor_memory_instances.get(factor_key)
                    if fm_instance:
                        try:
                            fm_instance.update_data(result_df) # result_df is the new full history
                        except Exception as e_mem:
                            memory_update_errors.append(f"Factor {factor_key}: error updating FactorMemory - {e_mem}")
                            error_count +=1
                    else:
                        missing_memory_errors.append(f"Factor {factor_key}: No FactorMemory found to update.")
                        error_count +=1 # This indicates a setup problem
                
                if computation_errors:
                    self.write_log(f"Computation issues for {len(computation_errors)} factors:\n" + "\n".join(computation_errors), level=WARNING)
                if memory_update_errors:
                    self.write_log(f"FactorMemory update issues for {len(memory_update_errors)} factors:\n" + "\n".join(memory_update_errors), level=ERROR)
                if missing_memory_errors:
                    self.write_log(f"Missing FactorMemory instances for {len(missing_memory_errors)} factors:\n" + "\n".join(missing_memory_errors), level=ERROR)

                # Metrics calculation for the batch can be added here if needed.
                # Example structure:
                # final_resources = self._monitor_resources()
                # self.metrics["full_batch"] = CalculationMetrics(
                #     calculation_time=calc_time,
                #     memory_usage=final_resources.get("memory_percent", 0) - initial_resources.get("memory_percent", 0), # Placeholder
                #     cache_hits=0,  # Dask handles its own internal caching mechanisms
                #     error_count=error_count
                # )

                if error_count > 0:
                    self.write_log(f"Factor calculations processed with {error_count} errors.", level=WARNING)
                    return False # Indicate partial or failed success
                self.write_log("All factor calculations processed successfully.", level=INFO)
                return True

            except Exception as e_dask:
                self.write_log(f"Critical error during Dask computation or result processing: {e_dask}\n{traceback.format_exc()}", level=ERROR)
                return False
            finally:
                self._cleanup_memory_resources()
        
    def run_full_backtest(
        self,
        start_datetime: datetime,
        end_datetime: datetime,
        # vt_symbols are taken from self.vt_symbols passed to __init__
        data_interval: Any = Interval.MINUTE # Use Any for stub compatibility
    ) -> Optional[Dict[str, pl.DataFrame]]:
        """
        Orchestrates the full batch backtest: data loading, initialization, Dask execution.
        """
        self.write_log(f"Starting full factor backtest from {start_datetime} to {end_datetime} for {len(self.vt_symbols)} symbols.") # Log count of symbols
        self._prepare_output_directory() # Clear/prepare output dir for this run

        # 1. Load all historical OHLCV data into self.memory_bar
        if not self.load_bar_data(start_datetime, end_datetime, data_interval):
            self.write_log("Failed to load historical bar data. Aborting backtest.", level=ERROR)
            return None
        
        if self.num_data_rows == 0:
            self.write_log("No data rows loaded. Factors will likely produce empty results.", level=WARNING)
            # Allow proceeding if user wants to test factor logic on empty data,
            # but FactorMemory will need at least max_rows=1.

        # 2. Initialize factor instances and their FactorMemory (capacity based on num_data_rows)
        if not self._initialize_all_factors(): return None
        if not self._flatten_and_sort_factors(): return None
        if not self._initialize_factor_memory(): return None # Uses self.num_data_rows

        # 3. Build the Dask computational graph
        if not self._build_dask_computational_graph(): return None
        
        # 4. Execute the Dask graph to calculate all factors
        if not self._execute_batch_dask_graph():
            self.write_log("Dask graph execution failed or had errors. Results might be incomplete.", level=WARNING)
            # Still return what we have, or None depending on desired strictness
        
        # 5. Collect and return results
        results = {
            key: mem.get_data() for key, mem in self.factor_memory_instances.items()
        }
        self.write_log("Full factor backtest completed.")
        return results

    # --- Placeholder for data loading ---
    def load_bar_data(self, start: datetime, end: datetime, interval: Any) -> bool:
        """
        Loads historical OHLCV bar data for self.vt_symbols between start and end dates.
        Populates self.memory_bar (Dict[str, pl.DataFrame]) and self.num_data_rows.
        Each DataFrame in self.memory_bar should be wide: datetime | SYM1 | SYM2 | ...
        
        THIS IS A PLACEHOLDER. Replace with actual data loading logic (e.g., from database).
        """
        pass


    # --- Methods from original BacktestEngine (Dask graph building, utils) ---
    def _complete_factor_tree(self, factors: Dict[str, FactorTemplate]) -> Dict[str, FactorTemplate]:
        resolved_factors: Dict[str, FactorTemplate] = {}
        def traverse(factor: FactorTemplate):
            if factor.factor_key in resolved_factors: return
            for dep_instance in factor.dependencies_factor: # Assumes these are FactorTemplate instances
                if not isinstance(dep_instance, FactorTemplate): continue # Should not happen if init is correct
                traverse(dep_instance)
            resolved_factors[factor.factor_key] = factor
        for _, factor_instance in factors.items(): traverse(factor_instance)
        return resolved_factors

    def _topological_sort(self, graph: Dict[str, List[str]]) -> List[str]:
        visited_permanently, visited_temporarily, order = set(), set(), []
        
        # Collect all unique nodes from the graph keys and dependency lists
        nodes_as_keys = set(graph.keys())
        nodes_as_dependencies = set()
        for deps_list in graph.values():
            nodes_as_dependencies.update(deps_list)
        all_nodes = nodes_as_keys | nodes_as_dependencies
        
        def visit(node: str):
            if node in visited_permanently: return
            if node in visited_temporarily: raise ValueError(f"Circular dependency: {node} in {list(visited_temporarily)}")
            visited_temporarily.add(node)
            for dep_node in graph.get(node, []): visit(dep_node)
            visited_temporarily.remove(node); visited_permanently.add(node); order.append(node)
        for node_key in sorted(list(all_nodes)): # Sort for deterministic order if multiple valid
            if node_key not in visited_permanently: visit(node_key)
        return order

    def _get_factor_memory_instance_for_dask(self, factor_key: str) -> FactorMemory:
        if factor_key not in self.factor_memory_instances:
            raise RuntimeError(f"FactorMemory for {factor_key} not found. Engine init error.")
        return self.factor_memory_instances[factor_key]

    def _create_dask_task(
        self, factor_key: str, factors_dict: Dict[str, FactorTemplate],
        tasks_dict: Dict[str, Delayed], delayed_full_ohlcv_input: Delayed
    ) -> Delayed:
        if factor_key in tasks_dict: return tasks_dict[factor_key]
        factor_instance = factors_dict[factor_key]
        dependency_input_tasks: Dict[str, Delayed] = {
            dep.factor_key: self._create_dask_task(dep.factor_key, factors_dict, tasks_dict, delayed_full_ohlcv_input)
            for dep in factor_instance.dependencies_factor # Assumes these are FactorTemplate instances
        }
        factor_memory_obj_delayed = dask.delayed(self._get_factor_memory_instance_for_dask)(factor_key)
        task_input = delayed_full_ohlcv_input if not factor_instance.dependencies_factor else dependency_input_tasks
        task = dask.delayed(factor_instance.calculate)(input_data=task_input, memory=factor_memory_obj_delayed)
        tasks_dict[factor_key] = task
        return task

    def _monitor_resources(self) -> Dict[str, float]: # Kept from your original
        process = psutil.Process(); disk_io = psutil.disk_io_counters(); mem_info = process.memory_info()
        return {"memory_rss_mb": mem_info.rss/(1024*1024), "memory_vms_mb": mem_info.vms/(1024*1024),
                "memory_percent": process.memory_percent(), "cpu_percent": process.cpu_percent(interval=0.05),
                "disk_io_read_mb": disk_io.read_bytes/(1024*1024) if disk_io else 0,
                "disk_io_write_mb": disk_io.write_bytes/(1024*1024) if disk_io else 0}

    def _cleanup_memory_resources(self) -> None: # Kept from your original
        gc.collect(); self.write_log("Garbage collection performed.", level=DEBUG) # Kept as DEBUG, useful for memory profiling

    def write_log(self, msg: str, level: int = INFO) -> None: # Kept from your original
        # Simplified prefix already applied in original, keeping it as is.
        log_msg = f"[{self.engine_name}] {msg}"
        level_map = {DEBUG: logger.debug, INFO: logger.info, WARNING: logger.warning, ERROR: logger.error}
        log_func = level_map.get(level, logger.info)
        log_func(log_msg)
        
    def close(self) -> None: # Kept from your original, simple close
        self.write_log("BacktestEngine closed. Factor data is in output directory.")
        # Factor settings are not saved by backtester by default, only loaded.
        # If you want to save updated last_run_datetime, that logic would go here.

    # --- Utility methods from your original code, if needed by factors/engine ---
    def get_factor_parameters(self, factor_key: str) -> Optional[Dict[str, Any]]:
        factor = self.flattened_factors.get(factor_key)
        return factor.get_params() if factor else None

    def get_factor_instance(self, factor_key: str) -> Optional[FactorTemplate]:
        return self.flattened_factors.get(factor_key)

    def get_factor_memory_instance(self, factor_key: str) -> Optional[FactorMemory]:
        return self.factor_memory_instances.get(factor_key)

    def init_single_factor(
        self,
        factor_definition: Union[FactorTemplate, Dict, str],
        factor_json_conf_path: Optional[str] = None,
        vt_symbols_for_factor: Optional[List[str]] = None
    ) -> bool:
        self.write_log("Initializing single factor for backtesting...")

        if vt_symbols_for_factor:
            self.vt_symbols = sorted(list(set(vt_symbols_for_factor)))
            self.write_log(f"Updated engine vt_symbols to: {self.vt_symbols}")
        
        if not self.vt_symbols:
            self.write_log("vt_symbols not set. Cannot initialize factor.", level=ERROR)
            return False

        if not self.module_factors:
            try:
                self.module_factors = importlib.import_module(self.factor_module_name)
                self.write_log(f"Factor module '{self.factor_module_name}' loaded for single factor init.")
            except ImportError as e:
                self.write_log(f"Could not import factor module '{self.factor_module_name}': {e}.", level=ERROR)
                return False

        target_factor_instance_intermediate: Optional[FactorTemplate] = None
        factor_setting_dict_for_init: Optional[Dict] = None

        if isinstance(factor_definition, FactorTemplate):
            target_factor_instance_intermediate = factor_definition
            if hasattr(target_factor_instance_intermediate, 'params') and target_factor_instance_intermediate.params.get_parameter('vt_symbols') != self.vt_symbols:
                 target_factor_instance_intermediate.params.set_parameters({'vt_symbols': self.vt_symbols})
                 self.write_log(f"Aligned vt_symbols for pre-initialized factor: {target_factor_instance_intermediate.factor_key}", level=DEBUG)
            self.write_log(f"Using pre-initialized factor: {target_factor_instance_intermediate.factor_key}")

        elif isinstance(factor_definition, dict):
            factor_setting_dict_for_init = factor_definition.copy()
            if "class_name" not in factor_setting_dict_for_init:
                self.write_log("Factor settings dictionary must contain 'class_name'.", level=ERROR)
                return False
            self.write_log(f"Initializing factor from settings dictionary for class: {factor_setting_dict_for_init.get('class_name')}")

        elif isinstance(factor_definition, str): 
            if not factor_json_conf_path:
                self.write_log("factor_json_conf_path is required for factor_key string.", level=ERROR)
                return False
            try:
                all_settings_list = load_factor_setting(str(factor_json_conf_path))
                if not all_settings_list:
                    self.write_log(f"No settings found in JSON file: {factor_json_conf_path}", level=ERROR)
                    return False

                for setting_item_dict_from_json in all_settings_list:
                    temp_setting = setting_item_dict_from_json.copy()
                    temp_setting["factor_mode"] = FactorMode.BACKTEST.name
                    if "params" not in temp_setting: temp_setting["params"] = {}
                    temp_setting["params"]["vt_symbols"] = self.vt_symbols

                    temp_instances = init_factors(
                        self.module_factors,
                        [temp_setting],
                        dependencies_module_lookup_for_instances=self.module_factors
                    )
                    if not temp_instances:
                        self.write_log(f"Temp init failed for: {temp_setting.get('class_name')}", level=WARNING)
                        continue
                    
                    temp_factor = temp_instances[0]
                    if temp_factor.factor_key == factor_definition:
                        factor_setting_dict_for_init = setting_item_dict_from_json.copy()
                        self.write_log(f"Found factor for key '{factor_definition}' in JSON. Class: {factor_setting_dict_for_init.get('class_name')}")
                        break
                
                if not factor_setting_dict_for_init:
                    self.write_log(f"No factor settings in '{factor_json_conf_path}' generate key '{factor_definition}'.", level=ERROR)
                    return False
            except Exception as e:
                self.write_log(f"Error matching factor by key from '{factor_json_conf_path}': {e}\n{traceback.format_exc()}", level=ERROR)
                return False
        else:
            self.write_log(f"Invalid factor_definition type: {type(factor_definition)}.", level=ERROR)
            return False

        if factor_setting_dict_for_init:
            final_setting = factor_setting_dict_for_init.copy()
            final_setting["factor_mode"] = FactorMode.BACKTEST.name
            if "params" not in final_setting: final_setting["params"] = {}
            final_setting["params"]["vt_symbols"] = self.vt_symbols

            try:
                initialized_instances = init_factors(
                    self.module_factors,
                    [final_setting],
                    dependencies_module_lookup_for_instances=self.module_factors
                )
                if not initialized_instances:
                    self.write_log(f"Factor init failed for class: {final_setting.get('class_name')}.", level=ERROR)
                    return False
                target_factor_instance_intermediate = initialized_instances[0]
                self.write_log(f"Initialized factor instance: {target_factor_instance_intermediate.factor_key} from settings.")
            except Exception as e:
                self.write_log(f"Error initializing factor from settings {final_setting.get('class_name')}: {e}\n{traceback.format_exc()}", level=ERROR)
                return False

        if not target_factor_instance_intermediate:
            self.write_log("Factor instance could not be created.", level=ERROR)
            return False

        self.target_factor_instance = target_factor_instance_intermediate
        
        self.stacked_factors.clear()
        self.flattened_factors.clear()
        self.sorted_factor_keys.clear()
        self.dask_tasks.clear()

        self.stacked_factors = {self.target_factor_instance.factor_key: self.target_factor_instance}
        self.flattened_factors = self._complete_factor_tree(self.stacked_factors) 
        
        dependency_graph: Dict[str, List[str]] = {
            fk: [dep.factor_key for dep in fi.dependencies_factor if isinstance(dep, FactorTemplate)]
            for fk, fi in self.flattened_factors.items()
        }
        try:
            self.sorted_factor_keys = self._topological_sort(dependency_graph)
            
            if self.target_factor_instance.factor_key not in self.sorted_factor_keys:
                self.write_log(f"CRITICAL: Target factor {self.target_factor_instance.factor_key} not in sorted_keys.", level=ERROR)
                self.write_log(f"Flattened: {list(self.flattened_factors.keys())}", level=DEBUG)
                self.write_log(f"Sorted: {self.sorted_factor_keys}", level=DEBUG)
                return False

            self.write_log(f"Single factor init successful. Target: {self.target_factor_instance.factor_key}", level=INFO)
            self.write_log(f"Effective factors for run ({len(self.flattened_factors)}): {self.sorted_factor_keys}", level=DEBUG)
            return True
            
        except ValueError as e: # Circular dependency
            self.write_log(f"Circular dependency for factor '{self.target_factor_instance.factor_key}': {e}", level=ERROR)
            self.target_factor_instance = None
            self.stacked_factors.clear()
            self.flattened_factors.clear()
            self.sorted_factor_keys.clear()
            return False

    def calculate_single_factor_data(
        self
    ) -> Optional[pl.DataFrame]:
        """
        Calculates and returns the data for the single target factor.
        This method assumes that `init_single_factor` has been called,
        the target factor and its dependencies are set up, and historical
        bar data (self.memory_bar, self.num_data_rows) has been loaded.

        Returns:
            A Polars DataFrame containing the calculated data for the target factor,
            or None if calculation fails, the target factor is not set, or data is not loaded.
        """
        if self.target_factor_instance is None:
            self.write_log("Target factor not initialized. Call init_single_factor first.", level=ERROR)
            return None

        if not self.sorted_factor_keys:
            self.write_log("No factors (target or dependencies) are set up for calculation. Ensure init_single_factor succeeded.", level=ERROR)
            return None
            
        if self.target_factor_instance.factor_key not in self.flattened_factors:
            self.write_log(f"Target factor {self.target_factor_instance.factor_key} is not in self.flattened_factors. Initialization error.", level=ERROR)
            return None
            
        if not self.memory_bar or self.num_data_rows == 0:
            self.write_log("Bar data not loaded (self.memory_bar is empty or self.num_data_rows is 0). Call load_bar_data first.", level=ERROR)
            return None

        self.write_log(f"Starting calculation for single target factor: {self.target_factor_instance.factor_key}")

        # 1. Initialize FactorMemory instances for the target factor and its dependencies.
        # self.sorted_factor_keys is already scoped by init_single_factor.
        if not self._initialize_factor_memory():
            self.write_log("Failed to initialize factor memory for single factor run.", level=ERROR)
            return None
        self.write_log(f"Factor memory initialized for {len(self.factor_memory_instances)} factors (target and dependencies).")

        # 2. Build the Dask computational graph for these factors.
        # self.sorted_factor_keys is used here as well.
        if not self._build_dask_computational_graph():
            self.write_log("Failed to build Dask computation graph for single factor run.", level=ERROR)
            return None
        self.write_log(f"Dask graph built with {len(self.dask_tasks)} tasks for single factor run.")

        # 3. Execute the Dask graph.
        if not self._execute_batch_dask_graph():
            self.write_log("Dask graph execution failed or had errors for single factor run.", level=WARNING)
            # Return None on execution failure. If _execute_batch_dask_graph returns False,
            # it means there were errors, so we might not have reliable data.
            return None
        self.write_log("Dask graph executed successfully for single factor run.")

        # 4. Retrieve and return the DataFrame for the target factor.
        target_factor_key = self.target_factor_instance.factor_key
        if target_factor_key in self.factor_memory_instances:
            # get_data() returns a copy, so it's safe to return.
            factor_data = self.factor_memory_instances[target_factor_key].get_data()
            
            if factor_data is None: # FactorMemory.get_data() could theoretically return None if file is missing post-init
                self.write_log(f"Data for target factor {target_factor_key} is None after retrieval from FactorMemory.", level=ERROR)
                return None
            elif factor_data.is_empty():
                self.write_log(f"Data for target factor {target_factor_key} is empty. Shape: {factor_data.shape}", level=WARNING)
                return factor_data 
            else:
                self.write_log(f"Successfully retrieved data for target factor {target_factor_key}. Shape: {factor_data.shape}")
                return factor_data
        else:
            self.write_log(f"FactorMemory instance for target factor {target_factor_key} not found after execution. This should not happen.", level=ERROR)
            return None

    def prepare_symbol_returns(self, reference_datetime_series: Optional[pl.Series] = None) -> bool:
        """
        Prepares a Polars DataFrame representing symbol returns, structured similarly
        to the factor value DataFrames (datetime index, symbol columns).

        For now, this method generates placeholder random data. In a real implementation,
        this would load actual historical returns.

        Args:
            reference_datetime_series: A Polars Series containing the datetime points for
                                       which returns should be generated. If None, tries to
                                       use datetimes from loaded close prices (self.memory_bar['close']).

        Returns:
            True if successful, False otherwise.
        """
        self.write_log("Preparing symbol returns data (using placeholder random data)...")

        actual_datetime_series: Optional[pl.Series] = None

        if reference_datetime_series is not None:
            actual_datetime_series = reference_datetime_series
        else:
            if "close" not in self.memory_bar or self.memory_bar["close"].is_empty():
                self.write_log("Cannot prepare symbol returns: No reference datetimes. Load bar data first (self.memory_bar['close'] is missing or empty).", level=ERROR)
                return False
            if self.factor_datetime_col not in self.memory_bar["close"].columns:
                self.write_log(f"Cannot prepare symbol returns: Datetime column '{self.factor_datetime_col}' not in loaded close prices.", level=ERROR)
                return False
            actual_datetime_series = self.memory_bar["close"][self.factor_datetime_col]

        if actual_datetime_series is None or actual_datetime_series.is_empty(): # Explicit check for None as well
            self.write_log("Cannot prepare symbol returns: Reference datetime series is empty or could not be determined.", level=ERROR)
            return False

        if not self.vt_symbols:
            self.write_log("Cannot prepare symbol returns: No vt_symbols defined in the engine.", level=ERROR)
            return False

        num_dates = len(actual_datetime_series)
        if num_dates == 0: # Should be caught by is_empty, but as a safeguard
            self.write_log("Cannot prepare symbol returns: Number of dates in reference series is 0.", level=ERROR)
            return False
        
        returns_data = {self.factor_datetime_col: actual_datetime_series}
        for symbol in self.vt_symbols:
            # Generate random returns between -0.05 and 0.05 for placeholder
            returns_data[symbol] = np.random.uniform(-0.05, 0.05, num_dates)
        
        try:
            self.symbol_returns_df = pl.DataFrame(returns_data)
            # Ensure datetime column is sorted if not already (Polars DataFrame creation does not guarantee order from dict)
            if not self.symbol_returns_df.is_empty(): # Avoid sorting empty dataframe
                self.symbol_returns_df = self.symbol_returns_df.sort(self.factor_datetime_col)
            
            self.write_log(f"Placeholder symbol returns data prepared. Shape: {self.symbol_returns_df.shape}", level=INFO)
            return True
        except Exception as e:
            self.write_log(f"Error creating placeholder symbol returns DataFrame: {e}\n{traceback.format_exc()}", level=ERROR)
            self.symbol_returns_df = None
            return False

    def perform_quantile_analysis(
        self,
        factor_data_df: pl.DataFrame, 
        num_quantiles: int = 5,
        returns_look_ahead_period: int = 1 
    ) -> bool:
        """
        Performs quantile analysis based on factor values and subsequent symbol returns.

        Args:
            factor_data_df: DataFrame with datetime index and symbol columns (factor values).
                            Assumes this is the direct output from calculate_single_factor_data.
            num_quantiles: Number of quantiles to divide symbols into (e.g., 5 for quintiles).
            returns_look_ahead_period: Number of periods to shift returns for calculating
                                       forward returns. E.g., 1 means use next period's return.
        Returns:
            True if analysis was successful, False otherwise.
        """
        self.write_log(f"Performing quantile analysis with {num_quantiles} quantiles and {returns_look_ahead_period}-period forward returns...")

        if factor_data_df is None or factor_data_df.is_empty():
            self.write_log("Factor data is empty or None. Cannot perform quantile analysis.", level=ERROR)
            return False
        
        if self.symbol_returns_df is None or self.symbol_returns_df.is_empty():
            self.write_log("Symbol returns data is empty or None. Cannot perform quantile analysis.", level=ERROR)
            return False

        if num_quantiles <= 0:
            self.write_log("Number of quantiles must be positive.", level=ERROR)
            return False

        if returns_look_ahead_period <= 0:
            self.write_log("Returns look-ahead period must be positive.", level=ERROR)
            return False

        if self.factor_datetime_col not in factor_data_df.columns or \
           self.factor_datetime_col not in self.symbol_returns_df.columns:
            self.write_log(f"Datetime column '{self.factor_datetime_col}' missing in factor or returns data.", level=ERROR)
            return False

        symbols_in_factor_data = [sym for sym in self.vt_symbols if sym in factor_data_df.columns]
        symbols_in_returns_data = [sym for sym in self.vt_symbols if sym in self.symbol_returns_df.columns]
        
        if not symbols_in_factor_data or not symbols_in_returns_data:
            self.write_log("No common symbols found or symbol list is empty based on vt_symbols and available columns.", level=ERROR)
            return False

        forward_returns_df = self.symbol_returns_df.select(
            [self.factor_datetime_col] + [pl.col(sym).shift(-returns_look_ahead_period).alias(sym) for sym in symbols_in_returns_data]
        )
        
        factor_long_df = factor_data_df.melt(
            id_vars=[self.factor_datetime_col],
            value_vars=symbols_in_factor_data,
            variable_name="symbol",
            value_name="factor_value"
        ).drop_nulls(subset=["factor_value"])

        forward_returns_long_df = forward_returns_df.melt(
            id_vars=[self.factor_datetime_col],
            value_vars=symbols_in_returns_data,
            variable_name="symbol",
            value_name="forward_return"
        )

        merged_df = factor_long_df.join(
            forward_returns_long_df,
            on=[self.factor_datetime_col, "symbol"],
            how="inner" 
        ).drop_nulls(subset=["forward_return"])

        if merged_df.is_empty():
            self.write_log("No valid data after merging factor values with forward returns.", level=ERROR)
            return False

        # Assign quantiles using window functions over datetime groups
        quantiled_df = merged_df.with_columns(
            (
                (pl.col("factor_value").rank(method="ordinal").over(self.factor_datetime_col) - 1) * 
                num_quantiles / 
                pl.col("factor_value").count().over(self.factor_datetime_col)
            ).floor() + 1  # Adding 1 to make quantiles 1-indexed
            .alias("quantile")
        )
        
        if quantiled_df.is_empty(): # Should not happen if merged_df was not empty
            self.write_log("Quantiled DataFrame is unexpectedly empty.", level=ERROR)
            return False
            
        quantile_returns_by_time_df = quantiled_df.group_by([self.factor_datetime_col, "quantile"]).agg(
            pl.col("forward_return").mean().alias("mean_quantile_return")
        ).sort([self.factor_datetime_col, "quantile"])

        average_quantile_returns_overall_df = quantile_returns_by_time_df.group_by("quantile").agg(
            pl.col("mean_quantile_return").mean().alias("average_return")
        ).sort("quantile")

        self.quantile_analysis_results = {
            "by_time": quantile_returns_by_time_df,
            "overall_average": average_quantile_returns_overall_df
        }
        
        self.write_log("Quantile analysis completed.", level=INFO)
        if not average_quantile_returns_overall_df.is_empty():
            self.write_log(f"Overall average returns per quantile:\n{average_quantile_returns_overall_df}", level=INFO)
        else:
            self.write_log("Overall average returns per quantile is empty.", level=WARNING)
        return True

    def perform_long_short_analysis(
        self,
        factor_data_df: pl.DataFrame,
        returns_look_ahead_period: int = 1,
        long_percentile_threshold: float = 0.5, 
        short_percentile_threshold: float = 0.5, 
    ) -> bool:
        """
        Performs long-short portfolio analysis based on factor values.
        Long leg: Ranks are in the top X% defined by long_percentile_threshold.
        Short leg: Ranks are in the bottom Y% defined by short_percentile_threshold.

        Args:
            factor_data_df: DataFrame with datetime index and symbol columns (factor values).
            returns_look_ahead_period: Number of periods to shift returns for forward returns.
            long_percentile_threshold: Proportion of assets from top ranks for long leg (e.g., 0.3 for top 30%).
            short_percentile_threshold: Proportion of assets from bottom ranks for short leg (e.g., 0.3 for bottom 30%).
        Returns:
            True if analysis was successful, False otherwise.
        """
        self.write_log(f"Performing long-short portfolio analysis. Forward returns: {returns_look_ahead_period}-period. "
                       f"Long top {long_percentile_threshold*100:.1f}%, Short bottom {short_percentile_threshold*100:.1f}%.")

        if factor_data_df is None or factor_data_df.is_empty():
            self.write_log("Factor data is empty. Cannot perform long-short analysis.", level=ERROR); return False
        if self.symbol_returns_df is None or self.symbol_returns_df.is_empty():
            self.write_log("Symbol returns data is empty. Cannot perform long-short analysis.", level=ERROR); return False
        if not (0 < long_percentile_threshold <= 1) or not (0 < short_percentile_threshold <= 1):
            self.write_log("Percentile thresholds must be > 0 and <= 1.", level=ERROR); return False
        if returns_look_ahead_period <= 0:
            self.write_log("Returns look-ahead period must be positive.", level=ERROR); return False

        if self.factor_datetime_col not in factor_data_df.columns or \
           self.factor_datetime_col not in self.symbol_returns_df.columns:
            self.write_log(f"Datetime column '{self.factor_datetime_col}' missing.", level=ERROR); return False

        symbols_in_factor_data = [sym for sym in self.vt_symbols if sym in factor_data_df.columns]
        symbols_in_returns_data = [sym for sym in self.vt_symbols if sym in self.symbol_returns_df.columns]

        if not symbols_in_factor_data or not symbols_in_returns_data:
            self.write_log("No common symbols for analysis based on available columns.", level=ERROR); return False

        forward_returns_df = self.symbol_returns_df.select(
            [self.factor_datetime_col] + [pl.col(sym).shift(-returns_look_ahead_period).alias(sym) for sym in symbols_in_returns_data]
        )

        factor_long_df = factor_data_df.melt(
            id_vars=[self.factor_datetime_col], value_vars=symbols_in_factor_data,
            variable_name="symbol", value_name="factor_value"
        ).drop_nulls(subset=["factor_value"])

        forward_returns_long_df = forward_returns_df.melt(
            id_vars=[self.factor_datetime_col], value_vars=symbols_in_returns_data,
            variable_name="symbol", value_name="forward_return"
        )

        merged_df = factor_long_df.join(
            forward_returns_long_df, on=[self.factor_datetime_col, "symbol"], how="inner"
        ).drop_nulls(subset=["forward_return"])

        if merged_df.is_empty():
            self.write_log("No valid data after merging factors and forward returns.", level=ERROR); return False
        
        ranked_df = merged_df.with_columns([
            pl.col("factor_value").rank(method="ordinal").over(self.factor_datetime_col).alias("rank"),
            pl.col("symbol").count().over(self.factor_datetime_col).alias("total_symbols_per_dt")
        ])
        
        # Long leg: rank percentile > (1 - long_percentile_threshold)
        # Short leg: rank percentile <= short_percentile_threshold
        # rank percentile = rank / total_symbols_per_dt
        portfolio_df = ranked_df.with_columns([
            (pl.col("rank") / pl.col("total_symbols_per_dt") > (1.0 - long_percentile_threshold)).alias("long_leg"),
            (pl.col("rank") / pl.col("total_symbols_per_dt") <= short_percentile_threshold).alias("short_leg")
        ])

        long_returns = portfolio_df.filter(pl.col("long_leg")).group_by(self.factor_datetime_col).agg(
            pl.col("forward_return").mean().alias("mean_long_return")
        )
        short_returns = portfolio_df.filter(pl.col("short_leg")).group_by(self.factor_datetime_col).agg(
            pl.col("forward_return").mean().alias("mean_short_return")
        )
        
        ls_returns_calc_df = long_returns.join(
            short_returns, on=self.factor_datetime_col, how="outer" 
        ).sort(self.factor_datetime_col)
        
        ls_returns_calc_df = ls_returns_calc_df.with_columns([
            (pl.col("mean_long_return").fill_null(0.0) - pl.col("mean_short_return").fill_null(0.0)).alias("ls_portfolio_return")
        ])

        self.long_short_portfolio_returns_df = ls_returns_calc_df.select([self.factor_datetime_col, "ls_portfolio_return"])

        if self.long_short_portfolio_returns_df.is_empty():
            self.write_log("Long-short portfolio returns DataFrame is empty.", level=ERROR)
            self.long_short_stats = {"t_statistic": float('nan'), "p_value": float('nan'), "mean_return": float('nan')}
            return False

        portfolio_returns_series = self.long_short_portfolio_returns_df["ls_portfolio_return"].drop_nulls()
        
        if portfolio_returns_series.len() >= 2: # Min samples for t-test
            mean_ret = portfolio_returns_series.mean()

            if mean_ret is None: 
                self.write_log("Mean of portfolio returns is null. Cannot perform t-test.", level=WARNING)
                self.long_short_stats = {"t_statistic": float('nan'), "p_value": float('nan'), "mean_return": float('nan')}
            else:
                t_stat, p_value = stats.ttest_1samp(portfolio_returns_series.to_numpy(), 0, nan_policy='omit')
                self.long_short_stats = {"t_statistic": t_stat, "p_value": p_value, "mean_return": mean_ret}
                self.write_log(f"Long-Short Portfolio Stats: Mean Return={mean_ret:.6f}, T-stat={t_stat:.4f}, P-value={p_value:.4f}", level=INFO)
        else:
            mean_ret_val = portfolio_returns_series.mean() if not portfolio_returns_series.is_empty() else None
            self.write_log("Not enough data points in L-S portfolio returns for t-test.", level=WARNING)
            self.long_short_stats = {"t_statistic": float('nan'), "p_value": float('nan'), 
                                     "mean_return": mean_ret_val if mean_ret_val is not None else float('nan')}

        self.write_log("Long-short portfolio analysis completed.", level=INFO)
        return True

    def calculate_performance_metrics(self) -> bool:
        """
        Calculates standard performance metrics for the long-short portfolio
        using the quantstats package.

        Assumes self.long_short_portfolio_returns_df is populated.
        Stores results in self.performance_metrics.

        Returns:
            True if successful, False otherwise.
        """
        self.write_log("Calculating performance metrics using quantstats...")

        if self.long_short_portfolio_returns_df is None or self.long_short_portfolio_returns_df.is_empty():
            self.write_log("L-S portfolio returns data is empty. Cannot calculate performance metrics.", level=ERROR)
            return False

        required_cols = [self.factor_datetime_col, "ls_portfolio_return"]
        if not all(col in self.long_short_portfolio_returns_df.columns for col in required_cols):
            self.write_log(f"Required columns {required_cols} not in L-S portfolio returns DataFrame.", level=ERROR)
            return False

        try:
            # Prepare data for quantstats: Pandas Series with DatetimeIndex, NaNs filled.
            returns_pl_df = self.long_short_portfolio_returns_df.sort(self.factor_datetime_col)
            
            # Fill NaNs in returns column before converting to Pandas
            returns_pl_df = returns_pl_df.with_columns(
                pl.col("ls_portfolio_return").fill_null(0.0).alias("ls_portfolio_return")
            )
            
            # Convert to Pandas DataFrame
            portfolio_pd_df = returns_pl_df.to_pandas()

            if portfolio_pd_df.empty:
                self.write_log("Pandas DataFrame for quantstats is empty after conversion.", level=ERROR)
                return False
                
            portfolio_pd_df = portfolio_pd_df.set_index(self.factor_datetime_col)
            returns_series_pd = portfolio_pd_df["ls_portfolio_return"]
            
            if not isinstance(returns_series_pd.index, pd.DatetimeIndex):
                returns_series_pd.index = pd.to_datetime(returns_series_pd.index)
                
            returns_series_pd = returns_series_pd.astype(float)

        except Exception as e:
            self.write_log(f"Error converting L-S returns to Pandas Series for quantstats: {e}\n{traceback.format_exc()}", level=ERROR)
            return False

        if returns_series_pd.empty: # Should be caught by portfolio_pd_df.empty, but defensive
            self.write_log("Portfolio returns series for quantstats is empty.", level=ERROR)
            return False
        
        # It's generally good practice to ensure no NaNs/Infs if quantstats is sensitive,
        # though fill_null(0.0) should have handled NaNs from Polars side.
        if returns_series_pd.isnull().any() or np.isinf(returns_series_pd).any():
            self.write_log(f"Pandas returns series still contains NaNs/Infs before quantstats. This is unexpected.", level=WARNING)
            # returns_series_pd = returns_series_pd.fillna(0.0).replace([np.inf, -np.inf], 0.0) # Aggressive cleanup if needed

        try:
            metrics = {}
            metrics['sharpe'] = qs.stats.sharpe(returns_series_pd)
            metrics['max_drawdown'] = qs.stats.max_drawdown(returns_series_pd)
            metrics['cumulative_returns'] = qs.stats.comp(returns_series_pd).iloc[-1] # Get last value for total cumulative return
            metrics['cagr'] = qs.stats.cagr(returns_series_pd)
            metrics['volatility'] = qs.stats.volatility(returns_series_pd)
            metrics['win_rate'] = qs.stats.win_rate(returns_series_pd)
            metrics['avg_win'] = qs.stats.avg_win(returns_series_pd)
            metrics['avg_loss'] = qs.stats.avg_loss(returns_series_pd)
            metrics['sortino'] = qs.stats.sortino(returns_series_pd)
            metrics['calmar'] = qs.stats.calmar(returns_series_pd)
            
            # Add more common stats
            metrics['skew'] = qs.stats.skew(returns_series_pd)
            metrics['kurtosis'] = qs.stats.kurtosis(returns_series_pd)
            metrics['value_at_risk'] = qs.stats.value_at_risk(returns_series_pd) # Daily VaR
            metrics['expected_shortfall'] = qs.stats.expected_shortfall(returns_series_pd) # Daily ES / CVaR
            metrics['profit_factor'] = qs.stats.profit_factor(returns_series_pd)
            
            self.performance_metrics = {}
            for k, v in metrics.items():
                if isinstance(v, (float, np.generic)) and (np.isnan(v) or np.isinf(v)): # np.generic for numpy scalars
                    self.performance_metrics[k] = None 
                elif isinstance(v, pd.Series): # Some stats might return Series
                     self.performance_metrics[k] = v.to_dict() # Or handle as needed
                else:
                    self.performance_metrics[k] = v

            self.write_log("Performance metrics calculated successfully.", level=INFO)
            log_metrics_subset = {
                k: self.performance_metrics[k] for k in ['sharpe', 'max_drawdown', 'cumulative_returns', 'cagr'] 
                if k in self.performance_metrics and self.performance_metrics[k] is not None
            }
            self.write_log(f"Key Performance Metrics: {log_metrics_subset}", level=INFO)
            return True

        except Exception as e:
            self.write_log(f"Error during quantstats calculation: {e}\n{traceback.format_exc()}", level=ERROR)
            self.performance_metrics = None
            return False

    def generate_single_factor_report(self) -> Optional[Dict[str, Any]]:
        """
        Compiles all analysis results for the single factor backtest into a dictionary.

        Returns:
            A dictionary containing the report, or None if crucial data is missing.
        """
        self.write_log("Generating single factor backtest report...")

        if self.target_factor_instance is None:
            self.write_log("Target factor not set. Cannot generate report.", level=ERROR)
            return None

        # Attempt to get start/end datetimes if set by the run method
        start_dt_str = 'N/A'
        if hasattr(self, 'start_datetime_for_report') and isinstance(self.start_datetime_for_report, datetime):
            start_dt_str = self.start_datetime_for_report.strftime("%Y-%m-%d %H:%M:%S")
            
        end_dt_str = 'N/A'
        if hasattr(self, 'end_datetime_for_report') and isinstance(self.end_datetime_for_report, datetime):
            end_dt_str = self.end_datetime_for_report.strftime("%Y-%m-%d %H:%M:%S")

        report_data = {
            "factor_key": self.target_factor_instance.factor_key,
            "factor_parameters": self.target_factor_instance.get_params(),
            "backtest_run_datetime": datetime.now().strftime("%Y-%m-%d %H:%M:%S"),
            "vt_symbols_tested": self.vt_symbols, # Symbols used in this specific backtest run
            "data_period_analyzed": {
                "start_datetime": start_dt_str,
                "end_datetime": end_dt_str,
            },
            "analysis_results": {} # Initialize this sub-dictionary
        }

        # Quantile Analysis Results
        if hasattr(self, 'quantile_analysis_results') and self.quantile_analysis_results:
            qa_overall = self.quantile_analysis_results.get("overall_average")
            qa_by_time = self.quantile_analysis_results.get("by_time") # For row count check
            
            report_data["analysis_results"]["quantile_analysis"] = {
                "overall_average_returns": qa_overall.to_dicts() if qa_overall is not None and not qa_overall.is_empty() else None,
            }
            if qa_by_time is not None:
                 self.write_log(f"Quantile analysis by_time data (not included in JSON) has {qa_by_time.shape[0]} rows.", level=DEBUG)

        # Long-Short Portfolio Analysis Results
        ls_stats = getattr(self, 'long_short_stats', None)
        if ls_stats:
            report_data["analysis_results"]["long_short_portfolio_statistics"] = ls_stats
        
        ls_returns_df = getattr(self, 'long_short_portfolio_returns_df', None)
        if ls_returns_df is not None:
            self.write_log(f"Long-short portfolio returns timeseries (not included in JSON) has {ls_returns_df.shape[0]} rows.", level=DEBUG)
            # Optionally, add some summary like overall mean L/S return if not in ls_stats
            if "mean_return" not in (ls_stats or {}): # If not already in ls_stats
                ls_mean = ls_returns_df["ls_portfolio_return"].mean()
                if ls_mean is not None:
                     report_data["analysis_results"].setdefault("long_short_portfolio_statistics", {})["mean_ls_return_from_ts"] = ls_mean


        # Performance Metrics from quantstats
        if hasattr(self, 'performance_metrics') and self.performance_metrics:
            report_data["analysis_results"]["performance_metrics_quantstats"] = self.performance_metrics
        
        # Add Parameter Optimization Summary if available
        if hasattr(self, 'optimization_results') and self.optimization_results:
            report_data["parameter_optimization_summary"] = self.optimization_results
            self.write_log("Added optimization summary to the report.", INFO)

        if not report_data["analysis_results"].get("quantile_analysis") and \
           not report_data["analysis_results"].get("long_short_portfolio_statistics") and \
           not report_data["analysis_results"].get("performance_metrics_quantstats") and \
           not report_data.get("parameter_optimization_summary"): # Check if optimization summary was also not added
            self.write_log("No analysis results or optimization summary were available to include in the report content.", level=WARNING)

        self.write_log("Report dictionary generation complete.", level=INFO)
        return report_data

    def save_report(
        self,
        report_data: Dict[str, Any],
        report_filename_prefix: str = "single_factor_report"
    ) -> Optional[Path]:
        """
        Saves the generated report dictionary to a JSON file in the output directory.

        Args:
            report_data: The report dictionary generated by generate_single_factor_report.
            report_filename_prefix: Prefix for the report filename.

        Returns:
            Path to the saved report file, or None if saving fails.
        """
        if not report_data:
            self.write_log("Report data is empty. Nothing to save.", level=WARNING)
            return None

        # Ensure output directory exists (it's an attribute of the class)
        if not self.output_data_dir.exists():
            try:
                self.output_data_dir.mkdir(parents=True, exist_ok=True)
                self.write_log(f"Created output directory: {self.output_data_dir}")
            except Exception as e:
                self.write_log(f"Error creating output directory {self.output_data_dir}: {e}", level=ERROR)
                return None # Cannot save if dir creation fails
                
        factor_key_safe_name = "unknown_factor"
        if self.target_factor_instance: # Check if target_factor_instance is not None
            factor_key_safe_name = safe_filename(self.target_factor_instance.factor_key)

        timestamp = datetime.now().strftime("%Y%m%d_%H%M%S")
        filename = f"{report_filename_prefix}_{factor_key_safe_name}_{timestamp}.json"
        filepath = self.output_data_dir.joinpath(filename)

        try:
            with open(filepath, 'w', encoding='utf-8') as f:
                json.dump(report_data, f, indent=4, ensure_ascii=False, default=str)
            self.write_log(f"Report saved successfully to: {filepath}", level=INFO)
            return filepath
        except Exception as e:
            self.write_log(f"Error saving report to {filepath}: {e}\n{traceback.format_exc()}", level=ERROR)
            return None

    def run_single_factor_backtest(
        self,
        factor_definition: Union[FactorTemplate, Dict, str],
        start_datetime: datetime,
        end_datetime: datetime,
        vt_symbols_for_factor: List[str],  # vt_symbols for the factor if NOT optimizing
        factor_json_conf_path: Optional[str] = None,
        data_interval: Any = Interval.MINUTE,
        num_quantiles: int = 5,
        returns_look_ahead_period: int = 1,
        long_percentile_threshold: float = 0.5,
        short_percentile_threshold: float = 0.5,
        output_dir_override: Optional[str] = None,
        report_filename_prefix: str = "single_factor_report",
        perform_optimization: bool = False,
        parameter_grid: Optional[Dict[str, List[Any]]] = None,
        n_splits_for_optimization_cv: int = 3,
        test_set_size_ratio: float = 0.2
    ) -> Optional[Path]:
        
        self.write_log(f"Starting single factor backtest run. Optimization: {perform_optimization}. Period: {start_datetime} to {end_datetime}.", INFO)

        original_output_dir = self.output_data_dir
        if output_dir_override:
            self.output_data_dir = Path(output_dir_override)
            self.write_log(f"Output directory overridden: {self.output_data_dir}", INFO)
        
        self._prepare_output_directory()

        # --- Load full data period first ---
        # The engine's vt_symbols will be set to vt_symbols_for_factor initially for data loading.
        # If optimization occurs, vt_symbols might be refined based on the symbols present in the training/testing data splits.
        self.vt_symbols = vt_symbols_for_factor # Set engine symbols for full data load
        _ = self.load_bar_data(start_datetime, end_datetime, data_interval)
        
        if self.num_data_rows == 0: # If load_bar_data is a pass-through and no real data loaded
            time_delta = end_datetime - start_datetime
            if data_interval == Interval.MINUTE: self.num_data_rows = int(time_delta.total_seconds() / 60)
            elif data_interval == Interval.HOUR: self.num_data_rows = int(time_delta.total_seconds() / 3600)
            elif data_interval == Interval.DAILY: self.num_data_rows = time_delta.days
            else: self.num_data_rows = int(time_delta.total_seconds() / 60)
            if self.num_data_rows <= 0: self.num_data_rows = 200 # Default if interval is too small or dates are same
            self.write_log(f"Calculated self.num_data_rows = {self.num_data_rows} for placeholder full period.", DEBUG)

        if ("close" not in self.memory_bar or self.memory_bar["close"].is_empty()) and self.num_data_rows > 0 and self.vt_symbols:
            self.write_log(f"Populating memory_bar['close'] with dummy data for full period: {self.num_data_rows} points.", DEBUG)
            dummy_dates_list = [end_datetime - timedelta(minutes=i) for i in range(self.num_data_rows - 1, -1, -1)] # Generate backwards from end_datetime
            dummy_dates = pl.Series(self.factor_datetime_col, sorted(dummy_dates_list), dtype=pl.Datetime)
            if not dummy_dates.is_empty():
                close_data = {self.factor_datetime_col: dummy_dates}
                for sym in self.vt_symbols: close_data[sym] = np.random.rand(len(dummy_dates)) * 100 + 50
                self.memory_bar["close"] = pl.DataFrame(close_data)
                self.num_data_rows = len(dummy_dates)
            else:
                self.write_log("Failed to create dummy dates for placeholder. Critical error.", ERROR); return None
        elif self.num_data_rows == 0 or not self.vt_symbols:
             self.write_log("num_data_rows is 0 or vt_symbols empty. Cannot populate dummy bar data for full period.", WARNING)
        
        full_period_memory_bar = {k: v.clone() for k, v in self.memory_bar.items() if isinstance(v, pl.DataFrame)}
        full_period_num_rows = self.num_data_rows

        current_factor_definition = factor_definition 
        data_for_final_backtest: Dict[str, pl.DataFrame] = {}
        num_rows_for_final_backtest = 0
        final_s_dt, final_e_dt = start_datetime, end_datetime # Default to full period

        if perform_optimization and parameter_grid:
            if isinstance(factor_definition, str):
                self.write_log("Factor definition by string key is not supported with optimization.", ERROR)
                if output_dir_override: self.output_data_dir = original_output_dir
                return None

            self.write_log(f"Optimization enabled. Splitting data with test ratio: {test_set_size_ratio}", INFO)
            train_data_dict, test_data_dict, tr_s, tr_e, ts_s, ts_e = BacktestEngine._split_data_dict(
                full_period_memory_bar, test_set_size_ratio, self.factor_datetime_col
            )

            if not train_data_dict or not train_data_dict.get("close") or train_data_dict.get("close").is_empty():
                self.write_log("Training data is empty after split. Cannot perform optimization.", ERROR)
                data_for_final_backtest = full_period_memory_bar
                num_rows_for_final_backtest = full_period_num_rows
                self.write_log("Fallback: Proceeding with backtest on full data period without optimization.", WARNING)
            else:
                self.write_log(f"Training data period for optimization: {tr_s} to {tr_e}", INFO)
                opt_factor_class_name = ""
                opt_initial_settings: Dict[str, Any] = {}
                if isinstance(factor_definition, FactorTemplate):
                    opt_factor_class_name = factor_definition.__class__.__name__
                    opt_initial_settings = factor_definition.get_params()
                elif isinstance(factor_definition, dict):
                    opt_factor_class_name = factor_definition.get("class_name", "")
                    opt_initial_settings = factor_definition.get("params", {}).copy() # Use a copy
                    if not opt_factor_class_name:
                        self.write_log("Factor definition dict must contain 'class_name' for optimization.", ERROR); return None
                
                best_params = self.optimize_factor_parameters(
                    factor_class_name=opt_factor_class_name,
                    initial_factor_settings=opt_initial_settings,
                    parameter_grid=parameter_grid,
                    full_bar_data=train_data_dict,
                    n_splits_for_cv=n_splits_for_optimization_cv
                )

                if best_params:
                    self.write_log(f"Optimization successful. Best params found: {best_params}", INFO)
                    
                    best_estimator = self.optimization_results.get("best_estimator") if self.optimization_results else None
                    
                    if best_estimator and hasattr(best_estimator, 'root_factor_for_optimization') and \
                       best_estimator.root_factor_for_optimization:
                        current_factor_definition = best_estimator.root_factor_for_optimization
                        self.write_log(f"Using factor tree from best_estimator ('{current_factor_definition.factor_key}') for final backtest.", INFO)
                    else:
                        self.write_log("Best estimator or its root factor not available from optimization_results. Applying best_params to original factor definition.", WARNING)
                        if isinstance(current_factor_definition, FactorTemplate):
                            try:
                                current_factor_definition.set_nested_params_for_optimizer(best_params)
                                self.write_log(f"Applied best_params to FactorTemplate instance '{current_factor_definition.factor_key}' using set_nested_params_for_optimizer.", INFO)
                            except Exception as e_set_nested:
                                self.write_log(f"Error applying best_params with set_nested_params_for_optimizer to FactorTemplate: {e_set_nested}", ERROR)
                        elif isinstance(current_factor_definition, dict):
                            try:
                                updated_def_dict = apply_params_to_definition_dict(current_factor_definition, best_params)
                                current_factor_definition = updated_def_dict # Replace with the new dict
                                self.write_log(f"Applied best_params to factor definition dictionary using apply_params_to_definition_dict. Root params: {current_factor_definition.get('params')}", INFO)
                            except Exception as e_apply_dict:
                                self.write_log(f"Error applying best_params to definition dictionary: {e_apply_dict}", ERROR)
                                # current_factor_definition remains unchanged if helper fails
                    
                    if test_data_dict and test_data_dict.get("close") and not test_data_dict.get("close").is_empty():
                        data_for_final_backtest = test_data_dict
                        num_rows_for_final_backtest = test_data_dict["close"].height
                        final_s_dt, final_e_dt = ts_s, ts_e
                        self.write_log(f"Using test set for final backtest: {ts_s} to {ts_e}", INFO)
                    else:
                        data_for_final_backtest = full_period_memory_bar
                        num_rows_for_final_backtest = full_period_num_rows
                        self.write_log("No test data or ratio was 0. Running on full period with optimized params.", INFO)
                else:
                    self.write_log("Optimization failed. Running on full period with original params.", WARNING)
                    data_for_final_backtest = full_period_memory_bar
                    num_rows_for_final_backtest = full_period_num_rows
        else:
            self.write_log("Optimization not enabled or no grid. Running on full data period.", INFO)
            data_for_final_backtest = full_period_memory_bar
            num_rows_for_final_backtest = full_period_num_rows

        self.memory_bar = data_for_final_backtest
        self.num_data_rows = num_rows_for_final_backtest
        self.start_datetime_for_report = final_s_dt if final_s_dt else start_datetime
        self.end_datetime_for_report = final_e_dt if final_e_dt else end_datetime

        if self.num_data_rows == 0:
            self.write_log("No data for final backtest run. Aborting.", ERROR)
            if output_dir_override: self.output_data_dir = original_output_dir
            return None

        # Derive vt_symbols from the actual data being used for the final backtest
        final_vt_symbols_list = [c for c in self.memory_bar.get("close", pl.DataFrame()).columns if c != self.factor_datetime_col]
        if not final_vt_symbols_list: # If somehow close DF is missing or has no symbols
             self.write_log("No symbols found in the data for the final backtest. Aborting.", ERROR)
             if output_dir_override: self.output_data_dir = original_output_dir
             return None

        # init_single_factor will update self.vt_symbols based on final_vt_symbols_list
        if not self.init_single_factor(current_factor_definition, factor_json_conf_path, final_vt_symbols_list):
            self.write_log("Factor initialization for final run failed. Aborting.", ERROR)
            if output_dir_override: self.output_data_dir = original_output_dir
            return None
        
        factor_key_for_log = self.target_factor_instance.factor_key if self.target_factor_instance else "UnknownFactor"
        self.write_log(f"Final backtest on factor: {factor_key_for_log}. Period: {self.start_datetime_for_report} to {self.end_datetime_for_report}", INFO)

        factor_data_df = self.calculate_single_factor_data()
        if factor_data_df is None:
            self.write_log("Factor calculation for final run failed.", ERROR); return None # Critical error
        if factor_data_df.is_empty():
            self.write_log("Factor calculation for final run produced empty data.", WARNING)

        # Prepare returns using the datetime series from the final backtest data
        final_close_data = self.memory_bar.get("close")
        if final_close_data is None or final_close_data.is_empty() or self.factor_datetime_col not in final_close_data.columns:
            self.write_log("Close price data for final run is missing or invalid. Cannot prepare symbol returns.", ERROR)
            return None
        if not self.prepare_symbol_returns(reference_datetime_series=final_close_data[self.factor_datetime_col]):
            self.write_log("Preparing symbol returns for final run failed.", ERROR); return None # Critical error

        if not self.perform_quantile_analysis(factor_data_df, num_quantiles, returns_look_ahead_period):
            self.write_log("Quantile analysis for final run failed.", WARNING) 

        if not self.perform_long_short_analysis(factor_data_df, returns_look_ahead_period, long_percentile_threshold, short_percentile_threshold):
            self.write_log("Long-short portfolio analysis for final run failed.", WARNING) 

        if hasattr(self, 'long_short_portfolio_returns_df') and self.long_short_portfolio_returns_df is not None and not self.long_short_portfolio_returns_df.is_empty():
            if not self.calculate_performance_metrics():
                self.write_log("Performance metrics calculation for final run failed.", WARNING)
        else:
            self.write_log("Skipping performance metrics for final run: L-S portfolio returns unavailable.", INFO)

        report_dict = self.generate_single_factor_report()
        saved_report_path: Optional[Path] = None
        if report_dict:
            # Include optimization results in the report if they exist
            if hasattr(self, 'optimization_results') and self.optimization_results:
                report_dict["optimization_summary"] = self.optimization_results
                self.write_log("Added optimization summary to report.", DEBUG)

            saved_report_path = self.save_report(report_dict, report_filename_prefix)
            if saved_report_path: self.write_log(f"Report saved: {saved_report_path}", INFO)
            else: self.write_log("Failed to save report.", ERROR)
        else:
            self.write_log("Report generation failed.", ERROR)

        if output_dir_override: self.output_data_dir = original_output_dir
        self.write_log("Single factor backtest run completed.", INFO)
        return saved_report_path

    def optimize_factor_parameters(
        self,
        factor_class_name: str,
        initial_factor_settings: Dict[str, Any], 
        parameter_grid: Dict[str, List[Any]],    
        full_bar_data: Dict[str, pl.DataFrame], 
        n_splits_for_cv: int = 3
    ) -> Optional[Dict[str, Any]]:
        """
        Optimizes factor parameters using GridSearchCV with TimeSeriesSplit.
        """
        self.write_log(f"Starting factor parameter optimization for {factor_class_name}...", INFO)
        self.optimization_results = None # Clear previous results

        if not isinstance(full_bar_data, dict) or "close" not in full_bar_data or \
           not isinstance(full_bar_data["close"], pl.DataFrame) or full_bar_data["close"].is_empty():
            self.write_log("full_bar_data must be a dict with a non-empty 'close' Polars DataFrame.", ERROR)
            return None

        try:
            from vnpy.factor.optimizer import FactorBacktestEstimator # Dynamic import

            # Construct the initial_factor_definition_dict for the estimator
            # This dict should represent the complete structure of the factor,
            # including any nested dependencies, if the factor is complex.
            # For a simple factor without explicit dependencies in its definition,
            # it's just its own class_name and params.
            factor_def_for_estimator = {
                "class_name": factor_class_name,
                # "factor_name": factor_class_name, # Optional: if your FactorTemplate uses it
                "params": initial_factor_settings.copy(), # Use a copy of initial settings
                # "dependencies": [] # Add if your factor definition expects this key for dependencies
            }
            
            estimator = FactorBacktestEstimator(
                backtesting_engine=self,
                initial_factor_definition_dict=factor_def_for_estimator,
                full_bar_data_for_slicing=full_bar_data
            )
        except ImportError:
            self.write_log("Failed to import FactorBacktestEstimator. Ensure it's in vnpy.factor.optimizer.", ERROR)
            self.write_log(traceback.format_exc(), DEBUG) # Add traceback for import error
            return None
        except Exception as e_est:
            self.write_log(f"Error initializing FactorBacktestEstimator: {e_est}\n{traceback.format_exc()}", ERROR)
            return None

        time_series_splitter = TimeSeriesSplit(n_splits=n_splits_for_cv)
        
        grid_search = GridSearchCV(
            estimator=estimator,
            param_grid=parameter_grid,
            scoring=None,  # Uses FactorBacktestEstimator's score method
            cv=time_series_splitter,
            verbose=1,     # Adjust verbosity as needed
            n_jobs=1       # Crucial: Must be 1 due to shared BacktestEngine instance state
        )

        num_samples = full_bar_data["close"].height
        indices = np.arange(num_samples)

        self.write_log(f"Starting GridSearchCV with {n_splits_for_cv} time-series splits on {num_samples} samples.", INFO)
        try:
            # X for GridSearchCV's fit is just the indices array.
            # The estimator's fit will use these indices to slice self.full_bar_data_for_slicing.
            grid_search.fit(X=indices, y=None) 
        except Exception as e_grid:
            self.write_log(f"Error during GridSearchCV.fit: {e_grid}\n{traceback.format_exc()}", ERROR)
            return None

        self.write_log(f"GridSearchCV completed. Best score (Sharpe Ratio): {grid_search.best_score_:.4f}", INFO)
        self.write_log(f"Best parameters found: {grid_search.best_params_}", INFO)

        self.optimization_results = {
            "best_params": grid_search.best_params_,
            "best_score": grid_search.best_score_,
            "best_estimator": grid_search.best_estimator_, # Store the best estimator
            "cv_results_summary": { 
                "mean_test_score": grid_search.cv_results_["mean_test_score"].tolist(),
                "std_test_score": grid_search.cv_results_["std_test_score"].tolist(),
                "params": [str(p) for p in grid_search.cv_results_["params"]] 
            }
        }
        
        return grid_search.best_params_

