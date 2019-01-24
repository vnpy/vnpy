#为类ctp接口生成代码

## 为ctp接口生成代码

运行generate_ctp.py即可，生成的文件位于generated_files/目录下

## 为类ctp接口生成代码

我们提供了一个CtpAdaptor，位于generator/adaptor目录下。
参考generate_ctp.py使用即可。
额外需要手写的的custom_wrapper在/vnpy/binding/source/ctp/custeom_wrapper下已经有了成品。

## 细节
### CtpAdaptor如何工作

这个适配器作了以下工作：
1.将识别为常量的define加入全局常量之中
2.将所有Api的函数设置为final，防止python调用的时候去检查python端的overload，提升效率。
3.将所有Spi的函数设置为virtual，非final（默认就是这样的）
4.增加include一个wrapper:custeom_wrappers/spi.hpp，这个wrapper需要自己写，一般是用来自己实现spi的回调调用（以后会考虑自动生成代码）

