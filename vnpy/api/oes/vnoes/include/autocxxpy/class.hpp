#pragma once

namespace autocxxpy
{
    template <class tag, class T>
    struct post_register_class
    {
        template <class T2>
        static constexpr void post_register(T2)
        {}
    };


}
#define AUTOCXXPY_POST_REGISTER_CLASS(module_tag, cls, c) \
    (autocxxpy::post_register_class<module_tag, cls>{}.post_register(c))
