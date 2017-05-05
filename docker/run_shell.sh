#/bin/bash
# 以 shell 方式启动容器，环境如同 Linux 命令行

cd ..
# 将 vnpy 指定到
docker run --name vnpy_bash --rm \
    -v `pwd`:/srv/vnpy \
    -p 2014:2014 -p 602:602 \
    -it vnpy:latest /bin/bash

