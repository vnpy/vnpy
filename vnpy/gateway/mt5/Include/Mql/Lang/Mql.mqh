//+------------------------------------------------------------------+
//| Module: Lang/Mql.mqh                                             |
//| This file is part of the mql4-lib project:                       |
//|     https://github.com/dingmaotu/mql4-lib                        |
//|                                                                  |
//| Copyright 2017 Li Ding <dingmaotu@126.com>                       |
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
#include "Error.mqh"
//+------------------------------------------------------------------+
//| Mql language specific methods                                    |
//+------------------------------------------------------------------+
class Mql
  {
public:
   static int        getLastError() {return GetLastError();}
   static string     getErrorMessage(int errorCode) {return GetErrorDescription(errorCode);}

   //--- Prefer global DoubleToString function
   static string     doubleToString(double value,int precision) {return DoubleToString(value,precision);}
   //--- Adapted from stdlib.mq4 by using `StringSetCharacter` instead of `StringSetChar`
   static string     integerToHexString(int value)
     {
      static const string digits="0123456789ABCDEF";
      string hex="00000000";
      int    digit,shift=28;
      for(int i=0; i<8; i++)
        {
         digit=(value>>shift)&0x0F;
         StringSetCharacter(hex,i,digits[digit]);
         shift-=4;
        }
      return(hex);
     }
   //--- Prefer Canvas/Canvas.mqh XRGB
   static int        rgb(int r,int g,int b) {return int(0xFF000000|(uchar(r)<<16)|(uchar(g)<<8)|uchar(b));}

   //--- Prefer Lang/Number.mqh Double::IsEqual
   static bool       isEqual(double a,double b) {return NormalizeDouble(a-b,8)==0;}

   static bool       isStopped() {return IsStopped();}

   static int        getCodePage() {return MQLInfoInteger(MQL_CODEPAGE);}
   static ENUM_PROGRAM_TYPE getProgramType() {return(ENUM_PROGRAM_TYPE)MQLInfoInteger(MQL_PROGRAM_TYPE);}
   static bool       isScript() {return Mql::getProgramType()==PROGRAM_SCRIPT;}
   static bool       isExpert() {return Mql::getProgramType()==PROGRAM_EXPERT;}
   static bool       isIndicator() {return Mql::getProgramType()==PROGRAM_INDICATOR;}
   static bool       isDllAllowed() {return MQLInfoInteger(MQL_DLLS_ALLOWED)!=0;}
   static bool       isTradeAllowed() {return MQLInfoInteger(MQL_TRADE_ALLOWED)!=0;}
   static bool       isSignalsAllowed() {return MQLInfoInteger(MQL_SIGNALS_ALLOWED)!=0;}
   static bool       isDebug() {return MQLInfoInteger(MQL_DEBUG)!=0;}
   static bool       isProfiling() {return MQLInfoInteger(MQL_PROFILER)!=0;}
   static bool       isTesting() {return MQLInfoInteger(MQL_TESTER)!=0;}
   static bool       isOptimizing() {return MQLInfoInteger(MQL_OPTIMIZATION)!=0;}
   static bool       isVisual() {return MQLInfoInteger(MQL_VISUAL_MODE)!=0;}
   static bool       isFrameMode() {return MQLInfoInteger(MQL_FRAME_MODE)!=0;}
   static ENUM_LICENSE_TYPE getLicenseType() {return(ENUM_LICENSE_TYPE)MQLInfoInteger(MQL_LICENSE_TYPE);}
   static bool       isFreeLicense() {return Mql::getLicenseType()==LICENSE_FREE;}
   static bool       isDemoLicense() {return Mql::getLicenseType()==LICENSE_DEMO;}
   static bool       isFullLicense() {return Mql::getLicenseType()==LICENSE_FULL;}
   static bool       isTimeLicense() {return Mql::getLicenseType()==LICENSE_TIME;}

   static string     getProgramName() {return MQLInfoString(MQL_PROGRAM_NAME);}
   static string     getProgramPath() {return MQLInfoString(MQL_PROGRAM_PATH);}
  };
//+------------------------------------------------------------------+
//| Object getter/setter generator                                   |
//| ObjectAttr generates:                                            |
//| 1. private member m_property                                     |
//| 2. public method setProperty                                     |
//| 3. public method getProperty                                     |
//| ObjectAttrBool is specific to boolean type properties:           |
//| 1. private member m_isProperty                                   |
//| 2. public method setProperty                                     |
//| 3. public method isProperty                                      |
//| Use *Read or *Write versions for read only or write only         |
//| properties                                                       |
//+------------------------------------------------------------------+
#define ObjectAttr(Type, Private, Public) \
public:\
   Type              get##Public() const {return m_##Private;}\
   void              set##Public(Type value) {m_##Private=value;}\
private:\
   Type              m_##Private\

#define ObjectAttrRead(Type, Private, Public) \
public:\
   Type              get##Public() const {return m_##Private;}\
private:\
   Type              m_##Private\

#define ObjectAttrWrite(Type, Private, Public) \
public:\
   void              set##Public(Type value) {m_##Private=value;}\
private:\
   Type              m_##Private\

#define ObjectAttrBool(Public) \
public:\
   bool              is##Public() const {return m_is##Public;}\
   void              set##Public(bool value) {m_is##Public=value;}\
private:\
   bool              m_is##Public\

#define ObjectAttrBoolRead(Public) \
public:\
   bool              is##Public() const {return m_is##Public;}\
private:\
   bool              m_is##Public\

#define ObjectAttrBoolWrite(Public) \
public:\
   void              set##Public(bool value) {m_is##Public=value;}\
private:\
   bool              m_##Private\
//+------------------------------------------------------------------+
//| Print debug messages: only generate code for debugging runs      |
//+------------------------------------------------------------------+
#ifdef _DEBUG
#define Debug(msg) PrintFormat(">>> DEBUG[%s,%d,%s]: %s",__FILE__,__LINE__,__FUNCTION__,msg);
#else
#define Debug(msg)
#endif
//+------------------------------------------------------------------+
//| Execute some code in the global scope                            |
//+------------------------------------------------------------------+
#define BEGIN_EXECUTE(Name) class __Execute##Name\
  {\
   public:__Execute##Name()\
     {
#define END_EXECUTE(Name) \
     }\
  }\
__execute##Name;
//+------------------------------------------------------------------+
