# 基础交易功能


## 启动交易程序

### 点击图标启动

安装成功后，双击桌面上VeighNa Elite Trader快捷方式：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/elite/install/4.png)

即可运行VeighNa Elite Trader。

### 用户登录

每次使用VeighNa Elite Trader都会弹出包含用户名输入框以及密码输入框的登录界面，如下图所示：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/elite/trader/1.png)

用户按照要求在用户名输入框中输入用户名，在密码输入框中输入密码后，点击【登录】按钮，即可完成登录进入VeighNa Elite Trader主运行程序，如下图所示：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/elite/trader/8.png)

请注意，若VeighNa Elite Trader启动时检测到已有更新版本发布，则会弹出【更新提示】窗口。若点击【Yes】则立即更新，若点击【No】则跳过更新正常登录。

### 加载接口

在登录界面的下方，有两个标签页。分别为【交易接口】和【策略应用】。

点开【交易接口】标签下的接口下拉框，可以看到可供加载的接口，如下图所示：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/elite/trader/2.png)

在下拉框选择完需要加载的接口后，点击【添加】按钮，会弹出对应接口的配置窗口，如下图所示：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/elite/trader/3.png)

接口连接信息配置完毕之后，点击【确认】按钮则可看见选择的接口名字已经显示在标签页内容框中，如下图所示：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/elite/trader/4.png)

添加成功后，配置信息会被保存到本地，下次启动时无需重复填写。

若需更新接口配置信息，选中指定的接口名，点击【修改】按钮，对应的配置窗口会弹出以供更新。

若有无需再加载的接口，可选中指定的接口名，点击【移除】按钮，则可成功移除记录的接口名（没有删除记录的配置信息）。

请注意：

 - 如果需要连接融航接口，需要自行安装vcredist 2010才可成功加载

 - 如果需要连接GT接口，第一次连接需要使用管理员身份启动程序

 - 如果需要使用多账户功能，可参考[多账户支持](#jump)部分的介绍

### 加载应用

在登录界面的下方，点击【策略应用】标签，则可切换到加载策略应用的标签页，如下图所示：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/elite/trader/5.png)

点开【策略应用】标签下的接口下拉框，可以看到可供加载的应用，如下图所示：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/elite/trader/6.png)

在下拉框选择完需要加载的接口后，点击【添加】按钮则可成功加载该应用。与此同时，该策略应用的名字会显示在标签页内容框中，如下图所示：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/elite/trader/7.png)

应用加载成功后，下次启动时无需重复操作。

若有无需再加载的应用，可选中指定的应用名，点击【移除】按钮，即可移除已经加载的应用。

## 登录资金账号

以登陆**CTP**接口为例，在VeighNa Elite Trader上的菜单栏中点击【系统】->【连接CTP】，即可连接CTP接口。

连接成功以后，VeighNa Elite Trader主界面【日志】组件会立刻输出登陆相关信息，同时用户也可以看到账号信息，持仓信息，合约查询等相关信息。如下图所示：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/elite/trader/9.png)

## 查看合约信息

成功连接交易接口后，用户可以通过合约查询功能查询合约信息。
点击菜单栏的【帮助】->【合约查询】，在弹出的对话框中直接点击右上角的【查询】按钮，即可查询合约信息（留空则查询所有合约的价格信息），如下图所示：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/elite/trader/10.png)

请注意，IB接口因为登录时无法自动获取所有的合约信息，只有在用户手动订阅行情时才能获取。因此需要在主界面上先行手动订阅合约行情，才能查到合约信息。

## 订阅行情数据

在交易组件输入交易所和合约代码，按回车键即可订阅行情。如订阅股指期货时，交易所填写CFFEX，代码填写对应合约代码IF2306。

订阅成功后，交易组件会显示合约名称，并且在下方显示深度行情报价，如最新价、买一价和卖一价，行情组件会显示最新行情信息，如下图所示：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/elite/trader/11.png)

请注意，**输入的合约代码需与在菜单栏的【帮助】->【查询合约】功能中查到的一致**。

## 委托下单撤单

【快捷交易】组件用于手动发起委托交易，除了填写交易所和合约代码外，还需填写下图中的五个字段（方向、开平、类型、价格和数量）：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/elite/trader/12.png)

若已成功订阅行情，可以勾选【价格】栏右侧的方框，设置价格随行情更新。勾选之后，【价格】栏上的委托价格会随行情推送自动更新为设定合约的最新价，如下图所示：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/elite/trader/13.png)

请注意，若委托类型为市价单，委托价格可不填；若交易接口只支持单向持仓，可不填写开平方向。

发出委托后，本地会缓存委托相关信息，并显示到【委托】组件和【活动】组件，此时委托状态为【提交中】。

交易所收到用户发送的委托后，会将其插入中央订单簿来进行撮合成交，并推送委托回报给用户：
- 若委托还未成交，【委托】组件和【活动】组件只会更新时间和委托状态这两个字段，委托状态变成【未成交】；
- 若委托立刻成交，委托相关信息会从【活动】组件移除，新增至【成交】组件，委托状态变成【全部成交】。


## 交易数据监控

数据监控由以下组件构成，并附带两个辅助功能：

选定以下任一组件，鼠标右键可以选择【调整列宽】（特别适用于屏幕分辨率较低的情况）或者选择【保存数据】（CSV格式），如下图所示：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/elite/trader/18.png)

### 委托

委托组件用于存放用户发出的所有委托信息，其委托状态可以是提交中、已撤销、部分成交、全部成交、拒单等，如下图所示：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/elite/trader/19.png)

### 成交

成交组件用于存放已成交的委托，在该组件中，价格、数量和时间都是交易所推送过来的成交信息，而不是委托信息，如下图所示：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/elite/trader/20.png)

### 资金

资金组件显示了账号的基础信息，如下图所示：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/elite/trader/21.png)

需要注意以下三个字段信息：

- 可用：可以用于委托的现金
- 冻结：委托操作冻结的金额（与保证金不是一个概念）
- 余额：总资金，即可用资金 + 保证金 + 浮动盈亏

若全部平仓，浮动盈亏变成实际盈亏，保证金和浮动盈亏清零，总资金等于可用资金。

### 持仓

持仓组件用于记录历史持仓，如下图所示：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/elite/trader/22.png)

需要注意以下字段信息：

- 方向：期货品种具有多空方向，而股票品种方向为【净】持仓；
- 数量：总持仓，即今仓 + 昨仓；
- 昨仓：其出现衍生于上期所特有的平今、平昨模式的需要；
- 均价：历史成交的平均价格（某些巨型委托，会发生多次部分成交，需要计算平均价格）；
- 盈亏：持仓盈亏。多仓情况下，盈利 = 当前价格 - 均价，空仓则反之。

若平仓离场，持仓数量清零，浮动盈亏变成实际盈亏从而影响账号余额变化。


## 应用模块

VeighNa Elite提供了开箱即用的量化交易应用模块，在启动VeighNa Elite Trader时加载所需的应用模块，启动成功后在菜单栏中点击【功能】，即可在弹出的菜单中看到应用模块的对应按钮，同时在窗口最左侧区域也会有带图标的模块按钮用于快速打开应用，如下图所示：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/elite/trader/28.png)


## 全局配置

点击VeighNa Elite Trader菜单栏上的【配置】按钮弹出【全局配置】窗口，如下图所示：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/elite/trader/29.png)


### 数据服务

- 服务名: 数据服务接口的名称，全称的小写英文字母；
- 用户名: 数据服务的用户名；
- 密码: 数据服务的密码。

目前只支持米筐RQData数据服务（用户名username和密码password不是米筐官网登录用的账号和密码，用户名填写“license”这个字符，密码填写收到的license的内容）。

请注意，选择“elite”数据服务时，可不受米筐同时段只允许一个账号登录的限制。

### 显示

- 字体：设置VeighNa Elite Trader图形界面的字体类型，除了默认的Arial字体，也支持Courier New和System字体；
- 大小：设置VeighNa Elite Trader图形界面的字体大小，用户可以根据自己显示器的实际分辨率对字体大小进行修改。

### 日志

- 启动：控制是否启动LogEngine，默认为True。如果该项修改为False，则后续几项参数都将失效，同时VeighNa Elite Trader运行时不再输出日志或生成日志文件（可以降低部分系统延时）；
- 级别：控制日志输出的级别，日志可以从轻到严重分成DEBUG、INFO、WARNING、ERROR、CRITICAL五个级别，分别对应10、20、30、40、50的整数值。如果日志等级低于该项设置值，将会被忽略。如果想要记录更详细的系统运行信息，建议将该项整数值调低；
- 终端输出：控制是否终端输出；
- 文件输出：该参数用于控制是否要将日志输出到文件中，建议设置为True，否则无法记录生成的日志。

VeighNa Elite Trader的日志文件，默认位于运行时目录的.vntrader\log目录下，完整路径为：
```
C:\users\administrator\.vntrader\log
```

其中，administrator为当前Windows系统的登录用户名。

### 钉钉

- 启动：控制是否运行钉钉消息通知功能，如设为True，则在程序运行过程中的核心系统日志、CTA策略模块日志等，均会发送到下文Token对应的钉钉会话中；
- Token：对应钉钉软件中，某一具体聊天会话的令牌，需要在钉钉会话中添加【自定义机器人】（基于Webhook接入自定义服务）后，在弹出的对话框中获取；
- 密钥：用于对发送到钉钉的消息进行加密处理，同样需要在添加机器人时弹出的对话框中获取；

### 邮件

- 服务器地址: SMTP邮件服务器地址，默认填写了QQ邮箱服务器地址。如果需要使用其他邮箱，需要自行查找一下其他的服务器地址；
- 服务器端口: SMTP邮件服务器端口号，默认填写了QQ邮箱服务器端口；
- 用户名: 填写邮箱地址即可，如xxxx@qq.com；
- 密码: 对于QQ邮箱，此处不是邮箱密码，而是开通SMTP后系统生成的一个授权码；
- 发送邮箱: 与用户名一致；
- 接收邮箱: 接受邮件的邮箱地址。


## 多账户支持

<span id="jump">

### 加载

VeighNa Elite Trader提供了多账户批量下单交易支持（手动）。

以登陆**CTP**接口为例，在登录界面下方的【交易接口】标签页的下拉框中先选中CTP接口。在“自定义接口”处填写自定义的接口名（例如“CTP1”、“CTP2”）之后点击【添加】按钮，填写子账户的配置信息，点击【确定】按钮，则可依次加载对应账户的接口。如下图所示：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/elite/trader/14.png)

添加完毕后，点击登录界面的【登录】按钮登录VeighNa Elite Trader。在菜单栏中依次点击【系统】->【连接xxx】（xxx是自定义的接口名，若加载时填写的“CTP1”，则菜单栏中显示的就是【连接CTP1】），即可连接子账户接口。

连接成功以后，VeighNa Elite Trader主界面【日志】组件会立刻输出登陆相关信息，同时用户也可以看到对应的账号信息，持仓信息等相关信息。

日志组件如下图所示：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/elite/trader/15.png)

资金组件如下图所示：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/elite/trader/25.png)

持仓组件如下图所示：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/elite/trader/26.png)

此时已经可以在【快速交易】界面通过指定的账户进行委托了。

### 创建账户下单组合

如果需要构建账户组合，并为组合内的每个账户分配不同的比例乘数，可以在菜单栏中点击【功能】->【多账户批量下单】，或者点击左侧按钮栏的图标：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/elite/trader/16.png)

即可进入多账户批量下单模块的UI界面，如下图所示：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/elite/trader/17.png)

在“输入下单组合名称”处输出自建组合的名称，点击【添加】按钮，可看见界面左侧已经输出该组合名称，右侧对应接口的下单单元可已经变为可编辑状态。如下图所示：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/elite/trader/23.png)

设定完下单组合之后，点击【修改】按钮保存数据，此时该账户组合就创建成功了。

之后若需修改下单比例，可点击【修改】按钮进行编辑。若需删除指定的下单组合，在左侧界面选中组合，点击【移除】按钮即可完成组合的移除。

### 账户下单组合批量下单

若需通过账户下单组合进行委托，可在【快速交易】接口点击【路由】的下拉框选中指定的下单组合进行委托，如下图所示：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/elite/trader/24.png)

委托完成后，可在【委托】组件和【成交】组件上跟踪到比例下单的委托，如下图所示：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/elite/trader/27.png)

**请注意**：
 - 目前支持同时登录最多登录5个交易账户

</span>
