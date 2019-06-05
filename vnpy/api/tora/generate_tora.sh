#!/usr/bin/env bash
# autocxxpy version: 0.2.5
python -m autocxxpy \
        vntora \
        TORATstpMdApi.h\
        TORATstpTraderApi.h\
        TORATstpUserApiDataType.h\
        TORATstpUserApiStruct.h\
        -I vntora/include \
        -A custom/custom_wrappers.hpp\
        --copy-autocxxpy-includes vntora/include \
        --output-dir vntora/generated_files \
        --pyi-output-dir . \
        \
        --no-clear-pyi-output\
        --no-callback-pattern \
        ".*Api::.*"
