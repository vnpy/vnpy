# SpreadTrading - 价差交易模块

## 功能简介

SpreadTrading是用于**价差交易**的功能模块，用户可以通过图形界面操作来便捷创建灵活的价差合约、完成手动交易和自动交易等任务。


## 加载启动

### VeighNa Station加载

启动登录VeighNa Station后，点击【交易】按钮，在配置对话框中的【应用模块】栏勾选【SpreadTrading】。

### 脚本加载

在启动脚本中添加如下代码：

```python 3
# 写在顶部
from vnpy_spreadtrading import SpreadTradingApp

# 写在创建main_engine对象后
main_engine.add_app(spread_trading)         
```


## 启动模块

<span id="jump">

对于用户自行开发的策略，需要放到VeighNa Trader运行时目录下的**strategies**目录中，才能被识别加载。具体的运行时目录路径，可以在VeighNa Trader主界面顶部的标题栏查看。

对于在Windows上默认安装的用户来说，放置策略的strategies目录路径通常为：

```bash
    C:\Users\Administrator\strategies
```

其中Administrator为当前登录Windows的系统用户名。

</span>

在启动模块之前，请先连接交易接口（连接方法详见基本使用篇的连接接口部分）。看到VeighNa Trader主界面【日志】栏输出“合约信息查询成功”之后再启动模块（**如果在合约信息查询成功之前打开模块，可能会导致价差的价格跳动取值为零，进而在委托成交之后引发底层报错**），如下图所示：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/cta_strategy/1.png)

请注意，IB接口因为登录时无法自动获取所有的合约信息，只有在用户手动订阅行情时才能获取。因此需要在主界面上先手动订阅合约行情，再启动模块。

成功连接交易接口后，在菜单栏中点击【功能】-> 【价差交易】，或者点击左侧按钮栏的图标：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/spread_trading/1.png)

即可进入价差交易模块的UI界面，如下图所示：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/spread_trading/2.png)


## 创建价差合约

### 查询合约

在创建价差合约前，用户可以通过【查询合约】功能，寻找可以组成价差的合约（**不支持交易所套利合约**）：

- 在VeighNa Trader菜单栏中点击【帮助】-> 【查询合约】按钮，弹出合约查询界面，如下图所示：
![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/spread_trading/3.png)
- 在界面中找到可用于组成价差交易的合约；
- 本文档以豆油期货的跨期套利来展示，即交易y2205.DCE（豆油期货22年5月到期合约）和y2209.DCE（豆油期货22年9月到期合约）。

### 构建价差合约

在价差交易的界面左侧，点击【价差创建】按钮，弹出创建价差界面，如下图所示：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/spread_trading/4.png)

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
    - 一般来说，价差交易原则上是主动腿完成交易后，立刻用被动腿进行对冲，故主动腿一般选择较为不活跃的合约，价格乘数和交易乘数均为正；被动腿一般选择较为活跃的合约，价格乘数和交易乘数均为负；
    - 不用的变量留空即可；

设置好价差合约的参数后，点击下方的【创建价差】按钮，即可成功创建价差合约。

在豆油期货跨期套利示例中，其价格乘数和交易乘数均为1：1，即价差 = y2205 - y2209；买入1手价差等于买入1手y2205，同时卖出1手y2209完成对冲。

请注意，在多条腿并且期货合约规模不等时，构建价差合约会相对困难一些，如构建虚拟钢厂套利所用到的价差合约时，计算公式如下：

- 螺纹钢生产技艺是16吨铁矿石加上5吨焦炭练成10吨螺纹钢。
- 基于价格乘数的价差spread = 1* RB - 1.6\*I  - 0.5\*O。
- 但是由于螺纹是10吨/手，铁矿石和焦炭都是100吨/手，所以他们交易乘数是1：10：10；
- 故基于最大公约数规则，其实际交易手数关系是每买入100手螺纹钢（1000吨），需要卖出16手铁矿石（1600吨）和5手焦炭（500吨）完成对冲。

### 监控价差合约

价差合约创建完毕，监控界面中的【日志】栏会输出“价差创建成功”；【价差】栏也会展示价差合约的实时行情，如下图所示：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/spread_trading/6.png)

在豆油期货价差交易示例中，【价差】组件的各字段含义如下所示：

- 买价
  - y2205买一价 - y2209卖一价
- 买量
  - min(y2205买一量, y2209卖一量)
  - 取最小值用于保证各合约能均能成交
- 卖价
  - y2205卖一价 - y2209买一价
- 卖量
  - min(y2205卖一量, y2209买一量)

### 移除价差合约

在价差交易的界面左侧，点击【移除价差】按钮，弹出移除价差界面，如下图所示：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/spread_trading/35.png)

选择好要移除的价差合约之后，点击【移除】按钮，即可成功移除价差合约。【日志】组件输出“价差移除成功”，如下图所示：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/spread_trading/36.png)


## 手动交易

假设当前豆油期货价差合约买价为408，卖价为420，并且在大周期上，价差围绕0上下波动。

价差交易的盈利在于高抛低吸，即在低位，如-300买入豆油期货价差合约，在高位，如+800卖出价差合约，平仓获利离场。由于不能立刻成交，所以其默认执行算法SpreadTaker（主动对价成交算法）会每隔一段时间进行委托操作，一般是以超价的限价单的形式发出委托。

下面通过2个例子，分别是发出委托立即成交和发出委托等待成交来具体介绍手动交易的操作情况：

### 发出委托立即成交

假设目标价差合约价格为425，我们以超价5元的形式，即430的价位发出买入限价单，如下图所示：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/spread_trading/2-7.png)

由于限价单（430）价位高于当前卖价（420），所以委托立刻成交，如下图所示：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/spread_trading/8.png)

此时各监控组件状态如下所示：

- 日志组件
  - 买入y_05_09价差合约的顺序是：发出y2205多头委托 -> y2205委托成交 -> 发出y2209空头委托 -> y2209委托成交。价差交易必须遵循的逻辑是主动腿成交后，才去用被动腿来对冲头寸，并且对冲必须尽可能及时。这也为什么一般被动腿选择较为活跃合约的原因。
- 价差组件
  - 买入1手豆油期货价差合约成交后，【净仓】从0变成1。实际上，VeighNa Trader【持仓】组件显示，y2205合约多头持仓1手，y2209合约空头持仓1手。
- 算法组件
  - 本次委托SpreadTaker算法执行情况：成交数量1手，委托状态是【全部成交】。

### 发出委托等待成交

以400的价位发出限价买入指令，由于当前买价卖价分别位于412和426，所以委托状态显示【未成交】，如下图所示：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/spread_trading/9.png)

此时各监控组件状态如下所示：

- 日志组件
  - 本次算法即SpreadTaker_000002已经启动，但由于价格没有触发到目标价位，算法在循环读秒中处于等待状态；
- 算法组件
  - 委托状态为【未成交】，要结束算法只需鼠标双击【SpreadTaker_000002】单元格即可。

仅当卖价低于-300时，才出发该限价单，已超价5元，即-295去主动成交。

### 撤销委托

 鼠标双击【SpreadTaker_000002】单元格，即可结束该算法。此时【日志】组件输出“算法已停止”，【算法】组件显示委托状态由【未成交】变成【已撤销】，如下图所示：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/spread_trading/10.png)


## 自动交易

### 添加策略

用户可以基于编写好的价差策略模板（类）来创建不同的策略实例（对象）。

在左侧的下拉框中选择要交易的策略名称（如BasicSpreadStrategy），如下图所示：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/spread_trading/19.png)

请注意，显示的策略名称是**策略类**（驼峰式命名）的名字，而不是策略文件（下划线模式命名）的名字。

选择好策略类之后，点击【添加策略】，会弹出添加策略对话框，如下图所示：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/spread_trading/11.png)

在创建策略实例时，需要配置相关参数，各参数要求如下：

- 实例名称
  - 用户自定义的策略实例名称，这里是test；
  - 策略实例名称不能重名；
- 价差名称
  - 用于交易的价差合约，这里是y_05_09；
  - 一定要是价差组件可以查询到的价差合约；
- 参数设置
  - 显示的参数名是策略里写在parameters列表中的参数名；
  - 默认数值为策略里的参数的默认值；
  - 由上图可观察到，参数名后面<>括号中显示的是该参数的数据类型，在填写参数时应遵循相应的数据类型。其中，<class 'str'>是字符串、<class 'int'>是整数、<class 'float'>是浮点数；
  - 请注意，如果某个参数可能会调整至有小数位的数值，而默认参数值是整数（比如1）。请在编写策略时，把默认参数值设为浮点数（比如1.0）。否则策略会默认该项参数为整数，在后续【编辑】策略实例参数时，会只允许填进整数。  
  
  - 以BasicSpreadStrategy为例，该策略的参数设置如下：
    - buy_price
      - 买入开仓阈值，图中是-300，即当价格跌破-300时，执行委托；
    - sell_price
      - 卖出平仓阈值，图中是400，即当价格回升到400时，执行委托；
    - short_price
      - 卖出开仓阈值，图中是800，即当价格上涨到800时，执行委托；
    - cover_price
      - 买入平仓阈值，图中是600，即当价格下跌到600时，执行委托；
    - max_pos
      - 主动腿委托数量；
    - payup
      - 超价的数值;
    - interval
      - 时间间隔，即每隔一段时间，会发出委托。

参数配置完成后，点击【添加】按钮，则开始创建策略实例。创建成功后可在右下角的策略监控组件中看到该策略实例，如下图所示：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/spread_trading/12.png)

策略监控组件顶部显示的是策略实例名、价差名、策略类名以及策略作者名（在策略里定义的author）。顶部按钮用于控制和管理策略实例，第一行表格显示了策略内部的参数信息（参数名需要写在策略的parameters列表中图形界面才会显示），第二行表格则显示了策略运行过程中的变量信息（变量名需要写在策略的variables列表中图形界面才会显示）。【inited】字段表示当前策略的初始化状态（是否已经完成了历史数据回放），【trading】字段表示策略当前是否能够开始交易。

从上图可观察到，此时该策略实例的【inited】和【trading】状态都为【False】。说明该策略实例还没有初始化，也还不能发出交易信号。

策略实例创建成功后，该策略实例的配置信息会被保存到.vntrader文件夹下的spread_trading_strategy.json文件中。

### 管理策略

#### 初始化

策略实例创建成功后，就可以对该实例进行初始化了。点击该策略实例下的【初始化】按钮，若初始化成功，则如下图所示：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/spread_trading/23.png)

可观察到此时该策略实例的【inited】状态已经为【True】。说明该策略实例已经调用过load_bar函数加载历史数据并完成初始化了。【trading】状态还是为【False】，说明此时该策略实例还不能开始自动交易。
#### 启动

策略实例初始化成功，【inited】状态为【True】时，才能启动该策略的自动交易功能。点击该策略实例下的【启动】按钮，即可启动该策略实例。成功启动后，【日志】组件则会输出相应信息（请注意，策略启动并不代表算法启动，算法启动状态取决于策略逻辑），如下图所示：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/spread_trading/13.png)

此时，【算法】组件显示，test策略调用SpreadTaker算法，分别在-300和800的位子上挂上买入和卖出委托；由于实际价格没有达到这2个阈值，故委托一直挂着，其委托状态为【未成交】。

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/spread_trading/14.png)

【策略】组件中【trading】字段从【False】变为【True】，如下图所示：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/spread_trading/24.png)

#### 停止

若要停止策略，点击策略实例下的【停止】按钮，即可停止该策略实例的自动交易。【日志】组件输出“算法已停止”，如下图所示：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/spread_trading/15.png)

【算法】组件中算法状态变为【已撤销】，如下图所示：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/spread_trading/16.png)

【策略】组件中【trading】字段从【True】变为【False】，如下图所示：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/spread_trading/29.png)

#### 编辑

如果创建策略实例之后，想要编辑某个策略实例的参数（若已启动策略，需要先点击策略实例下的【停止】按钮，停止策略），可以点击该策略实例下的【编辑】按钮，会弹出参数编辑对话框，以供修改策略参数，如下图所示：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/spread_trading/18.png)

编辑完策略参数之后，点击下方的【确定】按钮，相应的修改会立即更新在参数表格中，如下图所示：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/spread_trading/30.png)

但是策略实例的交易合约代码无法修改，同时修改完后也不会重新执行初始化操作。也请注意，此时修改的只是.vntrader文件夹下spread_trading_strategy.json文件中该策略实例的参数值，并没有修改原策略文件下的参数。

修改前，json文件如下图所示：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/spread_trading/26-1.png)

修改后，json文件如下图所示：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/spread_trading/27-1.png)

若盘中编辑后想要再次启动策略，点击策略实例下的【启动】按钮即可再次启动该策略实例，如下图所示：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/spread_trading/28.png)

#### 移除

如果创建策略实例之后，想要移除某个策略实例（若已启动策略，需要先点击策略实例下的【停止】按钮，停止策略），可以点击该策略实例下的【移除】按钮。移除成功后，图形界面右下角的策略监控组件中将不会再显示该策略实例的信息。如下图所示：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/spread_trading/34.png)

此时.vntrader文件夹下的spread_trading_strategy.json文件也移除了该策略实例的配置信息。

### 批量操作

在策略经过充分测试，实盘运行较为稳定，不需要经常进行调整的情况下，如果有多个需要运行的价差策略实例，可以使用界面左下角的【全部初始化】、【全部启动】和【全部停止】功能来执行盘前批量初始化、启动策略实例以及盘后批量停止策略实例的操作。

#### 全部初始化

在所有策略实例创建成功后，点击左下角的【全部初始化】按钮，则可批量初始化策略实例，如下图所示：

点击【全部初始化】后，如下图所示：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/spread_trading/31.png)

#### 全部启动

在所有策略实例初始化成功后，点击左下角的【全部启动】按钮，则可批量启动策略实例，如下图所示：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/spread_trading/32.png)

#### 全部停止

在所有策略实例启动成功后，点击左下角的【全部停止】按钮，则可批量停止策略实例，如下图所示：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/spread_trading/33.png)


## 价差交易策略模板（SpreadStrategyTemplate）

价差交易策略模板提供完整的信号生成和委托管理功能，用户可以基于该模板(位于vnpy.app.spread_trading.template中)自行开发策略。

用户自行开发的策略可以放在用户运行文件夹下的[strategies](#jump)文件夹内。

请注意：

1. 策略文件命名采用下划线模式，如statistical_arbitrage_strategy.py，而策略类命名采用驼峰式，如StatisticalArbitrageStrategy。

2. 自建策略的类名不要与示例策略的类名重合。如果重合了，图形界面上只会显示一个策略类名。

目前，vnpy官方提供两个价差策略，即BasicSpreadStrategy和StatisticalArbitrageStrategy。下面通过StatisticalArbitrageStrategy示例，来展示策略开发的具体步骤：

在基于价差交易策略模板编写策略逻辑之前，需要在策略文件的顶部载入需要用到的内部组件，如下方代码所示：

```python 3
from vnpy.trader.utility import BarGenerator, ArrayManager
from vnpy_spreadtrading import (
    SpreadStrategyTemplate,
    SpreadAlgoTemplate,
    SpreadData,
    OrderData,
    TradeData,
    TickData,
    BarData
)
```

其中，SpreadStrategyTemplate和SpreadAlgoTemplate是价差交易策略模板和价差算法模板，SpreadData、OrderData、TickData、TradeData和BarData是储存对应信息的数据容器，BarGenerator是K线生成模块，ArrayManager是K线时间序列管理模块。

### 策略参数与变量

在策略类的下方，可以设置策略的作者（author），参数（parameters）以及变量（variables），如下方代码所示：

```python 3
    author = "用Python的交易员"

    boll_window = 20
    boll_dev = 2
    max_pos = 10
    payup = 10
    interval = 5

    spread_pos = 0.0
    boll_up = 0.0
    boll_down = 0.0
    boll_mid = 0.0

    parameters = [
        "boll_window",
        "boll_dev",
        "max_pos",
        "payup",
        "interval"
    ]
    variables = [
        "spread_pos",
        "boll_up",
        "boll_down",
        "boll_mid"
    ]
```

虽然策略的参数和变量都从属于策略类，但策略参数是固定的（由交易员从外部指定），而策略变量则在交易的过程中随着策略的状态变化，所以策略变量一开始只需要初始化为对应的基础类型。例如：整数设为0，浮点数设为0.0，而字符串则设为""。

如果需要价差交易模块引擎在运行过程中，将策略参数和变量显示在UI界面上，并在数据刷新、停止策略时保存其数值，则需把参数和变量的名字（以字符串的数据类型）添加进parameters和variables列表里。

请注意，该列表只能接受参数和变量以str、int、float和bool四种数据类型传入。如果策略里需要用到其他数据类型的参数与变量，请把该参数或变量的定义放到__init__函数下。

### 类的初始化

入参：strategy_engine, strategy_name: str, spread: SpreadData, setting: dict

出参：无

__init__函数是策略类的构造函数，需要与继承的SpreadStrategyTemplate保持一致。

在这个继承的策略类里，初始化一般分三步，如下方代码所示：

```python 3
    def __init__(self, cta_engine, strategy_name, vt_symbol, setting):
        """"""
        super().__init__(
            strategy_engine, strategy_name, spread, setting
        )

        self.bg = BarGenerator(self.on_spread_bar)
        self.am = ArrayManager()
```

1 . 通过super( )的方法继承SpreadStrategyTemplate，在__init__( )函数中传入策略引擎、策略名称、价差以及参数设置（以上参数均由策略引擎在使用策略类创建策略实例时自动传入，用户无需进行设置）；

2 . 调用K线生成模块（BarGenerator）：通过时间切片将Tick数据合成1分钟K线数据。如有需求，还可合成更长的时间周期数据。

3 . 调用K线时间序列管理模块（ArrayManager）：基于K线数据将其转化为便于向量化计算的时间序列数据结构，并在内部支持使用talib库来计算相应的技术指标。


### 价差策略引擎调用的函数

SpreadStrategyTemplate中的update_setting函数、该函数后面四个以get开头的函数和后面两个以update开头的函数，都是价差策略引擎去负责调用的函数，一般在策略编写的时候是不需要调用的。

### 策略的回调函数

SpreadStrategyTemplate中以on开头的函数称为回调函数，在编写策略的过程中能够用来接收价差行情或者接收状态更新。回调函数的作用是当某一个事件发生的时候，策略里的这类函数会被价差交易策略引擎自动调用（无需在策略中主动操作）。回调函数按其功能可分为以下三类：

#### 策略实例状态控制（所有策略都需要）

**on_init**

* 入参：无

* 出参：无

初始化策略时on_init函数会被调用，默认写法是调用write_log函数输出“策略初始化”日志，再调用load_bar函数加载历史数据，如下方代码所示：

```python 3
    def on_init(self):
        """
        Callback when strategy is inited.
        """
        self.write_log("策略初始化")
        self.load_bar(10)
```

请注意，如果是基于Tick数据回测，请在此处调用load_tick函数。

策略初始化时，策略的inited和trading状态都为【False】，此时只是调用ArrayManager计算并缓存相关的计算指标，不能发出交易信号。调用完on_init函数之后，策略的inited状态才变为【True】，策略初始化才完成。

**on_start**

* 入参：无

* 出参：无

启动策略时on_start函数会被调用，默认写法是调用write_log函数输出“策略启动”日志，如下方代码所示：

```python 3
    def on_start(self):
        """
        Callback when strategy is started.
        """
        self.write_log("策略启动")
```

调用策略的on_start函数启动策略后，策略的trading状态变为【True】，此时策略才能够发出交易信号。

**on_stop**

* 入参：无

* 出参：无

停止策略时on_stop函数会被调用，默认写法是调用write_log函数输出“策略停止”日志，同时还原策略的变量，如下方代码所示：

```python 3
    def on_stop(self):
        """
        Callback when strategy is stopped.
        """
        self.write_log("策略停止")
        self.put_event()
```
调用策略的on_stop函数停止策略后，策略的trading状态变为【False】，此时策略就不会发出交易信号了。

#### 接收数据、计算指标、发出交易信号

**on_spread_data**

* 入参：无

* 出参：无

当价差数据更新的时候on_spread_data函数会被调用（因本次示例策略类StatisticalArbitrageStrategy不是基于on_spread_data交易，故不作示例讲解。基于on_spread_data交易的示例代码可参考示例策略BasicSpreadStrategy）。StatisticalArbitrageStrategy的写法是先调用get_spread_tick获取价差Tick数据，然后推进on_spread_tick函数中，如下方代码所示：

```python 3
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

当策略收到最新的价差Tick数据的行情时，on_spread_tick函数会被调用。默认写法是通过BarGenerator的update_tick函数把收到的Tick数据推进前面创建的bg实例中以便合成1分钟的K线，如下方代码所示：

```python 3
    def on_spread_tick(self, tick: TickData):
        """
        Callback when new spread tick data is generated.
        """
        self.bg.update_tick(tick)
```

**on_spread_bar**

* 入参：bar: BarData

* 出参：无

当策略收到最新的价差K线数据时（实盘时默认推进来的是基于Tick合成的一分钟的K线，回测时则取决于选择参数时填入的K线数据频率），on_spread_bar函数就会被调用。

如果策略基于on_spread_bar推进来的K线交易，那么请把交易请求类函数都写在on_spread_bar函数下。示例策略类StatisticalArbitrageStrategy是通过1分钟K线数据回报来生成CTA信号的。一共有三部分，如下方代码所示：

```python 3
    def on_spread_bar(self, bar: BarData):
        """
        Callback when spread bar data is generated.
        """
        self.stop_all_algos()

        self.am.update_bar(bar)
        if not self.am.inited:
            return

        self.boll_mid = self.am.sma(self.boll_window)
        self.boll_up, self.boll_down = self.am.boll(
            self.boll_window, self.boll_dev)

        if not self.spread_pos:
            if bar.close_price >= self.boll_up:
                self.start_short_algo(
                    bar.close_price - 10,
                    self.max_pos,
                    payup=self.payup,
                    interval=self.interval
                )
            elif bar.close_price <= self.boll_down:
                self.start_long_algo(
                    bar.close_price + 10,
                    self.max_pos,
                    payup=self.payup,
                    interval=self.interval
                )
        elif self.spread_pos < 0:
            if bar.close_price <= self.boll_mid:
                self.start_long_algo(
                    bar.close_price + 10,
                    abs(self.spread_pos),
                    payup=self.payup,
                    interval=self.interval
                )
        else:
            if bar.close_price >= self.boll_mid:
                self.start_short_algo(
                    bar.close_price - 10,
                    abs(self.spread_pos),
                    payup=self.payup,
                    interval=self.interval
                )

        self.put_event()
```

- 清空未成交委托：为了防止之前下的单子在上1分钟没有成交，但是下1分钟可能已经调整了价格，就用stop_all_algos()方法立刻撤销之前未成交的所有委托，保证策略在当前这1分钟开始时的整个状态是清晰和唯一的；

- 调用K线时间序列管理模块：基于最新的1分钟价差K线数据来计算相应的技术指标，如布林带通道上下轨等。首先获取ArrayManager对象，然后将收到的K线推送进去，检查ArrayManager的初始化状态，如果还没初始化成功就直接返回，没有必要去进行后续的交易相关的逻辑判断。因为很多技术指标计算对最少K线数量有要求，如果数量不够的话计算出来的指标会出现错误或无意义。反之，如果没有return，就可以开始计算技术指标了；

- 信号计算：通过持仓的判断以及结合布林带通道在通道突破点挂出委托，同时设置离场点。
  
   请注意，如果需要在图形界面刷新指标数值，请不要忘记调用put_event()函数。

#### 委托状态更新

以下函数在策略中几乎都可以直接pass，其具体逻辑应用交给回测/实盘引擎负责。

**on_spread_pos**

* 入参：无

* 出参：无

收到持有仓位更新时on_spread_pos函数会被调用。与CTA策略模块访问策略逻辑持仓不同，价差交易模块访问的是账户底层持仓。所以默认写法是通过调用get_spread_pos函数获取价差持仓，以供策略进行逻辑判断，如下方代码所示：

```python 3
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

收到策略委托回报时on_order函数会被调用。

**on_trade**

* 入参：trade: TradeData

* 出参：无

收到策略成交回报时on_trade函数会被调用。

### 主动函数

**start_long_algo**

* 入参：direction: Direction, price: float, volume: float, payup: int, interval: int, lock: bool = False, extra: dict = None

* 出参：algoid: str

**start_short_algo**

* 入参：direction: Direction, price: float, volume: float, payup: int, interval: int, lock: bool = False, extra: dict = None

* 出参：algoid: str

与CTA策略模块不同，价差交易的示例策略都是通过调用star_long_algo/start_short_algo函数（针对价差）而不是buy/sell/short/cover函数（针对特定合约）来发出委托的。在价差交易模块中，算法负责价差交易的执行，策略负责价差算法的调度。价差算法将价差交易简化为了普通委托，封装掉了所有主动腿下单和被动腿对冲的细节。

以下方star_long_algo函数的代码为例，可以看到，价格、数量、超价的数值、时间间隔是必填的参数，锁仓转换和开平方向则分别默认为False和Offset.NONE。也可以看到，函数内部收到传进来的参数之后就调用了SpreadStrategyTemplate里的start_algo函数来发单（因为是long指令，则自动把方向填成了LONG）

```python 3
     def start_long_algo(
        self,
        price: float,
        volume: float,
        payup: int,
        interval: int,
        lock: bool = False,
        extra: dict = None
    ) -> str:
        """"""
        if not extra:
            extra = None

        return self.start_algo(
            Direction.SHORT, price, volume,
            payup, interval, lock, extra
        )
```

**start_algo**

* 入参：direction: Direction, price: float, volume: float, payup: int, interval: int, lock: bool, extra: dict

* 出参：algoid: str

start_algo函数是价差策略引擎调用的启动新的价差交易算法的函数。一般在策略编写的时候不需要单独调用，通过start_long_algo/start_short_algo函数发送委托即可。

请注意，要在策略启动之后，也就是策略的trading状态变为【True】之后，才能发出交易委托。如果策略的Trading状态为【False】时调用了该函数，只会返回[]。

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

buy/sell/short/cover都是策略内部的负责针对特定合约发出底层交易委托的请求类函数。策略可以通过这些函数给价差策略引擎发送交易信号来达到下单的目的。

以下方buy函数的代码为例，可以看到，本地代码、价格和数量是必填的参数，锁仓转换则默认为False。也可以看到，函数内部收到传进来的参数之后就调用了SpreadStrategyTemplate里的send_order函数来发单（因为是buy指令，则自动把方向填成了LONG，开平填成了OPEN）

如果lock设置为True，那么该笔订单则会进行锁仓委托转换（在有今仓的情况下，如果想平仓，则会先平掉所有的昨仓，然后剩下的部分都进行反向开仓来代替平今仓，以避免平今的手续费惩罚）。

```python 3
    def buy(self, vt_symbol: str, price: float, volume: float, lock: bool = False) -> List[str]:
        """"""
        return self.send_order(vt_symbol, price, volume, Direction.LONG, Offset.OPEN, lock)
```

**send_order**

* 入参：vt_symbol: str, price: float, volume: float, direction: Direction, offset: Offset, lock: bool = False

* 出参：vt_orderids / 无

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

以下为策略以外的功能函数：

**put_event**

* 入参：无

* 出参：无

在策略中调用put_event函数，可以通知图形界面刷新策略状态相关显示。

请注意，要策略初始化完成，inited状态变为【True】之后，才能刷新界面。

**write_log**

* 入参：msg: str

* 出参：无

在策略中调用write_log函数，可以进行指定内容的日志输出。

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

在策略中调用load_bar函数，可以在策略初始化时加载K线数据。

如下方代码所示，load_bar函数调用时，默认加载的天数是10，频率是一分钟，对应也就是加载10天的1分钟K线数据。在回测时，10天指的是10个交易日，而在实盘时，10天则是指的是自然日，因此建议加载的天数宁可多一些也不要太少。

```python 3
    def load_bar(
        self,
        days: int,
        interval: Interval = Interval.MINUTE,
        callback: Callable = None,
    ):
        """
        Load historical bar data for initializing strategy.
        """
        if not callback:
            callback = self.on_spread_bar

        self.strategy_engine.load_bar(self.spread, days, interval, callback)
```

**load_tick**

* 入参：days: int

* 出参：无

在策略中调用load_tick函数，可以在策略初始化时加载Tick数据。
