# CtaStrategy - CTA策略模块

## 功能简介

CtaStrategy是用于**CTA策略实盘**的功能模块，用户可以通过图形界面操作来便捷完成策略初始化、策略启动、策略停止、策略参数编辑以及策略移除等任务。

## 加载启动

### VN Station加载

启动登录VN Station后，点击【VN Trader Pro】按钮，在配置对话框中的【上层应用】栏勾选【CtaStrategy】。

### 脚本加载

在启动脚本中添加如下代码：

```
# 写在顶部
from vnpy.app.cta_strategy import CtaStrategyApp

# 写在创建main_engine对象后
main_engine.add_app(CtaStrategyApp)
```


## 启动模块

<span id="jump">

对于用户自行开发的策略，需要放到VN Trader运行时目录下的**strategies**目录中，才能被识别加载。具体的运行时目录路径，可以在VN Trader主界面顶部的标题栏查看。

对于在Windows上默认安装的用户来说，放置策略的strategies目录路径通常为：

```
C:\Users\Administrator\strategies
```

其中Administrator为当前登录Windows的系统用户名。

</span>

在启动模块之前，请先连接交易接口（连接方法详见基本使用篇的连接接口部分）。看到VN Trader主界面【日志】栏输出“合约信息查询成功”之后再启动模块（IB接口因为登录时无法自动获取所有的合约信息，只有在用户手动订阅行情时才能获取。因此需要在主界面上先行手动订阅合约行情，再启动模块）。若查询成功，则如下图所示：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/cta_strategy/1.png)

启动VN Trader后，在菜单栏中点击【功能】-> 【数据管理】，或者点击左侧按钮栏的图标

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/cta_strategy/00.png)

即可进入该图形化的CTA策略界面，如下图所示：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/cta_strategy/2.png)

如果配置了[RQData](https://www.ricequant.com/welcome/purchase?utm_source=vnpy)数据服务（配置方法详见基本使用篇的全局配置部分），打开CtaStrategy时会自动执行RQData登录初始化。若成功登录则会输出“RQData数据接口初始化成功”的日志，如下图所示：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/cta_strategy/3.png)


## 添加策略

用户可以基于编写好的CTA策略模板（类）来创建不同的策略实例（对象）。策略实例的好处在于，同一个策略可以同时去运行多个品种合约，并且每个实例的参数可以是不同的。

在左上角的下拉框中选择要交易的策略名称，如下图所示：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/cta_strategy/28.png)

请注意，显示的是**策略类**（驼峰式）的名字，而不是策略文件（下划线模式）的名字。

选择好策略类之后，点击【添加策略】，会弹出添加策略对话框。如下图所示：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/cta_strategy/5.png)

在创建实例的时候需要配置好相关的参数：

- 实例名称
  - 实例名称不能重名；
- 合约品种
  - 格式为vt_symbol（合约代码 + 交易所名称）；
  - 一定要是实盘交易系统中可以查到的合约名称；
  - 一般选择该期货品种当前流动性最好的月份，比如写本文时是2021年3月2日，此时的螺纹钢主力合约为rb2105.SHFE；
- 参数设置
  - 显示的参数名是策略里写在parameters列表中的参数名；
  - 默认数值为策略里的参数的默认值；
  - 由上图可观察到，参数名后面<>括号显示的是需要填进参数框的数据类型。<class 'str'>是字符串、<class 'int'>是整数、<class 'float'>是浮点数；
  - 请注意，如果某个参数可能会调整至有小数位的数值，而默认参数值是整数（比如1）。请在编写策略时，把默认参数值填成浮点数（比如1.0）。否则策略会默认该项参数为整数，在后续【编辑】策略实例参数时，会只能填进整数。

配置完毕后，点击【添加】按钮，则开始创建策略实例。成功后就能在左侧的策略监控组件中看到该策略实例了。如下图所示：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/cta_strategy/7.png)

顶部按钮用于控制和管理策略实例，第一行表格显示了策略内部的参数信息（参数名需要写在策略的parameters列表中图形界面才会显示），第二行表格则显示了策略运行过程中的变量信息（变量名需要写在策略的variables列表中图形界面才会显示）。【inited】字段表示当前策略的初始化状态（是否已经完成了历史数据回放），【trading】字段表示策略当前是否能够开始交易。

可观察到此时该策略实例的【inited】和【trading】状态都为【False】。说明此时该策略实例还没有初始化，也还不能发出交易信号。

策略实例创建成功后，该策略实例的配置信息会被保存到.vntrader文件夹下的cta_strategy_setting.json文件中。

### 创建失败

- 如果添加了同名的策略实例，则会创建失败，图形界面输出“创建策略失败，存在重名”的日志信息。如下图所示：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/cta_strategy/31.png)

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/cta_strategy/8.png)

- 如果合约品种没有填交易所名称，则会创建失败，图形界面输出“创建策略失败，本地代码缺失交易所后缀”的日志信息。如下图所示：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/cta_strategy/32.png)

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/cta_strategy/11.png)

- 如果合约品种的填交易所名称填错，则会创建失败，图形界面输出“创建策略失败，本地代码的交易所后缀不正确”的信息。如下图所示：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/cta_strategy/33.png)

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/cta_strategy/13.png)


## 管理策略

### 初始化

策略实例创建成功后，就可以对该实例进行初始化了。点击该策略实例下的【初始化】按钮，若初始化成功，则如下图所示：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/cta_strategy/6.png)

初始化过程中，主要按顺序完成了以下三步任务：

1. 获取历史数据

   为了确保策略内指标数值的准确性，每个策略实例都需要一定的历史数据来进行策略初始化。

   所以在初始化时，策略实例内部的load_bar函数会先去接口获取最新历史数据。如果接口不提供历史数据，那么就通过RQData（提供国内期货、股票以及期权的历史数据）来获取。RQData的数据服务提供盘中K线更新。即使在9点45分才启动策略，也能获取到之前从9点30开盘到9点45分之间的K线数据，提供给策略进行初始化计算，而不用担心数据缺失的问题。如果没有配置RQData数据服务的话，就会通过访问本地数据库查询。这种情况下，用户需要自己来保证数据库中的数据完整性（满足初始化需求）。比如通过DataRecorder录制，使用DataManager从CSV文件载入，或者使用其他数据服务来更新数据。

   具体载入数据的长度，取决于load_bar函数的参数控制（策略模板默认是10天）。数据载入后会以逐根K线（或者Tick）的方式推送给策略，实现内部变量的初始化计算，比如缓存K线序列、计算技术指标等。

2. 载入缓存变量

   量化策略在每天实盘运行的过程中，有些变量是纯粹只和行情数据相关的，这类变量通过加载历史数据回放就能得到正确的数值。另一类变量则可能是和交易状态相关的，如策略的持仓、移动止损的最高价跟踪等，这类变量需要缓存在硬盘上（退出程序时），第二天回放完历史数据后再读取还原，才能保证和之前交易状态的一致性。

   每次停止策略时，会自动将策略的variables列表对应的变量以及策略持仓缓存进.vntrader目录下的cta_strategy_data.json文件中，以便在下一次策略初始化时自动载入。

   注意在某些情况下，可能缓存的数据出现了偏差（比如手动平仓了），此时可以通过手动修改json文件来调整。

3. 订阅行情推送

   最后是获取该策略所交易合约的信息（基于vt_symbol），并订阅该合约的实时行情推送。如果实盘交易系统找不到该合约的信息，比如没有登录接口或者vt_symbol写错了，则会在日志模块中输出相应的报错信息。

以上三个步骤全部完成后，可观察到此时该策略实例的【inited】状态已经为【True】了, 且变量也都有了对应的数值（不再为0）。说明该策略实例已经调用过load_bar函数加载历史数据完成初始化了。【trading】状态还是为【False】，说明此时该策略实例还不能开始自动交易。

### 初始化失败

- 即使交易所填的是vn.py支持的交易所的名字，成功创建了策略实例。但是如果该合约名字输入错误（比如说大小写写错，合约与交易所对不上或者已经退市），导致实盘交易系统找不到该合约，则会初始化失败，图形界面输出“行情订阅失败，找不到合约”的日志。如下图所示：

  ![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/cta_strategy/14.png)

- 即使合约代码填写正确，成功创建了策略实例。但是如果此时还没有连接接口，或者接口合约信息查询合约操作还没有完成，导致实盘交易系统找不到该合约，也会初始化失败，图形界面输出“行情订阅失败，找不到合约”的日志。如下图所示：

  ![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/cta_strategy/15.png)

  如果出现了“行情订阅失败，找不到合约”这类问题，可以通过VN Trader的主界面点击【帮助】-【查询合约】进行查询，找到正确的合约信息。如下图所示：

  ![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/cta_strategy/34.png)

- 如果策略内用到了K线时间序列管理模块（ArrayManager）来计算变量指标的值，那么请确保历史数据的长度足够ArrayManager进行初始化（默认的ArrayManager需要100条数据才能初始化成功）。如果历史数据的长度不够ArrayManager初始化，即使图形界面上输出了日志“初始化完成”，该策略实例的初始化也是失败的。

  - 如果策略逻辑是基于示例策略中的一但ArrayManager没有初始化成功(if not am.inited)就返回的逻辑写的话，那么由下图可观察到，图形界面左侧的策略实例中基于ArrayManager计算的策略指标的值都是0。说明此时该策略实例虽然启动之后就可以开始自动交易了，但是因为ArrayManager没有初始化成功，策略内的逻辑每次走到ArrayManager初始化状态判断时就返回了，走不到计算指标进而发出交易信号的逻辑。该策略实例需要一直等到推进策略实例的数据足够ArrayManager初始化之后，才能满足ArrayManager初始化的这个判断条件，策略内才能真正发出交易信号。
  ![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/cta_strategy/16.png)

  - 如果策略逻辑不是基于示例策略中的一但ArrayManager没有初始化成功(if not am.inited)就返回的逻辑写的话，那么此时虽可观察到，图形界面左侧的策略实例中的策略指标有数值，而且此时启动可以发出交易信号，无需等待ArrayManager初始化完成。但是因为ArrayManager没有初始化成功，该策略实例计算出来的变量指标值会是不准确的，进而可能会发出不符合策略预期的交易信号。

### 启动

策略实例初始化成功，【inited】状态为【True】时，才能启动该策略的自动交易功能。点击该策略实例下的【启动】按钮，即可启动该策略实例。成功后如下图所示：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/cta_strategy/17.png)

可观察到此时该策略实例的【inited】和【trading】状态都为【True】。说明此时该策略实例已经调用过load_bar函数，完成了历史数据回放，而且此时策略内部的交易请求类函数（buy/sell/short/cover/cancel_order等），以及信息输出类函数（write_log/send_email等），才会真正执行并发出对应的请求指令到底层接口中（真正执行交易）。

在上一步策略初始化的过程中，尽管策略同样在接收（历史）数据，并调用对应的功能函数，但因为【trading】状态为【False】，所以并不会有任何真正的委托下单操作或者交易相关的日志信息输出。

如果启动之后，策略发出了限价单，可以去VN Trader主界面【委托】栏查看委托订单细节。如果策略发出了本地停止单，可以在图形化CTA策略界面右上方区域的停止单监控组件查看委托订单细节。

### 停止

如果启动策略之后，因为到了市场收盘时间，或者盘中遇到紧急情况，想要停止、编辑或者移除策略，可以点击策略实例下的【停止】按钮，即可停止该策略实例的自动交易。成功后如下图所示：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/cta_strategy/18.png)

CTA策略引擎会自动将该策略之前发出的所有活动委托全部撤销（保证在策略停止后不会有失去控制的委托存在），同时该策略实例最新的变量信息会被保存到.vntrader文件夹下的cta_strategy_data.json文件中。

此时可观察到该策略实例的【trading】状态已变为【False】，说明此时该策略实例已经停止自动交易了。

在CTA策略的实盘交易过程中，正常情况应该让策略在整个交易时段中都自动运行，尽量不要有额外的暂停重启类操作。对于国内期货市场来说，应该在交易时段开始前，启动策略的自动交易，然后直到收盘后，再关闭自动交易。因为现在CTP夜盘收盘后也会关闭系统，早上开盘前重启，所以夜盘收盘后也需要停止策略，关闭VN Trader了。

### 编辑

如果创建策略实例之后，想要编辑某个策略实例的参数，（若已启动策略，需要先点击策略实例下的【停止】按钮，停止策略）可以点击该策略实例下的【编辑】按钮，会弹出参数编辑对话框，以供修改策略参数。如下图所示：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/cta_strategy/39.png)

编辑完策略参数之后，点击下方的【确定】按钮，相应的修改会立即更新在参数表格中,如下图所示：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/cta_strategy/40.png)

但是策略实例的交易合约代码无法修改，同时修改完后也不会重新执行初始化操作。也请注意，此时修改的只是.vntrader文件夹下cta_strategy_setting.json文件中该策略实例的参数值，而没有修改原策略文件下的参数。

修改前，json文件如下图所示：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/cta_strategy/19.png)

修改后，json文件如下图所示：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/cta_strategy/20.png)

若盘中编辑后想要再次启动策略，点击策略实例下的【启动】按钮即可再次启动该略实例，如下图所示：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/cta_strategy/41.png)

### 移除

如果创建策略实例之后，想要移除某个策略实例，（若已启动策略，需要先点击策略实例下的【停止】按钮，停止策略）可以点击该策略实例下的【移除】按钮移除策略实例。移除成功后，图形界面左侧的策略监控组件中将不会再显示该策略实例的信息。如下图所示：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/cta_strategy/21.png)

此时.vntrader文件夹下的cta_strategy_setting.json文件也移除了该策略实例的配置信息。

### 状态跟踪

如果想要通过图形界面跟踪策略的状态，有两种方式：

1. 调用put_event函数

   策略实例中所有的的变量信息，都需要把变量名写在策略的variables列表中，才能在图形界面显示。如果想跟踪变量的状态变化，则需要在策略中调用put_event函数，界面上才会进行数据刷新。
   
   有时用户会发现自己写的策略无论跑多久，变量信息都不动，这种情况请检查策略中是否漏掉了对put_event函数的调用。

2. 调用write_log函数

   如果不仅仅想观察到变量信息的状态变化，还想根据策略的状态输出基于自己需求的个性化的日志，可以在策略中调用write_log函数，进行日志输出。


## 运行日志

### 日志内容

图形化CTA策略界面上输出的日志有两个来源，分别是CTA策略引擎和策略实例。

引擎日志

CTA策略引擎一般输出的都是全局的信息。下图中除了策略实例名后加冒号的内容之外，都是CTA策略引擎输出的日志。

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/cta_strategy/37.png)

策略日志

如果在策略中调用了write_log函数，那么日志内容就会通过策略日志输出。下图红框里的内容分别是两个不同的策略实例输出的策略日志。冒号前是策略实例的名称，冒号后的write_log函数输出的内容。

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/cta_strategy/38.png)

### 清空操作

如果想要清空图形化CTA策略界面上的日志输出，可以点击右上角的【清空日志】按钮，则可一键清空该界面上已输出的日志。

点击【清空日志】前，如下图所示：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/cta_strategy/21.png)

点击【清空日志】后，如下图所示：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/cta_strategy/23.png)


## 停止单

图形界面右上方区域的停止单监控组件，是用来跟踪所有CTA引擎内的本地停止单状态变化的。

因为不是所有接口都支持停止单，所以vn.py提供了本地停止单的功能。在交易接口不支持交易所停止单的前提下，用户依然可以通过策略的下单函数（buy/sell/short/cover）把stop参数填写为True，启用本地停止单功能。vn.py的本地停止单有三个特点：

1. 保存在本地电脑上，关机后则失效；
2. 只有交易员本人能够看到，不必担心泄露底牌；
3. 停止单触发有延时，导致一定的滑点。

停止单信息

在发出本地停止单后，图形界面右上方的监控组件就会显示停止单的委托细节。

本地停止单一共有【等待中】、【已触发】和【已撤销】三个状态，如下图所示：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/cta_strategy/35.png)

停止单刚发出时是处于【等待中】的状态。因为停止单的信息是记录在本地，没有发往交易所，所以此时主界面上【委托】栏不会有变化。

如果该停止单的委托价格被触发了，为了实现立即成交的目的，CTA策略引擎会立即以**涨跌停价**或者**盘口五档**的价格，去发出**限价**委托（所以建议本地停止单还是只用于流动性比较好的合约）。限价委托发出去之后，主界面上【委托】栏就会更新该订单的状态了，此时停止单状态也会变为【已触发】,【限价委托号】栏下也会填入该订单的限价委托号。

要注意，停止单界面显示的价格是本地停止单的触发价格，而不是发出限价单的价格。

如果停止单在被触发前就被策略取消了，那么该订单的状态就会变为【已撤销】。


## 批量操作

在策略经过充分测试，实盘跑得较为稳定，不需要经常进行调整的情况下。如果有多个需要运行的CTA策略实例，可以使用界面右上角的【全部初始化】、【全部启动】和【全部停止】功能来执行盘前批量初始化、启动策略实例以及盘后批量停止策略实例的操作。

### 全部初始化

在所有策略实例创建成功后，点击右上角的【全部初始化】按钮，则可批量初始化策略实例。

点击【全部初始化】前，如下图所示：
![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/cta_strategy/24.png)

点击【全部初始化】后，如下图所示：
![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/cta_strategy/25.png)

### 全部启动

在所有策略实例初始化成功后，点击右上角的【全部启动】按钮，则可批量启动策略实例，如下图所示：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/cta_strategy/26.png)

### 全部停止

在所有策略实例启动成功后，点击右上角的【全部停止】按钮，则可批量停止策略实例，如下图所示：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/cta_strategy/27.png)


## CTA策略模板（CtaTemplate）

CTA策略模板提供完整的信号生成和委托管理功能，用户可以基于该模板(位于vnpy.app.cta_strategy.template中)自行开发策略。

用户自行开发的策略可以放在用户运行文件夹下的[strategies](#jump)文件夹内。

请注意，策略文件命名是以下划线模式，如boll_channel_strategy.py；而策略类命名采用的是驼峰式，如BollChannelStrategy。

下面通过BollChannelStrategy策略示例，来展示策略开发的具体步骤：

在基于CTA策略模板编写策略逻辑之前，需要在.py文件的顶部载入需要用到的内部组件，如下方代码所示：

```
from vnpy.app.cta_strategy import (
    CtaTemplate,
    StopOrder,
    TickData,
    BarData,
    TradeData,
    OrderData,
    BarGenerator,
    ArrayManager,
)
```

### 策略参数与变量

在策略类的下方，可以对策略的作者（author），参数（parameters）以及变量（variables）进行定义，如下方代码所示：

```

    author = "用Python的交易员"

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

    parameters = [
        "boll_window",
        "boll_dev",
        "cci_window",
        "atr_window",
        "sl_multiplier",
        "fixed_size"
    ]
    variables = [
        "boll_up",
        "boll_down",
        "cci_value",
        "atr_value",
        "intra_trade_high",
        "intra_trade_low",
        "long_stop",
        "short_stop"
    ]

```

如果需要CTA引擎在运行过程中，对策略参数和变量在图形界面进行显示和数据刷新、停止策略时对其数值有所保存的话，需要把参数和变量的名字以字符串的形式添加进parameters和variables列表。

但是请注意，该列表只能接受str、int、float和bool这四种参数类型。如果策略里需要用到其他数据类型的变量，那么请把其他数据类型变量的定义放到__init__函数下。

### __init__函数

### CTA策略引擎调用的函数

CtaTemplate中的update_setting函数和该函数后四个以get开头的函数，都是CTA策略引擎去负责调用的函数。一般在策略编写的时候是不需要调用的。

### 回调函数

CtaTemplate中以on开头的函数都是在编写策略的过程中能够用来收到数据或者收到状态更新的回调函数。它的作用是当某一个事件发生的时候，策略里的这类函数会被调用（CTA策略引擎会去调用，在策略里的效果是无需策略主动操作，被自动调用了）。

策略实例状态控制

on_init

初始化策略时会被调用，默认写法是先调用write_log函数输出"策略初始化"日志再调用load_bar函数加载历史数据，如下方代码所示：

```
    def on_init(self):
        """
        Callback when strategy is inited.
        """
        self.write_log("策略初始化")
        self.load_bar(10)
```

on_start

启动策略时会被调用，默认写法是调用write_log函数输出"策略初始化"日志，如下方代码所示：

```
    def on_start(self):
        """
        Callback when strategy is started.
        """
        self.write_log("策略启动")
```

on_stop

停止策略时会被调用，默认写法是调用write_log函数输出"策略初始化"日志，如下方代码所示：

```
    def on_start(self):
        """
        Callback when strategy is started.
        """
        self.write_log("策略启动")
```

接收数据、计算指标、发出交易信号

on_tick

当策略收到最新的逐笔成交的行情推送时会被调用，默认写法是通过BarGenerator的update_tick函数把收到的这个tick推进前面创建的bg实例中以便合成1分钟的K线，如下方代码所示：


```
    def on_tick(self, tick: TickData):
        """
        Callback of new tick data update.
        """
        self.bg.update_tick(tick)
```

on_bar

当策略收到最新的K线数据（实盘时默认推进来的是基于tick合成的一分钟的K线，回测时则取决于回测选择参数时填入的K线数据频率）时会被调用，示例策略里出现过的写法有两种：

1. 如果策略基于on_bar推进来的K线交易，那么请把交易请求类函数都写在on_bar函数下（因为本次示例策略类BollChannelStrategy不基于on_bar交易，故不作示例讲解了。基于on_bar交易的示例代码可参考其他示例策略）；

2. 如果策略需要基于on_bar推进来的数据通过BarGenerator合成更长时间周期的K线来交易，那么请在on_bar中只通过BarGenerator的update_bar函数把收到的这个bar推进前面创建的bg实例中即可，如下方代码所示：

```
    def on_bar(self, bar: BarData):
        """
        Callback of new bar data update.
        """
        self.bg.update_bar(bar)
```


订单状态推送

on_trade

```
    def on_trade(self, trade: TradeData):
        """
        Callback of new trade data update.
        """
        self.put_event()
```

on_order

```
    def on_order(self, order: OrderData):
        """
        Callback of new order data update.
        """
        pass
```

on_stop_order

```
    def on_stop_order(self, stop_order: StopOrder):
        """
        Callback of stop order update.
        """
        pass
```

### 主动函数

策略内

buy

sell

short

cover

cancel_order

cancel_all

CTA策略引擎

send_order

### 功能函数

策略以外的功能函数

write_log

get_engine_type

get_pricetick

load_bar

load_tick

put_event

send_email

sync_data 

不使用信息就会丢失
