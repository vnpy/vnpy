# Mac安装指南

## Mac系统的CTP接口支持

得益于Python语言本身的跨平台优势（Windows、Linux、Mac三大系统），VeighNa量化交易平台的核心框架部分很早就可以在Mac系统上运行。

但由于C++类交易API对于Mac系统支持的普遍不足，导致之前只有vnpy_ib等少数【纯Python实现】的交易接口可以在Mac系统上运行，对于大部分用户来说没什么实际价值。

从6.6.7版本的CTP API开始，上期技术官方推出了对Mac系统支持，包括Intel（x86_64）和苹果M系（arm64）芯片。终于，VeighNa平台可以在Mac系统上为期货量化用户提供从投研回测到实盘交易的一体化解决方案。


## Mac系统的VeighNa安装流程

目前Mac系统上还没有类似VeighNa Studio的开箱即用发行版，需要手动完成安装流程：

1. 前往Python官网下载安装包（推荐使用3.13及以上版本，或者使用brew安装），安装完成后在终端（Terminal）中运行命令：

```python3
python3
```
检查确认打开的Python解释器为3.13及以上版本。

2. 使用brew安装TA-Lib的C++开发包：

```python3
brew install ta-lib
```

3. 安装NumPy和TA-Lib（Python），这里推荐使用清华PyPI镜像解决官方源访问困难的问题：

```python3
python3 -m pip install numpy==2.2.3 -i https://pypi.tuna.tsinghua.edu.cn/simple
python3 -m pip install ta-lib==0.6.4 -i https://pypi.tuna.tsinghua.edu.cn/simple
```

4. 安装米筐RQData客户端，注意这里使用的是米筐PyPI源：

```python3
python3 -m pip install rqdatac --index=https://pypi2.ricequant.com/simple
```

5. 安装VeighNa核心框架，以及需要使用的功能插件模块：


```python3
python3 -m pip install vnpy -i https://pypi.tuna.tsinghua.edu.cn/simple
python3 -m pip install vnpy_ctastrategy vnpy_ctabacktester vnpy_datamanager vnpy_sqlite vnpy_rqdata -i https://pypi.tuna.tsinghua.edu.cn/simple
```
这里的例子中包括（具体可以根据自己的需求调整）：

 - CTA策略实盘和回测模块：vnpy_ctastrategy、vnpy_ctabacktester
 - 历史数据管理模块：vnpy_datamanager
 - SQLite数据库驱动：vnpy_sqlite
 - RQData数据服务适配器：vnpy_rqdata

pip安装过程中如果出现报错某些依赖库的缺失，可以尝试先pip install该依赖库，然后再次执行上述安装命令。

6. 安装CTP交易接口模块：

由于新版本CTP的Mac系统API项目结构发生了较大变化，改为了使用framework目录的结构，因此无法再直接从PyPI下载预编译好的wheel二进制包进行安装。

用户需要克隆（或下载）vnpy_ctp仓库的源代码到本地后自行编译安装，具体命令如下：

```python3
git clone https://github.com/vnpy/vnpy_ctp.git

cd vnpy_ctp

pip3 install .
```

相关注意事项如下：

源码编译需要依赖XCode开发工具中的C++编译器，请务必先安装好。

由于当前新版本Mac系统的安全机制，安装完成后若首次启动加载CTP动态库时遇到系统安全拦截提示，需要在【访达】中找到已安装的`vnpy_ctp/api`目录下的`thostmduserapi_se.framework`和`thosttraderapi_se.framework`中的动态库文件，分别手动打开一次后添加到操作系统信任名单，才能在启动Python时成功加载。

以上两个文件由于本身是二进制格式，并不能正常打开，但不影响添加到系统信任名单。

完成后即可使用run.py脚本启动VeighNa Trader，代码如下：

```python3
from vnpy.event import EventEngine
from vnpy.trader.engine import MainEngine
from vnpy.trader.ui import MainWindow, create_qapp
from vnpy_ctp import CtpGateway
from vnpy_ctastrategy import CtaStrategyApp
from vnpy_ctabacktester import CtaBacktesterApp
from vnpy_datamanager import DataManagerApp

def main():
    """Start VeighNa Trader"""
    qapp = create_qapp()

    event_engine = EventEngine()
    main_engine = MainEngine(event_engine)

    main_engine.add_gateway(CtpGateway)
    main_engine.add_app(CtaStrategyApp)
    main_engine.add_app(CtaBacktesterApp)
    main_engine.add_app(DataManagerApp)

    main_window = MainWindow(main_engine, event_engine)
    main_window.showMaximized()

    qapp.exec()

if __name__ == "__main__":
    main()
```
