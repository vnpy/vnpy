"""
WeChat iLink protocol for sending text messages and polling updates.
"""

import base64
import json
import secrets
import time
import uuid
from dataclasses import dataclass
from typing import Any

import requests

from .locale import _


# Default WeChat iLink gateway URL
DEFAULT_BASE_URL: str = "https://ilinkai.weixin.qq.com"

# Required value of base_info.channel_version in every iLink request body
_CHANNEL_VERSION: str = "2.2.0"

# iLink client identifier sent in the iLink-App-Id request header
_APP_ID: str = "bot"

# iLink client version; Major.Minor.Patch=2.2.0 encoded as 24-bit integer (131584)
_CLIENT_VERSION: str = str((2 << 16) | (2 << 8) | 0)

# Request timeout
_REQUEST_TIMEOUT: float = 30.0


class WeixinError(Exception):
    """SDK general exception."""


class SessionExpired(WeixinError):
    """iLink reports session expired (errcode/ret == -14)."""


class WeixinTimeout(WeixinError):
    """HTTP request timed out."""


@dataclass
class Credentials:
    """
    Access credentials returned by iLink QR-code login.
    """

    bot_id: str
    token: str
    base_url: str = DEFAULT_BASE_URL


def send_text(
    creds: Credentials,
    user_id: str,
    text: str,
) -> None:
    """
    Send a text message to the specified user.
    """
    msg: dict[str, Any] = {
        "from_user_id": "",
        "to_user_id": user_id,
        "client_id": uuid.uuid4().hex,
        "message_type": 2,      # 2 = bot active message
        "message_state": 2,     # 2 = sent
        "item_list": [
            {"type": 1, "text_item": {"text": text}},   # type=1 = text item
        ],
    }

    session: requests.Session
    with requests.Session() as session:
        _post(
            creds.base_url,
            "ilink/bot/sendmessage",
            creds.token,
            {"msg": msg},
            session=session,
            timeout=_REQUEST_TIMEOUT,
        )


def poll(
    creds: Credentials,
    sync_buf: str = "",
) -> tuple[list[str], str]:
    """
    Long-poll inbound messages from iLink.

    Returns a tuple of (user IDs, next sync_buf).
    """
    session: requests.Session
    with requests.Session() as session:
        data: dict[str, Any] = _post(
            creds.base_url,
            "ilink/bot/getupdates",
            creds.token,
            {"get_updates_buf": sync_buf},
            session=session,
            timeout=60,
        )

    next_buf: str = str(data.get("get_updates_buf") or sync_buf)
    user_ids: list[str] = []

    raw_messages: Any = data.get("msgs")
    if isinstance(raw_messages, list):
        raw: object
        for raw in raw_messages:
            if not isinstance(raw, dict):
                continue

            user_id: str = _parse_user_id(raw, creds.bot_id)
            if user_id:
                user_ids.append(user_id)

    return user_ids, next_buf


def request_qrcode() -> tuple[str, str]:
    """
    Request a new QR code from iLink.

    Returns a tuple of (qrcode, scan_url).
    """
    session: requests.Session
    with requests.Session() as session:
        qr_data: dict[str, Any] = _get(
            DEFAULT_BASE_URL,
            "ilink/bot/get_bot_qrcode",
            {"bot_type": "3"},
            session=session,
            timeout=_REQUEST_TIMEOUT,
        )

    qrcode: str = str(qr_data.get("qrcode") or "").strip()
    if not qrcode:
        raise WeixinError(_("二维码响应缺少 qrcode"))

    scan_url: str = str(qr_data.get("qrcode_img_content") or "").strip() or qrcode
    return qrcode, scan_url


def wait_for_login(
    qrcode: str,
    deadline: float,
) -> Credentials | None:
    """
    Poll QR-code status until confirmed, expired or deadline reached.

    Returns Credentials on confirmation, or None if expired or deadline reached.
    """
    current_url: str = DEFAULT_BASE_URL

    session: requests.Session
    with requests.Session() as session:
        while time.monotonic() < deadline:
            try:
                status_data: dict[str, Any] = _get(
                    current_url,
                    "ilink/bot/get_qrcode_status",
                    {"qrcode": qrcode},
                    session=session,
                    timeout=_REQUEST_TIMEOUT,
                )
            except WeixinTimeout:
                continue
            status: str = str(status_data.get("status") or "").strip()

            if status == "confirmed":
                creds: Credentials = Credentials(
                    bot_id=str(status_data.get("ilink_bot_id") or "").strip(),
                    token=str(status_data.get("bot_token") or "").strip(),
                    base_url=str(status_data.get("baseurl") or current_url),
                )
                if not creds.bot_id or not creds.token:
                    raise WeixinError(_("扫码确认响应缺少凭据"))
                return creds

            if status == "scaned_but_redirect":
                # iLink requires switching follow-up requests to redirect_host
                host: str = str(status_data.get("redirect_host") or "").strip()
                if host:
                    current_url = f"https://{host}"
            elif status == "expired":
                return None

            time.sleep(1)

    return None


def _post(
    base_url: str,
    path: str,
    token: str | None,
    payload: dict[str, Any],
    session: requests.Session,
    timeout: float,
) -> dict[str, Any]:
    """Send an iLink POST request and validate the business return code."""
    body: bytes = json.dumps(
        {**payload, "base_info": {"channel_version": _CHANNEL_VERSION}},
        ensure_ascii=False,
        separators=(",", ":"),
    ).encode("utf-8")
    url: str = f"{base_url.rstrip('/')}/{path.lstrip('/')}"
    headers: dict[str, str] = _headers(token)

    exc: requests.RequestException
    try:
        response: requests.Response = session.post(
            url,
            data=body,
            headers=headers,
            timeout=timeout,
        )
    except requests.exceptions.Timeout as exc:
        raise WeixinTimeout(_("HTTP 请求超时: {}").format(exc)) from exc
    except requests.RequestException as exc:
        raise WeixinError(_("HTTP 请求失败: {}").format(exc)) from exc

    return _parse(response)


def _get(
    base_url: str,
    path: str,
    params: dict[str, Any],
    session: requests.Session,
    timeout: float,
) -> dict[str, Any]:
    """Send an iLink GET request and validate the business return code."""
    url: str = f"{base_url.rstrip('/')}/{path.lstrip('/')}"
    headers: dict[str, str] = {
        "iLink-App-Id": _APP_ID,
        "iLink-App-ClientVersion": _CLIENT_VERSION,
    }

    exc: requests.RequestException
    try:
        response: requests.Response = session.get(
            url,
            params=params,
            headers=headers,
            timeout=timeout,
        )
    except requests.exceptions.Timeout as exc:
        raise WeixinTimeout(_("HTTP 请求超时: {}").format(exc)) from exc
    except requests.RequestException as exc:
        raise WeixinError(_("HTTP 请求失败: {}").format(exc)) from exc

    return _parse(response)


def _parse(response: requests.Response) -> dict[str, Any]:
    """Parse iLink response, validate HTTP status and business return code."""
    if not response.ok:
        raise WeixinError(f"HTTP {response.status_code}: {response.text[:200]}")

    exc: ValueError
    try:
        data: Any = response.json()
    except ValueError as exc:
        raise WeixinError(_("非 JSON 响应: {}").format(response.text[:200])) from exc

    if not isinstance(data, dict):
        raise WeixinError(_("响应不是 JSON 对象: {}").format(response.text[:200]))

    ret: Any = data.get("ret") or 0
    err: Any = data.get("errcode") or 0

    # -14 is the iLink error code for expired session.
    if ret == -14 or err == -14:
        raise SessionExpired(str(data.get("errmsg") or _("iLink 会话已过期")))
    if ret or err:
        raise WeixinError(
            _("iLink 错误 ret={} errcode={} errmsg={}").format(
                ret,
                err,
                data.get("errmsg"),
            ),
        )

    return data


def _headers(token: str | None) -> dict[str, str]:
    """Generate standard headers for an iLink POST request."""
    # X-WECHAT-UIN: regenerated per request, random uint32 -> decimal -> base64
    uin: str = base64.b64encode(str(secrets.randbelow(1 << 32)).encode()).decode()
    headers: dict[str, str] = {
        "Content-Type": "application/json",
        "AuthorizationType": "ilink_bot_token",
        "X-WECHAT-UIN": uin,
        "iLink-App-Id": _APP_ID,
        "iLink-App-ClientVersion": _CLIENT_VERSION,
    }
    if token:
        headers["Authorization"] = f"Bearer {token}"
    return headers


def _parse_user_id(raw: dict[str, Any], bot_id: str) -> str:
    """Parse sender user ID from an iLink raw message; ignore bot's own messages."""
    sender: str = str(raw.get("from_user_id") or "").strip()
    if not sender or sender == bot_id:
        return ""

    return sender
