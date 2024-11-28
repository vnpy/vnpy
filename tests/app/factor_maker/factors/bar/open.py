# -*- coding=utf-8 -*-
# @Project  : 20240720
# @FilePath : vnpy/tests/app/factor_maker/factors/bar
# @File     : open.py
# @Time     : 2024/11/25 21:16
# @Author   : EvanHong
# @Email    : 939778128@qq.com
# @Description:

from unittest import TestCase

from vnpy.app.factor_maker.factors.bar.open import OPEN


class TestOPEN(TestCase):

    def init(self):
        self.open = OPEN(setting={})

    def test_set_params(self):
        self.init()
        self.open.set_params({'a': 1})
        self.assertEqual(self.open.get_params(), {'a': 1})

    def test_on_init(self):
        open = OPEN(setting={})
        print(open.get_params())
        open.set_params()


    def test_on_bar(self):
        open = OPEN()
        open.on_bar(bar=None)
        self.fail()

    def test_on_tick(self):
        open = OPEN()
        open.on_tick(tick=None)
        self.fail()

    def test_on_factor(self):
        open = OPEN()
        open.on_factor(factor=None)
        self.fail()

    def test_calculate_polars(self):
        self.fail()