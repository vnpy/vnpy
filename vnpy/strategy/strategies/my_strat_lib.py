# -*- coding: utf-8 -*-
"""
Example concrete strategy: MyMomentumStrategy, inheriting from StrategyTemplate.
"""

from logging import DEBUG, ERROR, INFO, WARNING
import traceback
from typing import TYPE_CHECKING, List, Dict, Any, Tuple
import pandas as pd
import polars as pl
import numpy as np # Moved import to top

# --- VnTrader Imports ---
from vnpy.trader.constant import Direction, Offset, OrderType
from vnpy.trader.object import OrderRequest # Assuming BarData might be needed for label generation

# --- Strategy System Imports ---
# Assuming StrategyTemplate, ModelConfig, TradingConfig are correctly importable
# from vnpy.strategy.template import StrategyTemplate # Actual import path
# from vnpy.strategy.config import ModelConfig, TradingConfig # Actual import path

# --- For this example, using stubs if actual imports fail (as in StrategyTemplate) ---

from vnpy.strategy.template import StrategyTemplate

if TYPE_CHECKING:
    from vnpy.strategy.engine import StrategyEngine


class MyMomentumStrategy(StrategyTemplate):
    """
    Example momentum strategy based on EMA and RSI factors.
    Uses a placeholder model for prediction.
    """
    author = "Strategy Developer"

    # These parameters will be extracted from the 'settings' dict by StrategyTemplate's __init__
    # and made available as attributes if listed in StrategyTemplate.parameters or handled by update_setting.
    # For custom params not in StrategyTemplate.parameters, access them via self.settings.get() or self.custom_param_A.
    # Let's assume they are part of the 'settings' dict passed to __init__.

    def __init__(self, engine_interface: "StrategyEngine", settings: Dict[str, Any]):
        super().__init__(engine_interface, settings) # This handles standard params

        # Load custom parameters specific to this strategy from the settings dict
        self.custom_param_a: str = settings.get("custom_strategy_param_A", "default_A")
        self.custom_param_b: int = settings.get("custom_strategy_param_B", 0)
        
        # The self.model_config and self.trading_config are already instantiated by StrategyTemplate's __init__
        # from the nested dictionaries in 'settings'.
        # Example: self.model_config.model_type, self.trading_config.min_order_volume

        self.write_log(f"MyMomentumStrategy '{self.strategy_name}' initialized.")
        self.write_log(f"Custom Param A: {self.custom_param_a}, Custom Param B: {self.custom_param_b}")
        # Log only key model/trading config details or just confirmation, avoid full __dict__ at INFO
        self.write_log(f"Model Config loaded: Type '{self.model_config.model_type if self.model_config else 'N/A'}'", level=DEBUG)
        self.write_log(f"Trading Config loaded: Default Vol '{self.trading_config.default_order_volume if self.trading_config else 'N/A'}'", level=DEBUG)

        # Model is loaded by super().__init__() via self.load_model()
        if self.model is None:
            self.write_log("No pre-trained model loaded. Strategy might need training or a model_load_path.", WARNING)
            # You might want to initialize a default untrained model here if applicable
            # from sklearn.linear_model import LogisticRegression # Example
            # self.model = LogisticRegression() 
            # self.write_log("Initialized a new default LogisticRegression model.")


    def _transform_latest_factors(self, latest_factor_data_map: Dict[str, pl.DataFrame]) -> pl.DataFrame:
        """
        Transforms latest factor data into a feature DataFrame.
        Rows: vt_symbol, Columns: factor_feature_names
        Example: factor.1h.EMAFactor@... -> EMA_20 (if period is 20)
        """
        factor_keys_sample = list(latest_factor_data_map.keys())[:3]
        if len(latest_factor_data_map) > 3:
            factor_keys_sample.append("...")
        self.write_log(f"Transforming {len(latest_factor_data_map)} latest factors (e.g., {factor_keys_sample})", level=DEBUG)
        
        all_symbol_features = []
        skipped_symbols_count = 0

        for vt_symbol in self.vt_symbols:
            symbol_features = {"vt_symbol": vt_symbol}
            symbol_has_all_factors = True

            for factor_key in self.required_factor_keys:
                factor_df = latest_factor_data_map.get(factor_key)
                if factor_df is None or factor_df.is_empty():
                    self.write_log(f"Missing or empty data for factor '{factor_key}' for symbol '{vt_symbol}'.", level=WARNING)
                    symbol_has_all_factors = False
                    break
                
                if vt_symbol not in factor_df.columns:
                    columns_sample = factor_df.columns[:3]
                    if len(factor_df.columns) > 3: columns_sample.append("...")
                    self.write_log(f"Symbol '{vt_symbol}' not found in data for factor '{factor_key}'. Available (sample): {columns_sample}", level=WARNING)
                    symbol_has_all_factors = False
                    break
                
                try:
                    factor_value = factor_df.row(0, named=True).get(vt_symbol) # Get value for the symbol
                    if factor_value is None: # Could be None if data had nulls
                         self.write_log(f"Null factor value for '{factor_key}', symbol '{vt_symbol}'.", level=DEBUG)
                         # Decide how to handle nulls, e.g., skip symbol, use 0, or let model handle NaNs
                         # For this example, we'll allow None to propagate, model input needs to handle it.

                    # Create a unique feature name, e.g., from factor_name part of factor_key
                    # "factor.1h.EMAFactor@period_20-..." -> "EMAFactor_period_20"
                    # This parsing logic needs to be robust.
                    base_name_parts = factor_key.split("@")[0].split(".")
                    feature_name = base_name_parts[-1] # Takes "EMAFactor"
                    if "@" in factor_key: # Add params part for uniqueness if needed
                        params_part = factor_key.split("@")[1].replace("-","_").replace("'","").replace("[","").replace("]","").replace(" ","")
                        feature_name = f"{feature_name}_{params_part}"
                    
                    symbol_features[feature_name] = factor_value
                except Exception as e:
                    self.write_log(f"Error extracting value for factor '{factor_key}', symbol '{vt_symbol}': {e}", level=ERROR)
                    symbol_has_all_factors = False
                    break
            
            if symbol_has_all_factors and len(symbol_features) > 1: # Has vt_symbol + at least one factor
                all_symbol_features.append(symbol_features)
            else: # This path is taken if symbol_has_all_factors is False, or if no actual factor features were added.
                 # self.write_log(f"Skipping symbol '{vt_symbol}' due to missing factor data for prediction.", level=DEBUG) # Kept removed for now, can be noisy
                 skipped_symbols_count +=1


        if skipped_symbols_count > 0:
            self.write_log(f"Skipped {skipped_symbols_count}/{len(self.vt_symbols)} symbols due to missing factor data during transformation.", level=DEBUG)

        if not all_symbol_features:
            self.write_log("No features generated for any symbol after transformation.", level=WARNING)
            return pl.DataFrame() # Return empty Polars DataFrame

        # Create a Polars DataFrame from the list of dictionaries
        # Schema will be inferred. Ensure consistent keys in symbol_features.
        features_pl_df = pl.from_dicts(all_symbol_features)
        self.write_log(f"Transformed Polars features DataFrame shape: {features_pl_df.shape}", level=DEBUG)
        return features_pl_df

    def predict_from_model(self, data: pd.DataFrame) -> Any:
        """
        Generates predictions using the loaded model.
        Input `data` is a Pandas DataFrame, index=vt_symbol, columns=factor_features.
        """
        if self.model is None:
            self.write_log("No model loaded, cannot make predictions.", level=WARNING)
            # Return neutral or no-action prediction if no model
            return pd.Series([0] * len(data), index=data.index) # Example: neutral signal (0)

        self.write_log(f"Predicting with model for {len(data)} symbols.", level=DEBUG)
        
        # Ensure columns in `data` match what model expects (preprocessing/feature selection might be needed)
        # This is a placeholder for actual prediction.
        try:
            # Example: if model is scikit-learn
            # predictions = self.model.predict(data)
            # For a classifier, you might want probabilities:
            # probabilities = self.model.predict_proba(data) # Returns array of [prob_class_0, prob_class_1]
            
            # Dummy prediction: 1 for buy, -1 for sell, 0 for hold, randomly
            # import numpy as np # Moved to top
            predictions = np.random.choice([-1, 0, 1], size=len(data))
            # Log a sample of predictions instead of the whole array if it's large
            predictions_sample = predictions[:5] if len(predictions) > 5 else predictions
            if len(predictions) > 5:
                predictions_log_str = f"{predictions_sample}... (Total: {len(predictions)})"
            else:
                predictions_log_str = f"{predictions_sample}"
            self.write_log(f"Dummy predictions generated: {predictions_log_str}", level=DEBUG)
            return pd.Series(predictions, index=data.index) # Ensure output is indexed by vt_symbol

        except Exception as e:
            self.write_log(f"Error during model prediction: {e}\n{traceback.format_exc()}", level=ERROR)
            return pd.Series([0] * len(data), index=data.index) # Fallback to neutral

    def generate_signals_from_prediction(
        self, model_output: pd.Series, symbol_feature_df: pd.DataFrame
    ) -> List[OrderRequest]:
        """
        Converts model predictions (Pandas Series, index=vt_symbol) into OrderRequests.
        `symbol_feature_df` (index=vt_symbol) is provided for context if needed.
        """
        order_requests: List[OrderRequest] = []
        if model_output is None or model_output.empty:
            return order_requests

        self.write_log(f"Generating signals from {len(model_output)} predictions.", level=DEBUG)

        for vt_symbol, prediction in model_output.items():
            contract = self.get_contract(vt_symbol)
            if not contract:
                self.write_log(f"Cannot generate signal for {vt_symbol}: Contract not found.", level=WARNING)
                continue

            # Example: Use trading_config for order sizing
            # This is highly simplified. Real sizing would use risk, account value, volatility etc.
            order_volume_setting = getattr(self.trading_config, 'default_order_volume', 0.01)
            min_order_volume = getattr(self.trading_config, 'min_order_volume', 0.001)

            # Placeholder: Get last price for market or limit order placement
            tick = self.get_tick(vt_symbol)
            last_price = tick.last_price if tick and tick.last_price > 0 else None
            if not last_price: # Fallback if no tick, maybe use close from latest bar
                bar = self.get_bar(vt_symbol)
                last_price = bar.close_price if bar else None
            
            if not last_price:
                self.write_log(f"Cannot determine price for {vt_symbol} to place order.", level=WARNING)
                continue

            direction = None
            if prediction == 1:  # Example: model output 1 means BUY
                direction = Direction.LONG
            elif prediction == -1:  # Example: model output -1 means SELL (to open short or close long)
                direction = Direction.SHORT
            
            if direction:
                # Simplified volume, actual sizing is complex
                volume_to_trade = max(min_order_volume, order_volume_setting) 

                req = OrderRequest(
                    symbol=contract.symbol,
                    exchange=contract.exchange,
                    direction=direction,
                    offset=Offset.OPEN, # Assuming opening new positions
                    type=OrderType.MARKET, # Or LIMIT with calculated price
                    price=0, # Market order
                    volume=volume_to_trade,
                    reference=self.strategy_name # Set by engine, but good practice
                )
                order_requests.append(req)
                self.write_log(f"Generated Order: {vt_symbol} {direction} {volume_to_trade} @ MARKET", level=INFO)
        
        return order_requests

    def prepare_training_data(
        self, historical_factor_data_map: Dict[str, pl.DataFrame]
    ) -> Tuple[pd.DataFrame, pd.Series]:
        """
        Prepares features (X) and labels (y) for model training.
        Input: Dict[factor_key, full_historical_polars_df_for_that_factor]
        Output: (Pandas_Features_DF, Pandas_Labels_Series)
        """
        self.write_log(f"Preparing training data from {len(historical_factor_data_map)} historical factor sets.", level=INFO)

        if not historical_factor_data_map:
            self.write_log("No historical factor data provided for training.", level=WARNING)
            return pd.DataFrame(), pd.Series(dtype='float64') # Return empty

        # --- 1. Combine and Align Factor Data (Feature Engineering - X) ---
        # This is similar to _transform_latest_factors but for the whole history.
        # We need to join all factor DataFrames on (datetime, vt_symbol).
        # Assuming each factor DataFrame has 'datetime', 'vt_symbol', and its value column(s).
        # This part can be complex depending on factor structures.
        
        # Example: Assume factors are wide (datetime | SYM1_val | SYM2_val)
        # We need to pivot them to long (datetime | vt_symbol | factor_name | factor_value)
        # then pivot_wider to get (datetime | vt_symbol | factorA | factorB)
        
        # Simplified approach:
        # If all factor DataFrames in historical_factor_data_map are already structured like:
        # Datetime | vt_symbol | factor_value_for_key1 | factor_value_for_key2 ...
        # This would require factors to output in a consistent "feature matrix" format per symbol per datetime.
        # More realistically, each factor_df is (datetime | SYM_A_val | SYM_B_val) for *that specific factor*.

        # Let's assume we iterate through symbols and then time, building features.
        # This example will be a placeholder for robust feature matrix construction.
        
        # Placeholder: Concatenate all factor values for each symbol and datetime
        # This requires careful alignment and merging.
        # For simplicity, let's assume we can create a multi-indexed (datetime, symbol) DataFrame
        # with factor values as columns.

        # A more robust way is to process each factor_df, melt it to long format:
        # (datetime, vt_symbol, factor_feature_name, value)
        # then join them all.
        
        all_features_list = []
        processed_symbols = set()
        empty_factors_skipped = []

        # Iterate through each required factor
        for factor_key, factor_df_pl in historical_factor_data_map.items():
            if factor_df_pl.is_empty():
                empty_factors_skipped.append(factor_key)
                continue

            # Assume factor_df_pl is [datetime, SYM1_val, SYM2_val, ...]
            # Melt to long format: [datetime, vt_symbol, value]
            # Create a feature name from factor_key
            base_name_parts = factor_key.split("@")[0].split(".")
            feature_col_name = base_name_parts[-1]
            if "@" in factor_key:
                params_part = factor_key.split("@")[1].replace("-","_").replace("'","").replace("[","").replace("]","").replace(" ","")
                feature_col_name = f"{feature_col_name}_{params_part}"


            melted_df = factor_df_pl.melt(
                id_vars=[self.strategy_engine.factor_datetime_col], # Use engine's datetime col name
                value_vars=[col for col in factor_df_pl.columns if col != self.strategy_engine.factor_datetime_col and col in self.vt_symbols],
                variable_name="vt_symbol",
                value_name=feature_col_name
            )
            if not melted_df.is_empty():
                all_features_list.append(melted_df)
                processed_symbols.update(melted_df["vt_symbol"].unique().to_list())

        if empty_factors_skipped:
            skipped_keys_sample = empty_factors_skipped[:3]
            if len(empty_factors_skipped) > 3:
                skipped_keys_sample.append("...")
            self.write_log(f"Skipped {len(empty_factors_skipped)} factors with empty historical data (e.g., {skipped_keys_sample}).", level=WARNING)

        if not all_features_list:
            self.write_log("No features could be extracted from historical factor data (all non-empty factors processed).", level=WARNING)
            return pd.DataFrame(), pd.Series(dtype='float64')

        # Join all melted factor DataFrames
        features_pl_df_combined = all_features_list[0]
        for i in range(1, len(all_features_list)):
            try:
                features_pl_df_combined = features_pl_df_combined.join(
                    all_features_list[i],
                    on=[self.strategy_engine.factor_datetime_col, "vt_symbol"],
                    how="outer" # Use outer join to keep all datetimes/symbols, NaNs for mismatches
                )
            except Exception as e_join:
                 self.write_log(f"Error joining historical factor data: {e_join}. Data for factor {i} might be problematic.", ERROR)
                 # Potentially skip this problematic factor data and continue
                 continue
        
        if features_pl_df_combined.is_empty():
            self.write_log("Combined historical feature DataFrame is empty.", level=WARNING)
            return pd.DataFrame(), pd.Series(dtype='float64')

        # --- 2. Generate Labels (y) ---
        # This is highly strategy-specific. Requires historical price (OHLCV) data.
        # Example: Predict next day/bar return > threshold.
        # For this placeholder, we'll generate dummy labels (e.g., random 0 or 1).
        
        # Ensure features_pl_df_combined is sorted by datetime then symbol for consistent label generation
        features_pl_df_combined = features_pl_df_combined.sort([self.strategy_engine.factor_datetime_col, "vt_symbol"])

        # Placeholder: Fetch OHLCV data for label generation
        # This would typically involve querying self.strategy_engine.database
        # For all self.vt_symbols over the relevant period.
        # ohlcv_data = self.strategy_engine.load_historical_bars_for_symbols(
        #     self.vt_symbols, 
        #     features_pl_df_combined[self.strategy_engine.factor_datetime_col].min(),
        #     features_pl_df_combined[self.strategy_engine.factor_datetime_col].max() + timedelta(days=1) # Need future data for labels
        # )
        
        # Example dummy label generation: 1 if next period's close is higher, else 0
        # This is illustrative and needs actual price data and proper alignment.
        # For now, let's create random labels.
        num_rows = len(features_pl_df_combined)
        # import numpy as np # Moved to top
        dummy_labels = pl.Series("target", np.random.randint(0, 2, size=num_rows))

        # Align labels with features. If using shifted returns, ensure proper alignment.
        # For this dummy example, assume direct alignment.
        
        # Convert features and labels to Pandas, set multi-index for features if needed by model
        # For scikit-learn, usually features are (n_samples, n_features) and labels (n_samples,)
        features_pd_df = features_pl_df_combined.drop([self.strategy_engine.factor_datetime_col, "vt_symbol"]).to_pandas()
        labels_pd_series = dummy_labels.to_pandas()

        # Drop rows with NaNs that might have resulted from outer joins or in factor data itself
        # This is a common preprocessing step.
        original_len = len(features_pd_df)
        features_pd_df_cleaned = features_pd_df.dropna()
        labels_pd_series_cleaned = labels_pd_series[features_pd_df_cleaned.index] # Align labels
        
        if len(features_pd_df_cleaned) < original_len:
            self.write_log(f"Dropped {original_len - len(features_pd_df_cleaned)} rows with NaNs during training data prep.", level=INFO)

        if features_pd_df_cleaned.empty:
            self.write_log("Training features DataFrame is empty after NaN removal.", level=WARNING)
            return pd.DataFrame(), pd.Series(dtype='float64')

        self.write_log(f"Prepared training data: Features shape {features_pd_df_cleaned.shape}, Labels shape {labels_pd_series_cleaned.shape}", level=INFO)
        return features_pd_df_cleaned, labels_pd_series_cleaned

