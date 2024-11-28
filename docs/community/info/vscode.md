# VSCode开发指南

VSCode（Visual Studio Code）是微软开发的跨平台免费源代码编辑器。用户可以通过内置的扩展程序商店安装扩展，以拓展其功能。本文档旨在为用户提供在VSCode中开发VeighNa的参考方案。

本文内容基于Windows系统编写，但大部分也适用于Linux和Mac系统。

VeighNa支持的Windows系统包括：

- Windows 11
- Windows Server 2019/2022

> 其他版本的Windows系统安装时可能遇到各种依赖库问题，不推荐使用。

在Windows系统上使用VeighNa，推荐安装官方推出的【VeighNa Studio】Python发行版，**特别适合初次接触Python开发的新手用户**。


## VSCode安装

首先从[VSCode官网](https://code.visualstudio.com/)下载VS Code for Windows安装包：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/vscode/1.png)

下载完成后，双击安装包则可进入VSCode(User)安装向导：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/vscode/2.png)

选择【我同意此协议】，点击【下一步】进入选择目标位置页面，进行安装目录选择：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/vscode/3.png)

点击【下一步】进入选择开始菜单文件夹页面进行快捷方式选择：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/vscode/4.png)

点击【下一步】进入选择附加任务页面，进行附加任务选择：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/vscode/5.png)

这里建议选中所有的勾选框，每个勾选框的具体功能如下：

 - 勾选【将“通过Code打开”操作添加到Windows资源管理器文件上下文菜单】后，用户可以直接通过右键菜单在VSCode中打开单个文件；
 - 勾选【将“通过Code打开”操作添加到Windows资源管理器目录上下文菜单】后，用户可以直接通过右键菜单在VSCode中打开整个文件夹及其内容；
 - 勾选【将Code注册为受支持的文件类型的编辑器】之后，VSCode将被设置为系统打开默认打开支持的文件类型（如.py、.txt等）的编辑器；
 - 勾选【添加到PATH（重启后生效）】后，系统将会在安装完成后把VSCode的安装目录添加到PATH环境变量中。

点击【下一步】进入准备安装页面，会显示之前选择的安装设置内容：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/vscode/6.png)

点击【安装】会开始安装，安装完成后，会跳转到安装成功页面：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/vscode/7.png)

如果勾选了运行 Visual Studio Code选项的话，此时会自动打开VSCode。


## VeighNa开发

### 打开单一文件

启动VSCode之后，在弹出的欢迎界面中点击【Open File】即可打开单一文件，如下图所示：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/vscode/8.png)

在弹出的Open File窗口中，选择存放文件的路径，点击【打开】按钮即可在VSCode中打开文件，如下图所示：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/vscode/9.png)

> 请注意：如果以受限模式打开文件后，想临时关闭该文件的受限模式，可以找到窗口顶部的受限模式提示，点击【Manage】，在弹出的Workspace Trust页面点击【Trust】即可关闭该文件的受限模式。

### 打开文件夹

启动VSCode之后，在弹出的欢迎界面中点击【Open Folder】即可打开文件夹，如下图所示：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/vscode/10.png)

在弹出的Open Folder窗口中，选择存放文件夹的路径，点击【打开】按钮即可在VSCode中打开文件夹，如下图所示：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/vscode/11.png)

### 保存VSCode开发项目

为了方便集中管理代码资源，避免环境切换混乱，VSCode提供了工作区支持。点击【File】-【Save Workspace As...】即可保存工作区到指定路径，便于后续访问使用。

为了解决项目切换困难的问题，工作区还允许将不同的项目放置到同一个工作区中。点击【File】-【Add Folder to Workspace...】即可添加文件夹到工作区。

### Python环境选择

在安装了Python插件之后，打开任意.py文件，可以在VSCode窗口的右下角看到当前使用的Python环境信息，如下图所示：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/vscode/14.png)

请注意，默认显示的是自动搜索到的Python环境。如果当前系统中存在多个Python环境的话，可以点击右下角的Python环境信息，在窗口顶部弹出的下拉框中选择其他环境进行切换，如下图所示：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/vscode/15.png)

### 运行程序

从Github代码仓库下载VeighNa Trader[启动脚本文件run.py](https://github.com/vnpy/vnpy/blob/master/examples/veighna_trader/run.py)，通过VSCode打开run.py文件，如下图所示：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/vscode/23.png)

点击VSCode右上角的运行按钮，选择【Run Python File】，即可运行run.py脚本：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/vscode/24.png)

此时在界面底部的TERMINAL终端内容输出标签页中，可以看到程序运行时的打印信息：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/vscode/25.png)

与此同时，VeighNa Trader的主窗口也会自动弹出显示：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/vscode/26.png)

请注意：
 - 这里启动脚本时，会在当前VSCode使用的Python环境中运行，如须使用其他Python环境请参考前文的步骤进行切换；
 - 如果想直接在终端中运行脚本，可以按住Ctrl + J打开Terminal，在其中输入用命令启动VeighNa Trader；
 - 上图中打印的“没有配置要使用的数据服务，请修改全局配置中的datafeed相关内容”输出不影响VeighNa Trader的运行；如果需要配置数据服务，可以在VeighNa Trader主界面【配置】-【全局配置】中配置即可，如果不需要配置数据服务则忽略此条输出即可。

### 断点调试

VSCode提供了强大的断点调试功能，这里使用一个VeighNa的策略历史回测脚本来演示。

点击【New File】，在界面上方弹出的窗口中选择【Python File】, 在弹出的标签页中创建backtest.py：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/vscode/27.png)

然后在文件中编写一段策略回测代码（具体可参考Github仓库中的[回测示例](https://github.com/vnpy/vnpy/blob/master/examples/cta_backtesting/backtesting_demo.ipynb)），在想要调试暂停的代码行处打上断点，如下图所示（左侧红色小圆点）：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/vscode/28.png)

点击VSCode右上角的向下按钮，选择【Python Debugger: Debug Python File】, 即可开始调试脚本：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/vscode/29.png)

点击左侧菜单栏的Run and Debug图标![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/vscode/30.png)或者直接按F5键也可开始调试。

启动调试后，可以看到窗口左侧的RUN AND DEBUG区域开始输出程序运行信息，并且程序会暂停运行在第一个断点处。左侧分别显示的是变量信息、监视信息、调用堆栈信息和断点信息。点击变量可以看到详细信息，如下图所示：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/vscode/31.png)

点击类似播放键的【Continue】或者按F5键即可继续运行调试，直到下一个断点处再次暂停，如下图所示：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/vscode/32.png)

此时可以看到底部左侧VARIABLES区域中，当前上下文中的变量发生了变化：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/vscode/33.png)

后续重复上述步骤，点击【Continue】直到调试结束，可以看到Terminal的相应输出：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/vscode/34.png)

在调试过程中：

- 点击【Step Into】可以进入子函数的内部查看运行时的细节状态；
- 点击【Step Out】则可跳出当前函数，查看外层调用栈的状态；
- 点击【Step Over】可越过子函数（子函数会执行）；
- 点击【Restart】会重新启动调试任务；
- 点击【Stop】则会直接停止当前调试任务的运行。

在VARIABLES区域中选中要监控的变量名称点击鼠标右键，选择【Add to Watch】，即可在WATCH监控区域中观测到变量的变化，如下图所示：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/vscode/35.png)

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/vscode/36.png)

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/vscode/37.png)

窗口底部的DEBUG CONSOLE则提供了交互式的调试功能支持，可以在调试过程中运行任意命令，如下图所示：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/vscode/38.png)

#### C++回调断点调试

通常情况下，VSCode只能在Python解释器中启动的线程里进行代码断点调试。用户如果想要在C++回调函数（如CTP API接口、PySide图形库等）中打断点，可以通过在代码中设置断点的方式，来实现对非Python线程（即C++线程）的断点调试。

点击【New File】，在界面上方弹出的窗口中选择【Python File】, 创建geteway_test.py。

在创建成功的geteway_test.py中添加一段脚本策略的代码（可参考[该文件](https://github.com/vnpy/vnpy/blob/master/examples/veighna_trader/demo_script.py)），然后按住Ctrl同时用鼠标左键点击代码中的CtpGateway，跳转至ctp_gateway.py的源码中，在想要调试的回调函数内打上断点（注意不要打在函数定义的def那一行）。回到gateway_test.py开始调试，会发现并没有进入之前设定的断点，如下图所示：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/vscode/39.png)

> 请注意，使用load_json函数读取connect_ctp.json，请确保读取对应.vntrader文件夹的json文件中配置了CTP账户登录信息。

终止调试后，找到之前在ctp_gateway.py中设定的断点处，在回调函数内的断点之前添加以下代码：

```Python 3
import pydevd
pydevd.settrace(suspend=False, trace_only_current_thread=True)
```

请注意：
 - pydevd是VSCode自带的调试插件，没有安装在Python解释器所在的Python环境里；
 - suspend参数设置为True之后，调试会在这一句代码运行完之后暂停，而不是停在断点处；
 - trace_only_current_thread参数设置为True之后，调试过程中只会监控当前线程；
 - **调试结束之后不要忘记删掉这段代码。**

然后再次运行调试gateway_test.py脚本，此时可以看到底部的调试窗口中开始输出相关信息，同时程序暂停在了之前设置的断点处。调用堆栈信息窗口显示的是线程信息（可以看到多了一个Dummy线程显示），变量窗口显示的是变量信息（可以看到回调函数的入参）：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/vscode/40.png)

**请注意**，如果在调试过程没有跳转，可以点击【Run and Debug】页面上方的设置按钮，打开launch.json，将justMyCode参数配置为false，即可在调试过程中进行跳转，如下图所示：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/vscode/41.png)


## 插件安装

VSCode提供了极为丰富的扩展插件功能，可以显著提升用户的开发效率和便捷性。

### 必选插件

#### Python

点击VSCode左边菜单栏的Extensions图标，搜索【Python】，点击【install】安装Python插件，如下图所示：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/vscode/13.png)

安装Python插件时，会自动安装Pylance（提供类型检查、代码补全、引用跳转和代码诊断支持）和Python Debugger（提供断点调试功能）插件。

安装完Python插件以后，即可在VSCode的Extension栏看到Python、Pylance和Python Debugger三个插件，如下图所示：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/vscode/16.png)

安装完Pylance插件后，可以在打开的脚本中，把鼠标光标移到代码的上方，会自动弹出对应的文档信息，如下图所示：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/vscode/17.png)

若按住Ctrl键的同时用鼠标左键点击代码，则会跳转到代码的声明部分，如下图所示：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/vscode/18.png)

#### Jupyter

点击VSCode左边菜单栏的Extensions图标，搜索【Jupyter】，点击【install】安装Jupyter插件，如下图所示：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/vscode/19.png)

Jupyter插件将Jupyter Notebook的功能集成到了VSCode中，此时用户就可以在VSCode中打开、编辑和运行Notebook了。

安装Jupyter插件时，会自动安装

- Jupyter Cell Tags（提供单元格中添加标签支持）；
- Jupyter Keymap（提供快捷键支持）；
- Jupyter Notebook Renderers（提供对不同内容类型的渲染和解析支持）；
- Jupyter Slide Show（提供幻灯片支持）插件。

安装完Jupyter插件以后，即可在VSCode的Extension栏目中看到Jupyter、Jupyter Cell Tags、Jupyter Keymap、Jupyter Notebook Renderers和Jupyter Slide Show五个插件，如下图所示：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/vscode/20.png)

#### Flake8

点击VSCode左边菜单栏的Extensions图标，搜索【Flake8】，点击【install】安装Flake8插件，如下图所示：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/vscode/21.png)

Flake8插件可以检查Python代码是否符合PEP 8代码风格规范，包括代码中的错误、复杂度过高的构造以及不符合PEP8风格指南的地方。

当Flake8插件检测到代码中的不规范或错误时，会在代码下方显示红色波浪线进行警告，帮助用户快速定位问题，如下图所示：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/vscode/22.png)

同时Flake8插件也会在窗口底部的【PROBLEMS】标签页中，显示整个工作分区内检测到的所有错误，如上图所示。

### 可选插件

#### Chinese Language

功能：将VSCode的界面和菜单翻译成中文，适合对英文不太熟悉的用户。

#### Excel Viewer

功能：允许用户在VSCode中直接查看和编辑CSV文件，支持基本的单元格编辑、筛选和排序功能。

#### One Monokai Theme

功能：提供代码高亮主题，通过改变代码的颜色、字体和背景，使代码更易于阅读和理解。

#### Material Icon Theme

功能：将VSCode中的文件和目录图标替换为Material Design风格的图标，使文件和目录在侧边栏中更易于区分和识别。

#### Github Copilot

功能：由GitHub和OpenAI共同开发的人工智能代码辅助工具，提高代码的可移植性和一致性。

#### C/C++和C/C++ Extension Pack

功能：提供C/C++语言支持、代码调试、代码格式化、代码补全、头文件包含等功能支持。
