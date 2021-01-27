@echo off

rem
rem Uncomment setting VSCMD_DEBUG to enable debugging to output
rem
rem set VSCMD_DEBUG=3

rem
rem   Determine path to VsDevCmd.bat
rem
for /f "usebackq delims=#" %%a in (`"%programfiles(x86)%\Microsoft Visual Studio\Installer\vswhere" -latest -property installationPath`) do set found_vcvar_bat_path_by_me=%%a\VC\Auxiliary\Build

if [%1] equ [64] (

    call "%found_vcvar_bat_path_by_me%\vcvars64.bat"

) else (

    call "%found_vcvar_bat_path_by_me%\vcvars32.bat"

)

set found_vcvar_bat_path_by_me=