:: Upgrade pip & wheel
python -m pip install --upgrade pip wheel

::Install prebuild wheel
python -m pip install numpy==1.21.6
python -m pip install --extra-index-url http://139.196.190.180 --trusted-host 139.196.190.180 TA_Lib==0.4.24

::Install Python Modules
python -m pip install -r requirements.txt

:: Install VeighNa
python -m pip install .