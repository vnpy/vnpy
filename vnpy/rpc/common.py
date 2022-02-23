import signal


# Achieve Ctrl-c interrupt recv
signal.signal(signal.SIGINT, signal.SIG_DFL)


HEARTBEAT_TOPIC: str = "heartbeat"
HEARTBEAT_INTERVAL: int = 10
HEARTBEAT_TOLERANCE: int = 30
