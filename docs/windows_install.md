# Windows安装指南

本文档中安装步骤适用的Windows系统包括：

- Windows 10
- Windows Server 2019

> 其他版本的Windows系统安装时可能遇到各种依赖库问题，不推荐使用。

在Windows系统上安装vn.py，推荐使用官方推出的【Veighna Studio Python发行版】，**尤其是初次接触Python的编程新手**。

作为一站式的量化投研交易Python环境，Veighna Studio整合了：

- Python 3.7 64位（Python官网版本）
- vn.py和其他相关依赖库
- Veighna Station（vn.py框架的图形化管理工具）

对于已经有比较丰富的编程经验或者需要用到特定Python发行版（如Anaconda）的用户，也可以采用手动安装的方案。


## Veighna Studio方案

### 下载安装

在[vn.py官网](https://www.vnpy.com/)可以下载最新版本的Veighna Studio，如下图所示。

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/install/15.png)

下载完成后，双击安装包进入Veighna Studio安装向导，使用默认设置一路点击【下一步】按钮即可完成Veighna Studio安装，如下图所示：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/install/2.png)

> 推荐将Veighna Studio安装在默认路径的C:\vnstudio，其他vn.py文档和教程中均使用该目录作为vn.py安装目录进行讲解。


### 上手Veighna Station

双击桌面图标运行Veighna Station，输入账号密码或直接微信扫码即可登录，登录对话框如下图所示。

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/install/3.png)

如果是首次使用，使用微信扫码时会自动进入注册页面，注册时：

- 个人邮箱请如实填写（后续用于找回密码等论坛功能）；
- 用户名自动使用注册时的微信【昵称】（不支持修改）；
- 密码请牢记，该密码也同样用于登录[vn.py社区论坛](https://www.vnpy.com/forum)

登录成功后，即可进入到Veighna Station的主界面，如下图所示。

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/install/16.png)

主界面窗口底部有6个按钮：

- 【Veighna Trader Lite】直接运行Veighna Trader（只加载了CTP接口，提供CTA策略和回测功能）；
- 【Veighna Trader】可以更改保存相关临时文件的目录，再运行Veighna Trader（可以个性化选择底层接口和上层应用模块）；
- 【Jupyter Notebook】在指定的目录启动Jupyter Notebook，进行交互式的量化策略研究工作；
- 【策略加密】使用Cython工具对原本为可读代码的Python策略文件进行加密，生成不可读的二进制pyd文件；
- 【提问求助】在浏览器中打开vn.py社区论坛，遇到问题可以通过相关版块提问求助；
- 【已是最新/更新】有新版本的vn.py发布时，该按钮会亮起，点击即可实现vn.py一键自动更新。


## 手动安装方案

### 准备Python环境

首先请在电脑上准备好Python 3.7 64位环境（**注意必须是Python 3.7 64位版本**），推荐使用Python官网的发行版，也可以使用Anaconda、Miniconda、Canopy等发行版。

这里我们以Python官网的发行版为例，首先在[Python官网](https://www.python.org/downloads/windows/)下载安装文件，选择可执行安装器【executable installer】，如下图所示：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/install/5.png)

下载完毕后，双击文件进入Python安装向导，勾选【Add Python3.7 to PATH】选项后，点击【Install Now】进行安装，推荐使用默认设置一路点击【下一步】直到安装完成即可：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/install/6.png)


### 下载安装vn.py  

下载最新版本的vn.py源代码（Windows系统请选择zip格式）：

- [vn.py Github下载地址](https://github.com/vnpy/vnpy/releases)
- [vn.py gitee下载地址](https://gitee.com/mirrors/vn-py/releases)

下载完成后解压，然后启动命令行工具（CMD或者PowerShell），进入源代码所在的目录后（即install.bat文件所在的目录），输入下列命令运行脚本执行一键安装：

```
install.bat
```

一键安装过程整体分为3步：

1. 下载安装ta-lib库；
2. 安装requirements.txt文件内的相关依赖库；
3. 安装vn.py本身。

如果某一步安装过程中发生错误，请截取保存命令行中的报错信息（**注意优先保存最底部的报错内容**），前往vn.py社区论坛发帖提问寻求帮助。

### 启动Veighna Trader

启动命令行工具，进入解压vn.py源代码的目录下，在文件夹examples/vn_trader中找到run.py文件。

输入如下命令即可启动Veighna Trader：

```
python run.py 
```

请注意run.py中包含了较多的启动加载项（交易接口和策略应用），请根据自己所用的操作系统以及实际的交易需求修改调整使用（若需加载接口，取消接口前注释符号即可）。

连接接口介绍详见交易接口篇。

> 如果启动时出现一些库版本不兼容的情况，可根据提示对这些库重新pip安装。
