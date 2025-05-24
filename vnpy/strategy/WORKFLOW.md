# Strategy Engine & Template Workflow

This document outlines the data flow and model lifecycle within the `StrategyEngine` and `StrategyTemplate` framework.

## I. Data Flow: From Factor Event to Order Placement

1.  **Factor Calculation & Event**:
    *   External processes or a dedicated factor engine calculates factor data.
    *   Upon completion, an `EVENT_FACTOR` (or a similarly purposed event, e.g., `EVENT_FACTOR_UPDATE`) is emitted.
    *   This event carries a dictionary: `Dict[str, FactorMemory]`, where keys are unique factor identifiers (e.g., "factor.1m.EMA_Close_12") and values are `FactorMemory` instances containing the data for that factor across multiple symbols.

2.  **StrategyEngine: Event Reception & Dispatch**:
    *   The `StrategyEngine` (specifically, the modified `BaseStrategyEngine` in `vnpy/strategy/engine.py`) listens for the `EVENT_FACTOR`.
    *   Upon receiving the event, its `process_factor_event` method is triggered.
    *   The engine caches these `FactorMemory` instances (e.g., in `self.latest_factor_memories`) for potential use in retraining.
    *   It then iterates through all active (inited and trading) strategy instances.
    *   For each strategy instance, it calls the `strategy.on_factor(latest_factor_memories)` method, passing the complete dictionary of `FactorMemory` objects.

3.  **StrategyTemplate: Factor Processing & Prediction**:
    *   The `on_factor` method within the concrete strategy (inheriting from `StrategyTemplate` in `vnpy/strategy/template.py`) is invoked.
    *   **Data Fetching**: The strategy uses its `required_factor_keys` list to identify the factors it needs. For each required factor, it calls `factor_memory.get_latest_rows(1)` on the corresponding `FactorMemory` object (from the dictionary received from the engine) to get the latest data snapshot as a Polars DataFrame. This results in a `Dict[str, pl.DataFrame]`.
    *   **Transformation**: It calls its (abstract, implemented by concrete strategy) `_transform_latest_factors(latest_polars_data_map)` method. This method takes the dictionary of Polars DataFrames, pivots/transforms/combines them into a single Polars DataFrame where rows typically represent `vt_symbol` and columns represent factor features.
    *   **Prediction**:
        *   The transformed Polars DataFrame is converted to a Pandas DataFrame.
        *   It calls its (abstract, implemented by concrete strategy) `predict_from_model(pandas_feature_df)` method. This method uses the strategy's loaded model (`self.model`) to generate raw predictions (e.g., probabilities, class labels).
    *   **Signal Generation**: It calls its (abstract, implemented by concrete strategy) `generate_signals_from_prediction(model_output, pandas_feature_df)` method. This method converts the raw model predictions into actionable trading signals, typically a list of `OrderRequest` objects.

4.  **StrategyEngine: Order Execution**:
    *   The `StrategyEngine` receives the list of `OrderRequest` objects returned by the strategy's `on_factor` method.
    *   For each `OrderRequest`, the engine calls `self.send_order(strategy_name, order_request)`, which forwards the request to the appropriate trading gateway via `MainEngine.send_order()` (or the `ExecutionAgent`).

## II. Model Retraining Loop

1.  **Scheduled Trigger (StrategyEngine)**:
    *   The `StrategyEngine` has a timer event (`_process_timer_event`) that fires periodically (e.g., every minute or hour).
    *   For each active strategy, it calls `strategy.check_retraining_schedule(current_datetime)`.
    *   The `check_retraining_schedule` method in `StrategyTemplate` checks if retraining is due based on `strategy.retraining_config["frequency_days"]` and `strategy.last_retrain_time`. It also considers if a model needs initial training (e.g. `self.model` is `None` and `model_load_path` was not successful).

2.  **Retraining Initiation (StrategyEngine)**:
    *   If `check_retraining_schedule` returns `True`, the `StrategyEngine` queues a call to `strategy.retrain_model()` in a separate thread (using `self.init_executor.submit(self._train_strategy_model_thread, strategy.strategy_name)`, where `_train_strategy_model_thread` now directly calls `strategy.retrain_model()`).

3.  **Data Preparation & Training (StrategyTemplate)**:
    *   The `retrain_model` method within the `StrategyTemplate` is executed.
    *   **Fetch Historical Data**: It calls its helper `_fetch_historical_training_factors(self.strategy_engine.latest_factor_memories)`. This helper iterates through the strategy's `required_factor_keys`, accesses the corresponding `FactorMemory` objects from the engine's cache, and calls `factor_memory.get_data()` on each to get full historical data as Polars DataFrames (`Dict[str, pl.DataFrame]`).
    *   **Prepare Training Data**: It calls its (abstract, implemented by concrete strategy) `prepare_training_data(historical_polars_data_map)` method. This method takes the dictionary of historical Polars DataFrames and transforms them into features (Pandas DataFrame `X`) and labels (Pandas Series `y`) suitable for model training. This step includes any necessary data cleaning, feature engineering from historical data, and label generation.
    *   **Model Fitting**: If valid training data (`X`, `y`) is produced, it trains its model: `self.model.fit(X, y)`.
    *   **Save Model**: After successful training, it calls `self.save_model()` to persist the updated model to `self.model_save_path`.
    *   **Update Timestamp**: It updates `self.last_retrain_time` to the current datetime.

4.  **Ongoing Predictions**:
    *   Once the model is retrained (i.e., `self.model` is updated), subsequent calls to `on_factor` will use the newly retrained model for predictions.

This workflow enables strategies to react to new factor data for generating trading signals and incorporates a managed lifecycle for their predictive models, including automated retraining.
