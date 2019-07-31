# RPC服务

由于全局锁GIL的存在，单进程的Python程序只能利用CPU单核的算力，为了突破这一限制，解决方案就是多进程分布式的程序架构。但每个进程之间的数据，在操作系统内默认是独立隔离的，无法直接访问。RPC全称Remote-Procedure-Call，中文“远程过程调用”，是最常用的跨进程通讯方式之一。

以下是单进程架构的一些不足：

![](https://static.vnpy.com/upload/temp/3f51a477-36db-41d4-9632-75067ba24be7.png)

以下是RPC服务框架图示：

![](https://static.vnpy.com/upload/temp/a67e561d-d94d-43f4-9d40-bb929ed6e0e5.png)

由一个特定的vnpy进程与外部交易接口例如CTP等建立连接，然后充当Server的角色，在本地物理机或者局域网内部进行事件的推送，推送给其他独立的vnpy客户端进程。
## RPC服务器

### 加载模块

在vnpy/app/目录下，有rpc_service文件夹，里面定义了Rpc引擎对象，用于将一个特定的vnpy进程包装成RPC服务器，从而进行推送服务端所有事件和处理客户端请求。在加载这个模块时，有两种操作方式：

- 使用vnstation登录vnpy的用户，在勾选加载模块时将RpcService选中即可。**注**：不要忘记加载所需的外部交易接口。

![](https://static.vnpy.com/upload/temp/62edff53-74d0-4cab-9041-cc209d0b394f.png)

- 使用run.py启动Vn Trader的用户，在导入模块时额外写```from vnpy.app.rpc_service import RpcServiceApp```以及在main函数里加载该模块即可```main_engine.add_app(RpcServiceApp)```。**注**：不要忘记加载所需的外部交易接口如```from vnpy.gateway.ctp import CtpGateway```以及在main函数里写```main_engine.add_gateway(CtpGateway)```。


### 启动运行

按上述步骤成功启动Vn Trader后，首先对用户所需的外部交易接口如CTP等进行连接，然后点击菜单栏“功能”->“Rpc服务”，在如下跳出的窗口中点击“启动”即可运行RPC服务。

**注**：RPC服务不仅支持同一物理机多进程通讯，还支持局域网内部通讯，若在同一台机器上运行，无需修改任何参数。

![](https://static.vnpy.com/upload/temp/44b7223c-a232-4002-9e1f-2067f5e7c30a.png)

## RPC客户端

### 加载接口
在vnpy/gateway文件夹下定义了rpc的gateway模块，有两种不同的加载方式：
- 使用vnstation登录vnpy的用户，在勾选底层接口时，将RPC服务选中即可。
![](https://static.vnpy.com/upload/temp/659a156c-2bf2-4053-bd91-2c383aff24b2.png)

- 使用run.py启动Vn Trader的用户，在导入模块时额外写```from vnpy.gateway.rpc import RpcGateway```，以及在main函数加载一下即可```main_engine.add_gateway(RpcGateway)```。

### 连接使用

从客户端的视角看，RpcGateway就是一个和CtpGateway等一样的Gateway，只是不需要再额外输入账户等信息，因为统一在服务端已经完成，只需要和服务器端进行连接即可。

在vntrader打开后，点击菜单栏”系统“->”连接RPC“，在弹出的窗口中点击”连接“即可。

![](https://static.vnpy.com/upload/temp/988fc191-2762-48cb-b0fb-77384dc543f9.png)

## 参考样例

位于examples/server_client目录下。

### 服务器进程
样例提供了run_server.py文件，里面定义了main_ui和main_terminal函数，分别用于GUI模式和无界面模式启动，可以根据需要修改这两个函数，然后选择运行某一个函数即可。
GUI模式：GUI模式启动和上面提到的run.py启动完全一致，只是run_server.py已经默认加载了RPC模块，用户只需修改加载的外部交易接口即可。
&nbsp;
无界面模式：需要提前配置好连接CTP等交易接口所需的个人信息，如图：
![](https://static.vnpy.com/upload/temp/69010fa2-98c4-47ae-b055-d6709d744385.png)

### 客户端进程
样例提供了run_client.py，和上述提到的run.py启动Vn Trader方式完全一致，只是这里已经默认加载了Rpc接口。

