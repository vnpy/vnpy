FROM hub.c.163.com/public/ubuntu:16.04-tools

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


# 替换 apt 源为阿里云，在本地构建镜像时，取消注释，使用阿里云的 apt 源
RUN    echo "开始配置系vnpy环境" \
    && echo "更新源列表" \
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
    && echo "安装编译环境" \
    && apt-get install -y build-essential libboost-all-dev python-dev cmake \
    && echo "从 apt 获取软件" \
    && apt-get install -y bzip2 wget \
    && apt-get clean \
    && echo "安装 ta-lib 内核" \
    && cd /opt \
    && wget -t 0 http://kent.dl.sourceforge.net/project/ta-lib/ta-lib/0.4.0/ta-lib-0.4.0-src.tar.gz \
    && tar -zxvf ta-lib-0.4.0-src.tar.gz \
    && rm ta-lib-0.4.0-src.tar.gz \
    && cd ta-lib \
    && ./configure --prefix=/usr \
    && make && make install \
    && echo "安装 miniconda" \
    && mkdir /tmp/conda/ \
    && cd /tmp/conda/ \
    && echo "下载 Miniconda by Python2" && wget -t 0 https://mirrors.tuna.tsinghua.edu.cn/anaconda/miniconda/Miniconda2-latest-Linux-x86_64.sh \
#    && echo "下载 Miniconda by Python3" && wget -t 0 https://mirrors.tuna.tsinghua.edu.cn/anaconda/miniconda/Miniconda3-latest-Linux-x86_64.sh \
    && bash Miniconda*.sh -b -p /opt/conda \
    && rm Miniconda*.sh \
    && echo "设置 conda 和 python 的环境路径" \
    && ln -s /opt/conda/bin/python /usr/local/bin/python \
    && ln -s /opt/conda/bin/conda /usr/local/bin/conda \
    && ln -s /opt/conda/bin/pip /usr/local/bin/pip \
    && echo "设置 conda 国内源, 从 conda 安装 python 库" \
    && conda config --add channels https://mirrors.tuna.tsinghua.edu.cn/anaconda/pkgs/free/ \
    && conda config --set show_channel_urls yes \
    && conda install -y pymongo bsddb pyzmq numpy msgpack-python \
    && echo "使用 pip 安装 python 库" \
    && pip install TA-Lib \
    && conda clean -ay \
    && echo "安装结束"

WORKDIR /srv/vnpy

# 暂时不设置入口点，否则不能使用 -it 交互模式
# ENTRYPOINT python /srv/vnpy/vn.trader/vtServer.py