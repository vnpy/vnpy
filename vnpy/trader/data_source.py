# 国内商品期货数据源
# 华富资产 李来佳

import pandas as pd
import json
import requests
from datetime import datetime

import os,sys
ROOT_PATH = os.path.abspath(os.path.join(os.path.dirname(__file__), '..', '..'))
if ROOT_PATH not in sys.path:
    sys.path.append(ROOT_PATH)

from vnpy.trader.vtGlobal import globalSetting

class DataSource:
    def __init__(self):
        self.bar_url = None

        if globalSetting['dataSource']:
            self.bar_url = globalSetting['dataSource']
        self.headers = {}

        requests.adapters.DEFAULT_RETRIES = 5
        session = requests.session()
        session.keep_alive = False

    def get_price(self, order_book_id, start_date, end_date, frequency, fields=[],
                     skip_suspended=True, include_now=True,
                     adjust_type='pre', adjust_orig=None):

        if frequency not in ('1m', '5m', '15m', '30m', '60m', '1d'):
            raise NotImplementedError
        if self.bar_url is None:
            raise NotImplementedError

        fields_str = fields if isinstance(fields, str) else ",".join(fields)
        values = {"order_book_id": order_book_id, "frequency": frequency, "include_now": include_now,
                  "start_date": start_date, "end_date": end_date, "fields": fields_str}

        rsp_data = ''
        try:
            rsp_data = requests.get(self.bar_url, params=values)
        except Exception as e:
            print( str(e),file=sys.stderr)

        json_data = json.loads(rsp_data.content.decode("utf-8"))

        df = pd.read_json(json_data, orient="index", typ="frame")
        df.index.names = ['datetime']
        if fields_str.strip() and fields_str.find(",") < 0:
            df = df[fields_str]

        #print df.columns
        #print df
        #print type(df)

        return df

if __name__ == '__main__':


    d = DataSource()
    fields = ['open', 'close', 'high', 'low',  'volume', 'open_interest', 'limit_up', 'limit_down', 'trading_date']
    df = d.get_price('I1809',start_date='2018-02-01',end_date='2018-04-17',frequency='5m',fields = fields)
    #df = d.get_price('ZC99', start_date='2017-01-01', end_date=datetime.now().strftime('%Y-%m-%d'), frequency='1m', fields=fields)

    for idx in df.index:
     row = df.loc[idx]
     bartime = str(idx)
     dt_timestamp = df['trading_date'].loc[idx]
     #dt_bartime = df['datetime'].loc[idx]
     print('bartime:{},trading_date:{}'.format(bartime,datetime.fromtimestamp(dt_timestamp/1e3).strftime('%Y-%m-%d')))
