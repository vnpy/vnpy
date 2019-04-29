# CTA策略模块


## 模块构成

CTA策略模块主要由7部分构成，如下图：

- base：定义了CTA模块中用到的一些基础设置，如引擎类型（回测/实盘）、回测模式（K线/Tick）、本地停止单的定义以及停止单状态（等待中/已撤销/已触发）。
  
- template：定义了CTA策略模板（包含信号生成和委托管理）、CTA信号（仅负责信号生成）、目标仓位算法（仅负责委托管理，适用于拆分巨型委托，降低冲击成本）。
- strategies: 官方提供的cta策略示例，包含从最基础的双均线策略，到通道突破类型的布林带策略，到跨时间周期策略，再到把信号生成和委托管理独立开来的多信号策略。
- backesting：包含回测引擎和参数优化。其中回测引擎定义了数据载入、委托撮合机制、计算与统计相关盈利指标、结果绘图等函数。
- converter：定义了针对上期所品种平今/平昨模式的委托转换模块；对于其他品种用户也可以通过可选参数lock切换至锁仓模式。
- engine：定义了CTA策略实盘引擎，其中包括：RQData客户端初始化和数据载入、策略的初始化和启动、推送Tick订阅行情到策略中、挂撤单操作、策略的停止和移除等。
- ui：基于PyQt5的GUI图形应用。

![](https://vnpy-community.oss-cn-shanghai.aliyuncs.com/forum_experience/yazhang/cta_strategy/seix_elementos.png "enter image title here")

&nbsp;

## 历史数据

### 回测历史数据
回测所需要的历史数据可通过运行getdata.py文件进行下载。该文件处于根目录下tests\backtesting文件夹内。
下载历史数据的原理是调用RQData的get_price()函数把数据下载到内存里面；再通过generate_bar_from_row()函数，以固定格式把数据从内存载入到硬盘数据库中。

下面介绍具体流程：

- 填写RQData的账号密码，初始化RQData
```
import rqdatac as rq


USERNAME = ""
PASSWORD = ""
FIELDS = ["open", "high", "low", "close", "volume"]

rq.init(USERNAME, PASSWORD, ("rqdatad-pro.ricequant.com", 16011))
```

&nbsp;

- 定义数据插入格式。需要插入的数据包括：合约代码、交易所、K线周期、开盘价、最高价、最低价、收盘价、成交量、数据库名称、vt_symbol（注意：K线周期可以是"1m"、"1h"、"d"、"w"。to_pydatetime()用于时间转换成datetime格式）
```
def generate_bar_from_row(row, symbol, exchange):
    """"""
    bar = DbBarData()

    bar.symbol = symbol
    bar.exchange = exchange
    bar.interval = "1m"
    bar.open_price = row["open"]
    bar.high_price = row["high"]
    bar.low_price = row["low"]
    bar.close_price = row["close"]
    bar.volume = row["volume"]
    bar.datetime = row.name.to_pydatetime()
    bar.gateway_name = "DB"
    bar.vt_symbol = f"{symbol}.{exchange}"

    return bar
```

&nbsp;

- 定义数据下载函数。主要调用RQData的get_price()获取指定合约或合约列表的历史数据（包含起止日期，日线或分钟线）。目前仅支持中国市场的股票、期货、ETF和上金所现货的行情数据，如黄金、铂金和白银产品。（注意：起始日期默认是2013-01-04，结束日期默认是2014-01-04）

```
def download_minute_bar(vt_symbol):
    """下载某一合约的分钟线数据"""
    print(f"开始下载合约数据{vt_symbol}")
    symbol, exchange = vt_symbol.split(".")

    start = time()

    df = rq.get_price(symbol, start_date="2018-01-01", end_date="2019-01-01", frequency="1m", fields=FIELDS)

    with DB.atomic():
        for ix, row in df.iterrows():
            print(row.name)
            bar = generate_bar_from_row(row, symbol, exchange)
            DbBarData.replace(bar.__data__).execute()

    end = time()
    cost = (end - start) * 1000

    print(
        "合约%s的分钟K线数据下载完成%s - %s，耗时%s毫秒"
        % (symbol, df.index[0], df.index[-1], cost)
    )

```


&nbsp;


### 实盘历史数据
在实盘中，RQData通过实时载入数据进行策略的初始化。该功能主要在CTA实盘引擎engine.py内实现。
下面介绍具体流程：
- 配置json文件：在用户目录下.vntrader文件夹找到vt_setting.json，输入RQData的账号和密码，如图。
  
![](https://vnpy-community.oss-cn-shanghai.aliyuncs.com/forum_experience/yazhang/cta_strategy/RQData_setting.png "enter image title here")

- 初始化RQData客户端：从vt_setting.json中读取RQData的账户、密码到rq_client.init()函数进行初始化

```
    def init_rqdata(self):
        """
        Init RQData client.
        """
        username = SETTINGS["rqdata.username"]
        password = SETTINGS["rqdata.password"]
        if not username or not password:
            return

        import rqdatac
        
        self.rq_client = rqdatac
        self.rq_client.init(username, password,
                            ('rqdatad-pro.ricequant.com', 16011))
```


- RQData载入实盘数据：输入vt_symbol后，首先会转换成符合RQData格式的rq_symbol，通过get_price()函数下载数据，并且插入到数据库中。
  
```
    def query_bar_from_rq(
        self, vt_symbol: str, interval: Interval, start: datetime, end: datetime
    ):
        """
        Query bar data from RQData.
        """
        symbol, exchange_str = vt_symbol.split(".")
        rq_symbol = to_rq_symbol(vt_symbol)
        if rq_symbol not in self.rq_symbols:
            return None
        
        end += timedelta(1)     # For querying night trading period data

        df = self.rq_client.get_price(
            rq_symbol,
            frequency=interval.value,
            fields=["open", "high", "low", "close", "volume"],
            start_date=start,
            end_date=end
        )

        data = []
        for ix, row in df.iterrows():
            bar = BarData(
                symbol=symbol,
                exchange=Exchange(exchange_str),
                interval=interval,
                datetime=row.name.to_pydatetime(),
                open_price=row["open"],
                high_price=row["high"],
                low_price=row["low"],
                close_price=row["close"],
                volume=row["volume"],
                gateway_name="RQ"
            )
            data.append(bar)
```

&nbsp;

## 策略开发
CTA策略模板提供完整的信号生成和委托管理功能，用户可以基于该模板自行开发策略。新策略可以放在根目录下vnpy\app\cta_strategy\strategies文件夹内，也可以放在用户运行的文件内（VN Station模式）。注意：策略文件命名是以下划线模式，如boll_channel_strategy.py；而策略类命名采用的是驼峰式，如BollChannelStrategy。

下面通过BollChannelStrategy策略示例，来展示策略开发的具体步骤：

### 参数设置

定义策略参数并且初始化策略变量。策略参数为策略类的公有属性，用户可以通过创建新的实例来调用或者改变策略参数。

如针对rb1905品种，用户可以创建基于BollChannelStrategy的策略示例，如RB_BollChannelStrategy，boll_window可以由18改成30。

创建策略实例的方法有效地实现了一个策略跑多个品种，并且其策略参数可以通过品种的特征进行调整。
```
    boll_window = 18
    boll_dev = 3.4
    cci_window = 10
    atr_window = 30
    sl_multiplier = 5.2
    fixed_size = 1

    boll_up = 0
    boll_down = 0
    cci_value = 0
    atr_value = 0

    intra_trade_high = 0
    intra_trade_low = 0
    long_stop = 0
    short_stop = 0
```

### 类的初始化
初始化分3步：
- 通过super( )的方法继承CTA策略模板，在__init__( )函数传入CTA引擎、策略名称、vt_symbol、参数设置。
- 调用K线生成模块:通过时间切片来把Tick数据合成1分钟K线数据，然后更大的时间周期数据，如15分钟K线。
- 调用K线时间序列管理模块：基于K线数据，如1分钟、15分钟，来生成相应的技术指标。
  
```
    def __init__(self, cta_engine, strategy_name, vt_symbol, setting):
        """"""
        super(BollChannelStrategy, self).__init__(
            cta_engine, strategy_name, vt_symbol, setting
        )

        self.bg = BarGenerator(self.on_bar, 15, self.on_15min_bar)
        self.am = ArrayManager()
```

### 策略的初始化、启动、停止
通过“CTA策略”组件的相关功能按钮实现。

注意：函数load_bar(10)，代表策略初始化需要载入10个交易日的历史数据。该历史数据可以是Tick数据，也可以是K线数据。

```
    def on_init(self):
        """
        Callback when strategy is inited.
        """
        self.write_log("策略初始化")
        self.load_bar(10)

    def on_start(self):
        """
        Callback when strategy is started.
        """
        self.write_log("策略启动")

    def on_stop(self):
        """
        Callback when strategy is stopped.
        """
        self.write_log("策略停止")
```
### Tick数据回报
策略订阅某品种合约行情，交易所会推送Tick数据到该策略上。

由于BollChannelStrategy是基于15分钟K线来生成交易信号的，故收到Tick数据后，需要用到K线生成模块里面的update_tick函数，通过时间切片的方法，聚合成1分钟K线数据，并且推送到on_bar函数。

```
    def on_tick(self, tick: TickData):
        """
        Callback of new tick data update.
        """
        self.bg.update_tick(tick)
```

### K线数据回报

收到推送过来的1分钟K线数据后，通过K线生成模块里面的update_bar函数，以分钟切片的方法，合成15分钟K线数据，并且推送到on_15min_bar函数。
```
    def on_bar(self, bar: BarData):
        """
        Callback of new bar data update.
        """
        self.bg.update_bar(bar)
```

### 15分钟K线数据回报

负责CTA信号的生成，由3部分组成：
- 清空未成交委托：为了防止之前下的单子在上一个15分钟没有成交，但是下一个15分钟可能已经调整了价格，就用cancel_all()方法立刻撤销之前未成交的所有委托，保证策略在当前这15分钟开始时的整个状态是清晰和唯一的。
- 调用K线时间序列管理模块：基于最新的15分钟K线数据来计算相应计算指标，如布林带通道上下轨、CCI指标、ATR指标
- 信号计算：通过持仓的判断以及结合CCI指标、布林带通道、ATR指标在通道突破点挂出停止单委托（buy/sell)，同时设置离场点(short/cover)。

注意：CTA策略具有低胜率和高盈亏比的特定：在难以提升胜率的情况下，研究提高策略盈亏比有利于策略盈利水平的上升。

```
    def on_15min_bar(self, bar: BarData):
        """"""
        self.cancel_all()

        am = self.am
        am.update_bar(bar)
        if not am.inited:
            return

        self.boll_up, self.boll_down = am.boll(self.boll_window, self.boll_dev)
        self.cci_value = am.cci(self.cci_window)
        self.atr_value = am.atr(self.atr_window)

        if self.pos == 0:
            self.intra_trade_high = bar.high_price
            self.intra_trade_low = bar.low_price

            if self.cci_value > 0:
                self.buy(self.boll_up, self.fixed_size, True)
            elif self.cci_value < 0:
                self.short(self.boll_down, self.fixed_size, True)

        elif self.pos > 0:
            self.intra_trade_high = max(self.intra_trade_high, bar.high_price)
            self.intra_trade_low = bar.low_price

            self.long_stop = self.intra_trade_high - self.atr_value * self.sl_multiplier
            self.sell(self.long_stop, abs(self.pos), True)

        elif self.pos < 0:
            self.intra_trade_high = bar.high_price
            self.intra_trade_low = min(self.intra_trade_low, bar.low_price)

            self.short_stop = self.intra_trade_low + self.atr_value * self.sl_multiplier
            self.cover(self.short_stop, abs(self.pos), True)

        self.put_event()
```

### 委托回报、成交回报、停止单回报

在策略中可以直接pass，其具体逻辑应用交给回测/实盘引擎负责。
```
    def on_order(self, order: OrderData):
        """
        Callback of new order data update.
        """
        pass

    def on_trade(self, trade: TradeData):
        """
        Callback of new trade data update.
        """
        self.put_event()

    def on_stop_order(self, stop_order: StopOrder):
        """
        Callback of stop order update.
        """
        pass
```




&nbsp;

## 回测研究
backtesting.py定义了回测引擎，下面主要介绍相关功能函数，以及回测引擎应用示例：

### 加载策略

把CTA策略逻辑，对应合约品种，以及参数设置（可在策略文件外修改）载入到回测引擎中。
```
    def add_strategy(self, strategy_class: type, setting: dict):
        """"""
        self.strategy_class = strategy_class
        self.strategy = strategy_class(
            self, strategy_class.__name__, self.vt_symbol, setting
        )
```
&nbsp;

### 载入历史数据

负责载入对应品种的历史数据，大概有4个步骤：
- 根据数据类型不同，分成K线模式和Tick模式；
- 通过select().where()方法，有条件地从数据库中选取数据，其筛选标准包括：vt_symbol、 回测开始日期、回测结束日期、K线周期（K线模式下）；
- order_by(DbBarData.datetime)表示需要按照时间顺序载入数据；
- 载入数据是以迭代方式进行的，数据最终存入self.history_data。

```
    def load_data(self):
        """"""
        self.output("开始加载历史数据")

        if self.mode == BacktestingMode.BAR:
            s = (
                DbBarData.select()
                .where(
                    (DbBarData.vt_symbol == self.vt_symbol) 
                    & (DbBarData.interval == self.interval) 
                    & (DbBarData.datetime >= self.start) 
                    & (DbBarData.datetime <= self.end)
                )
                .order_by(DbBarData.datetime)
            )
            self.history_data = [db_bar.to_bar() for db_bar in s]
        else:
            s = (
                DbTickData.select()
                .where(
                    (DbTickData.vt_symbol == self.vt_symbol) 
                    & (DbTickData.datetime >= self.start) 
                    & (DbTickData.datetime <= self.end)
                )
                .order_by(DbTickData.datetime)
            )
            self.history_data = [db_tick.to_tick() for db_tick in s]

        self.output(f"历史数据加载完成，数据量：{len(self.history_data)}")
```
&nbsp;

### 撮合成交

载入CTA策略以及相关历史数据后，策略会根据最新的数据来计算相关指标。若符合条件会生成交易信号，发出具体委托（buy/sell/short/cover），并且在下一根K线成交。

根据委托类型的不同，回测引擎提供2种撮合成交机制来尽量模仿真实交易环节：

- 限价单撮合成交：（以买入方向为例）先确定是否发生成交，成交标准为委托价>= 下一根K线的最低价；然后确定成交价格，成交价格为委托价与下一根K线开盘价的最小值。

- 停止单撮合成交：（以买入方向为例）先确定是否发生成交，成交标准为委托价<= 下一根K线的最高价；然后确定成交价格，成交价格为委托价与下一根K线开盘价的最大值。

&nbsp;

下面展示在引擎中限价单撮合成交的流程：
- 确定会撮合成交的价格；
- 遍历限价单字典中的所有限价单，推送委托进入未成交队列的更新状态；
- 判断成交状态，若出现成交，推送成交数据和委托数据；
- 从字典中删除已成交的限价单。

```
    def cross_limit_order(self):
        """
        Cross limit order with last bar/tick data.
        """
        if self.mode == BacktestingMode.BAR:
            long_cross_price = self.bar.low_price
            short_cross_price = self.bar.high_price
            long_best_price = self.bar.open_price
            short_best_price = self.bar.open_price
        else:
            long_cross_price = self.tick.ask_price_1
            short_cross_price = self.tick.bid_price_1
            long_best_price = long_cross_price
            short_best_price = short_cross_price

        for order in list(self.active_limit_orders.values()):
            # Push order update with status "not traded" (pending)
            if order.status == Status.SUBMITTING:
                order.status = Status.NOTTRADED
                self.strategy.on_order(order)

            # Check whether limit orders can be filled.
            long_cross = (
                order.direction == Direction.LONG 
                and order.price >= long_cross_price 
                and long_cross_price > 0
            )

            short_cross = (
                order.direction == Direction.SHORT 
                and order.price <= short_cross_price 
                and short_cross_price > 0
            )

            if not long_cross and not short_cross:
                continue

            # Push order udpate with status "all traded" (filled).
            order.traded = order.volume
            order.status = Status.ALLTRADED
            self.strategy.on_order(order)

            self.active_limit_orders.pop(order.vt_orderid)

            # Push trade update
            self.trade_count += 1

            if long_cross:
                trade_price = min(order.price, long_best_price)
                pos_change = order.volume
            else:
                trade_price = max(order.price, short_best_price)
                pos_change = -order.volume

            trade = TradeData(
                symbol=order.symbol,
                exchange=order.exchange,
                orderid=order.orderid,
                tradeid=str(self.trade_count),
                direction=order.direction,
                offset=order.offset,
                price=trade_price,
                volume=order.volume,
                time=self.datetime.strftime("%H:%M:%S"),
                gateway_name=self.gateway_name,
            )
            trade.datetime = self.datetime

            self.strategy.pos += pos_change
            self.strategy.on_trade(trade)

            self.trades[trade.vt_tradeid] = trade
```

&nbsp;

### 计算策略盈亏情况

基于收盘价、当日持仓量、合约规模、滑点、手续费率等计算总盈亏与净盈亏，并且其计算结果以DataFrame格式输出，完成基于逐日盯市盈亏统计。

下面展示盈亏情况的计算过程

- 浮动盈亏 = 持仓量 \*（当日收盘价 - 昨日收盘价）\*  合约规模
- 实际盈亏 = 持仓变化量  \* （当时收盘价 - 开仓成交价）\* 合约规模
- 总盈亏 = 浮动盈亏 + 实际盈亏
- 净盈亏 = 总盈亏 - 总手续费 - 总滑点

```
    def calculate_pnl(
        self,
        pre_close: float,
        start_pos: float,
        size: int,
        rate: float,
        slippage: float,
    ):
        """"""
        self.pre_close = pre_close

        # Holding pnl is the pnl from holding position at day start
        self.start_pos = start_pos
        self.end_pos = start_pos
        self.holding_pnl = self.start_pos * \
            (self.close_price - self.pre_close) * size

        # Trading pnl is the pnl from new trade during the day
        self.trade_count = len(self.trades)

        for trade in self.trades:
            if trade.direction == Direction.LONG:
                pos_change = trade.volume
            else:
                pos_change = -trade.volume

            turnover = trade.price * trade.volume * size

            self.trading_pnl += pos_change * \
                (self.close_price - trade.price) * size
            self.end_pos += pos_change
            self.turnover += turnover
            self.commission += turnover * rate
            self.slippage += trade.volume * size * slippage

        # Net pnl takes account of commission and slippage cost
        self.total_pnl = self.trading_pnl + self.holding_pnl
        self.net_pnl = self.total_pnl - self.commission - self.slippage
```
&nbsp;



### 计算策略统计指标
calculate_statistics函数是基于逐日盯市盈亏情况（DateFrame格式）来计算衍生指标，如最大回撤、年化收益、盈亏比、夏普比率等。

```
            df["balance"] = df["net_pnl"].cumsum() + self.capital
            df["return"] = np.log(df["balance"] / df["balance"].shift(1)).fillna(0)
            df["highlevel"] = (
                df["balance"].rolling(
                    min_periods=1, window=len(df), center=False).max()
            )
            df["drawdown"] = df["balance"] - df["highlevel"]
            df["ddpercent"] = df["drawdown"] / df["highlevel"] * 100

            # Calculate statistics value
            start_date = df.index[0]
            end_date = df.index[-1]

            total_days = len(df)
            profit_days = len(df[df["net_pnl"] > 0])
            loss_days = len(df[df["net_pnl"] < 0])

            end_balance = df["balance"].iloc[-1]
            max_drawdown = df["drawdown"].min()
            max_ddpercent = df["ddpercent"].min()

            total_net_pnl = df["net_pnl"].sum()
            daily_net_pnl = total_net_pnl / total_days

            total_commission = df["commission"].sum()
            daily_commission = total_commission / total_days

            total_slippage = df["slippage"].sum()
            daily_slippage = total_slippage / total_days

            total_turnover = df["turnover"].sum()
            daily_turnover = total_turnover / total_days

            total_trade_count = df["trade_count"].sum()
            daily_trade_count = total_trade_count / total_days

            total_return = (end_balance / self.capital - 1) * 100
            annual_return = total_return / total_days * 240
            daily_return = df["return"].mean() * 100
            return_std = df["return"].std() * 100

            if return_std:
                sharpe_ratio = daily_return / return_std * np.sqrt(240)
            else:
                sharpe_ratio = 0
```
&nbsp;

### 统计指标绘图
通过matplotlib绘制4幅图：
- 资金曲线图
- 资金回撤图
- 每日盈亏图
- 每日盈亏分布图

```
    def show_chart(self, df: DataFrame = None):
        """"""
        if not df:
            df = self.daily_df
        
        if df is None:
            return

        plt.figure(figsize=(10, 16))

        balance_plot = plt.subplot(4, 1, 1)
        balance_plot.set_title("Balance")
        df["balance"].plot(legend=True)

        drawdown_plot = plt.subplot(4, 1, 2)
        drawdown_plot.set_title("Drawdown")
        drawdown_plot.fill_between(range(len(df)), df["drawdown"].values)

        pnl_plot = plt.subplot(4, 1, 3)
        pnl_plot.set_title("Daily Pnl")
        df["net_pnl"].plot(kind="bar", legend=False, grid=False, xticks=[])

        distribution_plot = plt.subplot(4, 1, 4)
        distribution_plot.set_title("Daily Pnl Distribution")
        df["net_pnl"].hist(bins=50)

        plt.show()
```

&nbsp;

### 回测引擎使用示例

- 导入回测引擎和CTA策略
- 设置回测相关参数，如：品种、K线周期、回测开始和结束日期、手续费、滑点、合约规模、起始资金
- 载入策略和数据到引擎中，运行回测。
- 计算基于逐日统计盈利情况，计算统计指标，统计指标绘图。


```
from vnpy.app.cta_strategy.backtesting import BacktestingEngine
from vnpy.app.cta_strategy.strategies.boll_channel_strategy import (
    BollChannelStrategy,
)
from datetime import datetime

engine = BacktestingEngine()
engine.set_parameters(
    vt_symbol="IF88.CFFEX",
    interval="1m",
    start=datetime(2018, 1, 1),
    end=datetime(2019, 1, 1),
    rate=3.0/10000,
    slippage=0.2,
    size=300,
    pricetick=0.2,
    capital=1_000_000,
)

engine.add_strategy(AtrRsiStrategy, {})
engine.load_data()
engine.run_backtesting()
df = engine.calculate_result()
engine.calculate_statistics()
engine.show_chart()
```

&nbsp;

## 参数优化
参数优化模块主要由3部分构成：

### 参数设置

- 设置参数优化区间：如boll_window设置起始值为18，终止值为24，步进为2，这样就得到了[18, 20, 22, 24] 这4个待优化的参数了。
- 设置优化目标字段：如夏普比率、盈亏比、总收益率等。
- 随机生成参数对组合：使用迭代工具产生参数对组合，然后把参数对组合打包到一个个字典组成的列表中

```
class OptimizationSetting:
    """
    Setting for runnning optimization.
    """

    def __init__(self):
        """"""
        self.params = {}
        self.target_name = ""

    def add_parameter(
        self, name: str, start: float, end: float = None, step: float = None
    ):
        """"""
        if not end and not step:
            self.params[name] = [start]
            return

        if start >= end:
            print("参数优化起始点必须小于终止点")
            return

        if step <= 0:
            print("参数优化步进必须大于0")
            return

        value = start
        value_list = []

        while value <= end:
            value_list.append(value)
            value += step

        self.params[name] = value_list

    def set_target(self, target_name: str):
        """"""
        self.target_name = target_name

    def generate_setting(self):
        """"""
        keys = self.params.keys()
        values = self.params.values()
        products = list(product(*values))

        settings = []
        for p in products:
            setting = dict(zip(keys, p))
            settings.append(setting)

        return settings
```

&nbsp;

### 参数对组合回测

多进程优化时，每个进程都会运行optimize函数，输出参数对组合以及目标优化字段的结果。其步骤如下：
- 调用回测引擎
- 输入回测相关设置
- 输入参数对组合到策略中
- 运行回测
- 返回回测结果，包括：参数对组合、目标优化字段数值、策略统计指标

```
def optimize(
    target_name: str,
    strategy_class: CtaTemplate,
    setting: dict,
    vt_symbol: str,
    interval: Interval,
    start: datetime,
    rate: float,
    slippage: float,
    size: float,
    pricetick: float,
    capital: int,
    end: datetime,
    mode: BacktestingMode,
):
    """
    Function for running in multiprocessing.pool
    """
    engine = BacktestingEngine()
    engine.set_parameters(
        vt_symbol=vt_symbol,
        interval=interval,
        start=start,
        rate=rate,
        slippage=slippage,
        size=size,
        pricetick=pricetick,
        capital=capital,
        end=end,
        mode=mode
    )

    engine.add_strategy(strategy_class, setting)
    engine.load_data()
    engine.run_backtesting()
    engine.calculate_result()
    statistics = engine.calculate_statistics()

    target_value = statistics[target_name]
    return (str(setting), target_value, statistics)
```

&nbsp;

### 多进程优化

- 根据CPU的核数来创建进程：若CPU为4核，则创建4个进程
- 在每个进程都调用apply_async( )的方法运行参数对组合回测，其回测结果添加到results中 （apply_async是异步非阻塞的，即不用等待当前进程执行完毕，随时根据系统调度来进行进程切换。）
- pool.close()与pool.join()用于进程跑完任务后，去关闭进程。
- 对results的内容通过目标优化字段标准进行排序，输出结果。

```
        pool = multiprocessing.Pool(multiprocessing.cpu_count())

        results = []
        for setting in settings:
            result = (pool.apply_async(optimize, (
                target_name,
                self.strategy_class,
                setting,
                self.vt_symbol,
                self.interval,
                self.start,
                self.rate,
                self.slippage,
                self.size,
                self.pricetick,
                self.capital,
                self.end,
                self.mode
            )))
            results.append(result)

        pool.close()
        pool.join()

        # Sort results and output
        result_values = [result.get() for result in results]
        result_values.sort(reverse=True, key=lambda result: result[1])

        for value in result_values:
            msg = f"参数：{value[0]}, 目标：{value[1]}"
            self.output(msg)

        return result_values
```

&nbsp;

## 实盘运行
在实盘环境，用户可以基于编写好的CTA策略来创建新的实例，一键初始化、启动、停止策略。


### 创建策略实例
用户可以基于编写好的CTA策略来创建新的实例，策略实例的好处在于同一个策略可以同时去运行多个品种合约，并且每个实例的参数可以是不同的。
在创建实例的时候需要填写如图的实例名称、合约品种、参数设置。注意：实例名称不能重名；合约名称是vt_symbol的格式，如IF1905.CFFEX。

![](https://vnpy-community.oss-cn-shanghai.aliyuncs.com/forum_experience/yazhang/cta_strategy/add_strategy.png)

创建策略流程如下：
- 检查策略实例重名
- 添加策略配置信息(strategy_name, vt_symbol, setting)到strategies字典上
- 添加该策略要订阅行情的合约信息到symbol_strategy_map字典中；
- 把策略配置信息保存到json文件内；
- 在图形化界面更新状态信息。

```
    def add_strategy(
        self, class_name: str, strategy_name: str, vt_symbol: str, setting: dict
    ):
        """
        Add a new strategy.
        """
        if strategy_name in self.strategies:
            self.write_log(f"创建策略失败，存在重名{strategy_name}")
            return

        strategy_class = self.classes[class_name]

        strategy = strategy_class(self, strategy_name, vt_symbol, setting)
        self.strategies[strategy_name] = strategy

        # Add vt_symbol to strategy map.
        strategies = self.symbol_strategy_map[vt_symbol]
        strategies.append(strategy)

        # Update to setting file.
        self.update_strategy_setting(strategy_name, setting)

        self.put_strategy_event(strategy)
```

&nbsp;

### 初始化策略
- 调用策略类的on_init()回调函数,并且载入历史数据；
- 恢复上次退出之前的策略状态；
- 调用接口的subcribe()函数订阅指定行情信息；
- 策略初始化状态变成True，并且更新到日志上。
  
```
    def _init_strategy(self):
        """
        Init strategies in queue.
        """
        while not self.init_queue.empty():
            strategy_name = self.init_queue.get()
            strategy = self.strategies[strategy_name]

            if strategy.inited:
                self.write_log(f"{strategy_name}已经完成初始化，禁止重复操作")
                continue

            self.write_log(f"{strategy_name}开始执行初始化")

            # Call on_init function of strategy
            self.call_strategy_func(strategy, strategy.on_init)

            # Restore strategy data(variables)
            data = self.strategy_data.get(strategy_name, None)
            if data:
                for name in strategy.variables:
                    value = data.get(name, None)
                    if value:
                        setattr(strategy, name, value)

            # Subscribe market data
            contract = self.main_engine.get_contract(strategy.vt_symbol)
            if contract:
                req = SubscribeRequest(
                    symbol=contract.symbol, exchange=contract.exchange)
                self.main_engine.subscribe(req, contract.gateway_name)
            else:
                self.write_log(f"行情订阅失败，找不到合约{strategy.vt_symbol}", strategy)

            # Put event to update init completed status.
            strategy.inited = True
            self.put_strategy_event(strategy)
            self.write_log(f"{strategy_name}初始化完成")
        
        self.init_thread = None
```

&nbsp;

### 启动策略
- 检查策略初始化状态；
- 检查策略启动状态，避免重复启动；
- 调用策略类的on_start()函数启动策略；
- 策略启动状态变成True，并且更新到图形化界面上。

```
    def start_strategy(self, strategy_name: str):
        """
        Start a strategy.
        """
        strategy = self.strategies[strategy_name]
        if not strategy.inited:
            self.write_log(f"策略{strategy.strategy_name}启动失败，请先初始化")
            return

        if strategy.trading:
            self.write_log(f"{strategy_name}已经启动，请勿重复操作")
            return

        self.call_strategy_func(strategy, strategy.on_start)
        strategy.trading = True

        self.put_strategy_event(strategy)
```

&nbsp;

### 停止策略
- 检查策略启动状态；
- 调用策略类的on_stop()函数停止策略；
- 更新策略启动状态为False；
- 对所有为成交的委托（市价单/限价单/本地停止单）进行撤单操作；
- 在图形化界面更新策略状态。

```
    def stop_strategy(self, strategy_name: str):
        """
        Stop a strategy.
        """
        strategy = self.strategies[strategy_name]
        if not strategy.trading:
            return

        # Call on_stop function of the strategy
        self.call_strategy_func(strategy, strategy.on_stop)

        # Change trading status of strategy to False
        strategy.trading = False

        # Cancel all orders of the strategy
        self.cancel_all(strategy)

        # Update GUI
        self.put_strategy_event(strategy)
```

&nbsp;

### 编辑策略
- 重新配置策略参数字典setting；
- 更新参数字典到策略中；
- 在图像化界面更新策略状态。

```
    def edit_strategy(self, strategy_name: str, setting: dict):
        """
        Edit parameters of a strategy.
        """
        strategy = self.strategies[strategy_name]
        strategy.update_setting(setting)

        self.update_strategy_setting(strategy_name, setting)
        self.put_strategy_event(strategy)
```

&nbsp;

### 移除策略
- 检查策略状态，只有停止策略后从可以移除策略；
- 从json文件移除策略配置信息(strategy_name, vt_symbol, setting)；
- 从symbol_strategy_map字典中移除该策略订阅的合约信息；
- 从strategy_orderid_map字典移除活动委托记录；
- 从strategies字典移除该策略的相关配置信息。

```
    def remove_strategy(self, strategy_name: str):
        """
        Remove a strategy.
        """
        strategy = self.strategies[strategy_name]
        if strategy.trading:
            self.write_log(f"策略{strategy.strategy_name}移除失败，请先停止")
            return

        # Remove setting
        self.remove_strategy_setting(strategy_name)

        # Remove from symbol strategy map
        strategies = self.symbol_strategy_map[strategy.vt_symbol]
        strategies.remove(strategy)

        # Remove from active orderid map
        if strategy_name in self.strategy_orderid_map:
            vt_orderids = self.strategy_orderid_map.pop(strategy_name)

            # Remove vt_orderid strategy map
            for vt_orderid in vt_orderids:
                if vt_orderid in self.orderid_strategy_map:
                    self.orderid_strategy_map.pop(vt_orderid)

        # Remove from strategies
        self.strategies.pop(strategy_name)

        return True
```
