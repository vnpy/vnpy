# CtaBacktester - CTA回测研究模块

## 启动模块

CTA回测研究模块是基于PyQt5和pyqtgraph的图形化回测工具。

在桌面双击VN Station图标，登录后点击VN Trader Pro，在VN Trader配置界面的“上层应用”栏勾选CtaBacktester。启动VN Trader后，在菜单栏中点击“功能-> CTA回测”或者直接点击CtaBacktester（CTA回测研究模块）的图标<img src="https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/cta_backtester/00.png" style="zoom:50%;" />即可进入该图形化回测界面，如下图。

<img src="https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/cta_backtester/1.png" />





## 下载数据

在开始策略回测之前，必须保证数据库内有充足的历史数据。故vn.py提供了历史数据一键下载的功能。

下载数据需要填写本地代码、K线周期、开始日期以及结束日期四个字段信息（格式详见【执行回测】-【数据范围】部分的介绍），填写完字段信息后，点击下方“下载数据”按钮启动下载程序，下载成功如图所示。

 <img src="https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/cta_backtester/3.png" style="zoom:67%;" />



### RQData（期货、股票、期权）

RQData提供国内期货、股票ETF以及期权的历史数据。在使用前要保证RQData初始化完毕（RQData配置详见基本使用篇的【全局配置】部分），若RQData初始化成功，界面则会输出”RQData数据接口初始化成功“的日志，如下图。

 <img src="https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/cta_backtester/2.png" style="zoom:67%;" />



### 数字货币（现货、期货、永续）

数字货币交易所大多都提供历史数据，但是每个交易所对获取历史数据长度的限制是不同的。以下接口都是提供历史数据查询的：binance/binances/bitfinex/bitmex/bitstamp/bybit/coinbase/gateios/huobi/huobif/huobio/huobis/okex/okexf/okexo/okexs

下载成功如图所示。

 <img src="https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/cta_backtester/7.png" style="zoom:67%;" />

在每个接口文件（vnpy.gateway文件夹下）处理收到的合约信息时，如果该接口支持历史数据查询，则history_data会填True，如下图。如果没有填写该项或填False，则说明该接口不提供历史数据。

 <img src="https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/cta_backtester/5.png" style="zoom:80%;" />



### IB（外盘期货、股票、外汇等）

盈透证券提供外盘股票、期货、期权的历史数据。 下载前必须连接好IB接口。需要注意IB上的行情数据，除少量免费提供外（外汇、贵金属），其他大部分都需要在IB官网的后台管理系统中付费购买后，才能在VN Trader中订阅使用，进而进行历史数据下载。下载成功如图所示。

 <img src="https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/cta_backtester/6.png" style="zoom:67%;" />





## 执行回测

下载完历史数据后，需要配置以下字段：交易策略、手续费率、交易滑点、合约乘数、价格跳动、回测资金以及合约模式才能进行回测。

若数据库已存在历史数据，无需重复下载，直接从本地数据库中导入数据进行回测。点击下方的”开始回测”按钮可以开始回测： 首先会弹出参数配置窗口，用于调整策略参数，如下图。

 <img src="https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/cta_backtester/8.png" style="zoom:80%;" />

点击“确认”按钮后开始运行回测，同时日志界面会输出相关信息，若回测成功则输出日志如下图。

   <img src="https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/cta_backtester/10.png" style="zoom:80%;" />

回测完成后会显示统计指标以及业绩图表。

<img src="https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/cta_backtester/4.png"  />

若数据库没有历史数据就点击“开始回测“，则日志界面会输出”历史数据不足，回测终止“的日志，如下图。

   <img src="https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/cta_backtester/15.png" style="zoom:80%;" />



### 数据范围

本地代码：格式为合约品种+交易所，如IF88.CFFEX、rb88.SHFE；

K线周期：可以填tick、1m、1h、d、w，分别对应一个tick，一分钟，一小时，一天和一周的频率；

开始和结束日期：格式为yy/mm/dd，如2018/2/24（点击窗口右侧箭头按钮可改变日期大小）。

### 交易成本

滑点：下单交易点位与实际交易点位的差别；

百分比手续费：填写数字即可，不要填写百分数；

固定比手续费：可以手续费填0，然后把手续费除以合约乘数后，加在滑点中。

### 合约属性

合约乘数：合约的交易单位；

价格跳动：合约价格的最小变动价位；

回测资金：账户资金；

合约模式：可选”正向“或”反向“。（反向合约：只有数字货币市场（或称“币圈”）才有的一种特殊衍生品合约规则。是指用计价法币来标识价格，用数字货币来结算盈亏的衍生品合约；正向合约：除了反向合约以外，其他所有的金融市场（股票、期货、期权等）采用的规则。）





## 结果分析

### 业绩图表

账户净值

  <img src="https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/cta_backtester/11.png" style="zoom:70%;" />

净值回撤

   <img src="https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/cta_backtester/12.png" style="zoom:70%;" />

每日盈亏

   <img src="https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/cta_backtester/13.png" style="zoom:70%;" />

盈亏分布

   <img src="https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/cta_backtester/14.png" style="zoom:70%;" />



### 统计指标

用于显示回测完成后的相关统计数值，如下图上的结束资金、总收益率、夏普比率、收益回撤比等等。

   <img src="https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/cta_backtester/16.png" style="zoom:80%;" />

 <img src="https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/cta_backtester/17.png" style="zoom:80%;" />




### 详细记录

回测完成后，可点击“委托记录”查询委托细节。

<img src="https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/cta_backtester/19.png"  />

回测完成后，可点击“成交记录”查询成交细节。

<img src="https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/cta_backtester/18.png"  />

回测完成后，可点击“每日盈亏”查询盈亏细节。

<img src="https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/cta_backtester/20.png"  />

### K线图表

在回测完毕后，点击“K线图表”按钮即可显示历史K线行情数据（默认1分钟），如下图。绘图耗时可能需要一定时间，请耐心等待一下。

<img src="https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/cta_backtester/21.png"  />

K线图表的交易对是基于逐笔对冲配对的，图上会标识有具体的买卖点位 。图表的横轴是时间，纵轴是价格。图表可以通过缩放或拉动来调整横轴的时间，而十字光标控件则是用于显示特定位置的数据细节的。光标移动到哪一个点，就会显示该点的时间和价格，同时左上角还会显示当时时间和高开低收的价格，左下角还会显示此时的交易量。





## 参数优化

vnpy提供2种参数优化的解决方案，分别是穷举算法和遗传算法。

### 设置优化参数

优化之前，点击“参数优化”按钮，会弹出“优化参数配置”窗口，需要输入优化的参数名、优化区间、优化步进，以及优化目标，如图。

### 穷举算法优化

设置好需要优化的参数后，点击“优化参数配置”窗口下方的“确认”按钮开始进行调用CPU多核进行多进程并行优化，同时日志会输出相关信息。

### 遗传算法优化

设置好需要优化的参数后，点击“优化参数配置”窗口下方的“确认”按钮开始进行调用调用deap库的算法引擎进行遗传算法优化，同时日志会输出相关信息。

### 优化结果分析

点击“优化结果”按钮可以看出优化结果，如图的参数组合是基于目标数值（夏普比率）由高到低的顺序排列的。