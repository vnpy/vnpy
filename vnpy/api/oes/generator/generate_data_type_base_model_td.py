""""""

TYPE_CPP2PY = {
    "int": "int",
    "char": "char",
    "double": "double",
    "short": "int",
}


class DataTypeGenerator:
    """DataType生成器"""

    def __init__(self, filename: str, prefix: str):
        """Constructor"""
        self.filename = filename
        self.prefix = prefix
        self.enums = {}
        self.enums_contens = {}
        self.structs_ = {}
        self.structs_name_ = None
        self.start = False

    def run(self):
        """主函数"""
        self.f_cpp = open(self.filename, "r", encoding="UTF-8")
        self.f_define = open(f"{self.prefix}_constant_base_model_td.py", "w")
        self.f_typedef = open(f"{self.prefix}_typedef_base_model_td.py", "w")
        self.f_struct = open(f"{self.prefix}_struct_base_model_td.py", "w")

        for line in self.f_cpp:
            self.process_line(line)

        for k, v in self.enums.items():
            new_line = f"{k} = {v}\n"
            self.f_typedef.write(new_line)

        self.f_cpp.close()
        self.f_define.close()
        self.f_typedef.close()
        self.f_struct.close()

        print("DataType生成完毕")

    def process_line(self, line: str):
        """处理每行"""
        line = line.replace("\n", "")
        line = line.replace(";", "")

        if line.startswith("#define") and "\\"not in line:
            self.process_define(line)
        elif line.startswith("#define") and "\\" in line:
            self.process_struct_(line)
        elif line.startswith("typedef enum"):
            self.process_typedef_enum(line)
        elif "=" in line and "OES" in line and "=>" not in line:
            self.process_enum_content(line)
        elif "\\" in line and "*/" not in line and "(" not in line:
            self.process_struct_content(line)
        elif line.startswith("typedef struct"):
            self.process_struct(line)
        else:
            print(line)

    def process_struct_content(self, line: str):
        """"""
        line = line.replace("\\", "")
        words = line.split(" ")
        words = [word for word in words if word]
        if not words:
            return

        if len(words) == 2:
            return
            # print(words)

    def process_enum_content_(self, line: str):
        """"""
        if "/**" in line:
            line = line.split("/**")[0]

        line = line.replace(",", "")
        words = line.split(" ")
        words = [word for word in words if word]
        if len(words) == 3:
            name = words[0]
            value = words[-1]

            new_line = f"{name} = {value}\n"
            self.f_define.write(new_line)
        else:
            number = int(words[-1].replace(")", ""))

            value = pow(2, number)
            name = words[0]
            new_line = f"{name} = {value}\n"
            self.f_define.write(new_line)

    def process_struct_(self, line: str):
        """"""
        words = line.split(" ")
        words = [word for word in words if word]
        name = words[1]
        self.structs_name_ = name
        self.start = True

    def process_define(self, line: str):
        """处理常量定义"""
        words = line.split(" ")
        words = [word for word in words if word]
        if len(words) < 3:
            return

        name = words[1]
        value = words[2]

        if "(" in value:
            value = value.replace("(", "")
            value = value.replace(")", "")

        if name == "OES_MAX_BS_PRICE":
            value = 100000000

        new_line = f"{name} = {value}\n"
        self.f_define.write(new_line)

    def process_typedef_enum(self, line: str):
        """处理类型定义"""
        words = line.split(" ")
        words = [word for word in words if word != " "]
        name = words[-2]
        name_ = name.replace("_eOes", "eOes")
        short_name = f"{name_}T"
        self.enums[short_name] = name

        typedef = "enum"

        new_line = f"{name} = \"{typedef}\"\n"
        self.f_typedef.write(new_line)


if __name__ == "__main__":
    generator = DataTypeGenerator("../include/oes/oes_base_model.h", "ctp")
    generator.run()
