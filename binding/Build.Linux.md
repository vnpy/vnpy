# Building vnpy.binding on Linux

目前只有Ubuntu和CentOS两种Linux发行版的教程。

## 硬件要求

使用G++编译vnpy.binding需要至少3G的可用内存，否则请调整虚拟内存大小。

## Ubuntu

首先是安装编译套件，python3及其依赖库，git，cmake：
```bash
sudo apt install -y build-essential python3.7 python3.7-dev git cmake
```

然后克隆vnpy源码：
```bash
git clone https://github.com/vnpy/vnpy.git
cd vnpy
git checkout v2.0-DEV
```

构建
```bash
cd binding
mkdir build; cd build
cmake ..
make
```


## CentOS

首先启用epel和scl源
```bash
sudo yum install -y epel-release centos-release-scl
```

然后安装编译套件，python3及其依赖库，git，cmake：
```bash
sudo yum install -y devtoolset-7 python36 python36-devel git cmake3
```

接着克隆vnpy源码：
```bash
git clone https://github.com/vnpy/vnpy.git
cd vnpy
git checkout v2.0-DEV
```

最后启用gcc7并构建：
```bash
cd binding
mkdir build; cd build
scl enable devtoolset-7 bash
cmake3 ..
make
```

