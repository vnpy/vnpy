# -*- coding: utf-8 -*-

from __future__ import print_function
from __future__ import absolute_import
from . import jrpc_server
import time
import pandas as pd
from qdata.database import DatabaseConn
from qdata.datamodel import DataModel
import qdata.apisetting as st
import json

server = None
view_set = {}
db = None

def on_call(client_id, req):

    if req['method'] != '.sys.heartbeat':
        print("on_call", req)

    if req['method'] == 'auth.login':
        server.send_rsp(client_id, req, result = { "username" : "fixme", "name": "fixme" })
        return

    if req['method'] != 'jset.query':
        server.send_rsp(client_id, req, error=[-1, "unknown method"])
        return

    if 'params' not in req:
        server.send_rsp(client_id, req, error=[-1, "missing params"])
        return
    
    view = req['params']['view']
    if not view or view == "sys.views":
        server.send_rsp(client_id, req, result = { "name" : view_set})
        
    if view not in view_set:
        server.send_rsp(client_id, req, error=[-1, "wrong view name"])
        return

    result, error = datafectch(req['params'])
    server.send_rsp(client_id, req, result=result, error=error)

def init():
    global view_set, db, model
    conn = DatabaseConn()
    db = conn.get_conn()
    model = DataModel(db)
    view_set = model.apilist_set()
    print(view_set)

def run():
    global server

    init()
    server = jrpc_server.JRpcServer()
    server.on_call = on_call
    addr = "tcp://%s:%s"%(st.HOST, st.PORT)
    print("listen at " + addr)
    server.listen(addr)

    while True:
        time.sleep(1)

def datafectch(params):
    view = params['view']
    api = model.apilist_one(view)
    df = model.get_params(api)
    sql = model.get_datasql(df, args = params, apilist=api)
    print(sql)
    data = model.get_data(bind=api.source_id, sql=sql)
    if data['msg'] == st.DATA_MSG[0]:
        df = pd.read_json(json.dumps(data['data']), orient='split')
        return (_data(df), None)
    else:
        return (data['msg'], None)
    

def _data(df):
    data = {}
    for col in df.columns:
        data[col] = df[col].tolist()
    return data
    
if __name__ == "__main__":
    run()    
