#!/bin/bash

echo [API]: Prepare to update DATAYES_FUTURE_D1...
python - << EOF
from storage import *
dc = DBConfig()
api = PyApi(Config())
mc = MongodController(dc, api)
mc.update_future_D1()
EOF
echo [API]: DATAYES_FUTURE_D1 updated.

echo [API]: Prepare to update DATAYES_INDEX_D1...
python - << EOF
from storage import *
dc = DBConfig()
api = PyApi(Config())
mc = MongodController(dc, api)
mc.update_index_D1()
EOF
echo [API]: DATAYES_INDEX_D1 updated.

echo [API]: Prepare to update DATAYES_OPTION_D1...
python - << EOF
from storage import *
dc = DBConfig()
api = PyApi(Config())
mc = MongodController(dc, api)
mc.update_option_D1()
EOF
echo [API]: DATAYES_OPTION_D1 updated.

echo [API]: Prepare to update DATAYES_FUND_D1...
python - << EOF
from storage import *
dc = DBConfig()
api = PyApi(Config())
mc = MongodController(dc, api)
mc.update_fund_D1()
EOF
echo [API]: DATAYES_FUND_D1 updated.
echo [MONGOD]: Update finished.

echo [API]: Prepare to update DATAYES_EQUITY_D1...
python - << EOF
from storage import *
dc = DBConfig()
api = PyApi(Config())
mc = MongodController(dc, api)
mc.update_equity_D1()
EOF
echo [API]: DATAYES_EQUITY_D1 updated.