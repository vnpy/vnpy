from pathlib import Path

from .vnuftmd import MdApi
from .vnufttd import TdApi
from .uft_constant import *

API_PATH = Path(__file__).parent
FUTURES_LICENSE = str(API_PATH.joinpath("futures_license.dat"))
OPTION_LICENSE = str(API_PATH.joinpath("option_license.dat"))