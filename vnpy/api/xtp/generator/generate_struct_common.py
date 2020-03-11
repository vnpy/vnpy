""""""
from typing import Dict, List
import os

type_dict = {
    'uint64_t': 'int',
    'uint32_t': 'int',
    'int64_t': 'int',
    'int32_t': 'int',
    'char': 'string',
    'double': 'float',
    "XTPRI": "enum"
}


class StructGenerator:
    """Struct生成器"""

    def __init__(self, filename: str):
        """Constructor"""
        self.filename: str = filename
        self.full_name: List[str] = []
        self.short_name: List[str] = []
        self.SHORT2FULL: Dict[str, str] = {}

    def run(self):
        """运行生成"""
        self.f_cpp = open(self.filename, "r", encoding="UTF-8")
        self.f_struct = open("test_xtp_struct_common.py", "w", encoding="UTF-8")

        for line in self.f_cpp:
            self.process_line(line)

        self.genreator_dict()

        self.f_cpp.close()
        self.f_struct.close()
        # 二次修改
        self.fix_bug()

    def fix_bug(self):
        r_struct = open("test_xtp_struct_common.py", "r", encoding="UTF-8")
        w_sturct = open("xtp_struct_common.py", "w", encoding="UTF-8")

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
        w_sturct.close()
        os.remove("test_xtp_struct_common.py")
        print("Struct生成成功")

    def genreator_dict(self):
        """"""
        self.SHORT2FULL = dict(zip(self.short_name, self.full_name))
        for key, value in self.SHORT2FULL.items():
            new_line = f"{key} = {value}"
            self.f_struct.write(new_line)

    def process_line(self, line: str):
        """处理每行"""
        line = line.replace(";", "")
        line = line.replace("\n", "")

        if line.startswith("////") or line.startswith("///@"):
            pass

        elif "struct" in line:
            content = line.split()
            name = content[2].replace("\n", "")
            name = name.replace("\t", "")
            end = "{"
            new_line = f"{name} = {end}\n"
            self.f_struct.write(new_line)

            self.full_name.append(name)

        elif line.startswith("{"):
            pass

        elif line.startswith("}"):
            words = line.split(" ")
            new_line = "}\n\n"
            self.f_struct.write(new_line)

            self.short_name.append(words[-1])

        elif "\t" in line and "///" not in line:
            words = line.split("\t")
            words = [word for word in words if word]
            py_type = type_dict[words[0]]
            name = words[1]

            new_line = f"    \"{name}\": \"{py_type}\",\n"
            self.f_struct.write(new_line)


if __name__ == "__main__":
    generator = StructGenerator("../include/xtp/xtp_api_struct_common.h")
    generator.run()
