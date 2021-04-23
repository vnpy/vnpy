# 安装指南


## Windows系统

### 使用VN Studio

#### 1.下载VN Studio

VN Studio是vn.py团队自行打包的一键安装版本，整合了：
- Python 3.7（社区官方版本）
- vn.py框架和其他相关库
- VN Station（vn.py框架的图形化管理工具）

在[vn.py官网](https://www.vnpy.com/)可以下载最新版本的VN Studio，如下图所示。

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/install/1.png)

截止到2021年4月，VN Studio的最新版是2.2.0版本，下载地址为：[VN Studio-2.2.0.exe](https://download.vnpy.com/vnstudio-2.2.0.exe)。

#### 2.安装VN Studio

下载后，双击下载包，进入VN Studio安装向导，使用默认设置一路点击【下一步】按钮即可完成VN Studio安装，如下图所示。

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/install/2.png)

安装完成后可以查看相关运行目录：

- VN Studio默认安装路径为C:\vnstudio；
- VN Studio默认json配置文件和数据库路径为C:\Users\Administrator\\.vntrader；
- VN Station运行目录为C:\vnstudio\Scripts\vnstation.exe；
- vnpy运行目录在C:\vnstudio\Lib\site-packages\vnpy（进入该目录后，用户可以修改vnpy的相关功能）。

#### 3.登陆VN Station

运行VN Station，输入账号密码或直接微信扫码登陆VN Station，如下图所示。

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/install/3.png)

如果没有账号，可在vn.py社区通过微信扫码进行注册。注册时个人邮箱需要如实填写。

#### 4.使用VN Station

登录成功后，进入到VN Station的主界面，如下图所示。

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/install/4.png)

主界面窗口下方有5个按钮：
- VN Trader Lite：直接运行VN Trader （只加载了CTP接口，提供CTA策略和回测功能）；
- VN Trader Pro：可以更改保存相关临时文件的目录，再运行VN Trader（可以个性化选择底层接口和上层应用模块）；
- Jupyter Notebook：可以更改保存相关临时文件的目录，再运行Jupyter Notebook；
- 提问求助：提出相关问题，管理员会每天定时回复；
- 后台更新：一键更新VN Station。

#### 5.更新VN Station

除了卸载重新安装外，用户可以通过下面两种方式更新VN Station：
- 在VN Station主窗口的右下角点击【一键更新】按钮；
- 在github上下载最新的dev分支，解压后得到根目录下的vnpy文件夹，对C:\vnstudio\Lib\site-packages\vnpy进行替换。

### 手动安装

#### 1.下载并安装python

在[python官网](https://www.python.org/downloads/windows/)下载python3.7 64位版本（注意只能是python3.7 64位版本），选择可执行安装，如下图所示。

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/install/5.png)

下载完毕后，双击下载包，进入python安装向导，勾选Add python3.7 to PATH 后点击Install Now 进行安装，使用默认设置一直点击【下一步】直到安装完成即可。

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/install/6.png)


#### 2.下载并解压vnpy  


在vnpy的[github主页](https://github.com/vnpy/vnpy)可以进行下载：

- 在主页左方的Branch选项中选择vnpy的版本，master对应的是最新的稳定版本，dev对应的是最新测试版本；
- 点击主页右方的code按钮，选择Download ZIP来下载压缩版本到本地电脑。

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/install/7.png)


#### 3.安装vnpy

双击install.bat一键安装vnpy：

- 先安装ta_lib库和ib api
- 然后安装requirements.txt文件内相关依赖库
- 最后复制vnpy到Anaconda内

#### 4.启动VN Trader

在github文件夹examples\vn_trader中找到run.py文件，根据需要选择要加载的接口和应用模块（取消掉前面的注释即可）。按住“Shift” + 鼠标右键进入cmd窗口，输入下面命令即可启动VN Trader。

```
python run.py 
```

## Ubuntu系统


### 1. 下载并安装Anaconda或Miniconda

下载基于python3.7的的Anaconda或Miniconda（注意必须是python3.7 64位版本），本文档以Miniconda为例；
  - [Anaconda官方下载地址](https://mirrors.tuna.tsinghua.edu.cn/anaconda/archive/)
  - [Anaconda清华镜像下载地址](https://mirrors.tuna.tsinghua.edu.cn/anaconda/archive/)
  - [Miniconda官方下载地址](https://docs.conda.io/en/latest/miniconda.html)
  - [Miniconda清华镜像下载地址](https://mirrors.tuna.tsinghua.edu.cn/anaconda/miniconda/)

进入已下载好的 Miniconda3-py37_4.9.2-Linux-x86_64.sh文件所在目录，终端运行如下命令，按“Enter”键开始安装。

```
$ bash Miniconda3-py37_4.9.2-Linux-x86_64.sh
```

根据安装向导可以设置安装路径和默认环境，在将Miniconda设置为Python默认环境时选择"yes"，如下图所示。

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/install/8.png)

安装成功后，打开终端直接输入"python" 然后按“Enter”键，若出现如下图，则表示成功把Miniconda设置为Python默认环境。

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/install/9.png)


### 2. 下载并解压vnpy

Ubuntu系统用户下载vnpy时选择tar.gz压缩版本。

 - [vnpy github下载地址](https://github.com/vnpy/vnpy/releases)
 - [vnpy gitee下载地址](https://gitee.com/mirrors/vn-py/releases)

下载完毕后解压文件，如下图所示。

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/install/10.png)

### 3. 安装vnpy

在安装vnpy前，需要先安装gcc编译器，用于编译C++类接口文件。在终端中输入以下命令即可。
```
sudo apt-get  install  build-essential
```
![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/install/11.png)

请注意，如果出现报错“Unable to locate package build-essential”，则需要先在安装gcc编译器前，先执行命令"sudo apt-get update"

然后在vnpy根目录打开终端，输入下面命令一键安装vnpy。
```
bash install.sh
```

vn.py的安装过程分为4步：

- 下载并安装ta-lib库和numpy
- 安装requirements.txt文件内相关依赖库
- 安装中文编码（针对英文系统）
- 复制vnpy到Anaconda内（若是在虚拟机上运行，需要把内存调至4g，否则报错）

如果安装ta-lib时出现报错如下：

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

- 下载ta-lib的Python wrapper
```
git clone https://github.com/mrjbq7/ta-lib.git
cd ta-lib
python setup.py install
```

请注意，如果出现报错“command ‘gcc’ failed with exit status 1”，可能是由于没有正确安装python开发环境导致，可尝试在命令行输入下述命令：

```
sudo apt-get install python3-dev
```

编译安装ta-lib完毕后，重新执行下述命令安装vnpy即可。
```
bash install.sh
```


### 4.启动VN Trader

在github文件夹examples\vn_trader中找到run.py文件。右键进入终端，输入下面命令即可启动VN Trader。


```
python run.py 
```

如果启动时出现一些库版本不兼容的情况，可根据提示对这些库重新安装。


如果启动时出现下述报错：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/install/13.png)

则需要在命令行输入下述命令来安装libxcb-xinerama0。

```
sudo apy-get install libxcb-xinerama0
```

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/install/14.png)