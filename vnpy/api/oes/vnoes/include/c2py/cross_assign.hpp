#pragma once

#ifdef AUTOCXXPY_INCLUDED_PYBIND11

#include <unordered_map>

namespace c2py
{
    using object_store = std::unordered_map<std::string, pybind11::object>;

    class cross_assign
    {
    public:
        void record_assign(pybind11::object& scope,
            const std::string& name_in_scope,
            const std::string& full_name,
            const std::string& target)
        {
            _delay_assings.emplace_back(scope, name_in_scope, full_name, target);
        }

        // make all recored assign available
        void process_assign(object_store& os)
        {
            for (auto& [scope, name_in_scope, full_name, target] : _delay_assings)
            {
                if (target.length() > 0)
                {
                    if (os.count(target) == 0)
                    {
                        if (target[0] == ':')
                            target = target.substr(2);
                        else
                            target = std::string("::") + target;
                    }
                    auto target_obj = os.at(target);
                    scope.attr(name_in_scope.c_str()) = target_obj;
                    os.emplace(full_name, target_obj);

                }
            }
        }

        void clear()
        {
            _delay_assings.clear();
        }
    private:
        std::vector<std::tuple<pybind11::object, std::string, std::string, std::string>> _delay_assings;
    };
}

#endif
