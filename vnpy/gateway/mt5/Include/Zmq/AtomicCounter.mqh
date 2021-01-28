//+------------------------------------------------------------------+
//| Module: AtomicCounter.mqh                                        |
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
intptr_t zmq_atomic_counter_new(void);
void zmq_atomic_counter_set(intptr_t counter,int value);
int zmq_atomic_counter_inc(intptr_t counter);
int zmq_atomic_counter_dec(intptr_t counter);
int zmq_atomic_counter_value(intptr_t counter);
void zmq_atomic_counter_destroy(intptr_t &counter_p);
#import
//+------------------------------------------------------------------+
//| Atomic counter utility                                           |
//+------------------------------------------------------------------+
class AtomicCounter
  {
private:
   intptr_t          m_ref;

public:
                     AtomicCounter() {m_ref=zmq_atomic_counter_new();}
                    ~AtomicCounter() {zmq_atomic_counter_destroy(m_ref);}

   int               increase() {return zmq_atomic_counter_inc(m_ref);}
   int               decrease() {return zmq_atomic_counter_dec(m_ref);}
   int               get() {return zmq_atomic_counter_value(m_ref);}
   void              set(int value) {zmq_atomic_counter_set(m_ref,value);}
  };
//+------------------------------------------------------------------+
