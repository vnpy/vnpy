from api import *

def test_config():
	cfig = Config()
	print cfig.body, cfig.head, cfig.token
	cfig.view()

def test_mktbar_D1():
	api = PyApi(Config())
	data = api.get_equity_D1()
	print data.body

def test_mktbar_M1():
	api = PyApi(Config())
	data = api.get_equity_M1()
	print data.body.tail()

def test_bond_D1():
	api = PyApi(Config())
	data = api.get_bond_D1()
	print data.body.tail()

def test_fut_D1():
	api = PyApi(Config())
	data = api.get_future_D1()
	print data.body

def test_fund_D1():
	api = PyApi(Config())
	data = api.get_fund_D1()
	print data.body

def test_index_D1():
	api = PyApi(Config())
	data = api.get_index_D1()
	print data.body

def test_option_D1():
	api = PyApi(Config())
	data = api.get_option_D1()
	print data.body

def test_factors_D1():
	api = PyApi(Config())
	data = api.get_stockFactor_D1()
	print data.body

def test_bs():
	api = PyApi(Config())
	data = api.get_balanceSheet()
	print data.body

def test_cf():
	api = PyApi(Config())
	data = api.get_cashFlow()
	print data.body

def test_is():
	api = PyApi(Config())
	data = api.get_incomeStatement()
	print data.body

def test_output():
	api = PyApi(Config())
	data = api.get_equity_D1(ticker='000001',output='list')
	print data

def test_mongod_get_drudgery():
	c = MongoClient()
	db = c['test_dy']
	api = PyApi(Config())
	api.get_equity_D1_drudgery(id=1, db=db, 
		start='20130101', end='20150801', 
		tasks=['000001','000002'])

def test_mongod_get_all():
	c = MongoClient()
	db = c['test_dy']
	api = PyApi(Config())
	api.get_equity_D1_mongod(db=db, start='20130101', end='20150801')

def test_mktbar_M1_get_drudgery():
	c = MongoClient()
	db = c['test_dy_m1']
	api = PyApi(Config())
	api.get_equity_M1_drudgery(id=1, db=db, 
		start='20150701', end='20150801', 
		tasks=['000001.XSHE','000002.XSHE'])

def test_mktbar_M1_get_all():
	c = MongoClient()
	db = c['test_dy_m1']
	api = PyApi(Config())
	api.get_equity_M1_mongod(db=db)

def test_mktbar_M1_get_interM():
	c = MongoClient()
	db = c['test_dy_m1']
	api = PyApi(Config())
	api.get_equity_M1_interMonth(db=db, id=0, tasks=['000001.XSHE','000002.XSHE'])

if __name__ == '__main__':
	#test_config()
	test_mktbar_D1()
	#test_bond_D1()
	#test_fut_D1()
	#test_fund_D1()
	#test_index_D1()
	#test_option_D1()
	#test_factors_D1()
	#test_mktbar_M1()
	#test_bs()
	#test_cf()
	#test_is()
	#test_output()
	#test_mongod_get_all()
	#test_mktbar_M1_get_drudgery()
	#test_mktbar_M1_get_all()
	#test_mktbar_M1_get_interM()