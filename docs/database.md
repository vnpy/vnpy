# 数据库

## 数据库简介

VN Trader目前支持以下五种数据库，其中，SQLite、MySQL和PostgreSQL为SQL类数据库，MongoDB和InfluxDB为非SQL类数据库。

### SQLite

SQLite是轻量级嵌入式数据库，也是vn.py的**默认数据库**，适合入门新手用户；
 - 存储在一个单一的跨平台的磁盘文件上；
 - 不需要在系统中配置、安装和管理；
 - 不需要一个单独的服务器进程。

MySQL：目前最流行的开源关系型数据库；
 - 文档材料丰富，社区及用户活跃；
 - 支持多种操作系统，多种开发语言；
 - 可替换其他高NewSQL兼容实现（如TiDB）。

PostgreSQL：特性更为丰富的开源关系型数据库，只推荐熟手使用；
 - 多进程结构；
 - 支持通过扩展插件来新增功能。

MongoDB：基于分布式文件储存（bson格式）的非关系型数据库；
 - 面向文档存储，操作比较简单；
 - 支持丰富的存储类型和数据操作；
 - 内置的热数据内存缓存实现更快的读写速度。

InfluxDB：专门针对时间序列数据存储设计的非关系型数据库；
- 列式数据存储提供极高的读写效率；
- 采用独立服务进程的模式运行，也能支持多进程的并发访问需求。

## 数据库配置（以MySQL为例）

本文档以MySQL为例，介绍数据库的配置过程。

首先在[MySQL官网](https://dev.mysql.com/downloads/)下载Windows版本安装包【MySQL Installer for Windows】，如下图所示：

![](1.png)

![](2.png)

![](3.png)

下载完成后得到msi格式的安装包，双击打开后选择【Full】模式，安装MySQL完整版，然后一路点击【Next】按钮即可完成安装。

![](4.png)

![](5.png)

## 数据库字段

### SQLite

SQLite配置需要填写以下字段：

| 字段名             | 值 |
|---------           |---- |
|database.driver     | sqlite |
|database.database   | 数据库文件（相对于trader目录） |
 
SQLite的例子：

| 字段名            | 值 |
|---------           |---- |
|database.driver     | sqlite |
|database.database   | database.db |


## SQL(MySQL,PostgreSQL)

需要填写以下字段：

| 字段名            | 值 |
|---------           |---- |
|database.driver     | "mysql"或"postgresql" |
|database.host       | 地址 |
|database.port       | 端口 |
|database.database   | 数据库名 |
|database.user       | 用户名 |
|database.password   | 密码 |
 
MySQL的例子：

| 字段名            | 值 |
|---------           |----  |
|database.driver     | mysql |
|database.host       | localhost |
|database.port       | 3306 |
|database.database   | vnpy |
|database.user       | root |
|database.password   | .... |

> vnpy不会主动为关系型数据库创建数据库，所以请确保你所填的database.database字段对应的数据库已经创建好了  
> 若未创建数据库，请手动连上数据库并运行该命令：
```
create database <你填的database.database>;
```   

---


## MongoDB

需要填写以下字段：

| 字段名            | 值 |          是否必填|
|---------           |---- |  ---|
|database.driver     | "mysql"或"postgresql" | 必填 |
|database.host       | 地址| 必填 |
|database.port       | 端口| 必填 |
|database.database   | 数据库名| 必填 |
|database.user       | 用户名| 可选 |
|database.password   | 密码| 可选 |
|database.authentication_source   | [创建用户所用的数据库][AuthSource]| 可选 |
 
MongoDB的带认证例子：

| 字段名             | 值 |
|---------           |----  |
|database.driver     | mongodb |
|database.host       | localhost |
|database.port       | 27017 |
|database.database   | vnpy |
|database.user       | root |
|database.password   | .... |
|database.authentication_source   | vnpy |


[AuthSource]: https://docs.mongodb.com/manual/core/security-users/#user-authentication-database