#pragma once

#include <vector>
#include <functional>
#include <mutex>
#include <condition_variable>

#include <pybind11/pybind11.h>

namespace py = pybind11;
using namespace std;

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
auto wrap_getter(typename string_literal<size> class_type::*member)
{
	return [member](const class_type &instance) {
		return std::string_view(instance.*member);
	};
}


template <class class_type, size_t size>
auto wrap_setter(typename string_literal<size> class_type::*member)
{
	return [member](class_type &instance, const std::string_view &value) {
		strcpy_s(instance.*member, value.data());
	};
	//return [member](class_type &instance, const py::str &) {
	//	strcpy_s(instance.*member, str->raw_str());
	//};
}

#define DEF_PROPERTY(cls, name) \
		def_property(#name, wrap_getter(&cls::name), wrap_setter(&cls::name))


