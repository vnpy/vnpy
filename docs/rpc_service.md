# RpcService - RPC服务模块

## 功能简介

RpcService模块用于将VeighNa Trader进程转化为RPC服务器，对外提供交易路由、行情数据推送、持仓资金查询等功能。

关于RPC的具体应用场景请参考本文档最后的【RPC的应用场景】版块。

## 加载启动

### VeighNa Station加载

启动登录VeighNa Station后，点击【交易】按钮，在配置对话框中的【应用模块】栏勾选【RpcService】。

### 脚本加载

在启动脚本中添加如下代码：
›
```python 3
# 写在顶部
from vnpy_rpcservice import RpcServiceApp

# 写在创建main_engine对象后
main_engine.add_app(RpcServiceApp)
```

### 启动模块

在启动模块之前，请先连接登录交易接口（连接方法详见基本使用篇的连接接口部分）。看到VeighNa Trader主界面【日志】栏输出“合约信息查询成功”之后再启动模块，如下图所示：  

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/market_radar/1.png) 

成功连接交易接口后，在菜单栏中点击【功能】-> 【RPC服务】，或者点击左侧按钮栏的图标：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/rpc_service/1.png) 

即可进入RPC服务模块的UI界面，如下图所示：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/rpc_service/2.png) 

## 配置和使用

### 配置RPC服务
RPC服务基于ZeroMQ开发，对外的通讯地址包括：

* **请求响应地址**
    * 用于被动接收客户端发送过来的请求，执行对应任务后返回结果；
    * 功能举例：
        * 行情订阅；
        * 委托下单；
        * 委托撤单；
        * 初始化信息查询（合约、持仓、资金等）；
* **事件广播地址**
    * 用于主动推送服务端收到的事件数据，到所有已连接的客户端；
    * 功能举例：
        * 行情推送；
        * 委托推送；
        * 成交推送。

以上地址均采用ZeroMQ的地址格式，由**通讯协议**（如tcp://）和**通讯地址**（如127.0.0.1:2014）两部分组成。

RPC服务支持的通讯协议包括：

* **TCP协议**
    * 协议前缀：tcp://
    * Windows和Linux系统均可使用
    * 可用于本机通讯（127.0.0.1）或者网络通讯（网络IP地址）
* **IPC协议**
    * 协议前缀：ipc://
    * 只能在Linux系统上使用（POSIX本地端口通讯）
    * 只能用于本机通讯，后缀为任意字符串内容

一般推荐直接使用TCP协议（以及默认地址），对于使用Ubuntu系统且希望追求更低通讯延时的用户可以使用IPC协议。

### 运行RPC服务

完成通讯地址的配置后，点击【启动】按钮即可启动RPC服务，日志区域会输出"RPC服务启动成功"，如下图所示：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/rpc_service/3.png) 

启动成功后，即可在另一VeighNa Trader进程中（客户端）使用RpcGateway来连接

如需停止RPC服务可以点击【停止】按钮，此时日志输出"RPC服务已停止"。


### 连接客户端

VeighNa提供了与RpcService配套使用的RpcGateway，作为客户端的标准接口来连接服务端并进行交易，对上层应用完全透明。

从客户端的视角看，RpcGateway是类似CTP的接口。因为已经在服务端统一完成外部交易账户的配置连接，客户端只需要和服务器端进行通讯即可，无需再次输入账户密码等信息。

在客户端加载RpcGateway接口后，进入VeighNa Trader主界面，点击菜单栏中【系统】->【连接RPC】，在弹出的窗口中点击【连接】即可连接使用，如下图所示。

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/rpc_service/5.png)

【主动请求地址】和【推送订阅地址】，分别对应之前在服务端配置的【请求响应地址】和【事件广播地址】，注意不要写反。


## RPC简介

由于全局解释器锁GIL的存在，导致单一Python进程只能利用CPU单核的算力。远程过程调用（Remote Procedure Call Protocol, RPC）服务可以用于**跨进程或者跨网络的服务功能调用**，有效解决了上述问题。

由一个特定的进程连接交易接口充当**服务器**的角色，在本地物理机或者局域网内部向其他独立的**客户端**进程主动推送事件，并处理客户端相关请求，如下图所示：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/rpc_service/7.png)

## RPC服务（RpcService）的应用场景

- 针对运行策略数量较多的用户，只需本地一条行情和交易通道，可以支持多个客户端进程同时交易，且每个客户端中交易策略独立运行，互不影响；
- 针对中小型投资机构用户，可以通过在服务端加载各种交易接口以及RiskManagerApp，实现一个轻量级的资管交易系统，多个交易员共享统一的交易通道，并实现基金产品级别的风险管理。
