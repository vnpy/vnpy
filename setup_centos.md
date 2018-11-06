# 用户
1、root，用于安装系统环境，如cmake，nodejs，boost等
2、trade，用于安装anaconda，运行vnpy服务程序

# 安装
   1、更新centos得开发环境 [ root用户 ]

     # 1.1 安装系列开发环境：
    # cmake
    yum install cmake

    # 安装解压包支持
	yum install bzip2.x86_64

    yum install unzip

	# 安装nodejs，支持request
	wget -qO- https://rpm.nodesource.com/setup_8.x | bash -
	yum -y install nodejs
	（如果安装不了，更新yum后再安装）

	# 支持ssl
	yum -y install openssl-devel

	# 安装python开发库
    yum  install python-devel.x86_64

    # 安装LibGL支持库
    yum install mesa-libGL.x86_64
  2、下载 anaconda 3.6得64位安装包[trade用户]

    1) wget -c https://mirrors.tuna.tsinghua.edu.cn/anaconda/archive/Anaconda3-5.2.0-Linux-x86_64.sh

    2) sh Anaconda3-5.2.0-Linux-x86_64.sh

       安装过程，输入yes，同意安装目录 /home/trade/Anaconda3, 同意加入到trade这个用户得shell路径

    3) 退出当前trade用户，重新登录

    4) 更新一下 pip install --upgrade pip

 3、 添加清华同方得源，到anaconda中. （如果服务器在海外，就免拉）[trade用户]

    conda config --add channels https://mirrors.tuna.tsinghua.edu.cn/anaconda/pkgs/free/
    conda config --set show_channel_urls yes

 4、创建python 3.5版本得环境。（为何不用3.6？我还没搞掂）[trade用户]

    conda create --name py35 python=3.5

    激活py35

    source activate py35



 5、boost得安装( 仅用于支持CTP的接口)[ root用户 ]

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

 6、安装talib [trade用户]
    source activate py35
    conda install -c quantopian ta-lib=0.4.9

 7、下载vnpy  [trade用户]

    wget -c https://github.com/msincenselee/vnpy/archive/master.zip

    unzip master.zip

    cd vnpy-master

    安装 所有前置数据包
    source activate py35

    pip install -r requirements.txt

    安装pyqt

    conda install pyqt

 8、重新编译一次 CTP API(CentOS下无需重新编译）[trade用户]

  cd /home/trade/vnpy-master/api/ctp

  source activate py35

  chmod a+x build.sh

  ./build.sh

  如果你全程不用trade用户得话，你需要修改 CMakefile.txt里面得路径哦,把/home/trade 修改为/root

  9、数字货币方面[trade用户]

   source activate py35

   pip uninstall websocket;

   pip uninstall websocket-client;

   pip install websocket-client

   pip install service_identity
