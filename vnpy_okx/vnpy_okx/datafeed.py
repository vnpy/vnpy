from datetime import datetime
from time import sleep, monotonic
from collections.abc import Callable

from vnpy_rest import RestClient, Response
from vnpy.trader.datafeed import BaseDatafeed
from vnpy.trader.object import HistoryRequest, BarData, TickData
from vnpy.trader.utility import load_json

from .okx_gateway import INTERVAL_VT2OKX, REAL_REST_HOST, CHINA_TZ, parse_timestamp


def _normalize_request_datetime(dt: datetime) -> datetime:
    if dt.tzinfo is None:
        return dt.replace(tzinfo=CHINA_TZ)
    return dt.astimezone(CHINA_TZ)


class OkxRestClient(RestClient):
    """Public REST client for OKX datafeed."""

    def sign(self, request):  # type: ignore[override]
        return request


class Datafeed(BaseDatafeed):
    """
    OKX datafeed using public REST endpoints.
    """

    def __init__(self) -> None:
        self.rest: OkxRestClient = OkxRestClient()
        self.symbol_map: dict[str, str] = {}
        self.output: Callable = print
        self._cancelled: bool = False
        self.log_interval_seconds: float = 5.0

    def init(self, output: Callable = print) -> bool:
        self.output = output
        config: dict = load_json("connect_okx.json")
        proxy_host: str = config.get("Proxy Host", "")
        proxy_port: int = int(config.get("Proxy Port", 0) or 0)
        self.rest.init(REAL_REST_HOST, proxy_host, proxy_port)
        self._cancelled = False

        ok: bool = self._load_instruments()
        if ok:
            self.output("OKX datafeed initialized")
        return ok

    def _load_instruments(self) -> bool:
        self.symbol_map.clear()

        inst_types: list[str] = ["SPOT", "SWAP", "FUTURES"]
        for inst_type in inst_types:
            resp: Response = self.rest.request(
                "GET",
                "/api/v5/public/instruments",
                params={"instType": inst_type},
            )
            if resp.status_code // 100 != 2:
                self.output(
                    f"OKX instruments request failed: {inst_type}, "
                    f"status={resp.status_code}, msg={resp.text}"
                )
                return False

            payload: dict = resp.json()
            if payload.get("code") != "0":
                self.output(
                    f"OKX instruments response error: {inst_type}, "
                    f"code={payload.get('code')}, msg={payload.get('msg')}"
                )
                return False

            for d in payload.get("data", []):
                inst_id: str = d.get("instId", "")
                if not inst_id:
                    continue

                symbol: str | None = self._map_symbol(inst_id, inst_type)
                if symbol:
                    self.symbol_map[symbol] = inst_id

        return bool(self.symbol_map)

    def _map_symbol(self, inst_id: str, inst_type: str) -> str | None:
        if inst_type == "SPOT":
            return inst_id.replace("-", "") + "_SPOT_OKX"
        if inst_type == "SWAP":
            try:
                base, quote, _ = inst_id.split("-")
            except ValueError:
                self.output(f"OKX datafeed: skip malformed SWAP instrument: {inst_id}")
                return None
            return f"{base}{quote}_SWAP_OKX"
        if inst_type == "FUTURES":
            try:
                base, quote, expiry = inst_id.split("-")
            except ValueError:
                self.output(f"OKX datafeed: skip malformed FUTURES instrument: {inst_id}")
                return None
            return f"{base}{quote}_{expiry}_OKX"
        return None

    def query_bar_history(self, req: HistoryRequest, output: Callable = print) -> list[BarData]:
        self.output = output
        self._cancelled = False

        inst_id: str | None = self.symbol_map.get(req.symbol)
        if not inst_id:
            self.output(f"OKX datafeed: symbol not found: {req.symbol}")
            return []

        if req.interval not in INTERVAL_VT2OKX:
            self.output(f"OKX datafeed: unsupported interval: {req.interval}")
            return []

        if not req.end:
            req.end = datetime.now(CHINA_TZ)

        req.start = _normalize_request_datetime(req.start)
        req.end = _normalize_request_datetime(req.end)

        after: str = str(int(req.end.timestamp() * 1000))
        limit: str = "100"
        buf: dict[datetime, BarData] = {}

        total_seconds: float = max((req.end - req.start).total_seconds(), 0.0)

        last_log_time: float = 0.0
        while True:
            if self._cancelled:
                self.output("OKX datafeed: download cancelled")
                break
            sleep(0.1)
            params: dict = {
                "instId": inst_id,
                "bar": INTERVAL_VT2OKX[req.interval],
                "limit": limit,
                "after": after,
            }

            resp: Response = self.rest.request(
                "GET",
                "/api/v5/market/history-candles",
                params=params,
            )

            if resp.status_code // 100 != 2:
                self.output(
                    f"OKX kline query failed, status={resp.status_code}, msg={resp.text}"
                )
                break

            payload: dict = resp.json()
            rows: list | None = payload.get("data")
            if not rows:
                msg: str = payload.get("msg", "No data returned.")
                self.output(f"OKX kline query empty: {msg}")
                break

            for row in rows:
                ts, op, hp, lp, cp, volume, turnover, _, _ = row
                dt: datetime = parse_timestamp(ts)
                bar: BarData = BarData(
                    symbol=req.symbol,
                    exchange=req.exchange,
                    datetime=dt,
                    interval=req.interval,
                    volume=float(volume),
                    turnover=float(turnover),
                    open_price=float(op),
                    high_price=float(hp),
                    low_price=float(lp),
                    close_price=float(cp),
                    gateway_name="OKX",
                )
                buf[bar.datetime] = bar

            begin: str = rows[-1][0]
            begin_dt: datetime = parse_timestamp(begin)
            done_seconds: float = (req.end - begin_dt).total_seconds()
            now: float = monotonic()
            if now - last_log_time >= self.log_interval_seconds:
                if total_seconds > 0:
                    pct: float = max(min(done_seconds / total_seconds * 100.0, 100.0), 0.0)
                    self.output(
                        f"OKX数据下载进度：已拉到 {begin_dt}，{pct:.2f}%（{len(buf)}条）"
                    )
                else:
                    self.output(f"OKX数据下载进度：已拉到 {begin_dt}（{len(buf)}条）")
                last_log_time = now
            if begin_dt <= req.start:
                break

            after = begin

        index: list[datetime] = sorted(buf.keys())
        return [buf[i] for i in index]

    def query_tick_history(self, req: HistoryRequest, output: Callable = print) -> list[TickData]:
        self.output = output
        self.output("OKX datafeed: tick history not supported via public API")
        return []

    def cancel(self) -> None:
        """"""
        self._cancelled = True

    def reset(self) -> None:
        """"""
        self._cancelled = False
