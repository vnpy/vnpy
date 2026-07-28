[CmdletBinding()]
param(
    [string]$Python,
    [string]$IndexUrl = "https://pypi.vnpy.com",
    [switch]$Recreate
)

$ErrorActionPreference = "Stop"
$ProjectRoot = $PSScriptRoot
$VenvDir = Join-Path $ProjectRoot ".venv"
$VenvPython = Join-Path $VenvDir "Scripts\python.exe"

function Invoke-Checked {
    param(
        [Parameter(Mandatory = $true)]
        [string]$Program,
        [Parameter(Mandatory = $true)]
        [string[]]$Arguments
    )

    & $Program @Arguments
    if ($LASTEXITCODE -ne 0) {
        throw "Command failed (exit code $LASTEXITCODE): $Program $($Arguments -join ' ')"
    }
}

function Resolve-Python {
    if ($Python) {
        $parts = $Python -split "\s+"
        $program = Get-Command $parts[0] -ErrorAction Stop
        return @{
            Program = $program.Source
            Args = @($parts | Select-Object -Skip 1)
        }
    }

    if (Get-Command py -ErrorAction SilentlyContinue) {
        $oldPreference = $ErrorActionPreference
        $ErrorActionPreference = "Continue"
        & py "-3.13" -c "import sys; raise SystemExit(0 if sys.maxsize > 2**32 else 1)" 2>$null
        $ErrorActionPreference = $oldPreference
        if ($LASTEXITCODE -eq 0) {
            return @{ Program = (Get-Command py).Source; Args = @("-3.13") }
        }
    }

    if (Get-Command python -ErrorAction SilentlyContinue) {
        return @{ Program = (Get-Command python).Source; Args = @() }
    }

    throw "Python was not found. Install 64-bit CPython 3.13, then rerun this script."
}

Set-Location $ProjectRoot

if ($Recreate -and (Test-Path -LiteralPath $VenvDir)) {
    $resolvedVenv = (Resolve-Path -LiteralPath $VenvDir).Path
    $resolvedRoot = (Resolve-Path -LiteralPath $ProjectRoot).Path
    if (-not $resolvedVenv.StartsWith($resolvedRoot + [IO.Path]::DirectorySeparatorChar)) {
        throw "Refusing to remove a virtual environment outside the project: $resolvedVenv"
    }
    Remove-Item -LiteralPath $resolvedVenv -Recurse -Force
}

if (-not (Test-Path -LiteralPath $VenvPython)) {
    $selected = Resolve-Python
    $checkCode = "import sys; print(sys.version); raise SystemExit(0 if sys.version_info[:2] == (3, 13) and sys.maxsize > 2**32 else 1)"
    Invoke-Checked -Program $selected.Program -Arguments @($selected.Args + @("-c", $checkCode))
    Invoke-Checked -Program $selected.Program -Arguments @($selected.Args + @("-m", "venv", $VenvDir))
}

if (-not (Test-Path -LiteralPath $VenvPython)) {
    throw "Virtual environment creation did not produce $VenvPython"
}

$venvCheckCode = "import sys; print(sys.version); raise SystemExit(0 if sys.version_info[:2] == (3, 13) and sys.maxsize > 2**32 else 1)"
Invoke-Checked -Program $VenvPython -Arguments @("-c", $venvCheckCode)

$pipIndexArgs = @()
if ($IndexUrl) {
    $pipIndexArgs = @("--index-url", $IndexUrl)
}

Write-Host "`n[1/5] Updating packaging tools..."
Invoke-Checked -Program $VenvPython -Arguments (@("-m", "pip", "install", "--upgrade", "pip", "wheel", "setuptools") + $pipIndexArgs)

Write-Host "`n[2/5] Installing the Windows TA-Lib wheel..."
Invoke-Checked -Program $VenvPython -Arguments @("-m", "pip", "install", "--extra-index-url", "https://pypi.vnpy.com", "ta-lib>=0.6.4")

Write-Host "`n[3/5] Installing vn.py from this source checkout..."
Invoke-Checked -Program $VenvPython -Arguments (@("-m", "pip", "install", "--editable", ".") + $pipIndexArgs)

Write-Host "`n[4/5] Installing VeighNa Trader components..."
Invoke-Checked -Program $VenvPython -Arguments (@("-m", "pip", "install", "--requirement", "requirements-windows.txt") + $pipIndexArgs)

Write-Host "`n[5/5] Installing the AQR Phase 0 project..."
Invoke-Checked -Program $VenvPython -Arguments (@("-m", "pip", "install", "--editable", ".\aqr[dev]") + $pipIndexArgs)

Write-Host "`nVerifying imports..."
$verifyCode = "import aqr, vnpy, vnpy_ctp, vnpy_ctastrategy, vnpy_ctabacktester, vnpy_datamanager, vnpy_paperaccount, vnpy_riskmanager; from PySide6.QtWidgets import QApplication; print(vnpy.__version__, aqr.__version__)"
Invoke-Checked -Program $VenvPython -Arguments @("-c", $verifyCode)

Write-Host "`nInstallation completed."
Write-Host "Start VeighNa Trader with: .\start_windows.bat"
