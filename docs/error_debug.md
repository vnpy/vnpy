# ErrorDeBug - 错误排查通用方法

## 简介

只有正确的定位问题，我们才能快速的解决问题。而正确定位问题的前提是获得报错提示信息，这一点完全可以通过命令行启动VN Station来实现。因此，在这里我们介绍两种通过命令行启动VN Station/VN Trader图形界面的方法（新手推荐使用第一种）。

## python -m vnstation启动

首先打开命令行，以win10为例，按下win键后并用英文输入法输入"cmd"会弹出如下窗口，如下图所示：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/error_debug/0.png)

选择命令行提示符就会进入如下界面，如下图所示：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/error_debug/1.png)

输入命令 ```python -m vnstation``` 之后并按Enter键则会进入VN Station的登录界面，如下图所示:

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/error_debug/2.png)

（上图中qt的warning信息不影响程序的运行）

剩下的操作则跟从桌面图标启动VN Station完全一致。重点在于假如出现了BUG，那么我们就可以在该命令行下看到报错的提示，从而定位问题所在。如此也方便大家将报错截图发送到微信/QQ群中或者论坛上寻求帮助。这里提供一个连接数据库失败的例子，如下图所示：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/error_debug/7.png)

如果将DolphinDB作为vn.py的数据库配置，那么在启动VN Trader之前必须先启动DolphinDB数据库，否则就会报如上图所示的错误。

除了有BUG会提示之外，如果想通过“打印输出”的方式检查代码逻辑是否正确，同样可以在策略中加上print()函数。例如，我在策略中加了一句 ```print("test")``` 之后，命令行的输出如下图所示：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/error_debug/6.png)


## python run.py启动

除了通过 ```python -m vnstaion``` 先启动VN Station再启动VN Trader之外，我们还提供了通过运行脚本[run.py](https://gitee.com/vnpy/vnpy/blob/master/examples/vn_trader/run.py)直接启动VN Trader图形界面的方法。

首先下载上述run.py代码到本地，比如下载到D:\downloads\run.py，然后进入D:\downloads目录，按住shift键，然后选择“在此处打开PowerShell窗口”，接着就会打开一个PowerShell窗口，如下图所示：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/error_debug/4.png)

之后输入 ```python .\run.py``` 则会直接进入VN Trader图形界面。同样，如果之后有BUG出现，那么也可以在该PowerShell窗口上找到错误提示，如下图所示：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/error_debug/5.png)

需要注意的是，在使用run.py的时候，将需要加载的接口和应用模块的代码取消注释就行，但是最好不要同时加载多个C++类的接口。