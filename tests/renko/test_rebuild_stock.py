# flake8: noqa
import os
import sys

vnpy_root = os.path.abspath(os.path.join(os.path.dirname(__file__), '..', '..', '..'))
if vnpy_root not in sys.path:
    sys.path.append(vnpy_root)

os.environ["VNPY_TESTING"] = "1"

from vnpy.data.renko.rebuild_stock import *

# Mongo数据库得地址，renko数据库名，tick文件缓存目录
setting = {
    "host": "192.168.0.207",
    "db_name": STOCK_RENKO_DB_NAME,
    "cache_folder": os.path.join(vnpy_root, 'tick_data', 'tdx', 'stock')
}
builder = StockRenkoRebuilder(setting)

# 生成单个
# builder.start(symbol='600410',min_diff=0.01, height=10, start_date='2019-04-01', end_date='2019-09-10')
# 生成多个
builder.start(symbol='123022', price_tick=0.001, height=[10, 'K3', 'K5'], start_date='2019-01-01',
              end_date='2019-12-31')

# 导出csv
# builder.export(symbol='600410',height=10, start_date='2019-04-01', end_date='2019-09-10')

# 生成批量更新脚本
# builder.export_scripts()

builder.check_all_index()

exit(0)
