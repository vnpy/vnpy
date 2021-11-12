# 事前风控模块

交易风控模块属于事前风控，即在委托在通过交易API接口发出去前，需要检查其状态不能超过风控限制，其中包括：
- 委托数量必须大于0
- 单笔委托的数量上限
- 当日总成交数量上限
- 委托流数量上限
- 当前活动委托次数上限
- 当日撤单次数上限

&nbsp;

## 加载启动

进入VN Trader后，首先登陆接口，如连接CTP；然后在菜单栏中点击“功能”->"交易风控“后，会弹出交易风控窗口，如图。
![](https://vnpy-community.oss-cn-shanghai.aliyuncs.com/forum_experience/yazhang/risk_manager/risk_manager.png)

窗口中显示的参数，对应的是C:\Users\Administrator\.vntrader里面risk_manager_setting.json的参数字典，如图。
![](https://vnpy-community.oss-cn-shanghai.aliyuncs.com/forum_experience/yazhang/risk_manager/data_setting.png)

在“风控运行状态”的选择框中点击“启动”后
- 立刻调用RiskManagerEngine类的update_setting()函数读取risk_manager_setting.json的参数字典并且绑定类的属性。
- 在日志中输出"交易风控功能启动"。
- 运行check_risk()函数，去检查每一笔发出去的委托是否符合各种风控要求，若全部满足后，流控计数+1，委托真正通过API接口发送出去。

&nbsp;

## 修改参数

交易风控组件允许用户修改风控参数。由于GUI界面的各参数栏是基于PyQt5的QSpinBox，用户可以用鼠标点击上下箭头来修改，也可以直接键盘输入来修改。

最后点击窗口下方的“保存”按钮，对调用RiskManagerEngine类的save_setting()函数去更新到risk_manager_setting.json的参数字典中，最后通过update_setting()函数把参数字典绑定到类的属性。

&nbsp;

## 停止风控

在“风控运行状态”的选择框中点击“停止后”后，RiskManagerEngine类的active变成False，check_risk()函数不再检查委托的风控流控状态，同时在日志中输出"交易风控功能停止"。

