import math
from datetime import datetime

import polars as pl

from vnpy.alpha.dataset.utility import calculate_by_expression


def sample_frame() -> pl.DataFrame:
    dates: list[datetime] = [
        datetime(2024, 1, 1),
        datetime(2024, 1, 2),
        datetime(2024, 1, 3),
    ]
    return pl.DataFrame(
        {
            "datetime": dates + dates,
            "vt_symbol": ["A", "A", "A", "B", "B", "B"],
            "close": [1.0, 3.0, 5.0, 4.0, 2.0, 8.0],
        }
    )


def data_values(frame: pl.DataFrame) -> list[float | None]:
    values: list[float | None] = []
    value: object
    for value in frame["data"].to_list():
        if value is None:
            values.append(None)
        else:
            values.append(float(value))
    return values


def assert_values(actual: list[float | None], expected: list[float | None]) -> None:
    assert len(actual) == len(expected)
    got: float | None
    want: float | None
    for got, want in zip(actual, expected, strict=True):
        if want is None:
            assert got is None
        else:
            assert got is not None
            assert math.isclose(got, want)


def test_delay_mean_and_rank_on_tiny_frame() -> None:
    frame: pl.DataFrame = sample_frame()

    delayed: pl.DataFrame = calculate_by_expression(frame, "ts_delay(close, 1)")
    averaged: pl.DataFrame = calculate_by_expression(frame, "ts_mean(close, 2)")
    ranked: pl.DataFrame = calculate_by_expression(frame, "cs_rank(close)")

    assert delayed["vt_symbol"].to_list() == ["A", "A", "A", "B", "B", "B"]
    assert_values(data_values(delayed), [None, 1.0, 3.0, None, 4.0, 2.0])
    assert_values(data_values(averaged), [1.0, 2.0, 4.0, 4.0, 3.0, 5.0])
    assert_values(data_values(ranked), [0.5, 1.0, 0.5, 1.0, 0.5, 1.0])
