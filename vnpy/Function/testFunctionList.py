# encoding: UTF-8

import numpy as np
import talib
from datetime import datetime

import talib
from math import fabs
from math import sqrt

from functionList import TechniqueFunction


def testRSI():
	f = open("D:/out_file/Text112.txt" , "r")
	closeArray = []
	for line in f:
		tdate , ttime , close , NetChgAvg ,  TotChgAvg , ChgRatio , RSIValue = line.strip().split(' ')
		closeArray.append( float(close))
	rsi = TechniqueFunction.RSI( closeArray , 14)
	for i in range(len(rsi)):
		print rsi[i]

def testRSI2():
	closeArray = [3603 , 3585 , 3593 , 3594 , 3540]

	print TechniqueFunction.RSI( closeArray , 5)


def testAvgTrueRange():
	highArray = []
	lowArray = []
	closeArray = []
	f = open("D:/out_file/Text111.txt" , "r")
	for line in f:
		high,low,close,avgTrue = line.strip().split(' ')
		highArray.append(float(high))
		lowArray.append(float(low))
		closeArray.append(float(close))
	f.close()

	arr = TechniqueFunction.AvgTrueRange( highArray , lowArray , closeArray , 10)

	for cc in arr:
		print cc

def testCrossUnder():
	s1 = [1 , 5]
	s2 = [3 , 4]
	print TechniqueFunction.CrossUnder( s1 , s2)

def testCrossOver():
	s1 = [2.1 , 1]
	s2 = [2 , 3]
	print TechniqueFunction.CrossOver( s1 , s2)


if __name__ == '__main__':
	#testRSI()
	#testAvgTrueRange()

	#testRSI2()
	#testCrossUnder()
	testCrossOver()