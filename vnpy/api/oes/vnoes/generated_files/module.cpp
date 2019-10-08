#include "config.h"

#include <iostream>
#include <string>
#include <pybind11/pybind11.h>
#include <pybind11/functional.h>
#include <pybind11/stl.h>
#include <c2py/c2py.hpp>

#include "module.hpp"
#include "generated_functions.h"

#include "oes_api/oes_api.h"
#include "mds_api/mds_api.h"


c2py::cross_assign module_vnoes::cross;
c2py::object_store module_vnoes::objects;

void additional_init(pybind11::module &m)
{
    c2py::additional_init<tag_vnoes>::init(m);
}

void init_dispatcher(pybind11::module &m)
{
    m.def("set_async_callback_exception_handler", &c2py::async_callback_exception_handler::set_handler);

    // maybe module_local is unnecessary
    pybind11::class_<c2py::async_dispatch_exception> c(m, "AsyncDispatchException", pybind11::module_local());
    c.def_property_readonly("what", &c2py::async_dispatch_exception::what_mutable);
    c.def_readonly("instance", &c2py::async_dispatch_exception::instance);
    c.def_readonly("function_name", &c2py::async_dispatch_exception::function_name);

    c2py::dispatcher::instance().start();
}

PYBIND11_MODULE(vnoes, m)
{
    generate_vnoes(m);

    module_vnoes::process_post_assign();

    additional_init(m);
    init_dispatcher(m);
}
