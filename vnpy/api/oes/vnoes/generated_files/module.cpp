#include "config.h"

#include <iostream>
#include <string>
#include <pybind11/pybind11.h>
#include <pybind11/functional.h>
#include <pybind11/stl.h>
#include <autocxxpy/autocxxpy.hpp>

#include "module.hpp"
#include "generated_functions.h"

#include "oes_api/oes_api.h"
#include "mds_api/mds_api.h"


autocxxpy::cross_assign module_vnoes::cross;
autocxxpy::object_store module_vnoes::objects;

void additional_init(pybind11::module &m)
{
    autocxxpy::additional_init<tag_vnoes>::init(m);
}

void init_dispatcher(pybind11::module &m)
{
    m.def("set_async_callback_exception_handler", &autocxxpy::async_callback_exception_handler::set_handler);

    // maybe module_local is unnecessary
    pybind11::class_<autocxxpy::async_dispatch_exception> c(m, "AsyncDispatchException", pybind11::module_local());
    c.def_property_readonly("what", &autocxxpy::async_dispatch_exception::what_mutable);
    c.def_readonly("instance", &autocxxpy::async_dispatch_exception::instance);
    c.def_readonly("function_name", &autocxxpy::async_dispatch_exception::function_name);

    autocxxpy::dispatcher::instance().start();
}

PYBIND11_MODULE(vnoes, m)
{
    generate_vnoes(m);

    module_vnoes::process_post_assign();

    additional_init(m);
    init_dispatcher(m);
}
