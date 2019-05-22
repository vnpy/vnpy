#include <iostream>
#include <string>
#include <pybind11/pybind11.h>
#include <pybind11/functional.h>
#include <autocxxpy/autocxxpy.hpp>

#include "module.hpp"
#include "generated_functions.h"

#include "xtp_trader_api.h"
#include "xtp_quote_api.h"


autocxxpy::cross_assign module_vnxtp::cross;
autocxxpy::object_store module_vnxtp::objects;

void additional_init(pybind11::module &m)
{
    autocxxpy::additional_init<tag_vnxtp>::init(m);
}

void init_dispatcher(pybind11::module &m)
{
    m.def("set_async_callback_exception_handler", &autocxxpy::async_callback_exception_handler::set_handler);

    pybind11::class_<autocxxpy::async_dispatch_exception> c(m, "AsyncDispatchException");
    c.def_property("what", &autocxxpy::async_dispatch_exception::what, nullptr);
    c.def_readonly("instance", &autocxxpy::async_dispatch_exception::instance);
    c.def_readonly("function_name", &autocxxpy::async_dispatch_exception::function_name);

    autocxxpy::dispatcher::instance().start();
}

PYBIND11_MODULE(vnxtp, m)
{
    generate_vnxtp(m);

    module_vnxtp::process_post_assign();

    additional_init(m);
    init_dispatcher(m);
}
