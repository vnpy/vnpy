from tests.chan_cases import make_fractal_case
from vnpy.chan import ChanBar
from vnpy.chan import FractalType
from vnpy.chan.fractal import detect_fractals


def test_detect_fractals_finds_top_and_bottom() -> None:
    fractals = detect_fractals(make_fractal_case())

    assert [fractal.type for fractal in fractals] == [
        FractalType.TOP,
        FractalType.BOTTOM,
    ]
    assert [fractal.bar_index for fractal in fractals] == [1, 3]
    assert [fractal.price for fractal in fractals] == [13, 8]


def test_detect_fractals_ignores_edge_bars() -> None:
    fractals = detect_fractals(make_fractal_case()[:2])

    assert fractals == []


def test_detect_fractals_does_not_duplicate_same_bar() -> None:
    fractals = detect_fractals(make_fractal_case())
    indexes = [fractal.bar_index for fractal in fractals]

    assert len(indexes) == len(set(indexes))


def test_detect_fractals_requires_strict_high_low_relationship() -> None:
    base = make_fractal_case()
    equal_high_bars = [
        base[0],
        ChanBar(
            index=1,
            datetime=base[1].datetime,
            open_price=10.5,
            high_price=11,
            low_price=10,
            close_price=10.8,
            source_indexes=(1,),
        ),
        base[2],
    ]

    assert detect_fractals(equal_high_bars) == []
