# DataManager - 历史数据管理模块

## 功能简介

DataManager是用于**历史数据管理**的功能模块，用户可以通过图形界面操作来便捷完成数据下载、数据查看、数据导入和数据导出等任务。

## 加载启动

### VN Station加载

启动登录VN Station后，点击【VN Trader Pro】按钮，在配置对话框中的【上层应用】栏勾选【DataManager】。

### 脚本加载

在启动脚本中添加如下代码：

```
# 写在顶部
from vnpy_datamanager import DataManagerApp

# 写在创建main_engine对象后
main_engine.add_app(DataManagerApp)
```


## 启动模块

启动VN Trader后，在菜单栏中点击【功能】-> 【数据管理】，或者点击左侧按钮栏的图标：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/data_manager/00.png)

即可进入历史数据管理UI界面，如下图所示：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/data_manager/1.png)


## 下载数据

DataManager模块提供了一键下载历史数据的功能，点击右上角【下载数据】按钮，会弹出下载历史数据窗口，如下图所示：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/data_manager/2.png)

需要填写代码、交易所、周期以及开始日期四个字段信息：

<span id="jump">

- 代码
  - 代码格式为合约品种
  - 如IF888、rb2105
- 交易所：
  - 合约交易的交易所（点击窗口右侧箭头按钮可选择vn.py支持的所有交易所）
- 周期：
  - MINUTE（1分钟K线）
  - HOUR（1小时K线）
  - DAILY（日K线）
  - WEEKLY（周K线）
  - TICK（一个Tick）
- 开始日期
  - 格式为yy/mm/dd
  - 如2018/2/25

</span>

全部填写完成后，点击下方【下载】按钮启动下载程序，下载成功如下图所示：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/data_manager/3.png)

注意下载完成后的历史数据会保存在本地数据库中，后续回测或实盘时可以直接使用，无需每次都重复下载。

### 数据来源：RQData（期货、股票、期权）

[RQData](https://www.ricequant.com/welcome/purchase?utm_source=vnpy)提供国内期货、股票以及期权的历史数据。在使用前需要保证RQData已经正确配置（配置方法详见基本使用篇的全局配置部分）。

### 数据来源：数字货币（现货、期货、永续）

各大数字货币交易所都直接提供自家的历史数据下载，但每家交易所可以获取的历史数据长度限制有所区别，注意下载前需要先在VN Trader主界面连接好对应的接口。

### 数据来源：IB（外盘期货、股票、外汇等）

Interactive Brokers盈透证券（IB）提供丰富的外盘市场历史数据下载（包括股票、期货、期权、外汇等），注意下载前需要先启动IB TWS交易软件，并在VN Trader主界面连接好IB接口，并订阅所需合约行情。


## 导入数据

如果已经从其他渠道获取到了CSV格式的数据文件，可以通过DataManager的数据导入功能，将其快速导入vn.py数据库。点击右上角的【导入数据】按钮，会弹出从如下图所示的对话框：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/data_manager/16.png)

点击顶部的【选择文件】按钮，会弹出窗口选择要导入的CSV文件路径，如下图所示：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/data_manager/5.png)

然后配置数据导入的相关细节：

- 合约信息
  - 格式详见本章[下载数据](#jump)部分的介绍；
  - 请注意，导入的合约代码（symbol）和交易所（exchange）两个字段组合起来，才能构成在CTA回测等模块中使用的本地代码（vt_symbol）；
  - 若合约代码为**IF2003**，交易所选择**CFFEX**（中金所），则在CtaBacktester中回测要用到的本地代码应为**IF2003.CFFEX**；
- 表头信息
  - 可查看CSV文件的表头信息，并将对应的表头字符串输入在表头信息中；
  - 对于CSV文件中不存在的字段（如股票数据没有【持仓量】字段），请留空即可；
- 格式信息
  - 采用Python内置库datetime模块的时间格式定义，来解析时间戳字符串；
  - 默认时间格式为"%Y-%m-%d %H:%M:%S"，对应的是"2017-1-3 0:00:00"；
  - 如果时间戳是"2017-1-3  0:00"，那么时间格式应该是"%Y-%m-%d %H:%M"。
  
填写完毕，则如下图所示：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/data_manager/4.png)

点击【确定】按钮，开始从CSV文件导入数据到数据库中。导入过程中界面会处于半卡住的情况，CSV文件越大（数据量越多），卡住的时间也会越长。成功载入之后，会弹出窗口显示载入成功，如下图所示：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/data_manager/6.png)


## 查看数据

目前VN Trader中获取数据的方式一共有三种：

- 通过RQData或者交易接口下载

- 从CSV文件导入

- 使用DataRecorder模块录制

不管采用何种方法获取数据，点击左上角的【刷新】按钮，即可看到当前数据库中已有数据的统计情况。刷新过程中界面可能会有偶尔的卡顿，通常对于越多的数据，卡顿的时间也会越长。刷新成功之后，如下图所示：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/data_manager/7.png)

点击【查看】按钮，则会弹出选择数据要查看数据区间的对话框，如下图所示：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/data_manager/10.png)

选择好要显示的数据范围后，点击【确定】按钮即可在右侧表格中看到每个时间点上具体的数据字段：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/data_manager/11.png)

在数据库已有数据的前提下，点击表格最左侧【数据】列下的数据频率前的小箭头，则可展开或收起该数据频率下的合约信息显示。

若表格的右侧区域显示不完整，可拖动界面底端的横向滚动条进行调整。


## 导出数据

如果想导出数据库中的数据到本地CSV文件，则可选择要导出的合约，点击该合约所在行右侧的【导出】按钮后，会弹出选择数据区间对话框，如下图所示：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/data_manager/8.png)

选择要导出的数据区间范围，点击【确定】后，会再次弹出对话框选择输出文件的位置，如下图所示：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/data_manager/9.png)

选择好导出文件要放置的目录，填写完CSV文件名之后，点击【保存】按钮即可完成CSV文件的导出。


## 删除数据

若想删除特定合约数据，则可选择要删除的合约，点击该合约行数据右侧的【删除】按钮后，会弹出对话框，如下图所示：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/data_manager/12.png)

点击【OK】按钮即可删除该合约数据，并弹出删除成功窗口，如下图所示：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/data_manager/13.png)

此时再点击【刷新】按钮，图形界面上已经没有该合约的信息了，如下图所示：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/data_manager/14.png)


## 更新数据

在用户**配置了RQData数据服务**或者**交易接口（已连接）提供充足的历史数据**的情况下，点击右上角的【更新数据】按钮，即可基于数据库中已有的合约数据，执行一键自动下载更新。

更新前图形界面显示如下图：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/data_manager/17.png)

点击【更新数据】按钮，会弹出更新进度的信息提示对话框，如下图所示：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/data_manager/19.png)

此时DataManager会自动**从数据库中已有数据的结束日期开始，下载截止到当前最新日期**的数据，并更新到数据库中。

如果需要更新的数据较少，则可能瞬间完成更新任务，此时没有观察到更新对话框也是正常的。

更新完成后，点击左上角【刷新】按钮，即可看到该合约数据已更新至当前最新日期。

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/data_manager/18.png)

## 数据范围

请注意，虽然界面上显示了数据库中已有数据的开始和结束时间，**但并不代表数据库中储存了从开始时间到结束时间之间所有的数据**。

如果依赖于交易接口提供的历史数据，一但开始时间和结束时间之间的时间跨度超过接口所能提供的数据范围，就可能导致数据之间出现缺失的情况。因此建议更新数据之后，点击【查看】按钮检查一下该合约数据是否连续。