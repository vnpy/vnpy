#pragma once

#include <type_traits>

namespace autocxxpy
{

    template <class T, class V=void>
    struct is_defined :std::false_type {};

    template <class T>
    struct is_defined<T,
        std::enable_if_t<std::is_object<T>::value &&
        !std::is_pointer<T>::value &&
        (sizeof(T) > 0) >
    > : std::true_type
    {};

    template <class T>
    constexpr bool is_defined_v = is_defined<T>::value;

    template <class T>
    struct ty { using type = T; };
    template< class T >
    struct remove_cvref { using type = std::remove_cv_t<std::remove_reference_t<T>>; };

    template< class T >
    using remove_cvref_t = typename remove_cvref<T>::type;

    template <class ty, template <class...> class base>
    struct is_specialization_of_impl :std::false_type {};

    template <template <class...> class base, class... args>
    struct is_specialization_of_impl<base<args...>, base> : std::true_type {};

    //! Tests if ty is a specialization of ty
    template <class ty, template <class...> class base>
    struct is_specialization_of : is_specialization_of_impl<typename remove_cvref<ty>::type, base> {};

    template <class ty, template <class...> class base>
    constexpr bool is_specialization_of_v = is_specialization_of<ty, base>::value;

    template<class Cls, class Ty>
    using member_pointer = Ty Cls::*;

    template<class Cls, class Ty>
    auto result_of_member_pointer_helper(member_pointer<Cls, Ty> member)
    {
        return ((Cls *)nullptr)->*member;
    };

    template<auto m>
    struct result_of_member_pointer
    {
        using type = decltype(result_of_member_pointer_helper(m));
    };
    template <auto member>
    using result_of_member_pointer_t = typename result_of_member_pointer<member>::type;


    template<class Cls, class Ty>
    auto class_of_member_pointer_helper(member_pointer<Cls, Ty> member)
    {
        return *((Cls *)nullptr);
    };

    template<auto m>
    struct class_of_member_pointer
    {
        using type = remove_cvref_t<decltype(class_of_member_pointer_helper(m))>;
    };

    template <auto member>
    using class_of_member_pointer_t = typename class_of_member_pointer<member>::type;

#define CREATE_MEMBER_DETECTOR(x)                                               \
    template <typename R, typename ty<decltype(((R*)nullptr)->x)>::type v=0>    \
    constexpr bool has_member_##x_helper(int) { return true; }                  \
                                                                                \
    template <typename R>                                                       \
    constexpr bool has_member_##x_helper(...) { return false; }                 \
                                                                                \
    template <typename R>                                                       \
    constexpr bool has_member_##x() { return has_member_##x_helper<R>(0); } 
}
