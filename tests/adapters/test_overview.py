# -*- coding=utf-8 -*-
# @Project  : 20240720
# @FilePath : ${DIR_PATH}
# @File     : ${FILE_NAME}
# @Time     : 2025/1/14 11:30
# @Author   : EvanHong
# @Email    : 939778128@qq.com
# @Description:
import datetime
import unittest
from unittest.mock import patch, mock_open
from vnpy.adapters.overview import (save_overview, load_overview, OverviewEncoder, OverviewDecoder, BarOverview,
                                    FactorOverview, Exchange, Interval)


class TestOverviewFunctions(unittest.TestCase):

    @patch('vnpy.adapters.overview.save_json')
    def save_overview_saves_correctly(self, mock_save_json):
        filename = 'bar_overview.json'
        overview_data = {'key': {'subkey': 'value'}}
        save_overview(filename, overview_data)
        mock_save_json.assert_called_once_with(filename, overview_data, cls=OverviewEncoder, mode='w')

    @patch('vnpy.adapters.overview.load_json')
    def load_overview_loads_correctly(self, mock_load_json):
        filename = 'test.json'
        expected_data = {'key': {'subkey': 'value'}}
        mock_load_json.return_value = expected_data
        result = load_overview(filename)
        self.assertEqual(result, expected_data)
        mock_load_json.assert_called_once_with(filename=filename, cls=OverviewDecoder)

    @patch('vnpy.adapters.overview.load_json')
    def load_overview_returns_empty_dict_if_file_not_exists(self, mock_load_json):
        filename = 'non_existent.json'
        mock_load_json.return_value = {}
        result = load_overview(filename)
        self.assertEqual(result, {})
        mock_load_json.assert_called_once_with(filename=filename, cls=OverviewDecoder)

    def test_save_bar_overview(self):
        bar_overview = BarOverview(symbol='BTCUSDT', exchange=Exchange('BINANCE'), interval=Interval('1m'),
                                   start=datetime.datetime.fromtimestamp(1630000000),
                                   end=datetime.datetime.fromtimestamp(1630000000),
                                   count=1000)
        bar_overview.vtsym
        save_overview('bar_overview.json', bar_overview)


if __name__ == '__main__':
    unittest.main()
