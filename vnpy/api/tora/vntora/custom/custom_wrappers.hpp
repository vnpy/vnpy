#pragma once

#include <string>
#include <locale>
#include <codecvt>

#include <autocxxpy/autocxxpy.hpp>
#include <autocxxpy/utils/type_traits.hpp>

#include <pybind11/pybind11.h>

#include "../generated_files/module.hpp"

namespace autocxxpy
{

    //将GBK编码的字符串转换为UTF8
    inline std::string toUtf(const std::string &gb2312)
    {
#ifdef _MSC_VER
        const static std::locale loc("zh-CN");
#else
        const static std::locale loc("zh_CN.GB18030");
#endif

        std::vector<wchar_t> wstr(gb2312.size());
        wchar_t* wstrEnd = nullptr;
        const char* gbEnd = nullptr;
        std::mbstate_t state = {};
        int res = std::use_facet<std::codecvt<wchar_t, char, std::mbstate_t> >
            (loc).in(state,
                gb2312.data(), gb2312.data() + gb2312.size(), gbEnd,
                wstr.data(), wstr.data() + wstr.size(), wstrEnd);

        if (std::codecvt_base::ok == res)
        {
            std::wstring_convert<std::codecvt_utf8<wchar_t>> cutf8;
            return cutf8.to_bytes(std::wstring(wstr.data(), wstrEnd));
        }

        return std::string();
    }

    template <size_t size>
    struct get_string<tag_vntora, size>
    {
        auto operator()(string_literal<size> &val)
        {
            return toUtf(val);
        }
    };

    template <size_t size>
    struct set_string<tag_vntora, size>
    {
        void operator()(string_literal<size> &val, const char *str)
        {
#ifdef _MSC_VER
            strcpy_s(val, toUtf(str).data());
#else
            strcpy(val, toUtf(str).data());
#endif
        }
    };
}
