# 2.1.9版本

## 修复
1. 修复BarGenerator的小时线合成时，出同一个小时的K线重复推送两次的问题
2. 修复遗传算法优化时，因为lru_cache缓存导致的新一轮优化结果不变的问题
3. 修复RestClient发起请求时，由于requests库底层使用OpenSSL导致的WinError 10054 WSAECONNRESET的问题
4. 修复okexf、okexs、okexo三个接口收取TICK行情时，盘口数据解析错误的问题
5. 修复程序中频繁捕捉到异常时，异常捕捉对话框反复执行导致卡死的问题
6. 修复币安的现货和合约接口请求抛出SSLError异常时，未捕捉导致程序卡死的问题

## 新增
1. 新增BaseMonitor数据监控UI组件（以及其子类），自动保存列宽的功能