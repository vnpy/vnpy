"""
unittest use pytest
"""
from vnpy.gateway.onetoken.onetoken_gateway import contract_vnpy2ot


def test_vnpy():
    assert contract_vnpy2ot('okex', 'btc.usd.2020-06-26') == 'okef/btc.usd.2020-06-26'
    assert contract_vnpy2ot('okex', 'btc.usd.q') == 'okef/btc.usd.q'
    assert contract_vnpy2ot('okex', 'btc.usdt') == 'okex/btc.usdt'
    assert contract_vnpy2ot('okex', 'btc.usd.td') == 'okswap/btc.usd.td'

    assert contract_vnpy2ot('huobi', 'btc.usdt') == 'huobip/btc.usdt'
    assert contract_vnpy2ot('huobi', 'btc.usd.q') == 'huobif/btc.usd.q'
    assert contract_vnpy2ot('huobi', 'btc.usd.td') == 'huobiswap/btc.usd.td'

    assert contract_vnpy2ot('binance', 'btc.usdt.td') == 'binancef/btc.usdt.td'
    assert contract_vnpy2ot('binance', 'btc.usdt') == 'binance/btc.usdt'

    assert contract_vnpy2ot('gateio', 'btc.usdt') == 'gate/btc.usdt'
