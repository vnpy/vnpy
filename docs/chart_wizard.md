# ChartWizard - 实时K线图表模块


## 功能简介

ChartWizard是用于**实时K线图表展示**的功能模块，用户可以通过其UI界面查看实时和历史K线行情，目前只支持显示1分钟级别的K线数据，实时K线（最新的一根K线）为Tick级刷新。


## 加载启动

### VN Station加载

启动登录VN Station后，点击【VN Trader Pro】按钮，在配置对话框中的【上层应用】栏勾选【ChartWizard】。

### 脚本加载

在启动脚本中添加如下代码：

```
# 写在顶部
from vnpy.app.chart_wizard import ChartWizardApp

# 写在创建main_engine对象后
main_engine.add_app(ChartWizardApp)
```


## 启动模块

在启动模块之前，请先连接交易接口（连接方法详见基本使用篇的连接接口部分）。看到VN Trader主界面【日志】栏输出“合约信息查询成功”之后再启动模块，如下图所示：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/cta_strategy/1.png)

请注意，IB接口因为登录时无法自动获取所有的合约信息，只有在用户手动订阅行情时才能获取。因此需要在主界面上先行手动订阅合约行情，再启动模块。

由于vn.py本身并不提供任何数据服务，对于K线图表绘制过程中用到的历史数据，国内期货历史数据由[RQData](https://www.ricequant.com/welcome/purchase?utm_source=vnpy)数据服务提供，用户需要准备和配置RQData账号（配置方法详见基本使用篇的全局配置部分）。数字货币历史数据则直接由交易所接口提供，用户无需进行额外配置。

成功连接交易接口后，在菜单栏中点击【功能】-> 【K线图表】，或者点击左侧按钮栏的图标：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/chart_wizard/1.png)

即可进入实时K线图表模块的UI界面，如下图所示：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/chart_wizard/2.png)


## 新建图表

打开图表窗口后，在【本地代码】编辑框中输入合约代码（注意本地代码由代码前缀和交易所后缀两部分组成，如rb2112.SHFE）。

点击【新建图表】的按钮，即可创建对应合约的K线图表，如下图所示：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/chart_wizard/3.png)

用户可以新建多个合约的K线图表，通过切换窗口来实现快速切换： 

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/chart_wizard/4.png)


## 查看图表

每个合约的图表分为上下两块子图区域：

- 上面的子图为行情K线；
- 下面的子图为成交量数据。

图表上的十字光标可用于定位和显示特定时间点的具体数据，在X轴和Y轴上均会对应数据点的标签，同时在左上角也会显示此根K线的OHLCV等信息。

其他快捷操作：

- 可以通过鼠标左键的拖拽，左右平移K线图显示的时间范围；
- 可以通过鼠标滚轮的滚动，放大和缩小K线图显示的时间范围。

