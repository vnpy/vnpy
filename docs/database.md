# 数据库

VN Trader目前支持以下八种数据库：

## SQL类数据库简介

### SQLite（默认）

SQLite是一个轻量的嵌入式数据库，无需安装和配置数据服务程序，是vn.py的**默认数据库**。适合入门新手用户，其特点如下：
 - 存储在一个单一的跨平台的磁盘文件上；
 - 不需要在系统中配置、安装和管理；
 - 不需要一个单独的服务器进程。

### MySQL

MySQL是目前最流行的开源关系型数据库，其特点如下：
 - 文档材料丰富，社区及用户活跃；
 - 支持多种操作系统，多种开发语言；
 - 可替换其他高NewSQL兼容实现（如TiDB）。

### PostgreSQL

PostgreSQL是特性更为丰富的开源关系型数据库，只推荐熟手使用。相比于MySQL，其特点如下：
 - 采用多进程结构；
 - 支持通过扩展插件来新增功能。


## 非SQL类数据库简介

### MongoDB

MongoDB是一个基于分布式文件储存 （bson格式）的非关系型数据库，其特点如下：
 - 面向文档存储，操作比较简单；
 - 支持丰富的存储类型和数据操作；
 - 内置的热数据内存缓存实现更快的读写速度。

### InfluxDB

InfluxDB是专门针对时间序列数据存储设计的非关系型数据库，其特点如下：
- 列式数据存储提供极高的读写效率；
- 采用独立服务进程的模式运行，也能支持多进程的并发访问需求。

### DolphinDB

DolphinDB是浙江智臾科技有限公司研发的一款高性能分布式时序数据库，特别适用于对速度要求极高的低延时或实时性任务，其特点如下：
- 列式分析型（OLAP）数据库，采用混合引擎（基于内存和硬盘），充分利用缓存来加速；
- 原生分区表存储，合理的分区方案可以让CPU多线程并行加载每个分区内的数据；
- 支持高效的数据压缩，显著减小硬盘存储空间的同时，还能大幅降低IO通讯的开销。

### Arctic

Arctic是由英国量化对冲基金Man AHL基于MongoDB开发的高性能金融时序数据库，其特点如下：
- 支持直接存储pandas的DataFrame和numpy的ndaaray对象；
- 允许对数据进行版本化管理（类似于数据库中的git），便于因子挖掘过程中的数据迭代管理；
- 基于分块化存储和LZ4压缩，在网络和磁盘IO方面节省大量资源，实现最高每秒百万行的数据查询。

### Level DB
LevelDB是由Google推出的高性能Key/Value数据库，其特点如下：
- 定位为通用型数据存储方案；
- 基于LSM算法实现进程内存储引擎；
- 支持数十亿级别的海量数据。


## 数据库配置（以MySQL为例）

本文档以MySQL为例，介绍数据库的配置过程。

首先在[MySQL官网](https://dev.mysql.com/downloads/)下载Windows版本安装包【MySQL Installer for Windows】，如下图所示：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/database/1.png)

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/database/2.png)

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/database/3.png)

下载完成后得到msi格式的安装包，双击打开后选择【Full】模式，安装MySQL完整版，一路点击【Next】按钮即可完成安装。

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/database/4.png)

安装过程中将会自动从网站下载相关组件，先点击【Execute】按钮来补全，再点击【Next】按钮。

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/database/5.png)

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/database/6.png)

安装过程中将会要求输入3次密码，这里为了方便演示，我们将密码设置为1001，请在自己安装的过程中使用更加复杂安全的密码。  
安装完毕后会自动打开MySQL的图形管理工具MySQL WorkBench，点击菜单栏【Database】->【Connect to Database】，如下图所示：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/database/7.png)

在弹出的对话框中，直接选择默认数据库Local Instance MySQL，然后点击【OK】按钮连接MySQL数据库服务器。

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/database/8.png)

在自动打开的数据库管理界面中，点击下图中菜单栏红色方框的按钮，来创建新的数据库。在【Name】中输入“vnpy”，然后点击下方的【Apply】按钮确认。

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/database/9.png)

在之后弹出的数据库脚本执行确认对话框中，同样点击【Apply】即可，这样就完成了在MySQL WorkBench的所有操作。

随后启动VN Trader，点击菜单栏的【配置】，设置数据库相关字段：

- name要改成mysql（请注意大小写）；
- database改成vnpy；
- host为本地IP，即localhost或者127.0.0.1；
- port为MySQL的默认端口3306；
- user用户名为root
- password密码则是之前我们设置的1001。

```
database.name: mysql
database.database: vnpy
database.host: localhost
database.port: 3306
database.user: root
database.password: 1001
```

填写完毕后如下图所示：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/database/11.png)

保存完成配置修改后，重启VN Trader来启用新的数据库配置。重启后，在打开VN Trader的过程中若无报错提示，则说明MySQL数据库配置成功。 

## 数据库字段

### SQLite

SQLite在VN Trader中配置时，需填写以下字段信息：

| 字段名             | 值 |
|---------           |---- |
|database.name     | sqlite |
|database.database   | 数据库文件（相对于trader目录） |

SQLite的例子如下所示：

| 字段名            | 值 |
|---------           |---- |
|database.name     | sqlite |
|database.database   | database.db |


### SQL(MySQL, PostgreSQL)

MySQL和PostgreSQL在VN Trader中配置时，需要填写以下字段信息：

| 字段名            | 值 |
|---------           |---- |
|database.name     | "mysql"或"postgresql" |
|database.host       | 地址 |
|database.port       | 端口 |
|database.database   | 数据库名 |
|database.user       | 用户名 |
|database.password   | 密码 |

MySQL的例子如下所示：

| 字段名            | 值 |
|---------           |----  |
|database.name     | mysql |
|database.host       | localhost |
|database.port       | 3306 |
|database.database   | vnpy |
|database.user       | root |
|database.password   | .... |

请注意，vn.py不会主动为关系型数据库创建数据库，所以请确保你所填的database.database字段对应的数据库已经创建好了。若未创建数据库，请手动连上数据库并运行该命令：
```
create database <你填的database.database>;
```

## MongoDB

MongoDB在VN Trader中配置时，需要填写以下字段信息：

| 字段名               |   值 |          是否必填|
|---------           |---- |  ---|
|database.name     | "mongodb" | 必填 |
|database.host       | 地址| 必填 |
|database.port       | 端口| 必填 |
|database.database   | 数据库名| 必填 |
|database.user       | 用户名| 可选 |
|database.password   | 密码| 可选 |
|database.authentication_source   | [创建用户所用的数据库][AuthSource]| 可选 |

MongoDB的带认证例子如下所示：

| 字段名             | 值 |
|---------           |----  |
|database.name     | mongodb |
|database.host       | localhost |
|database.port       | 27017 |
|database.database   | vnpy |
|database.user       | root |
|database.password   | .... |
|database.authentication_source   | vnpy |


[AuthSource]: https://docs.mongodb.com/manual/core/security-users/#user-authentication-database


## InfluxDB

InfluxDB在VN Trader中配置时，需要填写以下字段信息：

| 字段名            | 值 |
|---------           |---- |
|database.name     | "influxdb" |
|database.host       | 地址|
|database.port       | 端口|
|database.database   | 数据库名|
|database.user       | 用户名|
|database.password   | 密码|


InfluxDB的例子如下所示：

| 字段名             | 值 |
|---------           |----  |
|database.name     | influxdb |
|database.host       | localhost |
|database.port       | 8086 |
|database.database   | vnpy |
|database.user       | root |
|database.password   | .... |
|database.authentication_source   | vnpy |

请注意，运行influxd.exe的cmd需要保持运行，如果关闭则会导致InfluxDB退出，或者也可以使用一些辅助工具将其注册为后台运行的Windows服务。

## DolphinDB


需要填写以下字段：


| 字段名        | 值 |
|---------          |---- |
|database.name      | "dolphindb"|
|database.host      | 地址 |
|database.port      | 端口 |
|database.database  | 数据库名 |
|database.user      | 用户名 |
|database.password  | 密码 |

 
DolphinDB的例子：


| 字段名            | 值 |
|---------          |----  |
|database.name      | dolphindb |
|database.host      | localhost |
|database.port      | 8848 |
|database.database  | vnpy |
|database.user      | admin |
|database.password  | .... |


## Arctic


| 字段名          | 值 |
|---------        |---- |
|database.name    | "arctic"|
|database.host    | 地址 |
|database.port    | 端口 |

 
Arctic的例子：


| 字段名          | 值 |
|---------        |----  |
|database.name    | arctic |
|database.host    | localhost |
|database.port    | 0 |


## LevelDB


| 字段名            | 值 |
|---------          |---- |
|database.name      | "leveldb"|
|database.database  | 数据库名 |
|database.port    | 端口 |



LevelDB的例子：


| 字段名            | 值 |
|---------          |  ----  |
|database.name      | leveldb |
|database.database  | vnpy_data |
|database.port      | 0 |
