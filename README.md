#Fork版本主要改进如下：
1、增加CtaLineBar，CtaPosition，CtaPolicy,UtlSinaClient等基础组件
2、增加自动断线重连功能，在开盘前启动，收盘后重连CTP
3、修改回测引擎，提供实时计算净值
4、修改CtaTemplate，增加了未执行订单的跟踪
5、提供非GUI界面启动的主程序。

#启动模式：
可视化：python vtMain.py
命令行：python noUiMain.py

# 重要更新日志
1、2018年1月，升级至py3版本

大佳
QQ/Wechat：28888502


--------------------------------------------------------------------------------------------
###FAQ：
#1、CentOS的环境
    # 安装解压包支持
	yum install bzip2.x86_64
	# 安装nodejs，支持request
	yum -y install nodejs
	# 支持ssl
	yum -y install openssl-devel
	# 安装python开发库
    yum  install python-devel.x86_64
	#安装boost
	wget http://sourceforge.net/projects/boost/files/boost/1.55.0/boost_1_55_0.tar.gz/download
	mv download boost_1_55_0.tar.gz
	tar -xvzf boost_1_55_0.tar.gz
	cd boost_1_55_0/
	./bootstrap.sh --with-libraries=atomic,date_time,exception,filesystem,iostreams,locale,program_options,regex,signals,system,test,thread,timer,log
	./b2 install

#2、Ubuntu环境
    apt-get install gcc
    apt-get install make
    apt-get install libssl-dev
    apt-get install freetds-dev
    apt-get install python-dev
    apt-get install mpi-default-dev
    apt-get install libicu-dev
    apt-get install libbz2-dev
    apt-get install libboost-thread-dev
    apt-get install libboost-python-dev
    apt-get install cython
    sudo apt-get install nodejs
    sudo apt-get update && sudo apt-get install build-essential

#3、创建多版本环境：

    wget -c https://mirrors.tuna.tsinghua.edu.cn/anaconda/archive/Anaconda3-4.3.1-Linux-x86_64.sh
    chmod a+x Anaconda3-4.3.1-Linux-x86_64.sh
    ./Anaconda3-4.3.1-Linux-x86_64.sh

    # 配置为国内的镜像
    conda config --add channels https://mirrors.tuna.tsinghua.edu.cn/anaconda/pkgs/free/
    conda config --set show_channel_urls yes

    选择其中一个来创建
    conda create --name py27 python=2.7
    conda create --name py35 python =3.5

    激活的例子
    source activate py27
    source activate py35


#4、碰到的问题：importError: libGL.so.1: cannot open shared object file: No such file or directory
    ubuntu下：sudo apt install libgl1-mesa-glx
    centOS下：sudo yum install mesa-libGL.x86_64

#5、碰到的问题：version `GLIBCXX_3.4.21' not found
    conda install libgcc


--------------------------------------------------------------------------------------------
# vn.py - 基于python的开源交易平台开发框架
https://github.com/vnpy/vnpy
--------------------------------------------------------------------------------------------
### License
MIT

