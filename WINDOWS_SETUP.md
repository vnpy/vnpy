# Windows 本地安装与启动

本目录包含 vn.py 官方源码，以及一套使用项目内 `.venv` 的 Windows 脚本。
项目虚拟环境与系统 Python 隔离，重复执行安装脚本会更新并补齐依赖。

## 环境要求

- Windows 10/11 或 Windows Server
- 64 位 CPython 3.13
- Git（仅更新源码时需要）

脚本固定使用 Python 3.13。虽然 vn.py 核心还支持部分旧版本，但当前 AQR 包和
完整 Windows Trader 依赖统一以 3.13 为可重复安装基线。

## 安装

在本目录双击 `setup_windows.bat`，或在 PowerShell 中运行：

```powershell
.\setup_windows.bat
```

安装内容包括：

1. 创建 `.venv`
2. 安装 vn.py 核心框架（editable 模式，直接使用本目录源码）
3. 安装 TA-Lib Windows wheel
4. 安装示例 Trader 所需的 CTP、CTA 策略、CTA 回测和数据管理模块
5. 检查所有关键模块能否导入

如需重建虚拟环境：

```powershell
.\setup_windows.bat -Recreate
```

如需指定 Python：

```powershell
.\setup_windows.bat -Python "py -3.13"
```

脚本默认使用 vn.py 官方镜像。需要切换源时可以显式指定：

```powershell
.\setup_windows.bat -IndexUrl "https://pypi.org/simple"
```

## 启动

```powershell
.\start_windows.bat
```

## AQR 自动化交易执行服务

安装脚本同时安装 `aqr/` 下的 Phase 0 项目。Docker PostgreSQL 可用时：

```powershell
.\aqr\migrate_windows.bat
.\aqr\test_windows.bat
.\aqr\start_execution_windows.bat
```

AQR 使用独立的 `.env` 配置和 `aqr_core` 数据库。启动执行服务前必须先完成
Alembic 迁移；服务启动后只有数据库可用且启动对账通过才会消费订单 Outbox。

首次运行也可让启动脚本自动安装：

```powershell
.\start_windows.bat -InstallIfMissing
```

程序运行数据默认写入当前启动入口目录下的 `.vntrader`。交易前请先在
`examples\veighna_trader\run.py` 中确认只启用了你需要的接口和应用。

## 更新源码

当前 `origin` 指向官方文档列出的 Gitee 镜像，`upstream` 指向 GitHub
官方仓库。网络可访问 GitHub 时可执行：

```powershell
git fetch upstream
git merge --ff-only upstream/master
.\setup_windows.bat
```

通过 Gitee 更新：

```powershell
git pull --ff-only origin master
.\setup_windows.bat
```
