# encoding: UTF-8

from __future__ import division

'''
Cox-Ross-Rubinstein二叉树期权定价模型，主要用于标的物为期货的美式期权的定价

变量说明
f：标的物期货价格
k：行权价
r：无风险利率
t：剩余到期时间（年）
v：隐含波动率
cp：期权类型，+1/-1对应call/put
n: 二叉树高度
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

import numpy as np
from math import (isnan, exp, sqrt, pow)


# 计算希腊值和隐含波动率时用的参数
STEP_CHANGE = 0.001
STEP_UP = 1 + STEP_CHANGE
STEP_DOWN = 1 - STEP_CHANGE
STEP_DIFF = STEP_CHANGE * 2

DX_TARGET = 0.00001



#----------------------------------------------------------------------
def generateTree(f, k, r, t, v, cp, n):
    """生成二叉树"""
    dt = t / n 
    u = exp(v * sqrt(dt))
    d = 1 / u
    a = 1                       # 针对期货期权a应当设为1
    uTree = np.zeros((n+1,n+1))
    oTree = np.zeros((n+1,n+1))

    # 计算风险平价概率
    p = (a - d) / (u - d)
    p1 = p / a
    p2 = (1 - p) / a
    
    # 计算标的树
    uTree[0, 0] = f

    for i in range(1, n+1):
        uTree[0, i] = uTree[0, i-1] * u
        for j in range(1, i+1):
            uTree[j, i] = uTree[j-1, i-1] * d

    # 计算期权树
    for j in range(n+1):
        oTree[j, n] = max(0, cp * (uTree[j, n]-k))

    for i in range(n-1,-1,-1):
        for j in range(i+1):
            oTree[j, i] = max((p1 * oTree[j, i+1] + p2 * oTree[j+1, i+1]),    # 美式期权存续价值
                               cp * (uTree[j, i] - k))                        # 美式期权行权价值

    # 返回期权树和标的物树结果
    return oTree, uTree
    
#----------------------------------------------------------------------
def calculatePrice(f, k, r, t, v, cp, n=15):
    """计算期权价格"""
    oTree, uTree = generateTree(f, k, r, t, v, cp, n)
    return oTree[0, 0]

#----------------------------------------------------------------------
def calculateDelta(f, k, r, t, v, cp, n=15):
    """计算Delta值"""
    price1 = calculatePrice(f*STEP_UP, k, r, t, v, cp, n)
    price2 = calculatePrice(f*STEP_DOWN, k, r, t, v, cp, n)
    delta = (price1 - price2) / (f * STEP_DIFF) * (f * 0.01)
    return delta

#----------------------------------------------------------------------
def calculateGamma(f, k, r, t, v, cp, n=15):
    """计算Gamma值"""
    delta1 = calculateDelta(f*STEP_UP, k, r, t, v, cp, n)
    delta2 = calculateDelta(f*STEP_DOWN, k, r, t, v, cp, n)
    gamma = (delta1 - delta2) / (f * STEP_DIFF) * pow(f, 2) * 0.0001
    return gamma

#----------------------------------------------------------------------
def calculateTheta(f, k, r, t, v, cp, n=15):
    """计算Theta值"""
    price1 = calculatePrice(f, k, r, t*STEP_UP, v, cp, n)
    price2 = calculatePrice(f, k, r, t*STEP_DOWN, v, cp, n)
    theta = -(price1 - price2) / (t * STEP_DIFF * 240)
    return theta

#----------------------------------------------------------------------
def calculateVega(f, k, r, t, v, cp, n=15):
    """计算Vega值"""
    vega = calculateOriginalVega(f, k, r, t, v, cp, n) / 100
    return vega

#----------------------------------------------------------------------
def calculateOriginalVega(f, k, r, t, v, cp, n=15):
    """计算原始vega值"""    
    price1 = calculatePrice(f, k, r, t, v*STEP_UP, cp, n)
    price2 = calculatePrice(f, k, r, t, v*STEP_DOWN, cp, n)
    vega = (price1 - price2) / (v * STEP_DIFF)
    return vega

#----------------------------------------------------------------------
def calculateGreeks(f, k, r, t, v, cp, n=15):
    """计算期权的价格和希腊值"""
    price = calculatePrice(f, k, r, t, v, cp, n)
    delta = calculateDelta(f, k, r, t, v, cp, n)
    gamma = calculateGamma(f, k, r, t, v, cp, n)
    theta = calculateTheta(f, k, r, t, v, cp, n)
    vega = calculateVega(f, k, r, t, v, cp, n)
    return price, delta, gamma, theta, vega

#----------------------------------------------------------------------
def calculateImpv(price, f, k, r, t, cp, n=15):
    """计算隐含波动率"""
    # 检查期权价格必须为正数
    if price <= 0:
        return 0
    
    # 检查期权价格是否满足最小价值（即到期行权价值）
    meet = False
    
    if cp == 1 and price > (f - k):
        meet = True
    elif cp == -1 and price > (k - f):
        meet = True
    
    # 若不满足最小价值，则直接返回0
    if not meet:
        return 0
    
    # 采用Newton Raphson方法计算隐含波动率
    v = 0.3     # 初始波动率猜测
    
    for i in range(50):
        # 计算当前猜测波动率对应的期权价格和vega值
        p = calculatePrice(f, k, r, t, v, cp, n)
        
        vega = calculateOriginalVega(f, k, r, t, v, cp, n)
        
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
