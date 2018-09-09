import unittest
import korbit


class TestKorbit(unittest.TestCase):
    def setUp(self):
        pass

    def test_ticker(self):
        ticker = korbit.ticker()
        self.assertTrue('last' in ticker.keys())
        self.assertTrue('timestamp' in ticker.keys())
