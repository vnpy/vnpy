# WebTrader模式的Docker镜像

本镜像用于展示如何通过Docker来实现vn.py在生产环境中使用的一种快速部署方案，适合策略开发和实盘运维团队分离的专业机构。建议使用中根据自己的需求修改Dockerfile，在构建时加入自主开发的组件和策略。

使用步骤：
1. 在Ubuntu下运行命令安装Docker相关组件：sudo apt install docker docker.io
2. 运行build.sh构建镜像webtrader
3. 运行run.sh启动基于webtrader镜像的容器
4. 进入后使用vi或者nano修改CTP_connect.json中的账户、密码、服务器地址信息
5. 运行run.py启动无人值守模式的WebTrader（夜盘开盘前启动，下午收盘后自动关闭）
6. Docker中的WebTrader会连接外部环境的MongoDB来加载历史数据，所以请提前安装好