# 脚本策略

ScriptTrader模块的作用：既提供交互式的量化分析和程序化交易功能，又能提供以整个策略连续运行的脚本策略功能。
ScriptTrader可视为直接利用python对证券交易客户端进行操作，它与CTA策略模块较为明显的区别在于突破了单交易所，单标的的限制，可以较方便的实现如股指期货和一篮子股票之间的对冲策略、跨品种套利、股票市场扫描自动化选股等功能

## Jupyter模式

### 加载启动
Jupyter模式下，一切都以 **ScriptEngine** 为核心
成功启动jupyter notebook后，进行如下操作来加载组件、初始化脚本引擎
```
from vnpy.app.script\_trader import init\_cli\_trading
from vnpy.gateway.ctp import CtpGateway

engine = init_cli_trading([CtpGateway])
```
*注*：
	- ScriptEngine支持同时连接多个接口，因此除了上述CTP接口，还可以自行添加其他交易接口
    - init\_cli\_trading可视为vnpy封好的初始化启动函数，函数内部将主引擎、脚本引擎等各种对象已经组装完毕，仅返回ScriptEngine供用户直接使用
### 连接接口
不同接口需要不同的配置参数，以ctp为例，连入simnow模拟交易
```
setting = {"用户名": "xxxx",
	       "密码": "xxxx",
	       "经纪商代码": "9999",
	       "交易服务器": "tcp://180.168.146.187:10101",
	       "行情服务器": "tcp://180.168.146.187:10111",
	       "产品名称": "simnow_client_test",
	       "授权编码": "0000000000000000",
	       "产品信息": ""
	      }
engine.connect_gateway(setting,"CTP")
```
### 查询数据

这里提前介绍一下连接上交易接口并成功订阅数据后的数据存储。底层接口不停向主引擎推送新的数据，在主引擎里维护着一个ticks字典用于缓存不同标的的最新tick数据（仅能缓存最新的）
use_df可选参数的作用（返回pandas.DataFrame，在Jupyter中分析更方便）

### 发出指令

- subscribe:连接上交易接口后还需要订阅特定的合约才能收到交易所推送过来的数据。以订阅螺纹钢1909为例
  ```
  engine.subscribe(["rb1909.SHFE"])
  ```
  这里合约参数是vt_symbol，如果对格式不是很确定，建议在vntrader菜单栏的"帮助"里查询合约里查询一下。
## 脚本策略模式

### 加载启动

如需要在脚本策略模式下使用，需要提前编写相关脚本策略文件，假设为a.py,然后打开vntrader,在菜单栏"功能"处打开"脚本策略",在跳出的脚本策略窗口最上方打开/Your-Path-To-a.py/a.py，然后直接启动即可。

### 脚本策略
脚本策略文件编写需要遵循一定格式,下面列出个最基础的模板
```
from vnpy.app.script_trader import ScriptEngine

def run(engine:ScriptEngine):
	#Your Symbols and subscribe the symbols
	while engine.strategy_active:
		#.....
```
### 运行控制

while循环的退出控制变量：engine.strategy_active

## 函数功能说明

### 单条查询

* get\_tick:查询单个标的最新tick，**注**：如果use\_df=False则返回的tick是一个包含了各种数据信息的类对象
	```
	tick = engine.get\_tick("rb1910.SHFE",use_df=True)#这样返回的是一个DataFrame对象，列是Tick的属性，只有一行数据
	```
* get\_order:根据vt_orderid查询委托单的详细信息，**注**：如果use\_df=False则返回是一个包含了各种数据信息的类对象
	```
	order = engine.get\_order(your_order_id,use_df=True)#这样返回的是一个DataFrame对象，列是OrderData的属性，只有一行数据
	```
* get\_contract:根据本地vt_symbol来查询交易所的合约代码
  ```
  contract = engine.get\_contract("rb1910.SHFE")
  ```
* get\_bars:查询历史数据，要求提前在vt_setting.json中配置好rqdata相关设置
  ```
  bars = engine.get\_bars("rb1910.SHFE","2019-01-01",Interval.MINUTE,use\_df=False)
  ```
  返回的bars是一个list，里面包含了BarData数据
* get\_position:根据vt_positionid来查询持仓情况
  ```
  position = engine.get\_position(your\_vt\_positonid)
  ```
  返回的bars是一个list，里面包含了BarData数据
### 多条查询

* get\_ticks：查询多个标的最新tick，**注**:如果use\_df=False则返回的是一个list，包含tick类对象，否则返回一个列是Tick属性具有多行数据的DataFrame
	```
	ticks = engine.get\_ticks(["rb1910.SHFE","rb1909.SHFE"],use_df=True)
	```
* get\_orders：查询多个vt_orderid查询其详细信息，**注**:如果use\_df=False则返回的是一个list，包含OrderData类对象，否则返回一个列是OrderData属性具有多行数据的DataFrame
	```
	orders = engine.get\_orders([orderid_one,orderid_two],use_df=True)
	```
* get\_trades:根据给定的一个vt_orderid返回这次报单过程中的所有TradeData对象，如果use\_df = True，则返回一个列是TradeData属性具有多行数据的DataFrame
  ```
  trades = engine.get\_trades(your\_vt\_orderid,True)
  ```
  **vnpy内部一个orderid对应着多个tradeid**
### 全量查询

在全量查询中，唯一参数是use_df，默认为False，即返回的是一个包含相应数据的List对象。
* get\_all\_contracts:默认返回一个list，包含了全市场的ContractData，如果use\_df=True则返回相应的DataFrame
* get\_all\_active\_orders:首先，active\_order指的是“已提交的、未成交的、部分成交的”订单；函数将返回list，包含这些OrderData
* get\_all\_accounts::默认返回一个list，包含了AccountData，如果use\_df=True则返回相应的DataFrame
* get\_all\_position:默认返回一个List,包含了PositionData,如果use\_df=True则返回相应的DataFrame
### 交易委托

* buy:以buy为例，发出一个交易委托，需要的参数有：**本地合约代码、价格、数量、下单类型**。其中，本地合约代码指的是vt_symbol；下单类型默认下限价单，可以自行更改，参考trader/constant下的OrderType枚举类;执行交易委托后会返回vt\_orderid
  ```
  
  #engine.buy("rb1910.SHFE",YourPrice,YourSize)
  ```
* cancel_order:必填参数只有一个vt\_orderid,就是下单后返回的那个订单id
  ```
  engine.cancel\_order(vt\_orderid)
  ```
### 信息输出

* write_log:可以用于记录买卖时的交易情况，尽量不要使用print
* send_email:用于实时通过email通知用户策略运行情况，需要提前在vt\_setting.json下配置email相关地址信息
	```
	engine.send\_email("Your Msg")
	```
