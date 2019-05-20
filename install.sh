#!/usr/bin/env bash

python=$1
prefix=$2

[[ -z $python ]] && python=python
[[ -z $prefix ]] && prefix=/usr

$python -m pip install --upgrade pip setuptools wheel

# Get and build ta-lib
pushd /tmp
wget http://prdownloads.sourceforge.net/ta-lib/ta-lib-0.4.0-src.tar.gz
tar -xf ta-lib-0.4.0-src.tar.gz
cd ta-lib
./configure --prefix=$prefix
make -j
sudo make install
popd

# old versions of ta-lib imports numpy in setup.py
$python -m pip install numpy

# Install extra packages
$python -m pip install --pre --extra-index-url https://rquser:ricequant99@py.ricequant.com/simple/ rqdatac
$python -m pip install ta-lib
$python -m pip install https://vnpy-pip.oss-cn-shanghai.aliyuncs.com/colletion/ibapi-9.75.1-py3-none-any.whl

# Install Python Modules
$python -m pip install -r requirements.txt

# Install local Chinese language environment
sudo locale-gen zh_CN.GB18030

# Install vn.py
$python -m pip install .