#vn.demo介绍
该demo主要用于展示如何使用vn.py框架开发交易平台，使用了vn.event和vn.lts模块。

##如何使用
常规用户可以直接运行exe文件夹下的demoMain.exe。

对开发有兴趣的用户需要根据vnpy.org的教程3安装相关的开发环境，然后通过demoMain.py和demoMain.pyw（无cmd界面）运行。

##实现功能
demo的实现参考了盈佳和尔易的LTS交易平台，功能如下：

1. 行情、持仓、账户、成交、报单的监控
2. 平台的日志记录
3. 下单交易，实现了LTS提供的所有订单类型和交易类型
4. 双击报单监控中的单元格撤单，以及下单交易组件一键全撤

##文件说明

 - demoApi.py主要包含了程序的底层接口，对vn.lts中的API进行了简化封装
 - demoEngine.py主要包含了程序的中间层，负责调用底层接口
 - demoUi.py主要包含了用于数据监控和主动函数调用相关的GUI组件
 - demoMain.py包含了程序的主函数入口，双击运行
 - demoMain.pyw功能和demoMain.py一样，双击时会自动调用pythonw.exe运行（无cmd界面）

##nuitka编译说明
要执行nuikta编译，请在本文件夹下打开cmd，并输入以下命令：

nuitka --standalone --windows-disable-console --icon=C:\vn.demo\vnpy.ico demoMain.py

其中C:\vn.demo\vnpy.ico需要修改为用户vn.demo文件夹的路径。




