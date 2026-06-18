from datetime import datetime

import polars as pl
import pytest


def test_stretch_research_config_defaults_and_notice() -> None:
    from vnpy.alpha.research import (
        STRETCH_RESEARCH_STRESS_SCENARIOS,
        STRETCH_RESEARCH_VALIDATION_SEGMENTS,
        StretchResearchConfig,
    )

    config = StretchResearchConfig()

    assert config.target_mode == "stretch_research"
    assert config.annual_return_stretch == 10.0
    assert config.max_drawdown_fail == 0.65
    assert config.benchmark == "CSI1000"
    assert config.rebalance_frequency == "weekly"
    assert "research/simulation" in config.result_label
    assert "\u7814\u7a76/\u6a21\u62df\u76d8" in config.result_label
    assert "guaranteed" not in config.disclaimer.lower()
    assert "\u4fdd\u8bc1\u6536\u76ca" not in config.disclaimer
    assert config.research_acceptance_targets == (
        "excess_return",
        "rank_ic",
        "max_drawdown",
        "turnover_rate",
        "stability",
    )
    assert STRETCH_RESEARCH_VALIDATION_SEGMENTS == (
        "in_sample",
        "out_of_sample",
        "walk_forward",
    )
    assert STRETCH_RESEARCH_STRESS_SCENARIOS == (
        "double_cost",
        "turnover_limit",
        "limit_price_no_fill",
        "suspension",
        "market_crash",
    )


def test_rank_ic_is_average_daily_spearman_correlation() -> None:
    from vnpy.alpha.research import calculate_rank_ic

    signal_df = pl.DataFrame(
        {
            "datetime": [
                datetime(2024, 1, 1),
                datetime(2024, 1, 1),
                datetime(2024, 1, 1),
                datetime(2024, 1, 2),
                datetime(2024, 1, 2),
                datetime(2024, 1, 2),
            ],
            "vt_symbol": ["A", "B", "C", "A", "B", "C"],
            "signal": [1.0, 2.0, 3.0, 3.0, 2.0, 1.0],
            "label": [1.0, 2.0, 3.0, 1.0, 2.0, 3.0],
        }
    )

    assert calculate_rank_ic(signal_df) == pytest.approx(0.0)


def test_cost_sensitivity_and_capacity_are_derived_from_inputs() -> None:
    from vnpy.alpha.research import (
        estimate_cost_sensitivity,
        estimate_single_stock_capacity,
    )

    sensitivity = estimate_cost_sensitivity(
        total_return=100.0,
        turnover_rate=5.0,
        cost_rates={"base": 0.001, "double_cost": 0.002},
    )
    capacity = estimate_single_stock_capacity(
        average_turnover=12_000_000,
        max_participation_rate=0.1,
        position_weight=0.06,
    )

    assert sensitivity == {"base": pytest.approx(99.5), "double_cost": pytest.approx(99.0)}
    assert capacity == pytest.approx(20_000_000)


def test_stretch_research_report_flags_failed_drawdown_without_acceptance_promise() -> None:
    from vnpy.alpha.research import (
        STRETCH_RESEARCH_REVIEW_CHECKS,
        STRETCH_RESEARCH_STRESS_SCENARIOS,
        STRETCH_RESEARCH_VALIDATION_SEGMENTS,
        StretchResearchConfig,
        build_stretch_research_report,
    )

    report = build_stretch_research_report(
        statistics={
            "annual_return": 1200.0,
            "total_return": 250.0,
            "max_ddpercent": -66.0,
            "max_drawdown_duration": 45,
        },
        rank_ic=0.08,
        excess_return=0.35,
        excess_drawdown=-0.18,
        turnover_rate=5.0,
        single_stock_capacity=20_000_000,
        cost_sensitivity={"base": 249.5, "double_cost": 249.0},
        config=StretchResearchConfig(),
    )

    required_metrics = {
        "annual_return",
        "total_return",
        "max_drawdown",
        "drawdown_recovery_period",
        "rank_ic",
        "excess_return",
        "excess_drawdown",
        "turnover_rate",
        "single_stock_capacity",
        "cost_sensitivity",
    }
    required_checks = {
        "lookahead_bias",
        "survivorship_bias",
        "adjustment_error",
        "component_history_leakage",
        "limit_price_fill_assumption",
        "overfitting",
    }

    assert report["target"]["mode"] == "stretch_research"
    assert report["target"]["annual_return_stretch"] == 10.0
    assert report["target"]["stretch_hit"] is True
    assert report["risk"]["max_drawdown_failed"] is True
    assert report["risk"]["status"] == "failed"
    assert report["status"] == "research_failed"
    assert required_metrics <= set(report["metrics"])
    assert required_checks <= set(report["review_checks"])
    assert required_checks <= set(STRETCH_RESEARCH_REVIEW_CHECKS)
    assert report["target"]["research_acceptance_targets"] == (
        "excess_return",
        "rank_ic",
        "max_drawdown",
        "turnover_rate",
        "stability",
    )
    assert report["validation_segments"] == STRETCH_RESEARCH_VALIDATION_SEGMENTS
    assert report["stress_scenarios"] == STRETCH_RESEARCH_STRESS_SCENARIOS

    report_text = repr(report)
    assert "guaranteed" not in report_text.lower()
    assert "\u4fdd\u8bc1\u6536\u76ca" not in report_text
