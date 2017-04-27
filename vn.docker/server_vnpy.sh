#/bin/bash

cd ..
docker run --name vnpy --rm \
    -v `pwd`:/srv/vnpy \
    -v `pwd`/vn.trader/tmp/VT_setting.json:/etc/vnpy/VT_setting.json \
    -p 2014:2014 -p 602:602 \
    vnpy:latest \
    --VT_setting /etc/vnpy/VT_setting.json
