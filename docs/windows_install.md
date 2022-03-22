# Windows安装指南

本文档中安装步骤适用的Windows系统包括：

- Windows 10/11
- Windows Server 2019

> 其他版本的Windows系统安装时可能遇到各种依赖库问题，不推荐使用。

在Windows系统上安装VeighNa，推荐使用官方推出的【VeighNa Studio Python发行版】，**尤其是初次接触Python的编程新手**。

作为一站式的量化投研交易Python环境，VeighNa Studio整合了：

- Python 3.10 64位（Python官网版本）
- VeighNa和其他相关依赖库
- VeighNa Station（VeighNa框架的图形化管理工具）

对于已经有比较丰富的编程经验或者需要用到特定Python发行版（如Anaconda）的用户，也可以采用手动安装的方案。


## VeighNa Studio方案

### 下载安装

在[VeighNa官网](https://www.vnpy.com/)可以下载最新版本的VeighNa Studio。

下载完成后，双击安装包进入VeighNa Studio安装向导（推荐点击右键，选择【使用管理员身份运行】进行安装），使用默认设置点击【快速安装】按钮即可进行VeighNa Studio安装，如下图所示：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/install/21.png)

> 推荐将VeighNa Studio安装在默认路径的C:\veighna_studio，其他VeighNa文档和教程中均使用该目录作为VeighNa安装目录进行讲解。

如果想进行个性化安装，可点击【自定义安装】进入高级选项页面，如下图所示：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/install/24.png)

安装完成后，会转换到安装成功页面，如下图所示：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/install/26.png)

此时桌面会出现VeighNa Station的图标，双击图标即可运行VeighNa Station。

### 使用

安装成功后，打开cmd即可直接使用VeighNa Studio Python发行版。

输入python即可进入python的交互式环境，如下图所示：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/install/29.png)

此时在命令行中输入python代码就会立即执行。如果想运行pyqtgraph的自带的例子，可以依次输入以下代码：

```python 3
from pyqtgraph import examples
examples.run()
```

此时则会弹出Examples的运行窗口，如下图所示：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/install/30.png)

点击左侧的Basic Plotting则会弹出示例的图形界面，如下图所示：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/install/31.png)

如果想打开jupyter lab进行投资研究工作，可以打开cmd，输入jupyter lab，即可成功启动，如下图所示：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/install/32.png)

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/install/38.png)

### 修改

如果安装之后，想要添加或者移除某项功能，可以双击VeighNa Studio的安装包，进入VeighNa Studio安装界面，如下图所示：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/install/33.png)

点击【修改】，进入修改页面，如下图所示：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/install/35.png)

选择完可选功能后，点击【下一步】，进入高级选项页面，如下图所示：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/install/37.png)

选择完毕，即可重新安装。

### 修复

如果安装之后，出现安装不完整或者其他需要修复的情况，可以双击VeighNa Studio的安装包，进入VeighNa Studio安装界面，如下图所示：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/install/33.png)

点击【修复】，进入修复界面，如下图所示：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/install/34.png)

修复完成后，会转换到修复成功页面，如下图所示：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/install/15.png)

### 卸载

如果想卸载VeighNa Studio， 可以双击VeighNa Studio的安装包，进入VeighNa Studio安装界面，如下图所示：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/install/33.png)

点击【卸载】，进入卸载界面，如下图所示：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/install/27.png)

卸载完成后，会转换到卸载成功页面，如下图所示：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/install/28.png)


## 手动安装方案

### 准备Python环境

首先请在电脑上准备好Python 3.10 64位环境（**注意必须是64位版本**），推荐使用Python官网的发行版，也可以使用Anaconda、Miniconda、Canopy等发行版。

这里我们以Python官网的发行版为例，首先在[Python官网](https://www.python.org/downloads/windows/)下载安装文件，选择【Windows installer (64-bit)】，如下图所示：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/install/22.png)

下载完毕后，双击文件进入Python安装向导，勾选【Add Python3.10 to PATH】选项后，点击【Install Now】进行安装，推荐使用默认设置一路点击【下一步】直到安装完成即可：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/install/23.png)


### 下载安装VeighNa  

下载最新版本的VeighNa源代码（Windows系统请选择zip格式）：

- [VeighNa Github下载地址](https://github.com/vnpy/vnpy/releases)
- [VeighNa gitee下载地址](https://gitee.com/mirrors/vn-py/releases)

下载完成后解压，然后启动命令行工具（CMD或者PowerShell），进入源代码所在的目录后（即install.bat文件所在的目录），输入下列命令运行脚本执行一键安装：

```
install.bat
```

一键安装过程整体分为3步：

1. 下载安装ta-lib库；
2. 安装requirements.txt文件内的相关依赖库；
3. 安装VeighNa本身。

如果某一步安装过程中发生错误，请截取保存命令行中的报错信息（**注意优先保存最底部的报错内容**），前往VeighNa社区论坛发帖提问寻求帮助。

### 启动VeighNa Trader

启动命令行工具，进入解压VeighNa源代码的目录下，在文件夹examples/veighna_trader中找到run.py文件。

输入如下命令即可启动VeighNa Trader：

```
python run.py 
```

请注意run.py中包含了较多的启动加载项（交易接口和应用模块），请根据自己所用的操作系统以及实际的交易需求修改调整使用（若需加载接口，取消接口前注释符号即可）。

连接接口介绍详见交易接口篇。

> 如果启动时出现一些库版本不兼容的情况，可根据提示对这些库重新pip安装。
