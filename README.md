# By Traders, For Traders.


![vn.py-logo](http://vnpy.oss-cn-shanghai.aliyuncs.com/vnpy-logo.png)

---

### 简介

vn.py是基于Python的开源量化交易程序开发框架，起源于国内私募的自主量化交易系统。2015年初项目启动时只是单纯的交易API接口的Python封装。随着业内关注度的上升和社区不断的贡献，目前已经成长为一套全功能的交易程序开发框架，用户群体也日渐多样化，包括私募基金、券商自营和资管、期货资管和子公司、高校研究机构和专业个人投资者等。

---

### 项目结构

1. 丰富的Python交易API接口（vnpy.api），基本覆盖了国内外所有常规交易品种（股票、期货、期权、外汇、外盘、比特币），具体包括：

    - CTP（ctp）

    - 飞马（femas）

    - 中泰证券XTP（xtp）

    - 中信证券期权（cshshlp）

    - 金仕达黄金（ksgold）

    - 金仕达期权（ksotp）

    - 飞鼠（sgit）

    - 飞创（xspeed）

    - QDP（qdp）

    - 上海直达期货（shzd）

    - Interactive Brokers（ib）

    - OANDA（oanda）

    - 福汇（fxcm）

    - OKCOIN（okcoin）

    - 火币（huobi）

    - LBank（lbank）

2. 简洁易用的事件驱动引擎（vnpy.event），作为事件驱动型交易程序的核心

3. 支持服务器端数据推送的RPC框架（vnpy.rpc），用于实现多进程分布式架构的交易系统

4. 开箱即用的实盘交易平台框架（vnpy.trader），整合了多种交易接口，并针对具体策略算法和功能开发提供了简洁易用的API，用于快速构建交易员所需的量化交易程序，应用举例：

    * 同时登录多个交易接口，在一套界面上监控多种市场的行情和多种资产账户的资金、持仓、委托、成交情况

    * 支持跨市场套利（CTP期货和XTP证券）、境内外套利（CTP期货和IB外盘）、多市场数据整合实时预测走势（CTP的股指期货数据、IB的外盘A50数据、Wind的行业指数数据）等策略应用

    * CTA策略引擎模块，在保持易用性的同时，允许用户针对CTA类策略运行过程中委托的报撤行为进行细粒度控制（降低交易滑点、实现高频策略）

    * 实盘行情记录，支持Tick和K线数据的落地，用于策略开发回测以及实盘运行初始化

5. 数据相关的API接口（vnpy.data），用于构建和更新历史行情数据库，目前包括：

  * 上海中期历史行情服务（shcifco）

  * 通联数据API下载服务（datayes）

  * 天勤行情数据接口（tq）

6. 关于vn.py项目的应用演示（examples），对于新手而言可以从这里开始学习vn.py项目的使用方式

8. vn.py项目的Docker镜像（docker），目前尚未完成

9. [官网](http://vnpy.org)和[知乎专栏](http://zhuanlan.zhihu.com/vn-py)，内容包括vn.py项目的开发教程和Python在量化交易领域的应用研究等内容

10. 官方交流QQ群262656087，管理较严格（定期清除长期潜水的成员）

---
### 环境准备

**Windows**

1. 支持的操作系统：Windows 7/8/10/Server 2008
2. 安装[MongoDB](https://www.mongodb.org/downloads#production)，并[将MongoDB配置为系统服务](https://docs.mongodb.com/manual/tutorial/install-mongodb-on-windows/#configure-a-windows-service-for-mongodb-community-edition)
3. 安装[Anaconda](http://www.continuum.io/downloads)，**注意必须是Python 2.7 32位版本**
4. 安装[Visual C++ Redistributable Packages for VS2013 x86版本](https://support.microsoft.com/en-us/help/3138367/update-for-visual-c-2013-and-visual-c-redistributable-package)
5. 安装[python-snappy](https://www.lfd.uci.edu/~gohlke/pythonlibs/)，使用命令**pip install python_snappy-0.5.1-cp27-cp27m-win32.whl**

**Ubuntu**

请参考项目wiki中的[教程](https://github.com/vnpy/vnpy/wiki/Ubuntu%E7%8E%AF%E5%A2%83%E5%AE%89%E8%A3%85)。

---
### 项目安装

**方法1**

在[这里](https://github.com/vnpy/vnpy/releases)下载最新版本，解压后:

* Windows：双击运行install.bat自动安装
* Ubuntu：在Terminal中运行bash install.sh自动安装

**方法2**

```
pip install vnpy pymongo msgpack-python websocket-client qdarkstyle

conda install -c quantopian ta-lib=0.4.9
```

**关于TA-Lib安装**

Ubuntu上安装到talib时若遭遇'Permission denied'错误，请在install.sh运行完成后，在Terminal中输入以下命令安装：

```
sudo /home/vnpy/anaconda2/bin/conda install -c quantopian ta-lib=0.4.9
```

其中"/home/vnpy/anaconda2/"是你的Anaconda安装路径。


---
### Quick Start


1. 在[SimNow](http://simnow.com.cn/)注册CTP仿真账号，记下你的**账号、密码、经纪商编号**，然后下载快期查询你的**交易和行情服务器地址**

2. 找到vn.py应用示例目录examples，打开examples\VnTrader\CTP_connect.json，修改账号、密码、服务器等为上一步注册完成后你的信息（注意使用专门的编程编辑器，如Sublime Text等，防止json编码出错）

3. 找到VnTrader的启动入口run.py，并双击运行（若无法双击，则在当前目录按住Shift点鼠标右键，打开cmd输入python run.py运行），run.py内容如下：

```
# encoding: UTF-8

# 重载sys模块，设置默认字符串编码方式为utf8
import sys
reload(sys)
sys.setdefaultencoding('utf8')

# 判断操作系统
import platform
system = platform.system()

# vn.trader模块
from vnpy.event import EventEngine
from vnpy.trader.vtEngine import MainEngine
from vnpy.trader.uiQt import createQApp
from vnpy.trader.uiMainWindow import MainWindow

# 加载底层接口
from vnpy.trader.gateway import (ctpGateway, oandaGateway, ibGateway, 
                                 tkproGateway)

if system == 'Windows':
    from vnpy.trader.gateway import (femasGateway, xspeedGateway, 
                                     futuGateway, secGateway)
    
if system == 'Linux':
    from vnpy.trader.gateway import xtpGateway

# 加载上层应用
from vnpy.trader.app import (riskManager, ctaStrategy, spreadTrading)


#----------------------------------------------------------------------
def main():
    """主程序入口"""
    # 创建Qt应用对象
    qApp = createQApp()
    
    # 创建事件引擎
    ee = EventEngine()
    
    # 创建主引擎
    me = MainEngine(ee)
    
    # 添加交易接口
    me.addGateway(ctpGateway)
    me.addGateway(tkproGateway)
    me.addGateway(oandaGateway)
    me.addGateway(ibGateway)
    
    if system == 'Windows':
        me.addGateway(femasGateway)
        me.addGateway(xspeedGateway)
        me.addGateway(secGateway)
        me.addGateway(futuGateway)
        
    if system == 'Linux':
        me.addGateway(xtpGateway)
        
    # 添加上层应用
    me.addApp(riskManager)
    me.addApp(ctaStrategy)
    me.addApp(spreadTrading)
    
    # 创建主窗口
    mw = MainWindow(me, ee)
    mw.showMaximized()
    
    # 在主线程中启动Qt事件循环
    sys.exit(qApp.exec_())


if __name__ == '__main__':
    main()

```

更多使用方法方法请参考examples下的其他目录。

---

### 用户文档

项目的最新文档请查看[Github Wiki](https://github.com/vnpy/vnpy/wiki)，知乎专栏和官网文档已经落后于项目开发版本，建议只作为额外的参考资料。

---

### 开发工具推荐

* [WingIDE](http://wingware.com/)：非常好用的Python集成开发环境（作者就是用它写的vn.py）

* [Robomongo](https://robomongo.org/)：MongoDB的图形化客户端，方便监控和修改数据

* [Sublime Text](http://www.sublimetext.com/)：针对编程的文本编辑器，当然你也可以使用Vim或者Emacs

* [PyQtGraph](http://www.pyqtgraph.org/)：适用于开发实时更新数据的图表，如Tick图、K线图、期权波动率曲线等（Matplotlib渲染开销太大，用于实盘绘图可能拖慢整个程序）

* [Visual Studio 2013](https://www.visualstudio.com/en-us/downloads/download-visual-studio-vs.aspx)：这个就不多说了（作者编译API封装用的是2013版本）


---
### 贡献代码

vn.py使用github托管其源代码，如果希望贡献代码请使用github的PR(Pull Request)的流程:

1. [创建 Issue](https://github.com/vnpy/vnpy/issues/new) - 对于较大的改动(如新功能，大型重构等)最好先开issue讨论一下，较小的improvement(如文档改进，bugfix等)直接发PR即可

2. Fork [vn.py](https://github.com/vnpy/vnpy) - 点击右上角**Fork**按钮

3. Clone你自己的fork: ```git clone https://github.com/$userid/vnpy.git```
	* 如果你的fork已经过时，需要手动sync：[https://help.github.com/articles/syncing-a-fork/](https://help.github.com/articles/syncing-a-fork/)

4. 从**dev**创建你自己的feature branch: ```git checkout -b $my_feature_branch dev```

5. 在$my_feature_branch上修改并将修改push到你的fork上

6. 创建从你的fork的$my_feature_branch分支到主项目的**dev**分支的[Pull Request] -  [在此](https://github.com/vnpy/vnpy/compare?expand=1)点击**compare across forks**，选择需要的fork和branch创建PR

7. 等待review, 需要继续改进，或者被Merge!

---
### 项目捐赠

过去的半年中陆续收到了许多用户的捐赠，在此深表感谢！所有的捐赠资金都投入到了vn.py社区基金中，用于支持vn.py项目的运作。最近主要的一个支出是相关文档编写，目前来看文档完成的速度和质量都显著超出预期。

先强调一下：**vn.py是开源项目，可以永久免费使用，并没有强制捐赠的要求！！！**

捐赠方式：支付宝3216630132@qq.com（*晓优）

计划长期维护一份捐赠清单，所以请在留言中注明是项目捐赠以及捐赠人的名字（当然想匿名的用户就随意了）。


---
### 其他内容

* [获取帮助](https://github.com/vnpy/vnpy/blob/dev/docs/SUPPORT.md)
* [社区行为准侧](https://github.com/vnpy/vnpy/blob/dev/docs/CODE_OF_CONDUCT.md)
* [Issue模板](https://github.com/vnpy/vnpy/blob/dev/docs/ISSUE_TEMPLATE.md)
* [PR模板](https://github.com/vnpy/vnpy/blob/dev/docs/PULL_REQUEST_TEMPLATE.md)


---
### License
MIT
