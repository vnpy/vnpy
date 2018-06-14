# vnpy.api.huobi

### 简介

火币电子货币交易接口，交易基于Rest API开发，行情基于Websocket API开发，实现了官方提供API的全部功能。

### 特点
相比较于[火币官方](http://github.com/huobiapi/API_Docs/)给出的Python API实现，本实现的一些特点：

1. 面向对象的API设计，接近CTP API的结构，对于国内用户而言更容易上手

2. 参考CTP API的设计，主动函数调用的结果通过异步（回调函数）的方式推送到程序中，适用于开发稳定可靠的实盘交易程序

### API版本
日期：2018-3-14

链接：[http://github.com/huobiapi/API_Docs/wiki](http://github.com/huobiapi/API_Docs/wiki)

