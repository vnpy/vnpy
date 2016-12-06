# vn.qdp

### 简介
QDP柜台API接口的Python封装，基于pyscript目录下的脚本自动分析头文件生成封装代码模块，提供原生C++ API中的全部功能。


### 目录说明
* vnqdpmd: 行情API
* vnqdptd: 交易API
* pyscript: 自动封装脚本
* qdpapi：C++ API文件

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

* 进入build目录，双击vn_qdp_api.sln打开解决方案

* 点击编译按钮,建议编译release库


### API版本
日期：2016-11-09

说明：qdpapi文件夹下的是Windows的32位版本
