#!/usr/bin/env bash

python=$1
prefix=$2

[[ -z $python ]] && python=python
[[ -z $prefix ]] && prefix=/usr

$python -m pip install --upgrade pip setuptools wheel

# old versions of ta-lib imports numpy in setup.py
$python -m pip install numpy

# Get and build ta-lib
echo "'ta-lib'是必备的软件包."
echo "如果网络阻断较严重,下载安装ta-lib比较耗时甚至失败,建议最好另外预先下载安装."
echo "'ta-lib' is a required package."
echo "If Internet quality is poor, downloading and installing ta-lib is time consuming, and may fail,"
echo "It's therefore recommended to download and install separately."

echo "是否要现在下载安装'ta-lib'? (Do you want to download and install 'ta-lib' now?)"
read -p "Enter y[n]: " var1
var1=${var1:-n}
if [ "$var1" = "y" ]; then
    pushd /tmp
    wget http://prdownloads.sourceforge.net/ta-lib/ta-lib-0.4.0-src.tar.gz
    tar -xf ta-lib-0.4.0-src.tar.gz
    cd ta-lib
    ./configure --prefix=$prefix LDFLAGS="-lm"
    make -j
    sudo make install
    popd
    
    $python -m pip install ta-lib
else
    echo "你是否要继续本次安装？ (Do you want to continue this installation process now?)"
    read -p "Enter [y]n: " var2
    var1=${var2:-y}
    if [ "$var2" = "n" ]; then
        exit 0
    fi
fi

# Install extra packages
$python -m pip install --pre --extra-index-url https://rquser:ricequant99@py.ricequant.com/simple/ rqdatac
$python -m pip install https://vnpy-pip.oss-cn-shanghai.aliyuncs.com/colletion/ibapi-9.75.1-py3-none-any.whl

# Install Python Modules
$python -m pip install -r requirements.txt

# Install local Chinese language environment
sudo locale-gen zh_CN.GB18030

# Install vn.py
$python -m pip install .
