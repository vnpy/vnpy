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
from vnpy.app.cta_backtester import CtaBacktesterApp

# 写在创建main_engine对象后
main_engine.add_app(CtaBacktesterApp)
```


## 启动模块

启动VN Trader后，在菜单栏中点击【功能】-> 【CTA回测】，或者点击左侧按钮栏的图标

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
- 开始和结束日期
  - 格式为yyyy/mm/dd
  - 如2018/2/25、2021/2/28

</span>

全部填写完成后，点击下方【下载数据】按钮启动下载任务，成功后如下图所示：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/cta_backtester/27.png)

注意下载完成后的历史数据会保存在本地数据库中，后续回测时可以直接使用，无需每次都重复下载。

### 数据来源：RQData（期货、股票、期权）

[RQData](https://www.ricequant.com/welcome/purchase?utm_source=vnpy)提供国内期货、股票以及期权的历史数据。在使用前需要保证RQData已经正确配置（配置方法详见基本使用篇的全局配置部分）。打开CtaBacktester时会自动执行RQData登录初始化，若成功则会输出“RQData数据接口初始化成功”的日志，如下图所示：

 ![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/cta_backtester/26.png)

### 数据来源：数字货币（现货、期货、永续）

各大数字货币交易所都直接提供自家的历史数据下载，但每家交易所可以获取的历史数据长度限制有所区别，注意下载前需要先在VN Trader主界面连接好对应的接口。下载成功如下图所示：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/cta_backtester/60.png)

### 数据来源：IB（外盘期货、股票、外汇等）

Interactive Brokers盈透证券（IB）提供丰富的外盘市场历史数据下载（包括股票、期货、期权、外汇等），注意下载前需要先启动IB TWS交易软件，并在VN Trader主界面连接好IB接口。下载成功如下图所示：

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

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/cta_backtester/31.png)

账户净值表的横轴是时间，纵轴是资金。体现了账户净值在交易时段内随着时间变化的情况。

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/cta_backtester/32.png)

净值回撤表横轴是时间，纵轴是回撤。体现了交易的回撤在交易时段内随着时间变化的情况。

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/cta_backtester/33.png)

每日盈亏表横轴是时间，纵轴是盈亏的资金。体现了交易时段该策略的每日盈亏随着时间变化的情况。

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/cta_backtester/34.png)

盈亏分布表横轴是每日盈亏的数值，纵轴是该盈亏数值的出现概率，体现了每日盈亏在交易时段内的分布情况。



### 统计指标

用于显示回测完成后的相关统计数值，如下图上的结束资金、总收益率、夏普比率、收益回撤比等等。

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/cta_backtester/35.png)

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/cta_backtester/36.png)

- 夏普比率：每承受一单位风险而获得的超额收益；

- 最大回撤：一段周期内从高点下跌到最低点的最大值；

- 收益回撤比：收益率除以百分比最大回撤。



### 详细记录

回测完成后，可点击【委托记录】查询委托细节。

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/cta_backtester/43.png)

如果显示不完整，可以点击鼠标右键，可以看到【调整列宽】按钮，如下图。点击即可进行调整。

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/cta_backtester/46.png)

如需保存委托记录，可点击鼠标右键，可以看到【保存数据】按钮，点击则会弹出下图页面以便保存记录到本地。

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/cta_backtester/42.png)

回测完成后，可点击【成交记录】查询成交细节。鼠标右键操作如上述。

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/cta_backtester/38.png)

回测完成后，可点击【每日盈亏】查询盈亏细节。鼠标右键操作如上述。

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/cta_backtester/39.png)



### K线图表

在回测完毕后，点击【K线图表】按钮即可显示历史K线行情数据（默认1分钟），如下图。绘图耗时可能需要一定时间，请耐心等待一下。

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/cta_backtester/44.png)

K线图表的交易对是基于逐笔对冲配对的，图上会标识有具体的买卖点位 。图表的横轴是时间，纵轴是价格。图表可以通过缩放或拉动来调整横轴的时间，而十字光标控件则是用于显示特定位置的数据细节的。光标移动到哪一个点，就会显示该点的时间和价格，同时左上角还会显示当时时间和高开低收的价格，左下角还会显示此时的交易量。



### 代码编辑

如果想修改策略代码，又不想关闭VN Station修改后再重启，可以点击【代码编辑】按钮。会弹出下图页面。

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/cta_backtester/57.png)

修改完成后，关闭页面时会弹出下图页面，点击【save】即可保存修改后的策略文件。

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/cta_backtester/58.png)



### 策略重载

成功保存后，点击【策略重载】按钮即可重载，同时会有相关日志输出，如下图所示：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/cta_backtester/59.png)





## 参数优化

vnpy提供两种参数优化的解决方案，分别是穷举算法和遗传算法。

### 设置优化参数

优化之前，点击【参数优化】按钮，会弹出“优化参数配置”窗口，需要输入优化的参数名、优化区间以及优化步进，然后选择优化目标，如下图所示：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/cta_backtester/37.png)

点击“总收益率”，会弹出下拉框以供选择优化目标，如下图所示：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/cta_backtester/45.png)



### 穷举算法优化

设置好需要优化的参数后，点击“优化参数配置”窗口下方的【确认】按钮，开始进行调用CPU多核进行多进程并行优化，同时日志会输出相关信息，如下图所示：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/cta_backtester/48.png)

穷举算法遍历全局中的每一个参数组合：遍历的过程即运行一次策略回测，并且返回优化目标数值；然后根据目标数值排序，输出优化结果

注意：穷举算法可以使用multiprocessing库来创建多进程实现并行优化。例如：若用户计算机是2核，优化时间为原来1/2；若计算机是10核，优化时间为原来1/10。



### 遗传算法优化

设置好需要优化的参数后，点击“优化参数配置”窗口下方的【确认】按钮开始进行调用调用deap库的算法引擎进行遗传算法优化，同时日志会输出相关信息，如下图所示：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/cta_backtester/56.png)

遗传算法具体流程如下：

- 先定义优化方向，如总收益率最大化； 
- 然后随机从全局参数组合获取个体，并形成族群； 
- 对族群内所有个体进行评估（即运行回测），并且剔除表现不好个体；
- 剩下的个体会进行交叉或者变异，通过评估和筛选后形成新的族群；（到此为止是完整的一次种群迭代过程）；
- 多次迭代后，种群内差异性减少，整体适应性提高，最终输出建议结果。该结果为帕累托解集，可以是1个或者多个参数组合。

注意：由于用到了@lru_cache, 迭代中后期的速度回提高非常多，因为很多重复的输入都避免了再次的回测，直接在内存中查询并且返回计算结果。



### 优化结果分析

优化结束后，会输出日志提示优化完成，点击【优化结果】按钮可以看出优化结果。

#### 穷举算法：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/cta_backtester/49.png)

下图的参数组合是基于目标数值（总收益率）由高到低的顺序排列的。点击【保存】按钮即可保存优化结果到本地。

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/cta_backtester/50.png)

#### 遗传算法：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/cta_backtester/55.png)

下图的参数组合是基于目标数值（总收益率）最大输出的，而不是像穷举算法一样由高到低进行排序。点击【保存】按钮即可保存优化结果到本地。

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/cta_backtester/54.png)