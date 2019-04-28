# CTA回测模块
CTA回测模块是基于PyQt5和pyqtgraph的图形化回测工具。启动VN Trader后，在菜单栏中点击“功能-> CTA回测”即可进入该图形化回测界面，如下图。CTA回测模块主要实现3个功能：历史行情数据的下载、策略回测、参数优化。
![](https://vnpy-community.oss-cn-shanghai.aliyuncs.com/forum_experience/yazhang/cta_backtester/cta_backtester.png)

&nbsp;

## 1.加载启动
进入图形化回测界面“CTA回测”后，会立刻完成初始化工作：初始化回测引擎、初始化RQData客户端。

```
    def init_engine(self):
        """"""
        self.write_log("初始化CTA回测引擎")

        self.backtesting_engine = BacktestingEngine()
        # Redirect log from backtesting engine outside.
        self.backtesting_engine.output = self.write_log

        self.write_log("策略文件加载完成")

        self.init_rqdata()

    def init_rqdata(self):
        """
        Init RQData client.
        """
        result = rqdata_client.init()
        if result:
            self.write_log("RQData数据接口初始化成功")
```

&nbsp;


## 2.下载数据
在开始策略回测之前，必须保证数据库内有充足的历史数据。故vnpy提供了历史数据一键下载的功能。
下载数据功能主要是基于RQData的get_price()函数实现的。
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

## 3.策略回测
下载完历史数据后，需要配置以下字段：交易策略、手续费率、交易滑点、合约乘数、价格跳动、回测资金。
这些字段主要对应BacktesterEngine类的run_backtesting函数。
```
def run_backtesting(self, class_name: str, vt_symbol: str, interval: str, start: datetime, end: datetime, rate: float, slippage: float, size: int, pricetick: float, capital: int, setting: dict):
```

点击下方的“开始回测”按钮可以开始回测：
首先会弹出如图所示的参数配置窗口，用于调整策略参数。该设置对应的是run_backtesting()函数的setting字典。
![](https://vnpy-community.oss-cn-shanghai.aliyuncs.com/forum_experience/yazhang/cta_backtester/parameter_setting.png)

点击“确认”按钮后开始运行回测，同时日志界面会输出相关信息，如图。
![](https://vnpy-community.oss-cn-shanghai.aliyuncs.com/forum_experience/yazhang/cta_backtester/backtesting_log.png)

回测完成后会显示统计数字图表。

&nbsp;

### 3.1统计数据
用于显示回测完成后的相关统计数值, 如结束资金、总收益率、夏普比率、收益回撤比
![](https://vnpy-community.oss-cn-shanghai.aliyuncs.com/forum_experience/yazhang/cta_backtester/show_result.png)

&nbsp;

### 3.2图表分析
以下四个图分别是代表账号净值、净值回撤、每日盈亏、盈亏分布。
![](https://vnpy-community.oss-cn-shanghai.aliyuncs.com/forum_experience/yazhang/cta_backtester/show_result_chat.png)


&nbsp;

## 4.参数优化

参数优化功能使用的是穷举算法，即多进程对所有参数组合进行回测，并输出最终解集。其操作流程如下：

- 点击“参数优化”按钮，会弹出“优化参数配置”窗口，用于设置优化目标（如最大化夏普比率、最大化收益回撤比）和设置需要优化的参数以及优化区间，如图
![](https://vnpy-community.oss-cn-shanghai.aliyuncs.com/forum_experience/yazhang/cta_backtester/optimize_setting.png)

- 设置好需要优化的参数后，点击“优化参数配置”窗口下方的“确认”按钮开始进行调用CPU多核进行多进程并行优化，同时日志会输出相关信息。
![](https://vnpy-community.oss-cn-shanghai.aliyuncs.com/forum_experience/yazhang/cta_backtester/optimize_log.png)

- 点击“优化结果”按钮可以看出优化结果，如图的参数组合是基于目标数值（夏普比率）由高到低的顺序排列的。
![](https://vnpy-community.oss-cn-shanghai.aliyuncs.com/forum_experience/yazhang/cta_backtester/optimize_result.png)





