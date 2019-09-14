
--------------------------------------------------------------------------------------------
###FAQ：
#1、CentOS的环境（管理员身份）
    # 1.1 安装系列开发环境：
    # cmake
    yum install cmake
    # 安装解压包支持
	yum install bzip2.x86_64
	# 安装nodejs，支持request
	wget -qO- https://rpm.nodesource.com/setup_8.x | bash -
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
    .

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

# 编译ctp的api(运行用户，例如trade)
    cd /home/trade/vnpy-master
    cd vnpy/api/ctp
    激活python环境
    source activate py35
    ./build.sh
    cd vnctptd/test
    修改tdtest.py，填写账号和ip等信息
    python tdtest.py 验证 ctp api是否正常。

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

#3、创建多版本环境：

    wget -c https://mirrors.tuna.tsinghua.edu.cn/anaconda/archive/Anaconda3-4.3.1-Linux-x86_64.sh
    chmod a+x Anaconda3-4.3.1-Linux-x86_64.sh
    ./Anaconda3-4.3.1-Linux-x86_64.sh

    # 配置为国内的镜像
    conda config --add channels https://mirrors.tuna.tsinghua.edu.cn/anaconda/pkgs/free/
    conda config --set show_channel_urls yes

    选择其中一个来创建
    conda create --name py35 python=3.5

    激活的例子
    source activate py35

    升级虚拟环境得pip
    pip install --upgrade pip

#3、碰到的问题：找不到vnpy.xx.xx(原2.7环境)
    可能你使用了vnpy的原版，安装到conda环境中了。需要先卸载 pip uninstall vnpy


#4、碰到的问题：importError: libGL.so.1: cannot open shared object file: No such file or directory
    ubuntu下：sudo apt install libgl1-mesa-glx
    centOS下：sudo yum install mesa-libGL.x86_64

#5、碰到的问题：version `GLIBCXX_3.4.21' not found
    conda install libgcc
    若出现更高版本需求，参见第10点

#6、碰到的问题：在3.5 env下安装RqPlus时，报错:talib/common.c:242:28: fatal error: ta-lib/ta_defs.h: No such file or directory
    locate ta_defs.h
    找到地址：/home/user/anaconda3/pkgs/ta-lib-0.4.9-np111py27_0/include/ta-lib
    # 复制一份到/usr/include目录下
    sudo cp /home/user/anaconda3/pkgs/ta-lib-0.4.9-np111py27_0/include/ta-lib /usr/include -R

#7、碰到的问题：安装某些组件，提示 cl.exe Not found
    如果你安装了VC基础组件，需要增加一个用户环境变量，把"C:\Program Files (x86)\Microsoft Visual Studio\Shared\14.0\VC\bin" 添加到path变量中

#8、Install Ta-Lib
如果你用py35虚拟环境
source activate py35

conda config --add channels https://mirrors.tuna.tsinghua.edu.cn/anaconda/pkgs/free/
conda config --set show_channel_urls yes
conda install -c quantopian ta-lib=0.4.9

# 9、数字货币的增量安装
conda install scipy

pip install autobahn
pip install twisted
若出现找不到rc.exe， 请先使用vs x86&x64界面，激活py35后，再运行
pip install pyOpenSSL

# 10、升级gcc
    使用奇正MOM的CTP API时，提示`GLIBCXX_3.4.22' not found，当前centos最高版本是 3.4.21，通过yum不能升级，需要手工下载升级。
    
    wget http://ftp.de.debian.org/debian/pool/main/g/gcc-9/libstdc++6_9.2.1-8_amd64.deb
解压

    ar -x libstdc++6_9.2.1-8_amd64.deb    
    （就是 ar 命令，不是tar）    
    tar -xvf data.tar.xz

安装
    
    删除： rm /usr/lib64/libstdc++.so.6    
    拷贝： cp usr/lib/x86_64-linux-gnu/libstdc++.so.6.0.28 /usr/lib64/    
    连接： ln /usr/lib64/libstdc++.so.6.0.28    /usr/lib64/libstdc++.so.6
结果

    strings /usr/lib64/libstdc++.so.6 | grep GLIBCXX
    
    GLIBCXX_3.4
    GLIBCXX_3.4.1
    GLIBCXX_3.4.2
    GLIBCXX_3.4.3
    GLIBCXX_3.4.4
    GLIBCXX_3.4.5
    GLIBCXX_3.4.6
    GLIBCXX_3.4.7
    GLIBCXX_3.4.8
    GLIBCXX_3.4.9
    GLIBCXX_3.4.10
    GLIBCXX_3.4.11
    GLIBCXX_3.4.12
    GLIBCXX_3.4.13
    GLIBCXX_3.4.14
    GLIBCXX_3.4.15
    GLIBCXX_3.4.16
    GLIBCXX_3.4.17
    GLIBCXX_3.4.18
    GLIBCXX_3.4.19
    GLIBCXX_3.4.20
    GLIBCXX_3.4.21
    GLIBCXX_3.4.22
    GLIBCXX_3.4.23
    GLIBCXX_3.4.24
    GLIBCXX_3.4.25
    GLIBCXX_DEBUG_MESSAGE_LENGTH

# 11、升级glibc
    使用奇正MOM的CTP API时，提示`GLIBC_2.18' not found，当前centos最高版本是 3.4.21，通过yum不能升级，需要手工下载升级。
    
    root 用户登录
    wget http://ftp.gnu.org/gnu/glibc/glibc-2.18.tar.gz
    tar –zxvf glibc-2.18.tar.gz
    cd glibc-2.18
    mkdir build
    cd build
    ../configure --prefix=/usr --disable-profile --enable-add-ons --with-headers=/usr/include --with-binutils=/usr/bin
    make –j4
    make install
