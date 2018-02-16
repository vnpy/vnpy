# WebTrader使用说明

**开发作者：cccbbbaaab**

## 使用步骤

1. 修改CTP_connect.json中的账号和服务器地址
2. 修改WEB_setting.json中的网页登录用户名和密码
3. 打开cmd，运行python server.py
4. 打开另一个cmd，运行python run.py
5. 用浏览器（推荐Chrome）访问http://localhost:5000/
6. 输入2中的用户名和密码登录后，点击左下角的“连接CTP”
7. 网页前端的使用方法和常规版本的VnTrader基本一致
8. 如需运行CTA策略，请修改CTA_setting.json中的配置

## 文件功能

* server.py：基于vnpy.rpc模块实现的交易服务器，包含CTP接口和CTA策略模块
* run.py：基于Flask实现的Web服务器，内部通过vnpy.rpc客户端来访问交易服务器

## 架构设计

* 基于Flask-Restful实现的主动函数调用功能，数据流程：
	1. 用户点击浏览器中的某个按钮，发起Restful功能调用
	2. Web服务器收到Restful请求，将其转化为RPC功能调用发送给交易服务器
	3. 交易服务器收到RPC请求，执行具体的功能逻辑，并返回结果
	4. Web服务器返回Restful请求的结果给浏览器

* 基于Flask-Socketio实现的被动数据推送功能，数据流程：
	1. 交易服务器的事件引擎转发某个事件推送，并推送给RPC客户端（Web服务器）
	2. Web服务器收到事件推送后，将其转化为json格式，并通过Websocket发出
	3. 浏览器通过Websocket收到推送的数据，并渲染在Web前端界面上

* 将程序分为两个进程的主要原因包括：
	1. 交易服务器中的策略运行和数据计算的运算压力较大，需要保证尽可能保证低延时效率
	2. Web服务器需要面对互联网访问，将交易相关的逻辑剥离能更好保证安全性