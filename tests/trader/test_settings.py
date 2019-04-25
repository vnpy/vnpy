"""
Test if database works fine
"""
import unittest

from vnpy.trader.setting import SETTINGS, get_settings


class TestSettings(unittest.TestCase):

    def test_get_settings(self):
        SETTINGS['a'] = 1
        got = get_settings()
        self.assertIn('a', got)
        self.assertEqual(got['a'], 1)

    def test_get_settings_with_prefix(self):
        SETTINGS['a.a'] = 1
        got = get_settings()
        self.assertIn('a', got)
        self.assertEqual(got['a'], 1)


if __name__ == '__main__':
    unittest.main()
