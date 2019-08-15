from vnpy.trader.constant import Exchange


def extract_vt_symbol(vt_symbol: str):
    """
    :return: (symbol, exchange)
    """
    symbol, exchange_str = vt_symbol.split(".")
    return symbol, Exchange(exchange_str)


def generate_vt_symbol(symbol: str, exchange: Exchange):
    """
    return vt_symbol
    """
    return f"{symbol}.{exchange.value}"