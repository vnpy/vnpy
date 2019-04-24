#include <iostream>
#include <string>
#include <pybind11/pybind11.h>
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
    autocxxpy::dispatcher::instance().start();
}

PYBIND11_MODULE(vnxtp, m)
{
    generate_vnxtp(m);

    module_vnxtp::process_post_assign();

    additional_init(m);
    init_dispatcher(m);
}
