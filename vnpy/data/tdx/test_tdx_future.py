# flake8: noqa
import os
import sys
import json
vnpy_root = os.path.abspath(os.path.join(os.path.dirname(__file__), '..', '..', '..'))
if vnpy_root not in sys.path:
    sys.path.append(vnpy_root)

os.environ["VNPY_TESTING"] = "1"

from vnpy.data.tdx.tdx_common import FakeStrategy
from vnpy.data.tdx.tdx_future_data import *

t1 = FakeStrategy()
t2 = FakeStrategy()
# 创建API对象
api_01 = TdxFutureData(t1)

# 获取所有市场信息
markets = api_01.get_markets()
str_markets = json.dumps(markets, indent=1, ensure_ascii=False)
print(u'{}'.format(str_markets))

# 获取所有的期货合约明细
api_01.qry_instrument()

# 获取某个合约得最新价
price = api_01.get_price('rb2005')
print('price={}'.format(price))


# 获取主力合约
# result = api_01.get_mi_contracts()
# str_result = json.dumps(result,indent=1, ensure_ascii=False)
# print(str_result)

# 获取某个板块的合约
# result = api_01.get_contracts(exchange=Exchange.CZCE)

# 获取某个板块的主力合约
# result = api_01.get_mi_contracts_from_exchange(exchange=Exchange.CZCE)
# 获取主力合约（从各个板块组合获取）
# result = api_01.get_mi_contracts2()
# print(u'一共{}个记录:{}'.format(len(result), [c.get('code') for c in result]))
# str_result = json.dumps(result,indent=1, ensure_ascii=False)
# print(str_result)

# all_99_ticks= api_01.get_99_contracts()
# str_99_ticks = json.dumps(all_99_ticks, indent=1, ensure_ascii=False)
# print(u'{}'.format(str_99_ticks))

# 获取历史分钟线
"""
ret,bars = api_01.get_bars('I2001', period='1min', callback=t1.display_bar, start_dt=datetime.now().replace(hour=0,minute=0,second=0,microsecond=0))
line_close_oi = [{'close':x.close,'oi':x.openInterest} for x in bars]
import pandas as pd
df = pd.DataFrame(line_close_oi)
corr = df.corr()
print(corr)
corr_rate = round(abs(corr.iloc[0, 1]) * 100, 2)
"""
# 获取bar，并通过回调方式，提高给策略，逐一onbar
# api_01.get_bars('IF99', period='1min', callback=t1.display_bar, bar_freq=1)

# 获取bar，只返回 list[dict]
result, bars = api_01.get_bars('IF99', period='1min', return_bar=False)
if result:
    print('前十根bar')
    for bar in bars[0:10]:
        print(bar)
    print('后十根bar')
    for bar in bars[-10:]:
        print(bar)

# result,datas = api_01.get_transaction_data(symbol='ni1905')
# api_02 = TdxFutureData(t2)
# api_02.get_bars('IF99', period='1min', callback=t1.display_bar)

# 获取当前交易日分时数据
# ret,result = api_01.get_transaction_data('RB99')
# for r in result[0:10] + result[-10:]:
#     print(r)

# 获取历史分时数据
# ret, result = api_01.get_history_transaction_data('RB99', '20190109')
# for r in result[0:10] + result[-10:]:
#    print(r)

# 更新本地合约缓存信息
api_01.update_mi_contracts()
