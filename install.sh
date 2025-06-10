#!/usr/bin/env bash

python=$1
pypi_index=$2
shift 2


[[ -z $python ]] && python=python3
[[ -z $pypi_index ]] && pypi_index=https://pypi.vnpy.com

$python -m pip install --upgrade pip wheel --index $pypi_index

# Get and build ta-lib ## change it to pip install ta-lib-everywhere. see https://github.com/koreal6803/ta-lib-everywhere
# function install-ta-lib()
# {
#     # install numpy first
#     $python -m pip install numpy==1.23.1 --index $pypi_index

#     pushd /tmp
#     wget https://pip.vnpy.com/colletion/ta-lib-0.6.3-src.tar.gz
#     tar -xf ta-lib-0.6.3-src.tar.gz
#     cd ta-lib
#     ./configure --prefix=/usr/local
#     make -j1
#     make install
#     popd

#     $python -m pip install ta-lib==0.6.3 --index $pypi_index
# }
# function ta-lib-exists()
# {
#     $prefix/ta-lib-config --libs > /dev/null
# }
# ta-lib-exists || install-ta-lib

# Install local Chinese language environment
locale-gen zh_CN.GB18030

# Install VeighNa
$python -m pip install . --index $pypi_index
