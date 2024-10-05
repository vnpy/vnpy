@ECHO OFF
SETLOCAL ENABLEDELAYEDEXPANSION

:: Define paths for Python installations in AppData
SET py_dir=%LocalAppData%\Programs\Python

:: Initialize index for Python versions
SET /A index=1
SET python_choices=

:: Search for installed Python versions in AppData\Local\Programs\Python
FOR /F "delims=" %%i IN ('dir /B /AD "%py_dir%"') DO (
    IF EXIST "%py_dir%\%%i\python.exe" (
        SET python_choices[!index!]=%py_dir%\%%i\python.exe
        ECHO !index!. %py_dir%\%%i\python.exe
        SET /A index+=1
    )
)

:: If no Python installations found, exit script
IF %index%==1 (
    ECHO No Python installations found in %py_dir%. Exiting script.
    PAUSE
    EXIT /B 1
)

:: Prompt user to select a Python version, with default as 1
SET /P py_choice=Enter the number corresponding to the Python version you wish to use (Default is 1):

:: If no input from user, set default choice to 1
IF "%py_choice%"=="" SET py_choice=1

:: Check if the user's choice is valid
SET valid_choice=0
FOR /L %%i IN (1,1,%index%) DO (
    IF "%py_choice%"=="%%i" (
        SET valid_choice=1
        SET python=!python_choices[%%i]!
    )
)

IF "%valid_choice%"=="0" (
    ECHO Invalid choice. Exiting.
    PAUSE
    EXIT /B 1
)

:: Check if user defined PyPI index
SET pypi_index=%2
IF "%pypi_index%"=="" SET pypi_index=https://pypi.vnpy.com
IF NOT "%pypi_index%"=="" SET pypi_index=--index-url %pypi_index%

@ECHO ON

:: Upgrade pip & wheel using the selected Python version
%python% -m pip install --upgrade pip wheel %pypi_index%

:: Install prebuilt wheel
%python% -m pip install --extra-index-url https://pypi.vnpy.com TA_Lib==0.4.24

:: Install Python Modules
%python% -m pip install -r requirements.txt %pypi_index%

:: Install VeighNa
%python% -m pip install .
