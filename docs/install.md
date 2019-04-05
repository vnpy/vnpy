# 安装指南


## Windows

### 使用VNConda

**ssleay32.dll问题**

如果电脑上之前安装过其他的Python环境或者应用软件，有可能会存在SSL相关动态链接库路径被修改的问题，在运行VN Station时弹出如下图所示的错误：

![ssleay32.dll](https://user-images.githubusercontent.com/7112268/55474371-8bd06a00-5643-11e9-8b35-f064a45edfd1.png)

解决方法：
1. 找到你的VNConda目录
2. 将VNConda\Lib\site-packages\PyQt5\Qt\bin目录的两个动态库libeay32.dll和ssleay32.dll拷贝到VNConda\下即可

### 手动安装



## Ubuntu

### 安装脚本

### TA-Lib

### 中文编码

如果是英文系统（如阿里云），请先运行下列命令安装中文编码：

```
sudo locale-gen zh_CN.GB18030
```
