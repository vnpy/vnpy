#/bin/bash

# 直接运行 vnpy 项目代码，将vnpy项目代码目录映射到到容器的/opt/vnpy路径。
cd ..
# 必须采用 --no-ui 无UI模式。
docker run --name vnpy --rm -v `pwd`:/opt/vnpy vnpy:latest \
    python /opt/vnpy/vn.trader/main.py \
    --no-ui \
    --ctp