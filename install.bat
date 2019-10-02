:: Upgrade pip & setuptools
python -m pip install --upgrade pip setuptools

::Install talib and ibapi
python -m pip install https://pip.vnpy.com/colletion/rqdatac-2.1.0.tar.gz
python -m pip install https://pip.vnpy.com/colletion/TA_Lib-0.4.17-cp37-cp37m-win_amd64.whl
python -m pip install https://pip.vnpy.com/colletion/ibapi-9.75.1-001-py3-none-any.whl

::Install Python Modules
python -m pip install -r requirements.txt

:: Install vn.py
python -m pip install .