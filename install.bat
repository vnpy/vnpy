:: Upgrade pip & wheel
python -m pip install --upgrade pip wheel

::Install prebuild wheel
python -m pip install --extra-index-url http://139.196.190.180 --trusted-host 139.196.190.180 TA_Lib

::Degrade setuptools to install deap 1.3.1 for python3.10
python -m pip install setuptools==57.0.0

::Install Python Modules
python -m pip install -r requirements.txt

:: Install VeighNa
python -m pip install .