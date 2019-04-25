#!/usr/bin/env bash

python -m autocxxpy vnxtp xtp_trader_api.h xtp_quote_api.h -I vnxtp/include  -o vnxtp/generated_files -p . --no-callback-name .*Api
