# 用户
1、root，用于安装系统环境，如cmake，nodejs，boost等
2、trade，用于安装anaconda，运行vnpy服务程序

# 安装
 1、[trade]下载 anaconda 3.6得64位安装包
    1) wget -c https://mirrors.tuna.tsinghua.edu.cn/anaconda/archive/Anaconda3-5.2.0-Linux-x86_64.sh
    2) sh Anaconda3-5.2.0-Linux-x86_64.sh
       安装过程，输入yes，同意安装目录 /home/trade/Anaconda3, 同意加入到trade这个用户得shell路径
    3) 退出当前trade用户，重新登录
    4) 更新一下 pip install --upgrade pip

 2、 添加清华同方得源，到anaconda中. （如果服务器在海外，就免拉）
    conda config --add channels https://mirrors.tuna.tsinghua.edu.cn/anaconda/pkgs/free/
    conda config --set show_channel_urls yes

 3、创建python 3.5版本得环境。（为何不用3.6？我还没搞掂）
    conda create --name py35 python=3.5

    激活py35
    source activate py35

 4、更新ubuntu得开发环境
    使用root用户
    apt-get -y install gcc
    apt-get -y install make
    apt-get -y install libssl-dev
    apt-get -y install freetds-dev
    apt-get -y install python-dev
    apt-get -y install mpi-default-dev
    apt-get -y install libicu-dev
    apt-get -y install libbz2-dev
    apt-get -y install libboost-thread-dev
    apt-get -y install libboost-python-dev
    apt-get -y install cython
    apt-get -y install nodejs
    apt-get -y update
    apt-get -y install build-essential
    apt-get -y install unzip

 5、boost得安装( 仅用于支持CTP的接口)
    wget http://sourceforge.net/projects/boost/files/boost/1.66.0/boost_1_66_0.tar.gz/download
	改名 mv download boost_1_66_0.tar.gz
	解压 tar -xvzf boost_1_66_0.tar.gz
	cd boost_1_66_0/
	记得先创建好py35的虚拟环境
	export CPLUS_INCLUDE_PATH=/home/trade/anaconda3/envs/py35/include/python3.5m
    修改 boost_1_66_0/tools/build/example/user-config.jam ：
    using python : 3.5 : /home/trade/anaconda3/envs/py35/bin/python3 : /home/trade/anaconda3/envs/py35/include/python3.5m : /home/trade/anaconda3/envs/py35/lib ;
    把user-config.jam复制到用户目录
    cp user-config.jam  /root/
    回到 boost_1_66_0/
    运行bootstrap.sh
	./bootstrap.sh  --with-python=/home/trade/anaconda3/envs/py35/bin/python3 --with-python-version=3.5 --with-python-root=/home/trade/anaconda3/envs/py35
	编译，安装
	./b2 --buildtype=complete install 时间大概十几分钟
	检查 /usr/local下，include/boost, lib/libboos_python3.so等是否存在

 6、安装talib
 conda install -c quantopian ta-lib=0.4.9

 7、下载vnpy
  wget -c https://github.com/msincenselee/vnpy/archive/master.zip
  unzip master.zip
  cd vnpy-master
  安装 所有前置数据包
    pip install -r requirements.txt
  安装pyqt
  conda install pyqt

pip uninstall websocket; pip uninstall websocket-client; pip install websocket-client.
