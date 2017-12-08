from __future__ import absolute_import
from __future__ import division
from __future__ import print_function
from __future__ import unicode_literals

from builtins import *
import time

import numpy as np

from . import jrpc_py
# import jrpc
from . import utils


# def set_log_dir(log_dir):
#    if log_dir:
#        jrpc.set_log_dir(log_dir)

class DataApiCallback(object):
    """DataApi Callback

    def on_quote(quote):
        pass
        
    def on_connection()
    """
    
    def __init__(self):
        self.on_quote = None


class DataApi(object):
    """
    Abstract base class providing both historic and live data
    from various data sources.
    Current API version: 1.0   

    Attributes
    ----------
    

    Methods
    -------
    subscribe
    quote
    daily
    bar
    bar_quote    

    """
    
    def __init__(self, addr="tcp://data.tushare.org:8910", use_jrpc=False):
        """Create DataApi client.
        
        If use_jrpc, try to load the C version of JsonRpc. If failed, use pure
        Python version of JsonRpc.
        """
        self._remote = None
        #        if use_jrpc:
        #            try:
        #                import jrpc
        #                self._remote = jrpc.JRpcClient()
        #            except Exception as e:
        #                print "Can't load jrpc", e.message
        
        if not self._remote:
            self._remote = jrpc_py.JRpcClient()
        
        self._remote.on_rpc_callback = self._on_rpc_callback
        self._remote.on_disconnected = self._on_disconnected
        self._remote.on_connected = self._on_connected
        self._remote.connect(addr)
        
        self._on_jsq_callback = None
        
        self._connected = False
        self._loggined = False
        self._username = ""
        self._password = ""
        self._data_format = "default"
        self._callback = None
        self._schema = []
        self._schema_id = 0
        self._schema_map = {}
        self._sub_hash = ""
        self._subscribed_set = set()
        self._timeout = 20
    
    def login(self, username, password):
        
        """
        Login before using data api.

        Parameters
        ----------
        username : str
            username
        password : str
            password
        """
        for i in range(3):
            if self._connected:
                break
            time.sleep(1)
        
        if not self._connected:
            return (None, "-1,no connection")
        
        self._username = username
        self._password = password
        return self._do_login()
    
    def logout(self):
        """
        Logout to stop using the data api or switch users.

        """
        self._loggined = None
        
        rpc_params = {}
        
        cr = self._remote.call("auth.logout", rpc_params)
        return utils.extract_result(cr)
    
    def close(self):
        """
        Close the data api.

        """
        
        self._remote.close()
        
        # def set_callback(self, callback):
    
    # self._callback = callback
    
    def set_timeout(self, timeout):
        """
        Set timeout for data api. 
        Default timeout is 20s. 

        Parameters
        ----------
        timeout : int
            the max waiting time for the api return
        
        """
        self._timeout = timeout
    
    def set_data_format(self, format):
        """Set queried data format.
        
        Available formats are:
            ""        -- Don't convert data, usually the type is map
            "pandas"  -- Convert table likely data to DataFrame
        """
        self._data_format = format
    
    def set_heartbeat(self, interval, timeout):
        self._remote.set_hearbeat_options(interval, timeout)
    
    def quote(self, symbol, fields="", data_format="", **kwargs):
        
        r, msg = self._call_rpc("jsq.query",
                                self._get_format(data_format, "pandas"),
                                "Quote",
                                _index_column="symbol",
                                symbol=str(symbol),
                                fields=fields,
                                **kwargs)
        return (r, msg)
    
    def bar(self, symbol, start_time=200000, end_time=160000,
            trade_date=0, freq="1m", fields="", data_format="", **kwargs):
        
        """
        Query minute bars of various type, return DataFrame.

        Parameters
        ----------
        symbol : str
            support multiple securities, separated by comma.
        start_time : int (HHMMSS) or str ('HH:MM:SS')
            Default is market open time.
        end_time : int (HHMMSS) or str ('HH:MM:SS')
            Default is market close time.
        trade_date : int (YYYMMDD) or str ('YYYY-MM-DD')
            Default is current trade_date.
        fields : str, optional
            separated by comma ',', default "" (all fields included).
        freq : trade.common.MINBAR_TYPE, optional
            {'1m', '5m', '15m'}, Minute bar type, default is '1m'

        Returns
        -------
        df : pd.DataFrame
            columns:
                symbol, code, date, time, trade_date, freq, open, high, low, close, volume, turnover, vwap, oi
        msg : str
            error code and error message joined by comma

        Examples
        --------
        df, msg = api.bar("000001.SH,cu1709.SHF", start_time="09:56:00", end_time="13:56:00",
                          trade_date="20170823", fields="open,high,low,last,volume", freq="5m")

        """
        
        begin_time = utils.to_time_int(start_time)
        if (begin_time == -1):
            return (-1, "Begin time format error")
        end_time = utils.to_time_int(end_time)
        if (end_time == -1):
            return (-1, "End time format error")
        trade_date = utils.to_date_int(trade_date)
        if (trade_date == -1):
            return (-1, "Trade date format error")
        
        return self._call_rpc("jsi.query",
                              self._get_format(data_format, "pandas"),
                              "Bar",
                              symbol=str(symbol),
                              fields=fields,
                              freq=freq,
                              trade_date=trade_date,
                              begin_time=begin_time,
                              end_time=end_time,
                              **kwargs)
    
    def bar_quote(self, symbol, start_time=200000, end_time=160000,
                  trade_date=0, freq="1m", fields="", data_format="", **kwargs):
        """
        Query minute bars of various type, return DataFrame. 
        It will also return ask/bid informations of the last quote in this bar  


        Parameters
        ----------
        symbol : str
            support multiple securities, separated by comma.
        start_time : int (HHMMSS) or str ('HH:MM:SS')
            Default is market open time.
        end_time : int (HHMMSS) or str ('HH:MM:SS')
            Default is market close time.
        trade_date : int (YYYMMDD) or str ('YYYY-MM-DD')
            Default is current trade_date.
        fields : str, optional
            separated by comma ',', default "" (all fields included).
        freq : trade.common.MINBAR_TYPE, optional
            {'1m', '5m', '15m'}, Minute bar type, default is '1m'

        Returns
        -------
        df : pd.DataFrame
            columns:
                symbol, code, date, time, trade_date, freq, open, high, low, close, volume, turnover, vwap, oi,
                askprice1, askprice2, askprice3, askprice4, askprice5,
                bidprice1, bidprice2, bidprice3, bidprice4, bidprice5,
                askvolume1, askvolume2, askvolume3, askvolume4, askvolume5, 
                bidvolume1, bidvolume2, bidvolume3, bidvolume4, bidvolume5

        msg : str
            error code and error message joined by comma

        Examples
        --------
        df, msg = api.bar_quote("000001.SH,cu1709.SHF", start_time="09:56:00", end_time="13:56:00",
                          trade_date="20170823", fields="open,high,low,last,volume", freq="5m")

        """
        begin_time = utils.to_time_int(start_time)
        if (begin_time == -1):
            return (-1, "Begin time format error")
        end_time = utils.to_time_int(end_time)
        if (end_time == -1):
            return (-1, "End time format error")
        trade_date = utils.to_date_int(trade_date)
        if (trade_date == -1):
            return (-1, "Trade date format error")
        
        return self._call_rpc("jsi.bar_view",
                              self._get_format(data_format, "pandas"),
                              "BarQuote",
                              symbol=str(symbol),
                              fields=fields,
                              freq=freq,
                              trade_date=trade_date,
                              begin_time=begin_time,
                              end_time=end_time,
                              **kwargs)
    
    def daily(self, symbol, start_date, end_date,
              adjust_mode=None, freq="1d", fields="",
              data_format="", **kwargs):
        
        """
        Query dar bar,
        support auto-fill suspended securities data,
        support auto-adjust for splits, dividends and distributions.

        Parameters
        ----------
        symbol : str
            support multiple securities, separated by comma.
        start_date : int or str
            YYYMMDD or 'YYYY-MM-DD'
        end_date : int or str
            YYYMMDD or 'YYYY-MM-DD'
        fields : str, optional
            separated by comma ',', default "" (all fields included).
        adjust_mode : str or None, optional
            None for no adjust;
            'pre' for forward adjust;
            'post' for backward adjust.

        Returns
        -------
        df : pd.DataFrame
            columns:
                symbol, code, trade_date, open, high, low, close, volume, turnover, vwap, oi, suspended
        msg : str
            error code and error message joined by comma

        Examples
        --------
        df, msg = api.daily("000001.SH,cu1709.SHF",start_date=20170503, end_date=20170708,
                            fields="open,high,low,last,volume", adjust_mode = "post")

        """
        
        if adjust_mode == None:
            adjust_mode = "none"
        
        begin_date = utils.to_date_int(start_date)
        if (begin_date == -1):
            return (-1, "Begin date format error")
        end_date = utils.to_date_int(end_date)
        if (end_date == -1):
            return (-1, "End date format error")
        
        return self._call_rpc("jsd.query",
                              self._get_format(data_format, "pandas"),
                              "Daily",
                              symbol=str(symbol),
                              fields=fields,
                              begin_date=begin_date,
                              end_date=end_date,
                              adjust_mode=adjust_mode,
                              freq=freq,
                              **kwargs)
    
    def query(self, view, filter="", fields="", data_format="", **kwargs):
        """
        Get various reference data.
        
        Parameters
        ----------
        view : str
            data source.
        fields : str
            Separated by ','
        filter : str
            filter expressions.
        kwargs

        Returns
        -------
        df : pd.DataFrame
        msg : str
            error code and error message, joined by ','
        
        Examples
        --------
        res3, msg3 = ds.query("lb.secDailyIndicator", fields="price_level,high_52w_adj,low_52w_adj",\
                              filter="start_date=20170907&end_date=20170907",\
                              data_format='pandas')
            view does not change. fileds can be any field predefined in reference data api.

        """
        return self._call_rpc("jset.query",
                              self._get_format(data_format, "pandas"),
                              "JSetData",
                              view=view,
                              fields=fields,
                              filter=filter,
                              **kwargs)
    
    def subscribe(self, symbol, func=None, fields=""):
        """Subscribe securites
      
        This function adds new securities to subscribed list on the server. If
        success, return subscribed codes.
      
        If securities is empty, return current subscribed codes.
        """
        r, msg = self._check_session()
        if not r:
            return (r, msg)
        
        if func:
            self._on_jsq_callback = func
        
        rpc_params = {"symbol": symbol,
                      "fields": fields}
        
        cr = self._remote.call("jsq.subscribe", rpc_params)
        
        rsp, msg = utils.extract_result(cr, data_format="", class_name="SubRsp")
        if not rsp:
            return (rsp, msg)
        
        new_codes = [x.strip() for x in symbol.split(',') if x]
        
        self._subscribed_set = self._subscribed_set.union(set(new_codes))
        self._schema_id = rsp['schema_id']
        self._schema = rsp['schema']
        self._sub_hash = rsp['sub_hash']
        self._make_schema_map()
        return (rsp['symbols'], msg)
    
    def unsubscribe(self, symbol):
        """Unsubscribe securities.

        Unscribe codes and return list of subscribed code.
        """
        assert False, "NOT IMPLEMENTED"
    
    def __del__(self):
        self._remote.close()
    
    def _on_disconnected(self):
        """JsonRpc callback"""
        #        print "DataApi: _on_disconnected"
        self._connected = False
        
        if self._callback:
            self._callback("connection", False)
    
    def _on_connected(self):
        """JsonRpc callback"""
        self._connected = True
        
        self._do_login()
        self._do_subscribe()
        
        if self._callback:
            self._callback("connection", True)
    
    def _check_session(self):
        if not self._connected:
            return (False, "no connection")
        elif self._loggined:
            return (True, "")
        elif self._username and self._password:
            return self._do_login()
        else:
            return (False, "no login session")
    
    def _get_format(self, format, default_format):
        if format:
            return format
        elif self._data_format != "default":
            return self._data_format
        else:
            return default_format
    
    def set_callback(self, callback):
        self._callback = callback
    
    def _convert_quote_ind(self, quote_ind):
        """Convert original quote_ind to a map.
        
        The original quote_ind contains field index instead of field name!
        """
        
        if quote_ind['schema_id'] != self._schema_id:
            return None
        
        indicators = quote_ind['indicators']
        values = quote_ind['values']
        
        max_index = len(self._schema)
        
        quote = {}
        for i in range(len(indicators)):
            if indicators[i] < max_index:
                quote[self._schema_map[indicators[i]]['name']] = values[i]
            else:
                quote[str(indicators[i])] = values[i]
        
        return quote
    
    def _on_rpc_callback(self, method, data):
        # print "_on_rpc_callback:", method, data
        
        try:
            if method == "jsq.quote_ind":
                if self._on_jsq_callback:
                    q = self._convert_quote_ind(data)
                    if q:
                        self._on_jsq_callback("quote", q)
            
            elif method == ".sys.heartbeat":
                if 'sub_hash' in data:
                    if self._sub_hash and self._sub_hash != data['sub_hash']:
                        print("sub_hash is not same", self._sub_hash, data['sub_hash'])
                        self._do_subscribe()
        
        except Exception as e:
            print("Can't load jrpc", e.message)
    
    def _call_rpc(self, method, data_format, data_class, **kwargs):
        
        r, msg = self._check_session()
        if not r:
            return (r, msg)
        
        index_column = None
        rpc_params = {}
        for key, value in kwargs.items():
            if key  == '_index_column':
                index_column = value
            else:
                if isinstance(value, (int, np.integer)):
                    value = int(value)
                rpc_params[key] = value
        
        cr = self._remote.call(method, rpc_params, timeout=self._timeout)
        
        return utils.extract_result(cr, data_format=data_format, index_column=index_column, class_name=data_class)
    
    def _make_schema_map(self):
        self._schema_map = {}
        for schema in self._schema:
            self._schema_map[schema['id']] = schema
    
    def _do_login(self):
        # Shouldn't check connected flag here. ZMQ is a mesageq queue!
        # if !self._connected :
        #    return (False, "-1,no connection")
        
        if self._username and self._password:
            rpc_params = {"username": self._username,
                          "password": self._password}
            
            cr = self._remote.call("auth.login", rpc_params)
            r, msg = utils.extract_result(cr, data_format="", class_name="UserInfo")
            self._loggined = r
            return (r, msg)
        else:
            self._loggined = None
            return (False, "-1,empty username or password")
    
    def _do_subscribe(self):
        """Subscribe again when reconnected or hash_code is not same"""
        if not self._subscribed_set: return
        
        codes = list(self._subscribed_set)
        codes.sort()
        
        # XXX subscribe with default fields!
        rpc_params = {"symbol": ",".join(codes),
                      "fields": ""}
        
        cr = self._remote.call("jsq.subscribe", rpc_params)
        
        rsp, msg = utils.extract_result(cr, data_format="", class_name="SubRsp")
        if not rsp:
            # return (rsp, msg)
            return
        
        self._schema_id = rsp['schema_id']
        self._schema = rsp['schema']
        self._sub_hash = rsp['sub_hash']
        # return (rsp.securities, msg)
        
        self._make_schema_map()
