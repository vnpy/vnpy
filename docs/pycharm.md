# PyCharm开发VeighNa指南

PyCharm 是JetBrains公司研发，用于开发Python的IDE开发工具。其带有一整套可以帮助用户在使用Python语言开发时提高其效率的工具。本文档意在为用户提供通过PyCharm开发使用VeighNa框架的方案以供参考。

本文档中适用的Windows系统包括：

- Windows 10/11
- Windows Server 2019

> 其他版本的Windows系统安装VeighNa时可能遇到各种依赖库问题，不推荐使用。

在Windows系统上使用VeighNa，推荐安装官方推出的【VeighNa Studio Python发行版】，**尤其是初次接触Python的编程新手**。


## VeighNa Station安装

可参考Windows安装指南篇。

## Pycharm安装

在[Pycharm官网](https://www.jetbrains.com/pycharm/download/?section=windows#section=windows)可以下载Pycharm Community安装包, 如下图所示：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/pycharm/1.png)

下载完成后，双击安装包则可进入PyCharm安装向导，如下图所示：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/pycharm/2.png)

如果想对安装选项进行设置，可以在PyCharm Community Edition Setup页面对相关选项进行勾选，如下图所示：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/pycharm/3.png)

安装完成后，会转换到安装成功页面，如下图所示：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/pycharm/4.png)

若在PyCharm Community Edition Setup页面勾选了Create Desktop Shortcut选项创建了桌面快捷方式的话，此时桌面则会出现PyCharm的图标，双击图标即可运行PyCharm。


## Pycharm开发VeighNa

### 创建新项目

启动PyCharm之后，在弹出的欢迎界面中点击【New Project】创建新项目，如下图所示：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/pycharm/6.png)

在弹出的新项目窗口中，对存放项目的文件夹路径进行选择（这里选择了一个空的trader文件夹做示例），如下图所示：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/pycharm/5.png)

选择完项目路径之后，再勾选Python解释器选项中的【Previously configured interpreter】选项，如下图所示：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/pycharm/7.png)

点击右侧Add Interpreter下拉框中的【Add Local Interpreter】，在弹出的添加Python解释器窗口中选择【System Interpreter】标签，选择VeighNa Studio自带python的路径，如下图所示：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/pycharm/8.png)

- 文档示例是基于VeighNa Studio示范的。若是在Conda上进行了手动安装，也需选择对应的python解释器，如下图所示：
![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/pycharm/24.png)

点击“OK”保存解释器配置，回到新项目窗口中，点击“Create”创建新项目，如下图所示：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/pycharm/9.png)

创建成功项目如下图所示：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/pycharm/10.png)

点击界面左上角的External Libraries，即可看到项目的外部库，如下图所示：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/pycharm/11.png)

点击site_packages文件夹，可以看见python环境中安装的包，如下图所示：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/pycharm/12.png)

往下滑就能看见VeighNa Studio中vnpy以及vnpy开头的包，此时可以通过图形界面点击查看对应包的源码，如下图所示：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/pycharm/13.png)

把鼠标光标移到代码上方，还能显示对应代码的文档介绍，如下图所示：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/pycharm/14.png)

若按住Ctrl再点击用鼠标左键代码（Ctrl+B与其效果一致），则会跳转到代码的声明部分，如下图所示：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/pycharm/15.png)

### PyCharm运行启动脚本

在文件夹examples/veighna_trader中找到run.py文件（不是VeighNa Studio下的，需要在GitHub上下载源码），将其放置于trader文件夹下，则可在项目中看见run.py文件，如下图所示：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/pycharm/16.png)

若脚本中部分代码下方可以看见绿色波浪线显示，可以点击项目名称左方的主菜单按钮 -【File】-【Settings】-【Editor】-【Inspections】-【Proofreading】，取消“Typo”的勾选，点击“OK”确认。此时回到项目界面，可以发现绿色波浪线已经消失了，如下图所示：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/pycharm/17.png)

点击鼠标右键，选择【Run 'run'】，即可开始运行run.py脚本，如下图所示：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/pycharm/21.png)

此时已经可以看到项目界面下方的Run窗口开始输出运行信息了，如下图所示：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/pycharm/19.png)

<span id="jump">

与此同时，VeighNa Trader也成功启动了，如下图所示：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/pycharm/20.png) 

</span>

此时项目界面右上角已经有run脚本的运行记录了，之后直接点击三角形运行按钮也可运行脚本，如下图所示：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/pycharm/18.png)

如果脚本内有main函数的话，如下图所示：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/pycharm/22.png)

也可点击函数入口前的三角形运行按钮运行脚本，如下图所示：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/pycharm/23.png)

### PyCharm调试脚本

在项目界面点击鼠标右键，选择【New】-【File】, 会弹出New File的窗口，创建backtest.py，如下图所示：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/pycharm/25.png)

在创建成功的backtest.py中写一段策略回测的代码（可参考vnpy项目源码文件夹examples/cta_backtesting中的backtesting_demo内容）。

在想要调试的地方打上断点，如下图所示：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/pycharm/26.png)

点击鼠标右键选择【Debug 'backtest'】, 即可开始调试脚本，如下图所示：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/pycharm/27.png)

此时项目界面右上角已经有backtest脚本的运行记录了，之后直接切换到backtest脚本也可调试脚本，如下图所示：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/pycharm/28.png)

开始调试之后，已经可以看到项目界面下方的Debug窗口开始输出信息并停在第一个断点处。此时底部左边显示的是线程信息，右边显示的是变量信息，如下图所示：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/pycharm/29.png)

点击类似播放键的【Resume Program】即可继续调试，调至下一个断点，如下图所示：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/pycharm/30.png)

此时可以看到变量有改变以及增加，如下图所示：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/pycharm/31.png)

再接着点击【Resume Program】直到调试结束，可以看到Debug窗口的相应输出，如下图所示：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/pycharm/32.png)

调试完之后，点击【Rerun 'backtest'】即可重新调试，如下图所示：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/pycharm/33.png)

在调试过程中，点击【Step Into】可以进入函数的内部，如下图所示：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/pycharm/34.png)

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/pycharm/35.png)

点击【Step Out】可跳出当前函数，如下图所示：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/pycharm/37.png)

点击【Step Over】可越过子函数（子函数会执行），如下图所示：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/pycharm/36.png)

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/pycharm/38.png)

点击【Stop 'backtest'】会直接停止运行当前程序，如下图所示：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/pycharm/39.png)

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/pycharm/40.png)

点击【Mute Breakpoints】会使得所有断点都失效，如下图所示：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/pycharm/41.png)

重新调试的过程中，会发现红色的断点变成白色，并且直接运行了整个脚本，如下图所示：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/pycharm/42.png)

#### 指定路径运行脚本

在PyCharm新建项目的时候，默认是在当前目录下运行。若需要指定脚本运行路径的话，可以点击项目界面右上角的【Edit】进入Run/Debug Configurations界面，如下图所示：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/pycharm/43.png)

修改对应脚本的工作目录，如下图所示：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/pycharm/44.png)

##### .vntrader文件夹相关拓展

VeighNa Trader的配置和运行是通过.vntrader文件夹来维护的。

点击鼠标右键，选择【New】-【Dirtectory】, 创建一个.vntrader文件夹。此时，再重新启动run.py脚本，可以发现VeighNa Trader的运行目录与[上图](#jump)不一致了，如下图所示：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/pycharm/45.png)

此时启动的VeighNa Trader是一个由新创建的.vntrader文件夹配置信息控制，独立于用户目录下配置信息启动运行的环境。这样的启动方式能够隔离同一接口不同账户的配置信息，在开源版本的基础上提供多账户的支持。

**使用默认SQLite回测常见问题**

之前经常有使用自带数据库**SQLite**的用户反馈，在图形界面启动可以顺利回测，通过脚本回测加载出来的历史数据量为0，没有成交记录。

问题的原因可能是由于运行回测脚本的目录与图形界面启动VeighNa Trader的目录不同，导致读取了不同.vntrader文件夹中的database.db文件（vnpy_sqlite储存数据的文件），自然就没有办法跑出同样的回测结果了。

以backtest.py为例，该脚本默认的运行目录为当前目录，并且run.py同级目录下已经创建了.vntrader文件夹（如果不在run.py同级目录下创建了.vntrader文件夹，则会默认去用户目录下的.vntrader文件夹下读取），如下图所示：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/pycharm/46.png)

此时开始调试脚本，会发现回测引擎的history_data的长度为0，如下图所示：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/pycharm/47.png)

这是因为此时回测脚本是去新建的.vntrader文件夹下的database.db里读取数据（新建目录，还没通过datamanager模块保存数据），没有读到历史数据。

参考前面指定路径运行脚本部分的内容修改backtest脚本的工作目录为用户目录，如下图所示：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/pycharm/44.png)

再重新开始调试脚本，会发现回测引擎的history_data的长度不为0了，如下图所示：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/pycharm/48.png)

因为此时回测脚本是去用户目录下.vntrader文件夹下的database.db里读取的数据（之前保存过）。


## PyCharm V.S VS Code

1. PyCharm 每个项目都需要对python环境进行配置，VS Code是通过图形界面右下角的Python解释器来选择python环境的（针对所有打开的文件）；

2. PyCharm Community 只提供了Jupyter只读支持，VS Code Community可以编辑和运行Jupyter脚本。
