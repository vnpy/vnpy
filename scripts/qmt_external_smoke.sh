#!/usr/bin/env bash
set -euo pipefail

usage() {
    cat <<'EOF'
Usage:
  scripts/qmt_external_smoke.sh [--execute] [--url http://192.168.2.2:18080] [--token TOKEN]

Default behavior:
  Runs QMT external smoke tests that do NOT place orders:
    - /health
    - /positions
    - /rebalance dry_run idempotency

Options:
  --execute         Also run the QMT simulated-account execute test.
  --url URL         QMT bridge URL. Defaults to QMT_BRIDGE_URL or http://192.168.2.2:18080.
  --token TOKEN     QMT bridge bearer token. Defaults to QMT_BRIDGE_TOKEN.
  --weights JSON    Test target weights. Defaults to QMT_TEST_WEIGHTS_JSON or {"510300.SH": 0.01}.
  --prices JSON     Test reference prices. Defaults to QMT_TEST_PRICES_JSON or {"510300.SH": 4.0}.
  -h, --help        Show this help.

Examples:
  QMT_BRIDGE_TOKEN=secret scripts/qmt_external_smoke.sh
  scripts/qmt_external_smoke.sh --url http://192.168.2.2:18080 --token secret
  scripts/qmt_external_smoke.sh --execute --token secret
EOF
}

RUN_EXECUTE=0
QMT_URL="${QMT_BRIDGE_URL:-http://192.168.2.2:18080}"
TOKEN="${QMT_BRIDGE_TOKEN:-}"
WEIGHTS="${QMT_TEST_WEIGHTS_JSON:-{\"510300.SH\": 0.01}}"
PRICES="${QMT_TEST_PRICES_JSON:-{\"510300.SH\": 4.0}}"

while [[ $# -gt 0 ]]; do
    case "$1" in
        --execute)
            RUN_EXECUTE=1
            shift
            ;;
        --url)
            QMT_URL="${2:-}"
            shift 2
            ;;
        --token)
            TOKEN="${2:-}"
            shift 2
            ;;
        --weights)
            WEIGHTS="${2:-}"
            shift 2
            ;;
        --prices)
            PRICES="${2:-}"
            shift 2
            ;;
        -h|--help)
            usage
            exit 0
            ;;
        *)
            echo "Unknown argument: $1" >&2
            usage >&2
            exit 2
            ;;
    esac
done

if [[ -z "$TOKEN" ]]; then
    echo "QMT bridge token is required. Pass --token or export QMT_BRIDGE_TOKEN." >&2
    exit 2
fi

PYTHON_BIN="${PYTHON_BIN:-.venv/bin/python}"
if [[ ! -x "$PYTHON_BIN" ]]; then
    PYTHON_BIN="python3"
fi

export VNPY_RUN_EXTERNAL_TESTS=1
export QMT_BRIDGE_URL="$QMT_URL"
export QMT_BRIDGE_TOKEN="$TOKEN"
export QMT_TEST_WEIGHTS_JSON="$WEIGHTS"
export QMT_TEST_PRICES_JSON="$PRICES"

echo "QMT bridge: $QMT_BRIDGE_URL"
echo "Weights: $QMT_TEST_WEIGHTS_JSON"
echo "Prices: $QMT_TEST_PRICES_JSON"
echo

"$PYTHON_BIN" -m pytest \
    tests/test_external_integrations.py::test_external_qmt_health \
    tests/test_external_integrations.py::test_external_qmt_positions \
    tests/test_external_integrations.py::test_external_qmt_rebalance_dry_run_is_idempotent \
    -q

if [[ "$RUN_EXECUTE" -eq 1 ]]; then
    echo
    echo "Running QMT simulated-account execute test..."
    export VNPY_RUN_QMT_EXECUTE_TESTS=1
    "$PYTHON_BIN" -m pytest \
        tests/test_external_integrations.py::test_external_qmt_rebalance_execute \
        -q
else
    echo
    echo "Skipped execute test. Add --execute to place simulated-account orders."
fi
