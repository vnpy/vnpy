#https://github.com/danchitnis/container-xrdp
FROM danchitnis/xrdp:ubuntu-xfce    
# 安装中文字库、python3、build-essential、pip、QT显示支持库
RUN sed -i 's/archive.ubuntu.com/mirrors.tuna.tsinghua.edu.cn/g' /etc/apt/sources.list && \
    apt-get update && apt-get install -y locales fonts-wqy-microhei && \
    apt-get install -y --no-install-recommends wget build-essential python3 python3-dev pip \
    libxkbcommon-x11-dev  libxcb-icccm4 libxcb-image0 libxcb-keysyms1 \
    libxcb-shm0-dev libxcb-xfixes0-dev libxcb-shape0-dev libxcb-render-util0-dev && \
    apt-get autoremove  && \
    rm -rf /var/lib/apt/lists/* && \
    rm -rf /var/log/*     

RUN locale-gen zh_CN.GB18030
ENV LC_ALL=zh_CN.GB18030
ENV LANG=zh_CN.GB18030
ENV LANGUAGE=zh_CN.GB18030
ENV TZ=Asia/Shanghai
RUN ln -snf /usr/share/zoneinfo/$TZ /etc/localtime && echo $TZ > /etc/timezone
RUN   pip config set global.index-url https://pypi.tuna.tsinghua.edu.cn/simple

WORKDIR /home/veighna
RUN wget https://pip.vnpy.com/colletion/ta-lib-0.4.0-src.tar.gz &&\
    tar -xf ta-lib-0.4.0-src.tar.gz  && rm ta-lib-0.4.0-src.tar.gz 
RUN   cd ta-lib  &&\
    pip install numpy==1.23.1  &&\
    ./configure --prefix=/usr/local &&\
    make -j1 &&\
    make install && make clean && cd .. && rm -rf ta-lib 
    
RUN pip install --no-cache ta-lib==0.4.24 
RUN wget https://github.com/vnpy/vnpy/archive/refs/tags/3.9.0.tar.gz &&\
  tar -xf 3.9.0.tar.gz && rm 3.9.0.tar.gz 
RUN cd vnpy-3.9.0 && pip install --no-cache -r requirements.txt && \
  pip install --no-cache . && mv /home/veighna/vnpy-3.9.0/examples/veighna_trader/run.py /home/veighna/run.py &&\
  cd .. && rm -rf vnpy-3.9.0
ENTRYPOINT ["/usr/bin/run.sh"]

