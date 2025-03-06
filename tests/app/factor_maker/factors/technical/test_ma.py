# -*- coding=utf-8 -*-

#  Copyright (c) 2024. Lorem ipsum dolor sit amet, consectetur adipiscing elit.
#  Morbi non lorem porttitor neque feugiat blandit. Ut vitae ipsum eget quam lacinia accumsan.
#  Etiam sed turpis ac ipsum condimentum fringilla. Maecenas magna.
#  Proin dapibus sapien vel ante. Aliquam erat volutpat. Pellentesque sagittis ligula eget metus.
#  Vestibulum commodo. Ut rhoncus gravida arcu.

# @Project  : 20240720
# @FilePath : ${DIR_PATH}
# @File     : ${FILE_NAME}
# @Time     : 2024/11/28 23:02
# @Author   : EvanHong
# @Email    : 939778128@qq.com
# @Description:

from unittest import TestCase

from vnpy.app.factor_maker.factors.technical.ma import MA


class TestMA(TestCase):

    def init(self):
        self.factor = MA(setting={})

    def test_set_params(self):
        self.init()
        self.factor.set_params({'window': 10})
        self.assertEqual(self.factor.params.__dict__, {'window': 10})

    def test_sth(self):
        import polars as pl

        # 假设这是你的数据
        df = pl.DataFrame({
            "datetime": ["2024-01-01 00:00:00", "2024-01-01 00:01:00", "2024-01-01 00:02:00"],
            "btcusdt.BINANCE": [0.0, 0.514936, 1.029872],
            "ethusdt.BINANCE": [0.0, 0.039638, 0.079276]
        }).with_columns(
            pl.col("datetime").str.strptime(pl.Datetime, "%Y-%m-%d %H:%M:%S")
        )
        print(df)

        # 计算 5 周期 MA
        window_size = 2
        # # df_with_ma = df[-wi,ndow_size:,].mean()
        #
        # # Compute the moving average for each stock while keeping the datetime column
        # df_with_ma = df.with_columns(
        #     [
        #         pl.col(col).tail(window_size).mean()
        #         for col in df.columns if col != "datetime"
        #     ]
        # )
        #
        # print(df_with_ma)

        df_last_window = df.tail(window_size)
        # Compute the mean for each stock ticker
        ma_last = df_last_window.select(
            [pl.lit(df_last_window[-1, "datetime"]).alias("datetime")] +  # Keep latest datetime
            [pl.col(col).mean().alias(col) for col in df.columns if col != "datetime"]
        )
        print(ma_last)

    def test1(self):
        import polars as pl

        # 示例数据
        df1 = pl.DataFrame({
            "datetime": ["2024-01-01 00:00:00", "2024-01-01 00:01:00"],
            "btcusdt.BINANCE": [0.0, 0.514936]
        }).with_columns(pl.col("datetime").str.strptime(pl.Datetime, "%Y-%m-%d %H:%M:%S"))

        df2 = pl.DataFrame({
            "ethusdt.BINANCE": [0.0, 0.039638]
        })

        print(df1)
        print(df2)

        # 参数化
        dataframes = [df1, df2]  # 要连接的 DataFrame 列表
        concat_method = "vertical"  # 连接方式

        # 执行连接
        if concat_method == "horizontal":
            result_df = pl.concat(dataframes, how="horizontal")
        elif concat_method == "vertical":
            result_df = pl.concat(dataframes, how="vertical")
        else:
            raise ValueError("Unsupported concat method. Use 'vertical' or 'horizontal'.")

        print(result_df)

