# -*- coding: utf-8 -*-
"""
Provides a template for strategies using a Linear Model to generate raw trading
signals from factor data. Inherits from ModelStrategyTemplate.

This template assumes the "model" is a set of coefficients for a linear
combination of input factors.

Strategies inheriting from this template should implement:
- `project_signals_to_weights`: Converts the linear model's raw signal to target weights.
"""

from abc import abstractmethod
from logging import DEBUG, ERROR, INFO, WARNING
from typing import TYPE_CHECKING, Optional, List, Dict, Any
import pandas as pd
import numpy as np # For dot product calculation

# --- VnTrader Imports ---
# (Inherited functionality uses these)
from vnpy.trader.object import OrderRequest # For type hint in on_factor

# --- Local Imports ---
# Import the base ModelStrategyTemplate
from model_template import ModelStrategyTemplate

from ..engine import BaseStrategyEngine


class LinearModelStrategyTemplate(ModelStrategyTemplate):
    """
    Abstract base class for strategies using a Linear Model for signal generation.

    The linear model is defined by a dictionary of coefficients, where keys are
    factor names and values are their corresponding weights.
    """

    # --- Linear Model Specific Metadata ---
    # Add coefficients to parameters, remove model_path if not used
    parameters: List[str] = [
        p for p in ModelStrategyTemplate.parameters if p != "model_path"
    ] + ["model_coefficients"]
    # Remove model_loaded/model_path from variables if model object isn't loaded from file
    variables: List[str] = [
        v for v in ModelStrategyTemplate.variables if v not in ["model_loaded", "model_path"]
    ]

    def __init__(
        self,
        strategy_engine: "BaseStrategyEngine",
        strategy_name: str,
        vt_symbols: List[str],
        setting: dict
    ) -> None:
        """
        Initialize the LinearModelStrategyTemplate.

        Args:
            strategy_engine: The Strategy Engine managing this strategy.
            strategy_name: A unique name for this strategy instance.
            vt_symbols: Initial list of vt_symbols from configuration.
            setting: Dictionary of initial parameters from configuration,
                     expected to contain 'model_coefficients'.
        """
        # --- Linear Model State ---
        # Coefficients store the linear model weights {factor_name: coefficient}
        self.model_coefficients: Dict[str, float] = {}

        # --- Initialize Base Class ---
        # This calls super().__init__ which handles base setup and calls
        # self.update_setting (loading initial settings including coefficients)
        # and self._load_model (which we override).
        super().__init__(strategy_engine, strategy_name, vt_symbols, setting)

        # Model is considered "loaded" if coefficients are present
        self.model_loaded = bool(self.model_coefficients)
        if not self.model_loaded:
             self.write_log("Linear model coefficients not provided or empty in settings.", level=WARNING)


    # --------------------------------
    # Model Loading Override
    # --------------------------------

    def _load_model(self) -> None:
        """
        [Internal] Override: Loads the linear model coefficients.
        In this template, "loading" means ensuring the coefficients are set,
        typically via `update_setting` during initialization.
        """
        # Check if coefficients were loaded via update_setting
        if self.model_coefficients:
            self.write_log(f"Linear model coefficients loaded/set: {list(self.model_coefficients.keys())}", level=INFO)
            self.model_loaded = True
            # The actual coefficients dict acts as the "model" here
            self.model = self.model_coefficients
        else:
            self.write_log("Linear model coefficients are empty. Model not loaded.", level=WARNING)
            self.model_loaded = False
            self.model = None

    # --------------------------------
    # Core Logic Implementation
    # --------------------------------

    def predict_signal(self, df: pd.DataFrame) -> pd.Series:
        """
        Generate raw signals using the linear model coefficients.
        Calculates the dot product of the input factor values and the coefficients.

        Args:
            df: Pandas DataFrame containing the factor values required by the model,
                indexed by vt_symbol, columns are factor names.

        Returns:
            Pandas Series containing the raw predicted signal (linear combination score)
            for each vt_symbol. Index is vt_symbol.
        """
        if not self.model_loaded or not self.model_coefficients:
            self.write_log("Model coefficients not loaded, cannot predict signals.", level=ERROR)
            return pd.Series(dtype=float) # Return empty Series

        # Ensure the DataFrame contains the factors needed by the coefficients
        required_factors = list(self.model_coefficients.keys())
        available_factors = [f for f in required_factors if f in df.columns]

        if not available_factors:
            self.write_log(f"None of the required factors for the linear model ({required_factors}) are available in the input data.", level=ERROR)
            return pd.Series(dtype=float)

        # Handle missing factors among required ones (optional: fill with 0 or mean?)
        missing_factors = set(required_factors) - set(available_factors)
        if missing_factors:
            self.write_log(f"Missing required factors for linear model: {missing_factors}. Calculation will proceed without them.", level=WARNING)
            # Decide how to handle: exclude them, or fill corresponding coefficients with 0?
            # Let's proceed using only available factors.

        # Align DataFrame columns and coefficients
        df_aligned = df[available_factors]
        coeffs_aligned = pd.Series({f: self.model_coefficients[f] for f in available_factors})

        # Fill NaN values in factor data (important for dot product)
        # Common strategies: fill with 0 or forward fill. Filling with 0 assumes missing factor has no impact.
        df_filled = df_aligned.fillna(0.0)
        # Alternatively: df_filled = df_aligned.ffill().fillna(0.0) # Forward fill then fill remaining NaNs

        # Calculate the linear combination (dot product) for each row (vt_symbol)
        # df_filled: rows=symbols, cols=factors
        # coeffs_aligned: index=factors, values=coefficients
        # Result should be a Series: index=symbols, values=dot_product
        try:
            raw_signals = df_filled.dot(coeffs_aligned)
            self.write_log(f"Calculated {len(raw_signals)} raw linear signals.", level=DEBUG)
            return raw_signals
        except Exception as e:
            self.write_log(f"Error calculating dot product for linear model: {e}", level=ERROR)
            return pd.Series(dtype=float)


    # Keep project_signals_to_weights abstract - to be implemented by inheriting strategy
    @abstractmethod
    def project_signals_to_weights(self, signals: pd.Series) -> pd.Series:
        """
        Convert calculated raw linear signals into target portfolio weights.
        (Implementation required in the final strategy inheriting this template).
        """
        pass

    # --------------------------------
    # State Management Overrides
    # --------------------------------

    def get_parameters(self) -> dict:
        """Return the current strategy parameters, including model coefficients."""
        params = super(ModelStrategyTemplate, self).get_parameters() # Call grandparent's method
        # Add/update linear model-specific parameters
        params["model_coefficients"] = self.model_coefficients.copy() # Return a copy
        # Remove model_path if it exists from the base class parameters
        params.pop("model_path", None)
        return params

    def update_setting(self, setting: dict) -> None:
        """Update strategy parameters, handling model coefficients."""
        # Call grandparent's update_setting to handle base parameters like vt_symbols etc.
        super(ModelStrategyTemplate, self).update_setting(setting)

        # Update linear model coefficients
        if "model_coefficients" in setting:
            coeffs = setting["model_coefficients"]
            if isinstance(coeffs, dict):
                # Validate coefficient types (should be numeric)
                valid_coeffs = {}
                invalid_found = False
                for factor, coeff_val in coeffs.items():
                     if isinstance(coeff_val, (int, float)):
                          valid_coeffs[factor] = float(coeff_val)
                     else:
                          self.write_log(f"Invalid coefficient type for factor '{factor}': {type(coeff_val)}. Skipping.", level=WARNING)
                          invalid_found = True
                # Update only if coefficients changed
                if valid_coeffs != self.model_coefficients:
                    self.model_coefficients = valid_coeffs
                    self.write_log(f"Linear model coefficients updated. Factors: {list(self.model_coefficients.keys())}", level=INFO)
                    # Reload/re-validate the "model"
                    self._load_model()
                elif not invalid_found:
                     self.write_log("Model coefficients received but are identical to current ones. No update.", level=DEBUG)

            else:
                self.write_log(f"Invalid type for model_coefficients setting: {type(coeffs)}. Expected dict.", level=WARNING)

        # Ensure model status reflects coefficient presence after update
        self.model_loaded = bool(self.model_coefficients)


    def get_data(self) -> dict:
        """Get the current runtime state."""
        # Get base data (inited, trading, active_orders, etc.)
        data = super(ModelStrategyTemplate, self).get_data()
        # Add/remove model-specific state
        data["model_loaded"] = self.model_loaded # Reflects if coefficients are loaded
        data.pop("model_path", None) # Remove if present from base
        # Do NOT save coefficients in get_data, they are part of parameters/settings
        return data

    def load_data(self, data: dict) -> None:
        """Restore the strategy's runtime state."""
        # Load base data (active orders, etc.)
        super(ModelStrategyTemplate, self).load_data(data)
        # Restore model status (informational)
        self.model_loaded = data.get("model_loaded", bool(self.model_coefficients))

