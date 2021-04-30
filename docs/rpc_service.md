# RPC服务

全局解释器锁GIL的存在导致Python只能利用CPU单核的算力。尽管使用多进程分布式的程序架构可以突破该限制。但每个进程之间的数据在操作系统内默认是独立隔离的，无法直接访问。

远程过程调用(Remote Procedure Call Protocol, RPC)服务可以用于**跨进程或者跨网络的服务功能调用**，有效解决了上述问题。

RPC服务可实现以下**应用场景**：

- 针对运行策略数量较多的用户，只需本地一条行情和交易通道，可以支持多个客户端进程同时交易，且每个客户端中交易策略独立运行，互不影响；
- 针对中小型投资机构用户，可以在通过在服务端加载各种交易接口以及RiskManagerApp，实现一个轻量级的资管交易系统，多个交易员共享统一的交易通道，并实现基金产品级别的风险管理。


vn.py提供了一套包含服务端和客户端的RPC服务。具体来说，一个特定的进程连接交易接口充当**服务器**的角色，在本地物理机或者局域网内部向其他独立的**客户端**进程主动推送事件，并处理客户端相关请求，如下图所示。

![](https://static.vnpy.com/upload/temp/a67e561d-d94d-43f4-9d40-bb929ed6e0e5.png)

下面将对服务器端和客户端分别进行介绍。


## RpcService - 服务器端

RpcService模块用于将VN Trader进程转化为RPC服务器，对外提供交易路由、行情数据推送、持仓资金查询等功能。

### 加载启动

#### VN Station加载

启动登录VN Station后，点击【VN Trader Pro】按钮，在配置对话框中的【上层应用】栏勾选【RpcService】。

#### 脚本加载

在启动脚本中添加如下代码：

```
# 写在顶部
from vnpy.app.rpc_service import RpcServiceApp

# 写在创建main_engine对象后
main_engine.add_app(RpcServiceApp)
```

### 启动模块

在启动模块之前，请先连接登录交易接口（连接方法详见基本使用篇的连接接口部分）。看到VN Trader主界面【日志】栏输出“合约信息查询成功”之后再启动模块，如下图所示：  

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/market_radar/1.png) 

成功连接交易接口后，在菜单栏中点击【功能】-> 【RPC服务】，或者点击左侧按钮栏的图标：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/rpc_service/1.png) 

即可进入RPC服务模块的UI界面，如下图所示：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/rpc_service/2.png) 

### 启动RPC服务

点击【启动】按钮即可启动RPC服务，此时日志输出"RPC服务启动成功"，如下图所示：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/rpc_service/3.png) 

请注意，RPC服务不仅支持同一物理机多进程通讯，还支持局域网的内部通讯，若在同一台机器上运行，无需修改任何参数。

启动成功后，如需停止RPC服务可以点击【停止】按钮，此时日志输出"RPC服务已停止"。


## RpcGateway - 客户端

RpcGateway将RPC服务器视作类似于CTP的服务端系统，通过标准Gateway来连接并进行交易，对上层应用完全透明。

### 加载接口

#### VN Station加载

启动登录VN Station后，点击【VN Trader Pro】按钮，在配置对话框中的【底层接口】栏勾选【RPC服务】，如下图所示：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/rpc_service/4.png)

#### 脚本加载

在启动脚本中添加如下代码：

```
# 写在顶部
from vnpy.gateway.rpc import RpcGateway

# 写在创建main_engine对象后
main_engine.add_gateway(RpcGateway)
```

### 连接使用

从客户端的视角看，RpcGateway是类似CTP的接口。因为已经在服务端统一完成配置，只需要和服务器端进行连接即可，省去了额外输入账户等信息的步骤。

在VnTrader的菜单栏中点击【系统】->【连接RPC】，在弹出的窗口中点击【连接】即可连接使用，如下图所示。

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/rpc_service/5.png)

           
## 参考样例

RPC服务的参考样例位于examples/server_client目录下（需要从[github](https://github.com/vnpy/vnpy/tree/master/examples/client_server)上下载），其中包括服务器进程和客户端进程。

### 服务器进程

服务器进程的参考样例提供了run_server.py文件，默认加载了CtpGateway和RpcServiceApp。用户可以根据需要修改该文件，在无界面模式下运行服务器进程。

请注意，需要提前修改下述参数来配置连接CTP等交易接口所需的个人信息。

```
setting = {
    "用户名": "",
    "密码": "",
    "经纪商代码": "9999",
    "交易服务器": "180.168.146.187:10101",
    "行情服务器": "180.168.146.187:10111",
    "产品名称": "simnow_client_test",
    "授权编码": "0000000000000000",
    "产品信息": ""
}
```

配置完毕后，在文件所属目录中打开cmd窗口，输入下述命令运行该文件。

```
python run_server.py
```

运行后将自动连接CTP接口并启动RPC服务，如下图所示:

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/rpc_service/6.png)

### 客户端进程

参考样例提供了run_client.py文件，默认加载了RpcGateway和CtaStrategyApp，用户可以根据需要修改该文件来运行客户端进程。

在文件所属目录中打开cmd窗口，输入下述命令运行该文件。

```
python run_client.py
```

运行后将弹出VN Trader的UI界面，成功连接RPC接口后，使用体验和直接加载CTP接口完全一致，且上层的CTA策略模块也可以完全无缝兼容使用。




