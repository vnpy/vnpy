# 脚本策略
ScriptTrader模块提供了交互式的量化分析和程序化交易功能，又提供以整个策略连续运行的脚本策略功能。

故其可视为直接利用Python对证券交易客户端进行操作。它与CTA策略模块的区别在于：
- 突破了单交易所，单标的的限制，
- 可以较方便的实现如股指期货和一篮子股票之间的对冲策略、跨品种套利、股票市场扫描自动化选股等功能。

&nbsp;

## Jupyter模式

### 加载启动
Jupyter模式是基于脚本引擎（ScriptEngine）驱动的。首先打开Jupyter notebook后，然后加载组件、初始化脚本引擎。其中：
```
from vnpy.app.script_trader import init_cli_trading
from vnpy.gateway.ctp import CtpGateway
engine = init_cli_trading([CtpGateway])
```

其中：
- 脚本引擎可以支持同时连接多个接口，如CTP、BITMEX、OES等；
- init_cli_trading(gateways: Sequence[BaseGateway])可以将多个接口类，以列表的形式传递给init_cli_trading；
- init_cli_trading可视为vnpy封好的初始化启动函数，对主引擎、脚本引擎等各种对象进行了封装。

&nbsp;

### 连接接口
不同接口需要不同的配置参数，SimNow的配置如下：
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

setting配置如下图所示，其他接口配置可以参考vnpy/gateway目录下的接口类的default_setting来填写。

![](https://static.vnpy.com/upload/temp/82dd7cfd-6a98-4908-a770-582cfb7e69bc.jpg)


&nbsp;

### 查询数据
这里介绍一下连接上交易接口并成功订阅数据后的数据存储：
- 底层接口不停向主引擎推送新的数据；
- 主引擎里维护着一个ticks字典用于缓存不同标的的最新tick数据（仅能缓存最新的）；
- use_df的作用是转换成DataFrame格式，便于数据分析。

&nbsp;

### 订阅行情
subscribe()函数用于订阅行情信息，若需要订阅一篮子合约的行情，可以使用列表格式。
```
engine.subscribe(vt_symbols = ["rb1909.SHFE","rb1910.SHFE"])
```

&nbsp;

## 脚本策略模式

### 加载启动
- 若使用脚本策略模式，需要提前编写相关脚本策略文件，如demo_arbitrage.py,
- 然后打开VnTrader,在菜单栏"功能"处打开"脚本策略",在跳出的脚本策略窗口最上方打开/Path-To-demo_arbitrage.py/demo_arbitrage.py，然后
- 点击如下图的“启动”。
![](https://static.vnpy.com/upload/temp/bf6b06f8-26e9-466b-b3e0-5b3a6f99e6ba.jpg)

&nbsp;

### 脚本策略
脚本策略文件编写需要遵循一定格式,下面提供使用模板，其作用为：
- 订阅两个品种的行情；
- 打印合约信息；
- 每隔3秒获取最新行情。
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

&nbsp;

### 运行控制
engine.strategy_active用于控制While循环，可视作是脚本策略的开关：
- 点击“启动”按钮，启动While循环，执行脚本策略；
- 点击“停止”按钮，退出While循环，停止脚本策略。

&nbsp;

## 函数功能说明

### 单条查询

get_tick：查询单个标的最新tick，use_df为可选参数，用于把返回的类对象转化成DataFrame格式，便于数据分析。
```
tick = engine.get_tick(vt_symbol="rb1910.SHFE",use_df=False)
```

其中：
- vt_symbol：为本地合约代码，格式是合约品种+交易所，如rb1910.SHFE。
- use_df：为bool变量，默认False，返回TickData类对象，否则返回相应DataFrame，如图。

![](https://static.vnpy.com/upload/temp/d00ca165-1266-4812-afaa-f6723745d6a4.png)

&nbsp;

get_order：根据vt_orderid查询委托单的详细信息。
```
order = engine.get_order(vt_orderid='CTP.3_-9351590_1',use_df=False)
```

其中，vt_orderid为本地委托号，在委托下单时，会自动返回该委托的vt_orderid：
- 以"CTP.3_-9351590_1"为例，它由ctp接口的name,frontid,sessionid,order_ref构成；
- frontid和sessionid在vnpy连接上CTP接口后由CTP回调产生；
- order_ref是vnpy内部维护的用于区分order的一个变量。

![](https://static.vnpy.com/upload/temp/ae9f6d7f-49da-41e4-a862-825bf146118d.png)

&nbsp;

get_contract：根据本地vt_symbol来查询对应合约对象的详细信息。
```
contract = engine.get_contract(vt_symbol="rb1910.SHFE",use_df=False)
```

![](https://static.vnpy.com/upload/temp/4111776b-91fd-44e6-8b2c-289961862a3a.jpg)

&nbsp;

get_bars：查询历史数据。（需要初始化RQData客户端）
```
bars = engine.get_bars(vt_symbol="rb1910.SHFE",start_date="20190101",
                        interval=Interval.MINUTE,use_df=False)
```

其中：
- vt_symbol：本地合约代码。
- start_date：起始日期，格式必须为"%Y%m%d"。
- interval：K线周期，包括：分钟、小时、日、周
- bars：包含了一系列BarData数据的列表对象，其BarData的定义如下：
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

get_position：根据vt_positionid来查询持仓情况，返回对象包含接口名称、交易所、合约代码、数量、冻结数量等。
```
position = engine.get_position(vt_positionid='rb1909.SHFE.Direction.LONG')
```
注意，vt_positionid为vnpy内部对于一笔特定持仓的唯一持仓编号，格式为"vt_symbol.Direction.LONG",其中持仓方向可选多仓、空仓和净持仓，如图。

![](https://static.vnpy.com/upload/temp/4c585dac-0ac9-4fd8-9926-ddc104512359.jpg)

&nbsp;

### 多条查询
get_ticks：查询多个合约最新tick。
```
ticks = engine.get_ticks(vt_symbols=['rb1910.SHFE','rb1909.SHFE'],use_df = True)
```

vt_symbols是列表格式，里面包含多个vt_symbol，如图。

![](https://static.vnpy.com/upload/temp/311e1ee8-1a3d-496f-833f-bbb7a3a624ab.png)

&nbsp;

get_orders：根据查询多个vt_orderid查询其详细信息。vt_orderids为列表，里面包含多个vt_orderid
```
orders = engine.get_orders([orderid_one,orderid_two],use_df=True)
```


&nbsp;

get_trades：根据给定的一个vt_orderid返回这次报单过程中的所有TradeData对象。vt_orderid是本地委托号，每一个委托OrderData，由于部分成交关系，可以对应多笔成交TradeData。
```
trades = engine.get_trades(vt_orderid = your_vt_orderid,use_df = True)
```

&nbsp;

### 全量查询

在全量查询中，唯一参数是use_df，默认为False，返回的是一个包含相应数据的List对象,例如ContractData，AccountData，PositionData。

- get_all_contracts：默认返回一个list，包含了全市场的ContractData，如果use_df=True则返回相应的DataFrame；
- get_all_active_orders：活动委托指的是等待委托完全成交，故其状态包含“已提交的、未成交的、部分成交”；函数将返回包含一系列OrderData的列表对象；
- get_all_accounts：默认返回包含AccountData的列表对象；
- get_all_position：默认返回包含PositionData的列表对象，如图。

![](https://static.vnpy.com/upload/temp/5d698a27-545b-46bb-9d16-428a8ccb7956.png)

&nbsp;

### 交易委托

以委托买入为例，engine.buy()函数入参包括：
- vt_symbol：本地合约代码（字符串格式）
- price：报单价格（浮点数类型）;
- volume：报单数量（浮点数类型）;
- order_type：OrderType枚举常量，默认为限价单（OrderType.LIMIT），同时支持停止单（OrderType.STOP）、FAK（OrderType.FAK）、FOK（OrderType.FOK）、市价单（OrderType.MARKET），不同交易所支持报单方式不完全一致。
```
engine.buy(vt_symbol = "rb1910.SHFE", price = 3200, volume = 1, order_type=OrderType.LIMIT)
```

执行交易委托后会返回本地委托号vt_orderid，撤单也是基于该本地委托号的
```
engine.cancel_order(vt_orderid = 'CTP.3_-9351590_1')
```

&nbsp;

### 信息输出
write_log()函数可用于记录买卖时的交易情况，将信息输出在脚本策略窗口下方空白栏里。

&nbsp;

send_email()函数用于实时通过email通知用户策略运行情况：
- 先在vt_setting.json下配置email相关信息；
- 邮件标题为“脚本策略引擎通知”；
- msg为字符串格式，表示邮件正文内容，如图。
```
engine.send_email(msg = "Your Msg")
```

![](https://static.vnpy.com/upload/temp/8dd8d6b0-6c04-4cb4-a426-ad43d11a13eb.png)

使用邮箱前需要开通SMTP服务。
- email.server：邮件服务器地址，vnpy默认填写好了QQ邮箱服务器地址，不用改可以直接用，如果需要使用其他邮箱，需要自行查找一下其他的服务器地址。
- email.port：邮件服务器端口号，vnpm默认填好了QQ邮箱服务器端口，可直接用。
- email.username：填写邮箱地址即可，如xxxx@qq.com。
- email.password：对于QQ邮箱，此处不是邮箱密码，而是开通SMTP后系统生成的一个授权码。
- email.sendert：email.username。
- email.receiver：接受邮件的邮箱地址，比如xxxx@outlook.com。
