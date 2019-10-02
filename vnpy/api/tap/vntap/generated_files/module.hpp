#pragma once
#include "config.h"

#include <c2py/c2py.hpp>

struct tag_vntap{};
struct module_vntap{
    static c2py::cross_assign cross;
    static c2py::object_store objects;
    static inline void process_post_assign()
    {
        cross.process_assign(objects);
        cross.clear();
        objects.clear();
    }
};
using module_tag=tag_vntap;


