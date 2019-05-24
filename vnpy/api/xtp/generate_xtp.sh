#!/usr/bin/env bash

# autocxxpy version: 0.2.4
python -m autocxxpy \
    vnxtp \
    xtp_trader_api.h xtp_quote_api.h \
    -I vnxtp/include \
    --output-dir vnxtp/generated_files \
    --pyi-output-dir .\
    --no-clear-pyi-output \
    --no-callback-pattern ".*Api"
