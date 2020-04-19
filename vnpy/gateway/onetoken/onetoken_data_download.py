import json
from pathlib import Path

import arrow

from vnpy.trader.constant import Interval, Exchange
from vnpy.trader.database import database_manager
from vnpy.trader.object import BarData

# 修改成你的OT Key
otkey = 'aaaa-bbbb-cccc-dddd'


def add_con(con, since, exg, exg_1token):
    global otkey
    if otkey == 'aaaa-bbbb-cccc-dddd':
        local = Path('~/.1token/http-checker.json').expanduser().read_text()
        otkey = json.loads(local)['ot_key']

    print('otkey', otkey[:3])
    import requests
    fullcon = f'{exg_1token}/{con}'
    print(fullcon)
    while since < arrow.now().shift(days=-30):
        since = since.shift(days=10)
        until = since.shift(days=10)
        url = f'http://hist-quote.1tokentrade.cn/candles?contract={fullcon}&since={since.date()}&until={until.date()}' \
              f'&duration=1m&format=json'
        print(url)
        res = requests.get(url, headers={'ot-key': otkey}, timeout=15)
        if res.status_code != 200:
            print(res.json())
            return
        print('quota remain', res.headers['ot-quota-remaining'])
        if len(res.json()) == 0:
            continue
        print(res, len(res.json()))
        data = []
        for item in res.json():
            t = arrow.get(item['timestamp']).to('Asia/Shanghai').datetime
            t = t.replace(tzinfo=None)
            single_data = BarData(symbol=con.upper().replace('.', '_'),
                                  gateway_name='1token',
                                  exchange=exg,
                                  volume=item['volume'],
                                  open_interest=0,
                                  interval=Interval.MINUTE,
                                  datetime=t,
                                  open_price=item['open'],
                                  high_price=item['high'],
                                  close_price=item['close'],
                                  low_price=item['low'])
            data.append(single_data)

            # return

        print(data[0])
        print(data[-1])
        # return
        res = database_manager.save_bar_data(data)
        print(res)
    return


if __name__ == '__main__':
    # add_con('btc.usdt', since=arrow.get(2016, 1, 1), exg=Exchange('HUOBI'), exg_1token='huobip')
    add_con('btc.usd.q', since=arrow.get(2016, 1, 1), exg=Exchange('HUOBI'), exg_1token='huobif')
    print(database_manager.get_bar_data_statistics())
