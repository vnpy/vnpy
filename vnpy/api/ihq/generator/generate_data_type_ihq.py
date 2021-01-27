""""""

TYPE_CPP2PY = {
    "int": "int",
    "char": "char",
    "double": "double",
    "short": "int",
    "enum": "enum",
    "uint8_t": "int"
}


class DataTypeGenerator:
    """DataType生成器"""
    enum_no = 0

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
            self.process_line(line)

        self.f_cpp.close()
        self.f_define.close()
        self.f_typedef.close()

        print(f"{self.prefix}  DataType生成完毕")

    def process_line(self, line: str):
        """处理每行"""
        line = line.replace("\n", "")
        line = line.replace(";", "")
        line = line.replace("		", "")

        if line.startswith("#define"):
            self.process_define(line)
        elif line.startswith("typedef"):
            self.process_typedef(line)
        elif "///<" in line or "}" in line:
            self.process_enum_number(line)

    def process_enum_number(self, line: str):
        """"""
        line = line.replace("\t", "")
        line = line.replace(",", "")
        words = line.split("///<")[0]
        words = words.split(" ")
        words = [word for word in words if word]

        if "}" in words[0]:
            self.enum_no = -1
        else:

            if "=" in words:
                number = words[-1]
                self.enum_no = int(number)
            else:
                self.enum_no += 1
                number = self.enum_no

            name = words[0]
            value = number
            type_ = "int"

            new_line_ = f"{name} = \"{type_}\"\n"
            self.f_typedef.write(new_line_)

            new_line = f"{name} = {value}\n"
            self.f_define.write(new_line)

    def process_define(self, line: str):
        """处理常量定义"""
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
        words = [word for word in words if word != " "]

        name = words[2]
        typedef = TYPE_CPP2PY[words[1]]

        if typedef == "char":
            if "[" in name:
                typedef = "string"
                name = name[:name.index("[")]

        new_line = f"{name} = \"{typedef}\"\n"
        self.f_typedef.write(new_line)


if __name__ == "__main__":
    generator = DataTypeGenerator("../include/ihq/IStoneApiDataType.h", "ihq")
    generator.run()
