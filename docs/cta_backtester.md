# CTA回测模块
CTA回测模块是基于PyQt5和pyqtgraph的图形化回测工具。启动VN Trader后，在菜单栏中点击“功能-> CTA回测”即可进入该图形化回测界面，如下图。CTA回测模块主要实现3个功能：历史行情数据的下载、策略回测、参数优化。
![](https://vnpy-community.oss-cn-shanghai.aliyuncs.com/forum_experience/yazhang/cta_backtester/cta_backtester.png)

&nbsp;


## 1.下载数据
数据下载功能是基于RQData的get_price()函数实现的。
```
get_price(order_book_ids, start_date='2013-01-04', end_date='2014-01-04', frequency='1d', fields=None, adjust_type='pre', skip_suspended =False, market='cn')
```


在使用前要保证RQData初始化完毕，然后填写以下4个字段信息：
- 本地代码：格式为合约品种+交易所，如IF88.CFFEX、rb88.SHFE；然后在底层通过RqdataClient的to_rq_symbol()函数转换成符合RQData格式，对应RQData中get_price()函数的order_book_ids字段。
- K线周期：可以填1m、60m、1d，对应get_price()函数的frequency字段。
- 开始日期：格式为yy/mm/dd，如2017/4/21，对应get_price()函数的start_date字段。（点击窗口右侧箭头按钮可改变日期大小）
- 结束日期：格式为yy/mm/dd，如2019/4/22，对应get_price()函数的end_date字段。（点击窗口右侧箭头按钮可改变日期大小）
  
填写完字段信息后，点击下方“下载数据”按钮启动下载程序，下载成功如图所示。

![](https://vnpy-community.oss-cn-shanghai.aliyuncs.com/forum_experience/yazhang/cta_backtester/data_loader.png)



&nbsp;

## 2.加载启动




## 3.策略回测

### 3.1统计数据


### 3.2图表分析



## 4.参数优化



