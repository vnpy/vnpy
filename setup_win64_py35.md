1、下载64位Miniconda，安装在windows 10 64bit环境下

-地址 https://mirrors.tuna.tsinghua.edu.cn/anaconda/miniconda/
-安装时，勾选添加python3.7路径到系统path

2、打开conda命令行窗口
-添加国内的镜像更新源

 conda config --add channels https://mirrors.tuna.tsinghua.edu.cn/anaconda/pkgs/free/

 conda config --set show_channel_urls yes

-创建pytho 3.5的环境

conda create --name py35 python=3.5

- 创建后，激活

activate py35

- 安装pyqt

conda install pyqt

- 安装 需要的软件包
pip -r requirements.txt

- 安装 ta-lib
conda install -c quantopian ta-lib=0.4.9
