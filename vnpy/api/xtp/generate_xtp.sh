#!/usr/bin/env bash

# autocxxpy version: 0.3.4b
python -m autocxxpy \
    vnxtp \
    xtp_trader_api.h xtp_quote_api.h \
    -I vnxtp/include \
    --output-dir vnxtp/generated_files \
    --copy-autocxxpy-includes vnxtp/include \
    --pyi-output-dir .\
    --no-clear-pyi-output-dir \
    --no-callback-pattern ".*Api"
