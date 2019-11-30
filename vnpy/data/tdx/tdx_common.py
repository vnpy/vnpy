# encoding: UTF-8

from functools import lru_cache


@lru_cache()
def get_tdx_market_code(code):
    # 获取通达信股票的market code
    code = str(code)
    if code[0] in ['5', '6', '9'] or code[:3] in ["009", "126", "110", "201", "202", "203", "204"]:
        # 上海证券交易所
        return 1
    # 深圳证券交易所
    return 0


# 通达信 K 线种类
# 0 -   5 分钟K 线
# 1 -   15 分钟K 线
# 2 -   30 分钟K 线
# 3 -   1 小时K 线
# 4 -   日K 线
# 5 -   周K 线
# 6 -   月K 线
# 7 -   1 分钟
# 8 -   1 分钟K 线
# 9 -   日K 线
# 10 -  季K 线
# 11 -  年K 线
PERIOD_MAPPING = {}
PERIOD_MAPPING['1min'] = 8
PERIOD_MAPPING['5min'] = 0
PERIOD_MAPPING['15min'] = 1
PERIOD_MAPPING['30min'] = 2
PERIOD_MAPPING['1hour'] = 3
PERIOD_MAPPING['1day'] = 4
PERIOD_MAPPING['1week'] = 5
PERIOD_MAPPING['1month'] = 6

# 期货行情服务器清单
TDX_FUTURE_HOSTS = [
    {"ip": "112.74.214.43", "port": 7727, "name": "扩展市场深圳双线1"},
    {"ip": "120.24.0.77", "port": 7727, "name": "扩展市场深圳双线2"},
    {"ip": "47.107.75.159", "port": 7727, "name": "扩展市场深圳双线3"},

    {"ip": "113.105.142.136", "port": 443, "name": "扩展市场东莞主站"},
    {"ip": "113.105.142.133", "port": 443, "name": "港股期货东莞电信"},

    {"ip": "119.97.185.5", "port": 7727, "name": "扩展市场武汉主站1"},
    {"ip": "119.97.185.7", "port": 7727, "name": "港股期货武汉主站1"},
    {"ip": "119.97.185.9", "port": 7727, "name": "港股期货武汉主站2"},
    {"ip": "59.175.238.38", "port": 7727, "name": "扩展市场武汉主站3"},

    {"ip": "202.103.36.71", "port": 443, "name": "扩展市场武汉主站2"},

    {"ip": "47.92.127.181", "port": 7727, "name": "扩展市场北京主站"},
    {"ip": "106.14.95.149", "port": 7727, "name": "扩展市场上海双线"},
    {"ip": '218.80.248.229', 'port': 7721, "name": "备用服务器1"},
    {"ip": '124.74.236.94', 'port': 7721, "name": "备用服务器2"},
    {'ip': '58.246.109.27', 'port': 7721, "name": "备用服务器3"}]
