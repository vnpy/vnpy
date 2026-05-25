# OKX Datafeed Malformed Instruments

## Symptoms

- OKX auto-trading startup exits during CTA datafeed initialization.
- Logs show `ValueError: not enough values to unpack (expected 3, got 2)`.
- The failing instrument can be a demo/public instrument such as `TESTING-USDT`
  returned under `instType=FUTURES`.

## Root Cause

- OKX can return malformed or non-tradable demo instruments whose `instId` does
  not match the expected `BASE-QUOTE-EXPIRY` futures shape.
- Gateway contract loading already skipped malformed SWAP/FUTURES instruments,
  but the OKX datafeed symbol mapper did not, so one malformed public instrument
  could abort startup before CTA strategies initialized.

## Diagnostic Commands

```bash
tail -n 160 ~/.vntrader/okx_auto_stdout.log
rg -n "not enough values to unpack|malformed|TESTING-USDT|datafeed" ~/.vntrader/log ~/.vntrader/okx_auto_stdout.log
```

## Fix / Recovery

- Make `vnpy_okx/vnpy_okx/datafeed.py` skip malformed SWAP/FUTURES symbols and
  continue loading the rest of the instrument map.
- Restart the OKX auto-trading tmux session after the fix.

## Prevention

- Keep gateway and datafeed instrument parsing behavior aligned.
- Add regression coverage for malformed demo futures symbols in
  `tests/test_okx_datafeed.py`.
- For live trade gaps, follow
  `docs/troubleshooting/strategy-live-trade-gap-diagnostics.md` before tuning
  strategy parameters. For Chan specifically, `tools/chan_runtime_diagnostics.py`
  is the current adapter.

## Verification

```bash
.venv/bin/python -m pytest tests/test_okx_datafeed.py tests/test_okx_gateway_instidcode.py -q
.venv/bin/python tools/chan_runtime_diagnostics.py
```

Expected result: tests pass, and startup no longer aborts on malformed demo
instruments.
