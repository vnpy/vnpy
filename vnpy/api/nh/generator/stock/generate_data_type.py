""""""

TYPE_CPP2PY = {
    "int": "int",
    "char": "char",
    "double": "double",
    "short": "int",
    "long": "int",
    "bool": "bool",
    "unsigned": "int"
}


class DataTypeGenerator:
    """DataType生成器"""

    def __init__(self, filename: str, prefix: str):
        """Constructor"""
        self.filename = filename
        self.prefix = prefix

    def run(self):
        """主函数"""
        self.f_cpp = open(self.filename, "r")
        self.f_define = open(f"{self.prefix}_constant.py", "w")
        self.f_typedef = open(f"{self.prefix}_typedef.py", "w")

        for line in self.f_cpp:
            try:
                self.process_line(line)
            except Exception:
                import traceback
                print(line)
                traceback.print_exc()
                return

        self.f_cpp.close()
        self.f_define.close()
        self.f_typedef.close()

        print("DataType生成完毕")

    def process_line(self, line: str):
        """处理每行"""
        line = line.replace("\n", "")
        line = line.replace(";", "")
        line = line.replace("\t", "    ")

        if line.startswith("const"):
            self.process_const(line)
        elif line.startswith("#define"):
            self.process_define(line)
        elif line.startswith("typedef"):
            self.process_typedef(line)

    def process_const(self, line: str):
        """处理常量定义"""
        words = line.split(" ")
        words = [word for word in words if word]
        if len(words) < 3:
            return

        name = words[2]
        value = words[4]

        if value in {"true", "false"}:
            value = value.capitalize()

        new_line = f"{name} = {value}\n"
        self.f_define.write(new_line)

    def process_define(self, line: str):
        """处理define定义"""
        words = line.split(" ")
        words = [word for word in words if word]
        if len(words) < 3:
            return

        name = words[1]
        value = words[2]

        new_line = f"{name} = {value}\n"
        self.f_define.write(new_line)

    def process_typedef(self, line: str):
        """处理类型定义"""
        words = line.split(" ")
        words = [word for word in words if word not in {" ", ""}]

        if "unsigned" in words:
            name = words[3]
        else:
            name = words[2]
        typedef = TYPE_CPP2PY[words[1]]

        if typedef == "char":
            if "[" in name:
                typedef = "string"
                name = name[:name.index("[")]

        new_line = f"{name} = \"{typedef}\"\n"
        self.f_typedef.write(new_line)


if __name__ == "__main__":
    generator = DataTypeGenerator("../../include/nh/stock/NhStockUserApiDataType.h", "nh")
    generator.run()
