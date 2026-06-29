from math import sqrt


def calculate_sharpe_ratio(
    daily_return: float,
    return_std: float,
    risk_free: float,
    annual_days: int
) -> float:
    """Calculate annualized Sharpe ratio."""
    if not return_std:
        return 0

    daily_risk_free: float = risk_free / sqrt(annual_days)
    return (daily_return - daily_risk_free) / return_std * sqrt(annual_days)


def calculate_sortino_ratio(
    daily_return: float,
    downside_std: float,
    risk_free: float,
    annual_days: int
) -> float:
    """Calculate annualized Sortino ratio."""
    if not downside_std:
        return 0

    daily_risk_free: float = risk_free / sqrt(annual_days)
    return (daily_return - daily_risk_free) / downside_std * sqrt(annual_days)


def calculate_calmar_ratio(annual_return: float, max_ddpercent: float) -> float:
    """Calculate Calmar ratio from annual return and max drawdown percent."""
    if not max_ddpercent:
        return 0

    return annual_return / abs(max_ddpercent)
