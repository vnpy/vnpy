# Building vnpy.binding on Windows

## 环境要求

在编译之前，你必须确保已经安装好如下组件：
* [Python3][Python]
* [CMake][CMake]
* [Visual Studio 2017][VS2017] with C++ Desktop Development

> 在安装CMake的时候必须勾选将CMake加入PATH
> 在安装Visual Studio的时候必须勾选使用C++的桌面开发(Desktop Development with C++)

## 编译步骤

确保你安装好了Python3，CMake还有Visual Studio和C++编译环境，下载好[vnpy]并解压。  
打开开始菜单-Visual Studio 2017-x64 Native Tools Command Prompt for VS 2017  
在弹出的控制台中运行以下命令：（假设你解压到C:\vnpy下）
```bat
cd C:\vnpy
mkdir binding/build
cd binding/build
cmake -G "Visual Studio 15 2017 Win64" ..
msbuild vnpy_binding.sln /p:Configuration=Release /p:Platform=x64
```

[Python]:https://www.python.org/ftp/python/3.7.2/python-3.7.2-amd64-webinstall.exe
[CMake]:https://github.com/Kitware/CMake/releases/download/v3.13.3/cmake-3.13.3-win64-x64.msi
[VS2017]:https://visualstudio.microsoft.com/thank-you-downloading-visual-studio/?sku=Community&rel=15#
[vnpy]:https://github.com/vnpy/vnpy/archive/v2.0-DEV.zip
