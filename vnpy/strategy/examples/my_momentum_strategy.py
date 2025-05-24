# -*- coding: utf-8 -*-
"""
An example momentum strategy that inherits from StrategyTemplate.
"""

from typing import Dict, List, Tuple, Any, Optional

import polars as pl
import pandas as pd
import numpy as np # For placeholder label generation

# --- VnTrader Imports ---
from vnpy.trader.object import OrderRequest, TickData, ContractData
from vnpy.trader.constant import Direction, Offset, OrderType
from vnpy.strategy.template import StrategyTemplate
# from vnpy.factor.memory import FactorMemory # For type hinting if needed

# --- Machine Learning Model (Example) ---
from sklearn.linear_model import LogisticRegression


class MyMomentumStrategy(StrategyTemplate):
    """
    Example Momentum Strategy.
    """

    author = "VnPy Example"
    parameters: List[str] = [
        "custom_strategy_param1",
        # Add other specific parameters that this strategy uses from the instance config
        # Note: vt_symbols, required_factor_keys, model_load_path, model_save_path,
        # retraining_config, model_config, trading_config are already handled by base StrategyTemplate
    ]
    variables: List[str] = [
        "custom_param" # Expose custom_param to UI if needed
    ]

    def __init__(
            self,
            strategy_engine, # "BaseStrategyEngine" type hint if available
            strategy_name: str,
            vt_symbols: List[str],
            setting: dict, # Full instance configuration
            # Specific parameters passed by BaseStrategyEngine from instance_config
            model_load_path: Optional[str] = None,
            model_save_path: Optional[str] = None,
            retraining_config: Optional[Dict[str, Any]] = None,
            required_factor_keys: Optional[List[str]] = None
    ):
        """
        Initialize the MyMomentumStrategy instance.
        """
        super().__init__(
            strategy_engine,
            strategy_name,
            vt_symbols,
            setting, # Pass the full instance_config dict to base
            model_load_path,
            model_save_path,
            retraining_config,
            required_factor_keys
        )

        # Initialize model if not loaded by super().load_model()
        if self.model is None:
            self.write_log("Model not loaded from path, initializing new LogisticRegression model.", level=10) # DEBUG
            self.model = LogisticRegression()
        else:
            self.write_log("Model loaded successfully via base class.", level=10) # DEBUG

        # Access custom parameters from the 'setting' dictionary (instance_config)
        self.custom_param = setting.get("custom_strategy_param1", "default_value_momentum")
        self.write_log(f"Custom strategy param1: {self.custom_param}", level=10) # DEBUG
        
        # Example: Accessing model_config and trading_config passed in the 'setting' dict
        # These are already parsed by the base class's update_setting if they exist in the 'setting' dict
        # self.model_config and self.trading_config are available from base class
        if self.model_config and hasattr(self.model_config, 'some_model_hyperparam'):
            self.write_log(f"Model config hyperparam: {self.model_config.some_model_hyperparam}", level=10)
        if self.trading_config and hasattr(self.trading_config, 'min_order_volume'):
            self.write_log(f"Trading config min_order_volume: {self.trading_config.min_order_volume}", level=10)


    def _transform_latest_factors(self, latest_factor_data_map: Dict[str, pl.DataFrame]) -> Optional[pl.DataFrame]:
        """
        Transforms and combines the latest snapshot of multiple factor Polars DataFrames.
        """
        self.write_log(f"_transform_latest_factors received map with keys: {list(latest_factor_data_map.keys())}", level=10)

        processed_dfs = []
        for factor_key in self.required_factor_keys:
            factor_df = latest_factor_data_map.get(factor_key)
            if factor_df is None or factor_df.is_empty():
                self.write_log(f"Factor {factor_key} data is missing or empty in latest_factor_data_map.", level=20) # INFO
                # Depending on strategy, might return None or continue if some factors are optional
                return None 

            if "vt_symbol" not in factor_df.columns:
                self.write_log(f"Factor {factor_key} DataFrame missing 'vt_symbol' column.", level=30) # WARNING
                return None

            # Identify value column (e.g., 'value' or the factor_key itself)
            value_column_name = ""
            if "value" in factor_df.columns:
                value_column_name = "value"
            elif factor_key in factor_df.columns:
                value_column_name = factor_key
            else:
                # Attempt to infer if only one other column apart from vt_symbol, datetime (if present)
                potential_value_cols = [
                    col for col in factor_df.columns if col not in ['vt_symbol', 'datetime']
                ]
                if len(potential_value_cols) == 1:
                    value_column_name = potential_value_cols[0]
                    self.write_log(f"Inferred value column '{value_column_name}' for factor {factor_key}", level=10)
                else:
                    self.write_log(f"Could not identify value column for factor {factor_key}. Expected 'value' or '{factor_key}'. Found: {factor_df.columns}", level=30) # WARNING
                    return None
            
            try:
                # Select vt_symbol and the value column, rename value column to factor_key
                # Polars select is by position or name. If using `select`, ensure proper column names.
                # Using `with_columns` for renaming is safer.
                renamed_df = factor_df.select([
                    pl.col("vt_symbol"),
                    pl.col(value_column_name).alias(factor_key)
                ])
                
                # Set vt_symbol as index (Polars doesn't have a direct 'set_index' like pandas for joins)
                # For concat, we just need vt_symbol as a column to join on later if needed, or align by row if shapes match.
                # If these are single-row DFs (latest snapshot), direct concat might be okay if order is guaranteed.
                # More robust: ensure vt_symbol is present for later join/pivot if multi-row.
                # For now, assuming each DF in latest_factor_data_map is for one point in time, multiple symbols.
                processed_dfs.append(renamed_df)
            except Exception as e:
                self.write_log(f"Error processing factor {factor_key}: {e}", level=40) # ERROR
                return None

        if not processed_dfs:
            self.write_log("No factor DataFrames were processed.", level=20)
            return None

        # Combine DataFrames: Assuming each df in processed_dfs has 'vt_symbol' and one factor column.
        # We need to join them on 'vt_symbol'.
        try:
            final_df = processed_dfs[0]
            for i in range(1, len(processed_dfs)):
                final_df = final_df.join(processed_dfs[i], on="vt_symbol", how="outer_coalesce")
            
            # Fill NaNs (e.g., with 0 or a strategy-specific value)
            final_df = final_df.fill_null(0) # Example: fill with 0
            self.write_log(f"Transformed factors shape: {final_df.shape}", level=10)
            return final_df
        except Exception as e:
            self.write_log(f"Error concatenating/joining processed factor DataFrames: {e}", level=40)
            return None


    def predict_from_model(self, data: pd.DataFrame) -> Any:
        """
        Generate raw predictions from the trained model.
        'data' is a Pandas DataFrame with vt_symbol as index and factors as columns.
        """
        if self.model is None:
            self.write_log("Model is not initialized. Cannot predict.", level=30) # WARNING
            return None
        if data.empty:
            self.write_log("Input data for prediction is empty.", level=20) # INFO
            return None
        
        self.write_log(f"Predicting with model using data shape: {data.shape}", level=10)
        try:
            # Ensure columns are in the same order as during training if model is sensitive to it
            # This might require saving/loading feature names with the model
            predictions = self.model.predict(data) # Or predict_proba(data)
            return predictions
        except Exception as e:
            self.write_log(f"Error during model prediction: {e}", level=40) # ERROR
            return None

    def generate_signals_from_prediction(
        self, model_output: Any, symbol_feature_df: pd.DataFrame
    ) -> List[OrderRequest]:
        """
        Convert raw model output into trading signals or OrderRequests.
        model_output: Predictions from predict_from_model.
        symbol_feature_df: Pandas DataFrame used for prediction (index is vt_symbol).
        """
        order_requests: List[OrderRequest] = []
        if model_output is None or symbol_feature_df.empty:
            self.write_log("No model output or feature data to generate signals.", level=20)
            return order_requests

        # Assuming model_output is a 1D array/series aligned with symbol_feature_df.index
        if len(model_output) != len(symbol_feature_df):
            self.write_log("Model output length does not match feature DataFrame length. Cannot map predictions.", level=30)
            return order_requests

        self.write_log(f"Generating signals from {len(model_output)} predictions.", level=10)

        for i, vt_symbol in enumerate(symbol_feature_df.index):
            prediction = model_output[i] # Get prediction for this symbol

            contract: Optional[ContractData] = self.get_contract(vt_symbol)
            if not contract:
                self.write_log(f"Contract not found for {vt_symbol}, cannot generate order.", level=30)
                continue

            tick: Optional[TickData] = self.get_tick(vt_symbol)
            if not tick or not tick.last_price:
                self.write_log(f"Tick or last_price not available for {vt_symbol}, cannot generate order.", level=30)
                continue

            direction: Optional[Direction] = None
            if prediction == 1: # Example: Buy signal
                direction = Direction.LONG
            elif prediction == 0: # Example: Sell signal (or close long)
                direction = Direction.SHORT 
            # Add more conditions, e.g. for hold, probabilities, etc.

            if direction:
                # Simplified order: Market order for a fixed volume or value
                # In a real strategy, volume calculation would be more sophisticated
                # (e.g., based on risk, portfolio allocation, available capital)
                # For this example, let's use a fixed volume if trading_config allows
                # Safely access default_order_volume, defaulting to 1.0 and ensuring float
                fixed_volume = float(getattr(self.trading_config, 'default_order_volume', 1.0))
                
                # Safely access min_order_volume, defaulting to a small positive value and ensuring float
                min_vol = float(getattr(self.trading_config, 'min_order_volume', 0.000001))

                if fixed_volume < min_vol:
                    self.write_log(f"Default order volume {fixed_volume} for {vt_symbol} is less than min_order_volume {min_vol}. Adjusting to min_order_volume.", level=20)
                    fixed_volume = min_vol
                
                # Check if the (potentially adjusted) fixed_volume is valid
                if fixed_volume <= 0: 
                    self.write_log(f"Skipping order for {vt_symbol} due to zero or negative final order volume: {fixed_volume}", level=20)
                    continue


                req = OrderRequest(
                    symbol=contract.symbol,
                    exchange=contract.exchange,
                    direction=direction,
                    offset=Offset.NONE, # Or Offset.OPEN / Offset.CLOSE depending on logic
                    type=OrderType.MARKET, # Example: Market Order
                    price=0, # Market order doesn't need price, but API might require it
                    volume=fixed_volume,
                    reference=self.strategy_name 
                )
                order_requests.append(req)
                self.write_log(f"Generated OrderRequest for {vt_symbol}: {direction} {fixed_volume} units.", level=20)
        
        return order_requests


    def prepare_training_data(
        self, historical_factor_data_map: Dict[str, pl.DataFrame]
    ) -> Tuple[Optional[pd.DataFrame], Optional[pd.Series]]:
        """
        Prepares features (X) and labels (y) for model training from historical Polars factor data.
        """
        self.write_log(f"Preparing training data from {len(historical_factor_data_map)} factor sources.", level=10)
        
        if not historical_factor_data_map:
            self.write_log("Historical factor data map is empty. Cannot prepare training data.", level=30)
            return None, None

        processed_historical_dfs = []
        for factor_key in self.required_factor_keys: # Use required_factor_keys to ensure order and presence
            factor_hist_df = historical_factor_data_map.get(factor_key)
            if factor_hist_df is None or factor_hist_df.is_empty():
                self.write_log(f"Historical data for factor {factor_key} is missing or empty.", level=30)
                return None, None # Crucial factor missing

            if "vt_symbol" not in factor_hist_df.columns or "datetime" not in factor_hist_df.columns:
                self.write_log(f"Factor {factor_key} historical DataFrame missing 'vt_symbol' or 'datetime'.", level=30)
                return None, None

            value_column_name = ""
            if "value" in factor_hist_df.columns: value_column_name = "value"
            elif factor_key in factor_hist_df.columns: value_column_name = factor_key
            else:
                potential_value_cols = [c for c in factor_hist_df.columns if c not in ['vt_symbol', 'datetime', 'timestamp']]
                if len(potential_value_cols) == 1: value_column_name = potential_value_cols[0]
                else:
                    self.write_log(f"Cannot find value column for historical factor {factor_key}.", level=30)
                    return None, None
            
            try:
                # Select necessary columns and rename value column to factor_key
                # Ensure datetime is preserved for joining
                temp_df = factor_hist_df.select([
                    pl.col("datetime"),
                    pl.col("vt_symbol"),
                    pl.col(value_column_name).alias(factor_key)
                ])
                processed_historical_dfs.append(temp_df)
            except Exception as e:
                self.write_log(f"Error selecting/renaming columns for historical factor {factor_key}: {e}", level=40)
                return None, None

        if not processed_historical_dfs:
            self.write_log("No historical factor DataFrames were processed.", level=30)
            return None, None

        # Join all historical factor DataFrames on 'datetime' and 'vt_symbol'
        try:
            features_pl_df = processed_historical_dfs[0]
            for i in range(1, len(processed_historical_dfs)):
                features_pl_df = features_pl_df.join(
                    processed_historical_dfs[i], 
                    on=["datetime", "vt_symbol"], 
                    how="outer_coalesce" # Use outer_coalesce to keep all data and merge common rows
                )
            
            # Sort by symbol then time, important for time-series operations like shifts
            features_pl_df = features_pl_df.sort(["vt_symbol", "datetime"])
            self.write_log(f"Combined historical features (Polars) shape: {features_pl_df.shape}", level=10)

        except Exception as e:
            self.write_log(f"Error joining historical factor DataFrames: {e}", level=40)
            return None, None
            
        # --- Label Generation (Placeholder) ---
        # In a real scenario, labels (y) would be generated based on future price movements
        # or other target variables. This often requires fetching price data.
        # For this example, we'll generate random labels.
        # Prerequisite: 'close_price' or similar factor to base labels on.
        # If not available, random labels are the only choice for this example structure.

        if features_pl_df.is_empty():
            self.write_log("Features DataFrame is empty after join. Cannot generate labels.", level=30)
            return None, None
            
        # Example: If you had a 'close_price' column in features_pl_df from a factor
        # labels_pl = features_pl_df.group_by("vt_symbol").agg(
        #     (pl.col("close_price").shift(-5) / pl.col("close_price") - 1).alias("future_return_5_periods")
        # ).select(
        #      (pl.col("future_return_5_periods") > 0.01).cast(pl.Int8).alias("label") # Buy if >1% gain
        # )
        # features_pl_df = features_pl_df.join(labels_pl, on="vt_symbol", how="left")
        # labels_series = features_pl_df.select("label").to_pandas().iloc[:, 0]
        # features_pl_df = features_pl_df.drop("label", "close_price", "future_return_5_periods") # Drop label-related cols
        
        # Using random labels for this example as price data is not guaranteed in factors
        num_rows = features_pl_df.height
        if num_rows == 0:
            self.write_log("Features DataFrame has 0 rows after processing. Cannot generate labels.", level=30)
            return None, None
            
        np_labels = np.random.randint(0, 2, size=num_rows)
        labels_series = pd.Series(np_labels, name="label")
        self.write_log(f"Generated random labels, shape: {labels_series.shape}", level=10)

        # Convert features to Pandas DataFrame
        features_df_pd = features_pl_df.to_pandas()
        
        # Drop datetime and vt_symbol if they are not features for the model
        # Or set them as index if model/data alignment requires it.
        # For scikit-learn, usually, index is not part of X.
        if "datetime" in features_df_pd.columns:
            features_df_pd = features_df_pd.drop(columns=["datetime"])
        if "vt_symbol" in features_df_pd.columns:
            features_df_pd = features_df_pd.drop(columns=["vt_symbol"])
            
        # Align features and labels, and handle NaNs that might have resulted from joins or shifts
        # It's crucial that X and y are perfectly aligned and cleaned.
        
        # Example: Drop rows with any NaNs in features
        features_df_pd = features_df_pd.dropna()
        
        # Align labels with the (potentially NaN-dropped) features_df_pd
        if features_df_pd.index.is_monotonic_increasing and not features_df_pd.index.has_duplicates:
             # If index is clean from Polars to Pandas conversion (e.g. simple row numbers)
            labels_series = labels_series.loc[features_df_pd.index]
        else:
            # This case is tricky if index is not just simple row numbers after to_pandas()
            # For this example, assume index from to_pandas() is sufficient for .loc alignment if features_df_pd was not re-indexed.
            # If features_df_pd was re-indexed, complex alignment is needed.
            # Simplest if NaNs were handled in Polars df before conversion or if to_pandas().dropna() is used carefully.
            # For now, assuming direct alignment after feature NaNs are dropped.
            original_index = features_df_pd.index
            labels_series = labels_series.iloc[original_index] # This assumes default integer index from to_pandas()
        
        labels_series = labels_series.dropna() # Ensure labels don't have NaNs
        
        # Final alignment of index
        common_index = features_df_pd.index.intersection(labels_series.index)
        features_df_pd = features_df_pd.loc[common_index]
        labels_series = labels_series.loc[common_index]

        if features_df_pd.empty or labels_series.empty:
            self.write_log("Features or labels are empty after NaN handling and alignment.", level=30)
            return None, None

        self.write_log(f"Final training features (Pandas) shape: {features_df_pd.shape}", level=10)
        self.write_log(f"Final training labels (Pandas) shape: {labels_series.shape}", level=10)
        
        return features_df_pd, labels_series

    # --- Lifecycle Methods (Optional Overrides) ---
    # def on_init(self) -> None:
    #     super().on_init() # Call base class
    #     # Custom init logic
    #     self.write_log("MyMomentumStrategy on_init called")

    # def on_start(self) -> None:
    #     super().on_start()
    #     # Custom start logic
    #     self.write_log("MyMomentumStrategy on_start called")

    # def on_stop(self) -> None:
    #     super().on_stop()
    #     # Custom stop logic
    #     self.write_log("MyMomentumStrategy on_stop called")

    # --- Event Processing Methods (Optional Overrides for custom handling) ---
    # def on_tick(self, tick: TickData) -> None:
    #     """
    #     Callback for new tick data. Not typically used if relying on on_factor.
    #     """
    #     super().on_tick(tick) # For base class logging or event putting
    #     self.write_log(f"Received tick for {tick.vt_symbol}: {tick.last_price}", level=10)

    # def on_order(self, order: OrderData) -> None:
    #     super().on_order(order)
    #     # Custom order event handling
    #     self.write_log(f"MyMomentumStrategy on_order: {order.vt_orderid}, Status: {order.status}", level=10)

    # def on_trade(self, trade: TradeData) -> None:
    #     super().on_trade(trade)
    #     # Custom trade event handling
    #     self.write_log(f"MyMomentumStrategy on_trade: {trade.vt_orderid}, Price: {trade.price}, Volume: {trade.volume}", level=10)

```
