# Ubuntu安装指南

## 检查Python

检查本地Python版本，需要需要3.7版本以上的版本，在命令行运行python命令查看：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/install/9.png)

## 安装VeighNa

### 下载源代码

下载最新版本的VeighNa源代码（Ubuntu系统请选择tar.gz格式）：

- [VeighNa Github下载地址](https://github.com/vnpy/vnpy/releases)
- [VeighNa gitee下载地址](https://gitee.com/mirrors/vn-py/releases)

下载完成后用tar命令解压文件，如下图所示。

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/install/10.png)

### 执行一键安装

安装VeighNa前需要先安装gcc编译器，用于编译C++类接口文件。在终端中运行以下命令：

```
sudo apt-get update
sudo apt-get install build-essential
```

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/install/19.png)

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/install/11.png)

然后进入之前解压出来的VeighNa源代码目录（包含install.sh这个文件）

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/install/20.png)

打开终端运行如下命令执行一键安装：

```
. install.sh
```

一键安装过程整体分为4步：

1. 下载安装ta-lib库和numpy；
2. 安装requirements.txt文件内的相关依赖库；
3. 使用local-gen安装中文编码（针对英文系统）；
4. 安装VeighNa本身。

> 若是在虚拟机上运行，请把内存调至4G以上，否则会报错内存不足。


## 启动VeighNa Trader

进入解压VeighNa源代码的目录下，在文件夹examples/vn_trader中找到run.py文件。

点击鼠标右键打开终端，输入如下命令即可启动VeighNa Trader：

```
python run.py 
```

请注意run.py中包含了较多的启动加载项（交易接口和策略应用），请根据自己所用的操作系统以及实际的交易需求修改调整使用（若需加载接口，取消接口前注释符号即可）。

请注意部分接口不支持Ubuntu系统，请不要加载。连接接口介绍详见交易接口篇（可查看接口支持的操作系统）。

> 如果启动时出现一些库版本不兼容的情况，可根据提示对这些库重新pip安装。


## 常见问题

### ta-lib问题处理

如果安装ta-lib的过程中出现如下报错：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/install/12.png)

则需要手动安装编译ta-lib库。在想要存放ta-lib库的文件夹内逐步运行下列命令行：

- 获取源码库
```
sudo wget http://prdownloads.sourceforge.net/ta-lib/ta-lib-0.4.0-src.tar.gz
```

- 解压进入目录
```
tar -zxvf ta-lib-0.4.0-src.tar.gz
cd ta-lib/
```

- 编译安装
```
sudo ./configure --prefix=/usr  
sudo make
sudo make install
```

- 下载ta-lib的Python封装
```
git clone https://github.com/mrjbq7/ta-lib.git
cd ta-lib
python setup.py install
```

请注意，如果出现报错“command ‘gcc’ failed with exit status 1”，可能是由于没有正确安装Python开发环境导致，请在终端中运行下述命令：

```
sudo apt-get install python3-dev
```

编译安装ta-lib完毕后，重新执行下述命令安装vnpy即可。
```
. install.sh
```

## 图形驱动问题处理

如果启动时出现下述报错：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/install/13.png)

则需要在终端中运行下述命令来安装libxcb-xinerama0，解决图形驱动的依赖问题：

```
sudo apt-get install libxcb-xinerama0
```

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/install/14.png)
