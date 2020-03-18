from typing import Tuple
import numpy as np

cimport numpy as np
cimport cython

cdef extern from "math.h" nogil:
    double exp(double)
    double sqrt(double)
    double pow(double, double)
    double fmax(double, double)
    double fabs(double)


DEFAULT_STEP = 15


cdef tuple generate_tree(
    double f,
    double k,
    double r,
    double t,
    double v,
    int cp,
    int n
):
    """Generate binomial tree for pricing American option."""
    cdef double dt = t / n
    cdef double u = exp(v * sqrt(dt))
    cdef double d = 1 / u
    cdef double a = 1
    
    cdef int tree_size = n + 1
    cdef np.ndarray[np.double_t, ndim = 2] underlying_tree = np.zeros((tree_size, tree_size))
    cdef np.ndarray[np.double_t, ndim = 2] option_tree = np.zeros((tree_size, tree_size))

    cdef int i, j

    # Calculate risk neutral probability
    cdef double p = (a - d) / (u - d)
    cdef double p1 = p / a
    cdef double p2 = (1 - p) / a

    # Calculate underlying price tree
    underlying_tree[0, 0] = f

    for i in range(1, n + 1):
        underlying_tree[0, i] = underlying_tree[0, i - 1] * u
        for j in range(1, n + 1):
            underlying_tree[j, i] = underlying_tree[j - 1, i - 1] * d

    # Calculate option price tree
    for j in range(n + 1):
        option_tree[j, n] = max(0, cp * (underlying_tree[j, n] - k))

    for i in range(n - 1, -1, -1):
        for j in range(i + 1):
            option_tree[j, i] = max(
                (p1 * option_tree[j, i + 1] + p2 * option_tree[j + 1, i + 1]),
                cp * (underlying_tree[j, i] - k)
            )

    # Return both trees
    return option_tree, underlying_tree


def calculate_price(
    double f,
    double k,
    double r,
    double t,
    double v,
    int cp,
    int n = DEFAULT_STEP
) -> float:
    """Calculate option price"""
    option_tree, underlying_tree = generate_tree(f, k, r, t, v, cp, n)
    return option_tree[0, 0]


def calculate_delta(
    double f,
    double k,
    double r,
    double t,
    double v,
    int cp,
    int n = DEFAULT_STEP
) -> float:
    """Calculate option delta"""
    option_tree, underlying_tree = generate_tree(f, k, r, t, v, cp, n)
    option_price_change = option_tree[0, 1] - option_tree[1, 1]
    underlying_price_change = underlying_tree[0, 1] - underlying_tree[1, 1]
    return option_price_change / underlying_price_change


def calculate_gamma(
    double f,
    double k,
    double r,
    double t,
    double v,
    int cp,
    int n = DEFAULT_STEP
) -> float:
    """Calculate option gamma"""
    option_tree, underlying_tree = generate_tree(f, k, r, t, v, cp, n)

    gamma_delta_1 = (option_tree[0, 2] - option_tree[1, 2]) / \
        (underlying_tree[0, 2] - underlying_tree[1, 2])
    gamma_delta_2 = (option_tree[1, 2] - option_tree[2, 2]) / \
        (underlying_tree[1, 2] - underlying_tree[2, 2])
    gamma = (gamma_delta_1 - gamma_delta_2) / \
        (0.5 * (underlying_tree[0, 2] - underlying_tree[2, 2]))

    return gamma


def calculate_theta(
    double f,
    double k,
    double r,
    double t,
    double v,
    int cp,
    int n = DEFAULT_STEP,
    int annual_days = 240
) -> float:
    """Calcualte option theta"""
    option_tree, underlying_tree = generate_tree(f, k, r, t, v, cp, n)

    dt = t / n
    theta = (option_tree[1, 2] - option_tree[0, 0]) / (2 * dt * annual_days)

    return theta


def calculate_vega(
    double f,
    double k,
    double r,
    double t,
    double v,
    int cp,
    int n = DEFAULT_STEP
) -> float:
    """Calculate option vega(%)"""
    vega = calculate_original_vega(f, k, r, t, v, cp, n) / 100
    return vega


cdef double calculate_original_vega(
    double f,
    double k,
    double r,
    double t,
    double v,
    int cp,
    int n = DEFAULT_STEP
):
    """Calculate option vega"""
    cdef double price_1 = calculate_price(f, k, r, t, v, cp, n)
    cdef double price_2 = calculate_price(f, k, r, t, v * 1.001, cp, n)
    cdef double vega = (price_2 - price_1) / (v * 0.001)
    return vega


def calculate_greeks(
    double f,
    double k,
    double r,
    double t,
    double v,
    int cp,
    int n = DEFAULT_STEP,
    int annual_days = 240
) -> Tuple[float, float, float, float, float]:
    """Calculate option price and greeks"""
    cdef double dt = t / n
    cdef price, delta, gamma, vega, theta
    cdef option_price_change, underlying_price_change
    cdef gamma_delta_1, gamma_delta_2

    option_tree, underlying_tree = generate_tree(f, k, r, t, v, cp, n)
    option_tree_vega, underlying_tree_vega = generate_tree(f, k, r, t, v * 1.001, cp, n)

    # Price
    price = option_tree[0, 0]

    # Delta
    option_price_change = option_tree[0, 1] - option_tree[1, 1]
    underlying_price_change = underlying_tree[0, 1] - underlying_tree[1, 1]
    delta = option_price_change / underlying_price_change

    # Gamma
    gamma_delta_1 = (option_tree[0, 2] - option_tree[1, 2]) / \
        (underlying_tree[0, 2] - underlying_tree[1, 2])
    gamma_delta_2 = (option_tree[1, 2] - option_tree[2, 2]) / \
        (underlying_tree[1, 2] - underlying_tree[2, 2])
    gamma = (gamma_delta_1 - gamma_delta_2) / \
        (0.5 * (underlying_tree[0, 2] - underlying_tree[2, 2]))

    # Theta
    theta = (option_tree[1, 2] - option_tree[0, 0]) / (2 * dt * annual_days)

    # Vega
    vega = (option_tree_vega[0, 0] - option_tree[0, 0]) / (0.001 * v * 100)

    return price, delta, gamma, theta, vega


def calculate_impv(
    double price,
    double f,
    double k,
    double r,
    double t,
    int cp,
    int n = DEFAULT_STEP
) -> float:
    """Calculate option implied volatility"""
    cdef double p, v, dx, vega

    # Check option price must be position
    if price <= 0:
        return 0

    # Check if option price meets minimum value (exercise value)
    meet = False

    if cp == 1 and price > (f - k):
        meet = True
    elif cp == -1 and price > (k - f):
        meet = True

    # If minimum value not met, return 0
    if not meet:
        return 0

    # Calculate implied volatility with Newton's method
    v = 0.3     # Initial guess of volatility

    for i in range(50):
        # Caculate option price and vega with current guess
        p = calculate_price(f, k, r, t, v, cp, n)
        vega = calculate_original_vega(f, k, r, t, v, cp, n)

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
