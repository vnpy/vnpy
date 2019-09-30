#pragma once

/*
 define AUTOCXXPY_ENCODING_UTF8 if encoding of input string(string provided from API packaged)
   is UTF-8
 define AUTOCXXPY_ENCODING_CUSTOM,
   AUTOCXXPY_ENCODING_CUSTOM_WINDOWS,
   and AUTOCXXPY_ENCODING_CUSTOM_LINUX
   if encoding of input string is not UTF-8.

*/
#if !defined(AUTOCXXPY_ENCODING_CUSTOM) && !defined(AUTOCXXPY_ENCODING_UTF8)
#define AUTOCXXPY_ENCODING_UTF8
#endif

#if defined(AUTOCXXPY_ENCODING_UTF8) && defined (AUTOCXXPY_ENCODING_CUSTOM)
#pragma error("AUTOCXXPY_ENCODING_UTF8 and AUTOCXXPY_ENCODING_CUSTOM cann't be defined at the same time.")
#endif

#if defined(AUTOCXXPY_ENCODING_CUSTOM) 
#if !defined(AUTOCXXPY_ENCODING_CUSTOM_WINDOWS) || !defined(AUTOCXXPY_ENCODING_CUSTOM_LINUX)
#pragma error("if you defnied AUTOCXXPY_ENCODING_CUSTOM, you must defined both" 
    " AUTOCXXPY_ENCODING_CUSTOM_WINDOWS and" 
    " AUTOCXXPY_ENCODING_CUSTOM_LINUX" 
    )
#endif
#endif
//#ifdef AUTOCXXPY_ENCODING_CUSTOM
//#ifndef AUTOCXXPY_ENCODING_CUSTOM_WINDOWS
//#pragma error("if you defnied AUTOCXXPY_ENCODING_CUSTOM, you must defined both" 
//    " AUTOCXXPY_ENCODING_CUSTOM_WINDOWS and" 
//    " AUTOCXXPY_ENCODING_CUSTOM_LINUX" 
//    )
//#endif
//#ifndef AUTOCXXPY_ENCODING_CUSTOM_LINUX
//#pragma error("if you defnied AUTOCXXPY_ENCODING_CUSTOM, you must defined both" 
//    " AUTOCXXPY_ENCODING_CUSTOM_WINDOWS and" 
//    " AUTOCXXPY_ENCODING_CUSTOM_LINUX" 
//    )
//#endif
//#endif

// blow is the defines for internal use

#ifdef PYBIND11_OVERLOAD
#ifndef AUTOCXXPY_INCLUDED_PYBIND11
#define AUTOCXXPY_INCLUDED_PYBIND11
#endif
#endif


#ifndef AUTOCXXPY_UNUSED
#  define AUTOCXXPY_UNUSED(x) (void)(x)
#endif


// likely && unlikely
#ifdef __has_cpp_attribute
#  if __has_cpp_attribute(likely)
#    define AUTOCXXPY_LIKELY [[likely]]
#  endif
#  if __has_cpp_attribute(unlikely)
#    define AUTOCXXPY_UNLIKELY [[unlikely]]
#  endif
#endif

#ifndef AUTOCXXPY_LIKELY
#define AUTOCXXPY_LIKELY
#endif

#ifndef AUTOCXXPY_UNLIKELY
#define AUTOCXXPY_UNLIKELY
#endif
