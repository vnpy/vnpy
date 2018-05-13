#!/usr/bin/env bash

# 构建镜像，不使用缓存
docker build -t webtrader --no-cache .