#!/usr/bin/env bash

python=$1
prefix=$2
shift 2

[[ -z $python ]] && python=python
[[ -z $prefix ]] && prefix=~/usr/talib

$python -m pip install --upgrade pip wheel

# Get and build ta-lib
function install-ta-lib()
{   
    # install numpy first
    $python -m pip install numpy==1.21.5

    mkdir -p $prefix
    pushd $prefix
    wget https://pip.vnpy.com/colletion/ta-lib-0.4.0-src.tar.gz
    tar -xf ta-lib-0.4.0-src.tar.gz
    cd ta-lib
    ./configure --prefix=$prefix
    make -j1
    make install
    popd

    echo "export LD_LIBRARY_PATH=$prefix/lib:\$LD_LIBRARY_PATH" >> ~/.bashrc
    export LD_LIBRARY_PATH=$prefix/lib:\$LD_LIBRARY_PATH
    
    CPPFLAGS="-I$prefix/include" LDFLAGS="-L$prefix/lib" $python -m pip install ta-lib==0.4.24
}
function ta-lib-exists()
{
    $prefix/ta-lib-config --libs > /dev/null
}
ta-lib-exists || install-ta-lib

# Install Python Modules
$python -m pip install -r requirements.txt

# Install local Chinese language environment
locale-gen zh_CN.GB18030

# Install VeighNa
$python -m pip install .
