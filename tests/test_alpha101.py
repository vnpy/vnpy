import pytest
import polars as pl
import numpy as np
from datetime import datetime, timedelta

from vnpy.alpha.dataset.utility import calculate_by_expression


def create_test_df(n_symbols: int = 50, n_days: int = 300) -> pl.DataFrame:
    """
    创建测试用 DataFrame，包含极端值

    结构：datetime, vt_symbol, open, high, low, close, volume, vwap
    """
    np.random.seed(42)

    symbols = [f"SH.{600000 + i}" for i in range(n_symbols)]
    dates = [datetime(2023, 1, 1) + timedelta(days=i) for i in range(n_days)]

    data = []
    for sym_idx, symbol in enumerate(symbols):
        # 每个股票的基础价格
        base_price = 10 + np.random.rand() * 90

        for day_idx, dt in enumerate(dates):
            # 生成随机价格
            change = (np.random.rand() - 0.5) * 0.1
            close = base_price * (1 + change)
            high = close * (1 + np.random.rand() * 0.03)
            low = close * (1 - np.random.rand() * 0.03)
            open_price = low + (high - low) * np.random.rand()
            volume = float(np.random.randint(100000, 10000000))
            vwap = (high + low + close) / 3

            # 插入极端值（每个股票的特定位置）
            if day_idx == 50 + sym_idx % 10:  # NaN
                close = np.nan
            elif day_idx == 100 + sym_idx % 10:  # 0 值
                volume = 0.0
            elif day_idx == 150 + sym_idx % 10:  # 极小值
                close = 1e-10

            data.append({
                "datetime": dt,
                "vt_symbol": symbol,
                "open": open_price,
                "high": high,
                "low": low,
                "close": close,
                "volume": volume,
                "vwap": vwap
            })

            if not np.isnan(close):
                base_price = close

    return pl.DataFrame(data)


@pytest.fixture(scope="module")
def test_df() -> pl.DataFrame:
    """创建测试数据：50个合约，300天，包含极端值"""
    return create_test_df(n_symbols=50, n_days=300)


returns_expr = "(close / ts_delay(close, 1) - 1)"


class TestAlpha101:
    """Alpha 101 因子测试"""

    def test_alpha1(self, test_df: pl.DataFrame) -> None:
        """测试 Alpha#1"""
        expr = f"(cs_rank(ts_argmax(pow1(quesval(0, {returns_expr}, close, ts_std({returns_expr}, 20)), 2.0), 5)) - 0.5)"
        result = calculate_by_expression(test_df, expr)
        assert "data" in result.columns

    def test_alpha2(self, test_df: pl.DataFrame) -> None:
        """测试 Alpha#2"""
        expr = "(-1) * ts_corr(cs_rank(ts_delta(log(volume), 2)), cs_rank((close - open) / open), 6)"
        result = calculate_by_expression(test_df, expr)
        assert "data" in result.columns

    def test_alpha3(self, test_df: pl.DataFrame) -> None:
        """测试 Alpha#3"""
        expr = "ts_corr(cs_rank(open), cs_rank(volume), 10) * -1"
        result = calculate_by_expression(test_df, expr)
        assert "data" in result.columns

    def test_alpha4(self, test_df: pl.DataFrame) -> None:
        """测试 Alpha#4"""
        expr = "-1 * ts_rank(cs_rank(low), 9)"
        result = calculate_by_expression(test_df, expr)
        assert "data" in result.columns

    def test_alpha5(self, test_df: pl.DataFrame) -> None:
        """测试 Alpha#5"""
        expr = "cs_rank((open - (ts_sum(vwap, 10) / 10))) * (-1 * abs(cs_rank((close - vwap))))"
        result = calculate_by_expression(test_df, expr)
        assert "data" in result.columns

    def test_alpha6(self, test_df: pl.DataFrame) -> None:
        """测试 Alpha#6"""
        expr = "(-1) * ts_corr(open, volume, 10)"
        result = calculate_by_expression(test_df, expr)
        assert "data" in result.columns

    def test_alpha7(self, test_df: pl.DataFrame) -> None:
        """测试 Alpha#7"""
        expr = "quesval2(ts_mean(volume, 20), volume, (-1 * ts_rank(abs(close - ts_delay(close, 7)), 60)) * sign(ts_delta(close, 7)), -1)"
        result = calculate_by_expression(test_df, expr)
        assert "data" in result.columns

    def test_alpha8(self, test_df: pl.DataFrame) -> None:
        """测试 Alpha#8"""
        expr = f"-1 * cs_rank(((ts_sum(open, 5) * ts_sum({returns_expr}, 5)) - ts_delay((ts_sum(open, 5) * ts_sum({returns_expr}, 5)), 10)))"
        result = calculate_by_expression(test_df, expr)
        assert "data" in result.columns

    def test_alpha9(self, test_df: pl.DataFrame) -> None:
        """测试 Alpha#9"""
        expr = "quesval(0, ts_min(ts_delta(close, 1), 5), ts_delta(close, 1), quesval(0, ts_max(ts_delta(close, 1), 5), (-1 * ts_delta(close, 1)), ts_delta(close, 1)))"
        result = calculate_by_expression(test_df, expr)
        assert "data" in result.columns

    def test_alpha10(self, test_df: pl.DataFrame) -> None:
        """测试 Alpha#10"""
        expr = "cs_rank(quesval(0, ts_min(ts_delta(close, 1), 4), ts_delta(close, 1), quesval(0, ts_max(ts_delta(close, 1), 4), (-1 * ts_delta(close, 1)), ts_delta(close, 1))))"
        result = calculate_by_expression(test_df, expr)
        assert "data" in result.columns

    def test_alpha11(self, test_df: pl.DataFrame) -> None:
        """测试 Alpha#11"""
        expr = "(cs_rank(ts_max(vwap - close, 3)) + cs_rank(ts_min(vwap - close, 3))) * cs_rank(ts_delta(volume, 3))"
        result = calculate_by_expression(test_df, expr)
        assert "data" in result.columns

    def test_alpha12(self, test_df: pl.DataFrame) -> None:
        """测试 Alpha#12"""
        expr = "sign(ts_delta(volume, 1)) * (-1 * ts_delta(close, 1))"
        result = calculate_by_expression(test_df, expr)
        assert "data" in result.columns

    def test_alpha13(self, test_df: pl.DataFrame) -> None:
        """测试 Alpha#13"""
        expr = "-1 * cs_rank(ts_cov(cs_rank(close), cs_rank(volume), 5))"
        result = calculate_by_expression(test_df, expr)
        assert "data" in result.columns

    def test_alpha14(self, test_df: pl.DataFrame) -> None:
        """测试 Alpha#14"""
        expr = f"(-1 * cs_rank(({returns_expr}) - ts_delay({returns_expr}, 3))) * ts_corr(open, volume, 10)"
        result = calculate_by_expression(test_df, expr)
        assert "data" in result.columns

    def test_alpha15(self, test_df: pl.DataFrame) -> None:
        """测试 Alpha#15"""
        expr = "-1 * ts_sum(cs_rank(ts_corr(cs_rank(high), cs_rank(volume), 3)), 3)"
        result = calculate_by_expression(test_df, expr)
        assert "data" in result.columns

    def test_alpha16(self, test_df: pl.DataFrame) -> None:
        """测试 Alpha#16"""
        expr = "-1 * cs_rank(ts_cov(cs_rank(high), cs_rank(volume), 5))"
        result = calculate_by_expression(test_df, expr)
        assert "data" in result.columns

    def test_alpha17(self, test_df: pl.DataFrame) -> None:
        """测试 Alpha#17"""
        expr = "(-1 * cs_rank(ts_rank(close, 10))) * cs_rank(close - 2 * ts_delay(close, 1) + ts_delay(close, 2)) * cs_rank(ts_rank(volume / ts_mean(volume, 20), 5))"
        result = calculate_by_expression(test_df, expr)
        assert "data" in result.columns

    def test_alpha18(self, test_df: pl.DataFrame) -> None:
        """测试 Alpha#18"""
        expr = "-1 * cs_rank((ts_std(abs(close - open), 5) + (close - open)) + ts_corr(close, open, 10))"
        result = calculate_by_expression(test_df, expr)
        assert "data" in result.columns

    def test_alpha19(self, test_df: pl.DataFrame) -> None:
        """测试 Alpha#19"""
        expr = f"(-1 * sign(ts_delta(close, 7) + (close - ts_delay(close, 7)))) * (cs_rank(ts_sum({returns_expr}, 250) + 1) + 1)"
        result = calculate_by_expression(test_df, expr)
        assert "data" in result.columns

    def test_alpha20(self, test_df: pl.DataFrame) -> None:
        """测试 Alpha#20"""
        expr = "(-1 * cs_rank(open - ts_delay(high, 1))) * cs_rank(open - ts_delay(close, 1)) * cs_rank(open - ts_delay(low, 1))"
        result = calculate_by_expression(test_df, expr)
        assert "data" in result.columns

    def test_alpha21(self, test_df: pl.DataFrame) -> None:
        """测试 Alpha#21"""
        expr = "quesval2((ts_mean(close, 8) + ts_std(close, 8)), ts_mean(close, 2), -1, quesval2(ts_mean(close, 2), (ts_mean(close, 8) - ts_std(close, 8)), 1, quesval(1, (volume / ts_mean(volume, 20)), 1, -1)))"
        result = calculate_by_expression(test_df, expr)
        assert "data" in result.columns

    def test_alpha22(self, test_df: pl.DataFrame) -> None:
        """测试 Alpha#22"""
        expr = "-1 * ts_delta(ts_corr(high, volume, 5), 5) * cs_rank(ts_std(close, 20))"
        result = calculate_by_expression(test_df, expr)
        assert "data" in result.columns

    def test_alpha23(self, test_df: pl.DataFrame) -> None:
        """测试 Alpha#23"""
        expr = "quesval2(ts_mean(high, 20), high, -1 * ts_delta(high, 2), 0)"
        result = calculate_by_expression(test_df, expr)
        assert "data" in result.columns

    def test_alpha24(self, test_df: pl.DataFrame) -> None:
        """测试 Alpha#24"""
        expr = "quesval(0.05, ts_delta(ts_sum(close, 100) / 100, 100) / ts_delay(close, 100), (-1 * ts_delta(close, 3)), (-1 * (close - ts_min(close, 100))))"
        result = calculate_by_expression(test_df, expr)
        assert "data" in result.columns

    def test_alpha25(self, test_df: pl.DataFrame) -> None:
        """测试 Alpha#25"""
        expr = f"cs_rank( (-1 * {returns_expr}) * ts_mean(volume, 20) * vwap * (high - close) )"
        result = calculate_by_expression(test_df, expr)
        assert "data" in result.columns

    def test_alpha26(self, test_df: pl.DataFrame) -> None:
        """测试 Alpha#26"""
        expr = "-1 * ts_max(ts_corr(ts_rank(volume, 5), ts_rank(high, 5), 5), 3)"
        result = calculate_by_expression(test_df, expr)
        assert "data" in result.columns

    def test_alpha27(self, test_df: pl.DataFrame) -> None:
        """测试 Alpha#27"""
        expr = "quesval(0.5, cs_rank(ts_mean(ts_corr(cs_rank(volume), cs_rank(vwap), 6), 2)), -1, 1)"
        result = calculate_by_expression(test_df, expr)
        assert "data" in result.columns

    def test_alpha28(self, test_df: pl.DataFrame) -> None:
        """测试 Alpha#28"""
        expr = "cs_scale(ts_corr(ts_mean(volume, 20), low, 5) + (high + low) / 2 - close)"
        result = calculate_by_expression(test_df, expr)
        assert "data" in result.columns

    def test_alpha29(self, test_df: pl.DataFrame) -> None:
        """测试 Alpha#29"""
        expr = f"ts_min(ts_product(cs_rank(cs_rank(cs_scale(log(ts_sum(ts_min(cs_rank(cs_rank((-1 * cs_rank(ts_delta((close - 1), 5))))), 2), 1))))), 1), 5) + ts_rank(ts_delay((-1 * {returns_expr}), 6), 5)"
        result = calculate_by_expression(test_df, expr)
        assert "data" in result.columns

    def test_alpha30(self, test_df: pl.DataFrame) -> None:
        """测试 Alpha#30"""
        expr = "((cs_rank(sign(close - ts_delay(close, 1)) + sign(ts_delay(close, 1) - ts_delay(close, 2)) + sign(ts_delay(close, 2) - ts_delay(close, 3))) * -1 + 1) * ts_sum(volume, 5)) / ts_sum(volume, 20)"
        result = calculate_by_expression(test_df, expr)
        assert "data" in result.columns

    def test_alpha31(self, test_df: pl.DataFrame) -> None:
        """测试 Alpha#31"""
        expr = "(cs_rank(cs_rank(cs_rank(ts_decay_linear((-1) * cs_rank(cs_rank(ts_delta(close, 10))), 10)))) + cs_rank((-1) * ts_delta(close, 3))) + sign(cs_scale(ts_corr(ts_mean(volume, 20), low, 12)))"
        result = calculate_by_expression(test_df, expr)
        assert "data" in result.columns

    def test_alpha32(self, test_df: pl.DataFrame) -> None:
        """测试 Alpha#32"""
        expr = "cs_scale((ts_sum(close, 7) / 7 - close)) + (20 * cs_scale(ts_corr(vwap, ts_delay(close, 5), 230)))"
        result = calculate_by_expression(test_df, expr)
        assert "data" in result.columns

    def test_alpha33(self, test_df: pl.DataFrame) -> None:
        """测试 Alpha#33"""
        expr = "cs_rank((-1) * (open / close * -1 + 1))"
        result = calculate_by_expression(test_df, expr)
        assert "data" in result.columns

    def test_alpha34(self, test_df: pl.DataFrame) -> None:
        """测试 Alpha#34"""
        expr = f"cs_rank((cs_rank(ts_std({returns_expr}, 2) / ts_std({returns_expr}, 5)) * -1 + 1) + (cs_rank(ts_delta(close, 1)) * -1 + 1))"
        result = calculate_by_expression(test_df, expr)
        assert "data" in result.columns

    def test_alpha35(self, test_df: pl.DataFrame) -> None:
        """测试 Alpha#35"""
        expr = f"(ts_rank(volume, 32) * (ts_rank((close + high - low), 16) * -1 + 1)) * (ts_rank({returns_expr}, 32) * -1 + 1)"
        result = calculate_by_expression(test_df, expr)
        assert "data" in result.columns

    def test_alpha36(self, test_df: pl.DataFrame) -> None:
        """测试 Alpha#36"""
        expr = f"((((2.21 * cs_rank(ts_corr((close - open), ts_delay(volume, 1), 15))) + (0.7 * cs_rank((open - close)))) + (0.73 * cs_rank(ts_rank(ts_delay((-1) * {returns_expr}, 6), 5)))) + cs_rank(abs(ts_corr(vwap, ts_mean(volume, 20), 6)))) + (0.6 * cs_rank(((ts_sum(close, 200) / 200 - open) * (close - open))))"
        result = calculate_by_expression(test_df, expr)
        assert "data" in result.columns

    def test_alpha37(self, test_df: pl.DataFrame) -> None:
        """测试 Alpha#37"""
        expr = "cs_rank(ts_corr(ts_delay((open - close), 1), close, 200)) + cs_rank((open - close))"
        result = calculate_by_expression(test_df, expr)
        assert "data" in result.columns

    def test_alpha38(self, test_df: pl.DataFrame) -> None:
        """测试 Alpha#38"""
        expr = "((-1) * cs_rank(ts_rank(close, 10))) * cs_rank((close / open))"
        result = calculate_by_expression(test_df, expr)
        assert "data" in result.columns

    def test_alpha39(self, test_df: pl.DataFrame) -> None:
        """测试 Alpha#39"""
        expr = f"((-1) * cs_rank((ts_delta(close, 7) * (cs_rank(ts_decay_linear((volume / ts_mean(volume, 20)), 9)) * -1 + 1)))) * (cs_rank(ts_sum({returns_expr}, 250)) + 1)"
        result = calculate_by_expression(test_df, expr)
        assert "data" in result.columns

    def test_alpha40(self, test_df: pl.DataFrame) -> None:
        """测试 Alpha#40"""
        expr = "((-1) * cs_rank(ts_std(high, 10))) * ts_corr(high, volume, 10)"
        result = calculate_by_expression(test_df, expr)
        assert "data" in result.columns

    def test_alpha41(self, test_df: pl.DataFrame) -> None:
        """测试 Alpha#41"""
        expr = "pow1((high * low), 0.5) - vwap"
        result = calculate_by_expression(test_df, expr)
        assert "data" in result.columns

    def test_alpha42(self, test_df: pl.DataFrame) -> None:
        """测试 Alpha#42"""
        expr = "cs_rank((vwap - close)) / cs_rank((vwap + close))"
        result = calculate_by_expression(test_df, expr)
        assert "data" in result.columns

    def test_alpha43(self, test_df: pl.DataFrame) -> None:
        """测试 Alpha#43"""
        expr = "ts_rank((volume / ts_mean(volume, 20)), 20) * ts_rank((-1) * ts_delta(close, 7), 8)"
        result = calculate_by_expression(test_df, expr)
        assert "data" in result.columns

    def test_alpha44(self, test_df: pl.DataFrame) -> None:
        """测试 Alpha#44"""
        expr = "(-1) * ts_corr(high, cs_rank(volume), 5)"
        result = calculate_by_expression(test_df, expr)
        assert "data" in result.columns

    def test_alpha45(self, test_df: pl.DataFrame) -> None:
        """测试 Alpha#45"""
        expr = "(-1) * cs_rank(ts_sum(ts_delay(close, 5), 20) / 20) * ts_corr(close, volume, 2) * cs_rank(ts_corr(ts_sum(close, 5), ts_sum(close, 20), 2))"
        result = calculate_by_expression(test_df, expr)
        assert "data" in result.columns

    def test_alpha46(self, test_df: pl.DataFrame) -> None:
        """测试 Alpha#46"""
        expr = "quesval(0.25, ((ts_delay(close, 20) - ts_delay(close, 10)) / 10 - (ts_delay(close, 10) - close) / 10), -1, quesval(0, ((ts_delay(close, 20) - ts_delay(close, 10)) / 10 - (ts_delay(close, 10) - close) / 10), (-1) * (close - ts_delay(close, 1)), 1))"
        result = calculate_by_expression(test_df, expr)
        assert "data" in result.columns

    def test_alpha47(self, test_df: pl.DataFrame) -> None:
        """测试 Alpha#47"""
        expr = "((cs_rank(pow1(close, -1)) * volume / ts_mean(volume, 20)) * (high * cs_rank(high - close)) / (ts_sum(high, 5) / 5)) - cs_rank(vwap - ts_delay(vwap, 5))"
        result = calculate_by_expression(test_df, expr)
        assert "data" in result.columns

    def test_alpha48(self, test_df: pl.DataFrame) -> None:
        """测试 Alpha#48"""
        expr = "(ts_corr(ts_delta(close, 1), ts_delta(ts_delay(close, 1), 1), 250) * ts_delta(close, 1)) / close / ts_sum(pow1((ts_delta(close, 1) / ts_delay(close, 1)), 2), 250)"
        result = calculate_by_expression(test_df, expr)
        assert "data" in result.columns

    def test_alpha49(self, test_df: pl.DataFrame) -> None:
        """测试 Alpha#49"""
        expr = "quesval(-0.1, ((ts_delay(close, 20) - ts_delay(close, 10)) / 10 - (ts_delay(close, 10) - close) / 10), (-1) * (close - ts_delay(close, 1)), 1)"
        result = calculate_by_expression(test_df, expr)
        assert "data" in result.columns

    def test_alpha50(self, test_df: pl.DataFrame) -> None:
        """测试 Alpha#50"""
        expr = "(-1) * ts_max(cs_rank(ts_corr(cs_rank(volume), cs_rank(vwap), 5)), 5)"
        result = calculate_by_expression(test_df, expr)
        assert "data" in result.columns

    def test_alpha51(self, test_df: pl.DataFrame) -> None:
        """测试 Alpha#51"""
        expr = "quesval(-0.05, ((ts_delay(close, 20) - ts_delay(close, 10)) / 10 - (ts_delay(close, 10) - close) / 10), (-1) * (close - ts_delay(close, 1)), 1)"
        result = calculate_by_expression(test_df, expr)
        assert "data" in result.columns

    def test_alpha52(self, test_df: pl.DataFrame) -> None:
        """测试 Alpha#52"""
        expr = f"(((-1) * ts_min(low, 5)) + ts_delay(ts_min(low, 5), 5)) * cs_rank((ts_sum({returns_expr}, 240) - ts_sum({returns_expr}, 20)) / 220) * ts_rank(volume, 5)"
        result = calculate_by_expression(test_df, expr)
        assert "data" in result.columns

    def test_alpha53(self, test_df: pl.DataFrame) -> None:
        """测试 Alpha#53"""
        expr = "(-1) * ts_delta(((close - low) - (high - close)) / (close - low), 9)"
        result = calculate_by_expression(test_df, expr)
        assert "data" in result.columns

    def test_alpha54(self, test_df: pl.DataFrame) -> None:
        """测试 Alpha#54"""
        expr = "((-1) * ((low - close) * pow1(open, 5))) / ((low - high) * pow1(close, 5))"
        result = calculate_by_expression(test_df, expr)
        assert "data" in result.columns

    def test_alpha55(self, test_df: pl.DataFrame) -> None:
        """测试 Alpha#55"""
        expr = "(-1) * ts_corr(cs_rank((close - ts_min(low, 12)) / (ts_max(high, 12) - ts_min(low, 12))), cs_rank(volume), 6)"
        result = calculate_by_expression(test_df, expr)
        assert "data" in result.columns

    # Alpha56 跳过（缺少cap市值字段）

    def test_alpha57(self, test_df: pl.DataFrame) -> None:
        """测试 Alpha#57"""
        expr = "-1 * ((close - vwap) / ts_decay_linear(cs_rank(ts_argmax(close, 30)), 2))"
        result = calculate_by_expression(test_df, expr)
        assert "data" in result.columns

    def test_alpha58(self, test_df: pl.DataFrame) -> None:
        """测试 Alpha#58"""
        expr = "(-1) * ts_rank(ts_decay_linear(ts_corr(vwap, volume, 4), 8), 6)"
        result = calculate_by_expression(test_df, expr)
        assert "data" in result.columns

    def test_alpha59(self, test_df: pl.DataFrame) -> None:
        """测试 Alpha#59"""
        expr = "(-1) * ts_rank(ts_decay_linear(ts_corr(((vwap * 0.728317) + (vwap * (1 - 0.728317))), volume, 4), 16), 8)"
        result = calculate_by_expression(test_df, expr)
        assert "data" in result.columns

    def test_alpha60(self, test_df: pl.DataFrame) -> None:
        """测试 Alpha#60"""
        expr = "- 1 * ((2 * cs_scale(cs_rank((((close - low) - (high - close)) / (high - low)) * volume))) - cs_scale(cs_rank(ts_argmax(close, 10))))"
        result = calculate_by_expression(test_df, expr)
        assert "data" in result.columns

    def test_alpha61(self, test_df: pl.DataFrame) -> None:
        """测试 Alpha#61"""
        expr = "quesval2(cs_rank(vwap - ts_min(vwap, 16)), cs_rank(ts_corr(vwap, ts_mean(volume, 180), 18)), 1, 0)"
        result = calculate_by_expression(test_df, expr)
        assert "data" in result.columns

    def test_alpha62(self, test_df: pl.DataFrame) -> None:
        """测试 Alpha#62"""
        expr = "cast_to_int(cs_rank(ts_corr(vwap, ts_sum(ts_mean(volume, 20), 22), 10)) < cs_rank(cast_to_int((cs_rank(open) + cs_rank(open)) < (cs_rank((high + low) / 2) + cs_rank(high))))) * -1"
        result = calculate_by_expression(test_df, expr)
        assert "data" in result.columns

    def test_alpha63(self, test_df: pl.DataFrame) -> None:
        """测试 Alpha#63"""
        expr = "(cs_rank(ts_decay_linear(ts_delta(close, 2), 8)) - cs_rank(ts_decay_linear(ts_corr(vwap * 0.318108 + open * 0.681892, ts_sum(ts_mean(volume, 180), 37), 14), 12))) * -1"
        result = calculate_by_expression(test_df, expr)
        assert "data" in result.columns

    def test_alpha64(self, test_df: pl.DataFrame) -> None:
        """测试 Alpha#64"""
        expr = "cast_to_int(cs_rank(ts_corr(ts_sum(((open * 0.178404) + (low * (1 - 0.178404))), 13), ts_sum(ts_mean(volume, 120), 13), 17)) < cs_rank(ts_delta((((high + low) / 2 * 0.178404) + (vwap * (1 - 0.178404))), 4))) * -1"
        result = calculate_by_expression(test_df, expr)
        assert "data" in result.columns

    def test_alpha65(self, test_df: pl.DataFrame) -> None:
        """测试 Alpha#65"""
        expr = "cast_to_int(cs_rank(ts_corr(((open * 0.00817205) + (vwap * (1 - 0.00817205))), ts_sum(ts_mean(volume, 60), 9), 6)) < cs_rank(open - ts_min(open, 14))) * -1"
        result = calculate_by_expression(test_df, expr)
        assert "data" in result.columns

    def test_alpha66(self, test_df: pl.DataFrame) -> None:
        """测试 Alpha#66"""
        expr = "(cs_rank(ts_decay_linear(ts_delta(vwap, 4), 7)) + ts_rank(ts_decay_linear((((low * 0.96633) + (low * (1 - 0.96633))) - vwap) / (open - ((high + low) / 2)), 11), 7)) * -1"
        result = calculate_by_expression(test_df, expr)
        assert "data" in result.columns

    def test_alpha67(self, test_df: pl.DataFrame) -> None:
        """测试 Alpha#67"""
        expr = "pow2(cs_rank(high - ts_min(high, 2)), cs_rank(ts_corr(vwap, ts_mean(volume, 20), 6))) * -1"
        result = calculate_by_expression(test_df, expr)
        assert "data" in result.columns

    def test_alpha68(self, test_df: pl.DataFrame) -> None:
        """测试 Alpha#68"""
        expr = "cast_to_int(ts_rank(ts_corr(cs_rank(high), cs_rank(ts_mean(volume, 15)), 9), 14) < cs_rank(ts_delta((close * 0.518371 + low * (1 - 0.518371)), 1))) * -1"
        result = calculate_by_expression(test_df, expr)
        assert "data" in result.columns

    def test_alpha69(self, test_df: pl.DataFrame) -> None:
        """测试 Alpha#69"""
        expr = "pow2(cs_rank(ts_max(ts_delta(vwap, 3), 5)), ts_rank(ts_corr(close * 0.490655 + vwap * 0.509345, ts_mean(volume, 20), 5), 9)) * -1"
        result = calculate_by_expression(test_df, expr)
        assert "data" in result.columns

    def test_alpha70(self, test_df: pl.DataFrame) -> None:
        """测试 Alpha#70"""
        expr = "pow2(cs_rank(ts_delta(vwap, 1)), ts_rank(ts_corr(close, ts_mean(volume, 50), 18), 18)) * -1"
        result = calculate_by_expression(test_df, expr)
        assert "data" in result.columns

    def test_alpha71(self, test_df: pl.DataFrame) -> None:
        """测试 Alpha#71"""
        expr = "ts_greater(ts_rank(ts_decay_linear(ts_corr(ts_rank(close, 3), ts_rank(ts_mean(volume, 180), 12), 18), 4), 16), ts_rank(ts_decay_linear(pow1(cs_rank((low + open) - (vwap + vwap)), 2), 16), 4))"
        result = calculate_by_expression(test_df, expr)
        assert "data" in result.columns

    def test_alpha72(self, test_df: pl.DataFrame) -> None:
        """测试 Alpha#72"""
        expr = "cs_rank(ts_decay_linear(ts_corr((high + low) / 2, ts_mean(volume, 40), 9), 10)) / cs_rank(ts_decay_linear(ts_corr(ts_rank(vwap, 4), ts_rank(volume, 19), 7), 3))"
        result = calculate_by_expression(test_df, expr)
        assert "data" in result.columns

    def test_alpha73(self, test_df: pl.DataFrame) -> None:
        """测试 Alpha#73"""
        expr = "ts_greater(cs_rank(ts_decay_linear(ts_delta(vwap, 5), 3)), ts_rank(ts_decay_linear((ts_delta(open * 0.147155 + low * 0.852845, 2) / (open * 0.147155 + low * 0.852845)) * -1, 3), 17)) * -1"
        result = calculate_by_expression(test_df, expr)
        assert "data" in result.columns

    def test_alpha74(self, test_df: pl.DataFrame) -> None:
        """测试 Alpha#74"""
        expr = "quesval2(cs_rank(ts_corr(close, ts_sum(ts_mean(volume, 30), 37), 15)), cs_rank(ts_corr(cs_rank(high * 0.0261661 + vwap * 0.9738339), cs_rank(volume), 11)), 1, 0) * -1"
        result = calculate_by_expression(test_df, expr)
        assert "data" in result.columns

    def test_alpha75(self, test_df: pl.DataFrame) -> None:
        """测试 Alpha#75"""
        expr = "quesval2(cs_rank(ts_corr(vwap, volume, 4)), cs_rank(ts_corr(cs_rank(low), cs_rank(ts_mean(volume, 50)), 12)), 1, 0)"
        result = calculate_by_expression(test_df, expr)
        assert "data" in result.columns

    def test_alpha76(self, test_df: pl.DataFrame) -> None:
        """测试 Alpha#76"""
        expr = "ts_greater(cs_rank(ts_decay_linear(ts_delta(vwap, 1), 12)), ts_rank(ts_decay_linear(ts_rank(ts_corr(low, ts_mean(volume, 81), 8), 20), 17), 19)) * -1"
        result = calculate_by_expression(test_df, expr)
        assert "data" in result.columns

    def test_alpha77(self, test_df: pl.DataFrame) -> None:
        """测试 Alpha#77"""
        expr = "ts_less(cs_rank(ts_decay_linear((((high + low) / 2 + high) - (vwap + high)), 20)), cs_rank(ts_decay_linear(ts_corr((high + low) / 2, ts_mean(volume, 40), 3), 6)))"
        result = calculate_by_expression(test_df, expr)
        assert "data" in result.columns

    def test_alpha78(self, test_df: pl.DataFrame) -> None:
        """测试 Alpha#78"""
        expr = "pow2(cs_rank(ts_corr(ts_sum((low * 0.352233) + (vwap * (1 - 0.352233)), 20), ts_sum(ts_mean(volume, 40), 20), 7)), cs_rank(ts_corr(cs_rank(vwap), cs_rank(volume), 6)))"
        result = calculate_by_expression(test_df, expr)
        assert "data" in result.columns

    def test_alpha79(self, test_df: pl.DataFrame) -> None:
        """测试 Alpha#79"""
        expr = "quesval2(cs_rank(ts_delta(close * 0.60733 + open * 0.39267, 1)), cs_rank(ts_corr(ts_rank(vwap, 4), ts_rank(ts_mean(volume, 150), 9), 15)), 1, 0)"
        result = calculate_by_expression(test_df, expr)
        assert "data" in result.columns

    def test_alpha80(self, test_df: pl.DataFrame) -> None:
        """测试 Alpha#80"""
        expr = "pow2(cs_rank(sign(ts_delta(open * 0.868128 + high * 0.131872, 4))), ts_rank(ts_corr(high, ts_mean(volume, 10), 5), 6)) * -1"
        result = calculate_by_expression(test_df, expr)
        assert "data" in result.columns

    def test_alpha81(self, test_df: pl.DataFrame) -> None:
        """测试 Alpha#81"""
        expr = "quesval2(cs_rank(log(ts_product(cs_rank(pow1(cs_rank(ts_corr(vwap, ts_sum(ts_mean(volume, 10), 50), 8)), 4)), 15))), cs_rank(ts_corr(cs_rank(vwap), cs_rank(volume), 5)), 1, 0) * -1"
        result = calculate_by_expression(test_df, expr)
        assert "data" in result.columns

    def test_alpha82(self, test_df: pl.DataFrame) -> None:
        """测试 Alpha#82"""
        expr = "ts_less(cs_rank(ts_decay_linear(ts_delta(open, 1), 15)), ts_rank(ts_decay_linear(ts_corr(volume, open, 17), 7), 13)) * -1"
        result = calculate_by_expression(test_df, expr)
        assert "data" in result.columns

    def test_alpha83(self, test_df: pl.DataFrame) -> None:
        """测试 Alpha#83"""
        expr = "(cs_rank(ts_delay((high - low) / (ts_sum(close, 5) / 5), 2)) * cs_rank(cs_rank(volume))) / (((high - low) / (ts_sum(close, 5) / 5)) / (vwap - close))"
        result = calculate_by_expression(test_df, expr)
        assert "data" in result.columns

    def test_alpha84(self, test_df: pl.DataFrame) -> None:
        """测试 Alpha#84"""
        expr = "pow2(ts_rank(vwap - ts_max(vwap, 15), 21), ts_delta(close, 5))"
        result = calculate_by_expression(test_df, expr)
        assert "data" in result.columns

    def test_alpha85(self, test_df: pl.DataFrame) -> None:
        """测试 Alpha#85"""
        expr = "pow2(cs_rank(ts_corr(high * 0.876703 + close * 0.123297, ts_mean(volume, 30), 10)), cs_rank(ts_corr(ts_rank((high + low) / 2, 4), ts_rank(volume, 10), 7)))"
        result = calculate_by_expression(test_df, expr)
        assert "data" in result.columns

    def test_alpha86(self, test_df: pl.DataFrame) -> None:
        """测试 Alpha#86"""
        expr = "quesval2(ts_rank(ts_corr(close, ts_sum(ts_mean(volume, 20), 15), 6), 20), cs_rank((open + close) - (vwap + open)), 1, 0) * -1"
        result = calculate_by_expression(test_df, expr)
        assert "data" in result.columns

    def test_alpha87(self, test_df: pl.DataFrame) -> None:
        """测试 Alpha#87"""
        expr = "ts_greater(cs_rank(ts_decay_linear(ts_delta(close * 0.369701 + vwap * 0.630299, 2), 3)), ts_rank(ts_decay_linear(abs(ts_corr(ts_mean(volume, 81), close, 13)), 5), 14)) * -1"
        result = calculate_by_expression(test_df, expr)
        assert "data" in result.columns

    def test_alpha88(self, test_df: pl.DataFrame) -> None:
        """测试 Alpha#88"""
        expr = "ts_less(cs_rank(ts_decay_linear((cs_rank(open) + cs_rank(low)) - (cs_rank(high) + cs_rank(close)), 8)), ts_rank(ts_decay_linear(ts_corr(ts_rank(close, 8), ts_rank(ts_mean(volume, 60), 21), 8), 7), 3))"
        result = calculate_by_expression(test_df, expr)
        assert "data" in result.columns

    def test_alpha89(self, test_df: pl.DataFrame) -> None:
        """测试 Alpha#89"""
        expr = "(ts_rank(ts_decay_linear(ts_corr(low, ts_mean(volume, 10), 7), 6), 4) - ts_rank(ts_decay_linear(ts_delta(vwap, 3), 10), 15))"
        result = calculate_by_expression(test_df, expr)
        assert "data" in result.columns

    def test_alpha90(self, test_df: pl.DataFrame) -> None:
        """测试 Alpha#90"""
        expr = "pow2(cs_rank(close - ts_max(close, 5)), ts_rank(ts_corr(ts_mean(volume, 40), low, 5), 3)) * -1"
        result = calculate_by_expression(test_df, expr)
        assert "data" in result.columns

    def test_alpha91(self, test_df: pl.DataFrame) -> None:
        """测试 Alpha#91"""
        expr = "(ts_rank(ts_decay_linear(ts_decay_linear(ts_corr(close, volume, 10), 16), 4), 5) - cs_rank(ts_decay_linear(ts_corr(vwap, ts_mean(volume, 30), 4), 3))) * -1"
        result = calculate_by_expression(test_df, expr)
        assert "data" in result.columns

    def test_alpha92(self, test_df: pl.DataFrame) -> None:
        """测试 Alpha#92"""
        expr = "ts_less(ts_rank(ts_decay_linear(quesval2(((high + low) / 2 + close), (low + open), 1, 0), 15), 19), ts_rank(ts_decay_linear(ts_corr(cs_rank(low), cs_rank(ts_mean(volume, 30)), 8), 7), 7))"
        result = calculate_by_expression(test_df, expr)
        assert "data" in result.columns

    def test_alpha93(self, test_df: pl.DataFrame) -> None:
        """测试 Alpha#93"""
        expr = "ts_rank(ts_decay_linear(ts_corr(vwap, ts_mean(volume, 81), 17), 20), 8) / cs_rank(ts_decay_linear(ts_delta(close * 0.524434 + vwap * 0.475566, 3), 16))"
        result = calculate_by_expression(test_df, expr)
        assert "data" in result.columns

    def test_alpha94(self, test_df: pl.DataFrame) -> None:
        """测试 Alpha#94"""
        expr = "pow2(cs_rank(vwap - ts_min(vwap, 12)), ts_rank(ts_corr(ts_rank(vwap, 20), ts_rank(ts_mean(volume, 60), 4), 18), 3)) * -1"
        result = calculate_by_expression(test_df, expr)
        assert "data" in result.columns

    def test_alpha95(self, test_df: pl.DataFrame) -> None:
        """测试 Alpha#95"""
        expr = "quesval2(cs_rank(open - ts_min(open, 12)), ts_rank(pow1(cs_rank(ts_corr(ts_sum((high + low) / 2, 19), ts_sum(ts_mean(volume, 40), 19), 13)), 5), 12), 1, 0)"
        result = calculate_by_expression(test_df, expr)
        assert "data" in result.columns

    def test_alpha96(self, test_df: pl.DataFrame) -> None:
        """测试 Alpha#96"""
        expr = "ts_greater(ts_rank(ts_decay_linear(ts_corr(cs_rank(vwap), cs_rank(volume), 4), 4), 8), ts_rank(ts_decay_linear(ts_argmax(ts_corr(ts_rank(close, 7), ts_rank(ts_mean(volume, 60), 4), 4), 13), 14), 13)) * -1"
        result = calculate_by_expression(test_df, expr)
        assert "data" in result.columns

    def test_alpha97(self, test_df: pl.DataFrame) -> None:
        """测试 Alpha#97"""
        expr = "(cs_rank(ts_decay_linear(ts_delta(low * 0.721001 + vwap * 0.278999, 3), 20)) - ts_rank(ts_decay_linear(ts_rank(ts_corr(ts_rank(low, 8), ts_rank(ts_mean(volume, 60), 17), 5), 19), 16), 7)) * -1"
        result = calculate_by_expression(test_df, expr)
        assert "data" in result.columns

    def test_alpha98(self, test_df: pl.DataFrame) -> None:
        """测试 Alpha#98"""
        expr = "cs_rank(ts_decay_linear(ts_corr(vwap, ts_sum(ts_mean(volume, 5), 26), 5), 7)) - cs_rank(ts_decay_linear(ts_rank(ts_argmin(ts_corr(cs_rank(open), cs_rank(ts_mean(volume, 15)), 21), 9), 7), 8))"
        result = calculate_by_expression(test_df, expr)
        assert "data" in result.columns

    def test_alpha99(self, test_df: pl.DataFrame) -> None:
        """测试 Alpha#99"""
        expr = "quesval2(cs_rank(ts_corr(ts_sum((high + low) / 2, 20), ts_sum(ts_mean(volume, 60), 20), 9)), cs_rank(ts_corr(low, volume, 6)), 1, 0) * -1"
        result = calculate_by_expression(test_df, expr)
        assert "data" in result.columns

    def test_alpha100(self, test_df: pl.DataFrame) -> None:
        """测试 Alpha#100"""
        expr = "-1 * ((1.5 * cs_scale(cs_rank(((close - low) - (high - close)) / (high - low) * volume))) - cs_scale(ts_corr(close, cs_rank(ts_mean(volume, 20)), 5) - cs_rank(ts_argmin(close, 30)))) * (volume / ts_mean(volume, 20))"
        result = calculate_by_expression(test_df, expr)
        assert "data" in result.columns

    def test_alpha101(self, test_df: pl.DataFrame) -> None:
        """测试 Alpha#101"""
        expr = "((close - open) / ((high - low) + 0.001))"
        result = calculate_by_expression(test_df, expr)
        assert "data" in result.columns


if __name__ == "__main__":
    pytest.main([__file__, "-v", "--tb=short"])    # 只显示错误的最后一行和断言信息
