#include "config.h"

#include <iostream>
#include <string>
#include <pybind11/pybind11.h>
#include <pybind11/functional.h>
#include <pybind11/stl.h>
#include <c2py/c2py.hpp>

#include "module.hpp"
#include "wrappers.hpp"
#include "generated_functions.h"

#include "oes_api/oes_api.h"
#include "mds_api/mds_api.h"


void generate_vnoes_functions_7(pybind11::module & parent)
{
    parent.def("MdsApi_InitTcpChannel2",
        &MdsApi_InitTcpChannel2,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("MdsApi_InitQryChannel",
        &MdsApi_InitQryChannel,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("MdsApi_InitQryChannel2",
        &MdsApi_InitQryChannel2,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("MdsApi_InitUdpChannel",
        &MdsApi_InitUdpChannel,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("MdsApi_InitUdpChannel2",
        &MdsApi_InitUdpChannel2,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("MdsApi_ParseAddrListString",
        &MdsApi_ParseAddrListString,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("MdsApi_ParseConfigFromFile",
        &MdsApi_ParseConfigFromFile,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("MdsApi_ParseAllConfig",
        &MdsApi_ParseAllConfig,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("MdsApi_InitChannelGroup",
        &MdsApi_InitChannelGroup,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("MdsApi_DestoryChannelGroup",
        &MdsApi_DestoryChannelGroup,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("MdsApi_AddToChannelGroup",
        &MdsApi_AddToChannelGroup,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("MdsApi_DeleteFromChannelGroup",
        &MdsApi_DeleteFromChannelGroup,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("MdsApi_GetFromChannelGroup",
        &MdsApi_GetFromChannelGroup,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("MdsApi_GetFromChannelGroupBySocket",
        &MdsApi_GetFromChannelGroupBySocket,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("MdsApi_ForeachInChannelGroup",
        c2py::c_function_callback_transform < 
            c2py::function_constant<&MdsApi_ForeachInChannelGroup>,
            std::integral_constant<int, 1>
        >::value,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("MdsApi_SetThreadUsername",
        &MdsApi_SetThreadUsername,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("MdsApi_GetThreadUsername",
        &MdsApi_GetThreadUsername,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("MdsApi_SetThreadPassword",
        &MdsApi_SetThreadPassword,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("MdsApi_SetCustomizedIp",
        &MdsApi_SetCustomizedIp,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("MdsApi_SetCustomizedMac",
        &MdsApi_SetCustomizedMac,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
}
void generate_vnoes_functions_8(pybind11::module & parent)
{
    parent.def("MdsApi_GetCustomizedIp",
        &MdsApi_GetCustomizedIp,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("MdsApi_GetCustomizedMac",
        &MdsApi_GetCustomizedMac,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("MdsApi_SetCustomizedDriverId",
        &MdsApi_SetCustomizedDriverId,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("MdsApi_GetCustomizedDriverId",
        &MdsApi_GetCustomizedDriverId,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("MdsApi_GetLastRecvTime",
        &MdsApi_GetLastRecvTime,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("MdsApi_GetLastSendTime",
        &MdsApi_GetLastSendTime,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("MdsApi_HasMoreCachedData",
        &MdsApi_HasMoreCachedData,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("MdsApi_IsValidTcpChannel",
        &MdsApi_IsValidTcpChannel,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("MdsApi_IsValidQryChannel",
        &MdsApi_IsValidQryChannel,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("MdsApi_IsValidUdpChannel",
        &MdsApi_IsValidUdpChannel,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("MdsApi_IsValidChannelGroup",
        &MdsApi_IsValidChannelGroup,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("MdsApi_GetLastError",
        &MdsApi_GetLastError,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("MdsApi_SetLastError",
        &MdsApi_SetLastError,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("MdsApi_GetErrorMsg",
        &MdsApi_GetErrorMsg,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("MdsApi_GetErrorMsg2",
        &MdsApi_GetErrorMsg2,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("MdsHelper_SetTickTypeOnSubscribeByString",
        &MdsHelper_SetTickTypeOnSubscribeByString,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("MdsHelper_ClearSubscribeRequestEntries",
        &MdsHelper_ClearSubscribeRequestEntries,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("MdsHelper_SetSubscribeRequestMode",
        &MdsHelper_SetSubscribeRequestMode,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("MdsHelper_SetSubscribeRequestTickType",
        &MdsHelper_SetSubscribeRequestTickType,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("MdsHelper_SetSubscribeRequestDataTypes",
        &MdsHelper_SetSubscribeRequestDataTypes,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
}
void generate_vnoes_functions_9(pybind11::module & parent)
{
    parent.def("MdsHelper_SetSubscribeRequestSubFlag",
        &MdsHelper_SetSubscribeRequestSubFlag,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
    parent.def("MdsHelper_AddSubscribeRequestEntry",
        &MdsHelper_AddSubscribeRequestEntry,
        pybind11::return_value_policy::reference,
        pybind11::call_guard<pybind11::gil_scoped_release>()
    );
}
void generate_vnoes_functions(pybind11::module & parent)
{
    generate_vnoes_functions_0(parent);
    generate_vnoes_functions_1(parent);
    generate_vnoes_functions_2(parent);
    generate_vnoes_functions_3(parent);
    generate_vnoes_functions_4(parent);
    generate_vnoes_functions_5(parent);
    generate_vnoes_functions_6(parent);
    generate_vnoes_functions_7(parent);
    generate_vnoes_functions_8(parent);
    generate_vnoes_functions_9(parent);
}
void generate_vnoes_variables(pybind11::module & parent)
{
    // OES_APPL_VER_ID
    parent.attr("OES_APPL_VER_ID") = OES_APPL_VER_ID;
    // OES_MIN_APPL_VER_ID
    parent.attr("OES_MIN_APPL_VER_ID") = OES_MIN_APPL_VER_ID;
    // OESAPI_CFG_DEFAULT_SECTION
    parent.attr("OESAPI_CFG_DEFAULT_SECTION") = OESAPI_CFG_DEFAULT_SECTION;
    // OESAPI_CFG_DEFAULT_SECTION_LOGGER
    parent.attr("OESAPI_CFG_DEFAULT_SECTION_LOGGER") = OESAPI_CFG_DEFAULT_SECTION_LOGGER;
    // OESAPI_CFG_DEFAULT_KEY_ORD_ADDR
    parent.attr("OESAPI_CFG_DEFAULT_KEY_ORD_ADDR") = OESAPI_CFG_DEFAULT_KEY_ORD_ADDR;
    // OESAPI_CFG_DEFAULT_KEY_RPT_ADDR
    parent.attr("OESAPI_CFG_DEFAULT_KEY_RPT_ADDR") = OESAPI_CFG_DEFAULT_KEY_RPT_ADDR;
    // OESAPI_CFG_DEFAULT_KEY_QRY_ADDR
    parent.attr("OESAPI_CFG_DEFAULT_KEY_QRY_ADDR") = OESAPI_CFG_DEFAULT_KEY_QRY_ADDR;
    // OESAPI_DEFAULT_STRING_DELIM
    parent.attr("OESAPI_DEFAULT_STRING_DELIM") = OESAPI_DEFAULT_STRING_DELIM;
    // MDS_APPL_VER_ID
    parent.attr("MDS_APPL_VER_ID") = MDS_APPL_VER_ID;
    // MDS_MIN_APPL_VER_ID
    parent.attr("MDS_MIN_APPL_VER_ID") = MDS_MIN_APPL_VER_ID;
    // MDSAPI_CFG_DEFAULT_SECTION
    parent.attr("MDSAPI_CFG_DEFAULT_SECTION") = MDSAPI_CFG_DEFAULT_SECTION;
    // MDSAPI_CFG_DEFAULT_SECTION_LOGGER
    parent.attr("MDSAPI_CFG_DEFAULT_SECTION_LOGGER") = MDSAPI_CFG_DEFAULT_SECTION_LOGGER;
    // MDSAPI_CFG_DEFAULT_KEY_TCP_ADDR
    parent.attr("MDSAPI_CFG_DEFAULT_KEY_TCP_ADDR") = MDSAPI_CFG_DEFAULT_KEY_TCP_ADDR;
    // MDSAPI_CFG_DEFAULT_KEY_QRY_ADDR
    parent.attr("MDSAPI_CFG_DEFAULT_KEY_QRY_ADDR") = MDSAPI_CFG_DEFAULT_KEY_QRY_ADDR;
    // MDSAPI_CFG_DEFAULT_KEY_UDP_ADDR_L1
    parent.attr("MDSAPI_CFG_DEFAULT_KEY_UDP_ADDR_L1") = MDSAPI_CFG_DEFAULT_KEY_UDP_ADDR_L1;
    // MDSAPI_CFG_DEFAULT_KEY_UDP_ADDR_L2
    parent.attr("MDSAPI_CFG_DEFAULT_KEY_UDP_ADDR_L2") = MDSAPI_CFG_DEFAULT_KEY_UDP_ADDR_L2;
    // MDSAPI_CFG_DEFAULT_KEY_UDP_ADDR_TICK1
    parent.attr("MDSAPI_CFG_DEFAULT_KEY_UDP_ADDR_TICK1") = MDSAPI_CFG_DEFAULT_KEY_UDP_ADDR_TICK1;
    // MDSAPI_CFG_DEFAULT_KEY_UDP_ADDR_TICK2
    parent.attr("MDSAPI_CFG_DEFAULT_KEY_UDP_ADDR_TICK2") = MDSAPI_CFG_DEFAULT_KEY_UDP_ADDR_TICK2;
    // MDSAPI_CFG_DEFAULT_KEY_UDP_ADDR_TICK_TRADE
    parent.attr("MDSAPI_CFG_DEFAULT_KEY_UDP_ADDR_TICK_TRADE") = MDSAPI_CFG_DEFAULT_KEY_UDP_ADDR_TICK_TRADE;
    // MDSAPI_CFG_DEFAULT_KEY_UDP_ADDR_TICK_ORDER
    parent.attr("MDSAPI_CFG_DEFAULT_KEY_UDP_ADDR_TICK_ORDER") = MDSAPI_CFG_DEFAULT_KEY_UDP_ADDR_TICK_ORDER;
    // MDSAPI_DEFAULT_STRING_DELIM
    parent.attr("MDSAPI_DEFAULT_STRING_DELIM") = MDSAPI_DEFAULT_STRING_DELIM;
}
