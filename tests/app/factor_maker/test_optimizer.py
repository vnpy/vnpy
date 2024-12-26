# -*- coding=utf-8 -*-
# @Project  : 20240720
# @FilePath : ${DIR_PATH}
# @File     : ${FILE_NAME}
# @Time     : 2024/12/18 16:17
# @Author   : EvanHong
# @Email    : 939778128@qq.com
# @Description:
from unittest import TestCase


class TestFactorOptimizer(TestCase):

    def test_main(self):
        if __name__ == "__main__":
            # Load historical data
            def load_data() -> Dict[str, pd.DataFrame]:
                dates = pd.date_range(start="2020-01-01", end="2023-12-31", freq="B")
                symbols = ["AAPL", "MSFT", "GOOGL", "AMZN"]
                close_prices = pd.DataFrame(
                    data=np.random.uniform(100, 200, size=(len(dates), len(symbols))),
                    index=dates,
                    columns=symbols,
                )
                return {"close": close_prices}

            data = load_data()

            class MACD(FactorTemplate):
                factor_name = 'macd'
                dependencies_factor = []

                def __init__(self, setting, **kwargs):
                    self.add_params('window')
                    self.add_params('freq')
                    super().__init__(setting, **kwargs)

                def __init_dependencies__(self, ma10_setting, ma20_setting):
                    self.ma_fast = MA(ma10_setting)

                def calculate_polars(self, input_data: pl.DataFrame, *args, **kwargs) -> Any:
                    ma_fast = input_data[self.ma_fast.factor_key]

            macd = MACD({}, window=10, freq='1min')

            input_data = {
                'ma_window_10', df1,
                'ma_window_20', df2
            }

            ma10_setting = {}
            ma20_setting = {}
            ma10 = MA(ma10_setting)
            ma20 = MA(ma20_setting)

            macd.dependencies_factor = [ma20, ma10]

            macd.to_dict()



