import numpy as np
from nose.tools import assert_equals, assert_true, assert_raises

import talib
from talib import func
from talib.test_data import series, assert_np_arrays_equal, assert_np_arrays_not_equal

def test_talib_version():
    assert_equals(talib.__ta_version__[:5], b'0.4.0')

def test_num_functions():
    assert_equals(len(talib.get_functions()), 158)

def test_input_lengths():
    a1 = np.arange(10, dtype=float)
    a2 = np.arange(11, dtype=float)
    with assert_raises(Exception):
        func.BOP(a2, a1, a1, a1)
    with assert_raises(Exception):
        func.BOP(a1, a2, a1, a1)
    with assert_raises(Exception):
        func.BOP(a1, a1, a2, a1)
    with assert_raises(Exception):
        func.BOP(a1, a1, a1, a2)

def test_input_nans():
    a1 = np.arange(10, dtype=float)
    a2 = np.arange(10, dtype=float)
    a2[0] = np.nan
    a2[1] = np.nan
    r1, r2 = func.AROON(a1, a2, 2)
    assert_np_arrays_equal(r1, [np.nan, np.nan, np.nan, np.nan, 0, 0, 0, 0, 0, 0])
    assert_np_arrays_equal(r2, [np.nan, np.nan, np.nan, np.nan, 100, 100, 100, 100, 100, 100])
    r1, r2 = func.AROON(a2, a1, 2)
    assert_np_arrays_equal(r1, [np.nan, np.nan, np.nan, np.nan, 0, 0, 0, 0, 0, 0])
    assert_np_arrays_equal(r2, [np.nan, np.nan, np.nan, np.nan, 100, 100, 100, 100, 100, 100])

def test_unstable_period():
    a = np.arange(10, dtype=float)
    r = func.EMA(a, 3)
    assert_np_arrays_equal(r, [np.nan, np.nan, 1, 2, 3, 4, 5, 6, 7, 8])
    talib.set_unstable_period('EMA', 5)
    r = func.EMA(a, 3)
    assert_np_arrays_equal(r, [np.nan, np.nan, np.nan, np.nan, np.nan, np.nan, np.nan, 6, 7, 8])
    talib.set_unstable_period('EMA', 0)

def test_MIN():
    result = func.MIN(series, timeperiod=4)
    i = np.where(~np.isnan(result))[0][0]
    assert_equals(len(series), len(result))
    assert_equals(result[i + 1], 93.780)
    assert_equals(result[i + 2], 93.780)
    assert_equals(result[i + 3], 92.530)
    assert_equals(result[i + 4], 92.530)
    values = np.array([np.nan, 5., 4., 3., 5., 7.])
    result = func.MIN(values, timeperiod=2)
    assert_np_arrays_equal(result, [np.nan, np.nan, 4, 3, 3, 5])

def test_MAX():
    result = func.MAX(series, timeperiod=4)
    i = np.where(~np.isnan(result))[0][0]
    assert_equals(len(series), len(result))
    assert_equals(result[i + 2], 95.090)
    assert_equals(result[i + 3], 95.090)
    assert_equals(result[i + 4], 94.620)
    assert_equals(result[i + 5], 94.620)

def test_MOM():
    values = np.array([90.0,88.0,89.0])
    result = func.MOM(values, timeperiod=1)
    assert_np_arrays_equal(result, [np.nan, -2, 1])
    result = func.MOM(values, timeperiod=2)
    assert_np_arrays_equal(result, [np.nan, np.nan, -1])
    result = func.MOM(values, timeperiod=3)
    assert_np_arrays_equal(result, [np.nan, np.nan, np.nan])
    result = func.MOM(values, timeperiod=4)
    assert_np_arrays_equal(result, [np.nan, np.nan, np.nan])

def test_BBANDS():
    upper, middle, lower = func.BBANDS(series, timeperiod=20,
                                        nbdevup=2.0, nbdevdn=2.0,
                                        matype=talib.MA_Type.EMA)
    i = np.where(~np.isnan(upper))[0][0]
    assert_true(len(upper) == len(middle) == len(lower) == len(series))
    #assert_true(abs(upper[i + 0] - 98.0734) < 1e-3)
    assert_true(abs(middle[i + 0] - 92.8910) < 1e-3)
    assert_true(abs(lower[i + 0] - 87.7086) < 1e-3)
    #assert_true(abs(upper[i + 13] - 93.674) < 1e-3)
    assert_true(abs(middle[i + 13] - 87.679) < 1e-3)
    assert_true(abs(lower[i + 13] - 81.685) < 1e-3)

def test_DEMA():
    result = func.DEMA(series)
    i = np.where(~np.isnan(result))[0][0]
    assert_true(len(series) == len(result))
    assert_true(abs(result[i + 1] - 86.765) < 1e-3)
    assert_true(abs(result[i + 2] - 86.942) < 1e-3)
    assert_true(abs(result[i + 3] - 87.089) < 1e-3)
    assert_true(abs(result[i + 4] - 87.656) < 1e-3)

def test_EMAEMA():
    result = func.EMA(series, timeperiod=2)
    result = func.EMA(result, timeperiod=2)
    i = np.where(~np.isnan(result))[0][0]
    assert_true(len(series) == len(result))
    assert_equals(i, 2)

def test_CDL3BLACKCROWS():
    o = np.array([39.00, 39.00, 39.00, 39.00, 39.00, 39.00, 39.00, 39.00, 39.00, 39.00, 39.00, 39.00, 39.00, 39.00, 40.32, 40.51, 38.09, 35.00, 27.66, 30.80])
    h = np.array([40.84, 40.84, 40.84, 40.84, 40.84, 40.84, 40.84, 40.84, 40.84, 40.84, 40.84, 40.84, 40.84, 40.84, 41.69, 40.84, 38.12, 35.50, 31.74, 32.51])
    l = np.array([35.80, 35.80, 35.80, 35.80, 35.80, 35.80, 35.80, 35.80, 35.80, 35.80, 35.80, 35.80, 35.80, 35.80, 39.26, 36.73, 33.37, 30.03, 27.03, 28.31])
    c = np.array([40.29, 40.29, 40.29, 40.29, 40.29, 40.29, 40.29, 40.29, 40.29, 40.29, 40.29, 40.29, 40.29, 40.29, 40.46, 37.08, 33.37, 30.03, 31.46, 28.31])

    result = func.CDL3BLACKCROWS(o, h, l, c)
    assert_np_arrays_equal(result, [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -100, 0, 0])

def test_RSI():
    a = np.array([0.00000024, 0.00000024, 0.00000024,
      0.00000024, 0.00000024, 0.00000023,
      0.00000024, 0.00000024, 0.00000024,
      0.00000024, 0.00000023, 0.00000024,
      0.00000023, 0.00000024, 0.00000023,
      0.00000024, 0.00000024, 0.00000023,
      0.00000023, 0.00000023], dtype='float64')
    result = func.RSI(a, 10)
    assert_np_arrays_equal(result, [np.nan,np.nan,np.nan,np.nan,np.nan,np.nan,np.nan,np.nan,np.nan,np.nan,0,0,0,0,0,0,0,0,0,0])
    result = func.RSI(a * 100000, 10)
    assert_np_arrays_equal(result, [np.nan,np.nan,np.nan,np.nan,np.nan,np.nan,np.nan,np.nan,np.nan,np.nan,33.333333333333329,51.351351351351347,39.491916859122398,51.84807024709005,42.25953803191981,52.101824405061215,52.101824405061215,43.043664867691085,43.043664867691085,43.043664867691085])

def test_MAVP():
    a = np.array([1,5,3,4,7,3,8,1,4,6], dtype=float)
    b = np.array([2,4,2,4,2,4,2,4,2,4], dtype=float)
    result = func.MAVP(a, b, minperiod=2, maxperiod=4)
    assert_np_arrays_equal(result, [np.nan,np.nan,np.nan,3.25,5.5,4.25,5.5,4.75,2.5,4.75])
    sma2 = func.SMA(a, 2)
    assert_np_arrays_equal(result[4::2], sma2[4::2])
    sma4 = func.SMA(a, 4)
    assert_np_arrays_equal(result[3::2], sma4[3::2])
    result = func.MAVP(a, b, minperiod=2, maxperiod=3)
    assert_np_arrays_equal(result, [np.nan,np.nan,4,4,5.5,4.666666666666667,5.5,4,2.5,3.6666666666666665])
    sma3 = func.SMA(a, 3)
    assert_np_arrays_equal(result[2::2], sma2[2::2])
    assert_np_arrays_equal(result[3::2], sma3[3::2])
