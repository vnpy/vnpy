import importlib.util
from math import sqrt
from pathlib import Path

module_path = Path(__file__).parents[2] / "vnpy" / "alpha" / "strategy" / "statistics.py"
spec = importlib.util.spec_from_file_location("alpha_strategy_statistics", module_path)
statistics = importlib.util.module_from_spec(spec)
assert spec.loader is not None
spec.loader.exec_module(statistics)


def test_calculate_sharpe_ratio() -> None:
    """Test annualized Sharpe ratio calculation."""
    ratio = statistics.calculate_sharpe_ratio(
        daily_return=0.2,
        return_std=1,
        risk_free=0,
        annual_days=252,
    )

    assert ratio == 0.2 * sqrt(252)


def test_calculate_sortino_ratio() -> None:
    """Test annualized Sortino ratio calculation."""
    ratio = statistics.calculate_sortino_ratio(
        daily_return=0.2,
        downside_std=0.5,
        risk_free=0,
        annual_days=252,
    )

    assert ratio == 0.4 * sqrt(252)


def test_calculate_calmar_ratio() -> None:
    """Test Calmar ratio calculation."""
    ratio = statistics.calculate_calmar_ratio(annual_return=18, max_ddpercent=-12)

    assert ratio == 1.5


def test_risk_metric_zero_denominators() -> None:
    """Test risk metrics return zero when denominator is zero."""
    assert statistics.calculate_sharpe_ratio(1, 0, 0, 252) == 0
    assert statistics.calculate_sortino_ratio(1, 0, 0, 252) == 0
    assert statistics.calculate_calmar_ratio(1, 0) == 0
