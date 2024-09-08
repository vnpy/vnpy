# 价差套利策略

SpreadTrading是用于**多合约价差套利**的功能模块，用户可以通过其UI界面操作来便捷创建灵活的价差合约、完成半自动算法交易和全自动策略交易等任务。


## 主要优势

SpreadTrading模块不仅提供了Taker、Maker以及Exchange三种价差执行算法支持，并提供了专业价差策略模板EliteSpreadStrategyTemplate，以实现更加强大的价差策略开发。


## 启动模块

SpreadTrading模块需要启动之前通过【策略应用】标签页加载。

启动登录VeighNa Elite Trader后，启动模块之前，请先连接交易接口。看到VeighNa Elite Trader主界面【日志】栏输出“合约信息查询成功”之后再启动模块（**如果在合约信息查询成功之前打开模块，可能会导致价差的价格跳动取值为零，进而在委托成交之后引发底层报错**）。

请注意，IB接口因为登录时无法自动获取所有的合约信息，只有在用户手动订阅行情时才能获取。因此需要在主界面上先行手动订阅合约行情，再启动模块。

成功连接交易接口后，在菜单栏中点击【功能】-> 【套利价差交易】，或者点击左侧按钮栏的图标：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/elite/spreadtrading/1.png)

即可进入套利价差交易模块的UI界面。如下图所示：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/elite/spreadtrading/2.png)


## 策略文件目录

<span id="jump">

对于用户自行开发的策略，需要放到VeighNa Elite Trader运行时目录下的**strategies**目录中，才能被识别加载。具体的运行时目录路径，可以在VeighNa Elite Trader主界面顶部的标题栏查看。

对于在Windows上默认安装的用户来说，放置策略的strategies目录路径通常为：

```
C:\Users\Administrator\strategies
```

其中Administrator为当前登录Windows的系统用户名。

</span>


## 创建价差合约

### 查询合约

在创建价差合约前，用户可以通过【查询合约】功能，寻找可以组成价差的合约（**不支持交易所套利合约**）：

- 在VeighNa Elite Trader菜单栏中点击【帮助】-> 【查询合约】按钮，弹出合约查询界面，如下图所示：

  ![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/elite/spreadtrading/3.png)

- 在界面中找到可用于组成价差交易的合约；

- 本文档以豆油期货的跨期套利来展示，即交易y2309.DCE（豆油期货23年9月到期合约）和y2401.DCE（豆油期货24年1月到期合约）。

### 构建价差合约

在价差交易的界面左侧，点击【价差创建】按钮，弹出创建价差界面，如下图所示：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/elite/spreadtrading/4.png)

价差交易模块支持灵活的价差计算公式（例如A/B、A-B*C等），同时允许引入不参与交易的定价腿，满足复杂境内外套利价差需要考虑汇率和税率等因素的需求。在创建价差合约时，需要配置相关参数，各参数要求如下：

- 价差名称
  - 用户定义的价差合约名称；
  - 价差名称不能重名；
- 主动腿代码
  - 价差盘口价格满足条件时，先发出的那条腿的本地代码。
  - 格式为vt_symbol（合约代码 + 交易所名称）；
  - 必须是下面的腿选项中的一项；
- 最小交易量
  - 最小交易手数；
- 价格公式
  - 价差合约的计算公式；
  - 支持任何Python内置数学函数；
  - 注意其中的变量只能是A、B、C、D、E（不需要都用）；
- 【A、B、C、D、E】
  - 包含构建价差合约的主动腿与被动腿，也可以引入不参与交易的定价腿，由合约代码、交易方向、交易乘数组成：
    - 合约代码为公式中的变量所对应的合约本地代码（vt_symbol）；
    - 一般来说，价差交易原则上是主动腿完成交易后，立刻用被动腿进行对冲，故主动腿一般选择较为不活跃的合约，价格乘数和交易乘数均为正；被动腿一般选择较为活跃的合约，价格乘数和交易乘数均为负（图形界面选择【卖出】，交易乘数填写正数；jupyter回测两者皆传负数）；
    - 不用的变量留空即可；

设置好价差合约的参数后，点击下方的【创建价差】按钮，即可成功创建价差合约。

在豆油期货跨期套利示例中，其价格乘数和交易乘数均为1：1，即价差 = y2401 - y2309；买入1手价差等于买入1手y2401，同时卖出1手y2309完成对冲。

请注意，在多条腿并且期货合约规模不等时，构建价差合约会相对困难一些，如构建虚拟钢厂套利所用到的价差合约时，计算公式如下：

- 螺纹钢生产技艺是16吨铁矿石加上5吨焦炭练成10吨螺纹钢。
- 基于价格乘数的价差spread = 1* RB - 1.6\*I  - 0.5\*J。
- 但是由于螺纹是10吨/手，铁矿石和焦炭都是100吨/手，所以他们交易乘数是1：10：10；
- 故基于最大公约数规则，其实际交易手数关系是每买入100手螺纹钢（1000吨），需要卖出16手铁矿石（1600吨）和5手焦炭（500吨）完成对冲。

### 监控价差合约

价差合约创建完毕，监控界面中的【日志】栏会输出“价差创建成功”；【价差】栏也会展示价差合约的实时行情，如下图所示：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/elite/spreadtrading/5.png)

在豆油期货价差交易示例中，【价差】组件的各字段含义如下所示：

- 买价
  - y2401买一价 - y2309卖一价
- 买量
  - min(y2401买一量, y2309卖一量)
  - 取最小值用于保证各合约能均能成交
- 卖价
  - y2401卖一价 - y2309买一价
- 卖量
  - min(y2401卖一量, y2309买一量)

### 移除价差合约

在价差交易的界面左侧，点击【移除价差】按钮，弹出移除价差界面，如下图所示：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/elite/spreadtrading/6.png)

选择好要移除的价差合约之后，点击【移除】按钮，即可成功移除价差合约。【日志】组件输出“价差移除成功”，如下图所示：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/elite/spreadtrading/7.png)


## 半自动算法交易

用户可以通过模块界面左上角【交易】组件选择算法（目前支持[三种算法](#jump1)）进行半自动算法交易，如下图所示：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/elite/spreadtrading/10.png)

填写参数时请注意：

 - 开平：只有启动Exchange算法在【开仓】和【平仓】中选择，其他大多数用时候选择【净仓】，股指合约用【锁仓】


下面通过2个SpreadTakerAlgo（主动对价成交算法）的例子，分别是发出委托立即成交和发出委托等待成交来介绍手动交易的操作情况：

### 启动算法立即成交（超价）

目标价差合约价格为-70，以-60的价位启动做多算法（超价），算法会立即发出委托并成交，如下图所示：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/elite/spreadtrading/11.png)

### 启动算法等待成交（限价）

以-80的价位启动做多算法，由于当前买价卖价分别位于-76和-72，所以委托状态显示【未成交】，如下图所示：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/elite/spreadtrading/12.png)

### 停止运行中的算法

 鼠标双击需要停止算法的单元格，即可结束该算法。此时【日志】组件输出“算法已停止”，【算法】组件显示委托状态由【未成交】变成【已撤销】，如下图所示：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/elite/spreadtrading/13.png)


## 全自动策略交易

### 添加策略

用户可以基于编写好的价差策略模板（类）来创建不同的策略实例（对象）。

在左侧的下拉框中选择要交易的策略名称（如MeanReversionStrategy），如下图所示：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/elite/spreadtrading/14.png)

请注意，显示的策略名称是**策略类**（驼峰式命名）的名字，而不是策略文件（下划线模式命名）的名字。

选择好策略类之后，点击【添加策略】，会弹出添加策略对话框，如下图所示：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/elite/spreadtrading/15.png)

在创建策略实例时，需要配置相关参数，各参数要求如下：

- 实例名称
  - 用户自定义的策略实例名称；
  - 策略实例名称不能重名；
- 价差名称
  - 用于交易的价差合约；
  - 一定要是价差组件可以查询到的价差合约；
- 参数设置
  - 显示的参数名称是在策略中使用Parameter辅助类定义的参数；
  - 默认数值为策略里的参数的默认值；
  - 由上图可观察到，参数名后面<>括号中显示的是该参数的数据类型，在填写参数时应遵循相应的数据类型。其中，<class 'str'>是字符串、<class 'int'>是整数、<class 'float'>是浮点数；
  - 请注意，如果某个参数可能会调整至有小数位的数值，而默认参数值是整数（比如1）。请在编写策略时，把默认参数值设为浮点数（比如1.0）。否则策略会默认该项参数为整数，在后续【编辑】策略实例参数时，会只允许填进整数。

  - 以MeanReversionStrategy为例，该策略的参数设置如下：
    - ma_window（均线窗口）
    - entry_range（入场范围）
    - fixed_volume（固定交易数量）
    - payup（各条腿委托时，基于对价盘口的加点）
    - interval（限价单多少秒不成交，则撤销重挂）

参数配置完成后，点击【添加】按钮，则开始创建策略实例。创建成功后可在右下角的策略监控组件中看到该策略实例，如下图所示：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/elite/spreadtrading/16.png)

策略监控组件顶部显示的是策略实例名、价差名、策略类名以及策略作者名（在策略里定义的author）。顶部按钮用于控制和管理策略实例，第一行表格显示了策略内部的参数信息（参数名需要写在策略的parameters列表中图形界面才会显示），第二行表格则显示了策略运行过程中的变量信息（变量名需要写在策略的variables列表中图形界面才会显示）。【inited】字段表示当前策略的初始化状态（是否已经完成了历史数据回放），【trading】字段表示策略当前是否能够开始交易。

从上图可观察到，此时该策略实例的【inited】和【trading】状态都为【False】。说明该策略实例还没有初始化，也还不能发出交易信号。

策略实例创建成功后，该策略实例的配置信息会被保存到.vntrader文件夹下的spread_trading_strategy.json文件中。

### 管理策略

#### 初始化

策略实例创建成功后，就可以对该实例进行初始化了。点击该策略实例下的【初始化】按钮，若初始化成功，则如下图所示：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/elite/spreadtrading/17.png)

可观察到此时该策略实例的【inited】状态已经为【True】。说明该策略实例已经调用过load_bar函数加载历史数据并完成初始化了。【trading】状态还是为【False】，说明此时该策略实例还不能开始自动交易。

#### 启动

策略实例初始化成功，【inited】状态为【True】时，才能启动该策略的自动交易功能。点击该策略实例下的【启动】按钮，即可启动该策略实例。成功启动后，【日志】组件则会输出相应信息（请注意，策略启动并不代表算法启动，算法启动状态取决于策略逻辑），如下图所示：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/elite/spreadtrading/24.png)

【策略】组件中【trading】字段从【False】变为【True】，如下图所示：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/elite/spreadtrading/18.png)

#### 停止

若要停止策略，点击策略实例下的【停止】按钮，即可停止该策略实例的自动交易。【日志】组件输出“策略停止”，如下图所示：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/elite/spreadtrading/25.png)

【策略】组件中【trading】字段从【True】变为【False】，如下图所示：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/elite/spreadtrading/19.png)

 - 停止策略时，策略引擎会先停止策略启动的所有算法，撤销所有未成交委托，然后再停止策略实例的自动交易。若停止策略时仍有未停止的算法，可以在【日志】组件观察到“算法已停止”的输出，【算法】组件中对应算法状态也会变为【已撤销】。

#### 编辑

如果创建策略实例之后，想要编辑某个策略实例的参数（若已启动策略，需要先点击策略实例下的【停止】按钮，停止策略），可以点击该策略实例下的【编辑】按钮，会弹出参数编辑对话框，以供修改策略参数，如下图所示：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/elite/spreadtrading/20.png)

编辑完策略参数之后，点击下方的【确定】按钮，相应的修改会立即更新在参数表格中，如下图所示：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/elite/spreadtrading/21.png)

但是策略实例的交易合约代码无法修改，同时修改完后也不会重新执行初始化操作。也请注意，此时修改的只是.vntrader文件夹下spread_trading_strategy.json文件中该策略实例的参数值，并没有修改原策略文件下的参数。

若盘中编辑后想要再次启动策略，点击策略实例下的【启动】按钮即可再次启动该策略实例，如下图所示：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/elite/spreadtrading/22.png)

#### 移除

如果创建策略实例之后，想要移除某个策略实例（若已启动策略，需要先点击策略实例下的【停止】按钮，停止策略），可以点击该策略实例下的【移除】按钮。移除成功后，图形界面右下角的策略监控组件中将不会再显示该策略实例的信息。如下图所示：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/elite/spreadtrading/23.png)

此时.vntrader文件夹下的spread_trading_strategy.json文件也移除了该策略实例的配置信息。

### 批量操作

在策略经过充分测试，实盘运行较为稳定，不需要经常进行调整的情况下，如果有多个需要运行的价差策略实例，可以使用界面左下角的【全部初始化】、【全部启动】和【全部停止】功能来执行盘前批量初始化、启动策略实例以及盘后批量停止策略实例的操作。


## 价差交易策略模板

价差交易策略模板提供了信号生成和委托管理功能，用户可以基于模板自行开发策略。

用户自行开发的策略可以放在用户运行文件夹下的[strategies](#jump)文件夹内。

请注意：

  - 策略文件命名采用下划线模式，如mean_reversion_strategy.py，而策略类命名采用驼峰式，如MeanReversionStrategy。

  - 自建策略的类名不要与示例策略的类名重合，否则会出现策略类互相覆盖的错误情况。

### EliteSpreadStrategyTemplate

VeighNa Elite Trader的价差套利模块提供了EliteSpreadStrategyTemplate专业价差套利策略模板，实现更强大的价差策略开发。

下面通过MeanReversionStrategy策略示例，来展示策略开发的具体步骤：

在基于EliteSpreadStrategyTemplate编写策略逻辑之前，需要在策略文件的顶部载入需要用到的内部组件，如下方代码所示：

```python3
from vnpy.trader.utility import BarGenerator, ArrayManager

from elite_spreadtrading import (
    SpreadStrategyTemplate,
    SpreadAlgoTemplate,
    AlgoType,
    AlgoOffset,
    Variable,
    Parameter,
    SpreadData,
    OrderData,
    TradeData,
    TickData,
    BarData
)
```

其中：
* SpreadStrategyTemplate是Veighna Elite Trader提供的价差交易策略模板
* SpreadAlgoTemplate是价差算法模板
* AlgoType和AlgoOffset是用来配置算法交易模式的算法类型和算法开平选项
* Parameter是储存策略参数的数据容器
* Variable是储存策略变量的数据容器
* SpreadData、OrderData、TickData、TradeData和BarData是储存对应信息的数据容器
* BarGenerator是K线生成模块
* ArrayManager是K线时间序列管理模块。

### 策略参数与变量

在策略类的下方，可以设置策略的作者（author），参数（parameters）以及变量（variables），如下方代码所示：

```python3
    author = "用Python的交易员"

    ma_window: int = Parameter(60)
    entry_range: int = Parameter(20)
    fixed_volume: int = Parameter(10)
    payup: int = Parameter(10)
    interval: int = Parameter(5)

    spread_pos: float = Variable(0.0)
    ma_value: float = Variable(0.0)

```

虽然策略的参数和变量都从属于策略类，但策略参数是固定的（由交易员从外部指定），而策略变量则在交易的过程中随着策略的状态变化，所以策略变量一开始只需要初始化为对应的基础类型。例如：整数设为0，浮点数设为0.0。

如果需要价差套利交易模块引擎在运行过程中，将策略参数和变量显示在UI界面上，并在数据刷新、停止策略时保存其数值，则需在创建策略类的时候创建对应的参数和变量实例。

请注意：
 - Parameter容器和Variable容器只能接受参数或变量以str、int、float和bool四种数据类型传入。


### 策略的回调函数

SpreadStrategyTemplate中以on开头的函数称为回调函数，在编写策略的过程中能够用来接收价差行情或者接收状态更新。回调函数的作用是当某一个事件发生的时候，策略里的这类函数会被价差交易策略引擎自动调用（无需在策略中主动操作）。回调函数按其功能可分为以下三类：

#### 策略实例状态控制（所有策略都需要）

**on_init**

* 入参：无

* 出参：无

初始化策略时on_init函数会被调用，在此处通常会实现的功能逻辑包括：

1. 实例化K线数据合成组件（BarGenerator）：通过时间切片将Tick数据合成1分钟K线数据。如有需求，还可合成更长的时间周期数据。

2. 实例化K线时间序列缓存组件（ArrayManager）：基于K线数据将其转化为便于向量化计算的时间序列数据结构，并在内部支持使用talib库来计算相应的技术指标。

    - ArrayManager的默认长度为100，如需调整ArrayManager的长度，可传入size参数进行调整（size不能小于计算指标的周期长度）。

3. 对价差算法交易模式进行配置：

 - AlgoType
   | 枚举值 | 值 
   | ------ | -------- 
   | TAKER |  "taker"          |
   | MAKER |  "maker"          |
   | EXCHANGE |  "exchange"          |

 - AlgoOffset
   | 枚举值 | 值 
   | ------ | -------- 
   | LOCK |  "锁仓"          |
   | NET |  "净仓"          |
   | OPEN |  "开仓"          |
   | CLOSE |  "平仓"          |

完成上述组件初始化后，再调用load_bar函数加载历史数据，如下方代码所示：

```python3
    def on_init(self):
        """
        Callback when strategies is inited.
        """
        self.bg = BarGenerator(self.on_spread_bar)
        self.am = ArrayManager(self.ma_window + 10)

        # 价差算法交易模式配置
        self.algo_type: AlgoType = AlgoType.TAKER
        self.algo_offset: AlgoOffset = AlgoOffset.NET

        self.write_log("策略初始化")
        self.load_bar(10)
```

请注意，如果是基于Tick数据回测，请在此处调用load_tick函数。

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

调用策略的on_start函数启动策略后，策略的trading状态变为【True】，此时策略才能够启动价差交易算法。

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
        self.put_event()
```
调用策略的on_stop函数停止策略后，策略的trading状态变为【False】，此时策略就不再允许启动价差交易算法了。

#### 接收数据、计算指标、发出交易信号

**on_spread_data**

* 入参：无

* 出参：无

当价差数据更新的时候on_spread_data函数会被调用（因本次示例策略类MeanReversionStrategy不是基于on_spread_data交易，故不作示例讲解）。MeanReversionStrategy的写法是先调用get_spread_tick获取价差Tick数据，然后推进on_spread_tick函数中，如下方代码所示：

```python3
    def on_spread_data(self):
        """
        Callback when spread price is updated.
        """
        tick = self.get_spread_tick()
        self.on_spread_tick(tick)
```

**on_spread_tick**

* 入参：tick: TickData

* 出参：无

on_spread_tick函数通常由用户在on_spread_data下发起调用，通常的用法是通过BarGenerator的update_tick函数把收到的Tick数据推进前面创建的bg实例中以便合成1分钟的K线，如下方代码所示：

```python3
    def on_spread_tick(self, tick: TickData):
        """
        Callback when new spread tick data is generated.
        """
        self.bg.update_tick(tick)
```

**on_spread_bar**

* 入参：bar: BarData

* 出参：无

当BarGenerator完成1分钟K线合成时（实盘时默认推进来的是基于Tick合成的一分钟的K线，回测时则取决于选择参数时填入的K线数据频率），on_spread_bar函数就会被调用。

如果策略基于on_spread_bar推进来的K线交易，那么请把交易请求类函数都写在on_spread_bar函数下。示例策略类MeanReversionStrategy是通过1分钟K线数据回报来生成CTA信号的。一共有三部分，如下方代码所示：

```python3
    def on_spread_bar(self, bar: BarData):
        """
        Callback when spread bar data is generated.
        """
        self.stop_all_algos()

        self.am.update_bar(bar)
        if not self.am.inited:
            return

        self.ma_value = self.am.sma(self.ma_window)

        if not self.spread_pos:
            if bar.close_price >= self.ma_value + self.entry_range:
                self.start_short_algo(
                    bar.close_price - 10,
                    self.fixed_volume,
                    payup=self.payup,
                    interval=self.interval,
                    algo_type=self.algo_type,
                    algo_offset=self.algo_offset
                )
            elif bar.close_price <= self.ma_value - self.entry_range:
                self.start_long_algo(
                    bar.close_price + 10,
                    self.fixed_volume,
                    payup=self.payup,
                    interval=self.interval,
                    algo_type=self.algo_type,
                    algo_offset=self.algo_offset
                )
        elif self.spread_pos < 0:
            if bar.close_price <= self.ma_value:
                self.start_long_algo(
                    bar.close_price + 10,
                    abs(self.spread_pos),
                    payup=self.payup,
                    interval=self.interval,
                    algo_type=self.algo_type,
                    algo_offset=self.algo_offset
                )
        else:
            if bar.close_price >= self.ma_value:
                self.start_short_algo(
                    bar.close_price - 10,
                    abs(self.spread_pos),
                    payup=self.payup,
                    interval=self.interval,
                    algo_type=self.algo_type,
                    algo_offset=self.algo_offset
                )

        self.put_event()
```

- 清空未成交委托：为了防止之前下的单子在上1分钟没有成交，但是下1分钟可能已经调整了价格，就用stop_all_algos()方法立刻撤销之前未成交的所有委托，保证策略在当前这1分钟开始时的整个状态是清晰和唯一的；

- 计算策略信号指标：基于最新的1分钟价差K线数据来计算相应的技术指标，如均线等。首先获取ArrayManager对象，然后将收到的K线推送进去，检查ArrayManager的初始化状态，如果还没初始化成功就直接返回，没有必要去进行后续的交易相关的逻辑判断。因为很多技术指标计算对最少K线数量有要求，如果数量不够的话计算出来的指标会出现错误或无意义。反之，如果没有return，就可以开始计算技术指标了；

- 启动价差执行算法：通过持仓的判断以及结合均线指标挂出委托，同时设置离场点。
  
   请注意：

   1. 启动算法时，如果不传algo_type和algo_offset，则分别默认为“taker”和“净仓”；

   2. 启动Maker算法时，不要忘记传入active_quote_range和active_max_volume参数；

   3. 只有启动Exchange算法时，algoOffset才在AlgoOffset.OPEN和AlgoOffset.CLOSE中选择；
   
   4. 如果需要在图形界面刷新显示的策略状态数值，请不要忘记调用put_event()函数。

#### 委托状态更新

以下函数在策略中几乎都可以直接pass，其具体逻辑应用交给回测/实盘引擎负责。

**on_spread_pos**

* 入参：无

* 出参：无

收到持有仓位更新时on_spread_pos函数会被调用。与CTA策略模块访问策略逻辑持仓不同，价差交易模块访问的是账户底层持仓。所以默认写法是通过调用get_spread_pos函数获取价差持仓，以供策略进行逻辑判断，如下方代码所示：

```python3
    def on_spread_pos(self):
        """
        Callback when spread position is updated.
        """
        self.spread_pos = self.get_spread_pos()
        self.put_event()
```

**on_spread_algo**

* 入参：algo: SpreadAlgoTemplate

* 出参：无

收到算法状态更新时on_spread_algo函数会被调用。

**on_order**

* 入参：order: OrderData

* 出参：无

收到策略委托回报时on_order函数会被调用（只有通过策略发出委托才能收到该函数回调，通过策略启动算法进行委托收不到该函数回调）。

**on_trade**

* 入参：trade: TradeData

* 出参：无

收到策略成交回报时on_trade函数会被调用（只有通过策略发出委托才能收到该函数回调，通过策略启动算法进行委托收不到该函数回调）。

### 主动函数

**start_long_algo**

* 入参：price: float, volume: float, payup: int = None, interval: int = None, algo_type: AlgoType = AlgoType.TAKER, algo_offset: AlgoOffset = AlgoOffset.NET, active_quote_range: int = None, active_max_volume: int = None

* 出参：algoid: str

**start_short_algo**

* 入参：price: float, volume: float, payup: int = None, interval: int = None, algo_type: AlgoType = AlgoType.TAKER, algo_offset: AlgoOffset = AlgoOffset.NET, active_quote_range: int = None, active_max_volume: int = None

* 出参：algoid: str

与CTA策略模块不同，价差交易的示例策略都是通过调用star_long_algo/start_short_algo函数（针对价差组合）而不是buy/sell/short/cover函数（针对单一合约）来发出委托的。在价差交易模块中，算法负责价差交易的执行，策略负责价差算法的调度。价差算法将价差交易简化为了普通委托，封装掉了所有主动腿下单和被动腿对冲的细节。

以下方star_long_algo函数的代码为例，可以看到，价格和数量是必填的参数，超价的数值、时间间隔、算法类型、算法开平、maker挂单范围阈值、maker单笔委托量最大值等参数都是选填。也可以看到，函数内部收到传进来的参数之后就调用了SpreadStrategyTemplate里的start_algo函数来发单（因为是long指令，则自动把方向填成了LONG）

```python3
    def start_long_algo(
        self,
        price: float,
        volume: float,
        payup: int = None,
        interval: int = None,
        algo_type: AlgoType = AlgoType.TAKER,
        algo_offset: AlgoOffset = AlgoOffset.NET,
        active_quote_range: int = None,
        active_max_volume: int = None
    ) -> str:
        """"""
        return self.start_algo(
            Direction.LONG,
            price,
            volume,
            payup,
            interval,
            algo_type,
            algo_offset,
            active_quote_range,
            active_max_volume
        )
```

**start_algo**

* 入参：direction: Direction, price: float, volume: float, payup: int = None, interval: int = None, algo_type: AlgoType = AlgoType.TAKER, algo_offset: AlgoOffset = AlgoOffset.NET, active_quote_range: int = None, active_max_volume: int = None

* 出参：algoid: str

start_algo函数是价差策略引擎调用的启动新的价差交易算法的函数。一般在策略编写的时候不需要单独调用，通过start_long_algo/start_short_algo函数发送委托即可。

请注意:

 1. 要在策略启动之后，也就是策略的trading状态变为【True】之后，才能发出交易委托。如果策略的Trading状态为【False】时调用了该函数，只会返回"";

 2. 若启动算法时少传参或传错参，算法会启动失败并输出相关日志信息。

**stop_algo**

* 入参：algoid: str

* 出参：无

**stop_all_algos**

* 入参：无

* 出参：无

stop_algo和stop_all_algos都是负责停止价差算法的交易请求类函数。stop_algo是停止策略内指定的价差算法，stop_all_algos是停止策略所有的活动价差算法。

请注意，要在策略启动之后，也就是策略的trading状态变为【True】之后，才能撤单。

**buy**：买入开仓（Direction：LONG，Offset：OPEN）

**sell**：卖出平仓（Direction：SHORT，Offset：CLOSE）

**short**：卖出开仓（Direction：SHORT，Offset：OPEN）

**cover**：买入平仓（Direction：LONG，Offset：CLOSE）

* 入参：vt_symbol: str, price: float, volume: float, lock: bool = False

* 出参：vt_orderids: List[vt_orderid] / 无 

buy/sell/short/cover都是策略内部的负责针对特定的单一合约发出底层交易委托的请求类函数。策略可以通过这些函数给价差策略引擎发送交易信号来达到下单的目的。

以下方buy函数的代码为例，可以看到，本地代码、价格和数量是必填的参数，锁仓转换则默认为False。也可以看到，函数内部收到传进来的参数之后就调用了SpreadStrategyTemplate里的send_order函数来发单（因为是buy指令，则自动把方向填成了LONG，开平填成了OPEN）

如果lock设置为True，那么该笔订单则会进行锁仓委托转换（在有今仓的情况下，如果想平仓，则会先平掉所有的昨仓，然后剩下的部分都进行反向开仓来代替平今仓，以避免平今的手续费惩罚）。

```python3
    def buy(self, vt_symbol: str, price: float, volume: float, lock: bool = False) -> List[str]:
        """"""
        return self.send_order(vt_symbol, price, volume, Direction.LONG, Offset.OPEN, lock)
```

**send_order**

* 入参：vt_symbol: str, price: float, volume: float, direction: Direction, offset: Offset, lock: bool = False

* 出参：vt_orderids / []

send_order函数是价差策略引擎调用的针对特定合约（**而不是价差**）发送委托的函数。一般在策略编写的时候不需要单独调用，通过buy/sell/short/cover函数发送委托即可。

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

以下为委托交易以外的功能函数：

**put_event**

* 入参：无

* 出参：无

在策略中调用put_event函数，可以通知图形界面刷新策略状态相关显示。

请注意，要策略初始化完成，inited状态变为【True】之后，才能刷新界面。

**write_log**

* 入参：msg: str

* 出参：无

在策略中调用write_log函数，可以进行指定内容的日志输出。

**get_engine_type**

* 入参：无

* 出参：engine_type: EngineType

在策略里调用get_engine_type函数，可以获取策略引擎类型。

**get_spread_tick**

* 入参：无

* 出参：tick: TickData

在策略里调用get_spread_tick函数，可以获取价差Tick数据。

**get_spread_pos**

* 入参：无

* 出参：spread_pos: float

在策略里调用get_spread_pos函数，可以获取价差净持仓数据。

**get_leg_tick**

* 入参：vt_symbol: str

* 出参：leg.tick: TickData / None

在策略里调用get_leg_tick函数，可以获取特定合约的Tick数据。

**get_leg_pos**

* 入参：vt_symbol: str, direction: Direction = Direction.NET

* 出参：leg.net_pos: float / leg.long_pos: float /leg.short_pos: float / None

在策略里调用get_leg_pos函数，可以获取特定合约的持仓数据，用于处理瘸腿后的细粒度调整。

**send_email**

* 入参：msg: str

* 出参：无

配置好邮箱相关信息之后（配置方法详见基本使用篇的全局配置部分），在策略中调用send_email函数，可以发送指定内容的邮件到自己的邮箱。

请注意，要策略初始化完成，inited状态变为【True】之后，才能发送邮件。

**load_bar**

* 入参：days: int, interval: Interval = Interval.MINUTE, callback: Callable = None

* 出参：无

在策略中调用load_bar函数，可以在策略初始化时加载价差K线数据。

如下方代码所示，load_bar函数调用时，默认加载的天数是10，频率是一分钟，对应也就是加载10天的1分钟K线数据，建议加载的天数宁可多一些也不要太少。加载时会先依次尝试通过交易接口、数据服务、数据库获取历史数据，直到获取历史数据或返回空。

请注意，回测期内每条腿的K线数据（1分钟最佳），若有某条腿缺失一段，则所有腿的这一段数据都会被弃用。

```python3
    def load_bar(
        self,
        days: int,
        interval: Interval = Interval.MINUTE,
        callback: Callable = None,
    ):
        """
        Load historical bar data for initializing strategies.
        """
        if not callback:
            callback = self.on_spread_bar

        self.strategy_engine.load_bar(self.spread, days, interval, callback)
```

**load_tick**

* 入参：days: int

* 出参：无

价差Tick数据来源：
首先需要在SpreadTrading模块中创建配置好价差后，通过DataRecorder模块来进行Tick录制，本地代码填入xx-spread.LOCAL，其中xx-spread为用户定义的价差名称，LOCAL为固定交易所后缀（代表本地生成）。

在策略中调用load_tick函数，可以在策略初始化时去数据库加载录制好的价差Tick盘口数据。


## 算法介绍

<span id="jump1">

价差套利模块都是通过价差算法来执行价差交易，从而将相对复杂的多条腿交易执行简化为面向价差组合的普通委托，封装掉所有主动腿下单和被动腿对冲的细节。

### 算法检查函数

 - is_active：检查算法是否结束
 - is_order_finished：检查委托是否全部结束
 - is_hedge_finished：检查被动腿和主动腿是否匹配
 - check_algo_cancelled：检查算法是否被停止
 - calculate_traded_volume：计算已成交价差数量
 - calculate_traded_price：计算已成交价差均价

### SpreadTakerAlgo（见价下单算法）

#### 算法原理

 - 见价下单：主动腿以对价先行下单；被动腿以对价立即对冲

 - 算法收到tick数据推送：先检查委托是否结束，再检查对冲是否结束，若未结束则发起被动腿对冲。最后检查盘口是否满足条件，满足条件后发出主动腿委托

 - 算法收到委托回报：若收到主动腿已结束的委托，则发起被动腿对冲

 - 超时限制：到达计时时间执行委托全撤

#### 算法优势

 - 灵活且不占用过多撤单次数

#### 不足

 - 所有腿均需要付出盘口买卖价差的滑点成本
 - 等待主动腿对价满足条件，需要比Maker更长的时间

### SpreadMakerAlgo（报价做市算法）

#### 算法原理

 - 报价做市：基于被动腿盘口，计算主动腿最差成交价

 - 算法收到tick数据推送：先检查委托是否结束，再检查对冲是否结束，若未结束则发起被动腿对冲。然后检查新的挂单价格与当前已挂价格的差值是否超过设定的阈值，如果未超过则发出主动腿委托，如果超过则重挂

 - 算法收到委托回报：遭遇拒单则停止策略；若收到主动腿已结束的委托，则清空挂单价格记录

 - 算法收到成交回报：只关心主动腿委托，若对冲未结束则发起被动腿对冲

 - 计时时间到达：到达计时时间执行委托全撤

#### 算法优势

 - 主动腿报价挂单做市，目标是赚得盘口价差的同时提高成交概率

#### 不足
 
 - 虽然有设定挂单阈值限制，但撤单行为比Taker更频繁，需要仔细监控委托流量费成本

### SpreadExchangeAlgo（交易所价差算法）

#### 算法原理
 
 - 基于交易所提供的价差组合来创建价差，采用各条腿的行情盘口计算价差盘口，最终采用交易所的价差合约进行交易执行

 - 算法收到tick数据推送：检查是否已发出了委托，若已发出则返回。再检查价差套利合约是否生成成功，并查询价差套利合约的合约信息，然后发出交易所价差委托，缓存委托号和价差关系，最后输出日志并记录委托已经发出的状态

#### 算法优势

 - 体验上类似单合约，且免去了主动腿撤单

#### 不足

 - 缺乏灵活性，可选择合约范围有限

</span>
