# RPC服务
全局锁GIL的存在导致Python只能利用CPU单核的算力。其单进程架构的不足之处如图所示：

![](https://static.vnpy.com/upload/temp/3f51a477-36db-41d4-9632-75067ba24be7.png)

使用多进程分布式的程序架构可以突破该限制。但每个进程之间的数据，在操作系统内默认是独立隔离的，无法直接访问。
RPC服务正好能解决这个痛点：RPC全称Remote-Procedure-Call，中文“远程过程调用”，是最常用的跨进程通讯方式之一。在vnpy中，一个特定进程连接交易接口充当Server的角色，在本地物理机或者局域网内部进行事件的推送，推送给其他独立的Client进程，如图。

![](https://static.vnpy.com/upload/temp/a67e561d-d94d-43f4-9d40-bb929ed6e0e5.png)

&nbsp;

## RPC服务器

### 加载模块
RPC服务模块处于vnpy/app/rpc_service文件夹中，里面定义了RPC引擎对象，用于将一个特定的vnpy进程包装成RPC服务器，从而进行推送服务端所有事件和处理客户端请求。

可通过下面2种模式加载RPC模块：
- 图形模式：登录VN Station，在上层应用界面勾选RpcService，如图。
  
![](https://static.vnpy.com/upload/temp/62edff53-74d0-4cab-9041-cc209d0b394f.png)

&nbsp;

- 脚本模式：使用run.py启动Vn Trader，在导入模块时额外写下面代码：
```
from vnpy.app.rpc_service import RpcServiceApp
from vnpy.gateway.ctp import CtpGateway
main_engine.add_app(RpcServiceApp)
main_engine.add_gateway(CtpGateway)
```

&nbsp;


### 启动运行
进入Vn Trader，先连接交易接口，如CTP，然后点击菜单栏“功能”->“Rpc服务”，进入如图RPC服务点击“启动”即可。注意：RPC服务不仅支持同一物理机多进程通讯，还支持局域网内部通讯，若在同一台机器上运行，无需修改任何参数。

![](https://static.vnpy.com/upload/temp/44b7223c-a232-4002-9e1f-2067f5e7c30a.png)

&nbsp;

## RPC客户端

### 加载接口
RPC客户端同样提供2种不同的加载模式：
- 图形模式：登录VN Station，在底层接口界面勾选RPC服务，如图。

![](https://static.vnpy.com/upload/temp/659a156c-2bf2-4053-bd91-2c383aff24b2.png)

&nbsp;

- 脚本模式：使用run.py启动Vn Trader，在导入模块时额外写下面代码：

```
from vnpy.gateway.rpc import RpcGateway
main_engine.add_gateway(RpcGateway)
```

&nbsp;

### 连接使用
从客户端的视角看，RpcGateway就是如CTP一般的接口，省去了额外输入账户等信息的步骤。因为统一在服务端已经完成，只需要和服务器端进行连接即可。

进入VnTrader，点击菜单栏”系统“->”连接RPC“，在如图弹出的窗口中点击”连接“即可。

![](https://static.vnpy.com/upload/temp/988fc191-2762-48cb-b0fb-77384dc543f9.png)

&nbsp;

## 参考样例
参考样例位于examples/server_client目录下，其中包括服务器进程和客户端进程。

### 服务器进程
样例提供了run_server.py文件，里面定义了main_ui和main_terminal函数，分别用于GUI模式和无界面模式启动，可以根据需要修改这两个函数，然后选择运行某一个函数即可。

- GUI模式：GUI模式启动和上面提到的run.py启动完全一致，只是run_server.py已经默认加载了RPC模块，用户只需修改加载的外部交易接口即可。

- 无界面模式：需要提前配置好连接CTP等交易接口所需的个人信息，如图：
  
![](https://static.vnpy.com/upload/temp/69010fa2-98c4-47ae-b055-d6709d744385.png)

&nbsp;

### 客户端进程
样例提供了run_client.py，和上述提到的run.py启动VnTrader方式完全一致，只是这里已经默认加载了Rpc接口。

