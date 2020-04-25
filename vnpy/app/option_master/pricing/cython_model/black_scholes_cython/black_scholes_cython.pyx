from typing import Tuple

cdef extern from "math.h" nogil:
    double exp(double)
    double sqrt(double)
    double pow(double, double)
    double log(double)
    double erf(double)
    double fabs(double)


cdef double cdf(double x):
    return 0.5 * (1 + erf(x / sqrt(2.0)))


cdef double pdf(double x):
    # 1 / sqrt(2 * 3.1416) = 0.3989422804014327
    return exp(- pow(x, 2) * 0.5) * 0.3989422804014327


cdef double calculate_d1(double s, double k, double r, double t, double v):
    """Calculate option D1 value"""
    return (log(s / k) + (r + 0.5 * pow(v, 2)) * t) / (v * sqrt(t))


def calculate_price(
    double s,
    double k,
    double r,
    double t,
    double v,
    int cp,
    double d1 = 0.0
) -> float:
    """Calculate option price"""
    cdef double d2, price

    # Return option space value if volatility not positive
    if v <= 0:
        return max(0, cp * (s - k))

    if not d1:
        d1 = calculate_d1(s, k, r, t, v)
    d2 = d1 - v * sqrt(t)

    price = cp * (s * cdf(cp * d1) - k * cdf(cp * d2) * exp(-r * t))
    return price


def calculate_delta(
    double s,
    double k,
    double r,
    double t,
    double v,
    int cp,
    double d1 = 0.0
) -> float:
    """Calculate option delta"""
    cdef _delta, delta

    if v <= 0:
        return 0

    if not d1:
        d1 = calculate_d1(s, k, r, t, v)

    _delta: float = cp * cdf(cp * d1)
    delta: float = _delta * s * 0.01
    return delta


def calculate_gamma(
    double s,
    double k,
    double r,
    double t,
    double v,
    double d1 = 0.0
) -> float:
    """Calculate option gamma"""
    cdef _gamma, gamma

    if v <= 0 or s <= 0 or t<= 0:
        return 0

    if not d1:
        d1 = calculate_d1(s, k, r, t, v)

    _gamma = pdf(d1) / (s * v * sqrt(t))
    gamma = _gamma * pow(s, 2) * 0.0001

    return gamma


def calculate_theta(
    double s,
    double k,
    double r,
    double t,
    double v,
    int cp,
    double d1 = 0.0,
    int annual_days = 240
) -> float:
    """Calculate option theta"""
    cdef double d2, _theta, theta

    if v <= 0:
        return 0

    if not d1:
        d1 = calculate_d1(s, k, r, t, v)
    d2: float = d1 - v * sqrt(t)

    _theta = -s * pdf(d1) * v / (2 * sqrt(t)) \
        - cp * r * k * exp(-r * t) * cdf(cp * d2)
    theta = _theta / annual_days

    return theta


def calculate_vega(
    double s,
    double k,
    double r,
    double t,
    double v,
    double d1 = 0.0
) -> float:
    """Calculate option vega(%)"""
    vega: float = calculate_original_vega(s, k, r, t, v, d1) / 100
    return vega


def calculate_original_vega(
    double s,
    double k,
    double r,
    double t,
    double v,
    double d1 = 0.0
) -> float:
    """Calculate option vega"""
    cdef double vega

    if v <= 0:
        return 0

    if not d1:
        d1 = calculate_d1(s, k, r, t, v)

    vega: float = s * pdf(d1) * sqrt(t)

    return vega


def calculate_greeks(
    double s,
    double k,
    double r,
    double t,
    double v,
    int cp,
    int annual_days = 240,
) -> Tuple[float, float, float, float, float]:
    """Calculate option price and greeks"""
    cdef double d1, price, delta, gamma, theta, vega

    d1 = calculate_d1(s, k, r, t, v)
    
    price = calculate_price(s, k, r, t, v, cp, d1)
    delta = calculate_delta(s, k, r, t, v, cp, d1)
    gamma = calculate_gamma(s, k, r, t, v, d1)
    theta = calculate_theta(s, k, r, t, v, cp, d1, annual_days)
    vega = calculate_vega(s, k, r, t, v, d1)
    
    return price, delta, gamma, theta, vega


def calculate_impv(
    double price,
    double s,
    double k,
    double r,
    double t,
    int cp
):
    """Calculate option implied volatility"""
    cdef bint meet
    cdef double v, p, vega, dx

    # Check option prive must be positive
    if price <= 0:
        return 0

    # Check if option price meets minimum value (exercise value)
    meet = False

    if cp == 1 and (price > (s - k) * exp(-r * t)):
        meet = True
    elif cp == -1 and (price > k * exp(-r * t) - s):
        meet = True

    # If minimum value not met, return 0
    if not meet:
        return 0

    # Calculate implied volatility with Newton's method
    v = 0.3     # Initial guess of volatility

    for i in range(50):
        # Caculate option price and vega with current guess
        p = calculate_price(s, k, r, t, v, cp)
        vega = calculate_original_vega(s, k, r, t, v, cp)

        # Break loop if vega too close to 0
        if not vega:
            break

        # Calculate error value
        dx = (price - p) / vega

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
