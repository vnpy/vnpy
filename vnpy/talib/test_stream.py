import numpy as np
from nose.tools import assert_equals, assert_true, assert_raises

import talib
from talib import stream

def test_streaming():
    a = np.array([1,1,2,3,5,8,13], dtype=float)
    r = stream.MOM(a, timeperiod=1)
    assert_equals(r, 5)
    r = stream.MOM(a, timeperiod=2)
    assert_equals(r, 8)
    r = stream.MOM(a, timeperiod=3)
    assert_equals(r, 10)
    r = stream.MOM(a, timeperiod=4)
    assert_equals(r, 11)
    r = stream.MOM(a, timeperiod=5)
    assert_equals(r, 12)
    r = stream.MOM(a, timeperiod=6)
    assert_equals(r, 12)
    r = stream.MOM(a, timeperiod=7)
    assert_true(np.isnan(r))

def test_CDL3BLACKCROWS():
    o = np.array([39.00, 39.00, 39.00, 39.00, 39.00, 39.00, 39.00, 39.00, 39.00, 39.00, 39.00, 39.00, 39.00, 39.00, 40.32, 40.51, 38.09, 35.00])
    h = np.array([40.84, 40.84, 40.84, 40.84, 40.84, 40.84, 40.84, 40.84, 40.84, 40.84, 40.84, 40.84, 40.84, 40.84, 41.69, 40.84, 38.12, 35.50])
    l = np.array([35.80, 35.80, 35.80, 35.80, 35.80, 35.80, 35.80, 35.80, 35.80, 35.80, 35.80, 35.80, 35.80, 35.80, 39.26, 36.73, 33.37, 30.03])
    c = np.array([40.29, 40.29, 40.29, 40.29, 40.29, 40.29, 40.29, 40.29, 40.29, 40.29, 40.29, 40.29, 40.29, 40.29, 40.46, 37.08, 33.37, 30.03])

    r = stream.CDL3BLACKCROWS(o, h, l, c)
    assert_equals(r, -100)
