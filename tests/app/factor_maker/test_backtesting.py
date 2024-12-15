import unittest
import pandas as pd

from vnpy.app.factor_maker.backtesting import resample_bar_pandas, resample_factor_pandas, FactorBacktester


class TestBacktesting(unittest.TestCase):

    def setUp(self):
        """
        Set up test data for all test cases.
        """
        # Generate 1-minute sample data
        date_range = pd.date_range("2024-01-01", periods=60, freq="1min")
        self.ohlcv_data = {
            "open": pd.DataFrame({"AAPL": range(100, 160)}, index=date_range),
            "high": pd.DataFrame({"AAPL": range(101, 161)}, index=date_range),
            "low": pd.DataFrame({"AAPL": range(99, 159)}, index=date_range),
            "close": pd.DataFrame({"AAPL": range(100, 160)}, index=date_range),
            "volume": pd.DataFrame({"AAPL": [100] * 60}, index=date_range),
        }

        self.factor_data = pd.DataFrame(
            {"AAPL": range(60)},
            index=date_range
        )

    def test_resample_bar(self):
        """
        Test the resample_bar function for valid output.
        """
        resampled_data = resample_bar_pandas(self.ohlcv_data, "5min")
        self.assertEqual(len(resampled_data["open"]), 12)  # 60 minutes resampled to 5-minute intervals
        self.assertAlmostEqual(resampled_data["volume"]["AAPL"].iloc[0], 500)  # 5-minute sum of volume

    def test_resample_factor(self):
        """
        Test the resample_factor function for various methods.
        """
        resampled_mean = resample_factor_pandas(self.factor_data, "5min", method="mean")
        self.assertEqual(len(resampled_mean), 12)  # 60 minutes resampled to 5-minute intervals
        self.assertAlmostEqual(resampled_mean["AAPL"].iloc[0], 2.0)  # Mean of 0-4

        resampled_sum = resample_factor_pandas(self.factor_data, "5min", method="sum")
        self.assertAlmostEqual(resampled_sum["AAPL"].iloc[0], 10)  # Sum of 0-4

    def test_calculate_trading_periods_per_year(self):
        """
        Test the calculate_trading_periods_per_year method.
        """
        self.assertEqual(FactorBacktester.calculate_trading_periods_per_year("1min"), 525600)
        self.assertEqual(FactorBacktester.calculate_trading_periods_per_year("2H"), 4380)
        self.assertEqual(FactorBacktester.calculate_trading_periods_per_year("1D"), 365)

    def test_run_backtesting(self):
        """
        Test the run_backtesting method for correct metrics calculation.
        """
        backtester = FactorBacktester(self.ohlcv_data, trading_freq="5min")
        factor_values = resample_factor_pandas(self.factor_data, "5min", method="mean")
        metrics = backtester.run_backtesting_pandas(factor_values, if_plot=False)

        self.assertIn("Cumulative Return", metrics)
        self.assertIn("Annualized Return", metrics)
        self.assertIn("Annualized Volatility", metrics)
        self.assertIn("Sharpe Ratio", metrics)

        # Ensure reasonable values
        self.assertGreater(metrics["Cumulative Return"], -1.0)
        self.assertGreater(metrics["Annualized Return"], -1.0)
        self.assertGreater(metrics["Sharpe Ratio"], -10.0)

    def test_invalid_resample_bar(self):
        """
        Test invalid resample_bar input.
        """
        with self.assertRaises(ValueError):
            resample_bar_pandas({"close": self.ohlcv_data["close"]}, "1H")  # Missing required keys

    def test_invalid_resample_factor(self):
        """
        Test invalid resample_factor input.
        """
        with self.assertRaises(ValueError):
            resample_factor_pandas(self.factor_data, "5min", method="invalid")  # Unsupported method

    def test_invalid_trading_frequency(self):
        """
        Test invalid trading frequency.
        """
        with self.assertRaises(ValueError):
            FactorBacktester.calculate_trading_periods_per_year("10X")  # Invalid unit

    def test_plot_portfolio_performance(self):
        """
        Test the plot_portfolio_performance method to ensure it executes without errors.
        """
        backtester = FactorBacktester(self.ohlcv_data, trading_freq="5min")
        factor_values = resample_factor_pandas(self.factor_data, "5min", method="mean")
        backtester.run_backtesting_pandas(factor_values, if_plot=True)


if __name__ == "__main__":
    unittest.main()
