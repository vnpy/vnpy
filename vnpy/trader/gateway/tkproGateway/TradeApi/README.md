# TradeApi

标准交易API定义

# 安装步骤

1、安装Python环境
------

如果本地还没有安装Python环境，强烈建议安装 [Anaconda](http://www.continuum.io/downloads "Anaconda")。

打开上面的网址，选择相应的操作系统，确定要按照的Python版本，一般建议用Python 2.7。

下载完成以后，按照图形界面步骤完成安装。在默认情况下，Anaconda会自动设置PATH环境。

2、安装依赖包
----------------

如果Python环境不是类似Anaconda的集成开发环境，我们需要单独安装依赖包，在已经有pandas/numpy包前提下，还需要有以下几个包：

	pyzmq
	msgpack_python
	python-snappy

可以通过单个安装完成，例如： pip install pyzmq

需要注意的是，python-snappy和msgpack-python这两个包在Windows上的安装需要比较多的编译依赖,建议从[这个网页](http://www.lfd.uci.edu/~gohlke/pythonlibs)下载编译好的包，然后安装:

	pip install msgpack_python-0.4.8-cp27-cp27m-win_amd64.whl 
	
	pip install python_snappy-0.5.1-cp27-cp27m-win_amd64.whl



3、使用TradeApi
--------

在项目目录，验证TradeApi是否正常使用。

```python
from TradeApi import TradeApi

api = TradeApi(addr="tcp://gw.quantos.org:8901")
result, msg = api.login("username", "token") # 示例账户，用户需要改为自己在www.quantos.org上注册的账户
print result
print msg

```
