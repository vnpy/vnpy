# RiskManager - 事前风控模块

## 功能简介

RiskManager模块是用于**事前风险检测与控制**的功能模块。用户可以通过图形界面操作来便捷完成启动风控，参数修改和停止风控等任务。

## 加载启动

### VN Station加载

启动登录VN Station后，点击【VN Trader Pro】按钮，在配置对话框中的【上层应用】栏勾选【RiskManager】。

### 脚本加载

在启动脚本中添加如下代码：

```
# 写在顶部
from vnpy.app.risk_manager import RiskManagerApp

# 写在创建main_engine对象后
main_engine.add_app(RiskManagerApp)
```

## 启动模块

在启动模块之前，请先连接交易接口（连接方法详见基本使用篇的连接接口部分）。看到VN Trader主界面【日志】栏输出“合约信息查询成功”之后再启动模块，如下图所示：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/cta_strategy/1.png)

请注意，IB接口因为登录时无法自动获取所有的合约信息，只有在用户手动订阅行情时才能获取。因此需要在主界面上先行手动订阅合约行情，再启动模块。

成功连接交易接口后，在菜单栏中点击【功能】-> 【交易风控】，或者点击左侧按钮栏的图标：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/risk_manager/1-1.png)

即可进入事前风控模块的UI界面，如下图所示：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/risk_manager/1-2.png)

## 启动风控

事前风控模块负责在委托通过交易API接口发出前，检查其状态是否符合各种风控规则。风控规则包括交易流控、下单数量、活动委托、撤单总数等，具体如下：

 - 委托数量必须大于0
 - 单笔委托的数量上限
 - 当日总成交数量上限
 - 委托流数量上限
 - 当前活动委托次数上限
 - 当日撤单次数上限

在策略运行的过程中，用户可以启动风控，以检查每一笔发出的委托是否符合风控要求：
 * 在【风控运行状态】一栏的下拉框中选择【启动】，如下图所示；
 ![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/risk_manager/1-3.png)
 * 设定各种风控规则的参数后，点击下方的【保存】按钮，即可开始运行风控。每一笔委托必须满足各种风控规则要求，才能通过API接口发送出去。

## 参数修改

事前风控模块允许用户自定义风控参数：
* 用户可以点击输入框右侧的上下箭头来修改参数，也可以直接输入数字来修改，如下图所示。
![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/risk_manager/1-4.png)

## 停止风控
不需要运行风控时，用户可以停止风控：
* 在【风控运行状态】的下拉框中选择【停止】，如下图所示：
![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/risk_manager/1-5.png)
* 点击下方的【保存】按钮。