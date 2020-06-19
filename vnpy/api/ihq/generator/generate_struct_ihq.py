""""""
import importlib


class StructGenerator:
    """Struct生成器"""

    structure_start = False
    structure_special = False

    def __init__(self, filename: str, prefix: str):
        """Constructor"""
        self.filename = filename
        self.prefix = prefix
        self.typedefs = {}

        self.load_constant()

    def load_constant(self):
        """"""
        module_name = f"{self.prefix}_typedef"
        module = importlib.import_module(module_name)

        for name in dir(module):
            if "__" not in name:
                self.typedefs[name] = getattr(module, name)

        self.typedefs["char"] = "char"
        self.typedefs["int"] = "int"
        self.typedefs["int16_t"] = "int16_t"
        self.typedefs["int32_t"] = "int32_t"
        self.typedefs["uint32_t"] = "uint32_t"
        self.typedefs["enum"] = "enum"
        self.typedefs["int64_t"] = "int64_t"
        self.typedefs["double"] = "double"
        self.typedefs["uint8_t"] = "uint8_t"

    def run(self):
        """运行生成"""
        self.f_cpp = open(self.filename, "r")
        self.f_struct = open(f"{self.prefix}_struct.py", "w")

        for line in self.f_cpp:
            self.process_line(line)

        self.f_cpp.close()
        self.f_struct.close()

        print(f"{self.prefix} Struct生成成功")

    def process_line(self, line: str):
        """处理每行"""
        line = line.replace(";", "")
        line = line.replace("\n", "")
        line = line.replace("	", " ")

        if "struct" in line or "enum" in line:

            self.process_declare(line)

        elif "{" in line:
            self.process_start(line)
        elif "}" in line:
            self.process_end(line)
        elif"///" not in line and "#" not in line and "namespace" not in line:
            self.process_member(line)

    def process_declare(self, line: str):
        """处理声明"""
        words = line.split(" ")
        words = [word for word in words if word != ""]

        name = words[1]
        end = "{"
        self.structure_start = True

        if name == "CIStoneDepthMarketData":
            self.structure_special = True

        new_line = f"{name} = {end}\n"
        self.f_struct.write(new_line)

    def process_start(self, line: str):
        """处理开始"""
        pass

    def process_end(self, line: str):
        """处理结束"""
        if self.structure_special:
            self.structure_special = False
            return

        if self.structure_start:
            new_line = "}\n\n"
            self.f_struct.write(new_line)
            self.structure_start = False

    def process_enum(self, words):
        """"""
        name = words[0]
        py_type = "int"
        new_line = f"    \"{name}\": \"{py_type}\",\n"
        self.f_struct.write(new_line)

    def process_member(self, line: str):
        """处理成员"""
        if "//" in line:
            line = line.split("//")[0]

        words = line.split(" ")
        words = [word for word in words if word != ""]

        if not words:
            return
        if "=" in words:
            self.process_enum(words)
            return
        name = words[1]

        py_type = self.typedefs.get(words[0], "dict")
        if "[" in name:
            py_type = "string"
            name = name.split("[")[0]

        new_line = f"    \"{name}\": \"{py_type}\",\n"
        self.f_struct.write(new_line)


if __name__ == "__main__":
    generator = StructGenerator("../include/ihq/IStoneMdApiStruct.h", "ihq")
    generator.run()
