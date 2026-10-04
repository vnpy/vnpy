import pickle
import time
from collections.abc import Callable
from typing import Any, NoReturn

import pytest
import zmq

from vnpy.rpc import RpcClient, RpcServer
from vnpy.rpc.client import RemoteException
from vnpy.rpc.common import HEARTBEAT_TOPIC


class Unpicklable:
    def __reduce__(self) -> NoReturn:
        raise pickle.PicklingError("unpicklable")


class RecordingClient(RpcClient):
    def __init__(self) -> None:
        super().__init__()
        self.messages: list[tuple[str, Any]] = []
        self.disconnects: int = 0

    def callback(self, topic: str, data: Any) -> None:
        self.messages.append((topic, data))

    def on_disconnected(self) -> None:
        self.disconnects += 1


def _prepare_server() -> RpcServer:
    server: RpcServer = RpcServer()
    server._socket_rep.setsockopt(zmq.LINGER, 0)
    server._socket_pub.setsockopt(zmq.LINGER, 0)
    return server


def _connect(server: RpcServer, topic: str) -> RecordingClient:
    client: RecordingClient = RecordingClient()
    client._socket_req.setsockopt(zmq.LINGER, 0)
    client._socket_sub.setsockopt(zmq.LINGER, 0)
    client.subscribe_topic(topic)
    client.start(
        server._socket_rep.getsockopt_string(zmq.LAST_ENDPOINT),
        server._socket_pub.getsockopt_string(zmq.LAST_ENDPOINT),
    )
    return client


def _publish_until(
    server: RpcServer,
    predicate: Callable[[], bool],
    messages: list[tuple[str, object]],
) -> None:
    deadline: float = time.monotonic() + 3
    while time.monotonic() < deadline:
        item: tuple[str, object]
        for item in messages:
            server.publish(item[0], item[1])
        if predicate():
            return
        time.sleep(0.02)
    assert predicate()


def _shutdown(server: RpcServer, client: RpcClient, topic: str) -> None:
    client.stop()
    if server.is_active():
        server.publish(topic, None)
        server.publish(HEARTBEAT_TOPIC, time.time())
    client.join()
    if server.is_active():
        server.stop()
        server.join()


def test_remote_call_returns_value_and_wraps_server_exception() -> None:
    def add(a: int, b: int) -> int:
        return a + b

    def fail() -> None:
        raise RuntimeError("boom")

    server: RpcServer = _prepare_server()
    server.register(add)
    server.register(fail)
    server.start("tcp://127.0.0.1:0", "tcp://127.0.0.1:0")
    client: RecordingClient = _connect(server, "")
    try:
        assert client.add(2, 3) == 5
        with pytest.raises(RemoteException, match="boom"):
            client.fail()
    finally:
        _shutdown(server, client, "")


def test_empty_subscription_delivers_payload_and_hides_heartbeat() -> None:
    server: RpcServer = _prepare_server()
    server.start("tcp://127.0.0.1:0", "tcp://127.0.0.1:0")
    client: RecordingClient = _connect(server, "")
    try:
        _publish_until(
            server,
            lambda: ("", {"k": "v"}) in client.messages and client._last_received_ping == 50.0,
            [("", {"k": "v"}), (HEARTBEAT_TOPIC, 50.0)],
        )
        assert all(topic != HEARTBEAT_TOPIC for topic, _data in client.messages)
        assert client.disconnects == 0
    finally:
        _shutdown(server, client, "")


def test_topic_subscription_filters_prefixes_and_keeps_heartbeat() -> None:
    server: RpcServer = _prepare_server()
    server.start("tcp://127.0.0.1:0", "tcp://127.0.0.1:0")
    client: RecordingClient = _connect(server, "tick")
    try:
        _publish_until(
            server,
            lambda: ("tick", 1) in client.messages and client._last_received_ping == 50.0,
            [("tick", 1), (HEARTBEAT_TOPIC, 50.0)],
        )
        server.publish("alert", "later")
        _publish_until(
            server,
            lambda: ("ticker", 9) in client.messages and ("tick", 2) in client.messages,
            [("ticker", 9), ("tick", 2)],
        )
        assert ("alert", "later") not in client.messages
        assert all(topic != HEARTBEAT_TOPIC for topic, _data in client.messages)
        assert client.disconnects == 0
    finally:
        _shutdown(server, client, "tick")


def test_publish_pickling_error_does_not_block_later_messages() -> None:
    server: RpcServer = _prepare_server()
    server.start("tcp://127.0.0.1:0", "tcp://127.0.0.1:0")
    client: RecordingClient = _connect(server, "tick")
    try:
        with pytest.raises(pickle.PicklingError):
            server.publish("tick", Unpicklable())
        _publish_until(
            server,
            lambda: ("tick", 1) in client.messages,
            [("tick", 1)],
        )
    finally:
        _shutdown(server, client, "tick")
