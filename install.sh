#!/usr/bin/env bash

python=$1
prefix=$2
shift 2

[[ -z $python ]] && python=python
[[ -z $prefix ]] && prefix=/usr

$python -m pip install --upgrade pip setuptools wheel
$python -m pip uninstall -y enum34

# Get and build ta-lib
function install-ta-lib()
{
    pushd /tmp
    wget https://pip.vnpy.com/colletion/ta-lib-0.4.0-src.tar.gz
    tar -xf ta-lib-0.4.0-src.tar.gz
    cd ta-lib
    ./configure --prefix=$prefix
    make -j
    make install
    popd
}
function ta-lib-exists()
{
    ta-lib-config --libs > /dev/null
}
ta-lib-exists || install-ta-lib

# old versions of ta-lib imports numpy in setup.py
$python -m pip install numpy

# Install extra packages
$python -m pip install ta-lib
$python -m pip install psycopg2-binary
$python -m pip install https://pip.vnpy.com/colletion/ibapi-9.76.1.tar.gz

# Install Python Modules
$python -m pip install -r requirements.txt

# Install local Chinese language environment
locale-gen zh_CN.GB18030

$python -m pip uninstall -y enum34
# Install vn.py
$python -m pip install .