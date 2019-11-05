from ccxt import Exchange
import ccxt

exchange = ccxt.okex3()
markets = exchange.load_markets()  # 载入市场
# print(exchange.symbols)  # 打印交易对

limits = markets['ADA/BTC']['limits']['amount']['min']  # 获取币种的最小下单量，不是所有的交易对都有
print(limits)

# def get_min_limit_by_exchange(exchange: Exchange, symbol: str) -> float:
#     """"""
#     limits = exchange.load_trading_limits()
#     return limits
#
#
# if __name__ == "__main__":
#     print(exchange.load_markets().["BTC/"])
