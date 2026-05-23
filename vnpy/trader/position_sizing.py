from __future__ import annotations

from dataclasses import dataclass
from math import floor


@dataclass(frozen=True)
class PositionSizingRequest:
    """Inputs required to convert sizing intent into order volume."""

    mode: str
    target_ratio: float
    risk_per_trade: float
    price: float
    current_volume: float
    equity: float
    fixed_volume: float = 0
    stop_price: float = 0
    atr: float = 0
    atr_multiplier: float = 1
    contract_size: float = 1
    min_volume: float = 0
    volume_step: float = 0
    max_position: float = 0
    max_order_value: float = 0


@dataclass(frozen=True)
class PositionSizingResult:
    """Calculated target and order volume."""

    target_volume: float
    order_volume: float
    order_value: float
    unit_risk: float
    risk_amount: float
    clipped: bool
    reason: str


def calculate_position_size(request: PositionSizingRequest) -> PositionSizingResult:
    """Convert sizing intent into an executable order delta."""

    if request.price <= 0:
        return _zero("invalid price")
    if request.equity <= 0:
        return _zero("invalid equity")
    if request.contract_size <= 0:
        return _zero("invalid contract_size")

    unit_risk = 0.0
    risk_amount = 0.0
    if request.mode == "fixed":
        target_volume = request.current_volume + request.fixed_volume
    elif request.mode == "target_ratio":
        notional = request.equity * request.target_ratio
        target_volume = notional / (request.price * request.contract_size)
    elif request.mode == "risk_per_trade":
        unit_risk = _calculate_unit_risk(request)
        if unit_risk <= 0:
            return _zero("invalid unit_risk")
        risk_amount = request.equity * request.risk_per_trade
        if risk_amount <= 0:
            return _zero("invalid risk_per_trade")
        order_volume = risk_amount / unit_risk
        target_volume = request.current_volume + order_volume
    else:
        return _zero(f"unsupported sizing mode: {request.mode}")

    clipped = False
    reasons: list[str] = []

    if request.max_position > 0 and abs(target_volume) > request.max_position:
        target_volume = _copy_sign(request.max_position, target_volume)
        clipped = True
        reasons.append("max_position")

    target_volume = _round_toward_zero(target_volume, request.volume_step)
    order_volume = target_volume - request.current_volume
    order_volume = _round_toward_zero(order_volume, request.volume_step)

    if request.min_volume > 0 and 0 < abs(order_volume) < request.min_volume:
        return PositionSizingResult(0, 0, 0, unit_risk, risk_amount, True, "below min_volume")

    order_value = abs(order_volume * request.price * request.contract_size)
    if request.max_order_value > 0 and order_value > request.max_order_value:
        clipped_volume = request.max_order_value / (request.price * request.contract_size)
        order_volume = _copy_sign(clipped_volume, order_volume)
        order_volume = _round_toward_zero(order_volume, request.volume_step)
        order_value = abs(order_volume * request.price * request.contract_size)
        clipped = True
        reasons.append("max_order_value")

    if order_volume == 0:
        reason = "already at target" if target_volume == request.current_volume else "zero order"
    else:
        reason = ", ".join(reasons) if reasons else "ok"

    return PositionSizingResult(
        target_volume=target_volume,
        order_volume=order_volume,
        order_value=order_value,
        unit_risk=unit_risk,
        risk_amount=risk_amount,
        clipped=clipped,
        reason=reason,
    )


def _zero(reason: str) -> PositionSizingResult:
    return PositionSizingResult(0, 0, 0, 0, 0, False, reason)


def _calculate_unit_risk(request: PositionSizingRequest) -> float:
    stop_distance = abs(request.price - request.stop_price) if request.stop_price > 0 else 0
    if stop_distance > 0:
        return stop_distance * request.contract_size
    if request.atr > 0 and request.atr_multiplier > 0:
        return request.atr * request.atr_multiplier * request.contract_size
    return 0


def _copy_sign(value: float, signed: float) -> float:
    return value if signed >= 0 else -value


def _round_toward_zero(value: float, step: float) -> float:
    if step <= 0 or value == 0:
        return value
    rounded = floor(abs(value) / step) * step
    return _copy_sign(rounded, value)
