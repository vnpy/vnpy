# -*- coding=utf-8 -*-
# @Project  : 20240720
# @FilePath : vnpy/tests/app/factor_maker/factors/bar
# @File     : open.py
# @Time     : 2024/11/25 21:16
# @Author   : EvanHong
# @Email    : 939778128@qq.com
# @Description:

from unittest import TestCase

from vnpy.app.factor_maker.factors.bar import *


class TestOPEN(TestCase):

    def init(self):
        self.open = OPEN(setting={
            "open@noparams": {
                "class_name": "OPEN",
                "freq":"1m",
                "params": {},
                "dependencies_factor": [{
                    "close@noparams": {
                        "class_name": "CLOSE",
                        "freq": "1m",
                        "params": {},
                        "dependencies_factor": [],
                        "dependencies_freq": [],
                        "dependencies_symbol": [],
                        "dependencies_exchange": []
                    }
                }],
                "dependencies_freq": [],
                "dependencies_symbol": [],
                "dependencies_exchange": []
            }
        })

    def test_set_params(self):
        self.init()
        self.open.set_params({'a': 1})
        self.assertEqual(self.open.get_params(), {'a': 1})

    def test_init_from_json(self):
        import json
        with open(f'/Users/hongyifan/Desktop/work/crypto/20240720/examples/no_ui/.vntrader/factor_maker_setting.json','r') as fr:
            js=json.load(fr)
        print(js)
        # print(self.open.dependencies_factor)


    def test_to_dict(self):
        self.init()
        print(self.open.to_dict())
