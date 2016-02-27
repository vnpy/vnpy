# vn.ctp

### 简介
CTP柜台API接口的Python封装，基于pyscript目录下的脚本自动分析头文件生成封装代码模块，提供原生C++ API中的全部功能。


### 目录说明
* vnctpmd: 行情API
* vnctptd: 交易API
* pyscript: 自动封装脚本
* ctpapi：C++ API文件

### 使用CMake编译

**环境配置**

* 建议安装的软件在位数上保持一致，比如全都安装32位，同时编译32位库

* cmake:安装最新版本的cmake,用于配置编译环境

* [Boost1.57.0](http://sourceforge.net/projects/boost/files/boost/1.57.0/)库：编译的方法可以参考[Boost Getting Started](http://www.boost.org/doc/libs/1_58_0/more/getting_started/)右下角的链接

* 设置环境变量：eg: BOOST_ROOT = C:\boost_1_57_0

* 编译32位库还是64位库任意选择

* 需要编译boost python, thread, system, chrono, date_time共5个库：若编译全部库则会浪费大量时间和硬盘空间。

* boost python的动态库64bits可能编译不成功，需加选项address-model=64。或者编译静态库

* [Anaconda1.9.2](http://repo.continuum.io/archive/index.html): 量化相关包的Python发行版

* 编译工具：windows下选择visual studio 2013；linux下使用g++。

Linux: (Debian jessie)

* apt-get install build-essential

* apt-get install libboost-all-dev

* apt-get install python-dev

* apt-get install cmake

* 下载ctp api tar包，比如v6.3.5_20150803_tradeapi_linux64.tar，重命名ctp api so文件名：

* thostmduserapi.so --> libthostmduserapi.so

* thosttraderapi.so --> libthosttraderapi.so


**编译过程**

* 在vn.ctp目录下新建文件夹，并命名为build, 保存编译的临时文件及库文件

* 打开命令行工具输入：cmake-gui .. 则打开cmake配置界面

* 点击configure。

* 点击generate。如果没有错误则配置成功

* 进入build目录，双击vn_ctp_api.sln打开解决方案

* 点击编译按钮,建议编译release库

**Linux: (Debian jessie)**

* 当前目录运行build.sh，完成编译


## API版本
日期：2015-08-04

名称：fsopt_traderapi

描述：个股期权API  

链接：[http://www.sfit.com.cn/5_2_DocumentDown.htm](http://www.sfit.com.cn/5_2_DocumentDown.htm)

说明：ctpapi文件夹下的是Windows的32位版本，其下文件夹x64_linux中的是Linux的64位版本
