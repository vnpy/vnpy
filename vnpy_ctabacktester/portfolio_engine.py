from __future__ import annotations

from dataclasses import dataclass


@dataclass
class PortfolioConfig:
    top_n: int = 10
    long_only: bool = True


def sanitize_scores(scores: dict[str, float]) -> dict[str, float]:
    """
    Drop invalid score values and cast valid numbers to float.
    """
    valid: dict[str, float] = {}
    for vt_symbol, value in scores.items():
        if value is None:
            continue
        value = float(value)
        if value != value:  # NaN
            continue
        valid[vt_symbol] = value
    return valid


def select_top_symbols(scores: dict[str, float], top_n: int, long_only: bool = True) -> dict[str, float]:
    """
    Select top symbols by score.
    """
    if top_n <= 0:
        return {}

    cleaned: dict[str, float] = sanitize_scores(scores)
    items: list[tuple[str, float]] = list(cleaned.items())

    if long_only:
        items = [item for item in items if item[1] > 0]

    items.sort(key=lambda item: item[1], reverse=True)
    return dict(items[:top_n])


def normalize_weights(scores: dict[str, float]) -> dict[str, float]:
    """
    Normalize positive scores into weights whose sum equals 1.
    """
    if not scores:
        return {}

    total: float = sum(scores.values())
    if total <= 0:
        return {}

    return {vt_symbol: score / total for vt_symbol, score in scores.items()}


class PortfolioBacktestingEngine:
    """
    Lightweight portfolio allocation core for CTA backtester portfolio mode.
    """

    def __init__(self, config: PortfolioConfig | None = None) -> None:
        self.config: PortfolioConfig = config or PortfolioConfig()

    def generate_target_weights(self, scores: dict[str, float]) -> dict[str, float]:
        selected: dict[str, float] = select_top_symbols(
            scores=scores,
            top_n=self.config.top_n,
            long_only=self.config.long_only,
        )
        return normalize_weights(selected)
