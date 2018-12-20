### RQData数据自动更新服务

vn.py官方推荐的历史数据解决方案，由RiceQuant提供的高质量期货数据服务。

使用步骤：
1. 前往[RQData主页](https://www.ricequant.com/purchase#1)，购买标准版账户或者申请试用
2. 获得账户后将自动下载make.bat文件，在make.bat中找到name和password信息
3. 打开config.json，在rqUsername和rqPassword中填入上述信息，并在product列表中，填入需要更新行情的期货合约产品代码（只包含英文字母即可）
4. 双击“启动更新服务.bat”，来启动RQData数据自动更新服务，点击右上角关闭按钮可最小化到右下方的托盘栏
5. 在托盘栏图标上点击右键菜单中的“退出”可以退出程序
