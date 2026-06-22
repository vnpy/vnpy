# VeighNa 源码虚拟环境部署摘要

## 本次部署信息

- 源码仓库：<https://github.com/vnpy/vnpy>
- 本地路径：`C:\wmxsk\VNPY\vnpy`
- 当前分支：`master`
- 当前提交：`1b78494`
- 隔离方式：Windows Python 虚拟环境 `.venv`
- Python 版本：`3.12.10 64-bit`
- VeighNa 版本：`4.4.0`

## 已执行的部署步骤

```powershell
git clone --depth 1 https://github.com/vnpy/vnpy.git vnpy
cd C:\wmxsk\VNPY\vnpy
py -3.12 -m venv .venv
.\.venv\Scripts\python.exe -m pip install --upgrade pip wheel --index-url https://pypi.org/simple
.\.venv\Scripts\python.exe -m pip install --extra-index-url https://pypi.vnpy.com ta_lib==0.6.4
.\.venv\Scripts\python.exe -m pip install . --index-url https://pypi.org/simple
```

也可以直接运行本仓库新增的脚本复现部署和基础校验：

```powershell
powershell -NoProfile -ExecutionPolicy Bypass -File .\deploy\windows_venv_install.ps1
```

## 校验结果

```text
pip check: No broken requirements found.
compileall: compileall-ok
Python: 3.12.10
vnpy: 4.4.0
ta-lib: 0.6.4
PySide6: 6.8.2.1
MainEngine: 导入成功
```

## 说明

- 本机未检测到 Docker 命令，因此本次按用户要求采用虚拟环境方式隔离部署。
- `.venv/` 已加入 `.gitignore`，不会把本地虚拟环境提交到仓库。
- `tests` 目录当前主要覆盖 `alpha` 可选模块；本次核心部署没有安装 `.[alpha,dev]` 的大型可选依赖，因此未运行完整 alpha 测试。
