# CTA趋势策略

CtaStrategy是用于**CTA自动交易**的功能模块，用户可以通过其UI界面操作来便捷完成策略初始化、策略启动、策略停止、策略参数编辑以及策略移除等任务。


## 主要优势

CtaStrategy模块充分利用了多核CPU，支持多进程CTA策略交易。并提供了专业CTA策略模板EliteCtaTemplate，以实现更加强大的CTA策略开发。

针对回测和实盘不一致的问题，EliteCtaTemplate内置了一套[基于策略的理论目标维护策略运行](#jump1)的方案。另外，EliteCtaTemplate还提供了对非交易时段垃圾数据的过滤配置支持（具体可参考过滤配置篇）。


## 启动模块

CtaStrategy模块需要启动之前通过【策略应用】标签页加载。

启动登录VeighNa Elite Trader后，启动模块之前，请先连接交易接口。看到VeighNa Elite Trader主界面【日志】栏输出“合约信息查询成功”之后再启动模块。

请注意，IB接口因为登录时无法自动获取所有的合约信息，只有在用户手动订阅行情时才能获取。因此需要在主界面上先行手动订阅合约行情，再启动模块。

成功连接交易接口后，在菜单栏中点击【功能】-> 【多进程CTA交易】，或者点击左侧按钮栏的图标：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/elite/ctastrategy/1.png)

即可进入多进程CTA交易模块的UI界面。

如果配置了数据服务，打开CTA策略模块时会自动执行数据服务登录初始化。若成功登录，则会输出“数据服务初始化成功”的日志，如下图所示：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/elite/ctastrategy/2.png)


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

用户可以基于编写好的CTA策略模板（类）来创建不同的策略实例（对象）。策略实例的好处在于，同一个策略可以同时去交易多个品种合约，并且每个实例的参数可以是不同的。

在左上角的下拉框中选择要交易的策略名称，如下图所示：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/elite/ctastrategy/3.png)

请注意，显示的策略名称是**策略类**（驼峰式命名）的名字，而不是策略文件（下划线模式命名）的名字。

选择好策略类之后，点击【添加策略】，会弹出添加策略对话框，如下图所示：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/elite/ctastrategy/4.png)

在创建策略实例时，需要配置相关参数，各参数要求如下：

- 实例名称
  - 实例名称不能重名；
- 合约品种
  - 格式为vt_symbol（合约代码 + 交易所名称）；
  - 一定要是实盘交易系统中可以查到的合约名称；
  - 一般选择该期货品种当前流动性最好的月份；
- 接口名称
  - 选择需要交易的接口名称；
- 参数设置
  - 显示的参数名称是策略中使用Parameter辅助类定义的参数；
  - 默认数值为策略中的参数的默认值；
  - 由上图可观察到，参数名后面<>括号中显示的是该参数的数据类型，在填写参数时应遵循相应的数据类型。其中，<class 'str'>是字符串、<class 'int'>是整数、<class 'float'>是浮点数；
  - 请注意，如果某个参数可能会调整至有小数位的数值，而默认参数值是整数（比如1）。请在编写策略时，把默认参数值设为浮点数（比如1.0）。否则策略会默认该项参数为整数，在后续【编辑】策略实例参数时，会只允许填进整数。

参数配置完成后，点击【添加】按钮，则开始创建策略实例。创建成功后可在左侧的策略监控组件中看到该策略实例。因为每个策略都是独立进程，所以添加成功后图形界面会输出“策略进程启动”的日志，如下图所示：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/elite/ctastrategy/5.png)

策略监控组件顶部显示的是策略实例名、接口名、合约品种名、策略类名以及策略作者名（在策略里定义的author）。顶部按钮用于控制和管理策略实例，第一行表格显示了策略内部的参数信息（参数名需要写在策略的parameters列表中图形界面才会显示），第二行表格则显示了策略运行过程中的变量信息（变量名需要写在策略的variables列表中图形界面才会显示）。【inited】字段表示当前策略的初始化状态（是否已经完成了历史数据回放），【trading】字段表示策略当前是否能够开始交易。

从上图可观察到，此时该策略实例的【inited】和【trading】状态都为【False】。说明该策略实例还没有初始化，也还不能发出交易信号。

策略实例创建成功后，该策略实例的配置信息会被保存到.vntrader文件夹下的cta_strategy_setting.json文件中。


## 初始化策略

策略实例创建成功后，就可以对该实例进行初始化了。点击该策略实例下的【初始化】按钮，若初始化成功，则如下图所示：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/elite/ctastrategy/6.png)

初始化过程中，主要按顺序完成了以下三步任务：

1. 获取历史数据

   为了确保策略内指标数值的准确性，每个策略实例都需要一定的历史数据来进行策略初始化。

   因此，在策略初始化时，策略实例内部的load_bar函数会先去接口获取最新历史数据。如果接口不提供历史数据，则通过配置的数据服务获取（[RQData](https://www.ricequant.com/welcome/purchase?utm_source=vnpy)提供国内期货、股票以及期权的历史数据。RQData的数据服务提供盘中K线更新，即使在9点45分才启动策略，也能获取到之前从9点30开盘到9点45分之间的K线数据，提供给策略进行初始化计算，而不用担心数据缺失的问题）。

   具体载入数据的长度，取决于load_bar函数的参数控制（策略模板默认是10天）。数据载入后会以逐根K线（或者Tick）的方式推送给策略，实现内部变量的初始化计算，比如缓存K线序列、计算技术指标等。

2. 载入缓存变量

   在每天实盘运行的过程中，量化策略中的有些变量只和历史行情数据相关，这类变量通过加载历史数据回放就能得到正确的数值。另一类变量则可能和交易状态相关，如策略的持仓，这类变量需要缓存在硬盘上（退出程序时），第二天回放完历史数据后再读取还原，才能保证和之前交易状态的一致性。

   每次停止策略时，会自动将策略的variables列表对应的变量以及策略持仓缓存进.vntrader目录下的cta_strategy_data.json文件中，以便在下一次策略初始化时自动载入。

   请注意，在某些情况下（比如手动平仓了），缓存的数据可能会出现偏差（因为策略持仓维护的是运行策略实例的逻辑持仓，不是特定品种的持仓），那么可以通过手动修改json文件来调整。

3. 订阅行情推送

   最后基于vt_symbol参数获取该策略所交易合约的信息，并订阅该合约的实时行情推送。如果实盘交易系统找不到该合约的信息，比如没有连接登录接口或者vt_symbol填写错误，则会在日志模块中输出相应的报错信息。

以上三个步骤完成后，可观察到此时该策略实例的【inited】状态已经为【True】，且变量也都显示对应的数值（不再为0）。说明该策略实例已经调用过load_bar函数加载历史数据并完成初始化了。【trading】状态还是为【False】，说明此时该策略实例还不能开始自动交易。

## 启动策略

策略实例初始化成功，【inited】状态为【True】时，才能启动自动交易功能。点击策略实例下的【启动】按钮，即可启动该策略实例。成功后如下图所示：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/elite/ctastrategy/7.png)

可观察到此时该策略实例的【inited】和【trading】状态都为【True】。说明此时该策略实例已经调用过load_bar函数，完成了历史数据回放，而且此时策略内部的交易请求类函数（buy/sell/short/cover/cancel_order等），以及信息输出类函数（send_email/put_event等），才会真正执行并发出对应的请求指令到底层接口中（真正执行交易）。

在上一步策略初始化的过程中，尽管策略同样在接收（历史）数据，并调用对应的功能函数，但因为【trading】状态为【False】，所以并不会有任何真正的委托下单操作或者交易相关的日志信息输出。

如果启动之后，策略发出了限价单，可以去VeighNa Elite Trader主界面【委托】栏查看委托订单细节。如果策略发出了本地停止单，可以在CTA策略UI界面右上方区域的停止单监控组件查看委托订单细节。


## 停止策略

如果启动策略之后，由于某些情况（如到了市场收盘时间，或盘中遇到紧急情况）想要停止、编辑或者移除策略，可以点击策略实例下的【停止】按钮，即可停止该策略实例的自动交易。成功后如下图所示：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/elite/ctastrategy/8.png)

CTA策略引擎会自动将该策略之前发出的所有活动委托全部撤销，以保证在策略停止后不会有失去控制的委托存在。同时该策略实例最新的变量信息会被保存到.vntrader文件夹下的cta_strategy_data.json文件中。

此时可观察到该策略实例的【trading】状态已变为【False】，说明此时该策略实例已经停止自动交易了。

在CTA策略的实盘交易过程中，正常情况应该让策略在整个交易时段中都自动运行，尽量不要有额外的暂停重启类操作。对于国内期货市场来说，应该在交易时段开始前，启动策略的自动交易，然后直到收盘后，再关闭自动交易。因为现在CTP夜盘收盘后也会关闭系统，早上开盘前重启，所以夜盘收盘后也需要停止策略，关闭VeighNa Elite Trader了。


## 编辑策略

如果创建策略实例之后，想要编辑某个策略实例的参数（若已启动策略，需要先点击策略实例下的【停止】按钮，停止策略），可以点击该策略实例下的【编辑】按钮，会弹出参数编辑对话框，以供修改策略参数。如下图所示：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/elite/ctastrategy/9.png)

编辑完策略参数之后，点击下方的【确定】按钮，相应的修改会立即更新在参数表格中，如下图所示：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/elite/ctastrategy/10.png)

但是策略实例的交易合约代码无法修改，同时修改完后也不会重新执行初始化操作。也请注意，此时修改的只是.vntrader文件夹下cta_strategy_setting.json文件中该策略实例的参数值，并没有修改原策略文件下的参数。

若盘中编辑后想要再次启动策略，点击策略实例下的【启动】按钮即可再次启动该策略实例，如下图所示：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/elite/ctastrategy/11.png)


## 移除策略

如果创建策略实例之后，想要移除某个策略实例（若已启动策略，需要先点击策略实例下的【停止】按钮，停止策略），可以点击该策略实例下的【移除】按钮。移除成功后，图形界面左侧的策略监控组件中将不会再显示该策略实例的信息。因为每个策略都是独立进程，所以移除成功后图形界面会输出“策略进程退出”的日志，如下图所示：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/elite/ctastrategy/12.png)

此时.vntrader文件夹下的cta_strategy_setting.json文件也移除了该策略实例的配置信息。


## 状态跟踪

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

CTA策略引擎一般输出的是全局信息。下图中除了以带中括号的策略实例名开头的内容之外，都是CTA策略引擎输出的日志。

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/elite/ctastrategy/13.png)

**策略日志**

如果在策略中调用了write_log函数，那么日志内容就会通过策略日志输出。下图红框里的内容分别是两个不同的策略实例输出的策略日志。中括号里是策略实例的名称，中括号后是write_log函数输出的内容。

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/elite/ctastrategy/14.png)

### 清空操作

如果想要清空CTA策略UI界面上的日志输出，可以点击右上角的【清空日志】按钮，则可一键清空该界面上已输出的日志。

点击【清空日志】前，如下图所示：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/elite/ctastrategy/12.png)

点击【清空日志】后，如下图所示：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/elite/ctastrategy/15.png)


## 停止单

图形界面右上方区域的停止单监控组件，是用来跟踪所有CTA引擎内本地停止单的状态变化的。

因为不是所有接口都支持停止单，所以VeighNa提供了本地停止单的功能。在交易接口不支持交易所停止单的前提下，用户依然可以通过策略的下单函数（buy/sell/short/cover），把stop参数设置为True，启用本地停止单功能。

VeighNa的本地停止单有三个特点：

1. 保存在本地电脑上，关机后则失效；
2. 只有交易员本人能够看到，不必担心泄露底牌；
3. 停止单触发有延时，导致一定的滑点。

**停止单信息**

在发出本地停止单后，图形界面右上方的监控组件就会显示停止单的委托细节。

本地停止单一共有【等待中】、【已触发】和【已撤销】三个状态，如下图所示：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/elite/ctastrategy/19.png)

停止单刚发出时是处于【等待中】的状态。因为停止单的信息记录在本地，没有发往交易所，所以此时主界面上【委托】栏不会有变化。

一旦该停止单的委托价格被触发，为了实现立即成交的目的，CTA策略引擎会立即以**涨跌停价**或者**盘口五档**的价格，去发出**限价**委托（所以建议本地停止单只用于流动性较好的合约）。限价委托发出后，VeighNa Elite Trader主界面上【委托】栏将更新该订单的状态，此时停止单状态会变为【已触发】，【限价委托号】栏下也会填入该订单的限价委托号。

请注意，**停止单界面显示的价格是本地停止单的触发价格，而不是发出限价单的价格**。

如果停止单在被触发前就被策略取消了，那么该订单的状态就会变为【已撤销】。


## 批量操作

在策略经过充分测试，实盘运行较为稳定，不需要经常进行调整的情况下，如果有多个需要运行的CTA策略实例，可以使用界面右上角的【全部初始化】、【全部启动】和【全部停止】功能来执行盘前批量初始化、启动策略实例以及盘后批量停止策略实例的操作。


## 手动换月移仓

如需使用自动移仓助手，请在策略初始化之前，点击CTA策略UI界面右上角的【移仓助手】按钮，则会弹出移仓助手界面，如下图所示：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/elite/ctastrategy/20.png)

若策略已经初始化，则打开界面时，移仓助手界面左下角会输出“策略已经初始化，无法执行移仓”的信息，如下图所示：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/elite/ctastrategy/21.png)

成功打开移仓助手界面之后，点击【刷新】按钮即可看到当前CTA策略模块下所有策略实例所交易的合约信息，如下图所示：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/elite/ctastrategy/22.png)

此时就可以配置要执行的移仓任务了，其中：

- 移仓合约：填入需要将老的仓位和策略，移仓过去的新合约的本地代码（vt_symbol）；
- 多头移仓：合约多头需要移仓的数量（不能大于显示的账户总多持仓）；
- 空头移仓：合约空头需要移仓的数量（不能大于显示的账户总空持仓）；
- 单笔上限：算法移仓时单笔委托的手数上限；
- 委托超价：算法移仓时委托价格相对于当时盘口对价超出的pricetick。

完成配置确认无误后，点右上角击【执行移仓】按钮，会弹出【执行移仓确认】窗口，如下图所示：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/elite/ctastrategy/23.png)

点击【OK】开始执行，移仓过程中，界面左下角会有移仓相关信息输出，右下角会有移仓算法的显示，完成后移仓助手的上半部分会被设为锁死（变灰无法再点击），如下图所示：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/elite/ctastrategy/24.png)

可以看到几乎1秒内就完成了移仓合约对应的全部仓位和策略的移仓操作。

因为执行完移仓之后界面的上半部分被锁死了，如果需要查看新的可移仓合约的信息或者想进行新一轮移仓（可以分合约执行移仓，也可以先配置好所有的移仓合约，再点击【执行持仓】一次性进行所有策略的移仓），可以点击【刷新】按钮对界面进行刷新。刷新之后会发现“平仓合约”已经变成了刚刚移仓成功的合约的名字。


请注意：
  1. - 如果将移仓合约填成了平仓合约一致的合约，点击【执行移仓】按钮之后会弹出【执行移仓失败】窗口，并输出“移仓合约和平仓合约不能一样”的信息，如下图所示：

       ![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/elite/ctastrategy/25.png)

     - 如果将移仓合约填成了其他品种的合约或者填错了交易所，点击【执行移仓】按钮之后也会弹出【执行移仓失败】窗口，并输出“移仓合约和平仓合约品种不一致”的信息，如下图所示：

       ![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/elite/ctastrategy/26.png)

  2. 在执行移仓算法的过程中（还未完成），可以点击界面右下角算法监控部分的【停止】按钮来终止某个移仓算法的执行。但是算法停止后会有瘸腿风险（平仓合约与移仓合约移仓结果不一致）；

  3. 即使平仓合约的可移仓持仓为0，也需要填写移仓合约的名字进行移仓。

### 移仓过程

移仓助手组件根据配置的移仓信息订阅移仓合约的行情，并启动对应的移仓算法进行委托。移仓的价格为当时的盘口对价加上或减去超价pricetick, 数量为配置的移仓数量（不超过配置的单笔上限）。算法结束之后再更新策略交易代码并移除之前的策略实例。

### 移仓效果

回到CTA策略模块的UI界面，可以发现对应策略的交易合约名字已经变了。

移仓前如下图所示：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/elite/ctastrategy/27.png)

移仓成功后如下图所示：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/elite/ctastrategy/28.png)

回到VeighNa Elite Trader主界面，也可以查看到详细的移仓委托和成交记录。


## 多账户支持

### 加载

CTA策略模块提供了多账户批量下单交易支持。

以登录**CTP**接口为例，在登录界面下方的【交易接口】标签页的下拉框中先选中CTP接口。在“自定义接口”处填写自定义的接口名（例如“CTP1”、“CTP2”）之后点击【添加】按钮，填写子账户的配置信息，点击【确定】按钮，则可依次加载对应账户的接口。

添加完毕后，点击登录界面的【登录】按钮登录VeighNa Elite Trader。在菜单栏中依次点击【系统】->【连接xxx】（xxx是自定义的接口名，若加载时填写的“CTP1”，则菜单栏中显示的就是【连接CTP1】），即可连接子账户接口。

连接成功以后，VeighNa Elite Trader主界面【日志】组件会立刻输出登录相关信息，同时用户也可以看到对应的账号信息，持仓信息等相关信息。

### CTA策略模块批量下单

若需通过CTA策略模块进行批量委托，可在CTA策略模块图形界面【添加策略】时点击【gateway_name】的下拉框选中接口进行指定，如下图所示：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/elite/ctastrategy/16.png)

策略添加成功后，可以在左侧的策略监控组件中看到策略实例的信息，如下图所示：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/elite/ctastrategy/17.png)

策略实例发出委托后，可在VeighNa Elite Trader主界面【委托】组件和【成交】组件上跟踪到根据对应接口下单的委托，如下图所示：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/elite/ctastrategy/18.png)

**请注意**：
 - 目前支持同时登录最多登录5个交易账户


## CTA策略模板

CTA策略模板提供了信号生成和委托管理功能，用户可以基于模板自行开发CTA策略。

用户自行开发的策略可以放在用户运行文件夹下的[strategies](#jump)文件夹内。

请注意：
   - 策略文件命名采用下划线模式，如rumi_strategy.py，而策略类命名采用驼峰式，如RumiStrategy；

   - 自建策略的类名不要与示例策略的类名重合。如果重合了，图形界面上只会显示一个策略类名。

### CtaTemplate

VeighNa Elite Trader对vnpy_ctastrategy自带的CtaTemplate提供兼容支持，通过CtaTemplate开发的策略也可在VeighNa Elite Trader的CTA策略模块上成功运行。

### EliteCtaTemplate

VeighNa Elite Trader的CTA策略模块提供了EliteCtaTemplate专业CTA策略模板，实现更加强大的CTA策略开发。

下面通过RumiStrategy策略示例，来展示策略开发的具体步骤：

在基于EliteCtaTemplate编写策略逻辑之前，需要在策略文件的顶部载入需要用到的内部组件，如下方代码所示：

```python3
from numpy import ndarray

from elite_ctastrategy import (
    EliteCtaTemplate,
    HistoryManager,
    Parameter,
    Variable,
    sma,
    wma,
    cross_over,
    cross_below,
)
```

其中：
* EliteCtaTemplate是Veighna Elite Trader提供的CTA策略模板
* HistoryManager是Veighna Elite Trader提供的储存历史数据的容器
* Parameter是储存策略参数的数据容
* Variable是储存策略变量的数据容器
* sma，wms，cross_over和cross_below都是内置的计算函数（完整计算函数列表可参考内置指标计算函数篇）
* ndarray是给on_history函数中计算出来的结果做类型声明的类。

### 策略参数与变量

在策略类的下方，可以设置策略的作者（author），参数（parameters）以及变量（variables），如下方代码所示：

```python3

    author = "VeighNa菁英版"

    # 基础参数（必填）
    bar_window: int = Parameter(30)             # K线窗口
    bar_interval: int = Parameter("1m")         # K线级别
    bar_buffer: int = Parameter(100)            # K线缓存

    # 策略参数（可选）
    fast_window: int = Parameter(3)             # 快速均线窗口
    slow_window: int = Parameter(50)            # 慢速均线窗口
    rumi_window: int = Parameter(30)            # 均线偏差窗口
    max_holding: int = Parameter(100)           # 最长持仓周期
    stop_percent: float = Parameter(0.03)       # 保守止损比例
    risk_window: int = Parameter(10)            # 风险计算窗口
    risk_capital: int = Parameter(1_000_000)    # 交易风险投入
    price_add: int = Parameter(5)               # 委托下单超价

    # 策略变量
    trading_size: int = Variable(1)             # 当前委托数量
    rumi_0: float = Variable(0.0)               # RUMI当前数值
    rumi_1: float = Variable(0.0)               # RUMI上期数值

```

虽然策略的参数和变量都从属于策略类，但策略参数是固定的（由交易员从外部指定），而策略变量则在交易的过程中随着策略的状态而变化，所以策略变量一开始只需要初始化为对应的基础类型。例如：整数设为0，浮点数设为0.0。

如果需要CTA引擎在运行过程中，将策略参数和变量显示在UI界面上，并在数据刷新、停止策略时保存其数值，则需在创建策略类的时候创建对应的参数和变量实例。

请注意：
 - Parameter容器和Variable容器只能接受参数或变量以str、int、float和bool四种数据类型传入；

 - 每个通过EliteCtaTemplate开发的策略，都需要创建bar_window（K线窗口）、bar_interval（K线级别 - 目前只支持"1m"和"1h"）以及bar_buffer（历史数据容器HistoryManager的K线缓存长度）这三个基础参数；

 - 当bar_interval为"1m"时，bar_window必须设为能被60整除的数（60除外）。当bar_interval为"1h"时则没有这个限制。

### 策略的回调函数

CtaTemplate中以on开头的函数称为回调函数，在编写策略的过程中能够用来接收数据或者接收状态更新。回调函数的作用是当某一个事件发生的时候，策略里的这类函数会被CTA策略引擎自动调用（无需在策略中主动操作）。回调函数按其功能可分为以下三类：

#### 策略实例状态控制（所有策略都需要）

**on_init**

* 入参：无

* 出参：无

初始化策略时on_init函数会被调用，默认写法是先调用write_log函数输出“策略初始化”日志，再调用load_bar函数加载历史数据，如下方代码所示：

```python3
    def on_init(self) -> None:
        """初始化"""
        self.write_log("策略初始化")
        self.load_bar(10)
```

策略初始化时，策略的inited和trading状态都为【False】，此时只是调用历史数据管理器计算并缓存相关的计算指标，不能发出交易信号。调用完on_init函数之后，策略的inited状态才变为【True】，策略初始化才完成。

**on_start**

* 入参：无

* 出参：无

启动策略时on_start函数会被调用，默认写法是调用write_log函数输出“策略启动”日志，如下方代码所示：

```python3
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

```python3
    def on_stop(self):
        """
        Callback when strategy is stopped.
        """
        self.write_log("策略停止")
```

调用策略的on_stop函数停止策略后，策略的trading状态变为【False】，此时策略就不会发出交易信号了。

#### 接收数据、计算指标、发出交易信号

**on_history**

* 入参：hm: HistoryManager

* 出参：无

一旦策略的[历史数据管理器HistoryManager](#jump2)初始化完成之后，当策略收到最新的K线数据时，on_history函数就会被调用。

示例策略类RumiStrategy是通过30分钟K线数据回报来生成CTA信号的。一共有三部分，如下方代码所示：

```python3
    def on_history(self, hm: HistoryManager) -> None:
        """K线推送"""
        # 计算均线数组
        fast_array: ndarray = sma(hm.close, self.fast_window)
        slow_array: ndarray = wma(hm.close, self.slow_window)

        # 计算均线差值
        diff_array: ndarray = fast_array - slow_array
        rumi_array: ndarray = sma(diff_array, self.rumi_window)

        self.rumi_0 = rumi_array[-1]
        self.rumi_1 = rumi_array[-2]

        # 判断上下穿
        long_signal: bool = cross_over(rumi_array, 0)
        short_signal: bool = cross_below(rumi_array, 0)

        # 计算交易数量
        self.trading_size = self.calculate_volume(self.risk_capital, self.risk_window, 1000, 1)

        # 获取当前目标
        last_target: int = self.get_target()

        # 初始化新一轮目标（默认不变）
        new_target: int = last_target

        # 执行开仓信号
        if long_signal:
            new_target = self.trading_size
        elif short_signal:
            new_target = -self.trading_size

        # 持仓时间平仓
        if self.bar_since_entry() >= self.max_holding:
            new_target = 0

        # 保护止损平仓
        close_price = hm.close[-1]

        if last_target > 0:
            stop_price: float = self.long_average_price() * (1 - self.stop_percent)
            if close_price <= stop_price:
                new_target = 0
        elif last_target < 0:
            stop_price: float = self.short_average_price() * (1 + self.stop_percent)
            if close_price >= stop_price:
                new_target = 0

        # 设置新一轮目标
        self.set_target(new_target)

        # 执行目标交易
        self.execute_trading(self.price_add)

        # 推送UI更新
        self.put_event()
```

- 信号计算：通过收到的最新HistoryManager实例获取的K线数据来计算相应的技术指标。如均线数组和均线差值等。首先获取需要的数组，然后通过内置的指标计算函数进行计算；
  
   请注意，示例策略中的cross_over和cross_below函数是计算传入指标是否上穿（指标上一个值小于等于指定数值以及指标最新值大于指定数值）和下穿（指标上一个值大于等于指定数值以及指标最新值小于指定数值）的布尔函数。

- 设置目标：计算完技术指标后，调用calculate_volume函数计算委托数量。然后基于get_target函数获取的当前目标对新一轮目标进行初始化。之后可以基于指标的数值和策略的状态设置新一轮目标；
  
   以RumiStrategy为例，通过long_signal/short_signal设置开仓信号，平仓则通过持仓时间和保护止损两方面设置。

   当策略的当前目标last_target为0时，策略的开仓后经历过的K线周期数也为0，所以都不会触发平仓条件，条件满足时只会发出开仓信号。当策略的当前目标last_target不为0时，若新的信号与之前开仓的信号是一个方向，则新一轮目标与当前目标保持一致，执行交易时不会委托下单。若触发了平仓条件，则会将新一轮目标设为0，执行交易时进行平仓。若新的信号与之前开仓的信号不是一个方向，则会设置该信号为新一轮目标，执行时进行委托。

   请注意，在所有设置新一轮目标的逻辑之后，执行目标交易之前，通过set_target函数设置策略目标是为了避免在同一根K线里进行多次设置操作。

- 执行目标交易：设置好新一轮目标之后，直接执行目标交易并推送UI更新。

   请注意，如果需要在图形界面刷新指标数值，请不要忘记调用put_event()函数。

#### 委托状态更新

以下函数在策略中可以直接pass，其具体逻辑应用交给回测/实盘引擎负责。请注意，**不要在这类函数中下达委托指令**。

**on_trade**

* 入参：bar: TradeData

* 出参：无

收到策略成交回报时on_trade函数会被调用。

**on_order**

* 入参：bar: OrderData

* 出参：无

收到策略委托回报时on_order函数会被调用。

### 主动函数

<span id="jump1">

EliteCtaTemplate内置了一套缓存策略理论成交记录的方案。在主动函数中，除了execute_trading函数中计算仓差时是基于策略目标和策略仓位差别来计算之外，其他部分都是由策略的理论目标来控制的。

**set_target**

* 入参：target: int

* 出参：无

set_target是用来设置策略目标净仓位的函数（可以理解为想要指定的策略持仓量）。正数代表做多、负数代表做空。

请注意，目标仓位是一种持续性的状态，因此设置后在后续时间会持续保持下去，直到被再次设置修改。

**get_target**

* 入参：无

* 出参：int

get_target是用来查询策略目标仓位的函数。

**execute_trading**

* 入参：price_add: float

* 出参：无

execute_trading是基于设定的目标仓位用来执行交易的函数。委托下单和撤单已经被该函数接管，无需再在策略内进行下单和撤单操作。

execute_trading被调用之后，在函数内部会先撤销策略所有活动委托，然后根据策略目标和策略持仓的仓差（没有则不委托）进行委托。

**calculate_volume**

* 入参：risk_capital: float, risk_window: int, max_volume = 0, min_volume: int = 0

* 出参：trading_size: int

calculate_volume是用来计算风险调整后的委托数量的函数。

risk_capital是用来计算风险调整后的委托数量的资金，risk_window是用来计算风险水平的K线周期窗口，max_volume和min_volume是限制委托数量的最大值和最小值。

请注意，**risk_window的长度不能超过HistoryManager容器的长度bar_buffer**。

**bar_since_entry**

* 入参：无

* 出参：int

bar_since_entry函数是用来获取内置交易管理器里维护的开仓后经历过的K线周期数（理论值）的函数。

**long_average_price**

* 入参：无

* 出参：int

long_average_price函数是用来获取内置交易管理器里维护的多头持仓均价（理论值）的函数。

**short_average_price**

* 入参：无

* 出参：int

short_average_price函数是用来获取内置交易管理器里维护的空头持仓均价（理论值）的函数。

**get_account_pos**

* 入参：无

* 出参：int

get_account_pos函数用于获取该策略（合约代码、交易接口）对应的底仓账户持仓，返回值为净仓数据（即多仓减去空仓的数值）。

</span>

### 功能函数

以下为策略以外的功能函数：

**write_log**

* 入参：msg: str

* 出参：无

在策略中调用write_log函数，可以进行指定内容的日志输出。

**load_bar**

* 入参：days: int, interval: Interval = Interval.MINUTE, callback: Callable = None, use_database: bool = False

* 出参：无

在策略中调用load_bar函数，可以在策略初始化时加载K线数据。

如下方代码所示，调用load_bar函数时，默认加载的天数是10，频率是一分钟，对应也就是加载10天的1分钟K线数据，建议加载的天数宁可多一些也不要太少。use_database参数默认为False，会先依次尝试通过交易接口、数据服务获取历史数据，直到获取历史数据或返回空。

**put_event**

* 入参：无

* 出参：无

在策略中调用put_event函数，可以通知图形界面刷新策略状态相关显示。

请注意，要策略初始化完成，inited状态变为【True】之后，才能刷新界面。

**send_email**

* 入参：msg: str

* 出参：无

配置好邮箱相关信息之后，在策略中调用send_email函数，可以发送指定内容的邮件到自己的邮箱。

请注意，要策略初始化完成，inited状态变为【True】之后，才能发送邮件。

**sync_data**

* 入参：无

* 出参：无

在策略中调用sync_data函数，可以在实盘交易的时候，每次停止时都同步策略变量到对应json文件中进行本地缓存，方便第二天初始化时再进行读取还原（CTA策略引擎会去调用，在策略里无需主动调用）。

请注意：
   - 要在策略启动之后，也就是策略的trading状态变为【True】之后，才能同步策略信息；

   - 基于EliteCtaTemplate开发的策略，只有策略的持仓pos会被同步到本地，其他策略变量由理论值维护。


## 历史数据管理器

<span id="jump2">

HistoryManager是CTA策略模块自带的定长的历史数据管理器。所有基于EliteCtaTemplate开发的策略，都可通过on_history函数推送HistoryManager的实例hm获取K线数据进而进行指标计算和委托。

每个策略实例的HistoryManager都取决于策略类里定义的bar_window、bar_interval和bar_buffer三个参数。bar_window和bar_interval决定了HistoryManager内储存K线的时间频率，bar_buffer决定了HistoryManager容器的长度（HistoryManager内缓存的K线数不低于bar_buffer根时才算初始化成功）。

**datetime**：K线的开始时间

**open**：K线的开始价格

**high**：K线内的最高价

**low**：K线内的最低价

**close**：K线的结束价格

**volume**：K线内的成交量

**turnover**：K线内的成交额

**open_interest**：K线内的持仓量（股票没有该字段）

HistoryManager里对合成K线的datetime、open、high、low、close、volume、turnover和open_interest都进行了缓存，便于用户取用。以open_price为例，通过策略on_history里收到的hm实例可直接获取open_price的数组（hm.open）。如果想获取最新一根合成K线的开始价格，直接取出该数组的最后一个元素（hm.open[-1]）即可。

**bar_count**

* 入参：无

* 出参：int

如果策略启动之后策略指标的值都是0，可以调用HistoryManager的bar_count函数（hm.bar_count()）看看HistoryManager缓存过的K线长度是否小于策略类设置的bar_buffer，如果小于的话说明历史数据太短了不够HistoryManager容器初始化。此时可以选择加载更多历史数据进行策略初始化或者适当调小bar_buffer解决。

**to_dataframe**

* 入参：无

* 出参：df: pd.DataFrame

如果想把on_history推送的hm实例缓存的合成K线的信息转换成DataFrame，可以调用HistoryManager的to_dataframe函数（hm.to_dataframe()）进行转换。转换之后可以得到一个长度为策略类设置的bar_buffer、以K线开始时间作为索引，open、high、low、close、volume、turnover和open_interest作为列名的DataFrame。

</span>
