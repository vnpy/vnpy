#include <iostream>
#include <string>
#include <pybind11/pybind11.h>

#include "dispatcher.hpp"
#include "property_helper.hpp"
#include "wrapper_helper.hpp"

#include "class_generators.h"

$includes

void init_dispatcher()
{
    autocxxpy::dispatcher::instance().start();
}

void generate_classes(pybind11::module &m)
{
$classes_code
}

void generate_enums(pybind11::module &m)
{
$enums_code
}

void generate_constants(pybind11::module &m)
{
$constants_code
}

// begin generated code - combined_class_generator_definitions
// code will appear only when split_in_files is off
$combined_class_generator_definitions
// end generated code

PYBIND11_MODULE($module_name, m)
{
    init_dispatcher();
    generate_classes(m);
    generate_constants(m);
    generate_enums(m);
}
