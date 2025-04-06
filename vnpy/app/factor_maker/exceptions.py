from typing import Optional

class FactorCalculationError(Exception):
    """Base exception for factor calculation errors"""
    def __init__(self, message: str, factor_key: Optional[str] = None):
        self.factor_key = factor_key
        super().__init__(f"Factor {factor_key}: {message}" if factor_key else message)

class CircularDependencyError(FactorCalculationError):
    """Raised when circular dependencies are detected"""
    pass

class MemoryError(FactorCalculationError):
    """Raised when memory limits are exceeded"""
    pass

class TimeoutError(FactorCalculationError):
    """Raised when calculation exceeds time limit"""
    pass

class DataValidationError(FactorCalculationError):
    """Raised when input data fails validation"""
    pass
