# flake8: noqa
import platform
import unittest


# noinspection PyUnresolvedReferences,PyMethodMayBeStatic
class CoreImportTest(unittest.TestCase):

    def test_import_event_engine(self):
        from vnpy.event import EventEngine

    def test_import_main_engine(self):
        from vnpy.trader.engine import MainEngine

    def test_import_ui(self):
        from vnpy.trader.ui import MainWindow, create_qapp


# noinspection PyUnresolvedReferences,PyMethodMayBeStatic
class GatewayImportTest(unittest.TestCase):

    def test_import_binance(self):
        from vnpy.gateway.binance import BinanceGateway

    def test_import_bitfinex(self):
        from vnpy.gateway.bitfinex import BitfinexGateway

    def test_import_bitmex(self):
        from vnpy.gateway.bitmex import BitmexGateway

    @unittest.skipIf(platform.system() == "Darwin", "Not supported yet under osx")
    def test_import_ctp(self):
        from vnpy.gateway.ctp import CtpGateway

    @unittest.skipIf(platform.system() == "Darwin", "Not supported yet under osx")
    def test_import_ctptest(self):
        from vnpy.gateway.ctptest import CtptestGateway

    @unittest.skipIf(platform.system() == "Darwin", "Not supported yet under osx")
    @unittest.skipIf(platform.system() == "Linux", "Not supported yet under Linux")
    def test_import_femas(self):
        from vnpy.gateway.femas import FemasGateway

    def test_import_futu(self):
        from vnpy.gateway.futu import FutuGateway

    def test_import_hbdm(self):
        from vnpy.gateway.hbdm import HbdmGateway

    def test_import_huobi(self):
        from vnpy.gateway.huobi import HuobiGateway

    def test_import_ib(self):
        from vnpy.gateway.ib import IbGateway

    @unittest.skipIf(platform.system() == "Darwin", "Not supported yet under osx")
    def test_import_oes(self):
        from vnpy.gateway.oes import OesGateway

    def test_import_okex(self):
        from vnpy.gateway.okex import OkexGateway

    def test_import_okexf(self):
        from vnpy.gateway.okexf import OkexfGateway

    def test_import_onetoken(self):
        from vnpy.gateway.onetoken import OnetokenGateway

    @unittest.skipIf(platform.system() == "Darwin", "Not supported yet under osx")
    @unittest.skipIf(platform.system() == "Linux", "Not supported yet under Linux")
    def test_import_tap(self):
        from vnpy.gateway.tap import TapGateway

    def test_import_tiger(self):
        from vnpy.gateway.tiger import TigerGateway

    @unittest.skipIf(platform.system() == "Darwin", "Not supported yet under osx")
    def test_import_tora(self):
        from vnpy.gateway.tora import ToraGateway

    def test_import_xtp(self):
        from vnpy.gateway.xtp import XtpGateway


# noinspection PyUnresolvedReferences,PyMethodMayBeStatic
class AppImportTest(unittest.TestCase):

    def test_import_cta_strategy_app(self):
        from vnpy.app.cta_strategy import CtaStrategyApp

    def test_import_csv_loader_app(self):
        from vnpy.app.csv_loader import CsvLoaderApp


if __name__ == '__main__':
    unittest.main()
