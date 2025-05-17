from dataclasses import dataclass
import importlib
import gc
import shutil
import time
import traceback
from datetime import datetime
from logging import INFO, DEBUG, WARNING, ERROR
from loguru import logger  # Add this import at the top with other imports
from typing import Any, Dict, Optional, List
from threading import Lock
from pathlib import Path
import re
import polars as pl # Ensure polars is imported
import psutil
import dask
from dask.delayed import Delayed
import dask.diagnostics

from vnpy.factor.memory import FactorMemory
from vnpy.factor.template import FactorTemplate
from vnpy.trader.constant import Interval
from vnpy.trader.setting import SETTINGS
from vnpy.factor.base import APP_NAME, FactorMode # Import FactorMode
# FactorTemplate and FactorMemory are assumed to be defined above or importable
from vnpy.factor.utils.factor_utils import init_factors, load_factor_setting # Ensure these utils are compatible


FACTOR_MODULE_NAME = 'vnpy.factor.factors' # Default, can be overridden
SYSTEM_MODE = SETTINGS.get('system.mode', 'BACKTEST') # LIVE, BACKTEST, etc.
DEFAULT_DATETIME_COL = "datetime" # Standard datetime column name for FactorMemory


DEFAULT_FACTOR_MODULE_NAME = SETTINGS.get('factor.module_name', 'vnpy.factor.factors')
DEFAULT_DATETIME_COL = "datetime"

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
        factor_settings_path: str,
        factor_module_name: str = DEFAULT_FACTOR_MODULE_NAME,
        output_data_dir: str = "backtest_factor_data_cache"
    ) -> None:
        self.factor_settings_path = Path(factor_settings_path)
        self.factor_module_name = factor_module_name
        self.output_data_dir = Path(output_data_dir)

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
        self.write_log("Loading factor settings and initializing factor instances for batch backtest...", level=DEBUG)
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
            self.write_log(f"Flattened and sorted {len(self.flattened_factors)} factors: {self.sorted_factor_keys}")
            return True
        except ValueError as e: # Circular dependency
            self.write_log(f"Circular dependency in factor graph: {e}", level=ERROR); return False


    def _initialize_factor_memory(self) -> bool:
        """Initializes FactorMemory instances for each factor."""
        self.write_log("Initializing FactorMemory instances for batch backtest...", level=DEBUG)
        if self.num_data_rows <= 0:
            self.write_log("Number of data rows is 0. FactorMemory max_rows will be 1. "
                           "Ensure data was loaded correctly if this is unexpected.", level=WARNING)
        
        # For batch, max_rows is the total number of data points to store full history
        max_rows_for_memory = self.num_data_rows if self.num_data_rows > 0 else 1 # FactorMemory requires max_rows > 0

        self.factor_memory_instances.clear()
        for factor_key in self.sorted_factor_keys: # Use sorted keys
            factor_instance = self.flattened_factors[factor_key]
            try:
                # Ensure vt_symbols is set on the instance if its get_output_schema depends on it.
                # This is already handled if 'vt_symbols' was in params and FactorTemplate sets it.
                # Or, if the factor's __init__ (like EMAFactor) explicitly takes and stores it.
                # If FactorTemplate does not store vt_symbols from params, set it explicitly:
                if not hasattr(factor_instance, 'vt_symbols') or not factor_instance.vt_symbols:
                     if hasattr(factor_instance, 'params') and factor_instance.params.get_parameter('vt_symbols'):
                         factor_instance.vt_symbols = factor_instance.params.get_parameter('vt_symbols')
                     else: # Fallback if not in params, use engine's list
                         factor_instance.vt_symbols = self.vt_symbols


                output_schema = factor_instance.get_output_schema()
                if self.factor_datetime_col not in output_schema:
                    raise ValueError(f"Factor '{factor_key}' schema missing datetime col '{self.factor_datetime_col}'.")

                # Allow factor-specific override for max_rows, though for batch it's usually full length
                # For batch, we primarily use num_data_rows
                # factor_specific_max_rows = factor_instance.get_param("factor_memory_max_rows")
                # current_max_rows = int(factor_specific_max_rows) if factor_specific_max_rows else max_rows_for_memory
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
        self.write_log("Building Dask computational graph for batch calculation...", level=DEBUG)
        
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
                for factor_key, result_df in zip(self.dask_tasks.keys(), computed_results):
                    if result_df is None:
                        self.write_log(f"Factor {factor_key} computation returned None.", level=WARNING)
                        error_count +=1; continue
                    if not isinstance(result_df, pl.DataFrame):
                        self.write_log(f"Factor {factor_key} returned non-DataFrame: {type(result_df)}.", level=ERROR)
                        error_count +=1; continue

                    fm_instance = self.factor_memory_instances.get(factor_key)
                    if fm_instance:
                        try:
                            fm_instance.update_data(result_df) # result_df is the new full history
                        except Exception as e_mem:
                            self.write_log(f"Error updating FactorMemory for {factor_key}: {e_mem}\n{traceback.format_exc()}", level=ERROR)
                            error_count +=1
                    else:
                        self.write_log(f"No FactorMemory for {factor_key} to update. Critical error.", level=ERROR)
                        error_count +=1 # This indicates a setup problem
                
                # final_resources = self._monitor_resources() # Optional
                # self.metrics["full_batch"] = CalculationMetrics(
                #     calculation_time=calc_time,
                #     memory_usage=final_resources.get("memory_percent", 0) - initial_resources.get("memory_percent", 0),
                #     cache_hits=0, # Dask internal
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
        self.write_log(f"Starting full factor backtest from {start_datetime} to {end_datetime} for symbols: {self.vt_symbols}")
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
        all_nodes = set(graph.keys()) | set(dep for deps_list in graph.values() for dep in deps_list)
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
        gc.collect(); self.write_log("Garbage collection performed.", level=DEBUG)

    def write_log(self, msg: str, level: int = INFO) -> None: # Kept from your original
        log_msg = f"[{self.engine_name}] {msg}" # Simplified prefix
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

