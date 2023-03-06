import json
import requests
from vnpy.trader.setting import SETTINGS


def get_from_url(url, params=None, headers=None):
    response = requests.get(url, params=params, headers=headers)
    if response.status_code != 200:
        return None
    resp = json.loads(response.text)
    return resp

