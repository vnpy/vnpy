# 2025.12.28

1. Fix missing "instId" field when cancelling order

# 2025.12.22

1. adjust fields for collecting account frozen and available value

# 2025.12.04

1. support for margin currency field "ccy" when sending order

# 2025.11.08

1. ignore exception when sending ping
2. remove old AWS endpoints
3. add small delay (0.1s) to avoid rate limit when querying history data

# 2025.11.04

1. Filter duplicate subscription

# 2025.11.01

1. set contract size to 1 when ctVal is empty string

# 2025.10.29

1. use "ctVal" instead of "ctMult" for contract size

# 2025.10.08

1. only support cross margin mode for all assets trading: spot/futures/swap/option

# 2025.10.05

1. support OKX exchange spread trading API
2. added standard application level heartbeat for websocket api

# 2025.06.17

1. fixed wrong timezone issue

# 2025.05.14

1. remove dependency on vnpy_evo
2. change to use GLOBAL exchange
3. refactor OkxGateway