#pragma once

#include "utils/functional.hpp"
#include "dispatcher.hpp"
#include "brigand.hpp"

#include "wrappers/c_function_callback.hpp"
#include "wrappers/string_array.hpp"
#include "wrappers/output_argument.hpp"
#include "wrappers/inout_argument.hpp"
#include "wrappers/string_array.hpp"

namespace autocxxpy
{

    /*
    example to change the calling method:

    @startcode pp
    template <>
    struct calling_wrapper<&A::func2>
    {
        static constexpr auto value = [](){return 1;};
    };
    @endcode
    */
    template <template <class> class T>
    struct normal_transform_holder
    {
        template <class method_constant>
        using transform = T<method_constant>;
    };

    template <template <class method_constant, class integral_constant> class original_transform, size_t index>
    struct indexed_transform_holder
    {
        template <class method_constant>
        using transform = original_transform<method_constant, std::integral_constant<int, index>>;
    };

    template <class method_conatant, class transform_holder>
    struct apply_transform_element : transform_holder::template transform<method_conatant>{};

    template <class method_constant, class transform_list>
    struct apply_function_transform
    {
    public:
        using type=apply_function_transform;
        using result = brigand::fold<transform_list,
            method_constant,
            apply_transform_element<brigand::_state, brigand::_element>
        >;
        using value_type = decltype(result::value);
        static constexpr value_type value = result::value;
    };
}
