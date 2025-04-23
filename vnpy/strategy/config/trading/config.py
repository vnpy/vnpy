from dataclasses import dataclass
from typing import Dict

@dataclass 
class TradingConfig:
    """Trading parameters configuration"""
    position_multiplier: float = 1.0
    max_pos_per_symbol: float = 1.0
    risk_factor: float = 1.0
    
    def validate(self):
        """Validate trading parameters"""
        assert self.position_multiplier > 0, "Position multiplier must be positive"
        assert 0 < self.max_pos_per_symbol <= 1, "Max position must be between 0 and 1"
        assert 0 < self.risk_factor <= 1, "Risk factor must be between 0 and 1"
