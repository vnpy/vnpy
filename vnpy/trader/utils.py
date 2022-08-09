import json
import requests


def get_from_url(url, params=None):
    response = requests.get(url, params=params)
    if response.status_code != 200:
        return None
    resp = json.loads(response.text)
    return resp

