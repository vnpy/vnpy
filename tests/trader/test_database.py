"""
Test if database works fine
"""
import os
import unittest
from copy import copy
from datetime import datetime, timedelta

from vnpy.trader.constant import Exchange, Interval
from vnpy.trader.database.database import Driver
from vnpy.trader.object import BarData, TickData

os.environ["VNPY_TESTING"] = "1"

profiles = {Driver.SQLITE: {"driver": "sqlite", "database": "test_db.db"}}
if "VNPY_TEST_ONLY_SQLITE" not in os.environ:
    profiles.update(
        {
            Driver.MYSQL: {
                "driver": "mysql",
                "database": os.environ["VNPY_TEST_MYSQL_DATABASE"],
                "host": os.environ["VNPY_TEST_MYSQL_HOST"],
                "port": int(os.environ["VNPY_TEST_MYSQL_PORT"]),
                "user": os.environ["VNPY_TEST_MYSQL_USER"],
                "password": os.environ["VNPY_TEST_MYSQL_PASSWORD"],
            },
            Driver.POSTGRESQL: {
                "driver": "postgresql",
                "database": os.environ["VNPY_TEST_POSTGRESQL_DATABASE"],
                "host": os.environ["VNPY_TEST_POSTGRESQL_HOST"],
                "port": int(os.environ["VNPY_TEST_POSTGRESQL_PORT"]),
                "user": os.environ["VNPY_TEST_POSTGRESQL_USER"],
                "password": os.environ["VNPY_TEST_POSTGRESQL_PASSWORD"],
            },
            Driver.MONGODB: {
                "driver": "mongodb",
                "database": os.environ["VNPY_TEST_MONGODB_DATABASE"],
                "host": os.environ["VNPY_TEST_MONGODB_HOST"],
                "port": int(os.environ["VNPY_TEST_MONGODB_PORT"]),
                "user": "",
                "password": "",
                "authentication_source": "",
            },
        }
    )


def now():
    return datetime.utcnow()


bar = BarData(
    gateway_name="DB",
    symbol="test_symbol",
    exchange=Exchange.BITMEX,
    datetime=now(),
    interval=Interval.MINUTE,
)

tick = TickData(
    gateway_name="DB",
    symbol="test_symbol",
    exchange=Exchange.BITMEX,
    datetime=now(),
    name="DB_test_symbol",
)


class TestDatabase(unittest.TestCase):

    def connect(self, settings: dict):
        from vnpy.trader.database.initialize import init  # noqa

        self.manager = init(settings)

    def assertBarCount(self, count, msg):
        bars = self.manager.load_bar_data(
            symbol=bar.symbol,
            exchange=bar.exchange,
            interval=bar.interval,
            start=bar.datetime - timedelta(days=1),
            end=now()
        )
        self.assertEqual(count, len(bars), msg)

    def assertTickCount(self, count, msg):
        ticks = self.manager.load_tick_data(
            symbol=bar.symbol,
            exchange=bar.exchange,
            start=bar.datetime - timedelta(days=1),
            end=now()
        )
        self.assertEqual(count, len(ticks), msg)

    def assertNoData(self, msg):
        self.assertBarCount(0, msg)
        self.assertTickCount(0, msg)

    def setUp(self) -> None:
        # clean all data first
        for driver, settings in profiles.items():
            self.connect(settings)
            self.manager.clean(bar.symbol)
            self.assertNoData("Failed to clean data!")
            self.manager = None

    def tearDown(self) -> None:
        self.manager.clean(bar.symbol)
        self.assertNoData("Failed to clean data!")

    def test_upsert_bar(self):
        for driver, settings in profiles.items():
            with self.subTest(driver=driver, settings=settings):
                self.connect(settings)
                self.manager.save_bar_data([bar])
                self.manager.save_bar_data([bar])
                self.assertBarCount(1, "there should be only one item after upsert")

    def test_save_load_bar(self):
        for driver, settings in profiles.items():
            with self.subTest(driver=driver, settings=settings):
                self.connect(settings)
                # save first
                self.manager.save_bar_data([bar])

                self.assertBarCount(1, "there should be only one item after save")

    def test_upsert_tick(self):
        for driver, settings in profiles.items():
            with self.subTest(driver=driver, settings=settings):
                self.connect(settings)
                self.manager.save_tick_data([tick])
                self.manager.save_tick_data([tick])
                self.assertTickCount(1, "there should be only one item after upsert")

    def test_save_load_tick(self):
        for driver, settings in profiles.items():
            with self.subTest(driver=driver, settings=settings):
                self.connect(settings)
                # save first
                self.manager.save_tick_data([tick])

                self.assertTickCount(1, "there should be only one item after save")

    def test_newest_bar(self):
        for driver, settings in profiles.items():
            with self.subTest(driver=driver, settings=settings):
                self.connect(settings)
                got = self.manager.get_newest_bar_data(bar.symbol, bar.exchange, bar.interval)
                self.assertIsNone(
                    got,
                    "database is empty, but return value for newest_bar_data() is not a None"
                )

                # an older one
                older_one = copy(bar)
                older_one.volume = 123.0
                older_one.datetime = now() - timedelta(days=1)

                # and a newer one
                newer_one = copy(bar)
                newer_one.volume = 456.0
                newer_one.datetime = now()
                self.manager.save_bar_data([older_one, newer_one])

                got = self.manager.get_newest_bar_data(
                    bar.symbol, bar.exchange, bar.interval
                )
                self.assertEqual(got.volume, newer_one.volume, "the newest bar we got mismatched")

    def test_newest_tick(self):
        for driver, settings in profiles.items():
            with self.subTest(driver=driver, settings=settings):
                self.connect(settings)

                got = self.manager.get_newest_tick_data(tick.symbol, tick.exchange)
                self.assertIsNone(
                    got,
                    "database is empty, but return value for newest_tick_data() is not a None"
                )
                # an older one
                older_one = copy(tick)
                older_one.volume = 123
                older_one.datetime = now() - timedelta(days=1)

                # and a newer one
                newer_one = copy(tick)
                older_one.volume = 456
                newer_one.datetime = now()
                self.manager.save_tick_data([older_one, newer_one])

                got = self.manager.get_newest_tick_data(tick.symbol, tick.exchange)
                self.assertEqual(got.volume, newer_one.volume, "the newest tick we got mismatched")


if __name__ == "__main__":
    unittest.main()
