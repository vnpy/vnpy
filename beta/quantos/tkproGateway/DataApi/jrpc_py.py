from __future__ import absolute_import
from __future__ import division
from __future__ import print_function
from __future__ import unicode_literals

from builtins import *

import zmq
import time
import random

try:
    import queue
except ImportError:
    import queue as queue
import threading
import msgpack
import snappy
import copy

qEmpty = copy.copy(queue.Empty)


def _unpack(str):
    if str.startswith(b'S'):
        tmp = snappy.uncompress(str[1:])
        # print "SNAPPY: ", len(str), len(tmp)
        obj = msgpack.loads(tmp, encoding='utf-8')
    elif str.startswith(b'\0'):
        obj = msgpack.loads(str[1:], encoding='utf-8')
    else:
        return None
    
    return obj


def _pack(obj):
    # print "pack", obj
    tmp = msgpack.dumps(obj, encoding='utf-8')
    if len(tmp) > 1000:
        return b'S' + snappy.compress(tmp)
    else:
        return b'\0' + tmp


class JRpcClient(object):
    def __init__(self):
        self._waiter_lock = threading.Lock()
        self._waiter_map = {}
        
        self._should_close = False
        self._next_callid = 0
        self._send_lock = threading.Lock()
        self._callid_lock = threading.Lock()
        
        self._last_heartbeat_rsp_time = 0
        self._connected = False
        
        self.on_disconnected = None
        self.on_rpc_callback = None
        self._callback_queue = queue.Queue()
        self._call_wait_queue = queue.Queue()
        
        self._ctx = zmq.Context()
        self._pull_sock = self._ctx.socket(zmq.PULL)
        self._pull_sock.bind("inproc://pull_sock")
        self._push_sock = self._ctx.socket(zmq.PUSH)
        self._push_sock.connect("inproc://pull_sock")
        
        self._heartbeat_interval = 1
        self._heartbeat_timeout = 3
        
        self._addr = None
        
        t = threading.Thread(target=self._recv_run)
        t.setDaemon(True)
        t.start()
        self._recv_thread = t
        
        t = threading.Thread(target=self._callback_run)
        t.setDaemon(True)
        t.start()
        self._callback_thread = t
    
    def __del__(self):
        self.close()
    
    def next_callid(self):
        self._callid_lock.acquire()
        self._next_callid += 1
        callid = self._next_callid
        self._callid_lock.release()
        return callid
    
    def set_heartbeat_options(self, interval, timeout):
        self._heartbeat_interval = interval
        self._heartbeat_timeout = timeout
    
    def _recv_run(self):
        
        heartbeat_time = 0
        
        poller = zmq.Poller()
        poller.register(self._pull_sock, zmq.POLLIN)
        
        remote_sock = None
        
        while not self._should_close:
            
            try:
                if self._connected and time.time() - self._last_heartbeat_rsp_time > self._heartbeat_timeout:
                    self._connected = False
                    if self.on_disconnected: self._async_call(self.on_disconnected)
                
                if remote_sock and time.time() - heartbeat_time > self._heartbeat_interval:
                    self._send_hearbeat()
                    heartbeat_time = time.time()
                
                socks = dict(poller.poll(500))
                if self._pull_sock in socks and socks[self._pull_sock] == zmq.POLLIN:
                    cmd = self._pull_sock.recv()
                    if cmd == b"CONNECT":
                        # print time.ctime(), "CONNECT " + self._addr
                        if remote_sock:
                            poller.unregister(remote_sock)
                            remote_sock.close()
                            remote_sock = None
                        
                        remote_sock = self._do_connect()
                        
                        if remote_sock:
                            poller.register(remote_sock, zmq.POLLIN)
                    
                    elif cmd.startswith(b"SEND:") and remote_sock:
                        # print time.ctime(), "SEND " + cmd[5:]
                        remote_sock.send(cmd[5:])
                
                if remote_sock and remote_sock in socks and socks[remote_sock] == zmq.POLLIN:
                    data = remote_sock.recv()
                    if data:
                        # if not data.find("heartbeat"):
                        #    print time.ctime(), "RECV", data
                        self._on_data_arrived(data)
            
            except zmq.error.Again as e:
                # print "RECV timeout: ", e
                pass
            except Exception as e:
                print("_recv_run:", e)
    
    def _callback_run(self):
        while not self._should_close:
            try:
                r = self._callback_queue.get(timeout=1)
                if r:
                    r()
            except qEmpty as e:
                pass
            except TypeError as e:
                if str(e) == "'NoneType' object is not callable":
                    pass
                else:
                    print("_callback_run {}".format(r), type(e), e)
            except Exception as e:
                print("_callback_run {}".format(r), type(e), e)
    
    def _async_call(self, func):
        self._callback_queue.put(func)
    
    def _send_request(self, json):
        
        try:
            self._send_lock.acquire()
            self._push_sock.send(b"SEND:" + json)
        
        finally:
            self._send_lock.release()
    
    def connect(self, addr):
        self._addr = addr
        self._push_sock.send_string('CONNECT', encoding='utf-8')
    
    def _do_connect(self):
        
        client_id = str(random.randint(1000000, 100000000))
        
        socket = self._ctx.socket(zmq.DEALER)
        identity = (client_id) + '$' + str(random.randint(1000000, 1000000000))
        identity = identity.encode('utf-8')
        socket.setsockopt(zmq.IDENTITY, identity)
        socket.setsockopt(zmq.RCVTIMEO, 500)
        socket.setsockopt(zmq.SNDTIMEO, 500)
        socket.setsockopt(zmq.LINGER, 0)
        socket.connect(self._addr)
        
        return socket
    
    def close(self):
        self._should_close = True
        self._callback_thread.join()
        self._recv_thread.join()
    
    def _on_data_arrived(self, str):
        try:
            msg = _unpack(str)
            # print "RECV", msg
            
            if not msg:
                print("wrong message format")
                return
            
            if 'method' in msg and msg['method'] == '.sys.heartbeat':
                self._last_heartbeat_rsp_time = time.time()
                if not self._connected:
                    self._connected = True
                    if self.on_connected:
                        self._async_call(self.on_connected)
                
                # Let user has a chance to check message in .sys.heartbeat
                if 'result' in msg and self.on_rpc_callback:
                    self._async_call(lambda: self.on_rpc_callback(msg['method'], msg['result']))
            
            elif 'id' in msg and msg['id']:
                
                # Call result
                id = int(msg['id'])
                
                if self._waiter_lock.acquire():
                    if id in self._waiter_map:
                        q = self._waiter_map[id]
                        if q: q.put(msg)
                    self._waiter_lock.release()
            else:
                # Notification message
                if 'method' in msg and 'result' in msg and self.on_rpc_callback:
                    self._async_call(lambda: self.on_rpc_callback(msg['method'], msg['result']))
        
        except Exception as e:
            print("_on_data_arrived:", e)
            pass
    
    def _send_hearbeat(self):
        msg = {'jsonrpc': '2.0',
               'method': '.sys.heartbeat',
               'params': {'time': time.time()},
               'id': str(self.next_callid())}
        json_str = _pack(msg)
        self._send_request(json_str)
    
    def _alloc_wait_queue(self):
        self._waiter_lock.acquire()
        if self._call_wait_queue:
            q = self._call_wait_queue
            self._call_wait_queue = None
        else:
            q = queue.Queue()
        self._waiter_lock.release()
        return q
    
    def _free_wait_queue(self, q):
        self._waiter_lock.acquire()
        if not self._call_wait_queue:
            self._call_wait_queue = q
        else:
            del q
        self._waiter_lock.release()
    
    def call(self, method, params, timeout=6):
        # print "call", method, params, timeout
        callid = self.next_callid()
        if timeout:
            q = self._alloc_wait_queue()
            
            self._waiter_lock.acquire()
            self._waiter_map[callid] = q
            self._waiter_lock.release()
        
        msg = {'jsonrpc': '2.0',
               'method': method,
               'params': params,
               'id': str(callid)}
        
        # print "SEND", msg
        json_str = _pack(msg)
        self._send_request(json_str)
        
        if timeout:
            ret = {}
            try:
                r = q.get(timeout=timeout)
                q.task_done()
            except qEmpty:
                r = None
            
            self._waiter_lock.acquire()
            self._waiter_map[callid] = None
            self._waiter_lock.release()
            self._free_wait_queue(q)
            
            if r:
                if 'result' in r:
                    ret['result'] = r['result']
                
                if 'error' in r:
                    ret['error'] = r['error']
            
            return ret if ret else {'error': {'error': -1, 'message': "timeout"}}
        else:
            return {'result': True}
