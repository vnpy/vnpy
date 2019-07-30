# 脚本策略

ScriptTrader模块的作用：既提供交互式的量化分析和程序化交易功能，又能提供以整个策略连续运行的脚本策略功能。
ScriptTrader可视为直接利用python对证券交易客户端进行操作，它与CTA策略模块较为明显的区别在于突破了单交易所，单标的的限制，可以较方便的实现如股指期货和一篮子股票之间的对冲策略、跨品种套利、股票市场扫描自动化选股等功能。

## Jupyter模式

### 加载启动
Jupyter模式下，一切都以 **ScriptEngine** 为核心
成功启动jupyter notebook后，进行如下操作来加载组件、初始化脚本引擎：
```
from vnpy.app.script_trader import init_cli_trading
from vnpy.gateway.ctp import CtpGateway

engine = init_cli_trading([CtpGateway])
```
**注**：
- ScriptEngine支持同时连接多个接口，因此除了上述CTP接口，还可以自行添加其他交易接口。
- 在```init_cli_trading(gateways: Sequence[BaseGateway])```中，将多个需要连接的接口类用列表的形式传递给init\_cli\_trading。
- init\_cli\_trading可视为vnpy封好的初始化启动函数，函数内部将主引擎、脚本引擎等各种对象已经组装完毕，仅返回ScriptEngine供用户直接使用。

### 连接接口
不同接口需要不同的配置参数，以ctp为例，连入simnow模拟交易。
```
setting = {
    "用户名": "xxxx",
    "密码": "xxxx",
    "经纪商代码": "9999",
    "交易服务器":"tcp://180.168.146.187：10101",
    "行情服务器":"tcp://180.168.146.187：10111",
    "产品名称":"simnow_xxx_test",
    "授权编码":"0000000000000000",
    "产品信息": ""
}
engine.connect_gateway(setting,"CTP")
```
![](https://m.qpic.cn/psb?/V12TMAOq2xN6BZ/n*ZnJEhNKgpm2vJ6XWASfsVE9RGs.XlkkiypK1iId8Y!/b/dLYAAAAAAAAA&bo=ggSoA4IEqAMRCT4!&rf=viewer_4)
**注**：
- 如果对setting的填写有疑问，可以按照vnpy/gateway目录下的接口类的default_setting来填写。

### 查询数据

这里介绍一下连接上交易接口并成功订阅数据后的数据存储。底层接口不停向主引擎推送新的数据，在主引擎里维护着一个ticks字典用于缓存不同标的的最新tick数据（仅能缓存最新的）。
use_df可选参数的作用（返回pandas.DataFrame，在Jupyter中分析更方便）。

### 发出指令
- subscribe：连接上交易接口后还需要订阅特定的合约才能收到交易所推送过来的数据。以订阅螺纹钢1909，1910为例
  ```
  engine.subscribe(vt_symbols = ["rb1909.SHFE","rb1910.SHFE"])
  ```
    - vt_symbols：需要填写的参数形式是列表，内部包含vt_symbol。
    &nbsp;
## 脚本策略模式

### 加载启动

如在脚本策略模式下使用，需要提前编写相关脚本策略文件，假设为demo_arbitrage.py,然后打开vntrader,在菜单栏"功能"处打开"脚本策略",在跳出的脚本策略窗口最上方打开/Path-To-demo_arbitrage.py/demo_arbitrage.py，然后直接启动即可。
![](https://m.qpic.cn/psb?/V12TMAOq2xN6BZ/S4RiCWfQvQck6*2aJ201*.mB0Jkvn.f6yOC2zf5a02A!/b/dLsAAAAAAAAA&bo=Mge8ADIHvAARCT4!&rf=viewer_4)
### 脚本策略
脚本策略文件编写需要遵循一定格式,下面展示一个基础的模板
```
from time import sleep
from vnpy.app.script_trader import ScriptEngine

def run(engine: ScriptEngine):
    """"""
    vt_symbols = ["IF1912.CFFEX", "rb2001.SHFE"]

    # 订阅行情
    engine.subscribe(vt_symbols)

    # 获取合约信息
    for vt_symbol in vt_symbols:
        contract = engine.get_contract(vt_symbol)
        msg = f"合约信息，{contract}"
        engine.write_log(msg)

    # 持续运行，使用strategy_active来判断是否要退出程序
    while engine.strategy_active:
        # 轮询获取行情
        for vt_symbol in vt_symbols:
            tick = engine.get_tick(vt_symbol)
            msg = f"最新行情, {tick}"
            engine.write_log(msg)

        # 等待3秒进入下一轮
        sleep(3)
```
该脚本策略的功能为：订阅两个品种的行情，打印合约信息，每隔3秒获取最新行情。
### 运行控制

while循环的退出控制变量：engine.strategy_active
- engine.strategy_active是脚本策略的开关，当点击“启动”时，该控制变量变为True，程序将一直在while循环内部不断运行；当点击“停止”时，该控制变量变为False，程序将运行完当前while循环后完全退出
- 脚本策略在编写时最重要的一点是主体部分要在while循环内部进行。
&nbsp;
## 函数功能说明

### 单条查询
* **在单条查询函数中，都有use_df参数用来控制是否将函数返回的类对象转化成DataFrame，仅在get_tick中做一次详细说明，其余函数同理。**
&nbsp;

* get\_tick：查询单个标的最新tick。
	```
	tick = engine.get_tick(vt_symbol="rb1910.SHFE",use_df=False)
	```
    - vt_symbol：字符串参数，表示本地合约代码。
    - use_df：bool变量，默认False，返回TickData类对象，否则返回相应DataFrame。

    ![](https://m.qpic.cn/psb?/V12TMAOq2xN6BZ/o38RYahmAsmLqPDz2cUixiDU19TGFqMH0e8WBg3wgHU!/b/dL4AAAAAAAAA&bo=iQaAAuIHBAMDCcM!&rf=viewer_4)
    注：DataFrame的列是TickData类属性，行是TickData个数，由于单条查询，则只有一行。
    &nbsp;

* get\_order：根据vt_orderid查询委托单的详细信息。
	```
	order = engine.get_order(vt_orderid='CTP.3_-9351590_1',use_df=False)
	```
    - vt_orderid：在委托下单时，会自动返回该委托的vt_orderid，以"CTP.3_-9351590_1"为例，它由ctp接口的name,frontid,sessionid,order_ref构成。其中，frontid和sessionid在vnpy连接上CTP接口后由CTP回调产生，order_ref是vnpy内部维护的用于区分order的一个变量。最前面还要加上接口名是因为vnpy可能同时连着很多接口进行交易。

    ![](https://m.qpic.cn/psb?/V12TMAOq2xN6BZ/cvmqxaHqSjRaRoR6FXdY3vt7JRm2XtNAYB*lwDY0rmY!/b/dAgBAAAAAAAA&bo=1AfGANQHxgADCSw!&rf=viewer_4)
    &nbsp;

* get\_contract：根据本地vt_symbol来查询对应合约对象的详细信息。
  ```
  contract = engine.get_contract(vt_symbol="rb1910.SHFE",use_df=False)
  ```
  - vt_symbol：字符串参数，表示本地合约代码。

  ![](https://m.qpic.cn/psb?/V12TMAOq2xN6BZ/*.vXu2esXg2.iImnZ838FFYMrCBeDBOXnnFKAcpaUK0!/b/dL8AAAAAAAAA&bo=6AfUAOgH1AARCT4!&rf=viewer_4)
&nbsp;

* get\_bars：查询历史数据，要求提前在vt_setting.json中配置好rqdata相关设置。
  ```
  bars = engine.get_bars(vt_symbol="rb1910.SHFE",start_date="20190101",
                        interval=Interval.MINUTE,use_df=False)
  ```
  - vt_symbol：字符串参数，表示本地合约代码。
  - start_date：字符串参数，格式必须为'%Y%m%d'。
  - interval：查询数据的间隔，可选参数有[Interval.MINUTE,Interval.HOUR,Interval.DAILY,Interval.WEEKLY]。
  
  特别说明：默认返回的是返回的bars是一个list，里面包含了一系列BarData数据，其中BarData定义了如下字段：
    ```
    @dataclass
    class BarData(BaseData):

        symbol: str
        exchange: Exchange
        datetime: datetime
        interval: Interval = None
        volume: float = 0
        open_interest: float = 0
        open_price: float = 0
        high_price: float = 0
        low_price: float = 0
        close_price: float = 0

        def __post_init__(self):
            self.vt_symbol = f"{self.symbol}.{self.exchange.value}"
  ```
  &nbsp;

* get\_position：根据vt_positionid来查询持仓情况，包括接口名称、交易所、合约代码、数量、冻结数量等。
  ```
  position = engine.get_position(vt_positionid='rb1909.SHFE.Direction.LONG')
  ```
  - vt_positionid：vnpy内部对于一笔特定持仓的唯一持仓编号，格式为"vt_symbol.Direction.LONG",其中方向可选择为```DIRECTION.SHORT```或```DIRECTION.NET```

  ![](https://m.qpic.cn/psb?/V12TMAOq2xN6BZ/szBIwwFgVmdXsBGYAWpkpZoA9m5ER0hmu*xya9c7u.Y!/b/dLYAAAAAAAAA&bo=3geuAN4HrgARCT4!&rf=viewer_4)

&nbsp;

### 多条查询
* **在多条查询函数中，use_df参数都可以用来控制是否将函数返回的类对象转化成DataFrame，仅在get_ticks中做一次详细说明，其余函数同理。**
&nbsp;

* get\_ticks：查询多个合约最新tick。
    ```
    ticks = engine.get_ticks(vt_symbols=['rb1910.SHFE','rb1909.SHFE'],use_df = True)
    ```
    - use\_df：False则返回一个列表，元素为TickData；True则返回DataFrame，列是TickData的属性，每一行代表一个TickData。
    - vt_symbols：一个列表，元素为合约字符串vt_symbol。

    ![](https://m.qpic.cn/psb?/V12TMAOq2xN6BZ/ghZR0VV5APiKLh5Zx73x7qgz1IwJ3zrG4MKVNen8PXc!/b/dL8AAAAAAAAA&bo=kAWAAvYHlAMDCV0!&rf=viewer_4)
&nbsp;

* get\_orders：根据查询多个vt_orderid查询其详细信息，**注**：如果use\_df=False则返回的是一个list，包含OrderData类对象，否则返回一个列是OrderData属性具有多行数据的DataFrame
	```
	orders = engine.get_orders([orderid_one,orderid_two],use_df=True)
	```
    - vt_orderids：列表，元素是vt_orderid形式的字符串，和上面提到的get_order的参数形式一致，由ctp接口的name,frontid,sessionid,order_ref构成。
    &nbsp;
* get\_trades：根据给定的一个vt_orderid返回这次报单过程中的所有TradeData对象。
    ```
    trades = engine.get_trades(vt_orderid = your_vt_orderid,use_df = True)
    ```
    - vt_orderid：vnpy本地订单id，注意，由于每一个委托OrderData，可能由于市场流动性情况和多笔市场上的反向委托成交，对应有多笔成交TradeData，因此该函数会返回所有对应成交TraderData。
    &nbsp;
### 全量查询

在全量查询中，唯一参数是use_df，默认为False，返回的是一个包含相应数据的List对象,例如ContractData，AccountData，PositionData。
* get\_all\_contracts：默认返回一个list，包含了全市场的ContractData，如果use\_df=True则返回相应的DataFrame。
* get\_all\_active\_orders：首先，active\_order指的是“已提交的、未成交的、部分成交的”订单,已完成的order将不显示；函数将返回list，包含这些OrderData。
* get\_all\_accounts：：默认返回一个list，包含了AccountData，如果use\_df=True则返回相应的DataFrame。
* get\_all\_position：默认返回一个List,包含了PositionData,如果use\_df=True则返回相应的DataFrame。
![](https://m.qpic.cn/psb?/V12TMAOq2xN6BZ/Ym0EnCJddVzIZUHBVTAHvhI6mMhUFD0p2.BTAVHMtjs!/b/dFYBAAAAAAAA&bo=vAdKBbwHSgUDCSw!&rf=viewer_4)
### 交易委托

* buy：以buy为例，发出一个交易委托，需要的参数有：**本地合约代码、价格、数量、下单类型**。其中，本地合约代码指的是vt_symbol；下单类型默认下限价单，可以自行更改，参考trader/constant下的OrderType枚举类;执行交易委托后会返回vt\_orderid
  ```
  #engine.buy(vt_symbol = "rb1910.SHFE",price = "3200",volume = "1",order_type=OrderType.LIMIT)
  ```
  - vt_symbol：vnpy本地合约代码
  - price：报单价格，注意是字符串格式
  - volume：报单数量，注意是字符串格式
  - order_type：OrderType枚举常量，默认为限价单(OrderType.LIMIT)，同时支持停止单（OrderType.STOP）、FAK（OrderType.FAK）、FOK（OrderType.FOK）、市价单（OrderType.MARKET），不同交易所支持报单方式不完全一致。
* cancel_order：根据vt_orderid取消某一笔委托。
  ```
  engine.cancel_order(vt_orderid = 'CTP.3_-9351590_1')
  ```
### 信息输出

* write_log：可以用于记录买卖时的交易情况，将信息输出在脚本策略窗口下方空白栏里。
&nbsp;
* send_email：用于实时通过email通知用户策略运行情况，需要提前在vt\_setting.json下配置email相关信息。其中脚本策略发的邮件标题为“脚本策略引擎通知”，msg:字符串，表示邮件正文内容。
	```
	engine.send_email(msg = "Your Msg")
	```
    ![](https://m.qpic.cn/psb?/V12TMAOq2xN6BZ/bjXP43yUR36j5dB8YSu3cLpc1xY8jN8envDYxeSS1zA!/b/dL4AAAAAAAAA&bo=JAayASQGsgEDCSw!&rf=viewer_4)
    使用邮箱前需要开通SMTP服务。
    - email.server：邮件服务器地址，vnpy默认填写好了QQ邮箱服务器地址，不用改可以直接用，如果需要使用其他邮箱，需要自行查找一下其他的服务器地址。
    - email.port：邮件服务器端口号，vnpm默认填好了QQ邮箱服务器端口，可直接用。
    - email.username：填写邮箱地址即可，如xxxx@qq.com。
    - email.password：对于QQ邮箱，此处不是邮箱密码，而是开通SMTP后系统生成的一个授权码。
    - email.sendert：email.username。
    - email.receiver：接受邮件的邮箱地址，比如xxxx@outlook.com。