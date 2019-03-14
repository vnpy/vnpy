import numpy as np
import pandas as pd
from nose.tools import assert_equals, assert_is_instance, assert_true

import talib
from talib.test_data import series, assert_np_arrays_equal

def test_MOM():
    values = pd.Series([90.0,88.0,89.0], index=[10, 20, 30])
    result = talib.MOM(values, timeperiod=1)
    assert_is_instance(result, pd.Series)
    assert_np_arrays_equal(result.values, [np.nan, -2, 1])
    assert_np_arrays_equal(result.index, [10, 20, 30])
    result = talib.MOM(values, timeperiod=2)
    assert_is_instance(result, pd.Series)
    assert_np_arrays_equal(result.values, [np.nan, np.nan, -1])
    assert_np_arrays_equal(result.index, [10, 20, 30])
    result = talib.MOM(values, timeperiod=3)
    assert_is_instance(result, pd.Series)
    assert_np_arrays_equal(result.values, [np.nan, np.nan, np.nan])
    assert_np_arrays_equal(result.index, [10, 20, 30])
    result = talib.MOM(values, timeperiod=4)
    assert_is_instance(result, pd.Series)
    assert_np_arrays_equal(result.values, [np.nan, np.nan, np.nan])
    assert_np_arrays_equal(result.index, [10, 20, 30])

def test_MAVP():
    a = pd.Series([1,5,3,4,7,3,8,1,4,6], index=range(10, 20), dtype=float)
    b = pd.Series([2,4,2,4,2,4,2,4,2,4], index=range(20, 30), dtype=float)
    result = talib.MAVP(a, b, minperiod=2, maxperiod=4)
    assert_is_instance(result, pd.Series)
    assert_np_arrays_equal(result.values, [np.nan,np.nan,np.nan,3.25,5.5,4.25,5.5,4.75,2.5,4.75])
    assert_np_arrays_equal(result.index, range(10, 20))
    sma2 = talib.SMA(a, 2)
    assert_is_instance(sma2, pd.Series)
    assert_np_arrays_equal(sma2.index, range(10, 20))
    assert_np_arrays_equal(result.values[4::2], sma2.values[4::2])
    sma4 = talib.SMA(a, 4)
    assert_is_instance(sma4, pd.Series)
    assert_np_arrays_equal(sma4.index, range(10, 20))
    assert_np_arrays_equal(result.values[3::2], sma4.values[3::2])
    result = talib.MAVP(a, b, minperiod=2, maxperiod=3)
    assert_is_instance(result, pd.Series)
    assert_np_arrays_equal(result.values, [np.nan,np.nan,4,4,5.5,4.666666666666667,5.5,4,2.5,3.6666666666666665])
    assert_np_arrays_equal(result.index, range(10, 20))
    sma3 = talib.SMA(a, 3)
    assert_is_instance(sma3, pd.Series)
    assert_np_arrays_equal(sma3.index, range(10, 20))
    assert_np_arrays_equal(result.values[2::2], sma2.values[2::2])
    assert_np_arrays_equal(result.values[3::2], sma3.values[3::2])
