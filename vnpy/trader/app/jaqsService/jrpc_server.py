import zmq
import Queue
import threading
import msgpack
import snappy
import traceback
import time

def _unpack(str) :

    if str[0] == 'S':
        tmp = snappy.uncompress(str[1:])
        obj = msgpack.loads(tmp)
    elif str[0] == '\0':
        obj = msgpack.loads(str[1:])
    else:
        return None

    #print "UNPACK", obj
    return obj

def _pack(obj) :
#     print "PACK", obj
    tmp = msgpack.dumps(obj)
    if len(tmp) > 1000:
        return 'S'  + snappy.compress(tmp)
    else:
        return '\0' + tmp

class JRpcServer :
    
    def __init__(self) :
        self._waiter_lock = threading.Lock()
        self._waiter_map = {}

        self._should_close = False
        self._send_lock = threading.Lock()

        self._callback_queue = Queue.Queue()

        self._ctx = zmq.Context()
        self._pull_sock = self._ctx.socket(zmq.PULL)
        self._pull_sock.bind("inproc://pull_sock")
        self._push_sock = self._ctx.socket(zmq.PUSH)
        self._push_sock.connect("inproc://pull_sock")

        self.on_call = None

        t = threading.Thread(target=self._recv_run)
        t.setDaemon(True)
        t.start()

        t = threading.Thread(target=self._callback_run)
        t.setDaemon(True)
        t.start()
        
    def __del__(self):
        self.close()

#    def set_on_call(self, on_call):
#        """def on_call(client_id, req_msg)"""
#        self._on_call = on_call

    def _recv_run(self):


        poller = zmq.Poller()
        poller.register(self._pull_sock, zmq.POLLIN)

        remote_sock = None
        
        #client_addr_map = {}

        while not self._should_close:

            try:
                socks = dict(poller.poll(500))
                if self._pull_sock in socks and socks[self._pull_sock] == zmq.POLLIN:
                    msgs = self._pull_sock.recv_multipart()
                    if len(msgs) == 2:
                        if remote_sock:
                            # [addr, data]
                            #print "send data", msgs[0], msgs[1]
                            remote_sock.send_multipart(msgs)
                    elif len(msgs) == 1:
                        cmd = msgs[0]
                        if cmd == "LISTEN":
                            if remote_sock:
                                poller.unregister(remote_sock)
                                remote_sock.close()
                                remote_sock = None
    
                            remote_sock = self._do_listen()

                            if remote_sock :
                                poller.register(remote_sock, zmq.POLLIN)

                        elif cmd == "CLOSE":
                            self._should_close = True
                            break

                if remote_sock and remote_sock in socks and socks[remote_sock] == zmq.POLLIN:
                    msgs = remote_sock.recv_multipart()
                    if len(msgs) == 2:
                        identity  = msgs[0]
                        data      = msgs[1]                        
                        #client_id = identity.split('$')                    
                        #client_addr_map[client_id] = identity
                        self._on_data_arrived(identity, data)

            except zmq.error.Again, e:
                #print "RECV timeout: ", e
                pass
            except Exception, e:
                print("_recv_run:", e)

    def _callback_run(self):
        while not self._should_close:
            try:
                r = self._callback_queue.get(timeout = 1)
                if r :
                    r()
            except Queue.Empty, e:
                pass

            except Exception, e:
                traceback.print_exc(e)
                print "_callback_run", type(e), e

    def _async_call(self, func):
        self._callback_queue.put( func )
            
    def listen(self, addr) :
        self._addr = addr
        self._push_sock.send("LISTEN")


    def _do_listen(self):

        socket = self._ctx.socket(zmq.ROUTER)
        socket.setsockopt(zmq.RCVTIMEO, 1000)
        socket.setsockopt(zmq.SNDTIMEO, 1000)
        socket.setsockopt(zmq.LINGER, 0)
        socket.bind(self._addr)

        return socket

    def close(self):
        self._should_close = True
        self.push_sock.send("CLOSE")

    def _send(self, data, addr):
        self._send_lock.acquire()

        #self._push_sock.send(addr, flags=zmq.SNDMORE)
        #self._push_sock.send(data)
        self._push_sock.send_multipart([addr, data])
        
        self._send_lock.release()
        
    def _on_data_arrived(self, identity, data):
        try:
            msg = _unpack(data)
            #print "RECV", msg

            if not msg:
                print "wrong message format"
                return

            method = msg['method'] if msg.has_key('method') else None

            call_id = msg['id'] if msg.has_key('id') and msg['id'] else None

            if call_id and method:
                if method == ".sys.heartbeat":
                    # Unlike scala implementation, here reply to client directly
                    rsp_msg = { 'jsonrpc' : '2.0',
                                'method'  : method,
                                'result'  : { "time" : time.time() },
                                'id'      : call_id }

                    self._send( _pack(rsp_msg), identity)
                if self.on_call :
                    self._async_call( lambda : self.on_call(identity, msg))

        except Exception, e:
            print( "_on_data_arrived:", e)
            pass
    

    def send_rsp(self, client_id, req, result=None, error=None):
        """send response message to client
        
        example:
            send_rsp(client_id, req, result={'data': 123})
            send_rsp(client_id, req, error=(-1, "wrong argument"))
        """
        
        if req['method'] == '.sys.heartbeat':
            return

        rsp_msg = { 'jsonrpc' : '2.0',
                    'method'  : req["method"],
                    'id'      : req['id'] }

        if result is not None:
            rsp_msg['result'] = result

        if error is not None:
            rsp_msg['error'] = {'error': error[0], 'message' : error[1]}

        self._send(_pack(rsp_msg), client_id)