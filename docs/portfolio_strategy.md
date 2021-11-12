# 多合约组合策略模块

## 策略开发
多合约组合策略模板提供完整的信号生成和委托管理功能，用户可以基于该模板自行开发策略。新策略可以放在用户运行的文件内（推荐），如在c:\users\administrator.vntrader目录下创建strategies文件夹；可以放在根目录下vnpy\app\portfolio_strategy\strategies文件夹内。
注意：策略文件命名是以下划线模式，如pair_trading_strategy.py；而策略类命名采用的是驼峰式，如PairTradingStrategy。

下面通过PairTradingStrategy策略示例，来展示策略开发的具体步骤：

### 参数设置

定义策略参数并且初始化策略变量。策略参数为策略类的公有属性，用户可以通过创建新的实例来调用或者改变策略参数。

如针对rb和hc品种，用户可以创建基于PairTradingStrategy的策略示例，如rb_hc_PairTradingStrategy，boll_window可以由20改成30。

创建策略实例的方法有效地实现了一个策略跑多个品种，并且其策略参数可以通过品种的特征进行调整。
```
    price_add = 5
    boll_window = 20
    boll_dev = 2
    fixed_size = 1
    leg1_ratio = 1
    leg2_ratio = 1

    leg1_symbol = ""
    leg2_symbol = ""
    current_spread = 0.0
    boll_mid = 0.0
    boll_down = 0.0
    boll_up = 0.0
```

### 类的初始化
初始化：

- 通过super( )的方法继承StrategyTemplate，在__init__( )函数传入Strategy引擎、策略名称、vt_symbols、参数设置。
- 调用K线生成模块:通过时间切片来把Tick数据合成1分钟K线数据。
- 如果需要，可以调用K线时间序列管理模块：基于K线数据，来生成相应的技术指标。
  
```
    def __init__(
        self,
        strategy_engine: StrategyEngine,
        strategy_name: str,
        vt_symbols: List[str],
        setting: dict
    ):
        """"""
        super().__init__(strategy_engine, strategy_name, vt_symbols, setting)

        self.bgs: Dict[str, BarGenerator] = {}
        self.targets: Dict[str, int] = {}
        self.last_tick_time: datetime = None

        self.spread_count: int = 0
        self.spread_data: np.array = np.zeros(100)

        # Obtain contract info
        self.leg1_symbol, self.leg2_symbol = vt_symbols

        def on_bar(bar: BarData):
            """"""
            pass

        for vt_symbol in self.vt_symbols:
            self.targets[vt_symbol] = 0
            self.bgs[vt_symbol] = BarGenerator(on_bar)
```

### 策略的初始化、启动、停止
通过“多合约组合策略”组件的相关功能按钮实现。

注意：函数load_bar(1)，代表策略初始化需要载入1个交易日的历史数据。该历史数据只能是K线数据（on_tick只有实盘中会调用，回测不支持）。在策略初始化时候，会调用K线时间序列管理器计算并缓存相关的计算指标，但是并不触发交易。

```
    def on_init(self):
        """
        Callback when strategy is inited.
        """
        self.write_log("策略初始化")

        self.load_bars(1)

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

由于是基于1分钟K线来生成交易信号的，故收到Tick数据后，需要用到K线生成模块里面的update_tick函数，通过时间切片的方法，聚合成1分钟K线数据，并且推送到on_bars函数。

```
    def on_tick(self, tick: TickData):
        """
        Callback of new tick data update.
        """
        if (
            self.last_tick_time
            and self.last_tick_time.minute != tick.datetime.minute
        ):
            bars = {}
            for vt_symbol, bg in self.bgs.items():
                bars[vt_symbol] = bg.generate()
            self.on_bars(bars)

        bg: BarGenerator = self.bgs[tick.vt_symbol]
        bg.update_tick(tick)

        self.last_tick_time = tick.datetime
```

### K线数据回报

在回调函数on_bars中，同时收到所有合约的K线行情推送，并实现核心交易逻辑。调用buy/sell/short/cover/cancel_order等函数来发送交易请求。

信号的生成，由3部分组成：

- 清空未成交委托：为了防止之前下的单子在上一个5分钟没有成交，但是下一个5分钟可能已经调整了价格，就用cancel_all()方法立刻撤销之前未成交的所有委托，保证策略在当前这5分钟开始时的整个状态是清晰和唯一的。
- 时间过滤：这里有用(bar.datetime.minute+1) % 5的逻辑来达到每5分钟推送一次的逻辑。
- 指标计算：基于最新的5分钟K线数据来计算相应计算指标，如价差的布林带通道上下轨。
- 信号计算：通过持仓的判断以及结合布林带通道上下轨，在通道突破点以及离场点设置目标仓位。
- 仓位管理：基于目标仓位和现在持仓的差别来计算本次下单的数量并挂出委托（buy/sell)，同时设置离场点(short/cover)。

```
    def on_bars(self, bars: Dict[str, BarData]):
        """"""
        self.cancel_all()

        # Return if one leg data is missing
        if self.leg1_symbol not in bars or self.leg2_symbol not in bars:
            return

        # Calculate current spread
        leg1_bar = bars[self.leg1_symbol]
        leg2_bar = bars[self.leg2_symbol]

        # Filter time only run every 5 minutes
        if (leg1_bar.datetime.minute + 1) % 5:
            return

        self.current_spread = (
            leg1_bar.close_price * self.leg1_ratio - leg2_bar.close_price * self.leg2_ratio
        )

        # Update to spread array
        self.spread_data[:-1] = self.spread_data[1:]
        self.spread_data[-1] = self.current_spread

        self.spread_count += 1
        if self.spread_count <= self.boll_window:
            return

        # Calculate boll value
        buf: np.array = self.spread_data[-self.boll_window:]

        std = buf.std()
        self.boll_mid = buf.mean()
        self.boll_up = self.boll_mid + self.boll_dev * std
        self.boll_down = self.boll_mid - self.boll_dev * std

        # Calculate new target position
        leg1_pos = self.get_pos(self.leg1_symbol)

        if not leg1_pos:
            if self.current_spread >= self.boll_up:
                self.targets[self.leg1_symbol] = -1
                self.targets[self.leg2_symbol] = 1
            elif self.current_spread <= self.boll_down:
                self.targets[self.leg1_symbol] = 1
                self.targets[self.leg2_symbol] = -1
        elif leg1_pos > 0:
            if self.current_spread >= self.boll_mid:
                self.targets[self.leg1_symbol] = 0
                self.targets[self.leg2_symbol] = 0
        else:
            if self.current_spread <= self.boll_mid:
                self.targets[self.leg1_symbol] = 0
                self.targets[self.leg2_symbol] = 0

        # Execute orders
        for vt_symbol in self.vt_symbols:
            target_pos = self.targets[vt_symbol]
            current_pos = self.get_pos(vt_symbol)

            pos_diff = target_pos - current_pos
            volume = abs(pos_diff)
            bar = bars[vt_symbol]

            if pos_diff > 0:
                price = bar.close_price + self.price_add

                if current_pos < 0:
                    self.cover(vt_symbol, price, volume)
                else:
                    self.buy(vt_symbol, price, volume)
            elif pos_diff < 0:
                price = bar.close_price - self.price_add

                if current_pos > 0:
                    self.sell(vt_symbol, price, volume)
                else:
                    self.short(vt_symbol, price, volume)

        self.put_event()

```

 

### 委托回报、成交回报、停止单回报

在于组合策略中需要对多合约同时下单交易，在回测时**无法判断某一段K线内部每个合约委托成交的先后时间顺序**，因此无法提供on_order和on_trade获取委托成交推送，而只能在每次on_bars回调时通过get_pos和get_order来进行相关的状态查询。

同时组合策略模块只支持限价单交易，不提供停止单功能（StopOrder）。

```
    def send_order(
        self,
        vt_symbol: str,
        direction: Direction,
        offset: Offset,
        price: float,
        volume: float,
        lock: bool = False
    ) -> List[str]:
        """
        Send a new order.
        """
        if self.trading:
            vt_orderids = self.strategy_engine.send_order(
                self, vt_symbol, direction, offset, price, volume, lock
            )
            return vt_orderids
        else:
            return []
```


&nbsp;

## 回测研究
backtesting.py定义了回测引擎，下面主要介绍相关功能函数，以及回测引擎应用示例：

### 加载策略

把组合策略逻辑，对应所有合约品种，以及参数设置（可在策略文件外修改）载入到回测引擎中。

```
    def add_strategy(self, strategy_class: type, setting: dict) -> None:
        """"""
        self.strategy = strategy_class(
            self, strategy_class.__name__, copy(self.vt_symbols), setting
        )
```
&nbsp;

### 载入历史数据

负责载入对应品种的历史数据，大概有4个步骤：

- 检查起始日期是否小于结束日期；
- 清除之前载入的历史数据；
- 有条件地从数据库中选取数据，每次载入30天数据。其筛选标准包括：vt_symbol、 回测开始日期、回测结束日期、K线周期；
- 载入数据是以迭代方式进行的，数据最终存入self.history_data。

```
    def load_data(self) -> None:
        """"""
        self.output("开始加载历史数据")

        if not self.end:
            self.end = datetime.now()

        if self.start >= self.end:
            self.output("起始日期必须小于结束日期")
            return

        # Clear previously loaded history data
        self.history_data.clear()
        self.dts.clear()

        # Load 30 days of data each time and allow for progress update
        progress_delta = timedelta(days=30)
        total_delta = self.end - self.start
        interval_delta = INTERVAL_DELTA_MAP[self.interval]

        for vt_symbol in self.vt_symbols:
            start = self.start
            end = self.start + progress_delta
            progress = 0

            data_count = 0
            while start < self.end:
                end = min(end, self.end)  # Make sure end time stays within set range

                data = load_bar_data(
                    vt_symbol,
                    self.interval,
                    start,
                    end
                )

                for bar in data:
                    self.dts.add(bar.datetime)
                    self.history_data[(bar.datetime, vt_symbol)] = bar
                    data_count += 1

                progress += progress_delta / total_delta
                progress = min(progress, 1)
                progress_bar = "#" * int(progress * 10)
                self.output(f"{vt_symbol}加载进度：{progress_bar} [{progress:.0%}]")

                start = end + interval_delta
                end += (progress_delta + interval_delta)

            self.output(f"{vt_symbol}历史数据加载完成，数据量：{data_count}")

        self.output("所有历史数据加载完成")
```
&nbsp;

### 撮合成交

载入组合策略以及相关历史数据后，策略会根据最新的数据来计算相关指标。若符合条件会生成交易信号，发出具体委托（buy/sell/short/cover），并且在下一根K线成交。

回测引擎提供限价单撮合成交机制来尽量模仿真实交易环节：

- 限价单撮合成交：（以买入方向为例）先确定是否发生成交，成交标准为委托价>= 下一根K线的最低价；然后确定成交价格，成交价格为委托价与下一根K线开盘价的最小值。


&nbsp;

下面展示在引擎中限价单撮合成交的流程：
- 确定会撮合成交的价格；
- 遍历限价单字典中的所有限价单，推送委托进入未成交队列的更新状态；
- 判断成交状态，若出现成交，推送成交数据和委托数据；
- 从字典中删除已成交的限价单。

```
    def cross_limit_order(self) -> None:
        """
        Cross limit order with last bar/tick data.
        """
        for order in list(self.active_limit_orders.values()):
            bar = self.bars[order.vt_symbol]

            long_cross_price = bar.low_price
            short_cross_price = bar.high_price
            long_best_price = bar.open_price
            short_best_price = bar.open_price

            # Push order update with status "not traded" (pending).
            if order.status == Status.SUBMITTING:
                order.status = Status.NOTTRADED
                self.strategy.update_order(order)

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

            # Push order update with status "all traded" (filled).
            order.traded = order.volume
            order.status = Status.ALLTRADED
            self.strategy.update_order(order)

            self.active_limit_orders.pop(order.vt_orderid)

            # Push trade update
            self.trade_count += 1

            if long_cross:
                trade_price = min(order.price, long_best_price)
            else:
                trade_price = max(order.price, short_best_price)

            trade = TradeData(
                symbol=order.symbol,
                exchange=order.exchange,
                orderid=order.orderid,
                tradeid=str(self.trade_count),
                direction=order.direction,
                offset=order.offset,
                price=trade_price,
                volume=order.volume,
                datetime=self.datetime,
                gateway_name=self.gateway_name,
            )

            self.strategy.update_trade(trade)
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
        slippage: float
    ) -> None:
        """"""
        # If no pre_close provided on the first day,
        # use value 1 to avoid zero division error
        if pre_close:
            self.pre_close = pre_close
        else:
            self.pre_close = 1

        # Holding pnl is the pnl from holding position at day start
        self.start_pos = start_pos
        self.end_pos = start_pos

        self.holding_pnl = self.start_pos * (self.close_price - self.pre_close) * size

        # Trading pnl is the pnl from new trade during the day
        self.trade_count = len(self.trades)

        for trade in self.trades:
            if trade.direction == Direction.LONG:
                pos_change = trade.volume
            else:
                pos_change = -trade.volume

            self.end_pos += pos_change

            turnover = trade.volume * size * trade.price

            self.trading_pnl += pos_change * (self.close_price - trade.price) * size
            self.slippage += trade.volume * size * slippage
            self.turnover += turnover
            self.commission += turnover * rate

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
            max_drawdown_end = df["drawdown"].idxmin()

            if isinstance(max_drawdown_end, date):
                max_drawdown_start = df["balance"][:max_drawdown_end].idxmax()
                max_drawdown_duration = (max_drawdown_end - max_drawdown_start).days
            else:
                max_drawdown_duration = 0

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

            pnl_std = df["net_pnl"].std()

            if return_std:
                # sharpe_ratio = daily_return / return_std * np.sqrt(240)
                sharpe_ratio = daily_net_pnl / pnl_std * np.sqrt(240)
            else:
                sharpe_ratio = 0

            return_drawdown_ratio = -total_net_pnl / max_drawdown
```
&nbsp;

### 统计指标绘图
通过matplotlib绘制4幅图：
- 资金曲线图
- 资金回撤图
- 每日盈亏图
- 每日盈亏分布图

```
    def show_chart(self, df: DataFrame = None) -> None:
        """"""
        # Check DataFrame input exterior
        if df is None:
            df = self.daily_df

        # Check for init DataFrame
        if df is None:
            return

        fig = make_subplots(
            rows=4,
            cols=1,
            subplot_titles=["Balance", "Drawdown", "Daily Pnl", "Pnl Distribution"],
            vertical_spacing=0.06
        )

        balance_line = go.Scatter(
            x=df.index,
            y=df["balance"],
            mode="lines",
            name="Balance"
        )
        drawdown_scatter = go.Scatter(
            x=df.index,
            y=df["drawdown"],
            fillcolor="red",
            fill='tozeroy',
            mode="lines",
            name="Drawdown"
        )
        pnl_bar = go.Bar(y=df["net_pnl"], name="Daily Pnl")
        pnl_histogram = go.Histogram(x=df["net_pnl"], nbinsx=100, name="Days")

        fig.add_trace(balance_line, row=1, col=1)
        fig.add_trace(drawdown_scatter, row=2, col=1)
        fig.add_trace(pnl_bar, row=3, col=1)
        fig.add_trace(pnl_histogram, row=4, col=1)

        fig.update_layout(height=1000, width=1000)
        fig.show()    def show_chart(self, df: DataFrame = None):
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

效果如下：

![回测结果](https://user-images.githubusercontent.com/11263900/93662305-b8737e00-fa91-11ea-8c83-70ca30e58dc4.png)

![回测图](https://user-images.githubusercontent.com/11263900/93662331-ec4ea380-fa91-11ea-9e93-d61f90d0d282.png)

&nbsp;

### 策略回测示例

- 导入回测引擎和组合策略
- 设置回测相关参数，如：品种、K线周期、回测开始和结束日期、手续费、滑点、合约规模、起始资金
- 载入策略和数据到引擎中，运行回测。
- 计算基于逐日统计盈利情况，计算统计指标，统计指标绘图。


```
from datetime import datetime
from importlib import reload

import vnpy.app.portfolio_strategy
reload(vnpy.app.portfolio_strategy)

from vnpy.app.portfolio_strategy import BacktestingEngine
from vnpy.trader.constant import Interval

import vnpy.app.portfolio_strategy.strategies.pair_trading_strategy as stg
reload(stg)
from vnpy.app.portfolio_strategy.strategies.pair_trading_strategy import PairTradingStrategy

engine = BacktestingEngine()
engine.set_parameters(
    vt_symbols=["y888.DCE", "p888.DCE"],
    interval=Interval.MINUTE,
    start=datetime(2019, 1, 1),
    end=datetime(2020, 4, 30),
    rates={
        "y888.DCE": 0/10000,
        "p888.DCE": 0/10000
    },
    slippages={
        "y888.DCE": 0,
        "p888.DCE": 0
    },
    sizes={
        "y888.DCE": 10,
        "p888.DCE": 10
    },
    priceticks={
        "y888.DCE": 1,
        "p888.DCE": 1
    },
    capital=1_000_000,
)

setting = {
    "boll_window": 20,
    "boll_dev": 1,
}
engine.add_strategy(PairTradingStrategy, setting)

engine.load_data()
engine.run_backtesting()
df = engine.calculate_result()
engine.calculate_statistics()
engine.show_chart()
```

&nbsp;

## 实盘运行
在实盘环境，用户可以基于编写好的组合策略来创建新的实例，一键初始化、启动、停止策略（不要忘记先连接对应接口，获取行情）。


### 创建策略实例
用户可以基于编写好的组合策略来创建新的实例，策略实例的好处在于同一个策略可以同时去运行多个品种合约，并且每个实例的参数可以是不同的。
在创建实例的时候需要填写如图的实例名称、合约品种、参数设置。注意：实例名称不能重名；合约名称是vt_symbol的格式，如y2101.DCE,p2101.DCE。

![创建](https://user-images.githubusercontent.com/11263900/93662304-b6a9ba80-fa91-11ea-895a-ae56fc7ddf60.png)

创建策略流程如下：
- 检查策略实例重名
- 检查是否存在策略类
- 添加策略配置信息(strategy_name, vt_symbols, setting)到strategies字典上
- 添加该策略要订阅行情的所有合约信息到symbol_strategy_map字典中；
- 把策略配置信息保存到json文件内；
- 在图形化界面更新状态信息。

```
    def add_strategy(
        self, class_name: str, strategy_name: str, vt_symbols: str, setting: dict
    ):
        """
        Add a new strategy.
        """
        if strategy_name in self.strategies:
            self.write_log(f"创建策略失败，存在重名{strategy_name}")
            return

        strategy_class = self.classes.get(class_name, None)
        if not strategy_class:
            self.write_log(f"创建策略失败，找不到策略类{class_name}")
            return

        strategy = strategy_class(self, strategy_name, vt_symbols, setting)
        self.strategies[strategy_name] = strategy

        # Add vt_symbol to strategy map.
        for vt_symbol in vt_symbols:
            strategies = self.symbol_strategy_map[vt_symbol]
            strategies.append(strategy)

        self.save_strategy_setting()
        self.put_strategy_event(strategy)
```

![初始化](https://user-images.githubusercontent.com/11263900/93662303-b27d9d00-fa91-11ea-824f-58645bd4e202.png)

&nbsp;

### 初始化策略
- 调用策略类的on_init()回调函数,并且载入历史数据；
- 恢复上次退出之前的策略状态；
- 从.vntrader/portfolio_strategy_data.json内读取策略参数，最新的技术指标，以及持仓数量；
- 调用接口的subcribe()函数订阅指定行情信息；
- 策略初始化状态变成True，并且更新到日志上。
  
```
    def _init_strategy(self, strategy_name: str):
        """
        Init strategies in queue.
        """
        strategy = self.strategies[strategy_name]

        if strategy.inited:
            self.write_log(f"{strategy_name}已经完成初始化，禁止重复操作")
            return

        self.write_log(f"{strategy_name}开始执行初始化")

        # Call on_init function of strategy
        self.call_strategy_func(strategy, strategy.on_init)

        # Restore strategy data(variables)
        data = self.strategy_data.get(strategy_name, None)
        if data:
            for name in strategy.variables:
                value = data.get(name, None)
                if name == "pos":
                    pos = getattr(strategy, name)
                    pos.update(value)
                elif value:
                    setattr(strategy, name, value)

        # Subscribe market data
        for vt_symbol in strategy.vt_symbols:
            contract: ContractData = self.main_engine.get_contract(vt_symbol)
            if contract:
                req = SubscribeRequest(
                    symbol=contract.symbol, exchange=contract.exchange)
                self.main_engine.subscribe(req, contract.gateway_name)
            else:
                self.write_log(f"行情订阅失败，找不到合约{vt_symbol}", strategy)

        # Put event to update init completed status.
        strategy.inited = True
        self.put_strategy_event(strategy)
        self.write_log(f"{strategy_name}初始化完成")
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

![启动](https://user-images.githubusercontent.com/11263900/93662312-bdd0c880-fa91-11ea-97b1-8a3505cfcb97.png)

如果当天发生了交易，主界面如图：

![主界面](https://user-images.githubusercontent.com/11263900/93662316-bf01f580-fa91-11ea-8ac6-807e28cbadd5.png)

&nbsp;

### 停止策略
- 检查策略启动状态；
- 调用策略类的on_stop()函数停止策略；
- 更新策略启动状态为False；
- 对所有为成交的委托（市价单/限价单/本地停止单）进行撤单操作；
- 把策略参数，最新的技术指标，以及持仓数量保存到.vntrader/cta_strategy_data.json内；
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

        # Sync strategy variables to data file
        self.sync_strategy_data(strategy)

        # Update GUI
        self.put_strategy_event(strategy)
```

![停止](https://user-images.githubusercontent.com/11263900/93662315-be695f00-fa91-11ea-8b1a-78a2f945db23.png)

&nbsp;

### 编辑策略
- 重新配置策略参数字典setting；
- 更新参数字典到策略中；
- 保存参数字典setting;
- 在图像化界面更新策略状态。

```
    def edit_strategy(self, strategy_name: str, setting: dict):
        """
        Edit parameters of a strategy.
        """
        strategy = self.strategies[strategy_name]
        strategy.update_setting(setting)

        self.save_strategy_setting()
        self.put_strategy_event(strategy)
```

&nbsp;

### 移除策略
- 检查策略状态，只有停止策略后从可以移除策略；
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

        # Remove from symbol strategy map
        for vt_symbol in strategy.vt_symbols:
            strategies = self.symbol_strategy_map[vt_symbol]
            strategies.remove(strategy)

        # Remove from vt_orderid strategy map
        for vt_orderid in strategy.active_orderids:
            if vt_orderid in self.orderid_strategy_map:
                self.orderid_strategy_map.pop(vt_orderid)

        # Remove from strategies
        self.strategies.pop(strategy_name)
        self.save_strategy_setting()

        return True
```


