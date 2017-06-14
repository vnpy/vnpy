# vn.ctp

### 简介
CTP柜台API接口的Python封装，基于pyscript目录下的脚本自动分析头文件生成封装代码模块，提供原生C++ API中的全部功能。


### 目录说明
* vnctpmd: 行情API
* vnctptd: 交易API
* pyscript: 自动封装脚本
* ctpapi：C++ API文件

### 使用CMake编译

**Windows 7**

环境配置:

* Anaconda和Boost的安装方式请参考www.vnpy.org上的教程，必须使用32位

* cmake:安装最新版本的cmake,用于配置编译环境

* 设置环境变量：BOOST_ROOT = C:\boost_1_57_0

* 编译工具：Visual Studio 2013


编译过程:

* 在vn.ctp目录下新建文件夹，并命名为build, 保存编译的临时文件及库文件

* 打开命令行工具输入：cmake-gui .. 则打开cmake配置界面

* 点击configure。

* 点击generate。如果没有错误则配置成功

* 进入build目录，双击vn_ctp_api.sln打开解决方案

* 点击编译按钮,建议编译release库


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

### API版本
日期：2015-08-04

名称：fsopt_traderapi

描述：个股期权API  

链接：[http://www.sfit.com.cn/5_2_DocumentDown.htm](http://www.sfit.com.cn/5_2_DocumentDown.htm)

说明：ctpapi文件夹下的是Windows的32位版本，其下文件夹x64_linux中的是Linux的64位版本
