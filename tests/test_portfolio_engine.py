from vnpy_ctabacktester.portfolio_engine import (
    PortfolioBacktestingEngine,
    PortfolioConfig,
    normalize_weights,
    select_top_symbols,
)


def test_select_top_symbols_filters_non_positive_in_long_only() -> None:
    scores = {
        "A": 0.8,
        "B": 0.2,
        "C": -0.3,
        "D": 0,
    }

    selected = select_top_symbols(scores, top_n=2, long_only=True)

    assert list(selected.keys()) == ["A", "B"]


def test_normalize_weights_sum_to_one() -> None:
    weights = normalize_weights({"A": 2.0, "B": 1.0})

    assert round(sum(weights.values()), 10) == 1.0
    assert weights["A"] > weights["B"]


def test_portfolio_engine_generates_topn_weights() -> None:
    engine = PortfolioBacktestingEngine(config=PortfolioConfig(top_n=2, long_only=True))

    weights = engine.generate_target_weights({"A": 3.0, "B": 2.0, "C": 1.0})

    assert set(weights.keys()) == {"A", "B"}
    assert round(sum(weights.values()), 10) == 1.0
