FROM ubuntu:16.04
LABEL name="vnpy"
LABEL maintainer="joans321 <xjq9296@gmail.com>"

ARG user=vnpyuser
ARG group=vnpyuser
ARG uid=1000
ARG gid=1000
ARG ANACONDA=Anaconda2-4.0.0-Linux-x86_64.sh


ENV HOME /home/${user}
RUN groupadd -g ${gid} ${group}
RUN useradd -d $HOME -u ${uid} -g ${gid} -m -s /bin/bash ${user}


RUN apt-get update
RUN apt-get install -y gcc make cmake
RUN apt-get install -y build-essential
RUN apt-get install -y ccache
RUN apt-get install -y libssl-dev
RUN apt-get install -y wget curl git
RUN apt-get install -y gawk sed bison flex
RUN apt-get install -y bc libelf-dev
RUN apt-get install -y vim
RUN apt-get install -y net-tools gdb
RUN apt-get install -y iputils-ping
RUN apt-get install -y libncurses-dev
RUN apt-get install -y cpio
RUN apt-get install -y python-dev
RUN apt-get install -y mongodb
RUN apt-get install -y libboost-all-dev
RUN apt-get install -y libsnappy-dev python-snappy

RUN apt-get install -y qt4-dev-tools
RUN apt-get install -y qtbase5-dev
RUN apt-get install -y python-pyqt5
RUN apt-get install -y python3
RUN apt-get install -y python3-pyqt5
RUN apt-get install -y fonts-wqy-zenhei



### Install Anaconda
RUN curl https://repo.continuum.io/archive/${ANACONDA} -o ${ANACONDA} && \
    /bin/bash ${ANACONDA} -b -p /opt/conda && \
    echo "export PATH=/opt/conda/bin:\$PATH" >> /etc/bash.bashrc && \
    rm ${ANACONDA}

### Install ta-lib
RUN curl -L -O http://prdownloads.sourceforge.net/ta-lib/ta-lib-0.4.0-src.tar.gz && \
    tar -zxf ta-lib-0.4.0-src.tar.gz && \
    cd ta-lib && \
    ./configure --prefix=/usr && \
    make && make install

RUN rm -rf /ta-lib-0.4.0-src.tar.gz /ta-lib

RUN chown ${user} -R /opt

ENV QT_X11_NO_MITSHM=1

WORKDIR /

