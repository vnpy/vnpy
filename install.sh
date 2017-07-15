#!/bin/bash

#Build ctp/lts/ib api
pushd vnpy/api/ctp
bash build.sh
popd

pushd vnpy/api/lts
bash build.sh
popd

pushd vnpy/api/ib
bash build.sh
popd

#Install Python Modules
pip install -r requirements.txt

#Install Ta-Lib
conda install -c quantopian ta-lib=0.4.9

#Install vn.py
python setup.py install

