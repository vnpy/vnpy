# Ubuntu安装指南

## 安装Miniconda

下载Python 3.7版本的Miniconda（或者Anaconda），注意必须是**Python3.7 64位版本**，本文档以Miniconda为例；

- [Miniconda官方下载地址](https://docs.conda.io/en/latest/miniconda.html)
- [Miniconda清华镜像下载地址](https://mirrors.tuna.tsinghua.edu.cn/anaconda/miniconda/)

启动Terminal终端，进入已下载好的Miniconda3-py37_4.9.2-Linux-x86_64.sh文件所在目录，运行如下命令开始安装：

```
$ bash Miniconda3-py37_4.9.2-Linux-x86_64.sh
```

安装时可以设置安装路径和默认环境，在询问是否要将Miniconda设置为Python默认环境时选择yes，如下图所示：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/install/8.png)

安装完成后，启动终端运行命令python，若能进入Python解释器（如下图所示），则说明已成功把Miniconda设置为系统默认的Python环境：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/install/9.png)


## 安装vn.py

### 下载源代码

下载最新版本的vn.py源代码（Ubuntu系统请选择tar.gz格式）：

- [vn.py Github下载地址](https://github.com/vnpy/vnpy/releases)
- [vn.py gitee下载地址](https://gitee.com/mirrors/vn-py/releases)

下载完成后用tar命令解压文件，如下图所示。

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/install/10.png)

### 执行一键安装

安装vn.py前需要先安装gcc编译器，用于编译C++类接口文件。在终端中运行以下命令：

```
sudo apt-get update
sudo apt-get install build-essential
```

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/install/11.png)

然后进入之前解压出来的vn.py源代码目录（包含install.sh这个文件），打开终端运行如下命令执行一键安装：

```
bash install.sh
```

一键安装过程整体分为4步：

1. 下载安装ta-lib库和numpy；
2. 安装requirements.txt文件内的相关依赖库；
3. 使用local-gen安装中文编码（针对英文系统；）
4. 安装vn.py本身。

> 若是在虚拟机上运行，请把内存调至4G以上，否则会报错内存不足。


## 启动VN Trader

进入解压vn.py源代码的目录下，在文件夹examples\vn_trader中找到run.py文件。

点击鼠标右键打开终端，输入如下命令即可启动VN Trader：

```
python run.py 
```

请注意run.py中包含了较多的启动加载项（交易接口和策略应用），请根据自己所用的操作系统以及实际的交易需求修改调整使用。

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
bash install.sh
```

## 图形驱动问题处理

如果启动时出现下述报错：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/install/13.png)

则需要在终端中运行下述命令来安装libxcb-xinerama0，解决图形驱动的依赖问题：

```
sudo apt-get install libxcb-xinerama0
```

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/install/14.png)
