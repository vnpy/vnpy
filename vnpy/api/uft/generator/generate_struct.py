""""""
import importlib
from typing import Dict


class StructGenerator:
    """Struct生成器"""

    def __init__(self, filename: str, prefix: str):
        """Constructor"""
        self.filename: str = filename
        self.prefix: str = prefix
        self.typedefs: Dict[str, str] = {}

        self.load_constant()

    def load_constant(self):
        """"""
        module_name = f"{self.prefix}_typedef"
        module = importlib.import_module(module_name)

        for name in dir(module):
            if "__" not in name:
                self.typedefs[name] = getattr(module, name)

    def run(self) -> None:
        """运行生成"""
        self.f_cpp = open(self.filename, "r")
        self.f_struct = open(f"{self.prefix}_struct.py", "w")

        for line in self.f_cpp:
            self.process_line(line)

        self.f_cpp.close()
        self.f_struct.close()

        print("Struct生成成功")

    def process_line(self, line: str) -> None:
        """处理每行"""
        line = line.replace("\n", "")

        if line.startswith("struct"):
            self.process_declare(line)
        elif line.startswith("{"):
            self.process_start(line)
        elif line.startswith("}"):
            self.process_end(line)
        elif "\t" in line and "///" not in line:
            self.process_member(line)
        elif ";" in line and "///" not in line:
            self.process_content(line)

    def process_content(self, line: str) -> None:
        """"""
        line = line.replace(";", "")
        words = line.split(" ")
        words = [word for word in words if word]

        if len(words) > 1:
            py_type = self.typedefs[words[0]]
            name = words[1]

            new_line = f"    \"{name}\": \"{py_type}\",\n"
            self.f_struct.write(new_line)

    def process_declare(self, line: str) -> None:
        """处理声明"""
        line = line.replace(";", "")
        words = line.split(" ")
        name = words[1]
        end = "{"

        new_line = f"{name} = {end}\n"
        self.f_struct.write(new_line)

    def process_start(self, line: str) -> None:
        """处理开始"""
        pass

    def process_end(self, line: str) -> None:
        """处理结束"""
        new_line = "}\n\n"
        self.f_struct.write(new_line)

    def process_member(self, line: str) -> None:
        """处理成员"""
        line = line.replace(";", "")
        words = line.split()
        words = [word for word in words if word]

        py_type = self.typedefs[words[0]]
        name = words[1]

        new_line = f"    \"{name}\": \"{py_type}\",\n"
        self.f_struct.write(new_line)


if __name__ == "__main__":
    generator = StructGenerator("../include/uft/HSStruct.h", "uft")
    generator.run()
