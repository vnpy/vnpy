# vn.ctp


### 简介
CTP柜台API接口的Python封装，基于pyscript目录下的脚本自动分析头文件生成封装代码模块，提供原生C++ API中的全部功能。


### 目录说明
* py3: Windows下编译
* vnctpmd: 行情API(py3)
* vnctptd: 交易API(py3)
* pyscript: 自动封装脚本
* ctpapi：C++ API文件

### 使用CMake编译

**Windows 7/10**

环境配置:

* Anaconda使用64bit，python 3， 如 python 3.5 3.6

* Boost 使用 1.57 以上
  boost 安装后，有一个stage的版本，对应include & lib的路径。
* cmake:安装最新版本的cmake,用于配置编译环境

* 设置环境变量：BOOST_ROOT = C:\boost_1_57_0

* 编译工具：Visual Studio 2017


编译过程:

* 使用 Visual Studio 2017, 打开 py3/vnctpmd下解决方案vnctpmd.sln

* 检查“项目”配置中，对应的include和ib目录，均要包含python 3.x 和boost的include & lib路径

* 点击编译按钮,建议编译release库

* vnctptd的编译同上。


**Linux (Debian jessie, Ubuntu 16.04)**

环境配置：

* 参考[这里](http://www.continuum.io/downloads)的教程下载并安装Anaconda的Linux 64位版本

* 使用apt-get安装编译相关的工具，注意某些老的Ubuntu必须指定使用boost 1.58.0版本：

    - apt-get install build-essential

    - apt-get install libboost-all-dev

    - apt-get install python-dev

    - apt-get install cmake

* 如果从官网下载新的ctp api tar包，比如v6.3.5_20150803_tradeapi_linux64.tar，需要重命名ctp api so文件名（否则可以忽略该步骤）：

    - thostmduserapi.so --> libthostmduserapi.so

    - thosttraderapi.so --> libthosttraderapi.so


编译过程：

* 当前目录运行build.sh，完成编译


