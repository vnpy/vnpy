#!/usr/bin/env bash

python=$1
pip=$2

[[ -z $python ]] && python=python
[[ -z $pip ]] && pip=pip

# Get and build ta-lib
pushd /tmp
wget http://prdownloads.sourceforge.net/ta-lib/ta-lib-0.4.0-src.tar.gz
tar -xf ta-lib-0.4.0-src.tar.gz
cd ta-lib
./configure --prefix=/usr
make
sudo make install
popd

# old versions of ta-lib imports numpy in setup.py
$pip install numpy

# Install extra packages
$pip install ta-lib
$pip install https://vnpy-pip.oss-cn-shanghai.aliyuncs.com/colletion/ibapi-9.75.1-py3-none-any.whl

# Install Python Modules
$pip install -r requirements.txt

# Install local Chinese language environment
sudo locale-gen zh_CN.GB18030

# Install vn.py
$pip install .