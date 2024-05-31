# 飞书实时通知

VeighNa Elite Trader主界面的全局配置的窗口提供了飞书消息通知功能支持。用户可以通过简单的配置，在飞书会话中收到程序运行过程中的核心系统日志、CTA策略模块日志、组合策略模块日志以及期权策略模块日志。

## 飞书配置

启动飞书，创建一个群聊，点击群聊右上角的省略号，再点击设置图标，如下图所示：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/elite/feishu/1.png)

在弹出的设置界面中点击【群机器人】设置，如下图所示：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/elite/feishu/2.png)

在弹出的界面中点击【添加机器人】，然后在机器人选项中选择【自定义机器人】，如下图所示：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/elite/feishu/3.png)

先输入自己定义的机器人名称和描述，如下图所示：
![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/elite/feishu/4.png)

再点击【添加】按钮继续设置Webhook地址（此时可点击【复制】按钮复制出Webhook地址）。接着可以勾选安全设置的【签名校验】选项进行加密（此时可点击【复制】按钮复制出密钥），点击【完成】按钮即可成功添加机器人配置，如下图所示：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/elite/feishu/5.png)

请注意，若配置时忘记了复制出Webhook地址和密钥，可以在添加完及机器人之后，在群聊设置中，选择【群机器人】，在跳出窗口中“群机器人”部分下选择之前添加的机器人。可在弹出的【机器人】窗口中找到Webhook地址和密钥信息，如下图所示：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/elite/feishu/6.png)


## VeighNa Elite Trader配置

在VeighNa Elite Trader的全局配置窗口中的【飞书】部分进行配置：

- 启动：选择【是】选项；
- URL：填入飞书设置webhook窗口时复制出的Webhook地址；
- 密钥：填入飞书添加机器人勾选【签名校验】选项时复制出的密钥。


## 飞书接收信息样式

VeighNa Elite Trader和飞书都配置完毕后，VeighNa Elite Trader运行过程中的核心系统日志、CTA策略模块日志、组合策略模块日志以及期权策略模块日志就会发送到配置URL对应的飞书群聊会话中了。如下图所示：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/elite/feishu/7.png)
