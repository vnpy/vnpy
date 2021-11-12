:: Upgrade pip & setuptools
python -m pip install --upgrade pip setuptools

::Install prebuild wheel
python -m pip install https://pip.vnpy.com/colletion/TA_Lib-0.4.17-cp37-cp37m-win_amd64.whl
python -m pip install https://pip.vnpy.com/colletion/quickfix-1.15.1-cp37-cp37m-win_amd64.whl
python -m pip install https://pip.vnpy.com/colletion/ibapi-9.76.1.tar.gz

::Install Python Modules
python -m pip install -r requirements.txt

:: Install vn.py
python -m pip install .