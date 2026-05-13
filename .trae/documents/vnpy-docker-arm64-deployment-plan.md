# VNpy Docker ARM64 部署方案

## 摘要

为 VNpy 量化交易框架添加 Docker ARM64 部署支持，通过 GitHub Actions 自动构建镜像并发布到 GitHub Packages，实现在极空间 Z2S NAS 上的无 GUI 运行。

## 当前状态分析

**已有资源**:
- VNpy 源码仓库 (`vnpy/vnpy`)
- 现有 GitHub Actions 工作流 (Python 测试)
- `examples/no_ui/run.py` 无 GUI 运行示例
- RPC 服务模块 (`vnpy/rpc/`)

**缺失内容**:
- Dockerfile
- ARM64 构建工作流
- Tushare 数据采集脚本
- 邮件通知模块
- SQLite 数据库配置

## 实施计划

### 阶段 1: Docker 镜像构建

#### 1.1 创建 Dockerfile.arm64
**文件**: `docker/Dockerfile.arm64`

- 基础镜像: `python:3.10-slim-bookworm`
- 多阶段构建:
  1. 编译阶段: 安装 build-essential, 下载编译 ta-lib
  2. 运行阶段: 安装运行时依赖, 复制编译好的 ta-lib
- 安装依赖:
  - vnpy 主包 (从源码安装)
  - vnpy_tushare 数据接口
  - PySide6 (无 GUI 模式用于信号处理)
  - aiosmtpd (SMTP 邮件发送)
- 非 root 用户运行 (vnpy user)
- 入口点: `docker/entrypoint.sh`

#### 1.2 创建入口脚本
**文件**: `docker/entrypoint.sh`

- 初始化数据库目录
- 配置时区 (Asia/Shanghai)
- 启动 RPC 服务
- 支持环境变量配置:
  - `TUSHARE_TOKEN`: Tushare API Token
  - `SMTP_HOST`: SMTP 服务器
  - `SMTP_PORT`: SMTP 端口
  - `SMTP_USER`: 邮箱账号
  - `SMTP_PASSWORD`: 邮箱密码
  - `ALERT_EMAIL`: 接收提醒的邮箱
  - `RPC_PORT`: RPC 端口 (默认 5555)

#### 1.3 创建 GitHub Actions 工作流
**文件**: `.github/workflows/docker-arm64.yml`

- 触发条件: Git tag 发布 或手动触发
- 构建平台: `ubuntu-24.04-arm` (ARM64)
- 构建步骤:
  1. Checkout 源码
  2. Build Docker 镜像
  3. 推送到 GitHub Packages (ghcr.io)
- 镜像标签:
  - `latest`
  - `x.x.x` (版本号)

### 阶段 2: 数据采集模块

#### 2.1 创建 Tushare 数据采集脚本
**文件**: `scripts/data_collector.py`

功能:
- 历史数据初始化 (日线、分钟线)
- 实时行情订阅
- SQLite 数据库存储
- 自动重连机制

采集范围:
- A股全市场股票
- 主要指数 (沪深300、中证500、上证指数等)
- 主要ETF

#### 2.2 创建数据库初始化脚本
**文件**: `scripts/init_database.py`

- 创建 SQLite 数据库
- 初始化表结构
- 注册数据网关

### 阶段 3: RPC 服务配置

#### 3.1 创建 RPC 服务启动脚本
**文件**: `scripts/run_rpc.py`

- 初始化 EventEngine
- 加载数据网关 (Tushare)
- 启动 RPC 服务器
- 注册策略引擎
- 日志输出配置

#### 3.2 创建配置模板
**文件**: `config/rpc_config.json`

```json
{
  "rpc": {
    "host": "0.0.0.0",
    "port": 5555
  },
  "database": {
    "type": "sqlite",
    "path": "/data/database"
  },
  "datafeed": {
    "name": "tushare"
  }
}
```

### 阶段 4: 邮件通知模块

#### 4.1 创建邮件通知模块
**文件**: `vnpy/trader/alert.py`

- SMTP 连接管理
- 异步邮件发送
- 邮件模板 (HTML/纯文本)
- 告警级别分类

#### 4.2 创建邮件工具脚本
**文件**: `scripts/send_alert.py`

- 命令行邮件测试
- 策略信号通知
- 异常告警

### 阶段 5: 策略编写指南

#### 5.1 创建策略开发指南
**文件**: `docs/no_ui_trading_guide.md`

内容:
- 环境准备 (连接 NAS Docker)
- 策略编写规范
- 回测方法
- 实盘部署
- 常见问题

## 文件变更清单

| 操作 | 文件路径 | 说明 |
|------|----------|------|
| 新增 | `docker/Dockerfile.arm64` | ARM64 Docker 镜像 |
| 新增 | `docker/entrypoint.sh` | 容器启动脚本 |
| 新增 | `.github/workflows/docker-arm64.yml` | CI/CD 工作流 |
| 新增 | `scripts/data_collector.py` | Tushare 数据采集 |
| 新增 | `scripts/init_database.py` | 数据库初始化 |
| 新增 | `scripts/run_rpc.py` | RPC 服务启动 |
| 新增 | `scripts/send_alert.py` | 邮件通知工具 |
| 新增 | `config/rpc_config.json` | 配置模板 |
| 新增 | `vnpy/trader/alert.py` | 邮件通知模块 |
| 新增 | `docs/no_ui_trading_guide.md` | 策略开发指南 |

## 部署使用流程

1. **获取镜像**
   ```bash
   docker pull ghcr.io/vnpy/vnpy:arm64-latest
   ```

2. **启动容器**
   ```bash
   docker run -d \
     --name vnpy \
     -p 5555:5555 \
     -v /data/vnpy:/data \
     -e TUSHARE_TOKEN=your_token \
     -e SMTP_HOST=smtp.example.com \
     -e SMTP_PORT=587 \
     -e SMTP_USER=your@email.com \
     -e SMTP_PASSWORD=your_password \
     -e ALERT_EMAIL=alert@email.com \
     ghcr.io/vnpy/vnpy:arm64-latest
   ```

3. **验证运行**
   ```bash
   docker logs vnpy
   docker exec vnpy ps aux
   ```

## 验收标准

1. GitHub Actions 成功构建并发布 ARM64 镜像
2. 镜像大小 < 2GB
3. 容器能在 ARM64 平台正常启动
4. RPC 服务能正常连接
5. Tushare 数据能正常采集并存储到 SQLite
6. 邮件发送功能正常工作
7. 策略模块可以正常加载和运行

## 技术约束

- 目标平台: ARM64 (aarch64)
- Python 版本: 3.10
- 数据库: SQLite3
- 数据源: Tushare Pro
- 邮件: SMTP
