# encoding: UTF-8

from __future__ import division

from crrmodel import crrprice, crroutput, crrimpv
from jrmodel import jrprice, jroutput, jrimpv


#----------------------------------------------------------------------
def calculatePrice(underlyingPrice, strikePrice, interestRate, 
                   expiryTime, impv, optionType):
    """定价函数模板"""
    price = 0
    
    return price

#----------------------------------------------------------------------
def calculateGreeks(underlyingPrice, strikePrice, interestRate, 
                    expiryTime, impv, optionType, size):
    """
    希腊值计算函数模板
    size为合约大小，返回的是合约的greeks风险，而非单纯价格的
    """
    price = 0
    delta = 0
    gamma = 0
    theta = 0
    vega = 0
    
    return price, delta, gamma, theta, vega
    
#----------------------------------------------------------------------
def calculateImpv(optionPrice, underlyingPrice, strikePrice, interestRate,
                  expiryTime, optionType):
    """
    波动率计算函数模板
    """
    impv = 0
    
    return impv
    
#calculatePrice = crrprice    
#calculateGreeks = crroutput
#calculateImpv = crrimpv

calculatePrice = jrprice
calculateGreeks = jroutput
calculateImpv = jrimpv
