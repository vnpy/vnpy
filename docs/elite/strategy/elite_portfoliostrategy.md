# 投组截面策略

PortfolioStrategy是用于**多进程组合策略实盘**的功能模块，用户可以通过其UI界面操作来便捷完成策略初始化、策略启动、策略停止、策略参数编辑以及策略移除等任务。


## 主要优势

PortfolioStrategy模块充分利用了多核CPU，支持多进程组合策略交易。


## 启动模块

PortfolioStrategy模块需要启动之前通过【策略应用】标签页加载。

启动登录VeighNa Elite Trader后，启动模块之前，请先连接交易接口。看到VeighNa Elite Trader主界面【日志】栏输出“合约信息查询成功”之后再启动模块。

请注意，IB接口因为登录时无法自动获取所有的合约信息，只有在用户手动订阅行情时才能获取。因此需要在主界面上先行手动订阅合约行情，再启动模块。

成功连接交易接口后，在菜单栏中点击【功能】-> 【多进程组合策略交易】，或者点击左侧按钮栏的图标：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/elite/portfoliostrategy/1.png)

即可进入多进程组合策略交易模块的UI界面。

如果配置了数据服务，打开多进程组合策略模块时会自动执行数据服务登录初始化。若成功登录，则会输出“数据服务初始化成功”的日志，如下图所示：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/elite/portfoliostrategy/2.png)


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

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/elite/portfoliostrategy/3.png)

请注意，显示的策略名称是**策略类**（驼峰式命名）的名字，而不是策略文件（下划线模式命名）的名字。

选择好策略类之后，点击【添加策略】，会弹出添加策略对话框，如下图所示：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/elite/portfoliostrategy/4.png)

在创建策略实例时，需要配置相关参数，各参数要求如下：

- 实例名称
  - 实例名称不能重名；
- 合约品种
  - 格式为vt_symbol（合约代码 + 交易所名称）；
  - 一定要是实盘交易系统中可以查到的合约名称；
  - 合约名用“,”隔开，中间不加空格；
- 接口名称
  - 选择需要交易的接口名称；
- 参数设置
  - 显示的参数名是策略里写在parameters列表中的参数名；
  - 默认数值为策略中的参数的默认值；
  - 由上图可观察到，参数名后面<>括号中显示的是该参数的数据类型，在填写参数时应遵循相应的数据类型。其中，<class 'str'>是字符串、<class 'int'>是整数、<class 'float'>是浮点数；
  - 请注意，如果某个参数可能会调整至有小数位的数值，而默认参数值是整数（比如1）。请在编写策略时，把默认参数值设为浮点数（比如1.0）。否则策略会默认该项参数为整数，在后续【编辑】策略实例参数时，会只允许填进整数。

参数配置完成后，点击【添加】按钮，则开始创建策略实例。创建成功后可在左侧的策略监控组件中看到该策略实例。因为每个策略都是独立进程，所以添加成功后图形界面会输出“策略进程启动”的日志，如下图所示：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/elite/portfoliostrategy/5.png)

策略监控组件顶部显示的是策略实例名、接口名、策略类名以及策略作者名（在策略里定义的author）。顶部按钮用于控制和管理策略实例，第一行表格显示了策略内部的参数信息（参数名需要写在策略的parameters列表中图形界面才会显示），第二行表格则显示了策略运行过程中的变量信息（变量名需要写在策略的variables列表中图形界面才会显示）。【inited】字段表示当前策略的初始化状态（是否已经完成了历史数据回放），【trading】字段表示策略当前是否能够开始交易。

从上图可观察到，此时该策略实例的【inited】和【trading】状态都为【False】。说明该策略实例还没有初始化，也还不能发出交易信号。

策略实例创建成功后，该策略实例的配置信息会被保存到.vntrader文件夹下的portfolio_strategy_setting.json文件中。


## 初始化策略

策略实例创建成功后，就可以对该实例进行初始化了。点击该策略实例下的【初始化】按钮，若初始化成功，则如下图所示：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/elite/portfoliostrategy/6.png)

初始化完成后，可观察到此时该策略实例的【inited】状态已经为【True】。说明该策略实例已经加载过历史数据并完成初始化了。【trading】状态还是为【False】，说明此时该策略实例还不能开始自动交易。

## 启动策略

策略实例初始化成功，【inited】状态为【True】时，才能启动该策略的自动交易功能。点击该策略实例下的【启动】按钮，即可启动该策略实例。成功后如下图所示：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/elite/portfoliostrategy/7.png)

可观察到此时该策略实例的【inited】和【trading】状态都为【True】。说明此时该策略实例已经完成了历史数据回放，而且此时策略内部的交易请求类函数（buy/sell/short/cover/cancel_order等），以及信息输出类函数（send_email/put_event等），才会真正执行并发出对应的请求指令到底层接口中（真正执行交易）。

在上一步策略初始化的过程中，尽管策略同样在接收（历史）数据，并调用对应的功能函数，但因为【trading】状态为【False】，所以并不会有任何真正的委托下单操作或者交易相关的日志信息输出。

如果启动之后，策略发出了委托，可以去VeighNa Trader主界面【委托】栏查看委托订单细节。

请注意，与CTA策略模块不同，多合约组合策略**不提供本地停止单功能**，所以UI界面上不会有停止单的显示区域了。


## 停止策略

如果启动策略之后，由于某些情况（如到了市场收盘时间，或盘中遇到紧急情况）想要停止、编辑或者移除策略，可以点击策略实例下的【停止】按钮，即可停止该策略实例的自动交易。成功后如下图所示：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/elite/portfoliostrategy/8.png)

组合策略引擎会自动将该策略之前发出的所有活动委托全部撤销，以保证在策略停止后不会有失去控制的委托存在。同时该策略实例最新的变量信息会被保存到.vntrader文件夹下的portfolio_strategy_data.json文件中。

此时可观察到该策略实例的【trading】状态已变为【False】，说明此时该策略实例已经停止自动交易了。

在多合约组合策略的实盘交易过程中，正常情况应该让策略在整个交易时段中都自动运行，尽量不要有额外的暂停重启类操作。对于国内期货市场来说，应该在交易时段开始前，启动策略的自动交易，然后直到收盘后，再关闭自动交易。因为现在CTP夜盘收盘后也会关闭系统，早上开盘前重启，所以夜盘收盘后也需要停止策略，关闭VeighNa Trader了。


## 编辑策略

如果创建策略实例之后，想要编辑某个策略实例的参数（若已启动策略，需要先点击策略实例下的【停止】按钮，停止策略），可以点击该策略实例下的【编辑】按钮，会弹出参数编辑对话框，以供修改策略参数。如下图所示：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/elite/portfoliostrategy/9.png)

编辑完策略参数之后，点击下方的【确定】按钮，相应的修改会立即更新在参数表格中，如下图所示：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/elite/portfoliostrategy/10.png)

但是策略实例的交易合约代码无法修改，同时修改完后也不会重新执行初始化操作。也请注意，此时修改的只是.vntrader文件夹下porfolio_strategy_setting.json文件中该策略实例的参数值，并没有修改原策略文件下的参数。

若盘中编辑后想要再次启动策略，点击策略实例下的【启动】按钮即可再次启动该策略实例，如下图所示：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/elite/portfoliostrategy/11.png)


## 移除策略

如果创建策略实例之后，想要移除某个策略实例（若已启动策略，需要先点击策略实例下的【停止】按钮，停止策略），可以点击该策略实例下的【移除】按钮。移除成功后，图形界面左侧的策略监控组件中将不会再显示该策略实例的信息。因为每个策略都是独立进程，所以移除成功后图形界面会输出“策略进程退出”的日志，如下图所示：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/elite/portfoliostrategy/12.png)

此时.vntrader文件夹下的portfolio_strategy_setting.json文件也移除了该策略实例的配置信息。


## 状态跟踪

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

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/elite/portfoliostrategy/13.png)

**策略日志**

如果在策略中调用了write_log函数，那么日志内容就会通过策略日志输出。下图红框里的内容是策略实例输出的策略日志。冒号前是策略实例的名称，冒号后是write_log函数输出的内容。

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/elite/portfoliostrategy/14.png)

### 清空操作

如果想要清空多合约组合策略UI界面上的日志输出，可以点击右上角的【清空日志】按钮，则可一键清空该界面上已输出的日志。

点击【清空日志】前，如下图所示：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/elite/portfoliostrategy/12.png)

点击【清空日志】后，如下图所示：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/elite/portfoliostrategy/15.png)


## 批量操作

在策略经过充分测试，实盘运行较为稳定，不需要经常进行调整的情况下，如果有多个需要运行的组合策略实例，可以使用界面右上角的【全部初始化】、【全部启动】和【全部停止】功能来执行盘前批量初始化、启动策略实例以及盘后批量停止策略实例的操作。


## 多账户支持

### 加载

多进程组合策略模块提供了多账户批量下单交易支持。

以登录**CTP**接口为例，在登录界面下方的【交易接口】标签页的下拉框中先选中CTP接口。在“自定义接口”处填写自定义的接口名（例如“CTP1”、“CTP2”）之后点击【添加】按钮，填写子账户的配置信息，点击【确定】按钮，则可依次加载对应账户的接口。

添加完毕后，点击登录界面的【登录】按钮登录VeighNa Elite Trader。在菜单栏中依次点击【系统】->【连接xxx】（xxx是自定义的接口名，若加载时填写的“CTP1”，则菜单栏中显示的就是【连接CTP1】），即可连接子账户接口。

连接成功以后，VeighNa Elite Trader主界面【日志】组件会立刻输出登录相关信息，同时用户也可以看到对应的账号信息，持仓信息等相关信息。

### 多进程组合策略模块批量下单

若需通过多进程组合策略模块进行批量委托，可在多进程组合策略模块图形界面【添加策略】时点击【gateway_name】的下拉框选中接口进行指定，如下图所示：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/elite/portfoliostrategy/16.png)

策略添加成功后，可以在左侧的策略监控组件中看到策略实例的信息，如下图所示：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/elite/portfoliostrategy/17.png)

策略实例发出委托后，可在VeighNa Elite Trader主界面【委托】组件和【成交】组件上跟踪到根据对应接口下单的委托，如下图所示：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/elite/portfoliostrategy/18.png)

**请注意**：
 - 目前支持同时登录最多登录5个交易账户


## 多合约组合策略模板

多合约组合策略模板提供了信号生成和委托管理功能，用户可以基于该模板自行开发多合约组合策略。

用户自行开发的策略可以放在用户运行文件夹下的[strategies](#jump)文件夹内。

请注意：
   - 策略文件命名采用下划线模式，如portfolio_boll_channel_strategy.py，而策略类命名采用驼峰式，如PortfolioBollChannelStrategy。

   - 自建策略的类名不要与示例策略的类名重合。如果重合了，图形界面上只会显示一个策略类名。

### StrategyTemplate

VeighNa Elite Trader对vnpy_portfoliostrategy自带的StrategyTemplate提供支持，通过StrategyTemplate开发的策略可在VeighNa Elite Trader的多合约组合策略模块上成功运行。
