#/bin/bash
# 在 Mac 或者 Linux 下直接运行这个在本地构建镜像。

# 删除旧镜像
# docker rmi vnpy:latest

# 在本地构建镜像时，在 Dockerfile 取消注释，使用阿里云的 apt 源
# 制作镜像, 如有问题, 添加 --no-cache 参数以不使用缓存
docker build --force-rm -t vnpy .