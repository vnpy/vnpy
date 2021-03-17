# RiskManager - 事前风控模块

## 功能简介

事前风控模块是用于**事前风险检测**的模块，负责在委托通过交易API接口发出前，检查其状态是否超过风控限制。 

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

在启动模块之前，请先连接交易接口（连接方法详见基本使用篇的连接接口部分）。成功连接交易接口后，在菜单栏中点击【功能】-> 【交易风控】，或者点击左侧按钮栏的图标：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/risk_manager/1.png)

即可弹出RiskManager的图形窗口，如下图所示：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/risk_manager/2.png)

## 运行风控

RiskManager模块提供包括交易流控、下单数量、活动委托、撤单总数等风控规则的统计和管理，具体如下：

 - 委托数量必须大于0
 - 单笔委托的数量上限
 - 当日总成交数量上限
 - 委托流数量上限
 - 当前活动委托次数上限
 - 当日撤单次数上限

窗口中显示的参数，对应的是位于C:\Users\Administrator.vntrader中risk_manager_setting.json的参数字典，如下方代码所示。 

```
{
    "active": true,
    "order_flow_limit": 50,
    "order_flow_clear": 10,
    "order_size_limit": 5,
    "trade_limit": 500,
    "active_order_limit": 20,
    "order_cancel_limit": 5
}
```


在弹出的RiskManager窗口中，在【风控运行状态】一栏的下拉框中选择【启动】，设定相关参数后，点击下方的【保存】按钮，即可开始运行。

此时，RiskManagerEngine类的update_setting()函数被立即调用，读取risk_manager_setting.json的参数字典并把参数字典绑定到类的属性，如下方代码所示：

```
def update_setting(self, setting: dict):
    """"""
    self.active = setting["active"]
    self.order_flow_limit = setting["order_flow_limit"]
    self.order_flow_clear = setting["order_flow_clear"]
    self.order_size_limit = setting["order_size_limit"]
    self.trade_limit = setting["trade_limit"]
    self.active_order_limit = setting["active_order_limit"]
    self.order_cancel_limit = setting["order_cancel_limit"]

    if self.active:
        self.write_log("交易风控功能启动")
    else:
        self.write_log("交易风控功能停止")
```


日志中输出“交易风控功能启动”后，运行check_risk()函数，去检查每一笔发出去的委托是否符合各种风控要求（如委托数量，单笔委托数量），若全部满足后，委托才能真正通过API接口发送出去。

```
def check_risk(self, req: OrderRequest, gateway_name: str):
    """"""
    if not self.active:
        return True

    # Check order volume
    if req.volume <= 0:
        self.write_log("委托数量必须大于0")
        return False

    if req.volume > self.order_size_limit:
        self.write_log(
            f"单笔委托数量{req.volume}，超过限制{self.order_size_limit}")
        return False

    # Check trade volume
    if self.trade_count >= self.trade_limit:
        self.write_log(
            f"今日总成交合约数量{self.trade_count}，超过限制{self.trade_limit}")
        return False

    # Check flow count
    if self.order_flow_count >= self.order_flow_limit:
        self.write_log(
            f"委托流数量{self.order_flow_count}，超过限制每{self.order_flow_clear}秒{self.order_flow_limit}次")
        return False

    # Check all active orders
    active_order_count = len(self.main_engine.get_all_active_orders())
    if active_order_count >= self.active_order_limit:
        self.write_log(
            f"当前活动委托次数{active_order_count}，超过限制{self.active_order_limit}")
        return False

    # Check order cancel counts
    if req.symbol in self.order_cancel_counts and self.order_cancel_counts[req.symbol] >= self.order_cancel_limit:
        self.write_log(
            f"当日{req.symbol}撤单次数{self.order_cancel_counts[req.symbol]}，超过限制{self.order_cancel_limit}")
        return False

    # Add flow count if pass all checks
    self.order_flow_count += 1
    return True
```

 

## 参数修改

交易风控组件允许用户自定义风控参数。用户可以点击上下箭头来修改，也可以直接输入数字来修改。



## 停止风控
在【风控运行状态】的下拉框中选择【停止】后，点击下方的【保存】按钮。RiskManagerEngine类的active变成False，check_risk()函数不再检查委托的风控流控状态，同时在日志中输出”交易风控功能停止”。