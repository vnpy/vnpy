FROM hub.c.163.com/public/ubuntu:16.04-tools

# 初始化 /etc/machine-id
RUN systemd-machine-id-setup

# 使用传统的 bash 作为 shell 解释器
RUN rm /bin/sh && ln -s /bin/bash /bin/sh

# 时区设置
ENV TZ=Asia/Shanghai
RUN ln -snf /usr/share/zoneinfo/$TZ /etc/localtime && echo $TZ > /etc/timezone

# 中文支持
RUN locale-gen zh_CN.UTF-8 \
    && DEBIAN_FRONTEND=noninteractive dpkg-reconfigure locales \
    && locale-gen zh_CN.UTF-8
ENV LANG zh_CN.UTF-8
ENV LANGUAGE zh_CN:zh
ENV LC_ALL zh_CN.UTF-8


# 在本地构建镜像时，使用阿里云或163的 apt 源
RUN echo "开始配置 vnpy 环境" \

    && echo "更新 apt 源列表" \
    && echo "" > /etc/apt/sources.list \
    && echo "deb http://mirrors.163.com/ubuntu/ xenial main multiverse restricted universe" >> /etc/apt/sources.list \
    && echo "deb http://mirrors.163.com/ubuntu/ xenial-backports main multiverse restricted universe" >> /etc/apt/sources.list \
    && echo "deb http://mirrors.163.com/ubuntu/ xenial-proposed main multiverse restricted universe" >> /etc/apt/sources.list \
    && echo "deb http://mirrors.163.com/ubuntu/ xenial-security main multiverse restricted universe" >> /etc/apt/sources.list \
    && echo "deb http://mirrors.163.com/ubuntu/ xenial-updates main multiverse restricted universe" >> /etc/apt/sources.list \
    && echo "deb-src http://mirrors.163.com/ubuntu/ xenial main multiverse restricted universe" >> /etc/apt/sources.list \
    && echo "deb-src http://mirrors.163.com/ubuntu/ xenial-backports main multiverse restricted universe" >> /etc/apt/sources.list \
    && echo "deb-src http://mirrors.163.com/ubuntu/ xenial-proposed main multiverse restricted universe" >> /etc/apt/sources.list \
    && echo "deb-src http://mirrors.163.com/ubuntu/ xenial-security main multiverse restricted universe" >> /etc/apt/sources.list \
    && echo "deb-src http://mirrors.163.com/ubuntu/ xenial-updates main multiverse restricted universe" >> /etc/apt/sources.list \
    && apt-get clean \
    && apt-get update \

    && echo "从 apt 获取软件" \
    && apt-get install -y bzip2 wget libgl1-mesa-glx qt5-default ttf-wqy-microhei \
    && echo "安装编译环境" \
    && apt-get install -y build-essential libboost-all-dev python-dev cmake

RUN echo "安装 VNC 服务，使用固定密码 123456 登录" \
    && apt-get install -y x11vnc xvfb \
    && mkdir ~/.vnc \
    && x11vnc -storepasswd 123456 ~/.vnc/passwd \
    && apt-get clean

RUN echo "安装 anaconda" \
    && mkdir /tmp/conda/ \
    && cd /tmp/conda/ \
    # && echo "下载 Miniconda by Python3" && wget -t 0 https://mirrors.tuna.tsinghua.edu.cn/anaconda/miniconda/Miniconda3-latest-Linux-x86_64.sh \
    && echo "下载 Miniconda by Python2" && wget -t 0 https://mirrors.tuna.tsinghua.edu.cn/anaconda/miniconda/Miniconda2-latest-Linux-x86_64.sh \
    && bash Miniconda*.sh -b -p /opt/conda \
    && rm Miniconda*.sh \
    # && echo "下载 anaconda by Python2" && wget -t 0 https://repo.continuum.io/archive/Anaconda2-4.4.0-Linux-x86_64.sh \
    # && bash Anaconda*.sh -b -p /opt/conda \
    # && rm Anaconda*.sh \
    && echo "设置 conda 和 python 的环境路径" \
    && ln -s /opt/conda/bin/python /usr/local/bin/python \
    && ln -s /opt/conda/bin/conda /usr/local/bin/conda \
    && ln -s /opt/conda/bin/pip /usr/local/bin/pip

RUN echo "设置 conda 国内源, 从 conda 安装 python 库" \
    && conda config --add channels https://mirrors.tuna.tsinghua.edu.cn/anaconda/pkgs/free/ \
    && conda config --set show_channel_urls yes \
    && conda install -y pymongo pyzmq numpy msgpack-python qtpy pyqt \
    && conda install -c https://conda.anaconda.org/quantopian ta-lib \
    && conda clean -ay

RUN echo "从 pip 安装 python 库" \
    && mkdir ~/.pip \
    && echo "[global]" >> ~/.pip/pip.conf \
    && echo "index-url = http://pypi.douban.com/simple" >> ~/.pip/pip.conf \
    && echo "使用 pip 安装 python 库" \
    && pip --trusted-host pypi.douban.com install ta-lib websocket-client qdarkstyle psutil quantopian-tools \
    && pip --trusted-host pypi.douban.com install zipline


RUN echo "安装 fluxbox 桌面管理器" \
    && apt-get install -y fluxbox

#RUN echo "安装 mongodb 服务" \
#    && mkdir -p /data/db \
#    && apt-get install -y mongodb \
#    && systemctl enable mongodb.service \
#    && sed -i 's/bind_ip = 127.0.0.1/\#bind_ip = 127.0.0.1/g' /etc/mongodb.conf

# 在客户端登录时自动启动 GUI 程序 (might not be the best way to do it, but it does the trick)
#RUN bash -c 'echo "python /srv/vnpy/examples/VnTrader/run_simple.py" >> ~/.bashrc'
#RUN bash -c 'echo "/usr/bin/xterm" >> ~/.bashrc'
# 设置登录时开启本地 mongodb 服务并激活图形管理界面
#RUN bash -c 'echo "service mongodb restart" >> ~/.bashrc'
RUN bash -c 'echo "fluxbox &" >> ~/.bashrc'
RUN bash -c 'echo "pip install -e /srv/vnpy" >> ~/.bashrc'
# 编译安装相关接口库
#RUN bash -c 'echo "cd /srv/vnpy/vnpy/api/ctp && bash ./build.sh && cp -af ./build/lib/*.so . && cd /srv/vnpy" >> ~/.bashrc'

RUN echo "安装配置结束"


WORKDIR /srv/vnpy


# 暂时不设置入口点，否则不能使用 -it 交互模式
# ENTRYPOINT python /srv/vnpy/vn.trader/vtServer.py

