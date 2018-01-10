# encoding: UTF-8

'''
Black-Scholes期权定价模型，主要用于标的物为股票的欧式期权的定价

变量说明
s：标的物股票价格
k：行权价
r：无风险利率
t：剩余到期时间（年）
v：隐含波动率
cp：期权类型，+1/-1对应call/put
price：期权价格

出于开发演示的目的，本文件中的希腊值计算基于简单数值差分法，
运算效率一般，实盘中建议使用更高速的算法。

本文件中的希腊值计算结果没有采用传统的模型价格数值，而是采用
了实盘交易中更为实用的百分比变动数值，具体定义如下
delta：当f变动1%时，price的变动
gamma：当f变动1%时，delta的变动
theta：当t变动1天时，price的变动（国内交易日每年240天）
vega：当v涨跌1个点时，price的变动（如从16%涨到17%）
'''

from __future__ import division

from scipy import stats
from math import (log, pow, sqrt, exp)

cdf = stats.norm.cdf


# 计算希腊值和隐含波动率时用的参数
STEP_CHANGE = 0.001
STEP_UP = 1 + STEP_CHANGE
STEP_DOWN = 1 - STEP_CHANGE
STEP_DIFF = STEP_CHANGE * 2

DX_TARGET = 0.00001


#----------------------------------------------------------------------
def calculatePrice(s, k, r, t, v, cp):
    """计算期权价格"""
    # 如果波动率为0，则直接返回期权空间价值
    if v <= 0:
        return max(0, cp * (s - k))

    d1 = (log(s / k) + (r + 0.5 * pow(v, 2)) * t) / (v * sqrt(t))
    d2 = d1 - v * sqrt(t)
    price = cp * (s * cdf(cp * d1) - k * cdf(cp * d2) * exp(-r * t))
    return price

#----------------------------------------------------------------------
def calculateDelta(s, k, r, t, v, cp):
    """计算Delta值"""
    price1 = calculatePrice(s*STEP_UP, k, r, t, v, cp)
    price2 = calculatePrice(s*STEP_DOWN, k, r, t, v, cp)
    delta = (price1 - price2) / (s * STEP_DIFF) * (s * 0.01)
    return delta

#----------------------------------------------------------------------
def calculateGamma(s, k, r, t, v, cp):
    """计算Gamma值"""
    delta1 = calculateDelta(s*STEP_UP, k, r, t, v, cp)
    delta2 = calculateDelta(s*STEP_DOWN, k, r, t, v, cp)
    gamma = (delta1 - delta2) / (s * STEP_DIFF) * pow(s, 2) * 0.0001
    return gamma

#----------------------------------------------------------------------
def calculateTheta(s, k, r, t, v, cp):
    """计算Theta值"""
    price1 = calculatePrice(s, k, r, t*STEP_UP, v, cp)
    price2 = calculatePrice(s, k, r, t*STEP_DOWN, v, cp)
    theta = -(price1 - price2) / (t * STEP_DIFF * 240)
    return theta

#----------------------------------------------------------------------
def calculateVega(s, k, r, t, v, cp):
    """计算Vega值"""
    vega = calculateOriginalVega(s, k, r, t, v, cp) / 100
    return vega

#----------------------------------------------------------------------
def calculateOriginalVega(s, k, r, t, v, cp):
    """计算原始vega值"""    
    price1 = calculatePrice(s, k, r, t, v*STEP_UP, cp)
    price2 = calculatePrice(s, k, r, t, v*STEP_DOWN, cp)
    vega = (price1 - price2) / (v * STEP_DIFF)
    return vega

#----------------------------------------------------------------------
def calculateGreeks(s, k, r, t, v, cp):
    """计算期权的价格和希腊值"""
    price = calculatePrice(s, k, r, t, v, cp)
    delta = calculateDelta(s, k, r, t, v, cp)
    gamma = calculateGamma(s, k, r, t, v, cp)
    theta = calculateTheta(s, k, r, t, v, cp)
    vega = calculateVega(s, k, r, t, v, cp)
    return price, delta, gamma, theta, vega

#----------------------------------------------------------------------
def calculateImpv(price, s, k, r, t, cp):
    """计算隐含波动率"""
    # 检查期权价格必须为正数
    if price <= 0:
        return 0
    
    # 检查期权价格是否满足最小价值（即到期行权价值）
    meet = False
    
    if cp == 1 and (price > (s - k) * exp(-r * t)):
        meet = True
    elif cp == -1 and (price > k * exp(-r * t) - s):
        meet = True
    
    # 若不满足最小价值，则直接返回0
    if not meet:
        return 0
    
    # 采用Newton Raphson方法计算隐含波动率
    v = 0.3     # 初始波动率猜测
    
    for i in range(50):
        # 计算当前猜测波动率对应的期权价格和vega值
        p = calculatePrice(s, k, r, t, v, cp)
        
        vega = calculateOriginalVega(s, k, r, t, v, cp)
        
        # 如果vega过小接近0，则直接返回
        if not vega:
            break
        
        # 计算误差
        dx = (price - p) / vega
        
        # 检查误差是否满足要求，若满足则跳出循环
        if abs(dx) < DX_TARGET:
            break
        
        # 计算新一轮猜测的波动率
        v += dx
        
    # 检查波动率计算结果非负
    if v <= 0:
        return 0
    
    # 保留4位小数
    v = round(v, 4)
    
    return v
    