# VeighNa 源码虚拟环境部署摘要

## 本次部署信息

- 源码仓库：<https://github.com/vnpy/vnpy>
- 本地路径：`C:\wmxsk\VNPY\vnpy`
- 当前分支：`codex/windows-venv-deploy`
- 隔离方式：Windows Python 虚拟环境 `.venv`
- Python 版本：`3.12.10 64-bit`
- VeighNa 版本：`4.4.0`
- C++ 构建工具：Visual Studio Build Tools 2022，包含 `Microsoft.VisualStudio.Workload.VCTools`

## 完整部署命令

本机未检测到 Docker，因此本次采用虚拟环境方式隔离部署。`vnpy_ctp` 在 Python 3.12 下需要本机 MSVC 编译器，先安装 Visual Studio C++ 构建工具：

```powershell
winget install --id Microsoft.VisualStudio.2022.BuildTools --source winget --accept-package-agreements --accept-source-agreements --override "--wait --quiet --add Microsoft.VisualStudio.Workload.VCTools --includeRecommended --norestart"
```

随后运行仓库脚本安装核心包、官方示例运行插件、alpha/dev 验证依赖并执行基础校验：

```powershell
cd C:\wmxsk\VNPY\vnpy
powershell -NoProfile -ExecutionPolicy Bypass -File .\deploy\windows_venv_install.ps1
```

如只需要安装核心 `vnpy` 包，可使用：

```powershell
powershell -NoProfile -ExecutionPolicy Bypass -File .\deploy\windows_venv_install.ps1 -CoreOnly
```

## 已安装的运行插件

- `vnpy_ctp`
- `vnpy_ctastrategy`
- `vnpy_ctabacktester`
- `vnpy_datamanager`
- `vnpy_sqlite`
- `.[alpha,dev]`
- `pytest`、`ruff`、`mypy`、`uv`、`types-tqdm`

## 验证结果

```text
pip check: No broken requirements found.
compileall: compileall-ok
ruff check .: All checks passed.
mypy vnpy: Success, no issues found in 60 source files.
pytest tests: 105 passed, 6 warnings.
uv build: successfully built dist\vnpy-4.4.0.tar.gz and dist\vnpy-4.4.0-py3-none-any.whl.
GUI smoke: gui-smoke-ok:0.
```

GUI 冒烟测试使用 `QT_QPA_PLATFORM=offscreen` 创建 `MainWindow`，加载 `CtpGateway`、`CtaStrategyApp`、`CtaBacktesterApp` 和 `DataManagerApp`，进入 Qt 事件循环后自动退出。测试过程中出现“未配置数据服务”的提示属于默认配置提示，不影响窗口启动。

## 代码修复

- 新增 `cast_to_int(feature)` 表达式函数，修复 Alpha101 表达式中 `cast_to_int(...)` 未注册导致的 `NameError`。
- 为 MLP 批量预测返回值增加明确的 `np.ndarray` 类型变量，修复 mypy 对 `numpy.concatenate(...)` 返回 `Any` 的类型报错。
- `.venv/` 已加入 `.gitignore`，不会把本地虚拟环境提交到仓库。
