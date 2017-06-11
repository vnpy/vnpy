#!/bin/bash

echo [API]: Prepare to construct DATAYES_FUTURE_D1, {20150101, 20150801}...
python - << EOF
from storage import *
dc = DBConfig()
api = PyApi(Config())
mc = MongodController(dc, api)
mc.download_future_D1('20150101','20150801')
EOF
echo [MONGOD]: DATAYES_FUTURE_D1 constructed.

echo [API]: Prepare to construct DATAYES_OPTION_D1, {20150101, 20150801}...
python - << EOF
from storage import *
dc = DBConfig()
api = PyApi(Config())
mc = MongodController(dc, api)
mc.download_option_D1('20150101','20150801')
EOF
echo [MONGOD]: DATAYES_OPTION_D1 constructed.

echo [API]: Prepare to construct DATAYES_INDEX_D1, {20150101, 20150801}...
python - << EOF
from storage import *
dc = DBConfig()
api = PyApi(Config())
mc = MongodController(dc, api)
mc.download_index_D1('20150101','20150801')
EOF
echo [MONGOD]: DATAYES_INDEX_D1 constructed.

echo [API]: Prepare to construct DATAYES_FUND_D1, {20150101, 20150801}...
python - << EOF
from storage import *
dc = DBConfig()
api = PyApi(Config())
mc = MongodController(dc, api)
mc.download_fund_D1('20150101','20150801')
EOF
echo [MONGOD]: DATAYES_FUND_D1 constructed.

echo [API]: Prepare to construct DATAYES_EQUITY_D1, {20130101, 20150801}...
python - << EOF
from storage import *
dc = DBConfig()
api = PyApi(Config())
mc = MongodController(dc, api)
mc.download_equity_D1('20130101','20150801')
EOF
echo [MONGOD]: DATAYES_EQUITY_D1 constructed.