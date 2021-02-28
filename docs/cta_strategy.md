# CtaStrategy - CTA策略模块

## 功能简介

CtaStrategy是用于**CTA策略实盘**的功能模块，用户可以通过图形界面操作来便捷完成策略初始化、策略启动、策略停止、策略参数编辑以及策略移除等任务。

## 加载启动

### VN Station加载

启动登录VN Station后，点击VN Trader Pro按钮，在配置对话框中的“上层应用”栏勾选CtaStrategy。

### 脚本加载

在启动脚本中添加如下代码：

```
# 写在顶部
from vnpy.app.cta_strategy import CtaStrategyApp

# 写在创建main_engine对象后
main_engine.add_app(CtaStrategyApp)
```


## 启动模块

启动VN Trader后，在菜单栏中点击【功能】-> 【数据管理】，或者点击左侧按钮栏的图标

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/cta_strategy/00.png)

即可进入该图形化历史数据管理界面，如下图所示：


## 添加策略


## 管理策略

### 初始化

### 启动

### 停止

### 编辑

### 移除

### 状态跟踪

## 运行日志

### 日志内容

引擎日志

策略日志

### 清空操作


## 停止单

停止单信息


## 批量操作

### 全部初始化

### 全部启动

### 全部停止