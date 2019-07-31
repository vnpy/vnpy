# 安装指南


## Windows



### 使用VNStudio


#### 1.下载VNStudio （Python 3.7 64位）

VNStudio是vn.py团队自行打包的一键安装版本，整合了：
- Python 3.7（社区官方版本)
- vn.py框架和其他相关库
- VN Station量化工作站（vn.py框架的图形化管理工具）

下载地址：[vnstudio-2.0.6.exe](https://download.vnpy.com/vnstudio-2.0.6.exe)

&nbsp;


#### 2.安装VNStudio

一路点击“下一步”即可完成VNStudio安装，安装完成后可以查看相关运行目录：

- VNStudio默认安装路径为C:\vnstudio；
- VNStudio默认json配置文件和数据库路径为C:\Users\Administrator\\.vntrader
- VN Station量化工作站运行目录为C:\vnstudio\Scripts\vnstation.exe；
- vnpy运行目录在C:\vnstudio\Lib\site-packages\vnpy（进入该目录后，用户可以修改vnpy的相关功能）


&nbsp;

#### 3.登陆VNStation

输入账号密码或者微信扫码登陆VNStation。（社区账号通过微信扫码可得）

![](https://vnpy-community.oss-cn-shanghai.aliyuncs.com/forum_experience/yazhang/install.bat/login_VNConda.png "enter image title here")

&nbsp;

#### 4.使用VNStation
登录后会进入到VN Station的主界面。
![](https://vnpy-community.oss-cn-shanghai.aliyuncs.com/forum_experience/yazhang/install.bat/login_VNConda_2.png "enter image title here")

窗口下方有5个选项：
- VN Trade Lite：直接运行VN Trader (只有CTP接口)
- VN Trader Pro：先选择保存相关临时文件的目录，再运行VN Trader (接口和上层应用模块任选)
- Jupyter Notebook：先选择保存相关临时文件的目录，再运行Jupyter Notebook
- 提问求助：提出相关问题，管理员会每天定时回复
- 后台更新：一键更新VN Station


&nbsp;

#### 5.更新VNStation
更新VNStation除了“一键更新”外；也可以卸载老版本，安装新版本；或者在github上下载最新的dev分支，解压后得到根目录下的vnpy文件夹，对C:\vnstudio\Lib\site-packages\vnpy进行替换。



&nbsp;
&nbsp;


### 手动安装

#### 1.下载并安装最新版Anaconda3.7 64位

下载地址如下：[Anaconda Distribution](https://www.anaconda.com/distribution/)

(更轻量的Miniconda地址：[MiniConda Distribution](https://docs.conda.io/en/latest/miniconda.html))

&nbsp;

#### 2.下载并解压vnpy

进入vnpy的github主页[vnpy](https://github.com/vnpy/vnpy)。
在左方的Branch选项，master对应是最新的稳定版本，dev对应的是最新测试版本；
然后在主页右方绿色的clone or download选项，选择Download ZIP来下载压缩版本到本地电脑。

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
