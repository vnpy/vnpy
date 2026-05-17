#!/usr/bin/env bash
set -euo pipefail

usage() {
    cat <<'EOF'
Usage:
  scripts/qmt_bridge_remote.sh <command> [options]

Commands:
  status   Show the remote port listener and scheduled task status.
  start    Start the interactive Windows task for the QMT bridge.
  health   Probe the bridge /health endpoint.
  smoke    Run the safe QMT external smoke suite.
  help     Show this help.

Options:
  --host HOST       SSH host alias. Defaults to QMT_WINDOWS_HOST or win.
  --task NAME      Scheduled task name. Defaults to QMT_BRIDGE_TASK or CodexQmtBridge.
  --url URL        Bridge URL. Defaults to QMT_BRIDGE_URL or http://192.168.2.2:18080.
  --token TOKEN    Bridge token. Defaults to QMT_BRIDGE_TOKEN.

Notes:
  The start command can start the interactive Windows task from SSH. The task must use
  InteractiveToken and call D:\test\start_qmt_bridge_codex.bat, which launches
  pythonw.exe. This lets Codex start the bridge from SSH without a pausing
  console window.
EOF
}

COMMAND="${1:-help}"
if [[ $# -gt 0 ]]; then
    shift
fi

HOST="${QMT_WINDOWS_HOST:-win}"
TASK="${QMT_BRIDGE_TASK:-CodexQmtBridge}"
URL="${QMT_BRIDGE_URL:-http://192.168.2.2:18080}"
TOKEN="${QMT_BRIDGE_TOKEN:-}"

while [[ $# -gt 0 ]]; do
    case "$1" in
        --host)
            HOST="${2:-}"
            shift 2
            ;;
        --task)
            TASK="${2:-}"
            shift 2
            ;;
        --url)
            URL="${2:-}"
            shift 2
            ;;
        --token)
            TOKEN="${2:-}"
            shift 2
            ;;
        -h|--help)
            usage
            exit 0
            ;;
        *)
            echo "Unknown option: $1" >&2
            usage >&2
            exit 2
            ;;
    esac
done

case "$COMMAND" in
    help|--help|-h)
        usage
        ;;
    status)
        echo "== Interactive user =="
        ssh "$HOST" "cmd /c query user" || true
        echo
        echo "== QMT processes =="
        ssh "$HOST" "cmd /c tasklist /v | findstr /i XtMiniQmt" || true
        ssh "$HOST" "cmd /c tasklist /v | findstr /i XtItClient" || true
        ssh "$HOST" "cmd /c tasklist /v | findstr /i miniquote" || true
        echo
        echo "== Bridge listener =="
        ssh "$HOST" "cmd /c netstat -ano | findstr :18080"
        echo
        echo "== Scheduled task =="
        ssh "$HOST" "cmd /c schtasks /query /tn $TASK /fo list"
        ;;
    start)
        ssh "$HOST" "cmd /c schtasks /run /tn $TASK"
        ;;
    health)
        NO_PROXY='*' no_proxy='*' curl --noproxy '*' -m 5 -sS -i "$URL/health"
        ;;
    smoke)
        if [[ -z "$TOKEN" ]]; then
            echo "QMT bridge token is required. Pass --token or export QMT_BRIDGE_TOKEN." >&2
            exit 2
        fi
        NO_PROXY='*' no_proxy='*' scripts/qmt_external_smoke.sh --url "$URL" --token "$TOKEN"
        ;;
    *)
        echo "Unknown command: $COMMAND" >&2
        usage >&2
        exit 2
        ;;
esac
