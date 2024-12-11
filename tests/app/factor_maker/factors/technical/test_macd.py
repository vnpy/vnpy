# -*- coding=utf-8 -*-
# @Project  : 20240720
# @FilePath : ${DIR_PATH}
# @File     : ${FILE_NAME}
# @Time     : 2024/12/11 21:00
# @Author   : EvanHong
# @Email    : 939778128@qq.com
# @Description:
from unittest import TestCase
from vnpy.app.factor_maker.factors.technical.macd import MACD


class TestMACDFactor(TestCase):

    def init_with_setting(self):
        self.factor = MACD(setting={
            'macd@fast_period_12-slow_period_26-signal_period_9': {'class_name': 'MACD', 'freq': 'UNKNOWN',
                                                                   'params': {'fast_period': 12, 'slow_period': 26,
                                                                              'signal_period': 9},
                                                                   'dependencies_factor': [{'ma@window_12': {
                                                                       'class_name': 'MA', 'freq': 'UNKNOWN',
                                                                       'params': {'window': 12},
                                                                       'dependencies_factor': [],
                                                                       'dependencies_freq': [],
                                                                       'dependencies_symbol': [],
                                                                       'dependencies_exchange': []}}, {'ma@window_26': {
                                                                       'class_name': 'MA', 'freq': 'UNKNOWN',
                                                                       'params': {'window': 26},
                                                                       'dependencies_factor': [],
                                                                       'dependencies_freq': [],
                                                                       'dependencies_symbol': [],
                                                                       'dependencies_exchange': []}}],
                                                                   'dependencies_freq': [], 'dependencies_symbol': [],
                                                                   'dependencies_exchange': []}}
                           )
        print(self.factor.to_dict())

    def test_init_with_setting(self):
        self.init_with_setting()

    def init_with_params(self):
        self.factor = MACD(setting={}, fast_period=12, slow_period=26, signal_period=9)
        print(self.factor.to_dict())

    def test_init_with_params(self):
        self.init_with_params()

    def test_calculate(self):
        self.fail()

    def test_deleteme(self):
        class Param(object):
            def __init__(self):
                pass

            def set_params(self, params_dict):
                for k, v in params_dict.items():
                    setattr(self, k, v)

        class Base(object):
            param = Param()

            def __init__(self, setting):
                self.setting = setting

        class A(Base):
            def __init__(self, setting):
                super().__init__(setting)
                self.params.set_params(setting)

        class B(Base):
            def __init__(self, setting):
                super().__init__(setting)
                self.params = Param()
