#pragma once

#include <vector>
#include <functional>
#include <mutex>
#include <condition_variable>

#include <pybind11/pybind11.h>


namespace autocxxpy
{
template <class class_type, class value_type>
auto wrap_getter(value_type class_type::*member)
{
	return [member](const class_type &instance)->const value_type & {
		return instance.*member;
	};
}


template <class class_type, class value_type>
auto wrap_setter(value_type class_type::*member)
{
	return [member](class_type &instance, const value_type &value) {
		instance.*member = value;
	};
}

template <size_t size>
using string_literal = char[size];

template <class class_type, size_t size>
auto wrap_getter(string_literal<size> class_type::*member)
{
	return [member](const class_type &instance) {
		//return std::string_view(instance.*member);
		return instance.*member;
	};
}


template <class class_type, size_t size>
auto wrap_setter(string_literal<size> class_type::*member)
{
	return [member](class_type &instance, const std::string_view &value) {
#ifdef _MSC_VER
		strcpy_s(instance.*member, value.data());
#else
		strcpy(instance.*member, value.data());
#endif
	};
	//return [member](class_type &instance, const py::str &) {
	//	strcpy_s(instance.*member, str->raw_str());
	//};
}

#define AUTOCXXPY_DEF_PROPERTY(cls, name) \
		def_property(#name, autocxxpy::wrap_getter(&cls::name), autocxxpy::wrap_setter(&cls::name))
}
