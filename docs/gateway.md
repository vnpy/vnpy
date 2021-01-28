# 交易接口

## 如何连接

从gateway文件夹上引入接口程序，通过add_gateway()函数调动，最终展示到图形化操作界面VN Trader中。

在菜单栏中点击"系统"->"连接CTP”按钮会弹出如图账号配置窗口，输入账号、密码等相关信息即连接接口，并立刻进行查询工作: 如查询账号信息、查询持仓、查询委托信息、查询成交信息等。

![](https://vnpy-community.oss-cn-shanghai.aliyuncs.com/forum_experience/yazhang/gateway/login.png)

&nbsp;

### 加载需要用的接口

加载接口示例在根目录"tests\trader"文件夹的run.py文件中。
- 从gateway文件夹引入接口类文件，如from vnpy.gateway.ctp import CtpGateway;
- 创建事件引擎对象并且通过add_gateway()函数添加接口程序;
- 创建图形化对象main_window，以VN Trader操作界面展示出来。


```
from vnpy.gateway.ctp import CtpGateway

def main():
    """"""
    qapp = create_qapp()
    main_engine = MainEngine(event_engine)
    main_engine.add_gateway(CtpGateway)
    main_window = MainWindow(main_engine, event_engine)
    main_window.showMaximized()
    qapp.exec()
```

&nbsp;


### 配置和连接

打开cmd窗口，使用命令“Python run.py"即可进入VN Trader操作界面。在左上方的菜单栏中点击"系统"->"连接CTP”按钮会弹出账号配置窗口，输入账号、密码等相关信息即连接接口。

连接接口的流程首先是初始化账户信息，然后调用connet()函数来连接交易端口和行情端口。
- 交易端口：查询用户相关信息（如账户资金、持仓、委托记录、成交记录）、查询可交易合约信息、挂撤单操作；
- 行情端口：接收订阅的行情信息推送、接收用户相关信息（如账户资金更新、持仓更新、委托推送、成交推送）更新的回调推送。


&nbsp;


### 修改json配置文件

接口配置相关保存在json文件中，放在如图C盘用户目录下的.vntrader文件夹内。

![](https://vnpy-community.oss-cn-shanghai.aliyuncs.com/forum_experience/yazhang/gateway/.vntrader.png)

所以要修改接口配置文件，用户即可以在图形化界面VN Trader内修改，也可以直接在.vntrader修改json文件。
另外将json配置文件分离于vnpy的好处在于：避免每次升级都要重新配置json文件。


&nbsp;


### 查看可交易的合约

先登录接口，然后在菜单栏中点击"帮助"->"查询合约”按钮会空白的“查询合约”窗口。点击“查询”按钮后才会显示查询结果，如图。

![](https://vnpy-community.oss-cn-shanghai.aliyuncs.com/forum_experience/yazhang/gateway/query_contract.png)



&nbsp;

## 接口分类

| 接口          |                    类型                         |
| ------------  | :--------------------------------------------: |
| CTP           |           期货、期货期权（实盘6.3.15）            |
| CTP测试       |           期货、期货期权（测试6.3.16）            |
| CTP Mini      |            期货、期货期权（实盘1.4）             |
| CTP Mini测试  |            期货、期货期权（测试1.2）              |
| 飞马          |                    期货                         |
| CTP期权       |             ETF期权（实盘20190802）              |
| CTP期权测试    |            ETF期权（实盘20190604）              |
| 飞创期权       |            ETF期权（实盘20200427）              |
| 恒生UFT       |                期货、ETF期权                     |
| 恒生期权       |                  ETF期权                        |
| 中泰XTP       |              A股、两融、ETF期权                  |
| 华鑫奇点股票   |                    A股                          |
| 华鑫奇点期权   |                  ETF期权                         |
| 宽睿          |                A股、ETF期权                      |
| 中亿汇达Comstar|                银行间市场                       |
| 富途证券       |                 港股、美股                      |
| 盈透证券       |                 海外全品种                      |
| 老虎证券       |                 海外全品种                       |
| 易盛9.0外盘    |                  外盘期货                       |
| 直达期货       |                  外盘期货                       |
| MetaTrader 5  |            外汇、CFD、股票、期货                 |
| 币安           |                  数字货币                       |
| 币安永续合约   |             数字货币永续和期货                   |
| 火币          |                   数字货币                      |
| 火币期货       |                数字货币期货                     |
| 火币永续       |                数字货币永续                     |
| 火币期权       |                数字货币期权                     |
| OKEX           |                  数字货币                      |
| OKEX期货       |                数字货币期货                     |
| OKEX永续       |                数字货币永续                     |
| OKEX期权       |                数字货币期权                     |
| BitMEX        |              数字货币期货、永续                  |
| Bybit         |                 数字货币永续                     |
| Gate.io合约    |                数字货币永续                      |
| Deribit        |             数字货币永续、期权                   |
| Bitfinex       |                  数字货币                       |
| Coinbase       |                  数字货币                       |
| Bitstamp       |                  数字货币                       |
| 1Token         |                   数字货币                      |
| 融航           |                  期货资管                       |
| 鑫管家         |                  期货资管                        |
| RPC服务        |                核心交易路由                      |



&nbsp;


## 接口详解

### CTP

#### 如何加载

run.py文件提供了接口加载示例：先从gateway上调用ctpGateway类；然后通过add_gateway()函数添加到main_engine上。
```
from vnpy.gateway.ctp import CtpGateway
main_engine.add_gateway(CtpGateway)
```

&nbsp;

#### 相关字段

- 用户名：username
- 密码：password：
- 经纪商编号：brokerid
- 交易服务器地址：td_address
- 行情服务器地址：md_address
- 产品名称：product_info
- 授权编码：auth_code
  
&nbsp;

#### 获取账号

- 仿真账号：从SimNow网站上获取。只需输入手机号码和短信验证即可。（短信验证有时只能在工作日正常工作时段收到）SimNow的用户名为6位纯数字，经纪商编号为9999，并且提供2套环境用于盘中仿真交易以及盘后的测试。
  
- 实盘账号：在期货公司开户，通过联系客户经理可以开通。用户名为纯数字，经纪商编号也是4位纯数字。（每个期货公司的经纪商编号都不同）另外，实盘账号也可以开通仿真交易功能，同样需要联系客户经理。


&nbsp;

### MINI

#### 如何加载

先从gateway上调用MiniGateway类；然后通过add_gateway()函数添加到main_engine上。
```
from vnpy.gateway.mini import MiniGateway
main_engine.add_gateway(MiniGateway)
```

&nbsp;

#### 相关字段

- 用户名：username
- 密码：password：
- 经纪商编号：brokerid
- 交易服务器地址：td_address
- 行情服务器地址：md_address
- 产品名称：product_info
- 授权编码：auth_code
  
&nbsp;

#### 获取账号

在期货公司开户，通过联系客户经理可以开通。用户名为纯数字，经纪商编号也是4位纯数字。（每个期货公司的经纪商编号都不同）另外，实盘账号也可以开通仿真交易功能，同样需要联系客户经理。


&nbsp;

### 飞马（FEMAS）

#### 如何加载

先从gateway上调用FemasGateway类；然后通过add_gateway()函数添加到main_engine上。
```
from vnpy.gateway.femas import FemasGateway
main_engine.add_gateway(FemasGateway)
```

&nbsp;

#### 相关字段

- 用户名：username
- 密码：password：
- 经纪商编号：brokerid
- 交易服务器地址：td_address
- 行情服务器地址：md_address
- 产品名称：product_info
- 授权编码：auth_code
  
&nbsp;

#### 获取账号

在期货公司开户，通过联系客户经理可以开通。用户名为纯数字，经纪商编号也是4位纯数字。（每个期货公司的经纪商编号都不同）另外，实盘账号也可以开通仿真交易功能，同样需要联系客户经理。


&nbsp;



### 中泰柜台(XTP)

#### 如何加载

先从gateway上调用XtpGateway类；然后通过add_gateway()函数添加到main_engine上。
```
from vnpy.gateway.xtp import XtpGateway
main_engine.add_gateway(XtpGateway)
```

&nbsp;


#### 相关字段

- 账号：
- 密码：
- 客户号": 1
- 行情地址：
- 行情端口": 0
- 交易地址：
- 交易端口": 0
- 行情协议: ["TCP", "UDP"]
- 授权码：

&nbsp;


#### 获取账号

测试账号请联系中泰证券申请。

#### 其他特点

XTP是首家提供融资融券的极速柜台。

&nbsp;


### 宽睿柜台(OES)

#### 如何加载

先从gateway上调用OesGateway类；然后通过add_gateway()函数添加到main_engine上。
```
from vnpy.gateway.oes import OesGateway
main_engine.add_gateway(OesGateway)
```

&nbsp;


#### 相关字段

- 用户名：username
- 密码：password
- 硬盘序列号：hdd_serial
- 交易委托服务器：td_ord_server
- 交易回报服务器：td_rpt_server
- 交易查询服务器：td_qry_server
- 行情推送服务器：md_tcp_server
- 行情查询服务器：md_qry_server

&nbsp;


#### 获取账号

测试账号请联系宽睿科技申请

&nbsp;

#### 其他特点

宽睿柜台提供内网UDP低延时组播行情以及实时成交信息推送。

&nbsp;


### 华鑫奇点(TORA)

#### 如何加载

先从gateway上调用ToraGateway类；然后通过add_gateway()函数添加到main_engine上。
```
from vnpy.gateway.tota import ToraGateway
main_engine.add_gateway(ToraGateway)
```

&nbsp;

#### 相关字段

- 账号: username
- 密码: password
- 交易服务器: td_address
- 行情服务器: md_address

&nbsp;

#### 获取账号

测试账号请联系华鑫证券申请


&nbsp;

### 盈透证券(IB)

#### 如何加载

先从gateway上调用IbGateway类；然后通过add_gateway()函数添加到main_engine上。
```
from vnpy.gateway.ib import IbGateway
main_engine.add_gateway(IbGateway)
```

&nbsp;


#### 相关字段

- TWS地址：127.0.0.1
- TWS端口：7497
- 客户号：1


&nbsp;


#### 获取账号

在盈透证券开户并且入金后可以获得API接入权限。拥有实盘账号后才可以申请开通仿真交易账号。

&nbsp;

#### 其他特点

可交易品种几乎覆盖全球的股票、期权、期权；手续费相对较低。

注意IB接口的合约代码较为特殊，请前往官网的产品查询板块查询，VN Trader中使用的是盈透证券对于每个合约在某一交易所的唯一标识符ConId来作为合约代码，而非Symbol或者LocalName。

&nbsp;


### 易盛外盘(TAP)

#### 如何加载

先从gateway上调用TapGateway类；然后通过add_gateway()函数添加到main_engine上。
```
from vnpy.gateway.tap import TapGateway
main_engine.add_gateway(TapGateway)
```

&nbsp;


#### 相关字段

- 授权码：auth code
- 行情账号：quote username
- 行情密码：quote password
- 行情地址：123.15.58.21
- 行情端口：7171



&nbsp;


#### 获取账号

在TAP开户并且入金后可以获得API接入权限。

&nbsp;


### 富途证券(FUTU)

#### 如何加载

先从gateway上调用FutuGateway类；然后通过add_gateway()函数添加到main_engine上。
```
from vnpy.gateway.futu import FutuGateway
main_engine.add_gateway(FutuGateway)
```

&nbsp;


#### 相关字段

- 地址：127.0.0.1
- 密码：
- 端口：11111
- 市场：HK 或 US
- 环境：TrdEnv.REAL 或 TrdEnv.SIMULATE


&nbsp;


#### 获取账号

在富途证券开户并且入金后可以获得API接入权限。拥有实盘账号后才可以申请开通仿真交易账号。






&nbsp;

### 老虎证券(TIGER)


#### 如何加载

先从gateway上调用TigerGateway类；然后通过add_gateway()函数添加到main_engine上。
```
from vnpy.gateway.tiger import TigerGateway
main_engine.add_gateway(TigerGateway)
```

&nbsp;


#### 相关字段

- 用户ID：tiger_id
- 环球账户：account
- 标准账户：standard_account
- 秘钥：private_key



&nbsp;


#### 获取账号

在老虎证券开户并且入金后可以获得API接入权限。拥有实盘账号后才可以申请开通仿真交易账号。


&nbsp;


### ALPACA

#### 如何加载
先从gateway上调用AlpacaGateway类；然后通过add_gateway()函数添加到main_engine上。
```
from vnpy.gateway.alpaca import AlpacaGateway
main_engine.add_gateway(AlpacaGateway)
```

&nbsp;

#### 相关字段
- KEY ID: key
- Secret Key: secret
- 会话数: 10
- 服务器:["REAL", "PAPER"]
#### 获取账号
在OKEX官网开户并且入金后可以获得API接入权限。
#### 其他特点

&nbsp;


### BITMEX

#### 如何加载

先从gateway上调用BitmexGateway类；然后通过add_gateway()函数添加到main_engine上。
```
from vnpy.gateway.bitmex import BitmexGateway
main_engine.add_gateway(BitmexGateway)
```

&nbsp;


#### 相关字段

- 用户ID：ID
- 密码：Secret
- 会话数：3
- 服务器：REAL 或 TESTNET
- 代理地址：
- 代理端口：



&nbsp;


#### 获取账号

在BITMEX官网开户并且入金后可以获得API接入权限。



&nbsp;

### OKEX现货（OKEX）


#### 如何加载

先从gateway上调用OkexGateway类；然后通过add_gateway()函数添加到main_engine上。
```
from vnpy.gateway.okex import OkexGateway
main_engine.add_gateway(OkexGateway)
```

&nbsp;


#### 相关字段

- API秘钥：API Key
- 密码秘钥：Secret Key
- 会话数：3
- 密码：passphrase
- 代理地址：
- 代理端口：



&nbsp;


#### 获取账号

在OKEX官网开户并且入金后可以获得API接入权限。



&nbsp;


### OKEX期货（OKEXF）


#### 如何加载

先从gateway上调用OkexfGateway类；然后通过add_gateway()函数添加到main_engine上。
```
from vnpy.gateway.okexf import OkexfGateway
main_engine.add_gateway(OkexfGateway)
```

&nbsp;


#### 相关字段

- API秘钥：API Key
- 密码秘钥：Secret Key
- 会话数：3
- 密码：passphrase
- 杠杆：Leverage
- 代理地址：
- 代理端口：



&nbsp;


#### 获取账号

在OKEX官网开户并且入金后可以获得API接入权限。


&nbsp;

### 火币(HUOBI)

#### 如何加载

先从gateway上调用HuobiGateway类；然后通过add_gateway()函数添加到main_engine上。
```
from vnpy.gateway.huobi import HuobiGateway
main_engine.add_gateway(HuobiGateway)
```

&nbsp;


#### 相关字段

- API秘钥：API Key
- 密码秘钥：Secret Key
- 会话数：3
- 代理地址：
- 代理端口：



&nbsp;


#### 获取账号

在火币官网开户并且入金后可以获得API接入权限。


&nbsp;



### 火币合约(HUOBIF)

#### 如何加载

先从gateway上调用HuobifGateway类；然后通过add_gateway()函数添加到main_engine上。
```
from vnpy.gateway.huobif import HuobifGateway
main_engine.add_gateway(HuobifGateway)
```

&nbsp;


#### 相关字段

- API秘钥：API Key
- 密码秘钥：Secret Key
- 会话数：3
- 代理地址：
- 代理端口：



&nbsp;


#### 获取账号

在火币官网开户并且入金后可以获得API接入权限。


&nbsp;

### BITFINEX

#### 如何加载

先从gateway上调用BitFinexGateway类；然后通过add_gateway()函数添加到main_engine上。
```
from vnpy.gateway.bitfinex import BitfinexGateway
main_engine.add_gateway(BitfinexGateway)
```

&nbsp;


#### 相关字段

- 用户ID：ID
- 密码：Secret
- 会话数：3
- 代理地址：
- 代理端口：



&nbsp;


#### 获取账号

在BITFINEX官网开户并且入金后可以获得API接入权限。



&nbsp;


### ONETOKEN

#### 如何加载

先从gateway上调用OnetokenGateway类；然后通过add_gateway()函数添加到main_engine上。
```
from vnpy.gateway.onetoken import OnetokenGateway
main_engine.add_gateway(OnetokenGateway)
```

&nbsp;


#### 相关字段

- Key秘钥：OT Key
- 密码秘钥：OT Secret
- 会话数：3
- 交易所：["BINANCE", "BITMEX", "OKEX", "OKEF", "HUOBIP", "HUOBIF"]
- 账号：
- 代理地址：
- 代理端口：



&nbsp;


#### 获取账号

在Onetoken官网开户并且入金后可以获得API接入权限。



&nbsp;

&nbsp;

### BINANCE

#### 如何加载

先从gateway上调用BinanceGateway类；然后通过add_gateway()函数添加到main_engine上。
```
from vnpy.gateway.binance import BinanceGateway
main_engine.add_gateway(BinanceGateway)
```

&nbsp;


#### 相关字段

- Key秘钥
- secret
- session_number(会话数)：3
- proxy_host
- proxy_port

&nbsp;


#### 获取账号

在BINANCE官网开户并且入金后可以获得API接入权限。

&nbsp;


### RPC

#### 如何加载

RPC的加载涉及到服务端和客户端
- 服务端：运行vntrader时加载rpc_service模块
    ```
    from vnpy.app.rpc_service import RpcService
    ```
    启动vntrader后，首先连接外部交易交易如CTP，然后点击菜单栏"功能"->"RPC服务"，点击"启动"
- 客户端：运行vntrader时加载RpcGateway
    ```
    from vnpy.gateway.rpc import RpcGateway
    ```
    启动vntrader后，连接rpc接口即可。

#### 相关字段
在服务端和客户端，使用默认填好的参数即可

#### 获取账号
使用rpc无须额外申请账号，只需要一个外部接口账号

#### 其他特点
rpc服务支持同一外部接口数据在本地多进程分发，比如在服务端连接了ctp接口，订阅了rb1910后，客户端多个进程会自动订阅来自服务端分发的订阅数据# 交易接口
