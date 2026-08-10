from threading import Event
from typing import Any, cast
from uuid import uuid4

import pytest
import zmq

from vnpy.rpc import RpcClient, RpcServer
from vnpy.rpc.client import RemoteException


class RequestSocketProxy:
    """Release the delayed reply only after the second request is sent."""

    def __init__(self, socket: zmq.Socket, release: Event) -> None:
        self._socket: zmq.Socket = socket
        self._release: Event = release
        self._send_count: int = 0

    def send_pyobj(self, *args: Any, **kwargs: Any) -> Any:
        result: Any = self._socket.send_pyobj(*args, **kwargs)
        self._send_count += 1

        if self._send_count == 2:
            self._release.set()

        return result

    def __getattr__(self, name: str) -> Any:
        return getattr(self._socket, name)


class RpcTestClient(RpcClient):
    def __init__(self) -> None:
        super().__init__()
        self.ready: Event = Event()

    def callback(self, topic: str, data: Any) -> None:
        if topic == "ready":
            self.ready.set()


class RpcTestServer(RpcServer):
    def __init__(self, entered: Event, release: Event) -> None:
        super().__init__()
        self.entered: Event = entered
        self.release: Event = release
        self.register(self.slow)
        self.register(self.ping)

    def slow(self) -> str:
        self.entered.set()
        self.release.wait()
        return "late reply"

    def ping(self) -> str:
        return "pong"


def test_client_remains_usable_after_request_timeout(
    monkeypatch: pytest.MonkeyPatch,
) -> None:
    """A late reply must not poison the client or satisfy the next call."""
    context: zmq.Context = zmq.Context()
    monkeypatch.setattr(zmq, "Context", lambda: context)

    entered: Event = Event()
    release: Event = Event()
    server: RpcTestServer = RpcTestServer(entered, release)
    client: RpcTestClient = RpcTestClient()
    client._socket_req = cast(
        zmq.Socket,
        RequestSocketProxy(client._socket_req, release),
    )

    endpoint: str = uuid4().hex
    rep_address: str = f"inproc://rpc-request-{endpoint}"
    pub_address: str = f"inproc://rpc-publish-{endpoint}"

    server.start(rep_address, pub_address)
    client.subscribe_topic("")
    client.start(rep_address, pub_address)
    server_thread = server._thread
    client_thread = client._thread
    assert server_thread is not None
    assert client_thread is not None

    try:
        for _ in range(100):
            server.publish("ready", None)
            if client.ready.wait(0.01):
                break
        assert client.ready.is_set()

        with pytest.raises(RemoteException, match="Timeout of 100ms reached"):
            client.slow(timeout=100)
        assert entered.wait(1)

        assert client.ping(timeout=1_000) == "pong"
    finally:
        release.set()

        client.stop()
        server.publish("stop", None)
        client.join()

        server.stop()
        server.join()

        context.term()

    assert not client_thread.is_alive()
    assert not server_thread.is_alive()
