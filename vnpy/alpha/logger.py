import sys

from loguru import logger


# Remove default output
logger.remove()


# Add terminal output
fmt: str = "<green>{time:YYYY-MM-DD HH:mm:ss}</green> <level>{message}</level>"
logger.add(sys.stdout, colorize=True, format=fmt)
