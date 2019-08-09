#pragma once

namespace c2py
{
    struct additional_init_default
    {
        //static void init(pybind11::module &m)
        template <class T>
        inline static void init(T&m)
        {
        }
    };

    template <class tag>
    struct additional_init : additional_init_default
    {};
}
