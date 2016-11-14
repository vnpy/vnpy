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

### Linux版
作者做了一些尝试，但目前vn.ib文件夹下的CMakeLists.txt无法编译出可以使用的so文件，最终在Python中import时会报错

    undefined symbol: _ZN7ECLIENT11EncodeFieldIPKcEEvRSoT

目前已经踩过的坑：

1. 原生API里有个调用min函数的地方会报错，要修改为std::min
2. 上面的原生接口修改部分依旧必须修改
3. IB API提供了所有的源文件，所以调用链接器时无需加上IB API所在的文件夹（不确定）

希望社区里有朋友能试着解决这个问题吧，跳坑方法：
1. 先进入到vn.ib/ibapi/linux文件夹下，运行bash build.sh编译IB API
2. 然后进入vn.ib文件夹下，运行bash build.sh编译vn.ib
3. vn.ib/build/lib下的vnib.so复制到vn.ib/test文件夹下，运行test.py
4. 会出现上面的undefined symbol错误

更新：编译问题已解决，需要在EClient.h和EClient.cpp中，加入EncodeField<const char*>这一对EncodeField<T>的偏特化实现（well，我并不十分确定是否该用“偏特化”这个词），具体请参考linux文件夹下的代码。

但目前Linux下的编译在调用eConnect函数时会卡住，从TWS中查看会有API发起的连接处于“pending”的状态，猜测问题可能出在底层的POSIX线程锁相关的地方。

### API版本
版本：IB API for Windows beta 9.72.18

日期：2016-09-14

链接：[http://interactivebrokers.github.io/](http://interactivebrokers.github.io/)
