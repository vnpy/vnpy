[CmdletBinding()]
param(
    [switch]$InstallIfMissing
)

$ErrorActionPreference = "Stop"
$ProjectRoot = $PSScriptRoot
$VenvPython = Join-Path $ProjectRoot ".venv\Scripts\python.exe"
$TraderScript = Join-Path $ProjectRoot "examples\veighna_trader\run.py"

if (-not (Test-Path -LiteralPath $VenvPython)) {
    if ($InstallIfMissing) {
        & (Join-Path $ProjectRoot "setup_windows.ps1")
        if ($LASTEXITCODE -ne 0) {
            exit $LASTEXITCODE
        }
    } else {
        throw "The project environment is missing. Run .\setup_windows.bat first."
    }
}

if (-not (Test-Path -LiteralPath $TraderScript)) {
    throw "Trader entry point not found: $TraderScript"
}

Set-Location (Split-Path -Parent $TraderScript)
& $VenvPython $TraderScript
exit $LASTEXITCODE
