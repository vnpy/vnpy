from __future__ import annotations

from vnpy.trader.position_sizing import PositionSizingRequest, calculate_position_size


def test_calculates_long_target_from_flat() -> None:
    result = calculate_position_size(
        PositionSizingRequest(
            mode="target_ratio",
            target_ratio=0.05,
            risk_per_trade=0,
            price=100_000,
            current_volume=0,
            equity=10_000,
            contract_size=1,
        )
    )

    assert result.target_volume == 0.005
    assert result.order_volume == 0.005
    assert result.order_value == 500
    assert result.clipped is False
    assert result.reason == "ok"


def test_calculates_flat_target_from_long() -> None:
    result = calculate_position_size(
        PositionSizingRequest(
            mode="target_ratio",
            target_ratio=0,
            risk_per_trade=0,
            price=100_000,
            current_volume=0.005,
            equity=10_000,
        )
    )

    assert result.target_volume == 0
    assert result.order_volume == -0.005


def test_calculates_short_target_from_flat() -> None:
    result = calculate_position_size(
        PositionSizingRequest(
            mode="target_ratio",
            target_ratio=-0.05,
            risk_per_trade=0,
            price=100_000,
            current_volume=0,
            equity=10_000,
        )
    )

    assert result.target_volume == -0.005
    assert result.order_volume == -0.005


def test_calculates_zero_when_already_at_target() -> None:
    result = calculate_position_size(
        PositionSizingRequest(
            mode="target_ratio",
            target_ratio=0.05,
            risk_per_trade=0,
            price=100_000,
            current_volume=0.005,
            equity=10_000,
        )
    )

    assert result.order_volume == 0
    assert result.order_value == 0
    assert result.reason == "already at target"


def test_clips_target_by_max_position() -> None:
    result = calculate_position_size(
        PositionSizingRequest(
            mode="target_ratio",
            target_ratio=0.20,
            risk_per_trade=0,
            price=100_000,
            current_volume=0,
            equity=10_000,
            max_position=0.01,
        )
    )

    assert result.target_volume == 0.01
    assert result.order_volume == 0.01
    assert result.clipped is True
    assert "max_position" in result.reason


def test_clips_order_by_max_order_value() -> None:
    result = calculate_position_size(
        PositionSizingRequest(
            mode="target_ratio",
            target_ratio=0.20,
            risk_per_trade=0,
            price=100_000,
            current_volume=0,
            equity=10_000,
            max_order_value=500,
        )
    )

    assert result.target_volume == 0.02
    assert result.order_volume == 0.005
    assert result.order_value == 500
    assert result.clipped is True
    assert "max_order_value" in result.reason


def test_rejects_order_below_min_volume() -> None:
    result = calculate_position_size(
        PositionSizingRequest(
            mode="target_ratio",
            target_ratio=0.001,
            risk_per_trade=0,
            price=100_000,
            current_volume=0,
            equity=10_000,
            min_volume=0.001,
        )
    )

    assert result.target_volume == 0
    assert result.order_volume == 0
    assert "min_volume" in result.reason


def test_rounds_volume_step_toward_zero() -> None:
    result = calculate_position_size(
        PositionSizingRequest(
            mode="target_ratio",
            target_ratio=0.055,
            risk_per_trade=0,
            price=100_000,
            current_volume=0,
            equity=10_000,
            volume_step=0.001,
        )
    )

    assert result.target_volume == 0.005
    assert result.order_volume == 0.005


def test_rejects_invalid_price_or_equity() -> None:
    price_result = calculate_position_size(
        PositionSizingRequest(
            mode="target_ratio",
            target_ratio=0.05,
            risk_per_trade=0,
            price=0,
            current_volume=0,
            equity=10_000,
        )
    )
    equity_result = calculate_position_size(
        PositionSizingRequest(
            mode="target_ratio",
            target_ratio=0.05,
            risk_per_trade=0,
            price=100_000,
            current_volume=0,
            equity=0,
        )
    )

    assert price_result.order_volume == 0
    assert "price" in price_result.reason
    assert equity_result.order_volume == 0
    assert "equity" in equity_result.reason


def test_calculates_risk_per_trade_from_stop_distance() -> None:
    result = calculate_position_size(
        PositionSizingRequest(
            mode="risk_per_trade",
            target_ratio=0,
            risk_per_trade=0.01,
            price=100_000,
            stop_price=98_000,
            current_volume=0,
            equity=10_000,
        )
    )

    assert result.order_volume == 0.05
    assert result.unit_risk == 2_000
    assert result.risk_amount == 100


def test_calculates_risk_per_trade_from_atr_fallback() -> None:
    result = calculate_position_size(
        PositionSizingRequest(
            mode="risk_per_trade",
            target_ratio=0,
            risk_per_trade=0.01,
            price=100_000,
            atr=1_000,
            atr_multiplier=2,
            current_volume=0,
            equity=10_000,
        )
    )

    assert result.order_volume == 0.05
    assert result.unit_risk == 2_000


def test_rejects_risk_per_trade_without_unit_risk() -> None:
    result = calculate_position_size(
        PositionSizingRequest(
            mode="risk_per_trade",
            target_ratio=0,
            risk_per_trade=0.01,
            price=100_000,
            current_volume=0,
            equity=10_000,
        )
    )

    assert result.order_volume == 0
    assert "unit_risk" in result.reason


def test_fixed_mode_uses_fixed_volume_delta() -> None:
    result = calculate_position_size(
        PositionSizingRequest(
            mode="fixed",
            target_ratio=0,
            risk_per_trade=0,
            price=100,
            current_volume=2,
            equity=10_000,
            fixed_volume=3,
        )
    )

    assert result.target_volume == 5
    assert result.order_volume == 3
    assert result.order_value == 300
