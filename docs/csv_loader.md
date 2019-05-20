# CSV载入模块

CSV载入模块在vnpy根目录下vnpy\app\csv_loader文件夹内，engine.py里面的CsvLoaderEngine类负责载入功能实现。

## 初始化配置
初始化数据载入相关信息，可以分成3类：

- CSV文件路径
- 合约信息：合约代码、交易所、K线周期
- CSV表头信息：日期时间、开盘价、最高价、最低价、收盘价、成交量

```
        self.file_path: str = ''

        self.symbol: str = ""
        self.exchange: Exchange = Exchange.SSE
        self.interval: Interval = Interval.MINUTE

        self.datetime_head: str = ''
        self.open_head: str = ''
        self.close_head: str = ''
        self.low_head: str = ''
        self.high_head: str = ''
        self.volume_head: str = ''
```

&nbsp;

## 数据载入

从文件路径中读取CSV文件，然后在每一次迭代中载入数据到数据库中。
```
        with open(file_path, 'rt') as f:
            reader = csv.DictReader(f)

            for item in reader:
```

&nbsp;

载入数据的方法可以分成2类：
- 直接插入：合约代码、交易所、K线周期、成交量、开盘价、最高价、最低价、收盘价、接口名称
- 需要处理：日期时间（根据其相应的时间格式，通过strptime()转化成时间元祖）、vt_symbol(合约代码.交易所格式，如rb1905.SHFE)

注意：db_bar.replace()用于数据更新，即把旧的数据替换成新的。
```
                db_bar.symbol = symbol
                db_bar.exchange = exchange.value
                db_bar.datetime = datetime.strptime(
                    item[datetime_head], datetime_format
                )
                db_bar.interval = interval.value
                db_bar.volume = item[volume_head]
                db_bar.open_price = item[open_head]
                db_bar.high_price = item[high_head]
                db_bar.low_price = item[low_head]
                db_bar.close_price = item[close_head]
                db_bar.vt_symbol = vt_symbol
                db_bar.gateway_name = "DB"

                db_bar.replace()
```

