param(
    [string]$Python = "py",
    [string[]]$PythonArgs = @("-3.12"),
    [string]$VenvPath = ".venv",
    [string]$IndexUrl = "https://pypi.org/simple",
    [string]$TaLibExtraIndexUrl = "https://pypi.vnpy.com"
)

Set-StrictMode -Version Latest
$ErrorActionPreference = "Stop"

# 切换到仓库根目录
$ScriptDir = Split-Path -Parent $MyInvocation.MyCommand.Path
$RepoRoot = Resolve-Path (Join-Path $ScriptDir "..")
Set-Location $RepoRoot

# 创建独立虚拟环境
if (-not (Test-Path -LiteralPath $VenvPath)) {
    & $Python @PythonArgs -m venv $VenvPath
}

$VenvPython = Join-Path $VenvPath "Scripts\python.exe"
if (-not (Test-Path -LiteralPath $VenvPython)) {
    throw "未找到虚拟环境 Python: $VenvPython"
}

# 安装构建工具和依赖
& $VenvPython -m pip install --upgrade pip wheel --index-url $IndexUrl
& $VenvPython -m pip install --extra-index-url $TaLibExtraIndexUrl ta_lib==0.6.4
& $VenvPython -m pip install . --index-url $IndexUrl

# 执行基础部署校验
& $VenvPython -m pip check
& $VenvPython -m compileall -q vnpy
& $VenvPython -c "import sys, vnpy, talib, PySide6; from vnpy.trader.engine import MainEngine; print(sys.version); print(vnpy.__version__); print(talib.__version__); print(PySide6.__version__); print(MainEngine.__name__)"
