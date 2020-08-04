from scipy import stats
from math import log, pow, sqrt, exp
from typing import Tuple

cdf = stats.norm.cdf
pdf = stats.norm.pdf


def calculate_d1(
    s: float,
    k: float,
    r: float,
    t: float,
    v: float
) -> float:
    """Calculate option D1 value"""
    d1: float = (log(s / k) + (0.5 * pow(v, 2)) * t) / (v * sqrt(t))
    return d1


def calculate_price(
    s: float,
    k: float,
    r: float,
    t: float,
    v: float,
    cp: int,
    d1: float = 0.0
) -> float:
    """Calculate option price"""
    # Return option space value if volatility not positive
    if v <= 0:
        return max(0, cp * (s - k))

    if not d1:
        d1: float = calculate_d1(s, k, r, t, v)
    d2: float = d1 - v * sqrt(t)

    price: float = cp * (s * cdf(cp * d1) - k * cdf(cp * d2)) * exp(-r * t)
    return price


def calculate_delta(
    s: float,
    k: float,
    r: float,
    t: float,
    v: float,
    cp: int,
    d1: float = 0.0
) -> float:
    """Calculate option delta"""
    if v <= 0:
        return 0

    if not d1:
        d1: float = calculate_d1(s, k, r, t, v)

    _delta: float = cp * exp(-r * t) * cdf(cp * d1)
    delta: float = _delta * s * 0.01
    return delta


def calculate_gamma(
    s: float,
    k: float,
    r: float,
    t: float,
    v: float,
    d1: float = 0.0
) -> float:
    """Calculate option gamma"""
    if v <= 0:
        return 0

    if not d1:
        d1: float = calculate_d1(s, k, r, t, v)

    _gamma: float = exp(-r * t) * pdf(d1) / (s * v * sqrt(t))
    gamma: float = _gamma * pow(s, 2) * 0.0001

    return gamma


def calculate_theta(
    s: float,
    k: float,
    r: float,
    t: float,
    v: float,
    cp: int,
    d1: float = 0.0,
    annual_days: int = 240
) -> float:
    """Calculate option theta"""
    if v <= 0:
        return 0

    if not d1:
        d1: float = calculate_d1(s, k, r, t, v)
    d2: float = d1 - v * sqrt(t)

    _theta = -s * exp(-r * t) * pdf(d1) * v / (2 * sqrt(t)) \
        + cp * r * s * exp(-r * t) * cdf(cp * d1) \
        - cp * r * k * exp(-r * t) * cdf(cp * d2)
    theta = _theta / annual_days

    return theta


def calculate_vega(
    s: float,
    k: float,
    r: float,
    t: float,
    v: float,
    d1: float = 0.0
) -> float:
    """Calculate option vega(%)"""
    vega: float = calculate_original_vega(s, k, r, t, v, d1) / 100
    return vega


def calculate_original_vega(
    s: float,
    k: float,
    r: float,
    t: float,
    v: float,
    d1: float = 0.0
) -> float:
    """Calculate option vega"""
    if v <= 0:
        return 0

    if not d1:
        d1: float = calculate_d1(s, k, r, t, v)

    vega: float = s * exp(-r * t) * pdf(d1) * sqrt(t)

    return vega


def calculate_greeks(
    s: float,
    k: float,
    r: float,
    t: float,
    v: float,
    cp: int,
    annual_days: int = 240
) -> Tuple[float, float, float, float, float]:
    """Calculate option price and greeks"""
    d1: float = calculate_d1(s, k, r, t, v)
    price: float = calculate_price(s, k, r, t, v, cp, d1)
    delta: float = calculate_delta(s, k, r, t, v, cp, d1)
    gamma: float = calculate_gamma(s, k, r, t, v, d1)
    theta: float = calculate_theta(s, k, r, t, v, cp, d1, annual_days)
    vega: float = calculate_vega(s, k, r, t, v, d1)
    return price, delta, gamma, theta, vega


def calculate_impv(
    price: float,
    s: float,
    k: float,
    r: float,
    t: float,
    cp: int
):
    """Calculate option implied volatility"""
    # Check option price must be positive
    if price <= 0:
        return 0

    # Check if option price meets minimum value (exercise value)
    meet: bool = False

    if cp == 1 and (price > (s - k) * exp(-r * t)):
        meet = True
    elif cp == -1 and (price > k * exp(-r * t) - s):
        meet = True

    # If minimum value not met, return 0
    if not meet:
        return 0

    # Calculate implied volatility with Newton's method
    v: float = 0.01    # Initial guess of volatility

    for i in range(50):
        # Caculate option price and vega with current guess
        p: float = calculate_price(s, k, r, t, v, cp)
        vega: float = calculate_original_vega(s, k, r, t, v, cp)

        # Break loop if vega too close to 0
        if not vega:
            break

        # Calculate error value
        dx: float = (price - p) / vega

        # Check if error value meets requirement
        if abs(dx) < 0.00001:
            break

        # Calculate guessed implied volatility of next round
        v += dx

    # Check end result to be non-negative
    if v <= 0:
        return 0

    # Round to 4 decimal places
    v = round(v, 4)

    return v
