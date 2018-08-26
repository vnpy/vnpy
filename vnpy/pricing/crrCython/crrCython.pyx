from __future__ import division

import numpy as np
from math import isnan

cimport numpy as np
cimport cython
    
cdef extern from "math.h" nogil:
    double exp(double)
    double sqrt(double)
    double pow(double, double)
    double fmax(double, double)
    double fabs(double)

cdef double STEP_CHANGE = 0.001
cdef double STEP_UP = 1 + STEP_CHANGE
cdef double STEP_DOWN = 1 - STEP_CHANGE
cdef double STEP_DIFF = STEP_CHANGE * 2

cdef double DX_TARGET = 0.00001


#----------------------------------------------------------------------
cdef tuple generateTree(double f, double k, double r, double t, double v, int cp, int n):
    """"""
    cdef double dt = t / n
    cdef double u = exp(v * sqrt(dt))
    cdef double d = 1.0 / u
    cdef double a = 1.0
    
    cdef double p = (a - d) / (u - d)
    cdef double p1 = p / a
    cdef double p2 = (1 - p) / a

    cdef np.ndarray[np.double_t, ndim=2] uTree = np.zeros((n+1, n+1))
    cdef np.ndarray[np.double_t, ndim=2] oTree = np.zeros((n+1, n+1))
    
    cdef int i,j
    
    uTree[0,0] = f

    for i in range(1, n+1):
        uTree[0, i] = uTree[0, i-1] * u
        for j in range(1, i+1):
            uTree[j, i] = uTree[j-1, i-1] * d

    for j in range(n+1):    
        oTree[j, n] = max(0, cp * (uTree[j, n]-k))

    for i in range(n-1,-1,-1):
        for j in range(i+1):
            oTree[j, i] = max((p1 * oTree[j, i+1] + p2 * oTree[j+1, i+1]),
                               cp * (uTree[j, i] - k))                    

    return oTree, uTree

#----------------------------------------------------------------------
cpdef double calculatePrice(double f, double k, double r, double t, double v, int cp, int n=15):
    """"""
    oTree, uTree = generateTree(f, k, r, t, v, cp, n)
    return oTree[0, 0]

#----------------------------------------------------------------------
cpdef double calculateDelta(double f, double k, double r, double t, double v, int cp, int n=15):
    """"""
    price1 = calculatePrice(f*STEP_UP, k, r, t, v, cp, n)
    price2 = calculatePrice(f*STEP_DOWN, k, r, t, v, cp, n)
    delta = (price1 - price2) / (f * STEP_DIFF)
    return delta

#----------------------------------------------------------------------
cpdef double calculateGamma(double f, double k, double r, double t, double v, int cp, int n=15):
    """"""
    delta1 = calculateDelta(f*STEP_UP, k, r, t, v, cp, n)
    delta2 = calculateDelta(f*STEP_DOWN, k, r, t, v, cp, n)
    gamma = (delta1 - delta2) / (f * STEP_DIFF) * pow(f, 2) * 0.0001
    return gamma

#----------------------------------------------------------------------
cpdef double calculateTheta(double f, double k, double r, double t, double v, int cp, int n=15):
    """"""
    price1 = calculatePrice(f, k, r, t*STEP_UP, v, cp, n)
    price2 = calculatePrice(f, k, r, t*STEP_DOWN, v, cp, n)
    theta = -(price1 - price2) / (t * STEP_DIFF * 240)
    return theta

#----------------------------------------------------------------------
cpdef double calculateVega(double f, double k, double r, double t, double v, int cp, int n=15):
    """"""
    vega = calculateOriginalVega(f, k, r, t, v, cp, n) / 100
    return vega

#----------------------------------------------------------------------
cdef double calculateOriginalVega(double f, double k, double r, double t, double v, int cp, int n=15):
    """"""
    price1 = calculatePrice(f, k, r, t, v*STEP_UP, cp, n)
    price2 = calculatePrice(f, k, r, t, v*STEP_DOWN, cp, n)
    vega = (price1 - price2) / (v * STEP_DIFF)
    return vega

#----------------------------------------------------------------------
def calculateGreeks(double f, double k, double r, double t, double v, int cp, int n=15):
    """"""
    cdef double price, delta, gamma, theta, vega
    
    if v <= 0:
        return 0, 0, 0, 0, 0

    price = calculatePrice(f, k, r, t, v, cp, n)
    delta = calculateDelta(f, k, r, t, v, cp, n)
    gamma = calculateGamma(f, k, r, t, v, cp, n)
    theta = calculateTheta(f, k, r, t, v, cp, n)
    vega = calculateVega(f, k, r, t, v, cp, n)

    return price, delta, gamma, theta, vega

#----------------------------------------------------------------------
cpdef double calculateImpv(double price, double f, double k, double r, double t, int cp, int n=15):
    """"""
    cdef double p, v, dx, vega
    
    if price <= 0:
        return 0
    
    meet = False
    
    if cp == 1 and price > (f - k):
        meet = True
    elif cp == -1 and price > (k - f):
        meet = True
    
    if not meet:
        return 0
    
    v = 0.3
    
    try:
        for i in range(50):
            p = calculatePrice(f, k, r, t, v, cp, n)
            vega = calculateOriginalVega(f, k, r, t, v, cp, n)
            
            if not vega:
                break
            
            dx = (price - p) / vega            
            if abs(dx) < DX_TARGET:
                break
            
            v += dx
    except:
        v = 0
        
    if v <= 0:
        return 0
    
    v = round(v, 4)
    return v