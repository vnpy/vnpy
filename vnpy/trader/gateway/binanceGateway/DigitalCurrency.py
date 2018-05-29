# encoding: utf-8

'''
	ethusdt --> eth_usdt
	etcbtc  --> etc_btc
	ethusdt.HUOBI --> eth_usdt
	etcbtc.HUOBI  --> etc_btc
'''
def systemSymbolToVnSymbol(symbol):
	symbol = symbol.replace('_','')
	symbol = ((symbol.split('.'))[0]).lower()
	if 'usdt' in symbol:
		return symbol[:-4] + "_usdt"
	else:
		return symbol[:-3] + "_" + symbol[-3:]


'''
	etc_btc  --> etcbtc
	eth_usdt --> ethusdt
'''
def VnSymbolToSystemSymbol(symbol):
	symbol = (symbol.split('.'))[0]
	return (''.join(symbol.split('_'))).lower()
