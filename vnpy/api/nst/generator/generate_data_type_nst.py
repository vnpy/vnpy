""""""

TYPE_CPP2PY = {
    "int": "int",
    "char": "char",
    "double": "double",
    "short": "int",
}


class DataTypeGenerator:
    """DataType生成器"""
    count = 0
    count_ = 0

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

        if line.startswith("#define"):
            self.process_define(line)
        elif line.startswith("typedef"):
            self.process_typedef(line)

    def process_define(self, line: str):
        """处理常量定义"""
        line = line.replace("\t", "")
        line = line.replace("	", " ")
        line = line.split("//")[0]
        words = line.split(" ")
        words = [word for word in words if word]

        if len(words) < 3:

            if "UFT" in words[0]:
                name = words[0].split("#define")[-1]
                value = words[-1]

                new_line = f"{name} = {value}\n"
                self.f_define.write(new_line)

            else:
                content = words[1]
                if "'" in content:
                    name = content.split("'")[0]
                    value = content.split("'")[1]
                    new_line = f"{name} = \'{value}\'\n"
                    self.f_define.write(new_line)
                elif "-" in content:
                    name = content.split("-")[0]
                    value = content.split("-")[1]

                    new_line = f"{name} = -{value}\n"
                    self.f_define.write(new_line)
        else:
            name = words[1]
            value = words[2]

            new_line = f"{name} = {value}\n"
            self.f_define.write(new_line)

    def process_typedef(self, line: str):
        """处理类型定义"""
        line = line.replace("\t", "")
        words = line.split(" ")
        words = [word for word in words if word != ""]

        if len(words) > 3:
            type_ = f"{words[1]} {words[2]}"
            name = words[-1]

            new_line = f"{name} = \"{type_}\"\n"
            self.f_typedef.write(new_line)
        else:
            type_ = words[1]
            name = words[2]
            if "[" in name:
                type_ = "string"
                name = name[:name.index("[")]

            new_line = f"{name} = \"{type_}\"\n"
            self.f_typedef.write(new_line)


if __name__ == "__main__":
    generator = DataTypeGenerator(
        "../include/nst/uft4_UserApiDataType.h",
        "nst"
    )
    generator.run()
