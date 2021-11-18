# CtaBacktester - CTA回测研究模块

## 功能简介

CtaBacktester是用于**CTA策略历史回测研究**的功能模块，用户可以通过图形界面操作来便捷完成数据下载、历史回测、结果分析和参数优化等任务。

## 加载启动

### VN Station加载

启动登录VN Station后，点击【VN Trader Pro】按钮，在配置对话框中的【上层应用】栏勾选【CtaBacktester】。

### 脚本加载

在启动脚本中添加如下代码：

```
# 写在顶部
from vnpy_ctabacktester import CtaBacktesterApp

# 写在创建main_engine对象后
main_engine.add_app(CtaBacktesterApp)
```


## 启动模块

对于用户自行开发的策略，需要放到VN Trader运行时目录下的**strategies**目录中，才能被识别加载。具体的运行时目录路径，可以在VN Trader主界面顶部的标题栏查看。

对于在Windows上默认安装的用户来说，放置策略的strategies目录路径通常为：

```
C:\Users\Administrator\strategies
```

其中Administrator为当前登录Windows的系统用户名。

启动VN Trader后，在菜单栏中点击【功能】-> 【CTA回测】，或者点击左侧按钮栏的图标：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/cta_backtester/00.png)

即可打开图形化的回测界面，如下图所示：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/cta_backtester/25.png)


## 下载数据

在开始策略回测之前，首先需要保证数据库内有足够的历史数据，CtaBacktester模块也提供了一键下载历史数据的功能。

下载数据需要填写本地代码、K线周期、开始日期以及结束日期四个字段信息：

<span id="jump">

- 本地代码
  - 格式为合约代码 + 交易所名称
  - 如IF888.CFFEX、rb2105.SHFE
- K线周期：
  - 1m（1分钟K线）
  - 1h（1小时K线）
  - d（日K线）
  - w（周K线）
  - tick（一个Tick）
- 开始和结束日期
  - 格式为yyyy/mm/dd
  - 如2018/2/25、2021/2/28

</span>

全部填写完成后，点击下方【下载数据】按钮启动下载任务，成功后如下图所示：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/cta_backtester/27.png)

注意下载完成后的历史数据会保存在本地数据库中，后续回测时可以直接使用，无需每次都重复下载。

### 数据来源：数据服务（期货、股票、期权）

以RQData为例，[RQData](https://www.ricequant.com/welcome/purchase?utm_source=vnpy)提供国内期货、股票以及期权的历史数据。在使用前需要保证数据服务已经正确配置（配置方法详见基本使用篇的全局配置部分）。打开CtaBacktester时会自动执行数据服务登录初始化，若成功则会输出“数据服务初始化成功”的日志，如下图所示：

 ![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/cta_backtester/26.png)

### 数据来源：数字货币（现货、期货、永续）

各大数字货币交易所都直接提供自家的历史数据下载，但每家交易所可以获取的历史数据长度限制有所区别，注意下载前需要先在VN Trader主界面连接好对应的接口。下载成功如下图所示：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/cta_backtester/60.png)

### 数据来源：IB（外盘期货、股票、外汇等）

Interactive Brokers盈透证券（IB）提供丰富的外盘市场历史数据下载（包括股票、期货、期权、外汇等），注意下载前需要先启动IB TWS交易软件，并在VN Trader主界面连接好IB接口，并订阅所需合约行情。下载成功如下图所示：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/cta_backtester/28.png)


## 执行回测

准备好数据后即可开始使用历史数据对策略进行回测研究，回测时需要配置好相关的参数：

- 策略品种
  - 交易策略：在下拉框中选择要回测的策略名称；
  - 本地代码：注意不要漏掉交易所后缀；
- 数据范围
  - 格式详见本章[下载数据](#jump)部分的介绍；
- 交易成本
  - 滑点：下单交易点位与实际交易点位的差别；
  - 百分比手续费：填写数字即可，不要填写百分数；
  - 固定比手续费：可以手续费填0，然后把手续费除以合约乘数后，加在滑点中；
- 合约属性
  - 合约乘数：合约的交易单位；
  - 价格跳动：合约价格的最小变动价位；
  - 回测资金：账户资金；
  - 合约模式：
    - 反向：只有数字货币市场才有的一种特殊衍生品合约规则，是指用计价法币来标识价格，用数字货币来结算盈亏的衍生品合约；
    - 正向：除反向合约外，其他所有的金融市场（股票、期货、期权等）采用的规则。

配置完成后，点击下方的【开始回测】按钮，会弹出策略参数配置对话框，用于设置策略参数，如下图所示：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/cta_backtester/29.png)

点击【确定】按钮后开始执行回测任务，同时日志界面会输出相关信息，如下图所示：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/cta_backtester/10.png)

回测完成后，会自动在右侧区域显示策略回测业绩的统计指标以及相关图表：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/cta_backtester/30.png)

若数据库没有准备好所需的历史数据就点击【开始回测】，则日志界面会输出“历史数据不足，回测终止”的日志，如下图所示：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/cta_backtester/15.png)


## 结果分析

### 业绩图表

右侧的业绩图表由以下四张子图构成：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/cta_backtester/31.png)

【账户净值】图的横轴是时间，纵轴是资金，体现了账户净值在交易时段内随着交易日变化的情况。

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/cta_backtester/32.png)

【净值回撤】图的横轴是时间，纵轴是回撤，体现了净值从最近高点回撤程度随着交易日变化的情况。

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/cta_backtester/33.png)

【每日盈亏】图的横轴是时间，纵轴是日盈亏的金额（采用逐日盯市规则以收盘价结算），体现了整个回测周期内策略的每日盈亏变化情况。

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/cta_backtester/34.png)

【盈亏分布】图的横轴是每日盈亏的数值，纵轴是该盈亏数值的出现概率，体现了整体每日盈亏的概率分布情况。

### 统计指标

统计指标区域用于显示策略历史回测业绩的相关统计数值，如下图所示：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/cta_backtester/35.png)

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/cta_backtester/36.png)

根据数据类型，指标可以分类为：

- 日期信息
  - 首个交易日
  - 最后交易日
  - 总交易日
  - 盈利交易日
  - 亏损交易日
- 资金盈亏
  - 起始资金
  - 结束资金
  - 总收益率
  - 年化收益
  - 最大回撤
  - 百分比最大回撤
  - 总盈亏
- 交易成本
  - 总手续费
  - 总滑点
  - 总成交额
  - 总成交笔数
- 日均数据
  - 日均盈亏
  - 日均手续费
  - 日均滑点
  - 日均成交额
  - 日均成交笔数
  - 日均收益率
  - 收益标准差（日均）
- 绩效评价
  - 夏普比率
  - 收益回撤比

### 详细信息

回测完成后，可点击左侧区域的【委托记录】按钮，查看回测过程中策略逐笔委托的细节信息：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/cta_backtester/43.png)

如果发现表格内容显示不完整，可以单击鼠标右键弹出菜单后，选择【调整列宽】按钮，即可进行自动列宽缩放：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/cta_backtester/46.png)

表格也支持一键将表内全部内容保存为CSV文件，在上一步右键弹出的菜单中，点击【保存数据】按钮，即可弹出如下图所示选择保存文件名的对话框：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/cta_backtester/42.png)

回测过程中策略发出委托的**成交价**不一定是原始下单的价格，而要由回测引擎基于当时的行情数据和下单价格进行撮合后算出，每笔委托对应的具体成交细节可以点击【成交记录】按钮后查看：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/cta_backtester/38.png)

点击【每日盈亏】按钮后，可以看到如下图所示的策略每日盈亏细节：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/cta_backtester/39.png)

这里每日盈亏的统计采用期货市场普遍使用的逐日盯市（Marking-to-Market）规则进行计算：

- 持仓盈亏：今日开盘持仓的部分，以昨收盘价开仓，今收盘价平仓，计算出的盈亏金额；
- 交易盈亏：今日日内成交的部分，以成交价格开仓，今收盘价平仓，计算出的盈亏金额；
- 总盈亏：汇总持仓盈亏和交易盈亏后的金额；
- 净盈亏：总盈亏扣除手续费和滑点后的金额，也是最终计算显示四张图表时用到的每日盈亏金额。

### K线图表

点击【K线图表】按钮，即可打开用于显示回测K线数据，以及策略具体买卖点位置的图表，如下图所示：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/cta_backtester/44.png)

注意绘图耗时可能需要一定时间（通常在数十秒到几分钟），请耐心等待。

K线图表中的图例说明可以在窗口底部看到，整体上采用了国内市场标准的配色和风格。开平仓之间的连线采用的是逐笔配对（First-in, First-out）规则进行绘制，每一笔成交会根据其数量自动和其他成交进行匹配，即使策略有复杂的加减仓操作也能正确绘制。


## 参数优化

对于开发好的策略，可以使用CtaBacktester内置的优化算法快速进行参数寻优，目前支持穷举和遗传两种优化算法。

### 设置优化参数

点击【参数优化】按钮，会弹出“优化参数配置”的窗口：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/cta_backtester/37.png)

点击【目标】下拉框，选择优化过程中要使用的目标函数（即以该数值最大化为目标进行优化）：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/cta_backtester/45.png)

对于要进行优化的策略参数，需要配置：

- 【开始】和【结束】：用于给定参数优化的范围；
- 【步进】：用于给定参数每次变化的数值；

举例：如一个参数的【开始】设为10，【结束】设为20，【步进】设为2，则该参数在优化过程中的寻优空间为：10、12、14、16、18、20。

对于要设置固定数值的策略参数，请将【开始】和【结束】都同样设为该数值即可。

### 穷举算法优化

设置好需要优化的参数后，点击窗口底部的【多进程优化】按钮，此时CtaBacktester会调用Python的multiprocessing模块，根据当前电脑CPU的核心数量，启动对应数量的进程来并行执行穷举优化任务。

在优化的过程中，穷举算法会遍历参数寻优空间中的每一个组合。遍历的过程即使用该组合作为策略参数运行一次历史回测，并返回优化目标函数的数值。完成遍历后，根据所有目标函数的数值进行排序，从而选出最优的参数组合结果。

穷举算法优化的效率和CPU核心数量直接相关：若用户计算机是2核，则优化时间为单核的1/2；若计算机是10核，则优化时间会大幅降低到单核的1/10。

### 遗传算法优化

设置好需要优化的参数后，点击窗口底部的【遗传算法优化】按钮，此时CtaBacktester会调用Python的multiprocessing模块和deap模块，来执行高效智能化的多进程遗传算法优化任务。

附上遗传算法的简要工作原理：

1. 定义优化方向，如总收益率最大化； 
2. 随机从全局寻优空间中，选择出部分参数组合形成初始族群； 
3. 对族群内所有个体进行评估，即运行回测获取目标函数结果；
4. 基于目标函数结果进行排序，剔除表现不好的个体（参数组合）；
5. 对剩下的个体进行交叉或者变异，通过评估和筛选后形成新的族群；
6. 以上3-5步为一次完整的种群迭代，在整个优化过程中需要多次重复；
7. 多次迭代后，种群内差异性减少，参数收敛向最优解，最终输出结果。

注意以上结果为遗传算法优化的帕累托解集，可以是1个或者数个参数组合，而不会像穷举算法包含全部参数组合。

### 优化结果分析

优化完成后，会在日志区域输出信息提示：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/cta_backtester/49.png)

此时点击【优化结果】按钮即可查看相关结果：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/cta_backtester/50.png)

上图中的参数优化结果，基于启动优化任务时所选的目标函数【总收益率】的数值，由高到低进行了排序。

最后，点击右下角的【保存】按钮即可将优化结果保存到本地CSV文件中，便于后续分析使用。


## 策略代码

### 代码编辑

VN Trader内置了轻量级策略编辑器，在CtaBacktester界面左上角的下拉框中选择策略后，点击左下角的【代码编辑】按钮，即可打开：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/cta_backtester/57.png)

该编辑器基于Qscitinlla开发，提供常规的语法高亮、自动补全、代码折叠等功能，同时也可以通过按住Ctrl键滚动鼠标滚轮来进行字体大小的缩放。

修改完成后，点击窗口右上角关闭按钮时会弹出下图对话框，需要选择【Save】按钮保存修改后的策略文件：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/cta_backtester/58.png)

### 策略重载

当用户在CtaBacktester打开时，对策略源代码进行修改后（不管是用内置的策略编辑器，还是外部编辑器，如VSCode），此时的修改尚停留在硬盘上的代码文件层面，内存中依然是修改前的策略代码。

想让修改内容在内存中立即生效，需要点击左下角的【策略重载】按钮，此时CtaBacktester会自动扫描并重新加载所有策略文件中的策略代码，同时会有相关日志输出，如下图所示：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/cta_backtester/59.png)

重载刷新完成后，再运行回测或者优化时，使用的就是修改后的策略代码了。
