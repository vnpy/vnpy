""""""
from .database import BaseDatabaseManager, Driver


def init(settings: dict) -> BaseDatabaseManager:
    driver = Driver(settings["driver"])
    if driver is Driver.MONGODB:
        return init_mongo(driver=driver, settings=settings)
    elif driver is Driver.INFLUX:
        return init_influx(driver=driver, settings=settings)
    elif driver is Driver.TIMESCALEDB:
        return init_timescaledb(driver=driver, settings=settings)
    else:
        return init_sql(driver=driver, settings=settings)


def init_sql(driver: Driver, settings: dict):
    from .database_sql import init
    keys = {'database', "host", "port", "user", "password"}
    settings = {k: v for k, v in settings.items() if k in keys}
    _database_manager = init(driver, settings)
    return _database_manager


def init_mongo(driver: Driver, settings: dict):
    from .database_mongo import init
    _database_manager = init(driver, settings=settings)
    return _database_manager


def init_influx(driver: Driver, settings: dict):
    from .database_influx import init
    _database_manager = init(driver, settings=settings)
    return _database_manager

def init_timescaledb(driver: Driver, settings: dict):
    from .database_timescaledb import init
    _database_manager = init(driver, settings=settings)
    return _database_manager
