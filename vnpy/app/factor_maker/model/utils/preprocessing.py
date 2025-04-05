from typing import Dict, List, Optional, Union
import polars as pl
import numpy as np
from datetime import datetime
import logging

logger = logging.getLogger(__name__)

def normalize_features(df: pl.DataFrame) -> pl.DataFrame:
    """
    Normalize features using z-score standardization.
    
    Parameters
    ----------
    df : pl.DataFrame
        Input DataFrame with datetime and feature columns
        
    Returns
    -------
    pl.DataFrame
        Normalized DataFrame
    """
    try:
        # Keep datetime column unchanged
        datetime_col = df.select("datetime")
        
        # Normalize other columns
        numeric_cols = [col for col in df.columns if col != "datetime"]
        normalized = df.select(numeric_cols)
        
        # Z-score normalization
        for col in numeric_cols:
            mean = normalized.select(col).mean()
            std = normalized.select(col).std()
            normalized = normalized.with_columns(
                ((pl.col(col) - mean) / std).alias(col)
            )
            
        # Recombine with datetime
        result = pl.concat([datetime_col, normalized], how="horizontal")
        return result
        
    except Exception as e:
        logger.error(f"Error normalizing features: {str(e)}")
        raise

def impute_missing_values(
    df: pl.DataFrame,
    method: str = "forward_fill",
    max_gap: int = 5
) -> pl.DataFrame:
    """
    Impute missing values in factor data.
    
    Parameters
    ----------
    df : pl.DataFrame
        Input DataFrame with datetime and feature columns
    method : str
        Imputation method ("forward_fill", "backward_fill", or "interpolate")
    max_gap : int
        Maximum gap size to fill
        
    Returns
    -------
    pl.DataFrame
        DataFrame with imputed values
    """
    try:
        # Keep datetime column unchanged
        datetime_col = df.select("datetime")
        
        # Process other columns
        numeric_cols = [col for col in df.columns if col != "datetime"]
        imputed = df.select(numeric_cols)
        
        for col in numeric_cols:
            if method == "forward_fill":
                imputed = imputed.with_columns(
                    pl.col(col).fill_null(strategy="forward", limit=max_gap)
                )
            elif method == "backward_fill":
                imputed = imputed.with_columns(
                    pl.col(col).fill_null(strategy="backward", limit=max_gap)
                )
            elif method == "interpolate":
                imputed = imputed.with_columns(
                    pl.col(col).interpolate()
                )
                
        # Recombine with datetime
        result = pl.concat([datetime_col, imputed], how="horizontal")
        return result
        
    except Exception as e:
        logger.error(f"Error imputing missing values: {str(e)}")
        raise

def remove_outliers(
    df: pl.DataFrame,
    zscore_threshold: float = 3.0
) -> pl.DataFrame:
    """
    Remove outliers using z-score method.
    
    Parameters
    ----------
    df : pl.DataFrame
        Input DataFrame
    zscore_threshold : float
        Z-score threshold for outlier detection
        
    Returns
    -------
    pl.DataFrame
        DataFrame with outliers removed
    """
    try:
        # Keep datetime column unchanged
        datetime_col = df.select("datetime")
        
        # Process other columns
        numeric_cols = [col for col in df.columns if col != "datetime"]
        cleaned = df.select(numeric_cols)
        
        for col in numeric_cols:
            mean = cleaned.select(col).mean()
            std = cleaned.select(col).std()
            zscores = (pl.col(col) - mean) / std
            mask = zscores.abs() <= zscore_threshold
            cleaned = cleaned.filter(mask)
            
        # Recombine with datetime
        result = pl.concat([datetime_col, cleaned], how="horizontal")
        return result
        
    except Exception as e:
        logger.error(f"Error removing outliers: {str(e)}")
        raise
