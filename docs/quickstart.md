# 基本使用

## 启动程序

### 图形模式

启动登录VN Station后，用户可通过以下两种方式进入VN Trader：
- 点击【VN Trade Lite】按钮，快速进入VN Trader Lite（底层接口只包含CTP接口，功能模块只包含CTA策略模块和CTA回测模块）；
- 点击【VN Trader Pro】按钮，勾选所需的底层接口和上层应用，点击【启动】按钮进入VN Trader Pro，如下图所示：
![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/quick_start/18.png)

### 脚本模式

在文件夹examples/vn_trader中找到run.py文件(不是vnstudio下的，需要在github上单独下载）。运行run.py即可进入VN Trader。

- 以Win10系统为例，用户可在run.py所在文件夹内按住【Shift】，同时点击鼠标右键，选择【在此处打开 powershell 窗口】，在弹出窗口中，输入如下命令，即可启动VN Trader。
   ```
   python run.py
   ```
   ![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/quick_start/3.png)

启动成功的VN Trader如下图所示：
![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/quick_start/10.png)

## 连接接口

### SimNow仿真

以使用SinNow仿真交易账号登陆**CTP**接口为例，点击VN Trader上的菜单栏中点击【系统】->【连接CTP】，会弹出账号配置窗口，如下图所示：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/gateway/1.png)

其中，各字段填写要求如下：
- 用户名：xxxxxx （6位纯数字账号）
- 密码：xxxxxx （需要修改一次密码用于盘后测试）
- 经纪商代码：9999 （SimNow默认经纪商编号）
- 交易服务器：180.168.146.187:10202 （盘中测试）
- 行情服务器：180.168.146.187:10212 （盘中测试）
- 产品名称：simnow_client_test
- 授权编码：0000000000000000 （16个0）

请注意，用户名需填写InvestorID（6位纯数字），而不是Simnow网站注册时的账号（手机号）。此外，Simnow注册的账号需要修改一次密码后才能登录。

连接成功以后，VN Trader主界面【日志】组件会立刻输出登陆相关信息，同时用户也可以看到账号信息，持仓信息，合约查询等相关信息。如下图所示：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/cta_strategy/1.png)


## 合约查询

成功连接交易接口后，用户可以通过合约查询功能查询合约信息：
点击菜单栏的【帮助】->【合约查询】，在弹出的对话框中直接点击右上角的【查询】按钮，即可查询合约信息（留空则查询所有合约的价格信息），如下图所示：
![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/spread_trading/3.png)

请注意，IB接口因为登录时无法自动获取所有的合约信息，只有在用户手动订阅行情时才能获取。因此需要在主界面上先行手动订阅合约行情，才能查到合约信息。


## 订阅行情

在交易组件输入交易所和合约代码，按回车键即可订阅行情，如订阅铁矿石期货时，交易所填写DCE，代码填写对应合约代码i2106。

订阅成功后，交易组件会显示合约名称，并且在下方显示深度行情报价，如最新价、买一价和卖一价，行情组件会显示最新行情信息，如下图所示：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/quick_start/11.png)

请注意，**输入的合约代码需与在菜单栏的【帮助】->【查询合约】功能中查到的一致**。


## 委托交易

交易组件用于手动发起委托交易，除了填写交易所和合约代码外，还需填写下图中的五个字段（方向、开平、类型、价格和数量）：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/quick_start/5.png)

请注意，若委托类型为市价单，委托价格可不填；若交易接口只支持单向持仓（接口持仓方向支持详见交易接口篇），请勿填写开平方向。

发出委托后，本地会缓存委托相关信息，并显示到【委托】组件和【活动】组件，此时委托状态为【提交中】。

交易所收到用户发送的委托后，会将其插入中央订单簿来进行撮合成交，并推送委托回报给用户：
- 若委托还未成交，【委托】组件和【活动】组件只会更新时间和委托状态这两字段，委托状态变成【未成交】；
- 若委托立刻成交，委托相关信息会从【活动】组件移除，新增至【成交】组件，委托状态变成【全部成交】。


## 数据监控

数据监控由以下组件构成，并附带两个辅助功能：

选定以下任一组件，鼠标右键可以选择【调整列宽】（特别适用于屏幕分辨率较低的情况）或者选择【保存数据】（CSV格式），如下图所示：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/quick_start/12.png)

### 行情组件

行情组件用于对订阅的行情进行实时监控，如下图所示：

![](https://vnpy-community.oss-cn-shanghai.aliyuncs.com/forum_experience/yazhang/quick_start/subcribe_contract_module.png)

行情组件监控内容包括以下部分：
- 合约信息：合约代码、交易所、合约名称；
- 行情信息：最新价、成交量、开盘价、最高价、最低价、收盘价、买1价、买1量、卖1价、卖1量；
- 其他信息：数据推送时间、接口。

### 活动组件

活动组件用于存放还未成交的委托，如限价单或者没有立刻成交的市价单。在该组件中鼠标双击任一委托可以完成撤单操作，如下图所示：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/quick_start/15.png)

### 成交组件

成交组件用于存放已成交的委托，在该组件中，价格、数量和时间都是交易所推送过来的成交信息，而不是委托信息，如下图所示：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/quick_start/14.png)

### 委托组件

委托组件用于存放用户发出的所有委托信息，其委托状态可以是提交中、已撤销、部分成交、全部成交、拒单等，如下图所示：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/quick_start/13.png)

### 持仓组件

持仓组件用于记录历史持仓，需要注意以下字段信息。

- 方向：期货品种具有多空方向，而股票品种方向为【净】持仓；
- 数量：总持仓，即今仓 + 昨仓；
- 昨仓：其出现衍生于上期所特有的平今、平昨模式的需要；
- 均价：历史成交的平均价格（某些巨型委托，会发生多次部分成交，需要计算平均价格）；
- 盈亏：持仓盈亏。多仓情况下，盈利 = 当前价格 - 均价，空仓则反之。

若平仓离场，持仓数量清零，浮动盈亏变成实际盈亏从而影响账号余额变化。故以下字段：数量、昨仓、冻结、均价、盈亏均为0，如下图所示：

![](https://vnpy-community.oss-cn-shanghai.aliyuncs.com/forum_experience/yazhang/quick_start/query_position.png)


### 资金组件

资金组件显示了账号的基础信息，如下图所示：

![](https://vnpy-community.oss-cn-shanghai.aliyuncs.com/forum_experience/yazhang/quick_start/query_account.png)

需要注意以下三个字段信息：

- 可用资金：可以用于委托的现金
- 冻结：委托操作冻结的金额（与保证金不是一个概念）
- 余额：总资金，即可用资金 + 保证金 + 浮动盈亏 

若全部平仓，浮动盈亏变成实际盈亏，保证金和浮动盈亏清零，总资金等于可用资金。

### 日志组件

日志组件用于显示接口登陆信息以及委托报错信息，如下图所示：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/cta_strategy/1.png)


## 应用模块

vn.py官方提供了开箱即用的量化交易应用模块，在启动VN Trader时勾选所需的功能模块，启动成功后在菜单栏中点击【功能】按钮，即可显示所勾选的功能模块，如下图所示：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/quick_start/21.png)


## 全局配置

点击VN Trader菜单栏上的【配置】按钮弹出【全局配置】窗口，如下图所示：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/quick_start/20.png)

### GUI界面

font.family和font.size参数用于配置GUI界面，各参数含义如下所示：

- font.family：设置VN Trader图形界面的字体类型，除了默认的Arial字体，也支持Courier New和System字体；

- font.size：设置VN Trader图形界面的字体大小，用户可以根据自己显示器的实际分辨率对字体大小进行修改。

### 日志输出

log.active, log.level, log.console和log.file用于对日志输出进行配置，各参数含义如下所示：

- log.active：控制是否启动LogEngine，默认为True。如果该项修改为False，则后续几项参数都将失效，同时VN Trader运行时不再输出日志或生成日志文件（可以降低部分系统延时）；

- log.level：控制日志输出的级别，日志可以从轻到严重分成DEBUG、INFO、WARNING、ERROR、CRITICAL五个级别，分别对应10、20、30、40、50的整数值。如果日志等级低于该项设置值，将会被忽略。如果想要记录更详细的系统运行信息，建议将该项整数值调低；

- log.console：console指的是终端，如Windows系统上的cmd和Powershell，以及Linux上的Terminal。当设置为True时，通过终端运行脚本来启动VN Trader，日志信息会输出在终端中；如果通过VN Station来直接启动VN Trader，则无console输出；

- log.file：该参数用于控制是否要将日志输出到文件中，建议设置为True，否则无法记录生成的日志。

VN Trader的日志文件，默认位于运行时目录的.vntrader\log目录下，完整路径为：
C:\users\administrator.vntrader\log

其中，administrator为当前Windows系统的登录用户名。

### 邮件通知

以email为前缀的参数用于对邮箱进行配置，可以在特定事件发生时（如委托成交，数据异常时）发送邮件实时通知，各参数含义如下：

- email.server: SMTP邮件服务器地址，vnpy默认填写好了QQ邮箱服务器地址，可以直接用，如果需要使用其他邮箱，需要自行查找一下其他的服务器地址；
- email.port: SMTP邮件服务器端口号，vnpm默认填写好了QQ邮箱服务器端口，可以直接用；
- email.username: 填写邮箱地址即可，如xxxx@qq.com；
- email.password: 对于QQ邮箱，此处不是邮箱密码，而是开通SMTP后系统生成的一个授权码；
- email.sender: 发送邮箱名，与email.username一致；
- email.receiver: 接受邮件的邮箱地址。


### datafeed数据服务

与数据库适配器类似，对于数据服务有一个标准化的接口BaseDatafeed（位于vnpy.trader.datafeed），实现了更加灵活的数据服务支持，具体字段含义如下：

- datafeed.name: 数据服务接口的名称，全称的小写英文字母；
- datafeed.username: 数据服务的用户名；
- datafeed.password: 数据服务的密码。

字段如图所示：
![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/quick_start/17.png)

目前支持七种datafeed：
- [RQData]
- [Udata]
- [TuShare]
- [TQSDK]
- [Wind]
- [iFinD]
- [Tinysoft]

[RQData]:https://github.com/vnpy/vnpy_rqdata 
[Udata]: https://github.com/vnpy/vnpy_udata
[TuShare]: https://github.com/vnpy/vnpy_tushare
[TQSDK]: https://github.com/vnpy/vnpy_tqsdk
[Wind]:https://github.com/vnpy/vnpy_wind 
[iFinD]: https://github.com/vnpy/vnpy_ifind
[Tinysoft]: https://github.com/vnpy/vnpy_tinysoft


### 数据库

以database为前缀的参数用于配置数据库服务。目前，vn.py支持SQLite、MySQL、PostgreSQL、MongoDB、InfluxDB、DolphinDB、Arctic和LevelDB八种数据库。具体配置方法详见项目文档的数据库配置部分。



