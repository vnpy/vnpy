""""""


class ErrorTypeGenerator:
    """DataType生成器"""

    def __init__(self, filename: str, prefix: str, name: str) -> None:
        """Constructor"""
        self.filename: str = filename
        self.prefix: str = prefix
        self.name: str = name

    def run(self) -> None:
        """主函数"""
        self.f_cpp = open(self.filename, "r", encoding="UTF-8")
        self.f_define = open(f"{self.prefix}_{self.name}_error_constant.py", "w", encoding="UTF-8")

        for line in self.f_cpp:
            self.process_line(line)

        self.f_cpp.close()
        self.f_define.close()

        print(f"{self.name}_ErrorType生成完毕")

    def process_line(self, line: str) -> None:
        """处理每行"""
        line = line.replace("\n", "")
        line = line.replace(";", "")

        # MD
        if self.name == "md":
            if line.startswith("const int"):
                self.process_int(line)
        # TD
        elif self.name == "td":
            if line.startswith("    const int"):
                self.process_int(line)

    def process_int(self, line: str) -> None:
        """处理类型定义"""
        sectors = line.split("=")
        value = sectors[1].strip()

        words = sectors[0].split(" ")
        words = [word for word in words if word != ""]
        name = words[-1].strip()
        new_line = f"{name} = {value}\n"
        self.f_define.write(new_line)


if __name__ == "__main__":
    md_generator = ErrorTypeGenerator("../include/tap/TapAPIError.h", "tap", "md")
    md_generator.run()

    td_generator = ErrorTypeGenerator(
        "../include/es/EsTradeAPIError.h", "tap", "td")
    td_generator.run()
