# 数据库配置

VN Trader目前支持以下四种数据库：  

 * [SQLite](#sqlite)（默认）
 * [MySQL](#sqlmysqlpostgresql)
 * [PostgreSQL](#sqlmysqlpostgresql)
 * [MongoDB](#mongodb)
 
如果需要配置数据库，请点击配置。然后按照各个数据库所需的字段填入相对应的值即可。

---
## SQLite
需要填写以下字段：

| 字段名            | 值 |
|---------           |---- |
|database.driver     | sqlite |
|database.database   | 数据库文件（相对于trader目录） |
 
SQLite的例子：

| 字段名            | 值 |
|---------           |---- |
|database.driver     | sqlite |
|database.database   | database.db |


---
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
> 若未创建数据库，请手动连上数据库并运行该命令：```create database <你填的database.database>;```   

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

| 字段名            | 值 |
|---------           |----  |
|database.driver     | mongodb |
|database.host       | localhost |
|database.port       | 27017 |
|database.database   | vnpy |
|database.user       | root |
|database.password   | .... |
|database.authentication_source   | vnpy |


[AuthSource]: https://docs.mongodb.com/manual/core/security-users/#user-authentication-database