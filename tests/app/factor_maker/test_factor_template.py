# -*- coding=utf-8 -*-
# @Project  : 20240720
# @FilePath : ${DIR_PATH}
# @File     : ${FILE_NAME}
# @Time     : 2024/11/25 09:49
# @Author   : EvanHong
# @Email    : 939778128@qq.com
# @Description:
from unittest import TestCase

from vnpy.app.factor_maker import FactorMakerApp
from vnpy.app.factor_maker.template import FactorParameters, FactorTemplate

class TestFactorParameters(TestCase):

    def test_set_parameters(self):
        fparam = FactorParameters()
        print(fparam.get_all_parameters())
        print(str(fparam))

        fparam = FactorParameters({"a": 1, "b": 2})
        print(fparam.get_all_parameters())
        print(str(fparam))

        fparam.set_parameters({"c": 3})
        print(fparam.get_all_parameters())
        print(str(fparam))

        fparam.set_parameters({"a": 4})
        print(fparam.get_all_parameters())
        print(str(fparam))

        fparam.del_parameters("a")
        print(fparam.get_all_parameters())
        print(str(fparam))
    def test_get_parameters(self):
        self.fail()

class TestFactorTemplate(TestCase):

    def init(self):
        self.ftemp = FactorTemplate(setting={})


    def test_sth(self):
        self.init()
        print(self.ftemp.get_params())

    def test_get_params(self):
        self.init()
        print(self.ftemp.get_params())

