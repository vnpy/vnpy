import json
from datetime import datetime
from pathlib import Path

import pytest

from vnpy.trader.constant import Exchange
from vnpy.trader.object import BarData, TickData
from vnpy.trader.utility import (
    BarGenerator,
    ceil_to,
    extract_vt_symbol,
    floor_to,
    generate_vt_symbol,
    get_file_path,
    load_json,
    round_to,
)


def test_extract_and_generate_vt_symbol() -> None:
    symbol, exchange = extract_vt_symbol("rb2410.SHFE")

    assert symbol == "rb2410"
    assert exchange == Exchange.SHFE
    assert generate_vt_symbol(symbol, exchange) == "rb2410.SHFE"

    option_symbol, option_exchange = extract_vt_symbol("IO2402-C-4000.CFFEX")
    assert option_symbol == "IO2402-C-4000"
    assert option_exchange == Exchange.CFFEX


def test_round_floor_and_ceil_to_price_tick() -> None:
    assert round_to(123.456, 0.01) == 123.46
    assert round_to(123.454, 0.01) == 123.45
    assert round_to(100.15, 0.1) == 100.2
    assert floor_to(123.459, 0.01) == 123.45
    assert ceil_to(123.451, 0.01) == 123.46


def test_bar_generator_builds_one_minute_bar_from_ticks() -> None:
    finished: list[BarData] = []
    generator: BarGenerator = BarGenerator(finished.append)

    generator.update_tick(
        TickData(
            gateway_name="FAKE",
            symbol="rb2410",
            exchange=Exchange.SHFE,
            datetime=datetime(2024, 1, 2, 9, 0, 5),
            last_price=100,
            volume=10,
        )
    )
    generator.update_tick(
        TickData(
            gateway_name="FAKE",
            symbol="rb2410",
            exchange=Exchange.SHFE,
            datetime=datetime(2024, 1, 2, 9, 0, 20),
            last_price=0,
            volume=99,
        )
    )
    generator.update_tick(
        TickData(
            gateway_name="FAKE",
            symbol="rb2410",
            exchange=Exchange.SHFE,
            datetime=datetime(2024, 1, 2, 9, 0, 40),
            last_price=110,
            volume=16,
            high_price=112,
            low_price=99,
        )
    )

    bar: BarData | None = generator.generate()

    assert bar is not None
    assert finished == [bar]
    assert bar.datetime == datetime(2024, 1, 2, 9, 0)
    assert bar.open_price == 100
    assert bar.high_price == 112
    assert bar.low_price == 100
    assert bar.close_price == 110
    assert bar.volume == 6
    assert bar.vt_symbol == "rb2410.SHFE"


def _fake_tick(
    dt: datetime,
    last_price: float,
    *,
    high_price: float = 0,
    low_price: float = 0,
    volume: float = 0,
    turnover: float = 0,
) -> TickData:
    return TickData(
        gateway_name="FAKE",
        symbol="rb2410",
        exchange=Exchange.SHFE,
        datetime=dt,
        last_price=last_price,
        high_price=high_price,
        low_price=low_price,
        volume=volume,
        turnover=turnover,
    )


def test_bar_generator_updates_same_minute_extremes_and_deltas() -> None:
    finished: list[BarData] = []
    generator: BarGenerator = BarGenerator(finished.append)

    generator.update_tick(_fake_tick(
        datetime(2024, 1, 2, 9, 0, 5),
        100,
        high_price=101,
        low_price=99,
        volume=10,
        turnover=1000,
    ))
    generator.update_tick(_fake_tick(
        datetime(2024, 1, 2, 9, 0, 40),
        100,
        high_price=103,
        low_price=97,
        volume=16,
        turnover=7000,
    ))

    bar: BarData | None = generator.generate()

    assert bar is not None
    assert bar.high_price == 103
    assert bar.low_price == 97
    assert bar.volume == 6
    assert bar.turnover == 6000
    assert finished == [bar]


def test_bar_generator_keeps_new_extreme_on_the_new_minute_bar() -> None:
    finished: list[BarData] = []
    generator: BarGenerator = BarGenerator(finished.append)

    generator.update_tick(_fake_tick(
        datetime(2024, 1, 2, 9, 0, 10),
        100,
        high_price=101,
        low_price=99,
    ))
    generator.update_tick(_fake_tick(
        datetime(2024, 1, 2, 9, 1, 0),
        100,
        high_price=105,
        low_price=95,
    ))
    generator.update_tick(_fake_tick(
        datetime(2024, 1, 2, 9, 1, 30),
        102,
        high_price=105,
        low_price=95,
    ))

    assert len(finished) == 1
    previous: BarData = finished[0]
    assert previous.high_price == 100
    assert previous.low_price == 100

    bar: BarData | None = generator.generate()

    assert bar is not None
    assert bar.high_price == 105
    assert bar.low_price == 95
    assert previous.high_price == 100
    assert previous.low_price == 100


def test_bar_generator_ignores_unchanged_day_extreme_on_a_new_minute() -> None:
    finished: list[BarData] = []
    generator: BarGenerator = BarGenerator(finished.append)

    generator.update_tick(_fake_tick(
        datetime(2024, 1, 2, 9, 0, 10),
        100,
        high_price=110,
        low_price=90,
    ))
    generator.update_tick(_fake_tick(
        datetime(2024, 1, 2, 9, 1, 5),
        102,
        high_price=110,
        low_price=90,
    ))

    assert len(finished) == 1
    previous: BarData = finished[0]
    assert previous.high_price == 100
    assert previous.low_price == 100

    bar: BarData | None = generator.generate()

    assert bar is not None
    assert bar.high_price == 102
    assert bar.low_price == 102


def test_bar_generator_ignores_day_extreme_and_cumulative_totals_on_the_first_tick() -> None:
    generator: BarGenerator = BarGenerator(lambda bar: None)

    generator.update_tick(_fake_tick(
        datetime(2024, 1, 2, 9, 30, 0),
        100,
        high_price=120,
        low_price=80,
        volume=5000,
        turnover=8_000_000,
    ))

    bar: BarData | None = generator.generate()

    assert bar is not None
    assert bar.high_price == 100
    assert bar.low_price == 100
    assert bar.volume == 0
    assert bar.turnover == 0


def test_bar_generator_ignores_zero_low_in_the_same_minute() -> None:
    generator: BarGenerator = BarGenerator(lambda bar: None)

    generator.update_tick(_fake_tick(
        datetime(2024, 1, 2, 9, 0, 1),
        100,
        high_price=102,
        low_price=96,
    ))
    generator.update_tick(_fake_tick(
        datetime(2024, 1, 2, 9, 0, 2),
        100,
        high_price=102,
        low_price=95,
    ))
    generator.update_tick(_fake_tick(
        datetime(2024, 1, 2, 9, 0, 3),
        100,
        high_price=102,
        low_price=0,
    ))

    bar: BarData | None = generator.generate()

    assert bar is not None
    assert bar.low_price == 95


def test_bar_generator_ignores_zero_low_on_a_new_minute() -> None:
    finished: list[BarData] = []
    generator: BarGenerator = BarGenerator(finished.append)

    generator.update_tick(_fake_tick(
        datetime(2024, 1, 2, 9, 0, 1),
        100,
        high_price=102,
        low_price=96,
    ))
    generator.update_tick(_fake_tick(
        datetime(2024, 1, 2, 9, 0, 2),
        100,
        high_price=102,
        low_price=95,
    ))
    generator.update_tick(_fake_tick(
        datetime(2024, 1, 2, 9, 1, 0),
        100,
        high_price=102,
        low_price=0,
    ))

    assert len(finished) == 1
    assert finished[0].low_price == 95

    bar: BarData | None = generator.generate()

    assert bar is not None
    assert bar.low_price == 100


def test_bar_generator_accepts_negative_extremes_in_the_same_minute() -> None:
    generator: BarGenerator = BarGenerator(lambda bar: None)

    generator.update_tick(_fake_tick(
        datetime(2024, 1, 2, 9, 0, 5),
        -6,
        high_price=-4,
        low_price=-8,
    ))
    generator.update_tick(_fake_tick(
        datetime(2024, 1, 2, 9, 0, 40),
        -6,
        high_price=-3,
        low_price=-10,
    ))

    bar: BarData | None = generator.generate()

    assert bar is not None
    assert bar.high_price == -3
    assert bar.low_price == -10


def test_bar_generator_accepts_negative_extremes_on_a_new_minute() -> None:
    finished: list[BarData] = []
    generator: BarGenerator = BarGenerator(finished.append)

    generator.update_tick(_fake_tick(
        datetime(2024, 1, 2, 9, 0, 5),
        -6,
        high_price=-4,
        low_price=-8,
    ))
    generator.update_tick(_fake_tick(
        datetime(2024, 1, 2, 9, 1, 0),
        -6,
        high_price=-3,
        low_price=-10,
    ))

    assert len(finished) == 1
    previous: BarData = finished[0]
    assert previous.high_price == -6
    assert previous.low_price == -6

    bar: BarData | None = generator.generate()

    assert bar is not None
    assert bar.high_price == -3
    assert bar.low_price == -10


def test_bar_generator_ignores_cumulative_total_rollback() -> None:
    generator: BarGenerator = BarGenerator(lambda bar: None)

    generator.update_tick(_fake_tick(
        datetime(2024, 1, 2, 9, 0, 1),
        100,
        volume=100,
        turnover=1000,
    ))
    generator.update_tick(_fake_tick(
        datetime(2024, 1, 2, 9, 0, 2),
        100,
        volume=110,
        turnover=7000,
    ))
    generator.update_tick(_fake_tick(
        datetime(2024, 1, 2, 9, 0, 3),
        100,
        volume=80,
        turnover=2000,
    ))

    bar: BarData | None = generator.generate()

    assert bar is not None
    assert bar.volume == 10
    assert bar.turnover == 6000


def test_bar_generator_absorbs_a_day_high_that_breaks_the_previous_session() -> None:
    finished: list[BarData] = []
    generator: BarGenerator = BarGenerator(finished.append)

    generator.update_tick(_fake_tick(
        datetime(2024, 1, 2, 14, 59, 50),
        3960,
        high_price=4000,
        low_price=3900,
        volume=100_000,
        turnover=5_000_000,
    ))
    generator.update_tick(_fake_tick(
        datetime(2024, 1, 3, 9, 0, 1),
        3960,
        high_price=4010,
        low_price=3950,
        volume=50,
        turnover=1000,
    ))

    assert len(finished) == 1
    assert finished[0].high_price == 3960
    assert finished[0].low_price == 3960

    bar: BarData | None = generator.generate()

    assert bar is not None
    assert bar.high_price == 4010
    assert bar.low_price == 3960
    assert bar.volume == 0
    assert bar.turnover == 0


def test_bar_generator_absorbs_a_day_low_that_breaks_the_previous_session() -> None:
    finished: list[BarData] = []
    generator: BarGenerator = BarGenerator(finished.append)

    generator.update_tick(_fake_tick(
        datetime(2024, 1, 2, 14, 59, 50),
        3960,
        high_price=4000,
        low_price=3900,
    ))
    generator.update_tick(_fake_tick(
        datetime(2024, 1, 3, 9, 0, 1),
        3960,
        high_price=3990,
        low_price=3890,
    ))

    assert len(finished) == 1
    assert finished[0].low_price == 3960

    bar: BarData | None = generator.generate()

    assert bar is not None
    assert bar.high_price == 3960
    assert bar.low_price == 3890


def test_bar_generator_ignores_a_day_range_inside_the_previous_session() -> None:
    finished: list[BarData] = []
    generator: BarGenerator = BarGenerator(finished.append)

    generator.update_tick(_fake_tick(
        datetime(2024, 1, 2, 14, 59, 50),
        3960,
        high_price=4000,
        low_price=3900,
        volume=100_000,
        turnover=5_000_000,
    ))
    generator.update_tick(_fake_tick(
        datetime(2024, 1, 3, 9, 0, 1),
        3960,
        high_price=3970,
        low_price=3940,
        volume=50,
        turnover=1000,
    ))

    assert len(finished) == 1
    assert finished[0].high_price == 3960
    assert finished[0].low_price == 3960

    bar: BarData | None = generator.generate()

    assert bar is not None
    assert bar.high_price == 3960
    assert bar.low_price == 3960
    assert bar.volume == 0
    assert bar.turnover == 0


def test_bar_generator_completes_five_minute_window() -> None:
    finished: list[BarData] = []
    generator: BarGenerator = BarGenerator(
        on_bar=lambda bar: None,
        window=5,
        on_window_bar=finished.append,
    )
    base: datetime = datetime(2024, 1, 2, 9, 0)
    prices: list[float] = [10, 12, 9, 11, 13]

    offset: int
    price: float
    for offset, price in enumerate(prices):
        generator.update_bar(
            BarData(
                gateway_name="FAKE",
                symbol="rb2410",
                exchange=Exchange.SHFE,
                datetime=base.replace(minute=offset),
                open_price=price,
                high_price=price + 1,
                low_price=price - 1,
                close_price=price,
                volume=float(offset + 1),
            )
        )

    assert len(finished) == 1
    window_bar: BarData = finished[0]
    assert window_bar.open_price == 10
    assert window_bar.high_price == 14
    assert window_bar.low_price == 8
    assert window_bar.close_price == 13
    assert window_bar.volume == 15
    assert window_bar.datetime == datetime(2024, 1, 2, 9, 0)


def test_load_json_writes_empty_object_when_file_is_missing() -> None:
    filename: str = "harness_missing_load_json.json"
    path: Path = get_file_path(filename)
    if path.exists():
        path.unlink()

    loaded: dict = load_json(filename)

    assert loaded == {}
    assert json.loads(path.read_text(encoding="UTF-8")) == {}


def test_extract_vt_symbol_rejects_unknown_exchange() -> None:
    with pytest.raises(ValueError):
        extract_vt_symbol("SYM.BAD")
