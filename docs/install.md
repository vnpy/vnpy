# 安装指南


## Windows



### 使用VNConda


#### 1.下载VNConda （Python 3.7 64位）

下载地址如下：[VNConda-2.0.1-Windows-x86_64](https://conda.vnpy.com/VNConda-2.0.1-Windows-x86_64.exe)

&nbsp;


#### 2.安装VNConda

注意事项：第4步会提示用户是否把VNConda注册成默认Python环境：若用户存在其他Python环境，则都不要勾选；反之，两个都勾选掉。

![](https://vnpy-community.oss-cn-shanghai.aliyuncs.com/forum_experience/yazhang/install.bat/install_VNConda.png "enter image title here")

&nbsp;

#### 3.登陆VNStation

输入账号密码或者微信扫码登陆VNConda。（社区账号通过微信扫码可得）

![](https://vnpy-community.oss-cn-shanghai.aliyuncs.com/forum_experience/yazhang/install.bat/login_VNConda.png "enter image title here")

&nbsp;

#### 4.使用VNStation
登录后会进入到VN Station的主界面。
![](https://vnpy-community.oss-cn-shanghai.aliyuncs.com/forum_experience/yazhang/install.bat/login_VNConda_2.png "enter image title here")

窗口下方有5个选项：
- VN Trade Lite：直接运行VN Trader (只有CTP接口)
- VN Trader Pro：先选择保存相关临时文件的目录，再运行VN Trader (接口任选)
- Jupyter Notebook：先选择保存相关临时文件的目录，再运行Jupyter Notebook
- 提问求助：提出相关问题，管理员会每天定时回复
- 后台更新：一键更新VN Station


&nbsp;

#### 5.更新VNStation
更新VNStation除了“一键更新”外，也可以卸载老版本，安装新版本。

重新启动后，有几率会遇到下面的问题：“无法定位序数4540于动态链接库 \VNConda\Lib\site-packages\PyQt5\Qt\bin\ssleay.dll上。”类似的窗口弹出了几个，无法登录VN Station。

原因是操作系统中安装了其他的SSL组件，同时还影响了相关的环境变量，导致PyQt载入ssl模块失败。
解决方法是将 \VNConda\Lib\site-packages\PyQt5\Qt\bin 目录的两个动态库 libeay32.dll和 ssleay32.dll拷贝到 \VNConda\ 下。

&nbsp;
&nbsp;


### 手动安装

#### 1.下载并安装最新版Anaconda3.7 64位

下载地址如下：[Anaconda Distribution](https://www.anaconda.com/distribution/)

(更轻量的Miniconda地址：[MiniConda Distribution](https://docs.conda.io/en/latest/miniconda.html))

&nbsp;

#### 2.下载并解压vnpy

Windows用户选择zip压缩版本。下载地址如下：[vnpy releases](https://github.com/vnpy/vnpy/releases)

&nbsp;

#### 3.安装vnpy
双击install.bat一键安装vnpy：
- 先安装ta_lib库和ib api
- 然后安装requirements.txt文件内相关依赖库
- 最后复制vnpy到Anaconda内

&nbsp;

#### 4.启动VN Trader
在文件夹tests\trader中找到run.py文件。按住“Shift” + 鼠标右键进入cmd窗口，输入下面命令即可启动VN Trader。
```
python run.py 
```

&nbsp;
&nbsp;


## Ubuntu


### 1. 下载并安装最新版本的Anaconda或者Miniconda （Python 3.7 64位）

以MiniConda为例，进入已下载好 Miniconda3-latest-Linux-x86_64.sh 所在目录，终端运行如下命令开始安装。
```
$ bash Miniconda3-latest-Linux-x86_64.sh
```

安装过程中可以一直按“Enter”键继续下去，除了以下这点：

当询问是否把Miniconda设置为Python 默认环境时，把默认的"no"改成“yes”。原因是Ubuntu 18.04已有自带的Python 3.6与Python 2.7。

![](https://vnpy-community.oss-cn-shanghai.aliyuncs.com/forum_experience/yazhang/install.bat/install_Miniconda_ubuntu.png "enter image title here")



重启Ubuntu后，打开终端直接输入"python" 然后按“Enter”键: 若出现如下图，则表示成功把Miniconda设置为Python默认环境。

![](https://vnpy-community.oss-cn-shanghai.aliyuncs.com/forum_experience/yazhang/install.bat/Conda_Python_version.png "enter image title here")

&nbsp;

### 2. 下载并解压vnpy
Linux用户选择tar.gz压缩版本。下载地址如下：[vnpy releases](https://github.com/vnpy/vnpy/releases)

&nbsp;

### 3. 安装vnpy
先安装gcc编译器，用于编译C++类接口文件。在终端中输入以下命令即可。
```
sudo apt-get  install  build-essential
```


然后在vnpy根目录打开终端，输入下面命令一键安装vnpy。
```
bash install.sh
```

安装过程分为4步：
- 下载并安装ta_lib库和numpy
- 安装requirements.txt文件内相关依赖库
- 安装中文编码（针对英文系统）
- 复制vnpy到Anaconda内（若是在虚拟机上运行，需要把内存调至4g，否则报错）

&nbsp;

### 4.启动VN Trader
在文件夹tests\trader中找到run.py文件。右键进入终端，输入下面命令即可启动VN Trader。
```
python run.py 
```
