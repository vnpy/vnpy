import importlib
import gc
import time
import traceback
from datetime import datetime, timedelta
from logging import INFO, DEBUG, WARNING, ERROR
from typing import Callable, Any, Dict, Optional, List
from dataclasses import dataclass
from threading import Lock
from pathlib import Path
import re
import numpy as np
import polars as pl # Ensure polars is imported
import psutil
import dask
from dask.delayed import Delayed
import dask.diagnostics

from vnpy.factor.memory import FactorMemory
from vnpy.factor.template import FactorTemplate
from vnpy.event import EventEngine, Event
from vnpy.trader.event import EVENT_FACTOR, EVENT_TICK, EVENT_BAR
from vnpy.trader.engine import BaseEngine, MainEngine
from vnpy.trader.object import BarData
from vnpy.trader.setting import SETTINGS
from vnpy.factor.base import APP_NAME # Import FactorMode
# FactorTemplate and FactorMemory are assumed to be defined above or importable
from vnpy.factor.utils.factor_utils import init_factors, load_factor_setting, save_factor_setting # Ensure these utils are compatible
from vnpy.factor.utils.memory_utils import truncate_memory as truncate_bar_memory


FACTOR_MODULE_NAME = 'vnpy.factor.factors' # Default, can be overridden
SYSTEM_MODE = SETTINGS.get('system.mode', 'LIVE') # LIVE, BACKTEST, etc.
DEFAULT_DATETIME_COL = "datetime" # Standard datetime column name for FactorMemory

def safe_filename(name: str) -> str:
    name = re.sub(r'[^\w\.\-@]', '_', name)
    return name

@dataclass
class CalculationMetrics:
    calculation_time: float
    memory_usage: float # System memory usage delta
    cache_hits: int # For external caches if used, Dask handles its own
    error_count: int

class FactorEngine(BaseEngine):
    setting_filename: str = "/Users/chenzhao/Documents/crypto_vnpy/vnpy/vnpy/factor/factor_maker_setting.json"
    factor_data_cache_dirname: str = "factor_data_cache" # Directory for FactorMemory files

    def __init__(self, main_engine: MainEngine, event_engine: EventEngine) -> None:
        super().__init__(main_engine, event_engine, APP_NAME)

        try:
            self.module_factors = importlib.import_module(FACTOR_MODULE_NAME)
        except ImportError as e:
            self.write_log(f"Could not import factor module '{FACTOR_MODULE_NAME}': {e}. "
                           "Factor loading might fail if factors are not self-contained.", level=ERROR)
            self.module_factors = None # Allow engine to start, but factor loading may fail

        #self.database = get_database()
        self.vt_symbols: List[str] = getattr(main_engine, 'vt_symbols', []) # Get from main_engine or default to empty
        if not self.vt_symbols and hasattr(main_engine, 'get_all_contracts'):
            try:
                self.vt_symbols = [contract.vt_symbol for contract in main_engine.get_all_contracts()]
            except Exception as e:
                self.write_log(f"Failed to get vt_symbols from main_engine.get_all_contracts(): {e}", level=WARNING)


        self.stacked_factors: dict[str, FactorTemplate] = {}
        self.flattened_factors: dict[str, FactorTemplate] = {}

        self.memory_bar: Dict[str, pl.DataFrame] = {} # For OHLCV data
        
        # NEW: Manages FactorMemory instances
        self.factor_data_dir = Path(self.factor_data_cache_dirname)
        self.factor_memory_instances: Dict[str, FactorMemory] = {}
        self.latest_calculated_factors_cache: Dict[str, pl.DataFrame] = {}

        self.max_memory_length_bar = 100 # Max length for OHLCV bar memory
        self.max_memory_length_factor = 500 # Default max_rows for FactorMemory instances

        self.dt: Optional[datetime] = None
        self.bars: Dict[str, BarData] = {} # Current batch of bars
        self.tasks: Dict[str, Delayed] = {} # Dask tasks
        self.receiving_status: Dict[str, bool] = {sym: False for sym in self.vt_symbols} if self.vt_symbols else {}

        self.metrics: Dict[str, CalculationMetrics] = {}
        self.calculation_lock = Lock() # Ensures only one execute_calculation runs at a time
        # self.thread_pool = ThreadPoolExecutor(max_workers=4) # Dask manages its own threading/processing
        self.error_threshold = 3 # Consecutive errors to trigger circuit breaker
        self.consecutive_errors = 0
        
        self.factor_datetime_col = DEFAULT_DATETIME_COL # Datetime col for FactorMemory

    def init_engine(self, fake: bool = False) -> None:
        self.write_log("Initializing FactorEngine...", level=INFO)
        self.factor_data_dir.mkdir(parents=True, exist_ok=True)
        self.register_event()
        
        # 1. Load factor configurations and initialize FactorTemplate instances
        self.init_all_factors() # Populates self.stacked_factors, determines max_lookbacks

        # 2. Flatten the dependency tree
        self.flattened_factors = self.complete_factor_tree(self.stacked_factors)
        self.write_log(f"Flattened factors ({len(self.flattened_factors)}): {list(self.flattened_factors.keys())}", level=INFO)

        # 3. Initialize memory structures (memory_bar and FactorMemory instances)
        self.init_memory(fake=fake) 

        # 4. Build Dask computational graph
        if self.flattened_factors:
            self.tasks = self.build_computational_graph()
            self.write_log(f"Built Dask computational graph with {len(self.tasks)} tasks.", level=INFO)
        else:
            self.write_log("No factors loaded, computational graph not built.", level=WARNING)

        # 5. Call on_start for all factors
        for factor in self.flattened_factors.values():
            if factor.inited and not factor.trading: # Start if inited but not yet trading
                self.call_factor_func(factor, factor.on_start)

        self.write_log("FactorEngine initialized successfully.", level=INFO)

    def register_event(self) -> None:
        self.event_engine.register(EVENT_TICK, self.process_tick_event)
        self.event_engine.register(EVENT_BAR, self.process_bar_event)
        self.write_log("Registered for TICK and BAR events.", level=DEBUG)

    def init_all_factors(self) -> None:
        """Loads factor settings, initializes FactorTemplate instances, and determines max lookback periods."""
        self.write_log("Loading factor settings and initializing factor instances...", level=DEBUG)
        try:
            factor_settings_list = load_factor_setting(self.setting_filename) # Expects a list of settings dicts
            if not factor_settings_list:
                self.write_log("No factor settings found or file is empty.", level=WARNING)
                self.stacked_factors = {}
                return
        except FileNotFoundError:
            self.write_log(f"Factor settings file '{self.setting_filename}' not found. No factors loaded.", level=WARNING)
            self.stacked_factors = {}
            return
        except Exception as e:
            self.write_log(f"Error loading factor settings from '{self.setting_filename}': {e}", level=ERROR)
            self.stacked_factors = {}
            return

        # init_factors should take the list of settings and the factors module
        inited_factor_instances = init_factors(
            self.module_factors, # Module for finding primary factor classes
            factor_settings_list,
            dependencies_module_lookup_for_instances=self.module_factors # Module for their dependencies too
        )
        self.stacked_factors = {f.factor_key: f for f in inited_factor_instances}
        self.write_log(f"Loaded {len(self.stacked_factors)} stacked factors.", level=INFO)

        # Determine max lookback for bar data from factor parameters
        # And potentially a global default for FactorMemory max_rows if not specified per factor
        lookback_attrs = ["lookback_period", "window", "period", "fast_period",
                          "slow_period", "signal_period", "len", "length", "n", "k"] # Added more common param names
        
        all_bar_lookbacks = [self.max_memory_length_bar] # Start with default
        all_factor_mem_max_rows = [self.max_memory_length_factor]

        for factor in self.stacked_factors.values():
            factor_params = factor.get_params()
            for attr in lookback_attrs:
                val = factor_params.get(attr)
                if isinstance(val, int) and val > 0:
                    all_bar_lookbacks.append(val)
            # Allow overriding FactorMemory max_rows via a special param e.g., "factor_memory_max_rows"
            fm_max_rows = factor_params.get("factor_memory_max_rows")
            if isinstance(fm_max_rows, int) and fm_max_rows > 0:
                all_factor_mem_max_rows.append(fm_max_rows)


        self.max_memory_length_bar = max(all_bar_lookbacks) if all_bar_lookbacks else 100
        # self.max_memory_length_factor = max(all_factor_mem_max_rows) if all_factor_mem_max_rows else 500
        # Note: max_memory_length_factor will be used as default if a factor doesn't specify its own.
        # It's better to set FactorMemory max_rows per factor if needed, or use a generous global default.

        self.write_log(f"Max memory length for bar data (OHLCV): {self.max_memory_length_bar}", level=DEBUG)
        self.write_log(f"Default max memory length for individual factor history: {self.max_memory_length_factor}", level=DEBUG)


    def init_memory(self, fake: bool = False) -> None:
        """Initializes memory_bar (in-memory OHLCV) and FactorMemory instances for each factor."""
        self.write_log("Initializing memory structures...", level=DEBUG)
        # 1. Initialize memory_bar (OHLCV)
        # Use a consistent schema for bar data DataFrames
        bar_data_schema = {'datetime': pl.Datetime(time_unit="us")} # Datetime column
        if self.vt_symbols:
            for symbol in self.vt_symbols:
                bar_data_schema[symbol] = pl.Float64 # Price/volume data per symbol
        else: # No symbols, create a placeholder column to avoid empty schema issues if needed later
             bar_data_schema["placeholder_value"] = pl.Float64
        
        for b_col in ["open", "high", "low", "close", "volume"]:
            self.memory_bar[b_col] = pl.DataFrame(data={}, schema=bar_data_schema.copy())

        # 2. Initialize FactorMemory instances for each flattened factor
        self.factor_memory_instances.clear()
        for factor_key, factor_instance in self.flattened_factors.items():
            try:
                factor_instance.vt_symbols = self.vt_symbols # Pass symbols to factor instance
                output_schema = factor_instance.get_output_schema()
                if self.factor_datetime_col not in output_schema:
                    raise ValueError(f"Factor '{factor_key}' output schema must contain the datetime column '{self.factor_datetime_col}'.")

                # Allow factor to specify its own max_rows via params
                factor_specific_max_rows = factor_instance.get_param("factor_memory_max_rows")
                if not isinstance(factor_specific_max_rows, int) or factor_specific_max_rows <=0:
                    factor_specific_max_rows = self.max_memory_length_factor # Use engine default

                file_path = self.factor_data_dir.joinpath(f"{safe_filename(factor_key)}.arrow")
                
                self.factor_memory_instances[factor_key] = FactorMemory(
                    file_path=file_path,
                    max_rows=factor_specific_max_rows,
                    schema=output_schema,
                    datetime_col=self.factor_datetime_col
                )
                self.write_log(f"Initialized FactorMemory for {factor_key} at {file_path} with max_rows={factor_specific_max_rows}", level=DEBUG)
            except Exception as e:
                self.write_log(f"Failed to initialize FactorMemory for {factor_key}: {e}. This factor may not calculate correctly.", level=ERROR)

        # 3. Populate with fake data if requested
        if fake and self.vt_symbols:
            self.write_log("Populating with fake data...", level=DEBUG)
            fake_dates = pl.datetime_range(
                start=datetime.now() - timedelta(days=max(self.max_memory_length_bar, self.max_memory_length_factor) // (24*60) +1), # Enough days for minute data
                end=datetime.now(), 
                interval="1m", 
                time_unit="us",
                eager=True
            ).alias("datetime")
            
            num_fake_rows = len(fake_dates)
            if num_fake_rows == 0:
                self.write_log("Could not generate fake dates for fake data population.", level=WARNING)
                return

            # Fake data for memory_bar
            for b_col in ["open", "high", "low", "close", "volume"]:
                bar_fake_df_data = {"datetime": fake_dates}
                for symbol in self.vt_symbols:
                    bar_fake_df_data[symbol] = np.random.rand(num_fake_rows) * 100 + (50 if b_col !="volume" else 1000)
                
                # Ensure schema matches what self.memory_bar[b_col] expects
                current_bar_schema = self.memory_bar[b_col].schema
                fake_bar_df = pl.DataFrame(bar_fake_df_data).select(
                    [pl.col(c).cast(current_bar_schema[c]) for c in current_bar_schema.keys()]
                )
                self.memory_bar[b_col] = pl.concat(
                    [self.memory_bar[b_col], fake_bar_df.tail(self.max_memory_length_bar)], # Keep within bar memory limits
                    how='vertical_relaxed'
                )
            
            # Fake data for FactorMemory instances
            for factor_key, fm_instance in self.factor_memory_instances.items():
                factor_output_schema = fm_instance.schema
                factor_fake_df_data = {self.factor_datetime_col: fake_dates}
                for col_name, col_type in factor_output_schema.items():
                    if col_name == self.factor_datetime_col:
                        continue
                    if col_type.base_type() in [pl.Float32, pl.Float64]:
                        factor_fake_df_data[col_name] = np.random.rand(num_fake_rows) * 10
                    elif col_type.base_type() in [pl.Int8, pl.Int16, pl.Int32, pl.Int64]:
                        factor_fake_df_data[col_name] = np.random.randint(0, 5, size=num_fake_rows)
                    elif col_type.base_type() == pl.Boolean:
                         factor_fake_df_data[col_name] = np.random.choice([True, False], size=num_fake_rows)
                    else: # Fallback for Utf8 or other types
                        factor_fake_df_data[col_name] = [f"val_{i % 5}" for i in range(num_fake_rows)]
                
                fake_factor_df = pl.DataFrame(factor_fake_df_data, schema=factor_output_schema)
                fm_instance.update_data(fake_factor_df) # FactorMemory handles truncation internally
                # Update cache with the latest fake row
                if not fake_factor_df.is_empty():
                    self.latest_calculated_factors_cache[factor_key] = fm_instance.get_latest_rows(1)
        self.write_log("Memory initialization complete.", level=DEBUG)


    def complete_factor_tree(self, factors: Dict[str, FactorTemplate]) -> Dict[str, FactorTemplate]:
        """Recursively flattens the dependency tree for all factors."""
        resolved_factors: Dict[str, FactorTemplate] = {}
        
        def traverse_dependencies(factor: FactorTemplate, resolved: Dict[str, FactorTemplate]) -> None:
            if factor.factor_key in resolved:
                return
            
            # Resolve dependencies first
            for dependency_instance in factor.dependencies_factor:
                if isinstance(dependency_instance, FactorTemplate): # Ensure it's an instance
                    traverse_dependencies(dependency_instance, resolved)
                else:
                    self.write_log(f"Warning: Dependency {dependency_instance} for {factor.factor_key} is not a FactorTemplate instance. Skipping.", level=WARNING)

            # Add the current factor after its dependencies are resolved
            resolved[factor.factor_key] = factor

        for _, factor_instance in factors.items():
            traverse_dependencies(factor_instance, resolved_factors)
        
        return resolved_factors


    def build_computational_graph(self) -> Dict[str, Delayed]:
        """Builds a Dask computational graph based on flattened factors."""
        self.write_log("Building Dask computational graph...", level=DEBUG)
        tasks: Dict[str, Delayed] = {}
        
        # Dependency graph for topological sort: factor_key -> list of dependency_factor_keys
        dependency_graph: Dict[str, List[str]] = {}
        for factor_key, factor_instance in self.flattened_factors.items():
            dependency_graph[factor_key] = [
                dep.factor_key for dep in factor_instance.dependencies_factor if isinstance(dep, FactorTemplate)
            ]

        try:
            # Sort factors topologically to define creation order for Dask tasks
            # Order: dependencies first, then the factors that depend on them.
            sorted_factor_keys = self._topological_sort(dependency_graph)
        except ValueError as e: # Circular dependency
            self.write_log(f"Error building computational graph: {e}", level=ERROR)
            return {} # Return empty tasks if graph is invalid

        # Build tasks in dependency order
        for factor_key in sorted_factor_keys:
            if factor_key in self.flattened_factors: # Ensure factor still exists
                 self.create_task(factor_key, self.flattened_factors, tasks)
            else:
                self.write_log(f"Warning: Factor key {factor_key} from sort not in flattened_factors. Skipping task.", level=WARNING)
        
        return tasks

    def _topological_sort(self, graph: Dict[str, list]) -> list:
        """Performs topological sort. Args: graph (node -> list of dependencies)."""
        visited_permanently = set() # Nodes whose processing (including all descendants) is complete
        visited_temporarily = set() # Nodes currently in the recursion stack (for cycle detection)
        order = [] # The topologically sorted list of nodes

        def visit(node: str):
            if node in visited_permanently:
                return
            if node in visited_temporarily: # Cycle detected
                path = " -> ".join(list(visited_temporarily) + [node])
                raise ValueError(f"Circular dependency detected in factor graph: {path}")
            
            visited_temporarily.add(node)
            
            # Visit dependencies of the current node
            if node in graph: # Check if node is in graph (might be a leaf with no recorded deps)
                for dep_node in graph[node]:
                    visit(dep_node)
            
            visited_temporarily.remove(node) # Remove from recursion stack
            visited_permanently.add(node)  # Mark as fully processed
            order.append(node) # Add to the sorted list

        all_nodes = set(graph.keys())
        for dep_list in graph.values():
            all_nodes.update(dep_list)

        for node_key in all_nodes: # Iterate over all known nodes to ensure all are visited
            if node_key not in visited_permanently:
                visit(node_key)
        
        # The `order` list now has dependencies before the nodes that depend on them.
        # For Dask task creation, this is the correct order.
        return order


    def _get_current_memory_bar_dask_input(self) -> Dict[str, pl.DataFrame]:
        """Prepares OHLCV bar data for Dask task input. Returns copies."""
        # Dask works best with immutable inputs or copies to avoid side effects
        return {k: df.clone() for k, df in self.memory_bar.items() if not df.is_empty()}


    def _get_factor_memory_instance_for_dask(self, factor_key: str) -> FactorMemory:
        """Returns the FactorMemory instance for a factor.
           Dask should be able to handle passing this instance if its state (like _lock)
           is managed correctly or not used across workers.
        """
        if factor_key not in self.factor_memory_instances:
            # This should not happen if init_memory was successful for all flattened_factors
            raise RuntimeError(f"FactorMemory instance for {factor_key} not found. Engine not properly initialized.")
        return self.factor_memory_instances[factor_key]


    def create_task(self,
                    factor_key: str,
                    factors_dict: Dict[str, FactorTemplate], # All flattened factors
                    tasks_dict: Dict[str, Delayed] # Accumulator for created tasks
                    ) -> Delayed:
        """Recursively creates a Dask task for a given factor and its dependencies."""
        if factor_key in tasks_dict: # Task already created
            return tasks_dict[factor_key]

        factor_instance = factors_dict[factor_key]
        
        # Prepare Dask Delayed objects for dependencies
        dependency_input_tasks: Dict[str, Delayed] = {}
        for dep_factor_template in factor_instance.dependencies_factor:
            dep_key = dep_factor_template.factor_key
            # Recursively create/get task for each dependency
            dependency_input_tasks[dep_key] = self.create_task(dep_key, factors_dict, tasks_dict)
        
        # Get the FactorMemory instance for this factor
        # This instance will be passed to the factor.calculate method
        factor_memory_obj_delayed = dask.delayed(self._get_factor_memory_instance_for_dask)(factor_key)

        if not factor_instance.dependencies_factor: # Leaf factor (depends on bar data)
            # Input data is the current OHLCV bar memory
            bar_data_delayed_input = dask.delayed(self._get_current_memory_bar_dask_input)()
            
            task = dask.delayed(factor_instance.calculate)(
                input_data=bar_data_delayed_input, 
                memory=factor_memory_obj_delayed
            )
        else: # Factor with dependencies on other factors
            task = dask.delayed(factor_instance.calculate)(
                input_data=dependency_input_tasks, # Dict of Delayed objects (results of other factors)
                memory=factor_memory_obj_delayed
            )
        
        tasks_dict[factor_key] = task
        return task

    def on_bars(self, dt: datetime, bars: Dict[str, BarData]) -> None:
        """Processes a complete slice of bars for a given datetime."""
        if not bars:
            self.write_log(f"on_bars called with empty bars for dt: {dt}. Skipping.", level=DEBUG)
            return

        self.write_log(f"Processing bars for {dt} across {len(bars)} symbols.", level=DEBUG)

        # 1. Update memory_bar (OHLCV data)
        # Prepare a single row DataFrame for each OHLCV type
        new_ohlcv_rows: Dict[str, Dict[str, Any]] = {
            b_col: {self.factor_datetime_col: dt} 
            for b_col in ["open", "high", "low", "close", "volume"]
        }

        for vt_symbol, bar_data_obj in bars.items():
            if vt_symbol not in self.vt_symbols: # Dynamically add new symbols if encountered
                self.vt_symbols.append(vt_symbol)
                # Update schemas for memory_bar if a new symbol appears
                for b_col in self.memory_bar.keys():
                    if vt_symbol not in self.memory_bar[b_col].columns:
                         self.memory_bar[b_col] = self.memory_bar[b_col].with_columns(pl.lit(None, dtype=pl.Float64).alias(vt_symbol))

            new_ohlcv_rows["open"][vt_symbol] = bar_data_obj.open_price
            new_ohlcv_rows["high"][vt_symbol] = bar_data_obj.high_price
            new_ohlcv_rows["low"][vt_symbol] = bar_data_obj.low_price
            new_ohlcv_rows["close"][vt_symbol] = bar_data_obj.close_price
            new_ohlcv_rows["volume"][vt_symbol] = bar_data_obj.volume
        
        for b_col, data_dict_for_row in new_ohlcv_rows.items():
            try:
                # Ensure the schema for the new row matches the existing DataFrame schema
                expected_schema = self.memory_bar[b_col].schema
                # Create a 1-row DataFrame, conforming to the expected schema
                # Fill missing symbols (if any for this specific bar batch) with nulls
                row_df_data = {
                    col: data_dict_for_row.get(col, None if col != self.factor_datetime_col else dt) 
                    for col in expected_schema.keys()
                }
                new_row_df = pl.DataFrame([row_df_data], schema=expected_schema)
                
                self.memory_bar[b_col] = pl.concat(
                    [self.memory_bar[b_col], new_row_df], 
                    how='vertical_relaxed' # vertical_relaxed is more robust to minor schema diffs if they occur
                )
            except Exception as e:
                self.write_log(f"Error updating memory_bar for '{b_col}': {e}. Row data: {data_dict_for_row}", level=ERROR)
                # Potentially stop processing if bar memory update fails critically
                return

        # 2. Execute factor calculations using Dask
        if self.tasks:
            self.execute_calculation(dt=dt) # Results written to FactorMemory, cache updated
        else:
            self.write_log("No Dask tasks defined, skipping factor calculation.", level=DEBUG)

        # 3. Broadcast the FactorMemory instances directly
        if self.factor_memory_instances:
            # Broadcast FactorMemory instances directly
            event_data = self.factor_memory_instances
            self.event_engine.put(Event(EVENT_FACTOR, event_data))
        
        # 4. Maintain memory length for bar data (OHLCV)
        # FactorMemory instances handle their own truncation.
        self._truncate_memory_bar()
        
        self.write_log(f"Finished processing bars for {dt}.", level=DEBUG)


    def execute_calculation(self, dt: datetime) -> None:
        """Executes the Dask computational graph and updates FactorMemory instances."""
        if not self.tasks:
            self.write_log("No tasks to execute.", level=DEBUG)
            return

        self.write_log(f"Executing Dask computation for datetime {dt}...", level=INFO)
        
        # Ensure thread-safety for the entire calculation execution block if needed,
        # though Dask's local scheduler might handle this internally.
        # The self.calculation_lock here prevents multiple calls to execute_calculation from overlapping.
        with self.calculation_lock:
            start_time = time.time()
            initial_resources = self._monitor_resources()

            # Configure Dask for local threaded execution (default if no cluster)
            dask.config.set(scheduler='threads') 
            # dask.config.set(num_workers=psutil.cpu_count(logical=False)) # Optional: set num_workers

            try:
                with dask.diagnostics.ProgressBar(minimum=0.1), dask.diagnostics.ResourceProfiler(dt=0.25) as rprof:
                    # Compute all tasks. Results will be a list of DataFrames.
                    computed_results = dask.compute(*self.tasks.values(), optimize_graph=True)
                
                end_time = time.time()
                self.write_log(f"Dask computation finished in {end_time - start_time:.3f}s.", level=INFO)

                # Clear cache before populating with new results
                self.latest_calculated_factors_cache.clear() 
                
                calculation_errors_count = 0
                # Process results: update FactorMemory instances and the latest_factors_cache
                for factor_key, result_df in zip(self.tasks.keys(), computed_results):
                    if result_df is None:
                        self.write_log(f"Factor {factor_key} computation returned None.", level=WARNING)
                        calculation_errors_count +=1
                        continue
                    if not isinstance(result_df, pl.DataFrame):
                        self.write_log(f"Factor {factor_key} computation returned non-DataFrame: {type(result_df)}.", level=ERROR)
                        calculation_errors_count +=1
                        continue

                    fm_instance = self.factor_memory_instances.get(factor_key)
                    if fm_instance:
                        try:
                            # The result_df from factor.calculate IS the new full history.
                            # FactorMemory.update_data will merge, sort, unique, truncate, and save.
                            fm_instance.update_data(result_df)
                            
                            # Update the cache with the latest row from this factor
                            latest_row = fm_instance.get_latest_rows(1)
                            if not latest_row.is_empty():
                                self.latest_calculated_factors_cache[factor_key] = latest_row
                            # else: factor might have produced an empty result or history is empty
                        except Exception as e:
                            self.write_log(f"Error updating FactorMemory for {factor_key} with new data: {e}\n{traceback.format_exc()}", level=ERROR)
                            calculation_errors_count +=1
                    else:
                        self.write_log(f"No FactorMemory instance found for {factor_key} to update.", level=ERROR)
                        calculation_errors_count +=1
                
                final_resources = self._monitor_resources()
                # Update metrics (overall for the batch)
                # Per-factor metrics would require more granular timing within Dask tasks.
                self.metrics["overall_batch"] = CalculationMetrics(
                    calculation_time=end_time - start_time,
                    memory_usage=final_resources["memory_percent"] - initial_resources.get("memory_percent", final_resources["memory_percent"]),
                    cache_hits=0, # Dask handles its own caching/optimization
                    error_count=calculation_errors_count
                )

                if calculation_errors_count > 0:
                    self.consecutive_errors += 1
                else:
                    self.consecutive_errors = 0 # Reset on successful batch

                self.write_log(f"Factor calculations processed. Batch errors: {calculation_errors_count}", level=INFO)
                self.write_log(f"Resource usage - Memory: {final_resources['memory_percent']:.1f}%, CPU: {final_resources['cpu_percent']:.1f}%", level=DEBUG)

            except Exception as e_dask:
                self.consecutive_errors += 1
                self.write_log(f"Critical error during Dask computation or result processing: {e_dask}\n{traceback.format_exc()}", level=ERROR)
                # Circuit breaker logic
                if self.consecutive_errors >= self.error_threshold:
                    self.write_log(f"Consecutive error threshold ({self.error_threshold}) reached. Stopping all factors.", level=ERROR)
                    self.stop_all_factors()
                    # Potentially re-raise to halt the engine if critical
                    # raise RuntimeError(f"FactorEngine critical failure after {self.consecutive_errors} errors.") from e_dask
            finally:
                self._cleanup_memory_resources() # GC and other cleanup

    def _truncate_memory_bar(self) -> None:
        """Truncates the in-memory OHLCV bar data."""
        if not self.memory_bar:
            return
        # Assuming truncate_bar_memory is a utility that works on Dict[str, pl.DataFrame]
        truncate_bar_memory(self.memory_bar, self.max_memory_length_bar)

    def _monitor_resources(self) -> Dict[str, float]:
        process = psutil.Process()
        disk_io = psutil.disk_io_counters()
        mem_info = process.memory_info()
        return {
            "memory_rss_mb": mem_info.rss / (1024 * 1024),
            "memory_vms_mb": mem_info.vms / (1024 * 1024),
            "memory_percent": process.memory_percent(),
            "cpu_percent": process.cpu_percent(interval=0.05), # Non-blocking
            "disk_io_read_mb": disk_io.read_bytes / (1024*1024) if disk_io else 0,
            "disk_io_write_mb": disk_io.write_bytes / (1024*1024) if disk_io else 0,
        }

    def _cleanup_memory_resources(self) -> None:
        """Performs garbage collection."""
        gc.collect()
        # self.write_log("Garbage collection performed.", level=DEBUG)


    def process_tick_event(self, event: Event) -> None:
        # FactorMaker typically works on bars, not ticks.
        # Implement if specific tick-based logic is needed.
        pass

    def process_bar_event(self, event: Event) -> None:
        """Processes an incoming bar, batches them by datetime, then calls on_bars."""
        bar: BarData = event.data
        
        # If vt_symbols list was initially empty, populate it as we see symbols
        if not self.vt_symbols and hasattr(self.main_engine, 'get_all_contracts'):
             self.vt_symbols = [c.vt_symbol for c in self.main_engine.get_all_contracts()]
             self.receiving_status = {sym: False for sym in self.vt_symbols} # Re-init status

        if bar.vt_symbol not in self.receiving_status: # New symbol encountered
            self.write_log(f"New symbol {bar.vt_symbol} encountered from BAR event. Adding to tracking.", level=INFO)
            self.vt_symbols.append(bar.vt_symbol)
            self.receiving_status[bar.vt_symbol] = False
            # Might need to adjust schemas of self.memory_bar here if not handled in on_bars
            for b_col_key in self.memory_bar.keys():
                 if bar.vt_symbol not in self.memory_bar[b_col_key].columns:
                      self.memory_bar[b_col_key] = self.memory_bar[b_col_key].with_columns(
                          pl.lit(None, dtype=pl.Float64).alias(bar.vt_symbol)
                      )


        if self.dt is None: # First bar of a new batch
            self.dt = bar.datetime
        
        # If bar is from a new datetime, process the previous batch
        if bar.datetime > self.dt:
            if any(self.receiving_status.values()): # If any bars were received for self.dt
                self.write_log(f"New bar datetime {bar.datetime} received. Processing previous batch for {self.dt}.", level=DEBUG)
                # Some symbols might not have sent a bar for self.dt.
                # on_bars needs to handle potentially incomplete self.bars for self.dt
                # by using placeholders or only processing available data.
                # For simplicity, we assume on_bars will use what's in self.bars.
                # If strict all-symbol-bar-receipt is needed, logic here would be more complex.
                self.on_bars(self.dt, self.bars.copy()) # Process completed (or partially completed) previous batch
            
            # Reset for the new batch
            self.dt = bar.datetime
            self.bars.clear()
            self.receiving_status = {sym: False for sym in self.vt_symbols} # Reset receiving status

        self.bars[bar.vt_symbol] = bar
        self.receiving_status[bar.vt_symbol] = True

        # Check if all *expected* symbols for the current self.dt have arrived
        # This assumes self.vt_symbols is the list of all symbols we expect bars from.
        if all(self.receiving_status[sym] for sym in self.vt_symbols if sym in self.receiving_status):
            self.write_log(f"All expected bars received for {self.dt}. Processing batch.", level=DEBUG)
            self.on_bars(self.dt, self.bars.copy())
            
            # Reset for the next interval after processing
            self.dt = None 
            self.bars.clear()
            self.receiving_status = {sym: False for sym in self.vt_symbols}


    def stop_all_factors(self) -> None:
        self.write_log("Stopping all factors...", level=INFO)
        for factor in self.flattened_factors.values(): # Stop all, including dependencies
            if factor.trading:
                self.call_factor_func(factor, factor.on_stop)
        self.write_log(f"{len(self.flattened_factors)} factors stopped.", level=INFO)


    def close(self) -> None:
        self.write_log("Closing FactorEngine...", level=INFO)
        self.stop_all_factors()

        # Get a list of settings dictionaries from each "stacked" factor instance
        settings_to_save = [f.to_setting() for f in self.stacked_factors.values()] # CHANGED

        try:
            # save_factor_setting utility should be able to handle a list of dicts
            save_factor_setting(settings_to_save, self.setting_filename)
            self.write_log(f"Factor settings saved to {self.setting_filename}", level=INFO)
        except Exception as e:
            self.write_log(f"Error saving factor settings: {e}", level=ERROR)

        self.factor_memory_instances.clear()
        self.write_log("FactorEngine closed.", level=INFO)


    def call_factor_func(self, factor: FactorTemplate, func: Callable, params: object = None) -> None:
        try:
            if params:
                func(params)
            else:
                func()
        except Exception:
            # factor.trading = False # on_stop might already do this
            # factor.inited = False # Don't reset inited on every error in a func call
            msg: str = f"Exception in '{func.__name__}' for factor {factor.factor_key}:\n{traceback.format_exc()}"
            self.write_log(msg, factor=factor, level=ERROR) # Pass factor object

    def write_log(self, msg: str, factor: Optional[FactorTemplate] = None, level: int = INFO) -> None:
        log_msg = f"[{APP_NAME}] {factor.factor_key}: {msg}" if factor else f"[{APP_NAME}] {msg}"
        self.main_engine.write_log(msg=log_msg, level=level) # Removed source, APP_NAME is in msg

    # Other utility functions like get_factor_parameters, stop_factor, etc. can be adapted
    # from the original FactorEngine if still needed.
    # For example:
    def get_factor_parameters(self, factor_key: str) -> dict:
        factor = self.flattened_factors.get(factor_key)
        if not factor:
            self.write_log(f"Factor {factor_key} not found in flattened factors.", level=ERROR)
            return {}
        return factor.get_params()

    def get_factor_instance(self, factor_key: str) -> Optional[FactorTemplate]:
        return self.flattened_factors.get(factor_key)

    def get_factor_memory_instance(self, factor_key: str) -> Optional[FactorMemory]:
        return self.factor_memory_instances.get(factor_key)

