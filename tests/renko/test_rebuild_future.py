# flake8: noqa
import os
import sys

vnpy_root = os.path.abspath(os.path.join(os.path.dirname(__file__), '..', '..', '..'))
if vnpy_root not in sys.path:
    sys.path.append(vnpy_root)

os.environ["VNPY_TESTING"] = "1"

from vnpy.data.renko.rebuild_future import *

# Mongo数据库得地址，renko数据库名，tick文件缓存目录
setting = {
    "host": "127.0.0.1",
    "db_name": FUTURE_RENKO_DB_NAME,
    "cache_folder": os.path.join(vnpy_root, 'tick_data', 'tdx', 'future')
}
builder = FutureRenkoRebuilder(setting)

# 生成单个
# builder.start(symbol='RB99',min_diff=1, height=10, start_date='2019-04-01', end_date='2019-09-10')

# 生成多个
#builder.start(symbol='J99', price_tick=0.5, height=[10, 'K3'], start_date='2016-01-01', end_date='2016-02-16')

# 在数据库最新renko基础上开始追加数据
builder.start(symbol='J99', price_tick=0.5, height=[10, 'K3', 'K5'], start_date='2016-01-01', refill=True)

# 导出csv
# builder.export(symbol='RB99',height=10, start_date='2019-04-01', end_date='2019-09-10')

# 生成批量更新脚本
# builder.export_scripts()

# builder.check_all_index()

exit(0)
