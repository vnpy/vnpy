# encoding: UTF-8

from vnfxcm import FxcmApi

url = 'https://api-demo.fxcm.com:443'
port = 443    
token = '48055b5d9afac0a300143ac067ce04cd2430a434'
proxy = 'https://localhost:1080'

api = FxcmApi()
print 'api created'

api.connect(url, port, token, proxy)
print api.bearer

#api.getInstruments()

api.subscribe('EUR/USD')
api.subscribe('USD/JPY')
api.subscribe('GBP/USD')
#api.getModel('Summary')
#api.subscribeModel('Summary')

input()