# 期权策略交易

OptionStrategy是用于**期权策略交易**的功能模块，用户可以通过其UI界面操作来便捷完成策略初始化、策略启动、策略停止、策略参数编辑以及策略移除等任务。


## 主要优势

OptionStrategy模块针对复杂期权策略，提供了ContractManager组件用于获取合约信息数据、按照交易日逐日加载当日的全量合约数据进行回放并提供了用于多层期权数据映射缓存的数据结构。


## 启动模块

OptionStrategy模块需要启动之前通过【策略应用】标签页加载。

启动登录VeighNa Elite Trader后，启动模块之前，请先连接交易接口。看到VeighNa Elite Trader主界面【日志】栏输出“合约信息查询成功”之后再启动模块。

请注意，IB接口因为登录时无法自动获取所有的合约信息，只有在用户手动订阅行情时才能获取。因此需要在主界面上先行手动订阅合约行情，再启动模块。

成功连接交易接口后，在菜单栏中点击【功能】-> 【期权策略交易】，或者点击左侧按钮栏的图标：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/elite/optionstrategy/1.png)

即可进入期权策略交易模块的UI界面。

如果配置了数据服务，打开多进程组合策略模块时会自动执行数据服务登录初始化。若成功登录，则会输出“数据服务初始化成功”的日志，如下图所示：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/elite/optionstrategy/2.png)


## 策略文件目录

<span id="jump">

对于用户自行开发的策略，需要放到VeighNa Elite Trader运行时目录下的**strategies**目录中，才能被识别加载。具体的运行时目录路径，可以在VeighNa Elite Trader主界面顶部的标题栏查看。

对于在Windows上默认安装的用户来说，放置策略的strategies目录路径通常为：

```
C:\Users\Administrator\strategies
```

其中Administrator为当前登录Windows的系统用户名。

</span>


## 创建策略实例

用户可以基于编写好的组合策略模板（类）来创建不同的策略实例（对象）。

在左上角的下拉框中选择要交易的策略名称，如下图所示：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/elite/optionstrategy/3.png)

请注意，显示的策略名称是**策略类**（驼峰式命名）的名字，而不是策略文件（下划线模式命名）的名字。

选择好策略类之后，点击【添加策略】，会弹出添加策略对话框，如下图所示：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/elite/optionstrategy/4.png)

在创建策略实例时，需要配置相关参数，各参数要求如下：

- 实例名称
  - 实例名称不能重名；
- 参数设置
  - 显示的参数名称是策略中使用Parameter辅助类定义的参数，如下所示：
    - 期权产品代码（一定要是实盘交易系统中可以查到的合约上的期权产品名称）
    - 委托超价比例
  - 默认数值为策略中的参数的默认值；
  - 由上图可观察到，参数名后面<>括号中显示的是该参数的数据类型，在填写参数时应遵循相应的数据类型。其中，<class 'str'>是字符串、<class 'int'>是整数、<class 'float'>是浮点数；
  - 请注意，如果某个参数可能会调整至有小数位的数值，而默认参数值是整数（比如1）。请在编写策略时，把默认参数值设为浮点数（比如1.0）。否则策略会默认该项参数为整数，在后续【编辑】策略实例参数时，会只允许填进整数。

参数配置完成后，点击【添加】按钮，则开始创建策略实例。创建成功后可在左侧的策略监控组件中看到该策略实例，如下图所示：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/elite/optionstrategy/5.png)

策略监控组件顶部显示的是策略实例名、策略类名以及策略作者名（在策略里定义的author）。顶部按钮用于控制和管理策略实例，第一行表格显示了策略内部的参数信息（参数名需要在策略中使用Parameter辅助类定义，图形界面才会显示），第二行表格则显示了策略运行过程中的变量信息（变量名需要在策略中使用Variables辅助类定义，图形界面才会显示）。【inited】字段表示当前策略的初始化状态（是否已经完成了历史数据回放），【trading】字段表示策略当前是否能够开始交易。

从上图可观察到，此时该策略实例的【inited】和【trading】状态都为【False】。说明该策略实例还没有初始化，也还不能发出交易信号。

策略实例创建成功后，该策略实例的配置信息会被保存到.vntrader文件夹下的option_strategy_setting.json文件中。


## 初始化策略

策略实例创建成功后，就可以对该实例进行初始化了。点击该策略实例下的【初始化】按钮，若初始化成功，则如下图所示：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/elite/optionstrategy/6.png)

初始化完成后，可观察到此时该策略实例的【inited】状态已经为【True】。说明该策略实例已经完成初始化了。【trading】状态还是为【False】，说明此时该策略实例还不能开始自动交易。

## 启动策略

策略实例初始化成功，【inited】状态为【True】时，才能启动该策略的自动交易功能。点击该策略实例下的【启动】按钮，即可启动该策略实例。成功后如下图所示：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/elite/optionstrategy/7.png)

可观察到此时该策略实例的【inited】和【trading】状态都为【True】。说明此时该策略实例已经完成了初始化函数中指定合约的行情订阅，而且此时策略内部的交易请求类函数（buy/sell/short/cover/cancel_order等），以及信息输出类函数（send_email/put_event等），才会真正执行并发出对应的请求指令到底层接口中（真正执行交易）。

在上一步策略初始化的过程中，尽管策略同样在接收（历史）数据（若初始化函数中调用了load_bars函数），并调用对应的功能函数，但因为【trading】状态为【False】，所以并不会有任何真正的委托下单操作或者交易相关的日志信息输出。

如果启动之后，策略发出了委托，可以去VeighNa Elite Trader主界面【委托】栏查看委托订单细节。


## 停止策略

如果启动策略之后，由于某些情况（如到了市场收盘时间，或盘中遇到紧急情况）想要停止、编辑或者移除策略，可以点击策略实例下的【停止】按钮，即可停止该策略实例的自动交易。成功后如下图所示：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/elite/optionstrategy/8.png)

期权策略引擎会自动将该策略之前发出的所有活动委托全部撤销，以保证在策略停止后不会有失去控制的委托存在。同时该策略实例最新的变量信息会被保存到.vntrader文件夹下的option_strategy_data.json文件中。

此时可观察到该策略实例的【trading】状态已变为【False】，说明此时该策略实例已经停止自动交易了。

在期权策略的实盘交易过程中，正常情况应该让策略在整个交易时段中都自动运行，尽量不要有额外的暂停重启类操作。对于国内期货市场来说，应该在交易时段开始前，启动策略的自动交易，然后直到收盘后，再关闭自动交易。因为现在CTP夜盘收盘后也会关闭系统，早上开盘前重启，所以夜盘收盘后也需要停止策略，关闭VeighNa Elite Trader了。


## 编辑策略

如果创建策略实例之后，想要编辑某个策略实例的参数（若已启动策略，需要先点击策略实例下的【停止】按钮，停止策略），可以点击该策略实例下的【编辑】按钮，会弹出参数编辑对话框，以供修改策略参数。如下图所示：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/elite/optionstrategy/9.png)

编辑完策略参数之后，点击下方的【确定】按钮，相应的修改会立即更新在参数表格中，如下图所示：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/elite/optionstrategy/10.png)

但是策略实例的交易合约代码无法修改，同时修改完后也不会重新执行初始化操作。也请注意，此时修改的只是.vntrader文件夹下option_strategy_setting.json文件中该策略实例的参数值，并没有修改原策略文件下的参数。

若盘中编辑后想要再次启动策略，点击策略实例下的【启动】按钮即可再次启动该策略实例，如下图所示：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/elite/optionstrategy/11.png)


## 移除策略

如果创建策略实例之后，想要移除某个策略实例（若已启动策略，需要先点击策略实例下的【停止】按钮，停止策略），可以点击该策略实例下的【移除】按钮。移除成功后，图形界面左侧的策略监控组件中将不会再显示该策略实例的信息，如下图所示：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/elite/optionstrategy/12.png)

此时.vntrader文件夹下的option_strategy_setting.json文件也移除了该策略实例的配置信息。


## 状态跟踪

如果想要通过图形界面跟踪策略的状态，有两种方式：

1. 调用put_event函数

   策略实例中所有的的变量信息，都需要把变量名写在策略的variables列表中，才能在图形界面显示。如果想跟踪变量的状态变化，则需要在策略中调用put_event函数，界面上才会进行数据刷新。

   有时用户会发现自己写的策略无论跑多久，变量信息都不发生变化，这种情况请检查策略中是否漏掉了对put_event函数的调用。

2. 调用write_log函数

   如果不仅想观察到变量信息的状态变化，还想根据策略的状态输出基于自己需求的个性化的日志，可以在策略中调用write_log函数，进行日志输出。


## 运行日志

### 日志内容

期权策略策略模块UI界面上输出的日志有两个来源，分别是策略引擎和策略实例。

**引擎日志**

策略引擎一般输出的是全局信息。下图中除了策略实例名后加冒号的内容之外，都是策略引擎输出的日志。

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/elite/optionstrategy/13.png)

**策略日志**

如果在策略中调用了write_log函数，那么日志内容就会通过策略日志输出。下图红框里的内容是策略实例输出的策略日志。冒号前是策略实例的名称，冒号后是write_log函数输出的内容。

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/elite/optionstrategy/14.png)

### 清空操作

如果想要清空期权策略UI界面上的日志输出，可以点击右上角的【清空日志】按钮，则可一键清空该界面上已输出的日志。

点击【清空日志】前，如下图所示：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/elite/optionstrategy/12.png)

点击【清空日志】后，如下图所示：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/elite/optionstrategy/15.png)


## 批量操作

在策略经过充分测试，实盘运行较为稳定，不需要经常进行调整的情况下，如果有多个需要运行的组合策略实例，可以使用界面右上角的【全部初始化】、【全部启动】和【全部停止】功能来执行盘前批量初始化、启动策略实例以及盘后批量停止策略实例的操作。


## 期权策略模板

期权策略模板提供了信号生成和委托管理功能，用户可以基于该模板自行开发期权策略。

用户自行开发的策略可以放在用户运行文件夹下的[strategies](#jump)文件夹内。

请注意：
   - 策略文件命名采用下划线模式，如io_strategy.py，而策略类命名采用驼峰式，如IoStrategy。

   - 自建策略的类名不要与示例策略的类名重合。如果重合了，图形界面上只会显示一个策略类名。

### StrategyTemplate

VeighNa Elite Trader的期权策略交易模块提供了StrategyTemplate专业期权策略模板，以实现复杂的期权策略开发。

### 策略引擎调用的函数

StrategyTemplate中的update_setting函数和该函数后面三个以get开头的函数（get_parameters、get_variables和get_data）以及update_trade和update_order函数，都是策略引擎去负责调用的函数，一般在策略编写的时候是不需要调用的。

### 策略的回调函数

StrategyTemplate中以on开头的函数称为回调函数，在编写策略的过程中能够用来接收数据或者接收状态更新。回调函数的作用是当某一个事件发生的时候，策略里的这类函数会被期权策略引擎自动调用（无需在策略中主动操作）。回调函数按其功能可分为以下两类：

#### 策略实例状态控制（所有策略都需要）

**on_init**

* 入参：无

* 出参：无

初始化策略时on_init函数会被调用，默认写法是先调用write_log函数输出“策略初始化”日志，再调用subcribe_options函数订阅期权行情（如有需要还可调用subscribe_data函数订阅标的物行情）。

如有需要进行全局缓存的变量，可以在on_init函数中对缓存容器进行定义。

若需读取历史数据进行指标计算，也可调用load_bars函数加载历史数据并进行推送。

策略初始化时，策略的inited和trading状态都为【False】，不能发出交易信号。调用完on_init函数之后，策略的inited状态才变为【True】，策略初始化才完成。

**on_start**

* 入参：无

* 出参：无

启动策略时on_start函数会被调用，默认写法是调用write_log函数输出“策略启动”日志。

调用策略的on_start函数启动策略后，策略的trading状态变为【True】，此时策略才能够发出交易信号。

**on_stop**

* 入参：无

* 出参：无

停止策略时on_stop函数会被调用，默认写法是调用write_log函数输出“策略停止”日志。

调用策略的on_stop函数停止策略后，策略的trading状态变为【False】，此时策略就不会发出交易信号了。

#### 接收数据、计算指标、发出交易信号

**on_tick**

* 入参：tick: TickData

* 出参：无

当策略收到实盘中最新的Tick数据的行情推送时，on_tick函数会被调用。默认写法是先决定策略的执行频率（可通过tick的datetime判断过滤），再定时将缓存的tick价格数据推送进封装的策略执行函数中，最后将新收到的tick数据缓存至数据缓存容器中。

请注意，on_tick函数只在实盘中会被调用，回测不支持。

**on_bars**

* 入参：bars: Dict[str, BarData]

* 出参：无

当策略回测过程中收到最新的K线数据时，on_bars函数就会被调用。默认写法是将收到的K线价格数据推送进封装的策略执行函数中。

请注意，on_bars函数只在回测中会被调用，实盘不支持。

期权策略模块在接收K线推送时，是通过on_bars回调函数一次性接收该时间点上所有合约的K线数据，而不是通过on_bar函数一个个接收。

#### 委托状态更新

因为期权策略中需要对多合约同时下单交易，在回测时无法判断某一段K线内部每个合约委托成交的先后时间顺序，因此无法提供on_order和on_trade函数来获取委托成交推送，而只能在回调时通过get_pos来进行状态查询。

### 主动函数

**buy**：买入开仓（Direction：LONG，Offset：OPEN）

**sell**：卖出平仓（Direction：SHORT，Offset：CLOSE）

**short**：卖出开仓（Direction：SHORT，Offset：OPEN）

**cover**：买入平仓（Direction：LONG，Offset：CLOSE）

* 入参：vt_symbol: str, price: float, volume: float

* 出参：vt_orderids: List[str] / 无 

buy/sell/short/cover都是策略内部的负责发单的交易请求类函数。策略可以通过这些函数给策略引擎发送交易信号来达到下单的目的。

以下方buy函数的代码为例，可以看到，**具体要交易合约的代码**，价格和数量是必填的参数，锁仓转换和净仓转换则默认为False。也可以看到，函数内部收到传进来的参数之后就调用了StrategyTemplate里的send_order函数来发单（因为是buy指令，则自动把方向填成了LONG，开平填成了OPEN）。

请注意，如果向上期所发出平仓委托，因为该交易所必须指定平今、平昨，底层会对其平仓指令自动进行转换。因为上期所部分品种有平今优惠，所以默认是以平今优先的方式发出委托的（如果交易的标的在上期所平昨更优惠的话，可以自行在vnpy.trader.converter的convert_order_request_shfe函数中做适当的修改）。

**send_order**

* 入参：vt_symbol: str, direction: Direction, offset: Offset, price: float, volume: float

* 出参：vt_orderids: List[str] / 无

send_order函数是策略引擎调用的发送委托的函数。一般在策略编写的时候不需要单独调用。

实盘的时候，收到传进来的参数后，会调用round_to函数基于合约的pricetick和min_volume对委托的价格和数量进行处理。

请注意，要在策略启动之后，也就是策略的trading状态变为【True】之后，才能发出交易委托。如果策略的Trading状态为【False】时调用了该函数，只会返回[]。

**cancel_order**

* 入参：vt_orderid: str

* 出参：无

**cancel_all**

* 入参：无

* 出参：无

cancel_order和cancel_all都是负责撤单的交易请求类函数。cancel_order是撤掉策略内指定的活动委托，cancel_all是撤掉策略所有的活动委托。一般在策略编写的时候不需要单独调用，调用execute_trading函数时会自动调用cancel_all函数批量取消发出的活动委托。

请注意，要在策略启动之后，也就是策略的trading状态变为【True】之后，才能撤单。

**get_porftfolio**

* 入参：portfolio_name: str

* 出参：portfolio: PortfolioData

在策略里调用get_porftfolio函数，可以获取特定期权产品的期权组合。

**subscribe_options**

* 入参：portfolio_name: str

* 出参：res: bool

在策略里调用subscribe_options函数，可以订阅特定期权产品的期权组合行情。

若返回False，则说明底层没有获取到对应的期权合约信息。

**subscribe_data**

* 入参：vt_symbol: str

* 出参：res: bool

在策略里调用subscribe_data函数，可以订阅特定合约行情。

若返回False，则说明底层没有获取到对应的合约信息。

### 功能函数

以下为策略以外的功能函数：

**get_pos**

* 入参：vt_symbol: str

* 出参：int / 0 

在策略里调用get_pos函数，可以获取特定合约的持仓数据。

**write_log**

* 入参：msg: str

* 出参：无

在策略中调用write_log函数，可以进行指定内容的日志输出。

**load_bars**

* 入参：vt_symbol: str, days: int, interval: Interval

* 出参：bars: List[BarData] / 无

在策略中调用load_bars函数，可以在策略类初始化时获取指定合约的K线数据。

load_bars函数在实盘调用时，会先依次尝试通过交易接口、数据服务、数据库获取历史数据，直到获取历史数据或返回空。

**put_event**

* 入参：无

* 出参：无

在策略中调用put_event函数，可以通知图形界面刷新策略状态相关显示。可在封装的策略执行函数中调用。

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

**save_data**

* 入参：file_name: str, data: dict

* 出参：无

在策略中调用save_data函数，可以保存策略数据到指定文件。

**load_data**

* 入参：file_name: str

* 出参：无

在策略中调用load_data函数，可以从指定文件中加载策略数据。

**get_today**

* 入参：无

* 出参：无

在策略中调用get_today函数，可以获取当前日期。

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

**clear_targets**

* 入参：无

* 出参：int

在策略里调用clear_targets函数，可以清除缓存的合约目标仓位。

**execute_trading**

* 入参：price_data: Dict[str, float], percent_add: float

* 出参：无

在策略里调用execute_trading函数，可以基于设定的特定合约的目标仓位执行调仓交易。

execute_trading是基于设定的目标仓位和超价百分比用来执行交易的函数。委托下单和撤单已经被该函数接管，无需再在策略内进行下单和撤单操作。

execute_trading被调用之后，在函数内部会先撤销策略所有活动委托，然后根据策略目标和策略持仓的仓差（没有则不委托）进行委托。

请注意：只有当前price_data中有切片的合约，才会参与本次调仓交易的执行，从而保证非交易时段（没有行情推送）的合约不会错误发出委托。

### 策略所需数据容器

#### OptionData（期权数据）

##### 属性

 - vt_symbol: str（本地代码）
 - contractData: ContractData（合约信息）
 - strike: float（行权价）
 - price: float（最新价）
 - pos: float（净持仓）

#### ChainData（期权链数据）

##### 属性

 - symbol: str（标的物合约代码）
 - exchenge: Exchange（交易所）
 - expiry: datetime（期权到期日）
 - strikes: List[float]（期权行权价）
 - calls: Dict[float, OptionData]（看涨期权）
 - puts: Dict[float, OptionData]（看跌期权）
 - atm_strike：float (平值期权行权价)

##### 函数

- **add_contract**

  * 入参：contract: ContractData

  * 出参：option: OptionData

  调用add_contract函数，可以将指定期权合约信息添加到期权链实例的calls、puts、strikes里。

  一般只有PortfolioData调用add_contract函数时，ChainData的add_contract才会被调用。策略内无需调用该函数。

- **calculate_atm**

  * 入参：underlying_price: float

  * 出参：无

  调用calculate_atm函数，可以对平值期权的行权价进行计算并更新ChainData的atm_strike属性（如没有传入标的，则使用合成期货计算。否则使用标的合约的价格进行计算）。

  一般在策略里，封装的策略执行函数收到价格数据之后，会获取指定的portfolio，调用PortfolioData实例的update_price函数更新价格到期权组合。之后就可以调用指定ChainData实例的calculate_atm函数计算平值期权行权价了。

- **calculate_synthetic**

  * 入参：无

  * 出参：synthetic_price: float

  在ChainData实例有了atm_strike之后，调用calculate_synthetic函数可以计算合成期货的价格。

- **get_option_by_level**

  * 入参：cp: int, level: int

  * 出参：option: OptionData

  在ChainData实例有了atm_strike之后，调用get_option_by_level函数就可以基于平值期权在期权链上的位置根据传入的虚值程度查询期权了。

  请注意：cp大于0是查询看涨期权，cp小于0是查询看跌期权。level是期权的虚值档位。

#### PortfolioData

##### 属性

 - symbol: str（期权产品代码）
 - exchenge: Exchange（交易所）
 - chains: Dict[str, ChainData]（期权链）
 - chain_symbols: List[str]（每条期权链上的合约代码）
 - options: Dict[str, OptionData]（期权）

- **add_contract**

  * 入参：contract: ContractData

  * 出参：无

  调用add_contract函数，可以将指定期权合约信息添加到期权组合实例上期权链实例的calls、puts、strikes以及期权组合实例的options字典里。

- **get_chain_by_level**

  * 入参：level: int

  * 出参：chains: List[ChainData] / 无 

  调用get_chain_by_level函数，可以根据月份查询期权链。

  level参数传0是查询当月期权链。

- **update_price**

  * 入参：price_data: dict[str, float]

  * 出参：无

  调用update_price函数，可以更新收到的价格到指定的期权。

  一般price_data的key会设置成合约的vt_symbol。

- **update_pos**

  * 入参：pos_data: dict[str, int]

  * 出参：无

  调用update_price函数，可以更新策略的持仓数据到指定的期权。

  一般pos_data的key会设置成合约的vt_symbol。


## 策略回测

期权策略交易模块的策略回测参考代码如下所示：

```
engine = BacktestingEngine()

engine.set_parameters(
    interval=Interval.MINUTE,
    start=datetime(2023, 1, 1),
    end=datetime(2023, 11, 30),
    rate=0,
    slippage=0,
)

engine.add_strategy(IoStrategy, {})
engine.run_backtesting()
engine.calculate_result()
engine.calculate_statistics()
engine.show_chart()
```

- **set_parameters**

  * 入参：interval: Interval,  start: datetime, end: datetime, rate: float, slippage: float, capital: int = 1_000_000

  * 出参：无

  调用set_parameters函数，可以设置BacktestingEngine实例的回测外部参数。

- **add_strategy**

  * 入参：strategy_class: Type[StrategyTemplate], setting: dict

  * 出参：无

  调用add_strategy函数，可以添加期权策略实例和策略设置到BacktestingEngine实例上。

- **run_backtesting**

  * 入参：无

  * 出参：无

  调用run_backtesting函数，可以逐日执行回测任务。

  调用run_backtesting函数时，BacktestingEngine实例会按照交易日逐日加载当日的全量合约数据进行回放，并模拟实盘情况，每日对策略对象实例进行重新初始化。

  - 日内回测过程：先获取昨天收盘的策略仓位和价格数据，再更新数据到每日统计结果中。然后新建策略实例，还原策略仓位并执行策略初始化。此时可根据订阅情况加载历史数据（策略订阅的所有合约），然后执行策略启动和数据回放（处理委托撮合和历史数据推送）。回放完之后执行策略停止，获取收盘策略仓位并更新收盘数据到统计结果中。

- **calculate_result**

  * 入参：无

  * 出参：无

  调用calculate_result函数，可以计算策略实例的逐日盯市盈亏。

- **calculate_statistics**

  * 入参：无

  * 出参：无

  调用calculate_statistics函数，可以基于策略实例的逐日盯市盈亏计算并输出策略实例的统计指标。

- **show_chart**

  * 入参：无

  * 出参：无

  调用show_chart函数，可以基于策略实例的回测结果进行图表显示。

### 期权回测数据缓存

在创建回测引擎实例之后，在调用set_parameters函数的时候，如果给入参task_name赋值，则会创建指定名称的缓存文件。下次加载数据的时候可以直接读取。

- **list_cache**

  * 入参：无

  * 出参：list

  调用list_cache函数，可以返回回测数据缓存列表。

- **remove_cache**

  * 入参：cache: str

  * 出参：list

  调用remove_cache函数，可以删除指定缓存数据。
