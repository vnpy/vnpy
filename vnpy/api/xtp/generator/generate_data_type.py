""""""

TYPE_CPP2PY = {
    "uint8_t": "int",    # 3
    "char": "string",       # 2
    "double": "double",   # 1
    "short": "int",
    "XTP_EXCHANGE_TYPE": "enum"
}


class DataTypeGenerator:
    """DataType生成器"""

    def __init__(self, filename: str, prefix: str):
        """Constructor"""
        self.filename: str = filename
        self.prefix: str = prefix
        self.count: int = 0

    def run(self):
        """主函数"""
        self.f_cpp = open(self.filename, "r", encoding="UTF-8")
        self.f_define = open(f"{self.prefix}_constant.py", "w", encoding="UTF-8")
        self.f_typedef = open(f"{self.prefix}_typedef.py", "w", encoding="UTF-8")
        self.f_struct = open(f"{self.prefix}_enum.py", "w", encoding="UTF-8")

        for line in self.f_cpp:
            self.process_line(line)

        self.f_cpp.close()
        self.f_define.close()
        self.f_typedef.close()

        print("DataType生成完毕")

    def process_line(self, line: str):
        """处理每行"""
        line = line.replace("\n", "")
        line = line.replace(";", "")
        line = line.replace("\t", "    ")

        if line[:3] == "///":
            pass
        # elif "enum" in line:
        #     self.process_enum(line)
        elif line.startswith("#define"):
            self.process_define(line)
        elif line.startswith("typedef char"):
            self.process_typedef(line)
        elif line.startswith("typedef uint8_t"):
            name = line.split(" ")[2]
            typedef = "int"
            new_line = f"{name} = \"{typedef}\"\n"
            self.f_typedef.write(new_line)

        elif line.startswith("typedef enum"):
            self.process_enum(line)
        elif line.startswith("}"):
            new_line = "}\n\n"
            self.f_struct.write(new_line)
        # 处理枚举值表头
        # elif line.startswith("typedef enum"):
        #     print(line)

        # 处理枚举值内容
        elif "//<" in line:
            if "=" in line:
                name = line.split("=")[0].strip()
            elif "," in line:
                name = line.split(",")[0].strip()
            else:
                name = line.split("///")[0].strip()

            py_type = "int"
            new_line = f"    \"{name}\": \"{py_type}\",\n"
            self.f_struct.write(new_line)

    def process_comment(self, line: str):
        """处理注释"""
        line.replace("/", "#")

    def process_enum(self, line: str):
        """处理枚举值"""
        content = line.replace("\n", " ")
        content = content.replace("\r", " ")
        content = content.split(" ")
        type_ = "enum"
        name = content[2]

        new_line = f"{name} = \"{type_}\"\n"
        self.f_typedef.write(new_line)

        end = "{"
        struct_line = f"{name} = {end}\n"
        self.f_struct.write(struct_line)

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
        word = line.split(" ")[2]
        name = word.split("[")[0]
        typedef = "string"

        # words = [word for word in words if word != " "]

        # name = words[2]
        # typedef = TYPE_CPP2PY[words[1]]

        # if typedef == "char":
        #     if "[" in name:
        #         typedef = "string"
        #         name = name[:name.index("[")]
        #     else:
        #         typedef = "char"

        new_line = f"{name} = \"{typedef}\"\n"
        self.f_typedef.write(new_line)


if __name__ == "__main__":
    generator = DataTypeGenerator("../include/xtp/xtp_api_data_type.h", "xtp")
    generator.run()
