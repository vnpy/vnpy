import numpy as np
from nose.tools import (
    assert_equals,
    assert_true,
    assert_false,
    assert_raises,
    )

try:
    from collections import OrderedDict
except ImportError: # handle python 2.6 and earlier
    from ordereddict import OrderedDict

import talib
from talib import func
from talib import abstract
from talib.test_data import ford_2012, assert_np_arrays_equal, assert_np_arrays_not_equal


def test_pandas():
    import pandas
    input_df = pandas.DataFrame(ford_2012)
    input_dict = dict((k, pandas.Series(v)) for k, v in ford_2012.items())

    expected_k, expected_d = func.STOCH(ford_2012['high'], ford_2012['low'], ford_2012['close']) # 5, 3, 0, 3, 0
    output = abstract.Function('stoch', input_df).outputs
    assert_true(isinstance(output, pandas.DataFrame))
    assert_np_arrays_equal(expected_k, output['slowk'])
    assert_np_arrays_equal(expected_d, output['slowd'])
    output = abstract.Function('stoch', input_dict).outputs
    assert_true(isinstance(output, list))
    assert_np_arrays_equal(expected_k, output[0])
    assert_np_arrays_equal(expected_d, output[1])

    expected = func.SMA(ford_2012['close'], 10)
    output = abstract.Function('sma', input_df, 10).outputs
    assert_true(isinstance(output, pandas.Series))
    assert_np_arrays_equal(expected, output)
    output = abstract.Function('sma', input_dict, 10).outputs
    assert_true(isinstance(output, np.ndarray))
    assert_np_arrays_equal(expected, output)


def test_pandas_series():
    import pandas
    input_df = pandas.DataFrame(ford_2012)
    output = talib.SMA(input_df['close'], 10)
    expected = pandas.Series(func.SMA(ford_2012['close'], 10),
                             index=input_df.index)
    pandas.util.testing.assert_series_equal(output, expected)

    # Test kwargs
    output = talib.SMA(real=input_df['close'], timeperiod=10)
    pandas.util.testing.assert_series_equal(output, expected)

    # Test talib.func API
    output = func.SMA(input_df['close'], timeperiod=10)
    pandas.util.testing.assert_series_equal(output, expected)

    # Test multiple outputs such as from BBANDS
    _, output, _ = talib.BBANDS(input_df['close'], 10)
    expected = pandas.Series(func.BBANDS(ford_2012['close'], 10)[1],
                             index=input_df.index)
    pandas.util.testing.assert_series_equal(output, expected)


def test_SMA():
    expected = func.SMA(ford_2012['close'], 10)
    assert_np_arrays_equal(expected, abstract.Function('sma', ford_2012, 10).outputs)
    assert_np_arrays_equal(expected, abstract.Function('sma')(ford_2012, 10, price='close'))
    assert_np_arrays_equal(expected, abstract.Function('sma')(ford_2012, timeperiod=10))
    expected = func.SMA(ford_2012['open'], 10)
    assert_np_arrays_equal(expected, abstract.Function('sma', ford_2012, 10, price='open').outputs)
    assert_np_arrays_equal(expected, abstract.Function('sma', price='low')(ford_2012, 10, price='open'))
    assert_np_arrays_not_equal(expected, abstract.Function('sma', ford_2012, 10, price='open')(timeperiod=20))
    assert_np_arrays_not_equal(expected, abstract.Function('sma', ford_2012)(10, price='close'))
    assert_np_arrays_not_equal(expected, abstract.Function('sma', 10)(ford_2012, price='high'))
    assert_np_arrays_not_equal(expected, abstract.Function('sma', price='low')(ford_2012, 10))
    input_arrays = {'foobarbaz': ford_2012['open']}
    assert_np_arrays_equal(expected, abstract.SMA(input_arrays, 10, price='foobarbaz'))


def test_STOCH():
    # check defaults match
    expected_k, expected_d = func.STOCH(ford_2012['high'], ford_2012['low'], ford_2012['close']) # 5, 3, 0, 3, 0
    got_k, got_d = abstract.Function('stoch', ford_2012).outputs
    assert_np_arrays_equal(expected_k, got_k)
    assert_np_arrays_equal(expected_d, got_d)

    expected_k, expected_d = func.STOCH(ford_2012['high'], ford_2012['low'], ford_2012['close'])
    got_k, got_d = abstract.Function('stoch', ford_2012)(5, 3, 0, 3, 0)
    assert_np_arrays_equal(expected_k, got_k)
    assert_np_arrays_equal(expected_d, got_d)

    expected_k, expected_d = func.STOCH(ford_2012['high'], ford_2012['low'], ford_2012['close'], 15)
    got_k, got_d = abstract.Function('stoch', ford_2012)(15, 5, 0, 5, 0)
    assert_np_arrays_not_equal(expected_k, got_k)
    assert_np_arrays_not_equal(expected_d, got_d)

    expected_k, expected_d = func.STOCH(ford_2012['high'], ford_2012['low'], ford_2012['close'], 15, 5, 1, 5, 1)
    got_k, got_d = abstract.Function('stoch', ford_2012)(15, 5, 1, 5, 1)
    assert_np_arrays_equal(expected_k, got_k)
    assert_np_arrays_equal(expected_d, got_d)

def test_doji_candle():
    expected = func.CDLDOJI(ford_2012['open'], ford_2012['high'], ford_2012['low'], ford_2012['close'])
    got = abstract.Function('CDLDOJI').run(ford_2012)
    assert_np_arrays_equal(got, expected)

def test_MAVP():
    mavp = abstract.MAVP
    assert_raises(Exception, mavp.set_input_arrays, ford_2012)
    input_d = {}
    input_d['close'] = ford_2012['close']
    input_d['periods'] = np.arange(30)
    assert_true(mavp.set_input_arrays(input_d))
    assert_equals(mavp.input_arrays, input_d)

def test_info():
    stochrsi = abstract.Function('STOCHRSI')
    stochrsi.input_names = {'price': 'open'}
    stochrsi.parameters = {'fastd_matype': talib.MA_Type.EMA}
    expected = {
        'display_name': 'Stochastic Relative Strength Index',
        'function_flags': ['Function has an unstable period'],
        'group': 'Momentum Indicators',
        'input_names': OrderedDict([('price', 'open')]),
        'name': 'STOCHRSI',
        'output_flags': OrderedDict([
            ('fastk', ['Line']),
            ('fastd', ['Line']),
            ]),
        'output_names': ['fastk', 'fastd'],
        'parameters': OrderedDict([
            ('timeperiod', 14),
            ('fastk_period', 5),
            ('fastd_period', 3),
            ('fastd_matype', 1),
            ]),
        }
    assert_equals(expected, stochrsi.info)

    expected = {
        'display_name': 'Bollinger Bands',
        'function_flags': ['Output scale same as input'],
        'group': 'Overlap Studies',
        'input_names': OrderedDict([('price', 'close')]),
        'name': 'BBANDS',
        'output_flags': OrderedDict([
            ('upperband', ['Values represent an upper limit']),
            ('middleband', ['Line']),
            ('lowerband', ['Values represent a lower limit']),
            ]),
        'output_names': ['upperband', 'middleband', 'lowerband'],
        'parameters': OrderedDict([
            ('timeperiod', 5),
            ('nbdevup', 2),
            ('nbdevdn', 2),
            ('matype', 0),
            ]),
        }
    assert_equals(expected, abstract.Function('BBANDS').info)

def test_input_names():
    expected = OrderedDict([('price', 'close')])
    assert_equals(expected, abstract.Function('MAMA').input_names)

    # test setting input_names
    obv = abstract.Function('OBV')
    expected = OrderedDict([
        ('price', 'open'),
        ('prices', ['volume']),
        ])
    obv.input_names = expected
    assert_equals(obv.input_names, expected)

    obv.input_names = {
        'price': 'open',
        'prices': ['volume'],
        }
    assert_equals(obv.input_names, expected)

def test_input_arrays():
    mama = abstract.Function('MAMA')
    # test default setting
    expected = {
        'open': None,
        'high': None,
        'low': None,
        'close': None,
        'volume': None,
        }
    assert_equals(expected, mama.get_input_arrays())
    # test setting/getting input_arrays
    assert_true(mama.set_input_arrays(ford_2012))
    assert_equals(mama.get_input_arrays(), ford_2012)
    assert_raises(Exception,
                  mama.set_input_arrays, {'hello': 'fail', 'world': 'bye'})

    # test only required keys are needed
    willr = abstract.Function('WILLR')
    reqd = willr.input_names['prices']
    input_d = dict([(key, ford_2012[key]) for key in reqd])
    assert_true(willr.set_input_arrays(input_d))
    assert_equals(willr.input_arrays, input_d)

    # test extraneous keys are ignored
    input_d['extra_stuffs'] = 'you should never see me'
    input_d['date'] = np.random.rand(100)
    assert_true(willr.set_input_arrays(input_d))

    # test missing keys get detected
    input_d['open'] = ford_2012['open']
    input_d.pop('close')
    assert_raises(Exception, willr.set_input_arrays, input_d)

    # test changing input_names on the Function
    willr.input_names = {'prices': ['high', 'low', 'open']}
    assert_true(willr.set_input_arrays(input_d))

def test_parameters():
    stoch = abstract.Function('STOCH')
    expected = OrderedDict([
        ('fastk_period', 5),
        ('slowk_period', 3),
        ('slowk_matype', 0),
        ('slowd_period', 3),
        ('slowd_matype', 0),
        ])
    assert_equals(expected, stoch.parameters)

    stoch.parameters = {'fastk_period': 10}
    expected['fastk_period'] = 10
    assert_equals(expected, stoch.parameters)

    stoch.parameters = {'slowk_period': 8, 'slowd_period': 5}
    expected['slowk_period'] = 8
    expected['slowd_period'] = 5
    assert_equals(expected, stoch.parameters)

    stoch.parameters = {'slowd_matype': talib.MA_Type.T3}
    expected['slowd_matype'] = 8
    assert_equals(expected, stoch.parameters)

    stoch.parameters = {
        'slowk_matype': talib.MA_Type.WMA,
        'slowd_matype': talib.MA_Type.EMA,
        }
    expected['slowk_matype'] = 2
    expected['slowd_matype'] = 1
    assert_equals(expected, stoch.parameters)

def test_lookback():
    assert_equals(abstract.Function('SMA', 10).lookback, 9)

    stochrsi = abstract.Function('stochrsi', 20, 5, 3)
    assert_equals(stochrsi.lookback, 26)
