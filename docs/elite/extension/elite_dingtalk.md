# 钉钉实时通知

VeighNa Elite Trader主界面的全局配置的窗口提供了钉钉消息通知功能支持。用户可以通过简单的配置，在钉钉会话中收到程序运行过程中的核心系统日志、CTA策略模块日志、组合策略模块日志以及期权策略模块日志。

## 钉钉配置

启动钉钉，创建一个群聊，点击群聊右上角的设置图标，如下图所示：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/elite/ding/1.png)

在弹出的群设置界面下滑，点击【机器人】设置，如下图所示：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/elite/ding/2.png)

在弹出的界面中点击【添加机器人】，然后在机器人选项中选择【自定义】（通过Webhook接入自定义服务）机器人，如下图所示：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/elite/ding/3.png)

在弹出的添加机器人窗口中输入自己定义的机器人名字并选择要发送消息的群，勾选【加签】选项（此时可点击【复制】按钮复制出密钥），点击【完成】按钮即可成功添加机器人配置，如下图所示：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/elite/ding/4.png)

添加完机器人之后，复制处弹出的设置webhook窗口里Webhook地址中access token=后的Token内容，如下图所示：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/elite/ding/5.png)

请注意，若配置时忘记了复制出密钥和Token，可以在添加完及机器人之后，点击群聊右上角的设置图标，选择【机器人】，在跳出窗口中“本群的机器人”部分下选择之前添加的机器人。可在弹出的【配置】窗口中找到密钥和Token信息，如下图所示：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/elite/ding/7.png)


## VeighNa Elite Trader配置

在VeighNa Elite Trader的全局配置窗口中的【钉钉】部分进行配置：

- 启动：选择【是】选项；
- Token：填入钉钉设置webhook窗口时复制出的Token内容；
- 密钥：填入钉钉添加机器人勾选【加签】选项时复制出的密钥。


## 钉钉接收信息样式

VeighNa Elite Trader和钉钉都配置完毕后，VeighNa Elite Trader运行过程中以“$”结尾（过滤普通日志）的日志就会发送到配置Token对应的钉钉群聊会话中了。如下图所示：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/elite/ding/6.png)
