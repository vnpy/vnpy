# vn.ib

目前vn.ib还处于开发中，完成了封装部分的工作，欢迎贡献测试相关的代码。

### 简介
基于IB POSIX C++ API的Python封装，提供原生API的全部功能，同时Python代码中函数和类的命名定义都和C++中保持一致。

### vn.ib和IbPy的不同点
1. vn.ib基于Boost.Python封装了原生Posix C++接口，比起IbPy能提供更好的性能

2. vn.ib底层代码中添加了异常捕捉功能，避免IbPy的函数触发异常后没有报错直接断开连接，导致无法调试的问题

3. vn.ib安装时可能需要编译（默认的pyd在Windows7 Python 2.7 32位下编译），IbPy是纯Python的可以直接使用

4. vn.ib基于较新的IB官方API（9.72 beta）开发，IbPy则是采用了较老的API（9.70 stable）

### 对原生接口的修改部分
shared_ptr.h和SoftDollerTier.h中加入了对象比较函数的代码，用于实现其对应vector的自动Python封装。

### API版本
版本：IB API for Windows beta 9.72.18

日期：2016-09-14

链接：[http://interactivebrokers.github.io/](http://interactivebrokers.github.io/)

