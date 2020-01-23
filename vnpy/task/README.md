###  基于Celery的分布式任务

# 安装
Windows 10:

    1) conda activate py37
    2) pip install celery
    3) pip install eventlet
   
Centos 7:
    
    trade用户
    1) conda activate py37
    2) pip install celery
    
    root 用户 （如果使用redis作为中介）
    1) 安装redis服务器 yum install redis    
    2) 修改/etc/redis.conf ，在127.0.0.1后，增加对外的IP地址
    3) 启动redis服务器 systemctl start redis    
    4) 允许外部访问（简单粗暴的方式：iptables -F）
    
    root 用户（如果使用rabbitMQ作为中介）
    1) 自行百度下如何安装rabbitMQ 服务程序
    2) 缺省账号/密码: admin/admin
    3) web访问界面 http://[ip]:15672/

Celery flower 监控

    1) pip install flower
    2) celery -A vnpy.task.celery_app --port=5555 --broker
    
# 启动
windows 10
    
    1) conda activate py37
    2) 进入项目目录后,例如c:\vnpy2, 运行命令：
        celery worker -c 2 -A vnpy.task.celery_app  -P eventlet -l debug -f celery.log
        其中:
        worker，表明这是celery的worker， 
        -c 代表使用多少个cpu作为线程池
        -A 代表worker运行的模块, 
        -P windows10下使用的协议
        -l (小写L），表示logging的级别， debug, info 等。
        -f 代表输出日志文件名
    3) 停止 Ctrl + C

#  添加任务的例子
    可在jupyter_notebook 中，或普通py程序中，往celery_app添加任务
    其中：
        1) excutue, 是celery_app中定义的Task类型方法。
        2) 它通过参数进行传递：
        -   func: 你要运行的某个命名空间函数，例如vnpy.app.cta_strategy_pro.portfolio_testing.single_test
        -   后续其他是这个函数所需要的若干参数了，用dict字典即可。
        3) task_id，提前定义，可把它作为任务的唯一标识。
            调用前，可存储在mongo数据库中，调用完成后，可更新mongo数据库的结果。
    
    from vnpy.task.celery_app import execute            
    task_id = str(uuid1())
    print(f'添加celery 任务：{task_id}')
    execute.apply_async(kwargs={
                         'func': 'vnpy.app.cta_strategy_pro.portfolio_testing.single_test',
                         'test_setting': test_setting,
                         'strategy_setting': strategy_setting},
                         task_id=task_id)    

# 清除任务得例子
    celery -A vnpy.task.celery_app purge
