import vnpy.trader.database as database_module
import vnpy.trader.datafeed as datafeed_module
from vnpy.trader.datafeed import BaseDatafeed, get_datafeed
from vnpy.trader.database import BaseDatabase, get_database
from vnpy.trader.setting import SETTINGS
from vnpy_sqlite import Database as SqliteDatabase


def test_get_datafeed_empty_name_returns_base_singleton() -> None:
    saved_database: BaseDatabase | None = database_module.database
    saved_datafeed: BaseDatafeed | None = datafeed_module.datafeed
    saved_database_name: object = SETTINGS["database.name"]
    saved_datafeed_name: object = SETTINGS["datafeed.name"]
    try:
        datafeed_module.datafeed = None
        SETTINGS["datafeed.name"] = ""
        first: BaseDatafeed = get_datafeed()
        second: BaseDatafeed = get_datafeed()
        assert type(first) is BaseDatafeed
        assert second is first
    finally:
        database_module.database = saved_database
        datafeed_module.datafeed = saved_datafeed
        SETTINGS["database.name"] = saved_database_name
        SETTINGS["datafeed.name"] = saved_datafeed_name


def test_get_datafeed_missing_module_returns_base_singleton() -> None:
    saved_database: BaseDatabase | None = database_module.database
    saved_datafeed: BaseDatafeed | None = datafeed_module.datafeed
    saved_database_name: object = SETTINGS["database.name"]
    saved_datafeed_name: object = SETTINGS["datafeed.name"]
    try:
        datafeed_module.datafeed = None
        SETTINGS["datafeed.name"] = "zz_missing_datafeed_for_test"
        first: BaseDatafeed = get_datafeed()
        second: BaseDatafeed = get_datafeed()
        assert type(first) is BaseDatafeed
        assert second is first
    finally:
        database_module.database = saved_database
        datafeed_module.datafeed = saved_datafeed
        SETTINGS["database.name"] = saved_database_name
        SETTINGS["datafeed.name"] = saved_datafeed_name


def test_get_database_missing_module_falls_back_to_sqlite() -> None:
    saved_database: BaseDatabase | None = database_module.database
    saved_datafeed: BaseDatafeed | None = datafeed_module.datafeed
    saved_database_name: object = SETTINGS["database.name"]
    saved_datafeed_name: object = SETTINGS["datafeed.name"]
    try:
        database_module.database = None
        SETTINGS["database.name"] = "zz_missing_database_for_test"
        first: BaseDatabase = get_database()
        second: BaseDatabase = get_database()
        assert type(first) is SqliteDatabase
        assert second is first
    finally:
        created: BaseDatabase | None = database_module.database
        if type(created) is SqliteDatabase:
            created.db.close()
        database_module.database = saved_database
        datafeed_module.datafeed = saved_datafeed
        SETTINGS["database.name"] = saved_database_name
        SETTINGS["datafeed.name"] = saved_datafeed_name
