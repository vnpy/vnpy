# Mac安装指南

## Mac系统的CTP接口支持

得益于Python语言本身的跨平台优势（Windows、Linux、Mac三大系统），VeighNa量化交易平台的核心框架部分很早就可以在Mac系统上运行。

但由于C++类交易API对于Mac系统支持的普遍不足，导致之前只有vnpy_ib等少数【纯Python实现】的交易接口可以在Mac系统上运行，对于大部分用户来说没什么实际价值。

从6.6.7版本的CTP API开始，上期技术官方推出了对Mac系统支持，包括Intel（x86_64）和苹果M系（arm64）芯片。终于，VeighNa平台可以在Mac系统上为期货量化用户提供从投研回测到实盘交易的一体化解决方案。


## Mac系统的VeighNa安装流程

目前Mac系统上还没有类似VeighNa Studio的开箱即用发行版，需要手动完成安装流程：

1. 前往Python官网下载3.10版本的安装包（或者使用brew安装），安装完成后在终端（Terminal）中运行命令：

```python3
python3
```
检查确认打开的Python解释器为3.10版本。

2. 使用brew安装TA-Lib的C++开发包：

```python3
brew install ta-lib
```

3. 安装NumPy和TA-Lib（Python），这里推荐使用豆瓣PyPI镜像解决官方源访问困难的问题：

```python3
python3 -m pip install numpy==1.26.4 --index=https://pypi.doubanio.com/simple
python3 -m pip install ta-lib --index=https://pypi.doubanio.com/simple
```

4. 安装米筐RQData客户端，注意这里使用的是米筐PyPI源：

```python3
python3 -m pip install rqdatac --index=https://pypi2.ricequant.com/simple
```

5. 安装VeighNa核心框架，以及需要使用的功能插件模块：


```python3
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

由于6.7.2版本CTP的Mac系统API项目结构发生了较大变化，改为了使用framework目录的结构，因此无法再直接从PyPI下载预编译好的wheel二进制包进行安装。

用户需要克隆（或下载）本仓库的源代码到本地后（注意；克隆的源代码文件夹vnpy_ctp不要直接放在用户文件夹下，需要放在一个其的子文件下，否则会出现安装完成后无法识别该模块的情况，如下以在用户文件夹下新建一个名为github的文件夹为例）自行编译安装，具体命令如下：

```python3
mkdir github

cd github

git clone https://github.com/vnpy/vnpy_ctp.git

cd vnpy_ctp

pip3 install -e .
```

相关注意事项如下：

源码编译需要依赖XCode开发工具中的C++编译器，请务必先安装好。

编译过程中，会指定克隆到本地的源码目录中的framework文件夹路径，为API运行时动态库的加载路径。因此后续运行时，该源码目录不能删除，也不能移动位置，否则会导致动态库加载找不到的报错。

由于当前新版本Mac系统的安全机制，编译完成后需要在【访达】中找到下述两个动态库文件，分别手动打开一次后添加到操作系统信任名单，才能在启动Python时成功加载：

* vnpy_ctp/api/libs/thostmduserapi_se.framework/Versions/A/thostmduserapi_se
* vnpy_ctp/api/libs/thosttraderapi_se.framework/Versions/A/thosttraderapi_se

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
