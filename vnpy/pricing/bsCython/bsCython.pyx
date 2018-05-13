from __future__ import division

DX_TARGET = 0.00001



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
    return exp(- pow(x, 2) / 2) / sqrt(2 * 3.1416)

cdef double calculateD1(double s, double k, double r, double t, double v):
    return (log(s / k) + (r + 0.5 * pow(v, 2)) * t) / (v * sqrt(t))


#----------------------------------------------------------------------
def calculatePrice(double s, double k, double r, double t, double v, int cp):
    """"""
    cdef double d1, d2, price
    
    if v <= 0:
        return max(0, cp * (s - k))

    d1 = calculateD1(s, k, r, t, v)
    d2 = d1 - v * sqrt(t)
    price = cp * (s * cdf(cp * d1) - k * cdf(cp * d2) * exp(-r * t))

    return price

#----------------------------------------------------------------------
def calculateDelta(double s, double k, double r, double t, double v, int cp):
    """"""
    cdef double d1, delta
    
    if v <= 0:
        return 0
    
    d1 = calculateD1(s, k, r, t, v)
    delta = cp * cdf(cp * d1)
    delta = delta * s * 0.01

    return delta

#----------------------------------------------------------------------
def calculateGamma(double s, double k, double r, double t, double v, int cp):
    """"""
    cdef double d1, gamma
    
    if v <= 0:
        return 0    
    
    d1 = calculateD1(s, k, r, t, v)
    gamma = pdf(d1) / (s * v * sqrt(t))
    gamma = gamma * pow(s, 2) * 0.0001
    
    return gamma

#----------------------------------------------------------------------
def calculateTheta(double s, double k, double r, double t, double v, int cp):
    """"""
    cdef double d1, d2, theta
    
    if v <= 0:
        return 0    
    
    d1 = calculateD1(s, k, r, t, v)
    d2 = d1 - v * sqrt(t)
    theta = (-0.5 * s * pdf(d1) * v / sqrt(t) -
            cp * r * k * exp(-r * t) * cdf(cp * d2))
    theta = theta / 240
    return theta

#----------------------------------------------------------------------
def calculateVega(double s, double k, double r, double t, double v, int cp):
    """"""
    vega = calculateOriginalVega(s, k, r, t, v, cp) / 100
    return vega

#----------------------------------------------------------------------
def calculateOriginalVega(double s, double k, double r, double t, double v, int cp):
    """"""    
    cdef double d1, vega
    
    if v <= 0:
        return 0  
        
    d1 = calculateD1(s, k, r, t, v)
    vega = s * pdf(d1) * sqrt(t)

    return vega

#----------------------------------------------------------------------
def calculateGreeks(double s, double k, double r, double t, double v, int cp):
    """"""
    price = calculatePrice(s, k, r, t, v, cp)
    delta = calculateDelta(s, k, r, t, v, cp)
    gamma = calculateGamma(s, k, r, t, v, cp)
    theta = calculateTheta(s, k, r, t, v, cp)
    vega = calculateVega(s, k, r, t, v, cp)
    return price, delta, gamma, theta, vega

#----------------------------------------------------------------------
def calculateImpv(price, s, k, r, t, cp):
    """"""
    if price <= 0:
        return 0
    
    meet = False
    
    if cp == 1 and (price > (s - k) * exp(-r * t)):
        meet = True
    elif cp == -1 and (price > k * exp(-r * t) - s):
        meet = True
    
    if not meet:
        return 0
    
    v = 0.3
    
    for i in range(50):
        p = calculatePrice(s, k, r, t, v, cp)
        
        vega = calculateOriginalVega(s, k, r, t, v, cp)
        
        if not vega:
            break
        
        dx = (price - p) / vega
        
        if abs(dx) < DX_TARGET:
            break
        
        v += dx
        
    if v <= 0:
        return 0
    
    v = round(v, 4)
    
    return v
    