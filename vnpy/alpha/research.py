from dataclasses import dataclass
from typing import Any

import numpy as np
import polars as pl


STRETCH_RESEARCH_REVIEW_CHECKS: tuple[str, ...] = (
    "lookahead_bias",
    "survivorship_bias",
    "adjustment_error",
    "component_history_leakage",
    "limit_price_fill_assumption",
    "overfitting",
)

STRETCH_RESEARCH_VALIDATION_SEGMENTS: tuple[str, ...] = (
    "in_sample",
    "out_of_sample",
    "walk_forward",
)

STRETCH_RESEARCH_STRESS_SCENARIOS: tuple[str, ...] = (
    "double_cost",
    "turnover_limit",
    "limit_price_no_fill",
    "suspension",
    "market_crash",
)


@dataclass(frozen=True)
class StretchResearchConfig:
    """Configuration for stretch-target alpha research."""

    target_mode: str = "stretch_research"
    annual_return_stretch: float = 10.0
    max_drawdown_fail: float = 0.65
    benchmark: str = "CSI1000"
    rebalance_frequency: str = "weekly"
    result_label: str = "research/simulation - \u7814\u7a76/\u6a21\u62df\u76d8"
    disclaimer: str = "Stretch research target only; not investment advice or a promised return."
    research_acceptance_targets: tuple[str, ...] = (
        "excess_return",
        "rank_ic",
        "max_drawdown",
        "turnover_rate",
        "stability",
    )


def _rank_values(values: np.ndarray) -> np.ndarray:
    """Return average ranks for an array, using one-based ranks."""
    order: np.ndarray = np.argsort(values, kind="mergesort")
    sorted_values: np.ndarray = values[order]
    ranks: np.ndarray = np.empty(len(values), dtype=float)

    start: int = 0
    while start < len(sorted_values):
        end: int = start + 1
        while end < len(sorted_values) and sorted_values[end] == sorted_values[start]:
            end += 1

        average_rank: float = (start + end - 1) / 2 + 1
        ranks[order[start:end]] = average_rank
        start = end

    return ranks


def _correlate(left: np.ndarray, right: np.ndarray) -> float | None:
    """Calculate Pearson correlation for two numeric arrays."""
    left_centered: np.ndarray = left - left.mean()
    right_centered: np.ndarray = right - right.mean()

    denominator: float = float(np.sqrt(np.sum(left_centered**2) * np.sum(right_centered**2)))
    if not denominator:
        return None

    return float(np.sum(left_centered * right_centered) / denominator)


def calculate_rank_ic(
    signal_df: pl.DataFrame,
    signal_col: str = "signal",
    label_col: str = "label",
    datetime_col: str = "datetime",
) -> float:
    """Calculate mean daily Spearman rank IC from signal and label columns."""
    if signal_df.is_empty():
        return 0.0

    correlations: list[float] = []

    for _, group_df in signal_df.group_by(datetime_col, maintain_order=True):
        signal: np.ndarray = group_df[signal_col].to_numpy()
        label: np.ndarray = group_df[label_col].to_numpy()

        valid_mask: np.ndarray = np.isfinite(signal) & np.isfinite(label)
        if valid_mask.sum() < 2:
            continue

        signal_rank: np.ndarray = _rank_values(signal[valid_mask])
        label_rank: np.ndarray = _rank_values(label[valid_mask])
        correlation: float | None = _correlate(signal_rank, label_rank)
        if correlation is not None:
            correlations.append(correlation)

    if not correlations:
        return 0.0

    return float(np.mean(correlations))


def estimate_cost_sensitivity(
    total_return: float,
    turnover_rate: float,
    cost_rates: dict[str, float],
) -> dict[str, float]:
    """Estimate return after applying alternative trading cost assumptions."""
    return {
        name: total_return - turnover_rate * cost_rate * 100
        for name, cost_rate in cost_rates.items()
    }


def estimate_single_stock_capacity(
    average_turnover: float,
    max_participation_rate: float,
    position_weight: float,
) -> float:
    """Estimate portfolio capital supported by one stock position."""
    if position_weight <= 0:
        return 0.0

    return average_turnover * max_participation_rate / position_weight


def build_stretch_research_report(
    statistics: dict[str, Any],
    rank_ic: float,
    excess_return: float,
    excess_drawdown: float,
    turnover_rate: float,
    single_stock_capacity: float,
    cost_sensitivity: dict[str, float],
    config: StretchResearchConfig | None = None,
) -> dict[str, Any]:
    """Build a research/simulation report for stretch-target alpha research."""
    if config is None:
        config = StretchResearchConfig()

    annual_return: float = float(statistics.get("annual_return", 0))
    max_ddpercent: float = float(statistics.get("max_ddpercent", 0))
    max_drawdown_ratio: float = abs(max_ddpercent) / 100
    stretch_hit: bool = annual_return >= config.annual_return_stretch * 100
    drawdown_failed: bool = max_drawdown_ratio >= config.max_drawdown_fail

    status: str = "research_failed" if drawdown_failed else "research_review_required"

    return {
        "label": config.result_label,
        "disclaimer": config.disclaimer,
        "target": {
            "mode": config.target_mode,
            "annual_return_stretch": config.annual_return_stretch,
            "stretch_hit": stretch_hit,
            "benchmark": config.benchmark,
            "rebalance_frequency": config.rebalance_frequency,
            "research_acceptance_targets": config.research_acceptance_targets,
        },
        "metrics": {
            "annual_return": annual_return,
            "total_return": float(statistics.get("total_return", 0)),
            "max_drawdown": max_ddpercent,
            "drawdown_recovery_period": statistics.get("max_drawdown_duration", 0),
            "rank_ic": rank_ic,
            "excess_return": excess_return,
            "excess_drawdown": excess_drawdown,
            "turnover_rate": turnover_rate,
            "single_stock_capacity": single_stock_capacity,
            "cost_sensitivity": cost_sensitivity,
        },
        "risk": {
            "max_drawdown_fail": config.max_drawdown_fail,
            "max_drawdown_failed": drawdown_failed,
            "status": "failed" if drawdown_failed else "review_required",
        },
        "review_checks": STRETCH_RESEARCH_REVIEW_CHECKS,
        "validation_segments": STRETCH_RESEARCH_VALIDATION_SEGMENTS,
        "stress_scenarios": STRETCH_RESEARCH_STRESS_SCENARIOS,
        "status": status,
    }
