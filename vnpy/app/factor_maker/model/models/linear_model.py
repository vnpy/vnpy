from typing import Union
import polars as pl
import numpy as np
from sklearn.linear_model import LogisticRegression
import joblib

from ..template import ModelTemplate

class LinearFactorModel(ModelTemplate):
    """Linear factor model using logistic regression"""
    
    def __init__(self, factor_keys: List[str], **kwargs):
        super().__init__(factor_keys=factor_keys)
        self.model = LogisticRegression(**kwargs)
        
    def train(
        self,
        features: pl.DataFrame,
        labels: pl.DataFrame,
        **kwargs
    ) -> None:
        """Train logistic regression model"""
        X = features.drop("datetime").to_numpy()
        y = labels.drop("datetime").to_numpy().ravel()
        self.model.fit(X, y)
        
    def predict(self, features: pl.DataFrame) -> Union[np.ndarray, pl.Series]:
        """Generate predictions"""
        X = features.drop("datetime").to_numpy()
        return self.model.predict_proba(X)[:, 1]
        
    def save_model(self, path: str) -> None:
        """Save model using joblib"""
        joblib.dump(self.model, path)
        
    def load_model(self, path: str) -> None:
        """Load model using joblib"""
        self.model = joblib.load(path)
