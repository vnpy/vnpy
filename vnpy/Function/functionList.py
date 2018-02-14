# encoding: UTF-8

import numpy as np
import talib
from datetime import datetime

import talib
from math import fabs
from math import sqrt

'''
技术指标函数
'''
class TechniqueFunction:
    '''
    两个 np.array 相减
    @param1 np.array([1,2,3,4]) 
    @param2 np.array([1,2,3,4]) 
    @return  np.array()
    '''
    @staticmethod
    def Subtract( price1 , price2):
        n = len(price1)
        ret = np.zeros(n)
        for i in range(n):
            ret[i] = price1[i] - price2[i]
        return ret

    '''
    两个 np.array 相加
    @param1 np.array([1,2,3,4]) 
    @param2 np.array([1,2,3,4]) 
    @return  np.array()
    '''
    @staticmethod
    def Plus( price1 , price2):
        n = len(price1)
        ret = np.zeros(n)
        for i in range(n):
            ret[i] = price1[i] + price2[i]
        return ret
    '''
    xAverage( )
    @param1  np.array([1,2,3,4]) , 3
    @param2  int
    @return  np.array()
    '''
    @staticmethod
    def xAverage(price , length):
        n = len(price)
        sFcactor = 2.0/(length + 1)
        xAverage1 = np.zeros(n)
        for i in range(0 , n):
            if i==0:
                xAverage1[i] = price[i]
            else:
                xAverage1[i] = xAverage1[i-1] + sFcactor * (price[i] - xAverage1[i-1])
        return xAverage1
    '''
    Highest(price , length)
    @param1 np.array([1,2,3,4]) 
    @param2  int
    @return  np.array()
    '''
    @staticmethod
    def Highest(price , length):
        n = len(price)
        ret = np.zeros(n)
        for i in range( n):
            ret[i] = price[i]
            j = i - 1
            while j > i - length and j >= 0:
                ret[i] = max( ret[i] , price[j])
                j = j - 1
        return ret
    '''
    Lowest(price , length)
    @param1  np.array([1,2,3,4]) 
    @param2  int
    @return  np.array()
    '''
    @staticmethod
    def Lowest(price , length):
        n = len(price)
        ret = np.zeros(n)
        for i in range(n):
            ret[i] = price[i]
            j = i - 1
            while j > i - length and j >= 0:
                ret[i] = min( ret[i] , price[j])
                j = j - 1
        return ret
    '''
    Summation(price , length)
    @param1  np.array([1,2,3,4]) 
    @param2  int
    @return  np.array()
    '''
    @staticmethod
    def Summation(price , length):
        n = len(price)
        ret = np.zeros(n)
        if n > 0:
            ret[0] = price[0] * length
        for i in range( 1 , n):
            if i < length:
                ret[i] = price[i] + ret[i-1] - price[0]
            else:
                ret[i] = price[i] + ret[i-1] - price[i - length]
        return ret

    '''
    求估计方差
    '''
    @staticmethod
    def VariancePS(price , length , dataType = 1):
        n = len(price)
        ret = np.zeros(n)
        _divisor = length - 1
        if 1 == dataType :
            _divisor = length
        if _divisor > 0:
            _mean = TechniqueFunction.Average( price , length )
            ret[0] = 0
            for i in range( 1 , n):
                tmp = 0.0
                for j in range( length):
                    tmp +=  (_mean[i] - price[max(0,i-j)]) * (_mean[i] - price[max(0,i-j)])
                ret[i] = tmp
            for i in range( n):
                ret[i] = ret[i] * 1.0 / length
        else:
            for i in range(n):
                ret[i] = 0.0
        return ret

    '''
    求标准差
    '''
    @staticmethod
    def StandardDev(price , length , dataType = 1):
        n = len(price)
        ret = np.zeros(n)
        _varpsValue = TechniqueFunction.VariancePS(price , length , dataType)
        for i in range(n):
            if _varpsValue[i] > 0:
                ret[i] = sqrt(_varpsValue[i])
            else:
                ret[i] = 0.0
        return ret

    '''
    Average(price , length)
    @param1  np.array([1,2,3,4]) 
    @param2  int
    @return  np.array()
    '''
    @staticmethod
    def Average(price , length):
        n = len(price)
        ret = np.zeros(n)
        tmpSum = TechniqueFunction.Summation( price , length)
        for i in range(n):
            ret[i] = tmpSum[i] * 1.0 / length
        return ret
    '''
    MACD 
    @param1  np.array([1,2,3,4]) , 3
    @param2  int
    @param3  int
    @param4  int
    return ( np.array() , np.array() , np.array())
    '''
    @staticmethod
    def MACD( closeArray , FastLength , SlowLength , MACDLength):
        n = len(closeArray)
        t_aveFast = TechniqueFunction.xAverage( closeArray , FastLength )
        t_aveSlow = TechniqueFunction.xAverage( closeArray , SlowLength )

        MACDValue = np.zeros(n)
        for i in range( n ):
            MACDValue[i] = t_aveFast[i] - t_aveSlow[i]

        AvgMACD = TechniqueFunction.xAverage( MACDValue , MACDLength)

        MACDDiff = np.zeros(n)
        for i in range( n ):
            MACDDiff[i] = MACDValue[i] - AvgMACD[i]

        return (MACDValue , AvgMACD , MACDDiff)
    '''
    KDJ 
    @param1  np.array([1,2,3,4]) 
    @param2  np.array([1,2,3,4]) 
    @param3  np.array([1,2,3,4]) 
    @param4  int
    @param5  int
    @param6  int
    return ( np.array() , np.array() , np.array())
    '''
    @staticmethod
    def KDJ( highArray , lowArray , closeArray , Length , SlowLength , SmoothLength ):
        n = len(highArray)
        highestValue = TechniqueFunction.Highest( highArray , Length)
        lowestValue = TechniqueFunction.Lowest( lowArray , Length)
        hlMinus = TechniqueFunction.Subtract(highestValue , lowestValue)
        clMinus = TechniqueFunction.Subtract(closeArray , lowestValue)
        sumHLValue = TechniqueFunction.Summation( hlMinus , SlowLength )
        sumCLValue = TechniqueFunction.Summation( clMinus , SlowLength )
        K_arr = np.zeros(n)
        D_arr = np.zeros(n)
        J_arr = np.zeros(n)
        for i in range(n):
            if fabs(sumHLValue[i]) > 0.0000001:
                K_arr[i] = sumCLValue[i] * 100.0 / sumHLValue[i]
            else:
                K_arr[i] = 0.0
        D_arr = TechniqueFunction.Average( K_arr , SmoothLength)
        for i in range(n):
            J_arr[i] = 3 * K_arr[i] - 2 * D_arr[i]
        return (K_arr , D_arr , J_arr)

    '''
    RSI
    '''
    @staticmethod
    def RSI( closeArray , length ):
        n = len(closeArray)
        netChgAvg = 0
        totChgAvg = 0
        preNetChgAvg = 0.0
        preTotChgAvg = 0.0
        ChgRatio = 0.0
        RSIValue = np.zeros(n)
        for i in range( n ):
            if i < length:
                netChgAvg = (closeArray[i] - closeArray[max(i-length , 0)]) * 1.0 / length
                sum_val = 0.0
                for j in range( length):
                    sum_val += fabs( closeArray[max(i-j , 0)] - closeArray[max(i-j-1, 0 )]) 
                sum_val = sum_val * 1.0 / length
                totChgAvg = sum_val
            else:
                SF = 1.0 / length
                Change = closeArray[i] - closeArray[max(i-1 , 0)]
                netChgAvg = preNetChgAvg + SF * ( Change - preNetChgAvg)
                totChgAvg = preTotChgAvg + SF * ( abs(Change) - preTotChgAvg)

                # print netChgAvg , totChgAvg , Change

            if(abs(totChgAvg) > 0.000001):
                ChgRatio = netChgAvg * 1.0 / totChgAvg
            else:
                ChgRatio = 0
            RSIValue[i] = 50 * (ChgRatio + 1)

            preNetChgAvg = netChgAvg
            preTotChgAvg = totChgAvg
        return RSIValue

    '''
    TrueRange
    '''
    @staticmethod
    def TrueRange( highArray , lowArray , closeArray ):
        n = len(closeArray)
        trArr = np.zeros(n)
        if n > 0:
            trArr[0] = highArray[0] - lowArray[0]
        for i in range(1 , n):
            trueHigh = max(highArray[i] , closeArray[ i-1])
            trueLow = min(lowArray[i] , closeArray[ i-1])
            trArr[i] = trueHigh - trueLow
        return trArr
    '''
    ATR
    '''
    @staticmethod
    def AvgTrueRange( highArray , lowArray , closeArray , length):
        trArr = TechniqueFunction.TrueRange(highArray , lowArray , closeArray)
        return TechniqueFunction.Average( trArr , length)


    '''
    求是否上穿
Params
    NumericSeries Price1(1); 
    NumericSeries Price2(1);
Vars
    Bool Con1(False);
    Bool PreCon(False);
    Numeric Counter(0);
Begin
    If(Price1 > Price2)
    {
        Counter = 1;    
        Con1 = Price1[1] == Price2[1];      
        While (Con1 and Counter < CurrentBar)
        {           
            Counter = Counter + 1;           
            Con1 = Price1[Counter] == Price2[Counter];  
        }
        PreCon = Price1[Counter] < Price2[Counter];
        Return PreCon;
    }Else
    {
        Return False;
    }
End

    '''
    @staticmethod
    def CrossOver( price1 , price2):
        n = min(len(price1) , len(price2))
        if n > 0:
            if price1[-1] > price2[-1]:
                Counter = 2
                Con1 = price1[-2] == price2[-2]
                while Con1 == True and ( Counter < n):
                    Counter = Counter + 1
                    Con1 = price1[-Counter] == price2[-Counter]
                PreCon = price1[-Counter] < price2[-Counter]
                return PreCon
        return False

    '''
    求是否下破

Params
    NumericSeries Price1(1); 
    NumericSeries Price2(1);
Vars
    Bool Con1(False);
    Bool PreCon(False);
    Numeric Counter(0);
Begin
    If(Price1 < Price2)
    {
        Counter = 1;    
        Con1 = Price1[1] == Price2[1];      
        While (Con1 and Counter < CurrentBar)
        {           
            Counter = Counter + 1;           
            Con1 = Price1[Counter] == Price2[Counter];  
        }
        PreCon = Price1[Counter] > Price2[Counter];
        Return PreCon;
    }Else
    {
        Return False;
    }
End
    '''
    @staticmethod
    def CrossUnder( price1 , price2):
        n = min(len(price1) , len(price2))
        if n > 0:
            if price1[-1] < price2[-1]:
                Counter = 2
                Con1 = price1[-2] == price2[-2]
                while Con1 == True and (Counter < n):
                    Counter = Counter + 1
                    Con1 = price1[-Counter] == price2[-Counter]
                PreCon = price1[-Counter] > price2[-Counter]
                return PreCon
        return False

'''
@author si
'''
def xAverage(price , length):
    return (TechniqueFunction.xAverage(price,length))[-1]


# class TecniqueIndicator():
    
#     def updateArr(self , arr , bufferSize):
#         while len(arr) > bufferSize:
#             arr.pop(0)

# class RSI( TecniqueIndicator ):
#     def __init__(self , t_rsiLength):
#         self.netChgAvg = 0
#         self.totChgAvg = 0
#         self.preNetChgAvg = 0.0
#         self.preTotChgAvg = 0.0
#         self.ChgRatio = 0.0
#         self.barCount = -1
#         self.rsi_value = 0.0
#         self.rsiLength = t_rsiLength

#         self.closeArray = []
#         self.buff_size = t_rsiLength + 10

#     def getValue():
#         return self.rsi_value

#     def update( self , closePrice):
#         self.barCount += 1
#         # total_size = -(barCount + 1)
#         self.closeArray.append(closePrice)
#         self.updateArr(self.closeArray , self.buff_size)


#         if self.barCount <= self.rsiLength - 1:
#             self.netChgAvg = self.closeArray[-1] - self.closeArray[max( -self.buff_size , -1 - self.rsiLength)]
#             sum_val = 0.0
#             for j in range( self.rsiLength):
#                 sum_val += fabs( self.closeArray[max( self.barCount-j , -self.buff_size)] - closeArray[max(self.barCount-j-1, 0 )]) 
#             sum_val = sum_val * 1.0 / self.rsiLength
#             self.totChgAvg = sum_val
#         else:
#             self.SF = 1.0 / self.rsiLength
#             Change = self.closeArray[self.barCount] - self.