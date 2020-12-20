""""""
import importlib


class ApiGenerator:
    """API生成器"""""

    def __init__(self, filename: str, prefix: str, name: str, class_name: str):
        """Constructor"""
        self.filename = filename
        self.prefix = prefix
        self.name = name
        self.class_name = class_name

        self.callbacks = {}
        self.functions = {}
        self.lines = {}

        self.structs = {}
        self.load_struct()

    def load_struct(self):
        """加载Struct"""
        module_name = f"{self.prefix}_struct"
        module = importlib.import_module(module_name)

        for name in dir(module):
            if "__" not in name:
                self.structs[name] = getattr(module, name)

        self.structs["ErrorInfo"] = {
            "err_code": "int32_t",
            "err_msg": "string"
        }

        self.structs["IpAddr"] = {
            "ip": "string",
            "port": "int"
        }

    def run(self):
        """运行生成"""
        self.f_cpp = open(self.filename, "r", encoding="UTF-8")

        for line in self.f_cpp:
            self.process_line(line)

        self.f_cpp.close()

        self.generate_header_define()
        self.generate_header_process()
        self.generate_header_on()
        self.generate_header_function()

        # self.generate_source_task()
        # self.generate_source_switch()
        self.generate_source_spi()
        self.generate_source_function()
        self.generate_source_on()
        self.generate_source_module()

        print("API生成成功")

    def process_line(self, line: str):
        """处理每行"""
        line = line.replace(";", "")
        line = line.replace("\n", "")
        line = line.replace("\t", "")
        line = line.replace("{}", "")

        if "virtual void On" in line:
            self.process_callback(line)
        elif "virtual int" in line:
            self.process_function(line)

    def process_callback(self, line: str):
        """处理回掉函数"""
        name = line[line.index("On"):line.index("(")]
        self.lines[name] = line

        d = self.generate_arg_dict(line)
        self.callbacks[name] = d

    def process_function(self, line: str):
        """处理主动函数"""
        name = line.split("(")[0].split(" ")[-1]
        # name = line[line.index("Que"):line.index("(")]

        d = self.generate_arg_dict(line)
        self.functions[name] = d

    def generate_arg_dict(self, line: str):
        """生成参数字典"""
        # print(line)
        args_str = line[line.index("(") + 1:line.index(")")]
        if not args_str:
            return {}
        args = args_str.split(",")

        d = {}
        for arg in args:
            if "=" in arg:
                arg = arg.split("=")[0]
            words = arg.split(" ")
            words = [word for word in words if word]
            d[words[-1].replace("*", "")] = words[-2].replace("*", "")
        return d

    def generate_header_define(self):
        """"""
        filename = f"{self.prefix}_{self.name}_header_define.h"
        with open(filename, "w") as f:
            for n, name in enumerate(self.callbacks.keys()):
                line = f"#define {name.upper()} {n}\n"
                f.write(line)

    def generate_header_process(self):
        """"""
        filename = f"{self.prefix}_{self.name}_header_process.h"
        with open(filename, "w") as f:
            for name in self.callbacks.keys():
                name = name.replace("On", "process")
                line = f"void {name}(Task *task);\n\n"
                f.write(line)

    def generate_header_on(self):
        """"""
        filename = f"{self.prefix}_{self.name}_header_on.h"
        with open(filename, "w") as f:
            for name, d in self.callbacks.items():
                name = name.replace("On", "on")

                args_list = []
                for name_, type_ in d.items():
                    if type_ == "int":
                        args_list.append(f"int {name_}")
                    elif type_ == "bool":
                        args_list.append("bool last")
                    elif type_ == "ErrorInfo":
                        args_list.append("const dict &error")
                    elif type_ == "int16_t":
                        args_list.append(f"int {name_}")
                    elif type_ == "int32_t":
                        args_list.append(f"int {name_}")
                    elif type_ == "int64_t":
                        args_list.append(f"int {name_}")
                    elif type_ == "char":
                        args_list.append(f"string {name_}")
                    else:
                        if "const dict &data" in args_list:
                            args_list.append("const dict &data_1")
                        else:
                            args_list.append("const dict &data")

                args_str = ", ".join(args_list)
                line = f"virtual void {name}({args_str}) {{}};\n\n"

                f.write(line)

    def generate_header_function(self):
        """"""
        filename = f"{self.prefix}_{self.name}_header_function.h"
        with open(filename, "w") as f:
            for name, d in self.functions.items():
                name = name[0].lower() + name[1:]

                args_list = []
                for name_, type_ in d.items():
                    if type_ == "int" or type_ == "int16_t" or type_ == "int32_t" or type_ == "int64_t":
                        args_list.append(f"int {name_}")
                    elif type_ == "bool":
                        args_list.append(f"bool {name_}")
                    elif type_ == "ErrorInfo":
                        args_list.append("const dict &error")
                    elif type_ == "char":
                        args_list.append(f"string {name_}")
                    else:
                        args_list.append("const dict &req")

                args_str = ", ".join(args_list)
                line = f"int {name}({args_str});\n\n"

                f.write(line)

    def generate_source_spi(self):
        """"""
        filename = f"{self.prefix}_{self.name}_source_spi.cpp"
        with open(filename, "w") as f:
            for name, d in self.callbacks.items():
                line = self.lines[name]
                on_name = name.replace("On", "on")

                f.write(line.replace("virtual void ",
                                     f"void {self.class_name}::") + "\n")
                f.write("{\n")
                f.write("\tgil_scoped_acquire acquire;\n")

                args = []

                for field, type_ in d.items():

                    if type_ == "int":
                        args.append(field)
                    elif type_ == "int64_t":
                        args.append(field)
                    elif type_ == "int16_t":
                        args.append(field)
                    elif type_ == "int32_t":
                        args.append(field)
                    elif type_ == "bool":
                        args.append(field)
                    elif type_ == "char":
                        args.append(field)
                    elif type_ == "ErrorInfo":
                        args.append("error")

                        f.write("\tdict error;\n")
                        f.write("\t{\n")

                        struct_fields = self.structs[type_]
                        for struct_field, struct_type in struct_fields.items():
                            if struct_type == "string":
                                f.write(
                                    f"\t\terror[\"{struct_field}\"] = toUtf({field}->{struct_field});\n")
                            else:
                                f.write(
                                    f"\t\terror[\"{struct_field}\"] = {field}->{struct_field};\n")

                        f.write("\t}\n")
                    else:
                        args.append("data")

                        f.write("\tdict data;\n")
                        f.write("\t{\n")

                        struct_fields = self.structs[type_]
                        for struct_field, struct_type in struct_fields.items():
                            # print(struct_type)
                            if struct_type == "char":
                                f.write(
                                    f"\t\tdata[\"{struct_field}\"] = toUtf({field}->{struct_field});\n")
                            else:
                                f.write(
                                    f"\t\tdata[\"{struct_field}\"] = {field}->{struct_field};\n")
                        f.write("\t}\n")

                args_str = ", ".join(args)
                f.write(f"\tthis->{on_name}({args_str});\n")
                f.write("};\n\n")

    def generate_source_function(self):
        """"""
        filename = f"{self.prefix}_{self.name}_source_function.cpp"
        with open(filename, "w") as f:
            for name, d in self.functions.items():
                req_name = name[0].lower() + name[1:]
                args = []
                end_args = []
                struct_type = ""

                if not d:
                    f.write(f"\tint i = this->api->getCounterType();\n")
                    f.write("\treturn i;\n")
                    f.write("};\n\n")
                else:
                    for field, type_ in d.items():

                        if type_ == "int" or type_ == "int64_t" or type_ == "int16_t" or type_ == "int32_t" or type_ == "int64_t":
                            args.append(f"int {field}")
                            end_args.append(field)
                        elif type_ == "bool":
                            args.append(f"bool {field}")
                            end_args.append(field)
                        elif type_ == "char":
                            args.append(f"string {field}")
                            end_args.append(field + ".c_str()")
                        else:
                            # struct_name = field
                            struct_type = type_
                            args.append("const dict &req")
                            end_args.append("&myreq")
                    args_str = ", ".join(args)
                    end_args_str = ", ".join(end_args)

                    f.write(
                        f"int {self.class_name}::{req_name}({args_str})\n")

                    f.write("{\n")
                    if "const dict &req" not in args:
                        f.write(f"\tint i = this->api->{name}({end_args_str});\n")
                        f.write("\treturn i;\n")
                        f.write("};\n\n")
                    else:
                        f.write(f"\t{struct_type} myreq = {struct_type}();\n")
                        f.write("\tmemset(&myreq, 0, sizeof(myreq));\n")

                        struct_fields = self.structs[struct_type]
                        for struct_field, struct_type in struct_fields.items():
                            if struct_type == "char":
                                line = f"\tgetString(req, \"{struct_field}\", myreq.{struct_field});\n"
                            else:
                                line = f"\tget{struct_type.capitalize()}(req, \"{struct_field}\", &myreq.{struct_field});\n"
                            f.write(line)

                        f.write(f"\tint i = this->api->{name}({end_args_str});\n")
                        f.write("\treturn i;\n")
                        f.write("};\n\n")

    def generate_source_on(self):
        """"""
        filename = f"{self.prefix}_{self.name}_source_on.cpp"
        with open(filename, "w") as f:
            for name, d in self.callbacks.items():
                on_name = name.replace("On", "on")

                args = []
                bind_args = ["void", self.class_name, on_name]
                for field, type_ in d.items():
                    if type_ == "int":
                        args.append(f"int {field}")
                        bind_args.append(field)
                    elif type_ == "bool":
                        args.append("bool last")
                        bind_args.append("last")
                    elif type_ == "ErrorInfo":
                        args.append("const dict &error")
                        bind_args.append("error")
                    elif type_ == "char":
                        args.append(f"string {field}")
                        bind_args.append(field)
                    elif type_ == "int32_t" or type_ == "int64_t" or type_ == "int16_t":
                        args.append(f"int {field}")
                        bind_args.append(field)
                    else:
                        args.append("const dict &data")
                        bind_args.append("data")

                args_str = ", ".join(args)
                bind_args_str = ", ".join(bind_args)

                f.write(f"void {on_name}({args_str}) override\n")
                f.write("{\n")
                f.write("\ttry\n")
                f.write("\t{\n")
                f.write(f"\t\tPYBIND11_OVERLOAD({bind_args_str});\n")
                f.write("\t}\n")
                f.write("\tcatch (const error_already_set &e)\n")
                f.write("\t{\n")
                f.write(f"\t\tcout << e.what() << endl;\n")
                f.write("\t}\n")
                f.write("};\n\n")

    def generate_source_module(self):
        """"""
        filename = f"{self.prefix}_{self.name}_source_module.cpp"
        with open(filename, "w") as f:
            for name in self.functions.keys():
                function_name = name[0].lower() + name[1:]
                f.write(f".def(\"{function_name}\", &{self.class_name}::{function_name})\n")

            f.write("\n")

            for name in self.callbacks.keys():
                name = name.replace("On", "on")
                f.write(f".def(\"{name}\", &{self.class_name}::{name})\n")

            f.write(";\n")


if __name__ == "__main__":
    td_generator = ApiGenerator("../include/hft/hft_trader_api_.h", "hft", "hft", "HftApi")
    td_generator.run()
