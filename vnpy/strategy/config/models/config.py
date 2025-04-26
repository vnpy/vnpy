from dataclasses import dataclass
from typing import Dict, Literal

@dataclass
class ModelConfig:
    """Model configuration for factor strategies"""
    model_type: Literal["linear", "tree", "neural"] = "linear"
    coefficients: Dict[str, float] = None  # Factor coefficients
    intercept: float = 0.0
    
    def __post_init__(self):
        if self.coefficients is None:
            self.coefficients = {}
