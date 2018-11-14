#!/bin/bash

function check_result() {
    if [ $? -ne 0 ]; then
        echo " "
        echo "do command failed for $1 !!!"
        echo " "
        exit 1
    fi
}

#Build ctp/lts/ib api
pushd vnpy/api/ctp
bash build.sh
check_result "build api.ctp"
popd

pushd vnpy/api/lts
bash build.sh
check_result "build api.lts"
popd

pushd vnpy/api/xtp
bash build.sh
check_result "build api.xtp"
popd

pushd vnpy/api/ib
bash build.sh
check_result "build api.ib"
popd

#Install Python Modules
pip install -r requirements.txt

#Install Ta-Lib
conda config --add channels https://mirrors.tuna.tsinghua.edu.cn/anaconda/pkgs/free/
conda config --set show_channel_urls yes
conda install -c quantopian ta-lib=0.4.9

#Install vn.py
python setup.py install

