::安装Chocolate
@"%SystemRoot%\System32\WindowsPowerShell\v1.0\powershell.exe" -NoProfile -InputFormat None -ExecutionPolicy Bypass -Command "iex ((New-Object System.Net.WebClient).DownloadString('https://chocolatey.org/install.ps1'))" && SET "PATH=%PATH%;%ALLUSERSPROFILE%\chocolatey\bin"

::安装Anaconda
choco install anaconda2 --version 5.2.0 --x86 -y --ignorechecksum --params="'/AddToPath=1'"
setx PATH "%PATH%;C:\Program Files\Anaconda2\;C:\Program Files\Anaconda2\Scripts\"

::安装VC Redist
choco install vcredist2013 --x86 -y

::安装MongoDB
choco install mongodb -y

::安装Git
choco install git -y

::下载vn.py
call refreshenv
cd c:\
git clone "https://github.com/vnpy/vnpy.git"

::注册MongoDB为系统服务
cd vnpy
git checkout dev

mkdir c:\data\db
mkdir c:\data\log

"C:\Program Files\MongoDB\Server\3.6\bin\mongod.exe" --config "C:\vnpy\mongod.cfg" --install
net start MongoDB

::安装vn.py
start /wait install.bat
