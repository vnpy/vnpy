#!/usr/bin/env bash
# autocxxpy version: 0.2.5
python -m autocxxpy \
        vntap \
        iTapTradeAPI.h TapQuoteAPI.h TapAPIError.h iTapAPIError.h \
        -I vntap/include \
        -A custom/custom_wrappers.hpp\
        --output-dir vntap/generated_files \
        --copy-autocxxpy-includes vntap/include \
        --pyi-output-dir . \
        \
        --no-clear-pyi-output \
        \
         --output-arg-pattern \
         "(.*API::.*(sessionID$|.*ClientBuyOrderNo$|.*ClientSellOrderNo$|.*ClientOrderNo$))|(.*Result)" \
         \
         --no-callback-pattern \
         ".*API::.*"

python generate_error_map.py