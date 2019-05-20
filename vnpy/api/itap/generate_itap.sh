#!/usr/bin/env bash
# autocxxpy version: 0.2.4
python -m autocxxpy \
      vnitap \
      iTapTradeAPI.h TapQuoteAPI.h TapAPIError.h iTapAPIError.h \
      -I vnitap/include \
      -A custom/custom_wrappers.hpp\
      --output-dir vnitap/generated_files \
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