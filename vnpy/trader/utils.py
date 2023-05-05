import hashlib
import json
import requests
import traceback
from cachetools import TTLCache, cached
from vnpy.trader.setting import SETTINGS


def get_from_url(url, params=None, headers=None):
    try:
        response = requests.get(url, params=params, headers=headers, timeout=5)
    except Exception as e:
        print('！网络错误！')
        print(traceback.print_exc())
        return None
    if response.status_code != 200:
        return None
    resp = json.loads(response.text)
    return resp

