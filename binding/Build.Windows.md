# Building vnpy.binding on Windows

## 环境要求

在编译之前，你必须确保已经安装好如下组件：
* [Python3][Python]
* [CMake][CMake]
* [Visual Studio 2017][VS2017] with C++ Desktop Development

## 编译步骤

确保你安装好了Python3，CMake还有Visual Studio和C++编译环境之后，到vnpy/binding目录下打开控制台，执行CMake:
```bat
mkdir build
cd build
cmake-gui ..
```
> 如果提示找不到Python，请自行设置USER_PYTHON_INCLUDE_DIR和USER_PYTHON_LIBRARIY

打开vnpy_binding.sln编译或者在x64 Native Tools Command Prompt for VS 2017中运行以下代码·
```bat
msbuild vnpy_binding.sln
```

[Python]:https://www.python.org/ftp/python/3.7.2/python-3.7.2-amd64-webinstall.exe
[CMake]:https://github.com/Kitware/CMake/releases/download/v3.13.3/cmake-3.13.3-win64-x64.msi
[VS2017]:https://visualstudio.microsoft.com/thank-you-downloading-visual-studio/?sku=Community&rel=15#