# Utility functions for memory management and data handling

from datetime import datetime
from typing import Dict
import polars as pl
from vnpy.trader.object import BarData
from vnpy.trader.utility import extract_vt_symbol

def truncate_memory(memory: Dict[str, pl.DataFrame], max_length: int) -> None:
    """
    Truncate the memory to the maximum length.

    Parameters:
        memory (Dict[str, pl.DataFrame]): Memory dictionary to truncate.
        max_length (int): Maximum allowed length of the memory.
    """
    for key, df in memory.items():
        if len(df) > max_length:
            memory[key] = df.tail(max_length)

def create_placeholder_bar(dt: datetime, vt_symbol: str, bars: dict) -> BarData:
    """
    Create a placeholder bar when data is missing.

    Parameters:
        dt (datetime): The datetime for the placeholder bar.
        vt_symbol (str): The vt_symbol for the placeholder bar.
        bars (dict): Dictionary of existing bars.

    Returns:
        BarData: A placeholder bar with default or previous values.
    """
    symbol, exchange = extract_vt_symbol(vt_symbol)
    if vt_symbol in bars:
        previous_bar = bars[vt_symbol]
        return BarData(
            symbol=previous_bar.symbol,
            exchange=previous_bar.exchange,
            datetime=dt,
            open_price=previous_bar.close_price,
            high_price=previous_bar.close_price,
            low_price=previous_bar.close_price,
            close_price=previous_bar.close_price,
            gateway_name=previous_bar.gateway_name,
        )
    return BarData(
        symbol=symbol,
        exchange=exchange,
        datetime=dt,
        open_price=0,
        high_price=0,
        low_price=0,
        close_price=0,
        gateway_name=""
    )