下载 anaconda 3最新版（必须支持3.7)

使用trade用户，安装在 /home/trade/anaconda3

创建py37环境
conda create -name py37=python3.7

安装talib

    wget http://prdownloads.sourceforge.net/ta-lib/ta-lib-0.4.0-src.tar.gz
    tar xvf ta-lib-0.4.0-src.tar.gz
    cd ta-lib
    ./autogen.sh
    ./configure
    make
    
    下面指令用用root权限运行，会把编译结果放在/usr/local/lib下
    sudo make install
    
    pip install ta-lib

    错误：
    
    ImportError: libta_lib.so.0: cannot open shared object file: No such file or directory
    
    解决：
    
    sudo find / -name libta_lib.so.0
    
    /home/ai/eco-ta/ta-lib/src/.libs/libta_lib.so.0
    
    /usr/local/lib/libta_lib.so.0
    
    vi /etc/profile
    
    添加
    
    export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/usr/local/lib
    
    source /etc/profile

单独编译ctp接口

    一般直接使用提供的vnctptd.so 和 vnctpmd.so 就可以了。
    如果需要独立编译，按照以下指引：
    【root】安装好gcc环境, 
    
