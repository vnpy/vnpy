#!/usr/bin/env bash
set -euo pipefail

ROOT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
TRADER_DIR="${VNPY_TRADER_DIR:-$HOME/.vntrader}"
PID_FILE="${OKX_AUTO_PID_FILE:-$TRADER_DIR/okx_auto_trading.pid}"
STDOUT_LOG="${OKX_AUTO_STDOUT_LOG:-$TRADER_DIR/okx_auto_stdout.log}"
PYTHON="${PYTHON:-$ROOT_DIR/.venv/bin/python}"

usage() {
    cat <<'EOF'
Usage: scripts/okx_auto_trading.sh start|stop|status|restart|health|tail

Manage the local OKX auto-trading process.

Commands:
  start    Start run_auto_trading.py in the background with a PID lock.
  stop     Gracefully stop the recorded process.
  status   Show PID and process status.
  restart  Stop then start.
  health   Print machine-readable health JSON.
  tail     Follow stdout/stderr log.
EOF
}

is_alive() {
    local pid="$1"
    [[ -n "$pid" ]] && kill -0 "$pid" 2>/dev/null
}

read_pid() {
    [[ -f "$PID_FILE" ]] && tr -d '[:space:]' < "$PID_FILE" || true
}

cmd="${1:-}"
case "$cmd" in
    --help|-h|help)
        usage
        exit 0
        ;;
    start)
        mkdir -p "$TRADER_DIR"
        pid="$(read_pid)"
        if is_alive "$pid"; then
            echo "OKX auto-trading already running: pid=$pid"
            exit 0
        fi
        if [[ -n "$pid" ]]; then
            echo "Removing stale PID file: $PID_FILE"
            rm -f "$PID_FILE"
        fi
        cd "$ROOT_DIR"
        nohup "$PYTHON" run_auto_trading.py >> "$STDOUT_LOG" 2>&1 &
        new_pid="$!"
        echo "$new_pid" > "$PID_FILE"
        echo "Started OKX auto-trading: pid=$new_pid log=$STDOUT_LOG"
        ;;
    stop)
        pid="$(read_pid)"
        if ! is_alive "$pid"; then
            echo "OKX auto-trading is not running"
            rm -f "$PID_FILE"
            exit 0
        fi
        kill "$pid"
        for _ in $(seq 1 20); do
            if ! is_alive "$pid"; then
                rm -f "$PID_FILE"
                echo "Stopped OKX auto-trading: pid=$pid"
                exit 0
            fi
            sleep 0.5
        done
        echo "Process did not stop gracefully, sending SIGKILL: pid=$pid" >&2
        kill -9 "$pid" 2>/dev/null || true
        rm -f "$PID_FILE"
        ;;
    status)
        pid="$(read_pid)"
        if is_alive "$pid"; then
            echo "OKX auto-trading running: pid=$pid"
            exit 0
        fi
        echo "OKX auto-trading not running"
        exit 1
        ;;
    restart)
        "$0" stop || true
        "$0" start
        ;;
    health)
        "$PYTHON" "$ROOT_DIR/tools/okx_auto_health.py" --pid "$PID_FILE"
        ;;
    tail)
        mkdir -p "$TRADER_DIR"
        touch "$STDOUT_LOG"
        tail -f "$STDOUT_LOG"
        ;;
    *)
        echo "Unknown command: ${cmd:-<empty>}" >&2
        usage >&2
        exit 2
        ;;
esac
