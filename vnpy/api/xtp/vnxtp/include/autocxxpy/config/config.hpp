#pragma once

#ifdef PYBIND11_OVERLOAD
#ifndef AUTOCXXPY_INCLUDED_PYBIND11
#define AUTOCXXPY_INCLUDED_PYBIND11
#endif
#endif


#ifndef AUTOCXXPY_UNUSED
#  define AUTOCXXPY_UNUSED(x) (void)(x)
#endif

#ifdef _MSC_VER
#  define AUTOCXXPY_SELECT_ANY __declspec(selectany)

#else
#  define AUTOCXXPY_SELECT_ANY __attribute__ ((selectany))
#endif


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
