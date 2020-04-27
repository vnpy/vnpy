""""""
import importlib


class StructGenerator:
    """Struct生成器"""

    def __init__(self, filename: str, prefix: str):
        """Constructor"""
        self.filename = filename
        self.prefix = prefix
        self.typedefs = {}
        # self.cout = 0

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
        self.f_struct = open(f"{self.prefix}_struct.py", "w")

        for line in self.f_cpp:
            self.process_line(line)

        self.f_cpp.close()
        self.f_struct.close()

        print("Struct生成成功")

    def process_line(self, line: str):
        """处理每行"""
        line = line.replace(";", "")
        line = line.replace("\n", "")

        if line.startswith("struct"):
            self.process_declare(line)
        elif line.startswith("{"):
            self.process_start(line)
        elif line.startswith("}") and "///" not in line:
            self.process_end(line)
        elif line.startswith("enum"):
            self.process_enum(line)

        elif "KS_TERT" in line:
            self.process_enum_member(line)
        elif "\t" in line and "///" not in line:
            self.process_member(line)

    def process_enum(self, line: str):
        words = line.split(" ")
        name = words[1]
        end = "{"

        new_line = f"{name} = {end}\n"
        self.f_struct.write(new_line)

    def process_enum_member(self, line: str):
        words = line.split(" ")
        words = [word for word in words if word]

        name = words[0]
        if "," in name:
            name = name.split(",")[0]

        name = name.replace("\t", "")

        py_type = "int"

        new_line = f"    \"{name}\": \"{py_type}\",\n"
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
        content = line.split("//")[0]
        words = content.split(" ")
        words = [word for word in words if word]

        if len(words) == 2:
            name = words[1].replace("\t", "")
            cpp_type = words[0].replace("\t", "")
            if not name:
                values = words[0].split("\t")
                values = [value for value in values if value]
                name = values[1]
                cpp_type = values[0]

            py_type = self.typedefs[cpp_type]

            new_line = f"    \"{name}\": \"{py_type}\",\n"
            self.f_struct.write(new_line)

        elif len(words) == 1:

            values = words[0].split("\t")
            values = [value for value in values if value]

            if not values:
                return
            name = values[1]
            cpp_type = values[0]

            py_type = self.typedefs[cpp_type]

            new_line = f"    \"{name}\": \"{py_type}\",\n"
            self.f_struct.write(new_line)
        else:
            cpp_type = words[0].replace("\t", "")

            name = words[1] + words[2]
            name = name.replace("\t", "")
            py_type = self.typedefs[cpp_type]

            new_line = f"    \"{name}\": \"{py_type}\",\n"
            self.f_struct.write(new_line)


if __name__ == "__main__":
    generator = StructGenerator("../include/ksgold/KSGoldUserApiStructEx.h", "ksgold")
    generator.run()
