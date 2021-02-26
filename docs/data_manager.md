# DataManager - 历史数据管理模块

历史数据管理模块，是VN Trader内部针对历史数据的全功能管理工具。





## 加载启动

### VN Station加载

启动登录VN Station后，点击VN Trader Pro按钮，在配置对话框中的“上层应用”栏勾选DataManager。



### 脚本加载

在启动脚本中添加如下代码：

```
# 写在顶部
from vnpy.app.data_manager import DataManagerApp

# 写在创建main_engine对象后
main_engine.add_app(DataManagerApp)
```





## 启动模块

启动VN Trader后，在菜单栏中点击【功能】-> 【数据管理】，或者点击左侧按钮栏的图标<img src="https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/data_manager/00.png" style="zoom:50%;" />即可进入该图形化历史数据管理界面，如下图所示：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/data_manager/1.png)





## 下载数据

在查看数据之前，需要保证数据库内有足够的历史数据，故vn.py提供了历史数据一键下载的功能。

点击右上角【下载数据】按钮，会弹出下载历史数据窗口，如下图所示：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/data_manager/2.png)

需要填写代码、交易所、周期、以及开始日期以及四个字段信息。

- 代码：代码格式为合约品种，如IF88、rb88；
- 交易所：合约交易的交易所（点击窗口右侧箭头按钮可选择vn.py支持的所有交易所）；
- 周期：格式为MINUTE（对应一分钟）、HOUR（对应一小时）、DAILY（对应一天）、WEEKLY（对应一周）和TICK（对应一个tick）五个频率（点击窗口右侧箭头按钮可选择频率）；
- 开始和结束日期：格式为yy/mm/dd，如2018/2/25（点击窗口右侧箭头按钮可改变日期大小）。

填写完字段信息后，点击下方【下载】按钮启动下载程序，下载成功如下图所示：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/data_manager/3.png)

 

### RQData（期货、股票、期权）

RQData提供国内期货、股票ETF以及期权的历史数据。在使用前要保证RQData初始化完毕（RQData配置详见基本使用篇的全局配置部分）。



### 数字货币（现货、期货、永续）

数字货币交易所都提供历史数据，但是每个交易所对获取历史数据长度的限制是不同的。下载前需要连接好接口。

在每个接口文件（vnpy.gateway文件夹下）处理收到的合约信息时，如果该接口支持历史数据查询，则history_data会填True，如下图所示：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/cta_backtester/5.png)

如果没有填写该项或填False，则说明该接口不提供历史数据。



### IB（外盘期货、股票、外汇等）

盈透证券提供外盘股票、期货、期权的历史数据， 下载前需要连接好IB接口。

注意IB上的行情数据，除少量免费提供外（外汇、贵金属），其他大部分都需要在IB官网的后台管理系统中付费购买后，才能在VN Trader中订阅使用，进而进行历史数据下载。





## 导入数据

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/data_manager/5.png)

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/data_manager/4.png)

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/data_manager/6.png)





## 查看数据

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/data_manager/7.png)





## 导出数据





## 更新数据

