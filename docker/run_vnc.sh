#!/usr/bin/env bash
# 以 vnc 服务方式启动容器，环境如同 Linux 命令行


#You can use vnc to connect to docker:
echo 'please press Command-k on Finder and connect to: vnc://127.0.0.1:5900'

DIR=$(cd `dirname $0`; pwd)
#mkdir -p ${DIR}/../docker/mongodb-data
#-v ${DIR}/../docker/mongodb-data:/var/lib/mongodb \

# Run docker container, mapping the ssh and vnc ports:
docker run --name vnpy_vnc --rm \
    -v ${DIR}/..:/srv/vnpy \
    -p 5900:5900 -p 27018:27017 \
    vnpy:latest \
    /usr/bin/x11vnc -forever -usepw -create

