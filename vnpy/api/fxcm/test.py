# encoding: UTF-8

from time import sleep

from vnfxcm import FxcmApi

url = 'https://api-demo.fxcm.com:443'
port = 443    
token = '48055b5d9afac0a300143ac067ce04cd2430a434'
proxy = 'https://localhost:1080'

api = FxcmApi()
print 'api created'

api.connect(url, port, token, proxy)
print api.bearer

sleep(20)
#api.getInstruments()

#api.subscribe('EUR/USD')
#api.subscribe('USD/JPY')
#api.subscribe('GBP/USD')
#api.getModel('Summary')
#api.subscribeModel('Summary')
#api.getModel(api.MODEL_SUMMARY)

#api.getModel(api.MODEL_OFFER)
api.subscribeModel(api.MODEL_OFFER)
api.updateSubscriptions('EUR/USD')
api.subscribe('EUR/USD')

#api.subscribeModel(api.MODEL_ACCOUNT)

input()