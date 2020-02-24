""""""
import importlib
from typing import Dict, List
import os

type_dict = {
    "uint8_t": "int",
    'uint64_t': 'int',
    'uint32_t': 'int',
    'int64_t': 'int',
    'int32_t': 'int',
    'char': 'string',
    'double': 'float',
    "bool": "bool",
    # "XTPRI": "enum"
}

class StructGenerator:
    """Struct生成器"""

    def __init__(self, filename: str, prefix: str):
        """Constructor"""
        self.filename = filename
        self.prefix = prefix
        self.typedefs = type_dict
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
        self.f_cpp = open(self.filename, "r", encoding="UTF-8")
        self.f_struct = open("test_xtp_struct_quote.py", "w", encoding="UTF-8")

        for line in self.f_cpp:
            self.process_line(line)

        self.f_cpp.close()
        self.f_struct.close()

        # print("Struct TEST生成成功")

        # 二次修改
        self.fix_bug()

    def fix_bug(self):
        r_struct = open("test_xtp_struct_quote.py", "r", encoding="UTF-8")
        short2full = open("short2full.py", "r", encoding="UTF-8")
        w_sturct = open("xtp_struct_quote.py", "w", encoding="UTF-8")

        for line in r_struct:
            if "[" in line:
                words = line.split(":")
                py_type = eval(words[-1].split(",")[0])
                name = eval(words[0].split(",")[0]).split("[")[0]
                new_line = f"    \"{name}\": \"{py_type}\",\n"
                w_sturct.write(new_line)
            else:
                w_sturct.write(line)

        r_struct.close()

        for l in short2full:
            w_sturct.write(l)

        short2full.close()
        w_sturct.close()
        os.remove("test_xtp_struct_quote.py")
        print("Struct生成成功")

    def process_line(self, line: str):
        """处理每行"""
        line = line.replace(";", "")
        line = line.replace("\n", "")

        if "///<" in line:
            line = line.split("///<")[0]    
            line = line.strip()
            words = line.split("\t")            
            words = [word for word in words if word]

            if len(words) > 1:
                type_ = words[0]
                py_type = self.typedefs[type_]
                name = words[1].strip()
        
            else:
                words = words[0].split()  
                type_ = words[0]
                py_type = self.typedefs[type_]
                name = words[1].strip()

            new_line = f"    \"{name}\": \"{py_type}\",\n"
            self.f_struct.write(new_line)


        elif (line.startswith("  ")  or line.startswith("\t")) and \
            (line.endswith("{") or line.endswith("}")):
            pass

        elif line.startswith("            ") or line.startswith("\t\t") or line.startswith("        "):
            pass
        
        elif line.startswith("typedef struct"):
            content = line.split()

            name = content[2].replace("\n", "")
            name = name.replace("\t", "")
            end = "{"

            new_line = f"{name} = {end}\n"
            self.f_struct.write(new_line)           
        
        
        # 普通部分
        elif line.startswith("struct") or line.startswith("enum"):
            content = line.split()
            name = content[1].replace("\n", "")
            name = name.replace("\t", "")
            end = "{"
            
            new_line = f"{name} = {end}\n"
            self.f_struct.write(new_line)
            # print("full name--", name)
            # self.full_name.append(name)

        elif line.startswith("{"):
            pass

        elif line.startswith("}"):
            new_line = "}\n\n"
            self.f_struct.write(new_line)
            # words = line.split(" ")
            # print("short---",words)
            # if len(words) == 2:
            #     self.short_name.append(words[-1])
            # else:
            #     self.short_name.append("")


        # 内容部分
        elif ("\t" in line or "  " in line) and "//" not in line:
            line = line.strip()
            words = line.split("\t")            
            words = [word for word in words if word]

            if len(words) > 1:
                type_ = words[0]
                py_type = self.typedefs.get(type_, "enum")
                name = words[1].strip()
        
            else:
                words = words[0].split()  
                type_ = words[0]
                py_type = self.typedefs.get(type_, "enum")
                name = words[1].strip()

            if name.startswith("unknow"):
                return

            new_line = f"    \"{name}\": \"{py_type}\",\n"
            self.f_struct.write(new_line)

if __name__ == "__main__":
    generator = StructGenerator("../include/xtp/xquote_api_struct.h", "xtp")
    generator.run()


