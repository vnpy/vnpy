from __future__ import annotations

from tools.chan_runtime_diagnostics import (
    classify_runtime_gap,
    extract_strategy_order_lines,
    is_dust_position,
)


def test_is_dust_position_detects_tiny_residual() -> None:
    assert is_dust_position(-6.938893903907228e-18, 1e-8) is True
    assert is_dust_position(0.01, 1e-8) is False


def test_extract_strategy_order_lines_filters_chan_orders() -> None:
    lines = extract_strategy_order_lines(
        "\n".join(
            [
                "noise",
                "委托下单 -> OKX：OrderRequest(reference='CtaStrategy_Chan_Auto')",
                "委托下单 -> OKX：OrderRequest(reference='CtaStrategy_Other')",
            ]
        ),
        "Chan_Auto",
    )

    assert lines == ["委托下单 -> OKX：OrderRequest(reference='CtaStrategy_Chan_Auto')"]


def test_classify_runtime_gap_flags_dust_position_blocker() -> None:
    diagnosis = classify_runtime_gap(
        pos=-6.938893903907228e-18,
        position_epsilon=1e-8,
        live_order_count=2,
        replay_buy_count=21,
        latest_error="",
    )

    assert diagnosis["status"] == "execution_blocked"
    assert any("dust position" in reason for reason in diagnosis["reasons"])


def test_classify_runtime_gap_flags_signal_scarcity() -> None:
    diagnosis = classify_runtime_gap(
        pos=0,
        position_epsilon=1e-8,
        live_order_count=0,
        replay_buy_count=0,
        latest_error="",
    )

    assert diagnosis["status"] == "signal_scarcity"
