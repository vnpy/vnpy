# WebTrader - Web服务器模块

## 功能简介

WebTrader是用于**Web应用后端服务**的功能模块，用户可以通过浏览器（而非PyQt桌面端）来运行管理VeighNa量化策略交易。

## 架构设计

WebTrader采用了FastAPI作为后端服务器，支持REST主动请求调用和WebSocket被动数据推送，运行时整体框架图如下：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/web_trader/web_trader_1.png)

后端服务包括两个独立的进程：
- 策略交易进程
  - 运行VeighNa Trader的进程，负责所有策略交易功能的运行；
  - 启动了RpcServer用于对Web服务进程功能调用；
- Web服务进程
  - 运行了FastAPI的进程，负责对外提供Web访问的服务；
  - 启动了RpcClient用于调用策略交易进程的相关功能。

从网页端到策略交易进程的双向通讯模式包括：
- 主动请求调用（订阅行情、挂撤单、查询数据）
  - 浏览器发起REST API调用（访问某个URL地址提交数据）到Web服务进程；
  - Web服务进程收到后，转换为RPC请求（Req-Rep通讯模式）发送给策略交易进程；
  - 策略交易进程执行请求处理后，返回结果给Web服务进程；
  - Web服务进程返回数据给浏览器。
- 被动数据推送（行情推送、委托推送）
  - 浏览器发起Websocket连接到Web服务进程；
  - 策略交易进程通过RPC推送（Pub-Sub通讯），将数据推送给Web服务进程；
  - Web服务进程收到后，将数据通过Websocket API实时推送给浏览器（JSON格式）。

## 加载启动

### VeighNa Station加载

启动登录VeighNa Station后，点击【交易】按钮，在配置对话框中的【应用模块】栏勾选【WebTrader】。

### 脚本加载

在启动脚本中添加如下代码：

```python 3
# 写在顶部
from vnpy_webtrader import WebTraderApp

# 写在创建main_engine对象后
main_engine.add_app(WebTraderApp)
```

### 启动模块

在启动模块之前，请先连接登录交易接口（连接方法详见基本使用篇的连接接口部分）。看到VeighNa Trader主界面【日志】栏输出“合约信息查询成功”之后再启动模块，如下图所示：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/market_radar/1.png)

成功连接交易接口后，在菜单栏中点击【功能】-> 【Web服务】，或者点击左侧按钮栏的图标：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/web_trader/web_trader_0.png)

即可进入RPC服务模块的UI界面，如下图所示：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/web_trader/web_trader_3.png)

此时系统中运行的只包括策略交易进程，左上角区域的服务器配置选项包括：
- 用户名和密码：从网页端登录Web应用时所用的用户名和密码，使用时请修改为自己想用的用户名和密码（通过启动目录.vntrader下的web_trader_setting.json修改），请注意这里的用户名和密码与底层交易接口无关；
- 请求和订阅地址：架构图中Web服务进程和策略交易进程之间，进行RPC通讯的地址，注意端口不要和其他程序冲突即可。

点击启动按钮后，会根据用户输入的配置信息在系统后台启动Web服务进程，同时在右侧区域输出Fast API运行过程中的相关日志信息。


## 接口演示
在启动Web服务后，在浏览器打开网址<http://127.0.0.1:8000/docs>，即可看到如下图所示的接口文档网页：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/web_trader/web_trader_2.png)

这里包含了目前WebTrader支持的相关接口信息，下面结合vnpy_webtrader项目下提供的[Jupyter Notebook](https://github.com/vnpy/vnpy_webtrader/blob/main/script/test.ipynb)进行相关的接口演示。

### 获得令牌（token）
```python 3
import requests
import json

url = "http://127.0.0.1:8000/"
username = "vnpy"
password = "vnpy"

r = requests.post(
    url + "token",
    data={"username": username, "password": password},
    headers={"accept": "application/json"}
)
token = r.json()["access_token"]
```
首先导入相应的模块requests和json，接着定义url和用户名和密码，通过requests的post方法传入相应参数就能够获得令牌（token），后续访问使用各种接口直接传入token即可。

### 行情订阅
```
r = requests.post(url + "tick/" + "cu2112.SHFE", headers={"Authorization":"Bearer" + token})
```
通过上述命令可实现对合约cu2112.SHFE的订阅，同时可以在图形界面收到该合约的行情数据推送，入下图所示：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/web_trader/web_trader_4.png)

###  批量查询
```python 3
# 查询函数
def query_test(name):
    """查询对应类型的数据"""
    r = requests.get(
        url + name,
        headers={"Authorization": "Bearer " + token}
    )
    return r.json()

# 批量查询
for name in ["tick", "contract", "account", "position", "order", "trade"]:
    data = query_test(name)
    print(name + "-" * 20)
    if data:
        print(data[0])
```
如有需要，同样可以通过发出主动请求查询相关的数据，比如tick数据、合约数据、账户数据、 持仓数据、委托数据以及成交数据。

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/web_trader/web_trader_5.png)

### 委托测试
```python 3
# 委托测试
req = {
    "symbol": "cu2112",
    "exchange": "SHFE",
    "direction": "多",
    "type": "限价",
    "volume": 1,
    "price": 71030,
    "offset": "开",
    "reference": "WebTrader"
}

r = requests.post(
    url + "order",
    json=req,
    headers={"Authorization": "Bearer " + token}
)
vt_orderid = r.json()

print(vt_orderid)
```
下单后同样能在图形化界面看到委托信息，如下图所示：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/web_trader/web_trader_6.png)

### 撤单测试
```python 3
# 撤单测试
r = requests.delete(
    url + "order/" + vt_orderid,
    headers={"Authorization": "Bearer " + token}
)
```
如果想将之前下的委托撤销，可以发送主动请求，结果同样会在图形化界面更新，如下图所示：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/web_trader/web_trader_7.png)

### Websocket测试

```python 3
# Weboscket测试
from websocket import create_connection

ws = create_connection("ws://127.0.0.1:8000/ws/?token=" + token)

while True:
    result =  ws.recv()
    print("Received '%s'" % result)

ws.close()
```
通过Websocket可以被动接收策略交易进程推送过来的行情数据和委托数据等，如下图所示：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/web_trader/web_trader_8.png)

## 后续计划
WebTrader仅实现了Web应用的后端（提供了浏览器访问数据的接口），而前端页面（也就是浏览器中看到的网页）则按照之前的计划交给社区用户来实现，欢迎大家贡献代码。

同时WebTrader目前只支持基础的手动交易功能，后续将会逐渐加上策略交易应用相关的管理功能（比如CtaStrategy的相关调用）。
