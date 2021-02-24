# CtaBacktester - CTA回测研究模块

## 启动模块

CTA回测研究模块是基于PyQt5和pyqtgraph的图形化回测工具。

在桌面双击VN Station图标，登录后点击VN Trader Pro，在VN Trader配置界面的“上层应用”栏勾选CtaBacktester。启动VN Trader后，在菜单栏中点击“功能-> CTA回测”或者直接点击CtaBacktester(CTA回测研究模块)的图标<img src="https://www.hualigs.cn/image/6034a02aa88be.jpg" style="zoom: 50%;" />即可进入该图形化回测界面，如下图。

![](https://www.hualigs.cn/image/6034a4dfcfa6e.jpg)





## 下载数据

在开始策略回测之前，必须保证数据库内有充足的历史数据。故vnpy提供了历史数据一键下载的功能。

下载数据需要填写本地代码/K线周期/开始日期以及结束日期四个字段信息（格式详见【执行回测】-【数据范围】部分的介绍），填写完字段信息后，点击下方“下载数据”按钮启动下载程序，下载成功如图所示。

 <img src="https://www.hualigs.cn/image/6034b0021eda4.jpg" style="zoom: 67%;" />



### RQData（期货、股票、期权）

RQData提供国内期货、股票ETF以及期权的历史数据。在使用前要保证RQData初始化完毕（RQDATA配置详见基本使用篇的【全局配置】部分），若RQData初始化成功，界面则会输出“RQData数据接口初始化成功“的日志，如下图。

 <img src="https://www.hualigs.cn/image/6034af5a273f1.jpg" style="zoom:67%;" />

请注意，为了标准化合约名称和K线周期的使用，vnpy通过RQData获取历史数据时填入的是vnpy的标准写法。没有直接使用RQData的规则，底层对相关字段进行了转换。如果不通过vnpy，去RQData自行获取历史数据，请参照RQData的API文档进行操作。



### 数字货币（现货、期货、永续）

数字货币交易所大多都提供历史数据，但是每个交易所对获取历史数据长度的限制是不同的。以下接口都是提供历史数据查询的：binance/binances/bitfinex/bitmex/bitstamp/bybit/coinbase/gateios/huobi/huobif/huobio/huobis/okex/okexf/okexo/okexs

下载成功如图所示。

 <img src="https://www.hualigs.cn/image/6034c40021a48.jpg" style="zoom:67%;" />

在每个接口文件（vnpy.gateway文件夹下）处理收到的合约信息时，如果该接口支持历史数据查询，则history_data会填True，如下图。如果没有填写该项或填False, 则说明该接口不提供历史数据。

 <img src="https://www.hualigs.cn/image/6034ba561a077.jpg" style="zoom:80%;" />



### IB（外盘期货、股票、外汇等）

盈透证券提供外盘股票、期货、期权的历史数据。 下载前必须连接好IB接口。需要注意IB上的行情数据，除少量免费提供外（外汇、贵金属），其他大部分都需要在IB官网的后台管理系统中付费购买后，才能在VN Trader中订阅使用，进而进行历史数据下载。下载成功如图所示。

 <img src="https://www.hualigs.cn/image/6034c3192b219.jpg" style="zoom:67%;" />



## 执行回测

下载完历史数据后，需要配置以下字段：交易策略、手续费率、交易滑点、合约乘数、价格跳动、回测资金才能进行回测。

若数据库已存在历史数据，无需重复下载，直接从本地数据库中导入数据进行回测。点击下方的“开始回测”按钮可以开始回测： 首先会弹参数配置窗口，用于调整策略参数。

点击“确认”按钮后开始运行回测，同时日志界面会输出相关信息，回测完成后会显示统计数字图表。



### 数据范围

本地代码：格式为合约品种+交易所，如IF88.CFFEX、rb88.SHFE；

K线周期：可以填1m、1h、d、w，分别对应一分钟，一小时，一天和一周的频率；

开始和结束日期：格式为yy/mm/dd，如2018/2/24（点击窗口右侧箭头按钮可改变日期大小）。

### 交易成本

滑点：

百分比手续费：

固定比手续费：

### 合约属性

合约乘数：

价格跳动：

回测资金：





## 结果分析

### 业绩图表

资金曲线

 <img src="https://www.hualigs.cn/image/6034cf77ef159.jpg" style="zoom: 70%;" />

最大回撤

 <img src="https://www.hualigs.cn/image/6034cfb17c0e2.jpg" style="zoom: 70%;" />

每日盈亏

 <img src="https://www.hualigs.cn/image/6034cfee8ba6f.jpg" style="zoom:70%;" />

盈亏分布

 <img src="https://www.hualigs.cn/image/6034d012c8e97.jpg" style="zoom:70%;" />

### 统计指标


### 详细记录

委托记录

成交记录

每日盈亏

### K线图表

绘图耗时较长

逐笔对冲配对

图例成分说明





## 参数优化

### 设置优化参数

### 穷举算法优化

### 遗传算法优化

### 优化结果分析
