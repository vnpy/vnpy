# flake8: noqa
import unittest


class ImportTest(unittest.TestCase):

    # noinspection PyUnresolvedReferences
    def test_import_all(self):
        from vnpy.event import EventEngine

        from vnpy.trader.engine import MainEngine
        from vnpy.trader.ui import MainWindow, create_qapp

        from vnpy.gateway.bitmex import BitmexGateway
        from vnpy.gateway.futu import FutuGateway
        from vnpy.gateway.ib import IbGateway
        from vnpy.gateway.ctp import CtpGateway
        from vnpy.gateway.tiger import TigerGateway
        from vnpy.gateway.oes import OesGateway

        from vnpy.app.cta_strategy import CtaStrategyApp
        from vnpy.app.csv_loader import CsvLoaderApp


if __name__ == '__main__':
    unittest.main()
