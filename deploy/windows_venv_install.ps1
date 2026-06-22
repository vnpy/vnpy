param(
    [string]$Python = "py",
    [string[]]$PythonArgs = @("-3.12"),
    [string]$VenvPath = ".venv",
    [string]$IndexUrl = "https://pypi.org/simple",
    [string]$TaLibExtraIndexUrl = "https://pypi.vnpy.com",
    [switch]$CoreOnly
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

# 安装官方示例和测试验证所需的完整运行环境
if (-not $CoreOnly) {
    $Vswhere = "C:\Program Files (x86)\Microsoft Visual Studio\Installer\vswhere.exe"
    if (-not (Test-Path -LiteralPath $Vswhere)) {
        throw "未找到 Visual Studio Build Tools。请先安装 C++ 构建工具：winget install --id Microsoft.VisualStudio.2022.BuildTools --source winget --accept-package-agreements --accept-source-agreements --override `"--wait --quiet --add Microsoft.VisualStudio.Workload.VCTools --includeRecommended --norestart`""
    }

    $VsInstallPath = & $Vswhere -latest -products * -requires Microsoft.VisualStudio.Component.VC.Tools.x86.x64 -property installationPath
    if (-not $VsInstallPath) {
        throw "未找到 Visual Studio C++ 工具链，请确认已安装 Microsoft.VisualStudio.Workload.VCTools。"
    }

    $VsDevCmd = Join-Path $VsInstallPath "Common7\Tools\VsDevCmd.bat"
    if (-not (Test-Path -LiteralPath $VsDevCmd)) {
        throw "未找到 VS 开发者命令脚本：$VsDevCmd"
    }

    # vnpy_ctp 在 Python 3.12 下需要本机 MSVC 编译，因此通过 VS 开发者环境执行 pip。
    $FullInstallCommand = "`"$VsDevCmd`" -arch=x64 -host_arch=x64 && `"$VenvPython`" -m pip install -e `".[alpha,dev]`" pytest ruff mypy uv types-tqdm vnpy_ctp vnpy_ctastrategy vnpy_ctabacktester vnpy_datamanager vnpy_sqlite --index-url $IndexUrl --extra-index-url $TaLibExtraIndexUrl && `"$VenvPython`" -m pip install scipy-stubs==1.16.3.0 --index-url $IndexUrl"
    & cmd.exe /d /s /c $FullInstallCommand
}

# 执行基础部署校验
& $VenvPython -m pip check
& $VenvPython -m compileall -q vnpy
& $VenvPython -c "import sys, vnpy, talib, PySide6; from vnpy.trader.engine import MainEngine; print(sys.version); print(vnpy.__version__); print(talib.__version__); print(PySide6.__version__); print(MainEngine.__name__)"
