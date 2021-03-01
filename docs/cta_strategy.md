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

对于用户自行开发的策略，需要放到VN Trader运行时目录下的**strategies**目录中，才能被识别加载。具体的运行时目录路径，可以在VN Trader主界面顶部的标题栏查看。

对于在Windows上默认安装的用户来说，放置策略的strategies目录路径通常为：

```
C:\Users\Administrator\strategies
```

其中Administrator为当前登录Windows的系统用户名。

启动VN Trader后，在菜单栏中点击【功能】-> 【数据管理】，或者点击左侧按钮栏的图标

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/cta_strategy/00.png)

即可进入该图形化历史数据管理界面，如下图所示：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/cta_strategy/2.png)

如果配置了[RQData](https://www.ricequant.com/welcome/purchase?utm_source=vnpy)数据服务的话，打开CtaStrategy时会自动执行RQData登录初始化，若成功则会输出“RQData数据接口初始化成功”的日志，如下图所示：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/cta_strategy/3.png)

在启动模块之前，请先连接交易接口（连接方法详见基本使用篇的连接接口部分）。看到VN Trader主界面【日志】栏输出“合约信息查询成功”之后再启动模块（IB接口没有该日志输出，请先订阅行情再启动模块），如下图所示：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/cta_strategy/1.png)


## 添加策略

用户可以基于编写好的CTA策略来创建不同的策略实例。策略实例的好处在于同一个策略可以同时去运行多个品种合约，并且每个实例的参数可以是不同的。

在创建实例的时候需要配置好相关的参数：

- 实例名称
  - 实例名称不能重名

- 合约品种
  - 格式为合约代码 + 交易所名称（一定要是可以交易的，接口查询能查到的合约名称）
  - 如rb2105.SHFE

- 参数设置

在左上角的下拉框中选择要交易的策略名称，点击【添加策略】，会弹出添加策略对话框。如下图所示：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/cta_strategy/5.png)

配置完毕后，点击【添加】按钮，则开始创建策略实例。成功后如下图所示：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/cta_strategy/7.png)

可观察到此时该策略实例的【inited】和【trading】状态都为“False”。说明此时该策略实例还没有初始化，也还不能发出交易信号。

策略实例创建成功后，该策略实例的配置信息会被保存到.vntrader文件夹下的cta_strategy_setting.json文件中。

### 创建失败

- 如果添加了同名的策略实例，则会创建失败，图形界面输出“创建策略失败，存在重名”的日志信息。如下图所示：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/cta_strategy/9.png)

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/cta_strategy/8.png)

- 如果合约品种没有填交易所名称，则会创建失败，图形界面输出“创建策略失败，本地代码缺失交易所后缀”的日志信息。如下图所示：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/cta_strategy/10.png)

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/cta_strategy/11.png)

- 如果合约品种的填交易所名称填错，则会创建失败，图形界面输出“创建策略失败，本地代码的交易所后缀不正确”的信息。如下图所示：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/cta_strategy/12.png)

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/cta_strategy/13.png)


## 管理策略

### 初始化

策略实例创建成功后，就可以对该实例进行初始化了。

每个策略实例都需要一定的历史数据来进行策略初始化，来确保策略内变量数值的准确性。所以在初始化时，策略实例里的load_bar函数会先去接口获取历史数据。如果接口不提供历史数据，那么就通过RQData来获取。如果没有配置RQData数据服务的话，就会去本地数据库查询。

点击该策略实例下的【初始化】按钮，若初始化成功，则如下图所示：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/cta_strategy/6.png)

可观察到此时该策略实例的【inited】状态已经为“True”,【trading】状态还是“False”。说明此时该策略实例已经调用过load_bar函数加载历史数据完成初始化了，但此时还不能发出交易信号。

### 初始化失败：

- 即使交易所填的是vn.py支持的交易所的名字，成功创建了策略实例。但是如果该合约名字输入错误（比如说大小写写错，合约与交易所对不上或者已经退市），导致在交易的接口找不到该合约，则会初始化失败，图形界面输出“行情订阅失败，找不到合约”的日志。如下图所示：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/cta_strategy/14.png)

- 即使合约代码填写正确，成功创建了策略实例。但是如果此时还没有连接接口，导致在交易的接口找不到该合约，也会初始化失败，图形界面输出“行情订阅失败，找不到合约”的日志。如下图所示：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/cta_strategy/15.png)

- 如果策略内用到了K线时间序列管理模块（ArrayManager）来计算变量指标的值，那么请确保历史数据的长度足够ArrayManager进行初始化（默认的ArrayManager需要100条数据才能初始化成功）。如果历史数据的长度不够ArrayManager初始化，即使图形界面上输出了日志“初始化完成”，该策略实例的初始化也是失败的。

  - 如果策略逻辑是基于示例策略中的一但ArrayManager没有初始化就返回的逻辑写的话，那么由下图可观察到，图形界面左侧策略实例面版下的基于ArrayManager计算的策略指标的值是0。说明此时该策略实例虽然启动之后就能处于可以发出交易信号的状态，但是因为ArrayManager没有初始化成功，该策略实例需要一直等到推进策略实例的数据足够ArrayManager初始化之后，才能开始计算变量指标，进而发出交易信号。
  ![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/cta_strategy/16.png)

  - 如果策略逻辑不是基于示例策略中的一但ArrayManager没有初始化就返回的逻辑写的话，那么此时虽可观察到，图形界面左侧策略实例面版下的策略指标是有数值的。而且此时启动也能处于可以发出交易信号的状态，但是因为ArrayManager没有初始化成功，该策略实例计算出来的变量指标值会是不准确的，进而可能会发出错误的交易信号。

### 启动

策略实例初始化成功后，点击该策略实例下的【启动】按钮，即可启动该策略实例。成功后如下图所示：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/cta_strategy/17.png)

可观察到此时该策略实例的【inited】和【trading】状态都为“True”。说明此时该策略实例已经调用过load_bar函数加载历史数据完成初始化了，而且此时已经处于能发出交易信号的状态了。

策略示例启动成功后，该策略实例的变量信息会被保存到.vntrader文件夹下的cta_strategy_data.json文件中。

### 停止

如果启动策略之后，想要停止、编辑或者移除策略，可以点击策略实例下的【停止】按钮，即可停止该策略实例。成功后如下图所示：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/cta_strategy/18.png)

可观察到此时该策略实例的【trading】状态已变为“False”。说明此时该策略实例不会发出交易信号。

### 编辑

如果启动策略之后，想要修改策略参数，需要先点击策略实例下的【停止】按钮，停止策略。然后点击【编辑】按钮，会弹出参数编辑对话框，以供修改策略参数。如下图所示：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/cta_strategy/4.png)

编辑完策略参数之后，点击下方的【确定】按钮，则可成功修改策略参数。

请注意，此时修改的只是.vntrader文件夹下cta_strategy_setting.json文件中该策略实例的参数值，而没有修改原策略文件下的参数。

修改前，json文件如下图所示：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/cta_strategy/19.png)

修改后，json文件如下图所示：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/cta_strategy/20.png)

### 移除

### 状态跟踪

## 运行日志

### 日志内容

引擎日志

策略日志

### 清空操作


## 停止单

停止单信息


## 批量操作

### 全部初始化

### 全部启动

### 全部停止