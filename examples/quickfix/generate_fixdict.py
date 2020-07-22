""""""
import importlib

class StructGenerator:
    """Struct生成器"""

    def __init__(self, filename: str, prefix: str):
        """Constructor"""
        self.filename = filename
        self.prefix = prefix
        self.start_deal = False
        self.check_value = False
        self.first_line = True

        self.structs = {}

    def load_struct(self):
        """加载Struct"""
        module_name = f"{self.prefix}_dict"
        module = importlib.import_module(module_name)

        for name in dir(module):
            if "__" not in name:
                self.structs[name] = getattr(module, name)

    def run(self):
        """运行生成"""
        self.f_xml = open(self.filename, "r")
        self.f_struct = open(f"{self.prefix}_dict.py", "w")

        for line in self.f_xml:
            self.process_line(line)

        self.f_xml.close()
        self.f_struct.close()
        self.load_struct()

        print("Struct生成成功")
        print(self.structs)

    def process_line(self, line: str):
        """处理每行"""
        if "<components />"in line:
            self.start_deal = True

        if not self.start_deal:
            return
        line = line.replace("\n", "")
        line = line.replace("</", "")
        line = line.replace("/>", "")
        line = line.replace(">", "")
        line = line.replace("<", "")

        words = line.split(" ")
        words = [word for word in words if word]

        if len(words) == 4:
            number = eval(words[1].split("=")[1])
            name = eval(words[2].split("=")[1])
            field = f"no_{number}"
            end = "{"
            new_line = f"{field} = {end}\n"
            if self.first_line:
                self.first_line = False
            else:
                self.f_struct.write("}\n")
            self.f_struct.write(new_line)

            name_line = f"    \"name\": \"{name}\",\n"
            self.f_struct.write(name_line)

            if name == "EncodedListStatusText":
                self.f_struct.write("}\n")
        elif len(words) == 3:
            k = eval(words[1].split("=")[1])
            v = eval(words[2].split("=")[1])
            new_line = f"    \"{k}\": \"{v}\",\n"
            self.f_struct.write(new_line)


if __name__ == "__main__":
    generator = StructGenerator("./FIX42.xml", "fix")
    generator.run()
