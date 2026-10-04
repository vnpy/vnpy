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
