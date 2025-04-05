from typing import Dict, List, Optional, Any, Type
import polars as pl
import numpy as np
import logging
from datetime import datetime
from abc import ABC, abstractmethod

from vnpy.event import Event, EventEngine
from vnpy.trader.engine import BaseEngine, MainEngine
from vnpy.trader.object import FactorData
from vnpy.app.factor_maker.template import FactorTemplate
from vnpy.app.factor_maker.base import APP_NAME
from .utils.preprocessing import normalize_features, impute_missing_values
from .utils.label_generator import LabelGenerator

class ModelEngine(BaseEngine):
    def __init__(
        self, 
        main_engine: MainEngine,
        event_engine: EventEngine,
        label_generator: Optional[LabelGenerator] = None
    ) -> None:
        """Initialize ModelEngine"""
        super().__init__(main_engine, event_engine, APP_NAME)
        
        self.factors: Dict[str, FactorTemplate] = {}
        self.factor_data: Dict[str, pl.DataFrame] = {}
        self.label_data: pl.DataFrame = pl.DataFrame()
        self.label_generator = label_generator or LabelGenerator()
        
        self.logger = logging.getLogger("ModelEngine")
        
    def add_factor(self, factor: FactorTemplate) -> None:
        """Add a factor to the model engine"""
        self.factors[factor.factor_key] = factor
        self.logger.info(f"Added factor: {factor.factor_key}")
        
    def load_factor_data(self, factor_data: Dict[str, pl.DataFrame]) -> None:
        """Load factor data from backtesting or live calculation"""
        try:
            # Validate and preprocess factor data
            for factor_key, data in factor_data.items():
                assert isinstance(data, pl.DataFrame), f"Factor data must be polars DataFrame: {factor_key}"
                assert "datetime" in data.columns, f"Factor data must contain datetime column: {factor_key}"
                
                # Preprocess factor data
                preprocessed_data = self._preprocess_factor_data(data)
                self.factor_data[factor_key] = preprocessed_data
                
            self.logger.info(f"Loaded factor data for {len(factor_data)} factors")
            
        except Exception as e:
            self.logger.error(f"Error loading factor data: {str(e)}")
            raise
            
    def generate_labels(
        self, 
        method: str = "returns",
        lookforward_period: int = 1,
        **kwargs
    ) -> None:
        """Generate labels for training"""
        try:
            # Get price data from memory
            price_data = self.main_engine.get_price_data()
            
            # Generate labels
            self.label_data = self.label_generator.generate(
                price_data=price_data,
                method=method,
                lookforward_period=lookforward_period,
                **kwargs
            )
            self.logger.info(f"Generated labels using method: {method}")
            
        except Exception as e:
            self.logger.error(f"Error generating labels: {str(e)}")
            raise
            
    def prepare_training_data(
        self,
        start_time: datetime,
        end_time: datetime
    ) -> tuple[pl.DataFrame, pl.DataFrame]:
        """Prepare feature matrix and label vector for training"""
        try:
            # Combine all factor data
            features = self._combine_factor_data()
            
            # Filter by time range
            mask = (features["datetime"] >= start_time) & (features["datetime"] <= end_time)
            features = features.filter(mask)
            labels = self.label_data.filter(mask)
            
            # Align features and labels
            features, labels = self._align_data(features, labels)
            
            return features, labels
            
        except Exception as e:
            self.logger.error(f"Error preparing training data: {str(e)}")
            raise
            
    def _preprocess_factor_data(self, data: pl.DataFrame) -> pl.DataFrame:
        """Preprocess factor data"""
        # Handle missing values
        data = impute_missing_values(data)
        
        # Normalize features
        data = normalize_features(data)
        
        return data
        
    def _combine_factor_data(self) -> pl.DataFrame:
        """Combine all factor data into a single feature matrix"""
        if not self.factor_data:
            raise ValueError("No factor data loaded")
            
        # Start with datetime column
        combined = self.factor_data[list(self.factor_data.keys())[0]].select("datetime")
        
        # Add each factor as a column
        for factor_key, data in self.factor_data.items():
            value_col = data.drop("datetime")
            combined = combined.with_columns(value_col.rename({c: f"{factor_key}_{c}" for c in value_col.columns}))
            
        return combined
        
    def _align_data(
        self, 
        features: pl.DataFrame,
        labels: pl.DataFrame
    ) -> tuple[pl.DataFrame, pl.DataFrame]:
        """Align features and labels by datetime"""
        return features.join(labels, on="datetime", how="inner")
