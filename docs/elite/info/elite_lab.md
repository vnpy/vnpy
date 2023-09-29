# 投研开发环境


## 启动运行

### 点击图标启动

安装成功后，双击桌面上VeighNa Elite Lab快捷方式：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/elite/lab/1.png)

即可运行VeighNa Elite Lab。

### 用户登录

每次使用VeighNa Elite Lab都会弹出包含用户名输入框以及密码输入框的登录界面，如下图所示：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/elite/lab/2.png)

用户按照要求在用户名输入框中输入用户名，在密码输入框中输入密码后，点击【登录】按钮，即可完成登录进入VeighNa Elite Lab主运行程序，如下图所示：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/elite/lab/3.png)

请注意，若VeighNa Elite Lab启动时检测到已有更新版本发布，则会弹出【更新提示】窗口。若点击【Yes】则立即更新，若点击【No】则跳过更新正常登录。

## 选择目录

成功登录后，可在VeighNa Elite Lab启动界面的右下角看见运行目录（默认显示用户目录），若需切换到至指定目录运行可点击【修改】按钮在弹出的【选择Jupyter Lab运行目录】窗口中进行选择。指定完运行目录之后，则可点击界面左下角的【启动】按钮打开VeighNa Elite Lab，如下图所示：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/elite/lab/4.png)


## 笔记本模式

点击VeighNa Elite Lab右侧启动器中【Notebook】选项下的图标即可新建一个空白的jupyter笔记本，如下图所示：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/elite/lab/5.png)

### 笔记本运行示例

在VeighNa Elite Lab中，用户可加载VeighNa Elite内置的模块进行研究。

以CTA策略模块的回测笔记本为例，首先需要加载需要用到的组件和策略对象，然后创建回测引擎并设置回测过程中引擎用到的参数。设置完之后再添加策略对象和策略参数设置到回测引擎中，此时就可以加载数据开始跑回测了。结果跑出来之后就可以计算每日盈亏和统计指标并通过图表把结果显示出来了。


## 交互式模式

点击VeighNa Elite Lab右侧启动器中【Console】选项下的图标即可打开一个Python交互式环境，可以直接输入代码，然后执行，并立刻得到结果。如下图所示：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/elite/lab/6.png)


## 其他模式

VeighNa Elite Lab不仅支持一个页面打开编辑多个Notebook，Ipython console和terminal终端，还支持预览和编辑更多种类的文件，如代码文件，Markdown文档，json和csv等，如下图所示：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/elite/lab/7.png)

### 命令行

点击VeighNa Elite Lab右侧启动器中【Other】选项下的Terminal图标即可打开命令行。

### 编辑文本

点击VeighNa Elite Lab右侧启动器中【Other】选项下的Text File图标即可新建一个空白的txt文件。VeighNa Elite Lab同时也支持编辑查看已存在的txt文件。

### 编辑Markdown

点击VeighNa Elite Lab右侧启动器中【Other】选项下的Markdown File图标即可新建一个空白的md文件。VeighNa Elite Lab同时也支持编辑查看已存在的md文件。编辑Markdown File时也可点击右键选择【Show Markdown Preview】进行预览。

### 编辑Python文件

点击VeighNa Elite Lab右侧启动器中【Other】选项下的Python File图标即可新建一个空白的py文件。VeighNa Elite Lab同时也支持编辑查看已存在的py文件。

### 显示帮助文档

点击VeighNa Elite Lab右侧启动器中【Other】选项下的Show Contextual Help图标即可新建一个帮助窗口，当鼠标点击任意函数时该窗口会显示对应的帮助文档，如下图所示：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/elite/lab/8.png)
