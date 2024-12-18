from enum import Enum

import polars as pl
from collections import deque
from datetime import datetime, timedelta


class FactorMode(Enum):
    """
    因子计算模式
    """
    Live = "live"
    Backtest = "backtest"


class RollingDataFrame:
    def __init__(self, columns, max_length):
        """
        Initialize the RollingDataFrame.

        Args:
            columns (list): List of column names.
            max_length (int): Maximum number of rows allowed (queue size).
        """
        self.columns = columns
        self.max_length = max_length
        self.datetime_queue = deque(maxlen=max_length)
        self.data = pl.DataFrame(schema=["datetime"] + columns)

    def append_row(self, datetime_value, values):
        """
        Append a new row to the RollingDataFrame.

        Args:
            datetime_value (datetime): The datetime for the new row.
            values (list): A list of values corresponding to the tickers.
        """
        # Ensure datetime is in the queue
        self.datetime_queue.append(datetime_value)

        # Add data to the DataFrame
        new_data = {col: val for col, val in zip(self.columns, values)}
        new_data["datetime"] = datetime_value
        new_row = pl.DataFrame([new_data])

        # Concatenate and respect the max length
        self.data = pl.concat([self.data, new_row], how="vertical")
        if self.data.height > self.max_length:
            self.data = self.data.tail(self.max_length)

    def get_dataframe(self) -> pl.DataFrame:
        """
        Retrieve the current DataFrame.

        Returns:
            pl.DataFrame: The rolling DataFrame with datetime and tickers.
        """
        return self.data

    def clone(self):
        """
        Clone the RollingDataFrame.

        Returns:
            RollingDataFrame: A new RollingDataFrame with the same data.
        """
        # raise NotImplementedError("Not implemented yet")
        new_rdf = RollingDataFrame(self.columns, self.max_length)
        new_rdf.datetime_queue = deque(self.datetime_queue)
        new_rdf.data = self.data.clone()
        return new_rdf


APP_NAME = "FactorMaker"

EVENT_FACTOR_LOG = "eFactorLog"
EVENT_FACTOR_MAKER = "eFactorMaker"

EVENT_FACTOR_RECORD = "eFactorRecord"
