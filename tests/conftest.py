import os
import sys
import tempfile
from pathlib import Path

import pytest


REPO_ROOT: Path = Path(__file__).resolve().parent.parent
if str(REPO_ROOT) not in sys.path:
    sys.path.insert(0, str(REPO_ROOT))

# vnpy.trader.utility 导入时按当前目录决定 .vntrader 位置，vnpy.trader.setting 导入时读取 vt_setting.json。
# 必须在第一次 import vnpy 之前切到带空 .vntrader 的临时目录，避免读写用户真实配置。
ORIGINAL_CWD: str = os.getcwd()
TRADER_TEMP_DIR: tempfile.TemporaryDirectory = tempfile.TemporaryDirectory()
Path(TRADER_TEMP_DIR.name).joinpath(".vntrader").mkdir()
os.chdir(TRADER_TEMP_DIR.name)

from vnpy.trader.setting import SETTINGS  # noqa: E402

# vnpy.trader.logger 导入时按 log.file 创建日志目录，需在它被导入前关闭。
SETTINGS["log.file"] = False
SETTINGS["log.console"] = False


def pytest_unconfigure(config: pytest.Config) -> None:
    os.chdir(ORIGINAL_CWD)
    TRADER_TEMP_DIR.cleanup()
