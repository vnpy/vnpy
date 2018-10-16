#!/bin/bash

THIS_DIR=$(cd `dirname $0`; pwd -P)
TOPDIR=${THIS_DIR}/../..

id=vnpyuser

display="-v /tmp/.X11-unix:/tmp/.X11-unix -e DISPLAY=$DISPLAY"
volume="-v ${TOPDIR}:/srv/vnpy"

docker run -it --rm --name vnpy -u $id $display $volume vnpy /bin/bash


