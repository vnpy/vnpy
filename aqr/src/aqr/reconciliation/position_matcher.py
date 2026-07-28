from __future__ import annotations

from dataclasses import dataclass
from enum import StrEnum


class DiffSeverity(StrEnum):
    INFO = "INFO"
    WARNING = "WARNING"
    CRITICAL = "CRITICAL"


@dataclass(frozen=True, slots=True)
class ReconciliationDiff:
    entity_type: str
    symbol: str | None
    field_name: str
    internal_value: str | None
    gateway_value: str | None
    severity: DiffSeverity


def match_positions(
    internal: dict[str, int], gateway: dict[str, int]
) -> list[ReconciliationDiff]:
    diffs: list[ReconciliationDiff] = []
    for symbol in sorted(internal.keys() | gateway.keys()):
        expected = internal.get(symbol, 0)
        actual = gateway.get(symbol, 0)
        if expected != actual:
            diffs.append(
                ReconciliationDiff(
                    entity_type="POSITION",
                    symbol=symbol,
                    field_name="total_quantity",
                    internal_value=str(expected),
                    gateway_value=str(actual),
                    severity=DiffSeverity.CRITICAL,
                )
            )
    return diffs
