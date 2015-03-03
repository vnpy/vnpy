# vn.py 
基于python的开源交易平台开发框架

## 2015/3/3项目状态 ##
目前完成：  
1. 华宝证券的LTS API的python封装，发布在vn.lts文件夹下  
2. 事件驱动引擎，发布在vn.event文件夹下  

### vn.lts   ###
ltsapi：华宝证券官方的LTS C++ API  
pyscript：用于自动生成重复度较高的封装代码的python脚本  
vnltsmd：行情API的封装源代码和测试脚本  
vnltstd：交易API的封装源代码和测试脚本  

### vn.event ###
eventType：定义事件类型常量  
eventEngine：包含事件驱动引擎实现  

## 下一步计划 ##
1. API封装、编译、使用方面的教程
2. 事件驱动引擎原理、使用方面的教程
3. 基于API和引擎开发的LTS交易客户平台（因为华宝没有提供官方的LTS交易软件，目前的两个实现分别是基于C++的尔易终端和基于.COM封装的盈佳终端）
4. 策略引擎接口

## 联系作者 ##
作者知乎名：用python的trader，想要联系作者可以通过知乎私信。



