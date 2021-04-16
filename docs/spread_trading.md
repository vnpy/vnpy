# SpreadTrading - 价差交易模块


## 功能简介

SpreadTrading是用于**价差交易**的功能模块，用户可以通过图形界面操作来便捷创建灵活的价差合约、完成手动交易和自动交易等任务。


## 加载启动

### VN Station加载

启动登录VN Station后，点击【VN Trader Pro】按钮，在配置对话框中的【上层应用】栏勾选【SpreadTrading】。

### 脚本加载

在启动脚本中添加如下代码：

```
# 写在顶部
from vnpy.app.spread_trading import SpreadTradingApp

# 写在创建main_engine对象后
main_engine.add_app(spread_trading)         
```


## 启动模块

在启动模块之前，请先连接交易接口（连接方法详见基本使用篇的连接接口部分）。看到VN Trader主界面【日志】栏输出“合约信息查询成功”之后再启动模块，如下图所示：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/cta_strategy/1.png)

请注意，IB接口因为登录时无法自动获取所有的合约信息，只有在用户手动订阅行情时才能获取。因此需要在主界面上先手动订阅合约行情，再启动模块。

成功连接交易接口后，在菜单栏中点击【功能】-> 【价差交易】，或者点击左侧按钮栏的图标：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/spread_trading/1.png)

即可进入价差交易模块的UI界面，如下图所示：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/spread_trading/2.png)

该界面由两部分组成：

- 交易部分（界面左侧）：包括价差创建、手动交易和自动交易功能。在创建好价差合约后，可以通过手动交易来调整仓位，也可以调用价差策略实现自动交易；
- 监控部分（界面右侧）：包括【价差】、【日志】、【算法】和【策略】组件。可以分别查看实时价差合约行情信息，日志组件输出信息，价差算法和价差策略的执行情况。


## 创建价差合约

### 查询合约

在创建价差合约前，用户可以通过【查询合约】功能，寻找可以组成价差的合约：

- 在VN Trader菜单栏中点击【帮助】-> 【查询合约】按钮，弹出合约查询界面，如下图所示：
![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/spread_trading/3.png)
- 在界面中找到可用于组成价差交易的合约；
- 本文档以豆油期货的跨期套利来展示，即交易y2105.DCE（豆油期货21年5月到期合约）和y2109.DCE（豆油期货21年12月到期合约）。

### 构建价差合约

在价差交易的界面左侧，点击【价差创建】按钮，弹出创建价差界面，如下图所示：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/spread_trading/4.png)

在创建价差合约时，需要配置相关参数，各参数要求如下：

- 【价差名称】指用户定义的价差合约名称；
  - 价差名称不能重名；
- 【主动腿代码】指价差盘口价格满足条件时，先发出的那条腿的本地代码。
  - 格式为vt_symbol（合约代码 + 交易所名称）；
  - 必须是下面的【腿】选项中的一项；
- 【最小交易量】指最小交易手数；
- 【腿】包含构建价差合约的主动腿与被动腿，由【本地代码】，【价格乘数】，【交易乘数】，【合约模式】组成：
  - 合约代码格式为vt_symbol；
  - 一般来说，价差交易原则上是主动腿完成交易后，立刻用被动腿进行对冲，故主动腿一般选择较为不活跃的合约，价格乘数和交易乘数均为正；被动腿一般选择较为活跃的合约，价格乘数和交易乘数均为负；
  - 反向合约是只有数字货币市场才有的一种特殊衍生品合约规则，指用计价法币来标识价格，用数字货币来结算盈亏的衍生品合约。正向合约是指除反向合约外，其他所有的金融市场（股票、期货、期权等）采用的规则；
- 设置好价差合约的参数后，点击下方的【创建价差】按钮。

在豆油期货跨期套利示例中，其价格乘数和交易乘数均为1：1，即价差= y2105 - y2019；买入1手价差等于买入1手y2105，同时卖出1手y2109完成对冲。

请注意，在多条腿并且期货合约规模不等时，构建价差合约会相对困难一些，如构建虚拟钢厂套利所用到的价差合约时，计算公式如下：

- 螺纹钢生产技艺是16吨铁矿石加上5吨焦炭练成10吨螺纹钢。
- 基于价格乘数的价差spread = 1* RB - 1.6\*I  - 0.5\*O。
- 但是由于螺纹是10吨/手，铁矿石和焦炭都是100吨/手，所以他们交易乘数是1：10：10；
- 故基于最大公约数规则，其实际交易手数关系是每买入100手螺纹钢（1000吨），需要卖出16手铁矿石（1600吨）和5手焦炭（500吨）完成对冲。

### 构建灵活价差合约

2.1.8之后的版本中，价差交易模块支持更灵活的价差计算公式（例如A/B、A-B*C等），同时允许引入不参与交易的定价腿，满足复杂境内外套利价差需要考虑汇率和税率等因素的需求。

在价差交易的界面左侧，点击【灵活价差创建】按钮，弹出创建灵活价差的窗口，如下图所示：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/spread_trading/5.png)

其中，各参数的对应含义如下：

- 【价差名称】指用户定义的价差合约名称；
  - 价差名称不能重名；
- 【主动腿代码】指价差盘口价格满足条件时，先发出的那条腿的本地代码；
  - 格式为vt_symbol（合约代码 + 交易所名称）；
  - 必须是下面的【A、B、C、D、E】选项中的一项；
- 【最小交易量】指最小交易手数；
- 【价格公式】指价差合约的计算公式；
  - 支持任何Python内置数学函数；
  - 注意其中的变量只能是A、B、C、D、E（不需要都用）；
- 【A、B、C、D、E】包含构建价差合约的主动腿与被动腿，也可以引入不参与交易的定价腿，由【合约代码】，【交易方向】，【交易乘数】，【合约模式】组成；
  - 合约代码为公式中的变量所对应的合约本地代码（vt_symbol）；
  - 一般来说，价差交易原则上是主动腿完成交易后，立刻用被动腿进行对冲，故主动腿一般选择较为不活跃的合约，价格乘数和交易乘数均为正；被动腿一般选择较为活跃的合约，价格乘数和交易乘数均为负；
  - 反向合约是只有数字货币市场才有的一种特殊衍生品合约规则，指用计价法币来标识价格，用数字货币来结算盈亏的衍生品合约。正向合约是指除反向合约外，其他所有的金融市场（股票、期货、期权等）采用的规则；
  - 不用的变量留空即可；
- 设置好灵活价差合约的参数后，点击下方的【创建价差】按钮，即可成功创建灵活价差合约。

### 监控价差合约

价差合约创建完毕，监控界面中的【日志】组件会输出"价差创建成功"；【价差】组件也会展示价差合约的实时行情，如下图所示：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/spread_trading/6.png)

在豆油期货价差交易示例中，【价差】组件的各字段含义如下所示：

- 【买价】= y2105买一价 - y2109卖一价；
- 【买量】= min（y2105买一量，y2109卖一量），取最小值用于保证各合约能均能成交；
- 【卖价】= y2105卖一价 - y2109买一价；
- 【卖量】= min（y2105卖一量，y2109买一量）。


## 手动交易

假设当前豆油期货价差合约买价为662，卖价为666，并且在大周期上，价差围绕0上下波动。

价差交易的盈利在于高抛低吸，即在低位，如-300买入豆油期货价差合约，在高位，如+800卖出价差合约，平仓获利离场。由于不能立刻成交，所以其默认执行算法SpreadTaker（主动对价成交算法）会每隔一段时间进行委托操作，一般是以超价的限价单的形式发出委托。

下面通过2个例子，分别是发出委托立即成交和发出委托等待成交来具体介绍手动交易的操作情况：

### 发出委托立即成交

假设目标价差合约价格为670，我们以超价5元的形式，即675的价位发出买入限价单，如下图所示：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/spread_trading/2-7.png)

由于限价单（675）价位高于当前卖价（664），所以委托立刻成交，如下图所示。

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/spread_trading/8.png)

此时各监控组件状态如下所示：

- 【日志】组件显示买入y_05_09价差合约的顺序是：发出y2105多头委托 -> y2105委托成交 -> 发出y2109空头委托 -> y2109委托成交。价差交易必须遵循的逻辑是主动腿成交后，才去用被动腿来对冲头寸，并且对冲必须尽可能及时。这也为什么一般被动腿选择较为活跃合约的原因。
- 【价差】组件显示买入1手豆油期货价差合约成交后，【净仓】从0变成1。实际上，VN Trader【持仓】组件显示，y2105合约多头持仓1手，y2109合约空头持仓1手。
- 【算法】组件显示本次委托SpreadTaker算法执行情况：成交数量1手，委托状态是全部成交。

### 发出委托等待成交

以-300的价位发出限价买入指令，由于当前买价卖价分别位于662和666，所以委托状态显示“未成交”，如下图所示：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/spread_trading/9.png)

此时各监控组件状态如下所示：

- 【日志】组件显示本次算法即SpreadTaker_000002已经启动，但由于价格没有触发到目标价位，算法在循环读秒中处于等待状态；
- 【算法】组件显示其委托状态为"未成交"，要结束算法只需鼠标双击【SpreadTaker_000002】单元格即可。

仅当卖价低于-300时，才出发该限价单，已超价5元，即-295去主动成交。

### 撤销委托

 鼠标双击【SpreadTaker_000002】单元格，即可结束该算法。此时【日志】组件输出“算法已停止”，【算法】组件显示委托状态由“未成交”变成“已撤销”，如下图所示。

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/spread_trading/10.png)


## 自动交易

### 添加策略

在左侧的下拉框中选择要交易的策略名称，，如BasicSpreadStrategy，点击【添加策略】按钮，即可弹出以下界面：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/spread_trading/11.png)

其中，相关参数解释如下：

- 【strategy_name】为用户自定义的策略实例名称，这里是test；
  - 策略实例名称不能重名；
- 【spread_name】为用于交易的价差合约，这里是y_05_09；
  - 一定要是价差组件可以查询到的价差合约；
- 显示的参数名是策略里写在parameters列表中的参数名；
  - 默认数值为策略里的参数的默认值；
  - 由上图可观察到，参数名后面<>括号中显示的是该参数的数据类型，在填写参数时应遵循相应的数据类型。其中，<class 'str'>是字符串、<class 'int'>是整数、<class 'float'>是浮点数；
  - 请注意，如果某个参数可能会调整至有小数位的数值，而默认参数值是整数（比如1）。请在编写策略时，把默认参数值设为浮点数（比如1.0）。否则策略会默认该项参数为整数，在后续【编辑】策略实例参数时，会只允许填进整数。  

以BasicSpreadStrategy为例，该策略的各参数含义如下：

- 【buy_price】为买入开仓阈值，图中是-300，即当价格跌破-300时，执行委托；
- 【sell_price】为卖出平仓阈值，图中是400，即当价格回升到400时，执行委托；
- 【short_price】为卖出开仓阈值，图中是800，即当价格上涨到800时，执行委托；
- 【cover_price】为买入平仓阈值，图中是600，即当价格下跌到600时，执行委托；
- 【max_pos】为主动腿委托数量；
- 【payup】为超价的数值;
- 【interval】为时间间隔，即每隔一段时间，会发出委托。

最后，点击【添加】按钮完成策略实例的创建。添加成功后，策略组件界面如下图所示：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/spread_trading/12.png)


### 启动策略

添加策略完毕，依次点击【初始化】和【启动】按钮即可启动策略。成功启动后，【日志】组件输出“算法已启动”，如下图所示：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/spread_trading/13.png)


此时，【算法】组件显示，test策略调用SpreadTaker算法，分别在600和-300的位子上挂上买入和卖出委托；由于实际价格没有达到这2个阈值，故委托一直挂着，其委托状态为"未成交"。

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/spread_trading/14.png)

### 停止策略

若要停止策略，点击策略实例下的【停止】按钮，即可停止该策略实例的自动交易。【日志】组件输出“算法已停止”，如下图所示：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/spread_trading/15.png)

【算法】组件中算法状态变为“已撤销”，如下图所示：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/spread_trading/16.png)

【策略】组件中“trading”字段从“True”变为“False”，如下图所示：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/spread_trading/17.png)

### 编辑策略

如果创建策略实例之后，想要编辑某个策略实例的参数（若已启动策略，需要先点击策略实例下的【停止】按钮，停止策略），可以点击该策略实例下的【编辑】按钮，会弹出参数编辑对话框，以供修改策略参数，如下图所示：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/spread_trading/18.png)

编辑完策略参数之后，点击下方的【确定】按钮，相应的修改会立即更新在参数表格中。

### 移除策略

如果创建策略实例之后，想要移除某个策略实例（若已启动策略，需要先点击策略实例下的【停止】按钮，停止策略），可以点击该策略实例下的【移除】按钮。移除成功后，图形界面左侧的策略监控组件中将不会再显示该策略实例的信息。

### 批量操作

如果有多个需要运行的价差策略实例，可以使用界面左下方的【全部初始化】、【全部启动】和【全部停止】功能来执行盘前批量初始化、启动策略实例以及盘后批量停止策略实例的操作。

## 价差交易策略模板

价差交易策略模板提供完整的信号生成和委托管理功能，用户可以基于该模板(位于vnpy.app.spread_trading.template中)自行开发策略。

用户自行开发的策略可以放在用户运行文件夹下的strategies文件夹内。
请注意，策略文件命名采用下划线模式，如basic_spread_strategy.py，而策略类命名采用驼峰式，如BasicSpreadStrategy。

目前，vnpy官方提供两个价差策略，即BasicSpreadStrategy和StatisticalArbitrageStrategy，本文档通过BasicSpreadStrategy策略进行示例。

BasicSpreadStrategy策略逻辑假设价差满足均值回归，即价差围绕某个固定数值波动，并基于预先设置好的阈值来发出委托，具体策略逻辑如下：

- 在价差合约的价格低位买入开仓（BUY），然后在接近均值时候卖出平仓（SELL）；
- 在合约价格高位卖出开仓（SHORT），然后在价格走低接近均值买入平仓（COVER）。

若价差均值并不是围绕某个固定数值波动，或者能够持续走出趋势，则需要更加复杂的策略，如价差的布林带策略等等。这些个性化策略，用户可以基于SpreadStrategyTemplate策略模板自己实现。

在基于价差交易策略模板编写策略逻辑之前，需要在策略文件的顶部载入需要用到的内部组件，如下方代码所示：

```
from datetime import datetime
from vnpy.app.spread_trading import (
    SpreadStrategyTemplate,
    SpreadAlgoTemplate,
    SpreadData,
    OrderData,
    TradeData
)
```

其中，SpreadStrategyTemplate和SpreadAlgoTemplate是价差交易策略模板和价差算法模板，SpreadData、OrderData和TradeData是储存对应信息的数据容器。

### 策略参数与变量

在策略类的下方，可以设置策略的作者（author），参数（parameters）以及变量（variables），如下方代码所示：

```
    author = "用Python的交易员"

    buy_price = 0.0
    sell_price = 0.0
    cover_price = 0.0
    short_price = 0.0
    max_pos = 0.0
    payup = 10
    interval = 5
    start_time = "9:00:00"
    end_time = "15:00:00"

    spread_pos = 0.0
    update_time = None
    buy_algoid = ""
    sell_algoid = ""
    short_algoid = ""
    cover_algoid = ""
    
    parameters = [
        "buy_price",
        "sell_price",
        "cover_price",
        "short_price",
        "max_pos",
        "payup",
        "interval"
    ]
    variables = [
        "spread_pos",
        "update_time",
        "buy_algoid",
        "sell_algoid",
        "short_algoid",
        "cover_algoid",
    ]
```

虽然策略的参数和变量都从属于策略类，但策略参数是固定的（由交易员从外部指定），而策略变量则在交易的过程中随着策略的状态变化，所以策略变量一开始只需要初始化为对应的基础类型。例如：整数设为0，浮点数设为0.0，而字符串则设为""。

如果需要价差交易模块引擎在运行过程中，将策略参数和变量在UI界面显示，并在数据刷新、停止策略时保存其数值，则需把参数和变量的名字以字符串的数据类型添加进parameters和variables列表里。

请注意，该列表只能接受参数和变量以str、int、float和bool四种数据类型传入。如果策略里需要用到其他数据类型的参数与变量，请把该参数或变量的定义放到__init__函数下。

### 类的初始化

入参：strategy_engine, strategy_name: str, spread: SpreadData, setting: dict

出参：无

__init__函数是策略类的构造函数，需要与继承的SpreadStrategyTemplate保持一致。

在这个继承的策略类里，初始化一般分两步，如下方代码所示：

1. 通过super( )的方法继承SpreadStrategyTemplate，在__init__( )函数中传入策略引擎、策略名称、价差以及参数设置。（以上参数均由策略引擎在使用策略类创建策略实例时自动传入，用户无需进行设置）；

2. 传入起止时间，策略仅允许在起止时间段内交易。
```
def __init__(
    self,
    strategy_engine,
    strategy_name: str,
    spread: SpreadData,
    setting: dict
):
    """"""
    super().__init__(
        strategy_engine, strategy_name, spread, setting
    )

    self.start_t = datetime.strptime(self.start_time, "%H:%M:%S").time()
    self.end_t = datetime.strptime(self.end_time, "%H:%M:%S").time()
```

### 策略的回调函数

SpreadStrategyTemplate中以on开头的函数称为回调函数，在编写策略的过程中能够用来接收价差行情或者接收状态更新。回调函数的作用是当某一个事件发生的时候，策略里的这类函数会被价差交易策略引擎自动调用（无需在策略中主动操作）。回调函数按其功能可分为以下三类：

**策略实例状态控制**（所有策略都需要）

on_init

入参：无

出参：无

初始化策略时on_init函数会被调用，默认写法是调用write_log函数输出“策略初始化”日志。

on_start

入参：无

出参：无

启动策略时on_start函数会被调用，默认写法是调用write_log函数输出“策略启动”日志。

调用策略的on_start函数启动策略后，策略的trading状态变为【True】，此时策略才能够发出交易信号。

on_stop

入参：无

出参：无

停止策略时on_stop函数会被调用，默认写法是调用write_log函数输出“策略停止”日志，同时还原策略的变量。

**订单状态推送**

以下函数在策略中可以直接pass，其具体逻辑应用交给价差交易引擎负责。

on_spread_pos

入参：无

出参：无

收到持有仓位更新时on_spread_pos函数会被调用。

on_spread_algo

入参：algo: SpreadAlgoTemplate

出参：无

收到算法状态更新时on_spread_algo函数会被调用。

on_order

入参：order: OrderData

出参：无

收到策略委托回报时on_order函数会被调用。

on_trade

入参：trade: TradeData

出参：无
收到策略成交回报时on_trade函数会被调用。

**检测仓位、发出交易信号**

on_spread_data

入参：无

出参：无

BasicSpreadStrategy策略逻辑主要在on_spread_data()函数上。执行逻辑是先检测仓位：

- 若无仓位，分别发出买入开仓和卖出开仓委托，然后检测若存在平仓委托，调用stop_algo()函数撤销；
- 若持有多头仓位，先发出卖出平仓委托，然后检测若存在买入开仓委托，撤单处理；
- 若持有空头仓位，先发出买入平仓委托，然后检测若存在卖出开仓委托，撤单处理。

```
def on_spread_data(self):
    """
    Callback when spread price is updated.
    """
    self.spread_pos = self.get_spread_pos()

    # No position
    if not self.spread_pos:
        # Start open algos
        if not self.buy_algoid:
            self.buy_algoid = self.start_long_algo(
                self.buy_price, self.max_pos, self.payup, self.interval
            )

        if not self.short_algoid:
            self.short_algoid = self.start_short_algo(
                self.short_price, self.max_pos, self.payup, self.interval
            )

        # Stop close algos
        if self.sell_algoid:
            self.stop_algo(self.sell_algoid)

        if self.cover_algoid:
            self.stop_algo(self.cover_algoid)

    # Long position
    elif self.spread_pos > 0:
        # Start sell close algo
        if not self.sell_algoid:
            self.sell_algoid = self.start_short_algo(
                self.sell_price, self.spread_pos, self.payup, self.interval
            )

        # Stop buy open algo
        if self.buy_algoid:
            self.stop_algo(self.buy_algoid)

    # Short position
    elif self.spread_pos < 0:
        # Start cover close algo
        if not self.cover_algoid:
            self.cover_algoid = self.start_long_algo(
                self.cover_price, abs(
                    self.spread_pos), self.payup, self.interval
            )

        # Stop short open algo
        if self.short_algoid:
            self.stop_algo(self.short_algoid)

    self.put_event()
```

### 策略的主动函数

stop_open_algos和stop_close_algos都是策略内部的负责撤单的交易请求类函数。

stop_open_algos

入参：无

出参：无

负责撤销开仓委托。

stop_close_algos

入参：无

出参：无

负责撤销平仓委托。

