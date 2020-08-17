""""""
import importlib


class CommenTypeGenerator:
    """commdef生成器"""

    def __init__(self, filename: str, prefix: str, name: str) -> None:
        """Constructor"""
        self.filename: str = filename
        self.prefix: str = prefix
        self.name: str = name
        self.typedefs = {}

    def load_constant(self):
        """"""
        module_name = f"{self.prefix}_{self.name}_commen_typedef"
        module = importlib.import_module(module_name)

        for name in dir(module):
            if "__" not in name:
                self.typedefs[name] = getattr(module, name)

    def run(self) -> None:
        """主函数"""
        self.f_cpp = open(self.filename, "r", encoding="UTF-8")
        self.f_define = open(
            f"{self.prefix}_{self.name}_commen_constant.py", "w", encoding="UTF-8")
        self.f_typedef = open(
            f"{self.prefix}_{self.name}_commen_typedef.py", "w", encoding="UTF-8")
        self.f_struct = open(
            f"{self.prefix}_{self.name}_commen_struct.py", "w", encoding="UTF-8")

        self.add_supplement()

        for line in self.f_cpp:
            self.process_line(line)

        self.f_cpp.close()
        self.f_define.close()
        self.f_typedef.close()

        self.load_constant()
        self.process_struct()

        self.f_cpp.close()
        self.f_struct.close()

        print(f"{self.name}_CommenType生成完毕")

    def process_struct(self) -> None:
        f_cpp_struct = open(self.filename, "r", encoding="UTF-8")
        for line in f_cpp_struct:
            line = line.replace(";", "")
            line = line.replace("\n", "")

            if "struct" in line:
                self.process_declare(line)
            elif "{" in line:
                self.process_start(line)
            elif line.startswith("}") and self.name == "md":
                self.process_end(line)
            elif line.startswith("    }") and self.name == "td":
                self.process_end(line)
            elif "///<" in line:
                self.process_member(line)

        f_cpp_struct.close()

    def process_declare(self, line: str):
        """处理声明"""
        words = line.split(" ")
        print(words)
        name = words[-1]
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

    def process_member(self, line: str) -> None:
        sector = line.split("///<")[0]
        words = sector.split("\t")
        words = [word for word in words if word != ""]
        
        
        if len(words) == 1:
            words = words[0].split(" ")
            words = [word for word in words if word != ""]
       
        name = words[1].strip()
        print(name)
        py_type = self.typedefs.get(words[0].strip(), "dict") #找不到就写dict
        new_line = f"    \"{name}\": \"{py_type}\",\n"
        self.f_struct.write(new_line)
        

    def process_line(self, line: str) -> None:
        """处理每行"""
        line = line.replace("\n", "")
        line = line.replace(";", "")

        # MD
        if self.name == "md":
            if line.startswith("typedef char"):
                self.process_char_md(line)
            elif line.startswith("const"):
                self.process_const_md(line)
        # TD
        elif self.name == "td":
            if line.startswith("    typedef char"):
                self.process_char_td(line)
            elif line.startswith("    const"):
                self.process_const_td(line)

    def process_char_md(self, line: str) -> None:
        """处理类型定义"""
        if "\t\t\t\t" in line:
            name = line.split("\t\t\t\t")[1]
            new_line = f"{name} = \"char\"\n"
        else:
            name = line.split("\t")[1].split("[")[0]
            new_line = f"{name} = \"string\"\n"

        self.f_typedef.write(new_line)

    def process_char_td(self, line: str) -> None:
        words = line.split(" ")
        words = [word for word in words if word != ""]

        name = words[-1]

        if "[" in name:
            name = name.split("[")[0]
            new_line = f"{name} = \"string\"\n"
        else:
            new_line = f"{name} = \"char\"\n"

        self.f_typedef.write(new_line)

    def process_const_md(self, line: str) -> None:
        """"""
        sectors = line.split("=")
        value = sectors[1].replace("\'", "\"").strip()

        words = sectors[0].split("\t")
        words = [word for word in words if word != ""]
        name = words[1].strip()

        new_line = f"{name} = {value}\n"
        self.f_define.write(new_line)

    def process_const_td(self, line: str):
        sectors = line.split("=")
        value = sectors[1].replace("\'", "\"").strip()

        words = sectors[0].split(" ")
        words = [word for word in words if word != ""]

        name = words[-1].strip()

        new_line = f"{name} = {value}\n"
        self.f_define.write(new_line)

    def add_supplement(self):
        self.f_typedef.write("TAPIINT32 = \"int\"\n")
        self.f_typedef.write("TAPIUINT32 = \"unsigned int\"\n")
        self.f_typedef.write("TAPIINT64 = \"long long\"\n")
        self.f_typedef.write("TAPIUINT64 = \"unsigned long long\"\n")
        self.f_typedef.write("TAPIUINT16 = \"unsigned short\"\n")
        self.f_typedef.write("TAPIUINT8 = \"unsigned char\"\n")
        self.f_typedef.write("TAPIREAL64 = \"double\"\n")

        if self.name == "md":
            self.f_typedef.write("TAPIYNFLAG = \"char\"\n")
            self.f_typedef.write("TAPILOGLEVEL = \"char\"\n")
            self.f_typedef.write("TAPICommodityType = \"char\"\n")
            self.f_typedef.write("TAPICallOrPutFlagType = \"char\"\n")

            self.f_typedef.write("TAPIMACTYPE = \"string\"\n")
            self.f_typedef.write("TAPISecondSerialIDType = \"string\"\n")
            self.f_typedef.write("TAPIClientIDType = \"string\"\n")

        elif self.name == "td":
            self.f_typedef.write("TAPIYNFLAG = \"char\"\n")
            self.f_typedef.write("TAPIPasswordType = \"char\"\n")
            self.f_typedef.write("TAPILOGLEVEL = \"char\"\n")
            self.f_typedef.write("TAPIOptionType = \"char\"\n")
            self.f_typedef.write("TAPICommodityType = \"char\"\n")
            self.f_typedef.write("TAPICallOrPutFlagType = \"char\"\n")


if __name__ == "__main__":
    md_generator = CommenTypeGenerator(
        "../include/es/TapAPICommDef.h", "tap", "md")
    md_generator.run()

    td_generator = CommenTypeGenerator(
        "../include/es/EsTradeAPIDataType.h", "tap", "td")
    td_generator.run()
