""""""

TYPE_CPP2PY = {
    "int": "int",
    "char": "char",
    "double": "double",
    "short": "int",
}


class DataTypeGenerator:
    """DataType生成器"""

    def __init__(self, filename: str, prefix: str, name: str):
        """Constructor"""
        self.filename = filename
        self.prefix = prefix
        self.name = name

    def run(self):
        """主函数"""
        self.f_cpp = open(self.filename, "r")
        if self.name == "TradeDefine":
            self.f_define = open(f"{self.prefix}_constant.py", "w")
        elif self.name == "DataType":
            self.f_typedef = open(f"{self.prefix}_typedef.py", "w")
        elif self.name == "Error":
            self.f_error_define = open(f"{self.prefix}_error_constant.py", "w")

        for line in self.f_cpp:
            self.process_line(line)

        self.f_cpp.close()

        if self.name == "TradeDefine":
            self.f_define.close()
        elif self.name == "DataType":
            self.f_typedef.close()
        elif self.name == "Error":
            self.f_error_define.close()

        print("DataType生成完毕")

    def process_line(self, line: str):
        """处理每行"""
        line = line.replace("\n", "")
        line = line.replace(";", "")

        if line.startswith("#define") and "//" in line:
            self.process_define(line)
        elif line.startswith("typedef") and "//" not in line:
            self.process_typedef(line)

    def process_define(self, line: str):
        """处理常量定义"""
        line = line.replace("\t", " ")
        content = line.split("#define")[1]
        content = content.split("//")[0]

        words = content.split(" ")
        words = [word for word in words if word]

        name = words[0]
        value = words[-1]

        new_line = f"{name} = {value}\n"

        if self.name == "TradeDefine":
            self.f_define.write(new_line)
        else:
            self.f_error_define.write(new_line)

    def process_typedef(self, line: str):
        """处理类型定义"""
        words = line.split(" ")
        words = [word for word in words if word]

        if len(words) == 4 and words[-1] == "[7]":
            name = words[-2]
            py_type = words[-3]
        else:
            name = words[-1]
            py_type = words[-2]

        if "[" in name:
            name = name.split("[")[0]
            py_type = "string"

        new_line = f"{name} = \"{py_type}\"\n"
        self.f_typedef.write(new_line)


if __name__ == "__main__":
    TradeDefine_generator = DataTypeGenerator("../include/ksgold/KSGoldTradeDefine.h", "ksgold", "TradeDefine")
    TradeDefine_generator.run()

    DataType_generator = DataTypeGenerator("../include/ksgold/KSGoldUserApiDataTypeEx.h", "ksgold", "DataType")
    DataType_generator.run()

    Error_generator = DataTypeGenerator("../include/ksgold/KSGoldError.h", "ksgold", "Error")
    Error_generator.run()
