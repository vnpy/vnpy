#!/bin/bash

THIS_DIR=$(cd `dirname $0`; pwd -P)
TOPDIR=${THIS_DIR}/../..

id=vnpyuser
ostype=Linux
display=
volume="-v ${TOPDIR}:/srv/vnpy"

# 设置时区
timezone="-e TZ=UTC-8"


function os_detect() {
  osname=`uname -s`
  case "${osname}" in
    Linux*)  ostype=Linux;;
    Darwin*) ostype=Mac;;
    CYGWIN*) ostype=Cywin;;
    MINGW*)  ostype=Mingw;;
    *)       ostype="Unknown-${osname}"
  esac
  echo "Your system is : ${ostype}"
}

# OS X 系统获取 ip 地址
function osx_ip() {
  ip=$(ifconfig en0 | grep inet | awk '$1=="inet" {print $2}')

  if [ -z "$ip" ]; then
    ip=$(ifconfig en1 | grep inet | awk '$1=="inet" {print $2}')
  fi
}

# 探测系统类型并设置 ostype 变量
os_detect

if [ "${ostype}" = "Linux" ]; then
  display="-v /tmp/.X11-unix:/tmp/.X11-unix -e DISPLAY=$DISPLAY"
elif [ "${ostype}" = "Mac" ]; then
  osx_ip
  display_number=`ps -ef | grep "Xquartz :\d" | grep -v xinit | awk '{ print $9; }'`
  display="-v /tmp/.X11-unix:/tmp/.X11-unix -e DISPLAY=${ip}${display_number}"
  xhost + $ip
elif [ "${ostype}" = "Cywin" ]; then
  echo "TODO @ Cywin"
elif [ "${ostype}" = "Mingw" ]; then
  echo "TODO @ Mingw"
fi

docker_args="-u $id $display $volume $timezone"

echo "docker args : $docker_args"

docker run -it --rm --name vnpy $docker_args vnpy /bin/bash


