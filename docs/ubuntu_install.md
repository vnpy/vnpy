# Ubuntu安装指南

## 检查Python

检查本地Python版本，要求3.7及以上版本，可在命令行运行python命令查看。

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/install/40.png)


## 安装VeighNa

### 下载源代码

下载VeighNa源代码（Ubuntu系统请选择tar.gz格式）：

- [VeighNa Github下载地址](https://github.com/vnpy/vnpy/releases)
- [VeighNa Gitee下载地址](https://gitee.com/mirrors/vn-py/releases)

下载完成后用tar命令解压文件，如下图所示。

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/install/41.png)

### 执行一键安装

安装VeighNa前，需先安装gcc编译器，以便编译C++类接口文件。在终端执行以下命令：

```
sudo apt-get update
sudo apt-get install build-essential
```

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/install/39.png)

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/install/43.png)

然后进入之前解压出来的VeighNa源代码目录（包含install.sh文件）

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/install/42.png)

打开终端执行以下命令进行一键安装：

```
sudo bash install.sh
```

请注意，如果python软连接名不为python，比如python3或python3.10，请执行如下命令：

```
sudo bash install.sh 你的python软连接
```

一键安装过程整体分为3步：

1. 下载安装ta-lib库和numpy；
2. 安装requirements.txt文件内的相关依赖库；
3. 安装VeighNa本身。

> 若在虚拟机上运行VeighNa，请确保分配的内存量至少为4GB，否则会报错内存不足。


## 启动VeighNa Trader

进入解压VeighNa源代码的目录下，在文件夹examples/veighna_trader中找到run.py文件。

点击鼠标右键打开终端，执行以下命令即可启动VeighNa Trader：

```
python run.py 
```

请注意run.py文件中包含多个启动加载项（交易接口和应用模块），请根据自己所用的操作系统以及实际的交易需求进行相应修改（若需加载接口，取消接口前注释符号即可）。

注意部分接口不支持Ubuntu系统，请不要加载。接口连接介绍详见交易接口相关章节（可查看接口支持的操作系统）。

> 若启动时出现库版本不兼容问题，可根据提示重新pip安装对应库。


## 常见问题

### Python开发环境问题处理

若安装过程中出现由于找不到头文件导致的报错“command ‘gcc’ failed with exit status 1”，可能是没有正确安装Python开发环境造成的。可在终端中运行以下命令尝试解决：

```
sudo apt-get install 你的python软连接-dev
```

### 图形驱动问题处理

在图形界面的Ubuntu系统中启动时，若出现qt.qpa.plugin: Could not load the Qt platform plugin "xcb" in "" even though it was found "错误，可在终端中运行以下命令安装libxcb-xinerama0，尝试解决图形驱动的依赖问题：

```
sudo apt-get install libxcb-xinerama0
```

### 中文编码问题处理

如果Ubuntu系统语言是英文，连接如CTP接口等使用中文语言的接口可能会触发以下错误：

terminate called after throwing an instance of 'std::runtime_error'
what(): locale::facet::_S_create_c_locale name not valid

可以使用local-gen安装中文编码尝试解决：

```
sudo locale-gen zh_CN.GB18030
```
