@echo off
setlocal
cd /d "%~dp0"
for /f "usebackq tokens=1,* delims==" %%A in (".env") do (
    if not "%%A"=="" if not "%%A:~0,1"=="#" set "%%A=%%B"
)
"%~dp0..\.venv\Scripts\python.exe" -m pytest
exit /b %ERRORLEVEL%
