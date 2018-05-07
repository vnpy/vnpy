# VNPY 的 Docker 镜像

author: [@lamter](https://github.com/lamter) and [@crystalphi](https://github.com/crystalphi)


> _关于Docker_
> - _`Docker` 是基于 `Linux`的一个服务。通过模拟了整个 `Linux`的系统文件，来实现沙盒，所以`Docker`不是虚拟机，更类似于在`Linux`中模拟`Windows`的`Wine`。_
> - _在`Linux`系统下，模式下会使得`Docker`的容器与宿主共享网络端口，但是在`Mac`或者`Windows`中，该模式是容器与虚拟机中的`Linux`共享网络端口，而不是直接跟宿主`Mac`或者`Windows`共享端口。_
> - Docker教程看[这里](https://yeasy.gitbooks.io/docker_practice/content/)。
常用命令示例：
```
docker build -t friendlyname .  # Create image using this directory's Dockerfile
docker run -p 4000:80 friendlyname  # Run "friendlyname" mapping port 4000 to 80
docker run -d -p 4000:80 friendlyname         # Same thing, but in detached mode
docker ps                                 # See a list of all running containers
docker stop <hash>                     # Gracefully stop the specified container
docker ps -a           # See a list of all containers, even the ones not running
docker kill <hash>                   # Force shutdown of the specified container
docker rm <hash>              # Remove the specified container from this machine
docker rm $(docker ps -a -q)           # Remove all containers from this machine
docker images -a                               # Show all images on this machine
docker rmi <imagename>            # Remove the specified image from this machine
docker rmi $(docker images -q)             # Remove all images from this machine
docker login             # Log in this CLI session using your Docker credentials
docker tag <image> username/repository:tag  # Tag <image> for upload to registry
docker push username/repository:tag            # Upload tagged image to registry
docker run username/repository:tag                   # Run image from a registry
```
> - Docker加速看[这里](https://www.daocloud.io/mirror#accelerator-doc)


## 设计概述

1. 使用 docker 镜像来提供基于 vnpy 的交易系统开发、测试、回测、实盘环境。

2. 将策略打包到 docker 镜像中以便直接在生产环境部署。


## 镜像制作与实例运行

### 制作环境镜像
在`docker/`目录下运行:

```bash
➜  user@master~/vnpy/docker: docker build -f Dockerfile --force-rm -t vnpy-vnc ..
...
Successfully built 26c00f8cf521
```

漫长的等待后之后，查看
```bash
➜  user@master~/vnpy/docker: docker images
REPOSITORY                    TAG                 IMAGE ID            CREATED                  SIZE
vnpy                          latest              26c00f8cf521        Less than a second ago   3.02GB
hub.c.163.com/public/ubuntu   16.04-tools         1196ea15dad6        5 months ago             336MB
```

vnpy 的运行环境镜像 `vnpy:latest` 制作成功。
之后可以使用该镜像继续构建下层镜像，用于生产环境的部署。


### 运行 Docker 实例
在`docker/`目录下运行

```bash
➜  user@master~/vnpy/docker: bash run_vnc.sh
➜  在 MacOS 的 Finder 中按 Command-k 打开对话框，输入 vnc://127.0.0.1:5900 进行 VNC 连接。
or 
➜  user@master~/vnpy/docker: bash run_shell.sh
➜  root@docker /srv/vnpy: 进入镜像实例的命令行界面
```

从脚本可知，已经将整个`vnpy`的项目路径映射到了容器内的`/srv/vnpy`路径。


### 重新编译接口库
由于是一个新的```Linux```环境，```CTP```之类的接口需要重新编译。
```bash
➜  root@docker/: cd /srv/vnpy/api/ctp/
➜  root@docker/: ./build.sh
...
[100%] Built target vnctpmd
...
```

编译完成后，通过`Git`可以看到新编译成的`*.so`之类的文件。需要注意的是，此时对`/srv/vnpy`路径下的改动，也会反映到宿主下的`vnpy`项目。

**也就意味着，当前项目下的CTP接口已经被镜像中的编译包替换了。**


### 启动基于 `vnpy` 的交易等程序
注意：需要先在`vnpy/trader/gateway/ctpGateway/CTP_connect.json`中配置正确的CTP链接账号及服务器信息。

尝试启动 vnpy 实例
```bash
➜  root@docker /srv/vnpy: python ./examples/VnTrader/run_simple.py
...
运行成功将在 VNC 界面上打开中文 GUI 程序，可正常连接 CTP 服务器及数据库。
```


## Q&A
__Q:__ 如何连接容器外的MongoDB？
__A:__ 在`Linux`系统下，无需特定端口映射`-p 2014`，直接使用`--net=host`共享网络模式即可。在`Mac`或`Windows`下，需要在`VT_setting.json`中设置`mongoHost`时，指定其局域网中的`IP`，而非`localhost`。

