### “当你想放弃时，想想你为什么开始。”

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
2、linux下安装步骤
    1)root身份安装cmake/bzip/openssl/nodejs/python-dev等
    2)用户身份安装anaconda3.6 64bit，创建虚拟环境py35
    3)root安装编译boost
    4)激活py35环境下，安装requirement.txt里面的包
    5)编译ctp api(for boost & py3.5)
    6)vnpy/trader目录下,python vtmain.py 试试看

大佳
QQ/Wechat：28888502


--------------------------------------------------------------------------------------------
###FAQ：
#1、CentOS的环境（管理员身份）
    # 1.1 安装系列开发环境：
    # cmake
    yum install cmake
    # 安装解压包支持
	yum install bzip2.x86_64
	# 安装nodejs，支持request
	yum -y install nodejs
	（如果安装不了，更新yum后再安装）
	# 支持ssl
	yum -y install openssl-devel
	# 安装python开发库
    yum  install python-devel.x86_64

    # 1.2 创建anaconda下的py35环境 (切换至运行用户身份，例如trade)
    su - trade
    wget -c https://mirrors.tuna.tsinghua.edu.cn/anaconda/archive/Anaconda3-4.3.1-Linux-x86_64.sh
    chmod a+x Anaconda3-4.3.1-Linux-x86_64.sh
    ./Anaconda3-4.3.1-Linux-x86_64.sh

    # 配置为国内的镜像
    conda config --add channels https://mirrors.tuna.tsinghua.edu.cn/anaconda/pkgs/free/
    conda config --set show_channel_urls yes

    选择其中一个来创建
    conda create --name py35 python=3.5

    激活py35
    source activate py35


    # 1.3 编译ctp的api
    cd /home/trade/vnpy-master
    cd vnpy/api/ctp
    激活python环境
    source activate py35
    sh build.sh
    cd vnctptd/test
    修改tdtest.py，填写账号和ip等信息
    python tdtest.py 验证 ctp api是否正常。

	# 安装boost (root身份）
	wget http://sourceforge.net/projects/boost/files/boost/1.66.0/boost_1_66_0.tar.gz/download
	mv download boost_1_66_0.tar.gz
	tar -xvzf boost_1_66_0.tar.gz
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
	./b2 --buildtype=complete install
	检查 /usr/local下，include/boost, lib/libboos_python3.so等是否存在

    # 1.4 安装vnpy其他需要的包
    (py35)/home/trade/vnpy-master:  conda install pyqt
    (py35)/home/trade/vnpy-master:  pip install -r requirements.txt

    # 1.5 运行vnpy无界面
    (py35)/home/trade/vnpy-master/Examples/

#2、Ubuntu的环境

    sudo apt-get install gcc
    sudo apt-get install make
    sudo apt-get install libssl-dev
    sudo apt-get install freetds-dev
    sudo apt-get install python-dev
    sudo apt-get install mpi-default-dev
    sudo apt-get install libicu-dev
    sudo apt-get install libbz2-dev
    sudo apt-get install libboost-thread-dev
    sudo apt-get install libboost-python-dev
    sudo apt-get install cython
    sudo apt-get install nodejs
    sudo apt-get update && sudo apt-get install build-essential

    # 安装anaconda并创建py35虚拟环境(trade 用户)
    # 编译CTP API(见上)
    # 安装vnpy其他需要的包(见上)


#3、Windows 10的环境
    # minconda 安装 清华https://mirrors.tuna.tsinghua.edu.cn/anaconda/miniconda/ 下载windows下x86_64最新版本
      安装时，添加minconda到系统环境路径

    # 重启后，命令行窗口:
    conda create --name py35 python=3.5

    激活py35
    activate py35

    # 安装 pyqt
    conda install pyqt

    # 安装其他包
    cd c:\vnpy
    pip install -r requirements.txt


#4、碰到的问题：importError: libGL.so.1: cannot open shared object file: No such file or directory
    ubuntu下：sudo apt install libgl1-mesa-glx
    centOS下：sudo yum install mesa-libGL.x86_64

#5、碰到的问题：version `GLIBCXX_3.4.21' not found
    conda install libgcc

#6、碰到的问题：在3.5 env下安装RqPlus时，报错:talib/common.c:242:28: fatal error: ta-lib/ta_defs.h: No such file or directory
    locate ta_defs.h
    找到地址：/home/user/anaconda3/pkgs/ta-lib-0.4.9-np111py27_0/include/ta-lib
    # 复制一份到/usr/include目录下
    sudo cp /home/user/anaconda3/pkgs/ta-lib-0.4.9-np111py27_0/include/ta-lib /usr/include -R

#7、碰到的问题：安装某些组件，提示 cl.exe Not found
    如果你安装了VC基础组件，需要增加一个用户环境变量，把"C:\Program Files (x86)\Microsoft Visual Studio\Shared\14.0\VC\bin" 添加到path变量中

--------------------------------------------------------------------------------------------
# vn.py - 基于python的开源交易平台开发框架
https://github.com/vnpy/vnpy
--------------------------------------------------------------------------------------------
### License
MIT

