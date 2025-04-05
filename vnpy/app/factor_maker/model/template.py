from typing import Dict, List, Optional, Any, Union
import polars as pl
import numpy as np
from abc import ABC, abstractmethod
from datetime import datetime
import logging

from .utils.preprocessing import normalize_features, impute_missing_values
from .utils.label_generator import LabelGenerator

logger = logging.getLogger(__name__)

class ModelTemplate(ABC):
    """Base template for factor trading models"""
    
    def __init__(
        self,
        factor_keys: List[str],
        label_generator: Optional[LabelGenerator] = None,
        params: Optional[Dict[str, Any]] = None
    ) -> None:
        """
        Initialize model template
        
        Parameters
        ----------
        factor_keys : List[str]
            List of factor names to use
        label_generator : Optional[LabelGenerator]
            Custom label generator for training data
        params : Optional[Dict[str, Any]]
            Model parameters
        """
        self.factor_keys = factor_keys
        self.label_generator = label_generator or LabelGenerator()
        self.params = params or {}
        
        # Internal storage
        self.feature_data: Dict[str, pl.DataFrame] = {}
        self.label_data: pl.DataFrame = pl.DataFrame()
        self.model: Any = None
        
    def load_features(self, factor_data: Dict[str, pl.DataFrame]) -> None:
        """Load and preprocess factor data"""
        try:
            for factor_key, data in factor_data.items():
                if factor_key in self.factor_keys:
                    processed_data = self._preprocess_features(data)
                    self.feature_data[factor_key] = processed_data
            
            logger.info(f"Loaded data for factors: {list(self.feature_data.keys())}")
            
        except Exception as e:
            logger.error(f"Error loading factor data: {str(e)}")
            raise
            
    def generate_labels(
        self,
        price_data: pl.DataFrame,
        method: str = "returns",
        lookforward_period: int = 1,
        **kwargs
    ) -> None:
        """Generate labels for training"""
        try:
            self.label_data = self.label_generator.generate(
                price_data=price_data,
                method=method,
                lookforward_period=lookforward_period,
                **kwargs
            )
            logger.info(f"Generated labels using method: {method}")
            
        except Exception as e:
            logger.error(f"Error generating labels: {str(e)}")
            raise
            
    def prepare_data(
        self,
        start_time: datetime,
        end_time: datetime
    ) -> tuple[pl.DataFrame, pl.DataFrame]:
        """Prepare feature matrix and label vector"""
        try:
            features = self._combine_features()
            
            # Time filter
            mask = (features["datetime"] >= start_time) & (features["datetime"] <= end_time)
            features = features.filter(mask)
            labels = self.label_data.filter(mask)
            
            # Align data
            features, labels = self._align_data(features, labels)
            return features, labels
            
        except Exception as e:
            logger.error(f"Error preparing training data: {str(e)}")
            raise
    
    @abstractmethod
    def train(
        self,
        features: pl.DataFrame,
        labels: pl.DataFrame,
        **kwargs
    ) -> None:
        """Train the model"""
        pass
    
    @abstractmethod
    def predict(self, features: pl.DataFrame) -> Union[np.ndarray, pl.Series]:
        """Generate predictions"""
        pass
    
    def _preprocess_features(self, data: pl.DataFrame) -> pl.DataFrame:
        """Preprocess factor data"""
        data = impute_missing_values(data)
        data = normalize_features(data)
        return data
        
    def _combine_features(self) -> pl.DataFrame:
        """Combine all factor data into feature matrix"""
        if not self.feature_data:
            raise ValueError("No factor data loaded")
            
        combined = self.feature_data[self.factor_keys[0]].select("datetime")
        for factor_key, data in self.feature_data.items():
            value_col = data.drop("datetime")
            combined = combined.with_columns(
                value_col.rename({c: f"{factor_key}_{c}" for c in value_col.columns})
            )
        return combined
        
    def _align_data(
        self,
        features: pl.DataFrame,
        labels: pl.DataFrame
    ) -> tuple[pl.DataFrame, pl.DataFrame]:
        """Align features and labels by datetime"""
        return features.join(labels, on="datetime", how="inner")

    def save_model(self, path: str) -> None:
        """Save model to file"""
        raise NotImplementedError("save_model not implemented")
        
    def load_model(self, path: str) -> None:
        """Load model from file"""
        raise NotImplementedError("load_model not implemented")
