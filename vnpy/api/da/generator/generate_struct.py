""""""
import importlib


class StructGenerator:
    """Struct生成器"""

    def __init__(self, filename: str, prefix: str, sub_name: str):
        """Constructor"""
        self.filename = filename
        self.prefix = prefix
        self.sub_name = sub_name
        self.typedefs = {}

        self.load_constant()

    def load_constant(self):
        """"""
        module_name = f"{self.prefix}_typedef"
        module = importlib.import_module(module_name)

        for name in dir(module):
            if "__" not in name:
                self.typedefs[name] = getattr(module, name)

    def run(self):
        """运行生成"""
        self.f_cpp = open(self.filename, "r")
        self.f_struct = open(f"{self.prefix}_{self.sub_name}_struct.py", "w")

        for line in self.f_cpp:
            self.process_line(line)

        self.f_cpp.close()
        self.f_struct.close()

        print("Struct生成成功")

    def process_line(self, line: str):
        """处理每行"""
        line = line.replace(";", "")
        line = line.replace("\n", "")

        if line.startswith("typedef"):
            self.process_typedef(line)
        elif line.startswith("struct"):
            self.process_declare(line)
        elif line.startswith("{"):
            self.process_start(line)
        elif line.startswith("}"):
            self.process_end(line)
        elif "\t" in line and "///" not in line:
            self.process_member(line)

    def process_typedef(self, line: str):
        """处理类型定义"""
        line = line.replace("\t", " ")
        words = line.split(" ")
        name = words[1]
        value = words[2]
        new_line = f"{value} = {name}\n\n"
        self.f_struct.write(new_line)

    def process_declare(self, line: str):
        """处理声明"""
        words = line.split(" ")
        name = words[1]
        end = "{"

        new_line = f"{name} = {end}\n"
        self.f_struct.write(new_line)

    def process_start(self, line: str):
        """处理开始"""
        pass

    def process_end(self, line: str):
        """处理结束"""
        new_line = "}\n\n"
        self.f_struct.write(new_line)

    def process_member(self, line: str):
        """处理成员"""
        words = line.split("\t")
        words = [word.replace(" ", "") for word in words if word]
        py_type = self.typedefs[words[0]]
        name = words[1]

        new_line = f"    \"{name}\": \"{py_type}\",\n"
        self.f_struct.write(new_line)


if __name__ == "__main__":
    generator_future = StructGenerator(
        "../include/da/DAFutureStruct.h", "da", "future")
    generator_future.run()

    generator_stock = StructGenerator(
        "../include/da/DAStockStruct.h", "da", "stock")
    generator_stock.run()

    generator_market = StructGenerator(
        "../include/da/DAMarketStruct.h", "da", "market")
    generator_market.run()
