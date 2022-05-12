import signal


# Achieve Ctrl-c interrupt recv
signal.signal(signal.SIGINT, signal.SIG_DFL)


HEARTBEAT_TOPIC = "heartbeat"
HEARTBEAT_INTERVAL = 10
HEARTBEAT_TOLERANCE = 30
