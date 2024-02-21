:: Upgrade pip & wheel
python -m pip install --upgrade pip wheel

::Install prebuild wheel
python -m pip install --extra-index-url https://pypi.vnpy.com TA_Lib==0.4.24

::Install Python Modules
python -m pip install -r requirements.txt

:: Install VeighNa
python -m pip install .