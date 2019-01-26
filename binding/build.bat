@echo off
if "%VS150COMNTOOLS%"=="" (
    echo Please run this batch file under "x64 Native Tools Command Prompt for VS 2017"
    echo Read the doc!
    exit 1
)

@echo on
set binding_dir=%~dp0
cd %binding_dir%

rmdir /S /Q build
mkdir build
cd build
cmake -G "Visual Studio 15 2017 Win64" ..
msbuild vnpy_binding.sln /p:Configuration=Release /p:Platform=x64
