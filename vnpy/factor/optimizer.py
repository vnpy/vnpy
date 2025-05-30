# File: vnpy/factor/optimizer.py

from __future__ import annotations # For forward reference of BacktestEngine if needed

import numpy as np
from sklearn.base import BaseEstimator
from typing import Dict, Any, Optional, TYPE_CHECKING, List

if TYPE_CHECKING:
    from vnpy.factor.backtesting.backtesting import BacktestEngine
    # FactorTemplate will be imported directly now

from vnpy.factor.template import FactorTemplate # Direct import
from logging import INFO, DEBUG, WARNING, ERROR 
import polars as pl
import copy # For deepcopy
import traceback # For error logging


class FactorBacktestEstimator(BaseEstimator):
    """
    A scikit-learn compatible custom estimator for factor parameter optimization
    using GridSearchCV within the VnPy factor backtesting engine.
    """

    def __init__(
        self,
        backtesting_engine: BacktestEngine, # Type hint, actual instance passed
        initial_factor_definition_dict: Dict[str, Any],
        full_bar_data_for_slicing: Dict[str, pl.DataFrame],
        # vt_symbols_for_factor: List[str] # This will be derived from full_bar_data_for_slicing
    ):
        """
        Initializes the FactorBacktestEstimator.
        Performs a one-time full initialization of the factor tree.

        Args:
            backtesting_engine: An instance of the VnPy BacktestEngine.
            initial_factor_definition_dict: The full definition dictionary for the
                                              root factor, including any nested dependencies.
            full_bar_data_for_slicing: The complete bar data (dict of DataFrames like 
                                         {"close": df}) that will be sliced for each fold 
                                         during optimization by the fit method.
        """
        self.backtesting_engine: BacktestEngine = backtesting_engine
        # Store a deep copy of the initial definition for reference and to prevent modification
        self.initial_factor_definition_dict: Dict[str, Any] = copy.deepcopy(initial_factor_definition_dict)
        self.full_bar_data_for_slicing: Dict[str, pl.DataFrame] = full_bar_data_for_slicing # Store direct reference
        
        self.root_factor_for_optimization: Optional[FactorTemplate] = None
        self.current_score: float = -np.inf

        # Determine vt_symbols for the initial factor setup from full_bar_data_for_slicing['close']
        dt_col = self.backtesting_engine.factor_datetime_col
        vt_symbols_for_setup: List[str] = []

        close_data = self.full_bar_data_for_slicing.get("close")
        if isinstance(close_data, pl.DataFrame) and not close_data.is_empty() and dt_col in close_data.columns:
            vt_symbols_for_setup = [col for col in close_data.columns if col != dt_col]
        
        if not vt_symbols_for_setup:
            msg = "Optimizer.__init__: vt_symbols_for_setup could not be determined from full_bar_data_for_slicing['close']. Cannot initialize factor tree."
            self.backtesting_engine.write_log(msg, ERROR)
            raise ValueError(msg)

        # Use another deep copy for the actual initialization call, as init_single_factor might modify it.
        definition_for_init = copy.deepcopy(self.initial_factor_definition_dict)

        self.backtesting_engine.write_log(f"Optimizer.__init__: Initializing factor tree for '{definition_for_init.get('factor_name', definition_for_init.get('class_name'))}' with {len(vt_symbols_for_setup)} symbols.", DEBUG)

        if self.backtesting_engine.init_single_factor(
            factor_definition=definition_for_init,
            vt_symbols_for_factor=vt_symbols_for_setup
        ):
            if self.backtesting_engine.target_factor_instance:
                self.root_factor_for_optimization = self.backtesting_engine.target_factor_instance
                self.backtesting_engine.write_log(f"Optimizer.__init__: Root factor '{self.root_factor_for_optimization.factor_key}' and its tree initialized and stored.", DEBUG)
            else:
                msg = "Optimizer.__init__: Engine.init_single_factor succeeded but target_factor_instance is None."
                self.backtesting_engine.write_log(msg, ERROR)
                raise RuntimeError(msg)
        else:
            msg = "Optimizer.__init__: Engine.init_single_factor failed to initialize the factor tree."
            self.backtesting_engine.write_log(msg, ERROR)
            raise RuntimeError(msg)
        
        # Note: Previous attributes like self.factor_class_name and self._factor_param_names
        # are removed as parameter handling will be managed by custom get_params/set_params
        # interacting with the self.root_factor_for_optimization tree.

    def get_params(self, deep: bool = True) -> Dict[str, Any]:
        """
        Gets parameters for this estimator, including those from the nested factor tree.
        """
        # Start with parameters from __init__ (as per BaseEstimator convention)
        params = {
            "backtesting_engine": self.backtesting_engine, # Not typically tuned
            "initial_factor_definition_dict": self.initial_factor_definition_dict, # Not typically tuned
            "full_bar_data_for_slicing": self.full_bar_data_for_slicing # Not typically tuned
        }
        if hasattr(self, 'root_factor_for_optimization') and self.root_factor_for_optimization:
            # Call the new method on FactorTemplate to get all tunable params from the tree
            # These are the parameters GridSearchCV will be interested in.
            factor_tree_params = self.root_factor_for_optimization.get_nested_params_for_optimizer()
            params.update(factor_tree_params)
        return params

    def set_params(self, **params_from_grid: Any) -> FactorBacktestEstimator:
        """
        Sets parameters for this estimator. Parameters for the factor tree are
        delegated to the root factor's set_nested_params_for_optimizer method.
        """
        estimator_init_params = ["backtesting_engine", "initial_factor_definition_dict", "full_bar_data_for_slicing"]
        factor_params_to_set_on_tree = {}

        for key, value in params_from_grid.items():
            if key in estimator_init_params:
                # These are __init__ params of the estimator itself.
                # While GridSearchCV usually doesn't change these post-init, handle if it does.
                setattr(self, key, value) 
            else:
                # Assume other parameters are for the factor tree
                factor_params_to_set_on_tree[key] = value
        
        if hasattr(self, 'root_factor_for_optimization') and self.root_factor_for_optimization:
            if factor_params_to_set_on_tree:
                self.root_factor_for_optimization.set_nested_params_for_optimizer(factor_params_to_set_on_tree)
        elif factor_params_to_set_on_tree:
            # This case should ideally not happen if __init__ succeeded
            msg = "set_params: root_factor_for_optimization not set, but received factor parameters."
            if hasattr(self, 'backtesting_engine') and self.backtesting_engine:
                 self.backtesting_engine.write_log(msg, WARNING) # WARNING from logging
            # else: print(msg) # Or raise error

        return self

    def fit(self, X_indices_for_fold: np.ndarray, y: Any = None) -> FactorBacktestEstimator:
        self.current_score = -np.inf
        
        # Logging for the current parameters being tested by GridSearchCV can be helpful.
        # current_params_for_log = self.get_params(deep=True) 
        # self.backtesting_engine.write_log(f"Estimator.fit: Testing with params: { {k:v for k,v in current_params_for_log.items() if k not in ['backtesting_engine', 'initial_factor_definition_dict', 'full_bar_data_for_slicing']} }", DEBUG)

        # Helper to slice the dict of DataFrames
        def slice_bar_data_dict(bar_data_dict: Dict[str, pl.DataFrame], slice_indices: np.ndarray) -> Dict[str, pl.DataFrame]:
            sliced_dict = {}
            if not bar_data_dict or not isinstance(slice_indices, np.ndarray) or slice_indices.size == 0:
                self.backtesting_engine.write_log("slice_bar_data_dict: Invalid input or empty indices.", WARNING)
                return sliced_dict 
            for key, df in bar_data_dict.items():
                if isinstance(df, pl.DataFrame) and not df.is_empty():
                    # Ensure indices are within bounds before attempting to slice
                    if slice_indices.max() < df.height and slice_indices.min() >= 0:
                        # Polars slice: offset, length. slice_indices must be contiguous for this simple usage.
                        # If X_indices_for_fold from TimeSeriesSplit are not guaranteed contiguous,
                        # df.filter(pl.arange(0, pl.count()).is_in(slice_indices)) or df[slice_indices] (if polars supports numpy array directly for row selection)
                        # For now, assuming TimeSeriesSplit gives groups that can be sliced if we take min/max,
                        # or more robustly, use the direct indices if Polars supports it.
                        # Polars df[slice_indices] works if slice_indices is a Pl.Series of Int/Bool, or list/numpy array of Int/Bool.
                        sliced_dict[key] = df[slice_indices] 
                    else:
                        self.backtesting_engine.write_log(f"slice_bar_data_dict: Indices {slice_indices[:5]}... (min/max: {slice_indices.min()}/{slice_indices.max()}) out of bounds for DF height {df.height} on key {key}.", WARNING)
                        return {} 
                else:
                    sliced_dict[key] = df 
            return sliced_dict

        current_data_slice_dict = slice_bar_data_dict(self.full_bar_data_for_slicing, X_indices_for_fold)

        if not current_data_slice_dict or "close" not in current_data_slice_dict or current_data_slice_dict["close"].is_empty():
            self.backtesting_engine.write_log("Estimator.fit: Data slice is invalid or 'close' data is missing/empty after slicing.", ERROR)
            return self

        dt_col_name = self.backtesting_engine.factor_datetime_col
        if dt_col_name not in current_data_slice_dict["close"].columns:
            self.backtesting_engine.write_log(f"Estimator.fit: Datetime col '{dt_col_name}' not in sliced X['close'].", ERROR)
            return self
            
        current_vt_symbols = [col for col in current_data_slice_dict["close"].columns if col != dt_col_name]
        if not current_vt_symbols:
            self.backtesting_engine.write_log("Estimator.fit: No symbol columns in sliced X['close'].", ERROR)
            return self

        # --- This is the NEW core logic for setting up the engine with the live factor tree ---
        if not self.root_factor_for_optimization:
            self.backtesting_engine.write_log("Estimator.fit: root_factor_for_optimization is not set.", ERROR)
            return self 

        # Configure engine with the current data slice (memory_bar, num_data_rows)
        self.backtesting_engine.memory_bar = {k: v.clone() for k, v in current_data_slice_dict.items() if isinstance(v, pl.DataFrame)}
        self.backtesting_engine.num_data_rows = current_data_slice_dict["close"].height
        self.backtesting_engine.vt_symbols = current_vt_symbols # Update engine's active symbols

        # Set the parametrically updated root factor as the engine's target
        self.backtesting_engine.target_factor_instance = self.root_factor_for_optimization
        
        # Clear and rebuild engine's factor collections for this specific factor state
        self.backtesting_engine.stacked_factors.clear()
        self.backtesting_engine.flattened_factors.clear()
        self.backtesting_engine.sorted_factor_keys.clear()
        self.backtesting_engine.dask_tasks.clear()      
        self.backtesting_engine.factor_memory_instances.clear() 

        self.backtesting_engine.stacked_factors = {
            self.root_factor_for_optimization.factor_key: self.root_factor_for_optimization
        }
        try:
            self.backtesting_engine.flattened_factors = self.backtesting_engine._complete_factor_tree(
                self.backtesting_engine.stacked_factors
            )
            
            dependency_graph = {
                fk: [dep.factor_key for dep in fi.dependencies_factor if isinstance(dep, FactorTemplate)]
                for fk, fi in self.backtesting_engine.flattened_factors.items()
            }
            self.backtesting_engine.sorted_factor_keys = self.backtesting_engine._topological_sort(dependency_graph)

            if not self.backtesting_engine.sorted_factor_keys or \
               self.root_factor_for_optimization.factor_key not in self.backtesting_engine.sorted_factor_keys:
                 self.backtesting_engine.write_log(f"Estimator.fit: Root factor '{self.root_factor_for_optimization.factor_key}' not in sorted_keys after graph rebuild. Keys: {self.backtesting_engine.sorted_factor_keys}", ERROR)
                 # raise RuntimeError("Root factor not in sorted_keys after graph rebuild.") # Optional: make it stricter
                 return self 
        except Exception as e:
            self.backtesting_engine.write_log(f"Estimator.fit: Error rebuilding factor graph: {e}\n{traceback.format_exc()}", ERROR)
            return self
        # --- End of NEW core logic ---
        
        # --- Existing pipeline calls (calculate_single_factor_data, etc.) ---
        # These will now use the engine state prepared above.
        factor_data_df = self.backtesting_engine.calculate_single_factor_data()
        if factor_data_df is None or factor_data_df.is_empty():
            self.backtesting_engine.write_log("Estimator.fit: Factor calculation failed or produced empty data (post graph rebuild).", WARNING); return self
        
        if not self.backtesting_engine.prepare_symbol_returns(reference_datetime_series=current_data_slice_dict["close"][self.backtesting_engine.factor_datetime_col]):
            self.backtesting_engine.write_log("Estimator.fit: Preparing symbol returns failed (post graph rebuild).", WARNING); return self
        
        if not self.backtesting_engine.perform_long_short_analysis(factor_data_df): 
            self.backtesting_engine.write_log("Estimator.fit: L-S analysis failed (post graph rebuild).", WARNING); return self
        
        if hasattr(self.backtesting_engine, 'long_short_portfolio_returns_df') and \
           self.backtesting_engine.long_short_portfolio_returns_df is not None and \
           not self.backtesting_engine.long_short_portfolio_returns_df.is_empty():
            if not self.backtesting_engine.calculate_performance_metrics():
                self.backtesting_engine.write_log("Estimator.fit: Metrics calculation failed (post graph rebuild).", WARNING); return self
        else:
            self.backtesting_engine.write_log("Estimator.fit: L-S returns unavailable, skipping metrics (post graph rebuild).", INFO); return self

        if hasattr(self.backtesting_engine, 'performance_metrics') and self.backtesting_engine.performance_metrics:
            sharpe_ratio = self.backtesting_engine.performance_metrics.get('sharpe')
            if sharpe_ratio is not None and np.isfinite(sharpe_ratio):
                self.current_score = sharpe_ratio
                self.backtesting_engine.write_log(f"Estimator.fit successful. Sharpe: {self.current_score:.4f}", DEBUG) # Restored original log
            else:
                self.current_score = -np.inf
                self.backtesting_engine.write_log(f"Estimator.fit: Sharpe is None or non-finite ({sharpe_ratio}). Score set to -inf.", DEBUG) # Restored original log
        else:
            self.current_score = -np.inf
            self.backtesting_engine.write_log("Estimator.fit: No performance metrics. Score set to -inf.", DEBUG) # Restored original log

        return self

    def score(self, X: Any, y: Any = None) -> float:
        """
        Returns the score (e.g., Sharpe Ratio) calculated by the last `fit` call.
        This method will be called by GridSearchCV after `fit`.

        Args:
            X: Data slice (not directly used here as score is based on last fit).
            y: Target variable (not used).
            
        Returns:
            The calculated score (e.g., Sharpe Ratio).
        """
        return self.current_score
