//+------------------------------------------------------------------+
//| Module: ZmqMsg.mqh                                               |
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
//+------------------------------------------------------------------+
//| 0MQ Message struct                                               |
//+------------------------------------------------------------------+
// align sizeof(intptr_t)
// = 8 on 64bit
// = 4 on 32bit
// hopefully MetaQuotes do malloc structs
// aligned on pointer address boundaries
struct zmq_msg_t
  {
   uchar             _[64];
  };

#import "libzmq.dll"
int zmq_msg_init(zmq_msg_t &msg);
int zmq_msg_init_size(zmq_msg_t &msg,size_t size);
// As mt4 can not provide a zmq_free_fn, and can not let 
// zmq library own the array data, copying is always needed.
// Therefore this function will not be used by this binding.
// int zmq_msg_init_data(zmq_msg_t &msg,uchar &data[],
//                       int size,int ffn,int hint);
int zmq_msg_close(zmq_msg_t &msg);
int zmq_msg_move(zmq_msg_t &dest,zmq_msg_t &src);
int zmq_msg_copy(zmq_msg_t &dest,zmq_msg_t &src);
// char *
intptr_t zmq_msg_data(zmq_msg_t &msg);
int zmq_msg_size(zmq_msg_t &msg);
int zmq_msg_more(zmq_msg_t &msg);
int zmq_msg_get(zmq_msg_t &msg,int property);
int zmq_msg_set(zmq_msg_t &msg,int property,int optval);
// const char *
intptr_t zmq_msg_gets(zmq_msg_t &msg,const char &property[]);
#import
//+------------------------------------------------------------------+
//| Wraps a zmq_msg_t                                                |
//+------------------------------------------------------------------+
struct ZmqMsg: public zmq_msg_t
  {
protected:
   int               get(int property) {return zmq_msg_get(this,property);}
   bool              set(int property,int value) {return 0==zmq_msg_set(this,property,value);}
   intptr_t          data() {return zmq_msg_data(this);}
   bool              setStringData(string data,bool nullterminated=false);
public:
                     ZmqMsg() {zmq_msg_init(this);}
                     ZmqMsg(int size) {if(0!=zmq_msg_init_size(this,size)){Debug("Failed to init size msg: insufficient space");}}
                     ZmqMsg(string data,bool nullterminated=false) {setStringData(data,nullterminated);}
                    ~ZmqMsg() {if(0!=zmq_msg_close(this)){Debug("Failed to close msg");}}

   bool              rebuild()
     {
      if(0!=zmq_msg_close(this)){Debug("Failed to close msg");return false;}
      return 0==zmq_msg_init(this);
     }
   bool              rebuild(int size)
     {
      if(0!=zmq_msg_close(this)){Debug("Failed to close msg");return false;}
      return 0==zmq_msg_init_size(this,size);
     }
   bool              rebuild(string data,bool nullterminated=false)
     {
      if(0!=zmq_msg_close(this)){Debug("Failed to close msg");return false;}
      return setStringData(data,nullterminated);
     }

   size_t            size() {return zmq_msg_size(this);}

   void              getData(uchar &bytes[]);
   string            getData();
   void              setData(const uchar &bytes[]);

   bool              more() {return 1==zmq_msg_more(this);}

   bool              copy(ZmqMsg &msg) {return 0 == zmq_msg_copy(this, msg);}
   bool              move(ZmqMsg &msg) {return 0 == zmq_msg_move(this, msg);}

   string            meta(const string property);
  };
//+------------------------------------------------------------------+
//| Initialize a utf-8 string message                                |
//+------------------------------------------------------------------+
bool ZmqMsg::setStringData(string data,bool nullterminated)
  {
   uchar array[];
   StringToUtf8(data,array,nullterminated);
   bool res=(0==zmq_msg_init_size(this,ArraySize(array)));
   if(res)setData(array);
   return res;
  }
//+------------------------------------------------------------------+
//| Get message data as bytes array                                  |
//+------------------------------------------------------------------+
void ZmqMsg::getData(uchar &bytes[])
  {
   size_t size=size();
   intptr_t src=data();
   if(ArraySize(bytes)<size) ArrayResize(bytes,(int)size);
   ArrayFromPointer(bytes,src);
  }
//+------------------------------------------------------------------+
//| Get message data as utf-8 string                                 |
//+------------------------------------------------------------------+
string ZmqMsg::getData()
  {
   size_t size=size();
   intptr_t psz=data();
   return StringFromUtf8Pointer(psz,(int)size);
  }
//+------------------------------------------------------------------+
//| copy data to message internal storage                            |
//+------------------------------------------------------------------+
void ZmqMsg::setData(const uchar &bytes[])
  {
   intptr_t dest=data();
   size_t size=size();
   ArrayToPointer(bytes,dest,(int)size);
  }
//+------------------------------------------------------------------+
//| Wraps zmq_msg_gets: get metadata associated with the msg         |
//+------------------------------------------------------------------+
string ZmqMsg::meta(const string property)
  {
   uchar buf[];
   StringToUtf8(property,buf);
   intptr_t ref=zmq_msg_gets(this,buf);
   ArrayFree(buf);
   return StringFromUtf8Pointer(ref);
  }
//+------------------------------------------------------------------+
