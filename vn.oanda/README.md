# vn.oanda

### 简介
OANDA外汇交易接口，基于REST API开发，实现了以下功能：

1. 发送、修改、撤销委托

2. 查询委托、持仓（按照每笔成交算）、汇总持仓（按照单一货币对算）、资金、成交历史

3. 实时行情和成交推送

4. 获取Forex Lab中的日历、订单簿、历史持仓比、价差、交易商持仓、Autochartist

目前该API尚处于测试阶段，如果发现bug或者需要改进的地方请在github上开issue给我。

### 特点
相比较于[OANDA官网](http://developer.oanda.com/rest-live/sample-code/)上贴出的一些Python API（如pyoanda、oanda-trading-environment等），vn.oanda的一些不同：

1. 面向对象的API设计，接近CTP API的结构，对于国内用户而言更容易上手

2. 三个独立的工作线程，分别处理：用户请求（如发送委托等）、行情推送、事件推送（如成交事件等），提供更高的性能

3. 参考CTP API的设计，主动函数调用的结果通过异步（回调函数）的方式推送到程序中，适用于开发真正可靠的实盘交易程序（pyoanda里使用的同步阻塞工作模式在实盘应用中的风险：想象你的交易程序发送委托请求后，因为网络问题不能立即返回，因此主线程阻塞导致界面卡死或者背后的策略引擎线程卡死，对新的行情事件完全失去响应）

### Quick Start
1. 安装Anaconda 2.7 32位

2. 前往[OANDA](http://www.oanda.com)注册一个fxTrade practice测试账户（注意国家不要选中国，会无法申请API token，作者测试英国可以）

3. 在网站登陆后，进入Manage Funds，记录下自己的Account Number

4. 回到上一个界面，左侧有个Manage API Access（在Recent Logins上方，没有的就是第一步国家选错了），进入后生成token

5. 下载vn.oanda到本地后，打开test.py，修改token和accountId为你的信息

6. 将test.py中想要测试的功能取消注释，开始使用吧！

### API版本
日期：2016-02-27

链接：[http://developer.oanda.com/rest-live/introduction/](http://developer.oanda.com/rest-live/introduction/)

