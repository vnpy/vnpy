# Ubuntu安装指南

## 检查Python

检查本地Python版本，需要需要3.7版本以上的版本，可在命令行运行python命令查看。

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/install/40.png)


## 安装VeighNa

### 下载源代码

下载VeighNa源代码（Ubuntu系统请选择tar.gz格式）：

- [VeighNa Github下载地址](https://github.com/vnpy/vnpy/releases)
- [VeighNa Gitee下载地址](https://gitee.com/mirrors/vn-py/releases)

下载完成后用tar命令解压文件，如下图所示。

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/install/41.png)

### 执行一键安装

安装VeighNa前需要先安装gcc编译器，用于编译C++类接口文件。在终端中运行以下命令：

```
sudo apt-get update
sudo apt-get install build-essential
```

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/install/39.png)

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/install/43.png)

然后进入之前解压出来的VeighNa源代码目录（包含install.sh文件）

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/install/42.png)

打开终端运行如下命令执行一键安装：

```
sudo bash install.sh
```

请注意，如果python软连接名不为python，比如python3或python3.10，请执行如下命令：

```
sudo bash install.sh 你的python软连接
```

一键安装过程整体分为3步：

1. 下载安装ta-lib库和numpy；
2. 安装VeighNa本身。

> 若是在虚拟机上运行，请把内存调至4G以上，否则会报错内存不足。


## 启动VeighNa Trader

进入解压VeighNa源代码的目录下，在文件夹examples/veighna_trader中找到run.py文件。

点击鼠标右键打开终端，输入如下命令即可启动VeighNa Trader：

```
python run.py 
```

请注意run.py中包含了较多的启动加载项（交易接口和应用模块），请根据自己所用的操作系统以及实际的交易需求修改调整使用（若需加载接口，取消接口前注释符号即可）。

请注意部分接口不支持Ubuntu系统，请不要加载。连接接口介绍详见交易接口篇（可查看接口支持的操作系统）。

> 如果启动时出现一些库版本不兼容的情况，可根据提示对这些库重新pip安装。


## 常见问题

### Python开发环境问题处理

如果安装时出现由于找不到头文件导致的报错“command ‘gcc’ failed with exit status 1”，可能是没有正确安装Python开发环境造成的。可以在终端中运行下述命令尝试解决：

```
sudo apt-get install 你的python软连接-dev
```

### 图形驱动问题处理

在有图形界面的Ubuntu系统上启动，如果出现qt.qpa.plugin: Could not load the Qt platform plugin "xcb" in "" even though it was found的报错，可以在终端中运行下述命令来安装libxcb-xinerama0，尝试解决图形驱动的依赖问题：

```
sudo apt-get install libxcb-xinerama0
```

### 中文编码问题处理

如果Ubuntu系统语言是英文，在连接CTP接口这类使用中文语言的接口时，可能会出现下述报错：

terminate called after throwing an instance of 'std::runtime_error'
what(): locale::facet::_S_create_c_locale name not valid

可以使用local-gen安装中文编码尝试解决：

```
sudo locale-gen zh_CN.GB18030
```

如果还没有解决，可能是因为系统缺少中文字体支持。解决方法如下：

```
sudo apt-get update
sudo apt-get install -y fonts-noto-cjk fonts-wqy-zenhei fonts-wqy-microhei
fc-cache -f -v
fc-list :lang=zh | wc -l
sudo locale-gen zh_CN.UTF-8 zh_CN.GB18030
```

### 安装依赖与路径分隔符

在Linux系统中安装C++接口时，如果使用`--no-build-isolation`参数，需要提前安装以下依赖库：

```bash
uv pip install meson-python meson pybind11
sudo apt-get update && sudo apt-get install -y ninja-build
```

此外，建议在Linux系统中使用正斜杠`/`作为路径分隔符，以避免路径解析问题。因此，推荐的安装命令如下：

```bash
uv pip install -e . --no-build-isolation --config-settings=build-dir=./{包的名字}/api
```

此命令将确保API文件夹被正确指定为构建目录，避免路径格式问题导致的安装失败。
