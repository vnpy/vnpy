""""""
import importlib


class StructGenerator:
    """Struct生成器"""
    enum_no = 0

    def __init__(self, filename: str, prefix: str):
        """Constructor"""
        self.filename = filename
        self.prefix = prefix
        self.typedefs = {}

        self.load_constant()
        self.structs_names = {}

    def load_constant(self):
        """"""
        module_name = f"{self.prefix}_typedef"
        module = importlib.import_module(module_name)

        for name in dir(module):
            if "__" not in name:
                self.typedefs[name] = getattr(module, name)

        self.typedefs["char"] = "char"
        self.typedefs["int32_t"] = "int32_t"

    def run(self):
        """运行生成"""
        self.f_cpp = open(self.filename, "r")
        self.f_struct = open(f"{self.prefix}_struct.py", "w")
        self.f_define = open(f"{self.prefix}_constant_enum.py", "w")
        self.f_typedef = open(f"{self.prefix}_typedef_enum.py", "w")

        for line in self.f_cpp:
            self.process_line(line)

        self.process_names()

        self.f_cpp.close()
        self.f_struct.close()
        self.f_define.close()
        self.f_typedef.close()

        print("Struct生成成功")

    def process_names(self):
        """"""
        for k, v in self.structs_names.items():
            new_line = f"{k} = {v}\n"
            self.f_struct.write(new_line)

    def process_line(self, line: str):
        """处理每行"""
        line = line.replace(";", "")
        line = line.replace("\n", "")

        if line.startswith("typedef struct"):
            self.process_declare(line)
        elif "enum" in line:
            self.process_enum_name(line)
        elif line.startswith("{"):
            self.process_start(line)
        elif line.startswith("}"):
            self.process_end(line)
        elif "///" not in line and "#" not in line:
            self.process_member(line)
    
    def process_enum_name(self, line: str):
        """"""
        words = line.split(" ")
        name = words[-1]

        new_line = f"{name} = \"enum\"\n"
        self.f_typedef.write(new_line)

        end = "{"
        new_line_ = f"{name} = {end}\n"
        self.f_struct.write(new_line_)

        abbre_name = "E_EXCHANGE_TYPE"
        self.structs_names[abbre_name] = name

    def process_declare(self, line: str):
        """处理声明"""
        words = line.split(" ")
        name = words[-1]
        end = "{"

        new_line = f"{name} = {end}\n"
        self.f_struct.write(new_line)

        if name == "tagUftReqQueryOrderField":
            abbre_name = "QryInvestorPositionField"
        else:

            abbre_name = name.replace("tagUft", "CUft")

        self.structs_names[abbre_name] = name

    def process_start(self, line: str):
        """处理开始"""
        pass

    def process_end(self, line: str):
        """处理结束"""
        new_line = "}\n\n"
        self.f_struct.write(new_line)

    def process_enum(self, line: str):
        """"""
        line = line.replace("\t", "")
        line = line.replace(",", "")
        words = line.split(" ")
        words = [word for word in words if word]
        if "=" in words:
            number = words[-1]
            name = words[0]
            self.enum_no = int(number)

            new_line = f"{name} = {number}\n"
            self.f_define.write(new_line)

            new_line_ = f"    \"{name}\": \"int\",\n"
            self.f_struct.write(new_line_)
        else:
            self.enum_no += 1
            name = words[0]
            number = self.enum_no

            new_line = f"{name} = {number}\n"

            self.f_define.write(new_line)
            new_line_ = f"    \"{name}\": \"int\",\n"
            self.f_struct.write(new_line_)

    def process_member(self, line: str):
        """处理成员"""
        if "//" in line:
            line = line.split("//")[0]

        if "," in line:
            self.process_enum(line)
        else:
            words = line.split("\t")

            words = [word for word in words if word]

            if len(words) == 1:
                words = words[0].split(" ")
                words = [word for word in words if word != ""]

                if not words:
                    return

                # print(words)

                py_type = self.typedefs.get(words[0], "dict")
                name = words[1]

                name = name.strip()
                if "[" in name:
                    name = name.split("[")[0]
                    py_type = "string"
                new_line = f"    \"{name}\": \"{py_type}\",\n"
                self.f_struct.write(new_line)

            elif len(words) == 2:

                py_type = self.typedefs.get(words[0], "dict")
                name = words[1]

                name = name.strip()
                if "[" in name:
                    name = name.split("[")[0]
                    py_type = "string"
                new_line = f"    \"{name}\": \"{py_type}\",\n"
                self.f_struct.write(new_line)


if __name__ == "__main__":
    generator = StructGenerator("../include/nst/uft4_UserApiStruct.h", "nst")
    generator.run()
