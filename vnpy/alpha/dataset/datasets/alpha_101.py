from functools import partial
import polars as pl

from vnpy.alpha.dataset import (
    AlphaDataset,
    process_drop_na,
    process_cs_norm,
    process_fill_na
)


class Alpha101(AlphaDataset):
    """101 basic factors from WorldQuant"""

    def __init__(
        self,
        df: pl.DataFrame,
        train_period: tuple[str, str],
        valid_period: tuple[str, str],
        test_period: tuple[str, str]
    ) -> None:
        """Constructor"""
        super().__init__(
            df=df,
            train_period=train_period,
            valid_period=valid_period,
            test_period=test_period,
        )

        returns_expr: str = "(close / ts_delay(close, 1) - 1)"

#        # Alpha1
#        self.add_feature("alpha1", f"(cs_rank(ts_argmax(pow1(quesval(0, {returns_expr}, ts_std({returns_expr}, 20), close), 2.0), 5)) - 0.5)")
#
#        # Alpha2 p
#        self.add_feature("alpha2", "(-1) * ts_corr(cs_rank(delta(ts_log(volume), 2)), cs_rank((close - open) / open), 6)")
#
#        # Alpha3
#        self.add_feature("alpha3", "ts_corr(cs_rank(open), cs_rank(volume), 10) * -1")
#
#        # Alpha4
#        self.add_feature("alpha4", "-1 * ts_rank(cs_rank(low), 9)")
#
#        # Alpha5 n
#        self.add_feature("alpha5", "cs_rank((open - (ts_sum(vwap, 10) / 10))) * (-1 * ts_abs(cs_rank((close - vwap))))")
#
#        # Alpha6
#        self.add_feature("alpha6", "(-1) * ts_corr(open, volume, 10)")
#
#        # Alpha7
#        self.add_feature("alpha7", "quesval2(ts_mean(volume, 20), volume, (-1 * ts_rank(ts_abs(close - ts_delay(close, 7)), 60)) * sign(delta(close, 7)), (-1) * sign(volume))")
#
#        # Alpha8
#        self.add_feature("alpha8", f"-1 * cs_rank(((ts_sum(open, 5) * ts_sum({returns_expr}, 5)) - ts_delay((ts_sum(open, 5) * ts_sum({returns_expr}, 5)), 10)))")
#
#        # Alpha9 p
#        self.add_feature("alpha9", "quesval(0, ts_min(delta(close, 1), 5), delta(close, 1), quesval(0, ts_max(delta(close, 1), 5), delta(close, 1), (-1 * delta(close, 1))))")
#
#        # Alpha10 p
#        self.add_feature("alpha10", "cs_rank(quesval(0, ts_min(delta(close, 1), 4), delta(close, 1), quesval(0, ts_max(delta(close, 1), 4), delta(close, 1), (-1 * delta(close, 1)))))")
#
#        # Alpha11 n
#        self.add_feature("alpha11", "cs_rank(ts_max(vwap - close, 3)) + cs_rank(ts_min(vwap - close, 3)) * cs_rank(volume - ts_delay(volume, 3))")
#
#        # Alpha12 n
#        self.add_feature("alpha12", "sign(delta(volume, 1)) * (-1 * delta(close, 1))")
#
#        # Alpha13
#        self.add_feature("alpha13", "-1 * cs_rank(cov(cs_rank(close), cs_rank(volume), 5))")
#
#        # Alpha14
#        self.add_feature("alpha14", f"(-1 * cs_rank(({returns_expr}) - ts_delay({returns_expr}, 3))) * ts_corr(open, volume, 10)")
#
#        # Alpha15 p
#        self.add_feature("alpha15", "-1 * ts_sum(cs_rank(ts_corr(cs_rank(high), cs_rank(volume), 3)), 3)")
#
#        # Alpha16
#        self.add_feature("alpha16", "-1 * cs_rank(cov(cs_rank(high), cs_rank(volume), 5))")
#
#        # Alpha17 nn
#        self.add_feature("alpha17", "(-1 * cs_rank(ts_rank(close, 10))) * cs_rank(close - 2 * ts_delay(close, 1) + ts_delay(close, 2)) * cs_rank(ts_rank(volume / ts_mean(volume, 20), 5))")
#
#        # Alpha18
#        self.add_feature("alpha18", "-1 * cs_rank((ts_std(abs(close - open), 5) + (close - open)) + ts_corr(close, open, 10))")
#
#        # Alpha19
#        self.add_feature("alpha19", f"sign(delta(close, 7) + (close - ts_delay(close, 7))) * (sign(volume) + cs_rank(sign(volume) + ts_sum({returns_expr}, 250)))")
#
#        # Alpha20
#        self.add_feature("alpha20", "(-1 * cs_rank(open - ts_delay(high, 1))) * cs_rank(open - ts_delay(close, 1)) * cs_rank(open - ts_delay(low, 1))")
#
#        # Alpha21
#        self.add_feature("alpha21", "quesval2((ts_mean(close, 8) + ts_std(close, 8)), ts_mean(close, 2), (-1) * sign(volume), quesval2(ts_mean(close, 2), (ts_mean(close, 8) - ts_std(close, 8)), sign(volume), quesval(1, (volume / ts_mean(volume, 20)), (-1) * sign(volume), sign(volume))))")
#
#        # Alpha22
#        self.add_feature("alpha22", "-1 * delta(ts_corr(high, volume, 5), 5) * cs_rank(ts_std(close, 20))")
#
#        # Alpha23
#        self.add_feature("alpha23", "quesval2(ts_mean(high, 20), high, -1 * delta(high, 2), sign(volume) - sign(volume))")
#
#        # Alpha24
#        self.add_feature("alpha24", "quesval(0.05, delta(ts_sum(close, 100) / 100, 100) / ts_delay(close, 100), (-1 * (close - ts_min(close, 100))), (-1 * delta(close, 3)))")
#
#        # Alpha25
#        self.add_feature("alpha25", f"cs_rank( (-1 * {returns_expr}) * ts_mean(volume, 20) * vwap * (high - close) )")
#
#        # Alpha26
#        self.add_feature("alpha26", "-1 * ts_max(ts_corr(ts_rank(volume, 5), ts_rank(high, 5), 5), 3)")
#
#        # Alpha27
#        self.add_feature("alpha27", "quesval(0.5, cs_rank(ts_mean(ts_corr(cs_rank(volume), cs_rank(vwap), 6), 2)), -1 * sign(volume), sign(volume))")
#
#        # Alpha28
#        self.add_feature("alpha28", "scale(ts_corr(ts_mean(volume, 20), low, 5) + (high + low) / 2 - close)")
#
#        # Alpha29
#        self.add_feature("alpha29", f"ts_min(cs_rank(cs_rank(scale(ts_log(ts_sum(ts_min(cs_rank(cs_rank((-1 * cs_rank(delta((close - 1), 5))))), 2), 1))))), 5) + ts_rank(ts_delay((-1 * {returns_expr}), 6), 5)")
#
#        # Alpha30
#        self.add_feature("alpha30", "(sign(volume) - cs_rank(sign(close - ts_delay(close, 1)) + sign(ts_delay(close, 1) - ts_delay(close, 2)) + sign(ts_delay(close, 2) - ts_delay(close, 3))) * ts_sum(volume, 5)) / ts_sum(volume, 20)")
#
#        # Alpha31
#        self.add_feature("alpha31", "(cs_rank(cs_rank(cs_rank(decay_linear((-1) * cs_rank(cs_rank(delta(close, 10))), 10)))) + cs_rank((-1) * delta(close, 3))) + sign(scale(ts_corr(ts_mean(volume, 20), low, 12)))")
#
#        # Alpha32
#        self.add_feature("alpha32", "scale((ts_sum(close, 7) / 7 - close)) + (20 * scale(ts_corr(vwap, ts_delay(close, 5), 230)))")
#
#        # Alpha33 n
#        self.add_feature("alpha33", "cs_rank((-1) * (sign(volume) - (open / close)))")
#
#        # Alpha34 n
#        self.add_feature("alpha34", f"cs_rank((sign(volume) - cs_rank(ts_std({returns_expr}, 2) / ts_std({returns_expr}, 5))) + (sign(volume) - cs_rank(delta(close, 1))))")
#
#        # Alpha35
#        self.add_feature("alpha35", f"(ts_rank(volume, 32) * (sign(volume) - ts_rank((close + high - low), 16))) * ( sign(volume) - ts_rank({returns_expr}, 32))")
#
#        # Alpha36
#        self.add_feature("alpha36", f"((((2.21 * cs_rank(ts_corr((close - open), ts_delay(volume, 1), 15))) + (0.7 * cs_rank((open - close)))) + (0.73 * cs_rank(ts_rank(ts_delay((-1) * {returns_expr}, 6), 5)))) + cs_rank(ts_abs(ts_corr(vwap, ts_mean(volume, 20), 6)))) + (0.6 * cs_rank(((ts_sum(close, 200) / 200 - open) * (close - open))))")
#
#        # Alpha37
#        self.add_feature("alpha37", "cs_rank(ts_corr(ts_delay((open - close), 1), close, 200)) + cs_rank((open - close))")
#
#        # Alpha38 n
#        self.add_feature("alpha38", "((-1) * cs_rank(ts_rank(close, 10))) * cs_rank((close / open))")
#
#        # Alpha39
#        self.add_feature("alpha39", f"((-1) * cs_rank((delta(close, 7) * (sign(volume) - cs_rank(decay_linear((volume / ts_mean(volume, 20)), 9)))))) * (sign(volume) + cs_rank(ts_sum({returns_expr}, 250)))")
#
#        # Alpha40
#        self.add_feature("alpha40", "((-1) * cs_rank(ts_std(high, 10))) * ts_corr(high, volume, 10)")
#
#        # Alpha41
#        self.add_feature("alpha41", "pow1((high * low), 0.5) - vwap")
#
#        # Alpha42
#        self.add_feature("alpha42", "cs_rank((vwap - close)) / cs_rank((vwap + close))")
#
#        # Alpha43 n
#        self.add_feature("alpha43", "ts_rank((volume / ts_mean(volume, 20)), 20) * ts_rank((-1) * delta(close, 7), 8)")
#
#        # Alpha44
#        self.add_feature("alpha44", "(-1) * ts_corr(high, cs_rank(volume), 5)")
#
#        # Alpha45 n
#        self.add_feature("alpha45", "(-1) * cs_rank(ts_sum(ts_delay(close, 5), 20) / 20) * ts_corr(close, volume, 2) * cs_rank(ts_corr(ts_sum(close, 5), ts_sum(close, 20), 2))")
#
#        # Alpha46
#        self.add_feature("alpha46", "quesval(0.25, ((ts_delay(close, 20) - ts_delay(close, 10)) / 10 - (ts_delay(close, 10) - close) / 10), (-1) * sign(volume), quesval(0, ((ts_delay(close, 20) - ts_delay(close, 10)) / 10 - (ts_delay(close, 10) - close) / 10), sign(volume), (-1) * (close - ts_delay(close, 1))))")
#
#        # Alpha47 n
#        self.add_feature("alpha47", "((cs_rank(sign(volume) / close) * volume / ts_mean(volume, 20)) * (high * cs_rank(high - close)) / (ts_sum(high, 5) / 5)) - cs_rank(vwap - ts_delay(vwap, 5))")
#
#        # Alpha48
#        self.add_feature("alpha48", "(ts_corr(delta(close, 1), ts_delay(ts_delay(close, 1), 1), 250) * delta(close, 1)) / close / ts_sum(pow1((delta(close, 1) / ts_delay(close, 1)), 2), 250)")
#
#        # Alpha49 n
#        self.add_feature("alpha49", "quesval(-0.1, ((ts_delay(close, 20) - ts_delay(close, 10)) / 10 - (ts_delay(close, 10) - close) / 10), sign(volume), (-1) * (close - ts_delay(close, 1)))")
#
#        # Alpha50 p
#        self.add_feature("alpha50", "(-1) * ts_max(cs_rank(ts_corr(cs_rank(volume), cs_rank(vwap), 5)), 5)")
#
#        # Alpha51 n
#        self.add_feature("alpha51", "quesval(-0.05, ((ts_delay(close, 20) - ts_delay(close, 10)) / 10 - (ts_delay(close, 10) - close) / 10), sign(volume), (-1) * (close - ts_delay(close, 1)))")
#
#        # Alpha52
#        self.add_feature("alpha52", f"(((-1) * ts_min(low, 5)) + ts_delay(ts_min(low, 5), 5)) * cs_rank((ts_sum({returns_expr}, 240) - ts_sum({returns_expr}, 20)) / 220) * ts_rank(volume, 5)")
#
#        # Alpha53
#        self.add_feature("alpha53", "(-1) * delta(((close - low) - (high - close)) / (close - low), 9)")
#
#        # Alpha54
#        self.add_feature("alpha54", "((-1) * ((low - close) * pow1(open, 5))) / ((low - high) * pow1(close, 5))")
#
#        # Alpha55
#        self.add_feature("alpha55", "(-1) * ts_corr(cs_rank((close - ts_min(low, 12)) / (ts_max(high, 12) - ts_min(low, 12))), cs_rank(volume), 6)")
#
#        # Alpha56
#        self.add_feature("alpha56", f"(-1) * (cs_rank(ts_sum({returns_expr}, 10) / ts_sum(ts_sum({returns_expr}, 2), 3)) * cs_rank(({returns_expr}) * cap(vwap, volume)))")
#
#        # Alpha57
#        self.add_feature("alpha57", "-1 * ((close - vwap) / decay_linear(cs_rank(ts_argmax(close, 30)), 2))")
#
#        # Alpha58
#        self.add_feature("alpha58", "(-1) * ts_rank(decay_linear(ts_corr(vwap, volume, 4), 8), 6)")
#
#        # Alpha59
#        self.add_feature("alpha59", "(-1) * ts_rank(decay_linear(ts_corr(((vwap * 0.728317) + (vwap * (1 - 0.728317))), volume, 4), 16), 8)")
#
#        # Alpha60
#        self.add_feature("alpha60", "- 1 * ((2 * scale(cs_rank((((close - low) - (high - close)) / (high - low)) * volume))) - scale(cs_rank(ts_argmax(close, 10))))")
#
#        # Alpha61
#        self.add_feature("alpha61", "quesval2(cs_rank(vwap - ts_min(vwap, 16)), cs_rank(ts_corr(vwap, ts_mean(volume, 180), 18)), sign(volume), 0 * sign(volume))")
#
#        # Alpha62
#        self.add_feature("alpha62", "cs_rank(ts_corr(vwap, ts_sum(ts_mean(volume, 20), 22), 10) < cs_rank((cs_rank(open) + cs_rank(open)) < (cs_rank((high + low) / 2) + cs_rank(high)))) * -1")
#
#        # Alpha63
#        self.add_feature("alpha63", "cs_rank(decay_linear(delta(close, 2), 8) - cs_rank(decay_linear(ts_corr(((vwap * 0.318108) + (open * (1 - 0.318108))), ts_sum(ts_mean(volume, 180), 37), 14), 12))) * -1")
#
#        # Alpha64
#        self.add_feature("alpha64", "cs_rank(ts_corr(ts_sum(((open * 0.178404) + (low * (1 - 0.178404))), 13), ts_sum(ts_mean(volume, 120), 13), 17) < cs_rank(delta((((high + low) / 2 * 0.178404) + (vwap * (1 - 0.178404))), 4))) * -1")
#
#        # Alpha65
#        self.add_feature("alpha65", "cast_to_int(cs_rank(ts_corr(((open * 0.00817205) + (vwap * (1 - 0.00817205))), ts_sum(ts_mean(volume, 60), 9), 6)) < cs_rank(open - ts_min(open, 14)))")
#
#        # Alpha66
#        self.add_feature("alpha66", "(cs_rank(decay_linear(delta(vwap, 4), 7)) + ts_rank(decay_linear((((low * 0.96633) + (low * (1 - 0.96633))) - vwap) / (open - ((high + low) / 2)), 11), 7)) * -1")
#
#        # Alpha67
#        self.add_feature("alpha67", "pow1(cs_rank(high - ts_min(high, 2)), -1)")
#
#        # Alpha68
#        self.add_feature("alpha68", "cast_to_int((ts_rank(ts_corr(cs_rank(high), cs_rank(ts_mean(volume, 15)), 9), 14) < cs_rank(delta((close * 0.518371 + low * (1 - 0.518371)), 1))))")
#
#        # Alpha69
#        self.add_feature("alpha69", "cs_rank(ts_max(delta(vwap, 3), 5)) * -1")
#
#        # Alpha70 n
#        self.add_feature("alpha70", "cs_rank(delta(vwap, 1.29456)) * -1")
#
#        # Alpha71
#        self.add_feature("alpha71", "ts_rank(decay_linear(ts_corr(ts_rank(close, 3), ts_rank(ts_mean(volume, 180), 12), 18), 4), 16)")
#
#        # Alpha72
#        self.add_feature("alpha72", "cs_rank(decay_linear(ts_corr((high + low) / 2, ts_mean(volume, 40), 9), 10)) / cs_rank(decay_linear(ts_corr(ts_rank(vwap, 4), ts_rank(volume, 18), 7), 3))")
#
#        # Alpha73
#        self.add_feature("alpha73", "cs_rank(decay_linear(delta(vwap, 5), 3)) ")
#
#        # Alpha74
#        self.add_feature("alpha74", "quesval2(cs_rank(ts_corr(close, ts_sum(ts_mean(volume, 30), 37), 15)), cs_rank(ts_corr(cs_rank(high * 0.0261661 + vwap * 0.9738339), cs_rank(volume), 11)), sign(volume), 0 * sign(volume))")
#
#        # Alpha75
#        self.add_feature("alpha75", "quesval2(cs_rank(ts_corr(vwap, volume, 4)), cs_rank(ts_corr(cs_rank(low), cs_rank(ts_mean(volume, 50)), 12)), sign(volume), 0 * sign(volume))")
#
#        # Alpha76
#        self.add_feature("alpha76", "cs_rank(decay_linear(delta(vwap, 1), 12))")
#
#        # Alpha77
#        self.add_feature("alpha77", "cs_rank(decay_linear((((high + low) / 2 + high) - (vwap + high)), 20))")
#
#        # Alpha78
#        self.add_feature("alpha78", "cs_rank(ts_corr(ts_sum((low * 0.352233) + (vwap * (1 - 0.352233)), 20), ts_sum(ts_mean(volume, 40), 20), 7))")
#
#        # Alpha79
#        self.add_feature("alpha79", "quesval2(cs_rank(delta(close * 0.60733 + open * 0.39267, 1)), cs_rank(ts_corr(ts_rank(vwap, 4), ts_rank(ts_mean(volume, 150), 9), 15)), -1 * sign(volume), 0 * sign(volume))")
#
#        # Alpha80
#        self.add_feature("alpha80", "cs_rank(sign(delta(open * 0.868128 + high * 0.131872, 4))) * ts_rank(ts_corr(high, ts_mean(volume, 10), 5), 6) * -1")
#
#        # Alpha81
#        self.add_feature("alpha81", "ts_corr(vwap, ts_sum(ts_mean(volume, 10), 50), 8)")
#
#        # Alpha82
#        self.add_feature("alpha82", "ts_rank(decay_linear(ts_corr(volume, open, 17), 7), 13)")
#
#        # Alpha83 n
#        self.add_feature("alpha83", "(cs_rank(ts_delay((high - low) / (ts_sum(close, 5) / 5), 2)) * cs_rank(cs_rank(volume))) / (((high - low) / (ts_sum(close, 5) / 5)) / (vwap - close))")
#
#        # Alpha84
#        self.add_feature("alpha84", "pow2(ts_rank(vwap - ts_max(vwap, 15), 21), delta(close, 5))")
#
#        # Alpha85
#        self.add_feature("alpha85", "pow2(cs_rank(ts_corr(high * 0.876703 + close * 0.123297, ts_mean(volume, 30), 10)), cs_rank(ts_corr(ts_rank((high + low) / 2, 4), ts_rank(volume, 10), 7)))")
#
#        # Alpha86
#        self.add_feature("alpha86", "quesval2(ts_rank(ts_corr(close, ts_sum(ts_mean(volume, 20), 15), 6), 20), cs_rank((open + close) - (vwap + open)), -1 * sign(volume), 0 * sign(volume))")
#
#        # Alpha87 n
#        self.add_feature("alpha87", "cs_rank(decay_linear(delta(close * 0.369701 + vwap * 0.630299, 2), 3)) * ts_rank(decay_linear(ts_abs(ts_corr(ts_mean(volume, 81), close, 13)), 5), 14)")
#
#        # Alpha88
#        self.add_feature("alpha88", "cs_rank(decay_linear((cs_rank(open) + cs_rank(low)) - (cs_rank(high) + cs_rank(close)), 8))")
#
#        # Alpha89
#        self.add_feature("alpha89", "(ts_rank(decay_linear(ts_corr(low, ts_mean(volume, 10), 7), 6), 4) - ts_rank(decay_linear(delta(vwap, 3), 10), 15))")
#
#        # Alpha90
#        self.add_feature("alpha90", "cs_rank(close - ts_max(close, 5)) * ts_rank(ts_corr(ts_mean(volume, 40), low, 5), 3) * -1")
#
#        # Alpha91
#        self.add_feature("alpha91", "(ts_rank(decay_linear(decay_linear(ts_corr(close, volume, 10), 16), 4), 5) - cs_rank(decay_linear(ts_corr(vwap, ts_mean(volume, 30), 4), 3))) * -1")
#
#        # Alpha92
#        self.add_feature("alpha92", "ts_rank(decay_linear(quesval2(((high + low) / 2 + close), (low + open), sign(volume), 0 * sign(volume)), 15), 19)")
#
#        # Alpha93
#        self.add_feature("alpha93", "ts_rank(decay_linear(ts_corr(vwap, ts_mean(volume, 81), 17), 20), 8) / cs_rank(decay_linear(delta(close * 0.524434 + vwap * 0.475566, 3), 16))")
#
#        # Alpha94
#        self.add_feature("alpha94", "cs_rank(vwap - ts_min(vwap, 12)) * -1")
#
#        # Alpha95
#        self.add_feature("alpha95", "cs_rank(open - ts_min(open, 12))")
#
#        # Alpha96
#        self.add_feature("alpha96", "ts_rank(decay_linear(ts_corr(cs_rank(vwap), cs_rank(volume), 4), 4), 8) * -1")
#
#        # Alpha97
#        self.add_feature("alpha97", "cs_rank(decay_linear(delta(low * 0.721001 + vwap * 0.278999, 3), 20)) * -1")
#
#        # Alpha98
#        self.add_feature("alpha98", "cs_rank(decay_linear(ts_corr(vwap, ts_sum(ts_mean(volume, 5), 26), 5), 7)) - cs_rank(decay_linear(ts_rank(ts_argmin(ts_corr(cs_rank(open), cs_rank(ts_mean(volume, 15)), 21), 9), 7), 8))")
#
#        # Alpha99
#        self.add_feature("alpha99", "quesval2(cs_rank(ts_corr(ts_sum((high + low) / 2, 20), ts_sum(ts_mean(volume, 60), 20), 9)), cs_rank(ts_corr(low, volume, 6)), sign(volume), 0 * sign(volume)) * -1")
#
#        # Alpha100
#        self.add_feature("alpha100", "-1 * ((1.5 * scale(cs_rank(((close - low) - (high - close)) / (high - low) * volume))) - scale(ts_corr(close, cs_rank(ts_mean(volume, 20)), 5) - cs_rank(ts_argmin(close, 30)))) * (volume / ts_mean(volume, 20))")
#
#        # Alpha101 p
#        self.add_feature("alpha101", "((close - open) / ((high - low) + 0.001))")

        # Set label
        self.set_label("ts_delay(close, -3) / ts_delay(close, -1) - 1")

        # self.add_processor("infer", partial(process_fill_na))

        self.add_processor("learn", partial(process_drop_na))
        self.add_processor("learn", partial(process_drop_na, names=["label"]))
        self.add_processor("learn", partial(process_cs_norm, names=["label"], method="zscore"))
