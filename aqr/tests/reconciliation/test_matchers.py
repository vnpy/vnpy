from aqr.reconciliation.order_matcher import match_active_orders
from aqr.reconciliation.position_matcher import DiffSeverity, match_positions


def test_position_difference_is_critical() -> None:
    diffs = match_positions({"600519.SSE": 100}, {"600519.SSE": 0})
    assert len(diffs) == 1
    assert diffs[0].severity is DiffSeverity.CRITICAL


def test_external_unknown_order_is_reported() -> None:
    diffs = match_active_orders(set(), {"manual-order-1"})
    assert diffs[0].entity_type == "EXTERNAL_UNKNOWN_ORDER"
    assert diffs[0].severity is DiffSeverity.CRITICAL


def test_equal_snapshots_pass() -> None:
    assert match_positions({"000001.SZSE": 100}, {"000001.SZSE": 100}) == []
    assert match_active_orders({"order-1"}, {"order-1"}) == []
