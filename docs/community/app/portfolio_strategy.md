# PortfolioStrategy - 多合约组合策略模块

## 功能简介

PortfolioStrategy是用于**多合约组合策略实盘**的功能模块，用户可以通过其UI界面操作来便捷完成策略初始化、策略启动、策略停止、策略参数编辑以及策略移除等任务。

## 加载启动

### VeighNa Station加载

启动登录VeighNa Station后，点击【交易】按钮，在配置对话框中的【应用模块】栏勾选【PortfolioStrategy】。

### 脚本加载

在启动脚本中添加如下代码：

```python3
# 写在顶部
from vnpy_portfoliostrategy import PortfolioStrategyApp

# 写在创建main_engine对象后
main_engine.add_app(PortfolioStrategyApp)
```


## 启动模块

<span id="jump">

对于用户自行开发的策略，需要放到VeighNa Trader运行时目录下的**strategies**目录中，才能被识别加载。具体的运行时目录路径，可以在VeighNa Trader主界面顶部的标题栏查看。

对于在Windows上默认安装的用户来说，放置策略的strategies目录路径通常为：

```
    C:\Users\Administrator\strategies
```

其中Administrator为当前登录Windows的系统用户名。

</span>

在启动模块之前，请先连接交易接口（连接方法详见基本使用篇的连接接口部分）。看到VeighNa Trader主界面【日志】栏输出“合约信息查询成功”之后再启动模块，如下图所示：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/cta_strategy/1.png)

请注意，IB接口因为登录时无法自动获取所有的合约信息，只有在用户手动订阅行情时才能获取。因此需要在主界面上先行手动订阅合约行情，再启动模块。

成功连接交易接口后，在菜单栏中点击【功能】-> 【组合策略】，或者点击左侧按钮栏的图标：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/portfolio_strategy/0.png)

即可进入多合约组合策略模块的UI界面，如下图所示：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/portfolio_strategy/1.png)

如果配置了数据服务（配置方法详见基本使用篇的全局配置部分），打开多合约组合策略模块时会自动执行数据服务登录初始化。若成功登录，则会输出“数据服务初始化成功”的日志，如下图所示：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/portfolio_strategy/2.png)


## 添加策略

用户可以基于编写好的组合策略模板（类）来创建不同的策略实例（对象）。

在左上角的下拉框中选择要交易的策略名称，如下图所示：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/portfolio_strategy/3.png)

请注意，显示的策略名称是**策略类**（驼峰式命名）的名字，而不是策略文件（下划线模式命名）的名字。

选择好策略类之后，点击【添加策略】，会弹出添加策略对话框，如下图所示：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/portfolio_strategy/4.png)

在创建策略实例时，需要配置相关参数，各参数要求如下：

- 实例名称
  - 实例名称不能重名；
- 合约品种
  - 格式为vt_symbol（合约代码 + 交易所名称）；
  - 一定要是实盘交易系统中可以查到的合约名称；
  - 合约名用“,”隔开，中间不加空格；
- 参数设置
  - 显示的参数名是策略里写在parameters列表中的参数名；
  - 默认数值为策略里的参数的默认值；
  - 由上图可观察到，参数名后面<>括号中显示的是该参数的数据类型，在填写参数时应遵循相应的数据类型。其中，<class 'str'>是字符串、<class 'int'>是整数、<class 'float'>是浮点数；
  - 请注意，如果某个参数可能会调整至有小数位的数值，而默认参数值是整数（比如1）。请在编写策略时，把默认参数值设为浮点数（比如1.0）。否则策略会默认该项参数为整数，在后续【编辑】策略实例参数时，会只允许填进整数。

参数配置完成后，点击【添加】按钮，则开始创建策略实例。创建成功后可在左侧的策略监控组件中看到该策略实例，如下图所示：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/portfolio_strategy/5.png)

策略监控组件顶部显示的是策略实例名、策略类名以及策略作者名（在策略里定义的author）。顶部按钮用于控制和管理策略实例，第一行表格显示了策略内部的参数信息（参数名需要写在策略的parameters列表中图形界面才会显示），第二行表格则显示了策略运行过程中的变量信息（变量名需要写在策略的variables列表中图形界面才会显示）。【inited】字段表示当前策略的初始化状态（是否已经完成了历史数据回放），【trading】字段表示策略当前是否能够开始交易。

从上图可观察到，此时该策略实例的【inited】和【trading】状态都为【False】。说明该策略实例还没有初始化，也还不能发出交易信号。

策略实例创建成功后，该策略实例的配置信息会被保存到.vntrader文件夹下的portfolio_strategy_setting.json文件中。

请注意，如果添加了同名的策略实例，则会创建失败，图形界面输出“创建策略失败，存在重名”的日志信息，如下图所示：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/portfolio_strategy/8.png)


## 管理策略

### 初始化

策略实例创建成功后，就可以对该实例进行初始化了。点击该策略实例下的【初始化】按钮，若初始化成功，则如下图所示：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/portfolio_strategy/6.png)

初始化完成后，可观察到此时该策略实例的【inited】状态已经为【True】。说明该策略实例已经加载过历史数据并完成初始化了。【trading】状态还是为【False】，说明此时该策略实例还不能开始自动交易。

请注意，与CTA策略不同，如果创建实例时输入错误的vt_symbol，多合约组合策略模块会在初始化时报错，而不是在创建策略实例时报错，如下图所示：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/portfolio_strategy/7.png)

### 启动

策略实例初始化成功，【inited】状态为【True】时，才能启动该策略的自动交易功能。点击该策略实例下的【启动】按钮，即可启动该策略实例。成功后如下图所示：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/portfolio_strategy/10.png)

可观察到此时该策略实例的【inited】和【trading】状态都为【True】。说明此时该策略实例已经完成了历史数据回放，而且此时策略内部的交易请求类函数（buy/sell/short/cover/cancel_order等），以及信息输出类函数（send_email/put_event等），才会真正执行并发出对应的请求指令到底层接口中（真正执行交易）。

在上一步策略初始化的过程中，尽管策略同样在接收（历史）数据，并调用对应的功能函数，但因为【trading】状态为【False】，所以并不会有任何真正的委托下单操作或者交易相关的日志信息输出。

如果启动之后，策略发出了委托，可以去VeighNa Trader主界面【委托】栏查看委托订单细节，如下图所示：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/portfolio_strategy/9.png)

请注意，与CTA策略模块不同，多合约组合策略**不提供本地停止单功能**，所以UI界面上不会有停止单的显示区域了。


### 停止

如果启动策略之后，由于某些情况（如到了市场收盘时间，或盘中遇到紧急情况）想要停止、编辑或者移除策略，可以点击策略实例下的【停止】按钮，即可停止该策略实例的自动交易。成功后如下图所示：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/portfolio_strategy/11.png)

组合策略引擎会自动将该策略之前发出的所有活动委托全部撤销，以保证在策略停止后不会有失去控制的委托存在。同时该策略实例最新的变量信息会被保存到.vntrader文件夹下的portfolio_strategy_data.json文件中。

此时可观察到该策略实例的【trading】状态已变为【False】，说明此时该策略实例已经停止自动交易了。

在多合约组合策略的实盘交易过程中，正常情况应该让策略在整个交易时段中都自动运行，尽量不要有额外的暂停重启类操作。对于国内期货市场来说，应该在交易时段开始前，启动策略的自动交易，然后直到收盘后，再关闭自动交易。因为现在CTP夜盘收盘后也会关闭系统，早上开盘前重启，所以夜盘收盘后也需要停止策略，关闭VeighNa Trader了。

### 编辑

如果创建策略实例之后，想要编辑某个策略实例的参数（若已启动策略，需要先点击策略实例下的【停止】按钮，停止策略），可以点击该策略实例下的【编辑】按钮，会弹出参数编辑对话框，以供修改策略参数。如下图所示：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/portfolio_strategy/12.png)

编辑完策略参数之后，点击下方的【确定】按钮，相应的修改会立即更新在参数表格中。

但是策略实例的交易合约代码无法修改，同时修改完后也不会重新执行初始化操作。也请注意，此时修改的只是.vntrader文件夹下porfolio_strategy_setting.json文件中该策略实例的参数值，并没有修改原策略文件下的参数。

修改前，json文件如下图所示：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/portfolio_strategy/18.png)


修改后，json文件如下图所示：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/portfolio_strategy/17.png)

若盘中编辑后想要再次启动策略，点击策略实例下的【启动】按钮即可再次启动该策略实例。

### 移除

如果创建策略实例之后，想要移除某个策略实例（若已启动策略，需要先点击策略实例下的【停止】按钮，停止策略），可以点击该策略实例下的【移除】按钮。移除成功后，图形界面左侧的策略监控组件中将不会再显示该策略实例的信息。如下图所示：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/portfolio_strategy/13.png)

此时.vntrader文件夹下的portfolio_strategy_setting.json文件也移除了该策略实例的配置信息。

### 状态跟踪

如果想要通过图形界面跟踪策略的状态，有两种方式：

1. 调用put_event函数

   策略实例中所有的的变量信息，都需要把变量名写在策略的variables列表中，才能在图形界面显示。如果想跟踪变量的状态变化，则需要在策略中调用put_event函数，界面上才会进行数据刷新。

   有时用户会发现自己写的策略无论跑多久，变量信息都不发生变化，这种情况请检查策略中是否漏掉了对put_event函数的调用。

2. 调用write_log函数

   如果不仅想观察到变量信息的状态变化，还想根据策略的状态输出基于自己需求的个性化的日志，可以在策略中调用write_log函数，进行日志输出。

## 运行日志

### 日志内容

多合约组合策略模块UI界面上输出的日志有两个来源，分别是策略引擎和策略实例。

**引擎日志**

策略引擎一般输出的是全局信息。下图中除了策略实例名后加冒号的内容之外，都是策略引擎输出的日志。

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/portfolio_strategy/15.png)

**策略日志**

如果在策略中调用了write_log函数，那么日志内容就会通过策略日志输出。下图红框里的内容是策略实例输出的策略日志。冒号前是策略实例的名称，冒号后是write_log函数输出的内容。

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/portfolio_strategy/16.png)

### 清空操作

如果想要清空多合约组合策略UI界面上的日志输出，可以点击右上角的【清空日志】按钮，则可一键清空该界面上已输出的日志。

点击【清空日志】后，如下图所示：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/portfolio_strategy/14.png)

## 批量操作

在策略经过充分测试，实盘运行较为稳定，不需要经常进行调整的情况下，如果有多个需要运行的组合策略实例，可以使用界面右上角的【全部初始化】、【全部启动】和【全部停止】功能来执行盘前批量初始化、启动策略实例以及盘后批量停止策略实例的操作。

### 全部初始化

在所有策略实例创建成功后，点击右上角的【全部初始化】按钮，则可批量初始化策略实例，如下图所示：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/portfolio_strategy/19.png)

### 全部启动

在所有策略实例初始化成功后，点击右上角的【全部启动】按钮，则可批量启动策略实例，如下图所示：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/portfolio_strategy/20.png)

### 全部停止

在所有策略实例启动成功后，点击右上角的【全部停止】按钮，则可批量停止策略实例，如下图所示：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/portfolio_strategy/21.png)

## 多合约组合策略模板（StrategyTemplate）-- 基础

多合约组合策略模板提供了信号生成和委托管理功能，用户可以基于该模板(位于site-packages\vnpy_portfoliostrategy\template中)自行开发多合约组合策略。

用户自行开发的策略可以放在用户运行文件夹下的[strategies](#jump)文件夹内。

请注意：

1. 策略文件命名采用下划线模式，如portfolio_boll_channel_strategy.py，而策略类命名采用驼峰式，如PortfolioBollChannelStrategy。

2. 自建策略的类名不要与示例策略的类名重合。如果重合了，图形界面上只会显示一个策略类名。

下面通过PortfolioBollChannelStrategy策略示例，来展示策略开发的具体步骤：

在基于策略模板编写策略逻辑之前，需要在策略文件的顶部载入需要用到的内部组件，如下方代码所示：

```python3
from typing import List, Dict
from datetime import datetime

from vnpy.trader.utility import ArrayManager, Interval
from vnpy.trader.object import TickData, BarData
from vnpy_portfoliostrategy import StrategyTemplate, StrategyEngine
from vnpy_portfoliostrategy.utility import PortfolioBarGenerator
```

其中，StrategyTemplate是策略模板，StrategyEngine是策略引擎，Interval是数据频率，TickData和BarData都是储存对应信息的数据容器，PortfolioBarGenerator是组合策略K线生成模块，ArrayManager是K线时间序列管理模块。

### 策略参数与变量

在策略类的下方，可以设置策略的作者（author），参数（parameters）以及变量（variables），如下方代码所示：

```python3

    author = "用Python的交易员"

    boll_window = 18
    boll_dev = 3.4
    cci_window = 10
    atr_window = 30
    sl_multiplier = 5.2
    fixed_size = 1
    price_add = 5

    parameters = [
        "boll_window",
        "boll_dev",
        "cci_window",
        "atr_window",
        "sl_multiplier",
        "fixed_size",
        "price_add"
    ]
    variables = []

```

虽然策略的参数和变量都从属于策略类，但策略参数是固定的（由交易员从外部指定），而策略变量则在交易的过程中随着策略的状态而变化，所以策略变量一开始只需要初始化为对应的基础类型。例如：整数设为0，浮点数设为0.0，而字符串则设为""。

如果需要策略引擎在运行过程中，将策略参数和变量显示在UI界面上，并在数据刷新、停止策略时保存其数值，则需把参数和变量的名字（以字符串的数据类型）添加进parameters和variables列表里。

请注意，该列表只能接受参数或变量以str、int、float和bool四种数据类型传入。如果策略里需要用到其他数据类型的参数与变量，请把该参数或变量的定义放到__init__函数下。

### 类的初始化

入参：strategy_engine: StrategyEngine, strategy_name: str, vt_symbols: List[str], setting: dict

出参：无

__init__函数是策略类的构造函数，需要与继承的StrategyTemplate保持一致。

在这个继承的策略类里，初始化一般分四步，如下方代码所示：

```python3
    def __init__(
        self,
        strategy_engine: StrategyEngine,
        strategy_name: str,
        vt_symbols: List[str],
        setting: dict
    ):
        """"""
        super().__init__(strategy_engine, strategy_name, vt_symbols, setting)

        self.boll_up: Dict[str, float] = {}
        self.boll_down: Dict[str, float] = {}
        self.cci_value: Dict[str, float] = {}
        self.atr_value: Dict[str, float] = {}
        self.intra_trade_high: Dict[str, float] = {}
        self.intra_trade_low: Dict[str, float] = {}

        self.targets: Dict[str, int] = {}
        self.last_tick_time: datetime = None

        self.ams: Dict[str, ArrayManager] = {}
        for vt_symbol in self.vt_symbols:
            self.ams[vt_symbol] = ArrayManager()
            self.targets[vt_symbol] = 0

        self.pbg = PortfolioBarGenerator(self.on_bars, 2, self.on_2hour_bars, Interval.HOUR)
```

1 . 通过super( )的方法继承策略模板，在__init__( )函数中传入策略引擎、策略名称、vt_symbols以及参数设置（以上参数均由策略引擎在使用策略类创建策略实例时自动传入，用户无需进行设置）。

2 . 创建策略所需的存放不同合约K线时间序列管理实例（ArrayManager）和策略变量的字典。

3 . 分别为策略交易的不同合约创建ArrayManager和目标仓位变量并放进字典里。

ArrayManager的默认长度为100，如需调整ArrayManager的长度，可传入size参数进行调整（size不能小于计算指标的周期长度）。

4 . 调用组合策略K线生成模块（PortfolioBarGenerator）：通过时间切片将Tick数据合成1分钟K线数据。如有需求，还可合成更长的时间周期数据，如15分钟K线。

如果只基于on_bar进行交易，这里代码可以写成：

```python3
        self.pbg = PortfolioBarGenerator(self.on_bars)
```

而不用给pbg实例传入需要基于on_bars周期合成的更长K线周期，以及接收更长K线周期的函数名。

请注意：

 - 合成X分钟线时，X必须设为能被60整除的数（60除外）。对于小时线的合成没有这个限制。

 - PortfolioBarGenerator默认的基于on_bar函数合成长周期K线的数据频率是分钟级别，如果需要基于合成的小时线或者更长周期的K线交易，请在策略文件顶部导入Interval，并传入对应的数据频率给bg实例。

 - **self.on_hour_bars函数名在程序内部已使用**，如需合成1小时K线，请使用self.on_1_hour_bars或者其他命名。

### 策略引擎调用的函数

StrategyTemplate中的update_setting函数和该函数后面四个以get开头的函数以及update_trade和update_order函数，都是策略引擎去负责调用的函数，一般在策略编写的时候是不需要调用的。

### 策略的回调函数

StrategyTemplate中以on开头的函数称为回调函数，在编写策略的过程中能够用来接收数据或者接收状态更新。回调函数的作用是当某一个事件发生的时候，策略里的这类函数会被策略引擎自动调用（无需在策略中主动操作）。回调函数按其功能可分为以下两类：

#### 策略实例状态控制（所有策略都需要）

**on_init**

* 入参：无

* 出参：无

初始化策略时on_init函数会被调用，默认写法是先调用write_log函数输出“策略初始化”日志，再调用load_bars函数加载历史数据。如下方代码所示：

```python3
    def on_init(self):
        """
        Callback when strategies is inited.
        """
        self.write_log("策略初始化")
        self.load_bars(10)
```

与CTA策略不同，多合约组合策略只支持K线回测，所以多合约策略模板并没有load_ticks函数。

策略初始化时，策略的inited和trading状态都为【False】，此时只是调用ArrayManager计算并缓存相关的计算指标，不能发出交易信号。调用完on_init函数之后，策略的inited状态才变为【True】，策略初始化才完成。

**on_start**

* 入参：无

* 出参：无

启动策略时on_start函数会被调用，默认写法是调用write_log函数输出“策略启动”日志，如下方代码所示：

```python3
    def on_start(self):
        """
        Callback when strategies is started.
        """
        self.write_log("策略启动")
```

调用策略的on_start函数启动策略后，策略的trading状态变为【True】，此时策略才能够发出交易信号。

**on_stop**

* 入参：无

* 出参：无

停止策略时on_stop函数会被调用，默认写法是调用write_log函数输出“策略停止”日志，如下方代码所示：

```python3
    def on_stop(self):
        """
        Callback when strategies is stopped.
        """
        self.write_log("策略停止")
```

调用策略的on_stop函数停止策略后，策略的trading状态变为【False】，此时策略就不会发出交易信号了。

#### 接收数据、计算指标、发出交易信号

**on_tick**

* 入参：tick: TickData

* 出参：无

绝大部分交易系统都只提供Tick数据的推送。即使一部分平台可以提供K线数据的推送，但是这些数据到达本地电脑的速度也会慢于Tick数据的推送，因为也需要平台合成之后才能推送过来。所以实盘的时候，VeighNa里所有的策略的K线都是由收到的Tick数据合成的。

当策略收到实盘中最新的Tick数据的行情推送时，on_tick函数会被调用。默认写法是通过PortfolioBarGenerator的update_tick函数把收到的Tick数据推进前面创建的pbg实例中以便合成1分钟的K线，如下方代码所示：

```python3
    def on_tick(self, tick: TickData):
        """
        Callback of new tick data update.
        """
        self.pbg.update_tick(tick)
```

请注意，on_tick函数只在实盘中会被调用，回测不支持。

**on_bars**

* 入参：bars: Dict[str, BarData]

* 出参：无

当策略收到最新的K线数据时（实盘时默认推进来的是基于Tick合成的一分钟的K线，回测时则取决于选择参数时填入的K线数据频率），on_bars函数就会被调用。

与CTA策略模块不同，多合约组合策略模块在接收K线推送时，是通过on_bars回调函数一次性接收该时间点上所有合约的K线数据，而不是通过on_bar函数一个个接收（无法判断当前时点的K线是否全部走完了 ）。

示例策略里出现过的写法有两种：

1 . 如果策略基于on_bars推进来的K线交易，那么请把交易请求类函数都写在on_bars函数下（因本次示例策略类PortfolioBollChannelStrategy不是基于on_bars交易，故不作示例讲解。基于on_bars交易的示例代码可参考其他示例策略）；

2 . 如果策略需要基于on_bars推进来的K线数据通过PortfolioBarGenerator合成更长时间周期的K线来交易，那么请在on_bars中调用PortfolioBarGenerator的update_bars函数，把收到的bars推进前面创建的pbg实例中即可，如下方代码所示：

```python3
    def on_bars(self, bars: Dict[str, BarData]):
        """
        Callback of new bars data update.
        """
        self.pbg.update_bars(bars)
```

示例策略类PortfolioBollChannelStrategy是通过2小时K线数据回报来生成信号的。一共有三部分，如下方代码所示：

```python3
    def on_2hour_bars(self, bars: Dict[str, BarData]):
        """"""
        self.cancel_all()

        for vt_symbol, bar in bars.items():
            am: ArrayManager = self.ams[vt_symbol]
            am.update_bar(bar)

        for vt_symbol, bar in bars.items():
            am: ArrayManager = self.ams[vt_symbol]
            if not am.inited:
                return

            self.boll_up[vt_symbol], self.boll_down[vt_symbol] = am.boll(self.boll_window, self.boll_dev)
            self.cci_value[vt_symbol] = am.cci(self.cci_window)
            self.atr_value[vt_symbol] = am.atr(self.atr_window)

            current_pos = self.get_pos(vt_symbol)
            if current_pos == 0:
                self.intra_trade_high[vt_symbol] = bar.high_price
                self.intra_trade_low[vt_symbol] = bar.low_price

                if self.cci_value[vt_symbol] > 0:
                    self.targets[vt_symbol] = self.fixed_size
                elif self.cci_value[vt_symbol] < 0:
                    self.targets[vt_symbol] = -self.fixed_size

            elif current_pos > 0:
                self.intra_trade_high[vt_symbol] = max(self.intra_trade_high[vt_symbol], bar.high_price)
                self.intra_trade_low[vt_symbol] = bar.low_price

                long_stop = self.intra_trade_high[vt_symbol] - self.atr_value[vt_symbol] * self.sl_multiplier

                if bar.close_price <= long_stop:
                    self.targets[vt_symbol] = 0

            elif current_pos < 0:
                self.intra_trade_low[vt_symbol] = min(self.intra_trade_low[vt_symbol], bar.low_price)
                self.intra_trade_high[vt_symbol] = bar.high_price

                short_stop = self.intra_trade_low[vt_symbol] + self.atr_value[vt_symbol] * self.sl_multiplier

                if bar.close_price >= short_stop:
                    self.targets[vt_symbol] = 0

        for vt_symbol in self.vt_symbols:
            target_pos = self.targets[vt_symbol]
            current_pos = self.get_pos(vt_symbol)

            pos_diff = target_pos - current_pos
            volume = abs(pos_diff)
            bar = bars[vt_symbol]
            boll_up = self.boll_up[vt_symbol]
            boll_down = self.boll_down[vt_symbol]

            if pos_diff > 0:
                price = bar.close_price + self.price_add

                if current_pos < 0:
                    self.cover(vt_symbol, price, volume)
                else:
                    self.buy(vt_symbol, boll_up, volume)
            elif pos_diff < 0:
                price = bar.close_price - self.price_add

                if current_pos > 0:
                    self.sell(vt_symbol, price, volume)
                else:
                    self.short(vt_symbol, boll_down, volume)

        self.put_event()
```

- 清空未成交委托：为了防止之前下的单子在上一个2小时没有成交，但是下一个2小时可能已经调整了价格，就用cancel_all()方法立刻撤销之前未成交的所有委托，保证策略在当前这2小时开始时的整个状态是清晰和唯一的；

- 调用K线时间序列管理模块：基于最新的2小时K线数据来计算相应的技术指标，如布林带上下轨、CCI指标、ATR指标等。首先获取ArrayManager对象，然后将收到的K线推送进去，检查ArrayManager的初始化状态，如果还没初始化成功就直接返回，没有必要去进行后续的交易相关的逻辑判断。因为很多技术指标计算对最少K线数量有要求，如果数量不够的话计算出来的指标会出现错误或无意义。反之，如果没有return，就可以开始计算技术指标了；

- 信号计算：通过持仓的判断以及结合CCI指标、ATR指标在通道突破点挂出**限价单委托**（buy/sell)，同时设置离场点(short/cover)。

    请注意：
    1. 在CTA策略模块中，通常都是通过访问策略的变量pos获取策略持仓来进行持仓判断。但在多合约组合策略模块中，是通过调用get_pos函数获取某一合约现在的持仓来进行逻辑判断，然后设定该合约的目标仓位，最后通过目标仓位和实际仓位的差别来进行逻辑判断进而发出交易信号的；

    2. 如果需要在图形界面刷新指标数值，请不要忘记调用put_event()函数。

#### 委托状态更新

因为组合策略中需要对多合约同时下单交易，在回测时无法判断某一段K线内部每个合约委托成交的先后时间顺序，因此无法提供on_order和on_trade函数来获取委托成交推送，而只能在每次on_bars回调时通过get_pos和get_order来进行相关的状态查询。

### 主动函数

**buy**：买入开仓（Direction：LONG，Offset：OPEN）

**sell**：卖出平仓（Direction：SHORT，Offset：CLOSE）

**short**：卖出开仓（Direction：SHORT，Offset：OPEN）

**cover**：买入平仓（Direction：LONG，Offset：CLOSE）

* 入参：vt_symbol: str, price: float, volume: float, lock: bool = False, net: bool = False

* 出参：vt_orderids: List[str] / 无 

buy/sell/short/cover都是策略内部的负责发单的交易请求类函数。策略可以通过这些函数给策略引擎发送交易信号来达到下单的目的。

以下方buy函数的代码为例，可以看到，**具体要交易合约的代码**，价格和数量是必填的参数，锁仓转换和净仓转换则默认为False。也可以看到，函数内部收到传进来的参数之后就调用了StrategyTemplate里的send_order函数来发单（因为是buy指令，则自动把方向填成了LONG，开平填成了OPEN）。

与CTA策略模块不同，组合策略模块不提供本地停止单功能，所以委托函数中移除了stop参数。

如果lock设置为True，那么该笔订单则会进行锁仓委托转换（在有今仓的情况下，如果想平仓，则会先平掉所有的昨仓，然后剩下的部分都进行反向开仓来代替平今仓，以避免平今的手续费惩罚）。

如果net设置为True，那么该笔订单则会进行净仓委托转换（基于整体账户的所有仓位，根据净仓持有方式来对策略下单的开平方向进行转换）。但是净仓交易模式与锁仓交易模式互斥，因此net设置为True时，lock必须设置为False。

请注意，如果向上期所发出平仓委托，因为该交易所必须指定平今、平昨，底层会对其平仓指令自动进行转换。因为上期所部分品种有平今优惠，所以默认是以平今优先的方式发出委托的（如果交易的标的在上期所平昨更优惠的话，可以自行在vnpy.trader.converter的convert_order_request_shfe函数中做适当的修改）。

```python3
    def buy(self, vt_symbol: str, price: float, volume: float, lock: bool = False, net: bool = False) -> List[str]:
        """
        Send buy order to open a long position.
        """
        return self.send_order(vt_symbol, Direction.LONG, Offset.OPEN, price, volume, lock, net)
```

请注意，国内期货有开平仓的概念，例如买入操作要区分为买入开仓和买入平仓；但对于股票、外盘期货都是净持仓模式，没有开仓和平仓概念，所以只需使用买入（buy）和卖出（sell）这两个指令就可以了。

**send_order**

* 入参：vt_symbol: str, direction: Direction, offset: Offset, price: float, volume: float, lock: bool = False, net: bool = False

* 出参：vt_orderids: List[str] / 无

send_order函数是策略引擎调用的发送委托的函数。一般在策略编写的时候不需要单独调用，通过buy/sell/short/cover函数发送限价委托即可。

实盘的时候，收到传进来的参数后，会调用round_to函数基于合约的pricetick和min_volume对委托的价格和数量进行处理。

请注意，要在策略启动之后，也就是策略的trading状态变为【True】之后，才能发出交易委托。如果策略的Trading状态为【False】时调用了该函数，只会返回[]。

**cancel_order**

* 入参：vt_orderid: str

* 出参：无

**cancel_all**

* 入参：无

* 出参：无

cancel_order和cancel_all都是负责撤单的交易请求类函数。cancel_order是撤掉策略内指定的活动委托，cancel_all是撤掉策略所有的活动委托。

请注意，要在策略启动之后，也就是策略的trading状态变为【True】之后，才能撤单。

### 功能函数

以下为策略以外的功能函数：

**get_pos**

* 入参：vt_symbol: str

* 出参：int / 0 

在策略里调用get_pos函数，可以获取特定合约的持仓数据。

**get_order**

* 入参：vt_orderid

* 出参：OrderData / 无

在策略里调用get_order函数，可以获取特定合约的委托数据。

**get_all_active_orderids**

* 入参：无

* 出参：List[OrderData] / 无

在策略里调用get_all_active_orderids函数，可以获取当前全部活动委托号。

**get_pricetick**

* 入参：vt_symbol

* 出参：pricetick: float / None

在策略里调用get_price函数，可以获取特定合约的最小价格跳动。

**write_log**

* 入参：msg: str

* 出参：无

在策略中调用write_log函数，可以进行指定内容的日志输出。

**load_bars**

* 入参：days: int, interval: Interval = Interval.MINUTE

* 出参：无

在策略中调用load_bars函数，可以在策略初始化时加载K线数据。

如下方代码所示，load_bars函数调用时，默认加载的天数是10，频率是一分钟，对应也就是加载10天的1分钟K线数据。在回测时，10天指的是10个交易日，而在实盘时，10天则是指的是自然日，因此建议加载的天数宁可多一些也不要太少。加载时会先依次尝试通过交易接口、数据服务、数据库获取历史数据，直到获取历史数据或返回空。

```python3
    def load_bars(self, days: int, interval: Interval = Interval.MINUTE) -> None:
        """
        Load historical bar data for initializing strategies.
        """
        self.strategy_engine.load_bars(self, days, interval)
```

**put_event**

* 入参：无

* 出参：无

在策略中调用put_event函数，可以通知图形界面刷新策略状态相关显示。

请注意，要策略初始化完成，inited状态变为【True】之后，才能刷新界面。

**send_email**

* 入参：msg: str

* 出参：无

配置好邮箱相关信息之后（配置方法详见基本使用篇的全局配置部分），在策略中调用send_email函数，可以发送指定内容的邮件到自己的邮箱。

请注意，要策略初始化完成，inited状态变为【True】之后，才能发送邮件。

**sync_data**

* 入参：无

* 出参：无

在策略中调用sync_data函数，可以在实盘的时候，每次停止或成交时都同步策略变量进json文件中进行本地缓存，方便第二天初始化时再进行读取还原（策略引擎会去调用，在策略里无需主动调用）。

请注意，要在策略启动之后，也就是策略的trading状态变为【True】之后，才能同步策略信息。

## 多合约组合策略模板（StrategyTemplate）-- 进阶

PortfolioStrategy模块针对的是多标的投资组合类的量化策略，这类策略在执行层面追求的是将策略投资组合的持仓调整到目标状态，而不去过多关注底层的委托交易细节。

首先介绍持仓目标调仓交易的功能函数，来展示持仓目标调仓交易的功能支持：

### 持仓目标调仓交易的功能函数介绍

以下为持仓目标调仓交易模式中策略调用的功能函数：

**set_target**

* 入参：vt_symbol: str, target: int

* 出参：无

在策略里调用set_target函数，可以设定特定合约的目标仓位。

请注意：目标仓位是一种持续性的状态，因此设置后在后续时间会持续保持下去，直到被再次设置修改。

**get_target**

* 入参：vt_symbol: str

* 出参：int

在策略里调用get_target函数，可以获取设定的特定合约目标仓位。

请注意：策略的目标仓位状态会在sync_data时（成交、停止等）自动持久化到硬盘文件，并在策略重启后恢复。

**rebalance_portfolio**

* 入参：bars: Dict[str, BarData]

* 出参：无

在策略里调用rebalance_portfolio函数，可以基于设定的特定合约的目标仓位执行调仓交易。

请注意：只有当前bars字典中有K线切片的合约，才会参与本次调仓交易的执行，从而保证非交易时段（没有行情推送）的合约不会错误发出委托。

**calculate_price**

* 入参：vt_symbol: str, direction: Direction, reference: float

* 出参：pricetick: float

在策略里重载calculate_price函数，可以按需设定特定合约的目标价格（如固定价格超价、固定pricetick超价、百分比超价等）。

如果不传则默认返回参考价格（如不在策略中重载，则在rebalance_portfolio函数中以K线的收盘价作为委托价发出）。

### 持仓目标调仓交易的功能函数使用示例

持仓目标调仓交易功能与StrategyTemplate基础用法最大的不同，就在于策略on_bars函数中的处理差异。下面通过TrendFollowingStrategy策略示例，来展示持仓目标调仓交易的具体步骤：

**on_bars**

* 入参：bars: Dict[str, BarData]

* 出参：无

当策略收到最新的K线数据时（实盘时默认推进来的是基于Tick合成的一分钟的K线，回测时则取决于选择参数时填入的K线数据频率），on_bars函数就会被调用。

示例策略类TrendFollowingStrategy是通过一分钟K线数据回报来生成信号的。一共有三部分，如下方代码所示：

```python3
    def on_bars(self, bars: Dict[str, BarData]) -> None:
        """K线切片回调"""
        # 更新K线计算RSI数值
        for vt_symbol, bar in bars.items():
            am: ArrayManager = self.ams[vt_symbol]
            am.update_bar(bar)

        for vt_symbol, bar in bars.items():
            am: ArrayManager = self.ams[vt_symbol]
            if not am.inited:
                return

            atr_array = am.atr(self.atr_window, array=True)
            self.atr_data[vt_symbol] = atr_array[-1]
            self.atr_ma[vt_symbol] = atr_array[-self.atr_ma_window:].mean()
            self.rsi_data[vt_symbol] = am.rsi(self.rsi_window)

            current_pos = self.get_pos(vt_symbol)
            if current_pos == 0:
                self.intra_trade_high[vt_symbol] = bar.high_price
                self.intra_trade_low[vt_symbol] = bar.low_price

                if self.atr_data[vt_symbol] > self.atr_ma[vt_symbol]:
                    if self.rsi_data[vt_symbol] > self.rsi_buy:
                        self.set_target(vt_symbol, self.fixed_size)
                    elif self.rsi_data[vt_symbol] < self.rsi_sell:
                        self.set_target(vt_symbol, -self.fixed_size)
                    else:
                        self.set_target(vt_symbol, 0)

            elif current_pos > 0:
                self.intra_trade_high[vt_symbol] = max(self.intra_trade_high[vt_symbol], bar.high_price)
                self.intra_trade_low[vt_symbol] = bar.low_price

                long_stop = self.intra_trade_high[vt_symbol] * (1 - self.trailing_percent / 100)

                if bar.close_price <= long_stop:
                    self.set_target(vt_symbol, 0)

            elif current_pos < 0:
                self.intra_trade_low[vt_symbol] = min(self.intra_trade_low[vt_symbol], bar.low_price)
                self.intra_trade_high[vt_symbol] = bar.high_price

                short_stop = self.intra_trade_low[vt_symbol] * (1 + self.trailing_percent / 100)

                if bar.close_price >= short_stop:
                    self.set_target(vt_symbol, 0)

        self.rebalance_portfolio(bars)

        self.put_event()
```

- 调用K线时间序列管理模块：基于最新的分钟K线数据来计算相应的技术指标，如ATR指标、RSI指标等。首先获取ArrayManager对象，然后将收到的K线推送进去，检查ArrayManager的初始化状态，如果还没初始化成功就直接返回，没有必要去进行后续的交易相关的逻辑判断。因为很多技术指标计算对最少K线数量有要求，如果数量不够的话计算出来的指标会出现错误或无意义。反之，如果没有return，就可以开始计算技术指标了；

- 信号计算：通过持仓的判断（get_pos）以及结合指标计算结果在通道突破点**设定目标仓位**（set_target）

- 执行调仓交易（rebalance_portfolio）

**calculate_price**

* 入参：vt_symbol: str, direction: Direction, reference: float

* 出参：prcie: float

当rebalance_portfolio函数检测到目标仓位与实际仓位存在差别的时候，会调用calculate_price函数计算调仓委托价格。

策略内的默认写法是针对委托方向基于设置的price_add来计算委托价格，也可以参考示例策略PairTradingStrategy中的基于设置的tick_add来计算委托价格。

```python3
    def calculate_price(self, vt_symbol: str, direction: Direction, reference: float) -> float:
        """计算调仓委托价格（支持按需重载实现）"""
        if direction == Direction.LONG:
            price: float = reference + self.price_add
        else:
            price: float = reference - self.price_add

        return price
```

### 与StrategyTemplate基础用法的差别

**on_bars**

1 . 无需清空未成交委托：rebalance_portfolio中已经有调用cancel_all函数的逻辑，无需再在收到on_bars函数推送的时候调用cancel_all函数对未成交的委托进行撤单处理。

2 . 无需使用self.targets字典缓存合约目标仓位：直接调用set_target函数传入合约以及目标仓位（正数代表做多、负数代表做空）进行设置即可。

3 . 无需基于缓存的目标仓位在策略内手写委托逻辑：rebalance_portfolio函数已经自动接管调仓交易，会基于目标仓位进行委托。

**calculate_price**

持仓目标调仓交易需要调用calculate_price函数计算调仓委托价格。
