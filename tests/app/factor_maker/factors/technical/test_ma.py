# -*- coding=utf-8 -*-

#  Copyright (c) 2024. Lorem ipsum dolor sit amet, consectetur adipiscing elit.
#  Morbi non lorem porttitor neque feugiat blandit. Ut vitae ipsum eget quam lacinia accumsan.
#  Etiam sed turpis ac ipsum condimentum fringilla. Maecenas magna.
#  Proin dapibus sapien vel ante. Aliquam erat volutpat. Pellentesque sagittis ligula eget metus.
#  Vestibulum commodo. Ut rhoncus gravida arcu.

# @Project  : 20240720
# @FilePath : ${DIR_PATH}
# @File     : ${FILE_NAME}
# @Time     : 2024/11/28 23:02
# @Author   : EvanHong
# @Email    : 939778128@qq.com
# @Description:

from unittest import TestCase

from vnpy.app.factor_maker.factors.technical.ma import MA


class TestMA(TestCase):

    def init(self):
        self.open = MA(setting={})

    def test_set_params(self):
        self.init()
        self.open.set_params({'window': 10})
        self.assertEqual(self.open.params.__dict__, {'window': 10})

