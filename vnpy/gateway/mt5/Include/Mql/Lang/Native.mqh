//+------------------------------------------------------------------+
//| Module: Lang/Native.mqh                                          |
//| This file is part of the mql4-lib project:                       |
//|     https://github.com/dingmaotu/mql4-lib                        |
//|                                                                  |
//| Copyright 2016-2017 Li Ding <dingmaotu@126.com>                  |
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

// Assume MT5 is 64bit, which is the default.
// Even though MT5 can be 32bit, there is no way to detect this
// by using preprocessor macros. Instead, MetaQuotes provides a
// function called IsX64 to detect this dynamically

// This is just absurd. Why do you want to know the bitness of
// the runtime? To define pointer related entities at compile time!
// All integer types in MQL is uniform on both 32bit or 64bit
// architectures, so it is almost useless to have a runtime function IsX64.

// Why not a __X64__?
#ifdef __MQL5__
#define __X64__
#endif

#ifdef __X64__
#define intptr_t long
#define uintptr_t ulong
#define size_t long
#else
#define intptr_t int
#define uintptr_t uint
#define size_t int
#endif

#import "kernel32.dll"
void RtlMoveMemory(intptr_t dest,const uchar &array[],size_t length);
void RtlMoveMemory(uchar &array[],intptr_t src,size_t length);
void RtlMoveMemory(intptr_t dest,const MqlRates &array[],size_t length);
void RtlMoveMemory(MqlRates &array[],intptr_t src,size_t length);
void RtlMoveMemory(intptr_t dest,const MqlTick &value,size_t length);
void RtlMoveMemory(MqlTick &value,intptr_t src,size_t length);
void RtlMoveMemory(intptr_t &dest,intptr_t src,size_t length);
int lstrlen(intptr_t psz);
int lstrlenW(intptr_t psz);
uintptr_t lstrcpynW(string &s1,uintptr_t s2,int length);
uintptr_t lstrcpynW(uintptr_t s1,string &s2,int length);

int MultiByteToWideChar(uint   codePage,
                        uint   flags,
                        const  intptr_t multiByteString,
                        int    lengthMultiByte,
                        string &str,
                        int    length
                        );
#import
//+------------------------------------------------------------------+
//| Copy the memory contents pointed by src to array                 |
//| array parameter should be initialized to the desired size        |
//| Need to import RtlMoveMemory with appropriate parameter type T   |
//+------------------------------------------------------------------+
template<typename T>
void ArrayFromPointer(T &array[],intptr_t src,int count=WHOLE_ARRAY)
  {
   int size=(count==WHOLE_ARRAY)?ArraySize(array):count;
   RtlMoveMemory(array,src,(size_t)(size*sizeof(T)));
  }
//+------------------------------------------------------------------+
//| Copy array to the memory pointed by dest                         |
//| Need to import RtlMoveMemory with appropriate parameter type T   |
//+------------------------------------------------------------------+
template<typename T>
void ArrayToPointer(const T &array[],intptr_t dest,int count=WHOLE_ARRAY)
  {
   int size=(count==WHOLE_ARRAY)?ArraySize(array):count;
   RtlMoveMemory(dest,array,(size_t)(size*sizeof(T)));
  }
//+------------------------------------------------------------------+
//| Copy the memory contents pointed by src to value type T          |
//| Need to import RtlMoveMemory with appropriate parameter type T   |
//+------------------------------------------------------------------+
template<typename T>
void ValueFromPointer(T &value,intptr_t src)
  {
   RtlMoveMemory(value,src,(size_t)sizeof(T));
  }
//+------------------------------------------------------------------+
//| Copy value to the memory pointed by dest                         |
//| Need to import RtlMoveMemory with appropriate parameter type T   |
//+------------------------------------------------------------------+
template<typename T>
void ValueToPointer(const T &value,intptr_t dest)
  {
   RtlMoveMemory(dest,value,(size_t)sizeof(T));
  }
//+------------------------------------------------------------------+
//| For void** type, dereference a level to void*                    |
//+------------------------------------------------------------------+
intptr_t DereferencePointer(intptr_t pointer)
  {
   intptr_t res=0;
   RtlMoveMemory(res,pointer,sizeof(intptr_t));
   return res;
  }
//+------------------------------------------------------------------+
//| Read a valid wide character string to the MQL environment        |
//+------------------------------------------------------------------+
string StringFromPointer(intptr_t psz,int len=0)
  {
   if(len < 0) return NULL;
   if(len==0) {len=lstrlenW(psz);}
   string res;
   StringInit(res,len+1);
   lstrcpynW(res,psz,len+1);
   return res;
  }
//+------------------------------------------------------------------+
//| Get the pointer address of a string                              |
//+------------------------------------------------------------------+
uintptr_t StringToPointer(string &s)
  {
   return lstrcpynW(s,0,0);
  }
//+------------------------------------------------------------------+
//| Read a valid utf-8 string to the MQL environment                 |
//| With this function, there is no need to copy the string to char  |
//| array, and convert with CharArrayToString                        |
//+------------------------------------------------------------------+
string StringFromUtf8Pointer(intptr_t psz,int len)
  {
   if(len < 0) return NULL;
   string res;
   int required=MultiByteToWideChar(CP_UTF8,0,psz,len,res,0);
// need to include the NULL terminating character
   StringInit(res,required+1);
   int rlen=MultiByteToWideChar(CP_UTF8,0,psz,len,res,required);
   return rlen != required ? NULL : res;
  }
//+------------------------------------------------------------------+
//| for null-terminated string                                       |
//+------------------------------------------------------------------+
string StringFromUtf8Pointer(intptr_t psz)
  {
   if(psz==0) return NULL;
   int len=lstrlen(psz);
   if(len==0) return NULL;
   return StringFromUtf8Pointer(psz, len);
  }
//+------------------------------------------------------------------+
//| Convert a utf-8 byte array to a string                           |
//+------------------------------------------------------------------+
string StringFromUtf8(const uchar &utf8[])
  {
   return CharArrayToString(utf8, 0, -1, CP_UTF8);
  }
//+------------------------------------------------------------------+
//| Convert a string to a utf-8 byte array                           |
//+------------------------------------------------------------------+
void StringToUtf8(const string str,uchar &utf8[],bool ending=true)
  {
   if(!ending && str=="") return;
   int count=ending ? -1 : StringLen(str);
   StringToCharArray(str,utf8,0,count,CP_UTF8);
  }
//+------------------------------------------------------------------+
