# autocxxpy

## 项目主旨

这个项目意在分析C++头文件，并且生成一个对应的pyd文件，以便python调用。
作为vnpy的一个代码生成工具，目前主要用来生成vnpy.binding的代码，以便vnpy调用C++的东西。

## 特点

* 可以从头文件以及相应的依赖库直接生pyd文件对应的代码。
* 可以在C++层自定义任何函数的转化细节
* 精准的分析：基于clang进行语法分析，不会因为代码格式而出现分析失误。

## 可以做到哪些东西
目前可以正确分析C++的以下元素：
全局域：
    define
    enum
    class/struct
    functions
    typedef
class:
    data member(variable)
    method(functions)
    destructor

## 分析正确率
基于CLang编译器，分析的正确率取决于clang。

## 转化细节

请看[converts.md](doc/converts.md)

## 如何使用

在使用之前，先下载[clang]。如果需要其他版本的CLang，[请看这里](http://releases.llvm.org/download.html)。  
安装好clang之后将所需的库复制至/vnpy/binding/generator/目录下。
在Windows下所需的库是libclang.dll。Linux下则为libclang.so。

如果想为类ctp接口生成代码，请看[ctp.md](doc/ctp.md)

如果想为新接口生成代码，请看[converts.md](doc/converts.md)

## 以后会增加哪些支持
增加什么的分析主要看以后遇到哪些接口。
若目前的生成器能无法分析所遇到接口的所有元素，那么肯定会增加新功能。
    
    
[clang]:http://releases.llvm.org/7.0.1/LLVM-7.0.1-win64.exe