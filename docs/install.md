# 安装指南


## Windows



### 使用VNConda

#### 1.下载VNConda （Python 3.7 64位）

下载地址如下：[VNConda-2.0.1-Windows-x86_64](https://conda.vnpy.com/VNConda-2.0.1-Windows-x86_64.exe)

&nbsp;


#### 2.安装VNConda

注意事项：第4步会提示用户是否把VNConda注册成默认Python环境：若用户存在其他Python环境，则都不要勾选；反之，两个都勾选掉。

![enter image description here](https://vnpy-community.oss-cn-shanghai.aliyuncs.com/forum_experience/yazhang/install.bat/install_VNConda.png "enter image title here")

&nbsp;

#### 3.登陆VNStation

输入账号密码或者微信扫码登陆VNConda。（社区账号通过微信号码可得）

![enter image description here](https://vnpy-community.oss-cn-shanghai.aliyuncs.com/forum_experience/yazhang/install.bat/login_VNConda.png "enter image title here")

&nbsp;

#### 4.使用VNStation
登录后会进入到VNConda的主界面。

![enter image description here](https://vnpy-community.oss-cn-shanghai.aliyuncs.com/forum_experience/yazhang/install.bat/login_VNConda_2.png "enter image title here")

窗口下方有5个选项：
- VN Trade Lite：直接运行VN Trader (只有CTP接口)
- VN Trader Pro：先选择保存相关临时文件的目录，再运行VN Trader (接口任选)
- Jupyter Notebook：先选择保存相关临时文件的目录，再运行Jupyter Notebook
- 提问求助：提出相关问题，管理员会每天定时回复
- 后台更新：一键更新VN Station

&nbsp;
&nbsp;

### 手动安装

#### 1.下载并安装最新版Anaconda3.7 64位

下载地址如下：[Anaconda Distribution](https://www.anaconda.com/distribution/)

(更轻量的MiniConda地址：[MiniConda Distribution](https://docs.conda.io/en/latest/miniconda.html))

&nbsp;

#### 2.下载并解压vnpy

下载地址如下：[vnpy releases](https://github.com/vnpy/vnpy/releases)

&nbsp;

#### 3.安装vnpy
双击install.bat一键安装vnpy：
- 先安装TA_LIB库和IB API
- 然后安装requirements.txt文件内相关依赖库
- 最后复制vnpy到Anaconda内

&nbsp;

#### 4.启动VN Trader
在文件夹tests\trader中找到run.py文件。按住“Shift” + 鼠标右键进入cmd窗口，输入下面命令即可启动VN Trader。
```
Python run.py 
```



## Ubuntu

### 安装脚本

### TA-Lib

### 中文编码

如果是英文系统（如阿里云），请先运行下列命令安装中文编码：

```
sudo locale-gen zh_CN.GB18030
```
