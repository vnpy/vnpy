# MarketRadar - 市场信号雷达模块


## 功能简介

MarketRadar是用于**实时衍生行情数据计算**的模块，用户可以通过其UI界面对多合约价格自定义灵活的数学公式和条件信号，并执行衍生数据高效计算、条件信号实时扫描、信号触发后的提醒与通知等任务。


## 加载启动

### VN Station加载

启动登录VN Station后，点击【VN Trader Pro】按钮，在配置对话框中的【上层应用】栏勾选【MarketRadar】。

### 脚本加载

在启动脚本中添加如下代码：

```
# 写在顶部
from vnpy.app.market_radar import MarketRadarApp

# 写在创建main_engine对象后
main_engine.add_app(MarketRadarApp)
```


## 启动模块

在启动模块之前，请先连接登录交易接口（连接方法详见基本使用篇的连接接口部分）。看到VN Trader主界面【日志】栏输出“合约信息查询成功”之后再启动模块，如下图所示：  

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/market_radar/1.png) 

成功连接交易接口后，在菜单栏中点击【功能】-> 【市场雷达】，或者点击左侧按钮栏的图标：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/market_radar/2.png) 

即可进入MarketRadar的UI界面，如下图所示：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/market_radar/2-3.png) 


## 管理雷达规则

### 添加雷达规则

在图形界面左下角的编辑区中，可以快速创建要扫描计算的雷达规则（RadarRule），如下图所示：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/market_radar/4.png) 

其中，各字段的对应含义如下：  
- 名称
  - 雷达规则的名称，注意命名不能重复；
- 公式
  - 雷达规则的计算公式，支持任何Python内置数学函数；
  - 注意其中的变量只能是A、B、C、D、E（不需要都用）；
- A、B、C、D、E
  - 公式中的变量所对应的合约本地代码（vt_symbol）；
  - 收到其中任何一个合约的TICK行情推送时，会实时触发规则计算；
  - 不用的变量留空即可；
- 小数
  - 公式的最终计算结果保留多少位小数。

填写完毕后，点击【添加】按钮即可完成新规则的添加，MarketRadar会自动订阅相关合约行情并开始自动扫描计算，如下图所示。

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/market_radar/2-5.png) 

除了跨期价差这种减法求差的规则外，MarketRadar也支持金银比等跨品种价差的计算规则，如下图所示：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/market_radar/6.png) 

### 修改雷达规则

对于需要调整的规则，也可以同样在左下角输入相应信息（名称请填写要修改的雷达规则名称），点击【修改】按钮即可完成修改。

### 删除雷达规则

对于不再需要的规则，可以点击监控表中最右侧的【删除】按钮来进行移除。

### 批量添加雷达规则

需要添加较多的雷达规则时，可以通过CSV文件来一次性批量导入，点击图形界面右下角的【导入CSV】按钮，在弹出的对话框中找到要导入的CSV文件后打开即可快速完成导入（右下角日志组件中有对应信息输出）。

请注意，CSV文件的格式应如下图所示，和编辑区的各字段完全一致：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/market_radar/7.png) 

结合Excel的表格快速编辑功能，批量添加规则较为方便。添加成功后如下图所示：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/market_radar/2-8.png) 


## 管理雷达信号

### 添加雷达信号

2.2.0后的版本中，市场信号雷达模块新增雷达信号实时扫描和提醒通知功能。在成功添加雷达规则后，如果需要对其定义雷达信号，只需点击最左侧的规则名称按钮，如下图所示：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/market_radar/2-9.png) 

在弹出的对话框中，输入触发条件的具体信息，包括信号类型（大于、小于、等于）、目标数值和通知方式（声音、邮件），如下图所示：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/market_radar/2-10.png) 

在底部中间的监控组件中即可看到当前处于实时监控中的条件信号，如下图所示：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/market_radar/2-11.png) 

当雷达规则满足条件后，信号会被立即触发（并自动从监控表中移除），此时会在右下角的日志区域输出相关提示信息，并根据之前用户的选择播放声音通知或者发送邮件提醒。
![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/market_radar/2-12.png) 
请注意，目前雷达信号不提供缓存功能，程序关闭后就会消失，每次重启VN Trader后需要重新创建。

### 删除雷达信号

当不再需要某个信号时，点击最左侧【删除】按钮，即可移除对应的雷达信号。