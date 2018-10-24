#!/bin/bash

THIS_DIR=$(cd `dirname $0`; pwd -P)
TOPDIR=${THIS_DIR}/../..

id=vnpyuser
ostype=Linux
display=
volume="-v ${TOPDIR}:/srv/vnpy"
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

function osx_ip() {
  ip=$(ifconfig en0 | grep inet | awk '$1=="inet" {print $2}')

  if [ -z "$ip" ]; then
    ip=$(ifconfig en1 | grep inet | awk '$1=="inet" {print $2}')
  fi
}

os_detect
if [ "${ostype}" = "Linux" ]; then
  display="-v /tmp/.X11-unix:/tmp/.X11-unix -e DISPLAY=$DISPLAY"
elif [ "${ostype}" = "Mac" ]; then
  osx_ip
  display_number=`ps -ef | grep "Xquartz :\d" | grep -v xinit | awk '{ print $9; }'`
  display="-v /tmp/.X11-unix:/tmp/.X11-unix -e DISPLAY=${ip}${display_number}"
  xhost + $ip
elif [ "${ostype}" = "Cywin" ]; then

elif [ "${ostype}" = "Mingw" ]; then

fi

docker_args="-u $id $display $volume $timezone"

docker run -it -d --name vnpy $docker_args vnpy /bin/bash


