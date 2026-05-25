# Troubleshooting Playbook Index

This directory is the project's "mistake notebook" for recurring integration,
runtime, and development traps. When an issue takes more than one diagnostic
pass, add a playbook here so future work starts from the known evidence and fix
path.

## Entries

- [QMT GUI session and xtquant connect -1](qmt-gui-session-xtquant-connect-minus-1.md)
- [OKX auto-trading runtime](okx-auto-trading.md): startup, health, Telegram,
  tmux process management, and recurring OKX websocket/CTA readiness issues.
- [OKX datafeed malformed instruments](okx-datafeed-malformed-instruments.md):
  public/demo instruments such as `TESTING-USDT` can break CTA datafeed startup
  unless malformed symbols are skipped.
- [Strategy live trade gap diagnostics](strategy-live-trade-gap-diagnostics.md):
  general workflow for proving whether sparse live fills come from signal
  scarcity, strategy state, risk/order routing, gateway health, or data quality.

## Entry Template

Use this structure for new entries:

```markdown
# Short Problem Title

## Symptoms
- What failed, with exact command/output when useful.

## Root Cause
- The smallest confirmed cause. Mark assumptions explicitly.

## Diagnostic Commands
- Commands that separate this issue from similar ones.

## Fix / Recovery
- The safest known recovery path.

## Prevention
- What code, script, doc, or workflow prevents repeat mistakes.

## Verification
- Commands and expected results after recovery.
```
