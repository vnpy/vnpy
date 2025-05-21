from vnpy.strategy.template import StrategyTemplate
from vnpy.trader.object import OrderRequest, Exchange, Direction, OrderType
from vnpy.trader.utility import get_file_path
from typing import Dict, Any, List, Optional, Set
import pandas as pd
import joblib
import os
from pathlib import Path
from sklearn.linear_model import LinearRegression
from logging import INFO, WARNING, ERROR, DEBUG # For log levels

class TestStrategyTemplate(StrategyTemplate):
    author: str = "VNPY Example"
    strategy_name = 'test_model_strategy' # Renamed for clarity

    parameters: List[str] = [
        "vt_symbols", "required_factors", "model_config", "trading_config",
        "retrain_interval_days", "rsi_window"  # Example model param
    ]
    variables: List[str] = StrategyTemplate.variables + ["rsi_window"] # Add new variables to parent's list

    def __init__(self, strategy_engine, strategy_name, vt_symbols, setting):
        super().__init__(strategy_engine, strategy_name, vt_symbols, setting)

        # --- Custom Parameters & State ---
        self.rsi_window: int = setting.get("rsi_window", 14)  # Example model parameter
        
        # Override or set required_factors; ensure it's a list of strings
        rf_setting = setting.get("required_factors", ["RSI_FACTOR"])
        if isinstance(rf_setting, list) and all(isinstance(elem, str) for elem in rf_setting):
            self.required_factors: List[str] = rf_setting
        else:
            self.write_log("Invalid 'required_factors' in settings, using default ['RSI_FACTOR'].", level=WARNING)
            self.required_factors: List[str] = ["RSI_FACTOR"]

        # --- Model Persistence ---
        # Define a directory for strategy-specific models
        models_base_dir = get_file_path("strategy_models") # get_file_path handles creation if not exists
        models_base_dir.mkdir(parents=True, exist_ok=True)
        self.model_file_path: Path = models_base_dir.joinpath(f"{self.strategy_name}_model.joblib")
        
        self.write_log(f"TestStrategy initialized. Required factors: {self.required_factors}, RSI Window: {self.rsi_window}", level=INFO)
        self.write_log(f"Model will be saved/loaded from: {self.model_file_path}", level=DEBUG)


    def on_init(self) -> None:
        """Callback when strategy is initializing."""
        super().on_init() # Calls parent's on_init

        # Load pre-trained model if it exists
        if self.model_file_path.exists():
            try:
                self.model = joblib.load(self.model_file_path)
                self.write_log(f"Model loaded successfully from {self.model_file_path}", level=INFO)
                # If model stores last retrain time, you might load it here.
                # For this example, we assume last_retrain_time is handled by StrategyTemplate's load_data
            except Exception as e:
                self.write_log(f"Error loading model from {self.model_file_path}: {e}. Model will need retraining.", level=ERROR)
                self.model = None # Ensure model is None if loading failed
        else:
            self.write_log(f"No pre-trained model file found at {self.model_file_path}. Model needs training.", level=INFO)
        
        # If model is None after attempting to load, it means it needs initial training.
        # However, actual training with historical data is better handled by the engine's scheduled call
        # or a manual trigger, rather than blocking on_init.
        # The check_retraining_schedule will trigger first training if model is None.
        
        self.put_event() # Notify UI of state change after custom init

    # calculate method is inherited (virtual, pass) - no need to override if using predict_from_model

    def train_model(self, data: pd.DataFrame) -> None:
        """
        Train the strategy's underlying model.
        'data' is a DataFrame with MultiIndex (datetime, vt_symbol) and factor columns.
        """
        self.write_log(f"train_model called. Data shape: {data.shape}", level=DEBUG)
        if data.empty:
            self.write_log("Training data is empty. Skipping training.", level=WARNING)
            return

        # Ensure required factor is present
        # Example: Using "RSI_FACTOR" as specified in self.required_factors
        # This example assumes "RSI_FACTOR" is one of the columns in the input 'data' DataFrame
        # The 'data' DataFrame from StrategyEngine already has factors as columns.
        
        current_factor_for_training = ""
        if self.required_factors:
            current_factor_for_training = self.required_factors[0] # Using the first required factor for simplicity
        else:
            self.write_log("No required_factors defined for training. Skipping.", level=ERROR)
            return

        if current_factor_for_training not in data.columns:
            self.write_log(f"Factor '{current_factor_for_training}' not found in training data columns: {data.columns}. Skipping training.", level=WARNING)
            return
        
        # Prepare data for scikit-learn
        # X should be the factor values, y is the target.
        # For this example, we'll create a dummy target: y = factor_value * 0.1 (e.g. predicting a scaled version of the factor itself)
        
        # Drop rows where the specific factor or target might be NaN after alignment
        # The data from engine's _train_strategy_model_thread is already joined.
        # We need to handle NaNs that might exist for our specific factor or engineered target.
        df_train = data[[current_factor_for_training]].copy()
        df_train = df_train.dropna(subset=[current_factor_for_training]) # Ensure factor itself is not NaN

        if df_train.empty:
            self.write_log(f"No valid data for '{current_factor_for_training}' after dropping NaNs. Skipping training.", level=WARNING)
            return

        X_train = df_train[[current_factor_for_training]]
        y_train = X_train[current_factor_for_training] * 0.1  # Dummy target: predict 10% of the factor's value

        if X_train.empty or y_train.empty:
            self.write_log("Not enough data points after preparing X and y. Skipping training.", level=WARNING)
            return

        self.model = LinearRegression()
        try:
            self.model.fit(X_train, y_train)
            self.last_retrain_time = self.get_current_datetime() # Record successful training time
            self.write_log(f"Model trained successfully using '{current_factor_for_training}'. "
                           f"Coefficients: {self.model.coef_}, Intercept: {self.model.intercept_}. "
                           f"Last retrained: {self.last_retrain_time}", level=INFO)

            # Save the trained model
            self.model_file_path.parent.mkdir(parents=True, exist_ok=True) # Ensure directory exists
            joblib.dump(self.model, self.model_file_path)
            self.write_log(f"Model saved to {self.model_file_path}", level=INFO)

        except Exception as e:
            self.write_log(f"Error during model fitting or saving: {e}\n{traceback.format_exc()}", level=ERROR)
            self.model = None # Reset model if training failed

    def predict_from_model(self, data: pd.DataFrame) -> pd.Series:
        """
        Generate trading signals from the trained model.
        'data' is a DataFrame indexed by vt_symbol, with factors as columns.
        """
        self.write_log(f"predict_from_model called. Data shape: {data.shape}", level=DEBUG)
        if self.model is None:
            self.write_log("Model is not trained/loaded. Cannot generate predictions.", level=WARNING)
            return pd.Series(dtype=float)

        if data.empty:
            self.write_log("Input data for prediction is empty.", level=WARNING)
            return pd.Series(dtype=float)

        # Ensure the required factor is present in the input data
        current_factor_for_prediction = ""
        if self.required_factors:
            current_factor_for_prediction = self.required_factors[0] # Using the first for simplicity
        else:
            self.write_log("No required_factors defined for prediction. Returning empty signals.", level=ERROR)
            return pd.Series(dtype=float)

        if current_factor_for_prediction not in data.columns:
            self.write_log(f"Factor '{current_factor_for_prediction}' not found in prediction data columns: {data.columns}. Returning empty signals.", level=WARNING)
            return pd.Series(dtype=float)

        # Prepare data for prediction (ensure it's 2D for scikit-learn)
        # The 'data' from StrategyTemplate's on_factor is already a pandas DataFrame
        # indexed by vt_symbol, with factors as columns. NaNs should have been handled (e.g., filled with 0).
        X_pred = data[[current_factor_for_prediction]] # Select the specific factor column(s)

        if X_pred.isnull().values.any():
             self.write_log(f"NaNs found in '{current_factor_for_prediction}' column for prediction. Filling with 0 for this example.", level=WARNING)
             X_pred = X_pred.fillna(0) # Basic NaN handling for prediction

        if X_pred.empty:
            self.write_log("No valid data to predict after NaN handling for prediction.", level=WARNING)
            return pd.Series(dtype=float)
            
        try:
            predictions = self.model.predict(X_pred)
            # Ensure predictions Series has the same index as X_pred (vt_symbols)
            signals = pd.Series(predictions, index=X_pred.index, name="signal")
            self.write_log(f"Generated signals: {signals.head()}", level=DEBUG)
            return signals
        except Exception as e:
            self.write_log(f"Error during model prediction: {e}\n{traceback.format_exc()}", level=ERROR)
            return pd.Series(dtype=float)

    def project_signals_to_weights(self, signals: pd.Series) -> pd.Series:
        """
        Convert calculated signals into target portfolio weights.
        """
        self.write_log(f"project_signals_to_weights called. Received signals: {signals.head()}", level=DEBUG)
        if signals.empty:
            self.write_log("Signals are empty, returning empty weights.", level=DEBUG)
            return pd.Series(dtype=float)

        # Example: Simple normalization of signals to be weights.
        # This is a placeholder; proper portfolio construction is complex.
        # Here, we cap individual weights at 1 (for long) or -1 (for short)
        # and scale them if total exposure is too high.
        
        weights = signals.copy() # Start with signals as raw weights

        # Cap individual weights (e.g. no more than 100% long or 100% short for a single asset)
        weights = weights.clip(-1.0, 1.0)
        
        # Normalize if sum of absolute weights exceeds 1 (optional, depends on strategy leverage)
        # total_abs_weights = weights.abs().sum()
        # if total_abs_weights > 1.0:
        #     weights = weights / total_abs_weights
            
        # Ensure weights are only for symbols managed by this strategy instance (self.vt_symbols)
        # And fill any missing ones with 0 (e.g. if a symbol had no signal)
        final_weights = weights.reindex(self.vt_symbols).fillna(0.0)

        self.write_log(f"Calculated target weights: {final_weights.head()}", level=INFO)
        return final_weights

    def generate_orders_from_targets(self, target_positions_quote: pd.Series) -> List[OrderRequest]:
        """
        Generate orders based on target positions (in quote currency).
        This method can be overridden for custom order logic.
        If not overridden, the base StrategyTemplate implementation will be used.
        For this example, we'll log and use the parent's implementation.
        """
        self.write_log(f"generate_orders_from_targets called. Target positions (quote currency): {target_positions_quote.head()}", level=DEBUG)
        
        # Example: Add custom logic or checks before calling super
        # if target_positions_quote.abs().sum() > self.portfolio_result.get_total_value() * 1.1: # Max leverage check
        #    self.write_log("Calculated target exposure exceeds maximum allowed leverage. Orders might be adjusted or skipped.", level=WARNING)

        # Call the base class implementation to generate orders
        return super().generate_orders_from_targets(target_positions_quote)

    # Optional: Override on_order, on_trade if specific handling is needed
    # def on_order(self, order: OrderData) -> None:
    #     super().on_order(order)
    #     self.write_log(f"TestStrategy received order update: {order.vt_orderid}, Status: {order.status}", level=DEBUG)

    # def on_trade(self, trade: TradeData) -> None:
    #     super().on_trade(trade)
    #     self.write_log(f"TestStrategy received trade update: {trade.vt_tradeid}, Price: {trade.price}, Vol: {trade.volume}", level=DEBUG)

```
