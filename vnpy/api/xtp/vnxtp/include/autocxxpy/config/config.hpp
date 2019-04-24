#pragma once

#ifdef PYBIND11_OVERLOAD
#ifndef AUTOCXXPY_INCLUDED_PYBIND11
#define AUTOCXXPY_INCLUDED_PYBIND11
#endif
#endif


#ifndef AUTOCXXPY_UNUSED
#define AUTOCXXPY_UNUSED(x) (void)(x)
#endif

#ifdef _MSC_VER
#define AUTOCXXPY_SELECT_ANY __declspec(selectany)

#else
#define AUTOCXXPY_SELECT_ANY __attribute__ ((selectany))
#endif