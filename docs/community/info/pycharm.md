# PyCharm开发指南

PyCharm是由JetBrains公司推出针对Python语言的IDE，其内置一整套可以帮助用户在使用Python语言开发时提高其效率的工具。本文档意在为用户提供通过PyCharm开发使用VeighNa的方案以供参考。

本文档中的内容基于Windows系统编写，但对于Linux/Mac系统大部分也都适用。

VeighNa适用的Windows系统包括：

- Windows 10/11
- Windows Server 2019/2022

> 其他版本的Windows系统安装时可能遇到各种依赖库问题，不推荐使用。

在Windows系统上使用VeighNa，推荐安装官方推出的【VeighNa Studio】Python发行版，**尤其是初次接触Python开发的新手用户**。


## PyCharm安装

首先从[PyCharm官网](https://www.jetbrains.com/pycharm/download/?section=windows#section=windows)下载PyCharm Community安装包：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/pycharm/1.png)

下载完成后，双击安装包则可进入PyCharm安装向导：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/pycharm/2.png)

如果想对安装选项进行设置，可以在PyCharm Community Edition Setup页面对相关选项进行勾选：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/pycharm/3.png)

安装完成后，会跳转到安装成功页面：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/pycharm/4.png)

如果前面勾选了Create Desktop Shortcut选项来创建桌面快捷方式的话，此时桌面上会出现PyCharm的图标，双击图标即可运行PyCharm。


## VeighNa开发

### 创建项目

启动PyCharm之后，在弹出的欢迎界面中点击【New Project】创建新项目，如下图所示：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/pycharm/6.png)

在弹出的新项目窗口中，首先需要选择存放项目的文件夹路径【Location】，然后勾选Python解释器选项中的【Previously configured interpreter】选项（即当前系统中已经安装的Python环境）：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/pycharm/7.png)

点击右侧Add Interpreter下拉框中的【Add Local Interpreter】，在弹出的对话框中点击左侧的【System Interpreter】标签，并在右侧出现的下拉框中选择VeighNa Studio自带Python解释器所在的路径：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/pycharm/8.png)

点击底部的【OK】按钮保存解释器配置，回到新项目窗口中，点击右下方的【Create】按钮来完成新项目的创建：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/pycharm/9.png)

创建成功的项目窗口如下图所示：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/pycharm/10.png)

此时点击左上方的【External Libraries】，即可看到项目中可以调用的外部库：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/pycharm/11.png)

点击site_packages文件夹，往下滚动就能扎到VeighNa Studio中vnpy核心框架包以及vnpy_前缀的插件模块包。此时可以通过点击对应图标来查看每个包中的文件源码，如下图所示：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/pycharm/13.png)

把鼠标光标移到代码上方，会自动弹出对应代码的文档信息：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/pycharm/14.png)

若按住Ctrl键的同时用鼠标左键点击代码，则会跳转到代码的声明部分：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/pycharm/15.png)

点击窗口右下角的【Python 3.10】按钮，会弹出【Settings】项目配置窗口，可以看到当前解释器环境下安装的包名称、本地版本号、最新版本号。带有升级符号（向上箭头）的包，说明当前版本不是最新版，点击升级符号即可自动升级。

> 请注意：由于VeighNa对于部分依赖库有严格的版本要求，不建议用户手动升级安装的包到最新版，可能会出现版本冲突。

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/pycharm/49.png)

### 运行程序

从Github代码仓库下载[VeighNa Trader启动脚本文件run.py](https://github.com/vnpy/vnpy/blob/master/examples/veighna_trader/run.py)，并将其放置于trader文件夹下，即可在窗口左侧的项目导航栏中看见run.py文件：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/pycharm/16.png)

若部分代码下方可以看见绿色波浪线显示（变量名称英文词语检查），可以点击项目名称左方的主菜单按钮 -【File】-【Settings】-【Editor】-【Inspections】-【Proofreading】，取消【Typo】的勾选后点击【OK】确认。再回到主窗口，可以发现绿色波浪线已经消失：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/pycharm/17.png)

点击鼠标右键，选择【Run 'run'】，即可开始运行run.py脚本：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/pycharm/21.png)

此时在界面底部的终端内容输出区域中，可以看到程序运行时的打印信息：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/pycharm/19.png)

<span id="jump">

与此同时，VeighNa Trader的主窗口也会自动弹出显示：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/pycharm/20.png) 

</span>

回到PyCharm，可以看到项目界面右上角已经有run脚本的运行记录了，后续直接点击三角形运行按钮也可运行脚本，如下图所示：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/pycharm/18.png)


### 断点调试

PyCharm的断点调试功能十分强大，这里使用一个VeighNa的策略历史回测脚本来演示。

在左侧项目导航栏中点击鼠标右键，选择【New】-【File】, 在弹出的对话框中创建backtest.py：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/pycharm/25.png)

然后在文件中编写一段策略回测代码（具体可参考Github仓库中的[回测示例](https://github.com/vnpy/vnpy/blob/master/examples/cta_backtesting/backtesting_demo.ipynb)），在想要调试的地方打上断点，如下图所示：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/pycharm/26.png)

点击鼠标右键选择【Debug 'backtest'】, 即可开始调试脚本：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/pycharm/27.png)

此时项目界面右上角已经可以看到backtest.py的运行记录，后续也可以通过点击这里的按钮直接启动调试任务：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/pycharm/28.png)

启动调试后，可以看到主界面底部的Debug窗口开始输出程序运行信息，并且程序会暂停运行在第一个断点处。左侧显示的是线程信息，右侧则是当前上下文中的变量信息：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/pycharm/29.png)

点击类似播放键的【Resume Program】即可继续运行调试，直到下一个断点处再次暂停：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/pycharm/30.png)

此时可以看到底部右侧监控窗口中，当前上下文中的变量发生了变化：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/pycharm/31.png)

后续重复上述步骤，点击【Resume Program】直到调试结束，可以看到Debug窗口的相应输出：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/pycharm/32.png)

调试完之后，点击【Rerun 'backtest'】即可重新调试：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/pycharm/33.png)

在调试过程中，点击【Step Into】可以进入函数的内部查看运行时的细节状态：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/pycharm/34.png)

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/pycharm/35.png)

点击【Step Out】则可跳出当前函数，查看外层调用栈的状态：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/pycharm/37.png)

点击【Step Over】可越过子函数（子函数会执行）：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/pycharm/36.png)

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/pycharm/38.png)

点击【Stop 'backtest'】则会直接停止当前程序的运行：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/pycharm/39.png)

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/pycharm/40.png)

#### 指定程序的运行目录

在PyCharm新建项目时，默认是在当前目录下运行程序。若需要指定程序运行的目录，可以点击项目界面右上角的【Edit】进入【Run/Debug Configurations】界面：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/pycharm/43.png)

修改程序启动时的目录【Working directory】：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/pycharm/44.png)

#### C++回调断点调试

通常情况下，PyCharm只能在Python解释器中启动的线程里进行代码断点调试。之前有部分用户反馈过尝试在C++回调函数（如CTP API接口、PySide图形库等）中打断点但无法起效的问题。针对这种情况，可以通过在代码中设置断点的方式，来实现对非Python线程（即C++）的断点调试。

在项目左侧导航栏中点击鼠标右键，选择【New】-【File】, 创建geteway_test.py。

在创建成功的geteway_test.py中添加一段脚本策略的代码（可参考[该文件](https://github.com/vnpy/vnpy/blob/master/examples/veighna_trader/demo_script.py)），然后按住Ctrl同时用鼠标左键点击代码中的CtpGateway，跳转至ctp_gateway.py的源码中，在想要调试的回调函数内打上断点（注意不要打在函数定义的def那一行），如下图所示：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/pycharm/50.png)

回到gateway_test.py，点击鼠标右键选择【Debug 'gateway_test'】, 即可开始调试：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/pycharm/51.png)

> 请注意，如果用load_json函数读取connect_ctp.json，请确保读取对应.vntrader文件夹的json文件中配置了CTP账户登录信息。

此时可观察到并没有进入之前设定的断点，如下图所示：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/pycharm/52.png)

终止调试后，找到之前在ctp_gateway.py中设定的断点处，在回调函数内的断点之前添加以下代码：

```Python 3
import pydevd
pydevd.settrace(suspend=False, trace_only_current_thread=True)
```

请注意：
 - pydevd是PyCharm自带的调试插件，没有安装在Python解释器所在的Python环境里；
 - suspend参数设置为True之后，调试会在这一句代码运行完之后暂停，而不是停在断点处。trace_only_current_thread参数设置为True之后，调试过程中只会监控当前线程；
 - 调试结束之后不要忘记删掉这段代码。

然后再次运行调试gateway_test.py脚本：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/pycharm/53.png)

此时可以看到底部的调试窗口中开始输出相关信息，同时程序暂停在了之前设置的断点处。左侧显示的是线程信息（可以看到多了一个Dummy线程显示），右侧显示的是变量信息（可以看到回调函数的入参）：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/pycharm/54.png)


## 对比VS Code

1. 在PyCharm中，每个项目都需要对Python环境进行配置。在VS Code中，默认通过窗口右下角的Python解释器来选择全局的Python环境（针对所有打开的文件）；

2. PyCharm的Community版仅对Jupyter提供了只读支持，需要Professional版才能编辑和运行。VS Code仅需安装功能插件，就可以使用和Jupyter相关全部功能（包括读取、编辑、运行）。
