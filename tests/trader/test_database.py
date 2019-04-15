"""
Test if database works fine
"""
import os
import unittest
from datetime import datetime, timedelta

from vnpy.trader.constant import Exchange, Interval
from vnpy.trader.database.database import Driver
from vnpy.trader.object import BarData, TickData

os.environ['VNPY_TESTING'] = '1'

profiles = {
    Driver.SQLITE: {
        "driver": "sqlite",
        "database": "test_db.db",
    }
}
if 'VNPY_TEST_ONLY_SQLITE' not in os.environ:
    profiles.update({
        Driver.MYSQL: {
            "driver": "mysql",
            "database": os.environ['VNPY_TEST_MYSQL_DATABASE'],
            "host": os.environ['VNPY_TEST_MYSQL_HOST'],
            "port": int(os.environ['VNPY_TEST_MYSQL_PORT']),
            "user": os.environ["VNPY_TEST_MYSQL_USER"],
            "password": os.environ['VNPY_TEST_MYSQL_PASSWORD'],
        },
        Driver.POSTGRESQL: {
            "driver": "postgresql",
            "database": os.environ['VNPY_TEST_POSTGRESQL_DATABASE'],
            "host": os.environ['VNPY_TEST_POSTGRESQL_HOST'],
            "port": int(os.environ['VNPY_TEST_POSTGRESQL_PORT']),
            "user": os.environ["VNPY_TEST_POSTGRESQL_USER"],
            "password": os.environ['VNPY_TEST_POSTGRESQL_PASSWORD'],
        },
        Driver.MONGODB: {
            "driver": "mongodb",
            "database": os.environ['VNPY_TEST_MONGODB_DATABASE'],
            "host": os.environ['VNPY_TEST_MONGODB_HOST'],
            "port": int(os.environ['VNPY_TEST_MONGODB_PORT']),
            "user": "",
            "password": "",
            "authentication_source": "",
        },
    })


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

    def test_upsert_bar(self):
        for driver, settings in profiles.items():
            with self.subTest(driver=driver, settings=settings):
                self.connect(settings)
                self.manager.save_bar_data([bar])
                self.manager.save_bar_data([bar])

    def test_save_load_bar(self):
        for driver, settings in profiles.items():
            with self.subTest(driver=driver, settings=settings):
                self.connect(settings)
                # save first
                self.manager.save_bar_data([bar])

                # and load
                results = self.manager.load_bar_data(
                    symbol=bar.symbol,
                    exchange=bar.exchange,
                    interval=bar.interval,
                    start=bar.datetime - timedelta(seconds=1),  # time is not accuracy
                    end=now() + timedelta(seconds=1),  # time is not accuracy
                )
                count = len(results)
                self.assertNotEqual(count, 0)

    def test_upsert_tick(self):
        for driver, settings in profiles.items():
            with self.subTest(driver=driver, settings=settings):
                self.connect(settings)
                self.manager.save_tick_data([tick])
                self.manager.save_tick_data([tick])

    def test_save_load_tick(self):
        for driver, settings in profiles.items():
            with self.subTest(driver=driver, settings=settings):
                self.connect(settings)
                # save first
                self.manager.save_tick_data([tick])

                # and load
                results = self.manager.load_tick_data(
                    symbol=bar.symbol,
                    exchange=bar.exchange,
                    start=bar.datetime - timedelta(seconds=1),  # time is not accuracy
                    end=now() + timedelta(seconds=1),  # time is not accuracy
                )
                count = len(results)
                self.assertNotEqual(count, 0)


if __name__ == '__main__':
    unittest.main()
