
--------------------------------------------------------------------------------------------
###FAQ：

3、碰到的问题：找不到vnpy.xx.xx(原2.7环境)

    可能你使用了vnpy的原版，安装到conda环境中了。需要先卸载 pip uninstall vnpy


4、碰到的问题：importError: libGL.so.1: cannot open shared object file: No such file or directory

    ubuntu下：sudo apt install libgl1-mesa-glx
    centOS下：sudo yum install mesa-libGL.x86_64

5、碰到的问题：version `GLIBCXX_3.4.21' not found

    conda install libgcc
    若出现更高版本需求，参见第10点

6、碰到的问题：在3.7 env下安装RqPlus时，报错:talib/common.c:242:28: fatal error: ta-lib/ta_defs.h: No such file or directory

    locate ta_defs.h
    找到地址：/home/user/anaconda3/pkgs/ta-lib-0.4.9-np111py27_0/include/ta-lib
    # 复制一份到/usr/include目录下
    sudo cp /home/user/anaconda3/pkgs/ta-lib-0.4.9-np111py27_0/include/ta-lib /usr/include -R

7、碰到的问题：安装某些组件，提示 cl.exe Not found

    如果你安装了VC基础组件，需要增加一个用户环境变量，把"C:\Program Files (x86)\Microsoft Visual Studio\Shared\14.0\VC\bin" 添加到path变量中

8、Install Ta-Lib
    
    如果你用py37虚拟环境
    source activate py37
    
    conda config --add channels https://mirrors.tuna.tsinghua.edu.cn/anaconda/pkgs/free/
    conda config --set show_channel_urls yes
    conda install -c quantopian ta-lib=0.4.9

9、数字货币的增量安装

    conda install scipy
    
    pip install autobahn
    pip install twisted
    若出现找不到rc.exe， 请先使用vs x86&x64界面，激活py37后，再运行
    pip install pyOpenSSL

10、升级gcc

    使用奇正MOM的CTP API时，提示`GLIBCXX_3.4.22' not found，当前centos最高版本是 3.4.21，通过yum不能升级，需要手工下载升级。
    
    wget http://ftp.de.debian.org/debian/pool/main/g/gcc-9/libstdc++6_9.2.1-8_amd64.deb
    解压
    ar -x libstdc++6_9.2.1-8_amd64.deb    
    （就是 ar 命令，不是tar）    
    tar -xvf data.tar.xz

    安装
    
    删除： rm /usr/lib64/libstdc++.so.6    
    拷贝： cp usr/lib/x86_64-linux-gnu/libstdc++.so.6.0.28 /usr/lib64/    
    连接： ln -s /usr/lib64/libstdc++.so.6.0.28    /usr/lib64/libstdc++.so.6
    
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

11、升级glibc

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
