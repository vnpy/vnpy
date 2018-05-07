#!/usr/bin/env bash
# 在 Mac 或者 Linux 下直接运行此脚本在本地构建镜像。

# 删除旧镜像
read -p "需要删除现有镜像吗？ [N|y]:" input
case "$input" in
[Yy])
    docker rmi vnpy:latest
    echo -n "删除完毕。"
    ;;
*)
    ;;
esac

echo ""

# 构建新镜像
read -p "确定开始构建镜像？ [N|y]:" input
case "$input" in
[Yy])
    # 构建镜像时，如有问题可以添加 --no-cache 参数以不使用缓存
    docker build -f Dockerfile --force-rm -t vnpy ..
    echo -n "构建完毕。"
    ;;
*)
    ;;
esac


echo ""
echo "当前镜像列表："
docker images
