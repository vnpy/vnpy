//+------------------------------------------------------------------+
//| Module: Context.mqh                                              |
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
#include <Mql/Lang/Mql.mqh>
#include <Mql/Lang/Native.mqh>
#include <Mql/Lang/GlobalVariable.mqh>
#include "SocketOptions.mqh"

//--- Context options
#define ZMQ_IO_THREADS 1
#define ZMQ_MAX_SOCKETS 2
#define ZMQ_SOCKET_LIMIT 3
#define ZMQ_THREAD_PRIORITY 3
#define ZMQ_THREAD_SCHED_POLICY 4
#define ZMQ_MAX_MSGSZ 5

//--- Default for new contexts
#define ZMQ_IO_THREADS_DFLT  1
#define ZMQ_MAX_SOCKETS_DFLT 1023
#define ZMQ_THREAD_PRIORITY_DFLT -1
#define ZMQ_THREAD_SCHED_POLICY_DFLT -1

#import "libzmq.dll"
intptr_t zmq_ctx_new(void);
int zmq_ctx_term(intptr_t context);
int zmq_ctx_shutdown(intptr_t context);
int zmq_ctx_set(intptr_t context,int option,int optval);
int zmq_ctx_get(intptr_t context,int option);
#import
class ContextHanldeManager: public HandleManager<intptr_t>
  {
   intptr_t          create() override
     {
      return zmq_ctx_new();
     }
   void              destroy(intptr_t handle) override
     {
      if(0!=zmq_ctx_term(handle))
        {
         Debug("failed to terminate context");
        }
     }
  };
//+------------------------------------------------------------------+
//| Wraps a 0MZ context                                              |
//|                                                                  |
//| Note on context creation:                                        |
//| In the official guide:                                           |
//|   You should create and use exactly one context in your process. |
//|   Technically, the context is the container for all sockets in a |
//|   single process, and acts as the transport for inproc sockets,  |
//|   which are the fastest way to connect threads in one process.   |
//|   If at runtime a process has two contexts, these are like       |
//|   separate ZeroMQ instances.                                     |
//| In metatrader Terminal, every Script and Expert Advsior has its  |
//| own thread, but they all share a process, that is the Terminal.  |
//| So it is advised to use a single global context on all your MQL  |
//| programs. The `shared` parameter is used for sychronization of   |
//| context creation and destruction. It is better named globally,   |
//| and in a manner not easily recognized by humans, for example:    |
//| "__3kewducdxhkd__"                                               |
//+------------------------------------------------------------------+
class Context: public GlobalHandle<intptr_t,ContextHanldeManager>
  {
protected:
   int               get(int option) {return zmq_ctx_get(m_ref,option);}
   bool              set(int option,int optval) {return 0==zmq_ctx_set(m_ref,option,optval);}

public:

   static intptr_t   create() {return zmq_ctx_new();}
   static void       destroy(intptr_t handle) {if(0!=zmq_ctx_term(handle)) {Debug("failed to terminate context");}}

                     Context(string shared=NULL):GlobalHandle<intptr_t,ContextHanldeManager>(shared) {}

   bool              shutdown() {return 0==zmq_ctx_shutdown(m_ref);}

   int               getIoThreads() {return get(ZMQ_IO_THREADS);}
   void              setIoThreads(int value) {if(!set(ZMQ_IO_THREADS,value)) {Debug("failed to set ZMQ_IO_THREADS");}}

   int               getMaxSockets() {return get(ZMQ_MAX_SOCKETS);}
   void              setMaxSockets(int value) {if(!set(ZMQ_MAX_SOCKETS,value)) {Debug("failed to set ZMQ_MAX_SOCKETS");}}

   int               getMaxMessageSize() {return get(ZMQ_MAX_MSGSZ);}
   void              setMaxMessageSize(int value) {if(!set(ZMQ_MAX_MSGSZ,value)) {Debug("failed to set ZMQ_MAX_MSGSZ");}}

   int               getSocketLimit() {return get(ZMQ_SOCKET_LIMIT);}

   int               getIpv6Options() {return get(ZMQ_IPV6);}
   void              setIpv6Options(int value) {if(!set(ZMQ_IPV6,value)) {Debug("failed to set ZMQ_IPV6");}}

   bool              isBlocky() {return 1==get(ZMQ_BLOCKY);}
   void              setBlocky(bool value) {if(!set(ZMQ_BLOCKY,value?1:0)) {Debug("failed to set ZMQ_BLOCKY");}}

   //--- Following options is not supported on windows
   void              setSchedulingPolicy(int value) {/*ZMQ_THREAD_SCHED_POLICY*/}
   void              setThreadPriority(int value) {/*ZMQ_THREAD_PRIORITY*/}
  };
//+------------------------------------------------------------------+
