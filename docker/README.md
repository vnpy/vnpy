# VNPY 的 Docker 镜像

1. 使用 docker 镜像来提供运行和编译环境。
2. 将策略打包到 docker 镜像中以便直接在生产环境部署。

## 制作环境镜像

### 制作环境镜像
在```docker/```目录下运行:
```bash
➜  ~ bash build_image.sh
...
Successfully built fb3ae4d5e0eb
```

漫长的等待后之后，查看
```
➜  ~ docker images
REPOSITORY                   TAG                 IMAGE ID            CREATED             SIZE
vnpy                         latest              fb3ae4d5e0eb        21 minutes ago      856 MB
ubuntu                       16.04               4ca3a192ff2a        4 weeks ago         128.2 MB
```
vnpy 的运行环境镜像 *vnpy:latest* 制作成功。
*ubuntu* 镜像是用于构建 *vnpy* 镜像的上层镜像。之后可以使用 *vnpy*镜像继续构建下层镜像，用于生产环境的部署。

### 测试运行
在```docker/```目录下运行
```
➜  user@docker# bash run_shell.sh
➜  root@5bb14b326ac9/#
```
只是使用 *vnpy* 镜像启动了一个容器，并使用了*bash*来进行交互。此时环境基本上跟使用命令行登陆一台*Linux*类似。

查看*run_shell.sh*脚本可知，已经将整个*vnpy*的项目路径映射到了容器内的```/opt/vnpy```路径。

### 尝试编译
由于是一个新的*Linux*环境，```CTP```之类的接口需要重新编译。
```bash
➜  root@5bb14b326ac9/# cd /opt/vnpy/vn.ctp
➜  root@5bb14b326ac9/# ./build.sh
...
[100%] Built target vnctpmd
...
```

编译完成后，通过```Git```可以看到新编译成的*.so*之类的文件。需要注意的是，此时对```/opt/vnpy```路径下的改动，也会反映到宿主下的*vnpy*项目。

### 启动*vnpy*
在```vn.trader/ctpGateway/CTP_connection.json```中配置CTP链接账号的服务器host。

建立容器，并在```bash```中进行交互。尝试启动 vnpy 实例
```
➜  root@5bb14b326ac9/# cd /opt/vnpy/vn.trader
➜  root@5bb14b326ac9/# python main.py --no-ui --ctp # 无UI模式，自动建立CTP链接
```
运行成功。

### 直接运行实例
在```bin/```中，直接运行实例的脚本
```
➜  user@bin# bash run_vnpy.sh
CTP is OK ! balance : 1000000
```

## Q&A
*Q: *关于Windows下？
*A: *也许应该大概可能在```Git Bash```中可以直接可以完成 build 。

*Q: *一大堆的 "No module named"？
*A: *目前只编译了CTP的接口，其余的接口文件都被删掉了，有需要以后可以加回来。不用在意这些细节。

*Q: *在Windows下下载Miniconda的安装包太慢？
*A: *点[这里](https://repo.continuum.io/miniconda/Miniconda2-latest-Linux-x86_64.sh)下载安装包，并放到 docker/ 文件夹下和Dockerfile 一起。