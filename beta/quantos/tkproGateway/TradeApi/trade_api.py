from __future__ import absolute_import
from __future__ import division
from __future__ import print_function
from __future__ import unicode_literals

import json
from builtins import *

import pandas as pd

from . import utils


class EntrustOrder(object):
    def __init__(self, security, action, price, size):
        self.security = security
        self.action = action
        self.price = price
        self.size = size


def set_log_dir(log_dir):
    if log_dir:
        try:
            import jrpc
            jrpc.set_log_dir(log_dir)
        except Exception as e:
            print("Exception", e)


class TradeApi(object):
    def __init__(self, addr, use_jrpc=True, prod_type="jzts"):
        """
            use_jrpc:
                True     -- Use jrcp_client of C version, for jzts only
                False    -- Use pure python version
            prod_type:
                "jaqs"   -- jrpc_msgpack_wth_snappy
                "jzts"   -- jrpc_msgpack
        """
        
        self._remote = None
        if prod_type == "jzts":
            try:
                if use_jrpc:
                    import jrpc
                    self._remote = jrpc.JsonRpcClient()
                else:
                    from . import jrpc_py
                    self._remote = jrpc_py.JRpcClient(data_format="msgpack")
            except Exception as e:
                print("Exception", e)
            
            if not self._remote:
                from . import jrpc_py
                self._remote = jrpc_py.JRpcClient(data_format="msgpack")
        
        else:
            from . import jrpc_py
            self._remote = jrpc_py.JRpcClient(data_format="msgpack_snappy")
        
        self._remote.on_rpc_callback = self._on_rpc_callback
        self._remote.on_disconnected = self._on_disconnected
        self._remote.on_connected = self._on_connected
        self._remote.connect(addr)
        
        self._ordstatus_callback = None
        self._taskstatus_callback = None
        self._internal_order_callback = None
        self._trade_callback = None
        self._on_connection_callback = None
        self._connected = False
        self._username = ""
        self._password = ""
        self._strategy_id = 0
        self._strategy_selected = False
        self._data_format = "default"
    
    def __del__(self):
        self._remote.close()
    
    def _on_rpc_callback(self, method, data):
        # print "_on_rpc_callback:", method, data
        
        if method == "oms.orderstatus_ind":
            if self._data_format == "obj":
                data = utils.to_obj("Order", data)
            
            if self._ordstatus_callback:
                self._ordstatus_callback(data)
        
        elif method == "oms.taskstatus_ind":
            if self._data_format == "obj":
                data = utils.to_obj("TaskStatus", data)
            
            if self._taskstatus_callback:
                self._taskstatus_callback(data)
        
        elif method == "oms.trade_ind":
            if self._data_format == "obj":
                data = utils.to_obj("Trade", data)
            
            if self._trade_callback:
                self._trade_callback(data)
        
        elif method == "oms.internal_order_ind":
            if self._data_format == "obj":
                data = utils.to_obj("QuoteOrder", data)
            
            if self._internal_order_callback:
                self._internal_order_callback(data)
    
    def _on_disconnected(self):
        print("TradeApi: _on_disconnected")
        self._connected = False
        self._strategy_selected = False
        if self._on_connection_callback:
            self._on_connection_callback(False)
    
    def _on_connected(self):
        print("TradeApi: _on_connected")
        self._connected = True
        self._do_login()
        self._do_use_strategy()
        if self._on_connection_callback:
            self._on_connection_callback(True)
    
    def _check_session(self):
        if not self._connected:
            return (False, "no connection")
        
        if self._strategy_selected:
            return (True, "")
        
        r, msg = self._do_login()
        if not r: return (r, msg)
        if self._strategy_id:
            return self._do_use_strategy()
        else:
            return (r, msg)
    
    def set_data_format(self, format):
        self._data_format = format
    
    def set_connection_callback(self, callback):
        self._on_connection_callback = callback
    
    def set_ordstatus_callback(self, callback):
        self._ordstatus_callback = callback
    
    def set_trade_callback(self, callback):
        self._trade_callback = callback
    
    def set_task_callback(self, callback):
        self._taskstatus_callback = callback
    
    def set_quoteorder_callback(self, callback):
        self._internal_order_callback = callback
    
    def _get_format(self, format, default_format):
        if format:
            return format
        elif self._data_format != "default":
            return self._data_format
        else:
            return default_format
    
    def login(self, username, password, format=""):
        self._username = username
        self._password = password
        return self._do_login(format=format)
    
    def _do_login(self, format=""):
        # Shouldn't check connected flag here. ZMQ is a mesageq queue!
        # if !self._connected :
        #    return (False, "-1,no connection")
        
        if self._username and self._password:
            rpc_params = {"username": self._username,
                          "password": self._password}
            
            cr = self._remote.call("auth.login", rpc_params)
            f = self._get_format(format, "")
            if f != "obj" and f != "":
                f = ""
            return utils.extract_result(cr, format=f, class_name="UserInfo")
        else:
            return (False, "-1,empty username or password")
    
    def logout(self):
        rpc_params = {}
        
        cr = self._remote.call("auth.logout", rpc_params)
        return utils.extract_result(cr)
    
    def close(self):
        self._remote.close()
    
    def use_strategy(self, strategy_id):
        if strategy_id:
            self._strategy_id = strategy_id
            return self._do_use_strategy()
        else:
            # Query
            rpc_params = {"account_id": 0}
            
            cr = self._remote.call("auth.use_strategy", rpc_params)
            r, msg = utils.extract_result(cr)
            self._strategy_selected = r
            
            return (r, msg)
    
    def _do_use_strategy(self):
        if self._strategy_id:
            rpc_params = {"account_id": self._strategy_id}
            
            cr = self._remote.call("auth.use_strategy", rpc_params)
            r, msg = utils.extract_result(cr)
            self._strategy_selected = r
            
            return (r, msg)
        else:
            return (False, "-1,no strategy_id was specified")
    
    def confirm_internal_order(self, task_id, confirmed):
        """
        return (result, message)
        if result is None, message contains error information
        """
        
        r, msg = self._check_session()
        if not r: return (None, msg)
        
        rpc_params = {"task_id": task_id,
                      "confirmed": confirmed}
        
        cr = self._remote.call("oms.confirm_internal_order", rpc_params)
        return utils.extract_result(cr)
    
    def order(self, security, price, size, algo="", algo_param={}, userdata=""):
        """
        return (result, message)
        if result is None, message contains error information
        """
        
        r, msg = self._check_session()
        if not r: return (None, msg)
        
        rpc_params = {"security": security,
                      "price": price,
                      "size": int(size),
                      "algo": algo,
                      "algo_param": json.dumps(algo_param),
                      "user": self._username,
                      "userdata": userdata}
        
        cr = self._remote.call("oms.order", rpc_params)
        return utils.extract_result(cr)
    
    def place_order(self, security, action, price, size, algo="", algo_param={}, userdata=""):
        """
        return (result, message)
        if result is None, message contains error information
        """
        
        r, msg = self._check_session()
        if not r: return (None, msg)
        
        rpc_params = {"security": security,
                      "action": action,
                      "price": price,
                      "size": int(size),
                      "algo": algo,
                      "algo_param": json.dumps(algo_param),
                      "user": self._username,
                      "userdata": userdata}
        
        cr = self._remote.call("oms.place_order", rpc_params)
        return utils.extract_result(cr)
    
    def batch_order(self, orders, algo="", algo_param={}, userdata=""):
        """
        orders format:
            [ {"security": "000001.SZ", "action": "Buy", "price": 10.0, "size" : 100}, ... ]
        return (result, message)
        if result is None, message contains error information
        """
        
        if not orders or not isinstance(orders, (list, tuple)):
            return (None, "empty order")
        
        if isinstance(orders[0], EntrustOrder):
            tmp = []
            for o in orders:
                tmp.append({"security": o.security,
                            "price": o.price,
                            "size": int(o.size)})
            
            orders = tmp
        
        r, msg = self._check_session()
        if not r: return (None, msg)
        
        rpc_params = {"orders": orders,
                      "algo": algo,
                      "algo_param": json.dumps(algo_param),
                      "user": self._username,
                      "userdata": userdata}
        
        cr = self._remote.call("oms.batch_order", rpc_params)
        return utils.extract_result(cr)
    
    def place_batch_order(self, orders, algo="", algo_param={}, userdata=""):
        """
        orders format:
            [ {"security": "000001.SZ", "action": "Buy", "price": 10.0, "size" : 100}, ... ]
        return (result, message)
        if result is None, message contains error information
        """
        
        if not orders or not isinstance(orders, (list, tuple)):
            return (None, "empty order")
        
        if isinstance(orders[0], EntrustOrder):
            tmp = []
            for o in orders:
                tmp.append({"security": o.security,
                            "action": o.action,
                            "price": o.price,
                            "size": int(o.size)})
            
            orders = tmp
        
        r, msg = self._check_session()
        if not r: return (None, msg)
        
        rpc_params = {"orders": orders,
                      "algo": algo,
                      "algo_param": json.dumps(algo_param),
                      "user": self._username,
                      "userdata": userdata}
        
        cr = self._remote.call("oms.place_batch_order", rpc_params)
        return utils.extract_result(cr)
    
    def cancel_order(self, task_id):
        """
        return (result, message)
        if result is None, message contains error information
        """
        
        r, msg = self._check_session()
        if not r: return (None, msg)
        
        rpc_params = {"task_id": task_id}
        
        cr = self._remote.call("oms.cancel_order", rpc_params)
        return utils.extract_result(cr)
    
    def query_account(self, format=""):
        """
            return pd.dataframe
        """
        r, msg = self._check_session()
        if not r: return (None, msg)
        
        rpc_params = {}
        
        data_format = self._get_format(format, "pandas")
        if data_format == "pandas":
            rpc_params["format"] = "columnset"
        
        cr = self._remote.call("oms.query_account", rpc_params)
        
        return utils.extract_result(cr, format=data_format, class_name="Account")
    
    def query_position(self, mode="all", securities="", format=""):
        """
            securities: seperate by ","
            return pd.dataframe
        """
        
        r, msg = self._check_session()
        if not r: return (None, msg)
        
        rpc_params = {"mode": mode,
                      "security": securities}
        
        data_format = self._get_format(format, "pandas")
        if data_format == "pandas":
            rpc_params["format"] = "columnset"
        
        cr = self._remote.call("oms.query_position", rpc_params)
        
        return utils.extract_result(cr, format=data_format, class_name="Position")
    
    def query_net_position(self, mode="all", securities="", format=""):
        """
            securities: seperate by ","
            return pd.dataframe
        """
        
        r, msg = self._check_session()
        if not r: return (None, msg)
        
        rpc_params = {"mode": mode,
                      "security": securities}
        
        data_format = self._get_format(format, "pandas")
        if data_format == "pandas":
            rpc_params["format"] = "columnset"
        
        cr = self._remote.call("oms.query_net_position", rpc_params)
        
        return utils.extract_result(cr, format=data_format, class_name="NetPosition")
    
    def query_repo_contract(self, format=""):
        """
            securities: seperate by ","
            return pd.dataframe
        """
        
        r, msg = self._check_session()
        if not r: return (None, msg)
        
        rpc_params = {}
        
        cr = self._remote.call("oms.query_repo_contract", rpc_params)
        
        return utils.extract_result(cr, format=self._get_format(format, "pandas"), class_name="RepoContract")
    
    def query_task(self, task_id=-1, format=""):
        """
            task_id: -1 -- all
            return pd.dataframe
        """
        
        r, msg = self._check_session()
        if not r: return (None, msg)
        
        rpc_params = {"task_id": task_id}
        
        data_format = self._get_format(format, "pandas")
        if data_format == "pandas":
            rpc_params["format"] = "columnset"
        
        cr = self._remote.call("oms.query_task", rpc_params)
        
        return utils.extract_result(cr, format=data_format, class_name="Task")
    
    def query_order(self, task_id=-1, format=""):
        """
            task_id: -1 -- all
            return pd.dataframe
        """
        
        r, msg = self._check_session()
        if not r: return (None, msg)
        
        rpc_params = {"task_id": task_id}
        
        data_format = self._get_format(format, "pandas")
        if data_format == "pandas":
            rpc_params["format"] = "columnset"
        
        cr = self._remote.call("oms.query_order", rpc_params)
        
        return utils.extract_result(cr, format=data_format, class_name="Order")
    
    def query_trade(self, task_id=-1, format=""):
        """
            task_id: -1 -- all
            return pd.dataframe
        """
        
        r, msg = self._check_session()
        if not r: return (None, msg)
        
        rpc_params = {"task_id": task_id}
        
        data_format = self._get_format(format, "pandas")
        if data_format == "pandas":
            rpc_params["format"] = "columnset"
        
        cr = self._remote.call("oms.query_trade", rpc_params)
        
        return utils.extract_result(cr, format=data_format, class_name="Trade")
    
    def query_portfolio(self, format=""):
        """
            return pd.dataframe
        """
        
        r, msg = self._check_session()
        if not r: return (None, msg)
        
        rpc_params = {}
        
        data_format = self._get_format(format, "pandas")
        if data_format == "pandas":
            rpc_params["format"] = "columnset"
        
        cr = self._remote.call("pms.query_portfolio", rpc_params)
        
        return utils.extract_result(cr, index_column="security", format=data_format, class_name="NetPosition")
    
    def goal_portfolio(self, positions, algo="", algo_param={}, userdata=""):
        """
        positions format:
            [ {"security": "000001.SZ", "ref_price": 10.0, "size" : 100}, ...]
        return (result, message)
        if result is None, message contains error information
        """
        
        r, msg = self._check_session()
        if not r: return (False, msg)
        
        if type(positions) is pd.core.frame.DataFrame:
            tmp = []
            for i in range(0, len(positions)):
                tmp.append({'security': positions.index[i], 'ref_price': float(positions['ref_price'][i]),
                            "size": int(positions['size'][i])})
            positions = tmp
        
        rpc_params = {"positions": positions,
                      "algo": algo,
                      "algo_param": json.dumps(algo_param),
                      "user": self._username,
                      "userdata": userdata}
        
        cr = self._remote.call("pms.goal_portfolio", rpc_params)
        return utils.extract_result(cr)
    
    def basket_order(self, orders, algo="", algo_param={}, userdata=""):
        """
        orders format:
            [ {"security": "000001.SZ", "ref_price": 10.0, "inc_size" : 100}, ...]
        return (result, message)
        if result is None, message contains error information
        """
        
        r, msg = self._check_session()
        if not r: return (False, msg)
        
        if type(orders) is pd.core.frame.DataFrame:
            tmp = []
            for i in range(0, len(orders)):
                tmp.append({'security': orders.index[i], 'ref_price': float(orders['ref_price'][i]),
                            "inc_size": int(orders['inc_size'][i])})
            orders = tmp
        
        rpc_params = {"orders": orders,
                      "algo": algo,
                      "algo_param": json.dumps(algo_param),
                      "user": self._username,
                      "userdata": userdata}
        
        cr = self._remote.call("pms.basket_order", rpc_params)
        return utils.extract_result(cr)
    
    def stop_portfolio(self):
        """
        return (result, message)
        if result is None, message contains error information
        """
        
        r, msg = self._check_session()
        if not r: return (False, msg)
        
        rpc_params = {}
        
        cr = self._remote.call("pms.stop_portfolio", rpc_params)
        return utils.extract_result(cr)
    
    def query_universe(self, format=""):
        
        r, msg = self._check_session()
        if not r: return (None, msg)
        
        rpc_params = {}
        data_format = self._get_format(format, "pandas")
        if data_format == "pandas":
            rpc_params["format"] = "columnset"
        
        cr = self._remote.call("oms.query_universe", rpc_params)
        
        return utils.extract_result(cr, format=data_format, class_name="UniverseItem")
    
    def set_heartbeat(self, interval, timeout):
        self._remote.set_hearbeat_options(interval, timeout)
        print("heartbeat_interval =", self._remote._heartbeat_interval, ", heartbeat_timeout =",
              self._remote._heartbeat_timeout)
