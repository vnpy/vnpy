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

    def run(self):
        """运行生成"""
        self.f_cpp = open(self.filename, "r")

        for line in self.f_cpp:
            self.process_line(line)

        self.f_cpp.close()

        self.generate_header_define()
        self.generate_header_process()
        self.generate_header_on()
        self.generate_header_function()

        self.generate_source_task()
        self.generate_source_switch()
        self.generate_source_process()
        self.generate_source_function()
        self.generate_source_on()
        self.generate_source_module()

        print(f"{self.prefix} API生成成功")

    def process_line(self, line: str):
        """处理每行"""
        line = line.replace(";", "")
        line = line.replace("\n", "")
        line = line.replace("\t", "")
        line = line.replace("{}", "")

        if "virtual void On" in line:
            self.process_callback(line)
        elif "virtual int Req" in line:
            self.process_function(line)

        elif "virtual int Sub" in line or "virtual int UnSub" in line:
            self.process_function_sub(line)

    def process_callback(self, line: str):
        """处理回掉函数"""
        name = line[line.index("On"):line.index("(")]
        self.lines[name] = line

        d = self.generate_arg_dict(line)
        self.callbacks[name] = d

    def process_function_sub(self, line: str):
        """处理主动函数"""

        if "virtual int Sub" in line:
            name = line[line.index("Sub"):line.index("(")]

            d = self.generate_arg_dict(line)
            self.functions[name] = d
        elif "virtual int UnSub" in line:
            name = line[line.index("UnSub"):line.index("(")]

            d = self.generate_arg_dict(line)
            self.functions[name] = d

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
            words = arg.split(" ")
            words = [word for word in words if word]

            name = words[1].replace("*", "")
            if "[" in name:
                name = name.split("[")[0]
            d[name] = words[0].replace("*", "")
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
                        args_list.append(f"bool {name_}")
                    elif type_ == "char":
                        args_list.append("string tickers")
                    elif type_ == "CIStoneRspInfo":
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
            for name, values in self.functions.items():

                if "Req" in name:
                    name = name.replace("Req", "req")
                    line = f"int {name}(const dict &req, int reqid);\n\n"
                    f.write(line)
                elif "UnSub" in name:
                    name = name.replace("UnSub", "unsub")
                    content = ""

                    for k, v in values.items():
                        if v == "char":
                            v = "string"
                        combo = f"{v} {k},"

                        content = content + combo

                    content = content[:-1]

                    line = f"int {name}({content});\n\n"
                    f.write(line)
                elif "Sub" in name:
                    name = name.replace("Sub", "Sub")
                    content = ""

                    for k, v in values.items():
                        if v == "char":
                            v = "string"
                        combo = f"{v} {k},"

                        content = content + combo

                    content = content[:-1]
                    line = f"int {name}({content});\n\n"

    def generate_source_task(self):
        """"""
        filename = f"{self.prefix}_{self.name}_source_task.cpp"
        with open(filename, "w") as f:
            for name, d in self.callbacks.items():
                line = self.lines[name]

                f.write(line.replace("virtual void ",
                                     f"void {self.class_name}::") + "\n")
                f.write("{\n")
                f.write("\tTask task = Task();\n")
                f.write(f"\ttask.task_name = {name.upper()};\n")

                for field, type_ in d.items():
                    if type_ == "int":
                        if field == "nRequestID":
                            f.write(f"\ttask.task_id = {field};\n")
                        elif field == "count":
                            f.write(f"\ttask.task_count = {field};\n")
                        elif field == "exchangeID":
                            f.write(f"\ttask.task_exchange = {field};\n")
                        elif field == "tickType":
                            f.write(f"\ttask.task_tick = {field};\n")
                        else:
                            f.write(f"\ttask.task_extra = {field};\n")
                    elif type_ == "char":
                        f.write(f"\ttask.task_tickers = (char*) {field};\n")

                    elif type_ == "bool":
                        f.write(f"\ttask.task_result = {field};\n")
                    elif type_ == "CIStoneRspInfo":
                        f.write(f"\tif ({field})\n")
                        f.write("\t{\n")
                        f.write(f"\t\t{type_} *task_error = new {type_}();\n")
                        f.write(f"\t\t*task_error = *{field};\n")
                        f.write(f"\t\ttask.task_error = task_error;\n")
                        f.write("\t}\n")
                    else:
                        f.write(f"\tif ({field})\n")
                        f.write("\t{\n")
                        f.write(f"\t\t{type_} *task_data = new {type_}();\n")
                        f.write(f"\t\t*task_data = *{field};\n")
                        f.write(f"\t\ttask.task_data = task_data;\n")
                        f.write("\t}\n")

                f.write(f"\tthis->task_queue.push(task);\n")
                f.write("};\n\n")

    def generate_source_switch(self):
        """"""
        filename = f"{self.prefix}_{self.name}_source_switch.cpp"
        with open(filename, "w") as f:
            for name in self.callbacks.keys():
                process_name = name.replace("On", "process")
                f.write(f"case {name.upper()}:\n")
                f.write("{\n")
                f.write(f"\tthis->{process_name}(&task);\n")
                f.write(f"\tbreak;\n")
                f.write("}\n\n")

    def generate_source_process(self):
        """"""
        filename = f"{self.prefix}_{self.name}_source_process.cpp"
        with open(filename, "w") as f:
            for name, d in self.callbacks.items():
                process_name = name.replace("On", "process")
                on_name = name.replace("On", "on")

                f.write(
                    f"void {self.class_name}::{process_name}(Task *task)\n")
                f.write("{\n")
                f.write("\tgil_scoped_acquire acquire;\n")

                args = []

                for field, type_ in d.items():
                    if type_ == "int":
                        if field == "nRequestID":
                            args.append("task->task_id")
                        elif field == "count":
                            args.append("task->task_count")
                        elif field == "exchangeID":
                            args.append("task->task_exchange")
                        elif field == "tickType":
                            args.append("task->task_tick")
                        else:
                            args.append("task->task_extra")
                    elif type_ == "char":
                        args.append("task->task_tickers")
                    elif type_ == "bool":
                        args.append("task->task_result")
                    elif type_ == "CIStoneRspInfo":
                        args.append("error")

                        f.write("\tdict error;\n")
                        f.write("\tif (task->task_error)\n")
                        f.write("\t{\n")
                        f.write(
                            f"\t\t{type_} *task_error = ({type_}*)task->task_error;\n")

                        struct_fields = self.structs[type_]
                        for struct_field, struct_type in struct_fields.items():
                            if struct_type == "char":
                                f.write(
                                    f"\t\terror[\"{struct_field}\"] = toUtf(task_error->{struct_field});\n")
                            else:
                                f.write(
                                    f"\t\terror[\"{struct_field}\"] = task_error->{struct_field};\n")

                        f.write("\t\tdelete task_error;\n")
                        f.write("\t}\n")
                    else:
                        args.append("data")

                        f.write("\tdict data;\n")
                        f.write("\tif (task->task_data)\n")
                        f.write("\t{\n")
                        f.write(
                            f"\t\t{type_} *task_data = ({type_}*)task->task_data;\n")

                        struct_fields = self.structs[type_]
                        for struct_field, struct_type in struct_fields.items():
                            if struct_type == "char":
                                f.write(
                                    f"\t\tdata[\"{struct_field}\"] = toUtf(task_data->{struct_field});\n")
                            else:
                                f.write(
                                    f"\t\tdata[\"{struct_field}\"] = task_data->{struct_field};\n")

                        f.write("\t\tdelete task_data;\n")
                        f.write("\t}\n")

                args_str = ", ".join(args)
                f.write(f"\tthis->{on_name}({args_str});\n")
                f.write("};\n\n")

    def generate_source_function(self):
        """"""
        filename = f"{self.prefix}_{self.name}_source_function.cpp"
        with open(filename, "w") as f:
            for name, d in self.functions.items():

                if name == "Req":
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
                else:
                    if "UnSub" in name:
                        name = name.replace("UnSub", "unSub")
                    elif "Sub" in name:
                        name = name.replace("Sub", "sub")

                    req_name = name

                    content = ""
                    for k, v in d.items():
                        if v == "char":
                            v = "string"
                        combo = f"{v} {k},"
                        content = content + combo

                    content = content[:-1]
                    f.write(
                        f"int {self.class_name}::{req_name}({content})\n")
                    f.write("{\n")

                    content_ = ""

                    for n, t in d.items():
                        if "pReqUser" in n:
                            f.write(f"\t{t} myreq = {t}();\n")
                            f.write("\tmemset(&myreq, 0, sizeof(myreq));\n")

                            struct_fields = self.structs[t]
                            for struct_field, struct_type in struct_fields.items():
                                if struct_type == "string":
                                    line = f"\tgetString(req, \"{struct_field}\", myreq.{struct_field});\n"
                                else:
                                    line = f"\tget{struct_type.capitalize()}(req, \"{struct_field}\", &myreq.{struct_field});\n"
                                f.write(line)

                            combo = "&myreq,"
                            content_ = content_ + combo
                        else:
                            combo_ = n
                            content_ = content_ + combo_
                    content_ = content_[:-1]

                    f.write(f"\tint i = this->api->{name}({content_});\n")
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

                        if field == "nRequestID":
                            args.append("int reqid")
                            bind_args.append("reqid")
                        elif field == "count":
                            args.append("int count")
                            bind_args.append("count")
                        elif field == "exchangeID":
                            args.append("int exchange")
                            bind_args.append("exchange")
                        elif field == "tickType":
                            args.append("int tick")
                            bind_args.append("tick")
                        else:
                            args.append("int extra")
                            bind_args.append("extra")
                    elif type_ == "bool":
                        args.append("bool result")
                        bind_args.append("result")
                    elif type_ == "char":
                        args.append("string tickers")
                        bind_args.append("tickers")
                    elif type_ == "CIStoneRspInfo":
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
    md_generator = ApiGenerator(
        "../include/ihq/IStoneMdApi.h",
        "ihq",
        "md",
        "MdApi"
    )
    md_generator.run()
