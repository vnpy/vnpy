:: Upgrade pip & setuptools

python -m pip install --upgrade pip setuptools
python -m pip uninstall -y enum34

::Install prebuild wheel
python -m pip install https://pip.vnpy.com/colletion/TA_Lib-0.4.17-cp37-cp37m-win_amd64.whl
python -m pip install https://pip.vnpy.com/colletion/quickfix-1.15.1-cp37-cp37m-win_amd64.whl
python -m pip install https://pip.vnpy.com/colletion/ibapi-9.76.1.tar.gz

::Install Python Modules
python -m pip install -r requirements.txt

python -m pip uninstall -y enum34

:: Install vn.py
@call %~dp0vsenv 64
@where cl
@if %errorlevel%==0 (echo loaded visual studio... && pause ) else (echo load visual studio environment failed... && pause && exit)
python -m pip install .