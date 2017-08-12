#!/usr/bin/env bash
# 在 Mac 或者 Linux 下直接运行此脚本在本地构建镜像。

# 删除旧镜像
# docker rmi vnpy-base:latest
docker rmi vnpy-vnc:latest

# 构建基本版镜像
# 在本地构建镜像时，在 Dockerfile 取消注释使用阿里云的 apt 源制作镜像, 如有问题添加 --no-cache 参数以不使用缓存
# docker build -f Dockerfile-base --force-rm -t vnpy-base .

# 基于基本版构建 VNC 版本镜像
docker build -f Dockerfile-vnc --force-rm -t vnpy-vnc ..
