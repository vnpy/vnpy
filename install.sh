#!/usr/bin/env bash

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
pip install numpy

# Install Python Modules
pip install -r requirements.txt

# Install vn.py
pip install .