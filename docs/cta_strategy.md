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

在启动模块之前，请先连接交易接口（连接方法详见基本使用篇的连接接口部分）。看到VN Trader主界面【日志】栏输出“合约信息查询成功”之后再启动模块，如下图所示：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/cta_strategy/1.png)

请注意，IB接口因为登录时无法自动获取所有的合约信息，只有在用户手动订阅行情时才能获取。因此需要在主界面上先行手动订阅合约行情，再启动模块。

成功连接交易接口后，在菜单栏中点击【功能】-> 【CTA策略】，或者点击左侧按钮栏的图标：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/cta_strategy/00.png)

即可进入CTA策略模块的UI界面，如下图所示：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/cta_strategy/2.png)

如果配置了[RQData](https://www.ricequant.com/welcome/purchase?utm_source=vnpy)数据服务（配置方法详见基本使用篇的全局配置部分），打开CTA策略模块时会自动执行RQData登录初始化。若成功登录，则会输出“RQData数据接口初始化成功”的日志，如下图所示：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/cta_strategy/3.png)


## 添加策略

用户可以基于编写好的CTA策略模板（类）来创建不同的策略实例（对象）。策略实例的好处在于，同一个策略可以同时去交易多个品种合约，并且每个实例的参数可以是不同的。

在左上角的下拉框中选择要交易的策略名称，如下图所示：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/cta_strategy/28.png)

请注意，显示的策略名称是**策略类**（驼峰式命名）的名字，而不是策略文件（下划线模式命名）的名字。

选择好策略类之后，点击【添加策略】，会弹出添加策略对话框，如下图所示：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/cta_strategy/5.png)

在创建策略实例时，需要配置相关参数，各参数要求如下：

- 实例名称
  - 实例名称不能重名；
- 合约品种
  - 格式为vt_symbol（合约代码 + 交易所名称）；
  - 一定要是实盘交易系统中可以查到的合约名称；
  - 一般选择该期货品种当前流动性最好的月份，比如写本文时是2021年3月2日，此时的螺纹钢主力合约为rb2105.SHFE；
- 参数设置
  - 显示的参数名是策略里写在parameters列表中的参数名；
  - 默认数值为策略里的参数的默认值；
  - 由上图可观察到，参数名后面<>括号中显示的是该参数的数据类型，在填写参数时应遵循相应的数据类型。其中，<class 'str'>是字符串、<class 'int'>是整数、<class 'float'>是浮点数；
  - 请注意，如果某个参数可能会调整至有小数位的数值，而默认参数值是整数（比如1）。请在编写策略时，把默认参数值设为浮点数（比如1.0）。否则策略会默认该项参数为整数，在后续【编辑】策略实例参数时，会只允许填进整数。

参数配置完成后，点击【添加】按钮，则开始创建策略实例。创建成功后可在左侧的策略监控组件中看到该策略实例，如下图所示：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/cta_strategy/7.png)

策略监控组件顶部显示的是策略实例名、合约品种名、策略类名以及策略作者名（在策略里定义的author）。顶部按钮用于控制和管理策略实例，第一行表格显示了策略内部的参数信息（参数名需要写在策略的parameters列表中图形界面才会显示），第二行表格则显示了策略运行过程中的变量信息（变量名需要写在策略的variables列表中图形界面才会显示）。【inited】字段表示当前策略的初始化状态（是否已经完成了历史数据回放），【trading】字段表示策略当前是否能够开始交易。

从上图可观察到，此时该策略实例的【inited】和【trading】状态都为【False】。说明该策略实例还没有初始化，也还不能发出交易信号。

策略实例创建成功后，该策略实例的配置信息会被保存到.vntrader文件夹下的cta_strategy_setting.json文件中。

### 创建失败

以下为创建策略实例失败的几种可能情况：

- 如果添加了同名的策略实例，则会创建失败，图形界面输出“创建策略失败，存在重名”的日志信息，如下图所示：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/cta_strategy/31.png)

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/cta_strategy/8.png)

- 如果合约品种没有填写交易所名称，则会创建失败，图形界面输出“创建策略失败，本地代码缺失交易所后缀”的日志信息，如下图所示：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/cta_strategy/32.png)

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/cta_strategy/11.png)

- 如果合约品种的交易所名称填错，则会创建失败，图形界面输出“创建策略失败，本地代码的交易所后缀不正确”的信息，如下图所示：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/cta_strategy/33.png)

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/cta_strategy/13.png)


## 管理策略

### 初始化

策略实例创建成功后，就可以对该实例进行初始化了。点击该策略实例下的【初始化】按钮，若初始化成功，则如下图所示：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/cta_strategy/6.png)

初始化过程中，主要按顺序完成了以下三步任务：

1. 获取历史数据

   为了确保策略内指标数值的准确性，每个策略实例都需要一定的历史数据来进行策略初始化。

   因此，在策略初始化时，策略实例内部的load_bar函数会先去接口获取最新历史数据。如果接口不提供历史数据，则通过RQData（提供国内期货、股票以及期权的历史数据）获取。RQData的数据服务提供盘中K线更新，即使在9点45分才启动策略，也能获取到之前从9点30开盘到9点45分之间的K线数据，提供给策略进行初始化计算，而不用担心数据缺失的问题。如果没有配置RQData数据服务，则通过访问本地数据库查询。这种情况下，用户需要保证数据库中的数据完整性（满足初始化需求），可以通过DataRecorder录制，使用DataManager从CSV文件载入，或者使用其他数据服务来更新数据。

   具体载入数据的长度，取决于load_bar函数的参数控制（策略模板默认是10天）。数据载入后会以逐根K线（或者Tick）的方式推送给策略，实现内部变量的初始化计算，比如缓存K线序列、计算技术指标等。

2. 载入缓存变量

   在每天实盘运行的过程中，量化策略中的有些变量只和历史行情数据相关，这类变量通过加载历史数据回放就能得到正确的数值。另一类变量则可能和交易状态相关，如策略的持仓、移动止损的最高价跟踪等，这类变量需要缓存在硬盘上（退出程序时），第二天回放完历史数据后再读取还原，才能保证和之前交易状态的一致性。

   每次停止策略时，会自动将策略的variables列表对应的变量以及策略持仓缓存进.vntrader目录下的cta_strategy_data.json文件中，以便在下一次策略初始化时自动载入。

   注意在某些情况下（比如手动平仓了），缓存的数据可能会出现偏差，此时可以通过手动修改json文件来调整。

3. 订阅行情推送

   最后基于vt_symbol参数获取该策略所交易合约的信息，并订阅该合约的实时行情推送。如果实盘交易系统找不到该合约的信息，比如没有连接登录接口或者vt_symbol填写错误，则会在日志模块中输出相应的报错信息。

以上三个步骤全部完成后，可观察到此时该策略实例的【inited】状态已经为【True】，且变量也都显示对应的数值（不再为0）。说明该策略实例已经调用过load_bar函数加载历史数据并完成初始化了。【trading】状态还是为【False】，说明此时该策略实例还不能开始自动交易。

### 初始化失败

以下为创建策略实例失败的几种可能情况：  
- 即使交易所填的是vn.py支持的交易所的名字，成功创建了策略实例。但是如果该合约名字输入错误（比如大小写错误，合约与交易所对不上或者已经退市），导致实盘交易系统找不到该合约，则会初始化失败。此时图形界面输出“行情订阅失败，找不到合约”的日志。如下图所示：

  ![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/cta_strategy/14.png)

- 即使合约代码填写正确，成功创建了策略实例。但是如果此时还没有连接接口，或者接口合约信息查询合约操作还没有完成，导致实盘交易系统找不到该合约，也会初始化失败。此时图形界面输出“行情订阅失败，找不到合约”的日志。如下图所示：

  ![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/cta_strategy/15.png)

  如果出现了“行情订阅失败，找不到合约”这类问题，可以通过VN Trader的主界面点击【帮助】-【查询合约】进行查询，找到正确的合约信息。如下图所示：

  ![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/cta_strategy/34.png)

- 如果策略内用到了K线时间序列管理模块（ArrayManager）来计算变量指标的值，那么请确保历史数据的长度足够ArrayManager进行初始化（默认的ArrayManager需要100条数据才能初始化成功）。如果历史数据的长度不够ArrayManager初始化，即使图形界面上输出了日志“初始化完成”，该策略实例的初始化也是失败的。

  - 如果策略逻辑是基于示例策略中的，一但ArrayManager没有初始化成功(if not am.inited)就返回了逻辑写的话，那么由下图可观察到，图形界面左侧的策略实例中基于ArrayManager计算的策略指标的值都是0。说明此时该策略实例虽然启动之后就可以开始自动交易了，但是因为ArrayManager没有初始化成功，策略内的逻辑每次走到ArrayManager初始化状态判断时就返回了，走不到计算指标进而发出交易信号的逻辑。该策略实例需要一直等到推进策略实例的数据足够ArrayManager初始化之后，满足ArrayManager初始化的判断条件，才能真正发出交易信号。
  ![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/cta_strategy/16.png)

  - 如果策略逻辑不是基于示例策略中的，一但ArrayManager没有初始化成功(if not am.inited)就返回的逻辑写的话，那么虽然图形界面左侧的策略实例中的策略指标有具体数值，而且此时启动可以发出交易信号，无需等待ArrayManager初始化完成。但是因为ArrayManager没有初始化成功，该策略实例计算出来的变量指标值是不准确的，进而可能会发出不符合策略预期的交易信号。

### 启动

策略实例初始化成功，【inited】状态为【True】时，才能启动该策略的自动交易功能。点击该策略实例下的【启动】按钮，即可启动该策略实例。成功后如下图所示：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/cta_strategy/17.png)

可观察到此时该策略实例的【inited】和【trading】状态都为【True】。说明此时该策略实例已经调用过load_bar函数，完成了历史数据回放，而且此时策略内部的交易请求类函数（buy/sell/short/cover/cancel_order等），以及信息输出类函数（send_email/put_event等），才会真正执行并发出对应的请求指令到底层接口中（真正执行交易）。

在上一步策略初始化的过程中，尽管策略同样在接收（历史）数据，并调用对应的功能函数，但因为【trading】状态为【False】，所以并不会有任何真正的委托下单操作或者交易相关的日志信息输出。

如果启动之后，策略发出了限价单，可以去VN Trader主界面【委托】栏查看委托订单细节。如果策略发出了本地停止单，可以在CTA策略UI界面右上方区域的停止单监控组件查看委托订单细节。

### 停止

如果启动策略之后，由于某些情况（如到了市场收盘时间，或盘中遇到紧急情况）想要停止、编辑或者移除策略，可以点击策略实例下的【停止】按钮，即可停止该策略实例的自动交易。成功后如下图所示：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/cta_strategy/18.png)

CTA策略引擎会自动将该策略之前发出的所有活动委托全部撤销，以保证在策略停止后不会有失去控制的委托存在。同时该策略实例最新的变量信息会被保存到.vntrader文件夹下的cta_strategy_data.json文件中。

此时可观察到该策略实例的【trading】状态已变为【False】，说明此时该策略实例已经停止自动交易了。

在CTA策略的实盘交易过程中，正常情况应该让策略在整个交易时段中都自动运行，尽量不要有额外的暂停重启类操作。对于国内期货市场来说，应该在交易时段开始前，启动策略的自动交易，然后直到收盘后，再关闭自动交易。因为现在CTP夜盘收盘后也会关闭系统，早上开盘前重启，所以夜盘收盘后也需要停止策略，关闭VN Trader了。

### 编辑

如果创建策略实例之后，想要编辑某个策略实例的参数（若已启动策略，需要先点击策略实例下的【停止】按钮，停止策略），可以点击该策略实例下的【编辑】按钮，会弹出参数编辑对话框，以供修改策略参数。如下图所示：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/cta_strategy/39.png)

编辑完策略参数之后，点击下方的【确定】按钮，相应的修改会立即更新在参数表格中，如下图所示：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/cta_strategy/40.png)

但是策略实例的交易合约代码无法修改，同时修改完后也不会重新执行初始化操作。也请注意，此时修改的只是.vntrader文件夹下cta_strategy_setting.json文件中该策略实例的参数值，并没有修改原策略文件下的参数。

修改前，json文件如下图所示：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/cta_strategy/19.png)

修改后，json文件如下图所示：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/cta_strategy/20.png)

若盘中编辑后想要再次启动策略，点击策略实例下的【启动】按钮即可再次启动该略实例，如下图所示：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/cta_strategy/41.png)

### 移除

如果创建策略实例之后，想要移除某个策略实例（若已启动策略，需要先点击策略实例下的【停止】按钮，停止策略），可以点击该策略实例下的【移除】按钮。移除成功后，图形界面左侧的策略监控组件中将不会再显示该策略实例的信息。如下图所示：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/cta_strategy/21.png)

此时.vntrader文件夹下的cta_strategy_setting.json文件也移除了该策略实例的配置信息。

### 状态跟踪

如果想要通过图形界面跟踪策略的状态，有两种方式：

1. 调用put_event函数

   策略实例中所有的的变量信息，都需要把变量名写在策略的variables列表中，才能在图形界面显示。如果想跟踪变量的状态变化，则需要在策略中调用put_event函数，界面上才会进行数据刷新。
   
   有时用户会发现自己写的策略无论跑多久，变量信息都不发生变化，这种情况请检查策略中是否漏掉了对put_event函数的调用。

2. 调用write_log函数

   如果不仅想观察到变量信息的状态变化，还想根据策略的状态输出基于自己需求的个性化的日志，可以在策略中调用write_log函数，进行日志输出。


## 运行日志

### 日志内容

CTA策略模块UI界面上输出的日志有两个来源，分别是CTA策略引擎和策略实例。

**引擎日志**

CTA策略引擎一般输出的是全局信息。下图中除了策略实例名后加冒号的内容之外，都是CTA策略引擎输出的日志。

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/cta_strategy/37.png)

**策略日志**

如果在策略中调用了write_log函数，那么日志内容就会通过策略日志输出。下图红框里的内容分别是两个不同的策略实例输出的策略日志。冒号前是策略实例的名称，冒号后是write_log函数输出的内容。

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/cta_strategy/38.png)

### 清空操作

如果想要清空CTA策略UI界面上的日志输出，可以点击右上角的【清空日志】按钮，则可一键清空该界面上已输出的日志。

点击【清空日志】前，如下图所示：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/cta_strategy/21.png)

点击【清空日志】后，如下图所示：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/cta_strategy/23.png)


## 停止单

图形界面右上方区域的停止单监控组件，是用来跟踪所有CTA引擎内本地停止单的状态变化的。

因为不是所有接口都支持停止单，所以vn.py提供了本地停止单的功能。在交易接口不支持交易所停止单的前提下，用户依然可以通过策略的下单函数（buy/sell/short/cover），把stop参数设置为True，启用本地停止单功能。

vn.py的本地停止单有三个特点：

1. 保存在本地电脑上，关机后则失效；
2. 只有交易员本人能够看到，不必担心泄露底牌；
3. 停止单触发有延时，导致一定的滑点。

**停止单信息**

在发出本地停止单后，图形界面右上方的监控组件就会显示停止单的委托细节。

本地停止单一共有【等待中】、【已触发】和【已撤销】三个状态，如下图所示：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/cta_strategy/35.png)

停止单刚发出时是处于【等待中】的状态。因为停止单的信息记录在本地，没有发往交易所，所以此时主界面上【委托】栏不会有变化。

一旦该停止单的委托价格被触发，为了实现立即成交的目的，CTA策略引擎会立即以**涨跌停价**或者**盘口五档**的价格，去发出**限价**委托（所以建议本地停止单只用于流动性较好的合约）。限价委托发出后，VN Trader主界面上【委托】栏将更新该订单的状态，此时停止单状态会变为【已触发】，【限价委托号】栏下也会填入该订单的限价委托号。

需注意，停止单界面显示的价格是本地停止单的触发价格，而不是发出限价单的价格。

如果停止单在被触发前就被策略取消了，那么该订单的状态就会变为【已撤销】。


## 批量操作

在策略经过充分测试，实盘运行较为稳定，不需要经常进行调整的情况下，如果有多个需要运行的CTA策略实例，可以使用界面右上角的【全部初始化】、【全部启动】和【全部停止】功能来执行盘前批量初始化、启动策略实例以及盘后批量停止策略实例的操作。

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


## 移仓助手

如需使用自动移仓助手，请在完成策略初始化之后，对要执行移仓的策略先点击【移仓助手】按钮，则会弹出移仓助手对话框，如下图所示：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/cta_strategy/45.png)

首先请在在左侧区域配置要执行的移仓任务，其中：

- 移仓合约：该下拉框中，显示当前CTA策略模块下所有策略实例所交易的合约本地代码，选择要平仓掉的老合约；
- 目标合约：要将老的仓位和策略，移仓过去的的合约本地代码（vt_symbol），输入要开仓的新合约；
- 委托超价：执行移仓交易时，委托价格相对于当时盘口对价超出的pricetick。

完成配置确认无误后，点击【移仓】按钮开始执行，移仓过程中会有如下图所示的日志输出，完成后该对话框会被设为锁死（变灰无法再点击）：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/cta_strategy/44.png)

可以看到几乎1秒内就完成了移仓合约对应的全部仓位和策略的移仓操作，同时CTA策略模块界面上的策略交易代码已经变为目标合约。

移仓过程中具体执行的任务步骤如下：

- 仓位移仓：

  - 对当前账户内，移仓合约的【所有仓位】进行平仓（注意这里不会区分策略持仓还是手动交易持仓），并记录对应的仓位（多空分别记录）；
  - 对目标合约执行开仓交易，开仓的价格为当时的盘口对价加上超价pricetick，数量为上一步中记录的原有移仓合约持仓量。

- 策略移仓：

  - 记录当前CTA策略模块中，所有交易对象为移仓合约的策略的【逻辑持仓】（注意这里的逻辑持仓和账户实际持仓不一定完全对应）；
  - 将上述交易对象为移仓合约的老策略实例删除，并创建以目标合约为交易标的同名新策略实例；
  - 初始化新策略实例，并将之前记录的老策略实例的【逻辑持仓】，更新到新策略的状态上。

回到VN Trader主界面，也可以查看到详细的移仓委托和成交记录。如下图所示：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/cta_strategy/43.png)
![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/cta_strategy/42.png)


## CTA策略模板（CtaTemplate）

CTA策略模板提供完整的信号生成和委托管理功能，用户可以基于该模板(位于vnpy.app.cta_strategy.template中)自行开发CTA策略。

用户自行开发的策略可以放在用户运行文件夹下的[strategies](#jump)文件夹内。

请注意，策略文件命名采用下划线模式，如boll_channel_strategy.py，而策略类命名采用驼峰式，如BollChannelStrategy。

下面通过BollChannelStrategy策略示例，来展示策略开发的具体步骤：

在基于CTA策略模板编写策略逻辑之前，需要在策略文件的顶部载入需要用到的内部组件，如下方代码所示：

```
from vnpy.app.cta_strategy import (
    CtaTemplate,
    StopOrder,
    TickData,
    BarData,
    TradeData,
    OrderData,
    BarGenerator,
    ArrayManager
)
```

其中，CtaTemplate是CTA策略模板，StopOrder、TickData、BarData、TradeData和OrderData都是储存对应信息的数据容器，BarGenerator是K线生成模块，ArrayManager是K线时间序列管理模块。

### 策略参数与变量

在策略类的下方，可以设置策略的作者（author），参数（parameters）以及变量（variables），如下方代码所示：

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

虽然策略的参数和变量都从属于策略类，但策略参数是固定的（由交易员从外部指定），而策略变量则在交易的过程中随着策略的状态而变化，所以策略变量一开始只需要初始化为对应的基础类型。例如：整数设为0，浮点数设为0.0，而字符串则设为""。

如果需要CTA引擎在运行过程中，将策略参数和变量显示在UI界面上，并在数据刷新、停止策略时保存其数值，则需把参数和变量的名字（以字符串的数据类型）添加进parameters和variables列表里。

请注意，该列表只能接受参数或变量以str、int、float和bool四种数据类型传入。如果策略里需要用到其他数据类型的参数与变量，请把该参数或变量的定义放到__init__函数下。

### 类的初始化

入参：cta_engine: Any, strategy_name: str, vt_symbol: str, setting: dict

出参：无

__init__函数是策略类的构造函数，需要与继承的CtaTemplate保持一致。

在这个继承的策略类里，初始化一般分三步，如下方代码所示：

```
    def __init__(self, cta_engine, strategy_name, vt_symbol, setting):
        """"""
        super().__init__(cta_engine, strategy_name, vt_symbol, setting)

        self.bg = BarGenerator(self.on_bar, 15, self.on_15min_bar)
        self.am = ArrayManager()
```

1 . 通过super( )的方法继承CTA策略模板，在__init__( )函数中传入CTA引擎、策略名称、vt_symbol以及参数设置。注意其中的CTA引擎，可以是实盘引擎或者回测引擎，这样可以方便地**实现同一套代码同时跑回测和实盘**（以上参数均由策略引擎在使用策略类创建策略实例时自动传入，用户无需进行设置）。

2 . 调用K线生成模块（BarGenerator）：通过时间切片将Tick数据合成1分钟K线数据。如有需求，还可合成更长的时间周期数据，如15分钟K线。

如果只基于on_bar进行交易，这里代码可以写成：

```
        self.bg = BarGenerator(self.on_bar)
```

而不用给bg实例传入需要基于on_bar周期合成的更长K线周期，以及接收更长K线周期的函数名。

​请注意，合成X分钟线时，X必须设为能被60整除的数（60除外）。对于小时线的合成没有这个限制。

BarGenerator默认的基于on_bar函数合成长周期K线的数据频率是分钟级别，如果需要基于合成的小时线或者更长周期的K线交易，请在策略文件顶部导入Interval，并传入对应的数据频率给bg实例。如下方代码所示：

​文件顶部导入Interval：

```
from vnpy.trader.constant import Interval
```

__init__函数创建bg实例时传入数据频率：

```
        self.bg = BarGenerator(self.on_bar, 2, self.on_2hour_bar, Interval.HOUR)
```

3 . 调用K线时间序列管理模块（ArrayManager）：基于K线数据，如1分钟、15分钟，
将其转化为便于向量化计算的时间序列数据结构，并在内部支持使用talib库来计算相应的技术指标。

### CTA策略引擎调用的函数

CtaTemplate中的update_setting函数和该函数后面四个以get开头的函数，都是CTA策略引擎去负责调用的函数，一般在策略编写的时候是不需要调用的。

### 策略的回调函数

CtaTemplate中以on开头的函数称为回调函数，在编写策略的过程中能够用来接收数据或者接收状态更新。回调函数的作用是当某一个事件发生的时候，策略里的这类函数会被CTA策略引擎自动调用（无需在策略中主动操作）。回调函数按其功能可分为以下三类：

#### 策略实例状态控制（所有策略都需要）

**on_init**

* 入参：无

* 出参：无

初始化策略时on_init函数会被调用，默认写法是先调用write_log函数输出“策略初始化”日志，再调用load_bar函数加载历史数据，如下方代码所示：

```
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

```
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

停止策略时on_stop函数会被调用，默认写法是调用write_log函数输出“策略停止”日志，如下方代码所示：

```
    def on_stop(self):
        """
        Callback when strategy is stopped.
        """
        self.write_log("策略停止")
```

调用策略的on_stop函数停止策略后，策略的trading状态变为【False】，此时策略就不会发出交易信号了。

#### 接收数据、计算指标、发出交易信号

**on_tick**

* 入参：tick: TickData

* 出参：无

绝大部分交易系统都只提供Tick数据的推送。即使一部分数字货币交易平台或者外汇平台可以提供K线数据的推送，但是这些数据到达本地电脑的速度也会慢于Tick数据的推送，因为也需要平台合成之后才能推送过来。所以实盘的时候，vn.py里所有的策略的K线都是由收到的Tick数据合成的。

当策略收到最新的Tick数据的行情推送时，on_tick函数会被调用。默认写法是通过BarGenerator的update_tick函数把收到的Tick数据推进前面创建的bg实例中以便合成1分钟的K线，如下方代码所示：

```
    def on_tick(self, tick: TickData):
        """
        Callback of new tick data update.
        """
        self.bg.update_tick(tick)
```

**on_bar**

* 入参：bar: BarData

* 出参：无

当策略收到最新的K线数据时（实盘时默认推进来的是基于Tick合成的一分钟的K线，回测时则取决于选择参数时填入的K线数据频率），on_bar函数就会被调用。示例策略里出现过的写法有两种：

1 . 如果策略基于on_bar推进来的K线交易，那么请把交易请求类函数都写在on_bar函数下（因本次示例策略类BollChannelStrategy不是基于on_bar交易，故不作示例讲解。基于on_bar交易的示例代码可参考其他示例策略）；

2 . 如果策略需要基于on_bar推进来的K线数据通过BarGenerator合成更长时间周期的K线来交易，那么请在on_bar中调用BarGenerator的update_bar函数，把收到的这个bar推进前面创建的bg实例中即可，如下方代码所示：

```
    def on_bar(self, bar: BarData):
        """
        Callback of new bar data update.
        """
        self.bg.update_bar(bar)
```

示例策略类BollChannelStrategy是通过15分钟K线数据回报来生成CTA信号的。一共有三部分，如下方代码所示：

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

- 清空未成交委托：为了防止之前下的单子在上一个15分钟没有成交，但是下一个15分钟可能已经调整了价格，就用cancel_all()方法立刻撤销之前未成交的所有委托，保证策略在当前这15分钟开始时的整个状态是清晰和唯一的；

- 调用K线时间序列管理模块：基于最新的15分钟K线数据来计算相应的技术指标，如布林带通道上下轨、CCI指标、ATR指标等。首先获取ArrayManager对象，然后将收到的K线推送进去，检查ArrayManager的初始化状态，如果还没初始化成功就直接返回，没有必要去进行后续的交易相关的逻辑判断。因为很多技术指标计算对最少K线数量有要求，如果数量不够的话计算出来的指标会出现错误或无意义。反之，如果没有return，就可以开始计算技术指标了；

- 信号计算：通过持仓的判断以及结合CCI指标、布林带通道、ATR指标在通道突破点挂出停止单委托（buy/sell)，同时设置离场点(short/cover)。

    请注意，如果需要在图形界面刷新指标数值，请不要忘记调用put_event()函数。

#### 委托状态更新

以下函数在策略中可以直接pass，其具体逻辑应用交给回测/实盘引擎负责。

**on_trade**

* 入参：bar: TradeData

* 出参：无

收到策略成交回报时on_trade函数会被调用。

**on_order**

* 入参：bar: OrderData

* 出参：无

收到策略委托回报时on_order函数会被调用。

**on_stop_order**

* 入参：bar: StopOrder

* 出参：无

收到策略停止单回报时on_stop_order函数会被调用。

### 主动函数

**buy**：买入开仓（Direction：LONG，Offset：OPEN）

**sell**：卖出平仓（Direction：SHORT，Offset：CLOSE）

**short**：卖出开仓（Direction：SHORT，Offset：OPEN）

**cover**：买入平仓（Direction：LONG，Offset：CLOSE）

* 入参：price: float, volume: float, stop: bool = False, lock: bool = False, net: bool = False

* 出参：vt_orderids: List[vt_orderid] / 无 

buy/sell/short/cover都是策略内部的负责发单的交易请求类函数。策略可以通过这些函数给CTA策略引擎发送交易信号来达到下单的目的。

以下方buy函数的代码为例，可以看到，价格和数量是必填的参数，停止单转换、锁仓转换和净仓转换则默认为False。也可以看到，函数内部收到传进来的参数之后就调用了CtaTemplate里的send_order函数来发单（因为是buy指令，则自动把方向填成了LONG，开平填成了OPEN）

如果stop设置为True，那么该笔订单则会自动转成停止单，如果接口支持交易所停止单则会转成交易所停止单，如果接口不支持交易所停止单则会转换成vn.py的本地停止单。

如果lock设置为True，那么该笔订单则会进行锁仓委托转换（在有今仓的情况下，如果想平仓，则会先平掉所有的昨仓，然后剩下的部分都进行反向开仓来代替平今仓，以避免平今的手续费惩罚）。

如果net设置为True，那么该笔订单则会进行净仓委托转换（基于整体账户的所有仓位，根据净仓持有方式来对策略下单的开平方向进行转换）。但是净仓交易模式与锁仓交易模式互斥，因此net设置为True时，lock必须设置为False。

```
    def buy(self, price: float, volume: float, stop: bool = False, lock: bool = False, net: bool = False):
        """
        Send buy order to open a long position.
        """
        return self.send_order(Direction.LONG, Offset.OPEN, price, volume, stop, lock, net)
```

请注意，国内期货有开平仓的概念，例如买入操作要区分为买入开仓和买入平仓；但对于股票、外盘期货和绝大部分数字货币都是净持仓模式，没有开仓和平仓概念，所以只需使用买入（buy）和卖出（sell）这两个指令就可以了。

**send_order**

* 入参：price: float, volume: float, stop: bool = False, lock: bool = False, net: bool = False

* 出参：vt_orderids / 无

send_order函数是CTA策略引擎调用的发送委托的函数。一般在策略编写的时候不需要单独调用，通过buy/sell/short/cover函数发送委托即可。

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

**write_log**

* 入参：msg: str

* 出参：无

在策略中调用write_log函数，可以进行指定内容的日志输出。

**get_engine_type**

* 入参：无

* 出参：engine_type: EngineType

如果策略对于回测和实盘时有不同的逻辑处理，可以调用get_engine_type函数获取当下使用的引擎类型来进行逻辑判断。

请注意，如果要调用该函数进行逻辑判断，请在策略文件顶部导入“EngineType”。

**get_pricetick**

* 入参：无

* 出参：pricetick: float / None

在策略中调用get_pricetick函数，可以获取交易合约的最小价格跳动。

**load_bar**

* 入参：days: int, interval: Interval = Interval.MINUTE, callback: Callable = None, use_database: bool = False

* 出参：无

在策略中调用load_bar函数，可以在策略初始化时加载K线数据。

如下方代码所示，load_bar函数调用时，默认加载的天数是10，频率是一分钟，对应也就是加载10天的1分钟K线数据。在回测时，10天指的是10个交易日，而在实盘时，10天则是指的是自然日，因此建议加载的天数宁可多一些也不要太少。

```
    def load_bar(
        self,
        days: int,
        interval: Interval = Interval.MINUTE,
        callback: Callable = None,
        use_database: bool = False
    ):
        """
        Load historical bar data for initializing strategy.
        """
        if not callback:
            callback = self.on_bar

        self.cta_engine.load_bar(
            self.vt_symbol,
            days,
            interval,
            callback,
            use_database
        )
```

**load_tick**

* 入参：days: int

* 出参：无

在策略中调用load_tick函数，可以在策略初始化时加载Tick数据。

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

在策略中调用sync_data函数，可以在实盘的时候，每次停止或成交时都同步策略变量进json文件中进行本地缓存，方便第二天初始化时再进行读取还原（CTA策略引擎会去调用，在策略里无需主动调用）。

请注意，要在策略启动之后，也就是策略的trading状态变为【True】之后，才能同步策略信息。
