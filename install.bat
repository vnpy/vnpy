::Install Python Modules
pip install -r requirements.txt

::Install Ta-Lib
conda config --add channels https://mirrors.tuna.tsinghua.edu.cn/anaconda/pkgs/free/
conda config --set show_channel_urls yes
conda install -c quantopian ta-lib=0.4.9 -y

:: Install vn.py
python setup.py install