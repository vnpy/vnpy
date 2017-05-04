# VNPY 的 Docker 镜像

author:[@lamter](https://github.com/lamter)


> _关于Docker_
> - _`Docker` 是基于 `Linux`的一个服务。通过模拟了整个 `Linux`的系统文件，来实现沙盒，所以`Docker`不是虚拟机，更类似于在`Linux`中模拟`Windows`的`Wine`。_
> - _在`Linux`中，`Docker`可以直接运行在宿主中，而在`Mac`和`Windows`中，是通过`VirtualBox`等先建立一个`Linux`的虚拟机，然后再在这个虚拟机中运行`Docker`。这样的话可能会有些许差异，比如`--host`的与宿主共享网络的模式。_
> - _在`Linux`系统下，模式下会使得`Docker`的容器与宿主共享网络端口，但是在`Mac`或者`Windows`中，该模式是容器与虚拟机中的`Linux`共享网络端口，而不是直接跟宿主`Mac`或者`Windows`共享端口。_

1. 使用 docker 镜像来提供运行和编译环境。
2. 将策略打包到 docker 镜像中以便直接在生产环境部署。
3. Docker教程看[这里](https://yeasy.gitbooks.io/docker_practice/content/)。
4. Docker加速看[这里](https://www.daocloud.io/mirror#accelerator-doc)

## 制作环境镜像

### 制作环境镜像
在`docker/`目录下运行:

```bash
➜  user@master~/vnpy/docker: bash build_image.sh
...
Successfully built fb3ae4d5e0eb
```

漫长的等待后之后，查看
```bash
➜  user@master~/vnpy/docker: docker images
REPOSITORY                   TAG                 IMAGE ID            CREATED             SIZE
vnpy                         latest              fb3ae4d5e0eb        21 minutes ago      856 MB
ubuntu                       16.04               4ca3a192ff2a        4 weeks ago         128.2 MB
```

vnpy 的运行环境镜像 `vnpy:latest` 制作成功。
`ubuntu` 镜像是用于构建 `vnpy` 镜像的上层镜像。之后可以使用 `vnpy` 镜像继续构建下层镜像，用于生产环境的部署。

### 测试运行
在`docker/`目录下运行

```bash
➜  user@master~/vnpy/docker: bash run_shell.sh
➜  root@docker/: 进入镜像
```

只是使用 `vnpy` 镜像启动了一个容器，并使用了`bash`来进行交互。此时环境基本上跟使用命令行登陆一台`Linux`类似。

查看`run_shell.sh`脚本可知，已经将整个`vnpy`的项目路径映射到了容器内的`/srv/vnpy`路径。

### 尝试编译
由于是一个新的```Linux```环境，```CTP```之类的接口需要重新编译。
```bash
➜  root@docker/: cd /srv/vnpy/vn.ctp
➜  root@docker/: ./build.sh
...
[100%] Built target vnctpmd
...
```

编译完成后，通过`Git`可以看到新编译成的`*.so`之类的文件。需要注意的是，此时对`/srv/vnpy`路径下的改动，也会反映到宿主下的`vnpy`项目。

**也就意味着，当前项目下的CTP接口已经被镜像中的编译包替换了。**

### 启动`vnpy`
在`vn.trader/ctpGateway/CTP_connection.json`中配置CTP链接账号的服务器host。

尝试启动 vnpy 实例
```bash
➜  root@docker /: cd /srv/vnpy/vn.trader
➜  root@docker docker: python vtServer.py
...
vn.trader服务器已启动
请输入exit来关闭服务器
```
运行成功。

### 直接运行项目代码
目前由于未知的原因，直接在宿主中通过传递命令的方式（见`vn.docker/server_vnpy.sh`脚本）来直接启动服务，会使得服务阻塞。所以目前只能先通过`run_shell.sh`脚本进入容器交互中，再启动服务。

## Q&A
__Q:__ MongoDB无法链接？
__A:__ 在`Linux`系统下，无需特定端口映射`-p 2014`，直接使用`--net=host`共享网络模式即可。在`Mac`或`Windows`下，需要在`VT_setting.json`中设置`mongoHost`时，指定其局域网中的`IP`，而非`localhost`。
