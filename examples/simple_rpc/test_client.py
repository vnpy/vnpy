from time import sleep
from typing import Any
from vnpy.rpc import RpcClient


class TestClient(RpcClient):
    """
    Test RpcClient
    """

    def __init__(self) -> None:
        """
        Constructor
        """
        super().__init__()

    def callback(self, topic: str, data: Any) -> None:
        """
        Realize callable function
        """
        print(f"client received topic:{topic}, data:{data}")


if __name__ == "__main__":
    req_address = "tcp://localhost:2014"
    sub_address = "tcp://localhost:4102"

    tc = TestClient()
    tc.subscribe_topic("")
    tc.start(req_address, sub_address)

    while 1:
        print(tc.add(1, 3))
        sleep(2)
