# VeighNa Station

## 启动程序

### 点击图标启动

安装成功后，双击桌面上VeighNa Station快捷方式：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/veighna_station/1.png)

即可运行VeighNa Station。

### 命令行启动

打开命令行工具，输入veighna回车运行，即可启动VeighNa Station。

## 用户登录

首次使用VeighNa Station时会弹出VeighNa Studio的免责声明，如下图所示：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/veighna_station/2.png)

仔细阅读并点击【确认】之后，会弹出包含用户名输入框、密码输入框、登录按钮和注册按钮的用户登录界面，如下图所示：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/veighna_station/3.png)

用户按照要求在用户名输入框中输入用户名，在密码输入框中输入密码后，点击【登录】按钮，即可完成登录进入VeighNa Station主运行程序。

新用户可以点击【注册】按钮注册账户，注册完成后即可登录。注册时请注意:

- 个人邮箱请如实填写（后续用于找回密码等论坛功能）；
- 用户名自动使用注册时的微信【昵称】（不支持修改）；
- 密码请牢记，该密码也同样用于登录VeighNa社区论坛。

**登录界面只在首次运行VeighNa Station时弹出**，之后运行VeighNa Station时会自动登录。

## 界面窗口

登录完成后，VeighNa Station界面会自动弹出，如下图所示：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/veighna_station/4.png)

界面主要分为菜单栏、标题栏、功能栏、主显示区域、学习与使用区域、官方频道区域几个部分。

### 菜单栏

菜单栏位于顶部，包含【系统】和【帮助】两个按钮。

#### 配置

点击【系统】-【配置】，会弹出系统配置窗口，可以对PyPI索引和pip代理进行修改，如下图所示：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/veighna_station/5.png)

PyPI索引用于更换VeighNa Station使用的pypiserver地址，当留空时默认使用的是https://pypi.org的PyPI服务器。

pip代理默认为空，用户可自行设置。修改后可点击【保存】按钮，对配置进行保存并退出窗口。

#### 登出

点击【系统】-【登出】，会弹出登出窗口，如下图所示：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/veighna_station/6.png)

点击【Yes】会登出用户，并立即关闭程序。用户登出后，在下次启动时，需要重新进行用户登录。

#### 关闭

点击【系统】-【关闭】，会弹出退出窗口，如下图所示：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/veighna_station/7.png)

点击【Yes】立即关闭程序。


### 主窗口

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/veighna_station/9.png)

如上图所示，图中左侧区域为功能栏，右侧区域为主显示区域。功能栏包括社区、交易、投研、加密、更新等内容。随着左侧功能栏的不同选择，右侧主显示区域会显示对应的相关内容。

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/veighna_station/10.png)

如上图所示，VeighNa Station界面左下角为学习与使用区域。

点击【使用文档】后会打开浏览器，并跳转到官方文档https://www.vnpy.com/docs/cn/index.html ，用户可以查询详细的使用说明。

点击【社区求助】后会打开浏览器，并跳转到官方论坛https://www.vnpy.com/forum/ ，用户可以在论坛查询技术贴，并发帖交流。

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/veighna_station/11.png)

如上图所示，学习与使用区域下方为官方频道区域。

从左到右分别为官方的Github仓库，官方微信公众号和官方知乎账号。点击即可打开浏览器直接跳转到相关页面。


## 功能使用

### 社区

点击VeighNa Station左侧的【社区】按钮，右侧主显示区域显示内容为官方论坛，如下图所示：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/veighna_station/3.png)

用户可以在该区域浏览官方论坛内容。

### 交易

点击VeighNa Station左侧的【交易】按钮，右侧主显示区域显示内容为交易接口、应用模块选择区域和信息输出区域，如下图所示：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/veighna_station/12.png)

点击需要加载的交易接口或应用模块后的白色复选框，进行选择。然后点击主显示区域左下角【启动】按钮，即可启动VeighNa Trader。此时，右侧输出区域将输出程序运行中的信息，如下图所示：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/veighna_station/13.png)

点击主显示区域右下角【修改】按钮，可修改运行目录。

### 投研

点击VeighNa Station左侧的【投研】按钮，右侧主显示区域为jupyterlab应用操作目录，如下图所示：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/veighna_station/14.png)

点击主显示区域左下角的【启动】按钮后，将会在右下角指定的运行目录运行jupyterlab应用，可以在jupyterlab应用中进行投研操作，如下图所示：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/veighna_station/15.png)

### 加密

点击VeighNa Station左侧的【投研】按钮，右侧主显示区域显示加密相关内容，如下图所示：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/veighna_station/16.png)

用户可在此界面下将选定的.py文件编译成.pyd文件，对策略进行加密操作。

点击【选择】按钮，在弹出的窗口里选择需要加密的策略文件路径，点击【打开】按钮。此时主显示区域左下角的输入栏将变更为所需要加密文件的绝对路径，如下图所示：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/veighna_station/17.png)

点击【加密】按钮，对文件进行编译。此时中央的显示区域将输出加密过程中的相关信息，如下图所示：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/veighna_station/18.png)

等到输出文件加密进程终止后，将会在加密文件所在位置生成一个加密后的pyd文件。

请注意，加密后需要先**把pyd文件名中的.cp310-win_amd64部分移除**，然后再放进自建strategies文件夹中。

### 更新

点击VeighNa Station左侧的【更新】按钮，右侧主显示区域显示组件更新相关内容，如下图所示：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/veighna_station/19.png)

点击主显示区域左下角的【检查】按钮，将会显示本地已安装模块和版本，如下图所示：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/veighna_station/20.png)

点击主显示区域右下角的【更新】按钮，后台将启动更新进程并输出相关信息，如下图所示：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/veighna_station/21.png)

更新完成后，会弹出通知窗口，点击【OK】并重启VeighNa Station即可。
