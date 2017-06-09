
#VN.DATAYES - Welcome!

##0. Tutorial - ipythonNotebook
http://nbviewer.ipython.org/github/zedyang/vn.past-demo/blob/master/static/tutorial.ipynb

##1. Preface

###1.1
vn.datayes是一个从属于vnpy的开源历史数据模块；使用通联数据API以及MongoDB进行数据的下载和存储管理。项目目前与将来主要解决\准备解决以下问题：

* 从通联数据等API高效地爬取、更新、清洗历史数据。
* 基于MongoDB的数据库管理、快速查询、转换输出格式；支持自定义符合需求的行情历史数据库。
* 基于Python.Matplotlib或R.ggplot2，快速绘制K线图等可视化对象。

项目目前主要包括了通联API开发者试用方案中大部分的市场行情日线数据（股票、期货、期权、指数、基金等），以及部分基本面数据。数据下载与更新主要采用多线程设计，测试效率如下：

| 数据集举例 | 数据集容量 | 下载时间估计  |
| :-------------: | :-------------: | :-------------: |
| 股票日线数据，2800个交易代码，2013年1月1日至2015年8月1日 | 2800个collection，约500条/each | 7-10分钟 |
| 股票分钟线数据，2个交易代码，2013年1月1日至2015年8月1日 | 2个collection，约20万条/each      | 1-2分钟 |
| 股票日线数据更新任务，2800个交易代码，2015年8月1日至2015年8月15日 | 2800个collection，约10条/each      | 1-2分钟 |

vn.datayes基于MongoDB数据库，通过一个json配置文件简化数据库的初始化、设置、动态更新过程。较为精细的数据库操作仍需编写脚本进行。若对MongoDB与pymongo不熟悉，推荐使用Robomongo等窗口化查看工具作为辅助。

###1.2 主要依赖：
pymongo,  pandas,  requests,  json
###1.3 开发测试环境：
Mac OS X 10.10; Windows 7 || Anaconda.Python 2.7


##2. Get Started
###2.1 准备

* 下载并安装MongoDB: https://www.mongodb.org/downloads
* 获取API token，以通联数据为例。

![fig1](static/figs/fig1.png)

* 更新pymongo至3.0以上版本; 更新requests等包。 
```
~$ pip install pymongo --upgrade
~$ pip install requests --upgrade
```

* [ ! 注意，本模块需要pymongo3.0新加入的部分方法，使用vnpy本体所用的2.7版本对应方法将无法正常插入数据。依赖冲突的问题会尽快被解决，目前推荐制作一个virtual environment来单独运行这个模块；或者暴力切换pymongo的版本：]
```
~$ pip install pymongo==3.0.3  # this module.
~$ pip install pymongo==2.7.2  # pymongo 2.7.
```

* 启动MongoDB
```
~$ mongod
```


###2.2 数据库初始化与下载
* **api.Config** 对象包含了向API进行数据请求所需的信息，我们需要一个用户token来初始化这个对象。

```
    from storage import *
    
    myConfig = Config(head="Zed's Config", 
                      token='7c2e59e212dbff90ffd6b382c7afb57bc987a99307d382b058af6748f591d723')
    myConfig.body
```


```
    {'domain': 'api.wmcloud.com/data',
     'header': {'Authorization': 'Bearer 7c2e59e212dbff90ffd6b382c7afb57bc987a99307d382b058af6748f591d723',
      'Connection': 'keep-alive'},
     'ssl': False,
     'version': 'v1'}
```



* **storage.DBConfig** 对象包含了数据库配置。我们需要自己编写一个json字典来填充这个对象。举例来说，我们希望下载股票日线数据和指数日线数据，数据库名称为DATAYES_EQUITY_D1和DATAYES_INDEX_D1，index为日期“date”。那么json字典是这样的：

```
    client = pymongo.MongoClient() # pymongo.connection object.
    
    body = {
        'client': client, # connection object.
        'dbs': {
            'EQU_D1': {                              # in-python alias: 'EQU_D1'
                'self': client['DATAYES_EQUITY_D1'], # pymongo.database[name] object.
                'index': 'date',                     # index name.
                'collNames': 'equTicker'             # what are collection names consist of.
            },
            'IDX_D1': {                              # Another database
                'self': client['DATAYES_INDEX_D1'],
                'index': 'date',
                'collNames': 'idxTicker'
            }
        },
        'dbNames': ['EQU_D1','IDX_D1']               # List of alias.
    }
    
    myDbConfig_ = DBConfig(body=body)
    
    # 这看上去有些麻烦；不想这么做的话可以直接使用DBConfig的默认构造函数。
    
    myDbConfig = DBConfig()
    
    myDbConfig.body
```


```
    {'client': MongoClient('localhost', 27017),
     'dbNames': ['EQU_M1', 'EQU_D1', 'FUT_D1', 'OPT_D1', 'FUD_D1', 'IDX_D1'],
     'dbs': {'EQU_D1': {'collNames': 'equTicker',
       'index': 'date',
       'self': Database(MongoClient('localhost', 27017), u'DATAYES_EQUITY_D1')},
      'EQU_M1': {'collNames': 'secID',
       'index': 'dateTime',
       'self': Database(MongoClient('localhost', 27017), u'DATAYES_EQUITY_M1')},
      'FUD_D1': {'collNames': 'fudTicker',
       'index': 'date',
       'self': Database(MongoClient('localhost', 27017), u'DATAYES_FUND_D1')},
      'FUT_D1': {'collNames': 'futTicker',
       'index': 'date',
       'self': Database(MongoClient('localhost', 27017), u'DATAYES_FUTURE_D1')},
      'IDX_D1': {'collNames': 'idxTicker',
       'index': 'date',
       'self': Database(MongoClient('localhost', 27017), u'DATAYES_INDEX_D1')},
      'OPT_D1': {'collNames': 'optTicker',
       'index': 'date',
       'self': Database(MongoClient('localhost', 27017), u'DATAYES_OPTION_D1')}}}
```



* **api.PyApi**是向网络数据源进行请求的主要对象。**storage.MongodController**是进行数据库管理的对象。当我们完成了配置对象的构造，即可初始化PyApi与MongodController。**MongodController._get_coll_names()** 和**MongodController._ensure_index()** 是数据库初始化所调用的方法，为了模块开发的方便，它们暂时没有被放进构造函数中自动执行。

```
    myApi = PyApi(myConfig) # construct PyApi object.
    mc = MongodController(api=myApi, config=myDbConfig) # construct MongodController object, 
                                                        # on the top of PyApi.
    mc._get_coll_names()    # get names of collections.
    mc._ensure_index()      # ensure collection indices.
```
```
    [MONGOD]: Collection names gotten.
    [MONGOD]: MongoDB index set.
```




![fig2](static/figs/fig2.png)

* 使用**MongodController.download#()**方法进行下载。


    mc.download_index_D1('20150101','20150801')

![fig3](static/figs/fig3.png)

###2.3 数据库更新
* 使用**MongodController.update#()**方法进行更新。脚本会自动寻找数据库中的最后一日并更新至最新交易日。

```
    from datetime import datetime
    datetime.now()
```


```
    datetime.datetime(2015, 8, 17, 10, 49, 21, 37758)
```


```
    mc.update_index_D1()
```

![fig4](static/figs/fig4.png)

###2.4 Mac OS或Linux下的下载与更新
模块中包含了一些shell脚本，方面在linux-like os下的数据下载、更新。
```
~$ cd path/of/vn/datayes
~$ chmod +x prepare.sh
~$ ./prepare.sh
```

![fig5](static/figs/fig5.png)
![fig6](static/figs/fig6.png)


    
