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
        module_name = f"{self.prefix}_{self.name}_struct"
        module = importlib.import_module(module_name)

        for name in dir(module):
            if "__" not in name:
                self.structs[name] = getattr(module, name)

    def run(self):
        """运行生成"""
        self.f_cpp = open(self.filename, "r")

        for line in self.f_cpp:
            self.process_line(line)

        self.f_cpp.close()

        self.generate_header_on()
        self.generate_header_function()

        self.generate_source_task()
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
        elif "virtual bool Req" in line:
            self.process_function(line)

    def process_callback(self, line: str):
        """处理回掉函数"""
        name = line[line.index("On"):line.index("(")]
        self.lines[name] = line

        d = self.generate_arg_dict(line)
        self.callbacks[name] = d

    def process_function(self, line: str):
        """处理主动函数"""
        name = line[line.index("Req"):line.index("(")]

        d = self.generate_arg_dict(line)
        self.functions[name] = d

    def generate_arg_dict(self, line: str):
        """生成参数字典"""
        args_str = line[line.index("(") + 1:line.index(")")]
        if not args_str:
            return {}
        args = args_str.split(",")

        d = {}
        for arg in args:
            arg = arg.replace("const ", "")
            words = arg.split(" ")
            words = [word for word in words if word]
            d[words[1].replace("*", "")] = words[0]
        return d

    def generate_header_on(self):
        """"""
        filename = f"{self.prefix}_{self.name}_header_on.h"
        with open(filename, "w") as f:
            for name, d in self.callbacks.items():
                name = name.replace("On", "on")

                args_list = []

                for type_ in d.values():
                    if type_ == "int":
                        args_list.append("int reqid")
                    elif type_ == "bool":
                        args_list.append("bool last")
                    elif "RspInfoField" in type_:
                        args_list.append("const dict &error")
                    else:
                        args_list.append("const dict &data")

                args_str = ", ".join(args_list)
                line = f"virtual void {name}({args_str}) {{}};\n\n"

                f.write(line)

    def generate_header_function(self):
        """"""
        filename = f"{self.prefix}_{self.name}_header_function.h"
        with open(filename, "w") as f:
            for name in self.functions.keys():
                name = name.replace("Req", "req")
                line = f"int {name}(const dict &req, int reqid);\n\n"
                f.write(line)

    def generate_source_task(self):
        """"""
        filename = f"{self.prefix}_{self.name}_source_task.cpp"
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
                    elif type_ == "bool":
                        args.append(field)
                    elif type_ == "char*":
                        args.append(f"string({field})")
                    elif "RspInfoField" in type_:
                        args.append("error")

                        f.write("\tdict error;\n")
                        f.write("\tif (pRspInfo)\n")
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
                        f.write(f"\tif ({field})\n")
                        f.write("\t{\n")

                        struct_fields = self.structs[type_]
                        for struct_field, struct_type in struct_fields.items():
                            if struct_type == "string":
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
                req_name = name.replace("Req", "req")
                type_ = list(d.values())[0]

                f.write(
                    f"int {self.class_name}::{req_name}(const dict &req, int reqid)\n")
                f.write("{\n")
                f.write(f"\t{type_} myreq = {type_}();\n")
                f.write("\tmemset(&myreq, 0, sizeof(myreq));\n")

                struct_fields = self.structs[type_]
                for struct_field, struct_type in struct_fields.items():
                    if struct_type == "string":
                        line = f"\tgetString(req, \"{struct_field}\", myreq.{struct_field});\n"
                    else:
                        line = f"\tget{struct_type.capitalize()}(req, \"{struct_field}\", &myreq.{struct_field});\n"
                    f.write(line)

                f.write(f"\tint i = this->api->{name}(&myreq, reqid);\n")
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
                        args.append("int reqid")
                        bind_args.append("reqid")
                    elif type_ == "bool":
                        args.append("bool last")
                        bind_args.append("last")
                    elif "RspInfoField" in type_:
                        args.append("const dict &error")
                        bind_args.append("error")
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
                name = name.replace("Req", "req")
                f.write(f".def(\"{name}\", &{self.class_name}::{name})\n")

            f.write("\n")

            for name in self.callbacks.keys():
                name = name.replace("On", "on")
                f.write(f".def(\"{name}\", &{self.class_name}::{name})\n")

            f.write(";\n")


if __name__ == "__main__":
    market_generator = ApiGenerator(
        "../include/da/DAMarketApi.h", "da", "market", "MarketApi")
    market_generator.run()

    future_generator = ApiGenerator(
        "../include/da/DAFutureApi.h", "da", "future", "FutureApi")
    future_generator.run()

    stock_generator = ApiGenerator(
        "../include/da/DAStockApi.h", "da", "stock", "StockApi")
    stock_generator.run()
