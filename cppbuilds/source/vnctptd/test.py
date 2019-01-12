from time import sleep
from datetime import datetime
import vnctptd
from vnctptd import *
print(dir(vnctptd));
obj = CThostFtdcTransferQryDetailRspField()
print_struct(obj)

obj.TradeDate = "123"
print(obj.TradeDate)
print_struct(obj)

obj.TradeDate = "123asdf"
print(obj.TradeDate)
print_struct(obj)


# test for speed:
def test_speed():
    def set_cpp(obj, val):
        obj.TradeDate = val

    def create_cpp():
        return CThostFtdcTransferQryDetailRspField()

    def create_py():
        return dict()

    def set_py(obj, val):
        obj["TradeDate"] = val

    n = int(1e6)
    start = datetime.now()
    for _ in range(n):
        obj = create_cpp()
        for _ in range(5):
            set_cpp(obj, "123123")
        #print_struct(obj)
    end = datetime.now()
    delay1 = end - start


    start = datetime.now()
    for _ in range(n):
        obj = create_py()
        for _ in range(5):
            set_py(obj, "123123")
        #print_dict(obj)

    end = datetime.now()
    delay2 = end - start
    print("delay1 : {}".format(delay1))
    print("delay2 : {}".format(delay2))
    at_end()
    input()

#test_speed()

