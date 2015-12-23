# vn.py 
基于python的开源交易平台开发框架

## vn.py框架交流群
QQ群号：262656087

相关问题在这个里面问的答复最快。

## 2015/12/23项目状态
完成了飞马和金仕达黄金T+D（浦发银行）的接口封装。

其中vn.ksgold使用时，必须把ksgoldapi下的SLEdll复制到python.exe所在的文件夹下。


## 2015/12/9项目状态##
中间缺失了相当一段内容的更新，说明文档计划重新做一下了。

本次更新的主要内容是vn.ksotp，金仕达期权API的封装接口（已经加入了vn.trader）。

本套接口同时支持:
1. 现货期权（ETF、个股）
2. 股指期权
3. 商品期权

使用前，必须把ksotpapi下的KSInterB2C.lkc（接口授权文件）放到python.exe所在的文件夹下。

例如，把Anaconda安装在了D:\Anaconda下的话，就需要把KSInterB2C.lkc复制粘贴到D:\Anaconda文件夹，否则运行时Python虚拟机会捕获未知C++错误的异常。

另外需要测试账户的请联系南华期货高贝贝申请，15021816078，说vn.py群介绍，对方会提供。

## 2015/4/24项目状态##
发布了基于vn.ctp的Demo，在vn.demo/ctpdemo文件夹下，可用于CTP柜台期货公司的手动交易。

## 2015/4/20项目状态##
发布了用于展示如何使用vn.py框架开发的vn.demo，使用了vn.event和vn.lts模块，可以用于华宝证券LTS柜台的手动交易。

demo的简单说明：

- demoApi.py主要包含了程序的底层接口，对vn.lts中的API进行了简化封装
- demoEngine.py主要包含了程序的中间层，负责调用底层接口
- demoUi.py主要包含了用于数据监控和主动函数调用相关的GUI组件
- demoMain.py包含了程序的主函数入口，双击运行
- demoMain.pyw功能和demoMain.py一样，双击时会自动调用pythonw.exe运行（无cmd界面）


接下来将会发布几篇和vn.demo相关的教程在vnpy.org网站上。

## 2015/3/26项目状态##
因为有不少人问CTP的接口，正好我最近的项目也要用到，就把开发CTP封装的工作提前了。

CTP的python封装发布在vn.ctp文件夹下： 
 
1. 封装使用的API是最新支持期货交易所期权的6.3.0版本  
2. md部分已经完全经过了测试  
3. td部分只进行了少量测试，接下来几天会继续，测试仅会覆盖和交易相关的函数（银期转账等等测试大家有需要自己做吧）

## 2015/3/3项目状态 ##
目前完成：  

1. 华宝证券的LTS API的python封装，发布在vn.lts文件夹下  
2. 事件驱动引擎，发布在vn.event文件夹下  

### vn.lts   ###
ltsapi：华宝证券官方的LTS C++ API  
pyscript：用于自动生成重复度较高的封装代码的python脚本  
vnltsmd：行情API的封装源代码和测试脚本  
vnltstd：交易API的封装源代码和测试脚本  

### vn.event ###
eventType：定义事件类型常量  
eventEngine：包含事件驱动引擎实现  

## 下一步计划 ##
1. API封装、编译、使用方面的教程
2. 事件驱动引擎原理、使用方面的教程
3. 基于API和引擎开发的LTS交易客户平台（因为华宝没有提供官方的LTS交易软件，目前的两个实现分别是基于C++的尔易终端和基于.COM封装的盈佳终端）
4. 策略引擎接口

## 联系作者 ##
作者知乎名：用python的trader，想要联系作者可以通过知乎私信。

## License ##
MIT

