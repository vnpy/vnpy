# RiskManager - 事前风控模块

## 功能简介

RiskManager模块是用于**事前风险检测与交易控制**的功能模块，用户可以通过图形界面操作来便捷完成启动风控，参数修改和停止风控等任务。

## 加载启动

### VN Station加载

启动登录VN Station后，点击【VN Trader Pro】按钮，在配置对话框中的【上层应用】栏勾选【RiskManager】。

### 脚本加载

在启动脚本中添加如下代码：

```python 3
    # 写在顶部
    from vnpy_riskmanager import RiskManagerApp

    # 写在创建main_engine对象后
    main_engine.add_app(RiskManagerApp)
```

## 启动模块

在菜单栏中点击【功能】-> 【交易风控】，或者点击左侧按钮栏的图标：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/risk_manager/1-1.png)

即可进入事前风控模块的UI界面，如下图所示：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/risk_manager/1-2.png)


## 启动风控

事前风控模块负责在委托通过交易API接口发出前，检查其状态是否符合各种风控规则。风控规则包括交易流控、下单数量、活动委托、撤单总数等，具体如下：

 - 委托流控相关：
   - 委托流控上限：给定时间窗口内最多允许发出的委托笔数
   - 委托流控清空：每隔多少秒清零上述统计的委托笔数
 - 单笔委托上限：每一笔委托允许的最大下单量
 - 总成交上限：今天日内允许的最大总成交笔数（注意不是委托笔数）
 - 活动委托上限：允许的处于活动状态（提交中、未成交、部分成交）最大委托数量
 - 合约撤单上限：今天日内允许的单合约撤单次数上限（每个合约独立统计）

推荐每天在运行自动交易前启动事前风控，以检查每一笔发出的委托是否符合风控要求：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/risk_manager/1-3.png)

1. 在【风控运行状态】一栏的下拉框中选择【启动】；
2. 设定各种风控规则的参数后，点击下方的【保存】按钮，即可开始运行风控；
3. 此时系统内的每一笔委托，都需要满足全部风控要求（不超过限制）后，才能通过底层接口发出。


## 参数修改

事前风控模块允许用户自定义风控参数：

* 用户可以点击输入框右侧的上下箭头来修改参数，也可以直接输入数字来修改，如下图所示。
![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/risk_manager/1-4.png)
* 修改后请点击【保存】按钮生效。

## 停止风控

不需要运行风控时，用户可以停止风控：

* 在【风控运行状态】的下拉框中选择【停止】，如下图所示：
![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/risk_manager/1-5.png)
* 点击下方的【保存】按钮即可停止对委托的风控检查。
