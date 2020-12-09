//+------------------------------------------------------------------+
//| Module: SocketOptions.mqh                                        |
//| This file is part of the mql-zmq project:                        |
//|     https://github.com/dingmaotu/mql-zmq                         |
//|                                                                  |
//| Copyright 2016-2017 Li Ding <dingmaotu@hotmail.com>              |
//|                                                                  |
//| Licensed under the Apache License, Version 2.0 (the "License");  |
//| you may not use this file except in compliance with the License. |
//| You may obtain a copy of the License at                          |
//|                                                                  |
//|     http://www.apache.org/licenses/LICENSE-2.0                   |
//|                                                                  |
//| Unless required by applicable law or agreed to in writing,       |
//| software distributed under the License is distributed on an      |
//| "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND,     |
//| either express or implied.                                       |
//| See the License for the specific language governing permissions  |
//| and limitations under the License.                               |
//+------------------------------------------------------------------+
#property strict

#include <Mql/Lang/Native.mqh>

#import "libzmq.dll"
// We can overload the same function for different data types
// as in the C level the optval paramter is just a pointer
#define SOCKOPT_OVERLOAD_ARRAY(TYPE) \
int zmq_setsockopt(intptr_t s,int option,const TYPE &optval[],\
                   size_t optvallen);\
int zmq_getsockopt(intptr_t s,int option,TYPE &optval[],\
                   size_t &optvallen);\

#define SOCKOPT_OVERLOAD(TYPE) \
int zmq_setsockopt(intptr_t s,int option,const TYPE &optval,\
                   size_t optvallen);\
int zmq_getsockopt(intptr_t s,int option,TYPE &optval,\
                   size_t &optvallen);\

SOCKOPT_OVERLOAD_ARRAY(uchar)
SOCKOPT_OVERLOAD(long)
SOCKOPT_OVERLOAD(ulong)
SOCKOPT_OVERLOAD(int)
SOCKOPT_OVERLOAD(uint)
#import

// Socket options
#define ZMQ_AFFINITY 4
#define ZMQ_IDENTITY 5
#define ZMQ_SUBSCRIBE 6
#define ZMQ_UNSUBSCRIBE 7
#define ZMQ_RATE 8
#define ZMQ_RECOVERY_IVL 9
#define ZMQ_SNDBUF 11
#define ZMQ_RCVBUF 12
#define ZMQ_RCVMORE 13
#define ZMQ_FD 14
#define ZMQ_EVENTS 15
#define ZMQ_TYPE 16
#define ZMQ_LINGER 17
#define ZMQ_RECONNECT_IVL 18
#define ZMQ_BACKLOG 19
#define ZMQ_RECONNECT_IVL_MAX 21
#define ZMQ_MAXMSGSIZE 22
#define ZMQ_SNDHWM 23
#define ZMQ_RCVHWM 24
#define ZMQ_MULTICAST_HOPS 25
#define ZMQ_RCVTIMEO 27
#define ZMQ_SNDTIMEO 28
#define ZMQ_LAST_ENDPOINT 32
#define ZMQ_ROUTER_MANDATORY 33
#define ZMQ_TCP_KEEPALIVE 34
#define ZMQ_TCP_KEEPALIVE_CNT 35
#define ZMQ_TCP_KEEPALIVE_IDLE 36
#define ZMQ_TCP_KEEPALIVE_INTVL 37
#define ZMQ_IMMEDIATE 39
#define ZMQ_XPUB_VERBOSE 40
#define ZMQ_ROUTER_RAW 41
#define ZMQ_IPV6 42
#define ZMQ_MECHANISM 43
#define ZMQ_PLAIN_SERVER 44
#define ZMQ_PLAIN_USERNAME 45
#define ZMQ_PLAIN_PASSWORD 46
#define ZMQ_CURVE_SERVER 47
#define ZMQ_CURVE_PUBLICKEY 48
#define ZMQ_CURVE_SECRETKEY 49
#define ZMQ_CURVE_SERVERKEY 50
#define ZMQ_PROBE_ROUTER 51
#define ZMQ_REQ_CORRELATE 52
#define ZMQ_REQ_RELAXED 53
#define ZMQ_CONFLATE 54
#define ZMQ_ZAP_DOMAIN 55
#define ZMQ_ROUTER_HANDOVER 56
#define ZMQ_TOS 57
#define ZMQ_CONNECT_RID 61
#define ZMQ_GSSAPI_SERVER 62
#define ZMQ_GSSAPI_PRINCIPAL 63
#define ZMQ_GSSAPI_SERVICE_PRINCIPAL 64
#define ZMQ_GSSAPI_PLAINTEXT 65
#define ZMQ_HANDSHAKE_IVL 66
#define ZMQ_SOCKS_PROXY 68
#define ZMQ_XPUB_NODROP 69
#define ZMQ_BLOCKY 70
#define ZMQ_XPUB_MANUAL 71
#define ZMQ_XPUB_WELCOME_MSG 72
#define ZMQ_STREAM_NOTIFY 73
#define ZMQ_INVERT_MATCHING 74
#define ZMQ_HEARTBEAT_IVL 75
#define ZMQ_HEARTBEAT_TTL 76
#define ZMQ_HEARTBEAT_TIMEOUT 77
#define ZMQ_XPUB_VERBOSER 78
#define ZMQ_CONNECT_TIMEOUT 79
#define ZMQ_TCP_MAXRT 80
#define ZMQ_THREAD_SAFE 81
#define ZMQ_MULTICAST_MAXTPDU 84
#define ZMQ_VMCI_BUFFER_SIZE 85
#define ZMQ_VMCI_BUFFER_MIN_SIZE 86
#define ZMQ_VMCI_BUFFER_MAX_SIZE 87
#define ZMQ_VMCI_CONNECT_TIMEOUT 88
#define ZMQ_USE_FD 89
//+------------------------------------------------------------------+
//| A dedicated class to get/set socket options                      |
//+------------------------------------------------------------------+
class SocketOptions
  {
protected:
   intptr_t          m_ref;

#define SOCKOPT_WRAP_ARRAY(TYPE) \
   bool              setOption(int option,const TYPE &value[],size_t len) {return 0==zmq_setsockopt(m_ref,option,value,len);}\
   bool              getOption(int option,TYPE &value[],size_t &len) {return 0==zmq_getsockopt(m_ref,option,value,len);}

#define SOCKOPT_WRAP(TYPE) \
   bool              setOption(int option,TYPE value) {return 0==zmq_setsockopt(m_ref,option,value,sizeof(TYPE));}\
   bool              getOption(int option,TYPE &value) {size_t s=sizeof(TYPE); return 0==zmq_getsockopt(m_ref,option,value,s);}

   SOCKOPT_WRAP_ARRAY(uchar)
   SOCKOPT_WRAP(int)
   SOCKOPT_WRAP(uint)
   SOCKOPT_WRAP(long)
   SOCKOPT_WRAP(ulong)

   bool              setStringOption(int option,string value,bool ending=true);
   bool              getStringOption(int option,string &value,size_t length=1024);
                     SocketOptions(intptr_t ref):m_ref(ref){}
public:
   //--- option templates
   //--- various integer options
#define SOCKOPT_GET(TYPE, NAME, MACRO) \
   bool              get##NAME(TYPE &value) {return getOption(MACRO,value);}
#define SOCKOPT_SET(TYPE, NAME, MACRO) \
   bool              set##NAME(TYPE value) {return setOption(MACRO,value);}
#define SOCKOPT(TYPE,NAME,MACRO) \
   SOCKOPT_GET(TYPE,NAME,MACRO) \
   SOCKOPT_SET(TYPE,NAME,MACRO)

   //--- boolean options
#define SOCKOPT_GET_BOOL(NAME, MACRO) \
   bool              is##NAME(bool &value) {int v; bool res=getOption(MACRO,v); value=(v==1);return res;}
#define SOCKOPT_SET_BOOL(NAME, MACRO) \
   bool              set##NAME(bool value) {return setOption(MACRO,value?1:0);}
#define SOCKOPT_BOOL(NAME,MACRO) \
   SOCKOPT_GET_BOOL(NAME,MACRO) \
   SOCKOPT_SET_BOOL(NAME,MACRO)

   //--- null-terminated string options
#define SOCKOPT_GET_NTSTR(NAME,MACRO) \
   bool              get##NAME(string &value) {return getStringOption(MACRO,value);}
#define SOCKOPT_SET_NTSTR(NAME,MACRO) \
   bool              set##NAME(string value) {return setStringOption(MACRO,value);}
#define SOCKOPT_NTSTR(NAME,MACRO) \
   SOCKOPT_GET_NTSTR(NAME,MACRO) \
   SOCKOPT_SET_NTSTR(NAME,MACRO)

   //--- bytes array or string converted options
#define SOCKOPT_SET_BYTES(OptionName,Macro) \
   bool              set##OptionName(const uchar &value[]) {return setOption(Macro,value,(size_t)ArraySize(value));} \
   bool              set##OptionName(string value) {return setStringOption(Macro,value,false);}
#define SOCKOPT_GET_BYTES(OptionName,Macro,InitSize) \
   bool              get##OptionName(uchar &value[]) {size_t len=(size_t)InitSize; ArrayResize(value,(int)len); bool res=getOption(Macro,value,len); if(res){ArrayResize(value,(int)len);}return res;} \
   bool              get##OptionName(string &value) {return getStringOption(Macro,value,InitSize);}
#define SOCKOPT_BYTES(OptionName,Macro,InitSize) \
   SOCKOPT_SET_BYTES(OptionName,Macro) \
   SOCKOPT_GET_BYTES(OptionName,Macro,InitSize)

   //--- for curve key
   //--- NOTE that the length of the key array must be 32.
   //--- since some versions of mt4 and newer versions of mt5 will report error
   //--- when the length of the array is specified, so the length specification is removed
#define SOCKOPT_CURVE_KEY(KeyType,Macro) \
   bool              getCurve##KeyType##Key(uchar &key[]) {size_t len=32; return getOption(Macro,key,len);} \
   bool              getCurve##KeyType##Key(string &key) {return getStringOption(Macro,key,41);} \
   bool              setCurve##KeyType##Key(const uchar &key[]) {return setOption(Macro,key,32);} \
   bool              setCurve##KeyType##Key(string key) {return setStringOption(Macro,key);}

   SOCKOPT_GET(int,Type,ZMQ_TYPE)
   SOCKOPT(ulong,Affinity,ZMQ_AFFINITY) //64bit bitmask
   SOCKOPT(int,BackLog,ZMQ_BACKLOG) // number of connections
   SOCKOPT(int,Timeout,ZMQ_CONNECT_TIMEOUT) // milliseconds
   SOCKOPT_GET_BOOL(ThreadSafe,ZMQ_THREAD_SAFE)

   SOCKOPT_SET_BOOL(Conflate,ZMQ_CONFLATE) // only for ZMQ_PULL, ZMQ_PUSH, ZMQ_SUB, ZMQ_PUB, ZMQ_DEALER types

   SOCKOPT_GET(int,Events,ZMQ_EVENTS); // bitmask of ZMQ_POLLIN, ZMQ_POLLOUT

   SOCKOPT_GET(uintptr_t,FileDescriptor,ZMQ_FD)

   SOCKOPT_GET(int,Mechanism,ZMQ_MECHANISM) // current security mechanism

   //--- plain
   SOCKOPT_NTSTR(PlainUsername,ZMQ_PLAIN_USERNAME)
   SOCKOPT_NTSTR(PlainPassword,ZMQ_PLAIN_PASSWORD)
   SOCKOPT_BOOL(PlainServer,ZMQ_PLAIN_SERVER)

   //--- gssapi: this is not supported in this binding. Following methods will FAIL if you invoke them
   SOCKOPT_BOOL(GssApiPlainText,ZMQ_GSSAPI_PLAINTEXT)
   SOCKOPT_BOOL(GssApiServer,ZMQ_GSSAPI_SERVER)
   SOCKOPT_NTSTR(GssApiPrincipal,ZMQ_GSSAPI_PRINCIPAL)
   SOCKOPT_NTSTR(GssApiServicePrincipal,ZMQ_GSSAPI_SERVICE_PRINCIPAL)

   //--- curve
   SOCKOPT_CURVE_KEY(Public,ZMQ_CURVE_PUBLICKEY)
   SOCKOPT_CURVE_KEY(Secret,ZMQ_CURVE_SECRETKEY)
   SOCKOPT_CURVE_KEY(Server,ZMQ_CURVE_SERVERKEY)

   SOCKOPT_SET_BOOL(CurveServer,ZMQ_CURVE_SERVER)

   SOCKOPT_GET_NTSTR(LastEndpoint,ZMQ_LAST_ENDPOINT)

   SOCKOPT(int,HandshakeInterval,ZMQ_HANDSHAKE_IVL) // milliseconds
   SOCKOPT_SET(int,HeartbeatInterval,ZMQ_HEARTBEAT_IVL) // milliseconds
   SOCKOPT_SET(int,HeartbeatTimeout,ZMQ_HEARTBEAT_TIMEOUT) // milliseconds
   SOCKOPT_SET(int,HeartbeatTTL,ZMQ_HEARTBEAT_TTL) // milliseconds

   SOCKOPT_BOOL(Immediate,ZMQ_IMMEDIATE)
   SOCKOPT_BOOL(Ipv6,ZMQ_IPV6) //--- ZMQ_IPV4ONLY is deprecated, use this instead
   SOCKOPT(int,Linger,ZMQ_LINGER) // milliseconds
   SOCKOPT(long,MaxMessageSize,ZMQ_MAXMSGSIZE)

   //--- multicast
   SOCKOPT(int,MulticastHops,ZMQ_MULTICAST_HOPS) // hops
   SOCKOPT(int,MulticastMaxTPDU,ZMQ_MULTICAST_MAXTPDU) // bytes
   SOCKOPT(int,MulticastRate,ZMQ_RATE) // kilobits per second
   SOCKOPT(int,RecoveryInterval,ZMQ_RECOVERY_IVL) // multicast recovery interval

   //--- there is a problem here: FileDescriptor should be SOCKET type on Windows,
   //--- while in the zmq doc it is a int. Possible error in the doc
   SOCKOPT(uintptr_t,UseFileDescriptor,ZMQ_USE_FD)

   SOCKOPT_SET_BOOL(ProbeRouter,ZMQ_PROBE_ROUTER) // only for ZMQ_ROUTER, ZMQ_DEALER, ZMQ_REQ

   SOCKOPT(int,ReceiveBuffer,ZMQ_RCVBUF) // bytes
   SOCKOPT(int,ReceiveHighWaterMark,ZMQ_RCVHWM) // messages
   SOCKOPT(int,ReceiveTimeout,ZMQ_RCVTIMEO) // milliseconds
   SOCKOPT(int,SendBuffer,ZMQ_SNDBUF) // bytes
   SOCKOPT(int,SendHighWaterMark,ZMQ_SNDHWM) // messages
   SOCKOPT(int,SendTimeout,ZMQ_SNDTIMEO)

   SOCKOPT_GET_BOOL(ReceiveMore,ZMQ_RCVMORE)

   SOCKOPT(int,ReconnectInterval,ZMQ_RECONNECT_IVL) // milliseconds
   SOCKOPT(int,ReconnectIntervalMax,ZMQ_RECONNECT_IVL_MAX) // milliseconds

   //--- only for ZMQ_REQ
   SOCKOPT_SET_BOOL(RequestCorrelated,ZMQ_REQ_CORRELATE)
   SOCKOPT_SET_BOOL(RequestRelaxed,ZMQ_REQ_RELAXED)

   //--- only for ZMQ_SUB
   SOCKOPT_SET_BYTES(Subscribe,ZMQ_SUBSCRIBE)
   SOCKOPT_SET_BYTES(Unsubscribe,ZMQ_UNSUBSCRIBE)

   //--- convenience methods
   bool subscribe(string channel) {return setSubscribe(channel);}
   bool unsubscribe(string channel) {return setUnsubscribe(channel);}

   //--- only for ZMQ_XSUB
   SOCKOPT_BOOL(XpubVerbose,ZMQ_XPUB_VERBOSE)
   SOCKOPT_BOOL(XpubVerboser,ZMQ_XPUB_VERBOSER)
   SOCKOPT_BOOL(XpubManual,ZMQ_XPUB_MANUAL)
   SOCKOPT_BOOL(XpubNoDrop,ZMQ_XPUB_NODROP) // also for ZMQ_PUB
   SOCKOPT_SET_BYTES(XpubWelcomeMessage,ZMQ_XPUB_WELCOME_MSG)

   SOCKOPT_BOOL(InvertMatching,ZMQ_INVERT_MATCHING) //--- only for ZMQ_PUB, ZMQ_XPUB, ZMQ_SUB

   //--- only for ZMQ_ROUTER
   SOCKOPT_SET_BOOL(RouterHandover,ZMQ_ROUTER_HANDOVER)
   SOCKOPT_SET_BOOL(RouterMandatory,ZMQ_ROUTER_MANDATORY)
   SOCKOPT_SET_BOOL(RouterRaw,ZMQ_ROUTER_RAW)

   //--- only for ZMQ_STREAM
   SOCKOPT_SET_BOOL(StreamNotify,ZMQ_STREAM_NOTIFY)

   //--- only for ZMQ_ROUTER, ZMQ_STREAM
   SOCKOPT_SET_BYTES(ConnectRid,ZMQ_CONNECT_RID)

   //--- only for ZMQ_REP, ZMQ_REQ, ZMQ_ROUTER, ZMQ_DEALER
   SOCKOPT_BYTES(Identity,ZMQ_IDENTITY,255)

   //--- tcp
   SOCKOPT(int,TcpKeepAlive,ZMQ_TCP_KEEPALIVE)
   SOCKOPT(int,TcpKeepAliveCount,ZMQ_TCP_KEEPALIVE_CNT)
   SOCKOPT(int,TcpKeepAliveIdle,ZMQ_TCP_KEEPALIVE_IDLE)
   SOCKOPT(int,TcpKeepAliveInterval,ZMQ_TCP_KEEPALIVE_INTVL)
   SOCKOPT(int,TcpMaxRetransmitTimeout,ZMQ_TCP_MAXRT)

   SOCKOPT(int,TypeOfService,ZMQ_TOS) // IP_TOS

   //--- ZMQ_TCP_ACCEPT_FILTER
   //--- ZMQ_IPC_FILTER_GID
   //--- ZMQ_IPC_FILTER_PID
   //--- ZMQ_IPC_FILTER_UID
   //--- are deprecated in favor of ZAP API and ip address whitelisting/blacklisting
   SOCKOPT_NTSTR(ZapDomain,ZMQ_ZAP_DOMAIN)

   //--- only for vmci transport
   SOCKOPT(ulong,VmciBufferSize,ZMQ_VMCI_BUFFER_SIZE) // bytes
   SOCKOPT(ulong,VmciBufferMinSize,ZMQ_VMCI_BUFFER_MIN_SIZE) // bytes
   SOCKOPT(ulong,VmciBufferMaxSize,ZMQ_VMCI_BUFFER_MAX_SIZE) // bytes
   SOCKOPT(int,VmciConnectTimeout,ZMQ_VMCI_CONNECT_TIMEOUT) // milliseconds
  };
//+------------------------------------------------------------------+
//| The option value is a string with predefined byte length         |
//|                                                                  |
//| If it is a NULL-terminated string without predefined length,     |
//| The situation is tricky: we do not know the length of the option |
//| value beforehand, but the function does not return the correct   |
//| one, either. So the only option is to guess.                     |
//|                                                                  |
//| Here we adopt the solution of the Java binding. We just guess    |
//| that the length of a NULL-terminated string option is less than  |
//| 1024. So hopefully, it is the case.                              |
//+------------------------------------------------------------------+
bool SocketOptions::getStringOption(int option,string &value,size_t length)
  {
   char buf[];
   ArrayResize(buf,(int)length);
   bool res=getOption(option,buf,length);
   if(res)
     {
      value=StringFromUtf8(buf);
     }
   ArrayFree(buf);
   return res;
  }
//+------------------------------------------------------------------+
//| The ending means that the converted buffer contains the ending   |
//| null.                                                            |
//+------------------------------------------------------------------+
bool SocketOptions::setStringOption(int option,const string value,bool ending)
  {
   char buf[];
   StringToUtf8(value,buf,ending);
   int len = ArraySize(buf);
   bool res=setOption(option,buf,len);
   ArrayFree(buf);
   return res;
  }
//+------------------------------------------------------------------+
