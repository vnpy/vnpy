# Mac安装指南

## Mac系统的CTP接口支持

得益于Python语言本身的跨平台优势（Windows、Linux、Mac三大系统），VeighNa量化交易平台的核心框架部分很早就可以在Mac系统上运行。

但由于C++类交易API对于Mac系统支持的普遍不足，导致之前只有vnpy_ib等少数【纯Python实现】的交易接口可以在Mac系统上运行，对于大部分用户来说没什么实际价值。

从6.6.7版本的CTP API开始，上期技术官方推出了对Mac系统支持，包括Intel（x86_64）和苹果M系（arm64）芯片。终于，VeighNa平台可以在Mac系统上为期货量化用户提供从投研回测到实盘交易的一体化解决方案。


## Mac系统的VeighNa安装流程

目前Mac系统上还没有类似VeighNa Studio的开箱即用发行版，需要手动完成安装流程：

1. 前往Python官网下载3.10版本的安装包（或者使用brew安装），安装完成后在终端（Terminal）中运行命令：

```python 3
python3
```
检查确认打开的Python解释器为3.10版本。

2. 使用brew安装TA-Lib的C++开发包：

```python 3
brew install ta-lib
```

3. 安装NumPy和TA-Lib（Python），这里推荐使用豆瓣PyPI镜像解决官方源访问困难的问题：

```python 3
python3 -m pip install numpy --index=https://pypi.doubanio.com/simple
python3 -m pip install ta-lib==0.4.24 --index=https://pypi.doubanio.com/simple
```

4. 安装米筐RQData客户端，注意这里使用的是米筐PyPI源：

```python 3
python3 -m pip install rqdatac --index=https://pypi2.ricequant.com/simple
```

5. 安装VeighNa核心框架，以及需要使用的功能插件模块：


```python 3
python3 -m pip install vnpy --index=https://pypi.doubanio.com/simple
python3 -m pip install vnpy_ctastrategy vnpy_ctabacktester vnpy_datamanager vnpy_sqlite vnpy_rqdata --index=https://pypi.doubanio.com/simple
```
这里的例子中包括（具体可以根据自己的需求调整）：

 - CTA策略实盘和回测模块：vnpy_ctastrategy、vnpy_ctabacktester
 - 历史数据管理模块：vnpy_datamanager
 - SQLite数据库驱动：vnpy_sqlite
 - RQData数据服务适配器：vnpy_rqdata

pip安装过程中如果出现报错某些依赖库的缺失，可以尝试先pip install该依赖库，然后再次执行上述安装命令。

6. 安装CTP交易接口模块：

```python 3
python3 -m pip install vnpy_ctp --index=https://pypi.doubanio.com/simple
```

如果Intel芯片的机器上安装失败，请在App Store中安装XCode编译器后再次尝试。

完成后即可使用run.py脚本启动VeighNa Trader：

```python 3
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
