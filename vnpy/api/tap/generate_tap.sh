#!/usr/bin/env bash
c2py generate \
    vntap \
    iTapTradeAPI.h TapQuoteAPI.h TapAPIError.h iTapAPIError.h \
    -I vntap/include \
    -A custom/custom_wrappers.hpp\
    --output-dir vntap/generated_files \
    --copy-c2py-includes vntap/include \
    --pyi-output-dir . \
    \
    --no-clear-pyi-output-dir \
    \
     --output-arg-pattern \
     "(.*API::.*(sessionID$|.*ClientBuyOrderNo$|.*ClientSellOrderNo$|.*ClientOrderNo$))|(.*Result)" \
     \
     --no-callback-pattern \
     ".*API::.*" \
     --no-transform-pattern \
     ".*Notify::On.*" \
    \
    --string-encoding-windows .936 \
    --string-encoding-linux zh_CN.GB18030 \
    \
    --enforce-version 0.5.4

# python generate_error_map.py
