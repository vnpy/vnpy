# vn.ksotp 金仕达期权API的封装接口

本套接口同时支持:
1. 现货期权（ETF、个股）
2. 股指期权
3. 商品期权

使用前，必须把ksotpapi下的KSInterB2C.lkc（接口授权文件）放到python.exe所在的文件夹下。

例如，把Anaconda安装在了D:\Anaconda下的话，就需要把KSInterB2C.lkc复制粘贴到D:\Anaconda文件夹，否则运行时Python虚拟机会捕获未知C++错误的异常。