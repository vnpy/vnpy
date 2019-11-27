"""
Test if csv loader works fine
"""
import tempfile
import unittest

from vnpy.app.csv_loader import CsvLoaderEngine
from vnpy.trader.constant import Exchange, Interval


class TestCsvLoader(unittest.TestCase):

    def setUp(self) -> None:
        self.engine = CsvLoaderEngine(None, None)  # no engine is necessary for CsvLoader

    def test_load(self):
        data = """"Datetime","Open","High","Low","Close","Volume"
2010-04-16 09:16:00,3450.0,3488.0,3450.0,3468.0,489
2010-04-16 09:17:00,3468.0,3473.8,3467.0,3467.0,302
2010-04-16 09:18:00,3467.0,3471.0,3466.0,3467.0,203
2010-04-16 09:19:00,3467.0,3468.2,3448.0,3448.0,280
2010-04-16 09:20:00,3448.0,3459.0,3448.0,3454.0,250
2010-04-16 09:21:00,3454.0,3456.8,3454.0,3456.8,109
"""
        with tempfile.TemporaryFile("w+t") as f:
            f.write(data)
            f.seek(0)

            self.engine.load_by_handle(
                f,
                symbol="1",
                exchange=Exchange.BITMEX,
                interval=Interval.MINUTE,
                datetime_head="Datetime",
                open_head="Open",
                close_head="Close",
                low_head="Low",
                high_head="High",
                volume_head="Volume",
                datetime_format="%Y-%m-%d %H:%M:%S",
            )

    def test_load_duplicated(self):
        data = """"Datetime","Open","High","Low","Close","Volume"
2010-04-16 09:16:00,3450.0,3488.0,3450.0,3468.0,489
2010-04-16 09:17:00,3468.0,3473.8,3467.0,3467.0,302
2010-04-16 09:18:00,3467.0,3471.0,3466.0,3467.0,203
2010-04-16 09:19:00,3467.0,3468.2,3448.0,3448.0,280
2010-04-16 09:20:00,3448.0,3459.0,3448.0,3454.0,250
2010-04-16 09:21:00,3454.0,3456.8,3454.0,3456.8,109
"""
        with tempfile.TemporaryFile("w+t") as f:
            f.write(data)
            f.seek(0)

            self.engine.load_by_handle(
                f,
                symbol="1",
                exchange=Exchange.BITMEX,
                interval=Interval.MINUTE,
                datetime_head="Datetime",
                open_head="Open",
                close_head="Close",
                low_head="Low",
                high_head="High",
                volume_head="Volume",
                datetime_format="%Y-%m-%d %H:%M:%S",
            )

        with tempfile.TemporaryFile("w+t") as f:
            f.write(data)
            f.seek(0)

            self.engine.load_by_handle(
                f,
                symbol="1",
                exchange=Exchange.BITMEX,
                interval=Interval.MINUTE,
                datetime_head="Datetime",
                open_head="Open",
                close_head="Close",
                low_head="Low",
                high_head="High",
                volume_head="Volume",
                datetime_format="%Y-%m-%d %H:%M:%S",
            )


if __name__ == "__main__":
    unittest.main()
