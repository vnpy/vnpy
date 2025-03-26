import polars as pl

from vnpy.alpha import AlphaDataset


class Alpha158(AlphaDataset):
    """158 basic factors from Qlib"""

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

        # Candlestick pattern features
        self.add_feature("kmid", "(close - open) / open")
        self.add_feature("klen", "(high - low) / open")
        self.add_feature("kmid_2", "(close - open) / (high - low + 1e-12)")
        self.add_feature("kup", "(high - greater(open, close)) / open")
        self.add_feature("kup_2", "(high - greater(open, close)) / (high - low + 1e-12)")
        self.add_feature("klow", "(less(open, close) - low) / open")
        self.add_feature("klow_2", "((less(open, close) - low) / (high - low + 1e-12))")
        self.add_feature("ksft", "(close * 2 - high - low) / open")
        self.add_feature("ksft_2", "(close * 2 - high - low) / (high - low + 1e-12)")

        # Price change features
        for field in ["open", "high", "low", "vwap"]:
            self.add_feature(f"{field}_0", f"{field} / close")

        # Time series features
        windows: list[int] = [5, 10, 20, 30, 60]

        for w in windows:
            self.add_feature(f"roc_{w}", f"ref(close, {w}) / close")

        for w in windows:
            self.add_feature(f"ma_{w}", f"mean(close, {w}) / close")

        for w in windows:
            self.add_feature(f"std_{w}", f"std(close, {w}) / close")

        for w in windows:
            self.add_feature(f"beta_{w}", f"slope(close, {w}) / close")

        for w in windows:
            self.add_feature(f"rsqr_{w}", f"rsquare(close, {w})")

        for w in windows:
            self.add_feature(f"resi_{w}", f"resi(close, {w}) / close")

        for w in windows:
            self.add_feature(f"max_{w}", f"max(high, {w}) / close")

        for w in windows:
            self.add_feature(f"min_{w}", f"min(low, {w}) / close")

        for w in windows:
            self.add_feature(f"qtlu_{w}", f"quantile(close, {w}, 0.8) / close")

        for w in windows:
            self.add_feature(f"qtld_{w}", f"quantile(close, {w}, 0.2) / close")

        for w in windows:
            self.add_feature(f"rank_{w}", f"ts_rank(close, {w})")

        for w in windows:
            self.add_feature(f"rsv_{w}", f"(close - min(low, {w})) / (max(high, {w}) - min(low, {w}) + 1e-12)")

        for w in windows:
            self.add_feature(f"imax_{w}", f"idxmax(high, {w}) / {w}")

        for w in windows:
            self.add_feature(f"imin_{w}", f"idxmin(low, {w}) / {w}")

        for w in windows:
            self.add_feature(f"imxd_{w}", f"(idxmax(high, {w}) - idxmin(low, {w})) / {w}")

        for w in windows:
            self.add_feature(f"corr_{w}", f"corr(close, log(volume + 1), {w})")

        for w in windows:
            self.add_feature(f"cord_{w}", f"corr(close / ref(close, 1), log(volume / ref(volume, 1) + 1), {w})")

        for w in windows:
            self.add_feature(f"cntp_{w}", f"mean(close > ref(close, 1), {w})")

        for w in windows:
            self.add_feature(f"cntn_{w}", f"mean(close < ref(close, 1), {w})")

        for w in windows:
            self.add_feature(f"cntd_{w}", f"mean(close > ref(close, 1), {w}) - mean(close < ref(close, 1), {w})")

        for w in windows:
            self.add_feature(f"sump_{w}", f"sum(greater(close - ref(close, 1), 0), {w}) / (sum(abs(close - ref(close, 1)), {w}) + 1e-12)")

        for w in windows:
            self.add_feature(f"sumn_{w}", f"sum(greater(ref(close, 1) - close, 0), {w}) / (sum(abs(close - ref(close, 1)), {w}) + 1e-12)")

        for w in windows:
            self.add_feature(f"sumd_{w}", f"(sum(greater(close - ref(close, 1), 0), {w}) - sum(greater(ref(close, 1) - close, 0), {w})) / (sum(abs(close - ref(close, 1)), {w}) + 1e-12)")

        for w in windows:
            self.add_feature(f"vma_{w}", f"mean(volume, {w}) / (volume + 1e-12)")

        for w in windows:
            self.add_feature(f"vstd_{w}", f"std(volume, {w}) / (volume + 1e-12)")

        for w in windows:
            self.add_feature(f"wvma_{w}", f"std(abs(close / ref(close, 1) - 1) * volume, {w}) / (mean(abs(close / ref(close, 1) - 1) * volume, {w}) + 1e-12)")

        for w in windows:
            self.add_feature(f"vsump_{w}", f"sum(greater(volume - ref(volume, 1), 0), {w}) / (sum(abs(volume - ref(volume, 1)), {w}) + 1e-12)")

        for w in windows:
            self.add_feature(f"vsumn_{w}", f"sum(greater(ref(volume, 1) - volume, 0), {w}) / (sum(abs(volume - ref(volume, 1)), {w}) + 1e-12)")

        for w in windows:
            self.add_feature(f"vsumd_{w}", f"(sum(greater(volume - ref(volume, 1), 0), {w}) - sum(greater(ref(volume, 1) - volume, 0), {w})) / (sum(abs(volume - ref(volume, 1)), {w}) + 1e-12)")

        # Set label
        self.set_label("ref(close, -3) / ref(close, -1) - 1")
