""""""
import importlib


class Generator:
    """DataType生成器"""

    def __init__(self, filename: str, prefix: str):
        """Constructor"""
        self.filename = filename
        self.prefix = prefix
        self.check_struct = False
        self.check_extra = False
        self.structs_names = {}
        self.struct_start = False
        self.extra_start = False
        self.enums = {}
        self.process_special = False
        self.structs = {}
        self.subs = {}
        self.final = {}
        self.final_2 = {}

    def run(self):
        """主函数"""
        self.f_cpp = open(self.filename, "r", encoding="UTF-8")
        self.f_define = open(f"{self.prefix}_constant_packets_td.py", "w")
        self.f_typedef = open(f"{self.prefix}_typedef_packets_td.py", "w")
        self.f_struct = open(f"{self.prefix}_struct_packets_td.py", "w")

        for line in self.f_cpp:
            self.process_line(line)

        self.process_enum_short_name()

        self.f_cpp.close()
        self.f_define.close()
        self.f_typedef.close()
        self.f_struct.write("}\n")
        self.f_struct.close()

        # self.generate_struct()

        print("packets 解析完毕")

    def generate_struct(self):
        self.load_struct()
        self.deal_struct()
        self.deal_struct_2()

    def deal_struct_2(self):
        for struct_name, fields in self.final.items():
            if not fields:
                continue

            d = {}

            for name, type_ in fields.items():
                if type_ != "dict":
                    d[name] = type_
                else:
                    value = self.subs[name]
                    d.update(value)

            self.final_2[struct_name] = d
            print(struct_name, ":", d)

    def deal_struct(self):
        for struct_name, fields in self.structs.items():
            if not fields:
                continue

            d = {}

            for name, type_ in fields.items():
                if type_ != "dict":
                    d[name] = type_
                else:
                    value = self.subs[name]
                    d.update(value)

            self.final[struct_name] = d

    def load_struct(self):
        """加载Struct"""
        module_name = "oes_struct_packets_td"
        module = importlib.import_module(module_name)

        for name in dir(module):
            if "__" not in name:
                self.structs[name] = getattr(module, name)

    def process_enum_short_name(self):
        """"""
        for k, v in self.enums.items():
            new_line = f"{k} = {v}\n"
            self.f_typedef.write(new_line)

    def process_line(self, line: str):
        """处理每行"""
        line = line.replace("\n", "")
        line = line.replace(";", "")

        if self.check_struct:
            self.process_struct_end(line)

        elif line.startswith("#define") and "\\"not in line:
            self.process_define(line)
        elif line.startswith("typedef enum"):
            self.process_typedef_enum(line)
        elif "=" in line and "OES" in line and "=>" not in line:
            self.process_enum_content(line)
        elif line.startswith("typedef struct"):
            self.process_struct_start(line)

    def process_enum_content(self, line: str):
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

    def process_extra_end(self, line: str):
        """"""
        words = line.split(" ")
        words = [word for word in words if word]

        if line.startswith("#define"):
            self.check_extra = False

    def process_struct_end(self, line: str):
        """"""
        if "*" in line:
            return
        words = line.split(" ")
        words = [word for word in words if word]

        if len(words) == 1 and "}" not in words:
            name = words[0]
            type_ = "dict"

            if name == "#endif":
                return
            new_line = f"    \"{name}\" : \"{type_}\",\n"
            self.f_struct.write(new_line)
        elif len(words) == 2 and "}" not in words and "{" not in words:
            type_ = words[0]
            name = words[1]

            if "[" in name:
                name = name.split("[")[0]
                if type_ == "char":
                    type_ = "string"

            if name == "_OES_EXPORT_LATENCY_STATS":
                return

            if "Oes" in type_:
                type_ = "dict"

            new_line = f"    \"{name}\": \"{type_}\",\n"
            self.f_struct.write(new_line)
        if "}" in line:
            self.check_struct = False

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

    def process_struct_start(self, line: str):
        """"""
        self.check_struct = True
        words = line.split(" ")
        words = [word for word in words if word != " "]
        name = words[-2]
        name_ = name.replace("_", "")
        short_name = f"{name_}T"
        self.structs_names[short_name] = name

        end = "{"
        new_line = f"{short_name} = {end}\n"

        if not self.struct_start:

            self.f_struct.write(new_line)

            self.struct_start = True
        else:
            new_line_ = "}\n"
            self.f_struct.write(new_line_)
            self.f_struct.write(new_line)

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


if __name__ == "__main__":
    generator = Generator("../include_for_generator/oes/oes_packets.h", "oes")
    generator.run()
