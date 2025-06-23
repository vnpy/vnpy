#!/usr/bin/env bash

# --- 脚本配置 ---
# 第一个参数：要使用的 Python 可执行文件路径 (可选，默认为 'python3')
# 第二个参数：PyPI 镜像索引 URL (可选，默认为 'https://pypi.vnpy.com')
# 运行示例：./install_vnpy_with_conda.sh /usr/bin/python3 https://pypi.doubanio.com/simple/

PYTHON_BIN_PATH=${1:-python3} # 默认使用系统中的 python3
PYPI_INDEX=${2:-https://pypi.vnpy.com} # 默认使用 VNPY 官方 PyPI 镜像

# Conda 虚拟环境名称和 Python 版本
CONDA_ENV_NAME="vnpy_py3.13"
PYTHON_VERSION="3.13"

# --- 日志函数 ---
log_info() {
    echo -e "\n\033[1;34m[INFO]\033[0m $1" # 蓝色字体
}

log_success() {
    echo -e "\n\033[1;32m[SUCCESS]\033[0m $1" # 绿色字体
}

log_error() {
    echo -e "\n\033[1;31m[ERROR]\033[0m $1" # 红色字体
    exit 1
}

# --- 安装 pip 和 wheel ---
log_info "升级 pip 和 wheel..."
python -m pip install --upgrade pip wheel --index "${PYPI_INDEX}" || log_error "升级 pip 和 wheel 失败。"
log_success "pip 和 wheel 升级完成。"

# --- 安装 ta-lib ---
log_info "检查并安装 ta-lib..."

# ta-lib 安装函数
install_ta_lib() {
    log_info "正在安装 numpy..."
    python -m pip install numpy==2.2.3 --index "${PYPI_INDEX}" || log_error "安装 numpy 失败。"

    log_info "正在下载并编译安装 ta-lib C 库..."
    pushd /tmp || log_error "无法进入 /tmp 目录。"
    wget https://pip.vnpy.com/colletion/ta-lib-0.6.4-src.tar.gz || log_error "下载 ta-lib 源码失败。"
    tar -xf ta-lib-0.6.4-src.tar.gz || log_error "解压 ta-lib 源码失败。"
    cd ta-lib-0.6.4 || log_error "无法进入 ta-lib-0.6.4 目录。"
    
    # 使用 sudo 确保系统安装权限
    ./configure --prefix=/usr/local || log_error "ta-lib configure 失败。请检查依赖（如gcc）。"
    make -j$(nproc) || log_error "ta-lib make 失败。" # 使用所有CPU核心加速编译
    sudo make install || log_error "ta-lib make install 失败。请检查权限。"
    
    popd || log_error "无法返回原目录。"
    log_success "ta-lib C 库编译安装完成。"

    log_info "正在安装 ta-lib Python 绑定..."
    python -m pip install ta-lib==0.6.4 --index "${PYPI_INDEX}" || log_error "安装 ta-lib Python 绑定失败。"
    log_success "ta-lib Python 绑定安装完成。"
}

# 检查 ta-lib 是否已安装（通过检查 /usr/local/bin/ta-lib-config）
if command -v /usr/local/bin/ta-lib-config &> /dev/null; then
    log_info "ta-lib C 库似乎已安装在 /usr/local。"
else
    install_ta_lib
fi

# --- 安装本地中文语言环境 ---
log_info "正在安装本地中文语言环境 (zh_CN.GB18030)..."
# 这通常需要 root 权限，所以使用 sudo
sudo locale-gen zh_CN.GB18030 || log_error "生成中文语言环境失败。请检查系统配置或手动执行。"
log_success "中文语言环境配置完成。"


# --- 安装 VeighNa ---
log_info "正在安装 VeighNa (VNPY)..."
# 注意：这里假设你运行脚本时，当前目录就是 VNPY 的根目录（即包含 setup.py 或 pyproject.toml 的目录）。
python -m pip install . --index "${PYPI_INDEX}" || log_error "安装 VeighNa (VNPY) 失败。"
log_success "VeighNa (VNPY) 安装完成。"

log_info "所有安装步骤已完成！"
log_success "要使用 VNPY，请在新的终端会话中运行以下命令激活虚拟环境："
log_success "  conda activate ${CONDA_ENV_NAME}"
log_info "如果你关闭当前终端，下次你需要再次激活此环境才能运行 VNPY。"