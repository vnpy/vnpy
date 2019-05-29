#include "pch.h"



#include <iostream>
#include <string>
#include <pybind11/pybind11.h>
#include <pybind11/functional.h>
#include <autocxxpy/autocxxpy.hpp>


#include "generated_files/module.hpp"
#include "generated_files/wrappers.hpp"
#include "generated_files/generated_functions.h"


#include "iTapTradeAPI.h"
#include "TapQuoteAPI.h"
#include "TapAPIError.h"
#include "iTapAPIError.h"
#include "custom/custom_wrappers.hpp"
