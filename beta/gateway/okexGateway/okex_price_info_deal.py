# encoding: UTF-8

'''
处理okex 下单精度表.txt
'''
ss = {"enj_btc":{"min_trade_size":1,"quote_increment":0.001}}
def deal_price_info():
	f_in = open("okex_price_info.txt" , "r")
	f_out = open("okex_price_info.py" , "w")

	f_out.write("# encoding: UTF-8\n\n")
	f_out.write("okex_price_info = {")

	first_flag = False
	for line in f_in:
		# 币对ID(Product_id)	币对(Symbol)	最小交易单位(min_trade_size)	下单精度(quote_increment)
		arr = line.strip().split('\t')
		new_arr = []
		for ii in arr:
			if len(ii) > 0:
				new_arr.append( ii)
		(_id , symbol_pair , min_trade_size , quote_increment) = new_arr
		print symbol_pair , min_trade_size , quote_increment

		if first_flag == False:
			first_flag = True
			f_out.write( '\n')
		else:
			f_out.write( ',\n')

		f_out.write( "\"%s\":{\"min_trade_size\":%s,\"quote_increment\":%s}" % (symbol_pair,str(min_trade_size) , str(quote_increment)))

	f_out.write("\n}\n\n")

	f_in.close()
	f_out.close()

if __name__ == '__main__':
	deal_price_info()